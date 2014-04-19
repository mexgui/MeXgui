#pragma once

#include "core/plugins/interfaces/Job.h"
#include "AudioCodecSettings.h"
#include "Properties.Settings.h"
#include "core/details/mux/MuxProvider.h"
#include "core/details/Streams.h"
#include "core/details/CodecManager.h"
#include "core/util/VideoUtil.h"
#include <QString>

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




//using namespace System::Xml::Serialization;

using namespace MeXgui::core::details;
using namespace MeXgui::core::plugins::interfaces;

namespace MeXgui
{
	/// <summary>
	/// Container object for audio encoding
	/// holds all the parameters relevant for aac encoding in besweet
	/// </summary>
	class AudioJob : public Job
	{
	public:
		QString CutFile;
		AudioCodecSettings *Settings;
		int Delay;
		QString Language;
		QString Name;

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AudioJob() : this(nullptr, nullptr, nullptr, nullptr, 0, nullptr, nullptr)
		AudioJob();

		AudioJob(const QString &input, const QString &output, const QString &cutfile, AudioCodecSettings *settings, int delay, const QString &strLanguage, const QString &strName);

		qint64 SizeBytes;

		MuxableType *ToMuxableType();

		MuxStream *ToMuxStream();

		const virtual QString &getCodecString() const;

		const virtual QString &getEncodingMode() const;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore]
		const AudioType &getType() const;

		BitrateManagementMode BitrateMode;
	};
}
