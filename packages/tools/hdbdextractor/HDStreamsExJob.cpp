#include "HDStreamsExJob.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

	HDStreamsExJob::HDStreamsExJob() : Job()
	{
		featureNb = "";
		args = "";
		inputType = 1;
		source = QVector<QString>();
	}

	HDStreamsExJob::HDStreamsExJob(QVector<QString> &input, const QString &ouput, const QString &featureNb, const QString &args, int inputType)
	{
		Input = input[0];
		source = input;
		Output = ouput;
		setFeatureNb(featureNb);
		setArgs(args);
		setInputType(inputType);
	}

	const QString &HDStreamsExJob::getFeatureNb() const
	{
		return featureNb;
	}

	void HDStreamsExJob::setFeatureNb(const QString &value)
	{
		featureNb = value;
	}

	const QString &HDStreamsExJob::getArgs() const
	{
		return args;
	}

	void HDStreamsExJob::setArgs(const QString &value)
	{
		args = value;
	}

	const QVector<QString> &HDStreamsExJob::getSource() const
	{
		return source;
	}

	void HDStreamsExJob::setSource(const QVector<QString> &value)
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

	const QString &HDStreamsExJob::getCodecString() const
	{
		return "eac3to";
	}

	const QString &HDStreamsExJob::getEncodingMode() const
	{
		return "ext";
	}
}
