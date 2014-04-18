#include "AudioJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::details;
using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{

	AudioJob::AudioJob()
	{
	}

	AudioJob::AudioJob(const std::string &input, const std::string &output, const std::string &cutfile, AudioCodecSettings *settings, int delay, const std::string &strLanguage, const std::string &strName) : Job(input, output)
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

	MeGUI::core::details::MuxStream *AudioJob::ToMuxStream()
	{
		return new MuxStream(Output, Language, Name, 0, false, false, 0);
		// no delay correction is required since the audio job will fix the delay
	}

	const std::string &AudioJob::getCodecString() const
	{
		return Settings->getSettingsID();
	}

	const std::string &AudioJob::getEncodingMode() const
	{
		return "audio";
	}

	const AudioType &AudioJob::getType() const
	{
		return VideoUtil::guessAudioType(Output);
	}
}
