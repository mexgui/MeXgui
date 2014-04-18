#include "ffmsReader.h"








//using namespace System::Runtime::InteropServices;

//using namespace System::Xml::Serialization;


using namespace MeXgui::core::util;

namespace MeXgui
{

	IMediaFile *ffmsFileFactory::Open(const QString &file)
	{
		if (file.find("|") != string::npos)
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			return new ffmsFile(file.Split('|')[0], file.Split('|')[1]);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		else if (file.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".ffindex"))
			return new ffmsFile(0, file);
		else
			return new ffmsFile(file, 0);
	}

	int ffmsFileFactory::HandleLevel(const QString &file)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (file.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".ffindex") || File::Exists(file + ".ffindex"))
			return 12;
		return -1;
	}

	const QString &ffmsFileFactory::getID() const
	{
		return "ffms";
	}

	ffmsFile::ffmsFile(const QString &fileName, const QString &indexFile)
	{
		if (!indexFile.empty() && fileName.empty())
		{
			this->fileName = indexFile.substr(0, indexFile.length() - 8);
			indexFile = "";
		}
		else
			this->fileName = fileName;

		double fps = 0;
		MediaInfoFile *oInfo = 0;
		if (File::Exists(this->fileName))
		{
			oInfo = new MediaInfoFile(this->fileName);
			if (oInfo->getVideoInfo()->HasVideo && oInfo->getVideoInfo()->FPS > 0)
				fps = oInfo->getVideoInfo()->FPS;
		}

		reader = AvsFile::ParseScript(VideoUtil::getFFMSInputLine(this->fileName, indexFile, fps));
		info = reader->getVideoInfo()->Clone();
		if (oInfo != 0)
			info->DAR = oInfo->getVideoInfo()->DAR;
	}

	const VideoInformation &ffmsFile::getVideoInfo() const
	{
		return info;
	}

	const bool &ffmsFile::getCanReadVideo() const
	{
		return reader->getCanReadVideo();
	}

	const bool &ffmsFile::getCanReadAudio() const
	{
		return false;
	}

	IVideoReader *ffmsFile::GetVideoReader()
	{
		return reader->GetVideoReader();
	}

	IAudioReader *ffmsFile::GetAudioReader(int track)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	ffmsFile::~ffmsFile()
	{
		delete reader;
	}
}
