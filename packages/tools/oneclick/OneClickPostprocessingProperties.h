#pragma once

#include "core/util/FileSize.h"
#include "core/details/CodecManager.h"
#include "core/util/DAR.h"
#include "core/details/video/VideoCodecSettings.h"
#include "packages/tools/avscreator/AviSynthSettings.h"
#include "OneClickAudioTrack.h"
#include "OneClickStream.h"
#include "packages/tools/fileindexer/FileIndexerWindow.h"
#include "OneClickSettings.h"
#include "OneClickWindow.h"
#include "core/gui/MainForm.h"
#include <QString>
#include <QVector>

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

//using namespace System::Xml::Serialization;

using namespace MeXgui::core::util;

namespace MeXgui
{
	/// <summary>
	/// Summary description for OneClickPostprocessingProperties.
	/// </summary>
	class OneClickPostprocessingProperties
	{
	private:
		bool signalAR, autoDeint, autoCrop, keepInputResolution, prerenderJob, useChapterMarks, chapterExtracted, eac3toDemux, applyDelayCorrection;
		int horizontalOutputResolution, _titleNumberToProcess;
		Nullable<FileSize> splitSize;
		ContainerType *container;
		Nullable<FileSize> outputSize;
		Nullable<Dar> ar;
		VideoCodecSettings *videoSettings;
		AviSynthSettings *avsSettings;
		double customAR;
		QString chapterFile, finalOutput, aviSynthScript, deviceType, inputFile, workingDirectory, _videoFileToMux, ifoFile;
		QVector<QString> filesToDelete;
		QVector<OneClickAudioTrack*> _audioTracks;
		QVector<OneClickStream*> _subtitleTrack;
		FileIndexerWindow::IndexType _indexType;
		OneClickSettings *_oneClickSettings;
		QVector<OneClickFilesToProcess*> _filesToProcess;

	public:
		OneClickPostprocessingProperties();

		const bool &getAutoDeinterlace() const;
		void setAutoDeinterlace(const bool &value);

		/// <summary>
		/// gets / sets whether the chapter file has been created automatically
		/// </summary>
		const bool &getChapterExtracted() const;
		void setChapterExtracted(const bool &value);

		/// <summary>
		/// gets / sets whether the aspect ratio should be signalled in the output and thus
		/// resizing should not unstretch anamorphically stretched content
		/// </summary>
		const bool &getSignalAR() const;
		void setSignalAR(const bool &value);

		/// <summary>
		/// gets / sets the AutoCrop function
		/// </summary>
		const bool &getAutoCrop() const;
		void setAutoCrop(const bool &value);

		/// <summary>
		/// gets / sets Keep Input Resolution
		/// </summary>
		const bool &getKeepInputResolution() const;
		void setKeepInputResolution(const bool &value);

		/// <summary>
		/// gets / sets Prerender Job
		/// </summary>
		const bool &getPrerenderJob() const;
		void setPrerenderJob(const bool &value);

		/// <summary>
		/// gets / sets the horizontal output resolution the output should have
		/// </summary>
		const int &getHorizontalOutputResolution() const;
		void setHorizontalOutputResolution(const int &value);

		/// <summary>
		/// gets / sets the container of the output
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const ContainerType &getContainer() const;
		void setContainer(const ContainerType &value);

		const QString &getContainerTypeString() const;
		void setContainerTypeString(const QString &value);

		/// <summary>
		/// gets / sets the output size
		/// </summary>
		const Nullable<FileSize> &getOutputSize() const;
		void setOutputSize(const Nullable<FileSize> &value);

		/// <summary>
		/// gets / sets the split size for the output
		/// </summary>
		const Nullable<FileSize> &getSplitting() const;
		void setSplitting(const Nullable<FileSize> &value);

		/// <summary>
		/// gets / sets the aspect ratio of the video input (if known)
		/// </summary>
		const Nullable<Dar> &getDAR() const;
		void setDAR(const Nullable<Dar> &value);

		const AviSynthSettings &getAvsSettings() const;
		void setAvsSettings(const AviSynthSettings &value);

		/// <summary>
		/// gets / sets the video codec settings used for video encoding
		/// </summary>
		const VideoCodecSettings &getVideoSettings() const;
		void setVideoSettings(const VideoCodecSettings &value);

		/// <summary>
		/// gets / sets a custom aspect ratio for the input
		/// (requires AR set to AspectRatio.Custom to be taken into account)
		/// </summary>
		const double &getCustomAR() const;
		void setCustomAR(const double &value);

		/// <summary>
		/// gets / sets the chapter file for the output
		/// </summary>
		const QString &getChapterFile() const;
		void setChapterFile(const QString &value);

		/// <summary>
		/// gets / sets the path and name of the final output file
		/// </summary>
		const QString &getFinalOutput() const;
		void setFinalOutput(const QString &value);

		/// <summary>
		/// gets / sets the path and name of the video input file
		/// </summary>
		const QString &getVideoInput() const;
		void setVideoInput(const QString &value);

		/// <summary>
		/// gets / sets the path and name of the video input file
		/// </summary>
		const QString &getIFOInput() const;
		void setIFOInput(const QString &value);

		/// <summary>
		/// gets / sets the working directory
		/// </summary>
		const QString &getWorkingDirectory() const;
		void setWorkingDirectory(const QString &value);

		/// <summary>
		/// gets / sets the path and name of the AviSynth script created from the dgindex project
		/// this is filled in during postprocessing
		/// </summary>
		const QString &getAviSynthScript() const;
		void setAviSynthScript(const QString &value);

		/// <summary>
		/// gets / sets the device output type
		/// </summary>
		const QString &getDeviceOutputType() const;
		void setDeviceOutputType(const QString &value);

		const bool &getUseChaptersMarks() const;
		void setUseChaptersMarks(const bool &value);

		/// <summary>
		/// gets / sets if the input is demuxed with eac3to
		/// </summary>
		const bool &getEac3toDemux() const;
		void setEac3toDemux(const bool &value);

		/// <summary>
		/// gets / sets if a delay correction must be applied
		/// </summary>
		const bool &getApplyDelayCorrection() const;
		void setApplyDelayCorrection(const bool &value);

		const QVector<QString> &getFilesToDelete() const;
		void setFilesToDelete(const QVector<QString> &value);

		const QVector<OneClickAudioTrack*> &getAudioTracks() const;
		void setAudioTracks(const QVector<OneClickAudioTrack*> &value);

		const QVector<OneClickStream*> &getSubtitleTracks() const;
		void setSubtitleTracks(const QVector<OneClickStream*> &value);

		/// <summary>
		/// gets / sets the video file for mux only
		/// </summary>
		const QString &getVideoFileToMux() const;
		void setVideoFileToMux(const QString &value);

		/// <summary>
		/// gets / sets the file index type
		/// </summary>
		const FileIndexerWindow::IndexType &getIndexType() const;
		void setIndexType(const FileIndexerWindow::IndexType &value);

		/// <summary>
		/// gets / sets files which need to be processed
		/// </summary>
		const QVector<OneClickFilesToProcess*> &getFilesToProcess() const;
		void setFilesToProcess(const QVector<OneClickFilesToProcess*> &value);

		/// <summary>
		/// gets / sets settings for the FilesToProcess
		/// </summary>
		const OneClickSettings &getOneClickSetting() const;
		void setOneClickSetting(const OneClickSettings &value);

		/// <summary>
		/// gets / sets settings for the TitleNumberToProcess
		/// </summary>
		const int &getTitleNumberToProcess() const;
		void setTitleNumberToProcess(const int &value);
	};
}
