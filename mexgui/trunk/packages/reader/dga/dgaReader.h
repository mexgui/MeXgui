#pragma once

#include "core/plugins/interfaces/IMediaFile.h"
#include "packages/reader/avs/AvsReader.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/gui/MeGUI.MainForm.h"
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

using namespace MeGUI::core::util;

namespace MeGUI
{
	class dgaFileFactory : public IMediaFileFactory
	{


	public:
		IMediaFile *Open(const std::string &file);

		int HandleLevel(const std::string &file);



		const std::string &getID() const;

	};

/// <summary>
	/// Summary description for dgaReader.
	/// </summary>
	class dgaFile : public IMediaFile
	{
	private:
		AvsFile *reader;
		std::string fileName;
		VideoInformation *info;

		/// <summary>
		/// initializes the dga reader
		/// </summary>
		/// <param name="fileName">the DGAVCIndex project file that this reader will process</param>
	public:
		dgaFile(const std::string &fileName);

		/// <summary>
		/// reads the dga file, which is essentially a text file
		/// </summary>
	private:
		void readFileProperties();
	public:
		const VideoInformation &getVideoInfo() const;


		const bool &getCanReadVideo() const;

		const bool &getCanReadAudio() const;

		IVideoReader *GetVideoReader();

		IAudioReader *GetAudioReader(int track);



		~dgaFile();

	};
}
