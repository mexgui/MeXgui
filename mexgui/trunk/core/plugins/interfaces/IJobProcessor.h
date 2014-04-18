#pragma once

#include "core/details/StatusUpdate.h"
#include "Job.h"
#include "core/util/LogItem.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/util/GenericRegisterer.h"
#include <string>

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
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
//using namespace System::Text;

using namespace MeGUI::core::util;

namespace MeGUI
{
	typedef void (*JobProcessingStatusUpdateCallback)(StatusUpdate *su);
	typedef LogItem *(*Processor)(MainForm *info, Job *job);

	/// <summary>
	/// Returns an IJobProcessor if this job can be processed, returns null otherwise.
	/// </summary>
	/// <param name="info"></param>
	/// <param name="job"></param>
	/// <returns></returns>
	typedef IJobProcessor *(*ProcessorFactory)(MainForm *info, Job *job);
	class JobPreProcessor : public IIDable
	{
	private:
		std::string id;
	public:
		const std::string &getID() const;
	private:
		Processor processor;
	public:
		const Processor &getPreProcessor() const;
		JobPreProcessor(Processor p, const std::string &id);
	};
	class JobPostProcessor : public IIDable
	{
	private:
		std::string id;
	public:
		const std::string &getID() const;
	private:
		Processor processor;
	public:
		const Processor &getPostProcessor() const;
		JobPostProcessor(Processor p, const std::string &id);
	};
	class JobProcessorFactory : public IIDable
	{
	private:
		std::string id;
	public:
		const std::string &getID() const;
	private:
		ProcessorFactory factory;
	public:
		const ProcessorFactory &getFactory() const;
		JobProcessorFactory(ProcessorFactory factory, const std::string &id);
	};

	class IJobProcessor
	{
		/// <summary>
		/// sets up encoding
		/// </summary
		/// <param name="job">the job to be processed</param>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if the setup has succeeded, false if it has not</returns>
	public:
		virtual void setup(Job*, StatusUpdate*, LogItem*) = 0;
		/// <summary>
		/// starts the encoding process
		/// </summary>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if encoding has been successfully started, false if not</returns>
		virtual void start() = 0;
		/// <summary>
		/// stops the encoding process
		/// </summary>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if encoding has been successfully stopped, false if not</returns>
		virtual void stop() = 0;
		/// <summary>
		/// pauses the encoding process
		/// </summary>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if encoding has been successfully paused, false if not</returns>
		virtual void pause() = 0;
		/// <summary>
		/// resumes the encoding process
		/// </summary>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if encoding has been successfully started, false if not</returns>
		virtual void resume() = 0;
		/// <summary>
		/// changes the priority of the encoding process/thread
		/// </summary>
		/// <param name="priority">the priority to change to</param>
		/// <param name="error">output for any errors that might ocurr during this method</param>
		/// <returns>true if the priority has been changed, false if not</returns>
		virtual void changePriority(ProcessPriority) = 0;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		event JobProcessingStatusUpdateCallback StatusUpdate;
	};
}
