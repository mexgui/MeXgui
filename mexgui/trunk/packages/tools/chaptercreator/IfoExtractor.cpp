#include "IfoExtractor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
using namespace MeGUI::core::util;

namespace MeGUI
{

	const std::string &IfoExtractor::getExtensions() const
	{
		return new std::string[] {"ifo"};
	}

	const bool &IfoExtractor::getSupportsMultipleStreams() const
	{
		return false;
	}

	std::vector<ChapterInfo*> IfoExtractor::GetStreams(const std::string &ifoFile)
	{
		std::vector<ChapterInfo*> oList = std::vector<ChapterInfo*>();
		ChapterInfo *oChapterInfo;

		int pgcCount = static_cast<int>(IFOparser::getPGCnb(ifoFile));
		for (int i = 1; i <= pgcCount; i++)
		{
			oChapterInfo = GetChapterInfo(ifoFile, i);
			oList.push_back(oChapterInfo);
		}
		return oList;
	}

	ChapterInfo *IfoExtractor::GetChapterInfo(const std::string &location, int titleSetNum)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (location.StartsWith("VTS_"))
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
			titleSetNum = int::Parse(Path::GetFileNameWithoutExtension(location)->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Replace("VTS_", "")->Replace("_0.IFO", ""));
		}

		ChapterInfo *pgc = new ChapterInfo();
		pgc->setSourceType("DVD");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		pgc->setSourceName("PGC " + titleSetNum.ToString("D2"));
		pgc->setTitleNumber(titleSetNum);
		pgc->setSourceHash(ChapterExtractor::ComputeMD5Sum(location));
		pgc->setTitle(Path::GetFileNameWithoutExtension(location));
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		if (pgc->getTitle().Split('_')->Length == 3)
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			pgc->setTitle(pgc->getTitle().Split('_')[0] + "_" + pgc->getTitle().Split('_')[1]);

		TimeSpan *duration;
		double fps;
		pgc->setChapters(GetChapters(location, titleSetNum, duration, fps));
		pgc->setDuration(duration);
		pgc->setFramesPerSecond(fps);

		OnStreamDetected(pgc);
		OnExtractionComplete();
		return pgc;
	}

	std::vector<Chapter> IfoExtractor::GetChapters(const std::string &ifoFile, int programChain, TimeSpan *&duration, double &fps)
	{
		std::vector<Chapter> chapters = std::vector<Chapter>();
		duration = TimeSpan::Zero;
		fps = 0;

		long long pcgITPosition = IFOparser::GetPCGIP_Position(ifoFile);
		int programChainPrograms = -1;
		TimeSpan *programTime = TimeSpan::Zero;
		if (programChain >= 0)
		{
			double FPS;
			unsigned int chainOffset = IFOparser::GetChainOffset(ifoFile, pcgITPosition, programChain);
			Nullable<TimeSpan> tempVar = IFOparser.ReadTimeSpan(ifoFile, pcgITPosition, chainOffset, FPS);
			programTime = tempVar::HasValue ? tempVar : TimeSpan::Zero;
			programChainPrograms = IFOparser::GetNumberOfPrograms(ifoFile, pcgITPosition, chainOffset);
		}
		else
		{
			int programChains = IFOparser::GetProgramChains(ifoFile, pcgITPosition);
			for (int curChain = 1; curChain <= programChains; curChain++)
			{
				double FPS;
				unsigned int chainOffset = IFOparser::GetChainOffset(ifoFile, pcgITPosition, curChain);
				Nullable<TimeSpan*> time = IFOparser::ReadTimeSpan(ifoFile, pcgITPosition, chainOffset, FPS);
				if (!time.HasValue)
					break;

				if (time.Value > programTime)
				{
					programChain = curChain;
					programChainPrograms = IFOparser::GetNumberOfPrograms(ifoFile, pcgITPosition, chainOffset);
					programTime = time.Value;
				}
			}
		}
		if (programChain < 0)
			return 0;

		chapters.push_back(Chapter(new object[] {Name = "Chapter 01"}));

		unsigned int longestChainOffset = IFOparser::GetChainOffset(ifoFile, pcgITPosition, programChain);
		int programMapOffset = IFOparser::ToInt16(IFOparser::GetFileBlock(ifoFile, (pcgITPosition + longestChainOffset) + 230, 2));
		int cellTableOffset = IFOparser::ToInt16(IFOparser::GetFileBlock(ifoFile, (pcgITPosition + longestChainOffset) + 0xE8, 2));
		for (int currentProgram = 0; currentProgram < programChainPrograms; ++currentProgram)
		{
			int entryCell = IFOparser::GetFileBlock(ifoFile, ((pcgITPosition + longestChainOffset) + programMapOffset) + currentProgram, 1)[0];
			int exitCell = entryCell;
			if (currentProgram < (programChainPrograms - 1))
				exitCell = IFOparser::GetFileBlock(ifoFile, ((pcgITPosition + longestChainOffset) + programMapOffset) + (currentProgram + 1), 1)[0] - 1;

			TimeSpan *totalTime = TimeSpan::Zero;
			for (int currentCell = entryCell; currentCell <= exitCell; currentCell++)
			{
				int cellStart = cellTableOffset + ((currentCell - 1) * 0x18);
//ORIGINAL LINE: byte[] bytes = IFOparser.GetFileBlock(ifoFile, (pcgITPosition + longestChainOffset) + cellStart, 4);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				unsigned char *bytes = IFOparser::GetFileBlock(ifoFile, (pcgITPosition + longestChainOffset) + cellStart, 4);
				int cellType = bytes[0] >> 6;
				if (cellType == 0x00 || cellType == 0x01)
				{
					bytes = IFOparser::GetFileBlock(ifoFile, ((pcgITPosition + longestChainOffset) + cellStart) + 4, 4);
					Nullable<TimeSpan> tempVar2 = IFOparser.ReadTimeSpan(bytes, fps);
					TimeSpan *time = tempVar2::HasValue ? tempVar2 : TimeSpan::Zero;
					totalTime += time;
				}
			}

			//add a constant amount of time for each chapter?
			//totalTime += TimeSpan.FromMilliseconds(fps != 0 ? (double)1000 / fps / 8D : 0);

			duration += totalTime;
			if (currentProgram + 1 < programChainPrograms)
				chapters.push_back(Chapter(new object[] {Name = std::string::Format("Chapter {0:D2}", currentProgram + 2), Time = duration}));
		}
		return chapters;
	}
}
