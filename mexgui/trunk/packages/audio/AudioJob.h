#pragma once

#include "core/plugins/interfaces/Job.h"
#include "AudioCodecSettings.h"
#include "MeGUI.Properties.Settings.h"
#include "core/details/mux/MuxProvider.h"
#include "core/details/Streams.h"
#include "core/details/CodecManager.h"
#include "core/util/VideoUtil.h"
#include <string>

// ****************************************************************************
// 
// Copyright (C) 2005-2011  Doom9 & al
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
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::details;
using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{
	/// <summary>
	/// Container object for audio encoding
	/// holds all the parameters relevant for aac encoding in besweet
	/// </summary>
	class AudioJob : public Job
	{
	public:
		std::string CutFile;
		AudioCodecSettings *Settings;
		int Delay;
		std::string Language;
		std::string Name;

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AudioJob() : this(nullptr, nullptr, nullptr, nullptr, 0, nullptr, nullptr)
		AudioJob();

		AudioJob(const std::string &input, const std::string &output, const std::string &cutfile, AudioCodecSettings *settings, int delay, const std::string &strLanguage, const std::string &strName);

		long long SizeBytes;

		MuxableType *ToMuxableType();

		MuxStream *ToMuxStream();

		const virtual std::string &getCodecString() const;

		const virtual std::string &getEncodingMode() const;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore]
		const AudioType &getType() const;

		BitrateManagementMode BitrateMode;
	};
}
