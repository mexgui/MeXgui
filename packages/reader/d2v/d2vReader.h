#pragma once

#include "core/plugins/interfaces/IMediaFile.h"
#include "packages/reader/avs/AvsReader.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/gui/MainForm.h"
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
	enum FieldOperation
	{
		NONE = 0,
		FF,
		RAW
	};

	class d2vFileFactory : public IMediaFileFactory
	{

	public:
		IMediaFile *Open(const QString &file);

		int HandleLevel(const QString &file);

		const QString &getID() const;
	};

	/// <summary>
	/// Summary description for d2vReader.
	/// </summary>
	class d2vFile : public IMediaFile
	{
	private:
		AvsFile *reader;
		QString fileName;
		int fieldOperation;
		VideoInformation *info;
		double filmPercentage;

		static System::Text::RegularExpressions::Regex *const r;

	public:
		static double GetFilmPercent(const QString &file);

		/// <summary>
		/// initializes the d2v reader
		/// </summary>
		/// <param name="fileName">the dvd2avi project file that this reader will process</param>
		d2vFile(const QString &fileName);

		/// <summary>
		/// reads the d2v file, which is essentially a text file
		/// the first few lines contain the video properties in plain text and the 
		/// last line contains the film percentage
		/// this method reads all this information and stores it internally, then 
		/// closes the d2v file again
		/// </summary>
	private:
		void readFileProperties();

	public:
		const VideoInformation &getVideoInfo() const;

		/// <summary>
		/// returns the percentage of film of this source
		/// </summary>
		const double &getFilmPercentage() const;

		/// <summary>
		/// returns the field operation performed on this source
		/// </summary>
		const int &getFieldOperation() const;

		const bool &getCanReadVideo() const;

		const bool &getCanReadAudio() const;

		IVideoReader *GetVideoReader();

		IAudioReader *GetAudioReader(int track);

		~d2vFile();
	};
}
