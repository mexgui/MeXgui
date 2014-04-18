#include "MplsExtractor.h"




//using namespace System::Collections::Generic;

//using namespace System::Linq;

//using namespace System::Text;



//using namespace System::Diagnostics;

namespace MeXgui
{

	const QString &MplsExtractor::getExtensions() const
	{
		return new QString[] {"mpls"};
	}

	const bool &MplsExtractor::getSupportsMultipleStreams() const
	{
		return false;
	}

	QVector<ChapterInfo*> MplsExtractor::GetStreams(const QString &location)
	{
		ChapterInfo *pgc = new ChapterInfo();
		QVector<Chapter> chapters = QVector<Chapter>();
		pgc->setSourceName(location);
		pgc->setSourceHash(ChapterExtractor::ComputeMD5Sum(location));
		pgc->setSourceType("Blu-Ray");
		pgc->setTitle(Path::GetFileNameWithoutExtension(location));

		FileInfo *fileInfo = new FileInfo(location);
//ORIGINAL LINE: byte[] data = File.ReadAllBytes(location);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		unsigned char *data = File::ReadAllBytes(location);

		QString fileType = ASCIIEncoding::ASCII::GetString(data, 0, 8);

		if ((fileType != "MPLS0100" && fileType != "MPLS0200"))
		/*|| data[45] != 1*/
		{
			throw std::exception(QString::Format("Playlist {0} has an unknown file type {1}.", fileInfo->Name, fileType));
		}

		QVector<Clip*> chapterClips = GetClips(data);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		pgc->setDuration(new TimeSpan(static_cast<qint64>(chapterClips.Sum(c => c->Length) * static_cast<double>(TimeSpan::TicksPerSecond))));
		OnStreamDetected(pgc);

		int chaptersIndex = (static_cast<int>(data[12]) << 24) + (static_cast<int>(data[13]) << 16) + (static_cast<int>(data[14]) << 8) + (static_cast<int>(data[15]));

		int chaptersLength = (static_cast<int>(data[chaptersIndex]) << 24) + (static_cast<int>(data[chaptersIndex + 1]) << 16) + (static_cast<int>(data[chaptersIndex + 2]) << 8) + (static_cast<int>(data[chaptersIndex + 3]));

		unsigned char chapterData[chaptersLength];
		Array::Copy(data, chaptersIndex + 4, chapterData, 0, chaptersLength);

		int chapterCount = (static_cast<int>(chapterData[0]) << 8) + chapterData[1];
		int chapterOffset = 2;
		for (int chapterIndex = 0; chapterIndex < chapterCount; chapterIndex++)
		{
			if (chapterData[chapterOffset + 1] == 1)
			{
				int streamFileIndex = (static_cast<int>(chapterData[chapterOffset + 2]) << 8) + chapterData[chapterOffset + 3];

				Clip *streamClip = chapterClips[streamFileIndex];

				qint64 chapterTime = (static_cast<qint64>(chapterData[chapterOffset + 4]) << 24) + (static_cast<qint64>(chapterData[chapterOffset + 5]) << 16) + (static_cast<qint64>(chapterData[chapterOffset + 6]) << 8) + (static_cast<qint64>(chapterData[chapterOffset + 7]));

				double chapterSeconds = static_cast<double>(chapterTime) / 45000;
				double relativeSeconds = chapterSeconds - streamClip->TimeIn + streamClip->RelativeTimeIn;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				chapters.push_back(Chapter(new object[] {Name = "Chapter " + (chapterIndex + 1)->ToString("D2"), Time = new TimeSpan(static_cast<qint64>(relativeSeconds * static_cast<double>(TimeSpan::TicksPerSecond)))})); //string.Empty,
			}
			chapterOffset += 14;
		}
		pgc->setChapters(chapters);

		//TODO: get real FPS
		pgc->setFramesPerSecond(25.0);

		OnChaptersLoaded(pgc);
		OnExtractionComplete();
		const ChapterInfo* tempVector[] = {pgc};
		return QVector<ChapterInfo*>(tempVector, tempVector + sizeof(tempVector) / sizeof(tempVector[0]));
	}

	QVector<Clip*> MplsExtractor::GetClips(unsigned char data[])
	{
		QVector<Clip*> chapterClips = QVector<Clip*>();

		int playlistIndex = (static_cast<int>(data[8]) << 24) + (static_cast<int>(data[9]) << 16) + (static_cast<int>(data[10]) << 8) + (static_cast<int>(data[11]));

		// TODO: Hack for bad TSRemux output.
		int playlistLength = sizeof(data) / sizeof(data[0]) - playlistIndex - 4;
		int playlistLengthCorrect = (static_cast<int>(data[playlistIndex]) << 24) + (static_cast<int>(data[playlistIndex + 1]) << 16) + (static_cast<int>(data[playlistIndex + 2]) << 8) + (static_cast<int>(data[playlistIndex + 3]));

		unsigned char playlistData[playlistLength];
		Array::Copy(data, playlistIndex + 4, playlistData, 0, sizeof(playlistData) / sizeof(playlistData[0]));

		int streamFileCount = ((static_cast<int>(playlistData[2]) << 8) + static_cast<int>(playlistData[3]));

		int streamFileOffset = 6;
		for (int streamFileIndex = 0; streamFileIndex < streamFileCount; streamFileIndex++)
		{
			unsigned char condition = static_cast<unsigned char>(playlistData[streamFileOffset + 12] & 0xF);

			quint64 timeIn = (static_cast<quint64>(playlistData[streamFileOffset + 14]) << 24) + (static_cast<quint64>(playlistData[streamFileOffset + 15]) << 16) + (static_cast<quint64>(playlistData[streamFileOffset + 16]) << 8) + (static_cast<quint64>(playlistData[streamFileOffset + 17]));

			quint64 timeOut = (static_cast<quint64>(playlistData[streamFileOffset + 18]) << 24) + (static_cast<quint64>(playlistData[streamFileOffset + 19]) << 16) + (static_cast<quint64>(playlistData[streamFileOffset + 20]) << 8) + (static_cast<quint64>(playlistData[streamFileOffset + 21]));

			Clip *streamClip = new Clip();

			streamClip->TimeIn = static_cast<double>(timeIn) / 45000;
			streamClip->TimeOut = static_cast<double>(timeOut) / 45000;
			streamClip->Length = streamClip->TimeOut - streamClip->TimeIn;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			streamClip->RelativeTimeIn = chapterClips.Sum(c => c->Length);
			streamClip->RelativeTimeOut = streamClip->RelativeTimeIn + streamClip->Length;
			chapterClips.push_back(streamClip);

			//ignore angles

			streamFileOffset += 2 + (static_cast<int>(playlistData[streamFileOffset]) << 8) + (static_cast<int>(playlistData[streamFileOffset + 1]));
		}
		return chapterClips;
	}

	void Clip::InitializeInstanceFields()
	{
		AngleIndex = 0;
		FileSize = 0;
		PayloadBytes = 0;
		PacketCount = 0;
		PacketSeconds = 0;
		Chapters_Renamed = QVector<double>();
	}
}
