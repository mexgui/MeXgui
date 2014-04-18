#include "FFMSIndexer.h"




//using namespace System::Collections::Generic;



//using namespace System::Text;

//using namespace System::Text::RegularExpressions;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const FFMSIndexer::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "FFMSIndexer");

	IJobProcessor *FFMSIndexer::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<FFMSIndexJob*>(j) != 0)
			return new FFMSIndexer(mf->getSettings()->getFFMSIndexPath());
		return 0;
	}

	FFMSIndexer::FFMSIndexer(const QString &executableName)
	{
		executable = executableName;
	}

	void FFMSIndexer::ProcessLine(const QString &line, StreamType stream, ImageType oType)
	{
		if (Regex::IsMatch(line, "^Indexing, please wait... [0-9]{1,3}%", RegexOptions::Compiled))
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			su->setPercentageDoneExact(int::Parse(line.substr(25)->Split('%')[0]));
			su->setStatus("Creating FFMS index...");
			return;
		}

		if (Regex::IsMatch(line, "^Writing index...", RegexOptions::Compiled))
			su->setStatus("Writing FFMS index...");
		CommandlineJobProcessor::ProcessLine(line, stream, oType);
	}

	const QString &FFMSIndexer::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();
		if (job->getDemuxMode() > 0)
			sb->Append("-t -1 ");
		sb->Append("-f \"" + job->Input + "\"");
		if (!job->Output.empty())
			sb->Append(" \"" + job->Output + "\"");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}

	void FFMSIndexer::checkJobIO()
	{
		try
		{
			if (!job->Output.empty())
			{
				FileUtil::ensureDirectoryExists(Path::GetDirectoryName(job->Output));
				if (File::Exists(job->Output))
					File::Delete(job->Output);
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			CommandlineJobProcessor::checkJobIO();
		}
		su->setStatus("Creating FFMS index...");
	}

	void FFMSIndexer::doExitConfig()
	{
		if (job->getDemuxMode() > 0 && !su->getHasError() && !su->getWasAborted() && job->getAudioTracks().size() > 0)
		{
			int iTracksFound = 0;
			int iCurrentAudioTrack = -1;
			for (int iCurrentTrack = 0; iCurrentTrack <= 29; iCurrentTrack++) // hard limit to max. 30 tracks
			{
				StringBuilder *strAVSScript = new StringBuilder();
				QString strDLLPath = Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getFFMSIndexPath()), "ffms2.dll");
				strAVSScript->AppendLine("LoadPlugin(\"" + strDLLPath + "\")");
				strAVSScript->AppendLine("FFAudioSource(\"" + job->Input + "\", track=" + iCurrentTrack + (!job->Output.empty() ? ", cachefile=\"" + job->Output + "\"" : "") + ")");

				// is this an audio track?
				QString strErrorText;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				if (AudioUtil::AVSScriptHasAudio(strAVSScript->ToString(), strErrorText) == false)
					continue;
				iCurrentAudioTrack++;

				for (QVector<AudioTrackInfo*>::const_iterator oAudioTrack = job->getAudioTracks().begin(); oAudioTrack != job->getAudioTracks().end(); ++oAudioTrack)
				{
					if ((*oAudioTrack)->getTrackIndex() != iCurrentAudioTrack)
						continue;

					// write avs file
					QString strAudioAVSFile;
					strAudioAVSFile = Path::GetFileNameWithoutExtension(job->Output) + "_track_" + ((*oAudioTrack)->getTrackIndex() + 1) + "_" + (*oAudioTrack)->getLanguage()->ToLower(System::Globalization::CultureInfo::InvariantCulture) + ".avs";
					strAudioAVSFile = Path::Combine(Path::GetDirectoryName(job->Output), Path::GetFileName(strAudioAVSFile));
					try
					{
						strAVSScript->AppendLine("# detected channels: " + (*oAudioTrack)->getNbChannels());
						strAVSScript->Append("# detected channel positions: " + (*oAudioTrack)->getChannelPositions());
						StreamWriter *oAVSWriter = new StreamWriter(strAudioAVSFile, false, Encoding::Default);
						oAVSWriter->Write(strAVSScript);
						oAVSWriter->Close();
					}
					catch (IOException *ex)
					{
						log->LogValue("Error creating audio AVS file", ex);
					}
					break;
				}
				if (++iTracksFound == job->getAudioTracks().size())
					break;
			}
		}
		CommandlineJobProcessor::doExitConfig();
	}
}
