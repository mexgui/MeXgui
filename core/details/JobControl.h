#pragma once

#include "JobWorker.h"
#include "core/gui/JobWorker.h"
#include "core/gui/MeXgui.JobWorker.h"
#include "TaggedJob.h"
#include "core/plugins/interfaces/Job.h"
#include "core/util/Util.h"
#include "core/gui/MeXgui.MainForm.h"
#include "core/gui/MeXgui.WorkerSummary.h"
#include "MeXguiSettings.h"
#include "core/gui/MeXgui.UpdateWindow.h"
#include "core/gui/JobWorkerWindow.h"
#include "core/gui/JobQueue.h"
#include "core/util/LogItem.h"
#include "CleanupJob.h"
#include "core/util/FileUtil.h"
#include "MeXgui.JobChain.h"
#include "MeXgui.Properties.Settings.h"
#include "core/gui/MeXgui.InputBox.h"
#include "core/gui/MeXgui.HelpButton.h"
#include "core/gui/MeXgui.JobQueue.h"
#include <QString>
#include <QMap>
#include <QVector>
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




//using namespace System::Collections::Generic;



//using namespace System::Data;

//using namespace System::Diagnostics;





//using namespace System::Text;

//using namespace System::Threading;



//using namespace System::Xml::Serialization;

//using namespace System::Text::RegularExpressions;

using namespace MeXgui::core::util;
using namespace MeXgui::core::gui;

namespace MeXgui
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
					void handleEvent(QVector<TaggedJob*> &jobs);

					SendToWorkerThunk(JobWorker *w, JobControl *c);
				};

			public:
				class JobListSerializer
				{
				public:
					QVector<QString> mainJobList;
					QVector<Pair<QString, QVector<QString>*>*> workersAndTheirJobLists;

				private:
					void InitializeInstanceFields();

public:
					JobListSerializer()
					{
						InitializeInstanceFields();
					}
				};

			private:
				QMap<QString, TaggedJob*> allJobs; //storage for all the jobs and profiles known to the system
				QMap<QString, JobWorker*> workers;
				MeXgui::MainForm *mainForm;
				WorkerSummary *summary;
				AfterEncoding currentAfterEncoding;
				SeQMaphore *resourceLock;

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

				const SeQMaphore &getResourceLock() const;
				void setResourceLock(const SeQMaphore &value);

			private:
				void addSendToTemporaryWorkerMenuItem();

			public:
				void ReleaseJob(TaggedJob *j);

			private:
				void addSendToWorkerMenuItems();

			public:
				void setMainForm(const MeXgui::MainForm &value);

				const bool &getIsAnyWorkerEncoding() const;
				const bool &getIsAnyWorkerEncodingAudio() const;
				const AfterEncoding &getCurrentAfterEncoding() const;

			private:
				void addClearButton();

				void deleteAllJobsButton_Click();
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

				QVector<QString> toStringList(IEnumerable<TaggedJob*> *jobList);
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

				QVector<TaggedJob*> toJobList(IEnumerable<QString> *list);

				/// <summary>
				/// saves a job to programdirectory\jobs\jobname.xml
				/// using the XML Serializer we get a humanly readable file
				/// </summary>
				/// <param name="job">the Job object to be saved</param>
				/// <param name="path">The path where the program was launched from</param>
				void saveJob(TaggedJob *job, const QString &path);
				/// <summary>
				/// loads a job with a given name from programdirectory\jobs\jobname.xml
				/// </summary>
				/// <param name="name">name of the job to be loaded (corresponds to the filename)</param>
				/// <returns>the Job object that was read from the harddisk</returns>
				TaggedJob *loadJob(const QString &name);
				/// <summary>
				/// looks up the first free job number
				/// </summary>
				/// <returns>the job number that can be attributed to the next job to be added to the queue</returns>
			private:
				QString getFreeJobName();

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
				void showAfterEncodingStatus(MeXguiSettings *Settings);


				/// <summary>
				/// Returns the job under the given name
				/// </summary>
				/// <param name="p"></param>
				/// <returns></returns>
				TaggedJob *ByName(const QString &p);

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

				void RenameWorker(const QString &name, const QString &value);

			private:
				void jobQueue_StartClicked();

				void jobQueue_StopClicked();

				void jobQueue_AbortClicked();


				QString freeWorkerName();

			public:
				QVector<Pair<QString, bool>*> ListWorkers();

				void HideAllWorkers();

				void ShowAllWorkers();

				void RequestNewWorker();

			private:
				JobWorker *NewWorker(const QString &name, bool show);

				void WorkerFinishedJobs();

			public:
				void ShowSummary();

				void HideSummary();

				const bool &getSummaryVisible() const;

				void SetWorkerVisible(const QString &p, bool p_2);

			private:
				void newWorkerButton_Click();

			public:
				void UpdateProgress(const QString &name);

				void ShutDown(JobWorker *w);

				QVector<Pair<QString, bool>*> ListProgressWindows();

				void HideProgressWindow(const QString &p);

				void ShowProgressWindow(const QString &p);

			private:
				void cbAfterEncoding_SelectedIndexChanged();


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
				MeXgui::core::gui::HelpButton *helpButton1;
				MeXgui::core::gui::JobQueue *jobQueue;
				System::Windows::Forms::Button *newWorkerButton;
				System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;
				System::Windows::Forms::ComboBox *cbAfterEncoding;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
