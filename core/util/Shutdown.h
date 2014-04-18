#pragma once

#include <QString>

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************




//using namespace System::Runtime::InteropServices;

namespace MeXgui
{
	class Shutdown
	{
	private:
		class NullShutdown : public Shutdown
		{
		public:
			virtual bool DoShutdown();
		};

	private:
		class WindowsShutdown : public Shutdown
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential, Pack = 1)]
			class TokPriv1Luid
			{
			public:
				int Count;
				qint64 Luid;
				int Attr;
			};

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll", ExactSpelling = true)]
	public:
		__declspec(dllimport) static IntPtr GetCurrentProcess();

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("advapi32.dll", ExactSpelling = true, SetLastError = true)]
		__declspec(dllimport) static bool OpenProcessToken(IntPtr h, int acc, IntPtr &phtok);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("advapi32.dll", SetLastError = true)]
		__declspec(dllimport) static bool LookupPrivilegeValue(const QString &host, const QString &name, qint64 &pluid);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("advapi32.dll", ExactSpelling = true, SetLastError = true)]
		__declspec(dllimport) static bool AdjustTokenPrivileges(IntPtr htok, bool disall, TokPriv1Luid &newst, int len, IntPtr prev, IntPtr relen);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("user32.dll", ExactSpelling = true, SetLastError = true)]
		__declspec(dllimport) static bool ExitWindowsEx(int flg, unsigned int rea);

	private:
		static const int SE_PRIVILEGE_ENABLED = 0x00000002;
		static const int TOKEN_QUERY = 0x00000008;
		static const int TOKEN_ADJUST_PRIVILEGES = 0x00000020;
		static const QString SE_SHUTDOWN_NAME;
		static const int EWX_SHUTDOWN = 0x00000001;
		static const int EWX_REBOOT = 0x00000002;
		static const int EWX_FORCE = 0x00000004;
		static const int EWX_POWEROFF = 0x00000008;
		static const int EWX_FORCEIFHUNG = 0x00000010;

		static const unsigned int SHTDN_REASON_MAJOR_OPERATINGSYSTEM = 0x00020000;
		static const unsigned int SHTDN_REASON_MAJOR_APPLICATION = 0x00040000;
		static const unsigned int SHTDN_REASON_MAJOR_SYSTEM = 0x00050000;

		static const unsigned int SHTDN_REASON_MINOR_MAINTENANCE = 0x00000001;
		static const unsigned int SHTDN_REASON_MINOR_NONE = 0x000000ff;
		static const unsigned int SHTDN_REASON_MINOR_UPGRADE = 0x00000003;

		static const unsigned int SHTDN_REASON_FLAG_PLANNED = 0x80000000;

	public:
		WindowsShutdown();

		virtual bool DoShutdown();
		};
	private:
		static Shutdown *instance;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static Shutdown();

	public:
		virtual bool DoShutdown() = 0;

		static bool shutdown();

		/// <summary>
		/// Summary description for Shutdown.
		/// </summary>
	};
}
