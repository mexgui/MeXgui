#include "idxReader.h"




//using namespace System::Collections::Generic;



//using namespace System::Text;


using namespace MeXgui::core::util;

namespace MeXgui
{

	idxReader::idxReader(const QString &fileName)
	{
		this->fileName = fileName;
	}

	void idxReader::readFileProperties(const QString &infoFile, QVector<SubtitleInfo*> &subtitles)
	{
		subtitles = QVector<SubtitleInfo*>();
		QString lng = "";
		int idx = 0;
		SubtitleInfo *si;
		bool bNewSubIDFound = false;
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
					if (line.StartsWith("id")) // Language & Index values found
					{
						lng = line.substr(4, 2);
						idx = StringConverterHelper::fromString<int>(line.substr(15, 1));
						bNewSubIDFound = true;
					}

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
					if (line.StartsWith("timestamp: ") && bNewSubIDFound) // to ensure to have a sub, not just an idx/lng
					{
						si = new SubtitleInfo(lng, idx);
						subtitles.push_back(si);
						bNewSubIDFound = false;
					}
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
			MessageBox::Show("The following error ocurred when parsing the idx file " + infoFile + "\r\n" + i.what(), "Error parsing idx file", MessageBoxButtons::OK);
		}
	}

	int idxReader::defaultLangIdx(const QString &idxFile)
	{
		int idx = 0;

		try
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (StreamReader sr = new StreamReader(idxFile))
			StreamReader *sr = new StreamReader(idxFile);
			try
			{
				QString line = sr->ReadLine();
				while (line != "")
				{
					line = sr->ReadLine();
					if (line != "")
					{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
						if (line.StartsWith("langidx:"))
							idx = StringConverterHelper::fromString<int>(line.substr(9));
					}
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
			MessageBox::Show("The following error ocurred when parsing the idx file " + idxFile + "\r\n" + i.what(), "Error parsing idx file", MessageBoxButtons::OK);
		}

		return idx;
	}
}
