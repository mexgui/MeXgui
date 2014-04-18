#include "OneClickStream.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::util;

namespace MeXgui
{

	OneClickStream::OneClickStream(const QString &path, TrackType trackType, const QString &codec, const QString &container, int ID, const QString &language, const QString &name, int delay, bool bDefaultTrack, bool bForceTrack, AudioCodecSettings *oSettings, AudioEncodingMode oEncodingMode)
	{
		_trackInfo = new TrackInfo(language, name);
		_trackInfo->setTrackType(trackType);
		_trackInfo->setDelay(delay);
		_trackInfo->setDefaultTrack(bDefaultTrack);
		_trackInfo->setForcedTrack(bForceTrack);
		_trackInfo->setContainerType(container);
		_trackInfo->setCodec(codec);
		_trackInfo->setTrackID(ID);

		this->_inputFilePath = path;

		this->_encoderSettings = oSettings;
		if (static_cast<int>(oEncodingMode) == -1)
			this->_encodingMode = IfCodecDoesNotMatch;
		else
			this->_encodingMode = oEncodingMode;
	}

	OneClickStream::OneClickStream(AudioTrackInfo *oInfo)
	{
		this->_trackInfo = oInfo;
		this->_encodingMode = IfCodecDoesNotMatch;
	}

	OneClickStream::OneClickStream(SubtitleTrackInfo *oInfo)
	{
		this->_trackInfo = oInfo;
		this->_encodingMode = IfCodecDoesNotMatch;
	}

	OneClickStream::OneClickStream()
	{
	}

	const TrackType &OneClickStream::getType() const
	{
		return _trackInfo->getTrackType();
	}

	const QString &OneClickStream::getLanguage() const
	{
		return _trackInfo->getLanguage();
	}

	void OneClickStream::setLanguage(const QString &value)
	{
		_trackInfo->setLanguage(value);
	}

	const QString &OneClickStream::getName() const
	{
		return _trackInfo->getName();
	}

	void OneClickStream::setName(const QString &value)
	{
		_trackInfo->setName(value);
	}

	const QString &OneClickStream::getDemuxFilePath() const
	{
		if (!_demuxFilePath.empty())
			return _demuxFilePath;
		if (_trackInfo != 0 && _trackInfo->getDemuxFileName() != "")
			return _trackInfo->getDemuxFileName();
		else
			return _inputFilePath;
	}

	void OneClickStream::setDemuxFilePath(const QString &value)
	{
		_inputFilePath = _demuxFilePath = value;
	}

	const int &OneClickStream::getDelay() const
	{
		return _trackInfo->getDelay();
	}

	void OneClickStream::setDelay(const int &value)
	{
		_trackInfo->setDelay(value);
	}

	const bool &OneClickStream::getForcedStream() const
	{
		return _trackInfo->getForcedTrack();
	}

	void OneClickStream::setForcedStream(const bool &value)
	{
		_trackInfo->setForcedTrack(value);
	}

	const bool &OneClickStream::getDefaultStream() const
	{
		return _trackInfo->getDefaultTrack();
	}

	void OneClickStream::setDefaultStream(const bool &value)
	{
		_trackInfo->setDefaultTrack(value);
	}

	const MeXgui::TrackInfo &OneClickStream::getTrackInfo() const
	{
		return _trackInfo;
	}

	void OneClickStream::setTrackInfo(const MeXgui::TrackInfo &value)
	{
		_trackInfo = value;
	}

	const AudioCodecSettings &OneClickStream::getEncoderSettings() const
	{
		return _encoderSettings;
	}

	void OneClickStream::setEncoderSettings(const AudioCodecSettings &value)
	{
		_encoderSettings = value;
	}

	const AudioEncodingMode &OneClickStream::getEncodingMode() const
	{
		return _encodingMode;
	}

	void OneClickStream::setEncodingMode(const AudioEncodingMode &value)
	{
		if (static_cast<int>(value) == -1)
			_encodingMode = IfCodecDoesNotMatch;
		else
			_encodingMode = value;
	}

	QString OneClickStream::ToString()
	{
		QString strCodec = _trackInfo->getCodec();
		if (_trackInfo->IsMKVContainer())
		{
//ORIGINAL LINE: string[] arrCodec = new string[] { };
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			QString *arrCodec = new QString[] { };
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			arrCodec = _trackInfo->getCodec().Split('/');
			if (arrCodec[0].substr(1, 1)->Equals("_"))
				arrCodec[0] = arrCodec[0].substr(2);
			strCodec = arrCodec[0];
		}

		QString fullString = "[";
		if (_trackInfo->getTrackType() == Audio)
			fullString += (static_cast<AudioTrackInfo*>(_trackInfo))->getTrackIDx() + "] - " + strCodec;
		else
			fullString += _trackInfo->getMMGTrackID() + "] - " + strCodec;
		if (dynamic_cast<AudioTrackInfo*>(_trackInfo) != 0 && !((static_cast<AudioTrackInfo*>(_trackInfo))->getNbChannels()).empty())
			fullString += " - " + (static_cast<AudioTrackInfo*>(_trackInfo))->getNbChannels();
		if (dynamic_cast<AudioTrackInfo*>(_trackInfo) != 0 && !((static_cast<AudioTrackInfo*>(_trackInfo))->getSamplingRate()).empty())
			fullString += " - " + (static_cast<AudioTrackInfo*>(_trackInfo))->getSamplingRate();
		if (!_trackInfo->getLanguage().empty())
			fullString += " / " + _trackInfo->getLanguage();
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		return fullString.Trim();
	}
}
