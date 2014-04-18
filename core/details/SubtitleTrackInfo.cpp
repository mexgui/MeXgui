#include "SubtitleTrackInfo.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Xml::Serialization;

namespace MeXgui
{

	SubtitleTrackInfo::SubtitleTrackInfo()
	{
	}

	SubtitleTrackInfo::SubtitleTrackInfo(int mmgTrackID, const QString &language, const QString &name)
	{
		TrackInfo::setTrackType(Subtitle);
		TrackInfo::setLanguage(language);
		TrackInfo::setTrackID(-1);
		TrackInfo::setMMGTrackID(mmgTrackID);
		TrackInfo::setName(name);
	}

	QString SubtitleTrackInfo::ToString()
	{
		QString strCodec = this->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture);
		if (IsMKVContainer())
		{
//ORIGINAL LINE: string[] arrCodec = new string[] { };
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			QString *arrCodec = new QString[] { };
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			arrCodec = this->getCodec().Split('/');
			if (arrCodec[0].substr(1, 1)->Equals("_"))
				arrCodec[0] = arrCodec[0].substr(2);
			strCodec = arrCodec[0].ToUpper(System::Globalization::CultureInfo::InvariantCulture);
		}

		QString fullString = "[" + getMMGTrackID() + "] - " + strCodec;
		if (!getLanguage().empty())
			fullString += " / " + getLanguage();
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		return fullString.Trim();
	}
}
