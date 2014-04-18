#include "D2VIndexJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace MeGUI
{

	D2VIndexJob::D2VIndexJob() : IndexJob()
	{
	}

	D2VIndexJob::D2VIndexJob(const std::string &input, const std::string &output, int demuxType, std::vector<AudioTrackInfo*> &audioTracks, bool loadSources, bool demuxVideo) : IndexJob()
	{
		Input = input;
		Output = output;
		setDemuxMode(demuxType);
		setAudioTracks(audioTracks);
		setLoadSources(loadSources);
		setDemuxVideo(demuxVideo);
		FilesToDelete.push_back(Path::Combine(Path::GetDirectoryName(input), Path::GetFileNameWithoutExtension(input) + ".log"));
		FilesToDelete.push_back(output + ".bad");
		FilesToDelete.push_back(Path::ChangeExtension(output,".fix.txt"));
	}

	const std::string &D2VIndexJob::getCodecString() const
	{
		return "";
	}

	const std::string &D2VIndexJob::getEncodingMode() const
	{
		return "idx";
	}
}
