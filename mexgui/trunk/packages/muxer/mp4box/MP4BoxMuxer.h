#pragma once

#include "core/plugins/implemented/CommandlineMuxer.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/details/mux/MuxJob.h"
#include "core/details/mux/MuxProvider.h"
#include "core/plugins/implemented/CommandlineJobProcessor.h"
#include "core/util/LogItem.h"
#include "core/util/FileSize.h"
#include "core/details/mux/MuxSettings.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/details/CodecManager.h"
#include "core/details/Streams.h"
#include "core/util/LanguageSelectionContainer.h"
#include "packages/reader/ttxt/ttxtReader.h"
#include "core/util/FileUtil.h"
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
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{
	class MP4BoxMuxer : public CommandlineMuxer
	{
	private:
		enum LineType
		{
			other = 0,
			importing,
			writing,
			splitting,
			empty,
			error
		};
	public:
		static JobProcessorFactory *const Factory;

	private:
		static IJobProcessor *init(MainForm *mf, Job *j);

		int numberOfAudioTracks, numberOfSubtitleTracks, trackNumber;
		std::string lastLine;

	public:
		MP4BoxMuxer(const std::string &executablePath);
	protected:
		virtual void checkJobIO();


		/// <summary>
		/// looks at a line and returns its type
		/// </summary>
		/// <param name="line">the line to be analyzed</param>
		/// <returns>the line type</returns>
	private:
		LineType getLineType(const std::string &line);

	public:
		virtual void ProcessLine(const std::string &line, StreamType stream, ImageType oType);

		/// <summary>
		/// gets the completion percentage of an mp4box line
		/// </summary>
		/// <param name="line"></param>
		/// <returns></returns>
	private:
		Nullable<decimal> getPercentage(const std::string &line);

		/// <summary>
		/// determines if a read line is empty
		/// </summary>
		/// <param name="line"></param>
		/// <returns></returns>
		bool isEmptyLine(const std::string &line);
		/// <summary>
		/// compiles mp4 overhead statistics and dumps them to the log and a logfile
		/// </summary>
	public:
		void printStatistics();

	protected:
		const virtual std::string &getCommandline() const;
	};
}
