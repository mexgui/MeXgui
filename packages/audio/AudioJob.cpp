#include "AudioJob.h"




//using namespace System::Xml::Serialization;
using namespace MeXgui::core::details;
using namespace MeXgui::core::plugins::interfaces;

namespace MeXgui
{

	AudioJob::AudioJob()
	{
	}

	AudioJob::AudioJob(const QString &input, const QString &output, const QString &cutfile, AudioCodecSettings *settings, int delay, const QString &strLanguage, const QString &strName) : Job(input, output)
	{
		CutFile = cutfile;
		Settings = settings;
		Delay = delay;
		Language = strLanguage;
		Name = strName;
	}

	MuxableType *AudioJob::ToMuxableType()
	{
		return new MuxableType(getType(), Settings->getCodec());
	}

	MeXgui::core::details::MuxStream *AudioJob::ToMuxStream()
	{
		return new MuxStream(Output, Language, Name, 0, false, false, 0);
		// no delay correction is required since the audio job will fix the delay
	}

	const QString &AudioJob::getCodecString() const
	{
		return Settings->getSettingsID();
	}

	const QString &AudioJob::getEncodingMode() const
	{
		return "audio";
	}

	const AudioType &AudioJob::getType() const
	{
		return VideoUtil::guessAudioType(Output);
	}
}
