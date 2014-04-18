#include "FFMSIndexJob.h"




//using namespace System::Collections::Generic;

namespace MeXgui
{

	FFMSIndexJob::FFMSIndexJob() : IndexJob()
	{
	}

	FFMSIndexJob::FFMSIndexJob(const QString &input, const QString &indexFile, int demuxType, QVector<AudioTrackInfo*> &audioTracks, bool loadSources) : IndexJob()
	{
		Input = input;
		setLoadSources(loadSources);
		if (indexFile.empty())
			Output = input + ".ffindex";
		else
			Output = indexFile;

		if (audioTracks.empty() || audioTracks.empty())
		{
			setAudioTracks(QVector<AudioTrackInfo*>());
			setDemuxMode(0);
		}
		else
		{
			setDemuxMode(demuxType);
			setAudioTracks(audioTracks);
		}

		setDemuxVideo(false);
	}

	const QString &FFMSIndexJob::getCodecString() const
	{
		return "";
	}

	const QString &FFMSIndexJob::getEncodingMode() const
	{
		return "idx";
	}
}
