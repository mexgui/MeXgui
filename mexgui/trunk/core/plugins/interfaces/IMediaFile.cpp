#include "IMediaFile.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{

	MediaFile::MediaFile(std::vector<MediaTrack*> &tracks, Chapters *chapters, TimeSpan *playTime, ContainerType *container)
	{
		this->Container = container;

		AudioTracks = std::vector<AudioTrack*>();
		SubtitleTracks = std::vector<SubtitleTrack*>();

		for (std::vector<MediaTrack*>::const_iterator m = tracks.begin(); m != tracks.end(); ++m)
		{
			if (dynamic_cast<VideoTrack*>(*m) != 0)
			{
				assert(VideoTrack_Renamed == 0, "Only one video track per file supported");
				VideoTrack_Renamed = static_cast<VideoTrack*>(*m);
			}
			if (dynamic_cast<AudioTrack*>(*m) != 0)
				AudioTracks.push_back(static_cast<AudioTrack*>(*m));
			if (dynamic_cast<SubtitleTrack*>(*m) != 0)
				SubtitleTracks.push_back(static_cast<SubtitleTrack*>(*m));
		}

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		tracks.Sort(delegate(MediaTrack a, MediaTrack b)
		{
			return static_cast<int>(a::TrackNumber) - static_cast<int>(b::TrackNumber);
		}
	   );

		Tracks = tracks;

		Chapters_Renamed = chapters;
		PlayTime = playTime;
	}

	VideoInfo2::VideoInfo2()
	{
	}

	VideoInfo2::VideoInfo2(unsigned long long width, unsigned long long height, Dar dar, unsigned long long framecount, double fps)
	{
		Width = width;
		Height = height;
		DAR = dar;
		FrameCount = framecount;
		FPS = fps;
	}
}
