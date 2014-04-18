#include "dgaReader.h"








//using namespace System::Runtime::InteropServices;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::util;

namespace MeXgui
{

	IMediaFile *dgaFileFactory::Open(const QString &file)
	{
		return new dgaFile(file);
	}

	int dgaFileFactory::HandleLevel(const QString &file)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (file.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".dga"))
			return 11;
		return -1;
	}

	const QString &dgaFileFactory::getID() const
	{
		return "dga";
	}

	dgaFile::dgaFile(const QString &fileName)
	{
		this->fileName = fileName;
		QString strPath = Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgavcIndexPath());
		QString strDLL = Path::Combine(strPath, "DGAVCDecode.dll");
		reader = AvsFile::ParseScript("LoadPlugin(\"" + strDLL + "\")\r\nAVCSource(\"" + this->fileName + "\")");
		this->readFileProperties();
	}

	void dgaFile::readFileProperties()
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
					break;
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

	const VideoInformation &dgaFile::getVideoInfo() const
	{
		return info;
	}

	const bool &dgaFile::getCanReadVideo() const
	{
		return reader->getCanReadVideo();
	}

	const bool &dgaFile::getCanReadAudio() const
	{
		return false;
	}

	IVideoReader *dgaFile::GetVideoReader()
	{
		return reader->GetVideoReader();
	}

	IAudioReader *dgaFile::GetAudioReader(int track)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	dgaFile::~dgaFile()
	{
		delete reader;
	}
}
