#include "SubtitleTrackInfo.h"

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

	SubtitleTrackInfo::SubtitleTrackInfo()
	{
	}

	SubtitleTrackInfo::SubtitleTrackInfo(int mmgTrackID, const std::string &language, const std::string &name)
	{
		TrackInfo::setTrackType(Subtitle);
		TrackInfo::setLanguage(language);
		TrackInfo::setTrackID(-1);
		TrackInfo::setMMGTrackID(mmgTrackID);
		TrackInfo::setName(name);
	}

	std::string SubtitleTrackInfo::ToString()
	{
		std::string strCodec = this->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture);
		if (IsMKVContainer())
		{
//ORIGINAL LINE: string[] arrCodec = new string[] { };
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			std::string *arrCodec = new std::string[] { };
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			arrCodec = this->getCodec().Split('/');
			if (arrCodec[0].substr(1, 1)->Equals("_"))
				arrCodec[0] = arrCodec[0].substr(2);
			strCodec = arrCodec[0].ToUpper(System::Globalization::CultureInfo::InvariantCulture);
		}

		std::string fullString = "[" + getMMGTrackID() + "] - " + strCodec;
		if (!getLanguage().empty())
			fullString += " / " + getLanguage();
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		return fullString.Trim();
	}
}
