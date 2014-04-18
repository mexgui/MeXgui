#pragma once

#include "core/util/Exceptions.h"
#include <string>
#include <vector>
#include <cctype>
#include "stringconverter.h"

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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::details;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::tools::besplitter;

namespace MeGUI
{
	class JobID
	{
	private:
		static Random *const gen;

		std::string name;
	public:
		const std::string &getName() const;
	private:
		int uniqueID;
	public:
		const int &getUniqueID() const;

		JobID(const std::string &name);

		virtual std::string ToString();

		virtual bool Equals(object *obj);

		virtual int GetHashCode();
	};

	enum ProcessPriority
	{
		IDLE = 0,
		BELOW_NORMAL,
		NORMAL,
		ABOVE_NORMAL,
		HIGH
	};
	enum JobStatus
	{
		WAITING = 0,
		PROCESSING,
		POSTPONED,
		ERROR,
		ABORTED,
		DONE,
		SKIP,
		ABORTING
	};
	// status of job, 0: waiting, 1: processing, 2: postponed, 3: error, 4: aborted, 5: done, 6: skip, 7: aborting


	/// <summary>
	/// This represents an un-identifiable job. It only has information about how to complete
	/// it and no way to say *which specific job* it is in the queue. Furthermore, it doesn't
	/// have any extraneous information about its storage in the queue. That information is held
	/// in the TaggedJob class.
	/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlInclude(VideoJob::typeid), XmlInclude(AudioJob::typeid), XmlInclude(MuxJob::typeid), XmlInclude(MuxStream::typeid), XmlInclude(D2VIndexJob::typeid), XmlInclude(AviSynthJob::typeid), XmlInclude(SubtitleIndexJob::typeid), XmlInclude(AudioSplitJob::typeid), XmlInclude(AudioJoinJob::typeid), XmlInclude(CleanupJob::typeid), XmlInclude(DGAIndexJob::typeid), XmlInclude(FFMSIndexJob::typeid), XmlInclude(DGIIndexJob::typeid), XmlInclude(HDStreamsExJob::typeid), XmlInclude(PgcDemuxJob::typeid), XmlInclude(MkvExtractJob::typeid), XmlInclude(OneClickPostProcessingJob::typeid)]
	class Job
	{
	public:
		std::string Input;
		std::string Output;
		std::vector<std::string> FilesToDelete;

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public Job():this(nullptr, nullptr)
		Job();

		Job(const std::string &input, const std::string &output);

		/// <summary>
		/// Codec used
		/// </summary>
		virtual const std::string &getCodecString() const = 0;

		/// <summary>
		/// New meaning: Encoding mode means job type: video/audio/mux/index/split/etc
		/// </summary>
		virtual const std::string &getEncodingMode() const = 0;

	};
}
