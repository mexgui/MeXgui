#pragma once

#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MeGUI.MainForm.h"
#include "AudioJob.h"
#include "aften/AftenSettings.h"
#include "ffac3/AC3Settings.h"
#include "ffmp2/MP2Settings.h"
#include "flac/FlacSettings.h"
#include "lame/MP3Settings.h"
#include "naac/NeroAACSettings.h"
#include "opus/OpusSettings.h"
#include "qaac/QaacSettings.h"
#include "vorbis/OggVorbisSettings.h"
#include "MeGUI.Properties.Settings.h"
#include "core/util/LogItem.h"
#include "core/details/MeGUISettings.h"
#include "core/details/StatusUpdate.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/FileSize.h"
#include "core/plugins/implemented/CommandlineJobProcessor.h"
#include "packages/tools/avscreator/AvisynthWrapper.h"
#include "core/util/Util.h"
#include "core/util/AudioUtil.h"
#include "core/util/FileUtil.h"
#include "AudioCodecSettings.h"
#include "core/util/Exceptions.h"
#include "core/util/FilmCutter.h"
#include "core/util/VistaStuff.h"
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
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
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::util;

using namespace MediaInfoWrapper;

namespace MeGUI
{
	class AviSynthAudioEncoder : public IJobProcessor // : AudioEncoder
	{
	public:
		static JobProcessorFactory *const Factory;

	private:
		static IJobProcessor *init(MainForm *mf, Job *j);

		Process *_encoderProcess;
		std::string _avisynthAudioScript;
		std::string _encoderExecutablePath;
		std::string _encoderCommandLine;
		bool _mustSendWavHeaderToEncoderStdIn;

		int _sampleRate;

		ManualResetEvent *_mre; // lock used to pause encoding
		Thread *_encoderThread;

		ManualResetEvent *stdoutDone;
		ManualResetEvent *stderrDone;
		Thread *_readFromStdOutThread;
		Thread *_readFromStdErrThread;
		LogItem *stdoutLog;
		LogItem *stderrLog;
		LogItem *_log;
		std::string _encoderStdErr;
		static System::Text::RegularExpressions::Regex *const _cleanUpStringRegex;

		MeGUISettings *_settings;
		int SAMPLES_PER_UPDATE;
		AudioJob *audioJob;
		StatusUpdate *su;
		DateTime _start;

		std::vector<std::string> _tempFiles;
		const std::string _uniqueId;


		void writeTempTextFile(const std::string &filePath, const std::string &text);

		void deleteTempFiles();

		static void safeDelete(const std::string &filePath);

		void createTemporallyEqFiles(const std::string &tempPath);

		void raiseEvent();

		void setProgress(decimal n);

		void updateTime();

		void raiseEvent(const std::string &s);

	public:
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		AviSynthAudioEncoder(MeGUISettings *settings);

	private:
		void readStdOut();

		void readStdErr();

		void readStream(StreamReader *sr, ManualResetEvent *rEvent, StreamType str);

		void ProcessLine(const std::string &line, StreamType stream, ImageType oType);

		void encode();

		void deleteOutputFile();

		void createEncoderProcess(AviSynthClip *a);

		void writeHeader(Stream *target, AviSynthClip *a);

	public:
		void Start();

		void Abort();

	private:
		bool OpenSourceWithFFAudioSource(StringBuilder *&sbOpen);

		bool OpenSourceWithBassAudio(StringBuilder *&sbOpen);

		bool OpenSourceWithDirectShow(StringBuilder *&sbOpen, MediaInfoFile *oInfo);

		bool OpenSourceWithImportAVS(StringBuilder *&sbOpen, MediaInfoFile *oInfo);

		bool OpenSourceWithNicAudio(StringBuilder *&sbOpen, MediaInfoFile *oInfo, bool bForce);




	public:
		void setup(Job *job, StatusUpdate *su, LogItem *log);

	private:
		void createAviSynthScript();

	public:
		void start();

		void stop();

		void pause();

		void resume();

		void changePriority(ProcessPriority priority);

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event JobProcessingStatusUpdateCallback StatusUpdate;

	private:
		void InitializeInstanceFields();
	};
}
