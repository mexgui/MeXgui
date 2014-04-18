#pragma once

#include "core/details/StatusUpdate.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MeXgui.MainForm.h"
#include "AviSynthJob.h"
#include "packages/reader/avs/AvsReader.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include "core/util/LogItem.h"
#include "core/util/Exceptions.h"
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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

//using namespace System::Diagnostics;

//using namespace System::Text;

//using namespace System::Threading;

using namespace MeXgui::core::util;

namespace MeXgui
{
	 typedef void (*AviSynthStatusUpdateCallback)(StatusUpdate *su);

	class AviSynthProcessor : public IJobProcessor
	{
	private:
		DateTime startTime;
	public:
		static JobProcessorFactory *const Factory;

	private:
		static IJobProcessor *init(MainForm *mf, Job *j);

	protected:
		System::Threading::ManualResetEvent *mre; // lock used to pause encoding
#warning AvsFile should be refactored to IMediaFile once fast frame reading is supported
	private:
		AvsFile *file;
		IVideoReader *reader;
		bool aborted;
		quint64 position;
		Thread *processorThread, *statusThread;
	public:
		StatusUpdate *stup;
	private:
		AviSynthJob *job;
	public:
		AviSynthProcessor();

	private:
		void update();

		void process();
		/// <summary>
		/// sets up encoding
		/// </summary
		/// <param name="job">the job to be processed</param>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if the setup has succeeded, false if it has not</returns>
	public:
		void setup(Job *job, StatusUpdate *su, LogItem *_);
		/// <summary>
		/// starts the encoding process
		/// </summary>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if encoding has been successfully started, false if not</returns>
		void start();
		/// <summary>
		/// stops the encoding process
		/// </summary>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if encoding has been successfully stopped, false if not</returns>
		void stop();
		/// <summary>
		/// pauses the encoding process
		/// </summary>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if encoding has been successfully paused, false if not</returns>
		void pause();
		/// <summary>
		/// resumes the encoding process
		/// </summary>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if encoding has been successfully started, false if not</returns>
		void resume();
		/// <summary>
		/// changes the priority of the encoding process/thread
		/// </summary>
		/// <param name="priority">the priority to change to</param>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if the priority has been changed, false if not</returns>
		void changePriority(ProcessPriority priority);
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event JobProcessingStatusUpdateCallback StatusUpdate;

	private:
		void InitializeInstanceFields();
	};
}
