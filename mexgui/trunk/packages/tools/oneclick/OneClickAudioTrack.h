#pragma once

#include "packages/audio/AudioJob.h"
#include "core/details/Streams.h"
#include "core/details/AudioTrackInfo.h"

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
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{
	/// <summary>
	/// Summary description for OneClickAudioTrack.
	/// </summary>
	class OneClickAudioTrack
	{
	private:
		MeGUI::AudioJob *_audioJob;
		MuxStream *_directMuxAudio;
		MeGUI::AudioTrackInfo *_audioTrackInfo;

	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public OneClickAudioTrack() : this(nullptr, nullptr, nullptr, false)
		OneClickAudioTrack();

		OneClickAudioTrack(MeGUI::AudioJob *oAudioJob, MuxStream *oMuxStream, MeGUI::AudioTrackInfo *oAudioTrackInfo, bool bMKVTrack);

		/// <summary>
		/// gets / sets the container of the output
		/// </summary>
		const MeGUI::AudioJob &getAudioJob() const;
		void setAudioJob(const MeGUI::AudioJob &value);

		const MuxStream &getDirectMuxAudio() const;
		void setDirectMuxAudio(const MuxStream &value);

		const MeGUI::AudioTrackInfo &getAudioTrackInfo() const;
		void setAudioTrackInfo(const MeGUI::AudioTrackInfo &value);
	};
}
