#include "MP2Settings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

const std::string MP2Settings::ID = "FFmpeg MP2";
const object MP2Settings::SupportedBitrates[8] = {64, 128, 160, 192, 224, 256, 288, 320};

	MP2Settings::MP2Settings() : AudioCodecSettings(ID, AudioCodec::MP2, AudioEncoderType::FFMP2, 128)
	{
		AudioCodecSettings::setDownmixMode(StereoDownmix);
	}

	const BitrateManagementMode &MP2Settings::getBitrateMode() const
	{
		return CBR;
	}

	void MP2Settings::setBitrateMode(const BitrateManagementMode &value)
	{
		// Do Nothing
	}
}
