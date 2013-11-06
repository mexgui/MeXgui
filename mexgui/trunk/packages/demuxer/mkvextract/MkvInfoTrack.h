#pragma once

#include "core/util/LanguageSelectionContainer.h"
#include "core/details/AudioTrackInfo.h"
#include "core/details/SubtitleTrackInfo.h"
#include "packages/tools/oneclick/OneClickStream.h"
#include "packages/tools/oneclick/OneClickSettings.h"
#include <string>
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
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{
	enum TrackType
	{
		Audio,
		Subtitle,
		Unknown,
		Video
	};

	class MkvInfoTrack
	{
	private:
		TrackType _type;
		int _iTrackID;
		std::string _strCodecID, _strLanguage, _strInputFile, _strName, _strAudioChannels;
		bool _bDefault, _bForced;

	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public MkvInfoTrack() : this(nullptr)
		MkvInfoTrack();

		MkvInfoTrack(const std::string &strInputFile);

		const TrackType &getType() const;
		void setType(const TrackType &value);

		const int &getTrackID() const;
		void setTrackID(const int &value);

		const std::string &getCodecID() const;
		void setCodecID(const std::string &value);

		const std::string &getAudioChannels() const;
		void setAudioChannels(const std::string &value);

		const std::string &getLanguage() const;
		void setLanguage(const std::string &value);

		const std::string &getName() const;
		void setName(const std::string &value);

		const std::string &getInputFile() const;
		void setInputFile(const std::string &value);

		const bool &getDefaultTrack() const;
		void setDefaultTrack(const bool &value);

		const bool &getForcedTrack() const;
		void setForcedTrack(const bool &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const std::string &getFileName() const;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const MeGUI::AudioTrackInfo &getAudioTrackInfo() const;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const OneClickStream &getSubtitleTrackInfo() const;
	};
}
