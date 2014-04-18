#include "BDInfoExtractor.h"

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
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
using namespace BDInfo;

namespace MeGUI
{

	const std::string &BDInfoExtractor::getExtensions() const
	{
		return new std::string[] {"mpls"};
	}

	const bool &BDInfoExtractor::getSupportsMultipleStreams() const
	{
		return false;
	}

	std::vector<ChapterInfo*> BDInfoExtractor::GetStreams(const std::string &location)
	{
		ChapterInfo *pgc = new ChapterInfo();
		pgc->setChapters(std::vector<Chapter>());
		pgc->setSourceHash(ChapterExtractor::ComputeMD5Sum(location));
		pgc->setSourceName(location);
		pgc->setTitle(Path::GetFileNameWithoutExtension(location));
		pgc->setSourceType("Blu-Ray");

		FileInfo *fileInfo = new FileInfo(location);

		OnStreamDetected(pgc);
		TSPlaylistFile *mpls = new TSPlaylistFile(fileInfo);
		//Dictionary<string, TSStreamClipFile> clips = new Dictionary<string,TSStreamClipFile>();
		mpls->Scan();
		int count = 1;
		for (std::vector<double>::const_iterator d = mpls->Chapters.begin(); d != mpls->Chapters.end(); ++d)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			pgc->getChapters().push_back(Chapter(new object[] {Name = "Chapter " + count.ToString("D2"), Time = new TimeSpan(static_cast<long long>(*d * static_cast<double>(TimeSpan::TicksPerSecond)))}));
			count++;
		}

		pgc->setDuration(new TimeSpan(static_cast<long long>(mpls->getTotalLength() * static_cast<double>(TimeSpan::TicksPerSecond))));

		for (std::vector<TSStreamClip*>::const_iterator clip = mpls->StreamClips.begin(); clip != mpls->StreamClips.end(); ++clip)
		{
			(*clip)->StreamClipFile->Scan();
			for (std::map<unsigned short, TSStream*>::const_iterator stream = clip->StreamClipFile->Streams.begin(); stream != clip->StreamClipFile->Streams.end(); ++stream)
			{
				if (stream->second->IsVideoStream)
				{
					pgc->setFramesPerSecond(static_cast<double>((static_cast<TSVideoStream*>(stream->second))->FrameRateEnumerator) / static_cast<double>((static_cast<TSVideoStream*>(stream->second))->FrameRateDenominator));
					break;
				}
			}
			if (pgc->getFramesPerSecond() != 0)
				break;
		}

		OnChaptersLoaded(pgc);
		OnExtractionComplete();
		const ChapterInfo* tempVector[] = {pgc};
		return std::vector<ChapterInfo*>(tempVector, tempVector + sizeof(tempVector) / sizeof(tempVector[0]));
	}
}
