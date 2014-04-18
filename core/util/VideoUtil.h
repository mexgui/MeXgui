#pragma once

#include "core/gui/MeXgui.MainForm.h"
#include "JobUtil.h"
#include "packages/tools/chaptercreator/ChapterInfo.h"
#include "packages/tools/chaptercreator/IfoExtractor.h"
#include "Drives.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/details/AudioTrackInfo.h"
#include "LogItem.h"
#include "core/details/CodecManager.h"
#include "packages/audio/AudioJob.h"
#include "packages/tools/avscreator/AvisynthWrapper.h"
#include "core/details/video/VideoCodecSettings.h"
#include "core/details/Streams.h"
#include "core/plugins/interfaces/IMuxing.h"
#include "FileSize.h"
#include "packages/tools/oneclick/OneClickAudioTrack.h"
#include "core/details/MeXgui.JobChain.h"
#include "core/details/mux/MuxProvider.h"
#include "BitrateCalculatorPreProcessor.h"
#include "core/details/TaggedJob.h"
#include "core/details/video/VideoJob.h"
#include "core/plugins/interfaces/Job.h"
#include "core/details/MeXgui.SequentialChain.h"
#include "MeXgui.Properties.Settings.h"
#include "core/details/mux/MuxPath.h"
#include "GenericRegisterer.h"
#include "packages/tools/chaptercreator/ChapterCreator.h"
#include "Util.h"
#include "FileUtil.h"
#include <QString>
#include <QMap>
#include <QVector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "stringconverter.h"

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




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;



using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{
	/// <summary>
	/// VideoUtil is used to perform various video related tasks, namely autocropping, 
	/// auto resizing
	/// </summary>
	class VideoUtil
	{

	private:
		MainForm *mainForm;
		JobUtil *jobUtil;
	public:
		VideoUtil(MainForm *mainForm);


		/// <summary>
		/// gets the dvd decrypter generated chapter file
		/// </summary>
		/// <param name="fileName">name of the first vob to be loaded</param>
		/// <returns>full name of the chapter file or an empty string if no file was found</returns>
		static QString getChapterFile(const QString &fileName);

		/// <summary>
		/// gets chapters from IFO file and save them as Ogg Text File
		/// </summary>
		/// <param name="fileName"></param>
		/// <returns>chapter file name</returns>
		static QString getChaptersFromIFO(const QString &fileName, bool qpfile, const QString &outputDirectory, int iPGCNumber);

		/// <summary>
		/// checks if the input file has chapters
		/// </summary>
		/// <param name="fileName"></param>
		/// <returns>true if the file has chapters</returns>
		static bool HasChapters(MediaInfoFile *iFile);

		/// <summary>
		/// gets Timeline from Chapters Text file (formally as Ogg Format)
		/// </summary>
		/// <param name="fileName">the file read</param>
		/// <returns>chapters Timeline as string</returns>
		static QString getChapterTimeLine(const QString &fileName);

		static QVector<QString> setDeviceTypes(const QString &outputFormat);


		/// <summary>
		/// gets all demuxed audio files from a given dgindex project
		/// starts with the first file and returns the desired number of files
		/// </summary>
		/// <param name="audioTrackIDs">list of audio TrackIDs</param>
		/// <param name="projectName">the name of the dgindex project</param>
		/// <returns>an array of string of filenames</returns>
		QMap<int, QString> getAllDemuxedAudio(QVector<AudioTrackInfo*> &audioTracks, QVector<AudioTrackInfo*> &audioTracksDemux, QVector<QString> &arrDeleteFiles, const QString &projectName, LogItem *log);


		/// <summary>
		/// ensures that video and audio don't have the same filenames which would lead to severe problems
		/// </summary>
		/// <param name="videoOutput">name of the encoded video file</param>
		/// <param name="muxedOutput">name of the final output</param>
		/// <param name="aStreams">all encodable audio streams</param>
		/// <param name="audio">all muxable audio streams</param>
		/// <returns>the info to be added to the log</returns>
		LogItem *eliminatedDuplicateFilenames(QString &videoOutput, QString &muxedOutput, AudioJob aStreams[]);

		QString checkVideo(const QString &avsFile);

	private:
		QString checkVideo(const QString &avsFile, bool tryToFix);

		bool appendConvertToYV12(const QString &file);

		bool isConvertedToYV12(const QString &file);

		typedef VideoCodecSettings *(*CurrentSettingsDelegate)();
		VideoCodecSettings *GetCurrentVideoSettings();

	public:
		JobChain *GenerateJobSeries(VideoStream *video, const QString &muxedOutput, AudioJob audioStreams[], MuxStream subtitles[], const QString &chapters, Nullable<FileSize> desiredSize, Nullable<FileSize> splitSize, ContainerType *container, bool prerender, MuxStream muxOnlyAudio[], LogItem *log, const QString &deviceType, Zone zones[], const QString &videoFileToMux, OneClickAudioTrack audioTracks[], bool alwaysMuxOutput);

	private:
		void fixFileNameExtensions(VideoStream *video, AudioJob audioStreams[], ContainerType *container);

	public:
		static SubtitleType *guessSubtitleType(const QString &p);

		static VideoType *guessVideoType(const QString &p);

		static AudioType *guessAudioType(const QString &p);

		static ChapterType *guessChapterType(const QString &p);

		static DeviceType *guessDeviceType(const QString &p);

		static MuxableType *guessVideoMuxableType(const QString &p, bool useMediaInfo);

		static MuxableType *guessAudioMuxableType(const QString &p, bool useMediaInfo);

		static QString convertChaptersTextFileTox264QPFile(const QString &filename, double framerate);

		static QString GenerateCombinedFilter(OutputFileType types[]);

		static void getAvisynthVersion(LogItem *i);

		static QString getFFMSInputLine(const QString &inputFile, const QString &indexFile, double fps);

	private:
		static QString getFFMSBasicInputLine(const QString &inputFile, const QString &indexFile, int rffmode, int fpsnum, int fpsden);

	public:
		static QString getAssumeFPS(double fps, const QString &strInput);

	private:
		static bool getFPSFraction(double fps, const QString &strInput, int &fpsnum, int &fpsden);

	public:
		static double GetFPSFromAVSFile(const QString &strAVSScript);
	};
	/// <summary>
	/// helper structure for cropping
	/// holds the crop values for all 4 edges of a frame
	/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[LogByMembers]
	class CropValues
	{
	public:
		int left, top, right, bottom;
		CropValues *Clone();
		bool isCropped();
	};

	class SubtitleInfo
	{
	private:
		QString name;
		int index;
	public:
		SubtitleInfo(const QString &name, int index);
		const QString &getName() const;
		void setName(const QString &value);
		const int &getIndex() const;
		void setIndex(const int &value);
		virtual QString ToString();
	};
}
