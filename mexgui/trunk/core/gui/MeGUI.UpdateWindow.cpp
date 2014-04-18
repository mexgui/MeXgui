#include "MeGUI.UpdateWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Net;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace ICSharpCode::SharpZipLib::Zip;
using namespace SevenZip;
using namespace MeGUI::core::util;

namespace MeGUI
{

	void UpdateWindow::iUpgradeable::init()
	{
	}

	UpdateWindow::iUpgradeable::iUpgradeable()
	{
		InitializeInstanceFields();
		availableVersions = new Versions(2);

	} // constructor

	MeGUI::UpdateWindow::Version *UpdateWindow::iUpgradeable::GetLatestVersion()
	{
		Version *latest = new Version();
		for (MeGUI::UpdateWindow::Versions::const_iterator v = this->availableVersions->begin(); v != this->availableVersions->end(); ++v)
			if ((*v)->compare(latest) != 0)
				latest = *v;

		return latest;
	}

	const bool &UpdateWindow::iUpgradeable::getHasAvailableVersions() const
	{
		Version *latest = GetLatestVersion();
		if (this->name == "neroaacenc")
		{
			if (currentVersion->getFileVersion() != "" && currentVersion->getFileVersion().Equals(latest->getFileVersion()))
				latest->setUploadDate(currentVersion->getUploadDate());
		}
		return latest != 0 && (latest->compare(currentVersion) != 0);
	}

	bool UpdateWindow::iUpgradeable::isAvailable()
	{
		ArrayList *arrPath = new ArrayList();
		std::string strPath;

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (this.name)
//ORIGINAL LINE: case "base":
		if (this->name == "base")
		{
				arrPath->Add(System::Windows::Forms::Application::ExecutablePath);
		}
//ORIGINAL LINE: case "x264":
		else if (this->name == "x264")
		{
					arrPath->Add(MainForm::Instance->getSettings()->getX264Path());
	#if defined(x86)
					strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getX264Path());
					if (OSInfo::isWow64())
					{
						arrPath->Add(System::IO::Path::Combine(strPath, "avs4x264mod.exe"));
						arrPath->Add(System::IO::Path::Combine(strPath, "x264_64.exe"));
					}
	#endif
		}
//ORIGINAL LINE: case "x264_10b":
		else if (this->name == "x264_10b")
		{
				if (MainForm::Instance->getSettings()->getUse10bitsX264())
				{
					arrPath->Add(MainForm::Instance->getSettings()->getX26410BitsPath());
	#if defined(x86)
					strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getX26410BitsPath());
					if (OSInfo::isWow64())
					{
						arrPath->Add(System::IO::Path::Combine(strPath, "avs4x264mod.exe"));
						arrPath->Add(System::IO::Path::Combine(strPath, "x264-10b_64.exe"));
					}
	#endif
				}
		}
//ORIGINAL LINE: case "dgindex":
		else if (this->name == "dgindex")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getDgIndexPath());
				strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgIndexPath());
				arrPath->Add(System::IO::Path::Combine(strPath, "DGDecode.dll"));
		}
//ORIGINAL LINE: case "dgavcindex":
		else if (this->name == "dgavcindex")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getDgavcIndexPath());
				strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgavcIndexPath());
				arrPath->Add(System::IO::Path::Combine(strPath, "DGAVCDecode.dll"));
		}
//ORIGINAL LINE: case "dgindexnv":
		else if (this->name == "dgindexnv")
		{
				if (MainForm::Instance->getSettings()->getUseDGIndexNV())
				{
					arrPath->Add(MainForm::Instance->getSettings()->getDgnvIndexPath());
					strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgnvIndexPath());
					arrPath->Add(System::IO::Path::Combine(strPath, "DGDecodeNV.dll"));
				}
		}
//ORIGINAL LINE: case "ffms":
		else if (this->name == "ffms")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getFFMSIndexPath());
				strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getFFMSIndexPath());
				arrPath->Add(System::IO::Path::Combine(strPath, "ffms2.dll"));
		}
//ORIGINAL LINE: case "mp4box":
		else if (this->name == "mp4box")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getMp4boxPath());
		}
//ORIGINAL LINE: case "pgcdemux":
		else if (this->name == "pgcdemux")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getPgcDemuxPath());
		}
//ORIGINAL LINE: case "avimux_gui":
		else if (this->name == "avimux_gui")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getAviMuxGUIPath());
		}
//ORIGINAL LINE: case "tsmuxer":
		else if (this->name == "tsmuxer")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getTSMuxerPath());
		}
//ORIGINAL LINE: case "xvid_encraw":
		else if (this->name == "xvid_encraw")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getXviDEncrawPath());
		}
//ORIGINAL LINE: case "mkvmerge":
		else if (this->name == "mkvmerge")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getMkvmergePath());
				arrPath->Add(MainForm::Instance->getSettings()->getMkvExtractPath());
		}
//ORIGINAL LINE: case "ffmpeg":
		else if (this->name == "ffmpeg")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getFFMpegPath());
		}
//ORIGINAL LINE: case "oggenc2":
		else if (this->name == "oggenc2")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getOggEnc2Path());
		}
//ORIGINAL LINE: case "yadif":
		else if (this->name == "yadif")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getYadifPath());
		}
//ORIGINAL LINE: case "lame":
		else if (this->name == "lame")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getLamePath());
		}
//ORIGINAL LINE: case "aften":
		else if (this->name == "aften")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getAftenPath());
		}
//ORIGINAL LINE: case "flac":
		else if (this->name == "flac")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getFlacPath());
		}
//ORIGINAL LINE: case "eac3to":
		else if (this->name == "eac3to")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getEAC3toPath());
		}
//ORIGINAL LINE: case "qaac":
		else if (this->name == "qaac")
		{
				if (MainForm::Instance->getSettings()->getUseQAAC())
				{
					arrPath->Add(MainForm::Instance->getSettings()->getQaacPath());
				}
		}
//ORIGINAL LINE: case "opus":
		else if (this->name == "opus")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getOpusPath());
		}
//ORIGINAL LINE: case "libs":
		else if (this->name == "libs")
		{
					strPath = System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath);
					arrPath->Add((System::IO::Path::Combine(strPath, "ICSharpCode.SharpZipLib.dll")));
					arrPath->Add((System::IO::Path::Combine(strPath, "MessageBoxExLib.dll")));
					arrPath->Add((System::IO::Path::Combine(strPath, "LinqBridge.dll")));
		}
//ORIGINAL LINE: case "mediainfo":
		else if (this->name == "mediainfo")
		{
				arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "MediaInfo.dll"));
		}
//ORIGINAL LINE: case "mediainfowrapper":
		else if (this->name == "mediainfowrapper")
		{
				arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "MediaInfoWrapper.dll"));
		}
//ORIGINAL LINE: case "sevenzip":
		else if (this->name == "sevenzip")
		{
				arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "7z.dll"));
		}
//ORIGINAL LINE: case "sevenzipsharp":
		else if (this->name == "sevenzipsharp")
		{
				arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "SevenZipSharp.dll"));
		}
//ORIGINAL LINE: case "data":
		else if (this->name == "data")
		{
				arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "Data\\ContextHelp.xml"));
		}
//ORIGINAL LINE: case "avswrapper":
		else if (this->name == "avswrapper")
		{
				arrPath->Add((System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "AvisynthWrapper.dll")));
		}
//ORIGINAL LINE: case "updatecopier":
		else if (this->name == "updatecopier")
		{
				arrPath->Add((System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "updatecopier.exe")));
		}
//ORIGINAL LINE: case "convolution3dyv12":
		else if (this->name == "convolution3dyv12")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "Convolution3DYV12.dll"));
		}
//ORIGINAL LINE: case "undot":
		else if (this->name == "undot")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "UnDot.dll"));
		}
//ORIGINAL LINE: case "fluxsmooth":
		else if (this->name == "fluxsmooth")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "FluxSmooth.dll"));
		}
//ORIGINAL LINE: case "eedi2":
		else if (this->name == "eedi2")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "EEDI2.dll"));
		}
//ORIGINAL LINE: case "decomb":
		else if (this->name == "decomb")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "Decomb.dll"));
		}
//ORIGINAL LINE: case "leakkerneldeint":
		else if (this->name == "leakkerneldeint")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "LeakKernelDeint.dll"));
		}
//ORIGINAL LINE: case "tomsmocomp":
		else if (this->name == "tomsmocomp")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TomsMoComp.dll"));
		}
//ORIGINAL LINE: case "tdeint":
		else if (this->name == "tdeint")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TDeint.dll"));
		}
//ORIGINAL LINE: case "tivtc":
		else if (this->name == "tivtc")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TIVTC.dll"));
		}
//ORIGINAL LINE: case "colormatrix":
		else if (this->name == "colormatrix")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "ColorMatrix.dll"));
		}
//ORIGINAL LINE: case "vsfilter":
		else if (this->name == "vsfilter")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "VSFilter.dll"));
		}
//ORIGINAL LINE: case "nicaudio":
		else if (this->name == "nicaudio")
		{
				arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"));
		}
//ORIGINAL LINE: case "bassaudio":
		else if (this->name == "bassaudio")
		{
					arrPath->Add(MainForm::Instance->getSettings()->getBassPath());
					strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getBassPath());
					arrPath->Add(System::IO::Path::Combine(strPath, "bass.dll"));
					arrPath->Add(System::IO::Path::Combine(strPath, "bass_aac.dll"));
		}
//ORIGINAL LINE: case "vobsub":
		else if (this->name == "vobsub")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getVobSubPath());
		}
//ORIGINAL LINE: case "besplit":
		else if (this->name == "besplit")
		{
				arrPath->Add(MainForm::Instance->getSettings()->getBeSplitPath());
		}
//ORIGINAL LINE: case "avs":
		else if (this->name == "avs")
		{
					strPath = Path::GetDirectoryName(MainForm::Instance->getSettings()->getAviSynthPath());
					arrPath->Add((Path::Combine(strPath, "avisynth.dll")));
					arrPath->Add((Path::Combine(strPath, "directshowsource.dll")));
					arrPath->Add((Path::Combine(strPath, "devil.dll")));
		}
//ORIGINAL LINE: case "neroaacenc":
		else if (this->name == "neroaacenc")
		{
					if (MainForm::Instance->getSettings()->getUseNeroAacEnc())
					{
						arrPath->Add(MainForm::Instance->getSettings()->getNeroAacEncPath());
						if (File::Exists(MainForm::Instance->getSettings()->getNeroAacEncPath()))
						{
							System::Diagnostics::FileVersionInfo *finfo = System::Diagnostics::FileVersionInfo::GetVersionInfo(MainForm::Instance->getSettings()->getNeroAacEncPath());
							FileInfo *fi = new FileInfo(MainForm::Instance->getSettings()->getNeroAacEncPath());
							this->currentVersion->setFileVersion(finfo->FileMajorPart + "." + finfo->FileMinorPart + "." + finfo->FileBuildPart + "." + finfo->FilePrivatePart);
							this->currentVersion->setUploadDate(fi->LastWriteTimeUtc);
						}
					}
		}

		for (ArrayList::const_iterator strAppPath = arrPath->begin(); strAppPath != arrPath->end(); ++strAppPath)
		{
			if ((*strAppPath).empty())
				return false;
			if (File::Exists(*strAppPath) == false)
				return false;
			FileInfo *fInfo = new FileInfo(*strAppPath);
			if (fInfo->Length == 0)
				return false;
		}
		return true;
	}

	ListViewItem *UpdateWindow::iUpgradeable::CreateListViewItem()
	{
		ListViewItem *myitem = new ListViewItem();
		ListViewItem::ListViewSubItem *name = new ListViewItem::ListViewSubItem();
		ListViewItem::ListViewSubItem *existingVersion = new ListViewItem::ListViewSubItem();
		ListViewItem::ListViewSubItem *latestVersion = new ListViewItem::ListViewSubItem();
		ListViewItem::ListViewSubItem *existingDate = new ListViewItem::ListViewSubItem();
		ListViewItem::ListViewSubItem *latestDate = new ListViewItem::ListViewSubItem();
		ListViewItem::ListViewSubItem *platform = new ListViewItem::ListViewSubItem();
		ListViewItem::ListViewSubItem *status = new ListViewItem::ListViewSubItem();

		myitem->Name = this->getName();

		name->Name = "Name";
		existingVersion->Name = "Existing Version";
		latestVersion->Name = "Latest Version";
		existingDate->Name = "Existing Date";
		latestDate->Name = "Latest Date";
		platform->Name = "Platform";
		status->Name = "Status";

		name->Text = this->getDisplayName();

		Version *v = GetLatestVersion();
		if (v != 0)
		{
			latestVersion->Text = v->getFileVersion();
			latestDate->Text = v->getUploadDate().ToShortDateString();
		}
		else
		{
			latestVersion->Text = "unknown";
			latestDate->Text = "unknown";
		}

		if (this->getCurrentVersion() != 0)
		{
			existingVersion->Text = this->getCurrentVersion()->getFileVersion();
			existingDate->Text = this->getCurrentVersion()->getUploadDate().ToShortDateString();
		}
		else
		{
			existingVersion->Text = "N/A";
			existingDate->Text = "N/A";
		}

		if (!getHasAvailableVersions())
		{
			if (this->getDownloadChecked())
				status->Text = "Reinstalling";
			else
				status->Text = "No Update Available";
		}
		else
		{
			if (this->getAllowUpdate())
			{
	#if defined(DEBUG)
				if (this->getName().Equals("core"))
				{
					if ((int::Parse(existingVersion->Text)) > (int::Parse(latestVersion->Text)))
						status->Text = "Update Ignored";
					else
						status->Text = "Update Available";
				}
				else
	#endif
				status->Text = "Update Available";
			}
			else
				status->Text = "Update Ignored";
		}

		if (this->getAllowUpdate())
		{
			if (this->getDownloadChecked())
				myitem->Checked = true;
			else
				myitem->Checked = false;
		}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		platform->Text = this->getPlatform().ToString();

		myitem->SubItems->Add(name);
		myitem->SubItems->Add(existingVersion);
		myitem->SubItems->Add(latestVersion);
		myitem->SubItems->Add(existingDate);
		myitem->SubItems->Add(latestDate);
		myitem->SubItems->Add(platform);
		myitem->SubItems->Add(status);
		return myitem;
	}

	const bool &UpdateWindow::iUpgradeable::getDownloadChecked() const
	{
		return downloadChecked;
	}

	void UpdateWindow::iUpgradeable::setDownloadChecked(const bool &value)
	{
		downloadChecked = value;
	}

	const std::string &UpdateWindow::iUpgradeable::getSavePath() const
	{
		return savePath;
	}

	void UpdateWindow::iUpgradeable::setSavePath(const std::string &value)
	{
		savePath = value;
	}

	const std::string &UpdateWindow::iUpgradeable::getSaveFolder() const
	{
		return saveFolder;
	}

	void UpdateWindow::iUpgradeable::setSaveFolder(const std::string &value)
	{
		saveFolder = value;
	}

	const MeGUI::UpdateWindow::Version &UpdateWindow::iUpgradeable::getCurrentVersion() const
	{
		if (currentVersion == 0)
			currentVersion = new Version();
		else if (this->isAvailable() == false)
			currentVersion = new Version();
		return currentVersion;
	}

	void UpdateWindow::iUpgradeable::setCurrentVersion(const Version &value)
	{
		currentVersion = value;
	}

	const MeGUI::UpdateWindow::Versions &UpdateWindow::iUpgradeable::getAvailableVersions() const
	{
		return availableVersions;
	}

	void UpdateWindow::iUpgradeable::setAvailableVersions(const Versions &value)
	{
		availableVersions = value;
	}

	const bool &UpdateWindow::iUpgradeable::getAllowUpdate() const
	{
		return allowUpdate;
	}

	void UpdateWindow::iUpgradeable::setAllowUpdate(const bool &value)
	{
		if (!value)
			downloadChecked = false;
		allowUpdate = value;
	}

	const std::string &UpdateWindow::iUpgradeable::getName() const
	{
		return this->name;
	}

	void UpdateWindow::iUpgradeable::setName(const std::string &value)
	{
		this->name = value;
	}

	const std::string &UpdateWindow::iUpgradeable::getDisplayName() const
	{
		return this->displayName;
	}

	void UpdateWindow::iUpgradeable::setDisplayName(const std::string &value)
	{
		this->displayName = value;
	}

	const MeGUI::UpdateWindow::iUpgradeable::PlatformModes &UpdateWindow::iUpgradeable::getPlatform() const
	{
		return this->platform;
	}

	void UpdateWindow::iUpgradeable::setPlatform(const PlatformModes &value)
	{
		this->platform = value;
	}

	const int &UpdateWindow::iUpgradeable::getRequiredBuild() const
	{
		return requiredBuild;
	}

	void UpdateWindow::iUpgradeable::setRequiredBuild(const int &value)
	{
		requiredBuild = value;
	}

	const std::string &UpdateWindow::iUpgradeable::getRequiredNET() const
	{
		return requiredNET;
	}

	void UpdateWindow::iUpgradeable::setRequiredNET(const std::string &value)
	{
		requiredNET = value;
	}

	const std::string &UpdateWindow::iUpgradeable::getTreeViewID() const
	{
		return this->treeViewID;
	}

	void UpdateWindow::iUpgradeable::setTreeViewID(const std::string &value)
	{
		this->treeViewID = value;
	}

	const bool &UpdateWindow::iUpgradeable::getNeedsRestartedCopying() const
	{
		return needsRestartedCopying;
	}

	void UpdateWindow::iUpgradeable::setNeedsRestartedCopying(const bool &value)
	{
		needsRestartedCopying = value;
	}

	const bool &UpdateWindow::iUpgradeable::getNeedsInstalling() const
	{
		return false;
	}

	MeGUI::UpdateWindow::ErrorState UpdateWindow::iUpgradeable::Install(Stream *fileData)
	{
		throw std::exception("This kind of file cannot be installed.");
	}

	void UpdateWindow::iUpgradeable::InitializeInstanceFields()
	{
		needsRestartedCopying = false;
	}

	UpdateWindow::iUpgradeableCollection::iUpgradeableCollection()
	{
	}

	UpdateWindow::iUpgradeableCollection::iUpgradeableCollection(int capacity)
	{
		this->InnerList->Capacity = capacity;
	}

	MeGUI::UpdateWindow::iUpgradeable &UpdateWindow::iUpgradeableCollection::operator [](int index)
	{
		return static_cast<iUpgradeable*>(this->List[index]);
	}

//C# TO C++ CONVERTER TODO TASK: You cannot specify separate 'set' logic for indexers in native C++:
//	void UpdateWindow::iUpgradeableCollection::setdefault(const int &index, iUpgradeable *value)
//	{
//		this->List[index] = value;
//	}

	void UpdateWindow::iUpgradeableCollection::Add(iUpgradeable *item)
	{
		if (FindByName(item->getName()) != 0)
			throw std::exception("Can't have multiple upgradeable items with the same name");
		this->InnerList->Add(item);
	}

	void UpdateWindow::iUpgradeableCollection::Remove(iUpgradeable *item)
	{
		this->InnerList->Remove(item);
	}

	MeGUI::UpdateWindow::iUpgradeable *UpdateWindow::iUpgradeableCollection::FindByName(const std::string &name)
	{
		for (unknown::const_iterator file = this->InnerList.begin(); file != this->InnerList.end(); ++file)
		{
			if ((*file)->getName()->Equals(name))
				return file;
		}
		return 0;
	}

	int UpdateWindow::iUpgradeableCollection::CountCheckedFiles()
	{
		int count = 0;
		for (unknown::const_iterator file = this->InnerList.begin(); file != this->InnerList.end(); ++file)
		{
			if ((*file)->getDownloadChecked())
				count++;
		}
		return count;
	}

	UpdateWindow::ProfilesFile::ProfilesFile()
	{
	}

	UpdateWindow::ProfilesFile::ProfilesFile(const std::string &treeviewid, const std::string &name, MeGUI::MainForm *mainForm)
	{
		this->treeViewID = treeviewid;
		this->setName(name);
		this->setAllowUpdate(true);
		this->mainForm = mainForm;
	}

	void UpdateWindow::ProfilesFile::setMainForm(const MeGUI::MainForm &value)
	{
		mainForm = value;
	}

	const bool &UpdateWindow::ProfilesFile::getNeedsInstalling() const
	{
		return true;
	}

	MeGUI::UpdateWindow::ErrorState UpdateWindow::ProfilesFile::Install(Stream *fileData)
	{
		try
		{
			mainForm->importProfiles(fileData);
			if (mainForm->getImportProfileSuccessful() == true)
				return Successful;
			else
				return CouldNotInstall;
		}
		catch (...)
		{
			return CouldNotInstall;
		}

	}

	MeGUI::UpdateWindow::ErrorState UpdateWindow::ProfilesFile::Upgrade()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void UpdateWindow::AviSynthFile::init()
	{
		iUpgradeable::init();
		this->setSaveFolder(MainForm::Instance->getSettings()->getAvisynthPluginsPath());
	}

	UpdateWindow::AviSynthFile::AviSynthFile()
	{
		this->setSaveFolder(MainForm::Instance->getSettings()->getAvisynthPluginsPath());
	}

	UpdateWindow::AviSynthFile::AviSynthFile(const std::string &treeviewid, const std::string &name)
	{
		this->setName(name);
		this->setAllowUpdate(true);
		this->treeViewID = treeviewid;
		this->setSaveFolder(MainForm::Instance->getSettings()->getAvisynthPluginsPath());
	}

	MeGUI::UpdateWindow::ErrorState UpdateWindow::AviSynthFile::Upgrade()
	{
		return CouldNotDownloadFile;
	}

	UpdateWindow::MeGUIFile::MeGUIFile()
	{
	}

	UpdateWindow::MeGUIFile::MeGUIFile(const std::string &treeViewID, const std::string &name)
	{
		this->setName(name);
		this->setAllowUpdate(true);
		this->treeViewID = treeViewID;
		this->setSaveFolder(Application::StartupPath);
	}

	const MeGUI::UpdateWindow::Version &UpdateWindow::MeGUIFile::getCurrentVersion() const
	{
		if (getName() == "core")
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			iUpgradeable::getCurrentVersion()->setFileVersion((new System::Version(Application::ProductVersion))->Build->ToString());
			//FileInfo fi = new FileInfo(System.Windows.Forms.Application.ExecutablePath);
			//base.CurrentVersion.UploadDate = fi.LastWriteTimeUtc.Date.AddMinutes(Math.Floor(fi.LastWriteTimeUtc.TimeOfDay.TotalMinutes));
		}
		return iUpgradeable::getCurrentVersion();
	}

	void UpdateWindow::MeGUIFile::setCurrentVersion(const Version &value)
	{
		iUpgradeable::setCurrentVersion(value);
	}

	void UpdateWindow::MeGUIFile::init()
	{
		iUpgradeable::init();
		this->setSaveFolder(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath));
	}

	MeGUI::UpdateWindow::ErrorState UpdateWindow::MeGUIFile::Upgrade()
	{
		throw std::exception("The method or operation is not implemented.");
	}

	UpdateWindow::ProgramFile::ProgramFile()
	{
	}

	void UpdateWindow::ProgramFile::init()
	{
		if (getMeGUIFilePath() == "")
			throw new FileNotRegisteredYetException(getName());
		setSavePath(Path::Combine(Application::StartupPath, getMeGUIFilePath()));
		// If the file doesn't exist, assume it isn't set up, so put it in the standard install location
		if (!File::Exists(getSavePath()))
		{
			std::string extension = Path::GetExtension(getSavePath());
			std::string path = Path::Combine(System::Windows::Forms::Application::StartupPath, "tools");
			path = Path::Combine(path, getName());
			setSavePath(Path::Combine(path, getName() + extension));
			setMeGUIFilePath(getSavePath());
		}
	}

	UpdateWindow::ProgramFile::ProgramFile(const std::string &treeViewID, const std::string &name)
	{
		this->setName(name);
		this->setAllowUpdate(true);
		this->treeViewID = treeViewID;
		init();
	}

	const std::string &UpdateWindow::ProgramFile::getMeGUIFilePath() const
	{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (this.Name)
//ORIGINAL LINE: case ("dgindex"):
		if (this->getName() == ("dgindex"))
		{
				return meGUISettings::DgIndexPath;
		}
//ORIGINAL LINE: case ("mkvmerge"):
		else if (this->getName() == ("mkvmerge"))
		{
				return meGUISettings::MkvmergePath;
		}
//ORIGINAL LINE: case ("lame"):
		else if (this->getName() == ("lame"))
		{
				return meGUISettings::LamePath;
		}
//ORIGINAL LINE: case ("mp4box"):
		else if (this->getName() == ("mp4box"))
		{
				return meGUISettings::Mp4boxPath;
		}
//ORIGINAL LINE: case ("pgcdemux"):
		else if (this->getName() == ("pgcdemux"))
		{
				return meGUISettings::PgcDemuxPath;
		}
//ORIGINAL LINE: case ("neroaacenc"):
		else if (this->getName() == ("neroaacenc"))
		{
				return meGUISettings::NeroAacEncPath;
		}
//ORIGINAL LINE: case ("avimux_gui"):
		else if (this->getName() == ("avimux_gui"))
		{
				return meGUISettings::AviMuxGUIPath;
		}
//ORIGINAL LINE: case ("avs"):
		else if (this->getName() == ("avs"))
		{
				return meGUISettings::AviSynthPath;
		}
//ORIGINAL LINE: case ("x264"):
		else if (this->getName() == ("x264"))
		{
				return meGUISettings::X264Path;
		}
//ORIGINAL LINE: case ("x264_10b"):
		else if (this->getName() == ("x264_10b"))
		{
				return meGUISettings::X26410BitsPath;
		}
//ORIGINAL LINE: case ("xvid_encraw"):
		else if (this->getName() == ("xvid_encraw"))
		{
				return meGUISettings::XviDEncrawPath;
		}
//ORIGINAL LINE: case ("ffmpeg"):
		else if (this->getName() == ("ffmpeg"))
		{
				return meGUISettings::FFMpegPath;
		}
//ORIGINAL LINE: case ("oggenc2"):
		else if (this->getName() == ("oggenc2"))
		{
				return meGUISettings::OggEnc2Path;
		}
//ORIGINAL LINE: case ("yadif"):
		else if (this->getName() == ("yadif"))
		{
				return meGUISettings::YadifPath;
		}
//ORIGINAL LINE: case ("bassaudio"):
		else if (this->getName() == ("bassaudio"))
		{
				return meGUISettings::BassPath;
		}
//ORIGINAL LINE: case ("vobsub"):
		else if (this->getName() == ("vobsub"))
		{
				return meGUISettings::VobSubPath;
		}
//ORIGINAL LINE: case ("besplit"):
		else if (this->getName() == ("besplit"))
		{
				return meGUISettings::BeSplitPath;
		}
//ORIGINAL LINE: case ("aften"):
		else if (this->getName() == ("aften"))
		{
				return meGUISettings::AftenPath;
		}
//ORIGINAL LINE: case ("flac"):
		else if (this->getName() == ("flac"))
		{
				return meGUISettings::FlacPath;
		}
//ORIGINAL LINE: case ("eac3to"):
		else if (this->getName() == ("eac3to"))
		{
				return meGUISettings::EAC3toPath;
		}
//ORIGINAL LINE: case ("dgavcindex"):
		else if (this->getName() == ("dgavcindex"))
		{
				return meGUISettings::DgavcIndexPath;
		}
//ORIGINAL LINE: case ("dgindexnv"):
		else if (this->getName() == ("dgindexnv"))
		{
				return meGUISettings::DgnvIndexPath;
		}
//ORIGINAL LINE: case ("ffms"):
		else if (this->getName() == ("ffms"))
		{
				return meGUISettings::FFMSIndexPath;
		}
//ORIGINAL LINE: case ("tsmuxer"):
		else if (this->getName() == ("tsmuxer"))
		{
				return meGUISettings::TSMuxerPath;
		}
//ORIGINAL LINE: case ("qaac"):
		else if (this->getName() == ("qaac"))
		{
				return meGUISettings::QaacPath;
		}
//ORIGINAL LINE: case ("opus"):
		else if (this->getName() == ("opus"))
		{
				return meGUISettings::OpusPath;
		}
		else
		{
				return 0;
		}
	}

	void UpdateWindow::ProgramFile::setMeGUIFilePath(const std::string &value)
	{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (this.Name)
//ORIGINAL LINE: case ("neroaacenc"):
		if (this->getName() == ("neroaacenc"))
		{
				meGUISettings->NeroAacEncPath = value;
		}
	}

	MeGUI::UpdateWindow::ErrorState UpdateWindow::ProgramFile::Upgrade()
	{
		return CouldNotDownloadFile;
	}

	UpdateWindow::Version::Version()
	{
	}

	UpdateWindow::Version::Version(const std::string &version, const std::string &url)
	{
		this->fileVersion = version;
		this->url = url;
	}

	const std::string &UpdateWindow::Version::getFileVersion() const
	{
		return fileVersion;
	}

	void UpdateWindow::Version::setFileVersion(const std::string &value)
	{
		fileVersion = value;
	}

	const std::string &UpdateWindow::Version::getUrl() const
	{
		return url;
	}

	void UpdateWindow::Version::setUrl(const std::string &value)
	{
		url = value;
	}

	const DateTime &UpdateWindow::Version::getUploadDate() const
	{
		return uploadDate;
	}

	void UpdateWindow::Version::setUploadDate(const DateTime &value)
	{
		uploadDate = value;
	}

	const std::string &UpdateWindow::Version::getWeb() const
	{
		return web;
	}

	void UpdateWindow::Version::setWeb(const std::string &value)
	{
		web = value;
	}

	int UpdateWindow::Version::CompareUploadDate(Version *version1, Version *version2)
	{
		if (version1 == 0 && version2 == 0)
			return 0;
		else if (version1 == 0)
			return -1;
		else if (version2 == 0)
			return 1;
		else if (version1->uploadDate != DateTime() && version2->uploadDate != DateTime())
		{
			if (version1->uploadDate > version2->uploadDate)
				return 1;
			else if (version1->uploadDate < version2->uploadDate)
				return -1;
			else
				return 0;
		}

		return 1;
	}

	int UpdateWindow::Version::CompareTo(Version *other)
	{
		return CompareUploadDate(this, other);
	}

	UpdateWindow::Versions::Versions()
	{
		this->Capacity = 2;
	}

	UpdateWindow::Versions::Versions(int capacity)
	{
		this->Capacity = capacity;
	}

	MeGUI::UpdateWindow::Version &UpdateWindow::Versions::operator [](int index)
	{
		return static_cast<Version*>(this->List[index]);
	}

//C# TO C++ CONVERTER TODO TASK: You cannot specify separate 'set' logic for indexers in native C++:
//	void UpdateWindow::Versions::setdefault(const int &index, Version *value)
//	{
//		this->List[index] = value;
//	}

	void UpdateWindow::Versions::Add(Version *item)
	{
		this->InnerList->Add(item);
	}

	void UpdateWindow::Versions::Remove(Version *item)
	{
		this->InnerList->Remove(item);
	}

MeGUISettings *UpdateWindow::meGUISettings = 0;

	void UpdateWindow::SetProgressBar(int minValue, int maxValue, int currentValue)
	{
		if (this->progressBar->InvokeRequired)
		{
			try
			{
				UpdateProgressBar d = new UpdateProgressBar(this, &UpdateWindow::SetProgressBar);
				progressBar->Invoke(d, minValue, maxValue, currentValue);
			}
			catch (std::exception &e1)
			{
			}
		}
		else
		{
			this->progressBar->Minimum = static_cast<int>(minValue);
			this->progressBar->Maximum = static_cast<int>(maxValue);
			this->progressBar->Value = static_cast<int>(currentValue);
		}
	}

	void UpdateWindow::AddTextToLog(const std::string &text, ImageType oLogType)
	{
		oLog->LogEvent(text, oLogType);

		if (oLogType == Warning || oLogType == Error)
			logBuilder->AppendLine(oLogType + ": " + text);
		else
			logBuilder->AppendLine(text);
		if (!this->Visible)
			return;
		SetLogText d = new SetLogText(this, &UpdateWindow::UpdateLogText);
		if (this->txtBoxLog->InvokeRequired)
			this->Invoke(d);
		else
			d();
	}

	void UpdateWindow::UpdateLogText()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		this->txtBoxLog->Text = logBuilder->ToString();
		this->txtBoxLog->SelectionStart = txtBoxLog->Text->Length;
		this->txtBoxLog->ScrollToCaret();
	}

	void UpdateWindow::AddToListview(ListViewItem *item)
	{
		if (this->listViewDetails->InvokeRequired)
		{
			SetListView d = new SetListView(this, &UpdateWindow::AddToListview);
			this->Invoke(d, item);
		}
		else
			this->listViewDetails->Items->Add(item);

		if (item->Index % 2 != 0)
			item->BackColor = Color::White;
		else
			item->BackColor = Color::WhiteSmoke;
	}

	void UpdateWindow::ClearListview(ListView *listview)
	{
		if (listview->InvokeRequired)
		{
			ClearItems d = new ClearItems(this, &UpdateWindow::ClearListview);
			this->Invoke(d, listview);
		}
		else
		{
			listview->Items->Clear();
		}
	}

	void UpdateWindow::UpdateWindow_FormClosing(object *sender, FormClosingEventArgs *e)
	{
		SaveSettings();
	}

	UpdateWindow::UpdateWindow(MainForm *mainForm, bool bSilent)
	{
		InitializeInstanceFields();
		InitializeComponent();
		this->mainForm = mainForm;
		this->oLog = mainForm->getUpdateLog();
		LoadComponentSettings();
		this->upgradeData = new iUpgradeableCollection(32); // To avoid unnecessary resizing, start at 32.
		meGUISettings = mainForm->getSettings(); // Load up the MeGUI settings so i can access filepaths
		if (bSilent)
			return;
		if (mainForm->getSettings()->getAutoUpdateServerLists()[mainForm->getSettings()->getAutoUpdateServerSubList()].Length <= 1)
		{
			MessageBox::Show("Couldn't run auto-update since there are no servers registered.", "No servers registered", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		serverList = getUpdateServerList(mainForm->getSettings()->getAutoUpdateServerLists()[mainForm->getSettings()->getAutoUpdateServerSubList()]);
		LoadSettings();
	}

	void UpdateWindow::LoadComponentSettings()
	{
		// Restore Size/Position of the window
		this->ClientSize = mainForm->getSettings()->getUpdateFormSize();
		this->Location = mainForm->getSettings()->getUpdateFormLocation();
		this->splitContainer2->SplitterDistance = mainForm->getSettings()->getUpdateFormSplitter();

		colUpdate->Width = mainForm->getSettings()->getUpdateFormUpdateColumnWidth();
		colName->Width = mainForm->getSettings()->getUpdateFormNameColumnWidth();
		colExistingVersion->Width = mainForm->getSettings()->getUpdateFormLocalVersionColumnWidth();
		colLatestVersion->Width = mainForm->getSettings()->getUpdateFormServerVersionColumnWidth();
		colExistingDate->Width = mainForm->getSettings()->getUpdateFormLocalDateColumnWidth();
		colLatestDate->Width = mainForm->getSettings()->getUpdateFormServerDateColumnWidth();
		colPlatform->Width = mainForm->getSettings()->getUpdateFormPlatformColumnWidth();
		colStatus->Width = mainForm->getSettings()->getUpdateFormStatusColumnWidth();
	}

	void UpdateWindow::SaveComponentSettings()
	{
		mainForm->getSettings()->setUpdateFormUpdateColumnWidth(colUpdate->Width);
		mainForm->getSettings()->setUpdateFormNameColumnWidth(colName->Width);
		mainForm->getSettings()->setUpdateFormLocalVersionColumnWidth(colExistingVersion->Width);
		mainForm->getSettings()->setUpdateFormServerVersionColumnWidth(colLatestVersion->Width);
		mainForm->getSettings()->setUpdateFormLocalDateColumnWidth(colExistingDate->Width);
		mainForm->getSettings()->setUpdateFormServerDateColumnWidth(colLatestDate->Width);
		mainForm->getSettings()->setUpdateFormPlatformColumnWidth(colPlatform->Width);
		mainForm->getSettings()->setUpdateFormStatusColumnWidth(colStatus->Width);
	}

	bool UpdateWindow::isComponentMissing()
	{
		ArrayList *arrPath = new ArrayList();
		std::string strPath;

		// base 
		arrPath->Add(System::Windows::Forms::Application::ExecutablePath);
		// x264
		arrPath->Add(MainForm::Instance->getSettings()->getX264Path());
	#if defined(x86)
		strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getX264Path());
		if (OSInfo::isWow64())
		{
			arrPath->Add(System::IO::Path::Combine(strPath, "avs4x264mod.exe"));
			arrPath->Add(System::IO::Path::Combine(strPath, "x264_64.exe"));
		}
	#endif
		//x264 10bit
		if (MainForm::Instance->getSettings()->getUse10bitsX264())
		{
			arrPath->Add(MainForm::Instance->getSettings()->getX26410BitsPath());
	#if defined(x86)
			strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getX26410BitsPath());
			if (OSInfo::isWow64())
			{
				arrPath->Add(System::IO::Path::Combine(strPath, "avs4x264mod.exe"));
				arrPath->Add(System::IO::Path::Combine(strPath, "x264-10b_64.exe"));
			}
	#endif
		}

		// dgindex
		arrPath->Add(MainForm::Instance->getSettings()->getDgIndexPath());
		strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgIndexPath());
		arrPath->Add(System::IO::Path::Combine(strPath, "DGDecode.dll"));
	#if defined(x86)
		// dgavcindex
		arrPath->Add(MainForm::Instance->getSettings()->getDgavcIndexPath());
		strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgavcIndexPath());
		arrPath->Add(System::IO::Path::Combine(strPath, "DGAVCDecode.dll"));
	#endif
		//ffms
		arrPath->Add(MainForm::Instance->getSettings()->getFFMSIndexPath());
		strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getFFMSIndexPath());
		arrPath->Add(System::IO::Path::Combine(strPath, "ffms2.dll"));
		//mp4box
		arrPath->Add(MainForm::Instance->getSettings()->getMp4boxPath());
		//pgcdemux
		arrPath->Add(MainForm::Instance->getSettings()->getPgcDemuxPath());
		//avimux_gui
		arrPath->Add(MainForm::Instance->getSettings()->getAviMuxGUIPath());
		//tsmuxer
		arrPath->Add(MainForm::Instance->getSettings()->getTSMuxerPath());
		//xvid_encraw
		arrPath->Add(MainForm::Instance->getSettings()->getXviDEncrawPath());
		//mkvmerge
		arrPath->Add(MainForm::Instance->getSettings()->getMkvmergePath());
		arrPath->Add(MainForm::Instance->getSettings()->getMkvExtractPath());
		//ffmpeg
		arrPath->Add(MainForm::Instance->getSettings()->getFFMpegPath());
		//oggenc2
		arrPath->Add(MainForm::Instance->getSettings()->getOggEnc2Path());
		//yadif
		arrPath->Add(MainForm::Instance->getSettings()->getYadifPath());
		//lame
		arrPath->Add(MainForm::Instance->getSettings()->getLamePath());
		//aften
		arrPath->Add(MainForm::Instance->getSettings()->getAftenPath());
		//flac
		arrPath->Add(MainForm::Instance->getSettings()->getFlacPath());
		//eac3to
		arrPath->Add(MainForm::Instance->getSettings()->getEAC3toPath());
		//opus
		arrPath->Add(MainForm::Instance->getSettings()->getOpusPath());
		//libs":
		strPath = System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath);
		arrPath->Add((System::IO::Path::Combine(strPath, "ICSharpCode.SharpZipLib.dll")));
		arrPath->Add((System::IO::Path::Combine(strPath, "MessageBoxExLib.dll")));
		arrPath->Add((System::IO::Path::Combine(strPath, "LinqBridge.dll")));
		//mediainfo
		arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "MediaInfo.dll"));
		//mediainfowrapper
		arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "MediaInfoWrapper.dll"));
		//sevenzip
		arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "7z.dll"));
		//sevenzipsharp
		arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "SevenZipSharp.dll"));
		//data
		arrPath->Add(System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "Data\\ContextHelp.xml"));
		//avswrapper
		arrPath->Add((System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "AvisynthWrapper.dll")));
		//updatecopier
		arrPath->Add((System::IO::Path::Combine(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "updatecopier.exe")));
	#if defined(x86)
		//convolution3dyv12
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "Convolution3DYV12.dll"));
		//fluxsmooth
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "FluxSmooth.dll"));
		//decomb
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "Decomb.dll"));
		//tomsmocomp
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TomsMoComp.dll"));
		//tdeint
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TDeint.dll"));
		//tivtc
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TIVTC.dll"));
		//colormatrix
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "ColorMatrix.dll"));
		//vsfilter
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "VSFilter.dll"));
		//nicaudio
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"));
		//bassaudio
		arrPath->Add(MainForm::Instance->getSettings()->getBassPath());
		strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getBassPath());
		arrPath->Add(System::IO::Path::Combine(strPath, "bass.dll"));
		arrPath->Add(System::IO::Path::Combine(strPath, "bass_aac.dll"));
	#endif
		//undot
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "UnDot.dll"));
		//eedi2
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "EEDI2.dll"));
		//leakkerneldeint
		arrPath->Add(System::IO::Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "LeakKernelDeint.dll"));
		//vobsub
		arrPath->Add(MainForm::Instance->getSettings()->getVobSubPath());
		//besplit
		arrPath->Add(MainForm::Instance->getSettings()->getBeSplitPath());

		//qaac
		if (MainForm::Instance->getSettings()->getUseQAAC())
			arrPath->Add(MainForm::Instance->getSettings()->getQaacPath());

		//neroaacenc
		if (MainForm::Instance->getSettings()->getUseNeroAacEnc())
			arrPath->Add(MainForm::Instance->getSettings()->getNeroAacEncPath());

		// dgindexnv
		if (MainForm::Instance->getSettings()->getUseDGIndexNV())
		{
			arrPath->Add(MainForm::Instance->getSettings()->getDgnvIndexPath());
			strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgnvIndexPath());
			arrPath->Add(System::IO::Path::Combine(strPath, "DGDecodeNV.dll"));
		}

		// avisynth
		arrPath->Add(MainForm::Instance->getSettings()->getAviSynthPath());
		strPath = System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getAviSynthPath());
		arrPath->Add(System::IO::Path::Combine(strPath, "directshowsource.dll"));
		arrPath->Add(System::IO::Path::Combine(strPath, "devil.dll"));

		bool bComponentMissing = false;
		for (ArrayList::const_iterator strAppPath = arrPath->begin(); strAppPath != arrPath->end(); ++strAppPath)
		{
			if ((*strAppPath).empty())
			{
				MainForm::Instance->getUpdateLog()->LogEvent("No path to check for missing components!", Error);
				bComponentMissing = true;
				continue;
			}
			else if (File::Exists(*strAppPath) == false)
			{
				MainForm::Instance->getUpdateLog()->LogEvent("Component not found: " + *strAppPath, Error);
				bComponentMissing = true;
				continue;
			}
			FileInfo *fInfo = new FileInfo(*strAppPath);
			if (fInfo->Length == 0)
			{
				MainForm::Instance->getUpdateLog()->LogEvent("Component has 0 bytes: " + *strAppPath, Error);
				bComponentMissing = true;
			}
		}
		return bComponentMissing;
	}

	std::vector<std::string> UpdateWindow::getUpdateServerList(std::string& serverList[])
	{
		std::string lastUpdateServer = MainForm::Instance->getSettings()->getLastUpdateServer();
		std::vector<std::string> randomServerList = std::vector<std::string>();
		std::vector<std::string> sortedServerList = std::vector<std::string>(serverList);
		sortedServerList.RemoveAt(0); // remove header

		if (MainForm::Instance->getSettings()->getLastUpdateCheck().AddHours(4)->compare(DateTime::Now::ToUniversalTime()) > 0)
		{
			// update server used within the last 4 hours - therefore no new server will be selected
			if (std::find(sortedServerList.begin(), sortedServerList.end(), lastUpdateServer) != sortedServerList.end())
			{
				sortedServerList.Remove(lastUpdateServer);
				randomServerList.push_back(lastUpdateServer);
				lastUpdateServer = "";
			}
		}
		else
		{
			if (std::find(sortedServerList.begin(), sortedServerList.end(), lastUpdateServer) != sortedServerList.end())
				sortedServerList.Remove(lastUpdateServer);
		}

		Random *r = new Random();
		while (sortedServerList.size() > 0)
		{
			int i = r->Next(0, sortedServerList.size());
			randomServerList.push_back(sortedServerList[i]);
			sortedServerList.RemoveAt(i);
		}

		if (!lastUpdateServer.empty())
			randomServerList.push_back(lastUpdateServer);

		return randomServerList;
	}

	void UpdateWindow::UpdateWindow_Load(object *sender, EventArgs *e)
	{
		// Move window in the visible area of the screen if neccessary
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

		GetUpdateData(false);

		if (VistaStuff::getIsVistaOrNot())
			VistaStuff::SetWindowTheme(listViewDetails->Handle, "explorer", 0);
	}

	void UpdateWindow::LoadSettings()
	{
		std::string path = Path::Combine(Application::StartupPath, "AutoUpdate.xml");
		if (File::Exists(path))
		{
			try
			{
				XmlSerializer *serializer = new XmlSerializer(iUpgradeableCollection::typeid, new Type[] {ProgramFile::typeid, AviSynthFile::typeid, ProfilesFile::typeid, MeGUIFile::typeid});
				StreamReader *settingsReader = new StreamReader(path);
				iUpgradeableCollection *upgradeDataTemp = static_cast<iUpgradeableCollection*>(serializer->Deserialize(settingsReader));
				delete settingsReader;

				for (MeGUI::UpdateWindow::iUpgradeableCollection::const_iterator file = upgradeDataTemp->begin(); file != upgradeDataTemp->end(); ++file)
				{
					if ((*file)->getName()->Equals("neroaacenc") && !MainForm::Instance->getSettings()->getUseNeroAacEnc())
						continue;
					if ((*file)->getName()->Equals("dgindexnv") && !MainForm::Instance->getSettings()->getUseDGIndexNV())
						continue;
					if ((*file)->getName()->Equals("qaac") && !MainForm::Instance->getSettings()->getUseQAAC())
						continue;
					this->upgradeData->Add(*file);
				}

				for (MeGUI::UpdateWindow::iUpgradeableCollection::const_iterator file = upgradeData->begin(); file != upgradeData->end(); ++file)
				{
					try
					{
						(*file)->init();
					}
					catch (FileNotRegisteredYetException *e1)
					{
					}
				}

				return; //settings loaded correctly
			}
			catch (std::exception &e2)
			{
				MessageBox::Show("Error: Could not load previous settings", "Error", MessageBoxButtons::OK);
				return; // error loading settings
			}
		}
	}

	void UpdateWindow::SaveSettings()
	{
		try
		{
			XmlSerializer *serializer = new XmlSerializer(iUpgradeableCollection::typeid, new Type[] {ProgramFile::typeid, AviSynthFile::typeid, ProfilesFile::typeid, MeGUIFile::typeid});
			StreamWriter *output = new StreamWriter(Path::Combine(Application::StartupPath, "AutoUpdate.xml"), false);
			serializer->Serialize(output, this->upgradeData);
			delete output;
			return; //settings saved
		}
		catch (std::exception &e1)
		{
			MessageBox::Show("Error: Could not save settings", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}

	void UpdateWindow::GetUpdateData(bool wait)
	{
		if (!isOrHasDownloadedUpgradeData)
		{
			Thread *CreateTreeview = new Thread(new ThreadStart(ProcessUpdateXML));
			CreateTreeview->IsBackground = true;
			CreateTreeview->Start();
			if (wait)
				webUpdate->WaitOne();
			DisplayItems(chkShowAllFiles->Checked);
		}
	}

	MeGUI::UpdateWindow::ErrorState UpdateWindow::GetUpdateXML(const std::string &strServerAddress)
	{
		if (upgradeXml != 0) // the update file has already been downloaded and processed
			return Successful;

		std::string data = "";
		upgradeXml = new XmlDocument();

		if (strServerAddress.empty())
		{
			// check local file
	#if defined(x86)
			std::string strLocalUpdateXML = Path::Combine(Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "upgrade.xml");
	#endif
	#if defined(x64)
			std::string strLocalUpdateXML = Path::Combine(Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "upgrade_x64.xml");
	#endif
			if (File::Exists(strLocalUpdateXML))
			{
				AddTextToLog("Retrieving local update file", Information);
				StreamReader *sr = new StreamReader(strLocalUpdateXML);
				data = sr->ReadToEnd();
				sr->Close();
				AddTextToLog("Local update file opened successfully", Information);
			}
			else
			{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
				delete upgradeXml;
				return ServerNotAvailable;
			}
		}
		else
		{
			WebClient *serverClient = new WebClient();

			// check for proxy authentication...
			serverClient->Proxy = HttpProxy::GetProxy(meGUISettings);

			try
			{
	#if defined(x86)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				data = serverClient->DownloadString(strServerAddress + "upgrade.xml?offCache=" + System::Guid::NewGuid()->ToString("N"));
	#endif
	#if defined(x64)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				data = serverClient->DownloadString(strServerAddress + "upgrade_x64.xml?offCache=" + System::Guid::NewGuid()->ToString("N"));
	#endif
			}
			catch (...)
			{
				AddTextToLog("Could not connect to server " + strServerAddress, Error);
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
				delete upgradeXml;
				return ServerNotAvailable;
			}
		}

		try
		{
			upgradeXml->LoadXml(data);
		}
		catch (...)
		{
			AddTextToLog("Invalid or missing update file. Aborting.", Error);
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete upgradeXml;
			return InvalidXML;
		}
		return Successful;
	}

	void UpdateWindow::ProcessUpdateXML()
	{
		isOrHasDownloadedUpgradeData = true;
		ErrorState value = ServerNotAvailable;
		for (std::vector<std::string>::const_iterator serverName = serverList.begin(); serverName != serverList.end(); ++serverName)
		{
			ServerAddress = *serverName;
			AddTextToLog("Connecting to server: " + *serverName, Information);
			value = GetUpdateXML(*serverName);
			if (value == Successful)
			{
				MainForm::Instance->getSettings()->setLastUpdateCheck(DateTime::Now::ToUniversalTime());
				MainForm::Instance->getSettings()->setLastUpdateServer(*serverName);
				break;
			}
		}

		if (value != Successful)
		{
			value = GetUpdateXML(0);
			if (value != Successful)
				return;
		}

		// I'd prefer the main thread to parse the upgradeXML as opposed to using this
		// "downloading" thread but i didn't know a better way of doing it other than
		// using a delegate like this.
		BeginParseUpgradeXml d = new BeginParseUpgradeXml(this, &UpdateWindow::ParseUpgradeXml);
		XmlNode *node = this->upgradeXml->SelectSingleNode("/UpdateableFiles");

		if (node != 0) // xml file could be dodgy.
		{
			if (listViewDetails->InvokeRequired)
			{
				listViewDetails->Invoke(d, node, 0, node->Name);
			}
			else
			{
				d(node, 0, node->Name);
			}
		}
		RemoveOldFiles();

		int iUpdatesCount = NumUpdatableFiles();
		if (iUpdatesCount > 1)
			AddTextToLog(std::string::Format("There are {0} files which can be updated.", iUpdatesCount), Information);
		else if (iUpdatesCount == 1)
			AddTextToLog("There is 1 file which can be updated.", Information);
		else
			AddTextToLog("All files are up to date", Information);

		bool bChecked = chkShowAllFiles->Checked;
		if (chkShowAllFiles->InvokeRequired)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			chkShowAllFiles->Invoke(new MethodInvoker(delegate
			{
				chkShowAllFiles->Checked = iUpdatesCount == 0;
			}
		   ));
		else
			chkShowAllFiles->Checked = iUpdatesCount == 0;
		if (chkShowAllFiles->Checked == bChecked)
		{
			if (chkShowAllFiles->InvokeRequired)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				chkShowAllFiles->Invoke(new MethodInvoker(delegate
				{
					DisplayItems(chkShowAllFiles->Checked);
				}
			   ));
			else
				DisplayItems(chkShowAllFiles->Checked);
		}

		webUpdate->Set();
	}

	void UpdateWindow::RemoveOldFiles()
	{
		iUpgradeable *iFileToRemove = 0;
		XmlNodeList *xnList = upgradeXml->SelectNodes("/UpdateableFiles");
		do
		{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete iFileToRemove;
			for (MeGUI::UpdateWindow::iUpgradeableCollection::const_iterator iFile = upgradeData->begin(); iFile != upgradeData->end(); ++iFile)
			{
				if (FindFileInUpdateXML(xnList, (*iFile)->getName()) == false)
				{
					iFileToRemove = *iFile;
					break;
				}
			}
			upgradeData->Remove(iFileToRemove);
		} while (iFileToRemove != 0);
	}

	bool UpdateWindow::FindFileInUpdateXML(XmlNodeList *xnList, const std::string &strFile)
	{
		for (XmlNodeList::const_iterator l1 = xnList->begin(); l1 != xnList->end(); ++l1)
		{
			if ((*l1)->Attributes["type"]->Value->Equals("file"))
			{
				if ((*l1)->Name->Equals(strFile))
					return true;
				continue;
			}
			if (FindFileInUpdateXML((*l1)->ChildNodes, strFile) == true)
				return true;
		}
		return false;
	}

	void UpdateWindow::ParseUpgradeXml(XmlNode *currentNode, XmlNode *groupNode, const std::string &path)
	{
		for (unknown::const_iterator childnode = currentNode->ChildNodes.begin(); childnode != currentNode->ChildNodes.end(); ++childnode)
		{
			if ((*childnode)->Attributes["type"]->Value->Equals("file"))
			{
				ParseFileData(*childnode, groupNode, path);
				continue;
			}

			std::string newPath = path + "." + (*childnode)->Name;
			if ((*childnode)->Attributes["type"]->Value->Equals("tree"))
				ParseUpgradeXml(*childnode, *childnode, newPath);
			else if ((*childnode)->Attributes["type"]->Value->Equals("subtree"))
				ParseUpgradeXml(*childnode, groupNode, newPath);
		}
	}

	void UpdateWindow::ParseFileData(XmlNode *node, XmlNode *groupNode, const std::string &treePath)
	{
		iUpgradeable *file = 0;
		Version *availableFile = 0;
		bool fileAlreadyAdded = false;

		if (node->Name->Equals("neroaacenc") && !MainForm::Instance->getSettings()->getUseNeroAacEnc())
			return;
		if (node->Name->Equals("dgindexnv") && !MainForm::Instance->getSettings()->getUseDGIndexNV())
			return;
		if (node->Name->Equals("qaac") && !MainForm::Instance->getSettings()->getUseQAAC())
			return;
		if (node->Name->Equals("x264_10b") && !MainForm::Instance->getSettings()->getUse10bitsX264())
			return;

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++0x inferred typing option is selected:
		var nameAttribute = node->Attributes["platform"];
		if (nameAttribute != 0)
		{
	#if defined(x86)
			if (nameAttribute->Value->Equals("x64"))
	#endif
	#if defined(x64)
			if (nameAttribute->Value->Equals("x86"))
	#endif
				return;
		}

		if ((file = upgradeData->FindByName(node->Name)) == 0) // If this file isn't already in the upgradeData list
		{
			try
			{
				if (groupNode->Name->Equals("MeGUI"))
					file = new MeGUIFile(treePath, node->Name);
				else if (groupNode->Name->Equals("ProgramFile"))
					file = new ProgramFile(treePath, node->Name);
				else if (groupNode->Name->Equals("AviSynthFile"))
					file = new AviSynthFile(treePath, node->Name);
				else if (groupNode->Name->Equals("ProfilesFile"))
					file = new ProfilesFile(treePath, node->Name, mainForm);
				else
					return;
			}
			catch (FileNotRegisteredYetException *e1)
			{
				return;
			}
		}
		else
		{
			file->setAvailableVersions(new Versions());
			file->setDownloadChecked(false);
			file->treeViewID = treePath;
			fileAlreadyAdded = true;
			if (dynamic_cast<ProfilesFile*>(file) != 0)
				(dynamic_cast<ProfilesFile*>(file))->setMainForm(mainForm);
		}

		file->setPlatform(iUpgradeable::any);
		if (nameAttribute != 0)
		{
			if (nameAttribute->Value->Equals("x86"))
				file->setPlatform(iUpgradeable::x86);
			else if (nameAttribute->Value->Equals("x64"))
				file->setPlatform(iUpgradeable::x64);
		}

		file->setNeedsRestartedCopying(false);
		nameAttribute = node->Attributes["needsrestart"];
		if (nameAttribute != 0)
		{
			if (nameAttribute->Value->Equals("true"))
				file->setNeedsRestartedCopying(true);
		}

		file->setRequiredBuild(0);
		nameAttribute = node->Attributes["requiredbuild"];
		if (nameAttribute != 0)
		{
			file->setRequiredBuild(int::Parse(nameAttribute->Value));
		}

		file->setDisplayName(node->Name);
		nameAttribute = node->Attributes["name"];
		if (nameAttribute != 0)
		{
			file->setDisplayName(nameAttribute->Value);
		}

		file->setRequiredNET("");
		nameAttribute = node->Attributes["net"];
		if (nameAttribute != 0)
		{
			file->setRequiredNET(nameAttribute->Value);
		}

		for (unknown::const_iterator filenode = node->ChildNodes.begin(); filenode != node->ChildNodes.end(); ++filenode) // each filenode contains the upgrade url and version
		{
			availableFile = new Version();
			availableFile->setUrl((*filenode)->FirstChild->Value);

			for (unknown::const_iterator oAttribute = filenode->Attributes.begin(); oAttribute != filenode->Attributes.end(); ++oAttribute)
			{
				if ((*oAttribute)->Name->Equals("version"))
					availableFile->setFileVersion((*filenode)->Attributes["version"]->Value);
				else if ((*oAttribute)->Name->Equals("date"))
				{
					DateTime oDate = DateTime();
					DateTime::TryParse((*filenode)->Attributes["date"]->Value, new System::Globalization::CultureInfo("en-us"), System::Globalization::DateTimeStyles::None, oDate);
					availableFile->setUploadDate(oDate);
				}
				else if ((*oAttribute)->Name->Equals("url"))
				{
					availableFile->setWeb((*filenode)->Attributes["url"]->Value);
				}
			}

			file->getAvailableVersions()->Add(availableFile);
		}
		if (file->GetLatestVersion()->compare(file->getCurrentVersion()) != 0 && file->getAllowUpdate() && file->getHasAvailableVersions())
			file->setDownloadChecked(true);

		if (!fileAlreadyAdded)
			upgradeData->Add(file);
	}

	void UpdateWindow::DisplayItems(bool bShowAllFiles)
	{
		ClearListview(this->listViewDetails);

		for (MeGUI::UpdateWindow::iUpgradeableCollection::const_iterator file = upgradeData->begin(); file != upgradeData->end(); ++file)
		{
			if (!bShowAllFiles)
			{
				if ((*file)->getHasAvailableVersions() || (*file)->getDownloadChecked())
					AddToListview((*file)->CreateListViewItem());
			}
			else
			{
				AddToListview((*file)->CreateListViewItem());
			}
		}
	}

	void UpdateWindow::listViewDetails_ItemCheck(object *sender, ItemCheckEventArgs *e)
	{
		ListViewItem *itm = this->listViewDetails->Items[e->Index];
		// Do not allow checking if there are no updates or it is set to ignore.
		if (itm->SubItems["Status"]->Text->Equals("No Update Available") || itm->SubItems["Status"]->Text->Equals("Update Ignored"))
			e->NewValue = CheckState::Unchecked;

		iUpgradeable *file = upgradeData->FindByName(itm->Name);
		if (e->NewValue == CheckState->Checked)
			file->setDownloadChecked(true);
		else
			file->setDownloadChecked(false);

		if (e->NewValue == CheckState::Unchecked && itm->SubItems["Status"]->Text == "Reinstalling")
			itm->SubItems["Status"]->Text = file->getAllowUpdate() ? (file->getHasAvailableVersions() ? "Update Available" : "No Update Available") : "Update Ignored";
	}

	void UpdateWindow::listViewDetails_MouseClick(object *sender, MouseEventArgs *e)
	{
		if (e->Button == MouseButtons::Right)
		{
			if (listViewDetails->SelectedItems->Count > 0)
			{
				ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(statusToolStrip->Items[0]);
				bool allowupdate = false;
				for (unknown::const_iterator item = listViewDetails->SelectedItems.begin(); item != listViewDetails->SelectedItems.end(); ++item)
				{
					allowupdate |= upgradeData->FindByName((*item)->Name)->getAllowUpdate();
				}
				ts->Checked = !allowupdate;
				statusToolStrip->Show(Cursor::Position);
			}
		}
	}

	void UpdateWindow::setIgnoreValue_Click(object *sender, EventArgs *e)
	{
		ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(sender);
		for (unknown::const_iterator item = listViewDetails->SelectedItems.begin(); item != listViewDetails->SelectedItems.end(); ++item)
		{
			iUpgradeable *file = upgradeData->FindByName((*item)->Name);

			file->setAllowUpdate(!(ts->Checked));
			Version *latest = file->GetLatestVersion();

			if (file->getAllowUpdate())
			{
				if (latest == 0 && file->getCurrentVersion() == 0)
				{
					(*item)->SubItems["Status"]->Text = "No Update Available";
					(*item)->Checked = false;
				}
				else if (latest != 0 && file->getCurrentVersion() == 0)
				{
					(*item)->SubItems["Status"]->Text = "Update Available";
					(*item)->Checked = true;
				}
				else if (latest->compare(file->getCurrentVersion()) != 0)
				{
					(*item)->SubItems["Status"]->Text = "Update Available";
					(*item)->Checked = true;
				}
				else
					(*item)->SubItems["Status"]->Text = "No Update Available";
			}
			else
			{
				(*item)->Checked = false;
				(*item)->SubItems["Status"]->Text = "Update Ignored";
			}
		}
	}

	void UpdateWindow::StartAutoUpdate()
	{
		btnUpdate_Click(0, 0);
	}

	void UpdateWindow::btnUpdate_Click(object *sender, EventArgs *e)
	{
		btnUpdate->Enabled = false;
		btnAbort->Enabled = true;
		updateThread = new Thread(new ThreadStart(BeginUpdate));
		updateThread->IsBackground = true;
		updateThread->Start();
	}

	void UpdateWindow::InstallFiles(SortedDictionary<unsigned int, std::vector<iUpgradeable*>*> *groups)
	{
		continueUpdate = true;
		int currentFile = 1; //the first file we update is file 1.
		ErrorState result;
		std::vector<iUpgradeable*> succeededFiles = std::vector<iUpgradeable*>();
		std::vector<iUpgradeable*> failedFiles = std::vector<iUpgradeable*>();
		std::vector<iUpgradeable*> missingFiles = std::vector<iUpgradeable*>();

		// Count the number of files we can update before we restart
		int updateableFileCount = 0;
		bool needsRestart = false;
		for (SortedDictionary<unsigned int, std::vector<iUpgradeable*>*>::const_iterator group = groups->begin(); group != groups->end(); ++group)
			updateableFileCount += (*group).Count;

		// Now update the files we can
		for (SortedDictionary<unsigned int, std::vector<iUpgradeable*>*>::const_iterator group = groups->begin(); group != groups->end(); ++group)
		{
			for (std::vector::const_iterator file = group.begin(); file != group.end(); ++file)
			{
				if (!continueUpdate)
				{
					AddTextToLog("Update aborted by user", Information);
					return; // false
				}

				AddTextToLog(std::string::Format("Updating {0}. File {1}/{2}.", (*file)->getName(), currentFile, updateableFileCount), Information);

				if (!((*file)->GetLatestVersion()->Web)->empty())
				{
					std::string strText;

					if ((*file)->getName()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("neroaacenc"))
					{
						std::string strPath = System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath) + "\\tools\\eac3to\\neroAacEnc.exe";
						strText = "MeGUI cannot find " + (*file)->getName() + " on your system or it is outdated.\nDue to the licensing the component is not included on the MeGUI update server.\n\nTherefore please download the file on your own and extract neroaacenc.exe to:\n" + strPath + "\n\nIf necessary change the path in the settings:\n\"Settings\\External Program Settings\"\n\nDo you would like to download it now?";
					}
					else
						strText = "MeGUI cannot find " + (*file)->getName() + " on your system or it is outdated.\nDue to the licensing the component is not included on the MeGUI update server.\n\nTherefore please download the file on your own, extract it and set the path to the " + (*file)->getName() + ".exe in the MeGUI settings\n(\"Settings\\External Program Settings\").\n\nDo you would like to download it now?";

					if (MessageBox::Show(strText, "Component not found", MessageBoxButtons::YesNo, MessageBoxIcon::Information) == System::Windows::Forms::DialogResult::Yes)
					{
						System::Diagnostics::Process::Start((*file)->GetLatestVersion()->Web);
						succeededFiles.push_back(*file);
					}
					else
						failedFiles.push_back(*file);
				}
				else
				{
					Stream *str;
					result = UpdateCacher::DownloadFile((*file)->GetLatestVersion()->Url, new Uri(ServerAddress), str, wc_DownloadProgressChanged, this);
					if (result != Successful)
					{
						failedFiles.push_back(*file);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						AddTextToLog(std::string::Format("Failed to download file {0} with error: {1}.", (*file)->getName(), EnumProxy::Create(result)->ToString()), Error);
					}
					else
					{
						try
						{
							ErrorState state;
							if ((*file)->getNeedsInstalling())
								state = Install(*file, str);
							else
								state = SaveNewFile(*file, str);

							if (state != Successful)
							{
								if (state != RequirementNotMet)
								{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
									AddTextToLog(std::string::Format("Failed to install file {0} with error: {1}.", (*file)->getName(), EnumProxy::Create(state)->ToString()), Error);
									failedFiles.push_back(*file);
								}
								else
									missingFiles.push_back(*file);
							}
							else
							{
								succeededFiles.push_back(*file);
								(*file)->setDownloadChecked(false);
								if ((*file)->getNeedsRestartedCopying())
									needsRestart = true;
							}
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
						finally
						{
							str->Close();
						}
					}
				}
				currentFile++;
			}

			if (currentFile >= updateableFileCount)
				break;
		}

		SetProgressBar(0, 1, 1); //make sure progress bar is at 100%.

		if (succeededFiles.size() > 0)
			AddTextToLog("Files which have been successfully updated: " + succeededFiles.size(), Information);
		if (failedFiles.size() + missingFiles.size() > 0)
		{
			if (failedFiles.empty())
				AddTextToLog("Files which have not been successfully updated: " + missingFiles.size(), Warning);
			else
				AddTextToLog("Files which have not been successfully updated: " + (failedFiles.size() + missingFiles.size()), Error);
		}
		else
		{
	#if defined(x86)
			std::string strLocalUpdateXML = Path::Combine(Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "upgrade.xml");
	#endif
	#if defined(x64)
			std::string strLocalUpdateXML = Path::Combine(Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath), "upgrade_x64.xml");
	#endif
			if (File::Exists(strLocalUpdateXML))
				File::Delete(strLocalUpdateXML);
		}

		// call function so that avisynth dlls will be copied to the root if needed
		VideoUtil::getAvisynthVersion(0);

		std::vector<std::string> files = std::vector<std::string>();
		for (MeGUI::UpdateWindow::iUpgradeableCollection::const_iterator u = upgradeData->begin(); u != upgradeData->end(); ++u)
			files.push_back((*u)->GetLatestVersion()->Url);
		UpdateCacher::flushOldCachedFilesAsync(files, this);

		if (needsRestart)
		{
			if (MessageBox::Show("In order to finish the update, MeGUI needs to be restarted. Do you want to restart now?", "Restart now?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
			{
				mainForm->setRestart(true);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				this->Invoke(new MethodInvoker(delegate
				{
					this->Close();
				}
			   ));
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				mainForm->Invoke(new MethodInvoker(delegate
				{
					mainForm->Close();
				}
			   ));
				return; // true
			}
		}
		if (MainForm::Instance->getSettings()->getAutoUpdateSession())
		{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			this->Invoke(new MethodInvoker(delegate
			{
				this->Close();
			}
		   ));
			return;
		}
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		listViewDetails->Invoke(new MethodInvoker(delegate
		{
			DisplayItems(chkShowAllFiles->Checked);
		}
	   ));
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		Invoke(new MethodInvoker(delegate
		{
			btnAbort->Enabled = false;
			btnUpdate->Enabled = true;
		}
	   ));
	}

	void UpdateWindow::BeginUpdate()
	{
		// Sort the files to download according to their install priority
		SortedDictionary<unsigned int, std::vector<iUpgradeable*>*> *groups = new SortedDictionary<unsigned int, std::vector<iUpgradeable*>*>();
		for (MeGUI::UpdateWindow::iUpgradeableCollection::const_iterator file = upgradeData->begin(); file != upgradeData->end(); ++file)
		{
			if ((*file)->getDownloadChecked())
			{
				if (!groups->ContainsKey(0))
					groups[0] = std::vector<iUpgradeable*>();
				groups[0].push_back(*file);
			}
		}

		InstallFiles(groups); //, false
	}

	MeGUI::UpdateWindow::ErrorState UpdateWindow::Install(iUpgradeable *file, Stream *fileData)
	{
		if (file->getRequiredBuild() > 0 && (new System::Version(Application::ProductVersion))->Build < file->getRequiredBuild())
		{
			AddTextToLog(std::string::Format("Could not install module '{0}' as at least MeGUI build {1} is required.", file->getName(), file->getRequiredBuild()), Warning);
			return RequirementNotMet;
		}

		if (!file->getRequiredNET().empty() && (OSInfo::GetDotNetVersion(file->getRequiredNET())).empty())
		{
			AddTextToLog(std::string::Format("Could not install module '{0}' as .NET {1} is required.", file->getName(), file->getRequiredNET()), Warning);
			return RequirementNotMet;
		}

		ErrorState state = file->Install(fileData);
		if (state == Successful)
		{
			file->setCurrentVersion(file->GetLatestVersion());
			return Successful;
		}

		AddTextToLog(std::string::Format("Could not install module '{0}'.", file->getName()), Error);
		return state;
	}

	MeGUI::UpdateWindow::ErrorState UpdateWindow::SaveNewFile(iUpgradeable *file, Stream *data)
	{
		if (file->getRequiredBuild() > 0 && (new System::Version(Application::ProductVersion))->Build < file->getRequiredBuild())
		{
			AddTextToLog(std::string::Format("Could not install module '{0}' as at least MeGUI build {1} is required.", file->getName(), file->getRequiredBuild()), Warning);
			return RequirementNotMet;
		}

		if (!file->getRequiredNET().empty() && (OSInfo::GetDotNetVersion(file->getRequiredNET())).empty())
		{
			AddTextToLog(std::string::Format("Could not install module '{0}' as .NET {1} is required.", file->getName(), file->getRequiredNET()), Warning);
			return RequirementNotMet;
		}

		std::string filepath = "", filename = "";
		if (file->getSaveFolder() != "")
			filepath = file->getSaveFolder();
		else if (file->getSavePath() != "")
			filepath = Path::GetDirectoryName(file->getSavePath());
		else
		{
			AddTextToLog("The path to save " + file->getName() + " to is invalid.", Error);
			return CouldNotSaveNewFile;
		}
		if (file->getSavePath() != "")
			filename = file->getSavePath();
		else
			filename = filepath + "\\" + Path::GetFileName(file->GetLatestVersion()->getUrl());

		try
		{
			if (!Directory::Exists(filepath))
				Directory::CreateDirectory(filepath);
		}
		catch (IOException *e1)
		{
			AddTextToLog(std::string::Format("Could not create directory {0}.", filepath), Error);
			return CouldNotSaveNewFile;
		}

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (file->GetLatestVersion()->getUrl().EndsWith(".zip"))
		{
			try
			{
				ZipFile *zipFile = new ZipFile(Path::Combine(MainForm::Instance->getSettings()->getMeGUIUpdateCache(), Path::GetFileName(file->GetLatestVersion()->getUrl())));
				if (zipFile->TestArchive(true) == false)
				{
					AddTextToLog("Could not unzip " + file->getName() + ". Deleting file. Please run updater again.", Error);
					UpdateCacher::FlushFile(file->GetLatestVersion()->getUrl(), this);
					return CouldNotUnzip;
				}

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (ZipInputStream zip = new ZipInputStream(data))
				ZipInputStream *zip = new ZipInputStream(data);
				try
				{
					ZipEntry *zipentry;
					while ((zipentry = zip->GetNextEntry()) != 0)
					{
						filename = Path::Combine(filepath, zipentry->Name);
						if (zipentry->IsDirectory)
						{
							if (!Directory::Exists(filename))
								Directory::CreateDirectory(filename);
							continue;
						}
						if (mainForm->getSettings()->getAlwaysBackUpFiles())
						{
							ErrorState result = manageBackups(filename, file->getName(), file->getNeedsRestartedCopying());
							if (result != Successful)
								return result;
						}
						std::string oldFileName = "";
						if (file->getNeedsRestartedCopying())
						{
							oldFileName = filename;
							filename += ".tempcopy";
						}
						// create the output writer to save the file onto the harddisc
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//						using (Stream outputWriter = new FileStream(filename, FileMode.Create))
						Stream *outputWriter = new FileStream(filename, FileMode::Create);
						try
						{
							FileUtil::copyData(zip, outputWriter);
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
						finally
						{
							if (outputWriter != 0)
								outputWriter.Dispose();
						}
						File::SetLastWriteTime(filename, zipentry->DateTime);
						if (file->getNeedsRestartedCopying())
						{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
							mainForm->AddFileToReplace(file->getName(), filename, oldFileName, file->GetLatestVersion()->getUploadDate().ToString(new System::Globalization::CultureInfo("en-us")));
							file->getCurrentVersion()->setFileVersion(file->GetLatestVersion()->getFileVersion());
							needsRestart = true;
						}
					}
					if (!file->getNeedsRestartedCopying())
						file->setCurrentVersion(file->GetLatestVersion()); // the current installed version
					// is now the latest available version
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (zip != 0)
						zip.Dispose();
				}
			}
			catch (...)
			{
				AddTextToLog("Could not unzip " + file->getName() + ". Deleting file. Please run updater again.", Error);
				UpdateCacher::FlushFile(file->GetLatestVersion()->getUrl(), this);
				return CouldNotUnzip;
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		else if (file->GetLatestVersion()->getUrl().EndsWith(".7z"))
		{
			try
			{
				SevenZipExtractor *oArchiveCheck = new SevenZipExtractor(data);
				if (oArchiveCheck->Check() == false)
				{
					AddTextToLog("Could not extract " + file->getName() + ". Deleting file. Please run updater again.", Error);
					UpdateCacher::FlushFile(file->GetLatestVersion()->getUrl(), this);
					return CouldNotUnzip;
				}

				bool bNeedRestartForCopying = false;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (var oArchive = new SevenZipExtractor(data))
				SevenZipExtractor *oArchive = new SevenZipExtractor(data);
				try
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					oArchive->Extracting += (s, e) =>
						SetProgressBar(0, 100, e::PercentDone);
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (oArchive != 0)
						oArchive.Dispose();
				};
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					oArchive->FileExists += (o, e) =>
					{
						if (mainForm->getSettings()->getAlwaysBackUpFiles())
						{
							ErrorState result = manageBackups(e::FileName, file->getName(), file->getNeedsRestartedCopying());
							if (result != Successful)
							{
								e->Cancel = true;
								return;
							}
						}
						if (file->getNeedsRestartedCopying())
						{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
							mainForm->AddFileToReplace(file->getName(), e::FileName + ".tempcopy", e::FileName, file->GetLatestVersion()->getUploadDate().ToString(new System::Globalization::CultureInfo("en-us")));
							needsRestart = true;
							e::FileName += ".tempcopy";
							bNeedRestartForCopying = true;
						}
					};
					oArchive->ExtractArchive(filepath);
					if (bNeedRestartForCopying == false)
						file->setCurrentVersion(file->GetLatestVersion()); // the current installed version is now the latest available version
					else
						file->getCurrentVersion()->setFileVersion(file->GetLatestVersion()->getFileVersion()); // after the restart the new files will be active
			}
		}
			catch (...)
			{
				AddTextToLog("Could not unzip " + file->getName() + ". Deleting file. Please run updater again.", Error);
				UpdateCacher::FlushFile(file->GetLatestVersion()->getUrl(), this);
				return CouldNotUnzip;
			}
	}

	private *UpdateWindow::if_Renamed(mainForm->Settings->AlwaysBackUpFiles)
	{
		ErrorState result = manageBackups(filename, file->Name, file::NeedsRestartedCopying);
		if (result != Successful)
			return result;
	}

	private *UpdateWindow::if_Renamed(file::NeedsRestartedCopying)
	{
		oldFileName = filename;
		filename = filename + ".tempcopy";
	}

	void UpdateWindow::InitializeInstanceFields()
	{
		delete mainForm;
		continueUpdate = true;
		delete upgradeData;
		delete updateThread;
		logBuilder = new StringBuilder();
		webUpdate = new ManualResetEvent(false);
		delete upgradeXml;
		needsRestart = false;
		isOrHasDownloadedUpgradeData = false;
		delete components;
	}
}
