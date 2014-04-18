#include "MainForm.h"
#include <QProcess>
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
	void CommandlineUpgradeData::InitializeInstanceFields()
	{
		filename = QVector<QString>();
		tempFilename = QVector<QString>();
	}
	
	const bool &MainForm::getIsHiddenMode() const
	{
		return trayIcon->Visible;
	}

	const bool &MainForm::getIsOverlayIconActive() const
	{
		return taskbarIcon != 0;
	}

	const QString &MainForm::getLogFile() const
	{
		return strLogFile;
	}

	const SeQQMaphore &MainForm::getLogLock() const
	{
		return logLock;
	}

	void MainForm::setLogLock(const SeQQMaphore &value)
	{
		logLock = value;
	}

	const int &MainForm::getAvsLock() const
	{
		return avsLock;
	}

	void MainForm::setAvsLock(const int &value)
	{
		avsLock = value;
	}

	const MeXgui::core::util::LogItem &MainForm::getOneClickLog() const
	{
		return _oneClickLog;
	}

	void MainForm::setOneClickLog(const LogItem &value)
	{
		_oneClickLog = value;
	}

	const MeXgui::core::util::LogItem &MainForm::getAVSScriptCreatorLog() const
	{
		return _aVSScriptCreatorLog;
	}

	void MainForm::setAVSScriptCreatorLog(const LogItem &value)
	{
		_aVSScriptCreatorLog = value;
	}

	const MeXgui::core::util::LogItem &MainForm::getFileIndexerLog() const
	{
		return _fileIndexerLog;
	}

	void MainForm::setFileIndexerLog(const LogItem &value)
	{
		_fileIndexerLog = value;
	}

	const MeXgui::core::util::LogItem &MainForm::getUpdateLog() const
	{
		return _updateLog;
	}

	void MainForm::setUpdateLog(const LogItem &value)
	{
		_updateLog = value;
	}

	const MeXgui::core::util::LogItem &MainForm::getEac3toLog() const
	{
		return _eac3toLog;
	}

	void MainForm::setEac3toLog(const LogItem &value)
	{
		_eac3toLog = value;
	}

	void MainForm::RegisterForm(Form *f)
	{
	}

	void MainForm::DeleteOnClosing(const QString &file)
	{
		filesToDeleteOnClosing.push_back(file);
	}

	void MainForm::mnuGuide_Click(QObject *sender, QEvent *e)
	{
        QDesktopServices::openUrl("http://mewiki.project357.com/wiki/Main_Page");
	}

	void MainForm::menuItem2_Click(QObject *sender, QEvent *e)
	{

	}

	void MainForm::mnuChangelog_Click(QObject *sender, QEvent *e)
	{
        QString strChangeLog = QAplication::applicationDirPath() << "changelog.txt";

		if (File::Exists(strChangeLog))
		{
			try
			{
                QProcess *oProcess = new QProcess();
                oProcess->setProgram(strChangeLog);
				oProcess->StartInfo->UseShellExecute = true;
				oProcess->Start();
			}
            catch (MainForm::Application_ThreadException &ex)
			{
				MessageBox::Show(strChangeLog + " cannot be opened:\r\n" + ex.what(), "Process error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		else
		{
			MessageBox::Show(strChangeLog + " not found", "Changelog not found", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

	MainForm::MainForm()
	{
		// Log File Handling
		InitializeInstanceFields();
		QString strMeXguiLogPath = System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath) + "\\logs";
		FileUtil::ensureDirectoryExists(strMeXguiLogPath);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		strLogFile = strMeXguiLogPath + "\\logfile-" + DateTime::Now->ToString("yy'-'MM'-'dd'_'HH'-'mm'-'ss") + ".log";
        logLock = new QSemaphore(1, 1);
		avsLock = 0;
		try
		{
			logLock->WaitOne(10000, false);
			File::WriteAllText(strLogFile, "Preliminary log file only. During closing of MeXgui the well formed log file will be written.\r\n\r\n");
		}
		catch (std::exception &ex)
		{
			MessageBox::Show(ex.what(), "Log File Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		logLock->Release();
		Instance = this;
		constructMeXguiInfo();
		InitializeComponent();
		System::Reflection::Assembly *myAssembly = this->GetType()->Assembly;
		QString name = this->GetType()->Namespace + ".";
	#if defined(CSC)
		name = "";
	#endif
//ORIGINAL LINE: string[] resources = myAssembly.GetManifestResourceNames();
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		QString *resources = myAssembly->GetManifestResourceNames();
		this->trayIcon->Icon = new Icon(myAssembly->GetManifestResourceStream(name + "App.ico"));
		this->Icon = trayIcon->Icon;
		this->setTitleText(Application::ProductName + " " + (new System::Version(Application::ProductVersion))->Build);
	#if defined(x64)
		this->setTitleText(this->getTitleText() + " x64");
	#endif
		if (MainForm::Instance->getSettings()->getAutoUpdate() == true && MainForm::Instance->getSettings()->getAutoUpdateServerSubList() == 1)
			this->setTitleText(this->getTitleText() + " DEVELOPMENT UPDATE SERVER");
		setGUIInfo();
		getJobs()->showAfterEncodingStatus(getSettings());
		this->videoEncodingComponent1->setFileType(MainForm::Instance->getSettings()->getMainFileFormat());

		this->ClientSize = settings->getMainFormSize();
		this->Location = settings->getMainFormLocation();
		this->splitContainer2->SplitterDistance = static_cast<int>(0.42 * (this->splitContainer2->Panel1->Height + this->splitContainer2->Panel2->Height));

		Size *oSizeScreen = Screen::GetWorkingArea(this)->Size;
		Point *oLocation = Screen::GetWorkingArea(this)->Location;
		int iScreenHeight = oSizeScreen->Height - 2 * SystemInformation::FixedFrameBorderSize->Height;
		int iScreenWidth = oSizeScreen->Width - 2 * SystemInformation::FixedFrameBorderSize->Width;

		if (this->Size->Height >= iScreenHeight)
			this->Location = new Point(this->Location->X, oLocation->Y);
		else if (this->Location->Y <= oLocation->Y)
			this->Location = new Point(this->Location->X, oLocation->Y);
		else if (this->Location->Y + this->Size->Height > iScreenHeight)
			this->Location = new Point(this->Location->X, iScreenHeight - this->Size->Height);

		if (this->Size->Width >= iScreenWidth)
			this->Location = new Point(oLocation->X, this->Location->Y);
		else if (this->Location->X <= oLocation->X)
			this->Location = new Point(oLocation->X, this->Location->Y);
		else if (this->Location->X + this->Size->Width > iScreenWidth)
			this->Location = new Point(iScreenWidth - this->Size->Width, this->Location->Y);
	}

	const MeXgui::core::details::JobControl &MainForm::getJobs() const
	{
		return jobControl1;
	}

	const bool &MainForm::getProcessStatusChecked() const
	{
		return progressMenu->Checked;
	}

	void MainForm::setProcessStatusChecked(const bool &value)
	{
		progressMenu->Checked = value;
	}

	const VideoEncodingComponent &MainForm::getVideo() const
	{
		return videoEncodingComponent1;
	}

	const AudioEncodingComponent &MainForm::getAudio() const
	{
		return audioEncodingComponent1;
	}

	void MainForm::OnClosing(QCloseEvent *e)
	{
		if (jobControl1->getIsAnyWorkerEncoding())
		{
			//todo: handle closevent with qmethod
			e->Cancel = true; // abort closing
			MessageBox::Show("Please close running jobs before you close MeXgui.", "Job in progress", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		}
		if (!e->Cancel)
		{
			CloseSilent();
		}
		System::Windows::Forms::Form::OnClosing(e);
	}

	void MainForm::resetButton_Click()
	{
		videoEncodingComponent1->Reset();
		audioEncodingComponent1->Reset();
	}

	void MainForm::autoEncodeButton_Click()
	{
		RunTool("AutoEncode");
	}

	void MainForm::RunTool(const QString &p)
	{
		try
		{
			ITool *tool = getPackageSystem()->getTools()[p];
			tool->Run(this);
		}
		catch (KeyNotFoundException *e1)
		{
			MessageBox::Show("Required tool, '" + p + "', not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	QString MainForm::verifyOutputFile(const QString &filename)
	{
		try
		{
			filename = Path::GetFullPath(filename); // this will throw ArgumentException if invalid
			if (File::Exists(filename))
			{
				FileStream *fs = File::OpenWrite(filename); // this will throw if we'll have problems writing
				fs->Close();
			}
			else
			{
				FileStream *fs = File::Create(filename); // this will throw if we'll have problems writing
				fs->Close();
				File::Delete(filename);
			}
		}
		catch (std::exception &e)
		{
			return e.what();
		}
		return 0;
	}

	QString MainForm::verifyInputFile(const QString &filename)
	{
		try
		{
			filename = Path::GetFullPath(filename); // this will throw ArgumentException if invalid
			FileStream *fs = File::OpenRead(filename); // this will throw if we'll have problems reading
			fs->Close();
		}
		catch (std::exception &e)
		{
			return e.what();
		}
		return 0;
	}

	void MainForm::saveSettings()
	{
		XmlSerializer *ser = 0;
		QString fileName = this->path + "\\settings.xml";
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Stream s = File.Open(fileName, System.IO.FileMode.Create, System.IO.FileAccess.Write))
		Stream *s = File->Open(fileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
		try
		{
			try
			{
				ser = new XmlSerializer(MeXguiSettings::typeid);
				ser->Serialize(s, this->settings);
			}
			catch (std::exception &e)
			{
				LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
				_oLog->LogValue("saveSettings", e, Error);
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (s != 0)
				s.Dispose();
		}
	}

	void MainForm::loadSettings()
	{
		QString fileName = Path::Combine(path, "settings.xml");
		if (File::Exists(fileName))
		{
			XmlSerializer *ser = 0;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (Stream s = File.OpenRead(fileName))
			Stream *s = File::OpenRead(fileName);
			try
			{
				ser = new XmlSerializer(MeXguiSettings::typeid);
				try
				{
					this->settings = static_cast<MeXguiSettings*>(ser->Deserialize(s));
				}
				catch (...)
				{
					MessageBox::Show("MeXgui settings could not be loaded. Default values will be applied now.", "Error loading MeXgui settings", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (s != 0)
					s.Dispose();
			}
		}
	}

	const MeXgui::JobUtil &MainForm::getJobUtil() const
	{
		return jobUtil;
	}

	const QString &MainForm::getTitleText() const
	{
		return this->Text;
	}

	void MainForm::setTitleText(const QString &value)
	{
		this->Text = value;
		trayIcon->Text = value;
	}

	void MainForm::runAfterEncodingCommands()
	{
		if (getJobs()->getCurrentAfterEncoding() == DoNothing)
			return;
		this->profileManager->SaveProfiles();
		this->saveSettings();
		jobControl1->saveJobs();
		this->saveLog();

		if (getJobs()->getCurrentAfterEncoding() == Shutdown)
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (CountdownWindow countdown = new CountdownWindow(30))
			CountdownWindow *countdown = new CountdownWindow(30);
			try
			{
				if (countdown->show() == System::Windows::Forms::DialogResult::OK)
				{
					bool succ = Shutdown::shutdown();
					if (!succ)
						getLog()->LogEvent("Tried and failed to shut down system");
					else
						getLog()->LogEvent("Shutdown initiated");
				}
				else
					getLog()->LogEvent("User aborted shutdown");

			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (countdown != 0)
					countdown.Dispose();
			}
		}
		else if (getJobs()->getCurrentAfterEncoding() == CloseMeXgui)
		{
			this->CloseSilent();
			Application::Exit();
		}
		else if (getJobs()->getCurrentAfterEncoding() == RunCommand && !settings->getAfterEncodingCommand().empty())
		{
			QString filename = getMeXguiPath() + "\\after_encoding.bat";
			try
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (StreamWriter s = new StreamWriter(File.OpenWrite(filename)))
				StreamWriter *s = new StreamWriter(File::OpenWrite(filename));
				try
				{
					s->WriteLine(settings->getAfterEncodingCommand());
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (s != 0)
						s.Dispose();
				}
				ProcessStartInfo *psi = new ProcessStartInfo(filename);
				psi->CreateNoWindow = true;
				psi->UseShellExecute = false;
				Process *p = new Process();
				p->StartInfo = psi;
				p->Start();
			}
			catch (IOException *e)
			{
				MessageBox::Show("Error when attempting to run command: " + e->Message, "Run command failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

	const MeXgui::core::util::LogItem &MainForm::getLog() const
	{
		return logTree1->Log;
	}

	void MainForm::saveLog()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		QString text = getLog()->ToString();
		try
		{
			logLock->WaitOne(10000, false);
			File::WriteAllText(strLogFile, text);
		}
		catch (std::exception &e1)
		{
			MessageBox::Show("Log file cannot be saved", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			logLock->Release();
		}
	}

	void MainForm::exitMeXguiToolStripMenuItem_Click()
	{
		Close();
	}

	const ProfileManager &MainForm::getProfiles() const
	{
		return this->profileManager;
	}

	void MainForm::mnuFileOpen_Click()
	{
		openFileDialog->Filter = "All files|*.*";
		openFileDialog->Title = "Select your input file";
		if (openFileDialog->show() == System::Windows::Forms::DialogResult::OK)
			openFile(openFileDialog->FileName, false);
	}

	void MainForm::mnuViewMinimizeToTray_Click()
	{
		formsToReopen.clear();
		this->Visible = false;
		trayIcon->Visible = true;
	}

	void MainForm::mnuFileExit_Click()
	{
		this->Close();
	}

	void MainForm::mnuToolsSettings_Click()
	{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (SettingsForm sform = new SettingsForm())
		SettingsForm *sform = new SettingsForm();
		try
		{
			sform->setSettings(this->settings);
			if (sform->show() == System::Windows::Forms::DialogResult::OK)
			{
				this->settings = sform->getSettings();
				this->saveSettings();
				getJobs()->showAfterEncodingStatus(settings);
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (sform != 0)
				sform.Dispose();
		}
	}

	void MainForm::mnuTool_Click()
	{
		if ((!(dynamic_cast<System::Windows::Forms::MenuItem*>(sender) != 0)) || (!(dynamic_cast<ITool*>((dynamic_cast<MenuItem*>(sender))->Tag) != 0)))
			return;
		(static_cast<ITool*>((dynamic_cast<MenuItem*>(sender))->Tag))->Run(this);
	}

	void MainForm::mnuOptions_Click()
	{
		if ((!(dynamic_cast<System::Windows::Forms::MenuItem*>(sender) != 0)) || (!(dynamic_cast<IOption*>((dynamic_cast<MenuItem*>(sender))->Tag) != 0)))
			return;
		(static_cast<IOption*>((dynamic_cast<MenuItem*>(sender))->Tag))->Run(this);
	}

	void MainForm::mnuMuxer_Click()
	{
		if ((!(dynamic_cast<System::Windows::Forms::MenuItem*>(sender) != 0)) || (!(dynamic_cast<IMuxing*>((dynamic_cast<MenuItem*>(sender))->Tag) != 0)))
			return;
		MuxWindow *mw = new MuxWindow(static_cast<IMuxing*>((dynamic_cast<MenuItem*>(sender))->Tag), this);
		mw->Show();
	}

	void MainForm::mnuView_Popup()
	{
		QVector<Pair<QString, bool>*> workers = getJobs()->ListProgressWindows();
		progressMenu->MenuItems->Clear();
		progressMenu->MenuItems->Add(showAllProgressWindows);
		progressMenu->MenuItems->Add(hideAllProgressWindows);
		progressMenu->MenuItems->Add(separator2);

		for (QVector<Pair<QString, bool>*>::const_iterator p = workers.begin(); p != workers.end(); ++p)
		{
			MenuItem *i = new MenuItem((*p)->fst);
			i->Checked = (*p)->snd;
			i->Click += new EventHandler(this, &MainForm::mnuProgress_Click);
			progressMenu->MenuItems->Add(i);
		}

		if (workers.empty())
		{
			MenuItem *i = new MenuItem("(No progress windows to show)");
			i->Enabled = false;
			progressMenu->MenuItems->Add(i);
		}
	}

	void MainForm::mnuProgress_Click()
	{
		MenuItem *i = static_cast<MenuItem*>(sender);
		if (i->Checked)
			getJobs()->HideProgressWindow(i->Text);
		else
			getJobs()->ShowProgressWindow(i->Text);
	}

	void MainForm::mnuViewProcessStatus_Click()
	{
	}

	const MeXguiSettings &MainForm::getSettings() const
	{
		return settings;
	}

	const MeXgui::MediaFileFactory &MainForm::getMediaFileFactory() const
	{
		return mediaFileFactory;
	}

	void MainForm::trayIcon_MouseDoubleClick(QObject *sender, MouseQEvent *e)
	{
		// Activate the form.
		this->Show();
		this->Activate();

		if (progressMenu->Checked)
			getJobs()->ShowAllProcessWindows();
		trayIcon->Visible = false;
	}

	void MainForm::openMeXguiToolStripMenuItem_Click()
	{
		trayIcon->Visible = false;
		this->Visible = true;
	}

	void MainForm::openOtherVideoFile(const QString &fileName)
	{
		AviSynthWindow *asw = new AviSynthWindow(this, fileName);
		asw->OpenScript += new OpenScriptCallback(this, &getVideo()->openVideoFile);
		asw->Show();
	}

	void MainForm::openIndexableFile(const QString &fileName)
	{
		if (getDialogManager()->useOneClick())
		{
			OneClickWindow *ocmt = new OneClickWindow(this);
			ocmt->setInput(fileName);
			ocmt->show();
		}
		else
		{
			FileIndexerWindow *mpegInput = new FileIndexerWindow(this);
			mpegInput->setConfig(fileName, 0, 2, true, true, true, false);
			mpegInput->Show();
		}
	}

	bool MainForm::openFile(const QString &file, bool openVideo)
	{
		if (Path::GetExtension(file.ToLowerInvariant())->Equals(".zip"))
		{
			importProfiles(file);
			return false;
		}

		MediaInfoFile *iFile = new MediaInfoFile(file);
		if (iFile->getHasVideo())
		{
			if (iFile->isD2VIndexable() || iFile->isDGIIndexable() || iFile->isDGAIndexable() || iFile->isFFMSIndexable())
			{
				openIndexableFile(file);
			}
			else
			{
				if (iFile->getHasAudio())
					audioEncodingComponent1->openAudioFile(file);
				if (iFile->getContainerFileTypeString().Equals("AVS"))
				{
					getVideo()->openVideoFile(file);
					if (openVideo)
						return true;
				}
				else
					openOtherVideoFile(file);
			}
		}
		else if (iFile->getHasAudio())
			audioEncodingComponent1->openAudioFile(file);
		else if (Path::GetExtension(iFile->getFileName())->ToLowerInvariant()->Equals(".avs"))
		{
			try
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (AvsFile avi = AvsFile.OpenScriptFile(iFile.FileName))
				AvsFile *avi = AvsFile::OpenScriptFile(iFile->getFileName());
				try
				{
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (avi != 0)
						avi.Dispose();
				}
			}
			catch (std::exception &ex)
			{
				MessageBox::Show(ex.what(), "Error parsing avs file", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		else
			MessageBox::Show("This file cannot be opened", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}

	void MainForm::importProfiles(const QString &file)
	{
		(new ProfileImporter(this, file, false))->show();
	}

	void MainForm::MeXgui_DragDrop(QObject *sender, DragQEvent *e)
	{
//ORIGINAL LINE: string[] files = (string[])e.Data.GetData(DataFormats.FileDrop, false);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		QString *files = static_cast<QString[]>(e->Data->GetData(DataFormats::FileDrop, false));
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		Invoke(new MethodInvoker(delegate
		{
			openFile(files[0], false);
		}
	   ));
		this->tabControl1->SelectedIndex = 0;
	}

	void MainForm::MeXgui_DragEnter(QObject *sender, DragQEvent *e)
	{
		e->Effect = DragDropEffects::None;
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
		{
//ORIGINAL LINE: string[] files = (string[])e.Data.GetData(DataFormats.FileDrop, false);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			QString *files = static_cast<QString[]>(e->Data->GetData(DataFormats::FileDrop, false));
			if (sizeof(files) / sizeof(files[0]) > 0)
				e->Effect = DragDropEffects::All;
		}
	}

	void MainForm::importProfiles(Stream *data)
	{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		Util::ThreadSafeRun(this, delegate // wait until the profiles have been imported
		{
			ProfileImporter *importer = new ProfileImporter(this, data, true);
			if (importer->ErrorDuringInit())
				return;
				if (MainForm::Instance->settings->AutoUpdateSession)
				{
					importer->AutoImport();
				}
				else
				{
					importer->Show();
					while (importer->Visible == true)
					{
						Application::DoEvents();
						delay(100);
					}
				}
		}
	   );
	}

	const bool &MainForm::getImportProfileSuccessful() const
	{
		return bImportProfileSuccessful;
	}

	void MainForm::setImportProfileSuccessful(const bool &value)
	{
		bImportProfileSuccessful = value;
	}

	void MainForm::mnuFileImport_Click()
	{
		try
		{
			(new ProfileImporter(this, false))->show();
		}
		catch (CancelledException *e1)
		{
		}
	}

	void MainForm::mnuFileExport_Click()
	{
		(new ProfileExporter(this))->show();
	}

	void MainForm::mnuToolsAdaptiveMuxer_Click()
	{
		AdaptiveMuxWindow *amw = new AdaptiveMuxWindow(this);
		amw->Show();
	}

	void MainForm::MeXgui_Load()
	{
		RegisterForm(this);
	}

	void MainForm::beginUpdateCheck()
	{
	#if defined(x86)
		QString strLocalUpdateXML = Path::Combine(Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "upgrade.xml");
	#endif
	#if defined(x64)
		QString strLocalUpdateXML = Path::Combine(Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "upgrade_x64.xml");
	#endif
		if (File::Exists(strLocalUpdateXML))
			MainForm::Instance->getSettings()->setAutoUpdateSession(true);

		UpdateWindow *update = new UpdateWindow(this, false);
		update->GetUpdateData(true);
		bool bIsComponentMissing = UpdateWindow::isComponentMissing();
		if (bIsComponentMissing || update->HasUpdatableFiles()) // If there are updated or missing files, display the window
		{
			if (MainForm::Instance->getSettings()->getAutoUpdateSession())
			{
				update->Visible = true;
				update->StartAutoUpdate();
				while (update->Visible == true)
				{
					Application::DoEvents();
					delay(100);
				}
			}
			else
			{
				if (bIsComponentMissing)
				{
					if (AskToInstallComponents(filesToReplace.Keys->Count > 0) == true)
					{
						if (filesToReplace.Keys->Count > 0) // restart required
						{
							this->setRestart(true);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
							this->Invoke(new MethodInvoker(delegate
							{
								this->Close();
							}
						   ));
							return;
						}
					}
					else
						return;
				}
				if (MessageBox::Show("There are updated files available that may be necessary for MeXgui to work correctly. Some of them are binary files subject to patents, so they could be in violation of your local laws if you live e.g. in US, Japan and some countries in Europe. MeXgui will let you choose what files to update but please check your local laws about patents before proceeding. By clicking on the 'Yes' button you declare you have read this warning. Do you wish to proceed reviewing the updates?", "Updates Available", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
					update->show();
			}
			if (UpdateWindow::isComponentMissing() && !this->getRestart())
			{
				if (AskToInstallComponents(filesToReplace.Keys->Count > 0) == true)
				{
					if (filesToReplace.Keys->Count > 0) // restart required
					{
						this->setRestart(true);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
						this->Invoke(new MethodInvoker(delegate
						{
							this->Close();
						}
					   ));
						return;
					}
					else
						beginUpdateCheck();
				}
			}
		}
		else
		{
			if (File::Exists(strLocalUpdateXML))
				File::Delete(strLocalUpdateXML);
		}
	}

	void MainForm::mnuUpdate_Click(QObject *sender, QEvent *e)
	{
		UpdateWindow *update = new UpdateWindow(this, false);
		update->show();
	}

	void MainForm::AddFileToReplace(const QString &iUpgradeableName, const QString &tempFilename, const QString &filename, const QString &newUploadDate)
	{
		CommandlineUpgradeData *data = new CommandlineUpgradeData();
		data->filename.push_back(filename);
		data->tempFilename.push_back(tempFilename);
		data->newUploadDate = newUploadDate;
		if (filesToReplace.find(iUpgradeableName) != filesToReplace.end())
		{
			filesToReplace[iUpgradeableName]->tempFilename->push_back(tempFilename);
			filesToReplace[iUpgradeableName]->filename->push_back(filename);
			return;
		}
		filesToReplace.insert(make_pair(iUpgradeableName, data));
	}

	void MainForm::CloseSilent()
	{
		this->profileManager->SaveProfiles();
		this->saveSettings();
		this->saveApplicationSettings();
		jobControl1->saveJobs();
		this->saveLog();
		deleteFiles();
		this->runRestarter();
		Application::ApplicationExit += new EventHandler(this, &MainForm::Application_ApplicationExit);
	}

	void MainForm::Application_ApplicationExit(QObject *sender, QEvent *e)
	{
		MeXgui::Properties::Settings::getDefault()->Save();
	}

	void MainForm::saveApplicationSettings()
	{
	}

	void MainForm::deleteFiles()
	{
		for (QVector<QString>::const_iterator file = filesToDeleteOnClosing.begin(); file != filesToDeleteOnClosing.end(); ++file)
		{
			try
			{
				FileUtil::DeleteDirectoryIfExists(*file, true);
				if (File::Exists(*file))
					File::Delete(*file);
			}
			catch (...)
			{
			}
		}
	}

	const MeXgui::MuxProvider &MainForm::getMuxProvider() const
	{
		return muxProvider;
	}

	void MainForm::handleCommandline(CommandlineParser *parser)
	{
		for (QVector<QString>::const_iterator file = parser->failedUpgrades.begin(); file != parser->failedUpgrades.end(); ++file)
			System::Windows::Forms::MessageBox::Show("Failed to upgrade '" + *file + "'.", "Upgrade failed", MessageBoxButtons::OK, MessageBoxIcon::Error);

		if (parser->upgradeData.size() > 0)
		{
			UpdateWindow *update = new UpdateWindow(this, false);
			for (QQMap<QString, QString>::const_iterator file = parser->upgradeData.begin(); file != parser->upgradeData.end(); ++file)
				update->UpdateUploadDate(*file, parser->upgradeData[*file]);
			update->SaveSettings();
		}
	}

	void MainForm::setGUIInfo()
	{
		fillMenus();
		jobControl1->setMainForm(this);
		jobControl1->loadJobs();

	}

	void MainForm::constructMeXguiInfo()
	{
		muxProvider = new MuxProvider(this);
		this->codecs = new CodecManager();
		this->path = System::Windows::Forms::Application::StartupPath;
		this->jobUtil = new JobUtil(this);
		this->settings = new MeXguiSettings();
		addPackages();
		this->profileManager = new ProfileManager(this->path);
		this->profileManager->LoadProfiles();
		this->mediaFileFactory = new MediaFileFactory(this);
		this->loadSettings();
		this->dialogManager = new DialogManager(this);
	}

	void MainForm::fillMenus()
	{
		// Fill the muxing menu
		mnuMuxers->MenuItems->Clear();
		mnuToolsAdaptiveMuxer->Shortcut = Shortcut::Ctrl1;
		mnuMuxers->MenuItems->Add(mnuToolsAdaptiveMuxer);
		int index = 1;
		for (MeXgui::GenericRegisterer<IMuxing*>::const_iterator muxer = getPackageSystem()->getMuxerProviders()->begin(); muxer != getPackageSystem()->getMuxerProviders()->end(); ++muxer)
		{
			MenuItem *newMenuItem = new MenuItem();
			newMenuItem->Text = muxer->second->Name;
			newMenuItem->Tag = muxer->second;
			newMenuItem->Index = index;
			newMenuItem->Shortcut = muxer->second->Shortcut;
			index++;
			mnuMuxers->MenuItems->Add(newMenuItem);
			newMenuItem->Click += new System::EventHandler(this, &MainForm::mnuMuxer_Click);
		}

		// Fill the tools menu
		mnuTools->MenuItems->Clear();
		QVector<MenuItem*> toolsItems = QVector<MenuItem*>();
		QVector<Shortcut*> usedShortcuts = QVector<Shortcut*>();
		toolsItems.push_back(mnutoolsD2VCreator);
		toolsItems.push_back(mnuMuxers);
		usedShortcuts.push_back(mnuMuxers->Shortcut);

		for (MeXgui::GenericRegisterer<ITool*>::const_iterator tool = getPackageSystem()->getTools()->begin(); tool != getPackageSystem()->getTools()->end(); ++tool)
		{
			if (tool->second->Name != "File Indexer")
			{
				MenuItem *newMenuItem = new MenuItem();
				newMenuItem->Text = tool->second->Name;
				newMenuItem->Tag = tool->second;
				newMenuItem->Click += new System::EventHandler(this, &MainForm::mnuTool_Click);
				bool shortcutAttempted = false;
				for (System::Windows::Forms::Shortcut::const_iterator s = tool->getShortcuts()->begin(); s != tool->getShortcuts()->end(); ++s)
				{
					shortcutAttempted = true;
					assert(*s != Shortcut::None);
					if (!std::find(usedShortcuts.begin(), usedShortcuts.end(), *s) != usedShortcuts.end())
					{
						usedShortcuts.push_back(*s);
						newMenuItem->Shortcut = *s;
						break;
					}
				}

				if (shortcutAttempted && newMenuItem->Shortcut == Shortcut::None)
					getLog()->Warn("Shortcut for '" + tool->second->Name + "' is already used. No shortcut selected.");
				toolsItems.push_back(newMenuItem);
			}
		}

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		toolsItems.Sort(new Comparison<MenuItem*>(delegate(MenuItem a, MenuItem b)
		{
			return (a->Text->compare(b->Text));
		}
	   ));
		index = 0;
		for (QVector<MenuItem*>::const_iterator m = toolsItems.begin(); m != toolsItems.end(); ++m)
		{
			(*m)->Index = index;
			index++;
			mnuTools->MenuItems->Add(*m);
		}

		// Fill the Options Menu
		mnuOptions->MenuItems->Clear();
		QVector<MenuItem*> optionsItems = QVector<MenuItem*>();
		QVector<Shortcut*> usedShortcuts2 = QVector<Shortcut*>();
		optionsItems.push_back(mnuOptionsSettings);
		usedShortcuts2.push_back(mnuOptionsSettings->Shortcut);
		for (MeXgui::GenericRegisterer<IOption*>::const_iterator option = getPackageSystem()->getOptions()->begin(); option != getPackageSystem()->getOptions()->end(); ++option)
		{
			MenuItem *newMenuItem = new MenuItem();
			newMenuItem->Text = option->second->Name;
			newMenuItem->Tag = option->second;
			newMenuItem->Click += new System::EventHandler(this, &MainForm::mnuOptions_Click);
			bool shortcutAttempted = false;
			for (System::Windows::Forms::Shortcut::const_iterator s = option->getShortcuts()->begin(); s != option->getShortcuts()->end(); ++s)
			{
				shortcutAttempted = true;
				assert(*s != Shortcut::None);
				if (!std::find(usedShortcuts.begin(), usedShortcuts.end(), *s) != usedShortcuts.end())
				{
					usedShortcuts2.push_back(*s);
					newMenuItem->Shortcut = *s;
					break;
				}
			}
			if (shortcutAttempted && newMenuItem->Shortcut == Shortcut::None)
				getLog()->Warn("Shortcut for '" + option->second->Name + "' is already used. No shortcut selected.");
			optionsItems.push_back(newMenuItem);
		}

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		optionsItems.Sort(new Comparison<MenuItem*>(delegate(MenuItem a, MenuItem b)
		{
			return (a->Text->compare(b->Text));
		}
	   ));
		index = 0;
		for (QVector<MenuItem*>::const_iterator m = optionsItems.begin(); m != optionsItems.end(); ++m)
		{
			(*m)->Index = index;
			index++;
			mnuOptions->MenuItems->Add(*m);
		}
	}

	void MainForm::addPackages()
	{
		getPackageSystem()->getJobProcessors()->Register(AviSynthAudioEncoder::Factory);

		getPackageSystem()->getJobProcessors()->Register(ffmpegEncoder::Factory);
		getPackageSystem()->getJobProcessors()->Register(x264Encoder::Factory);
		getPackageSystem()->getJobProcessors()->Register(XviDEncoder::Factory);

		getPackageSystem()->getJobProcessors()->Register(MkvMergeMuxer::Factory);
		getPackageSystem()->getJobProcessors()->Register(MP4BoxMuxer::Factory);
		getPackageSystem()->getJobProcessors()->Register(AMGMuxer::Factory);
		getPackageSystem()->getJobProcessors()->Register(tsMuxeR::Factory);

		getPackageSystem()->getJobProcessors()->Register(MkvExtract::Factory);
		getPackageSystem()->getJobProcessors()->Register(PgcDemux::Factory);
		getPackageSystem()->getJobProcessors()->Register(OneClickPostProcessing::Factory);
		getPackageSystem()->getJobProcessors()->Register(CleanupJobRunner::Factory);

		getPackageSystem()->getJobProcessors()->Register(AviSynthProcessor::Factory);
		getPackageSystem()->getJobProcessors()->Register(D2VIndexer::Factory);
		getPackageSystem()->getJobProcessors()->Register(DGAIndexer::Factory);
		getPackageSystem()->getJobProcessors()->Register(DGIIndexer::Factory);
		getPackageSystem()->getJobProcessors()->Register(FFMSIndexer::Factory);
		getPackageSystem()->getJobProcessors()->Register(VobSubIndexer::Factory);
		getPackageSystem()->getJobProcessors()->Register(MeXgui::packages::tools::besplitter::Joiner::Factory);
		getPackageSystem()->getJobProcessors()->Register(MeXgui::packages::tools::besplitter::Splitter::Factory);
		getPackageSystem()->getJobProcessors()->Register(HDStreamExtractorIndexer::Factory);
		getPackageSystem()->getMuxerProviders()->Register(new AVIMuxGUIMuxerProvider());
		getPackageSystem()->getMuxerProviders()->Register(new TSMuxerProvider());
		getPackageSystem()->getMuxerProviders()->Register(new MKVMergeMuxerProvider());
		getPackageSystem()->getMuxerProviders()->Register(new MP4BoxMuxerProvider());
		getPackageSystem()->getTools()->Register(new MeXgui::packages::tools::cutter::CutterTool());
		getPackageSystem()->getTools()->Register(new AviSynthWindowTool());
		getPackageSystem()->getTools()->Register(new AutoEncodeTool());
		getPackageSystem()->getTools()->Register(new CQMEditorTool());
		getPackageSystem()->getTools()->Register(new CalculatorTool());
		getPackageSystem()->getTools()->Register(new ChapterCreatorTool());
		getPackageSystem()->getOptions()->Register(new UpdateOptions());
		getPackageSystem()->getTools()->Register(new MeXgui::packages::tools::besplitter::BesplitterTool());
		getPackageSystem()->getTools()->Register(new OneClickTool());
		getPackageSystem()->getTools()->Register(new D2VCreatorTool());
		getPackageSystem()->getTools()->Register(new AVCLevelTool());
		getPackageSystem()->getTools()->Register(new VobSubTool());
		getPackageSystem()->getTools()->Register(new MeXgui::packages::tools::hdbdextractor::HdBdExtractorTool());
		getPackageSystem()->getMediaFileTypes()->Register(new AvsFileFactory());
		getPackageSystem()->getMediaFileTypes()->Register(new d2vFileFactory());
		getPackageSystem()->getMediaFileTypes()->Register(new dgaFileFactory());
		getPackageSystem()->getMediaFileTypes()->Register(new dgiFileFactory());
		getPackageSystem()->getMediaFileTypes()->Register(new ffmsFileFactory());
		getPackageSystem()->getMediaFileTypes()->Register(new MediaInfoFileFactory());
		getPackageSystem()->getJobPreProcessors()->Register(BitrateCalculatorPreProcessor::CalculationProcessor);
		getPackageSystem()->getJobPostProcessors()->Register(d2vIndexJobPostProcessor::PostProcessor);
		getPackageSystem()->getJobPostProcessors()->Register(dgaIndexJobPostProcessor::PostProcessor);
		getPackageSystem()->getJobPostProcessors()->Register(dgiIndexJobPostProcessor::PostProcessor);
		getPackageSystem()->getJobPostProcessors()->Register(ffmsIndexJobPostProcessor::PostProcessor);
		getPackageSystem()->getJobPostProcessors()->Register(CleanupJobRunner::DeleteIntermediateFilesPostProcessor);
		getPackageSystem()->JobConfigurers->Register(MuxWindow::Configurer);
		getPackageSystem()->JobConfigurers->Register(AudioEncodingWindow::Configurer);
	}

Mutex *MainForm::mySingleInstanceMutex = new Mutex(true, "MeXgui_mutex");

	void MainForm::Main(QString& args[])
	{
		// Parse for the need to run the program elevated
		bool bRunElevated = false, bForceAdmin = false;
		for (QString::const_iterator strParam = args->begin(); strParam != args->end(); ++strParam)
		{
			if ((*strParam).Equals("-elevate"))
				bRunElevated = true;
			else if ((*strParam).Equals("-forceadmin"))
				bForceAdmin = true;
		}

		// Check if the program can write to the program dir
		if (!FileUtil::IsDirWriteable(Path::GetDirectoryName(Application::ExecutablePath)))
			bForceAdmin = true;

		// If needed run as elevated process
		if (bForceAdmin && !bRunElevated)
		{
			try
			{
				Process *p = new Process();
				p->StartInfo->FileName = Application::ExecutablePath;
				p->StartInfo->Arguments = "-elevate";
				p->StartInfo->Verb = "runas";
				p->Start();
				return;
			}
			catch (...)
			{
			}
		}

		System::Windows::Forms::Application::EnableVisualStyles();
	#if !defined(DEBUG)
		if (!mySingleInstanceMutex->WaitOne(0, false))
		{
			if (System::Windows::Forms::DialogResult::Yes != MessageBox::Show("Running MeXgui instance detected!\n\rThere's not really much point in running multiple copies of MeXgui, and it can cause problems.\n\rDo You still want to run yet another MeXgui instance?", "Running MeXgui instance detected", MessageBoxButtons::YesNo, MessageBoxIcon::Warning))
				return;
		}
	#endif
		Application::ThreadException += new System::Threading::ThreadExceptionEventHandler(&MainForm::Application_ThreadException);
		AppDomain::CurrentDomain::UnhandledException += new UnhandledExceptionEventHandler(&MainForm::CurrentDomain_UnhandledException);
		CommandlineParser *parser = new CommandlineParser();
		parser->Parse(args);
		MainForm *mainForm = new MainForm();
		mainForm->handleCommandline(parser);
		if (parser->start)
			Application::Run(mainForm);
	}

	void MainForm::CurrentDomain_UnhandledException(QObject *sender, QEvent *e)
	{
		HandleUnhandledException(static_cast<std::exception>(e->ExceptionObject));
	}

	void MainForm::HandleUnhandledException(std::exception &e)
	{
		LogItem *i = MainForm::Instance->getLog()->Error("Unhandled error");
		i->LogValue("Exception message", e.what());
		i->LogValue("Stacktrace", e.StackTrace);
		i->LogValue("Inner exception", e.InnerException);
		for (unknown::const_iterator info = e.Data.begin(); info != e.Data.end(); ++info)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			i->LogValue((*info)->Key->ToString(), (*info)->Value);

		MessageBox::Show("MeXgui encountered a fatal error and may not be able to proceed. Reason: " + e.what(), "Fatal error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	void MainForm::Application_ThreadException(QObject *sender, QEvent *e) //here was system threading event, may be buggy
	{
		HandleUnhandledException(e->Exception);
	}

	void MainForm::runRestarter()
	{
		if (filesToReplace.Keys->Count == 0)
			return;

		Process *proc = new Process();
		ProcessStartInfo *pstart = new ProcessStartInfo();
		pstart->FileName = Path::Combine(Application::StartupPath, "updatecopier.exe");
		for (QQMap<QString, CommandlineUpgradeData*>::const_iterator file = filesToReplace.begin(); file != filesToReplace.end(); ++file)
		{
			pstart->Arguments += QString::Format("--component \"{0}\" \"{1}\" ", file->first, filesToReplace[file->first]->newUploadDate);
			for (int i = 0; i < filesToReplace[file]->filename->size(); i++)
			{
				pstart->Arguments += QString::Format("\"{0}\" \"{1}\" ", filesToReplace[file->first]->filename[i], filesToReplace[file->first]->tempFilename[i]);
			}
		}
		if (restart)
			pstart->Arguments += "--restart";
		else
			pstart->Arguments += "--no-restart";

		// Check if the program can write to the program dir
		if (FileUtil::IsDirWriteable(Path::GetDirectoryName(Application::ExecutablePath)))
		{
			pstart->CreateNoWindow = true;
			pstart->UseShellExecute = false;
		}
		else
		{
			// Need admin permissions
			proc->StartInfo->Verb = "runas";
			pstart->UseShellExecute = true;
		}

		proc->StartInfo = pstart;
		try
		{
			if (!proc->Start())
				MessageBox::Show("Couldn't run updater.", "Couldn't run updater.", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		catch (...)
		{
			MessageBox::Show("Couldn't run updater.", "Couldn't run updater.", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	const MeXgui::core::details::PackageSystem &MainForm::getPackageSystem() const
	{
		return packageSystem;
	}

	const bool &MainForm::getRestart() const
	{
		return restart;
	}

	void MainForm::setRestart(const bool &value)
	{
		restart = value;
	}

	const MeXgui::DialogManager &MainForm::getDialogManager() const
	{
		return dialogManager;
	}

	const QString &MainForm::getMeXguiPath() const
	{
		return this->path;
	}

	void MainForm::ClosePlayer()
	{
		videoEncodingComponent1->ClosePlayer();
	}

	void MainForm::hidePlayer()
	{
		videoEncodingComponent1->hidePlayer();
	}

	void MainForm::showPlayer()
	{
		videoEncodingComponent1->showPlayer();
	}

	void MainForm::showAllWorkers_Click(QObject *sender, QEvent *e)
	{
		getJobs()->ShowAllWorkers();
	}

	void MainForm::hideAllWorkers_Click(QObject *sender, QEvent *e)
	{
		getJobs()->HideAllWorkers();
	}

	void MainForm::showAllWorkers_Popup(QObject *sender, QEvent *e)
	{
		viewSummary->Checked = getJobs()->getSummaryVisible();

		QVector<Pair<QString, bool>*> workers = getJobs()->ListWorkers();
		workersMenu->MenuItems->Clear();
		workersMenu->MenuItems->Add(showAllWorkers);
		workersMenu->MenuItems->Add(hideAllWorkers);
		workersMenu->MenuItems->Add(separator);

		for (QVector<Pair<QString, bool>*>::const_iterator p = workers.begin(); p != workers.end(); ++p)
		{
			MenuItem *i = new MenuItem((*p)->fst);
			i->Checked = (*p)->snd;
			i->Click += new EventHandler(this, &MainForm::mnuWorker_Click);
			workersMenu->MenuItems->Add(i);
		}

		if (workers.empty())
		{
			MenuItem *i = new MenuItem("(No workers to show)");
			i->Enabled = false;
			workersMenu->MenuItems->Add(i);
		}
	}

	void MainForm::mnuWorker_Click(QObject *sender1, QEvent *e)
	{
		MenuItem *sender = static_cast<MenuItem*>(sender1);
		getJobs()->SetWorkerVisible(sender->Text, !sender->Checked);
	}

	void MainForm::viewSummary_Click(QObject *sender, QEvent *e)
	{
		if (viewSummary->Checked)
		{
			viewSummary->Checked = false;
			getJobs()->HideSummary();
		}
		else
		{
			viewSummary->Checked = true;
			getJobs()->ShowSummary();
		}
	}

	void MainForm::createNewWorker_Click(QObject *sender, QEvent *e)
	{
		getJobs()->RequestNewWorker();
	}

	void MainForm::showAllProgressWindows_Click(QObject *sender, QEvent *e)
	{
		getJobs()->ShowAllProcessWindows();
	}

	void MainForm::hideAllProgressWindows_Click(QObject *sender, QEvent *e)
	{
		getJobs()->HideAllProcessWindows();
	}

	void MainForm::mnuForum_Click(QObject *sender, QEvent *e)
	{
		System::Diagnostics::Process::Start("http://forum.doom9.org/showthread.php?p=1677712");
	}

	void MainForm::mnuHome_Click(QObject *sender, QEvent *e)
	{
		System::Diagnostics::Process::Start("http://mexgui.wordpress.com/");
	}

	void MainForm::mnuBugTracker_Click(QObject *sender, QEvent *e)
	{
		System::Diagnostics::Process::Start("https://github.com/mexgui/MeXgui/issues");
	}

	void MainForm::mnuFeaturesReq_Click(QObject *sender, QEvent *e)
	{
		System::Diagnostics::Process::Start("https://github.com/mexgui/MeXgui/issues");
	}

	void MainForm::mnuDoc_Click(QObject *sender, QEvent *e)
	{
		System::Diagnostics::Process::Start("https://github.com/mexgui/MeXgui/wiki");
	}

	void MainForm::mnuOptionsSettings_Click(QObject *sender, QEvent *e)
	{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (SettingsForm sform = new SettingsForm())
		SettingsForm *sform = new SettingsForm();
		try
		{
			sform->setSettings(this->settings);
			if (sform->show() == System::Windows::Forms::DialogResult::OK)
			{
				this->settings = sform->getSettings();
				this->saveSettings();
				getJobs()->showAfterEncodingStatus(settings);
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (sform != 0)
				sform.Dispose();
		}
	}

	void MainForm::MainForm_Shown(QObject *sender, QEvent *e)
	{
		this->ClientSize = settings->getMainFormSize();

		if ((Environment::OSVersion::Version->Major == 6 && Environment::OSVersion::Version::Minor >= 1) || Environment::OSVersion::Version::Major > 6)
			taskbarItem = static_cast<ITaskbarList3*>(new ProgressTaskbar());

		getVersionInformation();

		if (_updateLog == 0)
			_updateLog = getLog()->Info("Update detection");
		if (settings->getAutoUpdate())
			startUpdateCheck();
		else
			_updateLog->LogEvent("Automatic update is disabled");

		if (settings->getAutoStartQueueStartup())
			jobControl1->StartAll(false);
	}

	void MainForm::startUpdateCheck()
	{
		// Need a seperate thread to run the updater to stop internet lookups from freezing the app.
		Thread *updateCheck = new Thread(new ThreadStart(beginUpdateCheck));
		updateCheck->IsBackground = true;
		updateCheck->Start();
	}

	void MainForm::getVersionInformation()
	{
		LogItem *i = getLog()->Info("Versions");
	#if defined(x86)
		i->LogValue("MeXgui", (new System::Version(Application::ProductVersion))->Build);
	#endif
	#if defined(x64)
		i->LogValue("MeXgui Version ", (new System::Version(Application::ProductVersion))->Build + " x64");
	#endif
		i->LogValue("Operating System", QString::Format("{0}{1} ({2}.{3}.{4}.{5})", OSInfo::GetOSName(), OSInfo::GetOSServicePack(), OSInfo::getOSMajorVersion(), OSInfo::getOSMinorVersion(), OSInfo::getOSRevisionVersion(), OSInfo::getOSBuildVersion()));
		i->LogValue(".Net Framework", QString::Format("{0}", OSInfo::DotNetVersionFormated(OSInfo::GetDotNetVersion())));

		VideoUtil::getAvisynthVersion(i);

		QString devil = Path::Combine(Path::GetDirectoryName(Application::ExecutablePath), "devil.dll");
		if (File::Exists(devil))
			FileUtil::GetFileInformation("DevIL", devil, i);
		FileUtil::GetFileInformation("AvisynthWrapper", Path::GetDirectoryName(Application::ExecutablePath) + "\\AvisynthWrapper.dll", i);

		// check if Haali Matroska Splitter is properly installed
		try
		{
			// A28F324B-DDC5-4999-AA25-D3A7E25EF7A8 = Haali Matroska Splitter x86
			// 55DA30FC-F16B-49FC-BAA5-AE59FC65F82D = Haali Matroska Splitter x64
	#if defined(x86)
			Type *comtype = Type::GetTypeFromCLSID(new Guid("A28F324B-DDC5-4999-AA25-D3A7E25EF7A8"));
			QString fileName = "splitter.ax";
	#endif
	#if defined(x64)
			Type *comtype = Type::GetTypeFromCLSID(new Guid("55DA30FC-F16B-49FC-BAA5-AE59FC65F82D"));
			QString fileName = "splitter.x64.ax";
	#endif
			object *comobj = Activator::CreateInstance(comtype);
			FileUtil::GetFileInformation("Haali Matroska Splitter", Path::Combine(MeXguiSettings::getHaaliMSPath(), fileName), i);
		}
		catch (std::exception &e1)
		{
			i->LogEvent("Haali Matroska Splitter not installed properly.", Warning);
			i->LogEvent("Therefore DSS2() and certain functions of FFVideoSource() and the HD Streams Extractor may also not work.", Warning);
			i->LogEvent("Please download and install it from http://haali.su/mkv/", Warning);
		}

		FileUtil::GetFileInformation("Haali DSS2", Path::Combine(MeXguiSettings::getHaaliMSPath(), "avss.dll"), i);
		FileUtil::GetFileInformation("ICSharpCode.SharpZipLib", Path::GetDirectoryName(Application::ExecutablePath) + "\\ICSharpCode.SharpZipLib.dll", i);
		FileUtil::GetFileInformation("LinqBridge", Path::GetDirectoryName(Application::ExecutablePath) + "\\LinqBridge.dll", i);
		FileUtil::GetFileInformation("MediaInfo", Path::GetDirectoryName(Application::ExecutablePath) + "\\MediaInfo.dll", i);
		FileUtil::GetFileInformation("MediaInfoWrapper", Path::GetDirectoryName(Application::ExecutablePath) + "\\MediaInfoWrapper.dll", i);
		FileUtil::GetFileInformation("MessageBoxExLib", Path::GetDirectoryName(Application::ExecutablePath) + "\\MessageBoxExLib.dll", i);
		FileUtil::GetFileInformation("SevenZipSharp", Path::GetDirectoryName(Application::ExecutablePath) + "\\SevenZipSharp.dll", i);
		FileUtil::GetFileInformation("7z", Path::GetDirectoryName(Application::ExecutablePath) + "\\7z.dll", i);
	}

	void MainForm::setOverlayIcon(Icon *oIcon)
	{
		if ((Environment::OSVersion::Version->Major == 6 && Environment::OSVersion::Version->Minor == 0) || Environment::OSVersion::Version::Major < 6)
			return;

		if (oIcon == 0)
		{
			// remove the overlay icon
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Util::ThreadSafeRun(this, delegate
			{
				taskbarItem->SetOverlayIcon(this->Handle, void*::Zero, 0);
			}
		   );
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete taskbarIcon;
			return;
		}

		if (taskbarIcon != 0 && oIcon->Handle == taskbarIcon->Handle)
			return;

		if (oIcon == System::Drawing::SystemIcons::Warning && taskbarIcon == System::Drawing::SystemIcons::Error)
			return;

		if (taskbarItem != 0)
		{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Util::ThreadSafeRun(this, delegate
			{
				taskbarItem->SetOverlayIcon(this->Handle, oIcon->Handle, 0);
			}
		   );
			taskbarIcon = oIcon;
		}
	}

	bool MainForm::AskToInstallComponents(bool bRestartRequired)
	{
		QString strQuestionText;

		if (bRestartRequired)
			strQuestionText = "MeXgui cannot find at least one required component. Without these components, MeXgui will not run properly (e.g. no job can be started).\n\nDo you want to restart MeXgui now?";
		else
			strQuestionText = "MeXgui cannot find at least one required component. Without these components, MeXgui will not run properly (e.g. no job can be started).\n\nDo you want to search now online for updates?";

		if (MessageBox::Show(strQuestionText, "MeXgui component(s) missing", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes)
			return true;
		else
			return false;
	}

	void MainForm::OneClickEncButton_Click(QObject *sender, QEvent *e)
	{
		RunTool("one_click");
	}

	void MainForm::HelpButton_Click(QObject *sender, QEvent *e)
	{
		System::Diagnostics::Process::Start("http://mewiki.project357.com/wiki/Main_Page");
	}

	void MainForm::menuItem5_Click(QObject *sender, QEvent *e)
	{
		FileIndexerWindow *d2vc = new FileIndexerWindow(this);
		d2vc->Show();
	}

	void MainForm::MainForm_Move(QObject *sender, QEvent *e)
	{
		if (this->WindowState != FormWindowState::Minimized && this->Visible == true)
			settings->setMainFormLocation(this->Location);
	}

	void MainForm::MainForm_Resize(QObject *sender, QEvent *e)
	{
		if (this->WindowState != FormWindowState::Minimized && this->Visible == true)
			settings->setMainFormSize(this->ClientSize);
	}

	void MainForm::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void MainForm::InitializeComponent()
	{
		this->components = new System::ComponentModel::Container();
		this->tabControl1 = new System::Windows::Forms::TabControl();
		this->inputTab = new System::Windows::Forms::TabPage();
		this->splitContainer2 = new System::Windows::Forms::SplitContainer();
		this->videoEncodingComponent1 = new MeXgui::VideoEncodingComponent();
		this->audioEncodingComponent1 = new MeXgui::AudioEncodingComponent();
		this->splitContainer1 = new System::Windows::Forms::SplitContainer();
		this->flowLayoutPanel1 = new System::Windows::Forms::FlowLayoutPanel();
		this->resetButton = new QPushButton;
		this->helpButton1 = new QPushButton;
		this->flowLayoutPanel2 = new System::Windows::Forms::FlowLayoutPanel();
		this->autoEncodeButton = new QPushButton;
		this->OneClickEncButton = new QPushButton;
		this->tabPage2 = new System::Windows::Forms::TabPage();
		this->jobControl1 = new MeXgui::core::details::JobControl();
		this->logTab = new System::Windows::Forms::TabPage();
		this->logTree1 = new MeXgui::core::gui::LogTree();
		this->mnuMuxers = new System::Windows::Forms::MenuItem();
		this->mnuToolsAdaptiveMuxer = new System::Windows::Forms::MenuItem();
		this->mainMenu1 = new System::Windows::Forms::MainMenu(this->components);
		this->mnuFile = new System::Windows::Forms::MenuItem();
		this->mnuFileOpen = new System::Windows::Forms::MenuItem();
		this->mnuFileImport = new System::Windows::Forms::MenuItem();
		this->mnuFileExport = new System::Windows::Forms::MenuItem();
		this->mnuFileExit = new System::Windows::Forms::MenuItem();
		this->mnuView = new System::Windows::Forms::MenuItem();
		this->progressMenu = new System::Windows::Forms::MenuItem();
		this->showAllProgressWindows = new System::Windows::Forms::MenuItem();
		this->hideAllProgressWindows = new System::Windows::Forms::MenuItem();
		this->separator2 = new System::Windows::Forms::MenuItem();
		this->menuItem7 = new System::Windows::Forms::MenuItem();
		this->mnuViewMinimizeToTray = new System::Windows::Forms::MenuItem();
		this->menuItem1 = new System::Windows::Forms::MenuItem();
		this->createNewWorker = new System::Windows::Forms::MenuItem();
		this->menuItem6 = new System::Windows::Forms::MenuItem();
		this->workersMenu = new System::Windows::Forms::MenuItem();
		this->showAllWorkers = new System::Windows::Forms::MenuItem();
		this->hideAllWorkers = new System::Windows::Forms::MenuItem();
		this->separator = new System::Windows::Forms::MenuItem();
		this->menuItem2 = new System::Windows::Forms::MenuItem();
		this->menuItem3 = new System::Windows::Forms::MenuItem();
		this->viewSummary = new System::Windows::Forms::MenuItem();
		this->mnuTools = new System::Windows::Forms::MenuItem();
		this->mnutoolsD2VCreator = new System::Windows::Forms::MenuItem();
		this->mnuOptions = new System::Windows::Forms::MenuItem();
		this->mnuOptionsSettings = new System::Windows::Forms::MenuItem();
		this->mnuHelp = new System::Windows::Forms::MenuItem();
		this->mnuChangelog = new System::Windows::Forms::MenuItem();
		this->mnuDoc = new System::Windows::Forms::MenuItem();
		this->mnuWebsite = new System::Windows::Forms::MenuItem();
		this->mnuHome = new System::Windows::Forms::MenuItem();
		this->mnuForum = new System::Windows::Forms::MenuItem();
		this->mnuBugTracker = new System::Windows::Forms::MenuItem();
		this->mnuFeaturesReq = new System::Windows::Forms::MenuItem();
		this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
		this->saveFileDialog = new System::Windows::Forms::SaveFileDialog();
		this->trayIcon = new System::Windows::Forms::NotifyIcon(this->components);
		this->trayMenu = new System::Windows::Forms::ContextMenuStrip(this->components);
		this->openMeXguiToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
		this->toolStripSeparator1 = new System::Windows::Forms::ToolStripSeparator();
		this->exitMeXguiToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
		this->tabControl1->SuspendLayout();
		this->inputTab->SuspendLayout();
		this->splitContainer2->Panel1->SuspendLayout();
		this->splitContainer2->Panel2->SuspendLayout();
		this->splitContainer2->SuspendLayout();
		this->splitContainer1->Panel1->SuspendLayout();
		this->splitContainer1->Panel2->SuspendLayout();
		this->splitContainer1->SuspendLayout();
		this->flowLayoutPanel1->SuspendLayout();
		this->flowLayoutPanel2->SuspendLayout();
		this->tabPage2->SuspendLayout();
		this->logTab->SuspendLayout();
		this->trayMenu->SuspendLayout();
		this->SuspendLayout();
		// 
		// tabControl1
		// 
		this->tabControl1->Controls->Add(this->inputTab);
		this->tabControl1->Controls->Add(this->tabPage2);
		this->tabControl1->Controls->Add(this->logTab);
		this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tabControl1->Location = new System::Drawing::Point(0, 0);
		this->tabControl1->Name = "tabControl1";
		this->tabControl1->SelectedIndex = 0;
		this->tabControl1->Size = new System::Drawing::Size(508, 499);
		this->tabControl1->TabIndex = 0;
		// 
		// inputTab
		// 
		this->inputTab->BackColor = System::Drawing::Color::Transparent;
		this->inputTab->Controls->Add(this->splitContainer2);
		this->inputTab->Controls->Add(this->splitContainer1);
		this->inputTab->Location = new System::Drawing::Point(4, 22);
		this->inputTab->Name = "inputTab";
		this->inputTab->Size = new System::Drawing::Size(500, 473);
		this->inputTab->TabIndex = 0;
		this->inputTab->Text = "Input";
		this->inputTab->UseVisualStyleBackColor = true;
		// 
		// splitContainer2
		// 
		this->splitContainer2->BackColor = System::Drawing::SystemColors::ControlLight;
		this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
		this->splitContainer2->IsSplitterFixed = true;
		this->splitContainer2->Location = new System::Drawing::Point(0, 0);
		this->splitContainer2->Name = "splitContainer2";
		this->splitContainer2->Orientation = System::Windows::Forms::Orientation::Horizontal;
		// 
		// splitContainer2.Panel1
		// 
		this->splitContainer2->Panel1->Controls->Add(this->videoEncodingComponent1);
		this->splitContainer2->Panel1MinSize = 168;
		// 
		// splitContainer2.Panel2
		// 
		this->splitContainer2->Panel2->Controls->Add(this->audioEncodingComponent1);
		this->splitContainer2->Panel2MinSize = 150;
		this->splitContainer2->Size = new System::Drawing::Size(500, 441);
		this->splitContainer2->SplitterDistance = 168;
		this->splitContainer2->TabIndex = 4;
		// 
		// videoEncodingComponent1
		// 
		this->videoEncodingComponent1->BackColor = System::Drawing::SystemColors::Control;
		this->videoEncodingComponent1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->videoEncodingComponent1->setFileType("");
		this->videoEncodingComponent1->Location = new System::Drawing::Point(0, 0);
		this->videoEncodingComponent1->MinimumSize = new System::Drawing::Size(500, 168);
		this->videoEncodingComponent1->Name = "videoEncodingComponent1";
		this->videoEncodingComponent1->setPrerenderJob(false);
		this->videoEncodingComponent1->Size = new System::Drawing::Size(500, 168);
		this->videoEncodingComponent1->TabIndex = 0;
		this->videoEncodingComponent1->setVideoInput("");
		this->videoEncodingComponent1->setVideoOutput("");
		// 
		// audioEncodingComponent1
		// 
		this->audioEncodingComponent1->AutoScroll = true;
		this->audioEncodingComponent1->BackColor = System::Drawing::SystemColors::Control;
		this->audioEncodingComponent1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->audioEncodingComponent1->Location = new System::Drawing::Point(0, 0);
		this->audioEncodingComponent1->MinimumSize = new System::Drawing::Size(400, 192);
		this->audioEncodingComponent1->Name = "audioEncodingComponent1";
		this->audioEncodingComponent1->Size = new System::Drawing::Size(500, 269);
		this->audioEncodingComponent1->TabIndex = 1;
		// 
		// splitContainer1
		// 
		this->splitContainer1->BackColor = System::Drawing::SystemColors::Control;
		this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->splitContainer1->IsSplitterFixed = true;
		this->splitContainer1->Location = new System::Drawing::Point(0, 441);
		this->splitContainer1->Name = "splitContainer1";
		// 
		// splitContainer1.Panel1
		// 
		this->splitContainer1->Panel1->Controls->Add(this->flowLayoutPanel1);
		// 
		// splitContainer1.Panel2
		// 
		this->splitContainer1->Panel2->Controls->Add(this->flowLayoutPanel2);
		this->splitContainer1->Size = new System::Drawing::Size(500, 32);
		this->splitContainer1->SplitterDistance = 244;
		this->splitContainer1->TabIndex = 3;
		// 
		// flowLayoutPanel1
		// 
		this->flowLayoutPanel1->BackColor = System::Drawing::SystemColors::Control;
		this->flowLayoutPanel1->Controls->Add(this->resetButton);
		this->flowLayoutPanel1->Controls->Add(this->helpButton1);
		this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->flowLayoutPanel1->Location = new System::Drawing::Point(0, 0);
		this->flowLayoutPanel1->Name = "flowLayoutPanel1";
		this->flowLayoutPanel1->Size = new System::Drawing::Size(244, 32);
		this->flowLayoutPanel1->TabIndex = 0;
		// 
		// resetButton
		// 
		this->resetButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->resetButton->AutoSize = true;
		this->resetButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->resetButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->resetButton->Location = new System::Drawing::Point(3, 3);
		this->resetButton->Name = "resetButton";
		this->resetButton->Size = new System::Drawing::Size(45, 23);
		this->resetButton->TabIndex = 4;
		this->resetButton->Text = "Reset";
		this->resetButton->Click += new System::EventHandler(this, &MainForm::resetButton_Click);
		// 
		// helpButton1
		// 
		this->helpButton1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(54, 3);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 5;
		this->helpButton1->Text = "Help";
		this->helpButton1->Click += new System::EventHandler(this, &MainForm::HelpButton_Click);
		// 
		// flowLayoutPanel2
		// 
		this->flowLayoutPanel2->AutoSize = true;
		this->flowLayoutPanel2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->flowLayoutPanel2->BackColor = System::Drawing::SystemColors::Control;
		this->flowLayoutPanel2->Controls->Add(this->autoEncodeButton);
		this->flowLayoutPanel2->Controls->Add(this->OneClickEncButton);
		this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
		this->flowLayoutPanel2->FlowDirection = System::Windows::Forms::FlowDirection::RightToLeft;
		this->flowLayoutPanel2->Location = new System::Drawing::Point(0, 0);
		this->flowLayoutPanel2->Name = "flowLayoutPanel2";
		this->flowLayoutPanel2->Size = new System::Drawing::Size(252, 32);
		this->flowLayoutPanel2->TabIndex = 5;
		// 
		// autoEncodeButton
		// 
		this->autoEncodeButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->autoEncodeButton->AutoSize = true;
		this->autoEncodeButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->autoEncodeButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->autoEncodeButton->Location = new System::Drawing::Point(174, 3);
		this->autoEncodeButton->Name = "autoEncodeButton";
		this->autoEncodeButton->Size = new System::Drawing::Size(75, 23);
		this->autoEncodeButton->TabIndex = 2;
		this->autoEncodeButton->Text = "AutoEncode";
		this->autoEncodeButton->Click += new System::EventHandler(this, &MainForm::autoEncodeButton_Click);
		// 
		// OneClickEncButton
		// 
		this->OneClickEncButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->OneClickEncButton->AutoSize = true;
		this->OneClickEncButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->OneClickEncButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->OneClickEncButton->Location = new System::Drawing::Point(106, 3);
		this->OneClickEncButton->Name = "OneClickEncButton";
		this->OneClickEncButton->Size = new System::Drawing::Size(62, 23);
		this->OneClickEncButton->TabIndex = 3;
		this->OneClickEncButton->Text = "One-Click";
		this->OneClickEncButton->Click += new System::EventHandler(this, &MainForm::OneClickEncButton_Click);
		// 
		// tabPage2
		// 
		this->tabPage2->Controls->Add(this->jobControl1);
		this->tabPage2->Location = new System::Drawing::Point(4, 22);
		this->tabPage2->Name = "tabPage2";
		this->tabPage2->Size = new System::Drawing::Size(500, 473);
		this->tabPage2->TabIndex = 12;
		this->tabPage2->Text = "Queue";
		this->tabPage2->UseVisualStyleBackColor = true;
		// 
		// jobControl1
		// 
		this->jobControl1->BackColor = System::Drawing::SystemColors::Control;
		this->jobControl1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->jobControl1->Location = new System::Drawing::Point(0, 0);
		this->jobControl1->Name = "jobControl1";
		this->jobControl1->Size = new System::Drawing::Size(500, 473);
		this->jobControl1->TabIndex = 0;
		// 
		// logTab
		// 
		this->logTab->Controls->Add(this->logTree1);
		this->logTab->Location = new System::Drawing::Point(4, 22);
		this->logTab->Name = "logTab";
		this->logTab->Size = new System::Drawing::Size(500, 473);
		this->logTab->TabIndex = 13;
		this->logTab->Text = "Log";
		this->logTab->UseVisualStyleBackColor = true;
		// 
		// logTree1
		// 
		this->logTree1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->logTree1->Location = new System::Drawing::Point(0, 0);
		this->logTree1->Name = "logTree1";
		this->logTree1->Size = new System::Drawing::Size(500, 473);
		this->logTree1->TabIndex = 0;
		// 
		// mnuMuxers
		// 
		this->mnuMuxers->Index = 0;
		this->mnuMuxers->MenuItems->AddRange(new System::Windows::Forms::MenuItem[1] {this->mnuToolsAdaptiveMuxer});
		this->mnuMuxers->Text = "Muxer";
		// 
		// mnuToolsAdaptiveMuxer
		// 
		this->mnuToolsAdaptiveMuxer->Index = 0;
		this->mnuToolsAdaptiveMuxer->Text = "Adaptive Muxer";
		this->mnuToolsAdaptiveMuxer->Click += new System::EventHandler(this, &MainForm::mnuToolsAdaptiveMuxer_Click);
		// 
		// mainMenu1
		// 
		this->mainMenu1->MenuItems->AddRange(new System::Windows::Forms::MenuItem[6] {this->mnuFile, this->mnuView, this->menuItem1, this->mnuTools, this->mnuOptions, this->mnuHelp});
		// 
		// mnuFile
		// 
		this->mnuFile->Index = 0;
		this->mnuFile->MenuItems->AddRange(new System::Windows::Forms::MenuItem[4] {this->mnuFileOpen, this->mnuFileImport, this->mnuFileExport, this->mnuFileExit});
		this->mnuFile->Text = "&File";
		// 
		// mnuFileOpen
		// 
		this->mnuFileOpen->Index = 0;
		this->mnuFileOpen->Shortcut = System::Windows::Forms::Shortcut::CtrlO;
		this->mnuFileOpen->Text = "&Open";
		this->mnuFileOpen->Click += new System::EventHandler(this, &MainForm::mnuFileOpen_Click);
		// 
		// mnuFileImport
		// 
		this->mnuFileImport->Index = 1;
		this->mnuFileImport->Shortcut = System::Windows::Forms::Shortcut::CtrlI;
		this->mnuFileImport->Text = "&Import Presets";
		this->mnuFileImport->Click += new System::EventHandler(this, &MainForm::mnuFileImport_Click);
		// 
		// mnuFileExport
		// 
		this->mnuFileExport->Index = 2;
		this->mnuFileExport->Shortcut = System::Windows::Forms::Shortcut::CtrlE;
		this->mnuFileExport->Text = "&Export Presets";
		this->mnuFileExport->Click += new System::EventHandler(this, &MainForm::mnuFileExport_Click);
		// 
		// mnuFileExit
		// 
		this->mnuFileExit->Index = 3;
		this->mnuFileExit->Shortcut = System::Windows::Forms::Shortcut::CtrlX;
		this->mnuFileExit->Text = "E&xit";
		this->mnuFileExit->Click += new System::EventHandler(this, &MainForm::mnuFileExit_Click);
		// 
		// mnuView
		// 
		this->mnuView->Index = 1;
		this->mnuView->MenuItems->AddRange(new System::Windows::Forms::MenuItem[2] {this->progressMenu, this->mnuViewMinimizeToTray});
		this->mnuView->Text = "&View";
		this->mnuView->Popup += new System::EventHandler(this, &MainForm::mnuView_Popup);
		// 
		// progressMenu
		// 
		this->progressMenu->Index = 0;
		this->progressMenu->MenuItems->AddRange(new System::Windows::Forms::MenuItem[4] {this->showAllProgressWindows, this->hideAllProgressWindows, this->separator2, this->menuItem7});
		this->progressMenu->Text = "&Process Status";
		// 
		// showAllProgressWindows
		// 
		this->showAllProgressWindows->Index = 0;
		this->showAllProgressWindows->Text = "Show all";
		this->showAllProgressWindows->Click += new System::EventHandler(this, &MainForm::showAllProgressWindows_Click);
		// 
		// hideAllProgressWindows
		// 
		this->hideAllProgressWindows->Index = 1;
		this->hideAllProgressWindows->Text = "Hide all";
		this->hideAllProgressWindows->Click += new System::EventHandler(this, &MainForm::hideAllProgressWindows_Click);
		// 
		// separator2
		// 
		this->separator2->Index = 2;
		this->separator2->Text = "-";
		// 
		// menuItem7
		// 
		this->menuItem7->Index = 3;
		this->menuItem7->Text = "(List of progress windows goes here)";
		// 
		// mnuViewMinimizeToTray
		// 
		this->mnuViewMinimizeToTray->Index = 1;
		this->mnuViewMinimizeToTray->Shortcut = System::Windows::Forms::Shortcut::CtrlM;
		this->mnuViewMinimizeToTray->Text = "&Minimize to Tray";
		this->mnuViewMinimizeToTray->Click += new System::EventHandler(this, &MainForm::mnuViewMinimizeToTray_Click);
		// 
		// menuItem1
		// 
		this->menuItem1->Index = 2;
		this->menuItem1->MenuItems->AddRange(new System::Windows::Forms::MenuItem[4] {this->createNewWorker, this->menuItem6, this->workersMenu, this->viewSummary});
		this->menuItem1->Text = "Workers";
		this->menuItem1->Popup += new System::EventHandler(this, &MainForm::showAllWorkers_Popup);
		// 
		// createNewWorker
		// 
		this->createNewWorker->Index = 0;
		this->createNewWorker->Text = "Create new worker";
		this->createNewWorker->Click += new System::EventHandler(this, &MainForm::createNewWorker_Click);
		// 
		// menuItem6
		// 
		this->menuItem6->Index = 1;
		this->menuItem6->Text = "-";
		// 
		// workersMenu
		// 
		this->workersMenu->Index = 2;
		this->workersMenu->MenuItems->AddRange(new System::Windows::Forms::MenuItem[5] {this->showAllWorkers, this->hideAllWorkers, this->separator, this->menuItem2, this->menuItem3});
		this->workersMenu->Text = "Workers";
		// 
		// showAllWorkers
		// 
		this->showAllWorkers->Index = 0;
		this->showAllWorkers->Text = "Show all";
		this->showAllWorkers->Click += new System::EventHandler(this, &MainForm::showAllWorkers_Click);
		// 
		// hideAllWorkers
		// 
		this->hideAllWorkers->Index = 1;
		this->hideAllWorkers->Text = "Hide all";
		this->hideAllWorkers->Click += new System::EventHandler(this, &MainForm::hideAllWorkers_Click);
		// 
		// separator
		// 
		this->separator->Index = 2;
		this->separator->Text = "-";
		// 
		// menuItem2
		// 
		this->menuItem2->Index = 3;
		this->menuItem2->Text = "(List of workers goes here)";
		// 
		// menuItem3
		// 
		this->menuItem3->Index = 4;
		this->menuItem3->Text = "ao";
		// 
		// viewSummary
		// 
		this->viewSummary->Index = 3;
		this->viewSummary->Text = "Worker summary";
		this->viewSummary->Click += new System::EventHandler(this, &MainForm::viewSummary_Click);
		// 
		// mnuTools
		// 
		this->mnuTools->Index = 3;
		this->mnuTools->MenuItems->AddRange(new System::Windows::Forms::MenuItem[2] {this->mnuMuxers, this->mnutoolsD2VCreator});
		this->mnuTools->Shortcut = System::Windows::Forms::Shortcut::CtrlT;
		this->mnuTools->Text = "&Tools";
		// 
		// mnutoolsD2VCreator
		// 
		this->mnutoolsD2VCreator->Index = 1;
		this->mnutoolsD2VCreator->Shortcut = System::Windows::Forms::Shortcut::CtrlF2;
		this->mnutoolsD2VCreator->Text = "File Indexer";
		this->mnutoolsD2VCreator->Click += new System::EventHandler(this, &MainForm::menuItem5_Click);
		// 
		// mnuOptions
		// 
		this->mnuOptions->Index = 4;
		this->mnuOptions->MenuItems->AddRange(new System::Windows::Forms::MenuItem[1] {this->mnuOptionsSettings});
		this->mnuOptions->Text = "&Options";
		// 
		// mnuOptionsSettings
		// 
		this->mnuOptionsSettings->Index = 0;
		this->mnuOptionsSettings->Shortcut = System::Windows::Forms::Shortcut::CtrlS;
		this->mnuOptionsSettings->Text = "Settings";
		this->mnuOptionsSettings->Click += new System::EventHandler(this, &MainForm::mnuOptionsSettings_Click);
		// 
		// mnuHelp
		// 
		this->mnuHelp->Index = 5;
		this->mnuHelp->MenuItems->AddRange(new System::Windows::Forms::MenuItem[3] {this->mnuChangelog, this->mnuDoc, this->mnuWebsite});
		this->mnuHelp->Text = "&Help";
		// 
		// mnuChangelog
		// 
		this->mnuChangelog->Index = 0;
		this->mnuChangelog->Text = "Changelog";
		this->mnuChangelog->Click += new System::EventHandler(this, &MainForm::mnuChangelog_Click);
		// 
		// mnuDoc
		// 
		this->mnuDoc->Index = 1;
		this->mnuDoc->Text = "Wiki - User Guides";
		this->mnuDoc->Click += new System::EventHandler(this, &MainForm::mnuDoc_Click);
		// 
		// mnuWebsite
		// 
		this->mnuWebsite->Index = 2;
		this->mnuWebsite->MenuItems->AddRange(new System::Windows::Forms::MenuItem[4] {this->mnuHome, this->mnuForum, this->mnuBugTracker, this->mnuFeaturesReq});
		this->mnuWebsite->Text = "Website";
		// 
		// mnuHome
		// 
		this->mnuHome->Index = 0;
		this->mnuHome->Text = "Homepage";
		this->mnuHome->Click += new System::EventHandler(this, &MainForm::mnuHome_Click);
		// 
		// mnuForum
		// 
		this->mnuForum->Index = 1;
		this->mnuForum->Text = "Forum";
		this->mnuForum->Click += new System::EventHandler(this, &MainForm::mnuForum_Click);
		// 
		// mnuBugTracker
		// 
		this->mnuBugTracker->Index = 2;
		this->mnuBugTracker->Text = "Bugs Tracker";
		this->mnuBugTracker->Click += new System::EventHandler(this, &MainForm::mnuBugTracker_Click);
		// 
		// mnuFeaturesReq
		// 
		this->mnuFeaturesReq->Index = 3;
		this->mnuFeaturesReq->Text = "Feature Requests";
		this->mnuFeaturesReq->Click += new System::EventHandler(this, &MainForm::mnuFeaturesReq_Click);
		// 
		// trayIcon
		// 
		this->trayIcon->BalloonTipText = "MeXgui is still working...";
		this->trayIcon->BalloonTipTitle = "MeXgui";
		this->trayIcon->ContextMenuStrip = this->trayMenu;
		this->trayIcon->Text = "MeXgui";
		this->trayIcon->MouseDoubleClick += new System::Windows::Forms::MouseEventHandler(this, &MainForm::trayIcon_MouseDoubleClick);
		// 
		// trayMenu
		// 
		this->trayMenu->Items->AddRange(new System::Windows::Forms::ToolStripItem[3] {this->openMeXguiToolStripMenuItem, this->toolStripSeparator1, this->exitMeXguiToolStripMenuItem});
		this->trayMenu->Name = "trayMenu";
		this->trayMenu->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
		this->trayMenu->Size = new System::Drawing::Size(143, 54);
		// 
		// openMeXguiToolStripMenuItem
		// 
		this->openMeXguiToolStripMenuItem->Name = "openMeXguiToolStripMenuItem";
		this->openMeXguiToolStripMenuItem->Size = new System::Drawing::Size(142, 22);
		this->openMeXguiToolStripMenuItem->Text = "Open MeXgui";
		this->openMeXguiToolStripMenuItem->Click += new System::EventHandler(this, &MainForm::openMeXguiToolStripMenuItem_Click);
		// 
		// toolStripSeparator1
		// 
		this->toolStripSeparator1->Name = "toolStripSeparator1";
		this->toolStripSeparator1->Size = new System::Drawing::Size(139, 6);
		// 
		// exitMeXguiToolStripMenuItem
		// 
		this->exitMeXguiToolStripMenuItem->Name = "exitMeXguiToolStripMenuItem";
		this->exitMeXguiToolStripMenuItem->Size = new System::Drawing::Size(142, 22);
		this->exitMeXguiToolStripMenuItem->Text = "Exit MeXgui";
		this->exitMeXguiToolStripMenuItem->Click += new System::EventHandler(this, &MainForm::exitMeXguiToolStripMenuItem_Click);
		// 
		// MainForm
		// 
		this->AllowDrop = true;
		this->AutoScaleDimensions = new System::Drawing::SizeF(96, 96);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
		this->ClientSize = new System::Drawing::Size(508, 499);
		this->Controls->Add(this->tabControl1);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->MaximizeBox = false;
		this->Menu = this->mainMenu1;
		this->MinimumSize = new System::Drawing::Size(524, 537);
		this->Name = "MainForm";
		this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
		this->Load += new System::EventHandler(this, &MainForm::MeXgui_Load);
		this->Shown += new System::EventHandler(this, &MainForm::MainForm_Shown);
		this->DragDrop += new System::Windows::Forms::DragEventHandler(this, &MainForm::MeXgui_DragDrop);
		this->DragEnter += new System::Windows::Forms::DragEventHandler(this, &MainForm::MeXgui_DragEnter);
		this->Move += new System::EventHandler(this, &MainForm::MainForm_Move);
		this->Resize += new System::EventHandler(this, &MainForm::MainForm_Resize);
		this->tabControl1->ResumeLayout(false);
		this->inputTab->ResumeLayout(false);
		this->splitContainer2->Panel1->ResumeLayout(false);
		this->splitContainer2->Panel2->ResumeLayout(false);
		this->splitContainer2->ResumeLayout(false);
		this->splitContainer1->Panel1->ResumeLayout(false);
		this->splitContainer1->Panel2->ResumeLayout(false);
		this->splitContainer1->Panel2->PerformLayout();
		this->splitContainer1->ResumeLayout(false);
		this->flowLayoutPanel1->ResumeLayout(false);
		this->flowLayoutPanel1->PerformLayout();
		this->flowLayoutPanel2->ResumeLayout(false);
		this->flowLayoutPanel2->PerformLayout();
		this->tabPage2->ResumeLayout(false);
		this->logTab->ResumeLayout(false);
		this->trayMenu->ResumeLayout(false);
		this->ResumeLayout(false);

	}

	void MainForm::InitializeInstanceFields()
	{
		filesToDeleteOnClosing = QVector<QString>();
		allForms = QVector<Form*>();
		formsToReopen = QVector<Form*>();
		bImportProfileSuccessful = false;
		restart = false;
		filesToReplace = QQMap<QString, CommandlineUpgradeData*>();
		packageSystem = new PackageSystem();
		settings = new MeXguiSettings();
		delete components;
	}
}
