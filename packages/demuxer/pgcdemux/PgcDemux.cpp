#include "PgcDeh"




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Text::RegularExpressions;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const PgcDemux::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "PgcDemux");

	IJobProcessor *PgcDemux::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<PgcDemuxJob*>(j) != 0)
			return new PgcDemux(mf->getSettings()->getPgcDemuxPath());
		return 0;
	}

	PgcDemux::PgcDemux(const QString &executablePath)
	{
		this->executable = executablePath;
	}

	void PgcDemux::checkJobIO()
	{
		try
		{
			if (!job->getOutputPath().empty())
				FileUtil::ensureDirectoryExists(job->getOutputPath());
			su->setStatus("Preparing VOB...");
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			CommandlineJobProcessor::checkJobIO();
		}
	}

	const QString &PgcDemux::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();

		// Input File
		sb->Append("-pgc " + job->getPGCNumber() + " -noaud -nosub -customvob n,v,a,s,l \"" + job->Input + "\" \"" + job->getOutputPath() + "\"");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}
}
