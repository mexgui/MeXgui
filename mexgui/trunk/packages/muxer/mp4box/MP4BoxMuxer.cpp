#include "MP4BoxMuxer.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{

JobProcessorFactory *const MP4BoxMuxer::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "MP4BoxMuxer");

	IJobProcessor *MP4BoxMuxer::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<MuxJob*>(j) != 0 && (dynamic_cast<MuxJob*>(j))->getMuxType() == MP4BOX)
			return new MP4BoxMuxer(mf->getSettings()->getMp4boxPath());
		return 0;
	}

	MP4BoxMuxer::MP4BoxMuxer(const std::string &executablePath)
	{
		this->executable = executablePath;
		trackNumber = 0;
		lastLine = "";
	}

	void MP4BoxMuxer::checkJobIO()
	{
		this->numberOfAudioTracks = job->getSettings()->getAudioStreams().size();
		this->numberOfSubtitleTracks = job->getSettings()->getSubtitleStreams().size();

		CommandlineMuxer::checkJobIO();
	}

	MeGUI::MP4BoxMuxer::LineType MP4BoxMuxer::getLineType(const std::string &line)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("Importing"))
			return importing;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("ISO File Writing"))
			return writing;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("Splitting"))
			return splitting;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("TTXT Loading"))
			return empty;
		if (isEmptyLine(line))
			return empty;
		return other;
	}

	void MP4BoxMuxer::ProcessLine(const std::string &line, StreamType stream, ImageType oType)
	{
		switch (getLineType(line))
		{
			case empty:
				if (getLineType(lastLine) == importing) // moving from one track to another
					trackNumber++;
				break;
			case importing:
				su->setPercentageDoneExact(getPercentage(line));
				if (trackNumber == 1) // video
				{
					if (su->getStatus().empty() || !su->getStatus().Equals("Importing Video Track..."))
					{
						su->setStatus("Importing Video Track...");
						startTime = DateTime::Now;
					}
				}
				else if (trackNumber == 2 && numberOfAudioTracks > 0) // first audio track
				{
					if (su->getStatus().empty() || !su->getStatus().Equals("Importing Audio Track 1..."))
					{
						su->setStatus("Importing Audio Track 1...");
						startTime = DateTime::Now;
					}
				}
				else if (trackNumber == 3 && numberOfAudioTracks > 1) // second audio track
				{
					if (su->getStatus().empty() || !su->getStatus().Equals("Importing Audio Track 2..."))
					{
						su->setStatus("Importing Audio Track 2...");
						startTime = DateTime::Now;
					}
				}
				else
				{
					if (su->getStatus().empty() || !su->getStatus().Equals("Importing Tracks..."))
					{
						su->setStatus("Importing Tracks...");
						startTime = DateTime::Now;
					}
				}
				break;

			case splitting:
				su->setPercentageDoneExact(getPercentage(line));
				su->setStatus("Splitting...");
				break;

			case writing:
				su->setPercentageDoneExact(getPercentage(line));
				if (su->getStatus().empty() || !su->getStatus().Equals("Writing..."))
				{
					su->setStatus("Writing...");
					startTime = DateTime::Now;
				}
				break;

			case other:
				CommandlineMuxer::ProcessLine(line, stream, oType);
				break;
		}
		lastLine = line;
	}

	Nullable<decimal> MP4BoxMuxer::getPercentage(const std::string &line)
	{
		try
		{
			int start = line.find("(") + 1;
			int end = line.find("/");
			std::string perc = line.substr(start, end - start);
			int percentage = int::Parse(perc);
			return percentage;
		}
		catch (std::exception &e)
		{
			log->LogValue("Exception in getPercentage(" + line + ") ", e, Warning);
			return 0;
		}
	}

	bool MP4BoxMuxer::isEmptyLine(const std::string &line)
	{
//ORIGINAL LINE: char[] characters = line.ToCharArray();
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		wchar_t *characters = line.ToCharArray();
		bool isEmpty = true;
		for (wchar_t::const_iterator c = characters->begin(); c != characters->end(); ++c)
		{
			if (*c != 32)
			{
				isEmpty = false;
				break;
			}
		}
		return isEmpty;
	}

	void MP4BoxMuxer::printStatistics()
	{
		try
		{
			FileSize len = FileSize::Of(job->Output);
			FileSize Empty = FileSize::Empty;
			if (!Path::GetExtension(job->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".mp4"))
			{
				FileSize rawSize = FileSize::Of(job->Input);
				LogItem *i = new LogItem("MP4 Muxing statistics");
				i->LogValue("Size of raw video stream", rawSize);
				i->LogValue("Size of final MP4 file", len);
				i->LogValue("Codec", job->getCodec());
				i->LogValue("Number of b-frames", job->getNbOfBFrames());
				i->LogValue("Number of source frames", job->getNbOfFrames());
				log->Add(i);
			}
		}
		catch (std::exception &e)
		{
			log->LogValue("An exception occurred when printing mux statistics", e, Warning);
		}
	}

	const std::string &MP4BoxMuxer::getCommandline() const
	{
		MuxSettings *settings = job->getSettings();
		CultureInfo *ci = new CultureInfo("en-us");
		StringBuilder *sb = new StringBuilder();

		if (!settings->getVideoInput().empty() || !settings->getMuxedInput().empty())
		{
			std::string strInput;
			if (!settings->getVideoInput().empty())
				strInput = settings->getVideoInput();
			else
				strInput = settings->getMuxedInput();

			if (settings->getDeviceType() != "Standard")
			{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//				switch (settings.DeviceType)
//ORIGINAL LINE: case "iPod":
				if (settings->getDeviceType() == "iPod")
				{
						sb->Append("-ipod -brand M4V  ");
				}
//ORIGINAL LINE: case "iPhone":
				else if (settings->getDeviceType() == "iPhone")
				{
						sb->Append("-ipod -brand M4VP:1 ");
				}
//ORIGINAL LINE: case "iPad":
				else if (settings->getDeviceType() == "iPad" || settings->getDeviceType() == "Apple TV")
				{
						sb->Append("-ipod -brand M4VH ");
				}
//ORIGINAL LINE: case "ISMA":
				else if (settings->getDeviceType() == "ISMA")
				{
						sb->Append("-isma ");
				}
//ORIGINAL LINE: case "PSP":
				else if (settings->getDeviceType() == "PSP")
				{
						sb->Append("-psp ");
				}
			}

			MediaInfoFile *oVideoInfo = new MediaInfoFile(strInput, log);
			sb->Append("-add \"" + strInput);

			int trackID = 1;
			if (oVideoInfo->getHasVideo() && oVideoInfo->getContainerFileType() == ContainerType::MP4)
				trackID = oVideoInfo->getVideoInfo()->getTrack()->getTrackID();
			sb->Append("#trackID=" + trackID);

			if (settings->getFramerate().HasValue)
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				std::string fpsString = settings->getFramerate().Value->ToString(ci);
				sb->Append(":fps=" + fpsString);
			}
			if (!settings->getVideoName().empty())
				sb->Append(":name=" + settings->getVideoName());
			else
				sb->Append(":name="); // to erase the default GPAC string
			sb->Append("\"");
		}
		int trackCount = 0;
		for (std::vector<MuxStream*>::const_iterator o = settings->getAudioStreams().begin(); o != settings->getAudioStreams().end(); ++o)
		{
			MuxStream *stream = static_cast<MuxStream*>(*o);
			MediaInfoFile *oInfo = new MediaInfoFile(stream->path, log);

			if (!oInfo->getHasAudio())
			{
				log->Error("No audio track found: " + stream->path);
				continue;
			}

			sb->Append(" -add \"" + stream->path);

			int trackID = 1;
			int heaac_flag = -1;
			if (oInfo->getAudioInfo()->getTracks().size() > 0)
			{
				if (oInfo->getContainerFileType() == ContainerType::MP4)
					trackID = oInfo->getAudioInfo()->getTracks()[0]->getTrackID();
				heaac_flag = oInfo->getAudioInfo()->getTracks()[0]->getAACFlag();
			}
			sb->Append("#trackID=" + trackID);

			if (oInfo->getContainerFileType() == ContainerType::MP4 || oInfo->getAudioInfo()->getCodecs()[0] == AudioCodec::AAC)
			{
				switch (heaac_flag)
				{
					case 1:
						sb->Append(":sbr");
						break;
					case 2:
						sb->Append(":ps");
						break;
					default:
						sb->Append("");
						break;
				}
			}
			if (!stream->getlanguage().empty())
			{
				for (std::map<std::string, std::string>::const_iterator strLanguage = LanguageSelectionContainer::getLanguagesTerminology().begin(); strLanguage != LanguageSelectionContainer::getLanguagesTerminology().end(); ++strLanguage)
				{
					if (stream->getlanguage().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
					{
						sb->Append(":lang=" + LanguageSelectionContainer::getISO639dot1(strLanguage->second));
						break;
					}
				}
			}
			if (!stream->getname().empty())
				sb->Append(":name=" + stream->getname());
			if (stream->delay != 0)
				sb->AppendFormat(":delay={0}", stream->delay);
			if (settings->getDeviceType() == "iPod" || settings->getDeviceType() == "iPhone" || settings->getDeviceType() == "iPad" || settings->getDeviceType() == "Apple TV")
			{
				sb->Append(":group=1");
				if (trackCount > 0)
					sb->Append(":disable");
			}
			if (stream->getname().empty())
				sb->Append(":name="); // to erase the default GPAC string
			sb->Append("\"");
			trackCount++;
		}
		trackCount = 0;
		for (std::vector<MuxStream*>::const_iterator o = settings->getSubtitleStreams().begin(); o != settings->getSubtitleStreams().end(); ++o)
		{
			MuxStream *stream = static_cast<MuxStream*>(*o);
			bool ttxtFFound = false;

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if (Path::GetExtension(stream->path)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith("ttxt"))
			{
				ttxtReader *ttxtFile = new ttxtReader(stream->path);
				ttxtFFound = ttxtFile->readFileProperties(stream->path);
				if (ttxtFFound)
					sb->Append(" -add \"" + stream->path + "#trackID=1");
			}
			else
			{
				sb->Append(" -add \"" + stream->path + "#trackID=1");
			}
			if (!stream->getlanguage().empty())
			{
				for (std::map<std::string, std::string>::const_iterator strLanguage = LanguageSelectionContainer::getLanguagesTerminology().begin(); strLanguage != LanguageSelectionContainer::getLanguagesTerminology().end(); ++strLanguage)
				{
					if (stream->getlanguage().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
					{
						sb->Append(":lang=" + LanguageSelectionContainer::getISO639dot1(strLanguage->second));
						break;
					}
				}
			}
			if (!stream->getname().empty())
				sb->Append(":name=" + stream->getname());
			if (settings->getDeviceType() == "iPod" || settings->getDeviceType() == "iPhone" || settings->getDeviceType() == "iPad" || settings->getDeviceType() == "Apple TV")
			{
				sb->Append(":hdlr=sbtl:layout=-1:group=2");
				if (trackCount > 0)
					sb->Append(":disable");
			}
			if (stream->getname().empty())
				sb->Append(":name="); // to erase the default GPAC string
			sb->Append("\"");
			trackCount++;
		}

		if (!settings->getChapterFile().empty())
		{
			// Add Apple Devices Chapter format
			if (settings->getDeviceType() == "iPod" || settings->getDeviceType() == "iPhone" || settings->getDeviceType() == "iPad" || settings->getDeviceType() == "Apple TV")
			{
				FileUtil::CreateXMLFromOGGChapFile(settings->getChapterFile());
				sb->Append(" -add \"" + Path::Combine(Path::GetDirectoryName(settings->getChapterFile()), Path::GetFileNameWithoutExtension(settings->getChapterFile()) + ".xml:name=:chap") + "\"");
				job->FilesToDelete.push_back(Path::GetFileNameWithoutExtension(settings->getChapterFile()) + ".xml");
			}
			else
			// Add Nero Style Chapters - this doesn't break Apple Devices playback  - just for better interoperability with other tools
			sb->Append(" -chap \"" + settings->getChapterFile() + "\"");

		}

		if (settings->getSplitSize().HasValue)
			sb->Append(" -splits " + settings->getSplitSize().Value::KB);

		// tmp directory
		if (!MainForm::Instance->getSettings()->getTempDirMP4().empty() && Directory::Exists(MainForm::Instance->getSettings()->getTempDirMP4()))
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
			sb->AppendFormat(" -tmp \"{0}\"", MainForm::Instance->getSettings()->getTempDirMP4().Replace("\\","\\\\"));
		else if (!Path::GetPathRoot(settings->getMuxedOutput())->Equals(settings->getMuxedOutput(), StringComparison::CurrentCultureIgnoreCase))
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
			sb->AppendFormat(" -tmp \"{0}\"", Path::GetDirectoryName(settings->getMuxedOutput())->Replace("\\", "\\\\"));

		if (settings->getDeviceType() == "iPod" || settings->getDeviceType() == "iPhone" || settings->getDeviceType() == "iPad" || settings->getDeviceType() == "Apple TV")
		{
			if (!settings->getVideoInput().empty())
				settings->setMuxedOutput(Path::ChangeExtension(settings->getMuxedOutput(), ".m4v"));
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if (settings->getVideoInput().empty() && !(settings->getAudioStreams().ToString())->empty())
				settings->setMuxedOutput(Path::ChangeExtension(settings->getMuxedOutput(), ".m4a"));
		}

		// force to create a new output file
		sb->Append(" -new \"" + settings->getMuxedOutput() + "\"");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}
}
