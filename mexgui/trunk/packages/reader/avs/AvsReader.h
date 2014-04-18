#pragma once

#include "core/plugins/interfaces/IMediaFile.h"
#include "packages/tools/avscreator/AvisynthWrapper.h"
#include "core/gui/MeGUI.MainForm.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "packages/tools/chaptercreator/MplsExtractor.h"
#include "core/util/DAR.h"
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
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::util;

namespace MeGUI
{
	class AvsFileFactory : public IMediaFileFactory
	{


	public:
		IMediaFile *Open(const std::string &file);



		int HandleLevel(const std::string &file);



		const std::string &getID() const;

	};
	class AvsFile : public IMediaFile
	{
	private:
		class AvsVideoReader : public IVideoReader
		{
		public:
			AvsVideoReader(AviSynthClip *clip, int width, int height);
		private:
			AviSynthClip *clip;
			int width, height;

		public:
			const int &getFrameCount() const;

			Bitmap *ReadFrameBitmap(int position);

		private:
			void InitializeInstanceFields();
		};
	private:
		class AvsAudioReader : public IAudioReader
		{
		public:
			AvsAudioReader(AviSynthClip *clip);
		private:
			AviSynthClip *clip;
		public:
			const long long &getSampleCount() const;

			const bool &getSupportsFastReading() const;

			long long ReadAudioSamples(long long nStart, int nAmount, IntPtr buf);

			unsigned char *ReadAudioSamples(long long nStart, int nAmount);
		};

	private:
		AviSynthClip *clip;
		AviSynthScriptEnvironment *enviroment;
		IAudioReader *audioReader;
		IVideoReader *videoReader;
		VideoInformation *info;
	public:
		const AviSynthClip &getClip() const;

		static AvsFile *OpenScriptFile(const std::string &fileName);

		static AvsFile *ParseScript(const std::string &scriptBody);

	private:
		AvsFile(const std::string &script, bool parse);

		void cleanup();
	public:
		const VideoInformation &getVideoInfo() const;
		const bool &getCanReadVideo() const;
		const bool &getCanReadAudio() const;
		IAudioReader *GetAudioReader(int track);
		IVideoReader *GetVideoReader();

		~AvsFile();


	private:
		void InitializeInstanceFields();
	};
}
