#include "MeGUI.AdaptiveMuxWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::details::mux;
using namespace MeGUI::core::util;

namespace MeGUI
{

	AdaptiveMuxWindow::AdaptiveMuxWindow(MainForm *mainForm) : baseMuxWindow(mainForm, 0)
	{
		InitializeInstanceFields();
		InitializeComponent();
		jobUtil = new JobUtil(mainForm);
		muxProvider = mainForm->getMuxProvider();

		audioTracks[0]->setFilter(VideoUtil::GenerateCombinedFilter(ContainerManager::AudioTypes->getValuesArray()));
		subtitleTracks[0]->setFilter(VideoUtil::GenerateCombinedFilter(ContainerManager::SubtitleTypes->getValuesArray()));
		vInput->setFilter(VideoUtil::GenerateCombinedFilter(ContainerManager::VideoTypes->getValuesArray()));
		chapters->setFilter(VideoUtil::GenerateCombinedFilter(ContainerManager::ChapterTypes->getValuesArray()));
		cbContainer->Visible = true;
		lbContainer->Visible = true;

		subtitleTracks[0]->chkDefaultStream->CheckedChanged += new System::EventHandler(this, &baseMuxWindow::chkDefaultStream_CheckedChanged);
		this->cbContainer->SelectedIndexChanged += new System::EventHandler(this, &AdaptiveMuxWindow::cbContainer_SelectedIndexChanged);
		baseMuxWindow::muxButton::Click += new System::EventHandler(this, &AdaptiveMuxWindow::muxButton_Click);
	}

	void AdaptiveMuxWindow::fileUpdated()
	{
		updatePossibleContainers();
	}

	void AdaptiveMuxWindow::upDeviceTypes()
	{
		updateDeviceTypes();
	}

	void AdaptiveMuxWindow::cbContainer_SelectedIndexChanged(object *sender, EventArgs *e)
	{
		output->setFilename(Path::ChangeExtension(output->getFilename(), (dynamic_cast<ContainerType*>(this->cbContainer->SelectedItem))->getExtension()));

		if (dynamic_cast<ContainerType*>(cbContainer->SelectedItem) != 0)
			output->setFilter((dynamic_cast<ContainerType*>(cbContainer->SelectedItem))->getOutputFilterString());
		else
			output->setFilter("");

		for (std::vector<MuxStreamControl*>::const_iterator oStream = subtitleTracks.begin(); oStream != subtitleTracks.end(); ++oStream)
		{
			if ((dynamic_cast<ContainerType*>(this->cbContainer->SelectedItem))->getExtension().Equals("mkv"))
				(*oStream)->setShowDelay(true);
			(**oStream)->setShowForceSubtitleStream((**oStream)->getShowDelay());
		(***oStream)->setShowDefaultSubtitleStream((***oStream)->getShowForceSubtitleStream());
			else
				(*oStream)->setShowDelay(false);
			(**oStream)->setShowForceSubtitleStream((**oStream)->getShowDelay());
		(***oStream)->setShowDefaultSubtitleStream((***oStream)->getShowForceSubtitleStream());
		}

		if ((dynamic_cast<ContainerType*>(this->cbContainer->SelectedItem))->getExtension().Equals("mkv"))
			subtitleTracks[0]->chkDefaultStream->Checked = true;
	}

	void AdaptiveMuxWindow::getTypes(AudioEncoderType aCodec[], MuxableType audioTypes[], MuxableType subtitleTypes[])
	{
		std::vector<MuxableType*> audioTypesList = std::vector<MuxableType*>();
		std::vector<MuxableType*> subTypesList = std::vector<MuxableType*>();
		std::vector<AudioEncoderType*> audioCodecList = std::vector<AudioEncoderType*>();

		int counter = 0;
		for (std::vector<MuxStreamControl*>::const_iterator c = audioTracks.begin(); c != audioTracks.end(); ++c)
		{
			if (minimizedMode && sizeof(knownAudioTypes) / sizeof(knownAudioTypes[0]) > counter)
			{
				audioCodecList.push_back(knownAudioTypes[counter]);
			}
			else if ((*c)->getStream() != 0)
			{
				MuxableType *audioType = VideoUtil::guessAudioMuxableType((*c)->getStream()->path, true);
				if (audioType != 0)
				{
					audioTypesList.push_back(audioType);
				}
			}
			counter++;
		}
		for (std::vector<MuxStreamControl*>::const_iterator c = subtitleTracks.begin(); c != subtitleTracks.end(); ++c)
		{
			if ((*c)->getStream() == 0)
				continue;
			SubtitleType *subtitleType = VideoUtil::guessSubtitleType((*c)->getStream()->path);
			if (subtitleType != 0)
			{
				subTypesList.push_back(new MuxableType(subtitleType, 0));
			}
		}
		audioTypes = audioTypesList.ToArray();
		subtitleTypes = subTypesList.ToArray();
		aCodec = audioCodecList.ToArray();
	}

	void AdaptiveMuxWindow::checkIO()
	{
		baseMuxWindow::checkIO();
		if (!(dynamic_cast<ContainerType*>(cbContainer->SelectedItem) != 0))
			muxButton->DialogResult = DialogResult::None;
	}

	void AdaptiveMuxWindow::updateDeviceTypes()
	{
		if (this->cbContainer->Text == "MKV")
			this->cbType->Enabled = false;
		else
			this->cbType->Enabled = true;

		std::vector<DeviceType*> supportedOutputDeviceTypes = this->muxProvider->GetSupportedDevices(static_cast<ContainerType*>(cbContainer->SelectedItem));
		this->cbType->Items->Clear();
		this->cbType->Items->Add("Standard");
		this->cbType->Items->AddRange(supportedOutputDeviceTypes.ToArray());

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (cbContainer->SelectedItem->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getContainer()))
		{
			for (unknown::const_iterator o = cbType->Items.begin(); o != cbType->Items.end(); ++o) // I know this is ugly, but using the DeviceOutputType doesn't work unless we're switching to manual serialization
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				if ((*o)->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getDeviceOutputType()))
				{
					cbType->SelectedItem = *o;
					break;
				}
			}
		}
		else
			this->cbType->SelectedIndex = 0;
	}

	void AdaptiveMuxWindow::updatePossibleContainers()
	{
		MuxableType *videoType;
		if (minimizedMode)
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete videoType;
		else
		{
			videoType = VideoUtil::guessVideoMuxableType(vInput->getFilename(), true);
			if (videoType != 0 && (videoType->codec == 0 || videoType->outputType == 0))
			{
				MessageBox::Show("Unable to determine type of input video. Mux-path finding cannot continue. Your video could well be corrupt.", "Determining type failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}

		if (!minimizedMode && videoType == 0)
		{
			this->cbContainer->Items->Clear();
			this->cbContainer->Items->AddRange(muxProvider->GetSupportedContainers().ToArray());
			this->cbContainer->SelectedIndex = 0;
			return;
		}

//ORIGINAL LINE: MuxableType[] audioTypes;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		MuxableType *audioTypes;
//ORIGINAL LINE: MuxableType[] subTypes;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		MuxableType *subTypes;
//ORIGINAL LINE: AudioEncoderType[] audioCodecs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		AudioEncoderType *audioCodecs;
		getTypes(audioCodecs, audioTypes, subTypes);

		std::vector<MuxableType*> allTypes = std::vector<MuxableType*>();
		if (videoType != 0)
			allTypes.push_back(videoType);
		allTypes.AddRange(audioTypes);
		allTypes.AddRange(subTypes);

		std::vector<ContainerType*> supportedOutputTypes;
		if (minimizedMode)
			supportedOutputTypes = this->muxProvider->GetSupportedContainers(knownVideoType, audioCodecs, allTypes.ToArray());
		else
			supportedOutputTypes = this->muxProvider->GetSupportedContainers(allTypes.ToArray());

		ContainerType *lastSelectedFileType = 0;
		if (dynamic_cast<ContainerType*>(cbContainer->SelectedItem) != 0)
			lastSelectedFileType = dynamic_cast<ContainerType*>(cbContainer->SelectedItem);

		if (supportedOutputTypes.size() > 0)
		{
			this->cbContainer->Items->Clear();
			this->cbContainer->Items->AddRange(supportedOutputTypes.ToArray());
			this->cbContainer->SelectedIndex = 0;
			if (lastSelectedFileType != 0 && cbContainer->Items->Contains(lastSelectedFileType))
				cbContainer->SelectedItem = lastSelectedFileType;
		}
		else
		{
			this->cbContainer->Items->Clear();
			MessageBox::Show("No muxer can be found that supports this input configuration", "Muxing impossible", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	const MeGUI::core::details::JobChain &AdaptiveMuxWindow::getJobs() const
	{
		if (minimizedMode)
			throw std::exception("Jobs property not accessible in minimized mode");

		VideoStream *myVideo = new VideoStream();
		myVideo->setInput("");
		myVideo->setOutput(vInput->getFilename());
		myVideo->setNumberOfFrames(1000); // Just a guess, since we have no way of actually knowing
		myVideo->setVideoType(VideoUtil::guessVideoMuxableType(vInput->getFilename(), true));
		myVideo->setSettings(new x264Settings());
		myVideo->getSettings()->setNbBframes(0);
		myVideo->getSettings()->setVideoName(this->videoName->Text);

//ORIGINAL LINE: MuxableType[] audioTypes;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		MuxableType *audioTypes;
//ORIGINAL LINE: MuxableType[] subtitleTypes;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		MuxableType *subtitleTypes;
//ORIGINAL LINE: AudioEncoderType[] audioCodecs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		AudioEncoderType *audioCodecs;
//ORIGINAL LINE: MuxStream[] audioStreams, subtitleStreams;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		MuxStream *audioStreams, *subtitleStreams;
		getTypes(audioCodecs, audioTypes, subtitleTypes);
		std::string chapters;
		getAdditionalStreams(audioStreams, subtitleStreams, chapters);

		Nullable<FileSize> splitSize = splitting->getValue();

		MuxableType *chapterInputType = 0;
		if (!this->chapters->getFilename().empty())
		{
			ChapterType *type = VideoUtil::guessChapterType(this->chapters->getFilename());
			if (type != 0)
				chapterInputType = new MuxableType(type, 0);
		}

		MuxableType *deviceOutputType = 0;
		if (!this->cbType->Text->empty())
		{
			DeviceType *type = VideoUtil::guessDeviceType(this->cbType->Text);
			if (type != 0)
				deviceOutputType = new MuxableType(type, 0);
		}

		return jobUtil->GenerateMuxJobs(myVideo, fps->getValue(), audioStreams, audioTypes, subtitleStreams, subtitleTypes, this->chapters->getFilename(), chapterInputType, (dynamic_cast<ContainerType*>(cbContainer->SelectedItem)), output->getFilename(), splitSize, std::vector<std::string>(), this->cbType->Text, deviceOutputType, false);
	}

	void AdaptiveMuxWindow::setMinimizedMode(const std::string &videoInput, const std::string &videoName, VideoEncoderType *videoType, double framerate, MuxStream audioStreams[], AudioEncoderType audioTypes[], const std::string &output, Nullable<FileSize> splitSize, ContainerType *cft)
	{
		baseMuxWindow::setConfig(videoInput, videoName, static_cast<decimal>(framerate), audioStreams, new MuxStream[0], 0, output, splitSize, 0, 0);

		minimizedMode = true;
		knownVideoType = videoType;
		knownAudioTypes = audioTypes;

		// disable controls where required
		videoGroupbox->Enabled = false;

		for (int i = 0; i < sizeof(audioStreams) / sizeof(audioStreams[0]); ++i)
			audioTracks[i]->SetAutoEncodeMode();

		this->output->setFilename(output);
		this->splitting->setValue(splitSize);
		this->muxButton->Text = "Go";
		updatePossibleContainers();
		if (this->cbContainer->Items->Contains(cft))
			cbContainer->SelectedItem = cft;
		checkIO();
	}

	void AdaptiveMuxWindow::getAdditionalStreams(MuxStream audio[], MuxStream subtitles[], std::string &chapters, std::string &output, ContainerType *&cot)
	{
		cot = (dynamic_cast<ContainerType*>(cbContainer->SelectedItem));
		output = this->output->getFilename();
		baseMuxWindow::getAdditionalStreams(audio, subtitles, chapters);
	}

	void AdaptiveMuxWindow::muxButton_Click(object *sender, System::EventArgs *e)
	{
		if (minimizedMode)
			return;

		if (muxButton->DialogResult != DialogResult::OK)
		{
			if (vInput->getFilename().empty())
			{
				MessageBox::Show("You must configure a video input file", "Missing input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				return;
			}
			else if (output->getFilename().empty())
			{
				MessageBox::Show("You must configure an output file", "Missing input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				return;
			}
			else if (MainForm::verifyOutputFile(output->getFilename()) != "")
			{
				MessageBox::Show("Invalid output file", "Invalid output", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			else if (!fps->getValue().HasValue)
			{
				MessageBox::Show("You must select a framerate", "Missing input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				return;
			}
		}
		else
		{
			if (this->muxButton->Text->Equals("Update"))
			{
				this->Close();
			}
			else
			{
				JobChain *oJobs = this->getJobs();
				if (oJobs->Jobs->Length == 0)
				{
					MessageBox::Show("No mux job created as input and output are the same", "Nothing to mux", MessageBoxButtons::OK, MessageBoxIcon::Stop);
					return;
				}
				mainForm->getJobs()->addJobsWithDependencies(oJobs, true);
				if (chkCloseOnQueue->Checked)
					this->Close();
				else
					output->setFilename("");
			}
		}
	}

	void AdaptiveMuxWindow::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		baseMuxWindow::Dispose(disposing);
	}

	void AdaptiveMuxWindow::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(AdaptiveMuxWindow::typeid);
		this->containerFormat = new System::Windows::Forms::ComboBox();
		this->label1 = new System::Windows::Forms::Label();
		this->SuspendLayout();
		// 
		// containerFormat
		// 
		this->containerFormat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->containerFormat->FormattingEnabled = true;
		this->containerFormat->Location = new System::Drawing::Point(118, 45);
		this->containerFormat->Name = "containerFormat";
		this->containerFormat->Size = new System::Drawing::Size(141, 21);
		this->containerFormat->TabIndex = 1;
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = new System::Drawing::Point(10, 49);
		this->label1->Name = "label1";
		this->label1->Size = new System::Drawing::Size(91, 13);
		this->label1->TabIndex = 0;
		this->label1->Text = "Container Format";
		// 
		// AdaptiveMuxWindow
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = new System::Drawing::Size(444, 597);
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->Name = "AdaptiveMuxWindow";
		this->Text = "MeGUI - Adaptive Muxer";
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void AdaptiveMuxWindow::InitializeInstanceFields()
	{
		minimizedMode = false;
		delete components;
	}
}
