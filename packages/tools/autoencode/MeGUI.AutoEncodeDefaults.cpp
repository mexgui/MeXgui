#include "MeXgui.AutoEncodeDefaults.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


using namespace MeXgui::core::util;

namespace MeXgui
{

	AutoEncodeDefaults::AutoEncodeDefaults()
	{
		InitializeInstanceFields();
		InitializeComponent();
	}

	const AutoEncodeDefaultsSettings &AutoEncodeDefaults::getSettings() const
	{
		AutoEncodeDefaultsSettings *defaults = new AutoEncodeDefaultsSettings();
		defaults->setAddAdditionalContent(addSubsNChapters->Checked);
		defaults->setSplitSize(splitSize->getValue());
		defaults->setFileSizeMode(FileSizeRadio->Checked);
		defaults->setFileSize(fileSize->getValue());
		defaults->setBitrateMode(averageBitrateRadio->Checked);
		if (defaults->getBitrateMode())
		{
			try
			{
				int bitrate = int::Parse(projectedBitrateKBits->Text);
				defaults->setBitrate(bitrate);
			}
			catch (std::exception &e1)
			{

			}
		}
		defaults->setNoTargetSizeMode(noTargetRadio->Checked);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		defaults->setContainer(container->SelectedItem->ToString());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		defaults->setDeviceOutputType(device->SelectedItem->ToString());
		return defaults;
	}

	void AutoEncodeDefaults::setSettings(const AutoEncodeDefaultsSettings &value)
	{
		AutoEncodeDefaultsSettings *defaults = value;
		addSubsNChapters->Checked = defaults->getAddAdditionalContent();
		splitSize->setValue(defaults->getSplitSize());
		FileSizeRadio->Checked = defaults->getFileSizeMode();
		fileSize->setValue(defaults->getFileSize());
		averageBitrateRadio->Checked = defaults->getBitrateMode();
		projectedBitrateKBits->Text = StringConverterHelper::toString(defaults->getBitrate());
		noTargetRadio->Checked = defaults->getNoTargetSizeMode();
		container->Items->AddRange(MainForm::Instance->getMuxProvider()->GetSupportedContainers().ToArray());
		for (unknown::const_iterator o = container->Items.begin(); o != container->Items.end(); ++o) // I know this is ugly, but using the ContainerType doesn't work unless we're switching to manual serialization
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if ((*o)->ToString()->Equals(defaults->getContainer()))
			{
				container->SelectedItem = *o;
				break;
			}
		}
		this->device->Items->Clear();
		this->device->Items->Add("Standard");
		this->device->Items->AddRange(MainForm::Instance->getMuxProvider()->GetSupportedDevices(static_cast<ContainerType*>(container->SelectedItem)).ToArray());
		this->device->SelectedIndex = 0;
		for (unknown::const_iterator o = device->Items.begin(); o != device->Items.end(); ++o) // I know this is ugly, but using the DeviceOutputType doesn't work unless we're switching to manual serialization
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if ((*o)->ToString()->Equals(defaults->getDeviceOutputType()))
			{
				device->SelectedItem = *o;
				break;
			}
		}
	}

	void AutoEncodeDefaults::FileSizeRadio_CheckedChanged()
	{
		if (averageBitrateRadio->Checked)
		{
			fileSize->Enabled = false;
			this->projectedBitrateKBits->Enabled = true;
		}
		else if (noTargetRadio->Checked)
		{
			fileSize->Enabled = false;
			this->projectedBitrateKBits->Enabled = false;
		}
		else
		{
			fileSize->Enabled = true;
			this->projectedBitrateKBits->Enabled = false;
		}
	}

	void AutoEncodeDefaults::textField_KeyPress(object *sender, KeyPressEventArgs *e)
	{
		if (!isdigit(e->KeyChar) && static_cast<int>(Keys::Back) != static_cast<int>(e->KeyChar))
			e->Handled = true;
	}

	void AutoEncodeDefaults::container_SelectedIndexChanged()
	{
		if (this->container->Text == "MKV")
			this->device->Enabled = false;
		else
			this->device->Enabled = true;

		this->device->Items->Clear();
		this->device->Items->Add("Standard");
		this->device->Items->AddRange(MainForm::Instance->getMuxProvider()->GetSupportedDevices(static_cast<ContainerType*>(container->SelectedItem)).ToArray());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (container->SelectedItem->ToString()->Equals(MainForm::Instance->getSettings()->getAedSettings()->getContainer()))
		{
			for (unknown::const_iterator o = device->Items.begin(); o != device->Items.end(); ++o) // I know this is ugly, but using the DeviceOutputType doesn't work unless we're switching to manual serialization
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				if ((*o)->ToString()->Equals(MainForm::Instance->getSettings()->getAedSettings()->getDeviceOutputType()))
				{
					device->SelectedItem = *o;
					break;
				}
			}
		}
		else
			this->device->SelectedIndex = 0;
	}

	void AutoEncodeDefaults::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void AutoEncodeDefaults::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(AutoEncodeDefaults::typeid);
		this->AutomaticEncodingGroup = new System::Windows::Forms::GroupBox();
		this->fileSize = new MeXgui::core::gui::TargetSizeSCBox();
		this->noTargetRadio = new System::Windows::Forms::RadioButton();
		this->averageBitrateRadio = new System::Windows::Forms::RadioButton();
		this->FileSizeRadio = new System::Windows::Forms::RadioButton();
		this->projectedBitrateKBits = new System::Windows::Forms::TextBox();
		this->AverageBitrateLabel = new System::Windows::Forms::Label();
		this->cancelButton = new QPushButton;
		this->saveButton = new QPushButton;
		this->OutputGroupBox = new System::Windows::Forms::GroupBox();
		this->DeviceLabel = new System::Windows::Forms::Label();
		this->device = new System::Windows::Forms::ComboBox();
		this->label1 = new System::Windows::Forms::Label();
		this->splitSize = new MeXgui::core::gui::TargetSizeSCBox();
		this->container = new System::Windows::Forms::ComboBox();
		this->containerLabel = new System::Windows::Forms::Label();
		this->addSubsNChapters = new System::Windows::Forms::CheckBox();
		this->AutomaticEncodingGroup->SuspendLayout();
		this->OutputGroupBox->SuspendLayout();
		this->SuspendLayout();
		// 
		// AutomaticEncodingGroup
		// 
		this->AutomaticEncodingGroup->Controls->Add(this->fileSize);
		this->AutomaticEncodingGroup->Controls->Add(this->noTargetRadio);
		this->AutomaticEncodingGroup->Controls->Add(this->averageBitrateRadio);
		this->AutomaticEncodingGroup->Controls->Add(this->FileSizeRadio);
		this->AutomaticEncodingGroup->Controls->Add(this->projectedBitrateKBits);
		this->AutomaticEncodingGroup->Controls->Add(this->AverageBitrateLabel);
		this->AutomaticEncodingGroup->Location = new System::Drawing::Point(3, 103);
		this->AutomaticEncodingGroup->Name = "AutomaticEncodingGroup";
		this->AutomaticEncodingGroup->Size = new System::Drawing::Size(424, 104);
		this->AutomaticEncodingGroup->TabIndex = 18;
		this->AutomaticEncodingGroup->TabStop = false;
		this->AutomaticEncodingGroup->Text = "Size and Bitrate";
		// 
		// fileSize
		// 
		this->fileSize->setCustomSizes(new MeXgui::core::util::FileSize[0]);
		this->fileSize->Location = new System::Drawing::Point(101, 12);
		this->fileSize->MaximumSize = new System::Drawing::Size(1000, 29);
		this->fileSize->MinimumSize = new System::Drawing::Size(64, 29);
		this->fileSize->Name = "fileSize";
		this->fileSize->setNullString("");
		this->fileSize->setSelectedIndex(0);
		this->fileSize->Size = new System::Drawing::Size(171, 29);
		this->fileSize->TabIndex = 23;
		// 
		// noTargetRadio
		// 
		this->noTargetRadio->Location = new System::Drawing::Point(16, 72);
		this->noTargetRadio->Name = "noTargetRadio";
		this->noTargetRadio->Size = new System::Drawing::Size(208, 18);
		this->noTargetRadio->TabIndex = 22;
		this->noTargetRadio->TabStop = true;
		this->noTargetRadio->Text = "No Target Size (use profile settings)";
		this->noTargetRadio->UseVisualStyleBackColor = true;
		this->noTargetRadio->CheckedChanged += new System::EventHandler(this, &AutoEncodeDefaults::FileSizeRadio_CheckedChanged);
		// 
		// averageBitrateRadio
		// 
		this->averageBitrateRadio->Location = new System::Drawing::Point(16, 47);
		this->averageBitrateRadio->Name = "averageBitrateRadio";
		this->averageBitrateRadio->Size = new System::Drawing::Size(79, 18);
		this->averageBitrateRadio->TabIndex = 16;
		this->averageBitrateRadio->Text = "Average Bitrate";
		this->averageBitrateRadio->CheckedChanged += new System::EventHandler(this, &AutoEncodeDefaults::FileSizeRadio_CheckedChanged);
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
		this->FileSizeRadio->CheckedChanged += new System::EventHandler(this, &AutoEncodeDefaults::FileSizeRadio_CheckedChanged);
		// 
		// projectedBitrateKBits
		// 
		this->projectedBitrateKBits->Enabled = false;
		this->projectedBitrateKBits->Location = new System::Drawing::Point(101, 44);
		this->projectedBitrateKBits->Name = "projectedBitrateKBits";
		this->projectedBitrateKBits->Size = new System::Drawing::Size(64, 21);
		this->projectedBitrateKBits->TabIndex = 9;
		this->projectedBitrateKBits->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, &AutoEncodeDefaults::textField_KeyPress);
		// 
		// AverageBitrateLabel
		// 
		this->AverageBitrateLabel->Location = new System::Drawing::Point(171, 47);
		this->AverageBitrateLabel->Name = "AverageBitrateLabel";
		this->AverageBitrateLabel->Size = new System::Drawing::Size(37, 23);
		this->AverageBitrateLabel->TabIndex = 10;
		this->AverageBitrateLabel->Text = "kbit/s";
		// 
		// cancelButton
		// 
		this->cancelButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->cancelButton->Location = new System::Drawing::Point(379, 215);
		this->cancelButton->Name = "cancelButton";
		this->cancelButton->Size = new System::Drawing::Size(48, 23);
		this->cancelButton->TabIndex = 20;
		this->cancelButton->Text = "Cancel";
		// 
		// saveButton
		// 
		this->saveButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->saveButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->saveButton->Location = new System::Drawing::Point(311, 215);
		this->saveButton->Name = "saveButton";
		this->saveButton->Size = new System::Drawing::Size(48, 23);
		this->saveButton->TabIndex = 19;
		this->saveButton->Text = "Save";
		// 
		// OutputGroupBox
		// 
		this->OutputGroupBox->Controls->Add(this->DeviceLabel);
		this->OutputGroupBox->Controls->Add(this->device);
		this->OutputGroupBox->Controls->Add(this->label1);
		this->OutputGroupBox->Controls->Add(this->splitSize);
		this->OutputGroupBox->Controls->Add(this->container);
		this->OutputGroupBox->Controls->Add(this->containerLabel);
		this->OutputGroupBox->Location = new System::Drawing::Point(3, 12);
		this->OutputGroupBox->Name = "OutputGroupBox";
		this->OutputGroupBox->Size = new System::Drawing::Size(424, 85);
		this->OutputGroupBox->TabIndex = 21;
		this->OutputGroupBox->TabStop = false;
		this->OutputGroupBox->Text = "Output Options";
		// 
		// DeviceLabel
		// 
		this->DeviceLabel->AutoSize = true;
		this->DeviceLabel->Location = new System::Drawing::Point(16, 54);
		this->DeviceLabel->Name = "DeviceLabel";
		this->DeviceLabel->Size = new System::Drawing::Size(39, 13);
		this->DeviceLabel->TabIndex = 40;
		this->DeviceLabel->Text = "Device";
		// 
		// device
		// 
		this->device->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->device->FormattingEnabled = true;
		this->device->Items->AddRange(new object[1] {"Standard"});
		this->device->Location = new System::Drawing::Point(101, 51);
		this->device->Name = "device";
		this->device->Size = new System::Drawing::Size(85, 21);
		this->device->TabIndex = 39;
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = new System::Drawing::Point(215, 27);
		this->label1->Name = "label1";
		this->label1->Size = new System::Drawing::Size(49, 13);
		this->label1->TabIndex = 27;
		this->label1->Text = "Splitting:";
		// 
		// splitSize
		// 
		this->splitSize->setCustomSizes(new MeXgui::core::util::FileSize[0]);
		this->splitSize->Location = new System::Drawing::Point(270, 20);
		this->splitSize->MaximumSize = new System::Drawing::Size(1000, 29);
		this->splitSize->MinimumSize = new System::Drawing::Size(64, 29);
		this->splitSize->Name = "splitSize";
		this->splitSize->setNullString("No splitting");
		this->splitSize->setSelectedIndex(0);
		this->splitSize->Size = new System::Drawing::Size(148, 29);
		this->splitSize->TabIndex = 26;
		// 
		// container
		// 
		this->container->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->container->FormattingEnabled = true;
		this->container->Location = new System::Drawing::Point(101, 24);
		this->container->Name = "container";
		this->container->Size = new System::Drawing::Size(85, 21);
		this->container->TabIndex = 25;
		this->container->SelectedIndexChanged += new System::EventHandler(this, &AutoEncodeDefaults::container_SelectedIndexChanged);
		// 
		// containerLabel
		// 
		this->containerLabel->AutoSize = true;
		this->containerLabel->Location = new System::Drawing::Point(16, 28);
		this->containerLabel->Name = "containerLabel";
		this->containerLabel->Size = new System::Drawing::Size(54, 13);
		this->containerLabel->TabIndex = 24;
		this->containerLabel->Text = "Container";
		// 
		// addSubsNChapters
		// 
		this->addSubsNChapters->Location = new System::Drawing::Point(19, 215);
		this->addSubsNChapters->Name = "addSubsNChapters";
		this->addSubsNChapters->Size = new System::Drawing::Size(256, 24);
		this->addSubsNChapters->TabIndex = 22;
		this->addSubsNChapters->Text = "Add additional content (audio, subs, chapters)";
		// 
		// AutoEncodeDefaults
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->CancelButton = this->cancelButton;
		this->ClientSize = new System::Drawing::Size(433, 241);
		this->Controls->Add(this->addSubsNChapters);
		this->Controls->Add(this->OutputGroupBox);
		this->Controls->Add(this->cancelButton);
		this->Controls->Add(this->saveButton);
		this->Controls->Add(this->AutomaticEncodingGroup);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = "AutoEncodeDefaults";
		this->ShowInTaskbar = false;
		this->Text = "MeXgui - Auto Encode Defaults";
		this->AutomaticEncodingGroup->ResumeLayout(false);
		this->AutomaticEncodingGroup->PerformLayout();
		this->OutputGroupBox->ResumeLayout(false);
		this->OutputGroupBox->PerformLayout();
		this->ResumeLayout(false);

	}

	void AutoEncodeDefaults::InitializeInstanceFields()
	{
		delete components;
	}
}
