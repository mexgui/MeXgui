#include "BDInfoExtractor.h"




//using namespace System::Collections::Generic;

//using namespace System::Linq;

//using namespace System::Text;



//using namespace System::Diagnostics;
using namespace BDInfo;

namespace MeXgui
{

	const QString &BDInfoExtractor::getExtensions() const
	{
		return new QString[] {"mpls"};
	}

	const bool &BDInfoExtractor::getSupportsMultipleStreams() const
	{
		return false;
	}

	QVector<ChapterInfo*> BDInfoExtractor::GetStreams(const QString &location)
	{
		ChapterInfo *pgc = new ChapterInfo();
		pgc->setChapters(QVector<Chapter>());
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
		for (QVector<double>::const_iterator d = mpls->Chapters.begin(); d != mpls->Chapters.end(); ++d)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			pgc->getChapters().push_back(Chapter(new object[] {Name = "Chapter " + count.ToString("D2"), Time = new TimeSpan(static_cast<qint64>(*d * static_cast<double>(TimeSpan::TicksPerSecond)))}));
			count++;
		}

		pgc->setDuration(new TimeSpan(static_cast<qint64>(mpls->getTotalLength() * static_cast<double>(TimeSpan::TicksPerSecond))));

		for (QVector<TSStreamClip*>::const_iterator clip = mpls->StreamClips.begin(); clip != mpls->StreamClips.end(); ++clip)
		{
			(*clip)->StreamClipFile->Scan();
			for (QMap<unsigned short, TSStream*>::const_iterator stream = clip->StreamClipFile->Streams.begin(); stream != clip->StreamClipFile->Streams.end(); ++stream)
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
		return QVector<ChapterInfo*>(tempVector, tempVector + sizeof(tempVector) / sizeof(tempVector[0]));
	}
}
