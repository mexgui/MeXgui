#include "IndexJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace MeGUI
{

	IndexJob::IndexJob() : Job()
	{
		loadSources = false;
		demuxVideo = false;
		demuxMode = 0;
		audioTracks = std::vector<AudioTrackInfo*>();
		audioTracksDemux = std::vector<AudioTrackInfo*>();
	}

	const bool &IndexJob::getLoadSources() const
	{
		return loadSources;
	}

	void IndexJob::setLoadSources(const bool &value)
	{
		loadSources = value;
	}

	const bool &IndexJob::getDemuxVideo() const
	{
		return demuxVideo;
	}

	void IndexJob::setDemuxVideo(const bool &value)
	{
		demuxVideo = value;
	}

	const int &IndexJob::getDemuxMode() const
	{
		return demuxMode;
	}

	void IndexJob::setDemuxMode(const int &value)
	{
		demuxMode = value;
	}

	const std::vector<AudioTrackInfo*> &IndexJob::getAudioTracks() const
	{
		return audioTracks;
	}

	void IndexJob::setAudioTracks(const std::vector<AudioTrackInfo*> &value)
	{
		audioTracks = value;
	}

	const std::vector<AudioTrackInfo*> &IndexJob::getAudioTracksDemux() const
	{
		return audioTracksDemux;
	}

	void IndexJob::setAudioTracksDemux(const std::vector<AudioTrackInfo*> &value)
	{
		audioTracksDemux = value;
	}

	const std::string &IndexJob::getCodecString() const
	{
		return "";
	}

	const std::string &IndexJob::getEncodingMode() const
	{
		return "idx";
	}
}
