#pragma once

#include "core/util/Exceptions.h"
#include <QString>
#include <QVector>
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




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;

//using namespace System::Xml::Serialization;

using namespace MeXgui::core::details;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::besplitter;

namespace MeXgui
{
	class JobID
	{
	private:
		static Random *const gen;

		QString name;
	public:
		const QString &getName() const;
	private:
		int uniqueID;
	public:
		const int &getUniqueID() const;

		JobID(const QString &name);

		virtual QString ToString();

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
		QString Input;
		QString Output;
		QVector<QString> FilesToDelete;

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public Job():this(nullptr, nullptr)
		Job();

		Job(const QString &input, const QString &output);

		/// <summary>
		/// Codec used
		/// </summary>
		virtual const QString &getCodecString() const = 0;

		/// <summary>
		/// New meaning: Encoding mode means job type: video/audio/mux/index/split/etc
		/// </summary>
		virtual const QString &getEncodingMode() const = 0;

	};
}
