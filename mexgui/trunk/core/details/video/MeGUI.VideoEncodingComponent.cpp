#include "MeGUI.VideoEncodingComponent.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::details::video;
using namespace MeGUI::core::gui;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::video;

namespace MeGUI
{

	void VideoEncodingComponent::initVideoInfo()
	{
		info = new VideoInfo();
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		info->VideoInputChanged += new StringChanged(delegate(object _, std::string val)
		{
			videoInput->setFilename(val);
		}
	   );
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		info->VideoOutputChanged += new StringChanged(delegate(object _, std::string val)
		{
			videoOutput->setFilename(val);
		}
	   );
	}

	const VideoInfo &VideoEncodingComponent::getInfo() const
	{
		return info;
	}

	const std::string &VideoEncodingComponent::getFileType() const
	{
		return fileType->Text;
		;
	}

	void VideoEncodingComponent::setFileType(const std::string &value)
	{
		fileType->Text = value;
	}

	const VideoCodecSettings &VideoEncodingComponent::getCurrentSettings() const
	{
		return static_cast<VideoCodecSettings*>(videoProfile->getSelectedProfile()->BaseSettings);
	}

	VideoEncodingComponent::VideoEncodingComponent()
	{
		InitializeInstanceFields();
		initVideoInfo();
		InitializeComponent();
		if (mainForm != 0) // Fix to allow VS2008 designer to load Form1
			videoProfile->setManager(mainForm->getProfiles());
	}

	const std::string &VideoEncodingComponent::getVideoInput() const
	{
		return info->getVideoInput();
	}

	void VideoEncodingComponent::setVideoInput(const std::string &value)
	{
		info->setVideoInput(value);
	}

	const std::string &VideoEncodingComponent::getVideoOutput() const
	{
		return info->getVideoOutput();
	}

	void VideoEncodingComponent::setVideoOutput(const std::string &value)
	{
		info->setVideoOutput(value);
	}

	const VideoType &VideoEncodingComponent::getCurrentVideoOutputType() const
	{
		return dynamic_cast<VideoType*>(this->fileType->SelectedItem);
	}

	const bool &VideoEncodingComponent::getPrerenderJob() const
	{
		return addPrerenderJob->Checked;
	}

	void VideoEncodingComponent::setPrerenderJob(const bool &value)
	{
		addPrerenderJob->Checked = value;
	}

	void VideoEncodingComponent::videoInput_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		if (!videoInput->getFilename().empty() && !mainForm->openFile(videoInput->getFilename(), true))
		{
			videoInput->setFilename("");
			videoOutput->setFilename("");
		}
	}

	void VideoEncodingComponent::videoOutput_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		info->setVideoOutput(videoOutput->getFilename());
	}

	void VideoEncodingComponent::openAvisynthScript(const std::string &fileName)
	{
		if (this->player != 0) // make sure only one preview window is open at all times
			player->Close();
		player = new VideoPlayer();
		info->setDAR(Nullable<Dar>()); // to be sure to initialize DAR values
		bool videoLoaded = player->loadVideo(mainForm, fileName, CREDITS, true);
		if (videoLoaded)
		{
			Nullable<Dar> tempVar = info.getDAR();
			info->setDAR(tempVar::HasValue ? tempVar : player->getFile()->getVideoInfo()->DAR);
			player->setDAR(info->getDAR());
			FrameRate = player->getFramerate();
			player->IntroCreditsFrameSet += new IntroCreditsFrameSetCallback(this, &VideoEncodingComponent::player_IntroCreditsFrameSet);
			player->Closed += new EventHandler(this, &VideoEncodingComponent::player_Closed);
			player->Show();
			player->SetScreenSize();
			if (mainForm->getSettings()->getAlwaysOnTop())
				player->TopMost = true;
		}
	}

	void VideoEncodingComponent::VideoInput_DoubleClick(object *sender, System::EventArgs *e)
	{
		if (!getVideoInput().Equals(""))
		{
			this->openAvisynthScript(getVideoInput());
			if (info->getCreditsStartFrame() > -1)
				this->player->setCreditsStart(info->getCreditsStartFrame());
			if (info->getIntroEndFrame() > -1)
				this->player->setIntroEnd(info->getIntroEndFrame());
		}
		else
			MessageBox::Show("Load an avisynth script first...", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	void VideoEncodingComponent::queueVideoButton_Click(object *sender, System::EventArgs *e)
	{
		fileType_SelectedIndexChanged(sender, e); // to select always correct output file extension
		std::string settingsError = verifyVideoSettings(); // basic input, logfile and output file settings are okay
		if (settingsError != "")
		{
			MessageBox::Show(settingsError, "Unsupported configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return;
		}
		VideoCodecSettings *vSettings = this->getCurrentSettings()->Clone();

		std::string videoOutput = info->getVideoOutput();
		if (vSettings->getSettingsID().Equals("x264") && (MainForm::Instance->getSettings()->getUseExternalMuxerX264()) || (fileType->Text->Equals("MP4")))
		{
			if (!fileType->Text->Equals("RAWAVC"))
				videoOutput = Path::ChangeExtension(videoOutput, "264");
		}

		JobChain *prepareJobs = mainForm->getJobUtil()->AddVideoJobs(info->getVideoInput(), videoOutput, this->getCurrentSettings()->Clone(), info->getIntroEndFrame(), info->getCreditsStartFrame(), info->getDAR(), getPrerenderJob(), true, info->getZones());

		if ((MainForm::Instance->getSettings()->getUseExternalMuxerX264()) || (fileType->Text->Equals("MP4")))
		{
			if ((vSettings->getSettingsID().Equals("x264")) && (!fileType->Text->Equals("RAWAVC")))
			{
				// create job
				MuxJob *mJob = new MuxJob();
				mJob->Input = videoOutput;

				if (fileType->Text->Equals("MKV"))
				{
					mJob->setMuxType(MKVMERGE);
					mJob->Output = Path::ChangeExtension(videoOutput, "mkv");
				}
				else if (fileType->Text->Equals("MP4"))
				{
					mJob->setMuxType(MP4BOX);
					mJob->Output = Path::ChangeExtension(videoOutput, "mp4");
				}

				mJob->getSettings()->setMuxAll(true);
				mJob->getSettings()->setFramerate(decimal::Round(static_cast<decimal>(FrameRate),3,MidpointRounding::AwayFromZero));
				mJob->getSettings()->setMuxedInput(mJob->Input);
				mJob->getSettings()->setMuxedOutput(mJob->Output);
				mJob->FilesToDelete.push_back(videoOutput);

				// add job to queue
				prepareJobs = new SequentialChain(prepareJobs, new SequentialChain(mJob));
			}
		}
		mainForm->getJobs()->addJobsWithDependencies(prepareJobs, true);
	}

	void VideoEncodingComponent::fileType_SelectedIndexChanged(object *sender, EventArgs *e)
	{
		videoOutput->setFilter(getCurrentVideoOutputType()->getOutputFilterString());
		this->setVideoOutput(Path::ChangeExtension(this->getVideoOutput(), getCurrentVideoOutputType()->getExtension()));
		if (!bInitialStart)
			MainForm::Instance->getSettings()->setMainFileFormat(fileType->Text);
		else
			bInitialStart = false;
	}

	void VideoEncodingComponent::updateIOConfig()
	{
		int encodingMode = getCurrentSettings()->getEncodingMode();
		if (encodingMode == 2 || encodingMode == 5) // first pass
		{
			videoOutput->Enabled = false;
		}
		else if (!videoOutput->Enabled)
		{
			videoOutput->Enabled = true;
		}
	}

	std::string VideoEncodingComponent::verifyVideoSettings()
	{
		// test for valid input filename
		if (this->getVideoInput().empty())
			return "Please specify a video input file";

		std::string fileErr = MainForm::verifyInputFile(this->getVideoInput());
		if (fileErr != "")
		{
			return "Problem with video input filename:\n" + fileErr;
		}

		// test for valid output filename (not needed if just doing 1st pass)
		if (!isFirstPass())
		{
			fileErr = MainForm::verifyOutputFile(this->getVideoOutput());
			if (fileErr != "")
			{
				return "Problem with video output filename:\n" + fileErr;
			}

			VideoType *vot = getCurrentVideoOutputType();
			// test output file extension
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
			if (!Path::GetExtension(this->getVideoOutput())->Replace(".", "")->Equals(vot->getExtension(), StringComparison::InvariantCultureIgnoreCase))
			{
				return "Video output filename does not have the correct extension.\nBased on current settings, it should be " + vot->getExtension();
			}
		}
		return 0;
	}

	const MuxableType &VideoEncodingComponent::getCurrentMuxableVideoType() const
	{
		return new MuxableType(getCurrentVideoOutputType(), getCurrentSettings()->getCodec());
	}

	void VideoEncodingComponent::openVideoFile(const std::string &fileName)
	{
		if (AudioUtil::AVSFileHasAudio(fileName))
			mainForm->getAudio()->openAudioFile(fileName);

		info->setCreditsStartFrame(-1);
		info->setIntroEndFrame(-1);
		info->setVideoInput(fileName);
		info->setDAR(Nullable<Dar>());
		info->setZones(0);

		if (mainForm->getSettings()->getAutoOpenScript())
			openAvisynthScript(fileName);
		else
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AvsFile avi = AvsFile.OpenScriptFile(fileName))
			AvsFile *avi = AvsFile::OpenScriptFile(fileName);
			try
			{
				info->setDAR(avi->getVideoInfo()->DAR);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (avi != 0)
					avi.Dispose();
			}
		}
		std::string filePath;
		if ((filePath = mainForm->getSettings()->getDefaultOutputDir())->empty())
			filePath = Path::GetDirectoryName(fileName);
		std::string fileNameNoExtension = Path::GetFileNameWithoutExtension(fileName);
		this->setVideoOutput(Path::Combine(filePath, fileNameNoExtension) + mainForm->getSettings()->getVideoExtension() + ".extension");
		this->setVideoOutput(Path::ChangeExtension(this->getVideoOutput(), this->getCurrentVideoOutputType()->getExtension()));
		updateIOConfig();
	}

	bool VideoEncodingComponent::isFirstPass()
	{
		VideoCodecSettings *settings = getCurrentSettings();
		if (settings->getEncodingMode() == 2 || settings->getEncodingMode() == 5)
			return true;
		else
			return false;
	}

	void VideoEncodingComponent::ClosePlayer()
	{
		if (this->player != 0)
		{
			player->Close();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete player;
		}
	}

	void VideoEncodingComponent::hidePlayer()
	{
		if (player != 0)
			player->Hide();
	}

	void VideoEncodingComponent::showPlayer()
	{
		if (player != 0)
			player->Show();
	}

	void VideoEncodingComponent::player_Closed(object *sender, EventArgs *e)
	{
		info->setDAR(player->getDAR());
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete this->player;
	}

	void VideoEncodingComponent::player_IntroCreditsFrameSet(int frameNumber, bool isCredits)
	{
		if (isCredits)
		{
			if (validateCredits(frameNumber))
			{
				player->setCreditsStart(frameNumber);
				info->setCreditsStartFrame(frameNumber);
			}
			else
				player->setCreditsStart(-1);
		}
		else
		{
			if (validateIntro(frameNumber))
			{
				info->setIntroEndFrame(frameNumber);
				player->setIntroEnd(frameNumber);
			}
			else
				player->setIntroEnd(-1);
		}
	}

	bool VideoEncodingComponent::validateCredits(int creditsStartFrame)
	{
		for (MeGUI::Zone::const_iterator z = getInfo()->getZones()->begin(); z != getInfo()->getZones()->end(); ++z)
		{
			if (creditsStartFrame <= (*z)->endFrame) // credits start before end of this zone -> intersection
			{
				MessageBox::Show("The start of the end credits intersects with an already configured zone\ngoing from frame " + (*z)->startFrame + " to frame " + (*z)->endFrame + "\nPlease select another credits start frame or reconfigure the zone in the codec configuration.", "Zone intersection detected", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				return false;
			}
		}
		return true;
	}

	bool VideoEncodingComponent::validateIntro(int introEndFrame)
	{
		for (MeGUI::Zone::const_iterator z = getInfo()->getZones()->begin(); z != getInfo()->getZones()->end(); ++z)
		{
			if (introEndFrame >= (*z)->startFrame)
			{
				MessageBox::Show("The end of the intro intersects with an already configured zone\ngoing from frame " + (*z)->startFrame + " to frame " + (*z)->endFrame + "\nPlease select another credits start frame or reconfigure the zone in the codec configuration.", "Zone intersection detected", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				return false;
			}
		}
		return true;
	}

	const MeGUI::VideoEncoderProvider &VideoEncodingComponent::getVideoEncoderProvider() const
	{
		return videoEncoderProvider;
	}

	void VideoEncodingComponent::Reset()
	{
		this->setVideoInput("");
		this->setVideoOutput("");
		info->setCreditsStartFrame(0);
		info->setZones(0);
	}

	void VideoEncodingComponent::addAnalysisPass_Click(object *sender, EventArgs *e)
	{
		if (getVideoInput().empty())
		{
			MessageBox::Show("Error: Could not add job to queue. Make sure that all the details are entered correctly", "Couldn't create job", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		AviSynthJob *job = new AviSynthJob(getVideoInput());
		mainForm->getJobs()->addJobsToQueue(new AviSynthJob(getVideoInput()));
	}

	void VideoEncodingComponent::videoProfile_SelectedProfileChanged(object *sender, EventArgs *e)
	{
		if (getCurrentSettings()->getEncoderType() == lastCodec)
			return;

		lastCodec = getCurrentSettings()->getEncoderType();

//ORIGINAL LINE: VideoType[] vArray = videoEncoderProvider.GetSupportedOutput(lastCodec);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		VideoType *vArray = videoEncoderProvider->GetSupportedOutput(lastCodec);
		if (lastCodec == VideoEncoderType::X264)
		{
			Array::Resize(vArray, sizeof(vArray) / sizeof(vArray[0]) + 1);
			vArray[sizeof(vArray) / sizeof(vArray[0]) - 1] = VideoType::MP4;
		}

		Util::ChangeItemsKeepingSelectedSame(fileType, vArray);
	}

	void VideoEncodingComponent::editZonesButton_Click(object *sender, EventArgs *e)
	{
		if (videoInput->getFilename().empty())
		{
			MessageBox::Show("Load an avisynth script first...", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		ClosePlayer();
		ZonesWindow *zw = new ZonesWindow(mainForm, getVideoInput());
		zw->setZones(getInfo()->getZones());
		if (zw->ShowDialog() == DialogResult::OK)
			getInfo()->setZones(zw->getZones());
	}

	void VideoEncodingComponent::videopreview_Click(object *sender, EventArgs *e)
	{
		VideoInput_DoubleClick(0, 0);
	}

	void VideoEncodingComponent::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		UserControl::Dispose(disposing);
	}

	void VideoEncodingComponent::InitializeComponent()
	{
		this->videoOutputLabel = new System::Windows::Forms::Label();
		this->videoInputLabel = new System::Windows::Forms::Label();
		this->queueVideoButton = new System::Windows::Forms::Button();
		this->addAnalysisPass = new System::Windows::Forms::Button();
		this->groupBox1 = new System::Windows::Forms::GroupBox();
		this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
		this->label1 = new System::Windows::Forms::Label();
		this->editZonesButton = new System::Windows::Forms::Button();
		this->videoProfile = new MeGUI::core::gui::ConfigableProfilesControl();
		this->label2 = new System::Windows::Forms::Label();
		this->videoInput = new MeGUI::FileBar();
		this->videoOutput = new MeGUI::FileBar();
		this->fileType = new System::Windows::Forms::ComboBox();
		this->videopreview = new System::Windows::Forms::Button();
		this->addPrerenderJob = new System::Windows::Forms::CheckBox();
		this->groupBox1->SuspendLayout();
		this->tableLayoutPanel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// videoOutputLabel
		// 
		this->videoOutputLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->videoOutputLabel->AutoSize = true;
		this->videoOutputLabel->Location = new System::Drawing::Point(3, 37);
		this->videoOutputLabel->Name = "videoOutputLabel";
		this->videoOutputLabel->Size = new System::Drawing::Size(127, 13);
		this->videoOutputLabel->TabIndex = 2;
		this->videoOutputLabel->Text = "Video Output";
		// 
		// videoInputLabel
		// 
		this->videoInputLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->videoInputLabel->AutoSize = true;
		this->videoInputLabel->Location = new System::Drawing::Point(3, 8);
		this->videoInputLabel->Name = "videoInputLabel";
		this->videoInputLabel->Size = new System::Drawing::Size(127, 13);
		this->videoInputLabel->TabIndex = 0;
		this->videoInputLabel->Text = "AviSynth Script";
		// 
		// queueVideoButton
		// 
		this->queueVideoButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->queueVideoButton->AutoSize = true;
		this->queueVideoButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->queueVideoButton->Location = new System::Drawing::Point(428, 121);
		this->queueVideoButton->Name = "queueVideoButton";
		this->queueVideoButton->Size = new System::Drawing::Size(53, 23);
		this->queueVideoButton->TabIndex = 11;
		this->queueVideoButton->Text = "Queue";
		this->queueVideoButton->Click += new System::EventHandler(this, &VideoEncodingComponent::queueVideoButton_Click);
		// 
		// addAnalysisPass
		// 
		this->addAnalysisPass->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->addAnalysisPass->AutoSize = true;
		this->addAnalysisPass->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->addAnalysisPass->Location = new System::Drawing::Point(282, 121);
		this->addAnalysisPass->Name = "addAnalysisPass";
		this->addAnalysisPass->Size = new System::Drawing::Size(140, 23);
		this->addAnalysisPass->TabIndex = 9;
		this->addAnalysisPass->Text = "Queue Analysis Pass";
		this->addAnalysisPass->UseVisualStyleBackColor = true;
		this->addAnalysisPass->Click += new System::EventHandler(this, &VideoEncodingComponent::addAnalysisPass_Click);
		// 
		// groupBox1
		// 
		this->groupBox1->Controls->Add(this->tableLayoutPanel1);
		this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->groupBox1->Location = new System::Drawing::Point(0, 0);
		this->groupBox1->Name = "groupBox1";
		this->groupBox1->Size = new System::Drawing::Size(490, 168);
		this->groupBox1->TabIndex = 0;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = "Video encoding";
		// 
		// tableLayoutPanel1
		// 
		this->tableLayoutPanel1->ColumnCount = 4;
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50));
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50));
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->Controls->Add(this->videoInputLabel, 0, 0);
		this->tableLayoutPanel1->Controls->Add(this->queueVideoButton, 3, 4);
		this->tableLayoutPanel1->Controls->Add(this->label1, 0, 3);
		this->tableLayoutPanel1->Controls->Add(this->editZonesButton, 3, 3);
		this->tableLayoutPanel1->Controls->Add(this->videoOutputLabel, 0, 1);
		this->tableLayoutPanel1->Controls->Add(this->videoProfile, 1, 2);
		this->tableLayoutPanel1->Controls->Add(this->label2, 0, 2);
		this->tableLayoutPanel1->Controls->Add(this->videoInput, 1, 0);
		this->tableLayoutPanel1->Controls->Add(this->videoOutput, 1, 1);
		this->tableLayoutPanel1->Controls->Add(this->fileType, 1, 3);
		this->tableLayoutPanel1->Controls->Add(this->videopreview, 1, 4);
		this->tableLayoutPanel1->Controls->Add(this->addAnalysisPass, 2, 4);
		this->tableLayoutPanel1->Controls->Add(this->addPrerenderJob, 0, 4);
		this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tableLayoutPanel1->Location = new System::Drawing::Point(3, 16);
		this->tableLayoutPanel1->Name = "tableLayoutPanel1";
		this->tableLayoutPanel1->RowCount = 5;
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
		this->tableLayoutPanel1->Size = new System::Drawing::Size(484, 149);
		this->tableLayoutPanel1->TabIndex = 14;
		// 
		// label1
		// 
		this->label1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->label1->AutoSize = true;
		this->label1->Location = new System::Drawing::Point(3, 95);
		this->label1->Name = "label1";
		this->label1->Size = new System::Drawing::Size(127, 13);
		this->label1->TabIndex = 6;
		this->label1->Text = "File format";
		// 
		// editZonesButton
		// 
		this->editZonesButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->editZonesButton->AutoSize = true;
		this->editZonesButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->editZonesButton->Location = new System::Drawing::Point(431, 90);
		this->editZonesButton->Margin = new System::Windows::Forms::Padding(6, 3, 6, 3);
		this->editZonesButton->Name = "editZonesButton";
		this->editZonesButton->Size = new System::Drawing::Size(47, 23);
		this->editZonesButton->TabIndex = 13;
		this->editZonesButton->Text = "Zones";
		this->editZonesButton->UseVisualStyleBackColor = true;
		this->editZonesButton->Click += new System::EventHandler(this, &VideoEncodingComponent::editZonesButton_Click);
		// 
		// videoProfile
		// 
		this->tableLayoutPanel1->SetColumnSpan(this->videoProfile, 3);
		this->videoProfile->Dock = System::Windows::Forms::DockStyle::Fill;
		this->videoProfile->Location = new System::Drawing::Point(136, 61);
		this->videoProfile->Name = "videoProfile";
		this->videoProfile->setProfileSet("Video");
		this->videoProfile->Size = new System::Drawing::Size(345, 23);
		this->videoProfile->TabIndex = 12;
		this->videoProfile->SelectedProfileChanged += new System::EventHandler(this, &VideoEncodingComponent::videoProfile_SelectedProfileChanged);
		// 
		// label2
		// 
		this->label2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->label2->AutoSize = true;
		this->label2->Location = new System::Drawing::Point(3, 66);
		this->label2->Name = "label2";
		this->label2->Size = new System::Drawing::Size(127, 13);
		this->label2->TabIndex = 2;
		this->label2->Text = "Encoder settings";
		// 
		// videoInput
		// 
		this->videoInput->AllowDrop = true;
		this->tableLayoutPanel1->SetColumnSpan(this->videoInput, 3);
		this->videoInput->Dock = System::Windows::Forms::DockStyle::Fill;
		this->videoInput->setFilename("");
		this->videoInput->setFilter("AviSynth files (*.avs)|*.avs|All files (*.*)|*.*");
		this->videoInput->setFilterIndex(0);
		this->videoInput->setFolderMode(false);
		this->videoInput->Location = new System::Drawing::Point(136, 3);
		this->videoInput->Name = "videoInput";
		this->videoInput->setReadOnly(true);
		this->videoInput->setSaveMode(false);
		this->videoInput->Size = new System::Drawing::Size(345, 23);
		this->videoInput->TabIndex = 1;
		this->videoInput->setTitle("Open AviSynth script");
		this->videoInput->FileSelected += new MeGUI::FileBarEventHandler(this, &VideoEncodingComponent::videoInput_FileSelected);
		// 
		// videoOutput
		// 
		this->tableLayoutPanel1->SetColumnSpan(this->videoOutput, 3);
		this->videoOutput->Dock = System::Windows::Forms::DockStyle::Fill;
		this->videoOutput->setFilename("");
		this->videoOutput->setFilter("");
		this->videoOutput->setFilterIndex(0);
		this->videoOutput->setFolderMode(false);
		this->videoOutput->Location = new System::Drawing::Point(136, 32);
		this->videoOutput->Name = "videoOutput";
		this->videoOutput->setReadOnly(false);
		this->videoOutput->setSaveMode(true);
		this->videoOutput->Size = new System::Drawing::Size(345, 23);
		this->videoOutput->TabIndex = 3;
		this->videoOutput->setTitle("Enter name of output");
		this->videoOutput->FileSelected += new MeGUI::FileBarEventHandler(this, &VideoEncodingComponent::videoOutput_FileSelected);
		// 
		// fileType
		// 
		this->fileType->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->fileType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->fileType->Location = new System::Drawing::Point(136, 91);
		this->fileType->Name = "fileType";
		this->fileType->Size = new System::Drawing::Size(140, 21);
		this->fileType->Sorted = true;
		this->fileType->TabIndex = 14;
		this->fileType->SelectedIndexChanged += new System::EventHandler(this, &VideoEncodingComponent::fileType_SelectedIndexChanged);
		// 
		// videopreview
		// 
		this->videopreview->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->videopreview->AutoSize = true;
		this->videopreview->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->videopreview->Location = new System::Drawing::Point(136, 121);
		this->videopreview->Name = "videopreview";
		this->videopreview->Size = new System::Drawing::Size(140, 23);
		this->videopreview->TabIndex = 16;
		this->videopreview->Text = "Reopen Video Preview";
		this->videopreview->UseVisualStyleBackColor = true;
		this->videopreview->Click += new System::EventHandler(this, &VideoEncodingComponent::videopreview_Click);
		// 
		// addPrerenderJob
		// 
		this->addPrerenderJob->Anchor = System::Windows::Forms::AnchorStyles::Right;
		this->addPrerenderJob->AutoSize = true;
		this->addPrerenderJob->Location = new System::Drawing::Point(3, 124);
		this->addPrerenderJob->Name = "addPrerenderJob";
		this->addPrerenderJob->Size = new System::Drawing::Size(127, 17);
		this->addPrerenderJob->TabIndex = 17;
		this->addPrerenderJob->Text = "Add pre-rendering job";
		this->addPrerenderJob->UseVisualStyleBackColor = true;
		// 
		// VideoEncodingComponent
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->Controls->Add(this->groupBox1);
		this->Name = "VideoEncodingComponent";
		this->Size = new System::Drawing::Size(490, 168);
		this->groupBox1->ResumeLayout(false);
		this->tableLayoutPanel1->ResumeLayout(false);
		this->tableLayoutPanel1->PerformLayout();
		this->ResumeLayout(false);

	}

	void VideoEncodingComponent::InitializeInstanceFields()
	{
		mainForm = MainForm::Instance;
		videoEncoderProvider = new VideoEncoderProvider();
		bInitialStart = true;
		delete lastCodec;
		delete components;
	}
}
