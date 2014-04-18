#include "FlacSettings.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

const QString FlacSettings::ID = "Flac";

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
