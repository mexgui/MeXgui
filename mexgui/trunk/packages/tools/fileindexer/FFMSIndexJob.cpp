#include "FFMSIndexJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace MeGUI
{

	FFMSIndexJob::FFMSIndexJob() : IndexJob()
	{
	}

	FFMSIndexJob::FFMSIndexJob(const std::string &input, const std::string &indexFile, int demuxType, std::vector<AudioTrackInfo*> &audioTracks, bool loadSources) : IndexJob()
	{
		Input = input;
		setLoadSources(loadSources);
		if (indexFile.empty())
			Output = input + ".ffindex";
		else
			Output = indexFile;

		if (audioTracks.empty() || audioTracks.empty())
		{
			setAudioTracks(std::vector<AudioTrackInfo*>());
			setDemuxMode(0);
		}
		else
		{
			setDemuxMode(demuxType);
			setAudioTracks(audioTracks);
		}

		setDemuxVideo(false);
	}

	const std::string &FFMSIndexJob::getCodecString() const
	{
		return "";
	}

	const std::string &FFMSIndexJob::getEncodingMode() const
	{
		return "idx";
	}
}
