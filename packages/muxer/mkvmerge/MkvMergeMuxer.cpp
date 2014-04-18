#include "MkvMergeMuxer.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;


using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const MkvMergeMuxer::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "MkvMergeMuxer");

	IJobProcessor *MkvMergeMuxer::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<MuxJob*>(j) != 0 && (dynamic_cast<MuxJob*>(j))->getMuxType() == MKVMERGE)
			return new MkvMergeMuxer(mf->getSettings()->getMkvmergePath());
		return 0;
	}

	MkvMergeMuxer::MkvMergeMuxer(const QString &executablePath)
	{
		this->executable = executablePath;
	}

	Nullable<decimal> MkvMergeMuxer::getPercentage(const QString &line)
	{
		try
		{
			int percentageStart = 10;
			int percentageEnd = line.find("%");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			QString frameNumber = line.substr(percentageStart, percentageEnd - percentageStart)->Trim();
			return int::Parse(frameNumber);
		}
		catch (std::exception &e)
		{
			log->LogValue("Exception in getPercentage(" + line + ")", e, Warning);
			return 0;
		}
	}

	void MkvMergeMuxer::checkJobIO()
	{
		su->setStatus("Muxing MKV...");
		CommandlineMuxer::checkJobIO();
	}

	void MkvMergeMuxer::ProcessLine(const QString &line, StreamType stream, ImageType oType)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("Progress: ")) //status update
		{
			su->setPercentageDoneExact(getPercentage(line));
			return;
		}

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("Error: "))
			oType = Error;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		else if (line.StartsWith("Warning: "))
			oType = Warning;
		CommandlineMuxer::ProcessLine(line, stream, oType);
	}

	void MkvMergeMuxer::setProjectedFileSize()
	{
		if (!job->getSettings()->getMuxAll())
			CommandlineMuxer::setProjectedFileSize();
	}

	const QString &MkvMergeMuxer::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();
		MuxSettings *settings = job->getSettings();
		int trackID;

		sb->Append("-o \"" + settings->getMuxedOutput() + "\"");
		if (settings->getMuxAll())
		{
			QString strInput = "";
			if (!settings->getVideoInput().empty())
				strInput = settings->getVideoInput();
			else if (!settings->getMuxedInput().empty())
				strInput = settings->getMuxedInput();
			MediaInfoFile *oVideoInfo = new MediaInfoFile(strInput, log);
			if (oVideoInfo->getContainerFileType() == ContainerType::MP4 || oVideoInfo->getContainerFileType() == ContainerType::MKV)
				trackID = oVideoInfo->getVideoInfo()->getTrack()->getMMGTrackID();
			else
				trackID = 0;

			sb->Append(" \"" + strInput + "\"");
			sb->Append(" \"--compression\" \"" + trackID + ":none\"");
			sb->Append(" --ui-language en");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			return sb->ToString();
		}

		if (!settings->getVideoInput().empty() || !settings->getMuxedInput().empty())
		{
			QString inputFile = settings->getVideoInput();
			if (settings->getVideoInput().empty())
				inputFile = settings->getMuxedInput();

			MediaInfoFile *oVideoInfo = new MediaInfoFile(inputFile, log);
			if (oVideoInfo->getContainerFileType() == ContainerType::MP4 || oVideoInfo->getContainerFileType() == ContainerType::MKV)
				trackID = oVideoInfo->getVideoInfo()->getTrack()->getMMGTrackID();
			else
				trackID = 0;

			if (settings->getDAR().HasValue && !settings->getVideoInput().empty())
				sb->Append(" --aspect-ratio " + trackID + ":" + settings->getDAR().Value::X + "/" + settings->getDAR().Value::Y);
			else
				sb->Append(" --engage keep_bitstream_ar_info"); // assuming that SAR info is already in the stream...
			if (!settings->getVideoName().empty())
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				sb->Append(" --track-name \"" + trackID + ":" + settings->getVideoName().Replace("\"", "\\\"") + "\"");
			if (settings->getFramerate().HasValue && (oVideoInfo->getVideoInfo()->getCodec() == 0 || oVideoInfo->getVideoInfo()->getCodec() != VideoCodec::AVC || oVideoInfo->getVideoInfo()->getScanType().ToLowerInvariant()->Equals("progressive")))
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				sb->Append(" --default-duration " + trackID + ":" + PrettyFormatting::ReplaceFPSValue(settings->getFramerate().Value->ToString()) + "fps");
			sb->Append(" \"--compression\" \"" + trackID + ":none\"");
			sb->Append(" -d \"" + trackID + "\" --no-chapters -A -S \"" + inputFile + "\"");
		}

		for (QVector<MuxStream*>::const_iterator o = settings->getAudioStreams().begin(); o != settings->getAudioStreams().end(); ++o)
		{
			MuxStream *stream = static_cast<MuxStream*>(*o);
			MediaInfoFile *oAudioInfo = new MediaInfoFile(stream->path, log);

			if (!oAudioInfo->getHasAudio())
			{
				log->LogEvent("No audio track found: " + stream->path, Warning);
				continue;
			}

			if (oAudioInfo->getContainerFileType() == ContainerType::MP4 || oAudioInfo->getContainerFileType() == ContainerType::MKV)
				trackID = oAudioInfo->getAudioInfo()->GetFirstTrackID();
			else
				trackID = 0;

			if (oAudioInfo->getContainerFileType() == ContainerType::MP4 || oAudioInfo->getAudioInfo()->getCodecs()[0] == AudioCodec::AAC)
			{
				int heaac_flag = -1;
				if (oAudioInfo->getAudioInfo()->getTracks().size() > 0)
					heaac_flag = oAudioInfo->getAudioInfo()->getTracks()[0]->getAACFlag();
				if (heaac_flag == 1)
					sb->Append(" --aac-is-sbr " + trackID + ":1");
				else if (heaac_flag == 0)
					sb->Append(" --aac-is-sbr " + trackID + ":0");
			}

			if (!stream->getlanguage().empty())
			{
				for (QMap<QString, QString>::const_iterator strLanguage = LanguageSelectionContainer::getLanguages().begin(); strLanguage != LanguageSelectionContainer::getLanguages().end(); ++strLanguage)
				{
					if (stream->getlanguage().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
					{
						sb->Append(" --language " + trackID + ":" + strLanguage->second);
						break;
					}
				}
			}
			if (!stream->getname().empty())
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				sb->Append(" --track-name \"" + trackID + ":" + stream->getname().Replace("\"", "\\\"") + "\"");
			if (stream->delay != 0)
				sb->AppendFormat(" --sync {0}:{1}ms", trackID, stream->delay);
			sb->Append(" \"--compression\" \"" + trackID + ":none\"");
			sb->Append(" -a " + trackID + " --no-chapters -D -S \"" + stream->path + "\"");
		}

		for (QVector<MuxStream*>::const_iterator o = settings->getSubtitleStreams().begin(); o != settings->getSubtitleStreams().end(); ++o)
		{
			MuxStream *stream = static_cast<MuxStream*>(*o);

			trackID = 0;
			if (System::IO::File::Exists(stream->path))
			{
				MediaInfoFile *oSubtitleInfo = new MediaInfoFile(stream->path, log);
				if (oSubtitleInfo->getContainerFileType() == ContainerType::MP4 || oSubtitleInfo->getContainerFileType() == ContainerType::MKV)
					trackID = oSubtitleInfo->getSubtitleInfo()->GetFirstTrackID();
			}

			if (stream->MuxOnlyInfo != 0)
			{
				trackID = stream->MuxOnlyInfo->getMMGTrackID();
				if (!stream->MuxOnlyInfo->getLanguage().empty())
					sb->Append(" --language " + trackID + ":" + stream->MuxOnlyInfo->getLanguage());
				if (!stream->MuxOnlyInfo->getName().empty())
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					sb->Append(" --track-name \"" + trackID + ":" + stream->MuxOnlyInfo->getName().Replace("\"", "\\\"") + "\"");
				if (stream->delay != 0)
					sb->AppendFormat(" --sync {0}:{1}ms", trackID, stream->delay);
				if (stream->MuxOnlyInfo->getDefaultTrack())
					sb->Append(" --default-track \"" + trackID + ":yes\"");
				else
					sb->Append(" --default-track \"" + trackID + ":no\"");
				if (stream->MuxOnlyInfo->getForcedTrack())
					sb->Append(" --forced-track \"" + trackID + ":yes\"");
				else
					sb->Append(" --forced-track \"" + trackID + ":no\"");
				sb->Append(" -s " + trackID + " -D -A -T --no-global-tags --no-chapters \"" + stream->MuxOnlyInfo->getSourceFileName() + "\"");
			}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			else if (stream->path.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".idx"))
			{
				QVector<SubtitleInfo*> subTracks;
				idxReader::readFileProperties(stream->path, subTracks);
				if (subTracks.empty())
				{
					log->LogEvent("No subtitle track found: " + stream->path, Warning);
					continue;
				}
				for (QVector<SubtitleInfo*>::const_iterator strack = subTracks.begin(); strack != subTracks.end(); ++strack)
				{
					for (QMap<QString, QString>::const_iterator strLanguage = LanguageSelectionContainer::getLanguages().begin(); strLanguage != LanguageSelectionContainer::getLanguages().end(); ++strLanguage)
					{
						if (trackID == 0 && !stream->getlanguage().empty() && stream->getlanguage().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
						{
							sb->Append(" --language " + trackID + ":" + strLanguage->second);
							break;
						}
						else if (((trackID == 0 && stream->getlanguage().empty()) || trackID > 0) && LanguageSelectionContainer::Short2FullLanguageName((*strack)->getName()).ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
						{
							sb->Append(" --language " + trackID + ":" + strLanguage->second);
							break;
						}
					}
					if (!stream->getname().empty())
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
						sb->Append(" --track-name \"" + trackID + ":" + stream->getname().Replace("\"", "\\\"") + "\"");
					if (stream->delay != 0)
						sb->AppendFormat(" --sync {0}:{1}ms", trackID, stream->delay);
					if (stream->bDefaultTrack && trackID == 0)
						sb->Append(" --default-track 0:yes");
					else
						sb->Append(" --default-track " + trackID + ":no");
					if (stream->bForceTrack)
						sb->Append(" --forced-track " + trackID + ":yes");
					else
						sb->Append(" --forced-track " + trackID + ":no");
					++trackID;
				}
				trackID = 0;
				sb->Append(" -s ");
				for (QVector<SubtitleInfo*>::const_iterator strack = subTracks.begin(); strack != subTracks.end(); ++strack)
				{
					if (trackID > 0)
						sb->Append("," + trackID);
					else
						sb->Append("0");
					++trackID;
				}
				sb->Append(" -D -A \"" + stream->path + "\"");
			}
			else
			{
				if (!stream->getlanguage().empty())
				{
					for (QMap<QString, QString>::const_iterator strLanguage = LanguageSelectionContainer::getLanguages().begin(); strLanguage != LanguageSelectionContainer::getLanguages().end(); ++strLanguage)
					{
						if (stream->getlanguage().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
						{
							sb->Append(" --language " + trackID + ":" + strLanguage->second);
							break;
						}
					}
				}
				if (!stream->getname().empty())
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					sb->Append(" --track-name \"" + trackID + ":" + stream->getname().Replace("\"", "\\\"") + "\"");
				if (stream->delay != 0)
					sb->AppendFormat(" --sync {0}:{1}ms", trackID, stream->delay);
				if (stream->bDefaultTrack)
					sb->Append(" --default-track \"" + trackID + ":yes\"");
				else
					sb->Append(" --default-track \"" + trackID + ":no\"");
				if (stream->bForceTrack)
					sb->Append(" --forced-track \"" + trackID + ":yes\"");
				else
					sb->Append(" --forced-track \"" + trackID + ":no\"");
				sb->Append(" -s " + trackID + " -D -A \"" + stream->path + "\"");
			}
		}
		if (!settings->getChapterFile().empty()) // a chapter file is defined
			sb->Append(" --chapters \"" + settings->getChapterFile() + "\"");

		if (settings->getSplitSize().HasValue)
			sb->Append(" --split " + (settings->getSplitSize().Value::MB) + "M");

		sb->Append(" --engage no_cue_duration --engage no_cue_relative_position --ui-language en");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}
}
