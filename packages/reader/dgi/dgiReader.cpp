#include "dgiReader.h"








//using namespace System::Runtime::InteropServices;

//using namespace System::Xml::Serialization;

//using namespace System::Text::RegularExpressions;
using namespace MeXgui::core::util;

namespace MeXgui
{

	IMediaFile *dgiFileFactory::Open(const QString &file)
	{
		return new dgiFile(file);
	}

	int dgiFileFactory::HandleLevel(const QString &file)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (file.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".dgi"))
			return 12;
		return -1;
	}

	const QString &dgiFileFactory::getID() const
	{
		return "dgi";
	}

	dgiFile::dgiFile(const QString &fileName)
	{
		this->fileName = fileName;

		QString strScript = "";
		QString strPath = Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgnvIndexPath());
		strScript = "LoadPlugin(\"" + Path::Combine(strPath, "DGDecodeNV.dll") + "\")\r\nDGSource(\"" + this->fileName + "\"";
		if (MainForm::Instance->getSettings()->getAutoForceFilm() && MainForm::Instance->getSettings()->getForceFilmThreshold() <= static_cast<decimal>(dgiFile::GetFilmPercent(this->fileName)))
			strScript += ",fieldop=1)";
		else
			strScript += ",fieldop=0)";

		reader = AvsFile::ParseScript(strScript);

		this->readFileProperties();
	}

Regex *const dgiFile::r = new Regex("[0-9.]+(?=% FILM)");

	double dgiFile::GetFilmPercent(const QString &file)
	{
		double filmPercentage = -1.0;

		if (file.empty())
			return filmPercentage;

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

	void dgiFile::readFileProperties()
	{
		info = reader->getVideoInfo()->Clone();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (StreamReader sr = new StreamReader(fileName))
		StreamReader *sr = new StreamReader(fileName);
		try
		{
			QString line = "";
			int iLineCount = 0;
			while ((line = sr->ReadLine()) != 0)
			{
				if (iLineCount == 3)
				{
					QString strSourceFile = line.substr(0, line.rfind(" "));
					if (File::Exists(strSourceFile))
					{
						MediaInfoFile *oInfo = new MediaInfoFile(strSourceFile);
						info->DAR = oInfo->getVideoInfo()->DAR;
					}
					break;
				}
				iLineCount++;
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (sr != 0)
				sr.Dispose();
		}
	}

	const VideoInformation &dgiFile::getVideoInfo() const
	{
		return info;
	}

	const bool &dgiFile::getCanReadVideo() const
	{
		return reader->getCanReadVideo();
	}

	const bool &dgiFile::getCanReadAudio() const
	{
		return false;
	}

	IVideoReader *dgiFile::GetVideoReader()
	{
		return reader->GetVideoReader();
	}

	IAudioReader *dgiFile::GetAudioReader(int track)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	dgiFile::~dgiFile()
	{
		delete reader;
	}
}
