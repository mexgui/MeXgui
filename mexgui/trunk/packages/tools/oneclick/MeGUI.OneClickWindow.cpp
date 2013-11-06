#include "MeGUI.OneClickWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::tools::oneclick;

namespace MeGUI
{

	void OneClickWindow::initOneClickHandler()
	{
		oneclickProfile->setManager(mainForm->getProfiles());
	}

	void OneClickWindow::initTabs()
	{
		audioTracks = std::vector<OneClickStreamControl*>();
		audioTracks.push_back(oneClickAudioStreamControl1);
		oneClickAudioStreamControl1->setStandardStreams(new object[] {"None"});
		oneClickAudioStreamControl1->setSelectedStreamIndex(0);
		oneClickAudioStreamControl1->setFilter(VideoUtil::GenerateCombinedFilter(ContainerManager::AudioTypes->getValuesArray()));

		subtitleTracks = std::vector<OneClickStreamControl*>();
		subtitleTracks.push_back(oneClickSubtitleStreamControl1);
		oneClickSubtitleStreamControl1->setStandardStreams(new object[] {"None"});
		oneClickSubtitleStreamControl1->setSelectedStreamIndex(0);
		oneClickSubtitleStreamControl1->setFilter(VideoUtil::GenerateCombinedFilter(ContainerManager::SubtitleTypes->getValuesArray()));
	}

	void OneClickWindow::OneClickProfileChanged(object *sender, EventArgs *e)
	{
		SetOneClickProfile(static_cast<OneClickSettings*>(oneclickProfile->getSelectedProfile()->BaseSettings));
	}

	const VideoCodecSettings &OneClickWindow::getVideoSettings() const
	{
		return static_cast<VideoCodecSettings*>(videoProfile->getSelectedProfile()->BaseSettings);
	}

	void OneClickWindow::initAudioHandler()
	{
		oneClickAudioStreamControl1->initProfileHandler();
		oneClickSubtitleStreamControl1->initProfileHandler();
	}

	OneClickWindow::OneClickWindow(MainForm *mainForm)
	{
		InitializeInstanceFields();
		this->mainForm = mainForm;
		this->_oLog = mainForm->getOneClickLog();
		if (_oLog == 0)
		{
			_oLog = mainForm->getLog()->Info("OneClick");
			mainForm->setOneClickLog(_oLog);
		}
		vUtil = new VideoUtil(mainForm);
		this->muxProvider = mainForm->getMuxProvider();
		acceptableContainerTypes = muxProvider->GetSupportedContainers().ToArray();
		InitializeComponent();
		videoProfile->setManager(mainForm->getProfiles());
		initTabs();
		initAudioHandler();
		avsProfile->setManager(mainForm->getProfiles());
		initOneClickHandler();

		//if containerFormat has not yet been set by the oneclick profile, add supported containers
		if (containerFormat->Items->Count == 0)
		{
			containerFormat->Items->AddRange(muxProvider->GetSupportedContainers().ToArray());
			this->containerFormat->SelectedIndex = 0;
		}

		//add device type
		if (devicetype->Items->Count == 0)
		{
			devicetype->Items->Add("Standard");
			devicetype->Items->AddRange(muxProvider->GetSupportedDevices(static_cast<ContainerType*>(this->containerFormat->SelectedItem)).ToArray());
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (containerFormat->SelectedItem->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getContainer()))
		{
			for (unknown::const_iterator o = devicetype->Items.begin(); o != devicetype->Items.end(); ++o) // I know this is ugly, but using the DeviceOutputType doesn't work unless we're switching to manual serialization
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				if ((*o)->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getDeviceOutputType()))
				{
					devicetype->SelectedItem = *o;
					break;
				}
			}
		}
		else
			this->devicetype->SelectedIndex = 0;

		bLock = true;
		cbGUIMode->DataSource = EnumProxy::CreateArray(new object[] {MeGUISettings::Basic, MeGUISettings::Default, MeGUISettings::Advanced});
		bLock = false;

		if (MainForm::Instance->getSettings()->IsDGIIndexerAvailable())
			input->setFilter("All supported files|*.avs;*.ifo;*.mkv;*.avi;*.mp4;*.flv;*.wmv;*.ogm;*.264;*.h264;*.avc;*.m2t*;*.m2ts;*.mts;*.tp;*.ts;*.trp;*.vob;*.ifo;*.mpg;*.mpeg;*.m1v;*.m2v;*.mpv;*.pva;*.vro;*.vc1;*.mpls|All DGAVCIndex supported files|*.264;*.h264;*.avc;*.m2t*;*.m2ts;*.mts;*.tp;*.ts;*.trp|All DGIndex supported files|*.vob;*.mpg;*.mpeg;*.m1v;*.m2v;*.mpv;*.tp;*.ts;*.trp;*.m2t;*.m2ts;*.pva;*.vro|All DGIndexNV supported files|*.264;*.h264;*.avc;*.m2v;*.mpv;*.vc1;*.mkv;*.vob;*.mpg;*.mpeg;*.m2t;*.m2ts;*.mts;*.tp;*.ts;*.trp|All FFMS Indexer supported files|*.mkv;*.avi;*.mp4;*.flv;*.wmv;*.ogm;*.vob;*.mpg;*.m2ts;*.ts|AviSynth Scripts|*.avs|IFO DVD files|*.ifo|Blu-Ray Playlist|*.mpls|All files|*.*");
		else
			input->setFilter("All supported files|*.avs;*.ifo;*.mkv;*.avi;*.mp4;*.flv;*.wmv;*.ogm;*.264;*.h264;*.avc;*.m2t*;*.m2ts;*.mts;*.tp;*.ts;*.trp;*.vob;*.ifo;*.mpg;*.mpeg;*.m1v;*.m2v;*.mpv;*.pva;*.vro;*.mpls|All DGAVCIndex supported files|*.264;*.h264;*.avc;*.m2t*;*.m2ts;*.mts;*.tp;*.ts;*.trp|All DGIndex supported files|*.vob;*.mpg;*.mpeg;*.m1v;*.m2v;*.mpv;*.tp;*.ts;*.trp;*.m2t;*.m2ts;*.pva;*.vro|All FFMS Indexer supported files|*.mkv;*.avi;*.mp4;*.flv;*.wmv;*.ogm;*.vob;*.mpg;*.m2ts;*.ts|AviSynth Scripts|*.avs|IFO DVD files|*.ifo|Blu-Ray Playlist|*.mpls|All files|*.*");
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		DragDropUtil::RegisterMultiFileDragDrop(input, setInput, delegate()
		{
			return input->getFilter() + "|All folders|*.";
		}
	   );
		DragDropUtil::RegisterSingleFileDragDrop(output, new SingleFileReceiver(this, &OneClickWindow::setOutput));
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		DragDropUtil::RegisterSingleFileDragDrop(chapterFile, 0, delegate()
		{
			return chapterFile->getFilter();
		}
	   );
		DragDropUtil::RegisterSingleFileDragDrop(workingDirectory, new SingleFileReceiver(this, &OneClickWindow::setWorkingDirectory));
	}

	void OneClickWindow::cbGUIMode_SelectedIndexChanged(object *sender, EventArgs *e)
	{
		EnumProxy *o = dynamic_cast<EnumProxy*>(cbGUIMode->SelectedItem);
		if (o == 0)
			return;

		if (bLock)
			cbGUIMode->SelectedItem = EnumProxy::Create(MainForm::Instance->getSettings()->getOneClickGUIMode());
		else
			MainForm::Instance->getSettings()->setOneClickGUIMode(static_cast<MeGUISettings::OCGUIMode>(o->getRealValue()));

		if (MainForm::Instance->getSettings()->getOneClickGUIMode() == MeGUISettings::Advanced)
		{
			audioTab->Height = 175;
			subtitlesTab->Location = new Point(subtitlesTab->Location->X, 258);
			subtitlesTab->Visible = true;
			outputTab->Location = new Point(outputTab->Location->X, 379);
			this->Height = 583;
			if (!tabControl1->TabPages->Contains(encoderConfigTab))
				tabControl1->TabPages->Add(encoderConfigTab);
		}
		else if (MainForm::Instance->getSettings()->getOneClickGUIMode() == MeGUISettings::Basic)
		{
			audioTab->Height = 90;
			subtitlesTab->Visible = false;
			outputTab->Location = new Point(outputTab->Location->X, 173);
			this->Height = 377;
			if (tabControl1->TabPages->Contains(encoderConfigTab))
				tabControl1->TabPages->Remove(encoderConfigTab);
		}
		else
		{
			audioTab->Height = 115;
			subtitlesTab->Location = new Point(subtitlesTab->Location->X, 198);
			subtitlesTab->Visible = true;
			outputTab->Location = new Point(outputTab->Location->X, 319);
			this->Height = 523;
			if (tabControl1->TabPages->Contains(encoderConfigTab))
				tabControl1->TabPages->Remove(encoderConfigTab);
		}
	}

	void OneClickWindow::containerFormat_SelectedIndexChanged(object *sender, EventArgs *e)
	{
		if (this->containerFormat->Text == "MKV")
			this->devicetype->Enabled = false;
		else
			this->devicetype->Enabled = true;
		updateFilename();

		//add device types
		devicetype->Items->Clear();
		devicetype->Items->Add("Standard");
		devicetype->Items->AddRange(muxProvider->GetSupportedDevices(static_cast<ContainerType*>(this->containerFormat->SelectedItem)).ToArray());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (containerFormat->SelectedItem->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getContainer()))
		{
			for (unknown::const_iterator o = devicetype->Items.begin(); o != devicetype->Items.end(); ++o) // I know this is ugly, but using the DeviceOutputType doesn't work unless we're switching to manual serialization
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				if ((*o)->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getDeviceOutputType()))
				{
					devicetype->SelectedItem = *o;
					break;
				}
			}
		}
		else
			this->devicetype->SelectedIndex = 0;
	}

	void OneClickWindow::updateWorkingName(const std::string &strInputFile)
	{
		int iPGCNumber = 0;
		if (_videoInputInfo != 0)
			iPGCNumber = _videoInputInfo->getVideoInfo()->PGCNumber;

		if (iPGCNumber > 1)
		{
			std::string strTempName = Path::GetFileNameWithoutExtension(strInputFile);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if (strTempName.StartsWith("VTS_", StringComparison::InvariantCultureIgnoreCase) && strTempName.EndsWith("1", StringComparison::InvariantCultureIgnoreCase))
			{
				strTempName = strTempName.substr(0, strTempName.length() - 1) + iPGCNumber;
				strTempName = Path::Combine(Path::GetDirectoryName(strInputFile), strTempName + Path::GetExtension(strInputFile));
				workingName->Text = PrettyFormatting::ExtractWorkingName(strTempName, _oSettings->getLeadingName(), _oSettings->getWorkingNameReplace(), _oSettings->getWorkingNameReplaceWith());
			}
			else
				workingName->Text = PrettyFormatting::ExtractWorkingName(strInputFile, _oSettings->getLeadingName(), _oSettings->getWorkingNameReplace(), _oSettings->getWorkingNameReplaceWith());
		}
		else
			workingName->Text = PrettyFormatting::ExtractWorkingName(strInputFile, _oSettings->getLeadingName(), _oSettings->getWorkingNameReplace(), _oSettings->getWorkingNameReplaceWith());

		this->updateFilename();
	}

	void OneClickWindow::updateFilename()
	{
		if (!outputChosen)
		{
			std::string strVideoInput = input->getSelectedText();
			if (!strVideoInput.empty() && File::Exists(strVideoInput))
			{
				if (!_oSettings->getDefaultOutputDirectory().empty() && Directory::Exists(_oSettings->getDefaultOutputDirectory()))
				{
					output->setFilename(Path::Combine(_oSettings->getDefaultOutputDirectory(), workingName->Text + "." + (static_cast<ContainerType*>(containerFormat->SelectedItem))->getExtension()));
				}
				else if (!MainForm::Instance->getSettings()->getDefaultOutputDir().empty() && Directory::Exists(MainForm::Instance->getSettings()->getDefaultOutputDir()))
				{
					output->setFilename(Path::Combine(MainForm::Instance->getSettings()->getDefaultOutputDir(), workingName->Text + "." + (static_cast<ContainerType*>(containerFormat->SelectedItem))->getExtension()));
				}
				else
				{
					output->setFilename(Path::Combine(Path::GetDirectoryName(strVideoInput), workingName->Text + "." + (static_cast<ContainerType*>(containerFormat->SelectedItem))->getExtension()));
				}
			}
			else
			{
				output->setFilename(Path::ChangeExtension(output->getFilename(), (static_cast<ContainerType*>(containerFormat->SelectedItem))->getExtension()));
			}
			outputChosen = false;
		}
		else
		{
			output->setFilename(Path::ChangeExtension(output->getFilename(), (static_cast<ContainerType*>(containerFormat->SelectedItem))->getExtension()));
		}
		output->setFilter((static_cast<ContainerType*>(containerFormat->SelectedItem))->getOutputFilterString());
	}

	void OneClickWindow::input_SelectionChanged(object *sender, const std::string &val)
	{
		if (!input->getSelectedText().empty())
		{
			if (!bAutomatedProcessing && !bLock)
				openInput(input->getSelectedText());
		}
	}

	void OneClickWindow::setOutput(const std::string &strFileName)
	{
		output->setFilename(strFileName);
		output_FileSelected(0, 0);
	}

	void OneClickWindow::output_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		outputChosen = true;
		updateFilename();
	}

	void OneClickWindow::setWorkingDirectory(const std::string &strFolder)
	{
		workingDirectory->setFilename(strFolder);
		updateFilename();
	}

	void OneClickWindow::workingDirectory_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		if (File::Exists(workingDirectory->getFilename()))
			workingDirectory->setFilename(Path::GetDirectoryName(workingDirectory->getFilename()));
		updateFilename();
	}

	void OneClickWindow::workingName_TextChanged(object *sender, EventArgs *e)
	{
		updateFilename();
	}

	void OneClickWindow::setInput(const std::string &strFileorFolderName)
	{
		input->AddCustomItem(strFileorFolderName);
		input->setSelectedObject(strFileorFolderName);
	}

	void OneClickWindow::setInput(std::string& strFileorFolderName[])
	{
		std::vector<OneClickFilesToProcess*> arrFilesToProcess = std::vector<OneClickFilesToProcess*>();
		for (std::string::const_iterator strFile = strFileorFolderName->begin(); strFile != strFileorFolderName->end(); ++strFile)
			if (File::Exists(*strFile))
				arrFilesToProcess.push_back(new OneClickFilesToProcess(*strFile, 1));
		if (arrFilesToProcess.empty())
		{
			MessageBox::Show("These files or folders cannot be used in OneClick mode.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
		goButton->Enabled = false;
		OneClickProcessing *oProcessor = new OneClickProcessing(this, arrFilesToProcess, _oSettings, _oLog);
	}

	void OneClickWindow::openInput(const std::string &fileName)
	{
		if (!Directory::Exists(fileName) && !File::Exists(fileName))
		{
			MessageBox::Show("Input " + fileName + " does not exists", "Input not found", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
		goButton->Enabled = false;
		OneClickProcessing *oProcessor = new OneClickProcessing(this, fileName, _oSettings, _oLog);
	}

	void OneClickWindow::setOpenFailure()
	{
		this->Cursor = System::Windows::Forms::Cursors::Default;
		MessageBox::Show("This file or folder cannot be used in OneClick mode.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	void OneClickWindow::setBatchProcessing(std::vector<OneClickFilesToProcess*> &arrFilesToProcess, OneClickSettings *oSettings)
	{
		bBatchProcessing = bAutomatedProcessing = true;
		SetOneClickProfile(oSettings);
		OneClickProcessing *oProcessor = new OneClickProcessing(this, arrFilesToProcess, oSettings, _oLog);
		return;
	}

	void OneClickWindow::setInputData(MediaInfoFile *iFile, std::vector<OneClickFilesToProcess*> &arrFilesToProcess)
	{
		if (iFile == 0)
			return;

		if (!bAutomatedProcessing && arrFilesToProcess.size() > 0)
		{
			std::string question = "Do you want to process all " + (arrFilesToProcess.size() + 1) + " files/tracks in the selection?\r\nThey all will be processed with the current settings\r\nin the OneClick profile \"" + oneclickProfile->getSelectedProfile()->getName() + "\".\r\nOther settings will be ignored.";
			DialogResult *dr = MessageBox::Show(question, "Automated folder processing", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
			if (dr == System::Windows::Forms::DialogResult::Yes)
			{
				bAutomatedProcessing = true;
				SetOneClickProfile(static_cast<OneClickSettings*>(oneclickProfile->getSelectedProfile()->BaseSettings));
				_oSettings->setLeadingName(MeGUI::core::gui::InputBox::Show("If desired please enter a leading name", "Please enter a leading name", _oSettings->getLeadingName()));
			}
		}
		bLock = true;
		if (input->getSelectedSCItem() == 0 || !iFile->getFileName().Equals(static_cast<std::string>(input->getSelectedObject())))
		{
			input->setStandardItems(new object[] {iFile->getFileName()});
			input->setSelectedIndex(0);
		}
		bLock = false;

		_videoInputInfo = iFile;

		int maxHorizontalResolution = int::Parse(StringConverterHelper::toString(iFile->getVideoInfo()->Width));

		std::vector<OneClickStream*> arrAudioTrackInfo = std::vector<OneClickStream*>();
		for (std::vector<AudioTrackInfo*>::const_iterator oInfo = iFile->getAudioInfo()->getTracks().begin(); oInfo != iFile->getAudioInfo()->getTracks().end(); ++oInfo)
			arrAudioTrackInfo.push_back(new OneClickStream(*oInfo));
		AudioResetTrack(arrAudioTrackInfo, _oSettings);

		std::vector<OneClickStream*> arrSubtitleTrackInfo = std::vector<OneClickStream*>();
		for (std::vector<SubtitleTrackInfo*>::const_iterator oInfo = iFile->getSubtitleInfo()->getTracks().begin(); oInfo != iFile->getSubtitleInfo()->getTracks().end(); ++oInfo)
			arrSubtitleTrackInfo.push_back(new OneClickStream(*oInfo));
		SubtitleResetTrack(arrSubtitleTrackInfo, _oSettings);

		horizontalResolution->Maximum = maxHorizontalResolution;

		// Detect Chapters
		if (!VideoUtil::HasChapters(iFile))
		{
			std::string chapterFile = VideoUtil::getChapterFile(iFile->getFileName());
			if (File::Exists(chapterFile))
				this->chapterFile->setFilename(chapterFile);
			if (!File::Exists(this->chapterFile->getFilename()))
				this->chapterFile->setFilename("");
		}
		else
			this->chapterFile->setFilename("<internal chapters>");

		if (workingDirectory->getFilename().empty())
		{
			std::string strPath = Path::GetDirectoryName(iFile->getFileName());
			if (Directory::Exists(strPath) && FileUtil::IsDirWriteable(strPath))
				workingDirectory->setFilename(strPath);
		}

		updateWorkingName(iFile->getFileName());

		this->ar->setValue(_videoInputInfo->getVideoInfo()->DAR);

		if (getVideoSettings()->getEncoderType()->getID() == "x264" && this->chapterFile->getFilename() != "")
			this->usechaptersmarks->Enabled = true;

		if (bAutomatedProcessing)
			createOneClickJob(arrFilesToProcess);

		this->Cursor = System::Windows::Forms::Cursors::Default;
		goButton->Enabled = true;
	}

	void OneClickWindow::updatePossibleContainers()
	{
		// Since everything calls everything else, this is just a safeguard to make sure we don't infinitely recurse
		if (beingCalled)
			return;
		beingCalled = true;

		std::vector<AudioEncoderType*> audioCodecs = std::vector<AudioEncoderType*>();
		std::vector<MuxableType*> dictatedOutputTypes = std::vector<MuxableType*>();

		if (audioTracks.size() > 0)
		{
			for (int i = 0; i < audioTracks.size(); ++i)
			{
				if (audioTracks[i]->getSelectedStreamIndex() == 0) // "None"
					continue;

				if (audioTracks[i]->getSelectedStream()->getEncoderSettings() != 0 && audioTracks[i]->getSelectedStream()->getEncodingMode() != Never)
					audioCodecs.push_back(audioTracks[i]->getSelectedStream()->getEncoderSettings()->getEncoderType());
				else if (audioTracks[i]->getSelectedStream()->getEncodingMode() == Never)
				{
					std::string typeString;
					if (audioTracks[i]->getSelectedItem()->IsStandard)
					{
						AudioTrackInfo *ati = static_cast<AudioTrackInfo*>(audioTracks[i]->getSelectedStream()->getTrackInfo());
						typeString = "file." + ati->getCodec();
					}
					else
					{
						typeString = audioTracks[i]->getSelectedFile();
					}

					if (VideoUtil::guessAudioType(typeString) != 0)
						dictatedOutputTypes.push_back(VideoUtil::guessAudioMuxableType(typeString, false));
				}
			}
		}

		if (subtitleTracks.size() > 0)
		{
			for (int i = 0; i < subtitleTracks.size(); ++i)
			{
				if (subtitleTracks[i]->getSelectedStreamIndex() == 0) // "None"
					continue;

				std::string typeString;
				if (subtitleTracks[i]->getSelectedItem()->IsStandard)
					typeString = subtitleTracks[i]->getSelectedStream()->getTrackInfo()->getDemuxFileName();
				else
					typeString = subtitleTracks[i]->getSelectedFile();

				SubtitleType *subtitleType = VideoUtil::guessSubtitleType(typeString);
				if (subtitleType != 0)
					dictatedOutputTypes.push_back((new MuxableType(subtitleType, 0)));
			}
		}

		std::vector<ContainerType*> tempSupportedOutputTypes = this->muxProvider->GetSupportedContainers(getVideoSettings()->getEncoderType(), audioCodecs.ToArray(), dictatedOutputTypes.ToArray());

		std::vector<ContainerType*> supportedOutputTypes = std::vector<ContainerType*>();

		for (MeGUI::ContainerType::const_iterator c = acceptableContainerTypes->begin(); c != acceptableContainerTypes->end(); ++c)
			if (std::find(tempSupportedOutputTypes.begin(), tempSupportedOutputTypes.end(), *c) != tempSupportedOutputTypes.end())
				supportedOutputTypes.push_back(*c);

		ignoreRestrictions = false;
		if (supportedOutputTypes.empty())
		{
			if (tempSupportedOutputTypes.size() > 0 && !ignoreRestrictions)
			{
				if (!bAutomatedProcessing)
				{
					std::string message = std::string::Format("No container type could be found that matches the list of acceptable types " + "in your chosen one click profile. {0}" + "Your restrictions are now being ignored.", "\r\n");
					MessageBox::Show(message, "Filetype restrictions too restrictive", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
				ignoreRestrictions = true;
			}
			if (ignoreRestrictions)
				supportedOutputTypes = tempSupportedOutputTypes;
			if (tempSupportedOutputTypes.empty())
			{
				if (bAutomatedProcessing)
					ignoreRestrictions = true;
				else
					MessageBox::Show("No container type could be found for your current settings. Please modify the codecs you use", "No container found", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		if (supportedOutputTypes.size() > 0)
		{
			this->containerFormat->Items->Clear();
			this->containerFormat->Items->AddRange(supportedOutputTypes.ToArray());
			this->containerFormat->SelectedIndex = 0;
			this->output->setFilename(Path::ChangeExtension(output->getFilename(), (dynamic_cast<ContainerType*>(this->containerFormat->SelectedItem))->getExtension()));
		}
		beingCalled = false;
	}

	void OneClickWindow::SetOneClickProfile(OneClickSettings *settings)
	{
		_oSettings = settings->Clone();

		for (std::vector<OneClickStreamControl*>::const_iterator oStream = audioTracks.begin(); oStream != audioTracks.end(); ++oStream)
			(*oStream)->setDefaultLanguage(_oSettings->getDefaultLanguage());

		for (std::vector<OneClickStreamControl*>::const_iterator oStream = subtitleTracks.begin(); oStream != subtitleTracks.end(); ++oStream)
			(*oStream)->setDefaultLanguage(_oSettings->getDefaultLanguage());

		if (_videoInputInfo != 0)
		{
			std::vector<OneClickStream*> arrAudioTrackInfo = std::vector<OneClickStream*>();
			for (std::vector<AudioTrackInfo*>::const_iterator oInfo = _videoInputInfo->getAudioInfo()->getTracks().begin(); oInfo != _videoInputInfo->getAudioInfo()->getTracks().end(); ++oInfo)
				arrAudioTrackInfo.push_back(new OneClickStream(*oInfo));
			AudioResetTrack(arrAudioTrackInfo, settings);

			std::vector<OneClickStream*> arrSubtitleTrackInfo = std::vector<OneClickStream*>();
			for (std::vector<SubtitleTrackInfo*>::const_iterator oInfo = _videoInputInfo->getSubtitleInfo()->getTracks().begin(); oInfo != _videoInputInfo->getSubtitleInfo()->getTracks().end(); ++oInfo)
				arrSubtitleTrackInfo.push_back(new OneClickStream(*oInfo));
			SubtitleResetTrack(arrSubtitleTrackInfo, settings);
		}
		else
			ResetAudioSettings(settings);

		videoProfile->SetProfileNameOrWarn(settings->getVideoProfileName());
		avsProfile->SetProfileNameOrWarn(settings->getAvsProfileName());

		std::vector<ContainerType*> temp = std::vector<ContainerType*>();
		std::vector<ContainerType*> allContainerTypes = muxProvider->GetSupportedContainers();
		for (std::string::const_iterator s = settings->getContainerCandidates()->begin(); s != settings->getContainerCandidates()->end(); ++s)
		{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			ContainerType *ct = allContainerTypes.Find(new Predicate<ContainerType*>(delegate(ContainerType t)
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return t->ToString() == *s;
			}
		   ));
			if (ct != 0)
				temp.push_back(ct);
		}
		acceptableContainerTypes = temp.ToArray();

		// bools
		chkDontEncodeVideo->Checked = settings->getDontEncodeVideo();
		signalAR->Checked = settings->getSignalAR();
		autoDeint->Checked = settings->getAutomaticDeinterlacing();
		autoCrop->Checked = settings->getAutoCrop();
		keepInputResolution->Checked = settings->getKeepInputResolution();
		addPrerenderJob->Checked = settings->getPrerenderVideo();
		usechaptersmarks->Checked = settings->getUseChaptersMarks();

		splitting->setValue(settings->getSplitSize());
		fileSize->setValue(settings->getFilesize());
		if (settings->getOutputResolution() <= horizontalResolution->Maximum)
			horizontalResolution->Value = settings->getOutputResolution();
		if (Directory::Exists(settings->getDefaultWorkingDirectory()) && FileUtil::IsDirWriteable(settings->getDefaultWorkingDirectory()))
			workingDirectory->setFilename(settings->getDefaultWorkingDirectory());
		else
			workingDirectory->setFilename("");

		// device type
		devicetype->Text = settings->getDeviceOutputType();

		// Clean up after those settings were set
		updatePossibleContainers();
		containerFormat_SelectedIndexChanged(0, 0);

		if (!input->getSelectedText().empty())
			updateWorkingName(input->getSelectedText());
	}

	void OneClickWindow::goButton_Click(object *sender, EventArgs *e)
	{
		goButton->Enabled = false;
		createOneClickJob(0);
	}

	void OneClickWindow::createOneClickJob(std::vector<OneClickFilesToProcess*> &arrFilesToProcess)
	{
		// checks if there is a suitable container
		if (ignoreRestrictions)
		{
			_oLog->LogEvent(_videoInputInfo->getFileName() + ": No container type could be found that matches the list of acceptable types in your chosen one click profile. Skipping...");
			if (arrFilesToProcess.size() > 0)
				setBatchProcessing(arrFilesToProcess, _oSettings);
			return;
		}

		// set random working directory
		std::string strWorkingDirectory = "";
		if (Directory::Exists(workingDirectory->getFilename()) && FileUtil::IsDirWriteable(workingDirectory->getFilename()))
			strWorkingDirectory = workingDirectory->getFilename();
		else if (File::Exists(output->getFilename()))
			strWorkingDirectory = Path::GetDirectoryName(output->getFilename());
		else if (File::Exists(_videoInputInfo->getFileName()))
			strWorkingDirectory = Path::GetDirectoryName(_videoInputInfo->getFileName());
		if (!strWorkingDirectory.empty())
		{
			do
				strWorkingDirectory = Path::Combine(strWorkingDirectory, Path::GetRandomFileName());
			while (Directory::Exists(strWorkingDirectory));
		}

		if (!verifyInputSettings(_videoInputInfo, strWorkingDirectory))
		{
			goButton->Enabled = true;
			return;
		}

		ContainerType *inputContainer = _videoInputInfo->getContainerFileType();
		JobChain *prepareJobs = 0;

		// set initial oneclick job settings
		OneClickPostprocessingProperties *dpp = new OneClickPostprocessingProperties();
		dpp->setDAR(ar->getValue());
		dpp->setAvsSettings(static_cast<AviSynthSettings*>(avsProfile->getSelectedProfile()->BaseSettings));
		dpp->setContainer(static_cast<ContainerType*>(containerFormat->SelectedItem));
		dpp->setFinalOutput(output->getFilename());
		dpp->setDeviceOutputType(devicetype->Text);
		dpp->setVideoSettings(getVideoSettings()->Clone());
		dpp->setSplitting(splitting->getValue());
		dpp->setVideoInput(_videoInputInfo->getFileName());
		dpp->setIndexType(_videoInputInfo->getIndexerToUse());
		dpp->setTitleNumberToProcess(_videoInputInfo->getVideoInfo()->PGCNumber);
		if (arrFilesToProcess.size() > 0)
		{
			dpp->setFilesToProcess(arrFilesToProcess);
			dpp->setOneClickSetting(_oSettings);
		}
		dpp->setWorkingDirectory(strWorkingDirectory);
		dpp->getFilesToDelete().push_back(dpp->getWorkingDirectory());
		dpp->setChapterFile(chapterFile->getFilename());
		dpp->setAutoCrop(autoCrop->Checked);


		// prepare input file
		if (Path::GetExtension(_videoInputInfo->getFileName().ToUpper(System::Globalization::CultureInfo::InvariantCulture)) == ".VOB")
		{
			// create pgcdemux job if needed
			std::string videoIFO;
			// PGC numbers are not present in VOB, so we check the main IFO
			if (Path::GetFileName(_videoInputInfo->getFileName())->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->substr(0, 4) == "VTS_")
				videoIFO = _videoInputInfo->getFileName().substr(0, _videoInputInfo->getFileName().rfind("_")) + "_0.IFO";
			else
				videoIFO = Path::ChangeExtension(_videoInputInfo->getFileName(), ".IFO");

			if (File::Exists(videoIFO))
			{
				dpp->setIFOInput(videoIFO);
				if (IFOparser::getPGCnb(videoIFO) > 1)
				{
					// more than one PGC - therefore pgcdemux must be used
					prepareJobs = new SequentialChain(new PgcDemuxJob(videoIFO, dpp->getWorkingDirectory(), _videoInputInfo->getVideoInfo()->PGCNumber));

					for (int i = 1; i < 10; i++)
						dpp->getFilesToDelete().push_back(Path::Combine(dpp->getWorkingDirectory(), "VTS_01_" + i + ".VOB"));
					dpp->setVideoInput(Path::Combine(dpp->getWorkingDirectory(), "VTS_01_1.VOB"));
					dpp->setApplyDelayCorrection(true);
				}
			}
		}

		std::string intermediateMKVFile = "";
		if (_videoInputInfo->isEac3toDemuxable())
		{
			// create eac3to demux job if needed
			dpp->setEac3toDemux(true);
			StringBuilder *sb = new StringBuilder();

			dpp->setVideoInput(Path::Combine(dpp->getWorkingDirectory(), Path::GetFileNameWithoutExtension(_videoInputInfo->getFileName()) + ".mkv"));
			sb->Append(std::string::Format("{0}:\"{1}\" ", _videoInputInfo->getVideoInfo()->getTrack()->getTrackID(), dpp->getVideoInput()));
			inputContainer = ContainerType::MKV;
			dpp->getFilesToDelete().push_back(dpp->getVideoInput());
			dpp->getFilesToDelete().push_back(Path::Combine(dpp->getWorkingDirectory(), Path::GetFileNameWithoutExtension(dpp->getVideoInput()) + " - Log.txt"));

			if (dpp->getChapterFile().Equals("<internal chapters>"))
			{
				int iTrackNumber = _videoInputInfo->getEac3toChaptersTrack();
				if (iTrackNumber > -1)
				{
					dpp->setChapterFile(Path::Combine(dpp->getWorkingDirectory(), Path::GetFileNameWithoutExtension(dpp->getVideoInput()) + " - chapter.txt"));
					sb->Append(std::string::Format("{0}:\"{1}\" ", iTrackNumber, dpp->getChapterFile()));
					dpp->getFilesToDelete().push_back(dpp->getChapterFile());
				}
			}

			for (std::vector<OneClickStreamControl*>::const_iterator oStreamControl = audioTracks.begin(); oStreamControl != audioTracks.end(); ++oStreamControl)
			{
				if (!(*oStreamControl)->getSelectedItem()->IsStandard)
					continue;

				if ((*oStreamControl)->getSelectedStreamIndex() <= 0) // not NONE
					continue;

				bool bCoreOnly = false;
				if (!isDontEncodeAudioPossible(_videoInputInfo, (*oStreamControl)->getSelectedItem()->IsStandard, inputContainer) || (*oStreamControl)->getSelectedStream()->EncodingMode != Never)
				{
					//check if core must be extracted
					if ((*oStreamControl)->getSelectedStream()->TrackInfo->Codec->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("truehd"))
					{
						(*oStreamControl)->getSelectedStream()->TrackInfo->Codec = "AC-3";
						bCoreOnly = true;
					}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
					else if ((*oStreamControl)->getSelectedStream()->TrackInfo->Codec->StartsWith("DTS-HD", StringComparison::InvariantCultureIgnoreCase))
					{
						(*oStreamControl)->getSelectedStream()->TrackInfo->Codec = "DTS";
						bCoreOnly = true;
					}
				}

				sb->Append(std::string::Format("{0}:\"{1}\" ", (*oStreamControl)->getSelectedStream()->TrackInfo->TrackID, Path::Combine(dpp->getWorkingDirectory(), (*oStreamControl)->getSelectedStream()->TrackInfo->DemuxFileName)));
				if (bCoreOnly)
					sb->Append("-core ");

				dpp->getFilesToDelete().push_back(Path::Combine(dpp->getWorkingDirectory(), (*oStreamControl)->getSelectedStream()->TrackInfo->DemuxFileName));
			}

			for (std::vector<OneClickStreamControl*>::const_iterator oStreamControl = subtitleTracks.begin(); oStreamControl != subtitleTracks.end(); ++oStreamControl)
			{
				if (!(*oStreamControl)->getSelectedItem()->IsStandard)
					continue;

				if ((*oStreamControl)->getSelectedStreamIndex() <= 0) // not NONE
					continue;

				std::string strDemuxFilePath = Path::Combine(dpp->getWorkingDirectory(), (*oStreamControl)->getSelectedStream()->TrackInfo->DemuxFileName);
				sb->Append(std::string::Format("{0}:\"{1}\" ", (*oStreamControl)->getSelectedStream()->TrackInfo->MMGTrackID, strDemuxFilePath));
				(*oStreamControl)->getSelectedStream()->DemuxFilePath = strDemuxFilePath;
				dpp->getFilesToDelete().push_back(strDemuxFilePath);
				dpp->getSubtitleTracks().push_back((*oStreamControl)->getSelectedStream());
			}

			if (sb->Length != 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			{
				const std::string tempVector[] = {_videoInputInfo->getFileName()};
				prepareJobs = new SequentialChain(prepareJobs, new HDStreamsExJob(std::vector<std::string>(tempVector, tempVector + sizeof(tempVector) / sizeof(tempVector[0])), dpp->getWorkingDirectory(), 0, sb->ToString(), 2));
			}
		}
		else if (inputContainer != ContainerType::MKV)
		{
			// mux input file into MKV if possible and necessary
			bool bRemuxInput = false;
			if (chkDontEncodeVideo->Checked && dpp->getContainer() == ContainerType::MKV)
				bRemuxInput = true;

			if (!bRemuxInput && (dpp->getIndexType() == FileIndexerWindow::FFMS || dpp->getIndexType() == FileIndexerWindow::AVISOURCE))
			{
				for (std::vector<OneClickStreamControl*>::const_iterator oStreamControl = audioTracks.begin(); oStreamControl != audioTracks.end(); ++oStreamControl)
				{
					if (!(*oStreamControl)->getSelectedItem()->IsStandard)
						continue;

					if ((*oStreamControl)->getSelectedStreamIndex() <= 0) // not NONE
						continue;

					bRemuxInput = true;
					break;
				}
			}

			if (!bRemuxInput && Path::GetExtension(_videoInputInfo->getFileName().ToUpper(System::Globalization::CultureInfo::InvariantCulture)) != ".VOB")
			{
				for (std::vector<OneClickStreamControl*>::const_iterator oStreamControl = subtitleTracks.begin(); oStreamControl != subtitleTracks.end(); ++oStreamControl)
				{
					if (!(*oStreamControl)->getSelectedItem()->IsStandard)
						continue;

					if ((*oStreamControl)->getSelectedStreamIndex() <= 0) // not NONE
						continue;

					bRemuxInput = true;
					break;
				}
			}

			if (bRemuxInput)
			{
				if (!_oSettings->getDisableIntermediateMKV() && _videoInputInfo->MuxableToMKV())
				{
					// create job
					MuxJob *mJob = new MuxJob();
					mJob->setMuxType(MKVMERGE);
					mJob->Input = dpp->getVideoInput();
					mJob->Output = Path::Combine(dpp->getWorkingDirectory(), Path::GetFileNameWithoutExtension(dpp->getVideoInput()) + ".mkv");
					;
					mJob->getSettings()->setMuxAll(true);
					mJob->getSettings()->setMuxedInput(mJob->Input);
					mJob->getSettings()->setMuxedOutput(mJob->Output);
					dpp->getFilesToDelete().push_back(mJob->Output);

					// change input file properties
					if (dpp->getIndexType() == FileIndexerWindow::FFMS || dpp->getIndexType() == FileIndexerWindow::AVISOURCE)
					{
						inputContainer = ContainerType::MKV;
						dpp->setVideoInput(mJob->Output);
					}
					else
						intermediateMKVFile = mJob->Output;

					// add job to queue
					prepareJobs = new SequentialChain(prepareJobs, mJob);
				}
				else
				{
					if (_oSettings->getDisableIntermediateMKV())
						_oLog->LogEvent("Input file will not be demuxed as intermediate MKV is disabled. Therefore some OneClick features will be disabled.");
					else
						_oLog->LogEvent("Input file cannot not be muxed into an intermediate MKV as this is not supported. Therefore some OneClick features will be disabled.");
				}
			}
		}

		// set video mux handling
		if (chkDontEncodeVideo->Checked)
		{
			if (dpp->getContainer() != ContainerType::MKV)
				_oLog->LogEvent("\"Don't encode video\" has been disabled as at the moment only the target container MKV is supported");
			else if (!intermediateMKVFile.empty())
				dpp->setVideoFileToMux(intermediateMKVFile);
			else if (inputContainer != ContainerType::MKV)
				_oLog->LogEvent("\"Don't encode video\" has been disabled as at the moment only the source container MKV is supported");
			else
				dpp->setVideoFileToMux(dpp->getVideoInput());
		}

		// set oneclick job settings
		if (dpp->getVideoFileToMux().empty())
		{
			dpp->setAutoDeinterlace(autoDeint->Checked);
			dpp->setKeepInputResolution(keepInputResolution->Checked);
			dpp->setOutputSize(fileSize->getValue());
			dpp->setPrerenderJob(addPrerenderJob->Checked);
			dpp->setUseChaptersMarks(usechaptersmarks->Checked);
			dpp->setSignalAR(signalAR->Checked);
		}
		else
		{
			dpp->setUseChaptersMarks(false);
		dpp->setPrerenderJob(dpp->getUseChaptersMarks());
	dpp->setAutoDeinterlace(dpp->getPrerenderJob());
			dpp->setSignalAR(false);
		dpp->setKeepInputResolution(dpp->getSignalAR());
			dpp->setOutputSize(Nullable<FileSize>());
		}

		if (keepInputResolution->Checked || !dpp->getVideoFileToMux().empty())
		{
			dpp->setHorizontalOutputResolution(0);
			dpp->setSignalAR(true);
		}
		else
			dpp->setHorizontalOutputResolution(static_cast<int>(horizontalResolution->Value));

		// MKV tracks which need to be extracted
		std::vector<TrackInfo*> oExtractMKVTrack = std::vector<TrackInfo*>();

		// get audio information
		JobChain *audioJobs = 0;
		std::vector<AudioTrackInfo*> arrAudioTrackInfo = std::vector<AudioTrackInfo*>();
		for (std::vector<OneClickStreamControl*>::const_iterator oStreamControl = audioTracks.begin(); oStreamControl != audioTracks.end(); ++oStreamControl)
		{
			if ((*oStreamControl)->getSelectedStreamIndex() <= 0) // "None"
				continue;

			std::string aInput = "";
			std::string strLanguage = "";
			std::string strName = "";
			std::string strAudioCodec = "";
			bool bExtractMKVTrack = false;
			AudioTrackInfo *oAudioTrackInfo = 0;
			int delay = (*oStreamControl)->getSelectedStream()->Delay;
			if ((*oStreamControl)->getSelectedItem()->IsStandard)
			{
				oAudioTrackInfo = static_cast<AudioTrackInfo*>((*oStreamControl)->getSelectedStream()->TrackInfo);
				if (dpp->getIndexType() == FileIndexerWindow::AVISOURCE && inputContainer != ContainerType::MKV)
				{
					_oLog->LogEvent("Internal audio track " + oAudioTrackInfo->getTrackID() + " will be skipped as AVISOURCE is going to be used", Warning);
					continue;
				}

				arrAudioTrackInfo.push_back(oAudioTrackInfo);
				if (dpp->getIndexType() != FileIndexerWindow::NONE && !dpp->getEac3toDemux())
					aInput = "::" + oAudioTrackInfo->getTrackID() + "::";
				else
					aInput = Path::Combine(dpp->getWorkingDirectory(), oAudioTrackInfo->getDemuxFileName());
				strName = oAudioTrackInfo->getName();
				strLanguage = oAudioTrackInfo->getLanguage();
				strAudioCodec = oAudioTrackInfo->getCodec();
				if (inputContainer == ContainerType::MKV && !dpp->getEac3toDemux()) // only if container MKV and no demux with eac3to
				{
					if (!strAudioCodec.Equals("PCM", StringComparison::InvariantCultureIgnoreCase)) // PCM track cannot be extracted by mkvextract
					{
						oExtractMKVTrack.push_back((*oStreamControl)->getSelectedStream()->TrackInfo);
						bExtractMKVTrack = true;
					}
				}
			}
			else
			{
				aInput = (*oStreamControl)->getSelectedFile();
				MediaInfoFile *oInfo = new MediaInfoFile(aInput, _oLog);
				if (oInfo->getAudioInfo()->getTracks().size() > 0)
					strAudioCodec = oInfo->getAudioInfo()->getTracks()[0]->getCodec();
				strName = (*oStreamControl)->getSelectedStream()->Name;
				strLanguage = (*oStreamControl)->getSelectedStream()->Language;
			}

			bool bIsDontEncodeAudioPossible = isDontEncodeAudioPossible(_videoInputInfo, (*oStreamControl)->getSelectedItem()->IsStandard, inputContainer);
			if (bIsDontEncodeAudioPossible && ((*oStreamControl)->getSelectedStream()->EncodingMode == Never || ((*oStreamControl)->getSelectedStream()->EncodingMode == NeverOnlyCore && dpp->getEac3toDemux()) || ((*oStreamControl)->getSelectedStream()->EncodingMode == IfCodecDoesNotMatch && (*oStreamControl)->getSelectedStream()->EncoderSettings->EncoderType->ACodec->ID->Equals(strAudioCodec, StringComparison::InvariantCultureIgnoreCase))))
			{
				dpp->getAudioTracks().push_back(new OneClickAudioTrack(0, new MuxStream(aInput, strLanguage, strName, delay, false, false, 0), oAudioTrackInfo, bExtractMKVTrack));
			}
			else
			{
				if (!bIsDontEncodeAudioPossible && ((*oStreamControl)->getSelectedStream()->EncodingMode == Never || ((*oStreamControl)->getSelectedStream()->EncodingMode == NeverOnlyCore && dpp->getEac3toDemux()) || ((*oStreamControl)->getSelectedStream()->EncodingMode == IfCodecDoesNotMatch && (*oStreamControl)->getSelectedStream()->EncoderSettings->EncoderType->ACodec->ID->Equals(strAudioCodec, StringComparison::InvariantCultureIgnoreCase))))
					_oLog->LogEvent("Audio " + (*oStreamControl)->getSelectedStream() + " cannot be processed with encoding mode \"" + (*oStreamControl)->getSelectedStream()->EncodingMode + "\" as it must be encoded");

				// audio track will be encoded
				std::string strFileName = "";
				if (!(*oStreamControl)->getSelectedItem()->IsStandard || !dpp->getEac3toDemux())
				{
					if (strAudioCodec.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("truehd"))
					{
						strAudioCodec = "AC-3";
						if ((*oStreamControl)->getSelectedItem()->IsStandard)
						{
							strFileName = Path::Combine(strWorkingDirectory, (*oStreamControl)->getSelectedStream()->TrackInfo->DemuxFileName);
							strFileName = Path::ChangeExtension(strFileName, "ac3");
							oAudioTrackInfo->setCodec(strAudioCodec);
							aInput = FileUtil::AddToFileName(strFileName, "_core");
						}
						else
						{
							strFileName = (*oStreamControl)->getSelectedFile();
							aInput = FileUtil::AddToFileName(Path::ChangeExtension(strFileName, "ac3"), "_core");
							aInput = Path::Combine(strWorkingDirectory, Path::GetFileName(aInput));
						}

						const std::string tempVector2[] = {strFileName};
						HDStreamsExJob *oJob = new HDStreamsExJob(std::vector<std::string>(tempVector2, tempVector2 + sizeof(tempVector2) / sizeof(tempVector2[0])), aInput, 0, "\"" + aInput + "\"", 2);
						audioJobs = new SequentialChain(audioJobs, new SequentialChain(oJob));
						dpp->getFilesToDelete().push_back(FileUtil::AddToFileName(Path::ChangeExtension(aInput, "txt"), " - Log"));
						dpp->getFilesToDelete().push_back(aInput);
					}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
					else if (strAudioCodec.StartsWith("DTS-HD", StringComparison::InvariantCultureIgnoreCase))
					{
						strAudioCodec = "DTS";
						if ((*oStreamControl)->getSelectedItem()->IsStandard)
						{
							strFileName = Path::Combine(strWorkingDirectory, (*oStreamControl)->getSelectedStream()->TrackInfo->DemuxFileName);
							oAudioTrackInfo->setCodec(strAudioCodec);
							aInput = FileUtil::AddToFileName(Path::ChangeExtension(strFileName, "dts"), "_core");
						}
						else
						{
							strFileName = (*oStreamControl)->getSelectedFile();
							aInput = FileUtil::AddToFileName(Path::ChangeExtension(strFileName, "dts"), "_core");
							aInput = Path::Combine(strWorkingDirectory, Path::GetFileName(aInput));
						}

						const std::string tempVector3[] = {strFileName};
						HDStreamsExJob *oJob = new HDStreamsExJob(std::vector<std::string>(tempVector3, tempVector3 + sizeof(tempVector3) / sizeof(tempVector3[0])), aInput, 0, "\"" + aInput + "\" -core", 2);
						audioJobs = new SequentialChain(audioJobs, new SequentialChain(oJob));
						dpp->getFilesToDelete().push_back(FileUtil::AddToFileName(Path::ChangeExtension(aInput, "txt"), " - Log"));
						dpp->getFilesToDelete().push_back(aInput);
					}
					else if ((*oStreamControl)->getSelectedItem()->IsStandard && strAudioCodec.Equals("PCM", StringComparison::InvariantCultureIgnoreCase))
					{
						if (_videoInputInfo->getContainerFileType() == ContainerType::MKV)
						{
							aInput = Path::Combine(strWorkingDirectory, (*oStreamControl)->getSelectedStream()->TrackInfo->DemuxFileName);
							const std::string tempVector4[] = {dpp->getVideoInput()};
							HDStreamsExJob *oJob = new HDStreamsExJob(std::vector<std::string>(tempVector4, tempVector4 + sizeof(tempVector4) / sizeof(tempVector4[0])), aInput, 0, (*oStreamControl)->getSelectedStream()->TrackInfo->TrackID + ":\"" + aInput + "\"", 2);
							audioJobs = new SequentialChain(audioJobs, new SequentialChain(oJob));
							dpp->getFilesToDelete().push_back(FileUtil::AddToFileName(Path::ChangeExtension(aInput, "txt"), " - Log"));
							dpp->getFilesToDelete().push_back(aInput);
						}
					}
				}

				if ((*oStreamControl)->getSelectedStream()->EncodingMode == NeverOnlyCore)
					dpp->getAudioTracks().push_back(new OneClickAudioTrack(0, new MuxStream(aInput, strLanguage, strName, delay, false, false, 0), oAudioTrackInfo, bExtractMKVTrack));
				else
					dpp->getAudioTracks().push_back(new OneClickAudioTrack(new AudioJob(aInput, 0, 0, (*oStreamControl)->getSelectedStream()->EncoderSettings, delay, strLanguage, strName), 0, oAudioTrackInfo, bExtractMKVTrack));
			}
		}


		// subtitle handling
		for (std::vector<OneClickStreamControl*>::const_iterator oStream = subtitleTracks.begin(); oStream != subtitleTracks.end(); ++oStream)
		{
			if ((*oStream)->getSelectedStreamIndex() <= 0) // not NONE
				continue;

			if ((*oStream)->getSelectedItem()->IsStandard)
			{
				std::string strExtension = Path::GetExtension((*oStream)->getSelectedStream()->TrackInfo->SourceFileName->ToLower(System::Globalization::CultureInfo::InvariantCulture));
				if (strExtension.Equals(".ifo") || strExtension.Equals(".vob"))
				{
					std::string strInput = (*oStream)->getSelectedStream()->TrackInfo->SourceFileName;
					if (strExtension.Equals(".vob"))
					{
						if (Path::GetFileName(strInput)->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->substr(0, 4) == "VTS_")
							strInput = strInput.substr(0, strInput.rfind("_")) + "_0.IFO";
						else
							strInput = Path::ChangeExtension(strInput, ".IFO");
					}
					std::string outputFile = Path::Combine(dpp->getWorkingDirectory(), Path::GetFileNameWithoutExtension(strInput)) + "_" + (*oStream)->getSelectedStream()->TrackInfo->MMGTrackID + ".idx";
					SubtitleIndexJob *oJob = new SubtitleIndexJob(strInput, outputFile, false, std::vector<int>(new *oStream[] {(*oStream)->getSelectedStream()->TrackInfo->MMGTrackID}), _videoInputInfo->getVideoInfo()->PGCNumber);
					prepareJobs = new SequentialChain(new SequentialChain(prepareJobs), new SequentialChain(oJob));
					(*oStream)->getSelectedStream()->DemuxFilePath = outputFile;
					dpp->getFilesToDelete().push_back(outputFile);
					dpp->getFilesToDelete().push_back(Path::ChangeExtension(outputFile, ".sub"));
					dpp->getSubtitleTracks().push_back((*oStream)->getSelectedStream());
				}
				else if (inputContainer == ContainerType::MKV && !dpp->getEac3toDemux()) // only if container MKV and no demux with eac3to
				{
					(*oStream)->getSelectedStream()->TrackInfo->ExtractMKVTrack = true;
					oExtractMKVTrack.push_back((*oStream)->getSelectedStream()->TrackInfo);
					dpp->getSubtitleTracks().push_back((*oStream)->getSelectedStream());
				}
			}
			else
				dpp->getSubtitleTracks().push_back((*oStream)->getSelectedStream());
		}


		// create MKV extract job if required
		if (oExtractMKVTrack.size() > 0)
		{
			MkvExtractJob *extractJob = new MkvExtractJob(dpp->getVideoInput(), dpp->getWorkingDirectory(), oExtractMKVTrack);
			prepareJobs = new SequentialChain(prepareJobs, new SequentialChain(extractJob));
			if (dpp->getApplyDelayCorrection())
				_oLog->LogEvent("Audio delay will be detected later as an intermediate MKV file is beeing used");
		}
		else
			dpp->setApplyDelayCorrection(false);


		// add audio job to chain if required
		prepareJobs = new SequentialChain(prepareJobs, new SequentialChain(audioJobs));

		JobChain *finalJobChain = 0;
		if (dpp->getIndexType() == FileIndexerWindow::D2V || dpp->getIndexType() == FileIndexerWindow::DGA)
		{
			std::string indexFile = "";
			IndexJob *job = 0;
			if (dpp->getIndexType() == FileIndexerWindow::D2V)
			{
				indexFile = Path::Combine(dpp->getWorkingDirectory(), workingName->Text + ".d2v");
				job = new D2VIndexJob(dpp->getVideoInput(), indexFile, 2, arrAudioTrackInfo, false, false);
			}
			else
			{
				indexFile = Path::Combine(dpp->getWorkingDirectory(), workingName->Text + ".dga");
				job = new DGAIndexJob(dpp->getVideoInput(), indexFile, 2, arrAudioTrackInfo, false, false);
			}
			OneClickPostProcessingJob *ocJob = new OneClickPostProcessingJob(dpp->getVideoInput(), indexFile, dpp);
			finalJobChain = new SequentialChain(prepareJobs, new SequentialChain(job), new SequentialChain(ocJob));
		}
		else if (dpp->getIndexType() == FileIndexerWindow::DGI || dpp->getIndexType() == FileIndexerWindow::FFMS)
		{
			std::string indexFile = "";
			if (dpp->getIndexType() == FileIndexerWindow::DGI)
				indexFile = Path::Combine(dpp->getWorkingDirectory(), workingName->Text + ".dgi");
			else
				indexFile = Path::Combine(dpp->getWorkingDirectory(), Path::GetFileName(dpp->getVideoInput()) + ".ffindex");
			OneClickPostProcessingJob *ocJob = new OneClickPostProcessingJob(dpp->getVideoInput(), indexFile, dpp);

			IndexJob *job = 0;
			if (inputContainer == ContainerType::MKV)
			{
				if (dpp->getIndexType() == FileIndexerWindow::DGI)
					job = new DGIIndexJob(dpp->getVideoInput(), indexFile, 0, 0, false, false);
				else
					job = new FFMSIndexJob(dpp->getVideoInput(), indexFile, 0, 0, false);
				if (!dpp->getVideoFileToMux().empty() && dpp->getContainer() == ContainerType::MKV)
				{
					finalJobChain = new SequentialChain(prepareJobs, new SequentialChain(ocJob));
					dpp->setIndexType(FileIndexerWindow::NONE);
				}
				else
					finalJobChain = new SequentialChain(prepareJobs, new SequentialChain(job), new SequentialChain(ocJob));
			}
			else
			{
				if (dpp->getIndexType() == FileIndexerWindow::DGI)
					job = new DGIIndexJob(dpp->getVideoInput(), indexFile, 2, arrAudioTrackInfo, false, false);
				else
					job = new FFMSIndexJob(dpp->getVideoInput(), indexFile, 2, arrAudioTrackInfo, false);
				finalJobChain = new SequentialChain(prepareJobs, new SequentialChain(job), new SequentialChain(ocJob));
			}
		}
		else
		{
			// no indexer
			if (inputContainer == ContainerType::MKV && dpp->getIndexType() == FileIndexerWindow::AVISOURCE && dpp->getVideoFileToMux().empty())
				dpp->setVideoInput(_videoInputInfo->getFileName());
			OneClickPostProcessingJob *ocJob = new OneClickPostProcessingJob(dpp->getVideoInput(), 0, dpp);
			finalJobChain = new SequentialChain(prepareJobs, new SequentialChain(ocJob));
		}


		// write all to be processed tracks into the log
		_oLog->LogEvent("Video: " + _videoInputInfo->getFileName());
		for (std::vector<OneClickAudioTrack*>::const_iterator oTrack = dpp->getAudioTracks().begin(); oTrack != dpp->getAudioTracks().end(); ++oTrack)
		{
			if ((*oTrack)->getAudioTrackInfo() != 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				_oLog->LogEvent("Audio: " + (*oTrack)->getAudioTrackInfo()->SourceFileName + " (" + (*oTrack)->getAudioTrackInfo()->ToString() + ")");
			else if ((*oTrack)->getAudioJob() != 0)
				_oLog->LogEvent("Audio: " + (*oTrack)->getAudioJob()->Input);
		}
		for (std::vector<OneClickStream*>::const_iterator oTrack = dpp->getSubtitleTracks().begin(); oTrack != dpp->getSubtitleTracks().end(); ++oTrack)
		{
			if ((*oTrack)->getTrackInfo() != 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				_oLog->LogEvent("Subtitle: " + (*oTrack)->getTrackInfo()->SourceFileName + " (" + (*oTrack)->getTrackInfo()->ToString() + ")");
		}

		// add jobs to queue
		mainForm->getJobs()->addJobsWithDependencies(finalJobChain, !bBatchProcessing);

		if (!this->openOnQueue->Checked && this->Visible)
		{
			tabControl1->SelectedTab = tabControl1->TabPages[0];
			goButton->Enabled = true;
		}
		else
			this->Close();
	}

	bool OneClickWindow::verifyInputSettings(MediaInfoFile *oVideoInputInfo, const std::string &strWorkingDirectory)
	{
		if (oVideoInputInfo == 0 || !File::Exists(oVideoInputInfo->getFileName()))
		{
			MessageBox::Show("Please select a valid input file!", "Incomplete configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return false;
		}

		if (output->getFilename().empty())
		{
			MessageBox::Show("Please select a valid output file!", "Incomplete configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return false;
		}

		if (!FileUtil::IsDirWriteable(Path::GetDirectoryName(output->getFilename())))
		{
			MessageBox::Show("MeGUI cannot write on the disc: " + Path::GetDirectoryName(output->getFilename()) + " \n" + "Please select a writeable output path to save your project!", "Incomplete configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return false;
		}

		if (strWorkingDirectory.empty())
		{
			MessageBox::Show("Please select a valid working directory!", "Incomplete configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return false;
		}

		if (!FileUtil::IsDirWriteable(strWorkingDirectory))
		{
			MessageBox::Show("MeGUI cannot write on the disc: " + strWorkingDirectory + " \n" + "Please select a writeable working path to save your project!", "Incomplete configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return false;
		}

		if ((verifyStreamSettings() != "") || (getVideoSettings() == 0) || workingName->Text->empty())
		{
			MessageBox::Show("MeGUI cannot process this job", "Wrong configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return false;
		}

		for (int i = 0; i < audioTracks.size() - 1; i++)
		{
			if (audioTracks[i]->getSelectedStreamIndex() <= 0) // not NONE
				continue;

			for (int j = i + 1; j < audioTracks.size(); j++)
			{
				if (audioTracks[j]->getSelectedStreamIndex() <= 0) // not NONE
					continue;

				// compare the two controls
				if (audioTracks[i]->getSelectedStream()->getDemuxFilePath()->Equals(audioTracks[j]->getSelectedStream()->getDemuxFilePath()) && audioTracks[i]->getSelectedStream()->getLanguage()->Equals(audioTracks[j]->getSelectedStream()->getLanguage()) && audioTracks[i]->getSelectedStream()->getName()->Equals(audioTracks[j]->getSelectedStream()->getName()) && audioTracks[i]->getSelectedStream()->getDefaultStream() == audioTracks[j]->getSelectedStream()->getDefaultStream() && audioTracks[i]->getSelectedStream()->getDelay() == audioTracks[j]->getSelectedStream()->getDelay() && audioTracks[i]->getSelectedStream()->getEncoderSettings()->Equals(audioTracks[j]->getSelectedStream()->getEncoderSettings()) && audioTracks[i]->getSelectedStream()->getEncodingMode() == audioTracks[j]->getSelectedStream()->getEncodingMode() && audioTracks[i]->getSelectedStream()->getForcedStream() == audioTracks[j]->getSelectedStream()->getForcedStream())
				{
					DialogResult *dr = MessageBox::Show("The audio tracks " + (i + 1) + " and " + (j + 1) + " are identical. Are you sure you want to proceed?", "Duplicate audio tracks found", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
					if (dr == System::Windows::Forms::DialogResult::No)
						return false;
				}
			}
		}

		for (int i = 0; i < subtitleTracks.size() - 1; i++)
		{
			if (subtitleTracks[i]->getSelectedStreamIndex() <= 0) // not NONE
				continue;

			for (int j = i + 1; j < subtitleTracks.size(); j++)
			{
				if (subtitleTracks[j]->getSelectedStreamIndex() <= 0) // not NONE
					continue;

				// compare the two controls
				if (subtitleTracks[i]->getSelectedStream()->getDemuxFilePath()->Equals(subtitleTracks[j]->getSelectedStream()->getDemuxFilePath()) && subtitleTracks[i]->getSelectedStream()->getLanguage()->Equals(subtitleTracks[j]->getSelectedStream()->getLanguage()) && subtitleTracks[i]->getSelectedStream()->getName()->Equals(subtitleTracks[j]->getSelectedStream()->getName()) && subtitleTracks[i]->getSelectedStream()->getDefaultStream() == subtitleTracks[j]->getSelectedStream()->getDefaultStream() && subtitleTracks[i]->getSelectedStream()->getDelay() == subtitleTracks[j]->getSelectedStream()->getDelay() && subtitleTracks[i]->getSelectedStream()->getEncoderSettings()->Equals(subtitleTracks[j]->getSelectedStream()->getEncoderSettings()) && subtitleTracks[i]->getSelectedStream()->getEncodingMode() == subtitleTracks[j]->getSelectedStream()->getEncodingMode() && subtitleTracks[i]->getSelectedStream()->getForcedStream() == subtitleTracks[j]->getSelectedStream()->getForcedStream())
				{
					DialogResult *dr = MessageBox::Show("The subtitle tracks " + (i + 1) + " and " + (j + 1) + " are identical. Are you sure you want to proceed?", "Duplicate subtitle tracks found", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
					if (dr == System::Windows::Forms::DialogResult::No)
						return false;
				}
			}
		}

		return true;
	}

	std::string OneClickWindow::verifyStreamSettings()
	{
		for (int i = 0; i < audioTracks.size(); ++i)
		{
			if (audioTracks[i]->getSelectedItem()->IsStandard || audioTracks[i]->getSelectedStreamIndex() <= 0)
				continue;

			std::string r = MainForm::verifyInputFile(audioTracks[i]->getSelectedFile());
			if (r != "")
				return r;
		}
		for (int i = 0; i < subtitleTracks.size(); ++i)
		{
			if (subtitleTracks[i]->getSelectedItem()->IsStandard || subtitleTracks[i]->getSelectedStreamIndex() <= 0)
				continue;

			std::string r = MainForm::verifyInputFile(subtitleTracks[i]->getSelectedFile());
			if (r != "")
				return r;
		}
		return 0;
	}

	void OneClickWindow::audio1_SomethingChanged(object *sender, EventArgs *e)
	{
		updatePossibleContainers();
	}

	void OneClickWindow::ProfileChanged(object *sender, EventArgs *e)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (videoProfile->getSelectedProfile()->getFQName().StartsWith("x264") && !chkDontEncodeVideo->Checked)
			usechaptersmarks->Enabled = true;
		else
			usechaptersmarks->Enabled = false;
		updatePossibleContainers();
	}

	void OneClickWindow::keepInputResolution_CheckedChanged(object *sender, EventArgs *e)
	{
		if (keepInputResolution->Checked)
			horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = false;
		else
			horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = true;
	}

	void OneClickWindow::chkDontEncodeVideo_CheckedChanged(object *sender, EventArgs *e)
	{
		if (chkDontEncodeVideo->Checked)
		{
			horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = videoProfile->Enabled = false;
			usechaptersmarks->Enabled = keepInputResolution->Enabled = addPrerenderJob->Enabled = false;
			autoDeint->Enabled = fileSize->Enabled = avsProfile->Enabled = ar->Enabled = false;
		}
		else
		{
			videoProfile->Enabled = keepInputResolution->Enabled = addPrerenderJob->Enabled = true;
			autoDeint->Enabled = fileSize->Enabled = avsProfile->Enabled = true;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
			if (videoProfile->getSelectedProfile()->getFQName().StartsWith("x264"))
				usechaptersmarks->Enabled = true;
			else
				usechaptersmarks->Enabled = false;
			if (keepInputResolution->Checked)
				horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = ar->Enabled = false;
			else
				horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = ar->Enabled = true;
		}
	}

	void OneClickWindow::subtitleMenu_Opening(object *sender, CancelEventArgs *e)
	{
		subtitleRemoveTrack->Enabled = (iSelectedSubtitleTabPage != subtitleTracks.size());
	}

	void OneClickWindow::subtitleAddTrack_Click(object *sender, EventArgs *e)
	{
		SubtitleAddTrack(true);
	}

	void OneClickWindow::subtitleRemoveTrack_Click(object *sender, EventArgs *e)
	{
		SubtitleRemoveTrack(iSelectedSubtitleTabPage);
	}

	void OneClickWindow::SubtitleAddTrack(bool bChangeFocus)
	{
		TabPage *p = new TabPage("Subtitle " + (subtitleTracks.size() + 1));
		p->UseVisualStyleBackColor = subtitlesTab->TabPages[0]->UseVisualStyleBackColor;
		p->Padding = subtitlesTab->TabPages[0]->Padding;

		OneClickStreamControl *a = new OneClickStreamControl();
		a->Dock = subtitleTracks[0]->Dock;
		a->Padding = subtitleTracks[0]->Padding;
		a->setShowDelay(subtitleTracks[0]->getShowDelay());
		a->setShowDefaultStream(subtitleTracks[0]->getShowDefaultStream());
		a->setShowForceStream(subtitleTracks[0]->getShowForceStream());
		a->setDefaultLanguage(subtitleTracks[0]->getDefaultLanguage());
		a->chkDefaultStream->CheckedChanged += new System::EventHandler(this, &OneClickWindow::chkDefaultStream_CheckedChanged);
		a->SomethingChanged += new EventHandler(this, &OneClickWindow::audio1_SomethingChanged);
		a->setFilter(subtitleTracks[0]->getFilter());
		a->FileUpdated += new System::EventHandler(this, &OneClickWindow::oneClickSubtitleStreamControl_FileUpdated);
		a->setStandardStreams(subtitleTracks[0]->getStandardStreams());
		a->setCustomStreams(subtitleTracks[0]->getCustomStreams());
		a->setSelectedStreamIndex(0);
		a->initProfileHandler();
		if (this->Visible)
			a->enableDragDrop();

		subtitlesTab->TabPages->Insert(subtitlesTab->TabCount - 1, p);
		p->Controls->Add(a);
		subtitleTracks.push_back(a);

		if (bChangeFocus)
			subtitlesTab->SelectedTab = p;
	}

	void OneClickWindow::SubtitleRemoveTrack(int iTabPageIndex)
	{
		if (iTabPageIndex == subtitlesTab->TabCount - 1)
			return;

		if (iTabPageIndex == 0 && subtitlesTab->TabCount == 1)
			SubtitleAddTrack(true);

		subtitlesTab->TabPages->RemoveAt(iTabPageIndex);
		subtitleTracks.RemoveAt(iTabPageIndex);

		for (int i = 0; i < subtitlesTab->TabCount - 1; i++)
			subtitlesTab->TabPages[i]->Text = "Subtitle " + (i + 1);

		updatePossibleContainers();
	}

	void OneClickWindow::chkDefaultStream_CheckedChanged(object *sender, EventArgs *e)
	{
		if ((static_cast<CheckBox*>(sender))->Checked == false)
			return;

		for (std::vector<OneClickStreamControl*>::const_iterator oTrack = subtitleTracks.begin(); oTrack != subtitleTracks.end(); ++oTrack)
		{
			if (sender != (*oTrack)->chkDefaultStream && (*oTrack)->chkDefaultStream->Checked == true)
				(*oTrack)->chkDefaultStream->Checked = false;
		}
	}

	void OneClickWindow::subtitlesTab_MouseClick(object *sender, MouseEventArgs *e)
	{
		if (e->Button != MouseButtons::Right)
			return;

		Point *p = e->Location;
		for (int i = 0; i < subtitlesTab->TabCount; i++)
		{
			Rectangle *rect = subtitlesTab->GetTabRect(i);
			rect->Offset(2, 2);
			rect->Width -= 4;
			rect->Height -= 4;
			if (rect->Contains(p))
			{
				iSelectedSubtitleTabPage = i;
				subtitleMenu->Show(subtitlesTab, e->Location);
				break;
			}
		}
	}

	void OneClickWindow::oneClickSubtitleStreamControl_FileUpdated(object *sender, EventArgs *e)
	{
		if (bLock)
			return;

		int i = subtitleTracks.find(static_cast<OneClickStreamControl*>(sender));

		if (i < 0)
			return;

		OneClickStreamControl *track = subtitleTracks[i];
		for (std::vector<OneClickStreamControl*>::const_iterator oControl = subtitleTracks.begin(); oControl != subtitleTracks.end(); ++oControl)
		{
			if (*oControl == track)
				continue;

			if (sizeof((*oControl)->getCustomStreams()) / sizeof((*oControl)->getCustomStreams()[0]) != sizeof(track->getCustomStreams()) / sizeof(track->getCustomStreams()[0]))
			{
				int iIndex = -1;
				if (!track->getSelectedItem()->IsStandard)
					iIndex = (*oControl)->getSelectedStreamIndex();
				bLock = true;
				(*oControl)->setCustomStreams(track->getCustomStreams());
				bLock = false;
				if (iIndex >= 0 && (*oControl)->getSelectedStreamIndex() != iIndex)
					(*oControl)->setSelectedStreamIndex(iIndex);
			}
		}

		updatePossibleContainers();
	}

	void OneClickWindow::SubtitleResetTrack(std::vector<OneClickStream*> &arrSubtitleTrackInfo, OneClickSettings *settings)
	{
		// generate track names
		std::vector<object*> trackNames = std::vector<object*>();
		trackNames.push_back("None");
		for (std::vector<OneClickStream*>::const_iterator o = arrSubtitleTrackInfo.begin(); o != arrSubtitleTrackInfo.end(); ++o)
			trackNames.push_back(*o);
		subtitleTracks[0]->setStandardStreams(trackNames.ToArray());
		subtitleTracks[0]->setCustomStreams(new object[0]);
		subtitleTracks[0]->setSelectedStreamIndex(0);

		// delete all tracks beside the first and last one
		try
		{
			while (subtitlesTab->TabCount > 2)
				subtitlesTab->TabPages->RemoveAt(1);
		}
		catch (std::exception &e1)
		{
		}
		subtitleTracks.RemoveRange(1, subtitleTracks.size() - 1);

		for (std::vector<std::string>::const_iterator strLanguage = settings->getDefaultSubtitleLanguage().begin(); strLanguage != settings->getDefaultSubtitleLanguage().end(); ++strLanguage)
			if ((*strLanguage).Equals("[none]"))
				return;

		int iCounter = 0;
		for (std::vector<std::string>::const_iterator strLanguage = settings->getDefaultSubtitleLanguage().begin(); strLanguage != settings->getDefaultSubtitleLanguage().end(); ++strLanguage)
		{
			for (int i = 0; i < arrSubtitleTrackInfo.size(); i++)
			{
				if (arrSubtitleTrackInfo[i]->getLanguage()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals((*strLanguage).ToLower(System::Globalization::CultureInfo::InvariantCulture)))
				{
					if (iCounter > 0)
						SubtitleAddTrack(false);
					subtitleTracks[iCounter++]->setSelectedStreamIndex(i + 1);
				}
			}
		}

		if (iCounter == 0 && arrSubtitleTrackInfo.size() > 0 && !settings->getUseNoLanguagesAsFallback())
		{
			for (int i = 0; i < arrSubtitleTrackInfo.size(); i++)
			{
				if (iCounter > 0)
					SubtitleAddTrack(false);
				subtitleTracks[iCounter++]->setSelectedStreamIndex(i + 1);
			}
		}
	}

	void OneClickWindow::subtitlesTab_MouseDoubleClick(object *sender, MouseEventArgs *e)
	{
		SubtitleAddTrack(true);
	}

	void OneClickWindow::audioMenu_Opening(object *sender, CancelEventArgs *e)
	{
		audioRemoveTrack->Enabled = (iSelectedAudioTabPage != audioTracks.size());
	}

	void OneClickWindow::audioAddTrack_Click(object *sender, EventArgs *e)
	{
	   AudioAddTrack(true);
	}

	void OneClickWindow::audioRemoveTrack_Click(object *sender, EventArgs *e)
	{
		AudioRemoveTrack(iSelectedAudioTabPage);
	}

	void OneClickWindow::AudioAddTrack(bool bChangeFocus)
	{
		TabPage *p = new TabPage("Audio " + (audioTracks.size() + 1));
		p->UseVisualStyleBackColor = audioTab->TabPages[0]->UseVisualStyleBackColor;
		p->Padding = audioTab->TabPages[0]->Padding;

		OneClickStreamControl *a = new OneClickStreamControl();
		a->Dock = audioTracks[0]->Dock;
		a->Padding = audioTracks[0]->Padding;
		a->setShowDelay(audioTracks[0]->getShowDelay());
		a->setShowDefaultStream(audioTracks[0]->getShowDefaultStream());
		a->setShowForceStream(audioTracks[0]->getShowForceStream());
		a->setFilter(audioTracks[0]->getFilter());
		a->FileUpdated += new System::EventHandler(this, &OneClickWindow::oneClickAudioStreamControl_FileUpdated);
		a->setStandardStreams(audioTracks[0]->getStandardStreams());
		a->setCustomStreams(audioTracks[0]->getCustomStreams());
		a->setSelectedStreamIndex(0);
		a->setDefaultLanguage(audioTracks[0]->getDefaultLanguage());
		a->SomethingChanged += new EventHandler(this, &OneClickWindow::audio1_SomethingChanged);
		a->setEncodingMode(audioTracks[0]->getEncodingMode());
		a->initProfileHandler();
		a->SelectProfileNameOrWarn(audioTracks[0]->getEncoderProfile());
		if (this->Visible)
			a->enableDragDrop();

		audioTab->TabPages->Insert(audioTab->TabCount - 1, p);
		p->Controls->Add(a);
		audioTracks.push_back(a);

		if (bChangeFocus)
			audioTab->SelectedTab = p;
	}

	void OneClickWindow::AudioRemoveTrack(int iTabPageIndex)
	{
		if (iTabPageIndex == audioTab->TabCount - 1)
			return;

		if (iTabPageIndex == 0 && subtitlesTab->TabCount == 1)
			AudioAddTrack(true);

		audioTab->TabPages->RemoveAt(iTabPageIndex);
		audioTracks.RemoveAt(iTabPageIndex);

		for (int i = 0; i < audioTab->TabCount - 1; i++)
			audioTab->TabPages[i]->Text = "Audio " + (i + 1);

		updatePossibleContainers();
	}

	void OneClickWindow::audioTab_MouseClick(object *sender, MouseEventArgs *e)
	{
		if (e->Button != MouseButtons::Right)
			return;

		Point *p = e->Location;
		for (int i = 0; i < audioTab->TabCount; i++)
		{
			Rectangle *rect = audioTab->GetTabRect(i);
			rect->Offset(2, 2);
			rect->Width -= 4;
			rect->Height -= 4;
			if (rect->Contains(p))
			{
				iSelectedAudioTabPage = i;
				audioMenu->Show(audioTab, e->Location);
				break;
			}
		}
	}

	void OneClickWindow::oneClickAudioStreamControl_FileUpdated(object *sender, EventArgs *e)
	{
		if (bLock)
			return;

		int i = audioTracks.find(static_cast<OneClickStreamControl*>(sender));

		if (i < 0)
			return;

		OneClickStreamControl *track = audioTracks[i];
		if (!track->getSelectedItem()->IsStandard)
			Nullable<int> tempVar = PrettyFormatting.getDelayAndCheck(track.getSelectedStream().getDemuxFilePath());
			track->getSelectedStream()->setDelay(tempVar::HasValue ? tempVar : 0);

		for (std::vector<OneClickStreamControl*>::const_iterator oControl = audioTracks.begin(); oControl != audioTracks.end(); ++oControl)
		{
			if (*oControl == track)
				continue;

			if (sizeof((*oControl)->getCustomStreams()) / sizeof((*oControl)->getCustomStreams()[0]) != sizeof(track->getCustomStreams()) / sizeof(track->getCustomStreams()[0]))
			{
				int iIndex = -1;
				if (!track->getSelectedItem()->IsStandard)
					iIndex = (*oControl)->getSelectedStreamIndex();
				bLock = true;
				(*oControl)->setCustomStreams(track->getCustomStreams());
				bLock = false;
				if (iIndex >= 0 && (*oControl)->getSelectedStreamIndex() != iIndex)
					(*oControl)->setSelectedStreamIndex(iIndex);
			}
		}

		updatePossibleContainers();
	}

	void OneClickWindow::AudioResetTrack(std::vector<OneClickStream*> &arrAudioTrackInfo, OneClickSettings *settings)
	{
		// generate track names
		std::vector<object*> trackNames = std::vector<object*>();
		trackNames.push_back("None");
		for (std::vector<OneClickStream*>::const_iterator o = arrAudioTrackInfo.begin(); o != arrAudioTrackInfo.end(); ++o)
			trackNames.push_back(*o);
		audioTracks[0]->setStandardStreams(trackNames.ToArray());
		audioTracks[0]->setCustomStreams(new object[0]);
		audioTracks[0]->setSelectedStreamIndex(0);

		// delete all tracks beside the first and last one
		try
		{
			while (audioTab->TabCount > 2)
				audioTab->TabPages->RemoveAt(1);
		}
		catch (std::exception &e1)
		{
		}
		audioTracks.RemoveRange(1, audioTracks.size() - 1);

		for (std::vector<std::string>::const_iterator strLanguage = settings->getDefaultAudioLanguage().begin(); strLanguage != settings->getDefaultAudioLanguage().end(); ++strLanguage)
			if ((*strLanguage).Equals("[none]"))
				return;

		int iCounter = 0;
		for (std::vector<std::string>::const_iterator strLanguage = settings->getDefaultAudioLanguage().begin(); strLanguage != settings->getDefaultAudioLanguage().end(); ++strLanguage)
		{
			for (int i = 0; i < arrAudioTrackInfo.size(); i++)
			{
				if (arrAudioTrackInfo[i]->getLanguage()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals((*strLanguage).ToLower(System::Globalization::CultureInfo::InvariantCulture)))
				{
					// should only the first audio track for this language be processed?
					bool bUseFirstTrackOnly = true;
					if (settings->getAudioSettings().size() > 0)
						bUseFirstTrackOnly = settings->getAudioSettings()[0]->getUseFirstTrackOnly();
					for (std::vector<OneClickAudioSettings*>::const_iterator oAudioSettings = settings->getAudioSettings().begin(); oAudioSettings != settings->getAudioSettings().end(); ++oAudioSettings)
					{
						if (arrAudioTrackInfo[i]->getLanguage()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals((*oAudioSettings)->getLanguage()->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
						{
							bUseFirstTrackOnly = (*oAudioSettings)->getUseFirstTrackOnly();
							break;
						}
					}

					bool bAddTrack = true;
					if (bUseFirstTrackOnly)
					{
						for (std::vector<OneClickStreamControl*>::const_iterator oAudioControl = audioTracks.begin(); oAudioControl != audioTracks.end(); ++oAudioControl)
						{
							if ((*oAudioControl)->getSelectedStreamIndex() > 0 && (*oAudioControl)->getSelectedStream()->Language->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(arrAudioTrackInfo[i]->getLanguage()->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
							{
								bAddTrack = false;
								break;
							}
						}
					}

					if (!bAddTrack)
						break;

					if (iCounter > 0)
						AudioAddTrack(false);
					audioTracks[iCounter++]->setSelectedStreamIndex(i + 1);
				}
			}
		}

		if (iCounter == 0 && arrAudioTrackInfo.size() > 0 && !settings->getUseNoLanguagesAsFallback())
		{
			for (int i = 0; i < arrAudioTrackInfo.size(); i++)
			{
				// should only the first audio track for this language be processed?
				bool bUseFirstTrackOnly = true;
				if (settings->getAudioSettings().size() > 0)
					bUseFirstTrackOnly = settings->getAudioSettings()[0]->getUseFirstTrackOnly();
				for (std::vector<OneClickAudioSettings*>::const_iterator oAudioSettings = settings->getAudioSettings().begin(); oAudioSettings != settings->getAudioSettings().end(); ++oAudioSettings)
				{
					if (arrAudioTrackInfo[i]->getLanguage()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals((*oAudioSettings)->getLanguage()->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
					{
						bUseFirstTrackOnly = (*oAudioSettings)->getUseFirstTrackOnly();
						break;
					}
				}

				bool bAddTrack = true;
				if (bUseFirstTrackOnly)
				{
					for (std::vector<OneClickStreamControl*>::const_iterator oAudioControl = audioTracks.begin(); oAudioControl != audioTracks.end(); ++oAudioControl)
					{
						if ((*oAudioControl)->getSelectedStreamIndex() > 0 && (*oAudioControl)->getSelectedStream()->Language->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(arrAudioTrackInfo[i]->getLanguage()->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
						{
							bAddTrack = false;
							break;
						}
					}
				}

				if (!bAddTrack)
					break;

				if (iCounter > 0)
					AudioAddTrack(false);
				audioTracks[iCounter++]->setSelectedStreamIndex(i + 1);
			}
		}

		ResetAudioSettings(settings);
	}

	void OneClickWindow::ResetAudioSettings(OneClickSettings *settings)
	{
		for (std::vector<OneClickStreamControl*>::const_iterator a = audioTracks.begin(); a != audioTracks.end(); ++a)
		{
			bool bFound = false;
			for (int i = 1; i < settings->getAudioSettings().size(); i++)
			{
				if ((*a)->getSelectedStream()->Language->Equals(settings->getAudioSettings()[i]->getLanguage()))
				{
					(*a)->SelectProfileNameOrWarn(settings->getAudioSettings()[i]->getProfile());
					(*a)->setEncodingMode(settings->getAudioSettings()[i]->getAudioEncodingMode());
					bFound = true;
					break;
				}
			}
			if (!bFound)
			{
				if (settings->getAudioSettings().size() > 0)
				{
					(*a)->SelectProfileNameOrWarn(settings->getAudioSettings()[0]->getProfile());
					(*a)->setEncodingMode(settings->getAudioSettings()[0]->getAudioEncodingMode());
				}
				else
					(*a)->setEncodingMode(IfCodecDoesNotMatch);
			}
		}
	}

	void OneClickWindow::audioTab_MouseDoubleClick(object *sender, MouseEventArgs *e)
	{
		AudioAddTrack(true);
	}

	void OneClickWindow::OneClickWindow_Shown(object *sender, EventArgs *e)
	{
		oneClickAudioStreamControl1->enableDragDrop();
		oneClickSubtitleStreamControl1->enableDragDrop();
		if (!input->getSelectedText().empty())
			OneClickProfileChanged(0, 0);
	}

	void OneClickWindow::audioTab_SelectedIndexChanged(object *sender, EventArgs *e)
	{
		if (audioTab->SelectedTab->Text->Equals("   +"))
			AudioAddTrack(true);
	}

	void OneClickWindow::audioTab_KeyUp(object *sender, KeyEventArgs *e)
	{
		if (e->KeyCode == Keys::Delete || e->KeyCode == Keys::Back)
			AudioRemoveTrack(audioTab->SelectedIndex);
	}

	void OneClickWindow::subtitlesTab_SelectedIndexChanged(object *sender, EventArgs *e)
	{
		if (subtitlesTab->SelectedTab->Text->Equals("   +"))
			SubtitleAddTrack(true);
	}

	void OneClickWindow::subtitlesTab_KeyUp(object *sender, KeyEventArgs *e)
	{
		if (e->KeyCode == Keys::Delete || e->KeyCode == Keys::Back)
			SubtitleRemoveTrack(audioTab->SelectedIndex);
	}

	bool OneClickWindow::isDontEncodeAudioPossible(MediaInfoFile *iFile, bool bIsStandardTrack, ContainerType *inputContainer)
	{
		if (!bIsStandardTrack)
			return true;

		if (iFile == 0)
			return false;

		if (inputContainer == ContainerType::MKV || iFile->getIndexerToUse() == FileIndexerWindow::D2V || iFile->getIndexerToUse() == FileIndexerWindow::DGA || iFile->getIndexerToUse() == FileIndexerWindow::DGI)
			return true;

		return false;
	}

	void OneClickWindow::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void OneClickWindow::InitializeComponent()
	{
		this->components = new System::ComponentModel::Container();
		System::Windows::Forms::Label *label1;
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(OneClickWindow::typeid);
		this->tabPage1 = new System::Windows::Forms::TabPage();
		this->outputTab = new System::Windows::Forms::TabControl();
		this->tabPage4 = new System::Windows::Forms::TabPage();
		this->label3 = new System::Windows::Forms::Label();
		this->outputLabel = new System::Windows::Forms::Label();
		this->videoTab = new System::Windows::Forms::TabControl();
		this->tabPage3 = new System::Windows::Forms::TabPage();
		this->inputLabel = new System::Windows::Forms::Label();
		this->audioTab = new System::Windows::Forms::TabControl();
		this->audioPage0 = new System::Windows::Forms::TabPage();
		this->tabPage2 = new System::Windows::Forms::TabPage();
		this->subtitlesTab = new System::Windows::Forms::TabControl();
		this->subPage0 = new System::Windows::Forms::TabPage();
		this->tabPage5 = new System::Windows::Forms::TabPage();
		this->subtitleMenu = new System::Windows::Forms::ContextMenuStrip(this->components);
		this->subtitleAddTrack = new System::Windows::Forms::ToolStripMenuItem();
		this->subtitleRemoveTrack = new System::Windows::Forms::ToolStripMenuItem();
		this->audioMenu = new System::Windows::Forms::ContextMenuStrip(this->components);
		this->audioAddTrack = new System::Windows::Forms::ToolStripMenuItem();
		this->audioRemoveTrack = new System::Windows::Forms::ToolStripMenuItem();
		this->tabControl1 = new System::Windows::Forms::TabControl();
		this->encoderConfigTab = new System::Windows::Forms::TabPage();
		this->avsBox = new System::Windows::Forms::GroupBox();
		this->keepInputResolution = new System::Windows::Forms::CheckBox();
		this->autoCrop = new System::Windows::Forms::CheckBox();
		this->autoDeint = new System::Windows::Forms::CheckBox();
		this->signalAR = new System::Windows::Forms::CheckBox();
		this->outputResolutionLabel = new System::Windows::Forms::Label();
		this->horizontalResolution = new System::Windows::Forms::NumericUpDown();
		this->label2 = new System::Windows::Forms::Label();
		this->ARLabel = new System::Windows::Forms::Label();
		this->locationGroupBox = new System::Windows::Forms::GroupBox();
		this->chapterLabel = new System::Windows::Forms::Label();
		this->workingDirectoryLabel = new System::Windows::Forms::Label();
		this->workingName = new System::Windows::Forms::TextBox();
		this->projectNameLabel = new System::Windows::Forms::Label();
		this->groupBox1 = new System::Windows::Forms::GroupBox();
		this->filesizeLabel = new System::Windows::Forms::Label();
		this->devicetype = new System::Windows::Forms::ComboBox();
		this->deviceLabel = new System::Windows::Forms::Label();
		this->containerFormatLabel = new System::Windows::Forms::Label();
		this->containerFormat = new System::Windows::Forms::ComboBox();
		this->videoGroupBox = new System::Windows::Forms::GroupBox();
		this->chkDontEncodeVideo = new System::Windows::Forms::CheckBox();
		this->usechaptersmarks = new System::Windows::Forms::CheckBox();
		this->label4 = new System::Windows::Forms::Label();
		this->addPrerenderJob = new System::Windows::Forms::CheckBox();
		this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
		this->goButton = new System::Windows::Forms::Button();
		this->openOnQueue = new System::Windows::Forms::CheckBox();
		this->cbGUIMode = new System::Windows::Forms::ComboBox();
		this->helpButton1 = new MeGUI::core::gui::HelpButton();
		this->oneclickProfile = new MeGUI::core::gui::ConfigableProfilesControl();
		this->output = new MeGUI::FileBar();
		this->input = new MeGUI::core::gui::FileSCBox();
		this->oneClickAudioStreamControl1 = new MeGUI::OneClickStreamControl();
		this->oneClickSubtitleStreamControl1 = new MeGUI::OneClickStreamControl();
		this->avsProfile = new MeGUI::core::gui::ConfigableProfilesControl();
		this->ar = new MeGUI::core::gui::ARChooser();
		this->chapterFile = new MeGUI::FileBar();
		this->workingDirectory = new MeGUI::FileBar();
		this->fileSize = new MeGUI::core::gui::TargetSizeSCBox();
		this->splitting = new MeGUI::core::gui::TargetSizeSCBox();
		this->videoProfile = new MeGUI::core::gui::ConfigableProfilesControl();
		label1 = new System::Windows::Forms::Label();
		this->tabPage1->SuspendLayout();
		this->outputTab->SuspendLayout();
		this->tabPage4->SuspendLayout();
		this->videoTab->SuspendLayout();
		this->tabPage3->SuspendLayout();
		this->audioTab->SuspendLayout();
		this->audioPage0->SuspendLayout();
		this->subtitlesTab->SuspendLayout();
		this->subPage0->SuspendLayout();
		this->subtitleMenu->SuspendLayout();
		this->audioMenu->SuspendLayout();
		this->tabControl1->SuspendLayout();
		this->encoderConfigTab->SuspendLayout();
		this->avsBox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->horizontalResolution))->BeginInit();
		this->locationGroupBox->SuspendLayout();
		this->groupBox1->SuspendLayout();
		this->videoGroupBox->SuspendLayout();
		this->SuspendLayout();
		// 
		// label1
		// 
		label1->AutoSize = true;
		label1->Location = new System::Drawing::Point(6, 47);
		label1->Name = "label1";
		label1->Size = new System::Drawing::Size(45, 13);
		label1->TabIndex = 39;
		label1->Text = "Splitting";
		// 
		// tabPage1
		// 
		this->tabPage1->Controls->Add(this->outputTab);
		this->tabPage1->Controls->Add(this->videoTab);
		this->tabPage1->Controls->Add(this->audioTab);
		this->tabPage1->Controls->Add(this->subtitlesTab);
		this->tabPage1->Location = new System::Drawing::Point(4, 22);
		this->tabPage1->Name = "tabPage1";
		this->tabPage1->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage1->Size = new System::Drawing::Size(464, 487);
		this->tabPage1->TabIndex = 0;
		this->tabPage1->Text = "General";
		this->tabPage1->UseVisualStyleBackColor = true;
		// 
		// outputTab
		// 
		this->outputTab->Controls->Add(this->tabPage4);
		this->outputTab->Location = new System::Drawing::Point(6, 379);
		this->outputTab->Name = "outputTab";
		this->outputTab->SelectedIndex = 0;
		this->outputTab->Size = new System::Drawing::Size(452, 95);
		this->outputTab->TabIndex = 22;
		// 
		// tabPage4
		// 
		this->tabPage4->Controls->Add(this->oneclickProfile);
		this->tabPage4->Controls->Add(this->label3);
		this->tabPage4->Controls->Add(this->output);
		this->tabPage4->Controls->Add(this->outputLabel);
		this->tabPage4->Location = new System::Drawing::Point(4, 22);
		this->tabPage4->Name = "tabPage4";
		this->tabPage4->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage4->Size = new System::Drawing::Size(444, 69);
		this->tabPage4->TabIndex = 0;
		this->tabPage4->Text = "Output";
		this->tabPage4->UseVisualStyleBackColor = true;
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = new System::Drawing::Point(3, 44);
		this->label3->Name = "label3";
		this->label3->Size = new System::Drawing::Size(81, 13);
		this->label3->TabIndex = 30;
		this->label3->Text = "OneClick profile";
		// 
		// outputLabel
		// 
		this->outputLabel->Location = new System::Drawing::Point(3, 14);
		this->outputLabel->Name = "outputLabel";
		this->outputLabel->Size = new System::Drawing::Size(100, 13);
		this->outputLabel->TabIndex = 28;
		this->outputLabel->Text = "Output file";
		// 
		// videoTab
		// 
		this->videoTab->Controls->Add(this->tabPage3);
		this->videoTab->Location = new System::Drawing::Point(6, 6);
		this->videoTab->Name = "videoTab";
		this->videoTab->SelectedIndex = 0;
		this->videoTab->Size = new System::Drawing::Size(452, 65);
		this->videoTab->TabIndex = 21;
		// 
		// tabPage3
		// 
		this->tabPage3->Controls->Add(this->input);
		this->tabPage3->Controls->Add(this->inputLabel);
		this->tabPage3->Location = new System::Drawing::Point(4, 22);
		this->tabPage3->Name = "tabPage3";
		this->tabPage3->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage3->Size = new System::Drawing::Size(444, 39);
		this->tabPage3->TabIndex = 0;
		this->tabPage3->Text = "Video";
		this->tabPage3->UseVisualStyleBackColor = true;
		// 
		// inputLabel
		// 
		this->inputLabel->Location = new System::Drawing::Point(8, 14);
		this->inputLabel->Name = "inputLabel";
		this->inputLabel->Size = new System::Drawing::Size(100, 13);
		this->inputLabel->TabIndex = 49;
		this->inputLabel->Text = "Input";
		// 
		// audioTab
		// 
		this->audioTab->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->audioTab->Controls->Add(this->audioPage0);
		this->audioTab->Controls->Add(this->tabPage2);
		this->audioTab->Location = new System::Drawing::Point(6, 77);
		this->audioTab->Name = "audioTab";
		this->audioTab->SelectedIndex = 0;
		this->audioTab->Size = new System::Drawing::Size(452, 175);
		this->audioTab->TabIndex = 20;
		this->audioTab->SelectedIndexChanged += new System::EventHandler(this, &OneClickWindow::audioTab_SelectedIndexChanged);
		this->audioTab->KeyUp += new System::Windows::Forms::KeyEventHandler(this, &OneClickWindow::audioTab_KeyUp);
		this->audioTab->MouseClick += new System::Windows::Forms::MouseEventHandler(this, &OneClickWindow::audioTab_MouseClick);
		this->audioTab->MouseDoubleClick += new System::Windows::Forms::MouseEventHandler(this, &OneClickWindow::audioTab_MouseDoubleClick);
		// 
		// audioPage0
		// 
		this->audioPage0->Controls->Add(this->oneClickAudioStreamControl1);
		this->audioPage0->Location = new System::Drawing::Point(4, 22);
		this->audioPage0->Name = "audioPage0";
		this->audioPage0->Padding = new System::Windows::Forms::Padding(3);
		this->audioPage0->Size = new System::Drawing::Size(444, 149);
		this->audioPage0->TabIndex = 2;
		this->audioPage0->Text = "Audio 1";
		this->audioPage0->UseVisualStyleBackColor = true;
		// 
		// tabPage2
		// 
		this->tabPage2->Location = new System::Drawing::Point(4, 22);
		this->tabPage2->Name = "tabPage2";
		this->tabPage2->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage2->Size = new System::Drawing::Size(444, 149);
		this->tabPage2->TabIndex = 3;
		this->tabPage2->Text = "   +";
		this->tabPage2->UseVisualStyleBackColor = true;
		// 
		// subtitlesTab
		// 
		this->subtitlesTab->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->subtitlesTab->Controls->Add(this->subPage0);
		this->subtitlesTab->Controls->Add(this->tabPage5);
		this->subtitlesTab->Location = new System::Drawing::Point(6, 258);
		this->subtitlesTab->Name = "subtitlesTab";
		this->subtitlesTab->SelectedIndex = 0;
		this->subtitlesTab->Size = new System::Drawing::Size(452, 115);
		this->subtitlesTab->TabIndex = 19;
		this->subtitlesTab->SelectedIndexChanged += new System::EventHandler(this, &OneClickWindow::subtitlesTab_SelectedIndexChanged);
		this->subtitlesTab->KeyUp += new System::Windows::Forms::KeyEventHandler(this, &OneClickWindow::subtitlesTab_KeyUp);
		this->subtitlesTab->MouseClick += new System::Windows::Forms::MouseEventHandler(this, &OneClickWindow::subtitlesTab_MouseClick);
		this->subtitlesTab->MouseDoubleClick += new System::Windows::Forms::MouseEventHandler(this, &OneClickWindow::subtitlesTab_MouseDoubleClick);
		// 
		// subPage0
		// 
		this->subPage0->Controls->Add(this->oneClickSubtitleStreamControl1);
		this->subPage0->Location = new System::Drawing::Point(4, 22);
		this->subPage0->Name = "subPage0";
		this->subPage0->Padding = new System::Windows::Forms::Padding(3);
		this->subPage0->Size = new System::Drawing::Size(444, 89);
		this->subPage0->TabIndex = 2;
		this->subPage0->Text = "Subtitle 1";
		this->subPage0->UseVisualStyleBackColor = true;
		// 
		// tabPage5
		// 
		this->tabPage5->Location = new System::Drawing::Point(4, 22);
		this->tabPage5->Name = "tabPage5";
		this->tabPage5->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage5->Size = new System::Drawing::Size(444, 89);
		this->tabPage5->TabIndex = 3;
		this->tabPage5->Text = "   +";
		this->tabPage5->UseVisualStyleBackColor = true;
		// 
		// subtitleMenu
		// 
		this->subtitleMenu->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->subtitleAddTrack, this->subtitleRemoveTrack});
		this->subtitleMenu->Name = "subtitleMenu";
		this->subtitleMenu->Size = new System::Drawing::Size(150, 48);
		this->subtitleMenu->Opening += new System::ComponentModel::CancelEventHandler(this, &OneClickWindow::subtitleMenu_Opening);
		// 
		// subtitleAddTrack
		// 
		this->subtitleAddTrack->Name = "subtitleAddTrack";
		this->subtitleAddTrack->Size = new System::Drawing::Size(149, 22);
		this->subtitleAddTrack->Text = "Add Track";
		this->subtitleAddTrack->Click += new System::EventHandler(this, &OneClickWindow::subtitleAddTrack_Click);
		// 
		// subtitleRemoveTrack
		// 
		this->subtitleRemoveTrack->Name = "subtitleRemoveTrack";
		this->subtitleRemoveTrack->Size = new System::Drawing::Size(149, 22);
		this->subtitleRemoveTrack->Text = "Remove Track";
		this->subtitleRemoveTrack->Click += new System::EventHandler(this, &OneClickWindow::subtitleRemoveTrack_Click);
		// 
		// audioMenu
		// 
		this->audioMenu->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->audioAddTrack, this->audioRemoveTrack});
		this->audioMenu->Name = "audioMenu";
		this->audioMenu->Size = new System::Drawing::Size(150, 48);
		this->audioMenu->Opening += new System::ComponentModel::CancelEventHandler(this, &OneClickWindow::audioMenu_Opening);
		// 
		// audioAddTrack
		// 
		this->audioAddTrack->Name = "audioAddTrack";
		this->audioAddTrack->Size = new System::Drawing::Size(149, 22);
		this->audioAddTrack->Text = "Add Track";
		this->audioAddTrack->Click += new System::EventHandler(this, &OneClickWindow::audioAddTrack_Click);
		// 
		// audioRemoveTrack
		// 
		this->audioRemoveTrack->Name = "audioRemoveTrack";
		this->audioRemoveTrack->Size = new System::Drawing::Size(149, 22);
		this->audioRemoveTrack->Text = "Remove Track";
		this->audioRemoveTrack->Click += new System::EventHandler(this, &OneClickWindow::audioRemoveTrack_Click);
		// 
		// tabControl1
		// 
		this->tabControl1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->tabControl1->Controls->Add(this->tabPage1);
		this->tabControl1->Controls->Add(this->encoderConfigTab);
		this->tabControl1->Location = new System::Drawing::Point(0, 0);
		this->tabControl1->Name = "tabControl1";
		this->tabControl1->SelectedIndex = 0;
		this->tabControl1->Size = new System::Drawing::Size(472, 513);
		this->tabControl1->TabIndex = 0;
		// 
		// encoderConfigTab
		// 
		this->encoderConfigTab->Controls->Add(this->avsBox);
		this->encoderConfigTab->Controls->Add(this->locationGroupBox);
		this->encoderConfigTab->Controls->Add(this->groupBox1);
		this->encoderConfigTab->Controls->Add(this->videoGroupBox);
		this->encoderConfigTab->Location = new System::Drawing::Point(4, 22);
		this->encoderConfigTab->Name = "encoderConfigTab";
		this->encoderConfigTab->Padding = new System::Windows::Forms::Padding(3);
		this->encoderConfigTab->Size = new System::Drawing::Size(464, 487);
		this->encoderConfigTab->TabIndex = 2;
		this->encoderConfigTab->Text = "Advanced Config";
		this->encoderConfigTab->UseVisualStyleBackColor = true;
		// 
		// avsBox
		// 
		this->avsBox->Controls->Add(this->keepInputResolution);
		this->avsBox->Controls->Add(this->autoCrop);
		this->avsBox->Controls->Add(this->avsProfile);
		this->avsBox->Controls->Add(this->ar);
		this->avsBox->Controls->Add(this->autoDeint);
		this->avsBox->Controls->Add(this->signalAR);
		this->avsBox->Controls->Add(this->outputResolutionLabel);
		this->avsBox->Controls->Add(this->horizontalResolution);
		this->avsBox->Controls->Add(this->label2);
		this->avsBox->Controls->Add(this->ARLabel);
		this->avsBox->Location = new System::Drawing::Point(6, 102);
		this->avsBox->Name = "avsBox";
		this->avsBox->Size = new System::Drawing::Size(452, 144);
		this->avsBox->TabIndex = 44;
		this->avsBox->TabStop = false;
		this->avsBox->Text = " AviSynth Settings ";
		// 
		// keepInputResolution
		// 
		this->keepInputResolution->AutoSize = true;
		this->keepInputResolution->Location = new System::Drawing::Point(120, 42);
		this->keepInputResolution->Name = "keepInputResolution";
		this->keepInputResolution->Size = new System::Drawing::Size(246, 17);
		this->keepInputResolution->TabIndex = 25;
		this->keepInputResolution->Text = "Keep Input Resolution (disable crop && resize)";
		this->keepInputResolution->UseVisualStyleBackColor = true;
		this->keepInputResolution->CheckedChanged += new System::EventHandler(this, &OneClickWindow::keepInputResolution_CheckedChanged);
		// 
		// autoCrop
		// 
		this->autoCrop->AutoSize = true;
		this->autoCrop->Checked = true;
		this->autoCrop->CheckState = System::Windows::Forms::CheckState::Checked;
		this->autoCrop->Location = new System::Drawing::Point(202, 19);
		this->autoCrop->Name = "autoCrop";
		this->autoCrop->Size = new System::Drawing::Size(72, 17);
		this->autoCrop->TabIndex = 24;
		this->autoCrop->Text = "AutoCrop";
		this->autoCrop->UseVisualStyleBackColor = true;
		// 
		// autoDeint
		// 
		this->autoDeint->AutoSize = true;
		this->autoDeint->Location = new System::Drawing::Point(119, 120);
		this->autoDeint->Name = "autoDeint";
		this->autoDeint->Size = new System::Drawing::Size(139, 17);
		this->autoDeint->TabIndex = 20;
		this->autoDeint->Text = "Automatic Deinterlacing";
		this->autoDeint->UseVisualStyleBackColor = true;
		// 
		// signalAR
		// 
		this->signalAR->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
		this->signalAR->AutoSize = true;
		this->signalAR->Location = new System::Drawing::Point(282, 19);
		this->signalAR->Name = "signalAR";
		this->signalAR->Size = new System::Drawing::Size(112, 17);
		this->signalAR->TabIndex = 5;
		this->signalAR->Text = "Anamorph Output";
		// 
		// outputResolutionLabel
		// 
		this->outputResolutionLabel->Location = new System::Drawing::Point(6, 20);
		this->outputResolutionLabel->Name = "outputResolutionLabel";
		this->outputResolutionLabel->Size = new System::Drawing::Size(100, 13);
		this->outputResolutionLabel->TabIndex = 3;
		this->outputResolutionLabel->Text = "Output Resolution";
		// 
		// horizontalResolution
		// 
		this->horizontalResolution->Increment = decimal(new int[4] {16, 0, 0, 0});
		this->horizontalResolution->Location = new System::Drawing::Point(120, 16);
		this->horizontalResolution->Maximum = decimal(new int[4] {5000, 0, 0, 0});
		this->horizontalResolution->Minimum = decimal(new int[4] {16, 0, 0, 0});
		this->horizontalResolution->Name = "horizontalResolution";
		this->horizontalResolution->Size = new System::Drawing::Size(64, 21);
		this->horizontalResolution->TabIndex = 0;
		this->horizontalResolution->Value = decimal(new int[4] {640, 0, 0, 0});
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = new System::Drawing::Point(7, 96);
		this->label2->Name = "label2";
		this->label2->Size = new System::Drawing::Size(82, 13);
		this->label2->TabIndex = 4;
		this->label2->Text = "Avisynth Profile";
		// 
		// ARLabel
		// 
		this->ARLabel->AutoSize = true;
		this->ARLabel->Location = new System::Drawing::Point(6, 69);
		this->ARLabel->Name = "ARLabel";
		this->ARLabel->Size = new System::Drawing::Size(105, 13);
		this->ARLabel->TabIndex = 4;
		this->ARLabel->Text = "Display Aspect Ratio";
		// 
		// locationGroupBox
		// 
		this->locationGroupBox->Controls->Add(this->chapterFile);
		this->locationGroupBox->Controls->Add(this->workingDirectory);
		this->locationGroupBox->Controls->Add(this->chapterLabel);
		this->locationGroupBox->Controls->Add(this->workingDirectoryLabel);
		this->locationGroupBox->Controls->Add(this->workingName);
		this->locationGroupBox->Controls->Add(this->projectNameLabel);
		this->locationGroupBox->Location = new System::Drawing::Point(6, 359);
		this->locationGroupBox->Name = "locationGroupBox";
		this->locationGroupBox->Size = new System::Drawing::Size(452, 122);
		this->locationGroupBox->TabIndex = 43;
		this->locationGroupBox->TabStop = false;
		this->locationGroupBox->Text = " Extra IO ";
		// 
		// chapterLabel
		// 
		this->chapterLabel->Location = new System::Drawing::Point(6, 53);
		this->chapterLabel->Name = "chapterLabel";
		this->chapterLabel->Size = new System::Drawing::Size(100, 13);
		this->chapterLabel->TabIndex = 36;
		this->chapterLabel->Text = "Chapter File";
		// 
		// workingDirectoryLabel
		// 
		this->workingDirectoryLabel->Location = new System::Drawing::Point(6, 21);
		this->workingDirectoryLabel->Name = "workingDirectoryLabel";
		this->workingDirectoryLabel->Size = new System::Drawing::Size(100, 13);
		this->workingDirectoryLabel->TabIndex = 32;
		this->workingDirectoryLabel->Text = "Working Directory";
		// 
		// workingName
		// 
		this->workingName->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->workingName->Location = new System::Drawing::Point(119, 79);
		this->workingName->Name = "workingName";
		this->workingName->Size = new System::Drawing::Size(329, 21);
		this->workingName->TabIndex = 30;
		this->workingName->TextChanged += new System::EventHandler(this, &OneClickWindow::workingName_TextChanged);
		// 
		// projectNameLabel
		// 
		this->projectNameLabel->Location = new System::Drawing::Point(6, 82);
		this->projectNameLabel->Name = "projectNameLabel";
		this->projectNameLabel->Size = new System::Drawing::Size(73, 16);
		this->projectNameLabel->TabIndex = 31;
		this->projectNameLabel->Text = "Project Name";
		// 
		// groupBox1
		// 
		this->groupBox1->Controls->Add(this->fileSize);
		this->groupBox1->Controls->Add(this->filesizeLabel);
		this->groupBox1->Controls->Add(this->devicetype);
		this->groupBox1->Controls->Add(this->deviceLabel);
		this->groupBox1->Controls->Add(this->containerFormatLabel);
		this->groupBox1->Controls->Add(this->containerFormat);
		this->groupBox1->Controls->Add(label1);
		this->groupBox1->Controls->Add(this->splitting);
		this->groupBox1->Location = new System::Drawing::Point(6, 252);
		this->groupBox1->Name = "groupBox1";
		this->groupBox1->Size = new System::Drawing::Size(452, 100);
		this->groupBox1->TabIndex = 42;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = " Output Settings ";
		// 
		// filesizeLabel
		// 
		this->filesizeLabel->Location = new System::Drawing::Point(6, 21);
		this->filesizeLabel->Name = "filesizeLabel";
		this->filesizeLabel->Size = new System::Drawing::Size(90, 13);
		this->filesizeLabel->TabIndex = 45;
		this->filesizeLabel->Text = "Filesize";
		// 
		// devicetype
		// 
		this->devicetype->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->devicetype->FormattingEnabled = true;
		this->devicetype->Location = new System::Drawing::Point(351, 69);
		this->devicetype->Name = "devicetype";
		this->devicetype->Size = new System::Drawing::Size(95, 21);
		this->devicetype->TabIndex = 44;
		// 
		// deviceLabel
		// 
		this->deviceLabel->AutoSize = true;
		this->deviceLabel->Location = new System::Drawing::Point(279, 72);
		this->deviceLabel->Name = "deviceLabel";
		this->deviceLabel->Size = new System::Drawing::Size(66, 13);
		this->deviceLabel->TabIndex = 43;
		this->deviceLabel->Text = "Device Type";
		// 
		// containerFormatLabel
		// 
		this->containerFormatLabel->AutoSize = true;
		this->containerFormatLabel->Location = new System::Drawing::Point(6, 72);
		this->containerFormatLabel->Name = "containerFormatLabel";
		this->containerFormatLabel->Size = new System::Drawing::Size(91, 13);
		this->containerFormatLabel->TabIndex = 42;
		this->containerFormatLabel->Text = "Container Format";
		// 
		// containerFormat
		// 
		this->containerFormat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->containerFormat->Location = new System::Drawing::Point(120, 69);
		this->containerFormat->Name = "containerFormat";
		this->containerFormat->Size = new System::Drawing::Size(95, 21);
		this->containerFormat->TabIndex = 41;
		this->containerFormat->SelectedIndexChanged += new System::EventHandler(this, &OneClickWindow::containerFormat_SelectedIndexChanged);
		// 
		// videoGroupBox
		// 
		this->videoGroupBox->Controls->Add(this->chkDontEncodeVideo);
		this->videoGroupBox->Controls->Add(this->usechaptersmarks);
		this->videoGroupBox->Controls->Add(this->label4);
		this->videoGroupBox->Controls->Add(this->videoProfile);
		this->videoGroupBox->Controls->Add(this->addPrerenderJob);
		this->videoGroupBox->Location = new System::Drawing::Point(6, 6);
		this->videoGroupBox->Name = "videoGroupBox";
		this->videoGroupBox->Size = new System::Drawing::Size(452, 90);
		this->videoGroupBox->TabIndex = 41;
		this->videoGroupBox->TabStop = false;
		this->videoGroupBox->Text = " Video Settings ";
		// 
		// chkDontEncodeVideo
		// 
		this->chkDontEncodeVideo->AutoSize = true;
		this->chkDontEncodeVideo->Location = new System::Drawing::Point(119, 16);
		this->chkDontEncodeVideo->Name = "chkDontEncodeVideo";
		this->chkDontEncodeVideo->Size = new System::Drawing::Size(118, 17);
		this->chkDontEncodeVideo->TabIndex = 40;
		this->chkDontEncodeVideo->Text = "Don\'t encode video";
		this->chkDontEncodeVideo->UseVisualStyleBackColor = true;
		this->chkDontEncodeVideo->CheckedChanged += new System::EventHandler(this, &OneClickWindow::chkDontEncodeVideo_CheckedChanged);
		// 
		// usechaptersmarks
		// 
		this->usechaptersmarks->AutoSize = true;
		this->usechaptersmarks->Location = new System::Drawing::Point(120, 67);
		this->usechaptersmarks->Name = "usechaptersmarks";
		this->usechaptersmarks->Size = new System::Drawing::Size(234, 17);
		this->usechaptersmarks->TabIndex = 39;
		this->usechaptersmarks->Text = "Force using Key-Frames for chapters marks";
		this->usechaptersmarks->UseVisualStyleBackColor = true;
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = new System::Drawing::Point(7, 42);
		this->label4->Name = "label4";
		this->label4->Size = new System::Drawing::Size(88, 13);
		this->label4->TabIndex = 38;
		this->label4->Text = "Encoder Settings";
		// 
		// addPrerenderJob
		// 
		this->addPrerenderJob->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
		this->addPrerenderJob->AutoSize = true;
		this->addPrerenderJob->Location = new System::Drawing::Point(-507, 47);
		this->addPrerenderJob->Name = "addPrerenderJob";
		this->addPrerenderJob->Size = new System::Drawing::Size(132, 17);
		this->addPrerenderJob->TabIndex = 16;
		this->addPrerenderJob->Text = "Add pre-rendering job";
		this->addPrerenderJob->UseVisualStyleBackColor = true;
		// 
		// openFileDialog
		// 
		this->openFileDialog->Filter = "IFO Files|*.ifo|VOB Files (*.vob)|*.vob|MPEG-1/2 Program Streams (*.mpg)|*.mpg|Tr" + "ansport Streams (*.ts)|*.ts";
		// 
		// goButton
		// 
		this->goButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->goButton->Location = new System::Drawing::Point(385, 519);
		this->goButton->Name = "goButton";
		this->goButton->Size = new System::Drawing::Size(75, 23);
		this->goButton->TabIndex = 29;
		this->goButton->Text = "Go!";
		this->goButton->UseVisualStyleBackColor = true;
		this->goButton->Click += new System::EventHandler(this, &OneClickWindow::goButton_Click);
		// 
		// openOnQueue
		// 
		this->openOnQueue->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->openOnQueue->Checked = true;
		this->openOnQueue->CheckState = System::Windows::Forms::CheckState::Checked;
		this->openOnQueue->Location = new System::Drawing::Point(273, 520);
		this->openOnQueue->Name = "openOnQueue";
		this->openOnQueue->Size = new System::Drawing::Size(106, 24);
		this->openOnQueue->TabIndex = 33;
		this->openOnQueue->Text = "close after Go!";
		// 
		// cbGUIMode
		// 
		this->cbGUIMode->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->cbGUIMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbGUIMode->FormattingEnabled = true;
		this->cbGUIMode->Location = new System::Drawing::Point(104, 521);
		this->cbGUIMode->Name = "cbGUIMode";
		this->cbGUIMode->Size = new System::Drawing::Size(145, 21);
		this->cbGUIMode->TabIndex = 34;
		this->cbGUIMode->SelectedIndexChanged += new System::EventHandler(this, &OneClickWindow::cbGUIMode_SelectedIndexChanged);
		// 
		// helpButton1
		// 
		this->helpButton1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
		this->helpButton1->setArticleName("One Click Encoder");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(12, 519);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 32;
		// 
		// oneclickProfile
		// 
		this->oneclickProfile->Location = new System::Drawing::Point(99, 40);
		this->oneclickProfile->Name = "oneclickProfile";
		this->oneclickProfile->setProfileSet("OneClick");
		this->oneclickProfile->Size = new System::Drawing::Size(332, 22);
		this->oneclickProfile->TabIndex = 31;
		this->oneclickProfile->SelectedProfileChanged += new System::EventHandler(this, &OneClickWindow::OneClickProfileChanged);
		// 
		// output
		// 
		this->output->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->output->setFilename("");
		this->output->setFilter("MP4 Files|*.mp4");
		this->output->setFilterIndex(0);
		this->output->setFolderMode(false);
		this->output->Location = new System::Drawing::Point(99, 8);
		this->output->Name = "output";
		this->output->setReadOnly(true);
		this->output->setSaveMode(true);
		this->output->Size = new System::Drawing::Size(333, 26);
		this->output->TabIndex = 29;
		this->output->setTitle("");
		this->output->FileSelected += new MeGUI::FileBarEventHandler(this, &OneClickWindow::output_FileSelected);
		// 
		// input
		// 
		this->input->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->input->setFilter("All files (*.*)|*.*");
		this->input->Location = new System::Drawing::Point(63, 6);
		this->input->MaximumSize = new System::Drawing::Size(1000, 29);
		this->input->MinimumSize = new System::Drawing::Size(64, 29);
		this->input->Name = "input";
		this->input->setSelectedIndex(-1);
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete this->input->getSelectedItem();
		this->input->Size = new System::Drawing::Size(368, 29);
		this->input->TabIndex = 50;
		this->input->setType(MeGUI::core::gui::FileSCBox::OC_FILE_AND_FOLDER);
		this->input->SelectionChanged += new MeGUI::StringChanged(this, &OneClickWindow::input_SelectionChanged);
		// 
		// oneClickAudioStreamControl1
		// 
		this->oneClickAudioStreamControl1->setCustomStreams(new object[0]);
		this->oneClickAudioStreamControl1->setFilter("All files (*.*)|*.*");
		this->oneClickAudioStreamControl1->Location = new System::Drawing::Point(0, 0);
		this->oneClickAudioStreamControl1->Name = "oneClickAudioStreamControl1";
		this->oneClickAudioStreamControl1->setSelectedStreamIndex(0);
		this->oneClickAudioStreamControl1->setShowDefaultStream(false);
		this->oneClickAudioStreamControl1->setShowDelay(true);
		this->oneClickAudioStreamControl1->setShowForceStream(false);
		this->oneClickAudioStreamControl1->Size = new System::Drawing::Size(434, 149);
		this->oneClickAudioStreamControl1->setStandardStreams(new object[0]);
		this->oneClickAudioStreamControl1->TabIndex = 0;
		this->oneClickAudioStreamControl1->FileUpdated += new System::EventHandler(this, &OneClickWindow::oneClickAudioStreamControl_FileUpdated);
		// 
		// oneClickSubtitleStreamControl1
		// 
		this->oneClickSubtitleStreamControl1->setCustomStreams(new object[0]);
		this->oneClickSubtitleStreamControl1->setFilter("All files (*.*)|*.*");
		this->oneClickSubtitleStreamControl1->Location = new System::Drawing::Point(0, 0);
		this->oneClickSubtitleStreamControl1->Name = "oneClickSubtitleStreamControl1";
		this->oneClickSubtitleStreamControl1->setSelectedStreamIndex(0);
		this->oneClickSubtitleStreamControl1->setShowDefaultStream(true);
		this->oneClickSubtitleStreamControl1->setShowDelay(true);
		this->oneClickSubtitleStreamControl1->setShowForceStream(true);
		this->oneClickSubtitleStreamControl1->Size = new System::Drawing::Size(434, 90);
		this->oneClickSubtitleStreamControl1->setStandardStreams(new object[0]);
		this->oneClickSubtitleStreamControl1->TabIndex = 0;
		this->oneClickSubtitleStreamControl1->FileUpdated += new System::EventHandler(this, &OneClickWindow::oneClickSubtitleStreamControl_FileUpdated);
		// 
		// avsProfile
		// 
		this->avsProfile->Location = new System::Drawing::Point(119, 92);
		this->avsProfile->Name = "avsProfile";
		this->avsProfile->setProfileSet("AviSynth");
		this->avsProfile->Size = new System::Drawing::Size(330, 22);
		this->avsProfile->TabIndex = 23;
		// 
		// ar
		// 
		this->ar->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->ar->setCustomDARs(new MeGUI::core::util::Dar[0]);
		this->ar->setHasLater(true);
		this->ar->Location = new System::Drawing::Point(119, 61);
		this->ar->MaximumSize = new System::Drawing::Size(1000, 29);
		this->ar->MinimumSize = new System::Drawing::Size(64, 29);
		this->ar->Name = "ar";
		this->ar->setSelectedIndex(0);
		this->ar->Size = new System::Drawing::Size(330, 29);
		this->ar->TabIndex = 22;
		// 
		// chapterFile
		// 
		this->chapterFile->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->chapterFile->setFilename("");
		this->chapterFile->setFilter("Chapter files (*.txt)|*.txt");
		this->chapterFile->setFilterIndex(0);
		this->chapterFile->setFolderMode(false);
		this->chapterFile->Location = new System::Drawing::Point(120, 47);
		this->chapterFile->Name = "chapterFile";
		this->chapterFile->setReadOnly(true);
		this->chapterFile->setSaveMode(false);
		this->chapterFile->Size = new System::Drawing::Size(326, 26);
		this->chapterFile->TabIndex = 39;
		this->chapterFile->setTitle("");
		// 
		// workingDirectory
		// 
		this->workingDirectory->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->workingDirectory->setFilename("");
		this->workingDirectory->setFilter("");
		this->workingDirectory->setFilterIndex(0);
		this->workingDirectory->setFolderMode(true);
		this->workingDirectory->Location = new System::Drawing::Point(120, 15);
		this->workingDirectory->Name = "workingDirectory";
		this->workingDirectory->setReadOnly(true);
		this->workingDirectory->setSaveMode(false);
		this->workingDirectory->Size = new System::Drawing::Size(326, 26);
		this->workingDirectory->TabIndex = 38;
		this->workingDirectory->setTitle("");
		this->workingDirectory->FileSelected += new MeGUI::FileBarEventHandler(this, &OneClickWindow::workingDirectory_FileSelected);
		// 
		// fileSize
		// 
		this->fileSize->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->fileSize->setCustomSizes(new MeGUI::core::util::FileSize[0]);
		this->fileSize->Location = new System::Drawing::Point(120, 13);
		this->fileSize->MaximumSize = new System::Drawing::Size(1000, 29);
		this->fileSize->MinimumSize = new System::Drawing::Size(64, 29);
		this->fileSize->Name = "fileSize";
		this->fileSize->setNullString("Don\'t Care");
		this->fileSize->setSaveCustomValues(false);
		this->fileSize->setSelectedIndex(0);
		this->fileSize->Size = new System::Drawing::Size(326, 29);
		this->fileSize->TabIndex = 46;
		// 
		// splitting
		// 
		this->splitting->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->splitting->AutoSize = true;
		this->splitting->setCustomSizes(new MeGUI::core::util::FileSize[0]);
		this->splitting->Location = new System::Drawing::Point(120, 40);
		this->splitting->MaximumSize = new System::Drawing::Size(1000, 29);
		this->splitting->MinimumSize = new System::Drawing::Size(64, 29);
		this->splitting->Name = "splitting";
		this->splitting->setNullString("No splitting");
		this->splitting->setSaveCustomValues(false);
		this->splitting->setSelectedIndex(0);
		this->splitting->Size = new System::Drawing::Size(326, 29);
		this->splitting->TabIndex = 40;
		// 
		// videoProfile
		// 
		this->videoProfile->Location = new System::Drawing::Point(119, 39);
		this->videoProfile->Name = "videoProfile";
		this->videoProfile->setProfileSet("Video");
		this->videoProfile->Size = new System::Drawing::Size(327, 22);
		this->videoProfile->TabIndex = 17;
		this->videoProfile->SelectedProfileChanged += new System::EventHandler(this, &OneClickWindow::ProfileChanged);
		// 
		// OneClickWindow
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = new System::Drawing::Size(472, 550);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->openOnQueue);
		this->Controls->Add(this->tabControl1);
		this->Controls->Add(this->goButton);
		this->Controls->Add(this->cbGUIMode);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->Name = "OneClickWindow";
		this->Text = "MeGUI - One Click Encoder";
		this->Shown += new System::EventHandler(this, &OneClickWindow::OneClickWindow_Shown);
		this->tabPage1->ResumeLayout(false);
		this->outputTab->ResumeLayout(false);
		this->tabPage4->ResumeLayout(false);
		this->tabPage4->PerformLayout();
		this->videoTab->ResumeLayout(false);
		this->tabPage3->ResumeLayout(false);
		this->audioTab->ResumeLayout(false);
		this->audioPage0->ResumeLayout(false);
		this->subtitlesTab->ResumeLayout(false);
		this->subPage0->ResumeLayout(false);
		this->subtitleMenu->ResumeLayout(false);
		this->audioMenu->ResumeLayout(false);
		this->tabControl1->ResumeLayout(false);
		this->encoderConfigTab->ResumeLayout(false);
		this->avsBox->ResumeLayout(false);
		this->avsBox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->horizontalResolution))->EndInit();
		this->locationGroupBox->ResumeLayout(false);
		this->locationGroupBox->PerformLayout();
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		this->videoGroupBox->ResumeLayout(false);
		this->videoGroupBox->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void OneClickWindow::InitializeInstanceFields()
	{
		ignoreRestrictions = false;
		outputChosen = false;
		iSelectedSubtitleTabPage = -1;
		iSelectedAudioTabPage = -1;
		delete components;
	}
}
