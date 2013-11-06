#pragma once

#include "core/details/Streams.h"
#include "core/util/DAR.h"
#include "core/util/FileSize.h"
#include "core/details/CodecManager.h"
#include <string>
#include <vector>

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

using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{
	/// <summary>
	/// Summary description for MuxSettings.
	/// </summary>
	class MuxSettings
	{
	private:
		std::vector<MuxStream*> audioStreams, subtitleStreams;
		Nullable<decimal> framerate;
		std::string chapterFile, videoName;
		std::string muxedInput, videoInput, muxedOutput, deviceType;
		bool muxAll;
		Nullable<Dar> dar;

		Nullable<FileSize> splitSize;

	public:
		MuxSettings();

		const std::string &getMuxedInput() const;
		void setMuxedInput(const std::string &value);

		const std::string &getMuxedOutput() const;
		void setMuxedOutput(const std::string &value);

		const std::string &getVideoInput() const;
		void setVideoInput(const std::string &value);

		/// <summary>
		/// Array of all the audio streams to be muxed
		/// </summary>
		const std::vector<MuxStream*> &getAudioStreams() const;
		void setAudioStreams(const std::vector<MuxStream*> &value);

		/// <summary>
		/// Array of subtitle tracks to be muxed
		/// </summary>
		const std::vector<MuxStream*> &getSubtitleStreams() const;
		void setSubtitleStreams(const std::vector<MuxStream*> &value);

		/// <summary>
		/// framerate of the video
		/// </summary>
		const Nullable<decimal> &getFramerate() const;
		void setFramerate(const Nullable<decimal> &value);

		/// <summary>
		/// the file containing the chapter information
		/// </summary>
		const std::string &getChapterFile() const;
		void setChapterFile(const std::string &value);

		/// <summary>
		/// file size at which the output file is to be split
		/// </summary>
		const Nullable<FileSize> &getSplitSize() const;
		void setSplitSize(const Nullable<FileSize> &value);

		const Nullable<Dar> &getDAR() const;
		void setDAR(const Nullable<Dar> &value);

		const std::string &getDeviceType() const;
		void setDeviceType(const std::string &value);

		/// <summary>
		/// gets / sets the name of the video track
		/// </summary>
	   const std::string &getVideoName() const;
	   void setVideoName(const std::string &value);

		/// <summary>
		/// gets / sets if the complete input file must be muxed
		/// </summary>
		const bool &getMuxAll() const;
		void setMuxAll(const bool &value);

	};
}
