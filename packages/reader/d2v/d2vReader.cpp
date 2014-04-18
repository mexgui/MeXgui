#include "d2vReader.h"








//using namespace System::Runtime::InteropServices;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::util;

namespace MeXgui
{

	IMediaFile *d2vFileFactory::Open(const QString &file)
	{
		return new d2vFile(file);
	}

	int d2vFileFactory::HandleLevel(const QString &file)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (file.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".d2v"))
			return 10;
		return -1;
	}

	const QString &d2vFileFactory::getID() const
	{
		return "d2v";
	}

System::Text::RegularExpressions::Regex *const d2vFile::r = new System::Text::RegularExpressions::Regex("(?<=FINISHED +)[0-9.]+(?=% FILM)");

	double d2vFile::GetFilmPercent(const QString &file)
	{
		double filmPercentage = -1.0;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (StreamReader sr = new StreamReader(file))
		StreamReader *sr = new StreamReader(file);
		try
		{
			QString line = sr->ReadLine();
			while ((line = sr->ReadLine()) != 0)
				if (r->IsMatch(line))
					filmPercentage = double::Parse(r->Match(line)->Value, System::Globalization::CultureInfo::InvariantCulture);
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (sr != 0)
				sr.Dispose();
		}
		return filmPercentage;
	}

	d2vFile::d2vFile(const QString &fileName)
	{
		this->fileName = fileName;
		QString strPath = Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgIndexPath());
		QString strDLL = Path::Combine(strPath, "DGDecode.dll");
		reader = AvsFile::ParseScript("LoadPlugin(\"" + strDLL + "\")\r\nDGDecode_Mpeg2Source(\"" + this->fileName + "\")");
		this->readFileProperties();
	}

	void d2vFile::readFileProperties()
	{
		info = reader->getVideoInfo()->Clone();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (StreamReader sr = new StreamReader(fileName))
		StreamReader *sr = new StreamReader(fileName);
		try
		{
			int iLineCount = 0;
			QString line = "";
			while ((line = sr->ReadLine()) != 0)
			{
				iLineCount++;
				if (iLineCount == 3)
				{
					QString strSourceFile = line;
					if (File::Exists(strSourceFile))
					{
						MediaInfoFile *oInfo = new MediaInfoFile(strSourceFile);
						info->DAR = oInfo->getVideoInfo()->DAR;
					}
				}
				if (line.find("Field_Operation") != -1)
				{
					QString fieldOp = line.substr(16, 1);
					this->fieldOperation = int::Parse(fieldOp);
				}
				else if (line.find("FINISHED") != -1 && line.find("FILM") != -1) // dgindex now reports VIDEO % if it's > 50%
				{
					int end = line.find("%");
					QString percentage = line.substr(10, end - 10);
					this->filmPercentage = double::Parse(percentage, System::Globalization::CultureInfo::InvariantCulture);
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

	const VideoInformation &d2vFile::getVideoInfo() const
	{
		return info;
	}

	const double &d2vFile::getFilmPercentage() const
	{
		return this->filmPercentage;
	}

	const int &d2vFile::getFieldOperation() const
	{
		return this->fieldOperation;
	}

	const bool &d2vFile::getCanReadVideo() const
	{
		return reader->getCanReadVideo();
	}

	const bool &d2vFile::getCanReadAudio() const
	{
		return false;
	}

	IVideoReader *d2vFile::GetVideoReader()
	{
		return reader->GetVideoReader();
	}

	IAudioReader *d2vFile::GetAudioReader(int track)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	d2vFile::~d2vFile()
	{
		delete reader;
	}
}
