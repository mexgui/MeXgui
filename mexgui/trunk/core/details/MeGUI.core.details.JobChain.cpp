#include "MeGUI.core.details.JobChain.h"

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
		namespace details
		{

			JobChain::operator JobChain*(Job *j)
			{
				return new JobDependencyChain(j);
			}
		}
	}
}
