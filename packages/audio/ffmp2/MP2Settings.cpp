#include "MP2Settings.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

const QString MP2Settings::ID = "FFmpeg MP2";
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
