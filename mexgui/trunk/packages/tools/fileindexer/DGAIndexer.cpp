#include "DGAIndexer.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
using namespace MeGUI::core::util;

namespace MeGUI
{

JobProcessorFactory *const DGAIndexer::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "DGAIndexer");

	IJobProcessor *DGAIndexer::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<DGAIndexJob*>(j) != 0)
			return new DGAIndexer(mf->getSettings()->getDgavcIndexPath());
		return 0;
	}

	DGAIndexer::DGAIndexer(const std::string &executableName)
	{
		executable = executableName;
	}

	void DGAIndexer::ProcessLine(const std::string &line, StreamType stream, ImageType oType)
	{
		if (Regex::IsMatch(line, "^[0-9]{1,3}$", RegexOptions::Compiled))
			su->setPercentageDoneExact(int::Parse(line));
		else
			CommandlineJobProcessor::ProcessLine(line, stream, oType);
	}

	void DGAIndexer::checkJobIO()
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
		su->setStatus("Creating DGA...");
	}

	const std::string &DGAIndexer::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();
		if (job->getDemuxVideo())
			 sb->Append("-i \"" + job->Input + "\" -od \"" + job->Output + "\" -e -h");
		else
			sb->Append("-i \"" + job->Input + "\" -o \"" + job->Output + "\" -e -h");
		if (job->getDemuxMode() == 2)
			sb->Append(" -a"); // demux everything
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}
}
