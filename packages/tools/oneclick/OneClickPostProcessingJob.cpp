#include "OneClickPostProcessingJob.h"




//using namespace System::Collections::Generic;

//using namespace System::Xml::Serialization;

namespace MeXgui
{

	OneClickPostProcessingJob::OneClickPostProcessingJob()
	{
	}

	OneClickPostProcessingJob::OneClickPostProcessingJob(const QString &input, const QString &strIndexFile, OneClickPostprocessingProperties *postprocessingProperties) : Job(input, 0)
	{
		this->postprocessingProperties = postprocessingProperties;
		this->strIndexFile = strIndexFile;
	}

	const QString &OneClickPostProcessingJob::getCodecString() const
	{
		return "";
	}

	const QString &OneClickPostProcessingJob::getEncodingMode() const
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

	const QString &OneClickPostProcessingJob::getIndexFile() const
	{
		return strIndexFile;
	}

	void OneClickPostProcessingJob::setIndexFile(const QString &value)
	{
		strIndexFile = value;
	}
}
