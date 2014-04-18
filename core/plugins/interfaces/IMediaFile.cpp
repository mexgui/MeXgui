#include "IMediaFile.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;
using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

	MediaFile::MediaFile(QVector<MediaTrack*> &tracks, Chapters *chapters, TimeSpan *playTime, ContainerType *container)
	{
		this->Container = container;

		AudioTracks = QVector<AudioTrack*>();
		SubtitleTracks = QVector<SubtitleTrack*>();

		for (QVector<MediaTrack*>::const_iterator m = tracks.begin(); m != tracks.end(); ++m)
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

	VideoInfo2::VideoInfo2(quint64 width, quint64 height, Dar dar, quint64 framecount, double fps)
	{
		Width = width;
		Height = height;
		DAR = dar;
		FrameCount = framecount;
		FPS = fps;
	}
}
