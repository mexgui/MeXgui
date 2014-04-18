#pragma once

#include "JobWorker.h"
#include "core/gui/JobWorker.h"
#include "core/gui/MeGUI.core.gui.JobWorker.h"
#include "TaggedJob.h"
#include "core/plugins/interfaces/Job.h"
#include "core/util/Util.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/gui/MeGUI.core.gui.WorkerSummary.h"
#include "MeGUISettings.h"
#include "core/gui/MeGUI.UpdateWindow.h"
#include "core/gui/JobWorkerWindow.h"
#include "core/gui/JobQueue.h"
#include "core/util/LogItem.h"
#include "CleanupJob.h"
#include "core/util/FileUtil.h"
#include "MeGUI.core.details.JobChain.h"
#include "MeGUI.Properties.Settings.h"
#include "core/gui/MeGUI.core.gui.InputBox.h"
#include "core/gui/MeGUI.core.gui.HelpButton.h"
#include "core/gui/MeGUI.core.gui.JobQueue.h"
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************

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
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;

using namespace MeGUI::core::util;
using namespace MeGUI::core::gui;

namespace MeGUI
{
	namespace core
	{
		namespace details
		{
			class JobControl : public UserControl
			{
			private:
				class SendToWorkerThunk
				{
				private:
					JobControl *c;
					JobWorker *w;
				public:
					void handleEvent(std::vector<TaggedJob*> &jobs);

					SendToWorkerThunk(JobWorker *w, JobControl *c);
				};

			public:
				class JobListSerializer
				{
				public:
					std::vector<std::string> mainJobList;
					std::vector<Pair<std::string, std::vector<std::string>*>*> workersAndTheirJobLists;

				private:
					void InitializeInstanceFields();

public:
					JobListSerializer()
					{
						InitializeInstanceFields();
					}
				};

			private:
				std::map<std::string, TaggedJob*> allJobs; //storage for all the jobs and profiles known to the system
				std::map<std::string, JobWorker*> workers;
				MeGUI::MainForm *mainForm;
				WorkerSummary *summary;
				AfterEncoding currentAfterEncoding;
				Semaphore *resourceLock;

				public:
				~JobControl()
				{
					this->Dispose(true);
				}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:
				void Finalize()
				{
					this->Dispose(false);
				}

			public:
				void ShowAllProcessWindows();

				void HideAllProcessWindows();

				void AbortAll();

				void StartAll(bool restartStopping);

				void StopAll();

				JobControl();

				const Semaphore &getResourceLock() const;
				void setResourceLock(const Semaphore &value);

			private:
				void addSendToTemporaryWorkerMenuItem();

			public:
				void ReleaseJob(TaggedJob *j);

			private:
				void addSendToWorkerMenuItems();

			public:
				void setMainForm(const MeGUI::MainForm &value);

				const bool &getIsAnyWorkerEncoding() const;
				const bool &getIsAnyWorkerEncodingAudio() const;
				const AfterEncoding &getCurrentAfterEncoding() const;

			private:
				void addClearButton();

				void deleteAllJobsButton_Click(object *sender, EventArgs *e);
			public:
				void DeleteJob(TaggedJob *job);
				/// <summary>
				/// removes this job, and any previous jobs that belong to a series of jobs from the
				/// queue, then update the queue positions
				/// </summary>
				/// <param name="job">the job to be removed</param>
				void RemoveCompletedJob(TaggedJob *job);

			private:
				void reallyDeleteJob(TaggedJob *job);

				void deleteAllDependantJobs(TaggedJob *job);

			public:
				void refresh();

				void StartPostponedWorkers();

				void StartIdleWorkers();

				std::vector<std::string> toStringList(IEnumerable<TaggedJob*> *jobList);
				/// <summary>
				/// saves all the jobs in the queue
				/// </summary>
				void saveJobs();

			private:
				void saveJobLists();

				void loadJobLists();

				/// <summary>
				/// loads all the jobs from the harddisk
				/// upon loading, the jobs are ordered according to their position field
				/// so that the order in which the jobs were previously shown in the GUI is preserved
				/// </summary>
			public:
				void loadJobs();

				std::vector<TaggedJob*> toJobList(IEnumerable<std::string> *list);

				/// <summary>
				/// saves a job to programdirectory\jobs\jobname.xml
				/// using the XML Serializer we get a humanly readable file
				/// </summary>
				/// <param name="job">the Job object to be saved</param>
				/// <param name="path">The path where the program was launched from</param>
				void saveJob(TaggedJob *job, const std::string &path);
				/// <summary>
				/// loads a job with a given name from programdirectory\jobs\jobname.xml
				/// </summary>
				/// <param name="name">name of the job to be loaded (corresponds to the filename)</param>
				/// <returns>the Job object that was read from the harddisk</returns>
				TaggedJob *loadJob(const std::string &name);
				/// <summary>
				/// looks up the first free job number
				/// </summary>
				/// <returns>the job number that can be attributed to the next job to be added to the queue</returns>
			private:
				std::string getFreeJobName();

			public:
				void addJobsWithDependencies(JobChain *c, bool bStartQueue);

				/// <summary>
				/// adds a job to the Queue (Hashtable) and the listview for graphical display
				/// </summary>
				/// <param name="job">the Job to be added to the next free spot in the queue</param>
//ORIGINAL LINE: public void addJobsToQueue(params Job[] jobs)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
				void addJobsToQueue(...);

			private:
				void addJob(TaggedJob *job);

				void updateProcessingStatus();

			public:
				void showAfterEncodingStatus(MeGUISettings *Settings);


				/// <summary>
				/// Returns the job under the given name
				/// </summary>
				/// <param name="p"></param>
				/// <returns></returns>
				TaggedJob *ByName(const std::string &p);

				/// <summary>
				/// Returns whether all the jobs that j depends on have been successfully completed
				/// </summary>
				/// <param name="j"></param>
				/// <returns></returns>
				bool areDependenciesMet(TaggedJob *j);

			private:
				object *nextJobLock;
				/// <summary>
				/// Returns the first job on the queue whose dependencies have been met, whose status
				/// is set to 'waiting', and which isn't owned by any JobWorkers
				/// </summary>
				/// <returns></returns>
			public:
				TaggedJob *getJobToProcess();

				void RenameWorker(const std::string &name, const std::string &value);

			private:
				void jobQueue_StartClicked(object *sender, EventArgs *e);

				void jobQueue_StopClicked(object *sender, EventArgs *e);

				void jobQueue_AbortClicked(object *sender, EventArgs *e);


				std::string freeWorkerName();

			public:
				std::vector<Pair<std::string, bool>*> ListWorkers();

				void HideAllWorkers();

				void ShowAllWorkers();

				void RequestNewWorker();

			private:
				JobWorker *NewWorker(const std::string &name, bool show);

				void WorkerFinishedJobs(object *sender, EventArgs *e);

			public:
				void ShowSummary();

				void HideSummary();

				const bool &getSummaryVisible() const;

				void SetWorkerVisible(const std::string &p, bool p_2);

			private:
				void newWorkerButton_Click(object *sender, EventArgs *e);

			public:
				void UpdateProgress(const std::string &name);

				void ShutDown(JobWorker *w);

				std::vector<Pair<std::string, bool>*> ListProgressWindows();

				void HideProgressWindow(const std::string &p);

				void ShowProgressWindow(const std::string &p);

			private:
				void cbAfterEncoding_SelectedIndexChanged(object *sender, EventArgs *e);


				/// <summary> 
				/// Required designer variable.
				/// </summary>
				System::ComponentModel::IContainer *components;

				/// <summary> 
				/// Clean up any resources being used.
				/// </summary>
				/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
				void Dispose(bool disposing);


				/// <summary> 
				/// Required method for Designer support - do not modify 
				/// the contents of this method with the code editor.
				/// </summary>
				void InitializeComponent();


				System::Windows::Forms::Label *lblAfterEncoding;
				MeGUI::core::gui::HelpButton *helpButton1;
				MeGUI::core::gui::JobQueue *jobQueue;
				System::Windows::Forms::Button *newWorkerButton;
				System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;
				System::Windows::Forms::ComboBox *cbAfterEncoding;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
