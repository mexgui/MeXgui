#include "QaacSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MeGUI
{

const std::string QaacSettings::ID = "QAAC";
const QaacProfile QaacSettings::SupportedProfiles[3] = {LC, HE, ALAC};
const QaacMode QaacSettings::SupportedModes[4] = {TVBR, CVBR, ABR, CBR};

	QaacSettings::QaacSettings() : AudioCodecSettings(ID, AudioCodec::AAC, AudioEncoderType::QAAC, 0, VBR)
	{
		setQuality(90);
		setMode(TVBR);
		setProfile(LC);
	}

	const QaacProfile &QaacSettings::getProfile() const
	{
		return profile;
	}

	void QaacSettings::setProfile(const QaacProfile &value)
	{
		profile = value;
	}

	const QaacMode &QaacSettings::getMode() const
	{
		return mode;
	}

	void QaacSettings::setMode(const QaacMode &value)
	{
		mode = value;
	}

	const short &QaacSettings::getQuality() const
	{
		return quality;
	}

	void QaacSettings::setQuality(const short &value)
	{
		quality = value;
	}

	const bool &QaacSettings::getNoDelay() const
	{
		return noDelay;
	}

	void QaacSettings::setNoDelay(const bool &value)
	{
		noDelay = value;
	}
}
