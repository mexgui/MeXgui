#include "D2VIndexJob.h"




//using namespace System::Collections::Generic;



namespace MeXgui
{

	D2VIndexJob::D2VIndexJob() : IndexJob()
	{
	}

	D2VIndexJob::D2VIndexJob(const QString &input, const QString &output, int demuxType, QVector<AudioTrackInfo*> &audioTracks, bool loadSources, bool demuxVideo) : IndexJob()
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

	const QString &D2VIndexJob::getCodecString() const
	{
		return "";
	}

	const QString &D2VIndexJob::getEncodingMode() const
	{
		return "idx";
	}
}
