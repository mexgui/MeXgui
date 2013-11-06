#include "D2VIndexer.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;

namespace MeGUI
{

Regex *const D2VIndexer::DGPercent = new Regex("\\[(?<num>[0-9]*)%\\]", RegexOptions::Compiled);
TimeSpan *const D2VIndexer::TwoSeconds = new TimeSpan(0, 0, 2);
JobProcessorFactory *const D2VIndexer::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "D2VIndexer");

	IJobProcessor *D2VIndexer::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<D2VIndexJob*>(j) != 0)
			return new D2VIndexer(mf->getSettings()->getDgIndexPath());
		return 0;
	}

	D2VIndexer::D2VIndexer(const std::string &executableName)
	{
		executable = executableName;
	}

	void D2VIndexer::ProcessLine(const std::string &line, StreamType stream, ImageType oType)
	{
		if (Regex::IsMatch(line, "^[0-9]{1,3}$", RegexOptions::Compiled))
			su->setPercentageDoneExact(int::Parse(line));
		else
			CommandlineJobProcessor::ProcessLine(line, stream, oType);
	}

	const std::string &D2VIndexer::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();
		int idx = 0;
		std::string projName = Path::Combine(Path::GetDirectoryName(job->Output), Path::GetFileNameWithoutExtension(job->Output));
		if (MainForm::Instance->getSettings()->getAutoLoadDG())
			sb->Append("-SD=< -AIF=<" + job->Input);
		else
			sb->Append("-SD=< -IF=<" + job->Input);
		if (job->getDemuxVideo())
			sb->Append("< -OFD=<" + projName + "< -FO=0 -exit -hide");
		else
			sb->Append("< -OF=<" + projName + "< -FO=0 -exit -hide");
		if (job->getDemuxMode() == 2)
			sb->Append(" -OM=2"); // demux everything
		else if (job->getDemuxMode() == 1)
		{
			sb->Append(" -OM=1 -TN="); // demux only tracks checked
			for (std::vector<AudioTrackInfo*>::const_iterator ati = job->getAudioTracks().begin(); ati != job->getAudioTracks().end(); ++ati)
			{
				if (idx > 0)
					 sb->Append("," + (*ati)->getDgIndexID());
				else
					sb->Append((*ati)->getDgIndexID());
				++idx;
			}
		}
		else
			sb->Append(" -OM=0"); // no audio demux
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}

	void D2VIndexer::checkJobIO()
	{
		try
		{
			if (!job->Output.empty())
				FileUtil::ensureDirectoryExists(Path::GetDirectoryName(job->Output));
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			CommandlineJobProcessor::checkJobIO();
		}
		su->setStatus("Creating DGV...");
	}

	void D2VIndexer::doExitConfig()
	{
		if (MainForm::Instance->getSettings()->getAutoForceFilm() && !su->getHasError() && !su->getWasAborted())
		{
			LogItem *l = log->LogEvent("Running auto force film");
			double filmPercent;
			try
			{
				filmPercent = d2vFile::GetFilmPercent(job->Output);
			}
			catch (std::exception &error)
			{
				l->LogValue("Exception opening file to apply force film", error, Error);
				su->setHasError(true);
				return;
			}
			if (!su->getHasError())
			{
				l->LogValue("Film percentage", filmPercent);
				if (MainForm::Instance->getSettings()->getForceFilmThreshold() <= static_cast<decimal>(filmPercent))
				{
					bool success = applyForceFilm(job->Output);
					if (success)
						l->LogEvent("Applied force film");
					else
					{
						l->Error("Applying force film failed");
						su->setHasError(true);
					}
				}
			}
		}
	}

	bool D2VIndexer::applyForceFilm(const std::string &fileName)
	{
		try
		{
			StringBuilder *sb = new StringBuilder();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (StreamReader sr = new StreamReader(fileName))
			StreamReader *sr = new StreamReader(fileName);
			try
			{
				std::string line = "";
				while ((line = sr->ReadLine()) != 0)
				{
					if (line.find("Field_Operation") != -1) // this is the line we have to replace
						sb->Append("Field_Operation=1" + "\r\n");
					else if (line.find("Frame_Rate") != -1)
					{
						if (line.find("/") != -1) // If it has a slash, it means the framerate is signalled as a fraction, like below
							sb->Append("Frame_Rate=23976 (24000/1001)" + "\r\n");
						else // If it doesn't, then it doesn't
							sb->Append("Frame_Rate=23976" + "\r\n");
					}
					else
					{
						sb->Append(line);
						sb->Append("\r\n");
					}
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (sr != 0)
					sr.Dispose();
			}
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (StreamWriter sw = new StreamWriter(fileName))
			StreamWriter *sw = new StreamWriter(fileName);
			try
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				sw->Write(sb->ToString());
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (sw != 0)
					sw.Dispose();
			}
			return true;
		}
		catch (std::exception &e)
		{
			log->LogValue("Exception in applyForceFilm", e, Error);
			return false;
		}
	}

	void D2VIndexer::doStatusCycleOverrides()
	{
		try
		{
			if (su->getTimeElapsed() < TwoSeconds) // give it some time to start up, otherwise MainWindowHandle remains null
				return;
			std::string text = proc->MainWindowTitle;

			Match *m = DGPercent->Match(text);
			if (m->Success)
			{
				su->setPercentageDoneExact(int::Parse(m->Groups["num"]->Value));
			}
		}
		catch (std::exception &e1)
		{
		}
	}
}
