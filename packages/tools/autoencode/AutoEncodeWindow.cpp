#include "AutoEncodeWindow.h"






//using namespace System::Collections::Generic;







//using namespace System::Text;


using namespace MeXgui::core::details;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::calculator;

namespace MeXgui
{

	AutoEncodeWindow::AutoEncodeWindow()
	{
		InitializeInstanceFields();
		InitializeComponent();
	}

	AutoEncodeWindow::AutoEncodeWindow(VideoStream *videoStream, QVector<AudioJob*> &audioStreams, MainForm *mainForm, bool prerender, VideoInfo *vInfo)
	{
		InitializeInstanceFields();
		this->vInfo = vInfo;
		mainForm->getLog()->Add(log);
		this->videoStream = videoStream;
		this->audioStreams = audioStreams;
		this->prerender = prerender;
		this->mainForm = mainForm;
		jobUtil = new JobUtil(mainForm);
		vUtil = new VideoUtil(mainForm);
		muxProvider = mainForm->getMuxProvider();
		container->Items->AddRange(muxProvider->GetSupportedContainers().ToArray());
		splitting->setMinimumFileSize(FileSize(MB, 1));
	}

	bool AutoEncodeWindow::init()
	{
		QVector<AudioEncoderType*> aTypes = QVector<AudioEncoderType*>();
//ORIGINAL LINE: AudioEncoderType[] audioTypes;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		AudioEncoderType *audioTypes;
		for (QVector<AudioJob*>::const_iterator stream = this->audioStreams.begin(); stream != this->audioStreams.end(); ++stream)
		{
			if ((*stream)->Settings != 0 && !(*stream)->Input->empty() && !(*stream)->Output->empty())
				aTypes.push_back((*stream)->Settings->EncoderType);
		}
		audioTypes = aTypes.ToArray();
		QVector<ContainerType*> supportedOutputTypes = this->muxProvider->GetSupportedContainers(this->videoStream->getSettings()->getEncoderType(), audioTypes);

		if (supportedOutputTypes.size() <= 0)
			return false;

		this->container->Items->Clear();
		this->container->Items->AddRange(supportedOutputTypes.ToArray());
		this->container->SelectedIndex = 0;

		QVector<DeviceType*> supportedOutputDeviceTypes = this->muxProvider->GetSupportedDevices(static_cast<ContainerType*>(container->SelectedItem));
		this->device->Items->AddRange(supportedOutputDeviceTypes.ToArray());
		this->device->SelectedIndex = 0;

		if (this->container->Text == "MKV")
			this->device->Enabled = false;
		else
			this->device->Enabled = true;

		QString muxedName = FileUtil::AddToFileName(vInfo->getVideoOutput(), "-muxed");

		this->muxedOutput->setFilename(Path::ChangeExtension(muxedName, (dynamic_cast<ContainerType*>(this->container->SelectedItem))->getExtension()));

		splitting->setValue(mainForm->getSettings()->getAedSettings()->getSplitSize());
		if (mainForm->getSettings()->getAedSettings()->getFileSizeMode())
		{
			FileSizeRadio->Checked = true;
			targetSize->setValue(mainForm->getSettings()->getAedSettings()->getFileSize());
		}
		else if (mainForm->getSettings()->getAedSettings()->getBitrateMode())
		{
			averageBitrateRadio->Checked = true;
			projectedBitrateKBits->Text = StringConverterHelper::toString(mainForm->getSettings()->getAedSettings()->getBitrate());
		}
		else
			noTargetRadio->Checked = true;
		if (mainForm->getSettings()->getAedSettings()->getAddAdditionalContent())
			addSubsNChapters->Checked = true;
		for (unknown::const_iterator o = container->Items.begin(); o != container->Items.end(); ++o) // I know this is ugly, but using the ContainerType doesn't work unless we're switching to manual serialization
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if ((*o)->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getContainer()))
			{
				container->SelectedItem = *o;
				break;
			}
		}
		for (unknown::const_iterator o = device->Items.begin(); o != device->Items.end(); ++o) // I know this is ugly, but using the DeviceOutputType doesn't work unless we're switching to manual serialization
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if ((*o)->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getDeviceOutputType()))
			{
				device->SelectedItem = *o;
				break;
			}
		}
		return true;
	}

	void AutoEncodeWindow::Dispose(bool disposing)
	{
		if (disposing)
		{
			if (components != 0)
			{
				delete components;
			}
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void AutoEncodeWindow::InitializeComponent()
	{
		this->components = new System::ComponentModel::Container();
		System::Windows::Forms::Label *label1;
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(AutoEncodeWindow::typeid);
		this->AutomaticEncodingGroup = new System::Windows::Forms::GroupBox();
		this->videoSize = new System::Windows::Forms::TextBox();
		this->label2 = new System::Windows::Forms::Label();
		this->projectedBitrateKBits = new System::Windows::Forms::TextBox();
		this->targetSize = new MeXgui::core::gui::TargetSizeSCBox();
		this->noTargetRadio = new System::Windows::Forms::RadioButton();
		this->averageBitrateRadio = new System::Windows::Forms::RadioButton();
		this->FileSizeRadio = new System::Windows::Forms::RadioButton();
		this->AverageBitrateLabel = new System::Windows::Forms::Label();
		this->queueButton = new QPushButton;
		this->OutputGroupBox = new System::Windows::Forms::GroupBox();
		this->device = new System::Windows::Forms::ComboBox();
		this->DeviceLabel = new System::Windows::Forms::Label();
		this->splitting = new MeXgui::core::gui::TargetSizeSCBox();
		this->container = new System::Windows::Forms::ComboBox();
		this->containerLabel = new System::Windows::Forms::Label();
		this->muxedOutputLabel = new System::Windows::Forms::Label();
		this->muxedOutput = new MeXgui::FileBar();
		this->cancelButton = new QPushButton;
		this->addSubsNChapters = new System::Windows::Forms::CheckBox();
		this->defaultToolTip = new System::Windows::Forms::ToolTip(this->components);
		this->helpButton1 = new MeXgui::core::gui::HelpButton();
		label1 = new System::Windows::Forms::Label();
		this->AutomaticEncodingGroup->SuspendLayout();
		this->OutputGroupBox->SuspendLayout();
		this->SuspendLayout();
		// 
		// label1
		// 
		label1->AutoSize = true;
		label1->Location = new System::Drawing::Point(191, 23);
		label1->Name = "label1";
		label1->Size = new System::Drawing::Size(49, 13);
		label1->TabIndex = 27;
		label1->Text = "Splitting:";
		// 
		// AutomaticEncodingGroup
		// 
		this->AutomaticEncodingGroup->Controls->Add(this->videoSize);
		this->AutomaticEncodingGroup->Controls->Add(this->label2);
		this->AutomaticEncodingGroup->Controls->Add(this->projectedBitrateKBits);
		this->AutomaticEncodingGroup->Controls->Add(this->targetSize);
		this->AutomaticEncodingGroup->Controls->Add(this->noTargetRadio);
		this->AutomaticEncodingGroup->Controls->Add(this->averageBitrateRadio);
		this->AutomaticEncodingGroup->Controls->Add(this->FileSizeRadio);
		this->AutomaticEncodingGroup->Controls->Add(this->AverageBitrateLabel);
		this->AutomaticEncodingGroup->Location = new System::Drawing::Point(10, 116);
		this->AutomaticEncodingGroup->Name = "AutomaticEncodingGroup";
		this->AutomaticEncodingGroup->Size = new System::Drawing::Size(456, 106);
		this->AutomaticEncodingGroup->TabIndex = 17;
		this->AutomaticEncodingGroup->TabStop = false;
		this->AutomaticEncodingGroup->Text = "Size and Bitrate";
		// 
		// videoSize
		// 
		this->videoSize->Location = new System::Drawing::Point(310, 48);
		this->videoSize->Name = "videoSize";
		this->videoSize->ReadOnly = true;
		this->videoSize->Size = new System::Drawing::Size(137, 21);
		this->videoSize->TabIndex = 28;
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = new System::Drawing::Point(246, 51);
		this->label2->Name = "label2";
		this->label2->Size = new System::Drawing::Size(58, 13);
		this->label2->TabIndex = 27;
		this->label2->Text = "Video size:";
		// 
		// projectedBitrateKBits
		// 
		this->projectedBitrateKBits->Enabled = false;
		this->projectedBitrateKBits->Location = new System::Drawing::Point(119, 45);
		this->projectedBitrateKBits->Name = "projectedBitrateKBits";
		this->projectedBitrateKBits->Size = new System::Drawing::Size(85, 21);
		this->projectedBitrateKBits->TabIndex = 9;
		this->projectedBitrateKBits->TextChanged += new System::EventHandler(this, &AutoEncodeWindow::projectedBitrate_TextChanged);
		this->projectedBitrateKBits->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, &AutoEncodeWindow::textField_KeyPress);
		// 
		// targetSize
		// 
		this->targetSize->setCustomSizes(new MeXgui::core::util::FileSize[0]);
		this->targetSize->Location = new System::Drawing::Point(116, 15);
		this->targetSize->MaximumSize = new System::Drawing::Size(1000, 29);
		this->targetSize->MinimumSize = new System::Drawing::Size(64, 29);
		this->targetSize->Name = "targetSize";
		this->targetSize->setNullString("Not calculated");
		this->targetSize->setSelectedIndex(0);
		this->targetSize->Size = new System::Drawing::Size(208, 29);
		this->targetSize->TabIndex = 25;
		this->targetSize->SelectionChanged += new MeXgui::StringChanged(this, &AutoEncodeWindow::targetSize_SelectionChanged);
		// 
		// noTargetRadio
		// 
		this->noTargetRadio->Location = new System::Drawing::Point(16, 75);
		this->noTargetRadio->Name = "noTargetRadio";
		this->noTargetRadio->Size = new System::Drawing::Size(218, 18);
		this->noTargetRadio->TabIndex = 22;
		this->noTargetRadio->TabStop = true;
		this->noTargetRadio->Text = "No Target Size (use profile settings)";
		this->defaultToolTip->SetToolTip(this->noTargetRadio, "Checking this allows the use of a previously defined bitrate or a non bitrate mod" + "e (CQ, CRF)");
		this->noTargetRadio->UseVisualStyleBackColor = true;
		this->noTargetRadio->CheckedChanged += new System::EventHandler(this, &AutoEncodeWindow::calculationMode_CheckedChanged);
		// 
		// averageBitrateRadio
		// 
		this->averageBitrateRadio->AutoSize = true;
		this->averageBitrateRadio->Location = new System::Drawing::Point(16, 49);
		this->averageBitrateRadio->Name = "averageBitrateRadio";
		this->averageBitrateRadio->Size = new System::Drawing::Size(101, 17);
		this->averageBitrateRadio->TabIndex = 16;
		this->averageBitrateRadio->Text = "Average Bitrate";
		this->averageBitrateRadio->CheckedChanged += new System::EventHandler(this, &AutoEncodeWindow::calculationMode_CheckedChanged);
		// 
		// FileSizeRadio
		// 
		this->FileSizeRadio->Checked = true;
		this->FileSizeRadio->Location = new System::Drawing::Point(16, 20);
		this->FileSizeRadio->Name = "FileSizeRadio";
		this->FileSizeRadio->Size = new System::Drawing::Size(100, 18);
		this->FileSizeRadio->TabIndex = 15;
		this->FileSizeRadio->TabStop = true;
		this->FileSizeRadio->Text = "File Size";
		this->FileSizeRadio->CheckedChanged += new System::EventHandler(this, &AutoEncodeWindow::calculationMode_CheckedChanged);
		// 
		// AverageBitrateLabel
		// 
		this->AverageBitrateLabel->AutoSize = true;
		this->AverageBitrateLabel->Location = new System::Drawing::Point(207, 51);
		this->AverageBitrateLabel->Name = "AverageBitrateLabel";
		this->AverageBitrateLabel->Size = new System::Drawing::Size(33, 13);
		this->AverageBitrateLabel->TabIndex = 10;
		this->AverageBitrateLabel->Text = "kbit/s";
		// 
		// queueButton
		// 
		this->queueButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
		this->queueButton->AutoSize = true;
		this->queueButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->queueButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->queueButton->Location = new System::Drawing::Point(358, 228);
		this->queueButton->Name = "queueButton";
		this->queueButton->Size = new System::Drawing::Size(49, 23);
		this->queueButton->TabIndex = 8;
		this->queueButton->Text = "Queue";
		this->queueButton->Click += new System::EventHandler(this, &AutoEncodeWindow::queueButton_Click);
		// 
		// OutputGroupBox
		// 
		this->OutputGroupBox->Controls->Add(this->device);
		this->OutputGroupBox->Controls->Add(this->DeviceLabel);
		this->OutputGroupBox->Controls->Add(label1);
		this->OutputGroupBox->Controls->Add(this->splitting);
		this->OutputGroupBox->Controls->Add(this->container);
		this->OutputGroupBox->Controls->Add(this->containerLabel);
		this->OutputGroupBox->Controls->Add(this->muxedOutputLabel);
		this->OutputGroupBox->Controls->Add(this->muxedOutput);
		this->OutputGroupBox->Location = new System::Drawing::Point(10, 4);
		this->OutputGroupBox->Name = "OutputGroupBox";
		this->OutputGroupBox->Size = new System::Drawing::Size(458, 106);
		this->OutputGroupBox->TabIndex = 18;
		this->OutputGroupBox->TabStop = false;
		this->OutputGroupBox->Text = "Output Options";
		// 
		// device
		// 
		this->device->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->device->FormattingEnabled = true;
		this->device->Items->AddRange(new object[1] {"Standard"});
		this->device->Location = new System::Drawing::Point(97, 47);
		this->device->Name = "device";
		this->device->Size = new System::Drawing::Size(85, 21);
		this->device->TabIndex = 38;
		// 
		// DeviceLabel
		// 
		this->DeviceLabel->AutoSize = true;
		this->DeviceLabel->Location = new System::Drawing::Point(6, 51);
		this->DeviceLabel->Name = "DeviceLabel";
		this->DeviceLabel->Size = new System::Drawing::Size(39, 13);
		this->DeviceLabel->TabIndex = 37;
		this->DeviceLabel->Text = "Device";
		// 
		// splitting
		// 
		this->splitting->setCustomSizes(new MeXgui::core::util::FileSize[0]);
		this->splitting->Location = new System::Drawing::Point(243, 16);
		this->splitting->MaximumSize = new System::Drawing::Size(1000, 29);
		this->splitting->MinimumSize = new System::Drawing::Size(64, 29);
		this->splitting->Name = "splitting";
		this->splitting->setNullString("No splitting");
		this->splitting->setSelectedIndex(0);
		this->splitting->Size = new System::Drawing::Size(208, 29);
		this->splitting->TabIndex = 26;
		// 
		// container
		// 
		this->container->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->container->FormattingEnabled = true;
		this->container->Location = new System::Drawing::Point(97, 20);
		this->container->Name = "container";
		this->container->Size = new System::Drawing::Size(85, 21);
		this->container->TabIndex = 25;
		this->container->SelectedIndexChanged += new System::EventHandler(this, &AutoEncodeWindow::container_SelectedIndexChanged);
		// 
		// containerLabel
		// 
		this->containerLabel->AutoSize = true;
		this->containerLabel->Location = new System::Drawing::Point(6, 23);
		this->containerLabel->Name = "containerLabel";
		this->containerLabel->Size = new System::Drawing::Size(54, 13);
		this->containerLabel->TabIndex = 24;
		this->containerLabel->Text = "Container";
		// 
		// muxedOutputLabel
		// 
		this->muxedOutputLabel->AutoSize = true;
		this->muxedOutputLabel->Location = new System::Drawing::Point(6, 81);
		this->muxedOutputLabel->Name = "muxedOutputLabel";
		this->muxedOutputLabel->Size = new System::Drawing::Size(82, 13);
		this->muxedOutputLabel->TabIndex = 23;
		this->muxedOutputLabel->Text = "Name of output";
		// 
		// muxedOutput
		// 
		this->muxedOutput->setFilename("");
		this->muxedOutput->setFilter("");
		this->muxedOutput->setFilterIndex(0);
		this->muxedOutput->setFolderMode(false);
		this->muxedOutput->Location = new System::Drawing::Point(97, 74);
		this->muxedOutput->Name = "muxedOutput";
		this->muxedOutput->setReadOnly(false);
		this->muxedOutput->setSaveMode(true);
		this->muxedOutput->Size = new System::Drawing::Size(352, 26);
		this->muxedOutput->TabIndex = 36;
		this->muxedOutput->setTitle("");
		// 
		// cancelButton
		// 
		this->cancelButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
		this->cancelButton->AutoSize = true;
		this->cancelButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->cancelButton->Location = new System::Drawing::Point(413, 228);
		this->cancelButton->Name = "cancelButton";
		this->cancelButton->Size = new System::Drawing::Size(49, 23);
		this->cancelButton->TabIndex = 19;
		this->cancelButton->Text = "Cancel";
		// 
		// addSubsNChapters
		// 
		this->addSubsNChapters->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
		this->addSubsNChapters->Location = new System::Drawing::Point(88, 228);
		this->addSubsNChapters->Name = "addSubsNChapters";
		this->addSubsNChapters->Size = new System::Drawing::Size(256, 24);
		this->addSubsNChapters->TabIndex = 20;
		this->addSubsNChapters->Text = "Add additional content (audio, subs, chapters)";
		this->defaultToolTip->SetToolTip(this->addSubsNChapters, "Checking this option allows you to specify pre-encoded audio and subtitle files t" + "o be added to your output, as well as assign audio/subtitle languages and assign" + " a chapter file");
		// 
		// helpButton1
		// 
		this->helpButton1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
		this->helpButton1->setArticleName("AutoEncode");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(10, 228);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 21;
		// 
		// AutoEncodeWindow
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->ClientSize = new System::Drawing::Size(471, 258);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->addSubsNChapters);
		this->Controls->Add(this->cancelButton);
		this->Controls->Add(this->OutputGroupBox);
		this->Controls->Add(this->AutomaticEncodingGroup);
		this->Controls->Add(this->queueButton);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = "AutoEncodeWindow";
		this->Text = "MeXgui - Automatic Encoding";
		this->AutomaticEncodingGroup->ResumeLayout(false);
		this->AutomaticEncodingGroup->PerformLayout();
		this->OutputGroupBox->ResumeLayout(false);
		this->OutputGroupBox->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void AutoEncodeWindow::container_SelectedIndexChanged()
	{
		ContainerType *cot = dynamic_cast<ContainerType*>(this->container->SelectedItem);
		this->muxedOutput->setFilter(cot->getOutputFilterString());
		if (!muxedOutput->getFilename().empty())
		{
			if (this->container->Text == "MKV")
				this->device->Enabled = false;
			else
				this->device->Enabled = true;

			QVector<DeviceType*> supportedOutputDeviceTypes = this->muxProvider->GetSupportedDevices(cot);
			this->device->Items->Clear();
			this->device->Items->Add("Standard");
			this->device->Items->AddRange(supportedOutputDeviceTypes.ToArray());

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if (container->SelectedItem->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getContainer()))
			{
				for (unknown::const_iterator o = device->Items.begin(); o != device->Items.end(); ++o) // I know this is ugly, but using the DeviceOutputType doesn't work unless we're switching to manual serialization
				{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					if ((*o)->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getDeviceOutputType()))
					{
						device->SelectedItem = *o;
						break;
					}
				}
			}
			else
				this->device->SelectedIndex = 0;

			this->muxedOutput->setFilename(Path::ChangeExtension(muxedOutput->getFilename(), (dynamic_cast<ContainerType*>(this->container->SelectedItem))->getExtension()));
		}
	}

	void AutoEncodeWindow::outputFormat_CheckedChanged()
	{
		ContainerType *cot = dynamic_cast<ContainerType*>(this->container->SelectedItem);
		this->muxedOutput->setFilename(Path::ChangeExtension(this->muxedOutput->getFilename(), cot->getExtension()));
	}

	void AutoEncodeWindow::separateEncodableAndMuxableAudioStreams(AudioJob encodable[], MuxStream muxable[], AudioEncoderType muxTypes[])
	{
		encodable = AudioUtil::getConfiguredAudioJobs(audioStreams.ToArray()); // discards improperly configured ones
		// the rest of the job is all encodeable
		muxable = new MuxStream[sizeof(encodable) / sizeof(encodable[0])];
		muxTypes = new AudioEncoderType[sizeof(encodable) / sizeof(encodable[0])];
		int j = 0;
		for (MeXgui::AudioJob::const_iterator stream = encodable->begin(); stream != encodable->end(); ++stream)
		{
			muxable[j] = (*stream)->ToMuxStream();
			muxTypes[j] = (*stream)->Settings->EncoderType;
			j++;
		}
	}

	void AutoEncodeWindow::setVideoBitrate()
	{
		try
		{
			CalcData *data = GetCalcData();
			data->setTotalSize(FileSize(targetSize->getValue().Value::Bytes));
			data->CalcByTotalSize();

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			this->videoSize->Text = data->getVideoSize().ToString();
			this->projectedBitrateKBits->Text = StringConverterHelper::toString(static_cast<int>(data->getVideoBitrate()));
		}
		catch (std::exception &e1)
		{
			this->projectedBitrateKBits->Text = "";
			videoSize->Text = "";
		}
	}

	MeXgui::packages::tools::calculator::CalcData *AutoEncodeWindow::GetCalcData()
	{
		CalcData *data = new CalcData(static_cast<qint64>(videoStream->getNumberOfFrames()), videoStream->getFramerate(), static_cast<ContainerType*>(container->SelectedItem), videoStream->getSettings()->getCodec(), videoStream->getSettings()->getNbBframes() > 0, getAudioStreamsForBitrate());
		return data;
	}

	AudioBitrateCalculationStream *AutoEncodeWindow::getAudioStreamsForBitrate()
	{
		QVector<AudioBitrateCalculationStream*> streams = QVector<AudioBitrateCalculationStream*>();
		for (QVector<AudioJob*>::const_iterator s = audioStreams.begin(); s != audioStreams.end(); ++s)
			streams.push_back(new AudioBitrateCalculationStream((*s)->Output));
		return streams.ToArray();
	}

	void AutoEncodeWindow::setTargetSize()
	{
		try
		{
			CalcData *data = GetCalcData();
			data->setVideoBitrate(int::Parse(this->projectedBitrateKBits->Text));
			data->CalcByVideoSize();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			this->videoSize->Text = data->getVideoSize().ToString();
			this->targetSize->setValue(FileSize(MB, data->getTotalSize().getMBExact()));
		}
		catch (std::exception &e1)
		{
			videoSize->Text = "";
			targetSize->setValue(Nullable<FileSize>());
		}
	}

	void AutoEncodeWindow::setAudioSize()
	{
		qint64 sizes[this->audioStreams.size()];
		int index = 0;
		for (QVector<AudioJob*>::const_iterator stream = this->audioStreams.begin(); stream != this->audioStreams.end(); ++stream)
		{
			if (!(*stream)->Output->empty()) // if we don't have the video length or the audio is not fully configured we can give up now
			{
				qint64 bytesPerSecond = 0;
				if ((*stream)->BitrateMode == CBR)
				{
					bytesPerSecond = (*stream)->Settings->Bitrate * 1000 / 8;
				}
				double lengthInSeconds = static_cast<double>(this->videoStream->getNumberOfFrames()) / static_cast<double>(this->videoStream->getFramerate());
				qint64 sizeInBytes = static_cast<qint64>(lengthInSeconds * bytesPerSecond);
				this->audioStreams[index]->SizeBytes = sizeInBytes;
				index++;
			}
		}
	}

	void AutoEncodeWindow::queueButton_Click()
	{
		if (!this->muxedOutput->getFilename().empty())
		{

			Nullable<FileSize> desiredSize = targetSize->getValue();
			Nullable<FileSize> splitSize = splitting->getValue();

			if (FileSizeRadio->Checked)
				log->LogValue("Desired Size ", desiredSize);
			else if (averageBitrateRadio->Checked)
				log->LogValue("Projected Bitrate ", QString::Format("{0}kbps", projectedBitrateKBits->Text));

			log->LogValue("Split Size ", splitSize);

//ORIGINAL LINE: MuxStream[] audio;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			MuxStream *audio;
//ORIGINAL LINE: AudioJob[] aStreams;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			AudioJob *aStreams;
//ORIGINAL LINE: AudioEncoderType[] muxTypes;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			AudioEncoderType *muxTypes;
			separateEncodableAndMuxableAudioStreams(aStreams, audio, muxTypes);
//ORIGINAL LINE: MuxStream[] subtitles = new MuxStream[0];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			MuxStream *subtitles = new MuxStream[0];
			QString chapters = "";
			QString videoInput = vInfo->getVideoInput();
			QString videoOutput = vInfo->getVideoOutput();
			QString muxedOutput = this->muxedOutput->getFilename();
			ContainerType *cot = dynamic_cast<ContainerType*>(this->container->SelectedItem);

			// determine audio language 
			for (MeXgui::core::details::MuxStream::const_iterator stream = audio->begin(); stream != audio->end(); ++stream)
			{
				for (QMap<QString, QString>::const_iterator strLanguage = LanguageSelectionContainer::getLanguages().begin(); strLanguage != LanguageSelectionContainer::getLanguages().end(); ++strLanguage)
				{
					if (Path::GetFileNameWithoutExtension((*stream)->path)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
					{
						(*stream)->setlanguage(strLanguage->first);
						break;
					}
				}
			}

			if (addSubsNChapters->Checked)
			{
				AdaptiveMuxWindow *amw = new AdaptiveMuxWindow(mainForm);
				amw->setMinimizedMode(videoOutput, "", videoStream->getSettings()->getEncoderType(), jobUtil->getFramerate(videoInput), audio, muxTypes, muxedOutput, splitSize, cot);
				if (amw->show() == System::Windows::Forms::DialogResult::OK)
					amw->getAdditionalStreams(audio, subtitles, chapters, muxedOutput, cot);
				else // user aborted, abort the whole process
					return;
			}
			removeStreamsToBeEncoded(audio, aStreams);
			mainForm->getJobs()->addJobsWithDependencies(vUtil->GenerateJobSeries(this->videoStream, muxedOutput, aStreams, subtitles, chapters, desiredSize, splitSize, cot, this->prerender, audio, log, this->device->Text, vInfo->getZones(), 0, 0, false), true);
			this->Close();
		}
	}

	void AutoEncodeWindow::removeStreamsToBeEncoded(MuxStream audio[], AudioJob aStreams[])
	{
		QVector<MuxStream*> newAudio = QVector<MuxStream*>();
		for (MeXgui::core::details::MuxStream::const_iterator stream = audio->begin(); stream != audio->end(); ++stream)
		{
			bool matchFound = false;
			for (MeXgui::AudioJob::const_iterator a = aStreams->begin(); a != aStreams->end(); ++a)
			{
				if ((*stream)->path == (*a)->Output)
				{
					matchFound = true; // found a file which needs to be encoded
					(*a)->Language = (*stream)->getlanguage(); // set language
					(*a)->Name = (*stream)->getname(); // set track name
					break;
				}
			}
			if (!matchFound) // not found any files which will be encoded first to produce this file
			{
				newAudio.push_back(*stream);
			}
		}
		audio = newAudio.ToArray();
	}

	void AutoEncodeWindow::textField_KeyPress(object *sender, KeyPressEventArgs *e)
	{
		if (!isdigit(e->KeyChar) && static_cast<int>(Keys::Back) != static_cast<int>(e->KeyChar))
			e->Handled = true;
	}

	void AutoEncodeWindow::containerOverhead_ValueChanged()
	{
		if (isBitrateMode)
			this->setVideoBitrate();
		else
			this->setTargetSize();
	}

	void AutoEncodeWindow::projectedBitrate_TextChanged()
	{
		if (!this->isBitrateMode)
			this->setTargetSize();
	}

	void AutoEncodeWindow::calculationMode_CheckedChanged()
	{
		if (averageBitrateRadio->Checked)
		{
			targetSize->Enabled = false;
			this->targetSize->setSelectedIndex(3);
			this->projectedBitrateKBits->Enabled = true;
			this->isBitrateMode = false;
		}
		else if (noTargetRadio->Checked)
		{
			targetSize->Enabled = false;
			this->targetSize->setSelectedIndex(0);
			this->projectedBitrateKBits->Enabled = false;
			this->isBitrateMode = false;
		}
		else
		{
			targetSize->Enabled = true;
			this->targetSize->setSelectedIndex(3);
			this->projectedBitrateKBits->Enabled = false;
			this->isBitrateMode = true;
		}
	}

	void AutoEncodeWindow::targetSize_SelectionChanged(object *sender, const QString &val)
	{
		if (isBitrateMode)
			this->setVideoBitrate();
	}

	void AutoEncodeWindow::InitializeInstanceFields()
	{
		log = new LogItem("AutoEncode job generation log", Information);
		isBitrateMode = true;
	}

	const QString &AutoEncodeTool::getName() const
	{
		return "AutoEncode";
	}

	void AutoEncodeTool::Run(MainForm *info)
	{
		// normal video verification
		QString error = "";
		if ((error = info->getVideo()->verifyVideoSettings()) != 0)
		{
			MessageBox::Show(error, "Unsupported video configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return;
		}
		if ((error = info->getAudio()->verifyAudioSettings()) != 0 && !error.Equals("No audio input defined."))
		{
			MessageBox::Show(error, "Unsupported audio configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return;
		}
	#warning must be fixed up to be more generic
		if (info->getVideo()->getCurrentSettings()->getEncodingMode() == 2 || info->getVideo()->getCurrentSettings()->getEncodingMode() == 5)
		{
			MessageBox::Show("First pass encoding is not supported for automated encoding as no output is generated.\nPlease choose another encoding mode", "Improper configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return;
		}

		VideoCodecSettings *vSettings = info->getVideo()->getCurrentSettings()->Clone();
//ORIGINAL LINE: Zone[] zones = info.Video.Info.Zones;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		Zone *zones = info->getVideo()->getInfo()->getZones(); // We can't simply modify the zones in place because that would reveal the final zones config to the user, including the credits/start zones
		bool cont = info->getJobUtil()->getFinalZoneConfiguration(vSettings, info->getVideo()->getInfo()->getIntroEndFrame(), info->getVideo()->getInfo()->getCreditsStartFrame(), zones);
		if (cont)
		{
			quint64 length = 0;
			double framerate = 0.0;
			VideoStream *myVideo = new VideoStream();
			JobUtil::getInputProperties(length, framerate, info->getVideo()->getVideoInput());
			myVideo->setInput(info->getVideo()->getInfo()->getVideoInput());
			myVideo->setOutput(info->getVideo()->getInfo()->getVideoOutput());
			myVideo->setNumberOfFrames(length);
			myVideo->setFramerate(static_cast<decimal>(framerate));
			myVideo->setDAR(info->getVideo()->getInfo()->getDAR());
			myVideo->setVideoType(info->getVideo()->getCurrentMuxableVideoType());
			myVideo->setSettings(vSettings);

			VideoInfo *vInfo = info->getVideo()->getInfo()->Clone(); // so we don't modify the data on the main form
			vInfo->setZones(zones);

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AutoEncodeWindow aew = new AutoEncodeWindow(myVideo, info.Audio.AudioStreams, info, info.Video.PrerenderJob, vInfo))
			AutoEncodeWindow *aew = new AutoEncodeWindow(myVideo, info->getAudio()->getAudioStreams(), info, info->getVideo()->getPrerenderJob(), vInfo);
			try
			{
				if (aew->init())
				{
					info->ClosePlayer();
					aew->show();
				}
				else
					MessageBox::Show("The currently selected combination of video and audio output cannot be muxed", "Unsupported configuration", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (aew != 0)
					aew.Dispose();
			}
		}
	}

	const Shortcut &AutoEncodeTool::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlF6};
	}

	const QString &AutoEncodeTool::getID() const
	{
		return "AutoEncode";
	}
}
