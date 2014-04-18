#include "DGAIndexJob.h"




//using namespace System::Collections::Generic;

namespace MeXgui
{

	DGAIndexJob::DGAIndexJob() : IndexJob()
	{
	}

	DGAIndexJob::DGAIndexJob(const QString &input, const QString &output, int demuxType, QVector<AudioTrackInfo*> &audioTracks, bool loadSources, bool demuxVideo)
	{
		Input = input;
		Output = output;
		setDemuxMode(demuxType);
		setAudioTracks(audioTracks);
		setLoadSources(loadSources);
		setDemuxVideo(demuxVideo);
		FilesToDelete.push_back(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(input), System::IO::Path::GetFileNameWithoutExtension(input) + ".log"));
	}

	const QString &DGAIndexJob::getCodecString() const
	{
		return "";
	}

	const QString &DGAIndexJob::getEncodingMode() const
	{
		return "idx";
	}
}
