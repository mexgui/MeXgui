#pragma once

#include "packages/audio/AudioCodecSettings.h"
#include "OneClickSettings.h"
#include "core/details/TrackInfo.h"
#include "core/details/AudioTrackInfo.h"
#include "core/details/SubtitleTrackInfo.h"
#include <string>

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
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::util;

namespace MeGUI
{
	class OneClickStream
	{
	private:
		std::string _inputFilePath;
		std::string _demuxFilePath;
		AudioCodecSettings *_encoderSettings;
		AudioEncodingMode _encodingMode;
		MeGUI::TrackInfo *_trackInfo;

	public:
		OneClickStream(const std::string &path, TrackType trackType, const std::string &codec, const std::string &container, int ID, const std::string &language, const std::string &name, int delay, bool bDefaultTrack, bool bForceTrack, AudioCodecSettings *oSettings, AudioEncodingMode oEncodingMode);

		OneClickStream(AudioTrackInfo *oInfo);

		OneClickStream(SubtitleTrackInfo *oInfo);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public OneClickStream() : this(nullptr, TrackType.Unknown, nullptr, nullptr, 0, nullptr, nullptr, 0, false, false, nullptr, AudioEncodingMode.IfCodecDoesNotMatch)
		OneClickStream();

		// Stream Type
		const TrackType &getType() const;

		// Stream Language
		const std::string &getLanguage() const;
		void setLanguage(const std::string &value);

		// Stream Name
		const std::string &getName() const;
		void setName(const std::string &value);

		// Demux File Path
		const std::string &getDemuxFilePath() const;
		void setDemuxFilePath(const std::string &value);

		// Stream Delay
		const int &getDelay() const;
		void setDelay(const int &value);

		// Stream Delay
		const bool &getForcedStream() const;
		void setForcedStream(const bool &value);

		// Stream Delay
		const bool &getDefaultStream() const;
		void setDefaultStream(const bool &value);

		// Track Info
		const MeGUI::TrackInfo &getTrackInfo() const;
		void setTrackInfo(const MeGUI::TrackInfo &value);

		// Audio Track Info
		const AudioCodecSettings &getEncoderSettings() const;
		void setEncoderSettings(const AudioCodecSettings &value);

		// Audio Track Info
		const AudioEncodingMode &getEncodingMode() const;
		void setEncodingMode(const AudioEncodingMode &value);

		virtual std::string ToString();
	};
}

