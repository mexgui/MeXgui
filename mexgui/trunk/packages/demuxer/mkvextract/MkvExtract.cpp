#include "MkvExtract.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
using namespace MeGUI::core::util;

namespace MeGUI
{

JobProcessorFactory *const MkvExtract::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "MkvExtract");

	IJobProcessor *MkvExtract::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<MkvExtractJob*>(j) != 0)
			return new MkvExtract(mf->getSettings()->getMkvExtractPath());
		return 0;
	}

	MkvExtract::MkvExtract(const std::string &executablePath)
	{
		this->executable = executablePath;
	}

	Nullable<decimal> MkvExtract::getPercentage(const std::string &line)
	{
		try
		{
			int percentageStart = 10;
			int percentageEnd = line.find("%");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			std::string frameNumber = line.substr(percentageStart, percentageEnd - percentageStart)->Trim();
			return int::Parse(frameNumber);
		}
		catch (std::exception &e)
		{
			log->LogValue("Exception in getPercentage(" + line + ")", e, MeGUI::core::util::Warning);
			return 0;
		}
	}

	void MkvExtract::ProcessLine(const std::string &line, StreamType stream, ImageType oType)
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

	const std::string &MkvExtract::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();

		// verify track IDs
		MediaInfoFile *oFile = new MediaInfoFile(job->Input, log);
		for (std::vector<TrackInfo*>::const_iterator oTrack = job->getMkvTracks().begin(); oTrack != job->getMkvTracks().end(); ++oTrack)
		{
			if ((*oTrack)->getTrackType() == Audio)
			{
				bool bFound = false;
				for (std::vector<AudioTrackInfo*>::const_iterator oAudioInfo = oFile->getAudioInfo()->getTracks().begin(); oAudioInfo != oFile->getAudioInfo()->getTracks().end(); ++oAudioInfo)
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
				for (std::vector<SubtitleTrackInfo*>::const_iterator oSubtitleInfo = oFile->getSubtitleInfo()->getTracks().begin(); oSubtitleInfo != oFile->getSubtitleInfo()->getTracks().end(); ++oSubtitleInfo)
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
		for (std::vector<TrackInfo*>::const_iterator oTrack = job->getMkvTracks().begin(); oTrack != job->getMkvTracks().end(); ++oTrack)
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
