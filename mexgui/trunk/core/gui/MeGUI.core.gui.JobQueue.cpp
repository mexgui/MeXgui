#include "MeGUI.core.gui.JobQueue.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
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

#if defined(CSC)
const std::string JobQueue::__Name = "";
#endif

#if ! defined(CSC)
const std::string JobQueue::__Name = "MeGUI.";
#endif

System::Reflection::Assembly *const JobQueue::myAssembly = JobQueue::typeid::Assembly;
Bitmap *const JobQueue::pauseImage = new Bitmap(myAssembly->GetManifestResourceStream(__Name + "pause.ico"));
Bitmap *const JobQueue::playImage = new Bitmap(myAssembly->GetManifestResourceStream(__Name + "play.ico"));

			const MeGUI::core::gui::StartStopMode &JobQueue::getStartStopMode() const
			{
				return startStopMode;
			}

			void JobQueue::setStartStopMode(const MeGUI::core::gui::StartStopMode &value)
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						setStartStopMode(value);
					}
				   ));
					return;
				}

				startStopMode = value;
				switch (value)
				{
					case Start:
						startStopButton->Text = "Start";
						break;

					case Stop:
						startStopButton->Text = "Stop";
						break;
				}
			}

			const MeGUI::core::gui::PauseResumeMode &JobQueue::getPauseResumeMode() const
			{
				return pauseResumeMode;
			}

			void JobQueue::setPauseResumeMode(const MeGUI::core::gui::PauseResumeMode &value)
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						setPauseResumeMode(value);
					}
				   ));
					return;
				}

				pauseResumeMode = value;
				switch (value)
				{
					case Disabled:
						pauseButton->Enabled = false;
						pauseButton->Image = pauseImage;
						break;

					case Pause:
						pauseButton->Enabled = true;
						pauseButton->Image = pauseImage;
						break;

					case Resume:
						pauseButton->Enabled = true;
						pauseButton->Image = playImage;
						break;
				}
			}

			const IEnumerable<TaggedJob*> &JobQueue::getJobList() const
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					return (IEnumerable<TaggedJob*>)Invoke(new Getter<IEnumerable<TaggedJob*>*>(delegate
					{
						return JobList;
					}
				   ));
				}

				TaggedJob jobList[jobs.size()];
				for (std::map<std::string, TaggedJob*>::const_iterator j = jobs.begin(); j != jobs.end(); ++j)
				{
					jobList[indexOf(j->second)] = j->second;
				}
				return jobList;
			}

			void JobQueue::setJobList(const IEnumerable<TaggedJob*> &value)
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						setJobList(value);
					}
				   ));
					return;
				}

				queueListView->BeginUpdate();
				queueListView->Items->Clear();
				for (IEnumerable<TaggedJob*>::const_iterator job = value->begin(); job != value->end(); ++job)
				{
					queueListView->Items->Add(new ListViewItem(new std::string[] {(*job)->getName(), "", "", "", "", "", "", "", "", ""}));
					jobs[(*job)->getName()] = *job;
				}
				queueListView->EndUpdate();
				refreshQueue();
			}

			void JobQueue::queueJob(TaggedJob *j)
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						queueJob(j);
					}
				   ));
					return;
				}

				queueListView->Items->Add(new ListViewItem(new std::string[] {j->getName(), "", "", "", "", "", "", "", "", ""}));
				jobs[j->getName()] = j;
				refreshQueue();
			}

			void JobQueue::removeJobFromQueue(TaggedJob *job)
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						removeJobFromQueue(job);
					}
				   ));
					return;
				}

				queueListView->Items[indexOf(job)]->Remove();
				jobs.erase(job->getName());
				queueListView->Refresh();
			}

			void JobQueue::addItem(ToolStripMenuItem *item, const std::string &parent)
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						addItem(item, parent);
					}
				   ));
					return;
				}

				if (parent == "")
					queueContextMenu->Items->Add(item);
				else
					for (unknown::const_iterator i = queueContextMenu->Items.begin(); i != queueContextMenu->Items.end(); ++i)
						if ((*i)->Text == parent)
						{
							(*i)->DropDownItems->Add(item);
							break;
						}
			}

			void JobQueue::AddDynamicSubMenu(const std::string &name, const std::string &parent, MultiJobMenuGenerator gen)
			{
				ToolStripMenuItem *item = new ToolStripMenuItem(name);
				menuGenerators.push_back(new Pair<ToolStripMenuItem*, MultiJobMenuGenerator>(item, gen));
				addItem(item, parent);
			}

			void JobQueue::AddMenuItem(const std::string &name, const std::string &parent)
			{
				addItem(new ToolStripMenuItem(name), parent);
			}

			void JobQueue::AddMenuItem(const std::string &name, const std::string &parent, SingleJobHandler handler)
			{
				ToolStripMenuItem *item = new ToolStripMenuItem(name);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				item->Click += delegate(object sender, EventArgs e)
				{
					assert(queueListView->SelectedItems->Count == 1);
					TaggedJob *j = jobs[queueListView->SelectedItems[0]->Text];
					handler(j);
				};
				singleJobHandlers.push_back(item);
				addItem(item, parent);
			}

			void JobQueue::AddMenuItem(const std::string &name, const std::string &parent, MultiJobHandler handler)
			{
				ToolStripMenuItem *item = new ToolStripMenuItem(name);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				item->Click += delegate(object sender, EventArgs e)
				{
					assert(queueListView->SelectedItems->Count > 0);
					std::vector<TaggedJob*> list = std::vector<TaggedJob*>();
					for (unknown::const_iterator i = queueListView->SelectedItems.begin(); i != queueListView->SelectedItems.end(); ++i)
						list.push_back(jobs[(*i)->Text]);
					handler(list);
				};
				addItem(item, parent);
				multiJobHandlers.push_back(item);
			}

			void JobQueue::AddButton(const std::string &name, EventHandler *handler)
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						AddButton(name, handler);
					}
				   ));
					return;
				}

				Button *b = new Button();
				b->Text = name;
				b->Click += handler;
				b->AutoSize = true;
				b->AutoSizeMode = AutoSizeMode::GrowAndShrink;
				flowLayoutPanel1->Controls->Add(b);
			}

			void JobQueue::SetStartStopButtonsTogether()
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						SetStartStopButtonsTogether();
					}
				   ));
					return;
				}

				flowLayoutPanel1->Controls->Remove(stopButton);
			}

			int JobQueue::indexOf(TaggedJob *j)
			{
				assert(jobs.find(j->getName()) != jobs.end(), "Looking for a job which isn't in the jobs dictionary");
				for (unknown::const_iterator i = queueListView->Items.begin(); i != queueListView->Items.end(); ++i)
				{
					if ((*i)->Text == j->getName())
					{
						int index = (*i)->Index;
						assert(index >= 0);
						return index;
					}
				}
				assert(false, "Couldn't find job in the GUI queue");
				throw std::exception();
			}

			JobQueue::JobQueue()
			{
				InitializeInstanceFields();
				InitializeComponent();
				setStartStopMode(Start);
				setPauseResumeMode(Disabled);

				this->LoadComponentSettings();
			}

			std::vector<TaggedJob*> JobQueue::removeAllDependantJobsFromQueue(TaggedJob *job)
			{
				removeJobFromQueue(job);
				std::vector<TaggedJob*> list = std::vector<TaggedJob*>();
				for (std::vector<TaggedJob*>::const_iterator j = job->EnabledJobs.begin(); j != job->EnabledJobs.end(); ++j)
				{
					if (jobs.find((*j)->getName()) != jobs.end())
						list.AddRange(removeAllDependantJobsFromQueue(*j));
					else
						list.push_back(*j);
				}
				return list;
			}

			void JobQueue::deleteJobButton_Click(object *sender, EventArgs *e)
			{
				if (queueListView->SelectedItems->Count <= 0)
					return;

				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					processUserRequestToDelete((*item)->Text);
				}
			}

			void JobQueue::processUserRequestToDelete(const std::string &name)
			{
				if (!jobs.find(name) != jobs.end()) // Check if it has already been deleted
					return;
				TaggedJob *job = jobs[name];
				if (job == 0)
					return;
				RequestJobDeleted(job);
			}

			void JobQueue::downButton_Click(object *sender, EventArgs *e)
			{
				MoveListViewItem(Down);
			}

			void JobQueue::upButton_Click(object *sender, EventArgs *e)
			{
				MoveListViewItem(Up);
			}

			void JobQueue::MoveListViewItem(Direction d)
			{
				// We can trust that the button will be disabled unless this condition is met
				assert(isSelectionMovable(d));

				ListView *lv = queueListView;
				ListView::ListViewItemCollection *items = lv->Items;

				int indices[lv->SelectedIndices->Count];
				lv->SelectedIndices->CopyTo(indices, 0);
				Array::Sort(indices);
				int min = indices[0];
				int max = indices[sizeof(indices) / sizeof(indices[0]) - 1];

				lv->BeginUpdate();
				if (d == Up)
				{
					items[max]->Selected = false;
					items[min - 1]->Selected = true;

					for (int i = min; i <= max; i++)
						swapContents(items[i], items[i - 1]);
				}
				else if (d == Down)
				{
					items[min]->Selected = false;
					items[max + 1]->Selected = true;

					for (int i = max; i >= min; i--)
						swapContents(items[i], items[i + 1]);
				}
				lv->EndUpdate();
				lv->Refresh();

			}

			void JobQueue::swapContents(ListViewItem *a, ListViewItem *b)
			{
				for (int i = 0; i < a->SubItems->Count; i++)
				{
					std::string cache = b->SubItems[i]->Text;
					b->SubItems[i]->Text = a->SubItems[i]->Text;
					a->SubItems[i]->Text = cache;
				}
			}

			bool JobQueue::isSelectionMovable(Direction d)
			{
				ListView *lv = queueListView;
				int indices[lv->SelectedIndices->Count];
				lv->SelectedIndices->CopyTo(indices, 0);
				Array::Sort(indices);

				if (sizeof(indices) / sizeof(indices[0]) == 0)
					return false;
				if (d == Up && indices[0] == 0)
					return false;
				if (d == Down && indices[sizeof(indices) / sizeof(indices[0]) - 1] == queueListView->Items->Count - 1)
					return false;
				if (!consecutiveIndices(indices))
					return false;

				return true;
			}

			bool JobQueue::isSelectionEditable()
			{
				if (queueListView->SelectedItems->Count != 1)
					return false;

				TaggedJob *job = jobs[queueListView->SelectedItems[0]->Text];
				if (job->getStatus() != WAITING && job->getStatus() != POSTPONED)
					return false;

				return true;
			}

			bool JobQueue::consecutiveIndices(int indices[])
			{
				assert(sizeof(indices) / sizeof(indices[0]) > 0);

				int last = indices[0] - 1;
				for (int::const_iterator i = indices->begin(); i != indices->end(); ++i)
				{
					if (*i != last + 1)
						return false;
					last = *i;
				}

				return true;
			}

			void JobQueue::queueListView_ItemSelectionChanged(object *sender, ListViewItemSelectionChangedEventArgs *e)
			{
				upButton->Enabled = isSelectionMovable(Up);
				downButton->Enabled = isSelectionMovable(Down);
				editJobButton->Enabled = isSelectionEditable();
				markDependentJobs();
			}

			void JobQueue::editJobButton_Click(object *sender, EventArgs *e)
			{
				bool bJobCanBeEdited = false;

				if (queueListView->SelectedItems->Count != 1)
					return;

				TaggedJob *job = jobs[queueListView->SelectedItems[0]->Text];
				if (job->getStatus() != WAITING && job->getStatus() != POSTPONED)
					return;

				for (MeGUI::GenericRegisterer<IDable<ReconfigureJob>*>::const_iterator i = MainForm::Instance->getPackageSystem()->JobConfigurers->begin(); i != MainForm::Instance->getPackageSystem()->JobConfigurers->end(); ++i)
				{
					Job *j = i->second->Data(job->getJob());
					if (j != 0)
					{
						bJobCanBeEdited = true;
						job->setJob(j);
					}
				}

				if (!bJobCanBeEdited)
					MessageBox::Show("This kind of job cannot be edited.", "Cannot edit job", MessageBoxButtons::OK, MessageBoxIcon::Warning);

			}

			bool JobQueue::AllJobsHaveStatus(JobStatus status)
			{
				if (this->queueListView->SelectedItems->Count <= 0)
				{
					return false;
				}
				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					TaggedJob *job = jobs[(*item)->Text];
					if (job->getStatus() != status)
						return false;
				}
				return true;
			}

			bool JobQueue::AnyJobsHaveStatus(JobStatus status)
			{
				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					TaggedJob *job = jobs[(*item)->Text];
					if (job->getStatus() == status)
						return true;
				}
				return false;
			}

			void JobQueue::queueListView_DoubleClick(object *sender, EventArgs *e)
			{
				if (this->queueListView->SelectedItems->Count > 0) // otherwise
				{
					int position = this->queueListView->SelectedItems[0]->Index;
					TaggedJob *job = jobs[this->queueListView->SelectedItems[0]->Text];
					if (job->getStatus() == PROCESSING || job->getStatus() == ABORTING) // job is being processed -> do nothing
						return;
					if (job->getStatus() == WAITING) // waiting -> postponed
						job->setStatus(POSTPONED);
					else
						job->setStatus(WAITING);
					this->queueListView->Items[position]->SubItems[5]->Text = job->getStatusString();
				}
			}

			void JobQueue::postponeMenuItem_Click(object *sender, EventArgs *e)
			{
				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					int position = (*item)->Index;
					TaggedJob *job = jobs[(*item)->Text];

					assert(job->getStatus() != PROCESSING, "shouldn't be able to postpone an active job");

					job->setStatus(POSTPONED);
					this->queueListView->Items[position]->SubItems[5]->Text = job->getStatusString();
				}
			}

			void JobQueue::waitingMenuItem_Click(object *sender, EventArgs *e)
			{
				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					int position = (*item)->Index;
					TaggedJob *job = jobs[(*item)->Text];

					assert(job->getStatus() != PROCESSING, "shouldn't be able to set an active job back to waiting");

					job->setStatus(WAITING);
					queueListView->Items[position]->SubItems[5]->Text = job->getStatusString();
				}
			}

			void JobQueue::queueContextMenu_Opened(object *sender, EventArgs *e)
			{
				int count = queueListView->SelectedItems->Count;
				for (std::vector<ToolStripItem*>::const_iterator i = multiJobHandlers.begin(); i != multiJobHandlers.end(); ++i)
					(*i)->Enabled = (count > 0);
				for (std::vector<ToolStripItem*>::const_iterator i = singleJobHandlers.begin(); i != singleJobHandlers.end(); ++i)
					(*i)->Enabled = (count == 1);

				// here we generate our submenus as required, giving them the event handlers
				if (count > 0)
				{
					for (std::vector<Pair<ToolStripMenuItem*, MultiJobMenuGenerator>*>::const_iterator p = menuGenerators.begin(); p != menuGenerators.end(); ++p)
					{
						(*p)->fst->DropDownItems->Clear();
						for (unknown::const_iterator pair = p->snd().begin(); pair != p->snd().end(); ++pair)
						{
							ToolStripItem *i = (*p)->fst->DropDownItems->Add((*pair)->fst);
							(*i)->Tag = (*pair)->snd;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
							(*i)->Click += delegate(object sender1, EventArgs e2)
							{
								assert(queueListView->SelectedItems->Count > 0);
								std::vector<TaggedJob*> list = std::vector<TaggedJob*>();
								for (unknown::const_iterator i2 = queueListView->SelectedItems.begin(); i2 != queueListView->SelectedItems.end(); ++i2)
									list.push_back(jobs[(*i2)->Text]);
								(static_cast<MultiJobHandler>((static_cast<ToolStripItem*>(sender1))->Tag))(list);
							};
						}
					}
				}

				AbortMenuItem->Enabled = AllJobsHaveStatus(PROCESSING) || AllJobsHaveStatus(ABORTED);
				AbortMenuItem->Checked = AllJobsHaveStatus(ABORTED);

				EditMenuItem->Enabled = isSelectionEditable();
				EditMenuItem->Checked = false;

				bool canModifySelectedJobs = !AnyJobsHaveStatus(PROCESSING) && !AnyJobsHaveStatus(ABORTING) && this->queueListView->SelectedItems->Count > 0;
				DeleteMenuItem->Enabled = PostponedMenuItem->Enabled = WaitingMenuItem->Enabled = canModifySelectedJobs;

				DeleteMenuItem->Checked = false;
				PostponedMenuItem->Checked = AllJobsHaveStatus(POSTPONED);
				WaitingMenuItem->Checked = AllJobsHaveStatus(WAITING);

				OpenMenuItem->Enabled = false;
				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					TaggedJob *job = jobs[(*item)->Text];
					inputFileToolStripMenuItem->Enabled = inputFolderToolStripMenuItem->Enabled = false;
					outputFileToolStripMenuItem->Enabled = outputFolderToolStripMenuItem->Enabled = false;
					if (File::Exists(job->getInputFile()))
						inputFileToolStripMenuItem->Enabled = OpenMenuItem->Enabled = true;
					if (Directory::Exists(FileUtil::GetDirectoryName(job->getInputFile())))
						inputFolderToolStripMenuItem->Enabled = OpenMenuItem->Enabled = true;
					if (File::Exists(job->getOutputFile()))
						outputFileToolStripMenuItem->Enabled = OpenMenuItem->Enabled = true;
					if (Directory::Exists(FileUtil::GetDirectoryName(job->getOutputFile())))
						outputFolderToolStripMenuItem->Enabled = OpenMenuItem->Enabled = true;

					(*item)->SubItems[5]->Text = (jobs[(*item)->Text])->getStatusString();
				}
			}

			void JobQueue::abortButton_Click(object *sender, EventArgs *e)
			{
				AbortClicked(this, e);
			}

			void JobQueue::startStopButton_Click(object *sender, EventArgs *e)
			{
				switch (startStopMode)
				{
					case Start:
						StartClicked(this, e);
						break;

					case Stop:
						StopClicked(this, e);
						break;
				}
			}

			void JobQueue::pauseButton_Click(object *sender, EventArgs *e)
			{
				switch (pauseResumeMode)
				{
					case Disabled:
						throw std::exception("The supposedly disabled pause button was clicked");

					case Pause:
						PauseClicked(this, e);
						break;

					case Resume:
						ResumeClicked(this, e);
						break;
				}
			}

			void JobQueue::refreshQueue()
			{
				if (!Visible)
					return;

				if (queueListView->InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					queueListView->Invoke(new MethodInvoker(delegate
					{
						refreshQueue();
					}
				   ));
					return;
				}

				queueListView->BeginUpdate();
				for (unknown::const_iterator item = queueListView->Items.begin(); item != queueListView->Items.end(); ++item)
				{
					TaggedJob *job = jobs[(*item)->Text];
					(*item)->SubItems[1]->Text = job->getInputFileName();
					(*item)->SubItems[2]->Text = job->getOutputFileName();
					(*item)->SubItems[3]->Text = job->getJob()->CodecString;
					(*item)->SubItems[4]->Text = job->getJob()->EncodingMode;
					(*item)->SubItems[5]->Text = job->getStatusString();
					std::string tempVar = job.getOwningWorker();
					(*item)->SubItems[6]->Text = (tempVar != 0) ? tempVar : "";

					if (job->getStatus() == DONE)
					{
						(*item)->SubItems[8]->Text = job->getEnd().ToLongTimeString();
						(*item)->SubItems[9]->Text = job->EncodingSpeed;
					}
					else
					{
						(*item)->SubItems[8]->Text = "";
						(*item)->SubItems[9]->Text = "";
					}
					if (job->getStatus() == DONE || job->getStatus() == PROCESSING || job->getStatus() == ABORTING)
						(*item)->SubItems[7]->Text = job->getStart().ToLongTimeString();
					else
						(*item)->SubItems[7]->Text = "";
				}
				queueListView->EndUpdate();
				queueListView->Refresh();
			}

			void JobQueue::stopButton_Click(object *sender, EventArgs *e)
			{
				StopClicked(this, e);
			}

			bool JobQueue::HasJob(TaggedJob *job)
			{
				return jobs.find(job->getName()) != jobs.end();
			}

			void JobQueue::queueListView_VisibleChanged(object *sender, EventArgs *e)
			{
				refreshQueue();
			}

			void JobQueue::AbortMenuItem_Click(object *sender, EventArgs *e)
			{
				if (AllJobsHaveStatus(ABORTED) && AbortMenuItem->Checked) // set them back to waiting
				{
					for (unknown::const_iterator item = queueListView->SelectedItems.begin(); item != queueListView->SelectedItems.end(); ++item)
					{
						jobs[(*item)->Text]->setStatus(WAITING);
					}
					refreshQueue();
				}
				else if (!AbortMenuItem->Checked)
					AbortClicked(this, e);
			}

			void JobQueue::queueListView_KeyDown(object *sender, KeyEventArgs *e)
			{
				if (e->Control && e->KeyCode->Equals(Keys::A))
				{
					for (unknown::const_iterator item = this->queueListView->Items.begin(); item != this->queueListView->Items.end(); ++item)
						(*item)->Selected = true;
					return;
				}

				switch (e->KeyCode)
				{
					case Keys::Delete:
						deleteJobButton_Click(sender, e);
						break;
					case Keys::Up:
						if (upButton->Enabled && e->Shift)
							upButton_Click(sender, e);
							break;
					case Keys::Down:
						if (downButton->Enabled && e->Shift)
							downButton_Click(sender, e);
							break;
					case Keys::Escape:
					case Keys::Enter:
						startStopButton_Click(sender, e);
						break;
				}
			}

			void JobQueue::LoadComponentSettings()
			{
				if (MainForm::Instance == 0) // Designer fix
					return;

				jobColumHeader->Width = MainForm::Instance->getSettings()->getJobColumnWidth();
				inputColumnHeader->Width = MainForm::Instance->getSettings()->getInputColumnWidth();
				outputColumnHeader->Width = MainForm::Instance->getSettings()->getOutputColumnWidth();
				codecHeader->Width = MainForm::Instance->getSettings()->getCodecColumnWidth();
				modeHeader->Width = MainForm::Instance->getSettings()->getModeColumnWidth();
				statusColumn->Width = MainForm::Instance->getSettings()->getStatusColumnWidth();
				ownerHeader->Width = MainForm::Instance->getSettings()->getOwnerColumnWidth();
				startColumn->Width = MainForm::Instance->getSettings()->getStartColumnWidth();
				endColumn->Width = MainForm::Instance->getSettings()->getEndColumnWidth();
				fpsColumn->Width = MainForm::Instance->getSettings()->getFPSColumnWidth();
			}

			void JobQueue::SaveComponentSettings()
			{
				if (MainForm::Instance == 0) // Designer fix
					return;

				MainForm::Instance->getSettings()->setJobColumnWidth(jobColumHeader->Width);
				MainForm::Instance->getSettings()->setInputColumnWidth(inputColumnHeader->Width);
				MainForm::Instance->getSettings()->setOutputColumnWidth(outputColumnHeader->Width);
				MainForm::Instance->getSettings()->setCodecColumnWidth(codecHeader->Width);
				MainForm::Instance->getSettings()->setModeColumnWidth(modeHeader->Width);
				MainForm::Instance->getSettings()->setStatusColumnWidth(statusColumn->Width);
				MainForm::Instance->getSettings()->setOwnerColumnWidth(ownerHeader->Width);
				MainForm::Instance->getSettings()->setStartColumnWidth(startColumn->Width);
				MainForm::Instance->getSettings()->setEndColumnWidth(endColumn->Width);
				MainForm::Instance->getSettings()->setFPSColumnWidth(fpsColumn->Width);
			}

			void JobQueue::JobQueue_Load(object *sender, EventArgs *e)
			{

				if (VistaStuff::getIsVistaOrNot())
				{
					VistaStuff::SetWindowTheme(queueListView->Handle, "explorer", 0);
				}
			}

			void JobQueue::queueListView_ColumnWidthChanged(object *sender, ColumnWidthChangedEventArgs *e)
			{
				this->SaveComponentSettings();
			}

			void JobQueue::markDependentJobs()
			{
				std::vector<std::string> oList = std::vector<std::string>();
				for (unknown::const_iterator oItem = queueListView->SelectedItems.begin(); oItem != queueListView->SelectedItems.end(); ++oItem)
				{
					if (!jobs.find((*oItem)->Text) != jobs.end()) // check if it has been removed
						continue;
					TaggedJob *job = jobs[(*oItem)->Text];
					if (job == 0)
						continue;
					getAllDependantJobs(job, oList);
				}

				queueListView->SuspendLayout();
				for (unknown::const_iterator oItem = queueListView->Items.begin(); oItem != queueListView->Items.end(); ++oItem)
				{
					if (std::find(oList.begin(), oList.end(), (*oItem)->Text) != oList.end())
						(*oItem)->BackColor = Color::FromArgb(255, 225, 235, 255);
					else
						(*oItem)->BackColor = SystemColors::Window;
				}
				queueListView->ResumeLayout();
			}

			void JobQueue::getAllDependantJobs(TaggedJob *job, std::vector<std::string> &oList)
			{
				if (std::find(oList.begin(), oList.end(), job->getName()) != oList.end())
					return;

				oList.push_back(job->getName());
				for (std::vector<TaggedJob*>::const_iterator j = job->EnabledJobs.begin(); j != job->EnabledJobs.end(); ++j)
					getAllDependantJobs(*j, oList);

				for (std::vector<TaggedJob*>::const_iterator j = job->RequiredJobs.begin(); j != job->RequiredJobs.end(); ++j)
					getAllDependantJobs(*j, oList);
			}

			void JobQueue::outputFolderToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					TaggedJob *job = jobs[(*item)->Text];
					if (!Directory::Exists(FileUtil::GetDirectoryName(job->getOutputFile())))
						continue;

					try
					{
						Process *prc = new Process();
						prc->StartInfo->FileName = FileUtil::GetDirectoryName(job->getOutputFile());
						prc->Start();
					}
					catch (std::exception &e1)
					{
					}
				}
			}

			void JobQueue::outputFileToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					TaggedJob *job = jobs[(*item)->Text];
					if (!File::Exists(job->getOutputFile()))
						continue;

					try
					{
						Process *prc = new Process();
						prc->StartInfo->FileName = job->getOutputFile();
						prc->Start();
					}
					catch (std::exception &e1)
					{
					}
				}
			}

			void JobQueue::inputFolderToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					TaggedJob *job = jobs[(*item)->Text];
					if (!Directory::Exists(FileUtil::GetDirectoryName(job->getInputFile())))
						continue;

					try
					{
						Process *prc = new Process();
						prc->StartInfo->FileName = FileUtil::GetDirectoryName(job->getInputFile());
						prc->Start();
					}
					catch (std::exception &e1)
					{
					}
				}
			}

			void JobQueue::inputFileToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				for (unknown::const_iterator item = this->queueListView->SelectedItems.begin(); item != this->queueListView->SelectedItems.end(); ++item)
				{
					TaggedJob *job = jobs[(*item)->Text];
					if (!File::Exists(job->getInputFile()))
						continue;

					try
					{
						Process *prc = new Process();
						prc->StartInfo->FileName = job->getInputFile();
						prc->Start();
					}
					catch (std::exception &e1)
					{
					}
				}
			}

			void JobQueue::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				UserControl::Dispose(disposing);
			}

			void JobQueue::InitializeComponent()
			{
				this->components = new System::ComponentModel::Container();
				System::Windows::Forms::Button *abortButton;
				System::Windows::Forms::Button *deleteButton;
				this->jobColumHeader = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->inputColumnHeader = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->outputColumnHeader = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->codecHeader = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->modeHeader = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->statusColumn = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->startColumn = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->endColumn = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->fpsColumn = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->upButton = new System::Windows::Forms::Button();
				this->downButton = new System::Windows::Forms::Button();
				this->queueListView = new System::Windows::Forms::ListView();
				this->ownerHeader = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
				this->queueContextMenu = new System::Windows::Forms::ContextMenuStrip(this->components);
				this->DeleteMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->StatusMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->PostponedMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->WaitingMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->AbortMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->EditMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->OpenMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->inputFileToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->inputFolderToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->outputFileToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->outputFolderToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->flowLayoutPanel1 = new System::Windows::Forms::FlowLayoutPanel();
				this->startStopButton = new System::Windows::Forms::Button();
				this->stopButton = new System::Windows::Forms::Button();
				this->pauseButton = new System::Windows::Forms::Button();
				this->editJobButton = new System::Windows::Forms::Button();
				abortButton = new System::Windows::Forms::Button();
				deleteButton = new System::Windows::Forms::Button();
				this->queueContextMenu->SuspendLayout();
				this->flowLayoutPanel1->SuspendLayout();
				this->SuspendLayout();
				// 
				// abortButton
				// 
				abortButton->AutoSize = true;
				abortButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				abortButton->Location = new System::Drawing::Point(123, 3);
				abortButton->Margin = new System::Windows::Forms::Padding(3, 3, 7, 3);
				abortButton->Name = "abortButton";
				abortButton->Size = new System::Drawing::Size(42, 23);
				abortButton->TabIndex = 3;
				abortButton->Text = "Abort";
				abortButton->UseVisualStyleBackColor = true;
				abortButton->Click += new System::EventHandler(this, &JobQueue::abortButton_Click);
				// 
				// deleteButton
				// 
				deleteButton->AutoSize = true;
				deleteButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				deleteButton->Location = new System::Drawing::Point(316, 3);
				deleteButton->Name = "deleteButton";
				deleteButton->Size = new System::Drawing::Size(48, 23);
				deleteButton->TabIndex = 8;
				deleteButton->Text = "Delete";
				deleteButton->UseVisualStyleBackColor = true;
				deleteButton->Click += new System::EventHandler(this, &JobQueue::deleteJobButton_Click);
				// 
				// jobColumHeader
				// 
				this->jobColumHeader->Text = "Name";
				// 
				// inputColumnHeader
				// 
				this->inputColumnHeader->Text = "Input";
				// 
				// outputColumnHeader
				// 
				this->outputColumnHeader->Text = "Output";
				// 
				// codecHeader
				// 
				this->codecHeader->Text = "Encoder";
				// 
				// modeHeader
				// 
				this->modeHeader->Text = "Mode";
				// 
				// statusColumn
				// 
				this->statusColumn->Text = "Status";
				// 
				// startColumn
				// 
				this->startColumn->Text = "Start";
				// 
				// endColumn
				// 
				this->endColumn->Text = "End";
				// 
				// fpsColumn
				// 
				this->fpsColumn->Text = "FPS";
				// 
				// upButton
				// 
				this->upButton->AutoSize = true;
				this->upButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->upButton->Enabled = false;
				this->upButton->Location = new System::Drawing::Point(224, 3);
				this->upButton->Margin = new System::Windows::Forms::Padding(7, 3, 3, 3);
				this->upButton->Name = "upButton";
				this->upButton->Size = new System::Drawing::Size(31, 23);
				this->upButton->TabIndex = 6;
				this->upButton->Text = "Up";
				this->upButton->UseVisualStyleBackColor = true;
				this->upButton->Click += new System::EventHandler(this, &JobQueue::upButton_Click);
				// 
				// downButton
				// 
				this->downButton->AutoSize = true;
				this->downButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->downButton->Enabled = false;
				this->downButton->Location = new System::Drawing::Point(261, 3);
				this->downButton->Margin = new System::Windows::Forms::Padding(3, 3, 7, 3);
				this->downButton->Name = "downButton";
				this->downButton->Size = new System::Drawing::Size(45, 23);
				this->downButton->TabIndex = 7;
				this->downButton->Text = "Down";
				this->downButton->UseVisualStyleBackColor = true;
				this->downButton->Click += new System::EventHandler(this, &JobQueue::downButton_Click);
				// 
				// queueListView
				// 
				this->queueListView->Columns->AddRange(new System::Windows::Forms::ColumnHeader[10] {this->jobColumHeader, this->inputColumnHeader, this->outputColumnHeader, this->codecHeader, this->modeHeader, this->statusColumn, this->ownerHeader, this->startColumn, this->endColumn, this->fpsColumn});
				this->queueListView->ContextMenuStrip = this->queueContextMenu;
				this->queueListView->Dock = System::Windows::Forms::DockStyle::Fill;
				this->queueListView->FullRowSelect = true;
				this->queueListView->HideSelection = false;
				this->queueListView->Location = new System::Drawing::Point(0, 0);
				this->queueListView->Name = "queueListView";
				this->queueListView->Size = new System::Drawing::Size(692, 513);
				this->queueListView->TabIndex = 0;
				this->queueListView->UseCompatibleStateImageBehavior = false;
				this->queueListView->View = System::Windows::Forms::View::Details;
				this->queueListView->ColumnWidthChanged += new System::Windows::Forms::ColumnWidthChangedEventHandler(this, &JobQueue::queueListView_ColumnWidthChanged);
				this->queueListView->ItemSelectionChanged += new System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &JobQueue::queueListView_ItemSelectionChanged);
				this->queueListView->VisibleChanged += new System::EventHandler(this, &JobQueue::queueListView_VisibleChanged);
				this->queueListView->DoubleClick += new System::EventHandler(this, &JobQueue::queueListView_DoubleClick);
				this->queueListView->KeyDown += new System::Windows::Forms::KeyEventHandler(this, &JobQueue::queueListView_KeyDown);
				// 
				// ownerHeader
				// 
				this->ownerHeader->Text = "Owner";
				// 
				// queueContextMenu
				// 
				this->queueContextMenu->Items->AddRange(new System::Windows::Forms::ToolStripItem[5] {this->DeleteMenuItem, this->StatusMenuItem, this->AbortMenuItem, this->EditMenuItem, this->OpenMenuItem});
				this->queueContextMenu->Name = "queueContextMenu";
				this->queueContextMenu->Size = new System::Drawing::Size(150, 114);
				this->queueContextMenu->Opened += new System::EventHandler(this, &JobQueue::queueContextMenu_Opened);
				// 
				// DeleteMenuItem
				// 
				this->DeleteMenuItem->Name = "DeleteMenuItem";
				this->DeleteMenuItem->ShortcutKeyDisplayString = "";
				this->DeleteMenuItem->Size = new System::Drawing::Size(149, 22);
				this->DeleteMenuItem->Text = "&Delete";
				this->DeleteMenuItem->ToolTipText = "Delete this job";
				this->DeleteMenuItem->Click += new System::EventHandler(this, &JobQueue::deleteJobButton_Click);
				// 
				// StatusMenuItem
				// 
				this->StatusMenuItem->DropDownItems->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->PostponedMenuItem, this->WaitingMenuItem});
				this->StatusMenuItem->Name = "StatusMenuItem";
				this->StatusMenuItem->Size = new System::Drawing::Size(149, 22);
				this->StatusMenuItem->Text = "&Change status";
				// 
				// PostponedMenuItem
				// 
				this->PostponedMenuItem->Name = "PostponedMenuItem";
				this->PostponedMenuItem->Size = new System::Drawing::Size(131, 22);
				this->PostponedMenuItem->Text = "&Postponed";
				this->PostponedMenuItem->Click += new System::EventHandler(this, &JobQueue::postponeMenuItem_Click);
				// 
				// WaitingMenuItem
				// 
				this->WaitingMenuItem->Name = "WaitingMenuItem";
				this->WaitingMenuItem->Size = new System::Drawing::Size(131, 22);
				this->WaitingMenuItem->Text = "&Waiting";
				this->WaitingMenuItem->Click += new System::EventHandler(this, &JobQueue::waitingMenuItem_Click);
				// 
				// AbortMenuItem
				// 
				this->AbortMenuItem->Name = "AbortMenuItem";
				this->AbortMenuItem->ShortcutKeyDisplayString = "";
				this->AbortMenuItem->Size = new System::Drawing::Size(149, 22);
				this->AbortMenuItem->Text = "&Abort";
				this->AbortMenuItem->ToolTipText = "Abort this job";
				this->AbortMenuItem->Click += new System::EventHandler(this, &JobQueue::AbortMenuItem_Click);
				// 
				// EditMenuItem
				// 
				this->EditMenuItem->Enabled = false;
				this->EditMenuItem->Name = "EditMenuItem";
				this->EditMenuItem->ShortcutKeyDisplayString = "";
				this->EditMenuItem->Size = new System::Drawing::Size(149, 22);
				this->EditMenuItem->Text = "&Edit";
				this->EditMenuItem->ToolTipText = "Edit job\r\nOnly possible if only one job is selected which is waiting or postponed" + "";
				this->EditMenuItem->Click += new System::EventHandler(this, &JobQueue::editJobButton_Click);
				// 
				// OpenMenuItem
				// 
				this->OpenMenuItem->DropDownItems->AddRange(new System::Windows::Forms::ToolStripItem[4] {this->inputFileToolStripMenuItem, this->inputFolderToolStripMenuItem, this->outputFileToolStripMenuItem, this->outputFolderToolStripMenuItem});
				this->OpenMenuItem->Name = "OpenMenuItem";
				this->OpenMenuItem->Size = new System::Drawing::Size(149, 22);
				this->OpenMenuItem->Text = "&Open";
				// 
				// inputFileToolStripMenuItem
				// 
				this->inputFileToolStripMenuItem->Name = "inputFileToolStripMenuItem";
				this->inputFileToolStripMenuItem->Size = new System::Drawing::Size(152, 22);
				this->inputFileToolStripMenuItem->Text = "Input File";
				this->inputFileToolStripMenuItem->Click += new System::EventHandler(this, &JobQueue::inputFileToolStripMenuItem_Click);
				// 
				// inputFolderToolStripMenuItem
				// 
				this->inputFolderToolStripMenuItem->Name = "inputFolderToolStripMenuItem";
				this->inputFolderToolStripMenuItem->Size = new System::Drawing::Size(152, 22);
				this->inputFolderToolStripMenuItem->Text = "Input Folder";
				this->inputFolderToolStripMenuItem->Click += new System::EventHandler(this, &JobQueue::inputFolderToolStripMenuItem_Click);
				// 
				// outputFileToolStripMenuItem
				// 
				this->outputFileToolStripMenuItem->Name = "outputFileToolStripMenuItem";
				this->outputFileToolStripMenuItem->Size = new System::Drawing::Size(152, 22);
				this->outputFileToolStripMenuItem->Text = "Output File";
				this->outputFileToolStripMenuItem->Click += new System::EventHandler(this, &JobQueue::outputFileToolStripMenuItem_Click);
				// 
				// outputFolderToolStripMenuItem
				// 
				this->outputFolderToolStripMenuItem->Name = "outputFolderToolStripMenuItem";
				this->outputFolderToolStripMenuItem->Size = new System::Drawing::Size(152, 22);
				this->outputFolderToolStripMenuItem->Text = "Output Folder";
				this->outputFolderToolStripMenuItem->Click += new System::EventHandler(this, &JobQueue::outputFolderToolStripMenuItem_Click);
				// 
				// flowLayoutPanel1
				// 
				this->flowLayoutPanel1->AutoSize = true;
				this->flowLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->flowLayoutPanel1->Controls->Add(this->startStopButton);
				this->flowLayoutPanel1->Controls->Add(this->stopButton);
				this->flowLayoutPanel1->Controls->Add(this->pauseButton);
				this->flowLayoutPanel1->Controls->Add(abortButton);
				this->flowLayoutPanel1->Controls->Add(this->editJobButton);
				this->flowLayoutPanel1->Controls->Add(this->upButton);
				this->flowLayoutPanel1->Controls->Add(this->downButton);
				this->flowLayoutPanel1->Controls->Add(deleteButton);
				this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Bottom;
				this->flowLayoutPanel1->Location = new System::Drawing::Point(0, 513);
				this->flowLayoutPanel1->Name = "flowLayoutPanel1";
				this->flowLayoutPanel1->Size = new System::Drawing::Size(692, 29);
				this->flowLayoutPanel1->TabIndex = 1;
				// 
				// startStopButton
				// 
				this->startStopButton->AutoSize = true;
				this->startStopButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->startStopButton->Location = new System::Drawing::Point(3, 3);
				this->startStopButton->Name = "startStopButton";
				this->startStopButton->Size = new System::Drawing::Size(39, 23);
				this->startStopButton->TabIndex = 0;
				this->startStopButton->Text = "Start";
				this->startStopButton->UseVisualStyleBackColor = true;
				this->startStopButton->Click += new System::EventHandler(this, &JobQueue::startStopButton_Click);
				// 
				// stopButton
				// 
				this->stopButton->AutoSize = true;
				this->stopButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->stopButton->Location = new System::Drawing::Point(48, 3);
				this->stopButton->Name = "stopButton";
				this->stopButton->Size = new System::Drawing::Size(39, 23);
				this->stopButton->TabIndex = 1;
				this->stopButton->Text = "Stop";
				this->stopButton->UseVisualStyleBackColor = true;
				this->stopButton->Click += new System::EventHandler(this, &JobQueue::stopButton_Click);
				// 
				// pauseButton
				// 
				this->pauseButton->Location = new System::Drawing::Point(93, 3);
				this->pauseButton->Name = "pauseButton";
				this->pauseButton->Size = new System::Drawing::Size(24, 23);
				this->pauseButton->TabIndex = 2;
				this->pauseButton->UseVisualStyleBackColor = true;
				this->pauseButton->Visible = false;
				this->pauseButton->Click += new System::EventHandler(this, &JobQueue::pauseButton_Click);
				// 
				// editJobButton
				// 
				this->editJobButton->AutoSize = true;
				this->editJobButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->editJobButton->Enabled = false;
				this->editJobButton->Location = new System::Drawing::Point(179, 3);
				this->editJobButton->Margin = new System::Windows::Forms::Padding(7, 3, 3, 3);
				this->editJobButton->Name = "editJobButton";
				this->editJobButton->Size = new System::Drawing::Size(35, 23);
				this->editJobButton->TabIndex = 4;
				this->editJobButton->Text = "Edit";
				this->editJobButton->UseVisualStyleBackColor = true;
				this->editJobButton->Click += new System::EventHandler(this, &JobQueue::editJobButton_Click);
				// 
				// JobQueue
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(96, 96);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
				this->Controls->Add(this->queueListView);
				this->Controls->Add(this->flowLayoutPanel1);
				this->Name = "JobQueue";
				this->Size = new System::Drawing::Size(692, 542);
				this->Load += new System::EventHandler(this, &JobQueue::JobQueue_Load);
				this->queueContextMenu->ResumeLayout(false);
				this->flowLayoutPanel1->ResumeLayout(false);
				this->flowLayoutPanel1->PerformLayout();
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void JobQueue::InitializeInstanceFields()
			{
				jobs = std::map<std::string, TaggedJob*>();
				singleJobHandlers = std::vector<ToolStripItem*>();
				multiJobHandlers = std::vector<ToolStripItem*>();
				menuGenerators = std::vector<Pair<ToolStripMenuItem*, MultiJobMenuGenerator>*>();
				delete components;
			}
		}
	}
}
