#pragma once

#include "core/plugins/interfaces/Job.h"
#include "core/details/AudioTrackInfo.h"
#include <string>
#include <vector>

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

namespace MeGUI
{
	/// <summary>
	/// Summary description for IndexJob.
	/// </summary>
	class IndexJob : public Job
	{
	private:
		bool loadSources;
		bool demuxVideo;
		int demuxMode;
		std::vector<AudioTrackInfo*> audioTracks;
		std::vector<AudioTrackInfo*> audioTracksDemux;

	public:
		IndexJob();

		/// <summary>
		/// gets / sets whether the audio and video files should be loaded after indexing
		/// </summary>
		const bool &getLoadSources() const;
		void setLoadSources(const bool &value);
		/// <summary>
		/// gets / sets whether the video stream should be extracted
		/// </summary>
		const bool &getDemuxVideo() const;
		void setDemuxVideo(const bool &value);
		/// <summary>
		/// gets / sets the demux mode
		/// 0 = no audio demux
		/// 1 = demux selected audio track
		/// 2 = demux all audio tracks
		/// </summary>
		const int &getDemuxMode() const;
		void setDemuxMode(const int &value);

		const std::vector<AudioTrackInfo*> &getAudioTracks() const;
		void setAudioTracks(const std::vector<AudioTrackInfo*> &value);

		const std::vector<AudioTrackInfo*> &getAudioTracksDemux() const;
		void setAudioTracksDemux(const std::vector<AudioTrackInfo*> &value);

		const virtual std::string &getCodecString() const;

		const virtual std::string &getEncodingMode() const;
	};
}
