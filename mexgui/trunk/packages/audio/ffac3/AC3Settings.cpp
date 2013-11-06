#include "AC3Settings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

std::string AC3Settings::ID = "FFmpeg AC-3";
const object AC3Settings::SupportedBitrates[14] = {64, 128, 160, 192, 224, 256, 288, 320, 352, 384, 448, 512, 576, 640};

	AC3Settings::AC3Settings() : AudioCodecSettings(ID, AudioCodec::AC3, AudioEncoderType::FFAC3, 384)
	{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		AudioCodecSettings::supportedBitrates = Array::ConvertAll<object*, int>(SupportedBitrates, delegate(object o)
		{
			return static_cast<int>(o);
		}
	   );
	}

	const BitrateManagementMode &AC3Settings::getBitrateMode() const
	{
		return CBR;
	}

	void AC3Settings::setBitrateMode(const BitrateManagementMode &value)
	{
		// Do Nothing
	}
}
