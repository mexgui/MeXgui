#pragma once

#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{
	class Drives
	{
	public:
		static bool ableToWriteOnThisDrive(const std::string &myDrive);

		// used to send string message to media control interface device (mci)
		// like cd rom
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("winmm.dll", EntryPoint = "mciSendStringA")]
		__declspec(dllimport) static int mciSendString(const std::string &lpstrCommand, const std::string &lpstrReturnString, int uReturnLength, int hwndCallback);

		// used to get information about a drive ex: its name, seial number
		// if this function return zero means that one of the information could not be retrieved
		// so if it is a CD ROM drive and we can't obtain its name ---> CD ROM is empty
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll", EntryPoint = "GetVolumeInformationA")]
		__declspec(dllimport) static int GetVolumeInformation(const std::string &lpRootPathName, StringBuilder *lpVolumeNameBuffer, int nVolumeNameSize, int lpVolumeSerialNumber, int lpMaximumComponentLength, int lpFileSystemFlags, const std::string &lpFileSystemNameBuffer, int nFileSystemNameSize);

		// get the drive type 
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll", EntryPoint = "GetDriveTypeA")]
		__declspec(dllimport) static int GetDriveType(const std::string &nDrive);
	};
}
