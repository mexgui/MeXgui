#include "Drives.h"

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

	bool Drives::ableToWriteOnThisDrive(const std::string &myDrive)
	{
		bool b = false;
		switch (GetDriveType(myDrive))
		{
			case 0: // Unknown
			case 1: // Invalid Path
			case 5: // CDROM
			case 6: // RAM
					b = false;
					break;
			case 2: // Removable (floppy, drive)
			case 3: // Fixed (hard drive)
			case 4: // Remote (Network drive)
					b = true;
					break;
		}
		return b;
	}
}
