#pragma once

#include "core/util/GenericRegisterer.h"
#include "core/details/CodecManager.h"
#include "core/details/mux/MuxProvider.h"
#include "core/details/MeXguiSettings.h"
#include "IJobProcessor.h"
#include "core/util/DAR.h"
#include "core/details/video/VideoCodecSettings.h"
#include "MeXgui.Properties.Settings.h"
#include <QString>

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
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
	enum ProcessingLevel
	{
		NONE,
		SOME,
		ALL
	};
	/// <summary>
	/// interface for muxer providers
	/// this interface offers a number of methods used to find out if a muxjob can be processed
	/// and how it can be processed
	/// </summary>
	class IMuxing : public IIDable
	{
	public:
		virtual bool SupportsVideoCodec(VideoCodec*) = 0;
		virtual bool SupportsAudioCodec(AudioCodec*) = 0;
		virtual QVector<VideoType*> GetSupportedVideoTypes() = 0;
		virtual QVector<VideoCodec*> GetSupportedVideoCodecs() = 0;
		virtual QVector<AudioCodec*> GetSupportedAudioCodecs() = 0;
		virtual QVector<AudioType*> GetSupportedAudioTypes() = 0;
		virtual QVector<SubtitleType*> GetSupportedSubtitleTypes() = 0;
		virtual QVector<ChapterType*> GetSupportedChapterTypes() = 0;
		virtual QVector<DeviceType*> GetSupportedDeviceTypes() = 0;
		virtual QVector<ContainerType*> GetSupportedContainers() = 0;
		virtual QVector<ContainerType*> GetSupportedContainerTypes() = 0;
		virtual QVector<ContainerType*> GetSupportedContainerInputTypes() = 0;
		/// <summary>
		/// checks all the given input stream types if they can be handled by this muxer
		/// </summary>
		/// <param name="inputTypes">all input stream types</param>
		/// <param name="handledInputTypes">input stream types this muxer can handle</param>
		/// <param name="unhandledInputTypes">input stream types this muxer cannot handle</param>
		/// <returns>ProcessingLevel indicating how much can be processed</returns>
		virtual ProcessingLevel CanBeProcessed(MuxableType[] , QVector<MuxableType*>&, QVector<MuxableType*>&) = 0;
		/// <summary>
		/// checks if the given input stream types and container input type can be handled by this muxer
		/// </summary>
		/// <param name="inputTypes">all input stream types</param>
		/// <param name="handledInputTypes">input stream types this muxer can handle</param>
		/// <param name="unhandledInputTypes">input stream types this muxer cannot handle</param>
		/// <returns>ProcessingLevel indicating how much can be processed</returns>
		virtual ProcessingLevel CanBeProcessed(ContainerType[] , MuxableType[] , QVector<MuxableType*>&, QVector<MuxableType*>&) = 0;
		virtual const MuxerType &getMuxerType() const = 0;
		virtual IJobProcessor *GetMuxer(MeXguiSettings*) = 0;
		virtual QString GetOutputTypeFilter(ContainerType*) = 0;
		virtual QString GetVideoInputFilter() = 0;
		virtual QString GetAudioInputFilter() = 0;
		virtual QString GetSubtitleInputFilter() = 0;
		virtual QString GetChapterInputFilter() = 0;
		virtual QString GetOutputTypeFilter() = 0;
		virtual QString GetMuxedInputFilter() = 0;
		virtual QString GetDeviceInputFilter() = 0;
		virtual const QString &getName() const = 0;
		virtual const System::Windows::Forms::Shortcut &getShortcut() const = 0;
		virtual QVector<ContainerType*> GetContainersInCommon(IMuxing*) = 0;
	};
//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
	template<typename TCodec, typename TType, typename TEncoderType> where TType : OutputType
	class IEncoding
	{
	public:
		virtual QVector<TEncoderType*> GetSupportedEncoderTypes() = 0;
		virtual QVector<TCodec*> GetSupportedCodecs() = 0;
		virtual QVector<TType*> GetSupportedOutputTypes(TEncoderType*) = 0;
		virtual IJobProcessor *GetEncoder(TEncoderType*, TType*, MeXguiSettings*) = 0;
		virtual QString GetOutputTypeFilter(TEncoderType*, TType*) = 0;
		virtual QString GetInputTypeFilter() = 0;
	};

	class VideoStream
	{
	private:
		QString input, output;
		quint64 numberOfFrames;
		Nullable<Dar> dar;
		decimal framerate;
		MuxableType *videoType;
		VideoCodecSettings *settings;
	public:
		VideoStream();
	  const QString &getOutput() const;
	  void setOutput(const QString &value);
	  const QString &getInput() const;
	  void setInput(const QString &value);
		const Nullable<Dar> &getDAR() const;
		void setDAR(const Nullable<Dar> &value);
	  const quint64 &getNumberOfFrames() const;
	  void setNumberOfFrames(const quint64 &value);
	  const decimal &getFramerate() const;
	  void setFramerate(const decimal &value);
		const MuxableType &getVideoType() const;
		void setVideoType(const MuxableType &value);
		const VideoCodecSettings &getSettings() const;
		void setSettings(const VideoCodecSettings &value);

	private:
		void InitializeInstanceFields();
	};
}
