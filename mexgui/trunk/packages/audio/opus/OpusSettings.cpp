#include "OpusSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MeGUI
{

const std::string OpusSettings::ID = "OPUS";
const OpusMode OpusSettings::SupportedModes[3] = {VBR, CVBR, HCBR};

	OpusSettings::OpusSettings() : AudioCodecSettings(ID, AudioCodec::OPUS, AudioEncoderType::OPUS, 96, VBR)
	{
		setMode(VBR);
	}

	const OpusMode &OpusSettings::getMode() const
	{
		return mode;
	}

	void OpusSettings::setMode(const OpusMode &value)
	{
		mode = value;
	}
}
