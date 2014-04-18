#include "TSPlaylistFile.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;

namespace BDInfo
{

	TSPlaylistFile::TSPlaylistFile(FileInfo *fileInfo)
	{
		InitializeInstanceFields();
		FileInfo = fileInfo;
		Name = fileInfo->Name->ToUpper(System::Globalization::CultureInfo::InvariantCulture);
	}

	QString TSPlaylistFile::ToString()
	{
		return Name;
	}

	const quint64 &TSPlaylistFile::getFileSize() const
	{
		quint64 size = 0;
		for (QVector<TSStreamClip*>::const_iterator clip = StreamClips.begin(); clip != StreamClips.end(); ++clip)
		{
			size += (*clip)->FileSize;
		}
		return size;
	}

	const double &TSPlaylistFile::getTotalLength() const
	{
		double length = 0;
		for (QVector<TSStreamClip*>::const_iterator clip = StreamClips.begin(); clip != StreamClips.end(); ++clip)
		{
			if ((*clip)->AngleIndex == 0)
			{
				length += (*clip)->Length;
			}
		}
		return length;
	}

	const double &TSPlaylistFile::getAngleLength() const
	{
		double length = 0;
		for (QVector<TSStreamClip*>::const_iterator clip = StreamClips.begin(); clip != StreamClips.end(); ++clip)
		{
			length += (*clip)->Length;
		}
		return length;
	}

	const quint64 &TSPlaylistFile::getTotalSize() const
	{
		quint64 size = 0;
		for (QVector<TSStreamClip*>::const_iterator clip = StreamClips.begin(); clip != StreamClips.end(); ++clip)
		{
			if ((*clip)->AngleIndex == 0)
			{
				size += (*clip)->getPacketSize();
			}
		}
		return size;
	}

	const quint64 &TSPlaylistFile::getAngleSize() const
	{
		quint64 size = 0;
		for (QVector<TSStreamClip*>::const_iterator clip = StreamClips.begin(); clip != StreamClips.end(); ++clip)
		{
			size += (*clip)->getPacketSize();
		}
		return size;
	}

	const quint64 &TSPlaylistFile::getTotalBitRate() const
	{
		if (getTotalLength() > 0)
		{
			return static_cast<quint64>(Math::Round(((getTotalSize() * 8.0) / getTotalLength())));
		}
		return 0;
	}

	const quint64 &TSPlaylistFile::getAngleBitRate() const
	{
		if (getAngleLength() > 0)
		{
			return static_cast<quint64>(Math::Round(((getAngleSize() * 8.0) / getAngleLength())));
		}
		return 0;
	}

	void TSPlaylistFile::Scan()
		//Dictionary<string, TSStreamFile> streamFiles,
		//Dictionary<string, TSStreamClipFile> streamClipFiles)
	{
		FileStream *fileStream = 0;
		BinaryReader *fileReader = 0;

		int streamFileCount = 0;
		QMap<QString, TSStreamClipFile*> streamClipFiles = QMap<QString, TSStreamClipFile*>();

		try
		{
	#if defined(DEBUG)
			Debug::WriteLine(QString::Format("Scanning {0}...", Name));
	#endif
			Streams.clear();
			StreamClips.clear();

			fileStream = File::OpenRead(FileInfo->FullName);
			fileReader = new BinaryReader(fileStream);

			unsigned char data[fileStream->Length];
			int dataLength = fileReader->Read(data, 0, sizeof(data) / sizeof(data[0]));

			unsigned char fileType[8];
			Array::Copy(data, 0, fileType, 0, sizeof(fileType) / sizeof(fileType[0]));

			FileType = ASCIIEncoding::ASCII::GetString(fileType);
			if ((FileType != "MPLS0100" && FileType != "MPLS0200"))
				/*|| data[45] != 1*/
			{
				throw std::exception(QString::Format("Playlist {0} has an unknown file type {1}.", FileInfo->Name, FileType));
			}
	#if defined(DEBUG)
			Debug::WriteLine(QString::Format("\tFileType: {0}", FileType));
	#endif
			int playlistIndex = (static_cast<int>(data[8]) << 24) + (static_cast<int>(data[9]) << 16) + (static_cast<int>(data[10]) << 8) + (static_cast<int>(data[11]));

			// TODO: Hack for bad TSRemux output.
			int playlistLength = sizeof(data) / sizeof(data[0]) - playlistIndex - 4;
			int playlistLengthCorrect = (static_cast<int>(data[playlistIndex]) << 24) + (static_cast<int>(data[playlistIndex + 1]) << 16) + (static_cast<int>(data[playlistIndex + 2]) << 8) + (static_cast<int>(data[playlistIndex + 3]));

			unsigned char playlistData[playlistLength];
			Array::Copy(data, playlistIndex + 4, playlistData, 0, sizeof(playlistData) / sizeof(playlistData[0]));

			streamFileCount = ((static_cast<int>(playlistData[2]) << 8) + static_cast<int>(playlistData[3]));
	#if defined(DEBUG)
			Debug::WriteLine(QString::Format("\tStreamFileCount: {0}", streamFileCount));
	#endif
			QVector<TSStreamClip*> chapterClips = QVector<TSStreamClip*>();
			int streamFileOffset = 6;
			for (int streamFileIndex = 0; streamFileIndex < streamFileCount; streamFileIndex++)
			{
				unsigned char streamFileNameData[5];
				Array::Copy(playlistData, streamFileOffset + 2, streamFileNameData, 0, sizeof(streamFileNameData) / sizeof(streamFileNameData[0]));

				//TSStreamFile streamFile = null;
				//string streamFileName = string.Format(
				//    "{0}.M2TS",
				//    ASCIIEncoding.ASCII.GetString(streamFileNameData));
				//if (streamFiles.ContainsKey(streamFileName))
				//{
				//    streamFile = streamFiles[streamFileName];
				//}
				//if (streamFile == null)
				//{
				//    throw new Exception(string.Format(
				//        "Playlist {0} referenced missing file {1}.",
				//        FileInfo.Name, streamFileName));
				//}

				TSStreamClipFile *streamClipFile = 0;
				QString streamClipFileName = QString::Format("{0}.CLPI", ASCIIEncoding::ASCII::GetString(streamFileNameData));
				QString streamClipFilePath = Path::Combine(Path::Combine(FileInfo->Directory->Parent->FullName, "CLIPINF"), streamClipFileName);
				if (File::Exists(streamClipFilePath) && !streamClipFiles.find(streamClipFileName) != streamClipFiles.end())
				  streamClipFiles.insert(make_pair(streamClipFileName, new TSStreamClipFile(new FileInfo(streamClipFilePath))));

				if (streamClipFiles.find(streamClipFileName) != streamClipFiles.end())
				{
					streamClipFile = streamClipFiles[streamClipFileName];
				}
				if (streamClipFile == 0)
				{
					throw std::exception(QString::Format("Playlist {0} referenced missing file {1}.", FileInfo->Name, streamClipFileName));
				}

				unsigned char condition = static_cast<unsigned char>(playlistData[streamFileOffset + 12] & 0xF);

				quint64 timeIn = (static_cast<quint64>(playlistData[streamFileOffset + 14]) << 24) + (static_cast<quint64>(playlistData[streamFileOffset + 15]) << 16) + (static_cast<quint64>(playlistData[streamFileOffset + 16]) << 8) + (static_cast<quint64>(playlistData[streamFileOffset + 17]));

				quint64 timeOut = (static_cast<quint64>(playlistData[streamFileOffset + 18]) << 24) + (static_cast<quint64>(playlistData[streamFileOffset + 19]) << 16) + (static_cast<quint64>(playlistData[streamFileOffset + 20]) << 8) + (static_cast<quint64>(playlistData[streamFileOffset + 21]));

				TSStreamClip *streamClip = new TSStreamClip(streamClipFile);
					//streamFile, 

				streamClip->TimeIn = static_cast<double>(timeIn) / 45000;
				streamClip->TimeOut = static_cast<double>(timeOut) / 45000;
				streamClip->Length = streamClip->TimeOut - streamClip->TimeIn;
				streamClip->RelativeTimeIn = getTotalLength();
				streamClip->RelativeTimeOut = streamClip->RelativeTimeIn + streamClip->Length;
				StreamClips.push_back(streamClip);
				chapterClips.push_back(streamClip);
	#if defined(DEBUG)
				Debug::WriteLine(QString::Format("\t{0} {1} {2} {3}", streamClip->Name, streamClip->TimeIn.TotalSeconds, streamClip->TimeOut.TotalSeconds, streamClip->Length.TotalSeconds));
	#endif
				if ((playlistData[streamFileOffset + 12] & 0x10) > 0)
				{
					int angleCount = playlistData[streamFileOffset + 34];
					if (angleCount - 1 > AngleCount)
					{
						AngleCount = angleCount - 1;
					}
					for (int angle = 0; angle < (angleCount - 1); angle++)
					{
						unsigned char angleFileNameData[5];
						int angleOffset = streamFileOffset + 26 + ((angle + 1) * 10);
						Array::Copy(playlistData, angleOffset, angleFileNameData, 0, sizeof(angleFileNameData) / sizeof(angleFileNameData[0]));

						//TSStreamFile angleFile = null;
						//string angleFileName = string.Format(
						//    "{0}.M2TS",
						//    ASCIIEncoding.ASCII.GetString(angleFileNameData));
						//if (streamFiles.ContainsKey(angleFileName))
						//{
						//    angleFile = streamFiles[angleFileName];
						//}
						//if (angleFile == null)
						//{
						//    throw new Exception(string.Format(
						//        "Playlist {0} referenced missing angle file {1}.",
						//        FileInfo.Name, angleFileName));
						//}

						TSStreamClipFile *angleClipFile = 0;
						QString angleClipFileName = QString::Format("{0}.CLPI", ASCIIEncoding::ASCII::GetString(angleFileNameData));
						if (streamClipFiles.find(angleClipFileName) != streamClipFiles.end())
						{
							angleClipFile = streamClipFiles[angleClipFileName];
						}
						if (angleClipFile == 0)
						{
							throw std::exception(QString::Format("Playlist {0} referenced missing angle file {1}.", FileInfo->Name, angleClipFileName));
						}

						TSStreamClip *angleClip = new TSStreamClip(angleClipFile); //angleFile,
						angleClip->AngleIndex = angle + 1;
						angleClip->TimeIn = streamClip->TimeIn;
						angleClip->TimeOut = streamClip->TimeOut;
						angleClip->RelativeTimeIn = streamClip->RelativeTimeIn;
						angleClip->RelativeTimeOut = streamClip->RelativeTimeOut;
						angleClip->Length = streamClip->Length;
						StreamClips.push_back(angleClip);
	#if defined(DEBUG)
						Debug::WriteLine(QString::Format("\t\t{0}", angleFileName));
	#endif
					}
				}
				streamFileOffset += 2 + (static_cast<int>(playlistData[streamFileOffset]) << 8) + (static_cast<int>(playlistData[streamFileOffset + 1]));
			}

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

					TSStreamClip *streamClip = chapterClips[streamFileIndex];

					qint64 chapterTime = (static_cast<qint64>(chapterData[chapterOffset + 4]) << 24) + (static_cast<qint64>(chapterData[chapterOffset + 5]) << 16) + (static_cast<qint64>(chapterData[chapterOffset + 6]) << 8) + (static_cast<qint64>(chapterData[chapterOffset + 7]));

					double chapterSeconds = static_cast<double>(chapterTime) / 45000;
					double relativeSeconds = chapterSeconds - streamClip->TimeIn + streamClip->RelativeTimeIn;

					// TODO: Ignore short last chapter?
					if (getTotalLength() - relativeSeconds > 1.0)
					{
						streamClip->Chapters.push_back(chapterSeconds);
						this->Chapters.push_back(relativeSeconds);
					}
	#if defined(DEBUG)
					Debug::WriteLine(QString::Format("\t{0} {1} {2}", chapterIndex, streamClip->Name, chapter::TotalSeconds));
	#endif
				}
				chapterOffset += 14;
			}
	#if defined(DEBUG)
			Debug::WriteLine(QString::Format("\tLength: {0}", Length::TotalSeconds));
			Debug::WriteLine(QString::Format("\tAngleLength: {0}", getAngleLength().TotalSeconds));
	#endif
			//LoadStreamClips();
			IsInitialized = true;
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (fileReader != 0)
			{
				fileReader->Close();
			}
			if (fileStream != 0)
			{
				fileStream->Close();
			}
		}
	}

	int TSPlaylistFile::CompareVideoStreams(TSVideoStream *x, TSVideoStream *y)
	{
		if (x == 0 && y == 0)
		{
			return 0;
		}
		else if (x == 0 && y != 0)
		{
			return 1;
		}
		else if (x != 0 && y == 0)
		{
			return -1;
		}
		else
		{
			if (x->Height > y->Height)
			{
				return -1;
			}
			else if (y->Height > x->Height)
			{
				return 1;
			}
			else if (x->PID > y->PID)
			{
				return 1;
			}
			else if (y->PID > x->PID)
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}

	int TSPlaylistFile::CompareAudioStreams(TSAudioStream *x, TSAudioStream *y)
	{
		if (x == y)
		{
			return 0;
		}
		else if (x == 0 && y == 0)
		{
			return 0;
		}
		else if (x == 0 && y != 0)
		{
			return -1;
		}
		else if (x != 0 && y == 0)
		{
			return 1;
		}
		else
		{
			if (x->ChannelCount > y->ChannelCount)
			{
				return -1;
			}
			else if (y->ChannelCount > x->ChannelCount)
			{
				return 1;
			}
			else
			{
				int sortX = GetStreamTypeSortIndex(x->StreamType);
				int sortY = GetStreamTypeSortIndex(y->StreamType);

				if (sortX > sortY)
				{
					return -1;
				}
				else if (sortY > sortX)
				{
					return 1;
				}
				else
				{
					if (x->getLanguageCode() == "eng")
					{
						return -1;
					}
					else if (y->getLanguageCode() == "eng")
					{
						return 1;
					}
					else
					{
						return x->LanguageName.compare(y->LanguageName);
					}
				}
			}
		}
	}

	int TSPlaylistFile::CompareTextStreams(TSTextStream *x, TSTextStream *y)
	{
		if (x == y)
		{
			return 0;
		}
		else if (x == 0 && y == 0)
		{
			return 0;
		}
		else if (x == 0 && y != 0)
		{
			return -1;
		}
		else if (x != 0 && y == 0)
		{
			return 1;
		}
		else
		{
			if (x->getLanguageCode() == "eng")
			{
				return -1;
			}
			else if (y->getLanguageCode() == "eng")
			{
				return 1;
			}
			else
			{
				if (x->getLanguageCode() == y->getLanguageCode())
				{
					if (x->PID > y->PID)
					{
						return 1;
					}
					else if (y->PID > x->PID)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return x->LanguageName.compare(y->LanguageName);
				}
			}
		}
	}

	int TSPlaylistFile::CompareGraphicsStreams(TSGraphicsStream *x, TSGraphicsStream *y)
	{
		if (x == y)
		{
			return 0;
		}
		else if (x == 0 && y == 0)
		{
			return 0;
		}
		else if (x == 0 && y != 0)
		{
			return -1;
		}
		else if (x != 0 && y == 0)
		{
			return 1;
		}
		else
		{
			int sortX = GetStreamTypeSortIndex(x->StreamType);
			int sortY = GetStreamTypeSortIndex(y->StreamType);

			if (sortX > sortY)
			{
				return -1;
			}
			else if (sortY > sortX)
			{
				return 1;
			}
			else if (x->getLanguageCode() == "eng")
			{
				return -1;
			}
			else if (y->getLanguageCode() == "eng")
			{
				return 1;
			}
			else
			{
				if (x->getLanguageCode() == y->getLanguageCode())
				{
					if (x->PID > y->PID)
					{
						return 1;
					}
					else if (y->PID > x->PID)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return x->LanguageName.compare(y->LanguageName);
				}
			}
		}
	}

	int TSPlaylistFile::GetStreamTypeSortIndex(TSStreamType streamType)
	{
		switch (streamType)
		{
			case Unknown:
				return 0;
			case MPEG1_VIDEO:
				return 1;
			case MPEG2_VIDEO:
				return 2;
			case AVC_VIDEO:
				return 3;
			case VC1_VIDEO:
				return 4;

			case MPEG1_AUDIO:
				return 1;
			case MPEG2_AUDIO:
				return 2;
			case AC3_PLUS_SECONDARY_AUDIO:
				return 3;
			case DTS_HD_SECONDARY_AUDIO:
				return 4;
			case AC3_AUDIO:
				return 5;
			case DTS_AUDIO:
				return 6;
			case AC3_PLUS_AUDIO:
				return 7;
			case DTS_HD_AUDIO:
				return 8;
			case AC3_TRUE_HD_AUDIO:
				return 9;
			case DTS_HD_MASTER_AUDIO:
				return 10;
			case LPCM_AUDIO:
				return 11;

			case SUBTITLE:
				return 1;
			case INTERACTIVE_GRAPHICS:
				return 2;
			case PRESENTATION_GRAPHICS:
				return 3;

			default:
				return 0;
		}
	}

	void TSPlaylistFile::InitializeInstanceFields()
	{
		delete FileInfo;
		FileType = "";
		IsInitialized = false;
		Name = "";
		Chapters = QVector<double>();
		Streams = QMap<unsigned short, TSStream*>();
		StreamClips = QVector<TSStreamClip*>();
		AngleStreams = QVector<QMap<unsigned short, TSStream*>*>();
		AngleCount = 0;
	}
}
