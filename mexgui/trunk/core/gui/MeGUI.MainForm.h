#pragma once

#include "ProgressTaskbar.h"
#include "core/util/LogItem.h"
#include "core/util/FileUtil.h"
#include "MeGUI.Properties.Settings.h"
#include "core/details/MeGUI.core.details.JobControl.h"
#include "core/details/video/MeGUI.VideoEncodingComponent.h"
#include "MeGUI.AudioEncodingComponent.h"
#include "core/details/PackageSystem.h"
#include "core/plugins/interfaces/IPackage.h"
#include "core/details/MeGUISettings.h"
#include "core/util/JobUtil.h"
#include "core/util/Shutdown.h"
#include "core/details/ProfileManager.h"
#include "core/plugins/interfaces/IMuxing.h"
#include "core/details/mux/MeGUI.MuxWindow.h"
#include "core/util/Util.h"
#include "core/details/MediaFileFactory.h"
#include "packages/tools/avscreator/MeGUI.AviSynthWindow.h"
#include "packages/tools/avscreator/AviSynthWindow.h"
#include "core/details/DialogManager.h"
#include "packages/tools/oneclick/MeGUI.OneClickWindow.h"
#include "packages/tools/fileindexer/MeGUI.FileIndexerWindow.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "MeGUI.core.gui.ProfileImporter.h"
#include "ProfileImporter.h"
#include "MeGUI.core.gui.ProfileExporter.h"
#include "MeGUI.AdaptiveMuxWindow.h"
#include "MeGUI.UpdateWindow.h"
#include "MainForm.h"
#include "core/details/mux/MuxProvider.h"
#include "core/details/CodecManager.h"
#include "core/details/CommandlineParser.h"
#include "core/util/GenericRegisterer.h"
#include "packages/audio/AudioEncoderInterface.h"
#include "packages/video/ffmpeg/ffmpegEncoder.h"
#include "packages/video/x264/x264Encoder.h"
#include "packages/video/xvid/XviDEncoder.h"
#include "packages/muxer/mkvmerge/MkvMergeMuxer.h"
#include "packages/muxer/mp4box/MP4BoxMuxer.h"
#include "packages/muxer/avimuxgui/AMGMuxer.h"
#include "packages/muxer/tsmuxer/tsMuxeR.h"
#include "packages/demuxer/mkvextract/MkvExtract.h"
#include "packages/demuxer/pgcdemux/PgcDemux.h"
#include "packages/tools/oneclick/OneClickPostProcessing.h"
#include "core/details/CleanupJob.h"
#include "packages/tools/avscreator/AviSynthProcessor.h"
#include "packages/tools/fileindexer/D2VIndexer.h"
#include "packages/tools/fileindexer/DGAIndexer.h"
#include "packages/tools/fileindexer/DGIIndexer.h"
#include "packages/tools/fileindexer/FFMSIndexer.h"
#include "packages/tools/vobsub/VobSubIndexer.h"
#include "packages/tools/besplitter/Joiner.h"
#include "packages/tools/besplitter/Splitter.h"
#include "packages/tools/hdbdextractor/HDStreamExtractorIndexer.h"
#include "packages/tools/cutter/Cutter.h"
#include "packages/tools/autoencode/AutoEncodeWindow.h"
#include "packages/tools/cqmeditor/QuantizerMatrixDialog.h"
#include "packages/tools/calculator/Calculator.h"
#include "packages/tools/chaptercreator/ChapterCreator.h"
#include "UpdateWindow.h"
#include "packages/tools/besplitter/Besplitter.h"
#include "packages/tools/oneclick/OneClickWindow.h"
#include "packages/tools/fileindexer/FileIndexerWindow.h"
#include "packages/tools/avclevelschecker/AVCLevels.h"
#include "packages/tools/vobsub/VobSubIndexWindow.h"
#include "packages/tools/hdbdextractor/HDBDStreamExtractor.h"
#include "packages/reader/avs/AvsReader.h"
#include "packages/reader/d2v/d2vReader.h"
#include "packages/reader/dga/dgaReader.h"
#include "packages/reader/dgi/dgiReader.h"
#include "packages/reader/ffms/ffmsReader.h"
#include "core/util/BitrateCalculatorPreProcessor.h"
#include "MeGUI.core.gui.AudioEncodingWindow.h"
#include "core/util/OSInfo.h"
#include "core/util/VideoUtil.h"
#include "MeGUI.core.gui.LogTree.h"
#include <string>
#include <map>
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
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::details;
using namespace MeGUI::core::gui;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;


namespace MeGUI
{
	class MainForm : public System::Windows::Forms::Form
	{
		// This instance is to be used by the serializers that can't be passed a MainForm as a parameter
	public:
		static MainForm *Instance;

	private:
		std::vector<std::string> filesToDeleteOnClosing;
		std::vector<Form*> allForms;
		std::vector<Form*> formsToReopen;
		ITaskbarList3 *taskbarItem;
		Icon *taskbarIcon;
		std::string strLogFile;
		Semaphore *logLock;
		int avsLock;
		LogItem *_oneClickLog;
		LogItem *_aVSScriptCreatorLog;
		LogItem *_fileIndexerLog;
		LogItem *_updateLog;
		LogItem *_eac3toLog;
		public:
		~MainForm()
		{
			this->Dispose(true);
		}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
		private:
		void Finalize()
		{
			this->Dispose(false);
		}

	public:
		const bool &getIsHiddenMode() const;
		const bool &getIsOverlayIconActive() const;
		const std::string &getLogFile() const;
		const Semaphore &getLogLock() const;
		void setLogLock(const Semaphore &value);
		const int &getAvsLock() const;
		void setAvsLock(const int &value);
		const LogItem &getOneClickLog() const;
		void setOneClickLog(const LogItem &value);
		const LogItem &getAVSScriptCreatorLog() const;
		void setAVSScriptCreatorLog(const LogItem &value);
		const LogItem &getFileIndexerLog() const;
		void setFileIndexerLog(const LogItem &value);
		const LogItem &getUpdateLog() const;
		void setUpdateLog(const LogItem &value);
		const LogItem &getEac3toLog() const;
		void setEac3toLog(const LogItem &value);

		void RegisterForm(Form *f);

		void DeleteOnClosing(const std::string &file);

		/// <summary>
		/// launches the megui wiki in the default browser
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
	private:
		void mnuGuide_Click(object *sender, EventArgs *e);

		/// <summary>
		/// launches the encoder gui forum in the default browser
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void menuItem2_Click(object *sender, EventArgs *e);

		/// <summary>
		/// shows the changelog dialog window
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void mnuChangelog_Click(object *sender, EventArgs *e);

	public:
		MainForm();

		const JobControl &getJobs() const;
		const bool &getProcessStatusChecked() const;
		void setProcessStatusChecked(const bool &value);
		const VideoEncodingComponent &getVideo() const;
		const AudioEncodingComponent &getAudio() const;
		/// <summary>
		/// initializes all the dropdown elements in the GUI to their default values
		/// </summary>

		/// <summary>
		/// handles the GUI closing event
		/// saves all jobs, stops the currently active job and saves all profiles as well
		/// </summary>
		/// <param name="e"></param>
	protected:
		virtual void OnClosing(System::ComponentModel::CancelEventArgs *e);
	private:
		void resetButton_Click(object *sender, System::EventArgs *e);
		void autoEncodeButton_Click(object *sender, System::EventArgs *e);

		void RunTool(const std::string &p);
		/// <summary>
		/// Test whether a filename is suitable for writing to
		/// </summary>
		/// <param name="filename"></param>
		/// <returns>Error message if problem, null if ok</returns>
	public:
		static std::string verifyOutputFile(const std::string &filename);

		/// <summary>
		/// Test whether a filename is suitable for reading from
		/// </summary>
		/// <param name="filename"></param>
		/// <returns>Error message if problem, null if ok</returns>
		static std::string verifyInputFile(const std::string &filename);
		/// <summary>
		/// saves the global GUI settings to settings.xml
		/// </summary>
		void saveSettings();
		/// <summary>
		/// loads the global settings
		/// </summary>
		void loadSettings();


		const MeGUI::JobUtil &getJobUtil() const;

		const std::string &getTitleText() const;
		void setTitleText(const std::string &value);

		/// <summary>
		/// shuts down the PC if the shutdown option is set
		/// also saves all profiles, jobs and the log as MeGUI is killed
		/// via the shutdown so the appropriate methods in the OnClosing are not called
		/// </summary>
		void runAfterEncodingCommands();

		const LogItem &getLog() const;

		/// <summary>
		/// saves the whole content of the log into a logfile
		/// </summary>
		void saveLog();
	private:
		void exitMeGUIToolStripMenuItem_Click(object *sender, EventArgs *e);
		/// <summary>
		/// returns the profile manager to whomever might require it
		/// </summary>
	public:
		const ProfileManager &getProfiles() const;
	private:
		void mnuFileOpen_Click(object *sender, EventArgs *e);
		void mnuViewMinimizeToTray_Click(object *sender, EventArgs *e);

		void mnuFileExit_Click(object *sender, System::EventArgs *e);

		void mnuToolsSettings_Click(object *sender, System::EventArgs *e);
		void mnuTool_Click(object *sender, System::EventArgs *e);

		void mnuOptions_Click(object *sender, System::EventArgs *e);

		void mnuMuxer_Click(object *sender, System::EventArgs *e);

		void mnuView_Popup(object *sender, System::EventArgs *e);

		void mnuProgress_Click(object *sender, EventArgs *e);
		void mnuViewProcessStatus_Click(object *sender, System::EventArgs *e);



	public:
		const MeGUISettings &getSettings() const;

		const MeGUI::MediaFileFactory &getMediaFileFactory() const;
	private:
		void trayIcon_MouseDoubleClick(object *sender, MouseEventArgs *e);
		void openMeGUIToolStripMenuItem_Click(object *sender, EventArgs *e);

		void openOtherVideoFile(const std::string &fileName);
		void openIndexableFile(const std::string &fileName);
	public:
		bool openFile(const std::string &file, bool openVideo);

	private:
		void importProfiles(const std::string &file);
		void MeGUI_DragDrop(object *sender, DragEventArgs *e);

		void MeGUI_DragEnter(object *sender, DragEventArgs *e);
	public:
		void importProfiles(Stream *data);

	private:
		bool bImportProfileSuccessful;
	public:
		const bool &getImportProfileSuccessful() const;
		void setImportProfileSuccessful(const bool &value);

	private:
		void mnuFileImport_Click(object *sender, EventArgs *e);

		void mnuFileExport_Click(object *sender, EventArgs *e);

		void mnuToolsAdaptiveMuxer_Click(object *sender, EventArgs *e);

		void MeGUI_Load(object *sender, EventArgs *e);

		void beginUpdateCheck();

		void mnuUpdate_Click(object *sender, EventArgs *e);

	public:
		void AddFileToReplace(const std::string &iUpgradeableName, const std::string &tempFilename, const std::string &filename, const std::string &newUploadDate);

		void CloseSilent();

	private:
		void Application_ApplicationExit(object *sender, EventArgs *e);

		void saveApplicationSettings();

		void deleteFiles();

		bool restart;
		std::map<std::string, CommandlineUpgradeData*> filesToReplace;
		MeGUI::DialogManager *dialogManager;
		std::string path; // path the program was started from
		MeGUI::MediaFileFactory *mediaFileFactory;
		MeGUI::core::details::PackageSystem *packageSystem;
		MeGUI::JobUtil *jobUtil;
		MeGUI::MuxProvider *muxProvider;
		MeGUISettings *settings;
		ProfileManager *profileManager;

		//public MeGUISettings Settings
		//{
		//    get { return settings; }
		//}

	public:
		const MeGUI::MuxProvider &getMuxProvider() const;

	private:
		CodecManager *codecs;
	public:
		void handleCommandline(CommandlineParser *parser);

		void setGUIInfo();

		/// <summary>
		/// default constructor
		/// initializes all the GUI components, initializes the internal objects and makes a default selection for all the GUI dropdowns
		/// In addition, all the jobs and profiles are being loaded from the harddisk
		/// </summary>
		void constructMeGUIInfo();

	private:
		void fillMenus();

		void addPackages();

		static Mutex *mySingleInstanceMutex;

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[STAThread]
		static void Main(std::string& args[]);

		static void CurrentDomain_UnhandledException(object *sender, UnhandledExceptionEventArgs *e);

		static void HandleUnhandledException(std::exception &e);

		static void Application_ThreadException(object *sender, System::Threading::ThreadExceptionEventArgs *e);

		void runRestarter();
	public:
		const MeGUI::core::details::PackageSystem &getPackageSystem() const;
		const bool &getRestart() const;
		void setRestart(const bool &value);
		const MeGUI::DialogManager &getDialogManager() const;
		/// <summary>
		/// gets the path from where MeGUI was launched
		/// </summary>
		const std::string &getMeGUIPath() const;

		void ClosePlayer();

		void hidePlayer();

		void showPlayer();


	private:
		void showAllWorkers_Click(object *sender, EventArgs *e);

		void hideAllWorkers_Click(object *sender, EventArgs *e);

		void showAllWorkers_Popup(object *sender, EventArgs *e);

		void mnuWorker_Click(object *sender1, EventArgs *e);

		void viewSummary_Click(object *sender, EventArgs *e);

		void createNewWorker_Click(object *sender, EventArgs *e);

		void showAllProgressWindows_Click(object *sender, EventArgs *e);

		void hideAllProgressWindows_Click(object *sender, EventArgs *e);

		void mnuForum_Click(object *sender, EventArgs *e);

		void mnuHome_Click(object *sender, EventArgs *e);

		void mnuBugTracker_Click(object *sender, EventArgs *e);

		void mnuFeaturesReq_Click(object *sender, EventArgs *e);

		void mnuDoc_Click(object *sender, EventArgs *e);

		void mnuOptionsSettings_Click(object *sender, EventArgs *e);

		void MainForm_Shown(object *sender, EventArgs *e);

	public:
		void startUpdateCheck();

	private:
		void getVersionInformation();

	public:
		void setOverlayIcon(Icon *oIcon);

	private:
		bool AskToInstallComponents(bool bRestartRequired);

		void OneClickEncButton_Click(object *sender, EventArgs *e);

		void HelpButton_Click(object *sender, EventArgs *e);

		void menuItem5_Click(object *sender, EventArgs *e);

		void MainForm_Move(object *sender, EventArgs *e);

		void MainForm_Resize(object *sender, EventArgs *e);


		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::IContainer *components;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		void Dispose(bool disposing);

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent();

		System::Windows::Forms::TabPage *inputTab;
		System::Windows::Forms::TabControl *tabControl1;
		System::Windows::Forms::MainMenu *mainMenu1;
		System::Windows::Forms::MenuItem *mnuFile;
		System::Windows::Forms::MenuItem *mnuFileExit;
		System::Windows::Forms::MenuItem *mnuTools;
		System::Windows::Forms::OpenFileDialog *openFileDialog;
		System::Windows::Forms::SaveFileDialog *saveFileDialog;
		System::Windows::Forms::MenuItem *mnuView;
		System::Windows::Forms::MenuItem *progressMenu;
		System::Windows::Forms::MenuItem *mnuViewMinimizeToTray;
		System::Windows::Forms::NotifyIcon *trayIcon;
		System::Windows::Forms::MenuItem *mnuMuxers;
		System::Windows::Forms::MenuItem *mnuFileOpen;
		System::Windows::Forms::ContextMenuStrip *trayMenu;
		System::Windows::Forms::ToolStripMenuItem *openMeGUIToolStripMenuItem;
		System::Windows::Forms::ToolStripSeparator *toolStripSeparator1;
		System::Windows::Forms::ToolStripMenuItem *exitMeGUIToolStripMenuItem;
		System::Windows::Forms::MenuItem *mnuFileImport;
		System::Windows::Forms::MenuItem *mnuFileExport;
		System::Windows::Forms::MenuItem *mnuToolsAdaptiveMuxer;
		AudioEncodingComponent *audioEncodingComponent1;
		VideoEncodingComponent *videoEncodingComponent1;
		System::Windows::Forms::TabPage *tabPage2;
		System::Windows::Forms::MenuItem *mnuHelp;
		System::Windows::Forms::MenuItem *mnuChangelog;
		System::Windows::Forms::MenuItem *menuItem1;
		System::Windows::Forms::MenuItem *createNewWorker;
		System::Windows::Forms::MenuItem *menuItem6;
		System::Windows::Forms::MenuItem *workersMenu;
		System::Windows::Forms::MenuItem *showAllWorkers;
		System::Windows::Forms::MenuItem *hideAllWorkers;
		System::Windows::Forms::MenuItem *separator;
		System::Windows::Forms::MenuItem *menuItem2;
		System::Windows::Forms::MenuItem *viewSummary;
		System::Windows::Forms::MenuItem *showAllProgressWindows;
		System::Windows::Forms::MenuItem *hideAllProgressWindows;
		System::Windows::Forms::MenuItem *separator2;
		System::Windows::Forms::MenuItem *menuItem7;
		System::Windows::Forms::MenuItem *menuItem3;
		System::Windows::Forms::MenuItem *mnuDoc;
		System::Windows::Forms::MenuItem *mnuWebsite;
		System::Windows::Forms::MenuItem *mnuHome;
		System::Windows::Forms::MenuItem *mnuForum;
		System::Windows::Forms::MenuItem *mnuBugTracker;
		System::Windows::Forms::MenuItem *mnuFeaturesReq;
		System::Windows::Forms::MenuItem *mnuOptions;
		System::Windows::Forms::MenuItem *mnuOptionsSettings;
		System::Windows::Forms::TabPage *logTab;
		System::Windows::Forms::SplitContainer *splitContainer1;
		System::Windows::Forms::SplitContainer *splitContainer2;
		System::Windows::Forms::Button *autoEncodeButton;
		System::Windows::Forms::Button *resetButton;
		System::Windows::Forms::Button *OneClickEncButton;
		System::Windows::Forms::Button *helpButton1;
		System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel1;
		System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel2;
		System::Windows::Forms::MenuItem *mnutoolsD2VCreator;
		MeGUI::core::details::JobControl *jobControl1;
		MeGUI::core::gui::LogTree *logTree1;

	private:
		void InitializeInstanceFields();
	};
}
