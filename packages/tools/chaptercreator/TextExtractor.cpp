#include "TextExtractor.h"




//using namespace System::Collections::Generic;

//using namespace System::Linq;

//using namespace System::Text;



namespace MeXgui
{

	const bool &TextExtractor::getSupportsMultipleStreams() const
	{
		return false;
	}

	const QString &TextExtractor::getExtensions() const
	{
		return new QString[] {"txt"};
	}

	QVector<ChapterInfo*> TextExtractor::GetStreams(const QString &location)
	{
		QVector<ChapterInfo*> pgcs = QVector<ChapterInfo*>();

		QVector<Chapter> list = QVector<Chapter>();

		int num = 0;
		TimeSpan *ts = new TimeSpan(0);
		QString time = "";
		QString name = "";
		bool onTime = true;
//ORIGINAL LINE: string[] lines = File.ReadAllLines(location);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		QString *lines = File::ReadAllLines(location);
		for (QString::const_iterator line = lines->begin(); line != lines->end(); ++line)
		{
			if (onTime)
			{
				num++;
				//read time
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				time = (*line).Replace("CHAPTER" + num.ToString("00") + "=", "");
				ts = TimeSpan::Parse(time);
			}
			else
			{
				//read name
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				name = (*line).Replace("CHAPTER" + num.ToString("00") + "NAME=", "");
				//add it to list
				list.push_back(Chapter(new object[] {Name = name, Time = ts}));
			}
			onTime = !onTime;
		}

		pgcs.push_back(new ChapterInfo(new object[] {Chapters = list, SourceName = location, SourceHash = ChapterExtractor::ComputeMD5Sum(location), FramesPerSecond = 25.0, Title = Path::GetFileNameWithoutExtension(location)}));

		OnStreamDetected(pgcs[0]);
		OnChaptersLoaded(pgcs[0]);
		OnExtractionComplete();
		return pgcs;
	}
}
