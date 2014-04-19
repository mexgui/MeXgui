#pragma once

#include "JobWorkerWindow.h"
#include "core/util/Exceptions.h"
#include "JobWorker.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "ProgressWindow.h"
#include "MainForm.h"
#include "core/details/video/VideoCodecSettings.h"
#include "core/util/GenericRegisterer.h"
#include "core/details/JobControl.h"
#include "core/details/StatusUpdate.h"
#include "ProgressWindow.h"
#include <QString>
#include <QMap>
#include <QVector>
#include <stdexcept>

#if defined(NONE)



//using namespace System::Collections::Generic;

//using namespace System::Text;
using namespace MeXgui::core::gui;

//using namespace System::Diagnostics;
using namespace MeXgui::core::util;





//using namespace System::Threading;

namespace MeXgui
{
	namespace core
	{
		namespace details
		{

			class NameTakenException : public MeXguiException
			{
			private:
				QString name;
			public:
				const QString &getName() const;
				NameTakenException(const QString &name);
			};
			/// <summary>
			/// This class represents a processing 'worker', which processes jobs
			/// one by one. In a single instance of MeXgui, there can be multiple
			/// workers, facilitating parallel job processing.
			/// 
			/// JobControl keeps the job queue, and distributes jobs one by one when
			/// requested by a JobWorker. Each JobWorker also maintains a list of jobs
			/// reserved for that particular worker. Ordinarily, this list is empty, 
			/// and the worker just requests jobs from the queue until none are left.
			/// However, it may be useful to specify 'run this job now' or 'run these
			/// jobs now', in which case they are put onto the reserved jobs list,
			/// and they are run before requesting any from the job queue.
			/// 
			/// This can be useful for running small jobs like muxing or d2v indexing
			/// while a video encode is going in the background: since the user is at
			/// the computer *now*, he/she doesn't want to wait until the video encode
			/// is finished, and can instead select 'run this job in a new worker.'
			/// This will also be how indexing and autodeint jobs are run from the
			/// AviSynth script creator. In fact, it will be possible to process jobs
			/// without them ever being on the main job queue: they can be put directly
			/// onto a worker's local list and run from that.
			/// 
			/// Dependencies are managed by JobControl. Each job has a list of jobs
			/// it depends on; a job will only be distributed to a worker if all the
			/// dependant jobs have been completed successfully.
			/// 
			/// A Worker can run in two modes: RequestNewJobs and CloseOnLocalListCompleted.
			/// RequestNewJobs means that after the the local list is completed, it
			/// requests another job from the Job Control, continuing until all jobs
			/// are completed. In this mode, the JobWorker never closes by itself.
			/// CloseOnLocalListCompleted means that it will complete the jobs on
			/// its local list and then close, without requesting any more jobs from
			/// the JobControl.
			/// 
			/// A Worker must always be in one of three states: Idle, Running, Stopping.
			/// Idle means that no jobs are currently being processed. Running means
			/// that a job is being processed, and further jobs will continue to be
			/// processed until either there are no more jobs or the worker is closed.
			/// Stopping means that a job is currently being processed, but after this
			/// job is completed, no further jobs will be started.
			/// 
			/// 
			/// 
			/// ProcessingThreads can run in several modes, enumerated 
			/// </summary>
			class JobWorker
			{
			private:
				enum ExceptionType
				{
					UserSkip,
					Error
				};
			private:
				class JobStartException : public MeXguiException
				{
				public:
					ExceptionType type;
					JobStartException(const QString &reason, ExceptionType type);
				};
			private:
				IJobProcessor *currentProcessor;
				Job *currentJob; // The job being processed at the moment
				ProgressWindow *pw;
				JobWorkerWindow *display;
				MainForm *mainForm;
				int progress;

			public:
				void HideProcessWindow();

				void ShowProcessWindow();

				const bool &getProcessWindowAccessible() const;
				/// <summary>
				/// callback for the Progress Window
				/// This is called when the progress window has been closed and ensures that
				/// no futher attempt is made to send a statusupdate to the progress window
				/// </summary>
			private:
				void pw_WindowClosed(bool hideOnly);
				/// <summary>
				/// callback for the progress window
				/// this method is called if the abort button in the progress window is called
				/// it stops the encoder cold
				/// </summary>
				void pw_Abort();

				/// <summary>
				/// catches the ChangePriority event from the progresswindow and forward it to the encoder class
				/// </summary>
				/// <param name="priority"></param>
				void pw_PriorityChanged(ProcessPriority priority);

			public:
				const int &getProgress() const;

			private:
				PauseState pauseStatus;
			public:
				const PauseState &getPauseStatus() const;


			private:
				JobWorkerMode mode;
			public:
				const JobWorkerMode &getMode() const;
				void setMode(const JobWorkerMode &value);

			private:
				JobWorkerStatus status;
			public:
				const JobWorkerStatus &getStatus() const;

				void SetStopping();

				void SetRunning();

			private:
				QString name;

			public:
				const QString &getName() const;
				void setName(const QString &value);

				const bool &getIsEncoding() const;

			private:
				std::QMap<QString, Job*> localJobs;

			public:
				JobWorker();


				static JobPostProcessor *const DeleteIntermediateFilesPostProcessor;

				/// <summary>
				/// Attempts to delete all files listed in job.FilesToDelete if settings.DeleteIntermediateFiles is checked
				/// </summary>
				/// <param name="job">the job which should just have been completed</param>
			private:
				static void deleteIntermediateFiles(MainForm *mainForm, Job *job);


				/// <summary>
				/// Postprocesses the given job according to the JobPostProcessors in the mainForm's PackageSystem
				/// </summary>
				/// <param name="job"></param>
				void postprocessJob(Job *job);

				/// <summary>
				/// Preprocesses the given job according to the JobPreProcessors in the mainForm's PackageSystem
				/// </summary>
				/// <param name="job"></param>
				void preprocessJob(Job *job);

				IJobProcessor *getProcessor(Job *job);

			public:
				void ShutDown(JobsOnQueue rest);
				void UserRequestShutDown();

				void GUIDeleteJob(Job *j);

				/// <summary>
				/// aborts the currently active job
				/// </summary>
				void Abort();

			private:
				void refreshAll();

			public:
				void StartEncoding(); //bool showMessageBoxes

				/// <summary>
				/// Copies completion info into the job: end time, FPS, status.
				/// </summary>
				/// <param name="job">Job to fill with info</param>
				/// <param name="su">StatusUpdate with info</param>
			private:
				void copyInfoIntoJob(Job *job, StatusUpdate *su);

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
				/// starts the job provided as parameters
				/// </summary>
				/// <param name="job">the Job object containing all the parameters</param>
				/// <returns>success / failure indicator</returns>
				bool startEncoding(Job *job);

				void addToLog(const QString &p);

				Job *getNextJob();

				JobStartInfo startNextJobInQueue();

				/// <summary>
				/// marks job currently marked as processing as aborted
				/// </summary>
				void markJobAborted();

			public:
				void Pause();

				void Resume();

				/// <summary>
				/// Makes sure that the progress window is closed
				/// </summary>
			private:
				void ensureProgressWindowClosed();


			public:
				void RemoveJobFromQueue(Job *job);

				void UserRequestedAbort();

			private:
				void InitializeInstanceFields();
			};

			enum PauseState
			{
				NotEncoding,
				Encoding,
				Paused
			};
			enum JobWorkerMode
			{
				RequestNewJobs,
				CloseOnLocalListCompleted
			};
			enum JobWorkerStatus
			{
				Idle,
				Running,
				Stopping
			};
			enum JobsOnQueue
			{
				Delete,
				ReturnToMainQueue
			};
		}
	}
}
#endif
