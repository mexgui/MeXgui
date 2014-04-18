#include "VobSubIndexer.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const VobSubIndexer::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "VobSubIndexer");

	IJobProcessor *VobSubIndexer::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<SubtitleIndexJob*>(j) != 0)
			return new VobSubIndexer();
		return 0;
	}

	const QString &VobSubIndexer::getCommandline() const
	{
		return "\"" + MainForm::Instance->getSettings()->getVobSubPath() + "\",Configure " + configFile;
	}

	VobSubIndexer::VobSubIndexer()
	{
		InitializeInstanceFields();
		executable = Environment::GetFolderPath(Environment::SpecialFolder::System) + "\\rundll32.exe";
	}

	void VobSubIndexer::checkJobIO()
	{
		CommandlineJobProcessor::checkJobIO();
		generateScript();
		Util::ensureExists(configFile);
		su->setStatus("Demuxing subtitles...");
	}

	void VobSubIndexer::generateScript()
	{
		configFile = Path::ChangeExtension(job->Output, ".vobsub");
		FileUtil::ensureDirectoryExists(Path::GetDirectoryName(configFile));

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (StreamWriter sw = new StreamWriter(configFile, false, Encoding.Default))
		StreamWriter *sw = new StreamWriter(configFile, false, Encoding::Default);
		try
		{
			sw->WriteLine(job->Input);
			sw->WriteLine(FileUtil::GetPathWithoutExtension(job->Output));
			sw->WriteLine(job->getPGC());
			sw->WriteLine("0"); // we presume angle processing has been done before
			if (job->getIndexAllTracks())
				sw->WriteLine("ALL");
			else
			{
				for (QVector<int>::const_iterator id = job->getTrackIDs().begin(); id != job->getTrackIDs().end(); ++id)
				{
					sw->Write(*id + " ");
				}
				sw->Write(sw->NewLine);
			}
			sw->WriteLine("CLOSE");
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (sw != 0)
				sw.Dispose();
		}

		job->FilesToDelete.push_back(configFile);
	}

	const bool &VobSubIndexer::getcanPause() const
	{
		return false;
	}

	const bool &VobSubIndexer::getcheckExitCode() const
	{
		return false;
	}

	void VobSubIndexer::InitializeInstanceFields()
	{
		configFile = "";
	}
}
