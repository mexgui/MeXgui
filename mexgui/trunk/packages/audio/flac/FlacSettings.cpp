#include "FlacSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

const std::string FlacSettings::ID = "Flac";

	FlacSettings::FlacSettings() : AudioCodecSettings(ID, AudioCodec::FLAC, AudioEncoderType::FLAC, 0)
	{
		setCompressionLevel(5);
		AudioCodecSettings::setAutoGain(false);
	}

	const int &FlacSettings::getCompressionLevel() const
	{
		return level;
	}

	void FlacSettings::setCompressionLevel(const int &value)
	{
		level = value;
	}

	const BitrateManagementMode &FlacSettings::getBitrateMode() const
	{
		return CBR;
	}

	void FlacSettings::setBitrateMode(const BitrateManagementMode &value)
	{
		// Do Nothing
	}
}
