#include "TrackInfo.h"

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

	TrackInfo::TrackInfo()
	{

	}

	TrackInfo::TrackInfo(const std::string &language, const std::string &name)
	{
		this->_language = language;
		this->_name = name;
		this->_trackType = Unknown;
		this->_trackID = 0;
		this->_mmgTrackID = 0;
		this->_delay = 0;
		this->_trackIndex = 0;
		this->_codec = _containerType = "";
		this->_bMKVTrack = false;
	}

	const MeGUI::TrackType &TrackInfo::getTrackType() const
	{
		return _trackType;
	}

	void TrackInfo::setTrackType(const MeGUI::TrackType &value)
	{
		_trackType = value;
	}

	const std::string &TrackInfo::getLanguage() const
	{
		return _language;
	}

	void TrackInfo::setLanguage(const std::string &value)
	{
		_language = value;
	}

	const std::string &TrackInfo::getSourceFileName() const
	{
		return _sourceFileName;
	}

	void TrackInfo::setSourceFileName(const std::string &value)
	{
		_sourceFileName = value;
	}

	const std::string &TrackInfo::getName() const
	{
		return _name;
	}

	void TrackInfo::setName(const std::string &value)
	{
		_name = value;
	}

	const int &TrackInfo::getTrackID() const
	{
		return _trackID;
	}

	void TrackInfo::setTrackID(const int &value)
	{
		_trackID = value;
	}

	const int &TrackInfo::getMMGTrackID() const
	{
		return _mmgTrackID;
	}

	void TrackInfo::setMMGTrackID(const int &value)
	{
		_mmgTrackID = value;
	}

	const std::string &TrackInfo::getContainerType() const
	{
		return _containerType;
	}

	void TrackInfo::setContainerType(const std::string &value)
	{
		_containerType = value;
	}

	const int &TrackInfo::getTrackIndex() const
	{
		return _trackIndex;
	}

	void TrackInfo::setTrackIndex(const int &value)
	{
		_trackIndex = value;
	}

	const std::string &TrackInfo::getCodec() const
	{
		return _codec;
	}

	void TrackInfo::setCodec(const std::string &value)
	{
		_codec = value;
	}

	const int &TrackInfo::getDelay() const
	{
		return _delay;
	}

	void TrackInfo::setDelay(const int &value)
	{
		_delay = value;
	}

	const bool &TrackInfo::getDefaultTrack() const
	{
		return _bDefault;
	}

	void TrackInfo::setDefaultTrack(const bool &value)
	{
		_bDefault = value;
	}

	const bool &TrackInfo::getForcedTrack() const
	{
		return _bForced;
	}

	void TrackInfo::setForcedTrack(const bool &value)
	{
		_bForced = value;
	}

	bool TrackInfo::IsMKVContainer()
	{
		if (_containerType.empty())
			return false;
		else
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			return _containerType.Trim()->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MATROSKA");
	}

	const bool &TrackInfo::getExtractMKVTrack() const
	{
		return _bMKVTrack;
	}

	void TrackInfo::setExtractMKVTrack(const bool &value)
	{
		_bMKVTrack = value;
	}

	const std::string &TrackInfo::getDemuxFileName() const
	{
		if (_sourceFileName.empty())
			return 0;

		std::string strExtension = "";
		std::string strCodec = "";
		std::string strFileName = "";

		if (!_codec.empty())
			strCodec = _codec.ToUpper(System::Globalization::CultureInfo::InvariantCulture);

		if (IsMKVContainer())
		{
//ORIGINAL LINE: string[] arrCodec = new string[] { };
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			std::string *arrCodec = new std::string[] { };
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			arrCodec = _codec.Split('/');
			if (arrCodec[0].substr(1, 1)->Equals("_"))
				arrCodec[0] = arrCodec[0].substr(2);
			strCodec = arrCodec[0].ToUpper(System::Globalization::CultureInfo::InvariantCulture);
		}

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (strCodec.StartsWith("DTS", StringComparison::InvariantCultureIgnoreCase))
			strCodec = "DTS";

		if (strCodec.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Contains("TRUEHD"))
			strCodec = "TRUEHD";

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (strCodec)
//ORIGINAL LINE: case "AC-3":
		if (strCodec == "AC-3")
		{
				strExtension = "ac3";
		}
//ORIGINAL LINE: case "TRUEHD":
		else if (strCodec == "TRUEHD")
		{
				strExtension = "thd";
		}
//ORIGINAL LINE: case "DTS":
		else if (strCodec == "DTS")
		{
				strExtension = "dts";
		}
//ORIGINAL LINE: case "MP3":
		else if (strCodec == "MP3")
		{
				strExtension = "mp3";
		}
//ORIGINAL LINE: case "MP2":
		else if (strCodec == "MP2")
		{
				strExtension = "mp2";
		}
//ORIGINAL LINE: case "PCM":
		else if (strCodec == "PCM")
		{
				strExtension = "w64";
		}
//ORIGINAL LINE: case "MS/ACM":
		else if (strCodec == "MS/ACM")
		{
				strExtension = "w64";
		}
//ORIGINAL LINE: case "VORBIS":
		else if (strCodec == "VORBIS")
		{
				strExtension = "ogg";
		}
//ORIGINAL LINE: case "FLAC":
		else if (strCodec == "FLAC")
		{
				strExtension = "flac";
		}
//ORIGINAL LINE: case "REAL":
		else if (strCodec == "REAL")
		{
				strExtension = "ra";
		}
//ORIGINAL LINE: case "AAC":
		else if (strCodec == "AAC")
		{
				strExtension = "aac";
		}
//ORIGINAL LINE: case "VOBSUB":
		else if (strCodec == "VOBSUB")
		{
				strExtension = "idx";
		}
//ORIGINAL LINE: case "ASS":
		else if (strCodec == "ASS")
		{
				strExtension = "ass";
		}
//ORIGINAL LINE: case "UTF-8":
		else if (strCodec == "UTF-8")
		{
				strExtension = "srt";
		}
//ORIGINAL LINE: case "SSA":
		else if (strCodec == "SSA")
		{
				strExtension = "ssa";
		}
//ORIGINAL LINE: case "USF":
		else if (strCodec == "USF")
		{
				strExtension = "usf";
		}
//ORIGINAL LINE: case "HDMV":
		else if (strCodec == "HDMV")
		{
				strExtension = "sup";
		}
//ORIGINAL LINE: case "PGS":
		else if (strCodec == "PGS")
		{
				strExtension = "sup";
		}
//ORIGINAL LINE: case "AVS":
		else if (strCodec == "AVS")
		{
				strExtension = "avs";
		}
		else
		{
				strExtension = strCodec + ".unknown";
		}

		if (!strExtension.Equals("avs", StringComparison::InvariantCultureIgnoreCase))
		{
			strFileName = System::IO::Path::GetFileNameWithoutExtension(_sourceFileName) + " - [" + _trackIndex + "]";
			if (!_language.empty())
				strFileName += " " + _language;
			if (_delay != 0)
				strFileName += " " + _delay + "ms";
			strFileName += "." + strExtension;
		}
		else
			strFileName = System::IO::Path::GetFileName(_sourceFileName);
		return strFileName;
	}
}
