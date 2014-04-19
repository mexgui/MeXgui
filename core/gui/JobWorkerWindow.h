#pragma once

#include "core/details/JobWorker.h"
#include "JobWorker.h"
#include "core/util/Exceptions.h"
#include <QString>

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



using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{
	namespace core
	{
		namespace gui
		{
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
			/// A Worker must always be in one of five states: Idle, Running, Stopping, Stopped, Postponed.
			/// Idle means that no jobs are currently being processed. Running means
			/// that a job is being processed, and further jobs will continue to be
			/// processed until either there are no more jobs or the worker is closed.
			/// Stopping means that a job is currently being processed, but after this
			/// job is completed, no further jobs will be started. Stopped means that no new
			/// will be processed automatically. Postponed means that because of another running
			/// job in another worker this worker is stopped temporarily.
			/// 
			/// ProcessingThreads can run in several modes, enumerated 
			/// </summary>

			class NameTakenException : public MeXguiException
			{
			private:
				QString name;
			public:
				const QString &getName() const;
				NameTakenException(const QString &name);
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
				Stopping,
				Stopped,
				Postponed
			};
			enum JobsOnQueue
			{
				Delete,
				ReturnToMainQueue
			};
			enum IdleReason
			{
				FinishedQueue,
				Stopped,
				Aborted
			};

		}
	}
}
