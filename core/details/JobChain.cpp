#include "JobChain.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
namespace MeXgui
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
