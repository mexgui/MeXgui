#include "tsMuxeR.h"

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
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace MediaInfoWrapper;

namespace MeGUI
{

JobProcessorFactory *const tsMuxeR::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "TSMuxer");

	IJobProcessor *tsMuxeR::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<MuxJob*>(j) != 0 && (dynamic_cast<MuxJob*>(j))->getMuxType() == TSMUXER)
			return new tsMuxeR(mf->getSettings()->getTSMuxerPath());
		return 0;
	}

	tsMuxeR::tsMuxeR(const std::string &executablePath)
	{
		InitializeInstanceFields();
		this->executable = executablePath;
	}

	void tsMuxeR::checkJobIO()
	{
		this->numberOfAudioTracks = job->getSettings()->getAudioStreams().size();
		this->numberOfSubtitleTracks = job->getSettings()->getSubtitleStreams().size();
		generateMetaFile();
		Util::ensureExists(metaFile);
		CommandlineMuxer::checkJobIO();
	}

	void tsMuxeR::setProjectedFileSize()
	{
	}

	const std::string &tsMuxeR::getCommandline() const
	{
		return " \"" + metaFile + "\"" + " \"" + job->Output + "\"";
	}

	void tsMuxeR::ProcessLine(const std::string &line, StreamType stream, ImageType oType)
	{
		if (Regex::IsMatch(line, "^[0-9]{1,3}\\.[0-9]{1}%", RegexOptions::Compiled))
		{
			su->setPercentageDoneExact(getPercentage(line));
			return;
		}

		if (stream == Stderr || line.ToLowerInvariant()->Contains("error"))
			oType = Error;
		else if (line.ToLowerInvariant()->Contains("warning"))
			oType = Warning;
		CommandlineMuxer::ProcessLine(line, stream, oType);
	}

	Nullable<decimal> tsMuxeR::getPercentage(const std::string &line)
	{
		try
		{
//ORIGINAL LINE: string[] strPercentage = line.Split('%')[0].Split('.');
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			std::string *strPercentage = line.Split('%')[0]->Split('.');
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to this .NET Convert class method:
			return Convert::ToDecimal(strPercentage[0]) + Convert::ToDecimal(strPercentage[1]) / 10;
		}
		catch (std::exception &e)
		{
			log->LogValue("Exception in getPercentage(" + line + ")", e, MeGUI::core::util::Warning);
			return 0;
		}
	}

	bool tsMuxeR::isEmptyLine(const std::string &line)
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

	void tsMuxeR::generateMetaFile()
	{
		metaFile = Path::ChangeExtension(job->Output, ".meta");
		MuxSettings *settings = job->getSettings();
		CultureInfo *ci = new CultureInfo("en-us");

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (StreamWriter sw = new StreamWriter(metaFile, false, Encoding.Default))
		StreamWriter *sw = new StreamWriter(metaFile, false, Encoding::Default);
		try
		{
			std::string vcodecID = "";
			std::string extra = "";

			sw->Write("MUXOPT --no-pcr-on-video-pid --new-audio-pes"); // mux options
			if (!settings->getDeviceType().empty() && settings->getDeviceType() != "Standard")
			{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//				switch (settings.DeviceType)
//ORIGINAL LINE: case "Blu-ray":
				if (settings->getDeviceType() == "Blu-ray")
				{
						sw->Write(" --blu-ray");
				}
//ORIGINAL LINE: case "AVCHD":
				else if (settings->getDeviceType() == "AVCHD")
				{
						sw->Write(" --avchd");
				}

				if (!settings->getChapterFile().empty()) // a chapter file is defined
				{
					std::string chapterTimeLine = VideoUtil::getChapterTimeLine(settings->getChapterFile());
					sw->Write(" --custom-chapters" + chapterTimeLine);
				}

				job->Output = Path::GetDirectoryName(job->Output) + "\\" + Path::GetFileNameWithoutExtension(job->Output); // remove m2ts file extension - use folder name only with this mode
			}
			sw->Write(" --vbr --vbv-len=500"); // mux options
			if (settings->getSplitSize().HasValue)
				sw->Write(" --split-size=" + settings->getSplitSize().Value::MB + "MB");

			MediaInfoFile *oVideoInfo = 0;
			if (!settings->getVideoInput().empty())
			{
				oVideoInfo = new MediaInfoFile(settings->getVideoInput(), log);
				if (!oVideoInfo->getHasVideo())
					log->Error("No video track found: " + settings->getVideoInput());
				else
				{
					if (oVideoInfo->getVideoInfo()->getCodec() == VideoCodec::AVC)
					{
						vcodecID = "V_MPEG4/ISO/AVC";
						extra = " insertSEI, contSPS";
						if (oVideoInfo->getContainerFileType() == ContainerType::MP4)
							extra += " , track=1";
					}
					else if (oVideoInfo->getVideoInfo()->getCodec() == VideoCodec::MPEG2)
						vcodecID = "V_MPEG-2";
					else if (oVideoInfo->getVideoInfo()->getCodec() == VideoCodec::VC1)
						vcodecID = "V_MS/VFW/WVC1";
				}
				sw->Write("\n" + vcodecID + ", ");

				sw->Write("\"" + settings->getVideoInput() + "\"");
			}
			else if (!settings->getMuxedInput().empty())
			{
				oVideoInfo = new MediaInfoFile(settings->getMuxedInput(), log);
				if (!oVideoInfo->getHasVideo())
					log->Error("No video track found: " + settings->getMuxedInput());
				else
				{
					if (oVideoInfo->getVideoInfo()->getCodec() == VideoCodec::AVC)
					{
						vcodecID = "V_MPEG4/ISO/AVC";
						extra = " insertSEI, contSPS";
						if (oVideoInfo->getContainerFileType() == ContainerType::MP4)
							extra += " , track=1";
					}
					else if (oVideoInfo->getHasVideo() && oVideoInfo->getVideoInfo()->getCodec() == VideoCodec::MPEG2)
						vcodecID = "V_MPEG-2";
					else if (oVideoInfo->getHasVideo() && oVideoInfo->getVideoInfo()->getCodec() == VideoCodec::VC1)
						vcodecID = "V_MS/VFW/WVC1";
				}
				sw->Write(vcodecID + ", ");

				sw->Write("\"" + settings->getMuxedInput() + "\"");
			}

			if (settings->getFramerate().HasValue)
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				std::string fpsString = settings->getFramerate().Value->ToString(ci);
				sw->Write(", fps=" + fpsString);
			}

			if (extra != "")
				sw->Write(" ," + extra);

			for (std::vector<MuxStream*>::const_iterator o = settings->getAudioStreams().begin(); o != settings->getAudioStreams().end(); ++o)
			{
				MuxStream *stream = static_cast<MuxStream*>(*o);
				std::string acodecID = "";

				MediaInfoFile *oInfo = new MediaInfoFile(stream->path, log);

				if (!oInfo->getHasAudio())
				{
					log->Error("No audio track found: " + stream->path);
					continue;
				}

				if (oInfo->getAudioInfo()->getCodecs()[0] == AudioCodec::AC3)
					acodecID = "A_AC3";
				else if (oInfo->getAudioInfo()->getCodecs()[0] == AudioCodec::AAC)
					acodecID = "A_AAC";
				else if (oInfo->getAudioInfo()->getCodecs()[0] == AudioCodec::DTS || oInfo->getAudioInfo()->getCodecs()[0] == AudioCodec::DTSHD || oInfo->getAudioInfo()->getCodecs()[0] == AudioCodec::DTSMA)
					acodecID = "A_DTS";
				else if (oInfo->getAudioInfo()->getCodecs()[0] == AudioCodec::PCM || oInfo->getAudioInfo()->getCodecs()[0] == AudioCodec::WAV)
					acodecID = "A_LPCM";

				sw->Write("\n" + acodecID + ", ");
				sw->Write("\"" + stream->path + "\"");

				if (stream->delay != 0)
				   sw->Write(", timeshift={0}ms", stream->delay);

				if (!stream->getlanguage().empty())
				{
					for (std::map<std::string, std::string>::const_iterator strLanguage = LanguageSelectionContainer::getLanguages().begin(); strLanguage != LanguageSelectionContainer::getLanguages().end(); ++strLanguage)
					{
						if (stream->getlanguage().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
						{
							sw->Write(", lang=" + strLanguage->second);
							break;
						}
					}
				}
			}

			for (std::vector<MuxStream*>::const_iterator o = settings->getSubtitleStreams().begin(); o != settings->getSubtitleStreams().end(); ++o)
			{
				MuxStream *stream = static_cast<MuxStream*>(*o);
				std::string scodecID = "";

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
				if (stream->path.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".srt"))
					scodecID = "S_TEXT/UTF8";
				else
					scodecID = "S_HDMV/PGS"; // sup files

				sw->Write("\n" + scodecID + ", ");
				sw->Write("\"" + stream->path + "\"");

				if (stream->delay != 0)
					sw->Write(", timeshift={0}ms", stream->delay);

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
				if (stream->path.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".srt"))
				{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sw->Write(", video-width={0}, video-height={1}, fps={2}", oVideoInfo->getVideoInfo()->Width, oVideoInfo->getVideoInfo()->Height, settings->getFramerate().Value->ToString(ci));
				}

				if (!stream->getlanguage().empty())
				{
					for (std::map<std::string, std::string>::const_iterator strLanguage = LanguageSelectionContainer::getLanguages().begin(); strLanguage != LanguageSelectionContainer::getLanguages().end(); ++strLanguage)
					{
						if (stream->getlanguage().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
						{
							sw->Write(", lang=" + strLanguage->second);
							break;
						}
					}
				}
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (sw != 0)
				sw.Dispose();
		}

		job->FilesToDelete.push_back(metaFile);
		if (File::Exists(metaFile))
		{
			std::string strMuxFile = "";
			try
			{
				StreamReader *sr = new StreamReader(metaFile);
				strMuxFile = sr->ReadToEnd();
				sr->Close();
			}
			catch (std::exception &e1)
			{

			}
			log->LogValue("mux script", strMuxFile);
		}
	}

	void tsMuxeR::InitializeInstanceFields()
	{
		metaFile = "";
	}
}
