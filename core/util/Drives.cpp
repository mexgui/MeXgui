#include "Drives.h"






//using namespace System::Collections::Generic;

//using namespace System::Runtime::InteropServices;

//using namespace System::Text;

namespace MeXgui
{

	bool Drives::ableToWriteOnThisDrive(const QString &myDrive)
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
