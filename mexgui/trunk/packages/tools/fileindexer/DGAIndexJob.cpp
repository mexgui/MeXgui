#include "DGAIndexJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace MeGUI
{

	DGAIndexJob::DGAIndexJob() : IndexJob()
	{
	}

	DGAIndexJob::DGAIndexJob(const std::string &input, const std::string &output, int demuxType, std::vector<AudioTrackInfo*> &audioTracks, bool loadSources, bool demuxVideo)
	{
		Input = input;
		Output = output;
		setDemuxMode(demuxType);
		setAudioTracks(audioTracks);
		setLoadSources(loadSources);
		setDemuxVideo(demuxVideo);
		FilesToDelete.push_back(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(input), System::IO::Path::GetFileNameWithoutExtension(input) + ".log"));
	}

	const std::string &DGAIndexJob::getCodecString() const
	{
		return "";
	}

	const std::string &DGAIndexJob::getEncodingMode() const
	{
		return "idx";
	}
}
