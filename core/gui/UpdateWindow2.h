#pragma once

#include "MeGUI.MainForm.h"
#include "core/util/OSInfo.h"
#include "UpdateWindow.h"
#include "core/details/MeGUISettings.h"
#include "core/util/LogItem.h"
#include "MeGUI.core.gui.CountdownWindow.h"
#include "core/util/VistaStuff.h"
#include "core/util/HttpProxy.h"
#include "UpdateCacher.h"
#include "core/util/EnumProxy.h"
#include "core/util/VideoUtil.h"
#include "core/util/FileUtil.h"
#include "MeGUI.core.gui.HelpButton.h"
#include <QString>
#include <QVector>
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






//using namespace System::Collections::Generic;





//using namespace System::Net;

//using namespace System::Text;

//using namespace System::Threading;



//using namespace System::Xml;

//using namespace System::Xml::Serialization;

using namespace ICSharpCode::SharpZipLib::Zip;
using namespace SevenZip;

using namespace MeGUI::core::util;


namespace MeGUI
{
	class UpdateWindow : public System::Windows::Forms::Form
	{
	public:
		class iUpgradeable
		{
		public:
			enum PlatformModes
			{
				any = 0,
				x86 = 1,
				x64 = 2
			};

			/// <summary>
			/// May be overridden in a special init is to be done after the xmlserializer
			/// </summary>
		public:
			virtual void init();

			iUpgradeable();

			// Overrideable methods
			Version *GetLatestVersion();

			const bool &getHasAvailableVersions() const;

			bool isAvailable();

			ListViewItem *CreateListViewItem();
			virtual ErrorState Upgrade() = 0;


		private:
			bool downloadChecked;
		public:
			const bool &getDownloadChecked() const;
			void setDownloadChecked(const bool &value);

		private:
			QString savePath;
		public:
			const QString &getSavePath() const;
			void setSavePath(const QString &value);
		private:
			QString saveFolder;
		public:
			const QString &getSaveFolder() const;
			void setSaveFolder(const QString &value);

		protected:
			Version *currentVersion;
		public:
			const virtual Version &getCurrentVersion() const;
			virtual void setCurrentVersion(const Version &value);

		private:
			Versions *availableVersions;
		public:
			const Versions &getAvailableVersions() const;
			void setAvailableVersions(const Versions &value);

		private:
			bool allowUpdate;
		public:
			const bool &getAllowUpdate() const;
			void setAllowUpdate(const bool &value);

			bool Reinstall;

		private:
			QString name;
		public:
			const QString &getName() const;
			void setName(const QString &value);

		private:
			QString displayName;
		public:
			const QString &getDisplayName() const;
			void setDisplayName(const QString &value);

		private:
			PlatformModes platform;
		public:
			const PlatformModes &getPlatform() const;
			void setPlatform(const PlatformModes &value);

		private:
			int requiredBuild;
		public:
			const int &getRequiredBuild() const;
			void setRequiredBuild(const int &value);

		private:
			QString requiredNET;
		public:
			const QString &getRequiredNET() const;
			void setRequiredNET(const QString &value);

			QString treeViewID;
			const QString &getTreeViewID() const;
			void setTreeViewID(const QString &value);

		private:
			bool needsRestartedCopying;
		public:
			const bool &getNeedsRestartedCopying() const;
			void setNeedsRestartedCopying(const bool &value);

			const virtual bool &getNeedsInstalling() const;

			virtual ErrorState Install(Stream *fileData);

		private:
			void InitializeInstanceFields();
		};
	public:
		class iUpgradeableCollection : public CollectionBase
		{
		public:
			iUpgradeableCollection();
			iUpgradeableCollection(int capacity);

			iUpgradeable &operator [](int index);
			void Add(iUpgradeable *item);
			void Remove(iUpgradeable *item);
			iUpgradeable *FindByName(const QString &name);
			int CountCheckedFiles();
		};
	public:
		class ProfilesFile : public iUpgradeable
		{
		public:
			ProfilesFile();

			ProfilesFile(const QString &treeviewid, const QString &name, MeGUI::MainForm *mainForm);

		private:
			MeGUI::MainForm *mainForm;

		public:
			void setMainForm(const MeGUI::MainForm &value);

			const virtual bool &getNeedsInstalling() const;

			virtual ErrorState Install(Stream *fileData);

			virtual ErrorState Upgrade();
		};
	public:
		class AviSynthFile : public iUpgradeable
		{
		public:
			virtual void init();
		private:
			AviSynthFile();
		public:
			AviSynthFile(const QString &treeviewid, const QString &name);

			virtual ErrorState Upgrade();
		};
	public:
		class MeGUIFile : public iUpgradeable
		{
		private:
			MeGUIFile();

		public:
			MeGUIFile(const QString &treeViewID, const QString &name);

			const virtual Version &getCurrentVersion() const;
			virtual void setCurrentVersion(const Version &value);

			virtual void init();


			virtual ErrorState Upgrade();
		};
	public:
		class ProgramFile : public iUpgradeable
		{
		private:
			ProgramFile();

		public:
			virtual void init();

			ProgramFile(const QString &treeViewID, const QString &name); // Constructor

		private:
			const QString &getMeGUIFilePath() const;
			void setMeGUIFilePath(const QString &value);

		public:
			virtual ErrorState Upgrade();
		};
	public:
		class Version : public IComparable<Version*>
		{
		public:
			Version();
			Version(const QString &version, const QString &url);
		private:
			QString fileVersion;
			QString url;
			DateTime uploadDate;
			QString web;

		public:
			const QString &getFileVersion() const;
			void setFileVersion(const QString &value);
			const QString &getUrl() const;
			void setUrl(const QString &value);
			const DateTime &getUploadDate() const;
			void setUploadDate(const DateTime &value);
			const QString &getWeb() const;
			void setWeb(const QString &value);

			/// <summary>
			/// Helper method to check if a newer upload date is available
			/// </summary>
			/// <param name="version1">The first version to compare</param>
			/// <param name="version2">The second version to compare</param>
			/// <returns>1 if version1 has a newer upload date</returns>
		private:
			int CompareUploadDate(Version *version1, Version *version2);


		public:
			int CompareTo(Version *other);

		};
	public:
		class Versions : public CollectionBase
		{
		public:
			Versions();
			Versions(int capacity);
			Version &operator [](int index);
			void Add(Version *item);
			void Remove(Version *item);
		};
	public:
		enum ErrorState
		{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("File cannot be found on the server")]
			FileNotOnServer,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Update server is not available")]
			ServerNotAvailable,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("File cannot be downloaded")]
			CouldNotDownloadFile,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Backup file cannot be removed")]
			CouldNotRemoveBackup,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("File cannot be saved")]
			CouldNotSaveNewFile,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("File cannot be renamed")]
			CouldNotRenameExistingFile,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("File cannot be installed")]
			CouldNotInstall,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Update successful")]
			Successful,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("File cannot be extracted")]
			CouldNotUnzip,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Update XML is invalid")]
			InvalidXML,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("The requirements for this file are not met")]
			RequirementNotMet
		};
	private:
		QVector<QString> serverList;
		MainForm *mainForm;
	public:
		static MeGUISettings *meGUISettings;
	private:
		bool continueUpdate;
		iUpgradeableCollection *upgradeData;
		Thread *updateThread;
		StringBuilder *logBuilder;
		System::Threading::ManualResetEvent *webUpdate;
		XmlDocument *upgradeXml;
	public:
		bool needsRestart;
	private:
		bool isOrHasDownloadedUpgradeData;
		LogItem *oLog;
		QString ServerAddress;

		typedef void (*BeginParseUpgradeXml)(XmlNode *node, XmlNode *groupNode, const QString &path);
		typedef void (*SetLogText)();
		typedef void (*SetListView)(ListViewItem *item);
		typedef void (*ClearItems)(ListView *listview);

		typedef void (*UpdateProgressBar)(int minValue, int maxValue, int currentValue);
		public:
		~UpdateWindow()
		{
			this->Dispose(true);
		}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
		private:
		void Finalize()
		{
			this->Dispose(false);
		}

		void SetProgressBar(int minValue, int maxValue, int currentValue);
	public:
		void AddTextToLog(const QString &text, ImageType oLogType);

	private:
		void UpdateLogText();

		void AddToListview(ListViewItem *item);
		void ClearListview(ListView *listview);
		void UpdateWindow_FormClosing(QObject *sender, FormClosingQEvent *e);

		/// <summary>
		/// Constructor for Updatewindow.
		/// </summary>
		/// <param name="mainForm">MainForm instance</param>
		/// <param name="savedSettings">Current MeGUI settings</param>
		/// <param name="bSilent">whether the update window should be displayed</param>
	public:
		UpdateWindow(MainForm *mainForm, bool bSilent);

	private:
		void LoadComponentSettings();

		void SaveComponentSettings();

	public:
		static bool isComponentMissing();

	private:
		QVector<QString> getUpdateServerList(QString& serverList[]);

		void UpdateWindow_Load(QObject *sender, QEvent *e);
		void LoadSettings();
	public:
		void SaveSettings();
		void GetUpdateData(bool wait);
		/// <summary>
		/// This method is called to retrieve the update data from the webserver
		/// and then set the relevant information to the grid.
		/// </summary>
		ErrorState GetUpdateXML(const QString &strServerAddress);
		/// <summary>
		/// This function downloads the update XML file from the server and then processes it.
		/// </summary>
	private:
		void ProcessUpdateXML();

		void RemoveOldFiles();

		bool FindFileInUpdateXML(XmlNodeList *xnList, const QString &strFile);

		/// <summary>
		/// Parses the upgrade XML file to populate the upgradeData array. 
		/// It's a recursive algorithm, so it needs to be passed the root node
		/// off the upgrade XML to start off, and it will then recurse
		/// through all the nodes in the file.
		/// </summary>
		/// <param name="currentNode">The node that the function should work on</param>
		void ParseUpgradeXml(XmlNode *currentNode, XmlNode *groupNode, const QString &path);

		/// <summary>
		/// Once a "file" is found in the upgrade XML file, the files node is passed
		/// to this function which generates the correct iUpgradeable filetype (i.e. MeGUIFile
		/// or AviSynthFile) and then fills in all the relevant data.
		/// </summary>
		/// <param name="node"></param>
		void ParseFileData(XmlNode *node, XmlNode *groupNode, const QString &treePath);
		void DisplayItems(bool bShowAllFiles);
		void listViewDetails_ItemCheck(QObject *sender, ItemCheckQEvent *e);

		void listViewDetails_MouseClick(QObject *sender, MouseQEvent *e);

		void setIgnoreValue_Click(QObject *sender, QEvent *e);

	public:
		void StartAutoUpdate();

	private:
		void btnUpdate_Click(QObject *sender, QEvent *e);
		void InstallFiles(SortedDictionary<unsigned int, QVector<iUpgradeable*>*> *groups);

		/// <summary>
		/// This function iterates through all the selected files and downloads them
		/// one by one.
		/// </summary>
		void BeginUpdate();

		ErrorState Install(iUpgradeable *file, Stream *fileData);

		/// <summary>
		/// This function takes in the byte array containing a downloaded file
		/// and the iUpgradeable file and saves the new file to the disk, it also unzips
		/// the file if necessary.
		/// </summary>
		/// <param name="file"></param>
		/// <param name="data"></param>
		/// <returns></returns>
		ErrorState SaveNewFile(iUpgradeable *file, Stream *data);
			else
			{
				private *if_Renamed(mainForm->Settings->AlwaysBackUpFiles);
				QString oldFileName;
				private *if_Renamed(file::NeedsRestartedCopying);
				try
				{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (Stream output = File.OpenWrite(filename))
					Stream *output = File::OpenWrite(filename);
					try
					{

						//filename, data);
						if (file::NeedsRestartedCopying)
						{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
							mainForm->AddFileToReplace(file->Name, filename, oldFileName, file->GetLatestVersion()->getUploadDate().ToString(new System::Globalization::CultureInfo("en-us")));
							file::CurrentVersion->FileVersion = file->GetLatestVersion()->getFileVersion();
							needsRestart = true;
						}
						else
							file->CurrentVersion = file->GetLatestVersion(); // current installed version
						// is now the latest available version
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (output != 0)
							output.Dispose();
					}
				}
				catch (...)
				{
					AddTextToLog("Latest version of " + file->Name + " could not be saved to disk. Check there is enough free space.", Error);
					return CouldNotSaveNewFile;
				}
			}
			return Successful;

		private:
			void InitializeInstanceFields();
	};

	private:
		ErrorState manageBackups(QString savePath, QString name, bool bCopyFile)
		{
			try
			{
				if (File::Exists(savePath + ".backup"))
					File::Delete(savePath + ".backup");
			}
			catch (...)
			{
				AddTextToLog("Outdated backup version of " + name + " could not be deleted. Check if it is in use.", Error);
				return CouldNotRemoveBackup;
			}
			try
			{
				if (File::Exists(savePath))
				{
					if (bCopyFile == false)
						File::Move(savePath, (savePath + ".backup"));
					else
						File::Copy(savePath, (savePath + ".backup"));
				}
			}
			catch (...)
			{
				AddTextToLog("Old version of " + name + " could not be backed up correctly. Restart MeGUI and try again.", Error);
				return CouldNotRenameExistingFile;
			}
			return Successful;
		}

		void wc_DownloadProgressChanged(object sender, DownloadProgressChangedQEvent e)
		{
			if (e::TotalBytesToReceive > 0)
				SetProgressBar(0, static_cast<int>(e::TotalBytesToReceive), static_cast<int>(e::BytesReceived));
		}

	public:
		bool HasUpdatableFiles()
		{
			return NumUpdatableFiles() > 0;
		}

		int NumUpdatableFiles()
		{
			int numUpdateableFiles = 0;
			for (unknown::const_iterator upgradeable = upgradeData.begin(); upgradeable != upgradeData.end(); ++upgradeable)
			{
				if ((*upgradeable)->Name->Equals("neroaacenc"))
				{
					if (*upgradeableVersion::FileVersion != 0 && *upgradeableVersion::FileVersion->Equals((*upgradeable)->GetLatestVersion()->FileVersion))
						(*upgradeable)->GetLatestVersion()->UploadDate = *upgradeableVersion::UploadDate;
				}
				if ((*upgradeable)->AllowUpdate && (*upgradeable)->GetLatestVersion()->compare(*upgradeableVersion) != 0)
					numUpdateableFiles++;
			}
			return numUpdateableFiles;
		}

		void UpdateUploadDate(QString name, QString strDate)
		{
			iUpgradeable *up = upgradeData::FindByName(name);
			if (up == 0)
				return;

			DateTime oDate;
			bool bReady = DateTime::TryParse(strDate, new System::Globalization::CultureInfo("en-us"), System::Globalization::DateTimeStyles::None, oDate);
			if (bReady)
				up->CurrentVersion->UploadDate = oDate;
		}

	private:
		void checkToolStripMenuItem_Click(object sender, QEvent e)
		{
			ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(sender);
			for (unknown::const_iterator item = listViewDetails::SelectedItems.begin(); item != listViewDetails::SelectedItems.end(); ++item)
				(*item)->Checked = true;
		}

		void uncheckToolStripMenuItem_Click(object sender, QEvent e)
		{
			ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(sender);
			for (unknown::const_iterator item = listViewDetails::SelectedItems.begin(); item != listViewDetails::SelectedItems.end(); ++item)
				(*item)->Checked = false;
		}

		void reinstallToolStripMenuItem_Click(object sender, QEvent e)
		{
			for (unknown::const_iterator item = listViewDetails::SelectedItems.begin(); item != listViewDetails::SelectedItems.end(); ++item)
			{
				(*item)->SubItems["Status"]->Text = "Reinstalling";
				(*item)->Checked = true;
			}
		}

		void btnAbort_Click(object sender, QEvent e)
		{
			updateThread::Abort();
			btnUpdate->Enabled = true;
			btnAbort->Enabled = false;
		}

		void chkShowAllFiles_CheckedChanged(object sender, QEvent e)
		{
			DisplayItems(chkShowAllFiles->Checked);
		}

		void UpdateWindow_Move(object sender, QEvent e)
		{
			if (this->WindowState != FormWindowState::Minimized && this->Visible == true)
				mainForm::Settings->UpdateFormLocation = this->Location;
		}

		void UpdateWindow_Resize(object sender, QEvent e)
		{
			if (this->WindowState != FormWindowState::Minimized && this->Visible == true)
				mainForm::Settings->UpdateFormSize = this->ClientSize;
		}

		void splitContainer2_SplitterMoved(object sender, SplitterQEvent e)
		{
			if (this->WindowState != FormWindowState::Minimized && this->Visible == true)
				mainForm::Settings->UpdateFormSplitter = this->splitContainer2->SplitterDistance;
		}

		void listViewDetails_ColumnWidthChanged(object sender, ColumnWidthChangedQEvent e)
		{
			SaveComponentSettings();
		}

		void splitContainer1_SizeChanged(object sender, QEvent e)
		{
			this->splitContainer1->SplitterDistance = this->splitContainer1->Size->Height - 65;
		}


		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::IContainer components = 0;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
	protected:
		void Dispose(bool disposing)
		{
			if (disposing && (components != 0))
			{
				delete components;
			}
			__super::Dispose(disposing);

		}


		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
	private:
		void InitializeComponent()
		{
			this->components = new System::ComponentModel::Container();
			System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(UpdateWindow::typeid);
			this->statusToolStrip = new System::Windows::Forms::ContextMenuStrip(this->components);
			this->setIgnoreValue = new System::Windows::Forms::ToolStripMenuItem();
			this->checkToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
			this->uncheckToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
			this->reinstallToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
			this->splitContainer1 = new System::Windows::Forms::SplitContainer();
			this->splitContainer2 = new System::Windows::Forms::SplitContainer();
			this->listViewDetails = new System::Windows::Forms::ListView();
			this->colUpdate = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
			this->colName = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
			this->colExistingVersion = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
			this->colLatestVersion = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
			this->colExistingDate = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
			this->colLatestDate = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
			this->colPlatform = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
			this->colStatus = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
			this->txtBoxLog = new System::Windows::Forms::TextBox();
			this->panel1 = new System::Windows::Forms::Panel();
			this->chkShowAllFiles = new System::Windows::Forms::CheckBox();
			this->helpButton1 = new MeGUI::core::gui::HelpButton();
			this->progressBar = new System::Windows::Forms::ProgressBar();
			this->btnUpdate = new System::Windows::Forms::Button();
			this->btnAbort = new System::Windows::Forms::Button();
			this->statusToolStrip->SuspendLayout();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusToolStrip
			// 
			this->statusToolStrip->Items->AddRange(new System::Windows::Forms::ToolStripItem[] {this->setIgnoreValue, this->checkToolStripMenuItem, this->uncheckToolStripMenuItem, this->reinstallToolStripMenuItem});
			this->statusToolStrip->Name = "statusToolStrip";
			this->statusToolStrip->Size = new System::Drawing::Size(213, 92);
			// 
			// setIgnoreValue
			// 
			this->setIgnoreValue->CheckOnClick = true;
			this->setIgnoreValue->Name = "setIgnoreValue";
			this->setIgnoreValue->Size = new System::Drawing::Size(212, 22);
			this->setIgnoreValue->Text = "Ignore updates for this file";
			this->setIgnoreValue->Click += new System::EventHandler(this, &this->setIgnoreValue_Click);
			// 
			// checkToolStripMenuItem
			// 
			this->checkToolStripMenuItem->Name = "checkToolStripMenuItem";
			this->checkToolStripMenuItem->Size = new System::Drawing::Size(212, 22);
			this->checkToolStripMenuItem->Text = "Check";
			this->checkToolStripMenuItem->Click += new System::EventHandler(this, &this->checkToolStripMenuItem_Click);
			// 
			// uncheckToolStripMenuItem
			// 
			this->uncheckToolStripMenuItem->Name = "uncheckToolStripMenuItem";
			this->uncheckToolStripMenuItem->Size = new System::Drawing::Size(212, 22);
			this->uncheckToolStripMenuItem->Text = "Uncheck";
			this->uncheckToolStripMenuItem->Click += new System::EventHandler(this, &this->uncheckToolStripMenuItem_Click);
			// 
			// reinstallToolStripMenuItem
			// 
			this->reinstallToolStripMenuItem->Name = "reinstallToolStripMenuItem";
			this->reinstallToolStripMenuItem->Size = new System::Drawing::Size(212, 22);
			this->reinstallToolStripMenuItem->Text = "Force (re)install";
			this->reinstallToolStripMenuItem->Click += new System::EventHandler(this, &this->reinstallToolStripMenuItem_Click);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = new System::Drawing::Point(0, 0);
			this->splitContainer1->Name = "splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->splitContainer2);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->panel1);
			this->splitContainer1->Size = new System::Drawing::Size(710, 375);
			this->splitContainer1->SplitterDistance = 305;
			this->splitContainer1->SplitterWidth = 1;
			this->splitContainer1->TabIndex = 11;
			this->splitContainer1->SizeChanged += new System::EventHandler(this, &this->splitContainer1_SizeChanged);
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->Location = new System::Drawing::Point(0, 0);
			this->splitContainer2->Name = "splitContainer2";
			this->splitContainer2->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->listViewDetails);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->txtBoxLog);
			this->splitContainer2->Size = new System::Drawing::Size(710, 305);
			this->splitContainer2->SplitterDistance = 199;
			this->splitContainer2->TabIndex = 0;
			this->splitContainer2->SplitterMoved += new System::Windows::Forms::SplitterEventHandler(this, &this->splitContainer2_SplitterMoved);
			// 
			// listViewDetails
			// 
			this->listViewDetails->CheckBoxes = true;
			this->listViewDetails->Columns->AddRange(new System::Windows::Forms::ColumnHeader[] {this->colUpdate, this->colName, this->colExistingVersion, this->colLatestVersion, this->colExistingDate, this->colLatestDate, this->colPlatform, this->colStatus});
			this->listViewDetails->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listViewDetails->FullRowSelect = true;
			this->listViewDetails->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->listViewDetails->Location = new System::Drawing::Point(0, 0);
			this->listViewDetails->Name = "listViewDetails";
			this->listViewDetails->Size = new System::Drawing::Size(710, 199);
			this->listViewDetails->TabIndex = 6;
			this->listViewDetails->UseCompatibleStateImageBehavior = false;
			this->listViewDetails->View = System::Windows::Forms::View::Details;
			this->listViewDetails->ColumnWidthChanged += new System::Windows::Forms::ColumnWidthChangedEventHandler(this, &this->listViewDetails_ColumnWidthChanged);
			this->listViewDetails->ItemCheck += new System::Windows::Forms::ItemCheckEventHandler(this, &this->listViewDetails_ItemCheck);
			this->listViewDetails->MouseClick += new System::Windows::Forms::MouseEventHandler(this, &this->listViewDetails_MouseClick);
			// 
			// colUpdate
			// 
			this->colUpdate->Text = "Update";
			this->colUpdate->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->colUpdate->Width = 47;
			// 
			// colName
			// 
			this->colName->Text = "Name";
			this->colName->Width = 105;
			// 
			// colExistingVersion
			// 
			this->colExistingVersion->Text = "Local Version";
			this->colExistingVersion->Width = 117;
			// 
			// colLatestVersion
			// 
			this->colLatestVersion->Text = "Server Version";
			this->colLatestVersion->Width = 117;
			// 
			// colExistingDate
			// 
			this->colExistingDate->Text = "Local Date";
			this->colExistingDate->Width = 70;
			// 
			// colLatestDate
			// 
			this->colLatestDate->Text = "Server Date";
			this->colLatestDate->Width = 70;
			// 
			// colPlatform
			// 
			this->colPlatform->Text = "Platform";
			this->colPlatform->Width = 52;
			// 
			// colStatus
			// 
			this->colStatus->Text = "Status";
			this->colStatus->Width = 111;
			// 
			// txtBoxLog
			// 
			this->txtBoxLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtBoxLog->Location = new System::Drawing::Point(0, 0);
			this->txtBoxLog->Multiline = true;
			this->txtBoxLog->Name = "txtBoxLog";
			this->txtBoxLog->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->txtBoxLog->Size = new System::Drawing::Size(710, 102);
			this->txtBoxLog->TabIndex = 9;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->chkShowAllFiles);
			this->panel1->Controls->Add(this->helpButton1);
			this->panel1->Controls->Add(this->progressBar);
			this->panel1->Controls->Add(this->btnUpdate);
			this->panel1->Controls->Add(this->btnAbort);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = new System::Drawing::Point(0, 4);
			this->panel1->Name = "panel1";
			this->panel1->Size = new System::Drawing::Size(710, 65);
			this->panel1->TabIndex = 13;
			// 
			// chkShowAllFiles
			// 
			this->chkShowAllFiles->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
			this->chkShowAllFiles->AutoSize = true;
			this->chkShowAllFiles->Location = new System::Drawing::Point(421, 34);
			this->chkShowAllFiles->Name = "chkShowAllFiles";
			this->chkShowAllFiles->Size = new System::Drawing::Size(87, 17);
			this->chkShowAllFiles->TabIndex = 9;
			this->chkShowAllFiles->Text = "Show all files";
			this->chkShowAllFiles->UseVisualStyleBackColor = true;
			this->chkShowAllFiles->CheckedChanged += new System::EventHandler(this, &this->chkShowAllFiles_CheckedChanged);
			// 
			// helpButton1
			// 
			this->helpButton1->ArticleName = "Update";
			this->helpButton1->AutoSize = true;
			this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->helpButton1->Location = new System::Drawing::Point(12, 30);
			this->helpButton1->Name = "helpButton1";
			this->helpButton1->Size = new System::Drawing::Size(38, 23);
			this->helpButton1->TabIndex = 8;
			// 
			// progressBar
			// 
			this->progressBar->Dock = System::Windows::Forms::DockStyle::Top;
			this->progressBar->Location = new System::Drawing::Point(0, 0);
			this->progressBar->Name = "progressBar";
			this->progressBar->Size = new System::Drawing::Size(710, 23);
			this->progressBar->TabIndex = 7;
			// 
			// btnUpdate
			// 
			this->btnUpdate->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
			this->btnUpdate->Location = new System::Drawing::Point(545, 30);
			this->btnUpdate->Name = "btnUpdate";
			this->btnUpdate->Size = new System::Drawing::Size(75, 23);
			this->btnUpdate->TabIndex = 3;
			this->btnUpdate->Text = "Update";
			this->btnUpdate->UseVisualStyleBackColor = true;
			this->btnUpdate->Click += new System::EventHandler(this, &this->btnUpdate_Click);
			// 
			// btnAbort
			// 
			this->btnAbort->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
			this->btnAbort->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnAbort->Enabled = false;
			this->btnAbort->Location = new System::Drawing::Point(626, 30);
			this->btnAbort->Name = "btnAbort";
			this->btnAbort->Size = new System::Drawing::Size(72, 23);
			this->btnAbort->TabIndex = 4;
			this->btnAbort->Text = "Abort";
			this->btnAbort->UseVisualStyleBackColor = true;
			this->btnAbort->Click += new System::EventHandler(this, &this->btnAbort_Click);
			// 
			// UpdateWindow
			// 
			this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = new System::Drawing::Size(710, 375);
			this->Controls->Add(this->splitContainer1);
			this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
			this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = new System::Drawing::Size(400, 200);
			this->Name = "UpdateWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = "MeGUI - Updater";
			this->FormClosing += new System::Windows::Forms::FormClosingEventHandler(this, &this->UpdateWindow_FormClosing);
			this->Load += new System::EventHandler(this, &this->UpdateWindow_Load);
			this->Move += new System::EventHandler(this, &this->UpdateWindow_Move);
			this->Resize += new System::EventHandler(this, &this->UpdateWindow_Resize);
			this->statusToolStrip->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			this->splitContainer2->Panel2->PerformLayout();
			this->splitContainer2->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}


		System::Windows::Forms::ListView listViewDetails;
		System::Windows::Forms::ColumnHeader colUpdate;
		System::Windows::Forms::ColumnHeader colName;
		System::Windows::Forms::ColumnHeader colExistingVersion;
		System::Windows::Forms::ColumnHeader colLatestVersion;
		System::Windows::Forms::ColumnHeader colStatus;
		System::Windows::Forms::TextBox txtBoxLog;
		System::Windows::Forms::ContextMenuStrip statusToolStrip;
		System::Windows::Forms::ToolStripMenuItem setIgnoreValue;
		System::Windows::Forms::ToolStripMenuItem checkToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem uncheckToolStripMenuItem;
		System::Windows::Forms::SplitContainer splitContainer1;
		System::Windows::Forms::SplitContainer splitContainer2;
		System::Windows::Forms::ToolStripMenuItem reinstallToolStripMenuItem;
		System::Windows::Forms::ColumnHeader colPlatform;
		System::Windows::Forms::ColumnHeader colExistingDate;
		System::Windows::Forms::ColumnHeader colLatestDate;
		System::Windows::Forms::Panel panel1;
		System::Windows::Forms::CheckBox chkShowAllFiles;
		core::gui::HelpButton helpButton1;
		System::Windows::Forms::ProgressBar progressBar;
		System::Windows::Forms::Button btnUpdate;
		System::Windows::Forms::Button btnAbort;
}
}
