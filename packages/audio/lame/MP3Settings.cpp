#include "MP3Settings.h"




namespace MeXgui
{

const QString MP3Settings::ID = "LAME MP3";

	MP3Settings::MP3Settings() : AudioCodecSettings(ID, AudioCodec::MP3, AudioEncoderType::LAME, 128)
	{
		quality = 4;
		AudioCodecSettings::setDownmixMode(StereoDownmix);
	}

	const int &MP3Settings::getQuality() const
	{
		if (quality > 9)
			return quality / 10;
		else
			return quality;
	}

	void MP3Settings::setQuality(const int &value)
	{
		quality = value;
	}

	const int &MP3Settings::getAbrBitrate() const
	{
		return abrBitrate;
	}

	void MP3Settings::setAbrBitrate(const int &value)
	{
		abrBitrate = value;
	}
}
