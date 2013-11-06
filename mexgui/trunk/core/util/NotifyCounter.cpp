#include "NotifyCounter.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

			NotifyCounter::AutoCloser::AutoCloser(NotifyCounter *counter)
			{
				this->counter = counter;
				counter->Increment();
			}

			NotifyCounter::AutoCloser::~AutoCloser()
			{
				counter->Decrement();
			}

			const bool &NotifyCounter::getReady() const
			{
				return (count == 0);
			}

			void NotifyCounter::Increment()
			{
				count++;
			}

			void NotifyCounter::Decrement()
			{
				assert(count > 0);
				count--;
			}

			IDisposable *NotifyCounter::Wrap()
			{
				return new AutoCloser(this);
			}

			void NotifyCounter::InitializeInstanceFields()
			{
				count = 0;
			}
		}
	}
}
