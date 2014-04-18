#include "JobWorker.h"

#if defined(NONE)


#endif
#if defined(NONE)

//using namespace System::Collections::Generic;
#endif
#if defined(NONE)

//using namespace System::Text;
#endif
#if defined(NONE)
using namespace MeXgui::core::gui;
#endif
#if defined(NONE)

//using namespace System::Diagnostics;
#endif
#if defined(NONE)
using namespace MeXgui::core::util;
#endif
#if defined(NONE)


#endif
#if defined(NONE)


#endif
#if defined(NONE)

//using namespace System::Threading;
#endif
namespace MeXgui
{
	namespace core
	{
		namespace details
		{

#if defined(NONE)
			const QString &NameTakenException::getName() const
			{
				return name;
			}
#endif

#if defined(NONE)
			NameTakenException::NameTakenException(const QString &name) : MeXguiException("Worker name '" + name + "' is already in use.")
			{
				this->name = name;
			}
#endif

#if defined(NONE)
			JobWorker::JobStartException::JobStartException(const QString &reason, ExceptionType type) : MeXguiException(reason)
			{
				this->type = type;
			}
#endif

#if defined(NONE)
			void JobWorker::HideProcessWindow()
			{
				if (pw != 0)
					pw->Hide();
			}
#endif

#if defined(NONE)
			void JobWorker::ShowProcessWindow()
			{
				if (pw != 0)
					pw->Show();
			}
#endif

#if defined(NONE)
			const bool &JobWorker::getProcessWindowAccessible() const
			{
				return (pw != 0);
			}
#endif

#if defined(NONE)
			void JobWorker::pw_WindowClosed(bool hideOnly)
			{
				mainForm->setProcessStatusChecked(false);
				if (!hideOnly)
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete pw;
			}
#endif

#if defined(NONE)
			void JobWorker::pw_Abort()
			{
				UserRequestedAbort();
			}
#endif

#if defined(NONE)
			void JobWorker::pw_PriorityChanged(ProcessPriority priority)
			{
				try
				{
					currentProcessor->changePriority(priority);
				}
				catch (JobRunException *e)
				{
					mainForm->addToLog("Error when attempting to change priority: " + e->Message);
				}
			}
#endif

#if defined(NONE)
			const int &JobWorker::getProgress() const
			{
				return progress;
			}
#endif

#if defined(NONE)
			const MeXgui::core::details::PauseState &JobWorker::getPauseStatus() const
			{
				return pauseStatus;
			}
#endif

#if defined(NONE)
			const MeXgui::core::details::JobWorkerMode &JobWorker::getMode() const
			{
				return mode;
			}
#endif

#if defined(NONE)
			void JobWorker::setMode(const JobWorkerMode &value)
			{
				mode = value;
			}
#endif

#if defined(NONE)
			const MeXgui::core::details::JobWorkerStatus &JobWorker::getStatus() const
			{
				return status;
			}
#endif

#if defined(NONE)
			void JobWorker::SetStopping()
			{
				assert(status == Running);
				status = Stopping;
			}
#endif

#if defined(NONE)
			void JobWorker::SetRunning()
			{
				assert(status == Stopping);
				status = Running;
			}
#endif

#if defined(NONE)
			const QString &JobWorker::getName() const
			{
				return name;
			}
#endif

#if defined(NONE)
			void JobWorker::setName(const QString &value)
			{
				mainForm->getJobs()->RenameWorker(name, value); // throws NameTakenException if it fails
				name = value;
			}
#endif

#if defined(NONE)
			const bool &JobWorker::getIsEncoding() const
			{
				return status == Running || status == Stopping;
			}
#endif

#if defined(NONE)
			JobWorker::JobWorker()
			{
				InitializeInstanceFields();
				display = new JobWorkerWindow(this);
			}
#endif

#if defined(NONE)
JobPostProcessor *const JobWorker::DeleteIntermediateFilesPostProcessor = new JobPostProcessor(new Processor(&deleteIntermediateFiles), "DeleteIntermediateFiles");
#endif

#if defined(NONE)
			void JobWorker::deleteIntermediateFiles(MainForm *mainForm, Job *job)
			{
				if (mainForm->getSettings()->getDeleteIntermediateFiles())
				{
					mainForm->addToLog("Job completed successfully and deletion of intermediate files is activated\r\n");
					for (QVector<QString>::const_iterator file = job->FilesToDelete.begin(); file != job->FilesToDelete.end(); ++file)
					{
						mainForm->addToLog("Found intermediate output file '" + (static_cast<QString>(*file)) + "', deleting...");
						try
						{
							File::Delete(*file);
							mainForm->addToLog("Deletion succeeded.\r\n");
						}
						catch (IOException *e1)
						{
							mainForm->addToLog("Deletion failed.\r\n");
						}
					}
				}
			}
#endif

#if defined(NONE)
			void JobWorker::postprocessJob(Job *job)
			{
				mainForm->addToLog("Starting postprocessing of job...\r\n");
				for (MeXgui::GenericRegisterer<JobPostProcessor*>::const_iterator pp = mainForm->getPackageSystem()->getJobPostProcessors()->begin(); pp != mainForm->getPackageSystem()->getJobPostProcessors()->end(); ++pp)
				{
					pp->second->PostProcessor(mainForm, job);
				}
				mainForm->addToLog("Postprocessing finished!\r\n");
			}
#endif

#if defined(NONE)
			void JobWorker::preprocessJob(Job *job)
			{
				mainForm->addToLog("Starting preprocessing of job...\r\n");
				for (MeXgui::GenericRegisterer<JobPreProcessor*>::const_iterator pp = mainForm->getPackageSystem()->getJobPreProcessors()->begin(); pp != mainForm->getPackageSystem()->getJobPreProcessors()->end(); ++pp)
				{
					pp->second->PreProcessor(mainForm, job);
				}
				mainForm->addToLog("Preprocessing finished!\r\n");
			}
#endif

#if defined(NONE)
			MeXgui::IJobProcessor *JobWorker::getProcessor(Job *job)
			{
				mainForm->addToLog("Looking for job processor for job...\r\n");
				for (MeXgui::GenericRegisterer<JobProcessorFactory*>::const_iterator f = mainForm->getPackageSystem()->getJobProcessors()->begin(); f != mainForm->getPackageSystem()->getJobProcessors()->end(); ++f)
				{
					IJobProcessor *p = f->second->Factory(mainForm, job);
					if (p != 0)
					{
						mainForm->addToLog("Processor found!\r\n");
						return p;
					}
				}
				mainForm->addToLog("No processor found!\r\n");
				return 0;
			}
#endif

#if defined(NONE)
			void JobWorker::ShutDown(JobsOnQueue rest)
			{
				throw std::exception("The method or operation is not implemented.");
			}
#endif

#if defined(NONE)
			void JobWorker::UserRequestShutDown()
			{
				throw std::exception("The method or operation is not implemented.");
			}
#endif

#if defined(NONE)
			void JobWorker::GUIDeleteJob(Job *j)
			{
				mainForm->getJobs()->DeleteJob(j);
					//            mainForm.Jobs
			}
#endif

#if defined(NONE)
			void JobWorker::Abort()
			{
				assert(getIsEncoding());
				if (currentProcessor == 0)
					return;
				try
				{
					currentProcessor->stop();
				}
				catch (JobRunException *er)
				{
					mainForm->addToLog("Error when trying to stop processing: " + er->Message + "\r\n");
				}
				markJobAborted();
				status = Idle;
				refreshAll();
			}
#endif

#if defined(NONE)
			void JobWorker::refreshAll()
			{
				if (display != 0)
					display->RefreshInfo();
			}
#endif

#if defined(NONE)
			void JobWorker::StartEncoding()
			{
				JobStartInfo retval = startNextJobInQueue();
				/*            if (showMessageBoxes)
				            {*/
				if (retval == COULDNT_START)
					MessageBox::Show("Couldn't start processing. Please consult the log for more details", "Processing failed", MessageBoxButtons::OK);
				else if (retval == NO_JOBS_WAITING)
					MessageBox::Show("No jobs are waiting. Nothing to do", "No jobs waiting", MessageBoxButtons::OK);
				//            }
			}
#endif

#if defined(NONE)
			void JobWorker::copyInfoIntoJob(Job *job, StatusUpdate *su)
			{
				assert(su->getIsComplete());

				job->End = DateTime::Now;
				job->EncodingSpeed = su->getProcessingSpeed();

				JobStatus s;
				if (su->getWasAborted())
					s = ABORTED;
				else if (su->getHasError())
					s = ERROR;
				else
					s = DONE;
				job->Status = s;
			}
#endif

#if defined(NONE)
			void JobWorker::UpdateGUIStatus(StatusUpdate *su)
			{
				if (su->getIsComplete())
				{
					// so we don't lock up the GUI, we start a new thread
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					new Thread(new ThreadStart(delegate
						// Logging
						// Postprocessing
					{
						Job *job = mainForm->getJobs()->ByName(su->getJobName());
						copyInfoIntoJob(job, su);
						progress = 0;
						ensureProgressWindowClosed();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
						delete currentProcessor;
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
						delete currentJob;
						addToLog("Processing ended at " + DateTime::Now::ToLongTimeString() + "\r\n");
						addToLog("----------------------" + "\r\n\r\nLog for job " + su->getJobName() + "\r\n\r\n" + su->getLog() + "\r\n----------------------\r\n");
						bool jobCompletedSuccessfully = (job->Status == DONE);
						if (jobCompletedSuccessfully)
							postprocessJob(job);
							if (jobCompletedSuccessfully && mainForm->getSettings()->getDeleteCompletedJobs())
								mainForm->getJobs()->removeCompletedJob(job);
								addToLog("End of log for " + job->Name + "\r\n" + "-------------------------------------------------------\r\n\r\n");
								if (job->Status == ABORTED)
								{
									addToLog("The current job was aborted. Stopping queue mode\r\n");
									status = Idle;
								}
								else if (status == Stopping)
								{
									addToLog("Told to stop. Stopping queue mode.\r\n");
									status = Idle;
								}
								else
									startNextJobInQueue();
									refreshAll();
					}
				   )).Start();
				}
				else // job is not complete yet
				{
					try
					{
						if (pw->IsHandleCreated) // the window is there, send the update to the window
						{
							pw->Invoke(new UpdateStatusCallback(pw->UpdateStatus), new object[] {su});
						}
					}
					catch (std::exception &e)
					{
						mainForm->addToLog("Exception when trying to update status while a job is running. Text: " + e.what() + " stacktrace: " + e.StackTrace);
					}

					progress = su->getPercentageDone();
					/*
					string percentage = (su.PercentageDoneExact ?? 0M).ToString("##.##");
					if (percentage.IndexOf(".") != -1 && percentage.Substring(percentage.IndexOf(".")).Length == 1)
					    percentage += "0";
					mainForm.TitleText = "MeXgui " + su.JobName + " " + percentage + "% ";
					if (mainForm.Settings.AfterEncoding == AfterEncoding.Shutdown)
					    mainForm.TitleText += "- SHUTDOWN after encode";
					this.jobProgress.Value = su.PercentageDone;*/
				}
			}
#endif

#if defined(NONE)
			bool JobWorker::startEncoding(Job *job)
			{
				assert(status == Idle);

				try
				{
					//Check to see if output file already exists before encoding.
					if (File::Exists(job->Output) && !mainForm->getDialogManager()->overwriteJobOutput(job->Output))
						throw new JobStartException("File exists and the user doesn't want to overwrite", UserSkip);

					// Get IJobProcessor
					currentProcessor = getProcessor(job);
					if (currentProcessor == 0)
						throw new JobStartException("No processor could be found", Error);

					addToLog("\r\n\r\n------------------------------------------------------\r\n\r\n");
					addToLog("Starting job " + job->Name + " at " + DateTime::Now::ToLongTimeString() + "\r\n");

					// Preprocess
					preprocessJob(job);

					// Setup
					try
					{
						currentProcessor->setup(job);
					}
					catch (JobRunException *e)
					{
						throw new JobStartException("Calling setup of processor failed with error '" + e->Message + "'", Error);
					}

					// Do JobControl setup
					addToLog("encoder commandline:\r\n" + job->Commandline + "\r\n");
					currentProcessor->StatusUpdate += new JobProcessingStatusUpdateCallback(this, &JobWorker::UpdateGUIStatus);

					// Progress window
					pw = new ProgressWindow(job->JobType);
					pw->WindowClosed += new WindowClosedCallback(this, &JobWorker::pw_WindowClosed);
					pw->Abort += new AbortCallback(this, &JobWorker::pw_Abort);
					pw->setPriority(job->Priority);
					pw->PriorityChanged += new PriorityChangedCallback(this, &JobWorker::pw_PriorityChanged);
					if (mainForm->getSettings()->getOpenProgressWindow() && mainForm->Visible)
						pw->Show();

					job->Status = PROCESSING;
					job->Start = DateTime::Now;
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
						throw new JobStartException("starting encoder failed with error '" + e->Message + "'", Error);
					}

					addToLog("successfully started encoding\r\n");

					refreshAll();
					return true;
				}
				catch (JobStartException *e)
				{
					addToLog("Job not started. Reason: " + e->Message + "\r\n");
					if (e->type == Error)
						job->Status = ERROR;
					else // ExceptionType.UserSkip
						job->Status = SKIP;
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
#endif

#if defined(NONE)
			void JobWorker::addToLog(const QString &p)
			{
				mainForm->addToLog(p);
			}
#endif

#if defined(NONE)
			MeXgui::Job *JobWorker::getNextJob()
			{
				for (unknown::const_iterator j = display->Jobs.begin(); j != display->Jobs.end(); ++j)
					if ((*j)->Status == WAITING && mainForm->getJobs()->areDependenciesMet(*j))
						return j;
				if (mode == RequestNewJobs)
					return mainForm->getJobs()->getJobToProcess();
				else
					return 0;
			}
#endif

#if defined(NONE)
			MeXgui::core::details::JobStartInfo JobWorker::startNextJobInQueue()
			{
				Job *job = getNextJob();

				if (job == 0)
					return NO_JOBS_WAITING;

				while (job != 0)
				{
					if (startEncoding(job)) // successful
						return JOB_STARTED;
					job = getNextJob();
				}
				return COULDNT_START;
			}
#endif

#if defined(NONE)
			void JobWorker::markJobAborted()
			{
				Job *job = currentJob;
				job->Status = ABORTED;
				job->End = DateTime::Now;
				if (mainForm->getSettings()->getDeleteAbortedOutput())
				{
					mainForm->addToLog("Job aborted, deleting output file...");
					try
					{
						File::Delete(job->Output);
						mainForm->addToLog("Deletion successful.\r\n");
					}
					catch (std::exception &e1)
					{
						mainForm->addToLog("Deletion failed.\r\n");
					}
				}
			}
#endif

#if defined(NONE)
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
					addToLog("Error when trying to pause encoding: " + ex->Message + "\r\n");
				}
			}
#endif

#if defined(NONE)
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
					addToLog("Error when trying to resume encoding: " + ex->Message + "\r\n");
				}
			}
#endif

#if defined(NONE)
			void JobWorker::ensureProgressWindowClosed()
			{
				if (pw != 0)
				{
					pw->setIsUserAbort(false); // ensures that the window will be closed
					pw->Close();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete pw;
				}
			}
#endif

#if defined(NONE)
			void JobWorker::RemoveJobFromQueue(Job *job)
			{
				localJobs.erase(job->Name);
				display.
			}
#endif

#if defined(NONE)
			void JobWorker::UserRequestedAbort()
			{
				throw std::exception("The method or operation is not implemented.");
			}
#endif

			void JobWorker::InitializeInstanceFields()
			{
#if defined(NONE)
				localJobs = QMap<QString, Job*>();
				localJobs = QMap<QString, Job*>();
#endif
			}
		}
	}
}
