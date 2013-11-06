#pragma once

#include "core/plugins/interfaces/IMediaFile.h"
#include "packages/reader/avs/AvsReader.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/VideoUtil.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include <string>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************

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
	class ffmsFileFactory : public IMediaFileFactory
	{


	public:
		IMediaFile *Open(const std::string &file);

		int HandleLevel(const std::string &file);



		const std::string &getID() const;

	};

	/// <summary>
	/// Summary description for ffmsReader.
	/// </summary>
	class ffmsFile : public IMediaFile
	{
	private:
		AvsFile *reader;
		std::string fileName;
		VideoInformation *info;

		/// <summary>
		/// initializes the ffms reader
		/// </summary>
		/// <param name="fileName">the FFMSIndex source file file that this reader will process</param>
		/// <param name="indexFile">the FFMSIndex index file that this reader will process</param>
	public:
		ffmsFile(const std::string &fileName, const std::string &indexFile);

		const VideoInformation &getVideoInfo() const;


		const bool &getCanReadVideo() const;

		const bool &getCanReadAudio() const;

		IVideoReader *GetVideoReader();

		IAudioReader *GetAudioReader(int track);



		~ffmsFile();

	};
}

