#include "HDStreamExtractorIndexer.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Text::RegularExpressions;
using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const HDStreamExtractorIndexer::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "HDStreamExtIndexer");

	IJobProcessor *HDStreamExtractorIndexer::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<HDStreamsExJob*>(j) != 0)
			return new HDStreamExtractorIndexer(mf->getSettings()->getEAC3toPath());
		return 0;
	}

	HDStreamExtractorIndexer::HDStreamExtractorIndexer(const QString &executablePath)
	{
		this->executable = executablePath;
	}

	Nullable<decimal> HDStreamExtractorIndexer::getPercentage(const QString &line)
	{
		try
		{
			if (Regex::IsMatch(line, "^process: [0-9]{1,3}%$", RegexOptions::Compiled))
			{
				int pct = int::Parse(Regex::Match(line, "[0-9]{1,3}")->Value);
				return pct;
			}
			else if (Regex::IsMatch(line, "^analyze: [0-9]{1,3}%$", RegexOptions::Compiled))
			{
				int pct = int::Parse(Regex::Match(line, "[0-9]{1,3}")->Value);
				return pct;
			}
			else
				return 0;
		}
		catch (std::exception &e)
		{
			log->LogValue("Exception in getPercentage(" + line + ") ", e, Warning);
			return 0;
		}
	}

	void HDStreamExtractorIndexer::checkJobIO()
	{
		for (QVector<QString>::const_iterator strSource = job->getSource().begin(); strSource != job->getSource().end(); ++strSource)
			Util::ensureExists(*strSource);
	}

	void HDStreamExtractorIndexer::ProcessLine(const QString &line, StreamType stream, ImageType oType)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("process: ")) //status update
		{
			su->setPercentageDoneExact(getPercentage(line));
			if (bSecondPass)
				su->setStatus("Fixing audio gaps/overlaps...");
			else
				su->setStatus("Extracting Tracks...");
		}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		else if (line.StartsWith("analyze: "))
		{
			su->setPercentageDoneExact(getPercentage(line));
			su->setStatus("Analyzing...");
		}
		else if (line.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("2nd"))
		{
			startTime = DateTime::Now;
			su->setTimeElapsed(TimeSpan::Zero);
			bSecondPass = true;
			su->setStatus("Fixing audio gaps/overlaps...");
			CommandlineJobProcessor::ProcessLine(line, stream, oType);
		}
		else if (line.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("without making use of the gap/overlap information"))
		{
			log->LogEvent("Job will be executed a second time to make use of the gap/overlap information");
			CommandlineJobProcessor::bRunSecondTime = true;
			CommandlineJobProcessor::ProcessLine(line, stream, oType);
		}
		else if (line.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("<error>"))
		{
			CommandlineJobProcessor::ProcessLine(line, stream, Error);
		}
		else if (line.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("<warning>") || (su->getPercentageDoneExact() > 0 && su->getPercentageDoneExact() < 100 && !line.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("creating file ") && !line.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("(seamless branching)...")))
		{
			CommandlineJobProcessor::ProcessLine(line, stream, Warning);
		}
		else
			CommandlineJobProcessor::ProcessLine(line, stream, oType);
	}

	const QString &HDStreamExtractorIndexer::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();
		if (job->getInputType() == 1) // Folder as Input
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if (job->Input.find("BDMV") > 0 && (job->Input.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".m2ts") || job->Input.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".mpls")))
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				sb->Append(QString::Format("\"{0}\" {1}) {2}", job->Input.substr(0, job->Input.find("BDMV")), job->getFeatureNb(), job->getArgs().Trim() + " -progressnumbers"));
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			else if (job->Input.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".evo"))
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				sb->Append(QString::Format("\"{0}\" {1}) {2}", job->Input.substr(0, job->Input.find("HVDVD_TS")), job->getFeatureNb(), job->getArgs().Trim() + " -progressnumbers"));
			else
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				sb->Append(QString::Format("\"{0}\" {1}) {2}", job->Input, job->getFeatureNb(), job->getArgs().Trim() + " -progressnumbers"));
		}
		else
		{
			if (job->getSource().empty() && !job->Input.empty())
				job->getSource().push_back(job->Input);

			QString strSource = QString::Format("\"{0}\"", job->getSource()[0]);
			for (int i = 1; i < job->getSource().size(); i++)
				strSource += QString::Format("+\"{0}\"", job->getSource()[i]);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			sb->Append(QString::Format("{0} {1}", strSource, job->getArgs().Trim() + " -progressnumbers"));
		}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}
}
