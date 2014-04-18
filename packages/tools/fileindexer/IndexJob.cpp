#include "IndexJob.h"




//using namespace System::Collections::Generic;

namespace MeXgui
{

	IndexJob::IndexJob() : Job()
	{
		loadSources = false;
		demuxVideo = false;
		demuxMode = 0;
		audioTracks = QVector<AudioTrackInfo*>();
		audioTracksDemux = QVector<AudioTrackInfo*>();
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

	const QVector<AudioTrackInfo*> &IndexJob::getAudioTracks() const
	{
		return audioTracks;
	}

	void IndexJob::setAudioTracks(const QVector<AudioTrackInfo*> &value)
	{
		audioTracks = value;
	}

	const QVector<AudioTrackInfo*> &IndexJob::getAudioTracksDemux() const
	{
		return audioTracksDemux;
	}

	void IndexJob::setAudioTracksDemux(const QVector<AudioTrackInfo*> &value)
	{
		audioTracksDemux = value;
	}

	const QString &IndexJob::getCodecString() const
	{
		return "";
	}

	const QString &IndexJob::getEncodingMode() const
	{
		return "idx";
	}
}
