#include "Shutdown.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;

namespace MeGUI
{

	bool Shutdown::NullShutdown::DoShutdown()
	{
		// FIXME: Do nothing would be best...
		return false;
	}

const std::string Shutdown::WindowsShutdown::SE_SHUTDOWN_NAME = "SeShutdownPrivilege";

	Shutdown::WindowsShutdown::WindowsShutdown()
	{
	}

	bool Shutdown::WindowsShutdown::DoShutdown()
	{
		bool success;
		TokPriv1Luid tp;
		void* hproc = GetCurrentProcess();
		void* htok = void*::Zero;
		success = OpenProcessToken(hproc, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, htok);
		tp.Count = 1;
		tp.Luid = 0;
		tp.Attr = SE_PRIVILEGE_ENABLED;
		success = LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, tp.Luid);
		success = AdjustTokenPrivileges(htok, false, tp, 0, void*::Zero, void*::Zero);
		return ExitWindowsEx(EWX_SHUTDOWN + EWX_FORCE, SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_NONE | SHTDN_REASON_FLAG_PLANNED);
	}

	Shutdown::Shutdown()
	{
		PlatformID *id = Environment::OSVersion::Platform;
		if (id == PlatformID::Win32NT || id == PlatformID::Win32S || id == PlatformID::Win32Windows || id == PlatformID::WinCE)
			instance = new WindowsShutdown();
		else
			instance = new NullShutdown();
	}

	bool Shutdown::shutdown()
	{
		return instance->DoShutdown();
	}
}
