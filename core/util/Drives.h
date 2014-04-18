#pragma once

#include <QString>






//using namespace System::Collections::Generic;

//using namespace System::Runtime::InteropServices;

//using namespace System::Text;

namespace MeXgui
{
	class Drives
	{
	public:
		static bool ableToWriteOnThisDrive(const QString &myDrive);

		// used to send string message to media control interface device (mci)
		// like cd rom
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("winmm.dll", EntryPoint = "mciSendStringA")]
		__declspec(dllimport) static int mciSendString(const QString &lpstrCommand, const QString &lpstrReturnString, int uReturnLength, int hwndCallback);

		// used to get information about a drive ex: its name, seial number
		// if this function return zero means that one of the information could not be retrieved
		// so if it is a CD ROM drive and we can't obtain its name ---> CD ROM is empty
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll", EntryPoint = "GetVolumeInformationA")]
		__declspec(dllimport) static int GetVolumeInformation(const QString &lpRootPathName, StringBuilder *lpVolumeNameBuffer, int nVolumeNameSize, int lpVolumeSerialNumber, int lpMaximumComponentLength, int lpFileSystemFlags, const QString &lpFileSystemNameBuffer, int nFileSystemNameSize);

		// get the drive type 
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll", EntryPoint = "GetDriveTypeA")]
		__declspec(dllimport) static int GetDriveType(const QString &nDrive);
	};
}
