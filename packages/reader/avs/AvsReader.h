#pragma once

#include "core/plugins/interfaces/IMediaFile.h"
#include "packages/tools/avscreator/AvisynthWrapper.h"
#include "core/gui/MeXgui.MainForm.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "packages/tools/chaptercreator/MplsExtractor.h"
#include "core/util/DAR.h"
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




//using namespace System::Collections::Generic;



//using namespace System::Text;



using namespace MeXgui::core::util;

namespace MeXgui
{
	class AvsFileFactory : public IMediaFileFactory
	{


	public:
        IMediaFile *Open(const QString &file);



        int HandleLevel(const QString &file);



        const QString &getID() const;

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

			BitQMap *ReadFrameBitQMap(int position);

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
			const qint64 &getSampleCount() const;

			const bool &getSupportsFastReading() const;

			qint64 ReadAudioSamples(qint64 nStart, int nAmount, IntPtr buf);

			unsigned char *ReadAudioSamples(qint64 nStart, int nAmount);
		};

	private:
		AviSynthClip *clip;
		AviSynthScriptEnvironment *enviroment;
		IAudioReader *audioReader;
		IVideoReader *videoReader;
		VideoInformation *info;
	public:
		const AviSynthClip &getClip() const;

        static AvsFile *OpenScriptFile(const QString &fileName);

        static AvsFile *ParseScript(const QString &scriptBody);

	private:
        AvsFile(const QString &script, bool parse);

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
