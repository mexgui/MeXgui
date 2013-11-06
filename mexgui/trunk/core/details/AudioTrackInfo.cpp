#include "AudioTrackInfo.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{

	AudioTrackInfo::AudioTrackInfo()
	{
	}

	AudioTrackInfo::AudioTrackInfo(const std::string &language, const std::string &codec, int trackID)
	{
		TrackInfo::setTrackType(Audio);
		TrackInfo::setLanguage(language);
		TrackInfo::setCodec(codec);
		TrackInfo::setTrackID(trackID);
		this->aacFlag = -1;
		this->nbChannels = "unknown";
		this->samplingRate = "unknown";
		this->channelPositions = "unknown";
	}

	const std::string &AudioTrackInfo::getTrackIDx() const
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return getContainerType() == "MPEG-TS" ? getTrackID().ToString("x3") : getTrackID().ToString("x");
	}

	void AudioTrackInfo::setTrackIDx(const std::string &value)
	{
		setTrackID(int::Parse(value, System::Globalization::NumberStyles::HexNumber));
	}

	const std::string &AudioTrackInfo::getDgIndexID() const
	{
		return getContainerType() == "MPEG-TS" ? StringConverterHelper::toString(getTrackIndex()) : getTrackIDx();
	}

	const std::string &AudioTrackInfo::getNbChannels() const
	{
		return nbChannels;
	}

	void AudioTrackInfo::setNbChannels(const std::string &value)
	{
		nbChannels = value;
	}

	const std::string &AudioTrackInfo::getChannelPositions() const
	{
		return channelPositions;
	}

	void AudioTrackInfo::setChannelPositions(const std::string &value)
	{
		channelPositions = value;
	}

	const std::string &AudioTrackInfo::getSamplingRate() const
	{
		return samplingRate;
	}

	void AudioTrackInfo::setSamplingRate(const std::string &value)
	{
		samplingRate = value;
	}

	const int &AudioTrackInfo::getAACFlag() const
	{
		return aacFlag;
	}

	void AudioTrackInfo::setAACFlag(const int &value)
	{
		aacFlag = value;
	}

	std::string AudioTrackInfo::ToString()
	{
		std::string fullString = "[" + getTrackIDx() + "] - " + this->getCodec();
		if (!nbChannels.empty())
			fullString += " - " + this->nbChannels;
		if (!samplingRate.empty())
			fullString += " / " + samplingRate;
		if (!getLanguage().empty())
			fullString += " / " + getLanguage();
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		return fullString.Trim();
	}
}
