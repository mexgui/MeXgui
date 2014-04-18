#include "JoinStream.h"




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

	JoinStream::JoinStream(const QString &s) : Stream(s)
	{
		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		Stream::setType(Join);
	}

	Stream *JoinStream::Parse(const QString &s)
	{
		//1: Joined EVO file

		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		return new JoinStream(s);
	}

	QString JoinStream::ToString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return Stream::ToString();
	}
}
