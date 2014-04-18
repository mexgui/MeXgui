#pragma once

#include "core/util/LogItem.h"
#include "core/util/FileUtil.h"
#include "core/util/GenericRegisterer.h"
#include "core/util/JobUtil.h"
#include "core/util/Shutdown.h"
#include "core/util/Util.h"
#include "core/util/BitrateCalculatorPreProcessor.h"
#include "core/util/OSInfo.h"
#include "core/util/VideoUtil.h"

#include "core/details/JobControl.h"
#include "core/details/video/VideoEncodingComponent.h"
#include "core/details/PackageSystem.h"
#include "core/details/DialogSettings.h"
#include "core/details/ProfileManager.h"
#include "core/details/mux/MuxWindow.h"
#include "core/details/MediaFileFactory.h"
#include "core/details/DialogManager.h"
#include "core/details/CleanupJob.h"
#include "core/details/mux/MuxProvider.h"
#include "core/details/CodecManager.h"
#include "core/details/CommandlineParser.h"

#include "core/plugins/interfaces/IMuxing.h"
#include "core/plugins/interfaces/IPackage.h"

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
#include "packages/tools/avscreator/AviSynthWindow.h"
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
#include "packages/tools/oneclick/OneClickWindow.h"
#include "packages/tools/fileindexer/FileIndexerWindow.h"
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
#include "packages/reader/mediainfo/MediaInfoFile.h"

#include "ProgressTaskbar.h"
#include "AudioEncodingWindow.h"
#include "AudioEncodingComponent.h"
#include "UpdateWindow.h"
#include "AdaptiveMuxWindow.h"
//#include "Properties.Settings.h"
#include "ProfileExporter.h"
#include "LogTree.h"
#include <QString>
#include <QMap>
#include <QVector>
#include <algorithm>
#include <stdexcept>
#include <Qt>
#include <QThread>
#include <QSemaphore>
#include <QSystemTrayIcon>
#include <QMenu>

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





//using namespace System::Threading;



//using namespace System::Xml::Serialization;

using namespace MeXgui::core::details;
using namespace MeXgui::core::gui;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;


namespace MeXgui
{
class MainForm : public QMainWindow
{
    Q_OBJECT

	public:
        explicit MainForm(QWidget *parent = 0);
        // This instance is to be used by the serializers that can't be passed a MainForm as a parameter
        //static MainForm *Instance;

	private:
		QVector<QString> filesToDeleteOnClosing;
        QVector<QWidget*> allForms;
        QVector<QWidget*> formsToReopen;
        QMenu *taskbarItem;
        QSystemTrayIcon *taskbarIcon;
		QString strLogFile;
        QSemaphore *logLock;
		int avsLock;
		LogItem *_oneClickLog;
		LogItem *_aVSScriptCreatorLog;
		LogItem *_fileIndexerLog;
		LogItem *_updateLog;
		LogItem *_eac3toLog;
        QString programpath;
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
		const QString &getLogFile() const;
        const QSemaphore &getLogLock() const;
		void setLogLock(const SeQQMaphore &value);
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

        //void RegisterForm(Form *f);

		void DeleteOnClosing(const QString &file);

		/// <summary>
		/// launches the MeXgui wiki in the default browser
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
	private:
		void mnuGuide_Click(QObject *sender, QEvent *e);

		/// <summary>
		/// launches the encoder gui forum in the default browser
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void menuItem2_Click(QObject *sender, QEvent *e);

		/// <summary>
		/// shows the changelog dialog window
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void mnuChangelog_Click(QObject *sender, QEvent *e);

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
		virtual void OnClosing(QCloseEvent *e);
	private:
		void resetButton_Click(QObject *sender, QEvent *e);
		void autoEncodeButton_Click(QObject *sender, QEvent *e);

		void RunTool(const QString &p);
		/// <summary>
		/// Test whether a filename is suitable for writing to
		/// </summary>
		/// <param name="filename"></param>
		/// <returns>Error message if problem, null if ok</returns>
	public:
		static QString verifyOutputFile(const QString &filename);

		/// <summary>
		/// Test whether a filename is suitable for reading from
		/// </summary>
		/// <param name="filename"></param>
		/// <returns>Error message if problem, null if ok</returns>
		static QString verifyInputFile(const QString &filename);
		/// <summary>
		/// saves the global GUI settings to settings.xml
		/// </summary>
		void saveSettings();
		/// <summary>
		/// loads the global settings
		/// </summary>
		void loadSettings();


		const MeXgui::JobUtil &getJobUtil() const;

		const QString &getTitleText() const;
		void setTitleText(const QString &value);

		/// <summary>
		/// shuts down the PC if the shutdown option is set
		/// also saves all profiles, jobs and the log as MeXgui is killed
		/// via the shutdown so the appropriate methods in the OnClosing are not called
		/// </summary>
		void runAfterEncodingCommands();

		const LogItem &getLog() const;

		/// <summary>
		/// saves the whole content of the log into a logfile
		/// </summary>
		void saveLog();
	private:
		void exitMeXguiToolStripMenuItem_Click(QObject *sender, QEvent *e);
		/// <summary>
		/// returns the profile manager to whomever might require it
		/// </summary>
	public:
		const ProfileManager &getProfiles() const;
	private:
		void mnuFileOpen_Click(QObject *sender, QEvent *e);
		void mnuViewMinimizeToTray_Click(QObject *sender, QEvent *e);

		void mnuFileExit_Click(QObject *sender, QEvent *e);

		void mnuToolsSettings_Click(QObject *sender, QEvent *e);
		void mnuTool_Click(QObject *sender, QEvent *e);

		void mnuOptions_Click(QObject *sender, QEvent *e);

		void mnuMuxer_Click(QObject *sender, QEvent *e);

		void mnuView_Popup(QObject *sender, QEvent *e);

		void mnuProgress_Click(QObject *sender, QEvent *e);
		void mnuViewProcessStatus_Click(QObject *sender, QEvent *e);



	public:
		const MeXguiSettings &getSettings() const;

		const MeXgui::MediaFileFactory &getMediaFileFactory() const;
	private:
		void trayIcon_MouseDoubleClick(QObject *sender, QMouseEvent *e);
		void openMeXguiToolStripMenuItem_Click(QObject *sender, QEvent *e);

		void openOtherVideoFile(const QString &fileName);
		void openIndexableFile(const QString &fileName);
	public:
		bool openFile(const QString &file, bool openVideo);

	private:
		void importProfiles(const QString &file);
		void MeXgui_DragDrop(QObject *sender, QDropEvent *e);

		void MeXgui_DragEnter(QObject *sender, QDragEnterEvent *e);
	public:
		void importProfiles(QTextStream *data);

	private:
		bool bImportProfileSuccessful;
	public:
		const bool &getImportProfileSuccessful() const;
		void setImportProfileSuccessful(const bool &value);

	private:
		void mnuFileImport_Click(QObject *sender, QEvent *e);

		void mnuFileExport_Click(QObject *sender, QEvent *e);

		void mnuToolsAdaptiveMuxer_Click(QObject *sender, QEvent *e);

		void MeXgui_Load(QObject *sender, QEvent *e);

		void beginUpdateCheck();

		void mnuUpdate_Click(QObject *sender, QEvent *e);

	public:
		void AddFileToReplace(const QString &iUpgradeableName, const QString &tempFilename, const QString &filename, const QString &newUploadDate);

		void CloseSilent();

	private:
		void Application_ApplicationExit(QObject *sender, QEvent *e);

		void saveApplicationSettings();

		void deleteFiles();

		bool restart;
		QQMap<QString, CommandlineUpgradeData*> filesToReplace;
		MeXgui::DialogManager *dialogManager;
		QString path; // path the program was started from
		MeXgui::MediaFileFactory *mediaFileFactory;
		MeXgui::core::details::PackageSystem *packageSystem;
		MeXgui::JobUtil *jobUtil;
		MeXgui::MuxProvider *muxProvider;
		MeXguiSettings *settings;
		ProfileManager *profileManager;

		//public MeXguiSettings Settings
		//{
		//    get { return settings; }
		//}

	public:
		const MeXgui::MuxProvider &getMuxProvider() const;

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
		void constructMeXguiInfo();

	private:
		void fillMenus();

		void addPackages();

		static Mutex *mySingleInstanceMutex;

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[STAThread]
		static void Main(QString& args[]);

		static void CurrentDomain_UnhandledException(QObject *sender, QtConcurrent::UnhandledException *e);

		static void HandleUnhandledException(std::exception &e);

		static void Application_ThreadException(QObject *sender, QEvent *e); //Thread eception handling is here used as QEvent, may be a bug

		void runRestarter();
	public:
		const MeXgui::core::details::PackageSystem &getPackageSystem() const;
		const bool &getRestart() const;
		void setRestart(const bool &value);
		const MeXgui::DialogManager &getDialogManager() const;
		/// <summary>
		/// gets the path from where MeXgui was launched
		/// </summary>
		const QString &getMeXguiPath() const;

		void ClosePlayer();

		void hidePlayer();

		void showPlayer();


	private:
		void showAllWorkers_Click(QObject *sender, QEvent *e);

		void hideAllWorkers_Click(QObject *sender, QEvent *e);

		void showAllWorkers_Popup(QObject *sender, QEvent *e);

		void mnuWorker_Click(QObject *sender1, QEvent *e);

		void viewSummary_Click(QObject *sender, QEvent *e);

		void createNewWorker_Click(QObject *sender, QEvent *e);

		void showAllProgressWindows_Click(QObject *sender, QEvent *e);

		void hideAllProgressWindows_Click(QObject *sender, QEvent *e);

		void mnuForum_Click(QObject *sender, QEvent *e);

		void mnuHome_Click(QObject *sender, QEvent *e);

		void mnuBugTracker_Click(QObject *sender, QEvent *e);

		void mnuFeaturesReq_Click(QObject *sender, QEvent *e);

		void mnuDoc_Click(QObject *sender, QEvent *e);

		void mnuOptionsSettings_Click(QObject *sender, QEvent *e);

		void MainForm_Shown(QObject *sender, QEvent *e);

	public:
		void startUpdateCheck();

	private:
		void getVersionInformation();

	public:
        void setOverlayIcon(QIcon *oIcon);

	private:
		bool AskToInstallComponents(bool bRestartRequired);

		void OneClickEncButton_Click(QObject *sender, QEvent *e);

		void HelpButton_Click(QObject *sender, QEvent *e);

		void menuItem5_Click(QObject *sender, QEvent *e);

		void MainForm_Move(QObject *sender, QEvent *e);

		void MainForm_Resize(QObject *sender, QEvent *e);


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
        System::Windows::Forms::TabPage *tabPage2;
        System::Windows::Forms::TabPage *logTab;
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
		System::Windows::Forms::ToolStripMenuItem *openMeXguiToolStripMenuItem;
		System::Windows::Forms::ToolStripSeparator *toolStripSeparator1;
		System::Windows::Forms::ToolStripMenuItem *exitMeXguiToolStripMenuItem;
		System::Windows::Forms::MenuItem *mnuFileImport;
		System::Windows::Forms::MenuItem *mnuFileExport;
		System::Windows::Forms::MenuItem *mnuToolsAdaptiveMuxer;
		AudioEncodingComponent *audioEncodingComponent1;
		VideoEncodingComponent *videoEncodingComponent1;
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
		System::Windows::Forms::SplitContainer *splitContainer1;
		System::Windows::Forms::SplitContainer *splitContainer2;
		System::Windows::Forms::Button *autoEncodeButton;
		System::Windows::Forms::Button *resetButton;
		System::Windows::Forms::Button *OneClickEncButton;
		System::Windows::Forms::Button *helpButton1;
		System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel1;
		System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel2;
		System::Windows::Forms::MenuItem *mnutoolsD2VCreator;
		MeXgui::core::details::JobControl *jobControl1;
		MeXgui::core::gui::LogTree *logTree1;

	private:
		void InitializeInstanceFields();
	};
}
