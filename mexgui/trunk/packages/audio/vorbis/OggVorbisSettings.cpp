#include "OggVorbisSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

const std::string OggVorbisSettings::ID = "Vorbis";

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
