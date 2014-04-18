#include "hfyuSettings.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

QString hfyuSettings::ID = "Huffyuv";
const QString hfyuSettings::m_fourCCs[1] = {"FFVH"};

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
