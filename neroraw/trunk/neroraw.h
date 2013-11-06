#pragma once

#include <string>
#include <iostream>
#include <stdexcept>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::CompilerServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;

// General Information about an assembly is controlled through the following 
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyTitle("neroraw")]
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyDescription("encodes RAW PCM data from stdin using Nero AAC")]
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyConfiguration("")]
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyCompany("www.doom9.net")]
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyCopyright("Licensed under the GPL")]
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyProduct("neroraw")]
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyTrademark("")]
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyCulture("")]

// Setting ComVisible to false makes the types in this assembly not visible 
// to COM components.  If you need to access a type in this assembly from 
// COM, set the ComVisible attribute to true on that type.
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: ComVisible(false)]


// Version information for an assembly consists of the following four values:
//
//      Major Version
//      Minor Version 
//      Build Number
//      Revision
//
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyVersion("0.0.2.1")]
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[assembly: AssemblyFileVersion("0.0.2.1")]

namespace MeGUI
{
	class NeroRawAacEncoder
	{
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("bsn.dll", CallingConvention = CallingConvention::Cdecl, ExactSpelling = true, CharSet = CharSet::Ansi, SetLastError = false)]
	private:
		__declspec(dllimport) static int BSN_Init(int &nSampleRate, int nChannelsCount, const std::string &sOutFileName, int nBitsPerSample, int nShowDialog, const std::string &path, std::string& argv[], int argc);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("bsn.dll", CallingConvention = CallingConvention::Cdecl, ExactSpelling = true, CharSet = CharSet::Ansi)]
		__declspec(dllimport) static void BSN_DeInit();

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("bsn.dll", CallingConvention = CallingConvention::Cdecl, ExactSpelling = true, CharSet = CharSet::Ansi)]
		__declspec(dllimport) static int BSN_EncodeBlock(IntPtr pBuf, unsigned int blockSizeRead);

		static int showUsage();

	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[STAThread]
		static int Main(std::string& args[]);

	private:
		static void killRegistryKey();

	};
}
