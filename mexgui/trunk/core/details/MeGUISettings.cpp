#include "MeGUISettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::util;
using namespace MeGUI::core::gui;

namespace MeGUI
{

	MeGUISettings::MeGUISettings()
	{
		strMeGUIPath = System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath);
		autoscroll = true;
		autoUpdateServerLists = new std::string[][] {new std::string[] {"Stable", "http://megui.org/auto/stable/", "http://megui.xvidvideo.ru/auto/stable/"}, new std::string[] {"Development", "http://megui.org/auto/", "http://megui.xvidvideo.ru/auto/"}, new std::string[] {"Custom"}};
		lastUpdateCheck = DateTime::Now::ToUniversalTime();
		lastUpdateServer = "";
		acceptableFPSError = 0.01;
		autoUpdateServerSubList = 0;
		autoUpdate = true;
		dialogSettings = new DialogSettings();
		sdSettings = new SourceDetectorSettings();
		setAedSettings(new AutoEncodeDefaultsSettings());
		useadvancedtooltips = true;
		audioSamplesPerUpdate = 100000;
		aviMuxGUIPath = getDownloadPath("tools\\avimux_gui\\avimux_gui.exe");
		mp4boxPath = getDownloadPath("tools\\mp4box\\mp4box.exe");
		mkvmergePath = getDownloadPath("tools\\mkvmerge\\mkvmerge.exe");
		mkvExtractPath = getDownloadPath("tools\\mkvmerge\\mkvextract.exe");
		pgcDemuxPath = getDownloadPath("tools\\pgcdemux\\pgcdemux.exe");
		qaacPath = getDownloadPath("tools\\qaac\\qaac.exe");
		opusPath = getDownloadPath("tools\\opus\\opusenc.exe");
	#if defined(x64)
		x264Path = getDownloadPath("tools\\x264\\x264_64.exe");
		b64bitX264 = true;
		x26410BitsPath = getDownloadPath("tools\\x264_10b\\x264-10b_64.exe");
	#endif
	#if defined(x86)
		x264Path = getDownloadPath("tools\\x264\\x264.exe");
		x26410BitsPath = getDownloadPath("tools\\x264_10b\\x264-10b.exe");
		if (OSInfo::isWow64())
			b64bitX264 = true;
	#endif
		dgIndexPath = getDownloadPath("tools\\dgindex\\dgindex.exe");
		ffmsIndexPath = getDownloadPath("tools\\ffms\\ffmsindex.exe");
		xvidEncrawPath = getDownloadPath("tools\\xvid_encraw\\xvid_encraw.exe");
		lamePath = getDownloadPath("tools\\lame\\lame.exe");
		neroAacEncPath = strMeGUIPath + "\\tools\\eac3to\\neroAacEnc.exe";
		oggEnc2Path = getDownloadPath("tools\\oggenc2\\oggenc2.exe");
		ffmpegPath = getDownloadPath("tools\\ffmpeg\\ffmpeg.exe");
		aftenPath = getDownloadPath("tools\\aften\\aften.exe");
		flacPath = getDownloadPath("tools\\flac\\flac.exe");
		yadifPath = getDownloadPath("tools\\yadif\\yadif.dll");
		bassPath = getDownloadPath("tools\\bassaudio\\bassaudio.dll");
		vobSubPath = getDownloadPath("tools\\vobsub\\vobsub.dll");
		besplitPath = getDownloadPath("tools\\besplit\\besplit.exe");
		dgavcIndexPath = getDownloadPath("tools\\dgavcindex\\dgavcindex.exe");
		dgnvIndexPath = getDownloadPath("tools\\dgindexnv\\dgindexnv.exe");
		eac3toPath = getDownloadPath("tools\\eac3to\\eac3to.exe");
		tsmuxerPath = getDownloadPath("tools\\tsmuxer\\tsmuxer.exe");
		aviSynthPath = getDownloadPath("tools\\avs\\avisynth.dll");
		meguiupdatecache = System::IO::Path::Combine(strMeGUIPath, "update_cache");
		avisynthpluginspath = System::IO::Path::Combine(strMeGUIPath, "tools\\avisynth_plugin");
		recalculateMainMovieBitrate = false;
		autoForceFilm = true;
		bAutoLoadDG = true;
		autoStartQueue = true;
		bAlwaysMuxMKV = true;
		bAutoStartQueueStartup = false;
		forceFilmThreshold = decimal(95);
		defaultLanguage1 = "";
		defaultLanguage2 = "";
		defaultPriority = IDLE;
		afterEncoding = DoNothing;
		autoOpenScript = true;
		enableMP3inMP4 = false;
		overwriteStats = true;
		keep2of3passOutput = false;
		deleteCompletedJobs = false;
		nbPasses = 2;
		deleteIntermediateFiles = true;
		deleteAbortedOutput = true;
		autoSelectHDStreams = true;
		openProgressWindow = true;
		videoExtension = "";
		audioExtension = "";
		safeProfileAlteration = false;
		alwaysOnTop = false;
		httpProxyMode = None;
		httpproxyaddress = "";
		httpproxyport = "";
		httpproxyuid = "";
		httpproxypwd = "";
		defaultOutputDir = "";
		tempDirMP4 = "";
		addTimePosition = true;
		alwaysbackupfiles = true;
		forcerawavcextension = false;
		strMainFileFormat = "";
		strMainAudioFormat = "";
		strLastSourcePath = "";
		strLastDestinationPath = "";
		minComplexity = 72;
		maxComplexity = 78;
		mainFormLocation = new Point(0, 0);
		mainFormSize = new Size(604, 478);
		updateFormLocation = new Point(0, 0);
		updateFormSize = new Size(710, 313);
		updateFormSplitter = 180;
		updateFormUpdateColumnWidth = 47;
		updateFormNameColumnWidth = 105;
		updateFormLocalVersionColumnWidth = 117;
		updateFormServerVersionColumnWidth = 117;
		updateFormLocalDateColumnWidth = 70;
		updateFormServerDateColumnWidth = 70;
		updateFormPlatformColumnWidth = 52;
		updateFormStatusColumnWidth = 111;
		jobWorkerSize = new Size(565, 498);
		jobColumnWidth = 40;
		inputColumnWidth = 89;
		outputColumnWidth = 89;
		codecColumnWidth = 43;
		setModeColumnWidth(75);
		statusColumnWidth = 51;
		ownerColumnWidth = 60;
		startColumnWidth = 55;
		endColumnWidth = 55;
		fpsColumnWidth = 35;
		bEnsureCorrectPlaybackSpeed = bUseDGIndexNV = bUseNeroAacEnc = bUseQAAC = false;
		ffmsThreads = 1;
		appendToForcedStreams = "";
		ocGUIMode = Default;
		bUseITU = true;
		bOpenAVSInThread = true;
		lastUsedOneClickFolder = "";
		bUse10BitsX264 = false;
	}

	std::string MeGUISettings::getDownloadPath(const std::string &strPath)
	{
		strPath = System::IO::Path::Combine(strMeGUIPath, strPath);
		return strPath;
	}

	const std::string &MeGUISettings::getYadifPath() const
	{
		return yadifPath;
	}

	const Point &MeGUISettings::getMainFormLocation() const
	{
		return mainFormLocation;
	}

	void MeGUISettings::setMainFormLocation(const Point &value)
	{
		mainFormLocation = value;
	}

	const Size &MeGUISettings::getMainFormSize() const
	{
		return mainFormSize;
	}

	void MeGUISettings::setMainFormSize(const Size &value)
	{
		mainFormSize = value;
	}

	const Point &MeGUISettings::getUpdateFormLocation() const
	{
		return updateFormLocation;
	}

	void MeGUISettings::setUpdateFormLocation(const Point &value)
	{
		updateFormLocation = value;
	}

	const Size &MeGUISettings::getUpdateFormSize() const
	{
		return updateFormSize;
	}

	void MeGUISettings::setUpdateFormSize(const Size &value)
	{
		updateFormSize = value;
	}

	const int &MeGUISettings::getUpdateFormSplitter() const
	{
		return updateFormSplitter;
	}

	void MeGUISettings::setUpdateFormSplitter(const int &value)
	{
		updateFormSplitter = value;
	}

	const int &MeGUISettings::getUpdateFormUpdateColumnWidth() const
	{
		return updateFormUpdateColumnWidth;
	}

	void MeGUISettings::setUpdateFormUpdateColumnWidth(const int &value)
	{
		updateFormUpdateColumnWidth = value;
	}

	const int &MeGUISettings::getUpdateFormNameColumnWidth() const
	{
		return updateFormNameColumnWidth;
	}

	void MeGUISettings::setUpdateFormNameColumnWidth(const int &value)
	{
		updateFormNameColumnWidth = value;
	}

	const int &MeGUISettings::getUpdateFormLocalVersionColumnWidth() const
	{
		return updateFormLocalVersionColumnWidth;
	}

	void MeGUISettings::setUpdateFormLocalVersionColumnWidth(const int &value)
	{
		updateFormLocalVersionColumnWidth = value;
	}

	const int &MeGUISettings::getUpdateFormServerVersionColumnWidth() const
	{
		return updateFormServerVersionColumnWidth;
	}

	void MeGUISettings::setUpdateFormServerVersionColumnWidth(const int &value)
	{
		updateFormServerVersionColumnWidth = value;
	}

	const int &MeGUISettings::getUpdateFormLocalDateColumnWidth() const
	{
		return updateFormLocalDateColumnWidth;
	}

	void MeGUISettings::setUpdateFormLocalDateColumnWidth(const int &value)
	{
		updateFormLocalDateColumnWidth = value;
	}

	const int &MeGUISettings::getUpdateFormServerDateColumnWidth() const
	{
		return updateFormServerDateColumnWidth;
	}

	void MeGUISettings::setUpdateFormServerDateColumnWidth(const int &value)
	{
		updateFormServerDateColumnWidth = value;
	}

	const int &MeGUISettings::getUpdateFormPlatformColumnWidth() const
	{
		return updateFormPlatformColumnWidth;
	}

	void MeGUISettings::setUpdateFormPlatformColumnWidth(const int &value)
	{
		updateFormPlatformColumnWidth = value;
	}

	const int &MeGUISettings::getUpdateFormStatusColumnWidth() const
	{
		return updateFormStatusColumnWidth;
	}

	void MeGUISettings::setUpdateFormStatusColumnWidth(const int &value)
	{
		updateFormStatusColumnWidth = value;
	}

	const Size &MeGUISettings::getJobWorkerSize() const
	{
		return jobWorkerSize;
	}

	void MeGUISettings::setJobWorkerSize(const Size &value)
	{
		jobWorkerSize = value;
	}

	const int &MeGUISettings::getJobColumnWidth() const
	{
		return jobColumnWidth;
	}

	void MeGUISettings::setJobColumnWidth(const int &value)
	{
		jobColumnWidth = value;
	}

	const int &MeGUISettings::getInputColumnWidth() const
	{
		return inputColumnWidth;
	}

	void MeGUISettings::setInputColumnWidth(const int &value)
	{
		inputColumnWidth = value;
	}

	const int &MeGUISettings::getOutputColumnWidth() const
	{
		return outputColumnWidth;
	}

	void MeGUISettings::setOutputColumnWidth(const int &value)
	{
		outputColumnWidth = value;
	}

	const int &MeGUISettings::getCodecColumnWidth() const
	{
		return codecColumnWidth;
	}

	void MeGUISettings::setCodecColumnWidth(const int &value)
	{
		codecColumnWidth = value;
	}

	const int &MeGUISettings::getModeColumnWidth() const
	{
		return modeColumnWidth;
	}

	void MeGUISettings::setModeColumnWidth(const int &value)
	{
		modeColumnWidth = value;
	}

	const int &MeGUISettings::getStatusColumnWidth() const
	{
		return statusColumnWidth;
	}

	void MeGUISettings::setStatusColumnWidth(const int &value)
	{
		statusColumnWidth = value;
	}

	const int &MeGUISettings::getOwnerColumnWidth() const
	{
		return ownerColumnWidth;
	}

	void MeGUISettings::setOwnerColumnWidth(const int &value)
	{
		ownerColumnWidth = value;
	}

	const int &MeGUISettings::getStartColumnWidth() const
	{
		return startColumnWidth;
	}

	void MeGUISettings::setStartColumnWidth(const int &value)
	{
		startColumnWidth = value;
	}

	const int &MeGUISettings::getEndColumnWidth() const
	{
		return endColumnWidth;
	}

	void MeGUISettings::setEndColumnWidth(const int &value)
	{
		endColumnWidth = value;
	}

	const int &MeGUISettings::getFPSColumnWidth() const
	{
		return fpsColumnWidth;
	}

	void MeGUISettings::setFPSColumnWidth(const int &value)
	{
		fpsColumnWidth = value;
	}

	const FileSize &MeGUISettings::getCustomFileSizes() const
	{
		return customFileSizes;
	}

	void MeGUISettings::setCustomFileSizes(const FileSize &value[])
	{
		customFileSizes = value;
	}

	const FPS &MeGUISettings::getCustomFPSs() const
	{
		return customFPSs;
	}

	void MeGUISettings::setCustomFPSs(const FPS &value[])
	{
		customFPSs = value;
	}

	const Dar &MeGUISettings::getCustomDARs() const
	{
		return customDARs;
	}

	void MeGUISettings::setCustomDARs(const Dar &value[])
	{
		customDARs = value;
	}

	const unsigned long long &MeGUISettings::getAudioSamplesPerUpdate() const
	{
		return audioSamplesPerUpdate;
	}

	void MeGUISettings::setAudioSamplesPerUpdate(const unsigned long long &value)
	{
		audioSamplesPerUpdate = value;
	}

	const std::string &MeGUISettings::getLastSourcePath() const
	{
		return strLastSourcePath;
	}

	void MeGUISettings::setLastSourcePath(const std::string &value)
	{
		strLastSourcePath = value;
	}

	const std::string &MeGUISettings::getLastDestinationPath() const
	{
		return strLastDestinationPath;
	}

	void MeGUISettings::setLastDestinationPath(const std::string &value)
	{
		strLastDestinationPath = value;
	}

	const bool &MeGUISettings::getAutoScrollLog() const
	{
		return autoscroll;
	}

	void MeGUISettings::setAutoScrollLog(const bool &value)
	{
		autoscroll = value;
	}

	const MeGUI::MeGUISettings::OCGUIMode &MeGUISettings::getOneClickGUIMode() const
	{
		return ocGUIMode;
	}

	void MeGUISettings::setOneClickGUIMode(const OCGUIMode &value)
	{
		ocGUIMode = value;
	}

	const bool &MeGUISettings::getEnsureCorrectPlaybackSpeed() const
	{
		return bEnsureCorrectPlaybackSpeed;
	}

	void MeGUISettings::setEnsureCorrectPlaybackSpeed(const bool &value)
	{
		bEnsureCorrectPlaybackSpeed = value;
	}

	const bool &MeGUISettings::getSafeProfileAlteration() const
	{
		return safeProfileAlteration;
	}

	void MeGUISettings::setSafeProfileAlteration(const bool &value)
	{
		safeProfileAlteration = value;
	}

	const decimal &MeGUISettings::getAcceptableFPSError() const
	{
		return acceptableFPSError;
	}

	void MeGUISettings::setAcceptableFPSError(const decimal &value)
	{
		acceptableFPSError = value;
	}

	const int &MeGUISettings::getAutoUpdateServerSubList() const
	{
		return autoUpdateServerSubList;
	}

	void MeGUISettings::setAutoUpdateServerSubList(const int &value)
	{
		autoUpdateServerSubList = value;
	}

	const DateTime &MeGUISettings::getLastUpdateCheck() const
	{
		return lastUpdateCheck;
	}

	void MeGUISettings::setLastUpdateCheck(const DateTime &value)
	{
		lastUpdateCheck = value;
	}

	const std::string &MeGUISettings::getLastUpdateServer() const
	{
		return lastUpdateServer;
	}

	void MeGUISettings::setLastUpdateServer(const std::string &value)
	{
		lastUpdateServer = value;
	}

	const std::string &*MeGUISettings::getAutoUpdateServerLists() const
	{
		if (sizeof(autoUpdateServerLists) / sizeof(autoUpdateServerLists[0]) > 2)
		{
			autoUpdateServerLists[0] = new std::string[] {"Stable", "http://megui.org/auto/stable/", "http://megui.xvidvideo.ru/auto/stable/"};
			autoUpdateServerLists[1] = new std::string[] {"Development", "http://megui.org/auto/", "http://megui.xvidvideo.ru/auto/"};
		}
		else
		{
			autoUpdateServerLists = new std::string[][] {new std::string[] {"Stable", "http://megui.org/auto/stable/", "http://megui.xvidvideo.ru/auto/stable/"}, new std::string[] {"Development", "http://megui.org/auto/", "http://megui.xvidvideo.ru/auto/"}, new std::string[] {"Custom"}};
		}
	#if defined(x64)
		autoUpdateServerLists = new std::string[][] {new std::string[] {"Stable", "http://megui.org/auto/", "http://megui.xvidvideo.ru/auto/"}, new std::string[] {"Development", "http://megui.org/auto/", "http://megui.xvidvideo.ru/auto/"}, new std::string[] {"Custom", "http://megui.org/auto/", "http://megui.xvidvideo.ru/auto/"}};
	#endif
	#if defined(DEBUG)
		autoUpdateServerLists = new std::string[][] {new std::string[] {"Stable", "http://megui.org/auto/"}, new std::string[] {"Development", "http://megui.org/auto/"}, new std::string[] {"Custom", "http://megui.org/auto/"}};
	#endif
		return autoUpdateServerLists;
	}

	void MeGUISettings::setAutoUpdateServerLists(const std::string &value[][])
	{
		autoUpdateServerLists = value;
	}

	const MeGUI::AfterEncoding &MeGUISettings::getAfterEncoding() const
	{
		return afterEncoding;
	}

	void MeGUISettings::setAfterEncoding(const MeGUI::AfterEncoding &value)
	{
		afterEncoding = value;
	}

	const std::string &MeGUISettings::getAfterEncodingCommand() const
	{
		return afterEncodingCommand;
	}

	void MeGUISettings::setAfterEncodingCommand(const std::string &value)
	{
		afterEncodingCommand = value;
	}

	const bool &MeGUISettings::getUseAdvancedTooltips() const
	{
		return useadvancedtooltips;
	}

	void MeGUISettings::setUseAdvancedTooltips(const bool &value)
	{
		useadvancedtooltips = value;
	}

	const bool &MeGUISettings::getUse64bitX264() const
	{
		return b64bitX264;
	}

	void MeGUISettings::setUse64bitX264(const bool &value)
	{
		b64bitX264 = value;
	}

	const bool &MeGUISettings::getUse10bitsX264() const
	{
		return bUse10BitsX264;
	}

	void MeGUISettings::setUse10bitsX264(const bool &value)
	{
		bUse10BitsX264 = value;
	}

	const bool &MeGUISettings::getAlwaysOnTop() const
	{
		return alwaysOnTop;
	}

	void MeGUISettings::setAlwaysOnTop(const bool &value)
	{
		alwaysOnTop = value;
	}

	const bool &MeGUISettings::getAddTimePosition() const
	{
		return addTimePosition;
	}

	void MeGUISettings::setAddTimePosition(const bool &value)
	{
		addTimePosition = value;
	}

	const bool &MeGUISettings::getUseExternalMuxerX264() const
	{
		return bExternalMuxerX264;
	}

	void MeGUISettings::setUseExternalMuxerX264(const bool &value)
	{
		bExternalMuxerX264 = value;
	}

	const std::string &MeGUISettings::getDefaultOutputDir() const
	{
		return defaultOutputDir;
	}

	void MeGUISettings::setDefaultOutputDir(const std::string &value)
	{
		defaultOutputDir = value;
	}

	const std::string &MeGUISettings::getTempDirMP4() const
	{
		if (tempDirMP4.empty() || System::IO::Path::GetPathRoot(tempDirMP4)->Equals(tempDirMP4, StringComparison::CurrentCultureIgnoreCase))
			return "";
		return tempDirMP4;
	}

	void MeGUISettings::setTempDirMP4(const std::string &value)
	{
		tempDirMP4 = value;
	}

	const std::string &MeGUISettings::getBeSplitPath() const
	{
		return besplitPath;
	}

	const std::string &MeGUISettings::getFFMpegPath() const
	{
		return ffmpegPath;
	}

	const std::string &MeGUISettings::getVobSubPath() const
	{
		return vobSubPath;
	}

	const std::string &MeGUISettings::getBassPath() const
	{
		return bassPath;
	}

	const std::string &MeGUISettings::getOggEnc2Path() const
	{
		return oggEnc2Path;
	}

	const std::string &MeGUISettings::getLamePath() const
	{
		return lamePath;
	}

	const std::string &MeGUISettings::getMkvmergePath() const
	{
		return mkvmergePath;
	}

	const std::string &MeGUISettings::getMkvExtractPath() const
	{
		return mkvExtractPath;
	}

	const std::string &MeGUISettings::getMp4boxPath() const
	{
		return mp4boxPath;
	}

	const std::string &MeGUISettings::getPgcDemuxPath() const
	{
		return pgcDemuxPath;
	}

	const std::string &MeGUISettings::getX264Path() const
	{
		return x264Path;
	}

	const std::string &MeGUISettings::getX26410BitsPath() const
	{
		return x26410BitsPath;
	}

	const std::string &MeGUISettings::getDgIndexPath() const
	{
		return dgIndexPath;
	}

	const std::string &MeGUISettings::getFFMSIndexPath() const
	{
		return ffmsIndexPath;
	}

	const std::string &MeGUISettings::getAviSynthPath() const
	{
		return aviSynthPath;
	}

	const std::string &MeGUISettings::getXviDEncrawPath() const
	{
		return xvidEncrawPath;
	}

	const std::string &MeGUISettings::getAviMuxGUIPath() const
	{
		return aviMuxGUIPath;
	}

	const std::string &MeGUISettings::getAftenPath() const
	{
		return aftenPath;
	}

	const std::string &MeGUISettings::getFlacPath() const
	{
		return flacPath;
	}

	const std::string &MeGUISettings::getDgavcIndexPath() const
	{
		return dgavcIndexPath;
	}

	const std::string &MeGUISettings::getDgnvIndexPath() const
	{
		return dgnvIndexPath;
	}

	const std::string &MeGUISettings::getEAC3toPath() const
	{
		return eac3toPath;
	}

	const std::string &MeGUISettings::getTSMuxerPath() const
	{
		return tsmuxerPath;
	}

	const std::string &MeGUISettings::getQaacPath() const
	{
		return qaacPath;
	}

	const std::string &MeGUISettings::getOpusPath() const
	{
		return opusPath;
	}

	const bool &MeGUISettings::getAlwaysBackUpFiles() const
	{
		return alwaysbackupfiles;
	}

	void MeGUISettings::setAlwaysBackUpFiles(const bool &value)
	{
		alwaysbackupfiles = value;
	}

	const bool &MeGUISettings::getForceRawAVCExtension() const
	{
		return forcerawavcextension;
	}

	void MeGUISettings::setForceRawAVCExtension(const bool &value)
	{
		forcerawavcextension = value;
	}

	const std::string &MeGUISettings::getHaaliMSPath() const
	{
		try
		{
			Microsoft::Win32::RegistryKey *key = 0;
	#if defined(x86)
			key = Microsoft::Win32::Registry::LocalMachine::OpenSubKey("SOFTWARE\\HaaliMkx");
			if (key == 0)
	#endif
				key = Microsoft::Win32::Registry::LocalMachine::OpenSubKey("SOFTWARE\\Wow6432Node\\HaaliMkx");

			if (key == 0)
				return "";

			std::string value = static_cast<std::string>(key->GetValue("Install_Dir"));
			if (value == "")
				return "";
			return value;
		}
		catch (...)
		{
			return "";
		}
	}

	const std::string &MeGUISettings::getAvisynthPluginsPath() const
	{
		return avisynthpluginspath;
	}

	const std::string &MeGUISettings::getMeGUIUpdateCache() const
	{
		return meguiupdatecache;
	}

	const bool &MeGUISettings::getRecalculateMainMovieBitrate() const
	{
		return recalculateMainMovieBitrate;
	}

	void MeGUISettings::setRecalculateMainMovieBitrate(const bool &value)
	{
		recalculateMainMovieBitrate = value;
	}

	const bool &MeGUISettings::getAutoForceFilm() const
	{
		return autoForceFilm;
	}

	void MeGUISettings::setAutoForceFilm(const bool &value)
	{
		autoForceFilm = value;
	}

	const bool &MeGUISettings::getAutoLoadDG() const
	{
		return bAutoLoadDG;
	}

	void MeGUISettings::setAutoLoadDG(const bool &value)
	{
		bAutoLoadDG = value;
	}

	const bool &MeGUISettings::getAutoSelectHDStreams() const
	{
		return autoSelectHDStreams;
	}

	void MeGUISettings::setAutoSelectHDStreams(const bool &value)
	{
		autoSelectHDStreams = value;
	}

	const bool &MeGUISettings::getAutoStartQueueStartup() const
	{
		return bAutoStartQueueStartup;
	}

	void MeGUISettings::setAutoStartQueueStartup(const bool &value)
	{
		bAutoStartQueueStartup = value;
	}

	const bool &MeGUISettings::getAlwaysMuxMKV() const
	{
		return bAlwaysMuxMKV;
	}

	void MeGUISettings::setAlwaysMuxMKV(const bool &value)
	{
		bAlwaysMuxMKV = value;
	}

	const bool &MeGUISettings::getAutoStartQueue() const
	{
		return autoStartQueue;
	}

	void MeGUISettings::setAutoStartQueue(const bool &value)
	{
		autoStartQueue = value;
	}

	const bool &MeGUISettings::getAutoOpenScript() const
	{
		return autoOpenScript;
	}

	void MeGUISettings::setAutoOpenScript(const bool &value)
	{
		autoOpenScript = value;
	}

	const bool &MeGUISettings::getOpenProgressWindow() const
	{
		return openProgressWindow;
	}

	void MeGUISettings::setOpenProgressWindow(const bool &value)
	{
		openProgressWindow = value;
	}

	const decimal &MeGUISettings::getForceFilmThreshold() const
	{
		return forceFilmThreshold;
	}

	void MeGUISettings::setForceFilmThreshold(const decimal &value)
	{
		forceFilmThreshold = value;
	}

	const std::string &MeGUISettings::getDefaultLanguage1() const
	{
		return defaultLanguage1;
	}

	void MeGUISettings::setDefaultLanguage1(const std::string &value)
	{
		defaultLanguage1 = value;
	}

	const std::string &MeGUISettings::getDefaultLanguage2() const
	{
		return defaultLanguage2;
	}

	void MeGUISettings::setDefaultLanguage2(const std::string &value)
	{
		defaultLanguage2 = value;
	}

	const ProcessPriority &MeGUISettings::getDefaultPriority() const
	{
		return defaultPriority;
	}

	void MeGUISettings::setDefaultPriority(const ProcessPriority &value)
	{
		defaultPriority = value;
	}

	const ProcessPriority &MeGUISettings::getProcessingPriority() const
	{
		if (!processingPrioritySet)
		{
			processingPriority = defaultPriority;
			processingPrioritySet = true;
		}
		return processingPriority;
	}

	void MeGUISettings::setProcessingPriority(const ProcessPriority &value)
	{
		processingPriority = value;
	}

	const bool &MeGUISettings::getOpenAVSInThread() const
	{
		return bOpenAVSInThread;
	}

	void MeGUISettings::setOpenAVSInThread(const bool &value)
	{
		bOpenAVSInThread = value;
	}

	const bool &MeGUISettings::getOpenAVSInThreadDuringSession() const
	{
		if (!bOpenAVSInThreadDuringSessionSet)
		{
			bOpenAVSInThreadDuringSession = bOpenAVSInThread;
			bOpenAVSInThreadDuringSessionSet = true;
		}
		return bOpenAVSInThreadDuringSession;
	}

	void MeGUISettings::setOpenAVSInThreadDuringSession(const bool &value)
	{
		bOpenAVSInThreadDuringSession = value;
	}

	const bool &MeGUISettings::getEnableMP3inMP4() const
	{
		return enableMP3inMP4;
	}

	void MeGUISettings::setEnableMP3inMP4(const bool &value)
	{
		enableMP3inMP4 = value;
	}

	const bool &MeGUISettings::getOverwriteStats() const
	{
		return overwriteStats;
	}

	void MeGUISettings::setOverwriteStats(const bool &value)
	{
		overwriteStats = value;
	}

	const bool &MeGUISettings::getKeep2of3passOutput() const
	{
		return keep2of3passOutput;
	}

	void MeGUISettings::setKeep2of3passOutput(const bool &value)
	{
		keep2of3passOutput = value;
	}

	const int &MeGUISettings::getNbPasses() const
	{
		return nbPasses;
	}

	void MeGUISettings::setNbPasses(const int &value)
	{
		nbPasses = value;
	}

	const bool &MeGUISettings::getDeleteCompletedJobs() const
	{
		return deleteCompletedJobs;
	}

	void MeGUISettings::setDeleteCompletedJobs(const bool &value)
	{
		deleteCompletedJobs = value;
	}

	const bool &MeGUISettings::getDeleteIntermediateFiles() const
	{
		return deleteIntermediateFiles;
	}

	void MeGUISettings::setDeleteIntermediateFiles(const bool &value)
	{
		deleteIntermediateFiles = value;
	}

	const bool &MeGUISettings::getDeleteAbortedOutput() const
	{
		return deleteAbortedOutput;
	}

	void MeGUISettings::setDeleteAbortedOutput(const bool &value)
	{
		deleteAbortedOutput = value;
	}

	const std::string &MeGUISettings::getVideoExtension() const
	{
		return videoExtension;
	}

	void MeGUISettings::setVideoExtension(const std::string &value)
	{
		videoExtension = value;
	}

	const std::string &MeGUISettings::getAudioExtension() const
	{
		return audioExtension;
	}

	void MeGUISettings::setAudioExtension(const std::string &value)
	{
		audioExtension = value;
	}

	const bool &MeGUISettings::getAutoUpdate() const
	{
		return autoUpdate;
	}

	void MeGUISettings::setAutoUpdate(const bool &value)
	{
		autoUpdate = value;
	}

	const MeGUI::DialogSettings &MeGUISettings::getDialogSettings() const
	{
		return dialogSettings;
	}

	void MeGUISettings::setDialogSettings(const MeGUI::DialogSettings &value)
	{
		dialogSettings = value;
	}

	const MeGUI::SourceDetectorSettings &MeGUISettings::getSourceDetectorSettings() const
	{
		return sdSettings;
	}

	void MeGUISettings::setSourceDetectorSettings(const MeGUI::SourceDetectorSettings &value)
	{
		sdSettings = value;
	}

	const AutoEncodeDefaultsSettings &MeGUISettings::getAedSettings() const
	{
		return aedSettings;
	}

	void MeGUISettings::setAedSettings(const AutoEncodeDefaultsSettings &value)
	{
		aedSettings = value;
	}

	const ProxyMode &MeGUISettings::getHttpProxyMode() const
	{
		return httpProxyMode;
	}

	void MeGUISettings::setHttpProxyMode(const ProxyMode &value)
	{
		httpProxyMode = value;
	}

	const std::string &MeGUISettings::getHttpProxyAddress() const
	{
		return httpproxyaddress;
	}

	void MeGUISettings::setHttpProxyAddress(const std::string &value)
	{
		httpproxyaddress = value;
	}

	const std::string &MeGUISettings::getHttpProxyPort() const
	{
		return httpproxyport;
	}

	void MeGUISettings::setHttpProxyPort(const std::string &value)
	{
		httpproxyport = value;
	}

	const std::string &MeGUISettings::getHttpProxyUid() const
	{
		return httpproxyuid;
	}

	void MeGUISettings::setHttpProxyUid(const std::string &value)
	{
		httpproxyuid = value;
	}

	const std::string &MeGUISettings::getHttpProxyPwd() const
	{
		return httpproxypwd;
	}

	void MeGUISettings::setHttpProxyPwd(const std::string &value)
	{
		httpproxypwd = value;
	}

	const std::string &MeGUISettings::getUseHttpProxy() const
	{
		return "migrated";
	}

	void MeGUISettings::setUseHttpProxy(const std::string &value)
	{
		if (value.Equals("migrated"))
			return;

		if (value.Equals("true"))
		{
			httpProxyMode = CustomProxy;
			System::Windows::Forms::MessageBox::Show("Please verify that your proxy settings are correct as they have been updated.", "Proxy settings changed");
		}
		else
			httpProxyMode = None;
	}

	const std::string &MeGUISettings::getAppendToForcedStreams() const
	{
		return appendToForcedStreams;
	}

	void MeGUISettings::setAppendToForcedStreams(const std::string &value)
	{
		appendToForcedStreams = value;
	}

	const std::string &MeGUISettings::getMainAudioFormat() const
	{
		return strMainAudioFormat;
	}

	void MeGUISettings::setMainAudioFormat(const std::string &value)
	{
		strMainAudioFormat = value;
	}

	const std::string &MeGUISettings::getMainFileFormat() const
	{
		return strMainFileFormat;
	}

	void MeGUISettings::setMainFileFormat(const std::string &value)
	{
		strMainFileFormat = value;
	}

	const std::string &MeGUISettings::getLastUsedOneClickFolder() const
	{
		return lastUsedOneClickFolder;
	}

	void MeGUISettings::setLastUsedOneClickFolder(const std::string &value)
	{
		lastUsedOneClickFolder = value;
	}

	const int &MeGUISettings::getMinComplexity() const
	{
		return minComplexity;
	}

	void MeGUISettings::setMinComplexity(const int &value)
	{
		minComplexity = value;
	}

	const int &MeGUISettings::getMaxComplexity() const
	{
		return maxComplexity;
	}

	void MeGUISettings::setMaxComplexity(const int &value)
	{
		maxComplexity = value;
	}

	const int &MeGUISettings::getFFMSThreads() const
	{
		return ffmsThreads;
	}

	void MeGUISettings::setFFMSThreads(const int &value)
	{
		ffmsThreads = value;
	}

	const bool &MeGUISettings::getUseITUValues() const
	{
		return bUseITU;
	}

	void MeGUISettings::setUseITUValues(const bool &value)
	{
		bUseITU = value;
	}

	const bool &MeGUISettings::getUseDGIndexNV() const
	{
		return bUseDGIndexNV;
	}

	void MeGUISettings::setUseDGIndexNV(const bool &value)
	{
		bUseDGIndexNV = value;
	}

	const std::string &MeGUISettings::getNeroAacEncPath() const
	{
		return neroAacEncPath;
	}

	void MeGUISettings::setNeroAacEncPath(const std::string &value)
	{
		if (!System::IO::File::Exists(value))
			neroAacEncPath = strMeGUIPath + "\\tools\\eac3to\\neroAacEnc.exe";
		else
			neroAacEncPath = value;
	}

	const bool &MeGUISettings::getUseNeroAacEnc() const
	{
		return bUseNeroAacEnc;
	}

	void MeGUISettings::setUseNeroAacEnc(const bool &value)
	{
		bUseNeroAacEnc = value;
	}

	const bool &MeGUISettings::getUseQAAC() const
	{
		return bUseQAAC;
	}

	void MeGUISettings::setUseQAAC(const bool &value)
	{
		bUseQAAC = value;
	}

	const bool &MeGUISettings::getAutoUpdateSession() const
	{
		return bAutoUpdateSession;
	}

	void MeGUISettings::setAutoUpdateSession(const bool &value)
	{
		bAutoUpdateSession = value;
	}

	const bool &MeGUISettings::getPortableAviSynth() const
	{
		return bPortableAviSynth;
	}

	void MeGUISettings::setPortableAviSynth(const bool &value)
	{
		bPortableAviSynth = value;
	}

	bool MeGUISettings::IsNeroAACEncAvailable()
	{
		return bUseNeroAacEnc && System::IO::File::Exists(neroAacEncPath);
	}

	bool MeGUISettings::IsQAACAvailable()
	{
		return bUseQAAC && System::IO::File::Exists(qaacPath);
	}

	bool MeGUISettings::IsDGIIndexerAvailable()
	{
		if (!bUseDGIndexNV)
			return false;

		// check if the license file is available
		if (!System::IO::File::Exists(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgnvIndexPath()), "license.txt")))
			return false;

		// DGI is not available in a RDP connection
		if (System::Windows::Forms::SystemInformation::TerminalServerSession == true)
			return false;

		// check if the indexer is available
		if (!System::IO::File::Exists(MainForm::Instance->getSettings()->getDgnvIndexPath()))
			return false;

		return true;
	}

	bool MeGUISettings::Is10Bitx264Available()
	{
		return bUse10BitsX264 && System::IO::File::Exists(x26410BitsPath);
	}
}
