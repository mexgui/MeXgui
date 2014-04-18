#pragma once

#include "core/details/CodecManager.h"
#include "core/details/TrackInfo.h"
#include "packages/tools/chaptercreator/ChapterCreator.h"
#include "core/util/DAR.h"
#include "core/gui/FPSChooser.h"
#include "core/util/GenericRegisterer.h"
#include "ISettingsProvider.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include <QVector>

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

//using namespace System::Diagnostics;



//using namespace System::Text;

using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{
	class MediaFile
	{
	public:
		ContainerType *Container;

		QVector<MediaTrack*> Tracks;

//C# TO C++ CONVERTER NOTE: The variable VideoTrack was renamed since it is named the same as a user-defined type:
		VideoTrack *VideoTrack_Renamed;
		QVector<AudioTrack*> AudioTracks;
		QVector<SubtitleTrack*> SubtitleTracks;
//C# TO C++ CONVERTER NOTE: The variable Chapters was renamed since it is named the same as a user-defined type:
		Chapters *Chapters_Renamed;

		TimeSpan *PlayTime;

		MediaFile(QVector<MediaTrack*> &tracks, Chapters *chapters, TimeSpan *playTime, ContainerType *container);
	};

	class MediaTrack
	{
	public:
		TrackInfo *Info;
		unsigned int TrackNumber;
		ICodec *Codec;
	};

	class VideoTrack : public MediaTrack
	{
	public:
		VideoCodec *VCodec;
		VideoInfo2 *StreamInfo;
	};

	class AudioTrack : public MediaTrack
	{
	public:
		AudioCodec *ACodec;
		AudioInfo *StreamInfo;
	};

	class SubtitleTrack : public MediaTrack
	{
	public:
		SubtitleCodec *SCodec;
		SubtitleInfo2 *StreamInfo;
	};

	class Chapters
	{
	public:
		QVector<Chapter> Data;
	};


	class VideoInfo2
	{
	public:
		quint64 Width;
		quint64 Height;
		Dar DAR;
		quint64 FrameCount;
		double FPS;

		VideoInfo2();

		VideoInfo2(quint64 width, quint64 height, Dar dar, quint64 framecount, double fps);
	};

	class AudioInfo
	{
	};

	class SubtitleInfo2
	{
	};

	class IMediaFileFactory : public IIDable
	{
		/// <summary>
		/// Tries to open the given file. Returns null if impossible.
		/// </summary>
		/// <param name="file">The media file to open</param>
		/// <returns></returns>
	public:
		virtual IMediaFile *Open(const QString&) = 0;
		/// <summary>
		/// Returns how well a given file is expected to be handled. This is so that better handlers
		/// can be given preference. This should be implemented only by filename and not by opening the file.
		/// </summary>
		/// <param name="extension">The filename to be checked.</param>
		/// <returns>Higher number for better handling, negative for impossible.</returns>
		virtual int HandleLevel(const QString&) = 0;
	};

	class IMediaFile : public IDisposable
	{
	public:
		virtual const VideoInformation &getVideoInfo() const = 0;

		virtual const bool &getCanReadVideo() const = 0;

		virtual const bool &getCanReadAudio() const = 0;

		virtual IVideoReader *GetVideoReader() = 0;
		virtual IAudioReader *GetAudioReader(int) = 0;
	};

	class IAudioReader
	{
		/// <summary>
		/// Returns the number of samples readable.
		/// </summary>
	public:
		virtual const qint64 &getSampleCount() const = 0;

		/// <summary>
		/// Gets whether ReadAudioSamples(long, int, IntPtr) is a supported operation.
		/// </summary>
		virtual const bool &getSupportsFastReading() const = 0;

		/// <summary>
		/// Reads up to nAmount samples into an array at buf. Fast method because it avoids the Marshaller.
		/// This needn't be supported; the SupportsFastReading property indicates whether it is.
		/// </summary>
		/// <param name="nStart">the index of the first sample</param>
		/// <param name="nAmount">the maximum number of samples to read</param>
		/// <param name="buf">a pointer to the memory for the samples</param>
		/// <returns>the number of samples read</returns>
		virtual qint64 ReadAudioSamples(qint64, int, IntPtr) = 0;

		/// <summary>
		/// Reads up to nAmount samples into an array and returns it. Slow method because of Marshaller.
		/// This must be supported.
		/// </summary>
		/// <param name="nStart">the index of the first sample</param>
		/// <param name="nAmount">the maximum number of samples to read</param>
		/// <returns>a newly-constructed array of samples</returns>
		virtual unsigned char *ReadAudioSamples(qint64, int) = 0;
	};
	/// <summary>
	/// The interface for sourcing frames
	/// </summary>
	class IVideoReader
	{
		/// <summary>
		/// Returns the number of frames readable.
		/// </summary>
	public:
		virtual const int &getFrameCount() const = 0;

		/// <summary>
		/// Reads and returns frame 'framenumber' from the video stream. Slow method, because of Marshaller.
		/// This must be supported
		/// </summary>
		/// <param name="framenumber">the 0-indexed frame number to get</param>
		/// <returns>The frame just read</returns>
		virtual BitQMap *ReadFrameBitQMap(int) = 0;
	};
}
