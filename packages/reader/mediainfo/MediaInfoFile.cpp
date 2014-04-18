#include "MediaInfoFile.h"




//using namespace System::Collections::Generic;

//using namespace System::Globalization;



//using namespace System::Text;

//using namespace System::Text::RegularExpressions;
using namespace MediaInfoWrapper;
using namespace MeXgui::core::details;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::hdbdextractor;

namespace MeXgui
{

	MediaInfoException::MediaInfoException(std::exception &e) : Exception("Media info error: " + e.what(), e)
	{
	}

    IMediaFile *MediaInfoFileFactory::Open(const QString &file)
	{
		return new MediaInfoFile(file);
	}

    int MediaInfoFileFactory::HandleLevel(const QString &file)
	{
		return 5;
	}

    const QString &MediaInfoFileFactory::getID() const
	{
		return "MediaInfo/DirectShowSource";
	}

    MediaFile *MediaInfoFile::Open(const QString &file)
	{
		try
		{
			MediaInfo *m = new MediaInfo(file);

			// tracks
			QVector<MediaTrack*> tracks = QVector<MediaTrack*>();
			for (unknown::const_iterator t = m->Video.begin(); t != m->Video.end(); ++t)
			{
				VideoTrack *v = new VideoTrack();
				v->Codec = v->VCodec = getVideoCodec((*t)->Codec);
				v->Info = new TrackInfo((*t)->Language, (*t)->Title);

				quint64 width = quint64::Parse((*t)->Width);
				quint64 height = quint64::Parse((*t)->Height);
				quint64 frameCount = quint64::Parse((*t)->FrameCount);
				Nullable<double> tempVar = easyParseDouble((*t).FrameRate);
				Nullable<double> tempVar2 = easyParseDouble((*t).FrameRateOriginal);
				double fps = (tempVar::HasValue ? tempVar : tempVar2::HasValue ? tempVar2 : 99);

				Dar dar = Resolution::GetDAR(static_cast<int>(width), static_cast<int>(height), (*t)->AspectRatio, 0, 0);

				v->StreamInfo = new VideoInfo2(width, height, dar, frameCount, fps);
				v->TrackNumber = unsigned int::Parse((*t)->ID);
				tracks.push_back(v);
			}

			for (unknown::const_iterator t = m->Audio.begin(); t != m->Audio.end(); ++t)
			{
				AudioTrack *a = new AudioTrack();
				a->Codec = a->ACodec = getAudioCodec((*t)->Format);
				a->Info = new TrackInfo((*t)->Language, (*t)->Title);

				a->StreamInfo = new AudioInfo();

				a->TrackNumber = unsigned int::Parse((*t)->ID);

				tracks.push_back(a);
			}

            for (QString::const_iterator t = m->Text->begin(); t != m->Text->end(); ++t)
			{
				SubtitleTrack *s = new SubtitleTrack();
				s->Codec = s->SCodec = getSubtitleCodec((*t)->Codec);
				s->Info = new TrackInfo((*t)->Language, (*t)->Title);
				s->StreamInfo = new SubtitleInfo2();
				s->TrackNumber = unsigned int::Parse((*t)->ID);

				tracks.push_back(s);
			}

			if (m->General->Count != 1)
				throw std::exception("Expected one general track");

			GeneralTrack *g = m->General[0];
			ContainerType *cType = getContainerType(g->Format, g->FormatString);
			TimeSpan *playTime = TimeSpan::Parse(g->PlayTimeString3);

			Chapters *chapters = 0;
			if (m->Chapters->Count == 1)
				chapters = parseChapters(m->Chapters[0]);

			delete m;
			return new MediaFile(tracks, chapters, playTime, cType);
		}
		catch (std::exception &e1)
		{
			return 0;
		}
	}

Regex *MediaInfoFile::chaptersRegex = new Regex("^(?<num>\\d+)\\s*:\\s*(?<hours>\\d+):(?<mins>\\d+):(?<secs>\\d+).(?<ms>\\d+) (?<name>.*)$", RegexOptions::Multiline | RegexOptions::Compiled);

	Chapters *MediaInfoFile::parseChapters(MediaInfoWrapper::ChaptersTrack *t)
	{
		// sample:

	/*Language             : English
	1                    : 00:00:00.000 Part 1
	2                    : 00:42:20.064 Part 2
	3                    : 01:26:34.240 Part 3*/

		QVector<Chapter> chapters = QVector<Chapter>();
		for (unknown::const_iterator m = chaptersRegex->Matches(t->Inform).begin(); m != chaptersRegex->Matches(t->Inform).end(); ++m)
		{
			Chapter c = Chapter();
			c.name = (*m)->Groups["name"]->Value;
			c.StartTime = new TimeSpan(0, int::Parse((*m)->Groups["hours"]->Value), int::Parse((*m)->Groups["mins"]->Value), int::Parse((*m)->Groups["secs"]->Value), int::Parse((*m)->Groups["ms"]->Value));
			chapters.push_back(c);
		}
		Chapters *ch = new Chapters();
		ch->Data = chapters;
		return ch;
	}

    SubtitleCodec *MediaInfoFile::getSubtitleCodec(const QString &p)
	{
		try
		{
			return 0;
		}
		catch (std::exception &e1)
		{
		   throw std::exception("The method or operation is not implemented.");
		}
	}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class
	Nullable<T> MediaInfoFile::easyParse(Getter<T> parse)
	{
		try
		{
			return parse();
		}
		catch (std::exception &e1)
		{
			return 0;
		}
	}

CultureInfo *const MediaInfoFile::culture = new CultureInfo("en-us");

	const AudioInformation &MediaInfoFile::getAudioInfo() const
	{
		return _AudioInfo;
	}

	const SubtitleInformation &MediaInfoFile::getSubtitleInfo() const
	{
		return _SubtitleInfo;
	}

	const VideoInformation &MediaInfoFile::getVideoInfo() const
	{
		return _VideoInfo;
	}

	const ContainerType &MediaInfoFile::getContainerFileType() const
	{
		return cType;
	}

    const QString &MediaInfoFile::getContainerFileTypeString() const
	{
		return _strContainer;
	}

    MediaInfoFile::MediaInfoFile(const QString &file, LogItem *&oLog)
	{
		InitializeInstanceFields();
	}

    MediaInfoFile::MediaInfoFile(const QString &file, LogItem *&oLog, int iPGCNumber)
	{
		InitializeInstanceFields();
		GetSourceInformation(file, oLog, iPGCNumber);
	}

    MediaInfoFile::MediaInfoFile(const QString &file)
	{
		InitializeInstanceFields();
	}

    MediaInfoFile::MediaInfoFile(const QString &file, int iPGCNumber)
	{
		InitializeInstanceFields();
		GetSourceInformation(file, 0, iPGCNumber);
	}

    void MediaInfoFile::GetSourceInformation(const QString &file, LogItem *oLog, int iPGCNumber)
	{
		if (file.find("|") != string::npos)
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			file = file.Split('|')[0];
		_Log = oLog;
		_file = file;
		_indexerToUse = FileIndexerWindow::NONE;
		this->_AudioInfo = new AudioInformation();
		this->_SubtitleInfo = new SubtitleInformation();
		this->_VideoInfo = new VideoInformation(false, 0, 0, Dar::A1x1, 0, 0, 0, 1);

		try
		{
			LogItem *infoLog = 0;
			if (oLog != 0)
			{
				infoLog = oLog->LogValue("MediaInfo", "");
				infoLog->Info("File: " + _file);
			}

			// if an index file is used extract the real file name
			if (Path::GetExtension(file)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".d2v") || Path::GetExtension(file)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".dga") || Path::GetExtension(file)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".dgi"))
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (StreamReader sr = new StreamReader(file, Encoding.Default))
				StreamReader *sr = new StreamReader(file, Encoding::Default);
				try
				{
                    QString line = "";
					int iLineCount = 0;
					while ((line = sr->ReadLine()) != 0)
					{
						iLineCount++;
						if (iLineCount == 3 && !Path::GetExtension(file)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".dgi"))
						{
                            QString strSourceFile = line;
							if (Path::GetExtension(file)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".dgi"))
								strSourceFile = line.substr(0, line.rfind(" "));
							if (File::Exists(strSourceFile))
								_file = file = strSourceFile;
							break;
						}
						else if (iLineCount == 4)
						{
                            QString strSourceFile = line.substr(0, line.rfind(" "));
							if (File::Exists(strSourceFile))
								_file = file = strSourceFile;
							break;
						}
					}
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (sr != 0)
						sr.Dispose();
				}
				if (infoLog != 0)
					infoLog->Info("Indexed File: " + _file);
			}

			// get basic media information
			MediaInfo *info = new MediaInfo(file);
			CorrectSourceInformation(info, file, infoLog, iPGCNumber);
			if (infoLog != 0)
				WriteSourceInformation(info, file, infoLog);

			// container detection
			if (info->General->Count < 1)
			{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
				delete cType;
			}
			else
			{
				cType = getContainerType(info->General[0]->Format, info->General[0]->FormatString);
				_strContainer = info->General[0]->Format;
			}

			// audio detection
			_AudioInfo->setCodecs(new AudioCodec[info->Audio->Count]);
			_AudioInfo->setBitrateModes(new BitrateManagementMode[info->Audio->Count]);

			if (sizeof(_AudioInfo->getCodecs()) / sizeof(_AudioInfo->getCodecs()[0]) == 1)
				_AudioInfo->setType(getAudioType(_AudioInfo->getCodecs()[0], cType, file));
			else
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
				delete _AudioInfo->getType();

			for (int counter = 0; counter < info->Audio->Count; counter++)
			{
				MediaInfoWrapper::AudioTrack *atrack = info->Audio[counter];

				if (atrack->Delay->empty() && atrack->SamplingRate->empty() && atrack->FormatProfile->empty() && atrack->Channels->empty())
					continue;

				_AudioInfo->getCodecs()[counter] = getAudioCodec(atrack->Format);
				if (atrack->BitRateMode == "VBR")
					_AudioInfo->getBitrateModes()[counter] = VBR;
				else
					_AudioInfo->getBitrateModes()[counter] = CBR;

				AudioTrackInfo *ati = new AudioTrackInfo();
				ati->setSourceFileName(_file);
				ati->setDefaultTrack(atrack->DefaultString->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("yes"));
				ati->setForcedTrack(atrack->ForcedString->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("yes"));
				// DGIndex expects audio index not ID for TS
				ati->setContainerType(info->General[0]->Format);
				ati->setTrackIndex(counter);
				int iID = 0;
				if (info->General[0]->Format == "CDXA/MPEG-PS")
					// MediaInfo doesn't give TrackID for VCD, specs indicate only MP1L2 is supported
					ati->setTrackID((0xC0 + counter));
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
				else if (atrack->ID != "0" && atrack->ID != "" && (int::TryParse(atrack->ID, iID) || (atrack->ID->Contains("-") && Int32::TryParse(atrack->ID->Split('-')[1], iID))))
					ati->setTrackID(iID);
				else
				{
					// MediaInfo failed to get ID try guessing based on codec
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//					switch (atrack.Format.Substring(0, 3))
//ORIGINAL LINE: case "AC-":
					if (atrack->Format->substr(0, 3) == "AC-" || atrack->Format->substr(0, 3) == "AC3")
					{
							ati->setTrackID((0x80 + counter));
					}
//ORIGINAL LINE: case "PCM":
					else if (atrack->Format->substr(0, 3) == "PCM")
					{
							ati->setTrackID((0xA0 + counter));
					}
//ORIGINAL LINE: case "MPE":
					else if (atrack->Format->substr(0, 3) == "MPE" || atrack->Format->substr(0, 3) == "MPA") // MPEG-1 Layer 1/2/3
					{
							ati->setTrackID((0xC0 + counter));
					}
//ORIGINAL LINE: case "DTS":
					else if (atrack->Format->substr(0, 3) == "DTS")
					{
							ati->setTrackID((0x88 + counter));
					}
				}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
				if (int::TryParse(atrack->StreamOrder, iID) || (atrack->StreamOrder->Contains("-") && Int32::TryParse(atrack->StreamOrder->Split('-')[1], iID)))
					ati->setMMGTrackID(iID);
				if (atrack->FormatProfile != "") // some tunings to have a more useful info instead of a typical audio Format
				{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//					switch (atrack.FormatProfile)
//ORIGINAL LINE: case "Dolby Digital":
					if (atrack->FormatProfile == "Dolby Digital")
					{
							ati->setCodec("AC-3");
					}
//ORIGINAL LINE: case "HRA / Core":
					else if (atrack->FormatProfile == "HRA / Core" || atrack->FormatProfile == "HRA")
					{
							ati->setCodec("DTS-HD High Resolution");
					}
//ORIGINAL LINE: case "Layer 1":
					else if (atrack->FormatProfile == "Layer 1")
					{
							ati->setCodec("MPA");
					}
//ORIGINAL LINE: case "Layer 2":
					else if (atrack->FormatProfile == "Layer 2")
					{
							ati->setCodec("MP2");
					}
//ORIGINAL LINE: case "Layer 3":
					else if (atrack->FormatProfile == "Layer 3")
					{
							ati->setCodec("MP3");
					}
//ORIGINAL LINE: case "LC":
					else if (atrack->FormatProfile == "LC")
					{
							ati->setCodec("AAC");
					}
//ORIGINAL LINE: case "MA":
					else if (atrack->FormatProfile == "MA" || atrack->FormatProfile == "MA / Core")
					{
							ati->setCodec("DTS-HD Master Audio");
					}
//ORIGINAL LINE: case "TrueHD":
					else if (atrack->FormatProfile == "TrueHD")
					{
							ati->setCodec("TrueHD");
					}
//ORIGINAL LINE: case "ES":
					else if (atrack->FormatProfile == "ES")
					{
							ati->setCodec("DTS-ES");
					}
					else
					{
							ati->setCodec(atrack->Format);
					}
				}
				else
					ati->setCodec(atrack->Format);
				ati->setNbChannels(atrack->ChannelsString);
				ati->setChannelPositions(atrack->ChannelPositionsString2);
				ati->setSamplingRate(atrack->SamplingRateString);
				int delay = 0;
				int::TryParse(atrack->Delay, delay);
				ati->setDelay(delay);
				// gets SBR/PS flag from AAC streams
				if (atrack->Format == "AAC")
				{
					ati->setAACFlag(0);
					if (atrack->FormatSettingsSBR == "Yes")
					{
						if (atrack->FormatSettingsPS == "Yes")
							ati->setAACFlag(2);
						else
							ati->setAACFlag(1);
					}
					if (atrack->SamplingRate == "24000")
					{
						if ((atrack->Channels == "2") || (atrack->Channels == "1")) // workaround for raw aac
							ati->setAACFlag(1);
					}
				}
				ati->setLanguage(atrack->LanguageString);
				_AudioInfo->getTracks().push_back(ati);
			}

			//subtitle detection
			int i = 0;
            for (QString::const_iterator oTextTrack = info->Text->begin(); oTextTrack != info->Text->end(); ++oTextTrack)
			{
				int mmgTrackID = 0;
				if (!int::TryParse((*oTextTrack)->StreamOrder, mmgTrackID) && (*oTextTrack)->StreamOrder->Contains("-"))
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					int::TryParse((*oTextTrack)->StreamOrder->Split('-')[1], mmgTrackID);
				SubtitleTrackInfo *oTrack = new SubtitleTrackInfo(mmgTrackID, (*oTextTrack)->LanguageString, (*oTextTrack)->Title);
				oTrack->setDefaultTrack((*oTextTrack)->DefaultString->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("yes"));
				oTrack->setForcedTrack((*oTextTrack)->ForcedString->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("yes"));
				oTrack->setSourceFileName(file);
				oTrack->setCodec((*oTextTrack)->CodecString);
				oTrack->setContainerType(_strContainer);
				oTrack->setTrackIndex(i++);
				int delay = 0;
				int::TryParse((*oTextTrack)->Delay, delay);
				oTrack->setDelay(delay);

				// only add supported subtitle tracks
                QString strCodec = oTrack->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture);
				if (cType == ContainerType::MKV)
				{
//ORIGINAL LINE: string[] arrCodec = new string[] { };
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    QString *arrCodec = new QString[] { };
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					arrCodec = strCodec.Split('/');
					if (arrCodec[0].substr(1, 1)->Equals("_"))
						arrCodec[0] = arrCodec[0].substr(2);
					strCodec = arrCodec[0];
				}
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//				switch (strCodec)
//ORIGINAL LINE: case "VOBSUB":
				if (strCodec == "VOBSUB" || strCodec == "ASS" || strCodec == "UTF-8" || strCodec == "SSA" || strCodec == "USF" || strCodec == "HDMV" || strCodec == "PGS")
				{
				}
				else
				{
						strCodec = "unknown";
				}

				if (!strCodec.Equals("unknown"))
					_SubtitleInfo->getTracks().push_back(oTrack);
			}

			// video detection
			_VideoInfo->HasVideo = (info->Video->Count > 0);
			if (_VideoInfo->HasVideo)
			{
				MediaInfoWrapper::VideoTrack *track = info->Video[0];
//				checked
					int _trackID = 0;
					int::TryParse(track->ID, _trackID);
					int _mmgTrackID = 0;
					int::TryParse(track->StreamOrder, _mmgTrackID);

					VideoTrackInfo *videoInfo = new VideoTrackInfo(_trackID, _mmgTrackID, track->LanguageString, track->Title, track->CodecString, track->Codec);
					videoInfo->setContainerType(_strContainer);
					_VideoInfo->setTrack(videoInfo);

					_VideoInfo->Width = static_cast<quint64>(easyParseInt(track->Width).Value);
					_VideoInfo->Height = static_cast<quint64>(easyParseInt(track->Height).Value);
					Nullable<int> tempVar = easyParseInt(track.FrameCount);
					_VideoInfo->FrameCount = static_cast<quint64>(tempVar::HasValue ? tempVar : 0);
					_VideoInfo->setScanType(track->ScanTypeString);
					_VideoInfo->setCodec(getVideoCodec(track->Codec));
					if (_VideoInfo->getCodec() == 0)
						_VideoInfo->setCodec(getVideoCodec(track->Format)); // sometimes codec info is not available, check the format then...
					_VideoInfo->setType(getVideoType(_VideoInfo->getCodec(), cType, file));
					_VideoInfo->DAR = Resolution::GetDAR(static_cast<int>(_VideoInfo->Width), static_cast<int>(_VideoInfo->Height), track->AspectRatio, easyParseDecimal(track->PixelAspectRatio), track->AspectRatioString);

					Nullable<double> tempVar2 = easyParseDouble(track.FrameRate);
					Nullable<double> fps = tempVar2::HasValue ? tempVar2 : easyParseDouble(track->FrameRateOriginal);
					if (!fps.HasValue)
					{
						fps = 23.976;
						if (infoLog == 0)
						{
							infoLog = MainForm::Instance->getLog()->Info("MediaInfo");
							infoLog->Info("File: " + _file);
							infoLog->Info("FrameRate: " + track->FrameRate);
							infoLog->Info("FrameRateOriginal: " + track->FrameRateOriginal);

						}
						infoLog->LogEvent("fps cannot be determined. 23.976 will be used as default.", Error);
					}
					_VideoInfo->FPS = static_cast<double>(fps);
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'checked' block
			}
			delete info;
		}
		catch (std::exception &ex)
		{
			if (oLog == 0)
				oLog = MainForm::Instance->getLog()->Info("MediaInfo");
			oLog->LogValue("MediaInfo - Unhandled Error", ex, Error);
		}
	}

    void MediaInfoFile::WriteSourceInformation(MediaInfo *oInfo, const QString &strFile, LogItem *infoLog)
	{
		try
		{
			// general track
			for (unknown::const_iterator t = oInfo->General.begin(); t != oInfo->General.end(); ++t)
			{
				LogItem *oTrack = new LogItem("General");

				oTrack->Info("Format: " + (*t)->Format);
				oTrack->Info("FormatString: " + (*t)->FormatString);
				oTrack->Info("FileSize: " + (*t)->FileSize);
				oTrack->Info("PlayTime: " + (*t)->PlayTimeString3);
				if (_VideoInfo->PGCCount > 0)
				{
					oTrack->Info("PGCCount: " + _VideoInfo->PGCCount);
					oTrack->Info("PGCNumber: " + _VideoInfo->PGCNumber);
				}

				infoLog->Add(oTrack);
			}

			// video track
			for (unknown::const_iterator t = oInfo->Video.begin(); t != oInfo->Video.end(); ++t)
			{
				LogItem *oTrack = new LogItem("Video");

				oTrack->Info("ID: " + (*t)->ID);
				oTrack->Info("StreamOrder: " + (*t)->StreamOrder);
				oTrack->Info("Width: " + (*t)->Width);
				oTrack->Info("Height: " + (*t)->Height);
				oTrack->Info("FrameCount: " + (*t)->FrameCount);
				oTrack->Info("FrameRate: " + (*t)->FrameRate);
				oTrack->Info("FrameRateOriginal: " + (*t)->FrameRateOriginal);
				oTrack->Info("FrameRateMode: " + (*t)->FrameRateMode);
				oTrack->Info("ScanType: " + (*t)->ScanTypeString);
				oTrack->Info("Codec: " + (*t)->Codec);
				oTrack->Info("CodecString: " + (*t)->CodecString);
				oTrack->Info("Bits Depth: " + (*t)->BitDepth);
				oTrack->Info("Format: " + (*t)->Format);
				oTrack->Info("AspectRatio: " + (*t)->AspectRatio);
				oTrack->Info("AspectRatioString: " + (*t)->AspectRatioString);
				oTrack->Info("Delay: " + (*t)->Delay);
				oTrack->Info("Title: " + (*t)->Title);
				oTrack->Info("Language: " + (*t)->Language);
				oTrack->Info("LanguageString: " + (*t)->LanguageString);
				oTrack->Info("Default: " + (*t)->Default);
				oTrack->Info("DefaultString: " + (*t)->DefaultString);
				oTrack->Info("Forced: " + (*t)->Forced);
				oTrack->Info("ForcedString: " + (*t)->ForcedString);

				infoLog->Add(oTrack);
			}

			// audio track
			for (unknown::const_iterator t = oInfo->Audio.begin(); t != oInfo->Audio.end(); ++t)
			{
				LogItem *oTrack = new LogItem("Audio");

				oTrack->Info("ID: " + (*t)->ID);
				oTrack->Info("StreamOrder: " + (*t)->StreamOrder);
				oTrack->Info("Format: " + (*t)->Format);
				oTrack->Info("FormatProfile: " + (*t)->FormatProfile);
				oTrack->Info("FormatSettingsSBR: " + (*t)->FormatSettingsSBR);
				oTrack->Info("FormatSettingsPS: " + (*t)->FormatSettingsPS);
				oTrack->Info("SamplingRate: " + (*t)->SamplingRate);
				oTrack->Info("SamplingRateString: " + (*t)->SamplingRateString);
				oTrack->Info("Channels: " + (*t)->Channels);
				oTrack->Info("ChannelsString: " + (*t)->ChannelsString);
				oTrack->Info("ChannelPositionsString2: " + (*t)->ChannelPositionsString2);
				oTrack->Info("BitRateMode: " + (*t)->BitRateMode);
				oTrack->Info("Delay: " + (*t)->Delay);
				oTrack->Info("Title: " + (*t)->Title);
				oTrack->Info("Language: " + (*t)->Language);
				oTrack->Info("LanguageString: " + (*t)->LanguageString);
				oTrack->Info("Default: " + (*t)->Default);
				oTrack->Info("DefaultString: " + (*t)->DefaultString);
				oTrack->Info("Forced: " + (*t)->Forced);
				oTrack->Info("ForcedString: " + (*t)->ForcedString);

				infoLog->Add(oTrack);
			}

			// text track
            for (QString::const_iterator t = oInfo->Text->begin(); t != oInfo->Text->end(); ++t)
			{
				LogItem *oTrack = new LogItem("Text");

				oTrack->Info("ID: " + (*t)->ID);
				oTrack->Info("StreamOrder: " + (*t)->StreamOrder);
				oTrack->Info("Codec: " + (*t)->Codec);
				oTrack->Info("CodecString: " + (*t)->CodecString);
				oTrack->Info("Delay: " + (*t)->Delay);
				oTrack->Info("Title: " + (*t)->Title);
				oTrack->Info("Language: " + (*t)->Language);
				oTrack->Info("LanguageString: " + (*t)->LanguageString);
				oTrack->Info("Default: " + (*t)->Default);
				oTrack->Info("DefaultString: " + (*t)->DefaultString);
				oTrack->Info("Forced: " + (*t)->Forced);
				oTrack->Info("ForcedString: " + (*t)->ForcedString);

				infoLog->Add(oTrack);
			}

			// chapter track
			for (unknown::const_iterator t = oInfo->Chapters.begin(); t != oInfo->Chapters.end(); ++t)
			{
				LogItem *oTrack = new LogItem("Chapters");

				oTrack->Info("ID: " + (*t)->ID);
				oTrack->Info("StreamOrder: " + (*t)->StreamOrder);
				oTrack->Info("Codec: " + (*t)->Codec);
				oTrack->Info("Inform: " + (*t)->Inform);
				oTrack->Info("Title: " + (*t)->Title);
				oTrack->Info("Language: " + (*t)->Language);
				oTrack->Info("LanguageString: " + (*t)->LanguageString);
				oTrack->Info("Default: " + (*t)->Default);
				oTrack->Info("DefaultString: " + (*t)->DefaultString);
				oTrack->Info("Forced: " + (*t)->Forced);
				oTrack->Info("ForcedString: " + (*t)->ForcedString);

				infoLog->Add(oTrack);
			}
		}
		catch (std::exception &ex)
		{
			infoLog->LogValue("Error parsing media file", ex, Information);
		}
	}

    void MediaInfoFile::CorrectSourceInformation(MediaInfo *&oInfo, const QString &strFile, LogItem *infoLog, int iPGCNumber)
	{
		try
		{
			if (oInfo->Video->Count > 0 && Path::GetExtension(strFile.ToLower(System::Globalization::CultureInfo::InvariantCulture)) == ".vob")
			{
                QString ifoFile;
				if (Path::GetFileName(strFile)->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->substr(0, 4) == "VTS_")
					ifoFile = strFile.substr(0, strFile.rfind("_")) + "_0.IFO";
				else
					ifoFile = Path::ChangeExtension(strFile, ".IFO");

				if (File::Exists(ifoFile))
				{
					// DVD Input File
					if (infoLog != 0)
						infoLog->Info("DVD source detected. Using IFO file: " + ifoFile);

					// PGC handling
					int iPGCCount = static_cast<int>(IFOparser::getPGCnb(ifoFile));
					_VideoInfo->PGCCount = iPGCCount;
					if (iPGCNumber < 1 || iPGCNumber > iPGCCount)
						_VideoInfo->PGCNumber = 1;
					else
						_VideoInfo->PGCNumber = iPGCNumber;

					// AR information may be false in VOB, use IFO instead
                    QString strResult = IFOparser::GetVideoAR(ifoFile);
					if (!strResult.empty())
						oInfo->Video[0]->AspectRatioString = strResult;

					// audio languages are not present in VOB, use IFO instead
					for (int counter = 0; counter < oInfo->Audio->Count; counter++)
					{
						MediaInfoWrapper::AudioTrack *atrack = oInfo->Audio[counter];
						if (atrack->LanguageString->empty())
							atrack->LanguageString = IFOparser::getAudioLanguage(ifoFile, counter);
					}

					// subtitle information is wrong in VOB, use IFO instead
					oInfo->Text->Clear();
//ORIGINAL LINE: string[] arrSubtitle = IFOparser.GetSubtitlesStreamsInfos(ifoFile, _VideoInfo.PGCNumber, false);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    QString *arrSubtitle = IFOparser::GetSubtitlesStreamsInfos(ifoFile, _VideoInfo->PGCNumber, false);
                    for (QString::const_iterator strSubtitle = arrSubtitle->begin(); strSubtitle != arrSubtitle->end(); ++strSubtitle)
					{
						TextTrack *oTextTrack = new TextTrack();
						oTextTrack->StreamOrder = StringConverterHelper::toString(int::Parse((*strSubtitle).substr(1, 2)));
//ORIGINAL LINE: string[] strLanguage = strSubtitle.Split('-');
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
                        QString *strLanguage = (*strSubtitle).Split('-');
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
						oTextTrack->LanguageString = strLanguage[1].Trim();
						if ((*strSubtitle).find('-', 7) > 0)
							oTextTrack->Title = (*strSubtitle).substr(7);
						if ((*strSubtitle).ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("force"))
							oTextTrack->ForcedString = "yes";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						oTextTrack->CodecString = SubtitleType::VOBSUB->ToString();
						oInfo->Text->Add(oTextTrack);
					}
				}
			}
			else if (oInfo->General[0]->FormatString->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("blu-ray playlist"))
			{
				// Blu-ray Input File
				if (infoLog != 0)
					infoLog->Info("Blu-ray playlist detected. Getting information from eac3to.");

                const QString tempVector[] = {strFile};
                _Eac3toInfo = new Eac3toInfo(QVector<QString>(tempVector, tempVector + sizeof(tempVector) / sizeof(tempVector[0])), this, infoLog);
				_Eac3toInfo->FetchAllInformation();

				int iAudioCount = 0;
				int iTextCount = 0;
				bool bVideoFound = false;
				int i = oInfo->Video->Count;
				for (unknown::const_iterator oTrack = _Eac3toInfo->getFeatures()[0]->Streams.begin(); oTrack != _Eac3toInfo->getFeatures()[0]->Streams.end(); ++oTrack)
				{
					if ((*oTrack)->getType() == eac3to::Subtitle)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						oInfo->Text[iTextCount++]->StreamOrder = (*oTrack)->getNumber()->ToString();
					else if ((*oTrack)->getType() == eac3to::Audio)
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						oInfo->Audio[iAudioCount]->ID = (*oTrack)->getNumber()->ToString();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						oInfo->Audio[iAudioCount++]->StreamOrder = (*oTrack)->getNumber()->ToString();
					}
					else if ((*oTrack)->getType() == eac3to::Video && !bVideoFound && !(*oTrack)->getName()->find("(right eye)") != string::npos)
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						oInfo->Video[0]->ID = (*oTrack)->getNumber()->ToString();
						bVideoFound = true;
					}
				}
				oInfo->Audio->RemoveRange(iAudioCount, oInfo->Audio->Count - iAudioCount);
				oInfo->Text->RemoveRange(iTextCount, oInfo->Text->Count - iTextCount);
			}
			else if (oInfo->Audio->Count == 0 && oInfo->Video->Count == 0 && Path::GetExtension(strFile)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".avs"))
			{
				// AVS Input File
				if (infoLog != 0)
					infoLog->Info("AVS input file detected. Getting media information from AviSynth.");

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (AvsFile avi = AvsFile.OpenScriptFile(strFile))
				AvsFile *avi = AvsFile::OpenScriptFile(strFile);
				try
				{
					MediaInfoWrapper::VideoTrack *oVideo = new MediaInfoWrapper::VideoTrack();
					MediaInfoWrapper::AudioTrack *oAudio = new MediaInfoWrapper::AudioTrack();

					oInfo->General[0]->Format = "AVS";
					oInfo->General[0]->FormatString = "AviSynth Script";
					if (avi->getClip()->getHasVideo() || avi->getClip()->getHasAudio())
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						oInfo->General[0]->PlayTimeString3 = (TimeSpan::FromMilliseconds((avi->getVideoInfo()->FrameCount / avi->getVideoInfo()->FPS) * 1000))->ToString();

					if (avi->getClip()->getHasVideo())
					{
						oVideo->ID = "0";
						oVideo->Width = StringConverterHelper::toString(avi->getVideoInfo()->Width);
						oVideo->Height = StringConverterHelper::toString(avi->getVideoInfo()->Height);
						oVideo->FrameCount = StringConverterHelper::toString(avi->getVideoInfo()->FrameCount);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						oVideo->FrameRate = avi->getVideoInfo()->FPS.ToString(culture);
						_VideoInfo->FPS_D = avi->getVideoInfo()->FPS_D;
						_VideoInfo->FPS_N = avi->getVideoInfo()->FPS_N;
						if (avi->getClip()->getinterlaced_frame() > 0)
							oVideo->ScanTypeString = "Interlaced";
						else
							oVideo->ScanTypeString = "Progressive";
						oVideo->Codec = "AVS Video";
						oVideo->CodecString = "AVS";
						oVideo->Format = "AVS";
						oVideo->AspectRatio = avi->getVideoInfo()->DAR.getX() + ":" + avi->getVideoInfo()->DAR.getY();
						oVideo->Delay = "0";
						oInfo->Video->Add(oVideo);
					}

					if (avi->getClip()->getHasAudio())
					{
						oAudio->ID = "0";
						oAudio->Format = "AVS";
						oAudio->SamplingRate = StringConverterHelper::toString(avi->getClip()->getAudioSampleRate());
						oAudio->SamplingRateString = StringConverterHelper::toString(avi->getClip()->getAudioSampleRate());
						oAudio->Channels = StringConverterHelper::toString(avi->getClip()->getChannelsCount());
						oAudio->ChannelsString = StringConverterHelper::toString(avi->getClip()->getChannelsCount()) + " channels";
						oAudio->ChannelPositionsString2 = AudioUtil::getChannelPositionsFromAVSFile(strFile);
						oAudio->BitRateMode = "CBR";
						oAudio->Delay = "0";
						oInfo->Audio->Add(oAudio);
					}
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (avi != 0)
						avi.Dispose();
				}
			}
		}
		catch (std::exception &ex)
		{
			if (infoLog == 0)
				infoLog = MainForm::Instance->getLog()->Info("MediaInfo");
			infoLog->LogValue("Error parsing media file " + strFile, ex.what(), Error);
		}
	}

	bool MediaInfoFile::hasMKVChapters()
	{
		if (cType != ContainerType::MKV)
			return false;

		if (_MkvInfo == 0)
			_MkvInfo = new MkvInfo(_file, _Log);

		return _MkvInfo->getHasChapters();
	}

	bool MediaInfoFile::MuxableToMKV()
	{
		if (cType == ContainerType::MKV)
			return true;

		if (_MkvInfo == 0)
			_MkvInfo = new MkvInfo(_file, _Log);

		return _MkvInfo->getIsMuxable();
	}

	int MediaInfoFile::getEac3toChaptersTrack()
	{
		if (!isEac3toDemuxable())
			return -1;

		if (_Eac3toInfo == 0)
		{
            const QString tempVector2[] = {_file};
            _Eac3toInfo = new Eac3toInfo(QVector<QString>(tempVector2, tempVector2 + sizeof(tempVector2) / sizeof(tempVector2[0])), this, _Log);
		}

		int iTrack = -1;
		for (unknown::const_iterator oTrack = _Eac3toInfo->getFeatures()[0]->Streams.begin(); oTrack != _Eac3toInfo->getFeatures()[0]->Streams.end(); ++oTrack)
		{
			if ((*oTrack)->getType() == eac3to::Chapter)
				iTrack = (*oTrack)->getNumber();
		}

		return iTrack;
	}

    bool MediaInfoFile::extractMKVChapters(const QString &strChapterFile)
	{
		if (cType != ContainerType::MKV)
			return false;

		if (_MkvInfo == 0)
			return false;

		return _MkvInfo->extractChapters(strChapterFile);
	}

	bool MediaInfoFile::isDGIIndexable()
	{
		// check if the file is a video file
		if (!_VideoInfo->HasVideo)
			return false;

		// check if the indexer and the license file are available
		if (!MainForm::Instance->getSettings()->IsDGIIndexerAvailable())
			return false;

		// only AVC, VC1 and MPEG2 are supported
		if (!_VideoInfo->getTrack()->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("AVC") && !_VideoInfo->getTrack()->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("VC-1") && !_VideoInfo->getTrack()->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-2 VIDEO"))
			return false;

		// only the following container formats are supported
		if (!_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MATROSKA") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-TS") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-PS") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG VIDEO") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-4") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("VC-1") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("AVC") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("BDAV") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("BLU-RAY PLAYLIST"))
			return false;

		return true;
	}

	bool MediaInfoFile::isD2VIndexable()
	{
		// check if the file is a video file
		if (!_VideoInfo->HasVideo)
			return false;

		// check if the indexer is available
		if (!File::Exists(MainForm::Instance->getSettings()->getDgIndexPath()))
			return false;

		// only MPEG1 and MPEG2 are supported
		if (!_VideoInfo->getTrack()->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-1 VIDEO") && !_VideoInfo->getTrack()->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-2 VIDEO"))
			return false;

		// only the following container formats are supported
		if (!_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-TS") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-PS") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG VIDEO") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("BDAV"))
			return false;

		return true;
	}

	bool MediaInfoFile::isDGAIndexable()
	{
		// check if the file is a video file
		if (!_VideoInfo->HasVideo)
			return false;

		// check if the indexer is available
		if (!File::Exists(MainForm::Instance->getSettings()->getDgavcIndexPath()))
			return false;

		// only AVC is supported
		if (!_VideoInfo->getTrack()->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("AVC"))
			return false;

		// only the following container formats are supported
		if (!_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-TS") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-PS") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG VIDEO") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("AVC") && !_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("BDAV"))
			return false;

		return true;
	}

	bool MediaInfoFile::isFFMSIndexable()
	{
		// check if the file is a video file
		if (!_VideoInfo->HasVideo)
			return false;

		// check if the indexer is available
		if (!File::Exists(MainForm::Instance->getSettings()->getFFMSIndexPath()))
			return false;

		// interlaced VC-1 is not supported
		if (_VideoInfo->getTrack()->getCodec().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("VC-1") && !_VideoInfo->getScanType().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("PROGRESSIVE"))
			return false;

		// some codecs are not supported by FFMS
		if (_VideoInfo->getTrack()->getCodecMediaInfo().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("DFSC/VFW") || _VideoInfo->getTrack()->getCodecMediaInfo().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("CFHD/CINEFORM"))
			return false;

		// only the following container formats are supported
		if (_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MATROSKA") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-TS") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-PS") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG VIDEO") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("AVI") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-4") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("FLASH VIDEO") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("OGG") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("WINDOWS MEDIA") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("BDAV") || _strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("BLU-RAY PLAYLIST"))
			return true;

		return false;
	}

	bool MediaInfoFile::isAVISourceIndexable(bool bStrictFilesOnly)
	{
		// check if the file is a video file
		if (!_VideoInfo->HasVideo)
			return false;

		// only the following container format is supported
		if (!_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("AVI"))
			return false;

		// if all AVI files should be processed or only the ones where FFMS cannot handle them
		if (!bStrictFilesOnly)
			return true;

		// some codecs are not supported by FFMS
		if (_VideoInfo->getTrack()->getCodecMediaInfo().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("DFSC/VFW") || _VideoInfo->getTrack()->getCodecMediaInfo().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("CFHD/CINEFORM"))
			return true;

		return false;
	}

	bool MediaInfoFile::recommendIndexer(FileIndexerWindow::IndexType &oType)
	{
		if (isDGIIndexable())
			oType = FileIndexerWindow::DGI;
		else if (isDGAIndexable())
			oType = FileIndexerWindow::DGA;
		else if (isD2VIndexable())
			oType = FileIndexerWindow::D2V;
		else if (isAVISourceIndexable(true))
			oType = FileIndexerWindow::AVISOURCE;
		else if (isFFMSIndexable())
			oType = FileIndexerWindow::FFMS;
		else
		{
			oType = FileIndexerWindow::FFMS;
			if (_indexerToUse == FileIndexerWindow::NONE)
				_indexerToUse = oType;
			return false;
		}
		if (_indexerToUse == FileIndexerWindow::NONE)
			_indexerToUse = oType;
		return true;
	}

    bool MediaInfoFile::recommendIndexer(QVector<QString> &arrIndexer)
	{
		FileIndexerWindow::IndexType oType = FileIndexerWindow::NONE;
        for (QVector<QString>::const_iterator strIndexer = arrIndexer.begin(); strIndexer != arrIndexer.end(); ++strIndexer)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if ((*strIndexer).Equals(FileIndexerWindow::FFMS->ToString()))
			{
				if (isFFMSIndexable())
				{
					oType = FileIndexerWindow::FFMS;
					break;
				}
				continue;
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			else if ((*strIndexer).Equals(FileIndexerWindow::DGI->ToString()))
			{
				if (isDGIIndexable())
				{
					oType = FileIndexerWindow::DGI;
					break;
				}
				continue;
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			else if ((*strIndexer).Equals(FileIndexerWindow::DGA->ToString()))
			{
				if (isDGAIndexable())
				{
					oType = FileIndexerWindow::DGA;
					break;
				}
				continue;
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			else if ((*strIndexer).Equals(FileIndexerWindow::D2V->ToString()))
			{
				if (isD2VIndexable())
				{
					oType = FileIndexerWindow::D2V;
					break;
				}
				continue;
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			else if ((*strIndexer).Equals(FileIndexerWindow::AVISOURCE->ToString()))
			{
				if (isAVISourceIndexable(false))
				{
					oType = FileIndexerWindow::AVISOURCE;
					break;
				}
				continue;
			}
		}

		if (oType != FileIndexerWindow::NONE)
		{
			if (_indexerToUse == FileIndexerWindow::NONE)
				_indexerToUse = oType;
			return true;
		}

		return recommendIndexer(oType);
	}

	const FileIndexerWindow::IndexType &MediaInfoFile::getIndexerToUse() const
	{
		return _indexerToUse;
	}

	void MediaInfoFile::setIndexerToUse(const FileIndexerWindow::IndexType &value)
	{
		_indexerToUse = value;
	}

	bool MediaInfoFile::isEac3toDemuxable()
	{
		// check if the indexer is available
		if (!File::Exists(MainForm::Instance->getSettings()->getEAC3toPath()))
			return false;

		// only the following container formats are supported
		if (_strContainer.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("BLU-RAY PLAYLIST"))
			return true;

		return false;
	}

    Nullable<int> MediaInfoFile::easyParseInt(const QString &value)
	{
		try
		{
			return (int::Parse(value, culture));
		}
		catch (std::exception &e1)
		{
			return 0;
		}
	}

    Nullable<double> MediaInfoFile::easyParseDouble(const QString &value)
	{
		try
		{
			return double::Parse(value, culture);
		}
		catch (std::exception &e1)
		{
			return 0;
		}
	}

    Nullable<decimal> MediaInfoFile::easyParseDecimal(const QString &value)
	{
		try
		{
			return decimal::Parse(value, culture);
		}
		catch (std::exception &e1)
		{
			return 0;
		}
	}

    ContainerType *MediaInfoFile::getContainerType(const QString &codec, const QString &description)
	{
		if (knownContainerTypes.find(codec) != knownContainerTypes.end())
			return knownContainerTypes[codec];
		description = description.ToLower(System::Globalization::CultureInfo::InvariantCulture);
        for (QMap<QString, ContainerType*>::const_iterator knownDescription = knownContainerDescriptions.begin(); knownDescription != knownContainerDescriptions.end(); ++knownDescription)
			if (description.find(knownDescription->first) != string::npos)
				return knownContainerDescriptions[knownDescription->first];
		return 0;
	}

    AudioCodec *MediaInfoFile::getAudioCodec(const QString &description)
	{
		description = description.ToLower(System::Globalization::CultureInfo::InvariantCulture);
        for (QMap<QString, AudioCodec*>::const_iterator knownDescription = knownAudioDescriptions.begin(); knownDescription != knownAudioDescriptions.end(); ++knownDescription)
			if (description.find(knownDescription->first) != string::npos)
				return knownAudioDescriptions[knownDescription->first];
		return 0;
		;
	}

    VideoCodec *MediaInfoFile::getVideoCodec(const QString &description)
	{
		description = description.ToLower(System::Globalization::CultureInfo::InvariantCulture);
        for (QMap<QString, VideoCodec*>::const_iterator knownDescription = knownVideoDescriptions.begin(); knownDescription != knownVideoDescriptions.end(); ++knownDescription)
			if (description.find(knownDescription->first) != string::npos)
				return knownVideoDescriptions[knownDescription->first];
		return 0;
	}

    VideoType *MediaInfoFile::getVideoType(VideoCodec *codec, ContainerType *cft, const QString &filename)
	{
        QString extension = Path::GetExtension(filename)->ToLower(System::Globalization::CultureInfo::InvariantCulture);
		for (MeXgui::GenericRegisterer<VideoType*>::const_iterator t = ContainerManager::VideoTypes->begin(); t != ContainerManager::VideoTypes->end(); ++t)
		{
			if (t->second->ContainerType == cft && Array->find<VideoCodec*>(t->second->SupportedCodecs, codec) >= 0 && "." + t->second->Extension == extension)
				return t->second;
		}
		return 0;
	}

    AudioType *MediaInfoFile::getAudioType(AudioCodec *codec, ContainerType *cft, const QString &filename)
	{
        QString extension = Path::GetExtension(filename)->ToLower(System::Globalization::CultureInfo::InvariantCulture);
		ContainerType *type = 0;
		if (cft != 0)
			type = cft;
		for (MeXgui::GenericRegisterer<AudioType*>::const_iterator t = ContainerManager::AudioTypes->begin(); t != ContainerManager::AudioTypes->end(); ++t)
		{
			if (t->second->ContainerType == type && Array->find<AudioCodec*>(t->second->SupportedCodecs, codec) >= 0 && "." + t->second->Extension == extension)
				return t->second;
		}
		return 0;
	}

	MediaInfoFile::MediaInfoFile()
	{
        knownVideoDescriptions = QMap<QString, VideoCodec*>();

		knownVideoDescriptions.insert(make_pair("divx 5", VideoCodec::ASP));
		knownVideoDescriptions.insert(make_pair("divx 4", VideoCodec::ASP));
		knownVideoDescriptions.insert(make_pair("divx 6", VideoCodec::ASP));
		knownVideoDescriptions.insert(make_pair("3ivx", VideoCodec::ASP));
		knownVideoDescriptions.insert(make_pair("xvid", VideoCodec::ASP));
		knownVideoDescriptions.insert(make_pair("asp", VideoCodec::ASP));
		knownVideoDescriptions.insert(make_pair("mpeg-4 adv simple", VideoCodec::ASP));
		knownVideoDescriptions.insert(make_pair("avc", VideoCodec::AVC));
		knownVideoDescriptions.insert(make_pair("h264", VideoCodec::AVC));
		knownVideoDescriptions.insert(make_pair("h.264", VideoCodec::AVC));
		knownVideoDescriptions.insert(make_pair("huffman", VideoCodec::HFYU));
		knownVideoDescriptions.insert(make_pair("ffvh", VideoCodec::HFYU));
		knownVideoDescriptions.insert(make_pair("mpeg-4v", VideoCodec::ASP));
		knownVideoDescriptions.insert(make_pair("vc-1", VideoCodec::VC1));
		knownVideoDescriptions.insert(make_pair("mpeg-2v", VideoCodec::MPEG2));

        knownAudioDescriptions = QMap<QString, AudioCodec*>();
		knownAudioDescriptions.insert(make_pair("aac", AudioCodec::AAC));
		knownAudioDescriptions.insert(make_pair("ac3", AudioCodec::AC3));
		knownAudioDescriptions.insert(make_pair("ac-3", AudioCodec::AC3));
		knownAudioDescriptions.insert(make_pair("dts", AudioCodec::DTS));
		knownAudioDescriptions.insert(make_pair("vorbis", AudioCodec::VORBIS));
		knownAudioDescriptions.insert(make_pair(" l3", AudioCodec::MP3));
		knownAudioDescriptions.insert(make_pair("mpeg-2 audio", AudioCodec::MP2));
		knownAudioDescriptions.insert(make_pair("mpeg-4 audio", AudioCodec::AAC));
		knownAudioDescriptions.insert(make_pair("flac", AudioCodec::FLAC));

        knownContainerTypes = QMap<QString, ContainerType*>();
		knownContainerTypes.insert(make_pair("AVI", ContainerType::AVI));
		knownContainerTypes.insert(make_pair("Matroska", ContainerType::MKV));
		knownContainerTypes.insert(make_pair("MPEG-4", ContainerType::MP4));
		knownContainerTypes.insert(make_pair("3GPP", ContainerType::MP4));
		knownContainerTypes.insert(make_pair("BDAV", ContainerType::M2TS));

        knownContainerDescriptions = QMap<QString, ContainerType*>();
	}

	const bool &MediaInfoFile::getHasAudio() const
	{
		return (_AudioInfo->HasAudio());
	}

	const bool &MediaInfoFile::getHasVideo() const
	{
		return _VideoInfo->HasVideo;
	}

	const bool &MediaInfoFile::getCanReadVideo() const
	{
		return true;
	}

	const bool &MediaInfoFile::getCanReadAudio() const
	{
		return false;
	}

	IVideoReader *MediaInfoFile::GetVideoReader()
	{
		if (!getVideoInfo()->HasVideo || !getCanReadVideo())
			throw std::exception("Can't read the video stream");
		if (videoSourceFile == 0 || videoReader == 0)
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			lock (this)
			{
				if (videoSourceFile == 0)
				{
					videoSourceFile = AvsFile::ParseScript(ScriptServer::GetInputLine(_file, 0, false, directShow, false, false, false, getVideoInfo()->FPS, false));
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete videoReader;
				}
				if (videoReader == 0)
				{
					videoReader = videoSourceFile->GetVideoReader();
				}
			}
		return videoReader;
	}

	IAudioReader *MediaInfoFile::GetAudioReader(int track)
	{
		throw std::exception("The method or operation is not implemented.");
	}

    const QString &MediaInfoFile::getFileName() const
	{
		return _file;
	}

	MediaInfoFile::~MediaInfoFile()
	{
		InitializeInstanceFields();
		if (videoSourceFile != 0)
		{
			delete videoSourceFile;
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete videoSourceFile;
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete videoReader;
		}
	}

	void MediaInfoFile::InitializeInstanceFields()
	{
		delete videoSourceFile;
		delete videoReader;
		_strContainer = "";
	}

	VideoInformation::VideoInformation(bool hasVideo, quint64 width, quint64 height, Dar dar, quint64 frameCount, double fps, int fps_n, int fps_d)
	{
		HasVideo = hasVideo;
		Width = width;
		Height = height;
		DAR = dar;
		FrameCount = frameCount;
		FPS = fps;
		FPS_N = fps_n;
		FPS_D = fps_d;
		PGCCount = 0;
		PGCNumber = 0;
	}

	const VideoTrackInfo &VideoInformation::getTrack() const
	{
		return _videoInfo;
	}

	void VideoInformation::setTrack(const VideoTrackInfo &value)
	{
		_videoInfo = value;
	}

    const QString &VideoInformation::getScanType() const
	{
		return _strVideoScanType;
	}

    void VideoInformation::setScanType(const QString &value)
	{
		_strVideoScanType = value;
	}

	const VideoType &VideoInformation::getType() const
	{
		return _vType;
	}

	void VideoInformation::setType(const VideoType &value)
	{
		_vType = value;
	}

	const VideoCodec &VideoInformation::getCodec() const
	{
		return _vCodec;
	}

	void VideoInformation::setCodec(const VideoCodec &value)
	{
		_vCodec = value;
	}

	VideoInformation *VideoInformation::Clone()
	{
		return static_cast<VideoInformation*>(this->MemberwiseClone());
	}

	AudioInformation::AudioInformation()
	{
		InitializeInstanceFields();
		_aCodecs = new AudioCodec[]{};
	}

	const AudioType &AudioInformation::getType() const
	{
		return _aType;
	}

	void AudioInformation::setType(const AudioType &value)
	{
		_aType = value;
	}

	const AudioCodec &AudioInformation::getCodecs() const
	{
		return _aCodecs;
	}

	void AudioInformation::setCodecs(const AudioCodec &value[])
	{
		_aCodecs = value;
	}

	const BitrateManagementMode &AudioInformation::getBitrateModes() const
	{
		return _aBitrateModes;
	}

	void AudioInformation::setBitrateModes(const BitrateManagementMode &value[])
	{
		_aBitrateModes = value;
	}

	const QVector<AudioTrackInfo*> &AudioInformation::getTracks() const
	{
		return _arrAudioTracks;
	}

	void AudioInformation::setTracks(const QVector<AudioTrackInfo*> &value)
	{
		_arrAudioTracks = value;
	}

	int AudioInformation::GetFirstTrackID()
	{
		// check if the file contains a video audio track
		if (sizeof(_aCodecs) / sizeof(_aCodecs[0]) == 0)
			return 0;

		return _arrAudioTracks[0]->getMMGTrackID();
	}

	bool AudioInformation::HasAudio()
	{
		if (_aCodecs != 0 && sizeof(_aCodecs) / sizeof(_aCodecs[0]) > 0)
			return true;
		return false;
	}

	VideoInformation *AudioInformation::Clone()
	{
		return static_cast<VideoInformation*>(this->MemberwiseClone());
	}

	void AudioInformation::InitializeInstanceFields()
	{
		_arrAudioTracks = QVector<AudioTrackInfo*>();
	}

	SubtitleInformation::SubtitleInformation()
	{

		InitializeInstanceFields();
	}

	const QVector<SubtitleTrackInfo*> &SubtitleInformation::getTracks() const
	{
		return _arrSubtitleTracks;
	}

	void SubtitleInformation::setTracks(const QVector<SubtitleTrackInfo*> &value)
	{
		_arrSubtitleTracks = value;
	}

	int SubtitleInformation::GetFirstTrackID()
	{
		// check if the file is a subtitle file
		if (_arrSubtitleTracks.empty())
			return 0;
		return _arrSubtitleTracks[0]->getMMGTrackID();
	}

	VideoInformation *SubtitleInformation::Clone()
	{
		return static_cast<VideoInformation*>(this->MemberwiseClone());
	}

	void SubtitleInformation::InitializeInstanceFields()
	{
		_arrSubtitleTracks = QVector<SubtitleTrackInfo*>();
	}
}
