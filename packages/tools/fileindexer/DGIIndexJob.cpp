#include "DGIIndexJob.h"




//using namespace System::Collections::Generic;

namespace MeXgui
{

	DGIIndexJob::DGIIndexJob() : IndexJob()
	{
	}

	DGIIndexJob::DGIIndexJob(const QString &input, const QString &output, int demuxType, QVector<AudioTrackInfo*> &audioTracks, bool loadSources, bool demuxVideo)
	{
		Input = input;
		Output = output;
		setDemuxMode(demuxType);
		setAudioTracks(audioTracks);
		setLoadSources(loadSources);
		setDemuxVideo(demuxVideo);
		FilesToDelete.push_back(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(input), System::IO::Path::GetFileNameWithoutExtension(input) + ".log"));
	}

	const QString &DGIIndexJob::getCodecString() const
	{
		return "";
	}

	const QString &DGIIndexJob::getEncodingMode() const
	{
		return "idx";
	}
}
