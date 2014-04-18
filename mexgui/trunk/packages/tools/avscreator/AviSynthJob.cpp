#include "AviSynthJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	AviSynthJob::AviSynthJob() : Job()
	{
	}

	AviSynthJob::AviSynthJob(const std::string &input) : Job(input, 0)
	{
	}

	const std::string &AviSynthJob::getCodecString() const
	{
		return "";
	}

	const std::string &AviSynthJob::getEncodingMode() const
	{
		return "avs";
	}
}
