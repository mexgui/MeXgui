#include "OneClickPostProcessingJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{

	OneClickPostProcessingJob::OneClickPostProcessingJob()
	{
	}

	OneClickPostProcessingJob::OneClickPostProcessingJob(const std::string &input, const std::string &strIndexFile, OneClickPostprocessingProperties *postprocessingProperties) : Job(input, 0)
	{
		this->postprocessingProperties = postprocessingProperties;
		this->strIndexFile = strIndexFile;
	}

	const std::string &OneClickPostProcessingJob::getCodecString() const
	{
		return "";
	}

	const std::string &OneClickPostProcessingJob::getEncodingMode() const
	{
		return "oneclick";
	}

	const OneClickPostprocessingProperties &OneClickPostProcessingJob::getPostprocessingProperties() const
	{
		return postprocessingProperties;
	}

	void OneClickPostProcessingJob::setPostprocessingProperties(const OneClickPostprocessingProperties &value)
	{
		postprocessingProperties = value;
	}

	const std::string &OneClickPostProcessingJob::getIndexFile() const
	{
		return strIndexFile;
	}

	void OneClickPostProcessingJob::setIndexFile(const std::string &value)
	{
		strIndexFile = value;
	}
}
