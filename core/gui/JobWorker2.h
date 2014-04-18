#pragma once

#include "core/details/JobWorker.h"
#include "JobWorker.h"
#include "core/util/Exceptions.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/details/TaggedJob.h"
#include "MeGUI.ProgressWindow.h"
#include "MeGUI.MainForm.h"
#include "core/util/LogItem.h"
#include "core/util/Util.h"
#include "core/plugins/interfaces/Job.h"
#include "JobWorkerWindow.h"
#include "core/details/video/VideoCodecSettings.h"
#include "ProgressWindow.h"
#include "core/util/GenericRegisterer.h"
#include "core/details/JobControl.h"
#include "core/details/StatusUpdate.h"
#include "core/util/WindowUtil.h"
#include "MeGUI.core.gui.InputBox.h"
#include "MeGUI.core.gui.HelpButton.h"
#include "MeGUI.core.gui.JobQueue.h"
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





//using namespace System::Threading;

//using namespace System::Text;



using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class JobWorker : public System::Windows::Forms::Form
			{
			private:
				enum ExceptionType
				{
					UserSkip,
					Error
				};
			private:
				class JobStartException : public MeGUIException
				{
				public:
					ExceptionType type;
					JobStartException(const QString &reason, ExceptionType type);
				};
			private:
				IJobProcessor *currentProcessor;
				TaggedJob *currentJob; // The job being processed at the moment
				ProgressWindow *pw;
				MainForm *mainForm;
				decimal progress;
				LogItem *log;

				public:
				~JobWorker()
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
				void HideProcessWindow();

				void ShowProcessWindow();
				/// <summary>
				/// callback for the progress window
				/// this method is called if the abort button in the progress window is called
				/// it stops the encoder cold
				/// </summary>
			private:
				void pw_Abort();

				/// <summary>
				/// catches the ChangePriority event from the progresswindow and forward it to the encoder class
				/// </summary>
				/// <param name="priority"></param>
				void pw_PriorityChanged(ProcessPriority priority);

			public:
				const decimal &getProgress() const;

			private:
				PauseState pauseStatus;
			public:
				const PauseState &getPauseStatus() const;

				const QString &getStatusString() const;

			private:
				JobWorkerMode mode;
			public:
				const JobWorkerMode &getMode() const;
				void setMode(const JobWorkerMode &value);

			private:
				JobWorkerStatus status;
			public:
				const JobWorkerStatus &getStatus() const;

			private:
				bool bIsTemporaryWorker;
			public:
				const bool &getIsTemporaryWorker() const;
				void setIsTemporaryWorker(const bool &value);

				void SetStopping();

				void SetRunning();

			private:
				QString name;
			public:
				const QString &getName() const;
				void setName(const QString &value);

				const int &getLocalJobCount() const;

				const bool &getIsEncoding() const;

				const bool &getIsEncodingAudio() const;

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler WorkerFinishedJobs;

			private:
				std::QMap<QString, TaggedJob*> localJobs;

			public:
				JobWorker(MainForm *mf);



				/// <summary>
				/// Postprocesses the given job according to the JobPostProcessors in the mainForm's PackageSystem
				/// </summary>
				/// <param name="job"></param>
			private:
				void postprocessJob(Job *job);

				/// <summary>
				/// Preprocesses the given job according to the JobPreProcessors in the mainForm's PackageSystem
				/// </summary>
				/// <param name="job"></param>
				void preprocessJob(Job *job);

				IJobProcessor *getProcessor(Job *job);

			public:
				void ShutDown();

				void UserRequestShutDown();

			private:
				void returnJobsToMainQueue();

			public:
				void GUIDeleteJob(TaggedJob *j);

			private:
				void refreshAll();

				void updateProgress();

				/// <summary>
				/// aborts the currently active job
				/// </summary>
			public:
				void Abort();


				void StartEncoding(bool showMessageBoxes);

				/// <summary>
				/// Copies completion info into the job: end time, FPS, status.
				/// </summary>
				/// <param name="job">Job to fill with info</param>
				/// <param name="su">StatusUpdate with info</param>
			private:
				void copyInfoIntoJob(TaggedJob *job, StatusUpdate *su);

				/// <summary>
				/// updates the actual GUI with the status information received as parameter
				/// If the StatusUpdate indicates that the job has ended, the Progress window is closed
				/// and the logging messages from the StatusUpdate object are added to the log tab
				/// if the job mentioned in the statusupdate has a next job name defined, the job is looked
				/// up and processing of that job starts - this applies even in queue encoding mode
				/// the linked jobs will always be encoded first, regardless of their position in the queue
				/// If we're in queue encoding mode, the next nob in the queue is also started
				/// </summary>
				/// <param name="su">StatusUpdate object containing the current encoder stats</param>
				void UpdateGUIStatus(StatusUpdate *su);

				/// <summary>
				/// shuts down this worker if no jobs are waiting
				/// </summary>
				/// <returns>true if worker was shut down, false otherwise</returns>
				bool shutdownWorkerIfJobsCompleted();

				/// <summary>
				/// starts the job provided as parameters
				/// </summary>
				/// <param name="job">the Job object containing all the parameters</param>
				/// <returns>success / failure indicator</returns>
				bool startEncoding(TaggedJob *job);

				TaggedJob *getNextJob();

				JobStartInfo startNextJobInQueue();

				/// <summary>
				/// marks job currently marked as processing as aborted
				/// </summary>
				void markJobAborted();

			public:
				void Pause();

				void Resume();
			protected:
				virtual void OnClosing(CancelQEvent *e);
			public:
				void RemoveJobFromQueue(TaggedJob *job);

				void UserRequestedAbort();


				const IEnumerable<TaggedJob*> &getJobs() const;
				void setJobs(const IEnumerable<TaggedJob*> &value);

				void UserRequestedRename();

				void ShutDownWhenFinished();


			private:
				void changeNameToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void setName(const QString &p);

				void shutDownWhenFinishedLocalQueueToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void shutDownWorkerNowToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void showProgressWindowToolStripMenuItem_Click(QObject *sender, QEvent *e);

			public:
				void RefreshInfo();

			private:
				void jobQueue1_AbortClicked(QObject *sender, QEvent *e);

				void jobQueue1_StartClicked(QObject *sender, QEvent *e);

				void jobQueue1_StopClicked(QObject *sender, QEvent *e);


			public:
				void AddJob(TaggedJob *j);

				const bool &getIsProgressWindowAvailable() const;

				const bool &getIsProgressWindowVisible() const;

			private:
				void progressWindowToolStripMenuItem_DropDownOpened(QObject *sender, QEvent *e);

				bool alive;
			public:
				void CloseForReal();

			private:
				void JobWorker_FormClosed(QObject *sender, FormClosedQEvent *e);


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


				JobQueue *jobQueue1;
				System::Windows::Forms::ProgressBar *jobProgress;
				System::Windows::Forms::Label *progressLabel;
				System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel2;
				System::Windows::Forms::MenuStrip *menuStrip1;
				System::Windows::Forms::ToolStripMenuItem *workerToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *progressWindowToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *showProgressWindowToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *changeNameToolStripMenuItem;
				System::Windows::Forms::ToolStripSeparator *toolStripSeparator1;
				System::Windows::Forms::ToolStripMenuItem *shutDownWhenFinishedLocalQueueToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *shutDownWorkerNowToolStripMenuItem;
				System::Windows::Forms::Panel *panel1;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
