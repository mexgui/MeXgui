#include "TextExtractor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace MeGUI
{

	const bool &TextExtractor::getSupportsMultipleStreams() const
	{
		return false;
	}

	const std::string &TextExtractor::getExtensions() const
	{
		return new std::string[] {"txt"};
	}

	std::vector<ChapterInfo*> TextExtractor::GetStreams(const std::string &location)
	{
		std::vector<ChapterInfo*> pgcs = std::vector<ChapterInfo*>();

		std::vector<Chapter> list = std::vector<Chapter>();

		int num = 0;
		TimeSpan *ts = new TimeSpan(0);
		std::string time = "";
		std::string name = "";
		bool onTime = true;
//ORIGINAL LINE: string[] lines = File.ReadAllLines(location);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		std::string *lines = File::ReadAllLines(location);
		for (std::string::const_iterator line = lines->begin(); line != lines->end(); ++line)
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
