#pragma once

#include <QString>
#include <stdexcept>
#include "stringconverter.h"

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
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






//using namespace System::Diagnostics;

//using namespace System::Management;

//using namespace System::Runtime::InteropServices;



namespace MeXgui
{
	/// <summary>
	/// OSInfo Class based from http://www.codeproject.com/csharp/osversion_producttype.asp
	/// </summary>
	class OSInfo
	{
	private:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential)]
		class OSVERSIONINFOEX
		{
		public:
			int dwOSVersionInfoSize;
			int dwMajorVersion;
			int dwMinorVersion;
			int dwBuildNumber;
			int dwPlatformId;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::ByValTStr, SizeConst = 128)]
			QString szCSDVersion;
			short wServicePackMajor;
			short wServicePackMinor;
			short wSuiteMask;
			unsigned char wProductType;
			unsigned char wReserved;
		};

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll")]
	private:
		__declspec(dllimport) static bool GetVersionEx(OSVERSIONINFOEX &osVersionInfo);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll")]
		__declspec(dllimport) static bool GetProductInfo(int dwOSMajorVersion, int dwOSMinorVersion, int dwSpMajorVersion, int dwSpMinorVersion, unsigned int &pdwReturnedProductType);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll", SetLastError = true, CallingConvention = CallingConvention::Winapi), return: MarshalAs(UnmanagedType::Bool)]
	public:
//ORIGINAL LINE: public static extern bool IsWow64Process([In] IntPtr hProcess, [Out] out bool lpSystemInfo);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		__declspec(dllimport) static bool IsWow64Process(IntPtr hProcess, bool &lpSystemInfo);

	private:
		static const int VER_NT_WORKSTATION = 1;
		static const int VER_NT_DOMAIN_CONTROLLER = 2;
		static const int VER_NT_SERVER = 3;
		static const int VER_SUITE_SMALLBUSINESS = 1;
		static const int VER_SUITE_ENTERPRISE = 2;
		static const int VER_SUITE_TERMINAL = 16;
		static const int VER_SUITE_DATACENTER = 128;
		static const int VER_SUITE_SINGLEUSERTS = 256;
		static const int VER_SUITE_PERSONAL = 512;
		static const int VER_SUITE_BLADE = 1024;
		static const int PRODUCT_UNDEFINED = 0x00000000;
		static const int PRODUCT_ULTIMATE = 0x00000001;
		static const int PRODUCT_HOME_BASIC = 0x00000002;
		static const int PRODUCT_HOME_PREMIUM = 0x00000003;
		static const int PRODUCT_ENTERPRISE = 0x00000004;
		static const int PRODUCT_ENTERPRISE_N = 0x0000001B;
		static const int PRODUCT_HOME_BASIC_N = 0x00000005;
		static const int PRODUCT_BUSINESS = 0x00000006;
		static const int PRODUCT_BUSINESS_N = 0x00000010;
		static const int PRODUCT_STARTER = 0x0000000B;
		static const int PRODUCT_PROFESSIONAL = 0x00000030;
		static const int PRODUCT_PROFESSIONAL_N = 0x00000031;
		static const int PRODUCT_PROFESSIONAL_WMC = 0x00000067;
		static const int PRODUCT_CORE = 0x00000065;
		static const int PRODUCT_CORE_N = 0x00000062;
		static const int PRODUCT_CORE_COUNTRYSPECIFIC = 0x00000063;

		/// <summary>
		/// Determines whether the specified process is running under WOW64. 
		/// </summary>
		/// <returns>a boolean</returns>
	public:
		static bool isWow64();

		/// <summary>
		/// Returns the service pack information of the operating system running on this computer.
		/// </summary>
		/// <returns>A string containing the operating system service pack information.</returns>
		static QString GetOSServicePack();

		/// <summary>
		/// Returns the name of the operating system running on this computer.
		/// </summary>
		/// <returns>A string containing the the operating system name.</returns>
		static QString GetOSName();

		/// <summary>
		/// Returns the name of the dotNet Framework running on this computer.
		/// </summary>
		/// <returns>A string containing the Name of the Framework Version.</returns>
		/// 
		static QString GetDotNetVersion();

		/// <summary>
		/// Returns the name of the dotNet Framework running on this computer.
		/// </summary>
		/// <param name="getSpecificVersion">if not empty only the specified version and if empty the highest version will be returned</param>
		/// <returns>A string containing the Name of the Framework Version.</returns>
		/// 
		static QString GetDotNetVersion(const QString &getSpecificVersion);

		/// <summary>
		/// Returns the name of the dotNet Framework formated
		/// </summary>
		/// <returns>A string containing the dotNet Framework</returns>
		/// 
		static QString DotNetVersionFormated(const QString &dotNetVersion);

		/// <summary>
		/// Get some stuff from the Management Object Queries
		/// </summary>
		/// <returns>A string containing the result of the MO query.</returns>
		/// 
		static QString GetMOStuff(const QString &queryObject);

		/// <summary>
		/// Gets the full version of the operating system running on this computer.
		/// </summary>
		const static QString &getOSVersion() const;

		/// <summary>
		/// Gets the major version of the operating system running on this computer.
		/// </summary>
		const static int &getOSMajorVersion() const;

		/// <summary>
		/// Gets the minor version of the operating system running on this computer.
		/// </summary>
		const static int &getOSMinorVersion() const;

		/// <summary>
		/// Gets the build version of the operating system running on this computer.
		/// </summary>
		const static int &getOSBuildVersion() const;

		/// <summary>
		/// Gets the revision version of the operating system running on this computer.
		/// </summary>
		const static int &getOSRevisionVersion() const;
	};
}
