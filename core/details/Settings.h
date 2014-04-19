#pragma once

#include "core/gui/SourceDetectorSettings.h"
#include "packages/tools/autoencode/AutoEncodeDefaultsSettings.h"
#include "DialogSettings.h"
#include "core/plugins/interfaces/Job.h"
#include "core/util/FileSize.h"
#include "core/gui/FPSChooser.h"
#include "core/util/DAR.h"
#include "core/util/OSInfo.h"
#include "core/gui/MainForm.h"
#include <QString>

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
using namespace MeXgui::core::gui;

namespace MeXgui
{
	/// <summary>
	/// Summary description for MeXguiSettings.
	/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[LogByMembers]
	class MeXguiSettings
	{
	public:
		enum OCGUIMode
		{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Show Basic Settings")]
			Basic,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Show Default Settings")]
			Default,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Show Advanced Settings")]
			Advanced
		};
	private:
//ORIGINAL LINE: private string[][] autoUpdateServerLists;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		QString **autoUpdateServerLists;
		DateTime lastUpdateCheck;
		QString qaacPath, opusPath, lamePath, neroAacEncPath, mp4boxPath, mkvmergePath, strMainAudioFormat, ffmpegPath, besplitPath, yadifPath, aftenPath, x264Path, strMainFileFormat, bassPath, dgIndexPath, xvidEncrawPath, aviMuxGUIPath, oggEnc2Path, dgavcIndexPath, aviSynthPath, eac3toPath, tsmuxerPath, MeXguiupdatecache, avisynthpluginspath, ffmsIndexPath, vobSubPath, defaultLanguage1, defaultLanguage2, afterEncodingCommand, videoExtension, audioExtension, strLastDestinationPath, strLastSourcePath, dgnvIndexPath, tempDirMP4, flacPath, httpproxyaddress, httpproxyport, httpproxyuid, httpproxypwd, defaultOutputDir, strMeXguiPath, mkvExtractPath, appendToForcedStreams, pgcDemuxPath, lastUsedOneClickFolder, lastUpdateServer, x26410BitsPath;
		bool recalculateMainMovieBitrate, autoForceFilm, autoStartQueue, enableMP3inMP4, autoOpenScript, overwriteStats, keep2of3passOutput, autoUpdate, deleteCompletedJobs, deleteIntermediateFiles, deleteAbortedOutput, openProgressWindow, useadvancedtooltips, autoSelectHDStreams, autoscroll, alwaysOnTop, safeProfileAlteration, addTimePosition, alwaysbackupfiles, bUseITU, bUse10BitsX264, forcerawavcextension, bAutoLoadDG, bAutoStartQueueStartup, bAlwaysMuxMKV, b64bitX264, bUseQAAC, bEnsureCorrectPlaybackSpeed, bOpenAVSInThread, bUseDGIndexNV, bUseNeroAacEnc, bExternalMuxerX264;
		quint64 audioSamplesPerUpdate;
		decimal forceFilmThreshold, acceptableFPSError;
		int nbPasses, autoUpdateServerSubList, minComplexity, updateFormSplitter, maxComplexity, jobColumnWidth, inputColumnWidth, outputColumnWidth, codecColumnWidth, modeColumnWidth, statusColumnWidth, ownerColumnWidth, startColumnWidth, endColumnWidth, fpsColumnWidth, updateFormUpdateColumnWidth, updateFormNameColumnWidth, updateFormLocalVersionColumnWidth, updateFormServerVersionColumnWidth, updateFormLocalDateColumnWidth, updateFormServerDateColumnWidth, updateFormPlatformColumnWidth, updateFormStatusColumnWidth, ffmsThreads;
		MeXgui::SourceDetectorSettings *sdSettings;
		AutoEncodeDefaultsSettings *aedSettings;
		MeXgui::DialogSettings *dialogSettings;
		ProcessPriority defaultPriority;
		Point *mainFormLocation, *updateFormLocation;
		Size *mainFormSize, *updateFormSize, *jobWorkerSize;
//ORIGINAL LINE: private FileSize[] customFileSizes;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		FileSize *customFileSizes;
//ORIGINAL LINE: private FPS[] customFPSs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		FPS *customFPSs;
//ORIGINAL LINE: private Dar[] customDARs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		Dar *customDARs;
		OCGUIMode ocGUIMode;
		MeXgui::AfterEncoding afterEncoding;
		ProxyMode httpProxyMode;
	public:
		MeXguiSettings();

	private:
		QString getDownloadPath(const QString &strPath);

	public:
		const QString &getYadifPath() const;

		const Point &getMainFormLocation() const;
		void setMainFormLocation(const Point &value);

		const Size &getMainFormSize() const;
		void setMainFormSize(const Size &value);

		const Point &getUpdateFormLocation() const;
		void setUpdateFormLocation(const Point &value);

		const Size &getUpdateFormSize() const;
		void setUpdateFormSize(const Size &value);

		const int &getUpdateFormSplitter() const;
		void setUpdateFormSplitter(const int &value);

		const int &getUpdateFormUpdateColumnWidth() const;
		void setUpdateFormUpdateColumnWidth(const int &value);

		const int &getUpdateFormNameColumnWidth() const;
		void setUpdateFormNameColumnWidth(const int &value);

		const int &getUpdateFormLocalVersionColumnWidth() const;
		void setUpdateFormLocalVersionColumnWidth(const int &value);

		const int &getUpdateFormServerVersionColumnWidth() const;
		void setUpdateFormServerVersionColumnWidth(const int &value);

		const int &getUpdateFormLocalDateColumnWidth() const;
		void setUpdateFormLocalDateColumnWidth(const int &value);

		const int &getUpdateFormServerDateColumnWidth() const;
		void setUpdateFormServerDateColumnWidth(const int &value);

		const int &getUpdateFormPlatformColumnWidth() const;
		void setUpdateFormPlatformColumnWidth(const int &value);

		const int &getUpdateFormStatusColumnWidth() const;
		void setUpdateFormStatusColumnWidth(const int &value);

		const Size &getJobWorkerSize() const;
		void setJobWorkerSize(const Size &value);

		const int &getJobColumnWidth() const;
		void setJobColumnWidth(const int &value);

		const int &getInputColumnWidth() const;
		void setInputColumnWidth(const int &value);

		const int &getOutputColumnWidth() const;
		void setOutputColumnWidth(const int &value);

		const int &getCodecColumnWidth() const;
		void setCodecColumnWidth(const int &value);

		const int &getModeColumnWidth() const;
		void setModeColumnWidth(const int &value);

		const int &getStatusColumnWidth() const;
		void setStatusColumnWidth(const int &value);

		const int &getOwnerColumnWidth() const;
		void setOwnerColumnWidth(const int &value);

		const int &getStartColumnWidth() const;
		void setStartColumnWidth(const int &value);

		const int &getEndColumnWidth() const;
		void setEndColumnWidth(const int &value);

		const int &getFPSColumnWidth() const;
		void setFPSColumnWidth(const int &value);

		const FileSize *getCustomFileSizes() const;
		void setCustomFileSizes(FileSize value[]);

		const FPS *getCustomFPSs() const;
		void setCustomFPSs(FPS value[]);

		const Dar *getCustomDARs() const;
		void setCustomDARs(Dar value[]);

		const quint64 &getAudioSamplesPerUpdate() const;
		void setAudioSamplesPerUpdate(const quint64 &value);

		const QString &getLastSourcePath() const;
		void setLastSourcePath(const QString &value);

		const QString &getLastDestinationPath() const;
		void setLastDestinationPath(const QString &value);

		/// <summary>
		/// Gets / sets whether the log should be autoscrolled
		/// </summary>
		const bool &getAutoScrollLog() const;
		void setAutoScrollLog(const bool &value);

		/// <summary>
		/// Gets / sets whether the one-click advanced settings will be shown
		/// </summary>
		const OCGUIMode &getOneClickGUIMode() const;
		void setOneClickGUIMode(const OCGUIMode &value);

		/// <summary>
		/// Gets / sets whether the playback speed in video preview should match the fps
		/// </summary>
		const bool &getEnsureCorrectPlaybackSpeed() const;
		void setEnsureCorrectPlaybackSpeed(const bool &value);

		const bool &getSafeProfileAlteration() const;
		void setSafeProfileAlteration(const bool &value);

		/// <summary>
		/// Maximum error that the bitrate calculator should accept when rounding the framerate
		/// </summary>
		const decimal &getAcceptableFPSError() const;
		void setAcceptableFPSError(const decimal &value);

		/// <summary>
		/// Which sublist to look in for the update servers
		/// </summary>
		const int &getAutoUpdateServerSubList() const;
		void setAutoUpdateServerSubList(const int &value);

		/// <summary>
		/// Last update check
		/// </summary>
		const DateTime &getLastUpdateCheck() const;
		void setLastUpdateCheck(const DateTime &value);

		/// <summary>
		/// Last update server
		/// </summary>
		const QString &getLastUpdateServer() const;
		void setLastUpdateServer(const QString &value);

		/// <summary>
		/// List of servers to use for autoupdate
		/// </summary>
		const QString **getAutoUpdateServerLists() const;
		void setAutoUpdateServerLists(QString value[][]);

		/// <summary>
		/// What to do after all encodes are finished
		/// </summary>
		const MeXgui::AfterEncoding &getAfterEncoding() const;
		void setAfterEncoding(const MeXgui::AfterEncoding &value);

		/// <summary>
		/// Command to run after encoding is finished (only if AfterEncoding is RunCommand)
		/// </summary>
		const QString &getAfterEncodingCommand() const;
		void setAfterEncodingCommand(const QString &value);

		/// <summary>
		/// bool to decide whether to use advanced or basic tooltips
		/// </summary>
		const bool &getUseAdvancedTooltips() const;
		void setUseAdvancedTooltips(const bool &value);

		/// <summary>
		/// bool to decide whether to use 64bit x264
		/// </summary>
		const bool &getUse64bitX264() const;
		void setUse64bitX264(const bool &value);

		/// <summary>
		/// bool to decide whether to use 10bit x264
		/// </summary>
		const bool &getUse10bitsX264() const;
		void setUse10bitsX264(const bool &value);

		///<summary>
		/// gets / sets whether MeXgui puts the Video Preview Form "Alwyas on Top" or not
		/// </summary>
		const bool &getAlwaysOnTop() const;
		void setAlwaysOnTop(const bool &value);

		///<summary>
		/// gets / sets whether MeXgui add the Time Position or not to the Video Player
		/// </summary>
		const bool &getAddTimePosition() const;
		void setAddTimePosition(const bool &value);

		/// <summary>
		/// bool to decide whether to use external muxer for the x264 encoder
		/// </summary>
		const bool &getUseExternalMuxerX264() const;
		void setUseExternalMuxerX264(const bool &value);
		/// <summary>
		/// gets / sets the default output directory
		/// </summary>
		const QString &getDefaultOutputDir() const;
		void setDefaultOutputDir(const QString &value);

		/// <summary>
		/// gets / sets the temp directory for MP4 Muxer
		/// </summary>
		const QString &getTempDirMP4() const;
		void setTempDirMP4(const QString &value);

		/// <summary>
		/// path of besplit.exe
		/// </summary>
		const QString &getBeSplitPath() const;

		/// <summary>
		/// filename and full path of the ffmpeg executable
		/// </summary>
		const QString &getFFMpegPath() const;

		/// <summary>
		/// filename and full path of the vobsub dll
		/// </summary>
		const QString &getVobSubPath() const;

		/// <summary>
		/// filename and full path of the bassaudio dll
		/// </summary>
		const QString &getBassPath() const;

		/// <summary>
		/// filename and full path of the oggenc2 executable
		/// </summary>
		const QString &getOggEnc2Path() const;

		/// <summary>
		/// filename and full path of the lame executable
		/// </summary>
		const QString &getLamePath() const;

		/// <summary>
		/// filename and full path of the mkvmerge executable
		/// </summary>
		const QString &getMkvmergePath() const;

		/// <summary>
		/// filename and full path of the mkvextract executable
		/// </summary>
		const QString &getMkvExtractPath() const;

		/// <summary>
		/// filename and full path of the mp4creator executable
		/// </summary>
		const QString &getMp4boxPath() const;

		/// <summary>
		/// filename and full path of the pgcdemux executable
		/// </summary>
		const QString &getPgcDemuxPath() const;

		/// <summary>
		/// filename and full path of the x264 executable
		/// </summary>
		const QString &getX264Path() const;

		/// <summary>
		/// filename and full path of the x264 10b executable
		/// </summary>
		const QString &getX26410BitsPath() const;

		/// <summary>
		/// filename and full path of the dgindex executable
		/// </summary>
		const QString &getDgIndexPath() const;
		/// <summary>
		/// filename and full path of the ffmsindex executable
		/// </summary>
		const QString &getFFMSIndexPath() const;
		/// <summary>
		/// filename and full path of the avisynth dll
		/// </summary>
		const QString &getAviSynthPath() const;
		/// <summary>
		/// filename and full path of the xvid_encraw executable
		/// </summary>
		const QString &getXviDEncrawPath() const;
		/// <summary>
		/// gets / sets the path of the avimuxgui executable
		/// </summary>
		const QString &getAviMuxGUIPath() const;
		/// <summary>
		/// filename and full path of the aften executable
		/// </summary>
		const QString &getAftenPath() const;
		/// <summary>
		/// filename and full path of the flac executable
		/// </summary>
		const QString &getFlacPath() const;
		/// <summary>
		/// filename and full path of the dgavcindex executable
		/// </summary>
		const QString &getDgavcIndexPath() const;
		/// <summary>
		/// filename and full path of the dgmpgindex executable
		/// </summary>
		const QString &getDgnvIndexPath() const;
		/// <summary>
		/// filename and full path of the eac3to executable
		/// </summary>
		const QString &getEAC3toPath() const;
		/// <summary>
		/// filename and full path of the tsmuxer executable
		/// </summary>
		const QString &getTSMuxerPath() const;

		/// <summary>
		/// filename and full path of the qaac executable
		/// </summary>
		const QString &getQaacPath() const;

		/// <summary>
		/// filename and full path of the opus executable
		/// </summary>
		const QString &getOpusPath() const;

		///<summary>
		/// gets / sets whether MeXgui backup files from updater or not
		/// </summary>
		const bool &getAlwaysBackUpFiles() const;
		void setAlwaysBackUpFiles(const bool &value);
		///<summary>
		/// gets / sets whether to force raw AVC file Extension for QuickTime compatibility
		/// more infos here : http://forum.doom9.org/showthread.php?p=1243370#post1243370
		/// </summary>
		const bool &getForceRawAVCExtension() const;
		void setForceRawAVCExtension(const bool &value);

		/// <summary>
		/// Haali Media Splitter Path
		/// </summary>
		const static QString &getHaaliMSPath() const;

		/// <summary>
		/// folder containing the avisynth plugins
		/// </summary>
		const QString &getAvisynthPluginsPath() const;

		/// <summary>
		/// folder containing local copies of update files
		/// </summary>
		const QString &getMeXguiUpdateCache() const;

		/// <summary>
		/// should the video bitrate be recalculated after credits encoding in video only mode?
		/// </summary>
		const bool &getRecalculateMainMovieBitrate() const;
		void setRecalculateMainMovieBitrate(const bool &value);
		/// <summary>
		/// should force film automatically be applies if the film percentage crosses the forceFilmTreshold?
		/// </summary>
		const bool &getAutoForceFilm() const;
		void setAutoForceFilm(const bool &value);
		/// <summary>
		/// should the file autoloaded incrementally if VOB
		/// </summary>
		const bool &getAutoLoadDG() const;
		void setAutoLoadDG(const bool &value);
		/// <summary>
		/// true if HD Streams Extractor should automatically select tracks
		/// </summary>
		const bool &getAutoSelectHDStreams() const;
		void setAutoSelectHDStreams(const bool &value);
		/// <summary>
		/// gets / sets whether pressing Queue should automatically start encoding at startup
		/// </summary>
		const bool &getAutoStartQueueStartup() const;
		void setAutoStartQueueStartup(const bool &value);
		/// <summary>
		/// gets / sets whether MKV files should always be muxed with mkvmerge even if x264 can output it directly
		/// </summary>
		const bool &getAlwaysMuxMKV() const;
		void setAlwaysMuxMKV(const bool &value);
		/// <summary>
		/// gets / sets whether pressing Queue should automatically start encoding
		/// </summary>
		const bool &getAutoStartQueue() const;
		void setAutoStartQueue(const bool &value);
		/// <summary>
		/// gets / sets whether MeXgui automatically opens the preview window upon loading an avisynth script
		/// </summary>
		const bool &getAutoOpenScript() const;
		void setAutoOpenScript(const bool &value);
		/// <summary>
		/// gets / sets whether the progress window should be opened for each job
		/// </summary>
		const bool &getOpenProgressWindow() const;
		void setOpenProgressWindow(const bool &value);
		/// <summary>
		/// the threshold to apply force film. If the film percentage is higher than this threshold,
		/// force film will be applied
		/// </summary>
		const decimal &getForceFilmThreshold() const;
		void setForceFilmThreshold(const decimal &value);
		/// <summary>
		/// <summary>
		/// first default language
		/// </summary>
		const QString &getDefaultLanguage1() const;
		void setDefaultLanguage1(const QString &value);
		/// <summary>
		/// second default language
		/// </summary>
		const QString &getDefaultLanguage2() const;
		void setDefaultLanguage2(const QString &value);
		/// <summary>
		/// default priority for all processes
		/// </summary>
		const ProcessPriority &getDefaultPriority() const;
		void setDefaultPriority(const ProcessPriority &value);
	private:
		ProcessPriority processingPriority;
		bool processingPrioritySet;
		/// <summary>
		/// default priority for all new processes during this session
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const ProcessPriority &getProcessingPriority() const;
		void setProcessingPriority(const ProcessPriority &value);
		/// <summary>
		/// open AVS files in a thread
		/// </summary>
		const bool &getOpenAVSInThread() const;
		void setOpenAVSInThread(const bool &value);
	private:
		bool bOpenAVSInThreadDuringSession;
		bool bOpenAVSInThreadDuringSessionSet;
		/// <summary>
		/// default priority for all new processes during this session
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const bool &getOpenAVSInThreadDuringSession() const;
		void setOpenAVSInThreadDuringSession(const bool &value);
		/// <summary>
		/// enables no spec compliant mp3 in mp4 muxing
		/// </summary>
		const bool &getEnableMP3inMP4() const;
		void setEnableMP3inMP4(const bool &value);
		/// <summary>
		/// sets / gets if the stats file is updated in the 3rd pass of 3 pass encoding
		/// </summary>
		const bool &getOverwriteStats() const;
		void setOverwriteStats(const bool &value);
		/// <summary>
		///  gets / sets if the output is video output of the 2nd pass is overwritten in the 3rd pass of 3 pass encoding
		/// </summary>
		const bool &getKeep2of3passOutput() const;
		void setKeep2of3passOutput(const bool &value);
		/// <summary>
		/// sets the number of passes to be done in automated encoding mode
		/// </summary>
		const int &getNbPasses() const;
		void setNbPasses(const int &value);
		/// <summary>
		/// sets / gets whether completed jobs will be deleted
		/// </summary>
		const bool &getDeleteCompletedJobs() const;
		void setDeleteCompletedJobs(const bool &value);
		/// <summary>
		/// sets / gets if intermediate files are to be deleted after encoding
		/// </summary>
		const bool &getDeleteIntermediateFiles() const;
		void setDeleteIntermediateFiles(const bool &value);
		/// <summary>
		/// gets / sets if the output of an aborted job is to be deleted
		/// </summary>
		const bool &getDeleteAbortedOutput() const;
		void setDeleteAbortedOutput(const bool &value);
		const QString &getVideoExtension() const;
		void setVideoExtension(const QString &value);
		const QString &getAudioExtension() const;
		void setAudioExtension(const QString &value);
		const bool &getAutoUpdate() const;
		void setAutoUpdate(const bool &value);
		const MeXgui::DialogSettings &getDialogSettings() const;
		void setDialogSettings(const MeXgui::DialogSettings &value);
		const MeXgui::SourceDetectorSettings &getSourceDetectorSettings() const;
		void setSourceDetectorSettings(const MeXgui::SourceDetectorSettings &value);
		/// <summary>
		/// gets / sets the default settings for the autoencode window
		/// </summary>
		const AutoEncodeDefaultsSettings &getAedSettings() const;
		void setAedSettings(const AutoEncodeDefaultsSettings &value);
		/// <summary>
		/// gets / sets the default settings for the Proxy
		/// </summary>
		const ProxyMode &getHttpProxyMode() const;
		void setHttpProxyMode(const ProxyMode &value);
		/// <summary>
		/// gets / sets the default settings for the Proxy Adress
		/// </summary>
		const QString &getHttpProxyAddress() const;
		void setHttpProxyAddress(const QString &value);
		/// <summary>
		/// gets / sets the default settings for the Proxy Port
		/// </summary>
		const QString &getHttpProxyPort() const;
		void setHttpProxyPort(const QString &value);
		/// <summary>
		/// gets / sets the default settings for the Proxy Uid
		/// </summary>
		const QString &getHttpProxyUid() const;
		void setHttpProxyUid(const QString &value);
		/// <summary>
		/// gets / sets the default settings for the Proxy Password
		/// </summary>
		const QString &getHttpProxyPwd() const;
		void setHttpProxyPwd(const QString &value);
		/// <summary>
		/// gets / sets the default settings for the Proxy
		/// </summary>
		const QString &getUseHttpProxy() const;
		void setUseHttpProxy(const QString &value);
		/// <summary>
		/// gets / sets the text to append to forced streams
		/// </summary>
		const QString &getAppendToForcedStreams() const;
		void setAppendToForcedStreams(const QString &value);

		const QString &getMainAudioFormat() const;
		void setMainAudioFormat(const QString &value);

		const QString &getMainFileFormat() const;
		void setMainFileFormat(const QString &value);

		const QString &getLastUsedOneClickFolder() const;
		void setLastUsedOneClickFolder(const QString &value);

		const int &getMinComplexity() const;
		void setMinComplexity(const int &value);

		const int &getMaxComplexity() const;
		void setMaxComplexity(const int &value);

		const int &getFFMSThreads() const;
		void setFFMSThreads(const int &value);

		const bool &getUseITUValues() const;
		void setUseITUValues(const bool &value);

		const bool &getUseDGIndexNV() const;
		void setUseDGIndexNV(const bool &value);

		/// <summary>
		/// filename and full path of the neroaacenc executable
		/// </summary>
		const QString &getNeroAacEncPath() const;
		void setNeroAacEncPath(const QString &value);

		const bool &getUseNeroAacEnc() const;
		void setUseNeroAacEnc(const bool &value);

		const bool &getUseQAAC() const;
		void setUseQAAC(const bool &value);


	private:
		bool bAutoUpdateSession;
		/// <summary>
		/// automatic update process
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const bool &getAutoUpdateSession() const;
		void setAutoUpdateSession(const bool &value);

	private:
		bool bPortableAviSynth;
		/// <summary>
		/// portable avisynth in use
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const bool &getPortableAviSynth() const;
		void setPortableAviSynth(const bool &value);

		bool IsNeroAACEncAvailable();

		bool IsQAACAvailable();

		bool IsDGIIndexerAvailable();

		bool Is10Bitx264Available();

	};
	enum AfterEncoding
	{
		DoNothing = 0,
		Shutdown = 1,
		RunCommand = 2,
		CloseMeXgui = 3
	};
	enum ProxyMode
	{
		None = 0,
		SystemProxy = 1,
		CustomProxy = 2,
		CustomProxyWithLogin = 3
	};
}
