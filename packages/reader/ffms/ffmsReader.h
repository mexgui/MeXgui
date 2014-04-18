#pragma once

#include "core/plugins/interfaces/IMediaFile.h"
#include "packages/reader/avs/AvsReader.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/VideoUtil.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include <QString>
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








//using namespace System::Runtime::InteropServices;

//using namespace System::Xml::Serialization;



using namespace MeXgui::core::util;

namespace MeXgui
{
	class ffmsFileFactory : public IMediaFileFactory
	{


	public:
		IMediaFile *Open(const QString &file);

		int HandleLevel(const QString &file);



		const QString &getID() const;

	};

	/// <summary>
	/// Summary description for ffmsReader.
	/// </summary>
	class ffmsFile : public IMediaFile
	{
	private:
		AvsFile *reader;
		QString fileName;
		VideoInformation *info;

		/// <summary>
		/// initializes the ffms reader
		/// </summary>
		/// <param name="fileName">the FFMSIndex source file file that this reader will process</param>
		/// <param name="indexFile">the FFMSIndex index file that this reader will process</param>
	public:
		ffmsFile(const QString &fileName, const QString &indexFile);

		const VideoInformation &getVideoInfo() const;


		const bool &getCanReadVideo() const;

		const bool &getCanReadAudio() const;

		IVideoReader *GetVideoReader();

		IAudioReader *GetAudioReader(int track);



		~ffmsFile();

	};
}

