#include "HDStreamsExJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	HDStreamsExJob::HDStreamsExJob() : Job()
	{
		featureNb = "";
		args = "";
		inputType = 1;
		source = std::vector<std::string>();
	}

	HDStreamsExJob::HDStreamsExJob(std::vector<std::string> &input, const std::string &ouput, const std::string &featureNb, const std::string &args, int inputType)
	{
		Input = input[0];
		source = input;
		Output = ouput;
		setFeatureNb(featureNb);
		setArgs(args);
		setInputType(inputType);
	}

	const std::string &HDStreamsExJob::getFeatureNb() const
	{
		return featureNb;
	}

	void HDStreamsExJob::setFeatureNb(const std::string &value)
	{
		featureNb = value;
	}

	const std::string &HDStreamsExJob::getArgs() const
	{
		return args;
	}

	void HDStreamsExJob::setArgs(const std::string &value)
	{
		args = value;
	}

	const std::vector<std::string> &HDStreamsExJob::getSource() const
	{
		return source;
	}

	void HDStreamsExJob::setSource(const std::vector<std::string> &value)
	{
		source = value;
	}

	const int &HDStreamsExJob::getInputType() const
	{
		return inputType;
	}

	void HDStreamsExJob::setInputType(const int &value)
	{
		inputType = value;
	}

	const std::string &HDStreamsExJob::getCodecString() const
	{
		return "eac3to";
	}

	const std::string &HDStreamsExJob::getEncodingMode() const
	{
		return "ext";
	}
}
