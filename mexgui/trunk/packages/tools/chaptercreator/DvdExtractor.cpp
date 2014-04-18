#include "DvdExtractor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
using namespace MeGUI::core::util;

namespace MeGUI
{

	const std::string &DvdExtractor::getExtensions() const
	{
		return new std::string[] { };
	}

	std::vector<ChapterInfo*> DvdExtractor::GetStreams(const std::string &location)
	{
		std::string videoIFO;
		std::string path;

		if (File::Exists(location) && Path::GetExtension(location)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".ifo"))
		{
			path = Path::GetDirectoryName(location);
			videoIFO = location;
		}
		else if (Directory::Exists(location) && Directory::GetFiles(location, "*.IFO")->Length > 0)
		{
			path = location;
			videoIFO = Path::Combine(path, "VIDEO_TS.IFO");
		}
		else if (Directory::Exists(Path::Combine(location, "VIDEO_TS")) && Directory::GetFiles(Path::Combine(location, "VIDEO_TS"), "*.IFO")->Length > 0)
		{
			path = Path::Combine(location, "VIDEO_TS");
			videoIFO = Path::Combine(path, "VIDEO_TS.IFO");
		}
		else
			throw new FileNotFoundException("No DVD IFO data found in " + location);

		std::vector<ChapterInfo*> streams = std::vector<ChapterInfo*>();

		IfoExtractor *ex = new IfoExtractor();
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		ex->StreamDetected += (sender, args) => OnStreamDetected(args::ProgramChain);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		ex->ChaptersLoaded += (sender, args) => OnChaptersLoaded(args::ProgramChain);

		if (File::Exists(videoIFO) && Path::GetFileName(videoIFO)->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("VIDEO_TS.IFO"))
		{
			unsigned char bytRead[4];
			long long VMG_PTT_STPT_Position = IFOparser::ToFilePosition(IFOparser::GetFileBlock(videoIFO, 0xC4, 4));
			int titlePlayMaps = IFOparser::ToInt16(IFOparser::GetFileBlock(videoIFO, VMG_PTT_STPT_Position, 2));

			// get PGC count from all ifo files
			int pgcCount = 0;
			for (unknown::const_iterator file = Directory::GetFiles(path, "VTS_*_0.IFO").begin(); file != Directory::GetFiles(path, "VTS_*_0.IFO").end(); ++file)
				pgcCount += static_cast<int>(IFOparser::getPGCnb(*file));

			if (pgcCount > titlePlayMaps)
			{
				// process all the ifo files as there are more PGCs than in the VIDEO_TS.IFO
				for (unknown::const_iterator file = Directory::GetFiles(path, "VTS_*_0.IFO").begin(); file != Directory::GetFiles(path, "VTS_*_0.IFO").end(); ++file)
					streams.AddRange(ex->GetStreams(*file));
			}
			else
			{
				for (int currentTitle = 1; currentTitle <= titlePlayMaps; ++currentTitle)
				{
					long long titleInfoStart = 8 + ((currentTitle - 1) * 12);
					int titleSetNumber = IFOparser::GetFileBlock(videoIFO, (VMG_PTT_STPT_Position + titleInfoStart) + 6LL, 1)[0];
					int titleSetTitleNumber = IFOparser::GetFileBlock(videoIFO, (VMG_PTT_STPT_Position + titleInfoStart) + 7LL, 1)[0];
					std::string vtsIFO = Path::Combine(path, std::string::Format("VTS_{0:D2}_0.IFO", titleSetNumber));
					if (!File::Exists(vtsIFO))
					{
						Trace::WriteLine(std::string::Format("VTS IFO file missing: {0}", Path::GetFileName(vtsIFO)));
						continue;
					}
					streams.push_back(ex->GetChapterInfo(vtsIFO, titleSetTitleNumber));
				}
			}
		}
		else if (File::Exists(videoIFO))
		{
			// read only the selected ifo file
			streams.AddRange(ex->GetStreams(videoIFO));
		}
		else
		{
			// read all the ifo files
			for (unknown::const_iterator file = Directory::GetFiles(path, "VTS_*_0.IFO").begin(); file != Directory::GetFiles(path, "VTS_*_0.IFO").end(); ++file)
				streams.AddRange(ex->GetStreams(*file));
		}

		OnExtractionComplete();
		return streams;
	}
}
