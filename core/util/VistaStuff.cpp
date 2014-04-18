#include "VistaStuff.h"




//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;

//using namespace System::Runtime::InteropServices;

//using namespace System::Runtime::ConstrainedExecution;

//using namespace System::Text;

//using namespace System::Threading;
namespace MeXgui
{
	namespace core
	{
		namespace util
		{

			const bool &VistaStuff::getIsVistaOrNot() const
			{
				return Environment::OSVersion->Platform == PlatformID::Win32NT && Environment::OSVersion::Version::Major >= 6;
			}

			void VistaStuff::SetProcessPriority(IntPtr handle, ProcessPriorityClass *priority)
			{
				if (getIsVistaOrNot())
				{
					int prioIO = VistaStuff::PRIORITY_IO_NORMAL;
					int prioMemory = VistaStuff::PRIORITY_MEMORY_NORMAL;
					if (priority == ProcessPriorityClass::Idle || priority == ProcessPriorityClass::BelowNormal)
					{
						prioIO = VistaStuff::PRIORITY_IO_LOW;
						prioMemory = VistaStuff::PRIORITY_MEMORY_LOW;
						SetPriorityClass(handle, PROCESS_MODE_BACKGROUND_BEGIN);
					}
					else
						SetPriorityClass(handle, PROCESS_MODE_BACKGROUND_END);
					NtSetInformationProcess(handle, PROCESS_INFORMATION_IO_PRIORITY, prioIO, Marshal::SizeOf(prioIO));
					NtSetInformationProcess(handle, PROCESS_INFORMATION_MEMORY_PRIORITY, prioMemory, Marshal::SizeOf(prioMemory));
				}
			}

			void VistaStuff::SetThreadPriority(IntPtr handle, ThreadPriority *priority)
			{
				if (getIsVistaOrNot())
				{
					if (priority == ThreadPriority::Lowest || priority == ThreadPriority::BelowNormal)
						SetThreadPriority(handle, THREAD_MODE_BACKGROUND_BEGIN);
					else
						SetThreadPriority(handle, THREAD_MODE_BACKGROUND_END);
				}
			}
		}
	}
}
