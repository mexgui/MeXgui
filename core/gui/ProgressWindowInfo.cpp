#include "ProgressWindowInfo.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
namespace MeGUI
{
	namespace core
	{
		namespace plugins
		{
			namespace interfaces
			{

				ProgressWindowInfo::ProgressWindowInfo(const QString &pLabel, const QString &dataLabel, const QString &rateLabel, const QString &rateUnit, const QString &name)
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
