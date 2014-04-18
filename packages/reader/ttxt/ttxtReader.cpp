#include "ttxtReader.h"




//using namespace System::Collections::Generic;



//using namespace System::Text;


using namespace MeXgui::core::util;

namespace MeXgui
{

	ttxtReader::ttxtReader(const QString &fileName)
	{
		this->fileName = fileName;
	}

	bool ttxtReader::readFileProperties(const QString &infoFile)
	{
		bool ttxtFileFound = false;
		QString line;

		try
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (StreamReader sr = new StreamReader(infoFile))
			StreamReader *sr = new StreamReader(infoFile);
			try
			{
				while ((line = sr->ReadLine()) != 0)
				{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
					if (line.StartsWith("<!-- GPAC 3GPP Text Stream -->"))
						ttxtFileFound = true;
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (sr != 0)
					sr.Dispose();
			}
		}
		catch (std::exception &i)
		{
			MessageBox::Show("The following error ocurred when parsing the ttxt file " + infoFile + "\r\n" + i.what(), "Error parsing ttxt file", MessageBoxButtons::OK);
		}

		return ttxtFileFound;
	}
}
