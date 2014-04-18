#include "NeroAACSettings.h"




namespace MeXgui
{

const QString NeroAACSettings::ID = "Nero AAC";
const AacProfile NeroAACSettings::SupportedProfiles[4] = {Auto, PS, HE, LC};

	NeroAACSettings::NeroAACSettings() : AudioCodecSettings(ID, AudioCodec::AAC, AudioEncoderType::NAAC, 0, VBR)
	{
		setQuality(0.5);
		setProfile(Auto);
		setCreateHintTrack(false);
	}

	const AacProfile &NeroAACSettings::getProfile() const
	{
		return profile;
	}

	void NeroAACSettings::setProfile(const AacProfile &value)
	{
		profile = value;
	}

	const Decimal &NeroAACSettings::getQuality() const
	{
		return quality;
	}

	void NeroAACSettings::setQuality(const Decimal &value)
	{
		quality = value;
	}

	const bool &NeroAACSettings::getCreateHintTrack() const
	{
		return createHintTrack;
	}

	void NeroAACSettings::setCreateHintTrack(const bool &value)
	{
		createHintTrack = value;
	}
}
