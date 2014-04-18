#pragma once

#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MeGUI.MainForm.h"
#include "OneClickPostProcessingJob.h"
#include "core/gui/SourceDetector.h"
#include "core/details/StatusUpdate.h"
#include "core/util/LogItem.h"
#include "core/util/VideoUtil.h"
#include "packages/tools/avclevelschecker/AVCLevels.h"
#include "core/util/DeinterlaceFilter.h"
#include "core/util/Util.h"
#include "core/details/AudioTrackInfo.h"
#include "packages/audio/AudioJob.h"
#include "core/details/Streams.h"
#include "core/util/FileUtil.h"
#include "OneClickAudioTrack.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "packages/tools/fileindexer/MeGUI.FileIndexerWindow.h"
#include "core/details/CodecManager.h"
#include "core/plugins/interfaces/IMuxing.h"
#include "core/details/video/VideoCodecSettings.h"
#include "core/util/DAR.h"
#include "core/util/JobUtil.h"
#include "core/details/mux/MuxProvider.h"
#include "OneClickStream.h"
#include "core/details/MeGUI.core.details.JobChain.h"
#include "core/details/CleanupJob.h"
#include "MeGUI.OneClickWindow.h"
#include "core/util/PrettyFormatting.h"
#include "packages/tools/avscreator/AviSynthSettings.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include "packages/tools/avscreator/AviSynthWindow.h"
#include "packages/video/x264/x264Device.h"
#include "packages/reader/dgi/dgiReader.h"
#include "packages/reader/d2v/d2vReader.h"
#include "packages/reader/dga/dgaReader.h"
#include "packages/reader/ffms/ffmsReader.h"
#include "packages/reader/avs/AvsReader.h"
#include "packages/video/x264/x264Settings.h"
#include "core/util/Resolution.h"
#include "core/util/Autocrop.h"
#include "packages/tools/avscreator/ScriptServer.h"
#include "core/util/Exceptions.h"
#include <string>
#include <map>
#include <vector>
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
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;

using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{
	class OneClickPostProcessing : public IJobProcessor
	{
	public:
		static JobProcessorFactory *const Factory;

	private:
		static IJobProcessor *init(MainForm *mf, Job *j);

		Thread *_processThread;
		Thread *_processTime;
		SourceDetector *_sourceDetector;
		DateTime _start;
		StatusUpdate *su;
		OneClickPostProcessingJob *job;
		LogItem *_log;

		MainForm *mainForm;
		std::map<int, std::string> audioFiles;
		VideoUtil *vUtil;
		AVCLevels *al;
		bool finished;
		bool interlaced;
//ORIGINAL LINE: private DeinterlaceFilter[] filters;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		DeinterlaceFilter *filters;
		std::string qpfile;

	public:
		OneClickPostProcessing(MainForm *mf);


		void Start();

		void Abort();

	private:
		static void safeDelete(const std::string &filePath);

		void raiseEvent();

		void setProgress(decimal n);

		void updateTime();

		void raiseEvent(const std::string &s);


		void StartPostProcessing();

		void fillInAudioInformation(std::vector<AudioJob*> &arrAudioJobs, std::vector<MuxStream*> &arrMuxStreams);

		/// <summary>
		/// if input is a track number (of the form, "::&lt;number&gt;::")
		/// then it returns the file path of that track number. Otherwise,
		/// it returns the string only
		/// </summary>
		/// <param name="input"></param>
		/// <returns></returns>
		std::string convertTrackNumberToFile(const std::string &input, int &delay);

		/// <summary>
		/// creates the AVS Script file
		/// if the file can be properly opened, auto-cropping is performed, then depending on the AR settings
		/// the proper resolution for automatic resizing, taking into account the derived cropping values
		/// is calculated, and finally the avisynth script is written and its name returned
		/// </summary>
		/// <param name="path">dgindex script</param>
		/// <param name="aspectRatio">aspect ratio selection to be used</param>
		/// <param name="customDAR">custom display aspect ratio for this source</param>
		/// <param name="desiredOutputWidth">desired horizontal resolution of the output</param>
		/// <param name="settings">the codec settings (used only for x264)</param>
		/// <param name="sarX">pixel aspect ratio X</param>
		/// <param name="sarY">pixel aspect ratio Y</param>
		/// <param name="height">the final height of the video</param>
		/// <param name="signalAR">whether or not ar signalling is to be used for the output 
		/// (depending on this parameter, resizing changes to match the source AR)</param>
		/// <param name="autoCrop">whether or not autoCrop is used for the input</param>
		/// <returns>the name of the AviSynth script created, empty if there was an error</returns>
		std::string createAVSFile(const std::string &indexFile, const std::string &inputFile, Nullable<Dar> AR, int desiredOutputWidth, bool signalAR, LogItem *_log, AviSynthSettings *avsSettings, bool autoDeint, VideoCodecSettings *settings, Nullable<Dar> &dar, bool autoCrop, bool keepInputResolution, bool useChaptersMarks);

	public:
		void finishedAnalysis(SourceInfo *info, bool error, const std::string &errorMessage);

		void analyseUpdate(int amountDone, int total);

	private:
		void waitTillAnalyseFinished();



	public:
		void setup(Job *job, StatusUpdate *su, LogItem *_log);

		void resume();

		void pause();

		void start();

		void stop();

		void changePriority(ProcessPriority priority);

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event JobProcessingStatusUpdateCallback StatusUpdate;

	private:
		void InitializeInstanceFields();
	};
}
