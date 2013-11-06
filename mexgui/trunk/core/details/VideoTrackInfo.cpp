#include "VideoTrackInfo.h"

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

	VideoTrackInfo::VideoTrackInfo()
	{
	}

	VideoTrackInfo::VideoTrackInfo(int trackID, int mmgTrackID, const std::string &language, const std::string &name, const std::string &codecString, const std::string &codec)
	{
		TrackInfo::setTrackType(Video);
		TrackInfo::setLanguage(language);
		TrackInfo::setName(name);
		TrackInfo::setTrackID(trackID);
		TrackInfo::setMMGTrackID(mmgTrackID);
		TrackInfo::setCodec(codecString);
		_codecMediaInfo = codec + "/" + codecString;
	}

	const std::string &VideoTrackInfo::getCodecMediaInfo() const
	{
		return _codecMediaInfo;
	}

	std::string VideoTrackInfo::ToString()
	{
		std::string fullString = "[" + getTrackID() + "] - " + this->getCodec();
		if (!getLanguage().empty())
			fullString += " / " + getLanguage();
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		return fullString.Trim();
	}
}
