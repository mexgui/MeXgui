#include "hfyuSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

std::string hfyuSettings::ID = "Huffyuv";
const std::string hfyuSettings::m_fourCCs[1] = {"FFVH"};

	hfyuSettings::hfyuSettings() : VideoCodecSettings(ID, VideoEncoderType::HFYU)
	{
		VideoCodecSettings::setBitrateQuantizer(0);
		VideoCodecSettings::setEncodingMode(static_cast<int>(CQ));
		VideoCodecSettings::setFourCC(0);
		setFourCCs(m_fourCCs);
	}

	const bool &hfyuSettings::getUsesSAR() const
	{
		return false;
	}
}
