#include "VideoTrackInfo.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Xml::Serialization;

namespace MeXgui
{

	VideoTrackInfo::VideoTrackInfo()
	{
	}

	VideoTrackInfo::VideoTrackInfo(int trackID, int mmgTrackID, const QString &language, const QString &name, const QString &codecString, const QString &codec)
	{
		TrackInfo::setTrackType(Video);
		TrackInfo::setLanguage(language);
		TrackInfo::setName(name);
		TrackInfo::setTrackID(trackID);
		TrackInfo::setMMGTrackID(mmgTrackID);
		TrackInfo::setCodec(codecString);
		_codecMediaInfo = codec + "/" + codecString;
	}

	const QString &VideoTrackInfo::getCodecMediaInfo() const
	{
		return _codecMediaInfo;
	}

	QString VideoTrackInfo::ToString()
	{
		QString fullString = "[" + getTrackID() + "] - " + this->getCodec();
		if (!getLanguage().empty())
			fullString += " / " + getLanguage();
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		return fullString.Trim();
	}
}
