#pragma once

#include "packages/audio/AudioCodecSettings.h"
#include "OneClickSettings.h"
#include "core/details/TrackInfo.h"
#include "core/details/AudioTrackInfo.h"
#include "core/details/SubtitleTrackInfo.h"
#include <QString>

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

//using namespace System::Text;

//using namespace System::Xml::Serialization;

using namespace MeXgui::core::util;

namespace MeXgui
{
	class OneClickStream
	{
	private:
		QString _inputFilePath;
		QString _demuxFilePath;
		AudioCodecSettings *_encoderSettings;
		AudioEncodingMode _encodingMode;
		MeXgui::TrackInfo *_trackInfo;

	public:
		OneClickStream(const QString &path, TrackType trackType, const QString &codec, const QString &container, int ID, const QString &language, const QString &name, int delay, bool bDefaultTrack, bool bForceTrack, AudioCodecSettings *oSettings, AudioEncodingMode oEncodingMode);

		OneClickStream(AudioTrackInfo *oInfo);

		OneClickStream(SubtitleTrackInfo *oInfo);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public OneClickStream() : this(nullptr, TrackType.Unknown, nullptr, nullptr, 0, nullptr, nullptr, 0, false, false, nullptr, AudioEncodingMode.IfCodecDoesNotMatch)
		OneClickStream();

		// Stream Type
		const TrackType &getType() const;

		// Stream Language
		const QString &getLanguage() const;
		void setLanguage(const QString &value);

		// Stream Name
		const QString &getName() const;
		void setName(const QString &value);

		// Demux File Path
		const QString &getDemuxFilePath() const;
		void setDemuxFilePath(const QString &value);

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
		const MeXgui::TrackInfo &getTrackInfo() const;
		void setTrackInfo(const MeXgui::TrackInfo &value);

		// Audio Track Info
		const AudioCodecSettings &getEncoderSettings() const;
		void setEncoderSettings(const AudioCodecSettings &value);

		// Audio Track Info
		const AudioEncodingMode &getEncodingMode() const;
		void setEncodingMode(const AudioEncodingMode &value);

		virtual QString ToString();
	};
}

