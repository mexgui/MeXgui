#include "AudioTrackInfo.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Xml::Serialization;

namespace MeXgui
{

	AudioTrackInfo::AudioTrackInfo()
	{
	}

	AudioTrackInfo::AudioTrackInfo(const QString &language, const QString &codec, int trackID)
	{
        AudioTrackInfo::setTrackType(Audio);
        AudioTrackInfo::setLanguage(language);
        AudioTrackInfo::setCodec(codec);
        AudioTrackInfo::setTrackID(trackID);
		this->aacFlag = -1;
		this->nbChannels = "unknown";
		this->samplingRate = "unknown";
		this->channelPositions = "unknown";
	}

	const QString &AudioTrackInfo::getTrackIDx() const
	{
        QString returnInt;
        if (getContainerType() == "MPEG-TS") {
            returnInt = QString::number(getTrackID(), 3);
        }
        else returnInt = QString::number(getTrackID());

        return returnInt; //orginal was x3 : x in C# int.toString formatting
	}

    void AudioTrackInfo::setTrackIDx(const QString &value)
	{
        setTrackID(value.toLongLong()); //we convert hex string to int32
	}

	const QString &AudioTrackInfo::getDgIndexID() const
	{
		return getContainerType() == "MPEG-TS" ? StringConverterHelper::toString(getTrackIndex()) : getTrackIDx();
	}

	const QString &AudioTrackInfo::getNbChannels() const
	{
		return nbChannels;
	}

	void AudioTrackInfo::setNbChannels(const QString &value)
	{
		nbChannels = value;
	}

	const QString &AudioTrackInfo::getChannelPositions() const
	{
		return channelPositions;
	}

	void AudioTrackInfo::setChannelPositions(const QString &value)
	{
		channelPositions = value;
	}

	const QString &AudioTrackInfo::getSamplingRate() const
	{
		return samplingRate;
	}

	void AudioTrackInfo::setSamplingRate(const QString &value)
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

	QString AudioTrackInfo::ToString()
	{
		QString fullString = "[" + getTrackIDx() + "] - " + this->getCodec();
        if (!nbChannels.isEmpty())
			fullString += " - " + this->nbChannels;
        if (!samplingRate.isEmpty())
			fullString += " / " + samplingRate;
        if (!getLanguage().isEmpty())
			fullString += " / " + getLanguage();
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
        return fullString.trimmed();
	}
}
