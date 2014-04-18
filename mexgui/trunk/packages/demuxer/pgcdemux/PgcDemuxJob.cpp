#include "PgcDemuxJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{

	PgcDemuxJob::PgcDemuxJob()
	{
	}

	PgcDemuxJob::PgcDemuxJob(const std::string &strInput, const std::string &strOutputPath, int pgcNumber) : Job(strInput, 0)
	{
		this->_strOutputPath = strOutputPath;
		this->_pgcNumber = pgcNumber;
		if (!strOutputPath.empty())
		{
			FilesToDelete.push_back(System::IO::Path::Combine(strOutputPath, "LogFile.txt"));
			FilesToDelete.push_back(System::IO::Path::Combine(strOutputPath, "Celltimes.txt"));
		}
	}

	const std::string &PgcDemuxJob::getCodecString() const
	{
		return "pgcdemux";
	}

	const std::string &PgcDemuxJob::getEncodingMode() const
	{
		return "ext";
	}

	const std::string &PgcDemuxJob::getOutputPath() const
	{
		return _strOutputPath;
	}

	void PgcDemuxJob::setOutputPath(const std::string &value)
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
