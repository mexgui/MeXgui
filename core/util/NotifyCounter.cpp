#include "NotifyCounter.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;

//using namespace System::Text;
namespace MeXgui
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
