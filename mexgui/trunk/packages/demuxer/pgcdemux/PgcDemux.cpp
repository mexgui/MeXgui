#include "PgcDemux.h"

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

JobProcessorFactory *const PgcDemux::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "PgcDemux");

	IJobProcessor *PgcDemux::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<PgcDemuxJob*>(j) != 0)
			return new PgcDemux(mf->getSettings()->getPgcDemuxPath());
		return 0;
	}

	PgcDemux::PgcDemux(const std::string &executablePath)
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

	const std::string &PgcDemux::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();

		// Input File
		sb->Append("-pgc " + job->getPGCNumber() + " -noaud -nosub -customvob n,v,a,s,l \"" + job->Input + "\" \"" + job->getOutputPath() + "\"");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}
}
