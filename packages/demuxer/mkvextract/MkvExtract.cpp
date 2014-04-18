#include "MkvExtract.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Text::RegularExpressions;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const MkvExtract::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "MkvExtract");

	IJobProcessor *MkvExtract::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<MkvExtractJob*>(j) != 0)
			return new MkvExtract(mf->getSettings()->getMkvExtractPath());
		return 0;
	}

	MkvExtract::MkvExtract(const QString &executablePath)
	{
		this->executable = executablePath;
	}

	Nullable<decimal> MkvExtract::getPercentage(const QString &line)
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
			log->LogValue("Exception in getPercentage(" + line + ")", e, MeXgui::core::util::Warning);
			return 0;
		}
	}

	void MkvExtract::ProcessLine(const QString &line, StreamType stream, ImageType oType)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("Progress: ")) //status update
		{
			su->setPercentageDoneExact(getPercentage(line));
			su->setStatus("Extracting Tracks...");
			return;
		}

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (!line.ToLower(System::Globalization::CultureInfo::InvariantCulture)->StartsWith("extracting track"))
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
			if (line.ToLower(System::Globalization::CultureInfo::InvariantCulture)->StartsWith("error"))
				oType = Error;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
			else if (line.ToLower(System::Globalization::CultureInfo::InvariantCulture)->StartsWith("warning"))
				oType = Warning;
		}
		CommandlineJobProcessor::ProcessLine(line, stream, oType);
	}

	const QString &MkvExtract::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();

		// verify track IDs
		MediaInfoFile *oFile = new MediaInfoFile(job->Input, log);
		for (QVector<TrackInfo*>::const_iterator oTrack = job->getMkvTracks().begin(); oTrack != job->getMkvTracks().end(); ++oTrack)
		{
			if ((*oTrack)->getTrackType() == Audio)
			{
				bool bFound = false;
				for (QVector<AudioTrackInfo*>::const_iterator oAudioInfo = oFile->getAudioInfo()->getTracks().begin(); oAudioInfo != oFile->getAudioInfo()->getTracks().end(); ++oAudioInfo)
				{
					if ((*oAudioInfo)->getMMGTrackID() == (*oTrack)->getMMGTrackID())
						bFound = true;
				}

				if (!bFound)
					(*oTrack)->setMMGTrackID(oFile->getAudioInfo()->getTracks()[(*oTrack)->getTrackIndex()]->getMMGTrackID());
			}
			else if ((*oTrack)->getTrackType() == Subtitle)
			{
				bool bFound = false;
				for (QVector<SubtitleTrackInfo*>::const_iterator oSubtitleInfo = oFile->getSubtitleInfo()->getTracks().begin(); oSubtitleInfo != oFile->getSubtitleInfo()->getTracks().end(); ++oSubtitleInfo)
				{
					if ((*oSubtitleInfo)->getMMGTrackID() == (*oTrack)->getMMGTrackID())
						bFound = true;
				}

				if (!bFound)
					(*oTrack)->setMMGTrackID(oFile->getSubtitleInfo()->getTracks()[(*oTrack)->getTrackIndex()]->getMMGTrackID());
			}

		}

		// Input File
		sb->Append("tracks \"" + job->Input + "\" --ui-language en");

		// Tracks to extract
		for (QVector<TrackInfo*>::const_iterator oTrack = job->getMkvTracks().begin(); oTrack != job->getMkvTracks().end(); ++oTrack)
		{
			// Extract only audio/subtitle tracks
			if ((*oTrack)->getTrackType() != Audio && (*oTrack)->getTrackType() != Subtitle)
				continue;

			sb->Append(" " + (*oTrack)->getMMGTrackID() + ":\"" + job->getOutputPath() + "\\" + (*oTrack)->getDemuxFileName() + "\"");
		}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}
}
