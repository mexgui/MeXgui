#include "OggVorbisSettings.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

const QString OggVorbisSettings::ID = "Vorbis";

	OggVorbisSettings::OggVorbisSettings() : AudioCodecSettings(ID, AudioCodec::VORBIS, AudioEncoderType::VORBIS, 0)
	{
		this->Quality = 1.0;
	}

	const BitrateManagementMode &OggVorbisSettings::getBitrateMode() const
	{
		return VBR;
	}

	void OggVorbisSettings::setBitrateMode(const BitrateManagementMode &value)
	{
		// Do Nothing
	}
}
