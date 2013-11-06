#include "SubtitleStream.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace eac3to
{

	const std::string &SubtitleStream::getLanguage() const
	{
		return privateLanguage;
	}

	void SubtitleStream::setLanguage(const std::string &value)
	{
		privateLanguage = value;
	}

	const bool &SubtitleStream::getIsSDH() const
	{
		return privateIsSDH;
	}

	void SubtitleStream::setIsSDH(const bool &value)
	{
		privateIsSDH = value;
	}

	const object &SubtitleStream::getExtractTypes() const
	{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (base.Description.Substring(11, 3))
//ORIGINAL LINE: case "ASS":
		if (Stream::getDescription().substr(11, 3) == "ASS")
		{
				return new object[] {"ASS"};
		}
//ORIGINAL LINE: case "SSA":
		else if (Stream::getDescription().substr(11, 3) == "SSA")
		{
				return new object[] {"SSA"};
		}
//ORIGINAL LINE: case "SRT":
		else if (Stream::getDescription().substr(11, 3) == "SRT")
		{
				return new object[] {"SRT"};
		}
//ORIGINAL LINE: case "Vob":
		else if (Stream::getDescription().substr(11, 3) == "Vob")
		{
				return new object[] {"IDX"};
		}
		else
		{
				return new object[] {"SUP"};
		}

	}

	SubtitleStream::SubtitleStream(const std::string &s) : Stream(s)
	{
		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		Stream::setType(Subtitle);
	}

	Stream *SubtitleStream::Parse(const std::string &s)
	{
		//5: Subtitle, English, "SDH"
		//6: Subtitle, French
		//7: Subtitle, Spanish

		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		SubtitleStream *subtitleStream = new SubtitleStream(s);

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		subtitleStream->setLanguage((s.find(',') == s.rfind(',')) ? s.substr(s.find(',') + 1)->Trim() : s.substr(s.find(',') + 1, s.rfind(',') - s.find(',') - 1)->Trim());
		subtitleStream->setIsSDH(s.find("\"SDH\"") != string::npos ? true : false);

		return new SubtitleStream(s);
	}

	std::string SubtitleStream::ToString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return Stream::ToString();
	}
}
