#include "ffmsReader.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;

namespace MeGUI
{

	IMediaFile *ffmsFileFactory::Open(const std::string &file)
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

	int ffmsFileFactory::HandleLevel(const std::string &file)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (file.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".ffindex") || File::Exists(file + ".ffindex"))
			return 12;
		return -1;
	}

	const std::string &ffmsFileFactory::getID() const
	{
		return "ffms";
	}

	ffmsFile::ffmsFile(const std::string &fileName, const std::string &indexFile)
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
