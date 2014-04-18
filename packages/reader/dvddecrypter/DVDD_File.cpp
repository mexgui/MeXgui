#include "DVDD_File.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
namespace MeXgui
{
	namespace packages
	{
		namespace reader
		{
			namespace dvddecrypter
			{

				MeXgui::IMediaFile *DVDD_FileFactory::Open(const QString &file)
				{
					throw std::exception("The method or operation is not implemented.");
				}

				int DVDD_FileFactory::HandleLevel(const QString &file)
				{
					throw std::exception("The method or operation is not implemented.");
				}

				const QString &DVDD_FileFactory::getID() const
				{
					return "DVDDecrypterFile";
				}
			}
		}
	}
}
