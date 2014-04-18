#pragma once

#include "TrackInfo.h"
#include "CodecManager.h"
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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{
	class AudioTrackInfo : public TrackInfo
	{
	private:
		std::string nbChannels, samplingRate, channelPositions;
		int aacFlag;

	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AudioTrackInfo() : this(nullptr, nullptr, 0)
		AudioTrackInfo();

		AudioTrackInfo(const std::string &language, const std::string &codec, int trackID);

		const std::string &getTrackIDx() const;
		void setTrackIDx(const std::string &value);

		const std::string &getDgIndexID() const;

		const std::string &getNbChannels() const;
		void setNbChannels(const std::string &value);

		const std::string &getChannelPositions() const;
		void setChannelPositions(const std::string &value);

		const std::string &getSamplingRate() const;
		void setSamplingRate(const std::string &value);

		const int &getAACFlag() const;
		void setAACFlag(const int &value);

		virtual std::string ToString();
	};
}
