#include "MeGUI.core.gui.JobWorker.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			JobWorker::JobStartException::JobStartException(const std::string &reason, ExceptionType type) : MeGUIException(reason)
			{
				this->type = type;
			}

			void JobWorker::HideProcessWindow()
			{
				if (pw != 0)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Util::ThreadSafeRun(pw, delegate
					{
						pw->Hide();
					}
				   );
			}

			void JobWorker::ShowProcessWindow()
			{
				if (pw != 0)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Util::ThreadSafeRun(pw, delegate
					{
						pw->Show();
					}
				   );
			}

			void JobWorker::pw_Abort()
			{
				UserRequestedAbort();
			}

			void JobWorker::pw_PriorityChanged(ProcessPriority priority)
			{
				try
				{
					currentProcessor->changePriority(priority);
				}
				catch (JobRunException *e)
				{
					log->LogValue("Error attempting to change priority", e, Error);
				}
			}

			const decimal &JobWorker::getProgress() const
			{
				return progress;
			}

			const MeGUI::core::details::PauseState &JobWorker::getPauseStatus() const
			{
				return pauseStatus;
			}

			const std::string &JobWorker::getStatusString() const
			{
				if (status == Idle)
					return "idle";
				if (status == Stopped)
					return "stopped";
				if (status == Postponed)
					return "postponed (another worker is processing an audio job)";
				std::string _status = "running";
				if (currentJob != 0)
					_status += std::string::Format(" {0} ({1:P2})", currentJob->getName(), progress / 100);
				if (mode == CloseOnLocalListCompleted)
					_status += " (delete worker after current job)";
				else if (status == Stopping)
					_status += " (stop worker after current job)";
				if (pauseStatus == Paused)
					_status += " (paused)";
				return _status;
			}

			const MeGUI::core::details::JobWorkerMode &JobWorker::getMode() const
			{
				return mode;
			}

			void JobWorker::setMode(const JobWorkerMode &value)
			{
				mode = value;
			}

			const MeGUI::core::details::JobWorkerStatus &JobWorker::getStatus() const
			{
				return status;
			}

			const bool &JobWorker::getIsTemporaryWorker() const
			{
				return bIsTemporaryWorker;
			}

			void JobWorker::setIsTemporaryWorker(const bool &value)
			{
				bIsTemporaryWorker = value;
			}

			void JobWorker::SetStopping()
			{
				if (status == Running)
					status = Stopping;
			}

			void JobWorker::SetRunning()
			{
				if (status == Stopping)
					status = Running;
			}

			const std::string &JobWorker::getName() const
			{
				return name;
			}

			void JobWorker::setName(const std::string &value)
			{
				name = value;
				Text = value;
			}

			const int &JobWorker::getLocalJobCount() const
			{
				return localJobs.size();
			}

			const bool &JobWorker::getIsEncoding() const
			{
				return status == Running || status == Stopping;
			}

			const bool &JobWorker::getIsEncodingAudio() const
			{
				return getIsEncoding() && currentJob != 0 && currentJob->getJob()->EncodingMode->Equals("audio");
			}

			JobWorker::JobWorker(MainForm *mf)
			{
				InitializeInstanceFields();
				mainForm = mf;

				InitializeComponent();
				jobQueue1->SetStartStopButtonsTogether();
				jobQueue1->RequestJobDeleted = new RequestJobDeleted(this, &JobWorker::GUIDeleteJob);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				jobQueue1->AddMenuItem("Return to main job queue", 0, delegate(std::vector<TaggedJob*> jobs)
				{
					for (unknown::const_iterator j = jobs.begin(); j != jobs.end(); ++j)
						mainForm->getJobs()->ReleaseJob(*j);
				}
			   );

				pw = new ProgressWindow();
				pw->Abort += new AbortCallback(this, &JobWorker::pw_Abort);
				pw->PriorityChanged += new PriorityChangedCallback(this, &JobWorker::pw_PriorityChanged);
				pw->CreateControl();
				mainForm->RegisterForm(pw);
			}

			void JobWorker::postprocessJob(Job *job)
			{
				LogItem *i = log->LogEvent("Postprocessing");
				for (MeGUI::GenericRegisterer<JobPostProcessor*>::const_iterator pp = mainForm->getPackageSystem()->getJobPostProcessors()->begin(); pp != mainForm->getPackageSystem()->getJobPostProcessors()->end(); ++pp)
				{
					LogItem *plog = pp->second->PostProcessor(mainForm, job);
					if (plog != 0)
					{
						i->Add(plog);
					}
				}
			}

			void JobWorker::preprocessJob(Job *job)
			{
				LogItem *i = log->LogEvent("Preprocessing");
				for (MeGUI::GenericRegisterer<JobPreProcessor*>::const_iterator pp = mainForm->getPackageSystem()->getJobPreProcessors()->begin(); pp != mainForm->getPackageSystem()->getJobPreProcessors()->end(); ++pp)
				{
					LogItem *plog = pp->second->PreProcessor(mainForm, job);
					if (plog != 0)
					{
						i->Add(plog);
					}
				}
			}

			MeGUI::IJobProcessor *JobWorker::getProcessor(Job *job)
			{
				for (MeGUI::GenericRegisterer<JobProcessorFactory*>::const_iterator f = mainForm->getPackageSystem()->getJobProcessors()->begin(); f != mainForm->getPackageSystem()->getJobProcessors()->end(); ++f)
				{
					IJobProcessor *p = f->second->Factory(mainForm, job);
					if (p != 0)
					{
						return p;
					}
				}
				log->Error("No processor found");
				return 0;
			}

			void JobWorker::ShutDown()
			{
				if (getIsEncoding())
					Abort();
				returnJobsToMainQueue();
				mainForm->getJobs()->ShutDown(this);
			}

			void JobWorker::UserRequestShutDown()
			{
				DialogResult *r = MessageBox::Show("Do you really want to delete this job worker?", "Really delete?", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
				if (r == System::Windows::Forms::DialogResult::Yes)
					ShutDown();
			}

			void JobWorker::returnJobsToMainQueue()
			{
				std::vector<TaggedJob*> list = std::vector<TaggedJob*>(localJobs.Values);
				for (std::vector<TaggedJob*>::const_iterator j = list.begin(); j != list.end(); ++j)
					mainForm->getJobs()->ReleaseJob(*j);
			}

			void JobWorker::GUIDeleteJob(TaggedJob *j)
			{
				mainForm->getJobs()->DeleteJob(j);
			}

			void JobWorker::refreshAll()
			{
				jobQueue1->refreshQueue();
				switch (getStatus())
				{
					case Idle:
						jobQueue1->setStartStopMode(Start);
						jobQueue1->setPauseResumeMode(Disabled);
						break;

					case Postponed:
						jobQueue1->setStartStopMode(Start);
						jobQueue1->setPauseResumeMode(Disabled);
						break;

					case Stopped:
						jobQueue1->setStartStopMode(Start);
						jobQueue1->setPauseResumeMode(Disabled);
						break;

					case Running:
						jobQueue1->setStartStopMode(Stop);
						jobQueue1->setPauseResumeMode((pauseStatus == Paused) ? Resume : Pause);
						break;

					case Stopping:
						jobQueue1->setStartStopMode(Start);
						jobQueue1->setPauseResumeMode((pauseStatus == Paused) ? Resume : Pause);
						break;
				}
				updateProgress();
				mainForm->getJobs()->refresh();
			}

			void JobWorker::updateProgress()
			{
				if (this->InvokeRequired)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						jobProgress->Value = static_cast<int>(getProgress());
					}
				   ));
				else
					jobProgress->Value = static_cast<int>(getProgress());
				if (alive)
					mainForm->getJobs()->UpdateProgress(this->getName());
			}

			void JobWorker::Abort()
			{
				assert(getIsEncoding());
				if (currentProcessor == 0 || currentJob->getStatus() == ABORTING)
					return;
				try
				{
					currentJob->setStatus(ABORTING);
					refreshAll();
					currentProcessor->stop();
				}
				catch (JobRunException *er)
				{
					mainForm->getLog()->LogValue("Error attempting to stop processing", er, Error);
				}
				markJobAborted();
				status = Stopped;
				refreshAll();
			}

			void JobWorker::StartEncoding(bool showMessageBoxes)
			{
				status = Idle;
				JobStartInfo retval = startNextJobInQueue();
				if (showMessageBoxes)
				{
					if (retval == COULDNT_START)
						MessageBox::Show("Couldn't start processing. Please consult the log for more details", "Processing failed", MessageBoxButtons::OK);
					else if (retval == NO_JOBS_WAITING)
						MessageBox::Show("No jobs are waiting or can be processed at the moment.\r\nOnly one audio job can run at a time and there may be\r\nsome dependencies which have to be fulfilled first.", "No jobs waiting", MessageBoxButtons::OK);
				}
			}

			void JobWorker::copyInfoIntoJob(TaggedJob *job, StatusUpdate *su)
			{
				assert(su->getIsComplete());

				job->setEnd(DateTime::Now);
				job->EncodingSpeed = su->getProcessingSpeed();

				if (su->getWasAborted())
					job->setStatus(ABORTED);
				else if (su->getHasError())
					job->setStatus(ERROR);
			}

			void JobWorker::UpdateGUIStatus(StatusUpdate *su)
			{
				if (su->getIsComplete())
				{
					MeGUI::core::util::WindowUtil::AllowSystemPowerdown();
					// so we don't lock up the GUI, we start a new thread
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Thread *t = new Thread(new ThreadStart(delegate
						// Postprocessing
						// Logging
					{
						TaggedJob *job = mainForm->getJobs()->ByName(su->getJobName());
						JobStartInfo JobInfo = JOB_STARTED;
						copyInfoIntoJob(job, su);
						progress = 0;
						HideProcessWindow();
						bool jobFailed = (job->getStatus() != PROCESSING);
						if (!jobFailed)
						{
							postprocessJob(job->getJob());
							job->setStatus(DONE);
						}
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
						delete currentProcessor;
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
						delete currentJob;
						log->LogEvent("Job completed");
						log->Collapse();
						if (!jobFailed && mainForm->getSettings()->getDeleteCompletedJobs())
							mainForm->getJobs()->RemoveCompletedJob(job);
							else
								mainForm->getJobs()->saveJob(job, mainForm->getMeGUIPath());
								if (mode == CloseOnLocalListCompleted && shutdownWorkerIfJobsCompleted())
								{
									MeGUI::core::util::WindowUtil::AllowSystemPowerdown();
									JobInfo = COULDNT_START;
								}
								else if (job->getStatus() == ABORTED)
								{
									MeGUI::core::util::WindowUtil::AllowSystemPowerdown();
									log->LogEvent("Current job was aborted");
									status = Stopped;
									JobInfo = COULDNT_START;
								}
								else if (status == Stopping)
								{
									MeGUI::core::util::WindowUtil::AllowSystemPowerdown();
									log->LogEvent("Queue mode stopped");
									status = Stopped;
									JobInfo = COULDNT_START;
								}
								else
								{
									JobInfo = startNextJobInQueue();
									switch (JobInfo)
									{
										case JOB_STARTED:
											MeGUI::core::util::WindowUtil::PreventSystemPowerdown();
											break;
											case COULDNT_START:
												MeGUI::core::util::WindowUtil::AllowSystemPowerdown();
												if (status != Postponed)
													status = Idle;
													break;
													case NO_JOBS_WAITING:
														MeGUI::core::util::WindowUtil::AllowSystemPowerdown();
														if (status != Postponed)
															status = Idle;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
															new Thread(delegate()
															{
																WorkerFinishedJobs(this, EventArgs::Empty);
															}
														   ).Start();
															break;
									}
								}
								if (JobInfo == JOB_STARTED)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
									Util::ThreadSafeRun(mainForm->getJobs(), delegate
									{
										mainForm->getJobs()->StartIdleWorkers();
									}
								   );
									refreshAll();
					}
				   ));
					t->IsBackground = true;
					t->Start();
				}
				else // job is not complete yet
				{
					try
					{
						if (pw->IsHandleCreated && pw->Visible) // the window is there, send the update to the window
						{
							TaggedJob *job = mainForm->getJobs()->ByName(su->getJobName());
							su->setJobStatus(job->getStatus());
							pw->BeginInvoke(new UpdateStatusCallback(pw->UpdateStatus), su);
						}
					}
					catch (std::exception &e)
					{
						mainForm->getLog()->LogValue("Error trying to update status while a job is running", e, Warning);
					}

					if (su->getPercentageDoneExact() > 100)
						progress = 100;
					else
						Nullable<decimal> tempVar = su.getPercentageDoneExact();
						progress = tempVar::HasValue ? tempVar : 0;
					updateProgress();
				}
			}

			bool JobWorker::shutdownWorkerIfJobsCompleted()
			{
				for (std::map<std::string, TaggedJob*>::const_iterator j = localJobs.begin(); j != localJobs.end(); ++j)
					if (j->second->Status == WAITING)
						return false; // do not shut down as jobs are waiting

				ShutDown();
				return true;
			}

			bool JobWorker::startEncoding(TaggedJob *job)
			{
				try
				{
					log = mainForm->getLog()->Info(std::string::Format("Log for {0} ({1}, {2} -> {3})", job->getName(), job->getJob()->EncodingMode, job->getInputFileName(), job->getOutputFileName()));
					log->LogEvent("Started handling job");
					log->Expand();

					status = Running;
					MeGUI::core::util::WindowUtil::PreventSystemPowerdown();

					//Check to see if output file already exists before encoding.
					if (File::Exists(job->getJob()->Output) && !mainForm->getDialogManager()->overwriteJobOutput(job->getJob()->Output))
						throw new JobStartException("File exists and the user doesn't want to overwrite", UserSkip);

					// Get IJobProcessor
					currentProcessor = getProcessor(job->getJob());
					if (currentProcessor == 0)
						throw new JobStartException("No processor could be found", Error);


					// Preprocess
					preprocessJob(job->getJob());

					// Setup
					try
					{
						currentProcessor->setup(job->getJob(), new StatusUpdate(job->getName()), log);
					}
					catch (JobRunException *e)
					{
						throw new JobStartException("Calling setup of processor failed with error '" + e->Message + "'", Error);
					}

					if (currentProcessor == 0)
					{
						throw new JobStartException("starting job failed", Error);
					}

					// Do JobControl setup
					currentProcessor->StatusUpdate += new JobProcessingStatusUpdateCallback(this, &JobWorker::UpdateGUIStatus);

					// Progress window
					pw->setPriority(mainForm->getSettings()->getProcessingPriority());
					if (mainForm->getSettings()->getOpenProgressWindow() && mainForm->Visible)
						this->ShowProcessWindow();

					job->setStatus(PROCESSING);
					job->setStart(DateTime::Now);
					status = Running;
					pauseStatus = Encoding;
					currentJob = job;

					// Start
					try
					{
						currentProcessor->start();
					}
					catch (JobRunException *e)
					{
						throw new JobStartException("starting job failed with error '" + e->Message + "'", Error);
					}

					refreshAll();
					return true;
				}
				catch (JobStartException *e)
				{
					this->HideProcessWindow();
					log->LogValue("Error starting job", e);
					if (e->type == Error)
						job->setStatus(ERROR);
					else // ExceptionType.UserSkip
						job->setStatus(SKIP);
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete currentProcessor;
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete currentJob;
					status = Idle;
					pauseStatus = NotEncoding;
					refreshAll();
					return false;
				}

			}

			MeGUI::core::details::TaggedJob *JobWorker::getNextJob()
			{
				for (IEnumerable<TaggedJob*>::const_iterator j = jobQueue1->getJobList()->begin(); j != jobQueue1->getJobList()->end(); ++j)
					if ((*j)->getStatus() == WAITING && mainForm->getJobs()->areDependenciesMet(*j))
						return j;
				if (mode == RequestNewJobs)
					return mainForm->getJobs()->getJobToProcess();
				else
					return 0;
			}

			MeGUI::core::details::JobStartInfo JobWorker::startNextJobInQueue()
			{
				mainForm->getJobs()->getResourceLock()->WaitOne(10000, false);

				TaggedJob *job = getNextJob();

				if (job == 0)
				{
					status = Idle;
					mainForm->getJobs()->getResourceLock()->Release();
					return NO_JOBS_WAITING;
				}

				while (job != 0)
				{
					if (job->getJob()->EncodingMode->Equals("audio") && mainForm->getJobs()->getIsAnyWorkerEncodingAudio())
					{
						// another audio encoding is already in process. postpone the worker
						status = Postponed;
						mainForm->getJobs()->getResourceLock()->Release();
						return NO_JOBS_WAITING;
					}

					if (startEncoding(job)) // successful
					{
						mainForm->getJobs()->getResourceLock()->Release();
						return JOB_STARTED;
					}
					job = getNextJob();
				}
				status = Idle;
				mainForm->getJobs()->getResourceLock()->Release();
				return COULDNT_START;
			}

			void JobWorker::markJobAborted()
			{
				if (currentJob == 0)
					return;
				TaggedJob *job = currentJob;
				job->setStatus(ABORTED);
				job->setEnd(DateTime::Now);
				long long iCounter = 0;

				LogItem *i = new LogItem("Deleting aborted output");

				i->LogValue("Delete aborted output set", mainForm->getSettings()->getDeleteAbortedOutput());

				if (mainForm->getSettings()->getDeleteAbortedOutput() && File::Exists(job->getJob()->Output))
				{
					i->LogValue("File to delete", job->getJob()->Output);
					while (File::Exists(job->getJob()->Output))
					{
						try
						{
							File::Delete(job->getJob()->Output);
						}
						catch (std::exception &e)
						{
							if (++iCounter >= 3)
							{
								i->LogValue("Problem deleting file", e.what(), Warning);
								break;
							}
							else
								delay(2000);
						}
					}
					if (!File::Exists(job->getJob()->Output))
						i->LogEvent("File deleted");
				}
				log->Add(i);
			}

			void JobWorker::Pause()
			{
				assert(pauseStatus == Encoding);
				try
				{
					currentProcessor->pause();
					pauseStatus = Paused;
					refreshAll();
				}
				catch (JobRunException *ex)
				{
					mainForm->getLog()->LogValue("Error trying to pause encoding", ex, Warning);
				}
			}

			void JobWorker::Resume()
			{
				assert(pauseStatus == Paused);
				try
				{
					currentProcessor->resume();
					pauseStatus = Encoding;
				}
				catch (JobRunException *ex)
				{
					mainForm->getLog()->LogValue("Error trying to resume encoding", ex, Warning);
				}
			}

			void JobWorker::OnClosing(CancelEventArgs *e)
			{
				if (!alive)
				{
					System::Windows::Forms::Form::OnClosing(e);
					return;
				}
				e->Cancel = true;
				Hide();
			}

			void JobWorker::RemoveJobFromQueue(TaggedJob *job)
			{
				localJobs.erase(job->getName());
				jobQueue1->removeJobFromQueue(job);
			}

			void JobWorker::UserRequestedAbort()
			{
				if (currentJob->getStatus() == ABORTED || currentJob->getStatus() == ABORTING)
				{
					MessageBox::Show("Job already aborting. Please wait.", "Abort in progress", MessageBoxButtons::OK);
					return;
				}
				DialogResult *r = MessageBox::Show("Do you really want to abort?", "Really abort?", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
				if (r == System::Windows::Forms::DialogResult::Yes)
					Abort();
			}

			const IEnumerable<TaggedJob*> &JobWorker::getJobs() const
			{
				return jobQueue1->getJobList();
			}

			void JobWorker::setJobs(const IEnumerable<TaggedJob*> &value)
			{
				jobQueue1->setJobList(value);
			}

			void JobWorker::UserRequestedRename()
			{
				try
				{
					std::string name = InputBox::Show("Please enter the new name for this worker", "Please enter the new name", "New Worker Name");
					if (name != "")
						setName(name);
				}
				catch (NameTakenException *ex)
				{
					MessageBox::Show("The name you entered, '" + ex->getName() + "' is already in use. The worker was not renamed.", "Worker not renamed", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}

			}

			void JobWorker::ShutDownWhenFinished()
			{
				shutDownWhenFinishedLocalQueueToolStripMenuItem->Checked = !shutDownWhenFinishedLocalQueueToolStripMenuItem->Checked;
				if (shutDownWhenFinishedLocalQueueToolStripMenuItem->Checked)
				{
					if (localJobs.empty() && status == Idle)
						UserRequestShutDown();
					else
						mode = CloseOnLocalListCompleted;
				}
				else
					mode = RequestNewJobs;
			}

			void JobWorker::changeNameToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				UserRequestedRename();
			}

			void JobWorker::setName(const std::string &p)
			{
				mainForm->getJobs()->RenameWorker(this->name, p); // throws NameTakenException if it fails
			}

			void JobWorker::shutDownWhenFinishedLocalQueueToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				ShutDownWhenFinished();
			}

			void JobWorker::shutDownWorkerNowToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				UserRequestShutDown();
			}

			void JobWorker::showProgressWindowToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				if (showProgressWindowToolStripMenuItem->Checked)
					HideProcessWindow();
				else
					ShowProcessWindow();
			}

			void JobWorker::RefreshInfo()
			{
				throw std::exception("The method or operation is not implemented.");
			}

			void JobWorker::jobQueue1_AbortClicked(object *sender, EventArgs *e)
			{
				UserRequestedAbort();
			}

			void JobWorker::jobQueue1_StartClicked(object *sender, EventArgs *e)
			{
				if (getStatus() == Stopping)
					SetRunning();
				else
				{
					assert(getStatus() == Idle || getStatus() == Postponed);
					StartEncoding(true);
				}
			}

			void JobWorker::jobQueue1_StopClicked(object *sender, EventArgs *e)
			{
				if (getStatus() == Running)
					SetStopping();
			}

			void JobWorker::AddJob(TaggedJob *j)
			{
				j->setOwningWorker(this->getName());
				jobQueue1->queueJob(j);
				localJobs[j->getName()] = j;
			}

			const bool &JobWorker::getIsProgressWindowAvailable() const
			{
				return getIsEncoding();
			}

			const bool &JobWorker::getIsProgressWindowVisible() const
			{
				return (pw != 0 && pw->Visible);
			}

			void JobWorker::progressWindowToolStripMenuItem_DropDownOpened(object *sender, EventArgs *e)
			{
				showProgressWindowToolStripMenuItem->Enabled = getIsProgressWindowAvailable();
				showProgressWindowToolStripMenuItem->Checked = getIsProgressWindowVisible();
			}

			void JobWorker::CloseForReal()
			{
				alive = false;
			}

			void JobWorker::JobWorker_FormClosed(object *sender, FormClosedEventArgs *e)
			{
			}

			void JobWorker::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				System::Windows::Forms::Form::Dispose(disposing);
			}

			void JobWorker::InitializeComponent()
			{
				System::Windows::Forms::GroupBox *groupBox1;
				MeGUI::core::gui::HelpButton *helpButton1;
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(JobWorker::typeid);
				this->jobQueue1 = new MeGUI::core::gui::JobQueue();
				this->panel1 = new System::Windows::Forms::Panel();
				this->progressLabel = new System::Windows::Forms::Label();
				this->jobProgress = new System::Windows::Forms::ProgressBar();
				this->flowLayoutPanel2 = new System::Windows::Forms::FlowLayoutPanel();
				this->menuStrip1 = new System::Windows::Forms::MenuStrip();
				this->workerToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->changeNameToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->toolStripSeparator1 = new System::Windows::Forms::ToolStripSeparator();
				this->shutDownWhenFinishedLocalQueueToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->shutDownWorkerNowToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->progressWindowToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->showProgressWindowToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				groupBox1 = new System::Windows::Forms::GroupBox();
				helpButton1 = new MeGUI::core::gui::HelpButton();
				groupBox1->SuspendLayout();
				this->panel1->SuspendLayout();
				this->flowLayoutPanel2->SuspendLayout();
				this->menuStrip1->SuspendLayout();
				this->SuspendLayout();
				// 
				// groupBox1
				// 
				groupBox1->Controls->Add(this->jobQueue1);
				groupBox1->Controls->Add(this->panel1);
				groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
				groupBox1->Location = new System::Drawing::Point(4, 28);
				groupBox1->Name = "groupBox1";
				groupBox1->Size = new System::Drawing::Size(635, 201);
				groupBox1->TabIndex = 33;
				groupBox1->TabStop = false;
				groupBox1->Text = "Worker-Local Queue";
				// 
				// jobQueue1
				// 
				this->jobQueue1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->jobQueue1->Location = new System::Drawing::Point(3, 17);
				this->jobQueue1->Name = "jobQueue1";
				this->jobQueue1->Padding = new System::Windows::Forms::Padding(2);
				this->jobQueue1->setPauseResumeMode(MeGUI::core::gui::Disabled);
				this->jobQueue1->Size = new System::Drawing::Size(629, 155);
				this->jobQueue1->setStartStopMode(MeGUI::core::gui::Start);
				this->jobQueue1->TabIndex = 0;
				this->jobQueue1->AbortClicked += new System::EventHandler(this, &JobWorker::jobQueue1_AbortClicked);
				this->jobQueue1->StartClicked += new System::EventHandler(this, &JobWorker::jobQueue1_StartClicked);
				this->jobQueue1->StopClicked += new System::EventHandler(this, &JobWorker::jobQueue1_StopClicked);
				// 
				// panel1
				// 
				this->panel1->AutoSize = true;
				this->panel1->Controls->Add(this->progressLabel);
				this->panel1->Controls->Add(this->jobProgress);
				this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
				this->panel1->Location = new System::Drawing::Point(3, 172);
				this->panel1->Name = "panel1";
				this->panel1->Size = new System::Drawing::Size(629, 26);
				this->panel1->TabIndex = 2;
				// 
				// progressLabel
				// 
				this->progressLabel->Dock = System::Windows::Forms::DockStyle::Left;
				this->progressLabel->Location = new System::Drawing::Point(0, 0);
				this->progressLabel->Margin = new System::Windows::Forms::Padding(3);
				this->progressLabel->Name = "progressLabel";
				this->progressLabel->Padding = new System::Windows::Forms::Padding(0, 5, 0, 5);
				this->progressLabel->Size = new System::Drawing::Size(55, 26);
				this->progressLabel->TabIndex = 29;
				this->progressLabel->Text = "Progress";
				this->progressLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				// 
				// jobProgress
				// 
				this->jobProgress->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
				this->jobProgress->Location = new System::Drawing::Point(58, 3);
				this->jobProgress->Margin = new System::Windows::Forms::Padding(0);
				this->jobProgress->Name = "jobProgress";
				this->jobProgress->Size = new System::Drawing::Size(571, 23);
				this->jobProgress->TabIndex = 30;
				// 
				// helpButton1
				// 
				helpButton1->setArticleName("Parallel job execution");
				helpButton1->AutoSize = true;
				helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				helpButton1->Location = new System::Drawing::Point(3, 3);
				helpButton1->Name = "helpButton1";
				helpButton1->Size = new System::Drawing::Size(38, 23);
				helpButton1->TabIndex = 36;
				// 
				// flowLayoutPanel2
				// 
				this->flowLayoutPanel2->AutoSize = true;
				this->flowLayoutPanel2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->flowLayoutPanel2->Controls->Add(helpButton1);
				this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Bottom;
				this->flowLayoutPanel2->Location = new System::Drawing::Point(4, 229);
				this->flowLayoutPanel2->Name = "flowLayoutPanel2";
				this->flowLayoutPanel2->Size = new System::Drawing::Size(635, 29);
				this->flowLayoutPanel2->TabIndex = 36;
				// 
				// menuStrip1
				// 
				this->menuStrip1->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->workerToolStripMenuItem, this->progressWindowToolStripMenuItem});
				this->menuStrip1->Location = new System::Drawing::Point(4, 4);
				this->menuStrip1->Name = "menuStrip1";
				this->menuStrip1->Size = new System::Drawing::Size(635, 24);
				this->menuStrip1->TabIndex = 37;
				this->menuStrip1->Text = "menuStrip1";
				// 
				// workerToolStripMenuItem
				// 
				this->workerToolStripMenuItem->DropDownItems->AddRange(new System::Windows::Forms::ToolStripItem[4] {this->changeNameToolStripMenuItem, this->toolStripSeparator1, this->shutDownWhenFinishedLocalQueueToolStripMenuItem, this->shutDownWorkerNowToolStripMenuItem});
				this->workerToolStripMenuItem->Name = "workerToolStripMenuItem";
				this->workerToolStripMenuItem->Size = new System::Drawing::Size(57, 20);
				this->workerToolStripMenuItem->Text = "Worker";
				// 
				// changeNameToolStripMenuItem
				// 
				this->changeNameToolStripMenuItem->Name = "changeNameToolStripMenuItem";
				this->changeNameToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F2;
				this->changeNameToolStripMenuItem->Size = new System::Drawing::Size(311, 22);
				this->changeNameToolStripMenuItem->Text = "Rename worker";
				this->changeNameToolStripMenuItem->Click += new System::EventHandler(this, &JobWorker::changeNameToolStripMenuItem_Click);
				// 
				// toolStripSeparator1
				// 
				this->toolStripSeparator1->Name = "toolStripSeparator1";
				this->toolStripSeparator1->Size = new System::Drawing::Size(308, 6);
				// 
				// shutDownWhenFinishedLocalQueueToolStripMenuItem
				// 
				this->shutDownWhenFinishedLocalQueueToolStripMenuItem->Name = "shutDownWhenFinishedLocalQueueToolStripMenuItem";
				this->shutDownWhenFinishedLocalQueueToolStripMenuItem->Size = new System::Drawing::Size(311, 22);
				this->shutDownWhenFinishedLocalQueueToolStripMenuItem->Text = "Delete worker when finished local queue";
				this->shutDownWhenFinishedLocalQueueToolStripMenuItem->Click += new System::EventHandler(this, &JobWorker::shutDownWhenFinishedLocalQueueToolStripMenuItem_Click);
				// 
				// shutDownWorkerNowToolStripMenuItem
				// 
				this->shutDownWorkerNowToolStripMenuItem->Name = "shutDownWorkerNowToolStripMenuItem";
				this->shutDownWorkerNowToolStripMenuItem->ShortcutKeys = (static_cast<System::Windows::Forms::Keys*>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::W)));
				this->shutDownWorkerNowToolStripMenuItem->Size = new System::Drawing::Size(311, 22);
				this->shutDownWorkerNowToolStripMenuItem->Text = "Delete worker now";
				this->shutDownWorkerNowToolStripMenuItem->Click += new System::EventHandler(this, &JobWorker::shutDownWorkerNowToolStripMenuItem_Click);
				// 
				// progressWindowToolStripMenuItem
				// 
				this->progressWindowToolStripMenuItem->DropDownItems->AddRange(new System::Windows::Forms::ToolStripItem[1] {this->showProgressWindowToolStripMenuItem});
				this->progressWindowToolStripMenuItem->Name = "progressWindowToolStripMenuItem";
				this->progressWindowToolStripMenuItem->Size = new System::Drawing::Size(111, 20);
				this->progressWindowToolStripMenuItem->Text = "Progress Window";
				this->progressWindowToolStripMenuItem->DropDownOpened += new System::EventHandler(this, &JobWorker::progressWindowToolStripMenuItem_DropDownOpened);
				// 
				// showProgressWindowToolStripMenuItem
				// 
				this->showProgressWindowToolStripMenuItem->Name = "showProgressWindowToolStripMenuItem";
				this->showProgressWindowToolStripMenuItem->Size = new System::Drawing::Size(198, 22);
				this->showProgressWindowToolStripMenuItem->Text = "Show Progress Window";
				this->showProgressWindowToolStripMenuItem->Click += new System::EventHandler(this, &JobWorker::showProgressWindowToolStripMenuItem_Click);
				// 
				// JobWorker
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = new System::Drawing::Size(643, 262);
				this->Controls->Add(groupBox1);
				this->Controls->Add(this->flowLayoutPanel2);
				this->Controls->Add(this->menuStrip1);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->setName("JobWorker");
				this->Padding = new System::Windows::Forms::Padding(4);
				this->Text = "Job Worker Window";
				this->FormClosed += new System::Windows::Forms::FormClosedEventHandler(this, &JobWorker::JobWorker_FormClosed);
				groupBox1->ResumeLayout(false);
				groupBox1->PerformLayout();
				this->panel1->ResumeLayout(false);
				this->flowLayoutPanel2->ResumeLayout(false);
				this->flowLayoutPanel2->PerformLayout();
				this->menuStrip1->ResumeLayout(false);
				this->menuStrip1->PerformLayout();
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void JobWorker::InitializeInstanceFields()
			{
				localJobs = std::map<std::string, TaggedJob*>();
				alive = true;
				delete components;
			}
		}
	}
}
