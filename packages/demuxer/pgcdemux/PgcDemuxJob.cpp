#include "PgcDemuxJob.h"




//using namespace System::Collections::Generic;

//using namespace System::Xml::Serialization;

namespace MeXgui
{

	PgcDemuxJob::PgcDemuxJob()
	{
	}

	PgcDemuxJob::PgcDemuxJob(const QString &strInput, const QString &strOutputPath, int pgcNumber) : Job(strInput, 0)
	{
		this->_strOutputPath = strOutputPath;
		this->_pgcNumber = pgcNumber;
		if (!strOutputPath.empty())
		{
			FilesToDelete.push_back(System::IO::Path::Combine(strOutputPath, "LogFile.txt"));
			FilesToDelete.push_back(System::IO::Path::Combine(strOutputPath, "Celltimes.txt"));
		}
	}

	const QString &PgcDemuxJob::getCodecString() const
	{
		return "pgcdemux";
	}

	const QString &PgcDemuxJob::getEncodingMode() const
	{
		return "ext";
	}

	const QString &PgcDemuxJob::getOutputPath() const
	{
		return _strOutputPath;
	}

	void PgcDemuxJob::setOutputPath(const QString &value)
	{
		_strOutputPath = value;
	}

	const int &PgcDemuxJob::getPGCNumber() const
	{
		return _pgcNumber;
	}

	void PgcDemuxJob::setPGCNumber(const int &value)
	{
		_pgcNumber = value;
	}
}
