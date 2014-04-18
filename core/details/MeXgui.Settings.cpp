#include "MeXguiSettings.h"




//using namespace System::Collections::Generic;



//using namespace System::Xml::Serialization;
using namespace MeXgui::core::util;
using namespace MeXgui::core::gui;

namespace MeXgui
{

	MeXguiSettings::MeXguiSettings()
	{
		strMeXguiPath = System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath);
		autoscroll = true;
		autoUpdateServerLists = new QString[][] {new QString[] {"Stable", "http://MeXgui.org/auto/stable/", "http://MeXgui.xvidvideo.ru/auto/stable/"}, new QString[] {"Development", "http://MeXgui.org/auto/", "http://MeXgui.xvidvideo.ru/auto/"}, new QString[] {"Custom"}};
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
		pgcDemuxPath = getDownloadPath("tools\\pgcdemux\\pgcdeexe");
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
		neroAacEncPath = strMeXguiPath + "\\tools\\eac3to\\neroAacEnc.exe";
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
		MeXguiupdatecache = System::IO::Path::Combine(strMeXguiPath, "update_cache");
		avisynthpluginspath = System::IO::Path::Combine(strMeXguiPath, "tools\\avisynth_plugin");
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

	QString MeXguiSettings::getDownloadPath(const QString &strPath)
	{
		strPath = System::IO::Path::Combine(strMeXguiPath, strPath);
		return strPath;
	}

	const QString &MeXguiSettings::getYadifPath() const
	{
		return yadifPath;
	}

	const Point &MeXguiSettings::getMainFormLocation() const
	{
		return mainFormLocation;
	}

	void MeXguiSettings::setMainFormLocation(const Point &value)
	{
		mainFormLocation = value;
	}

	const Size &MeXguiSettings::getMainFormSize() const
	{
		return mainFormSize;
	}

	void MeXguiSettings::setMainFormSize(const Size &value)
	{
		mainFormSize = value;
	}

	const Point &MeXguiSettings::getUpdateFormLocation() const
	{
		return updateFormLocation;
	}

	void MeXguiSettings::setUpdateFormLocation(const Point &value)
	{
		updateFormLocation = value;
	}

	const Size &MeXguiSettings::getUpdateFormSize() const
	{
		return updateFormSize;
	}

	void MeXguiSettings::setUpdateFormSize(const Size &value)
	{
		updateFormSize = value;
	}

	const int &MeXguiSettings::getUpdateFormSplitter() const
	{
		return updateFormSplitter;
	}

	void MeXguiSettings::setUpdateFormSplitter(const int &value)
	{
		updateFormSplitter = value;
	}

	const int &MeXguiSettings::getUpdateFormUpdateColumnWidth() const
	{
		return updateFormUpdateColumnWidth;
	}

	void MeXguiSettings::setUpdateFormUpdateColumnWidth(const int &value)
	{
		updateFormUpdateColumnWidth = value;
	}

	const int &MeXguiSettings::getUpdateFormNameColumnWidth() const
	{
		return updateFormNameColumnWidth;
	}

	void MeXguiSettings::setUpdateFormNameColumnWidth(const int &value)
	{
		updateFormNameColumnWidth = value;
	}

	const int &MeXguiSettings::getUpdateFormLocalVersionColumnWidth() const
	{
		return updateFormLocalVersionColumnWidth;
	}

	void MeXguiSettings::setUpdateFormLocalVersionColumnWidth(const int &value)
	{
		updateFormLocalVersionColumnWidth = value;
	}

	const int &MeXguiSettings::getUpdateFormServerVersionColumnWidth() const
	{
		return updateFormServerVersionColumnWidth;
	}

	void MeXguiSettings::setUpdateFormServerVersionColumnWidth(const int &value)
	{
		updateFormServerVersionColumnWidth = value;
	}

	const int &MeXguiSettings::getUpdateFormLocalDateColumnWidth() const
	{
		return updateFormLocalDateColumnWidth;
	}

	void MeXguiSettings::setUpdateFormLocalDateColumnWidth(const int &value)
	{
		updateFormLocalDateColumnWidth = value;
	}

	const int &MeXguiSettings::getUpdateFormServerDateColumnWidth() const
	{
		return updateFormServerDateColumnWidth;
	}

	void MeXguiSettings::setUpdateFormServerDateColumnWidth(const int &value)
	{
		updateFormServerDateColumnWidth = value;
	}

	const int &MeXguiSettings::getUpdateFormPlatformColumnWidth() const
	{
		return updateFormPlatformColumnWidth;
	}

	void MeXguiSettings::setUpdateFormPlatformColumnWidth(const int &value)
	{
		updateFormPlatformColumnWidth = value;
	}

	const int &MeXguiSettings::getUpdateFormStatusColumnWidth() const
	{
		return updateFormStatusColumnWidth;
	}

	void MeXguiSettings::setUpdateFormStatusColumnWidth(const int &value)
	{
		updateFormStatusColumnWidth = value;
	}

	const Size &MeXguiSettings::getJobWorkerSize() const
	{
		return jobWorkerSize;
	}

	void MeXguiSettings::setJobWorkerSize(const Size &value)
	{
		jobWorkerSize = value;
	}

	const int &MeXguiSettings::getJobColumnWidth() const
	{
		return jobColumnWidth;
	}

	void MeXguiSettings::setJobColumnWidth(const int &value)
	{
		jobColumnWidth = value;
	}

	const int &MeXguiSettings::getInputColumnWidth() const
	{
		return inputColumnWidth;
	}

	void MeXguiSettings::setInputColumnWidth(const int &value)
	{
		inputColumnWidth = value;
	}

	const int &MeXguiSettings::getOutputColumnWidth() const
	{
		return outputColumnWidth;
	}

	void MeXguiSettings::setOutputColumnWidth(const int &value)
	{
		outputColumnWidth = value;
	}

	const int &MeXguiSettings::getCodecColumnWidth() const
	{
		return codecColumnWidth;
	}

	void MeXguiSettings::setCodecColumnWidth(const int &value)
	{
		codecColumnWidth = value;
	}

	const int &MeXguiSettings::getModeColumnWidth() const
	{
		return modeColumnWidth;
	}

	void MeXguiSettings::setModeColumnWidth(const int &value)
	{
		modeColumnWidth = value;
	}

	const int &MeXguiSettings::getStatusColumnWidth() const
	{
		return statusColumnWidth;
	}

	void MeXguiSettings::setStatusColumnWidth(const int &value)
	{
		statusColumnWidth = value;
	}

	const int &MeXguiSettings::getOwnerColumnWidth() const
	{
		return ownerColumnWidth;
	}

	void MeXguiSettings::setOwnerColumnWidth(const int &value)
	{
		ownerColumnWidth = value;
	}

	const int &MeXguiSettings::getStartColumnWidth() const
	{
		return startColumnWidth;
	}

	void MeXguiSettings::setStartColumnWidth(const int &value)
	{
		startColumnWidth = value;
	}

	const int &MeXguiSettings::getEndColumnWidth() const
	{
		return endColumnWidth;
	}

	void MeXguiSettings::setEndColumnWidth(const int &value)
	{
		endColumnWidth = value;
	}

	const int &MeXguiSettings::getFPSColumnWidth() const
	{
		return fpsColumnWidth;
	}

	void MeXguiSettings::setFPSColumnWidth(const int &value)
	{
		fpsColumnWidth = value;
	}

	const FileSize &MeXguiSettings::getCustomFileSizes() const
	{
		return customFileSizes;
	}

	void MeXguiSettings::setCustomFileSizes(const FileSize &value[])
	{
		customFileSizes = value;
	}

	const FPS &MeXguiSettings::getCustomFPSs() const
	{
		return customFPSs;
	}

	void MeXguiSettings::setCustomFPSs(const FPS &value[])
	{
		customFPSs = value;
	}

	const Dar &MeXguiSettings::getCustomDARs() const
	{
		return customDARs;
	}

	void MeXguiSettings::setCustomDARs(const Dar &value[])
	{
		customDARs = value;
	}

	const quint64 &MeXguiSettings::getAudioSamplesPerUpdate() const
	{
		return audioSamplesPerUpdate;
	}

	void MeXguiSettings::setAudioSamplesPerUpdate(const quint64 &value)
	{
		audioSamplesPerUpdate = value;
	}

	const QString &MeXguiSettings::getLastSourcePath() const
	{
		return strLastSourcePath;
	}

	void MeXguiSettings::setLastSourcePath(const QString &value)
	{
		strLastSourcePath = value;
	}

	const QString &MeXguiSettings::getLastDestinationPath() const
	{
		return strLastDestinationPath;
	}

	void MeXguiSettings::setLastDestinationPath(const QString &value)
	{
		strLastDestinationPath = value;
	}

	const bool &MeXguiSettings::getAutoScrollLog() const
	{
		return autoscroll;
	}

	void MeXguiSettings::setAutoScrollLog(const bool &value)
	{
		autoscroll = value;
	}

	const MeXgui::MeXguiSettings::OCGUIMode &MeXguiSettings::getOneClickGUIMode() const
	{
		return ocGUIMode;
	}

	void MeXguiSettings::setOneClickGUIMode(const OCGUIMode &value)
	{
		ocGUIMode = value;
	}

	const bool &MeXguiSettings::getEnsureCorrectPlaybackSpeed() const
	{
		return bEnsureCorrectPlaybackSpeed;
	}

	void MeXguiSettings::setEnsureCorrectPlaybackSpeed(const bool &value)
	{
		bEnsureCorrectPlaybackSpeed = value;
	}

	const bool &MeXguiSettings::getSafeProfileAlteration() const
	{
		return safeProfileAlteration;
	}

	void MeXguiSettings::setSafeProfileAlteration(const bool &value)
	{
		safeProfileAlteration = value;
	}

	const decimal &MeXguiSettings::getAcceptableFPSError() const
	{
		return acceptableFPSError;
	}

	void MeXguiSettings::setAcceptableFPSError(const decimal &value)
	{
		acceptableFPSError = value;
	}

	const int &MeXguiSettings::getAutoUpdateServerSubList() const
	{
		return autoUpdateServerSubList;
	}

	void MeXguiSettings::setAutoUpdateServerSubList(const int &value)
	{
		autoUpdateServerSubList = value;
	}

	const DateTime &MeXguiSettings::getLastUpdateCheck() const
	{
		return lastUpdateCheck;
	}

	void MeXguiSettings::setLastUpdateCheck(const DateTime &value)
	{
		lastUpdateCheck = value;
	}

	const QString &MeXguiSettings::getLastUpdateServer() const
	{
		return lastUpdateServer;
	}

	void MeXguiSettings::setLastUpdateServer(const QString &value)
	{
		lastUpdateServer = value;
	}

	const QString &*MeXguiSettings::getAutoUpdateServerLists() const
	{
		if (sizeof(autoUpdateServerLists) / sizeof(autoUpdateServerLists[0]) > 2)
		{
			autoUpdateServerLists[0] = new QString[] {"Stable", "http://MeXgui.org/auto/stable/", "http://MeXgui.xvidvideo.ru/auto/stable/"};
			autoUpdateServerLists[1] = new QString[] {"Development", "http://MeXgui.org/auto/", "http://MeXgui.xvidvideo.ru/auto/"};
		}
		else
		{
			autoUpdateServerLists = new QString[][] {new QString[] {"Stable", "http://MeXgui.org/auto/stable/", "http://MeXgui.xvidvideo.ru/auto/stable/"}, new QString[] {"Development", "http://MeXgui.org/auto/", "http://MeXgui.xvidvideo.ru/auto/"}, new QString[] {"Custom"}};
		}
	#if defined(x64)
		autoUpdateServerLists = new QString[][] {new QString[] {"Stable", "http://MeXgui.org/auto/", "http://MeXgui.xvidvideo.ru/auto/"}, new QString[] {"Development", "http://MeXgui.org/auto/", "http://MeXgui.xvidvideo.ru/auto/"}, new QString[] {"Custom", "http://MeXgui.org/auto/", "http://MeXgui.xvidvideo.ru/auto/"}};
	#endif
	#if defined(DEBUG)
		autoUpdateServerLists = new QString[][] {new QString[] {"Stable", "http://MeXgui.org/auto/"}, new QString[] {"Development", "http://MeXgui.org/auto/"}, new QString[] {"Custom", "http://MeXgui.org/auto/"}};
	#endif
		return autoUpdateServerLists;
	}

	void MeXguiSettings::setAutoUpdateServerLists(const QString &value[][])
	{
		autoUpdateServerLists = value;
	}

	const MeXgui::AfterEncoding &MeXguiSettings::getAfterEncoding() const
	{
		return afterEncoding;
	}

	void MeXguiSettings::setAfterEncoding(const MeXgui::AfterEncoding &value)
	{
		afterEncoding = value;
	}

	const QString &MeXguiSettings::getAfterEncodingCommand() const
	{
		return afterEncodingCommand;
	}

	void MeXguiSettings::setAfterEncodingCommand(const QString &value)
	{
		afterEncodingCommand = value;
	}

	const bool &MeXguiSettings::getUseAdvancedTooltips() const
	{
		return useadvancedtooltips;
	}

	void MeXguiSettings::setUseAdvancedTooltips(const bool &value)
	{
		useadvancedtooltips = value;
	}

	const bool &MeXguiSettings::getUse64bitX264() const
	{
		return b64bitX264;
	}

	void MeXguiSettings::setUse64bitX264(const bool &value)
	{
		b64bitX264 = value;
	}

	const bool &MeXguiSettings::getUse10bitsX264() const
	{
		return bUse10BitsX264;
	}

	void MeXguiSettings::setUse10bitsX264(const bool &value)
	{
		bUse10BitsX264 = value;
	}

	const bool &MeXguiSettings::getAlwaysOnTop() const
	{
		return alwaysOnTop;
	}

	void MeXguiSettings::setAlwaysOnTop(const bool &value)
	{
		alwaysOnTop = value;
	}

	const bool &MeXguiSettings::getAddTimePosition() const
	{
		return addTimePosition;
	}

	void MeXguiSettings::setAddTimePosition(const bool &value)
	{
		addTimePosition = value;
	}

	const bool &MeXguiSettings::getUseExternalMuxerX264() const
	{
		return bExternalMuxerX264;
	}

	void MeXguiSettings::setUseExternalMuxerX264(const bool &value)
	{
		bExternalMuxerX264 = value;
	}

	const QString &MeXguiSettings::getDefaultOutputDir() const
	{
		return defaultOutputDir;
	}

	void MeXguiSettings::setDefaultOutputDir(const QString &value)
	{
		defaultOutputDir = value;
	}

	const QString &MeXguiSettings::getTempDirMP4() const
	{
		if (tempDirMP4.empty() || System::IO::Path::GetPathRoot(tempDirMP4)->Equals(tempDirMP4, StringComparison::CurrentCultureIgnoreCase))
			return "";
		return tempDirMP4;
	}

	void MeXguiSettings::setTempDirMP4(const QString &value)
	{
		tempDirMP4 = value;
	}

	const QString &MeXguiSettings::getBeSplitPath() const
	{
		return besplitPath;
	}

	const QString &MeXguiSettings::getFFMpegPath() const
	{
		return ffmpegPath;
	}

	const QString &MeXguiSettings::getVobSubPath() const
	{
		return vobSubPath;
	}

	const QString &MeXguiSettings::getBassPath() const
	{
		return bassPath;
	}

	const QString &MeXguiSettings::getOggEnc2Path() const
	{
		return oggEnc2Path;
	}

	const QString &MeXguiSettings::getLamePath() const
	{
		return lamePath;
	}

	const QString &MeXguiSettings::getMkvmergePath() const
	{
		return mkvmergePath;
	}

	const QString &MeXguiSettings::getMkvExtractPath() const
	{
		return mkvExtractPath;
	}

	const QString &MeXguiSettings::getMp4boxPath() const
	{
		return mp4boxPath;
	}

	const QString &MeXguiSettings::getPgcDemuxPath() const
	{
		return pgcDemuxPath;
	}

	const QString &MeXguiSettings::getX264Path() const
	{
		return x264Path;
	}

	const QString &MeXguiSettings::getX26410BitsPath() const
	{
		return x26410BitsPath;
	}

	const QString &MeXguiSettings::getDgIndexPath() const
	{
		return dgIndexPath;
	}

	const QString &MeXguiSettings::getFFMSIndexPath() const
	{
		return ffmsIndexPath;
	}

	const QString &MeXguiSettings::getAviSynthPath() const
	{
		return aviSynthPath;
	}

	const QString &MeXguiSettings::getXviDEncrawPath() const
	{
		return xvidEncrawPath;
	}

	const QString &MeXguiSettings::getAviMuxGUIPath() const
	{
		return aviMuxGUIPath;
	}

	const QString &MeXguiSettings::getAftenPath() const
	{
		return aftenPath;
	}

	const QString &MeXguiSettings::getFlacPath() const
	{
		return flacPath;
	}

	const QString &MeXguiSettings::getDgavcIndexPath() const
	{
		return dgavcIndexPath;
	}

	const QString &MeXguiSettings::getDgnvIndexPath() const
	{
		return dgnvIndexPath;
	}

	const QString &MeXguiSettings::getEAC3toPath() const
	{
		return eac3toPath;
	}

	const QString &MeXguiSettings::getTSMuxerPath() const
	{
		return tsmuxerPath;
	}

	const QString &MeXguiSettings::getQaacPath() const
	{
		return qaacPath;
	}

	const QString &MeXguiSettings::getOpusPath() const
	{
		return opusPath;
	}

	const bool &MeXguiSettings::getAlwaysBackUpFiles() const
	{
		return alwaysbackupfiles;
	}

	void MeXguiSettings::setAlwaysBackUpFiles(const bool &value)
	{
		alwaysbackupfiles = value;
	}

	const bool &MeXguiSettings::getForceRawAVCExtension() const
	{
		return forcerawavcextension;
	}

	void MeXguiSettings::setForceRawAVCExtension(const bool &value)
	{
		forcerawavcextension = value;
	}

	const QString &MeXguiSettings::getHaaliMSPath() const
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

			QString value = static_cast<QString>(key->GetValue("Install_Dir"));
			if (value == "")
				return "";
			return value;
		}
		catch (...)
		{
			return "";
		}
	}

	const QString &MeXguiSettings::getAvisynthPluginsPath() const
	{
		return avisynthpluginspath;
	}

	const QString &MeXguiSettings::getMeXguiUpdateCache() const
	{
		return MeXguiupdatecache;
	}

	const bool &MeXguiSettings::getRecalculateMainMovieBitrate() const
	{
		return recalculateMainMovieBitrate;
	}

	void MeXguiSettings::setRecalculateMainMovieBitrate(const bool &value)
	{
		recalculateMainMovieBitrate = value;
	}

	const bool &MeXguiSettings::getAutoForceFilm() const
	{
		return autoForceFilm;
	}

	void MeXguiSettings::setAutoForceFilm(const bool &value)
	{
		autoForceFilm = value;
	}

	const bool &MeXguiSettings::getAutoLoadDG() const
	{
		return bAutoLoadDG;
	}

	void MeXguiSettings::setAutoLoadDG(const bool &value)
	{
		bAutoLoadDG = value;
	}

	const bool &MeXguiSettings::getAutoSelectHDStreams() const
	{
		return autoSelectHDStreams;
	}

	void MeXguiSettings::setAutoSelectHDStreams(const bool &value)
	{
		autoSelectHDStreams = value;
	}

	const bool &MeXguiSettings::getAutoStartQueueStartup() const
	{
		return bAutoStartQueueStartup;
	}

	void MeXguiSettings::setAutoStartQueueStartup(const bool &value)
	{
		bAutoStartQueueStartup = value;
	}

	const bool &MeXguiSettings::getAlwaysMuxMKV() const
	{
		return bAlwaysMuxMKV;
	}

	void MeXguiSettings::setAlwaysMuxMKV(const bool &value)
	{
		bAlwaysMuxMKV = value;
	}

	const bool &MeXguiSettings::getAutoStartQueue() const
	{
		return autoStartQueue;
	}

	void MeXguiSettings::setAutoStartQueue(const bool &value)
	{
		autoStartQueue = value;
	}

	const bool &MeXguiSettings::getAutoOpenScript() const
	{
		return autoOpenScript;
	}

	void MeXguiSettings::setAutoOpenScript(const bool &value)
	{
		autoOpenScript = value;
	}

	const bool &MeXguiSettings::getOpenProgressWindow() const
	{
		return openProgressWindow;
	}

	void MeXguiSettings::setOpenProgressWindow(const bool &value)
	{
		openProgressWindow = value;
	}

	const decimal &MeXguiSettings::getForceFilmThreshold() const
	{
		return forceFilmThreshold;
	}

	void MeXguiSettings::setForceFilmThreshold(const decimal &value)
	{
		forceFilmThreshold = value;
	}

	const QString &MeXguiSettings::getDefaultLanguage1() const
	{
		return defaultLanguage1;
	}

	void MeXguiSettings::setDefaultLanguage1(const QString &value)
	{
		defaultLanguage1 = value;
	}

	const QString &MeXguiSettings::getDefaultLanguage2() const
	{
		return defaultLanguage2;
	}

	void MeXguiSettings::setDefaultLanguage2(const QString &value)
	{
		defaultLanguage2 = value;
	}

	const ProcessPriority &MeXguiSettings::getDefaultPriority() const
	{
		return defaultPriority;
	}

	void MeXguiSettings::setDefaultPriority(const ProcessPriority &value)
	{
		defaultPriority = value;
	}

	const ProcessPriority &MeXguiSettings::getProcessingPriority() const
	{
		if (!processingPrioritySet)
		{
			processingPriority = defaultPriority;
			processingPrioritySet = true;
		}
		return processingPriority;
	}

	void MeXguiSettings::setProcessingPriority(const ProcessPriority &value)
	{
		processingPriority = value;
	}

	const bool &MeXguiSettings::getOpenAVSInThread() const
	{
		return bOpenAVSInThread;
	}

	void MeXguiSettings::setOpenAVSInThread(const bool &value)
	{
		bOpenAVSInThread = value;
	}

	const bool &MeXguiSettings::getOpenAVSInThreadDuringSession() const
	{
		if (!bOpenAVSInThreadDuringSessionSet)
		{
			bOpenAVSInThreadDuringSession = bOpenAVSInThread;
			bOpenAVSInThreadDuringSessionSet = true;
		}
		return bOpenAVSInThreadDuringSession;
	}

	void MeXguiSettings::setOpenAVSInThreadDuringSession(const bool &value)
	{
		bOpenAVSInThreadDuringSession = value;
	}

	const bool &MeXguiSettings::getEnableMP3inMP4() const
	{
		return enableMP3inMP4;
	}

	void MeXguiSettings::setEnableMP3inMP4(const bool &value)
	{
		enableMP3inMP4 = value;
	}

	const bool &MeXguiSettings::getOverwriteStats() const
	{
		return overwriteStats;
	}

	void MeXguiSettings::setOverwriteStats(const bool &value)
	{
		overwriteStats = value;
	}

	const bool &MeXguiSettings::getKeep2of3passOutput() const
	{
		return keep2of3passOutput;
	}

	void MeXguiSettings::setKeep2of3passOutput(const bool &value)
	{
		keep2of3passOutput = value;
	}

	const int &MeXguiSettings::getNbPasses() const
	{
		return nbPasses;
	}

	void MeXguiSettings::setNbPasses(const int &value)
	{
		nbPasses = value;
	}

	const bool &MeXguiSettings::getDeleteCompletedJobs() const
	{
		return deleteCompletedJobs;
	}

	void MeXguiSettings::setDeleteCompletedJobs(const bool &value)
	{
		deleteCompletedJobs = value;
	}

	const bool &MeXguiSettings::getDeleteIntermediateFiles() const
	{
		return deleteIntermediateFiles;
	}

	void MeXguiSettings::setDeleteIntermediateFiles(const bool &value)
	{
		deleteIntermediateFiles = value;
	}

	const bool &MeXguiSettings::getDeleteAbortedOutput() const
	{
		return deleteAbortedOutput;
	}

	void MeXguiSettings::setDeleteAbortedOutput(const bool &value)
	{
		deleteAbortedOutput = value;
	}

	const QString &MeXguiSettings::getVideoExtension() const
	{
		return videoExtension;
	}

	void MeXguiSettings::setVideoExtension(const QString &value)
	{
		videoExtension = value;
	}

	const QString &MeXguiSettings::getAudioExtension() const
	{
		return audioExtension;
	}

	void MeXguiSettings::setAudioExtension(const QString &value)
	{
		audioExtension = value;
	}

	const bool &MeXguiSettings::getAutoUpdate() const
	{
		return autoUpdate;
	}

	void MeXguiSettings::setAutoUpdate(const bool &value)
	{
		autoUpdate = value;
	}

	const MeXgui::DialogSettings &MeXguiSettings::getDialogSettings() const
	{
		return dialogSettings;
	}

	void MeXguiSettings::setDialogSettings(const MeXgui::DialogSettings &value)
	{
		dialogSettings = value;
	}

	const MeXgui::SourceDetectorSettings &MeXguiSettings::getSourceDetectorSettings() const
	{
		return sdSettings;
	}

	void MeXguiSettings::setSourceDetectorSettings(const MeXgui::SourceDetectorSettings &value)
	{
		sdSettings = value;
	}

	const AutoEncodeDefaultsSettings &MeXguiSettings::getAedSettings() const
	{
		return aedSettings;
	}

	void MeXguiSettings::setAedSettings(const AutoEncodeDefaultsSettings &value)
	{
		aedSettings = value;
	}

	const ProxyMode &MeXguiSettings::getHttpProxyMode() const
	{
		return httpProxyMode;
	}

	void MeXguiSettings::setHttpProxyMode(const ProxyMode &value)
	{
		httpProxyMode = value;
	}

	const QString &MeXguiSettings::getHttpProxyAddress() const
	{
		return httpproxyaddress;
	}

	void MeXguiSettings::setHttpProxyAddress(const QString &value)
	{
		httpproxyaddress = value;
	}

	const QString &MeXguiSettings::getHttpProxyPort() const
	{
		return httpproxyport;
	}

	void MeXguiSettings::setHttpProxyPort(const QString &value)
	{
		httpproxyport = value;
	}

	const QString &MeXguiSettings::getHttpProxyUid() const
	{
		return httpproxyuid;
	}

	void MeXguiSettings::setHttpProxyUid(const QString &value)
	{
		httpproxyuid = value;
	}

	const QString &MeXguiSettings::getHttpProxyPwd() const
	{
		return httpproxypwd;
	}

	void MeXguiSettings::setHttpProxyPwd(const QString &value)
	{
		httpproxypwd = value;
	}

	const QString &MeXguiSettings::getUseHttpProxy() const
	{
		return "migrated";
	}

	void MeXguiSettings::setUseHttpProxy(const QString &value)
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

	const QString &MeXguiSettings::getAppendToForcedStreams() const
	{
		return appendToForcedStreams;
	}

	void MeXguiSettings::setAppendToForcedStreams(const QString &value)
	{
		appendToForcedStreams = value;
	}

	const QString &MeXguiSettings::getMainAudioFormat() const
	{
		return strMainAudioFormat;
	}

	void MeXguiSettings::setMainAudioFormat(const QString &value)
	{
		strMainAudioFormat = value;
	}

	const QString &MeXguiSettings::getMainFileFormat() const
	{
		return strMainFileFormat;
	}

	void MeXguiSettings::setMainFileFormat(const QString &value)
	{
		strMainFileFormat = value;
	}

	const QString &MeXguiSettings::getLastUsedOneClickFolder() const
	{
		return lastUsedOneClickFolder;
	}

	void MeXguiSettings::setLastUsedOneClickFolder(const QString &value)
	{
		lastUsedOneClickFolder = value;
	}

	const int &MeXguiSettings::getMinComplexity() const
	{
		return minComplexity;
	}

	void MeXguiSettings::setMinComplexity(const int &value)
	{
		minComplexity = value;
	}

	const int &MeXguiSettings::getMaxComplexity() const
	{
		return maxComplexity;
	}

	void MeXguiSettings::setMaxComplexity(const int &value)
	{
		maxComplexity = value;
	}

	const int &MeXguiSettings::getFFMSThreads() const
	{
		return ffmsThreads;
	}

	void MeXguiSettings::setFFMSThreads(const int &value)
	{
		ffmsThreads = value;
	}

	const bool &MeXguiSettings::getUseITUValues() const
	{
		return bUseITU;
	}

	void MeXguiSettings::setUseITUValues(const bool &value)
	{
		bUseITU = value;
	}

	const bool &MeXguiSettings::getUseDGIndexNV() const
	{
		return bUseDGIndexNV;
	}

	void MeXguiSettings::setUseDGIndexNV(const bool &value)
	{
		bUseDGIndexNV = value;
	}

	const QString &MeXguiSettings::getNeroAacEncPath() const
	{
		return neroAacEncPath;
	}

	void MeXguiSettings::setNeroAacEncPath(const QString &value)
	{
		if (!System::IO::File::Exists(value))
			neroAacEncPath = strMeXguiPath + "\\tools\\eac3to\\neroAacEnc.exe";
		else
			neroAacEncPath = value;
	}

	const bool &MeXguiSettings::getUseNeroAacEnc() const
	{
		return bUseNeroAacEnc;
	}

	void MeXguiSettings::setUseNeroAacEnc(const bool &value)
	{
		bUseNeroAacEnc = value;
	}

	const bool &MeXguiSettings::getUseQAAC() const
	{
		return bUseQAAC;
	}

	void MeXguiSettings::setUseQAAC(const bool &value)
	{
		bUseQAAC = value;
	}

	const bool &MeXguiSettings::getAutoUpdateSession() const
	{
		return bAutoUpdateSession;
	}

	void MeXguiSettings::setAutoUpdateSession(const bool &value)
	{
		bAutoUpdateSession = value;
	}

	const bool &MeXguiSettings::getPortableAviSynth() const
	{
		return bPortableAviSynth;
	}

	void MeXguiSettings::setPortableAviSynth(const bool &value)
	{
		bPortableAviSynth = value;
	}

	bool MeXguiSettings::IsNeroAACEncAvailable()
	{
		return bUseNeroAacEnc && System::IO::File::Exists(neroAacEncPath);
	}

	bool MeXguiSettings::IsQAACAvailable()
	{
		return bUseQAAC && System::IO::File::Exists(qaacPath);
	}

	bool MeXguiSettings::IsDGIIndexerAvailable()
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

	bool MeXguiSettings::Is10Bitx264Available()
	{
		return bUse10BitsX264 && System::IO::File::Exists(x26410BitsPath);
	}
}
