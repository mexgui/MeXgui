#include "DGAIndexer.h"




//using namespace System::Collections::Generic;



//using namespace System::Text;

//using namespace System::Text::RegularExpressions;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const DGAIndexer::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "DGAIndexer");

	IJobProcessor *DGAIndexer::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<DGAIndexJob*>(j) != 0)
			return new DGAIndexer(mf->getSettings()->getDgavcIndexPath());
		return 0;
	}

	DGAIndexer::DGAIndexer(const QString &executableName)
	{
		executable = executableName;
	}

	void DGAIndexer::ProcessLine(const QString &line, StreamType stream, ImageType oType)
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

	const QString &DGAIndexer::getCommandline() const
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
