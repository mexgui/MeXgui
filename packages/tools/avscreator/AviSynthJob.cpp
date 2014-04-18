#include "AviSynthJob.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

	AviSynthJob::AviSynthJob() : Job()
	{
	}

	AviSynthJob::AviSynthJob(const QString &input) : Job(input, 0)
	{
	}

	const QString &AviSynthJob::getCodecString() const
	{
		return "";
	}

	const QString &AviSynthJob::getEncodingMode() const
	{
		return "avs";
	}
}
