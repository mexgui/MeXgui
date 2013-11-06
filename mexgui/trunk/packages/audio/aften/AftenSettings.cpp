#include "AftenSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

object AftenSettings::SupportedBitrates[14] = {64, 128, 160, 192, 224, 256, 288, 320, 352, 384, 448, 512, 576, 640};
const std::string AftenSettings::ID = "Aften AC-3";

	AftenSettings::AftenSettings() : AudioCodecSettings(ID, AudioCodec::AC3, AudioEncoderType::AFTEN, 384)
	{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		AudioCodecSettings::supportedBitrates = Array::ConvertAll<object*, int>(SupportedBitrates, delegate(object o)
		{
			return static_cast<int>(o);
		}
	   );
	}

	const BitrateManagementMode &AftenSettings::getBitrateMode() const
	{
		return CBR;
	}

	void AftenSettings::setBitrateMode(const BitrateManagementMode &value)
	{
		// Do Nothing
	}
}
