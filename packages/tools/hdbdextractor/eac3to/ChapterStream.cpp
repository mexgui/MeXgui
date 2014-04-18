#include "ChapterStream.h"




//using namespace System::Collections::Generic;

namespace eac3to
{

	const QVector<Chapter*> &ChapterStream::getChapters() const
	{
		return privateChapters;
	}

	void ChapterStream::setChapters(const QVector<Chapter*> &value)
	{
		privateChapters = value;
	}

	const object &ChapterStream::getExtractTypes() const
	{
		return new object[] {"TXT"};
	}

	ChapterStream::ChapterStream(const QString &s) : Stream(s)
	{
		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		Stream::setType(Chapter);
	}

	Stream *ChapterStream::Parse(const QString &s)
	{
		//2: Chapters, 27 chapters without names

		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		return new ChapterStream(s);
	}

	QString ChapterStream::ToString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return Stream::ToString();
	}
}
