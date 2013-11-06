#include "OneClickStream.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::util;

namespace MeGUI
{

	OneClickStream::OneClickStream(const std::string &path, TrackType trackType, const std::string &codec, const std::string &container, int ID, const std::string &language, const std::string &name, int delay, bool bDefaultTrack, bool bForceTrack, AudioCodecSettings *oSettings, AudioEncodingMode oEncodingMode)
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

	const std::string &OneClickStream::getLanguage() const
	{
		return _trackInfo->getLanguage();
	}

	void OneClickStream::setLanguage(const std::string &value)
	{
		_trackInfo->setLanguage(value);
	}

	const std::string &OneClickStream::getName() const
	{
		return _trackInfo->getName();
	}

	void OneClickStream::setName(const std::string &value)
	{
		_trackInfo->setName(value);
	}

	const std::string &OneClickStream::getDemuxFilePath() const
	{
		if (!_demuxFilePath.empty())
			return _demuxFilePath;
		if (_trackInfo != 0 && _trackInfo->getDemuxFileName() != "")
			return _trackInfo->getDemuxFileName();
		else
			return _inputFilePath;
	}

	void OneClickStream::setDemuxFilePath(const std::string &value)
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

	const MeGUI::TrackInfo &OneClickStream::getTrackInfo() const
	{
		return _trackInfo;
	}

	void OneClickStream::setTrackInfo(const MeGUI::TrackInfo &value)
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

	std::string OneClickStream::ToString()
	{
		std::string strCodec = _trackInfo->getCodec();
		if (_trackInfo->IsMKVContainer())
		{
//ORIGINAL LINE: string[] arrCodec = new string[] { };
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			std::string *arrCodec = new std::string[] { };
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			arrCodec = _trackInfo->getCodec().Split('/');
			if (arrCodec[0].substr(1, 1)->Equals("_"))
				arrCodec[0] = arrCodec[0].substr(2);
			strCodec = arrCodec[0];
		}

		std::string fullString = "[";
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
