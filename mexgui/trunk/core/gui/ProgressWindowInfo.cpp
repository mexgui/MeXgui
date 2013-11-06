#include "ProgressWindowInfo.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
namespace MeGUI
{
	namespace core
	{
		namespace plugins
		{
			namespace interfaces
			{

				ProgressWindowInfo::ProgressWindowInfo(const std::string &pLabel, const std::string &dataLabel, const std::string &rateLabel, const std::string &rateUnit, const std::string &name)
				{
					this->ProgressLabel = pLabel;
					this->DataLabel = dataLabel;
					this->RateLabel = rateLabel;
					this->RateUnit = rateUnit;
					this->Name = name;
				}
			}
		}
	}
}
