#include "DVDD_File.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
namespace MeGUI
{
	namespace packages
	{
		namespace reader
		{
			namespace dvddecrypter
			{

				MeGUI::IMediaFile *DVDD_FileFactory::Open(const std::string &file)
				{
					throw std::exception("The method or operation is not implemented.");
				}

				int DVDD_FileFactory::HandleLevel(const std::string &file)
				{
					throw std::exception("The method or operation is not implemented.");
				}

				const std::string &DVDD_FileFactory::getID() const
				{
					return "DVDDecrypterFile";
				}
			}
		}
	}
}
