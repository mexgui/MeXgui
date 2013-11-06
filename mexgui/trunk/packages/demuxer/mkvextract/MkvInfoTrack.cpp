#include "MkvInfoTrack.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{

	MkvInfoTrack::MkvInfoTrack()
	{
	}

	MkvInfoTrack::MkvInfoTrack(const std::string &strInputFile)
	{
		this->_strInputFile = strInputFile;
		this->_type = Unknown;
		this->_iTrackID = -1;
		this->_strCodecID = "";
		this->_strLanguage = "";
		this->_bDefault = true;
		this->_bForced = false;
		this->_strName = "";
		this->_strAudioChannels = "";
	}

	const TrackType &MkvInfoTrack::getType() const
	{
		return _type;
	}

	void MkvInfoTrack::setType(const TrackType &value)
	{
		_type = value;
		if (_type != Video && _type != Unknown && _strLanguage.empty())
			_strLanguage = "eng";
	}

	const int &MkvInfoTrack::getTrackID() const
	{
		return _iTrackID;
	}

	void MkvInfoTrack::setTrackID(const int &value)
	{
		_iTrackID = value;
	}

	const std::string &MkvInfoTrack::getCodecID() const
	{
		return _strCodecID;
	}

	void MkvInfoTrack::setCodecID(const std::string &value)
	{
		_strCodecID = value;
	}

	const std::string &MkvInfoTrack::getAudioChannels() const
	{
		return _strAudioChannels;
	}

	void MkvInfoTrack::setAudioChannels(const std::string &value)
	{
		_strAudioChannels = value;
	}

	const std::string &MkvInfoTrack::getLanguage() const
	{
		return _strLanguage;
	}

	void MkvInfoTrack::setLanguage(const std::string &value)
	{
		_strLanguage = value;
	}

	const std::string &MkvInfoTrack::getName() const
	{
		return _strName;
	}

	void MkvInfoTrack::setName(const std::string &value)
	{
		_strName = value;
	}

	const std::string &MkvInfoTrack::getInputFile() const
	{
		return _strInputFile;
	}

	void MkvInfoTrack::setInputFile(const std::string &value)
	{
		_strInputFile = value;
	}

	const bool &MkvInfoTrack::getDefaultTrack() const
	{
		return _bDefault;
	}

	void MkvInfoTrack::setDefaultTrack(const bool &value)
	{
		_bDefault = value;
	}

	const bool &MkvInfoTrack::getForcedTrack() const
	{
		return _bForced;
	}

	void MkvInfoTrack::setForcedTrack(const bool &value)
	{
		_bForced = value;
	}

	const std::string &MkvInfoTrack::getFileName() const
	{
		if (_type != Audio && _type != Subtitle)
			return 0;

		std::string strExtension = "";
//ORIGINAL LINE: string[] strCodec = _strCodecID.Split('/');
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		std::string *strCodec = _strCodecID.Split('/');
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (strCodec[0])
//ORIGINAL LINE: case "A_AC3":
		if (strCodec[0] == "A_AC3")
		{
				strExtension = "ac3";
		}
//ORIGINAL LINE: case "A_TRUEHD":
		else if (strCodec[0] == "A_TRUEHD")
		{
				strExtension = "thd";
		}
//ORIGINAL LINE: case "A_MPEG":
		else if (strCodec[0] == "A_MPEG")
		{
				if (sizeof(strCodec) / sizeof(strCodec[0]) > 0 && strCodec[1].Equals("L3"))
					strExtension = "mp3";
				else
					strExtension = "mp2";
		}
//ORIGINAL LINE: case "A_DTS":
		else if (strCodec[0] == "A_DTS")
		{
				strExtension = "dts";
		}
//ORIGINAL LINE: case "A_PCM":
		else if (strCodec[0] == "A_PCM")
		{
				strExtension = "wav";
		}
//ORIGINAL LINE: case "A_VORBIS":
		else if (strCodec[0] == "A_VORBIS")
		{
				strExtension = "ogg";
		}
//ORIGINAL LINE: case "A_FLAC":
		else if (strCodec[0] == "A_FLAC")
		{
				strExtension = "flac";
		}
//ORIGINAL LINE: case "A_REAL":
		else if (strCodec[0] == "A_REAL")
		{
				strExtension = "ra";
		}
//ORIGINAL LINE: case "A_AAC":
		else if (strCodec[0] == "A_AAC")
		{
				strExtension = "aac";
		}
//ORIGINAL LINE: case "A_MS/ACM":
		else if (strCodec[0] == "A_MS/ACM")
		{
				strExtension = "wav";
		}
//ORIGINAL LINE: case "S_TEXT":
		else if (strCodec[0] == "S_TEXT")
		{
				if (sizeof(strCodec) / sizeof(strCodec[0]) > 0 && strCodec[1].Equals("SSA"))
					strExtension = "ssa";
				else if (sizeof(strCodec) / sizeof(strCodec[0]) > 0 && strCodec[1].Equals("ASS"))
					strExtension = "ass";
				else if (sizeof(strCodec) / sizeof(strCodec[0]) > 0 && strCodec[1].Equals("USF"))
					strExtension = "usf";
				else
					strExtension = "srt";
		}
//ORIGINAL LINE: case "S_VOBSUB":
		else if (strCodec[0] == "S_VOBSUB")
		{
				strExtension = "idx";
		}
//ORIGINAL LINE: case "S_HDMV":
		else if (strCodec[0] == "S_HDMV")
		{
				strExtension = "sup";
		}
		else
		{
				strExtension = strCodec[0] + ".unknown";
		}

		if (strExtension.empty())
			return 0;

		return Path::GetFileNameWithoutExtension(_strInputFile) + " - [" + _iTrackID + "] " + LanguageSelectionContainer::lookupISOCode(_strLanguage) + "." + strExtension;
	}

	const MeGUI::AudioTrackInfo &MkvInfoTrack::getAudioTrackInfo() const
	{
		if (_type != Audio)
			return 0;

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		std::string strCodecID = _strCodecID.Split('/')[0]->Replace("AC3", "AC-3");
		if (strCodecID.length() > 2 && strCodecID.substr(1, 1)->Equals("_"))
			strCodecID = strCodecID.substr(2);

		MeGUI::AudioTrackInfo *oAudioTrack = new AudioTrackInfo(LanguageSelectionContainer::lookupISOCode(_strLanguage), _strAudioChannels, strCodecID, _iTrackID);
		oAudioTrack->setContainerType("MATROSKA");
		oAudioTrack->setName(_strName);

		return oAudioTrack;
	}

	const OneClickStream &MkvInfoTrack::getSubtitleTrackInfo() const
	{
		if (_type != Subtitle)
			return 0;

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		std::string strCodecID = _strCodecID.Split('/')[0]->Replace("AC3", "AC-3");
		if (strCodecID.length() > 2 && strCodecID.substr(1,1)->Equals("_"))
			strCodecID = strCodecID.substr(2);

		OneClickStream *oSubtitleTrack = new OneClickStream(_strInputFile, Subtitle, strCodecID, "MATROSKA", StringConverterHelper::toString(_iTrackID), LanguageSelectionContainer::lookupISOCode(_strLanguage), _strName, 0, _bDefault, _bForced, 0, IfCodecDoesNotMatch, this);

		return oSubtitleTrack;
	}
}
