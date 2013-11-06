#include "JoinStream.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace eac3to
{

	const object &JoinStream::getExtractTypes() const
	{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (base.Name.ToString())
//ORIGINAL LINE: case "Joined EVO":
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (Stream::getName().ToString() == "Joined EVO")
		{
				return new object[] {"EVO"};
		}
//ORIGINAL LINE: case "Joined VOB":
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		else if (Stream::getName().ToString() == "Joined VOB")
		{
				return new object[] {"VOB"};
		}
		else
		{
				return new object[] {""};
		}
	}

	JoinStream::JoinStream(const std::string &s) : Stream(s)
	{
		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		Stream::setType(Join);
	}

	Stream *JoinStream::Parse(const std::string &s)
	{
		//1: Joined EVO file

		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		return new JoinStream(s);
	}

	std::string JoinStream::ToString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return Stream::ToString();
	}
}
