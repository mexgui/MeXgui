#pragma once

#include "core/gui/MeGUI.MainForm.h"
#include "core/details/video/VideoCodecSettings.h"
#include "core/details/video/VideoJob.h"
#include "DAR.h"
#include "core/details/CodecManager.h"
#include "core/details/Streams.h"
#include "core/details/mux/MuxProvider.h"
#include "core/plugins/interfaces/IMuxing.h"
#include "FileSize.h"
#include "core/details/MeGUI.core.details.JobChain.h"
#include "core/details/mux/MuxPath.h"
#include "core/details/mux/MuxJob.h"
#include "VideoUtil.h"
#include "core/details/MeGUI.core.details.SequentialChain.h"
#include "packages/tools/fileindexer/FFMSIndexJob.h"
#include "packages/video/huffyuv/hfyuSettings.h"
#include "core/plugins/interfaces/Job.h"
#include "Exceptions.h"
#include "packages/video/xvid/xvidSettings.h"
#include <string>
#include <vector>
#include <algorithm>
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
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{
	/// <summary>
	/// JobUtil is used to perform various job related tasks like loading/saving jobs, 
	/// generating all types of jobs, update bitrates in jobs, and get the properties
	/// of a video input file
	/// </summary>
	class JobUtil
	{

	private:
		MainForm *mainForm;
		std::string mbtreeFile;

	public:
		JobUtil(MainForm *mainForm);


		VideoJob *generateVideoJob(const std::string &input, const std::string &output, VideoCodecSettings *settings, Nullable<Dar> dar, Zone zones[]);

		/// <summary>
		/// generates a videojob from the given settings
		/// returns the job and whether or not this is an automated job (in which case another job
		/// will have to be created)
		/// </summary>
		/// <param name="input">the video input (avisynth script)</param>
		/// <param name="output">the video output</param>
		/// <param name="settings">the codec settings for this job</param>
		/// <returns>the generated job or null if there was an error with the video source</returns>
		VideoJob *generateVideoJob(const std::string &input, const std::string &output, VideoCodecSettings *settings, bool skipVideoCheck, Nullable<Dar> dar, Zone zones[]);

	private:
		void checkVideo(const std::string &p);
		/// <summary>
		/// sets the number of encoder threads in function of the number of processors found on the system
		/// </summary>
		/// <param name="settings"></param>
		void adjustNbThreads(VideoCodecSettings *settings);

	public:
		JobChain *GenerateMuxJobs(VideoStream *video, Nullable<decimal> framerate, MuxStream audioStreamsArray[], MuxableType audioTypes[], MuxStream subtitleStreamsArray[], MuxableType subTypes[], const std::string &chapterFile, MuxableType *chapterInputType, ContainerType *container, const std::string &output, Nullable<FileSize> splitSize, std::vector<std::string> &inputsToDelete, const std::string &deviceType, MuxableType *deviceOutputType, bool alwaysMuxOutput);

		JobChain *AddVideoJobs(const std::string &movieInput, const std::string &movieOutput, VideoCodecSettings *settings, int introEndFrame, int creditsStartFrame, Nullable<Dar> dar, bool prerender, bool checkVideo, Zone zones[]);

		/// <summary>
		/// at first, the job from the currently configured settings is generated. In addition, we find out if this job is 
		/// a part of an automated series of jobs. If so, it means the first generated job was the second pass, and we have
		/// to create the first pass using the same settings
		/// then, all the generated jobs are returned
		/// </summary>
		/// <returns>an Array of VideoJobs in the order they are to be encoded</returns>
		JobChain *prepareVideoJob(const std::string &movieInput, const std::string &movieOutput, VideoCodecSettings *settings, Nullable<Dar> dar, bool prerender, bool checkVideo, Zone zones[]);
		/// <summary>
		/// creates a copy of the most important parameters of a job
		/// </summary>
		/// <param name="oldJob">the job to be cloned</param>
		/// <returns>the cloned job</returns>
	private:
		VideoJob *cloneJob(VideoJob *oldJob);
		/// <summary>
		/// updates the video bitrate of a video job with the given bitrate
		/// in addition, the commandline is regenerated to reflect the bitrate change
		/// </summary>
		/// <param name="job">the job whose video bitrate is to be updated</param>
		/// <param name="bitrate">the new desired video bitrate</param>
	public:
		void updateVideoBitrate(VideoJob *job, int bitrate);
		/// <summary>
		/// gets the number of frames and framerate from an avisynth script
		/// </summary>
		/// <param name="nbOfFrames">number of frames of the source</param>
		/// <param name="framerate">framerate of the source</param>
		/// <param name="video">path of the source</param>
		/// <returns>true if the input file could be opened, false if not</returns>
		static bool getInputProperties(unsigned long long &nbOfFrames, double &framerate, const std::string &video);
		/// <summary>
		/// gets the number of frames, framerate, horizontal and vertical resolution from a video source
		/// </summary>
		/// <param name="nbOfFrames">the number of frames</param>
		/// <param name="framerate">the framerate</param>
		/// <param name="hRes">the horizontal resolution</param>
		/// <param name="vRes">the vertical resolution</param>
		/// <param name="video">the video whose properties are to be read</param>
		/// <returns>whether the source could be opened or not</returns>
		static bool GetAllInputProperties(unsigned long long &nbOfFrames, double &framerate, int &framerate_n, int &framerate_d, int &hRes, int &vRes, Dar &dar, const std::string &video);

		  /// <summary>
		/// gets the number of frames, framerate, horizontal and vertical resolution from a video source
		/// </summary>
		/// <param name="nbOfFrames">the number of frames</param>
		/// <param name="framerate">the framerate</param>
		/// <param name="hRes">the horizontal resolution</param>
		/// <param name="vRes">the vertical resolution</param>
		/// <param name="video">the video whose properties are to be read</param>
		/// <returns>whether the source could be opened or not</returns>
		static bool GetAllInputProperties(unsigned long long &nbOfFrames, double &framerate, int &hRes, int &vRes, Dar &dar, const std::string &video);

		/// <summary>
		/// gets the number of frames of a videostream
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		unsigned long long getNumberOfFrames(const std::string &path);

		/// <summary>
		/// gets the framerate of a video stream
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		double getFramerate(const std::string &path);
		/// <summary>
		/// takes a series of non overlapping zones and adds zones with weight 1.0 in between
		/// this is used for xvid which doesn't know zone end frames
		/// </summary>
		/// <param name="zones">a set of zones to be analyzed</param>
		/// <param name="nbOfFrames">number of frames the video source has</param>
		/// <returns>an array of all the zones</returns>
		Zone *createHelperZones(Zone zones[], int nbOfFrames);
		/// <summary>
		/// compiles the final zone configuration based on intro end frame, credits start frame and the configured zones
		/// </summary>
		/// <param name="vSettings">the video settings containing the list of configured zones</param>
		/// <param name="introEndFrame">the frame where the intro ends</param>
		/// <param name="creditsStartFrame">the frame where the credits begin</param>
		/// <param name="newZones">the zones that are returned</param>
		/// <returns>an array of zones objects in the proper order</returns>
		bool getFinalZoneConfiguration(VideoCodecSettings *vSettings, int introEndFrame, int creditsStartFrame, Zone zones[]);

	private:
		void InitializeInstanceFields();
	};
}
