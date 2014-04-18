#include "ChapterStream.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace eac3to
{

	const std::vector<Chapter*> &ChapterStream::getChapters() const
	{
		return privateChapters;
	}

	void ChapterStream::setChapters(const std::vector<Chapter*> &value)
	{
		privateChapters = value;
	}

	const object &ChapterStream::getExtractTypes() const
	{
		return new object[] {"TXT"};
	}

	ChapterStream::ChapterStream(const std::string &s) : Stream(s)
	{
		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		Stream::setType(Chapter);
	}

	Stream *ChapterStream::Parse(const std::string &s)
	{
		//2: Chapters, 27 chapters without names

		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		return new ChapterStream(s);
	}

	std::string ChapterStream::ToString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return Stream::ToString();
	}
}
