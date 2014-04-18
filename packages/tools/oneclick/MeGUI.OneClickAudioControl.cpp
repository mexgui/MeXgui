#include "MeXgui.OneClickAudioControl.h"




//using namespace System::Collections::Generic;




using namespace MeXgui::core::gui;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;

namespace MeXgui
{

	OneClickAudioControl::OneClickAudioControl()
	{
		InitializeInstanceFields();
		InitializeComponent();
		language->Items->AddRange((QVector<QString>(LanguageSelectionContainer::getLanguages().Keys))->ToArray());
		cbEncodingMode->Items->AddRange(EnumProxy::CreateArray(OneClickSettings::SupportedModes));
		if (MainForm::Instance != 0)
			encoderProfile->setManager(MainForm::Instance->getProfiles());
	}

	void OneClickAudioControl::SetProfileNameOrWarn(const QString &fqname)
	{
		encoderProfile->SetProfileNameOrWarn(fqname);
	}

	const AudioEncodingMode &OneClickAudioControl::getEncodingMode() const
	{
		return static_cast<AudioEncodingMode>(cbEncodingMode->SelectedIndex);
	}

	void OneClickAudioControl::setEncodingMode(const AudioEncodingMode &value)
	{
		cbEncodingMode->SelectedIndex = static_cast<int>(value);
	}

	const Profile &OneClickAudioControl::getEncoderProfile() const
	{
		return encoderProfile->getSelectedProfile();
	}

	const QString &OneClickAudioControl::getLanguage() const
	{
		return language->Text;
	}

	void OneClickAudioControl::setLanguage(const QString &value)
	{
		language->SelectedItem = value;
	}

	const bool &OneClickAudioControl::getUseFirstTrackOnly() const
	{
		return cbFirstTrackOnly->Checked;
	}

	void OneClickAudioControl::setUseFirstTrackOnly(const bool &value)
	{
		cbFirstTrackOnly->Checked = value;
	}

	void OneClickAudioControl::cbEncodingMode_SelectedIndexChanged()
	{
		encoderProfile->Enabled = !cbEncodingMode->SelectedText->Equals("never");
	}

	void OneClickAudioControl::language_SelectedIndexChanged()
	{
		LanguageChanged(this, 0);
	}

	void OneClickAudioControl::SetDefault()
	{
		language->Enabled = false;
		language->Items->Add("[default]");
		language->SelectedIndex = 0;
	}

	void OneClickAudioControl::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		UserControl::Dispose(disposing);
	}

	void OneClickAudioControl::InitializeComponent()
	{
		this->language = new System::Windows::Forms::ComboBox();
		this->languageLabel = new System::Windows::Forms::Label();
		this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
		this->label2 = new System::Windows::Forms::Label();
		this->cbEncodingMode = new System::Windows::Forms::ComboBox();
		this->encoderProfile = new MeXgui::core::gui::ConfigableProfilesControl();
		this->label1 = new System::Windows::Forms::Label();
		this->cbFirstTrackOnly = new System::Windows::Forms::CheckBox();
		this->tableLayoutPanel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// language
		// 
		this->tableLayoutPanel1->SetColumnSpan(this->language, 2);
		this->language->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->language->Location = new System::Drawing::Point(64, 3);
		this->language->Name = "language";
		this->language->Size = new System::Drawing::Size(312, 21);
		this->language->Sorted = true;
		this->language->TabIndex = 37;
		this->language->SelectedIndexChanged += new System::EventHandler(this, &OneClickAudioControl::language_SelectedIndexChanged);
		// 
		// languageLabel
		// 
		this->languageLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->languageLabel->AutoSize = true;
		this->languageLabel->Location = new System::Drawing::Point(3, 8);
		this->languageLabel->Name = "languageLabel";
		this->languageLabel->Size = new System::Drawing::Size(55, 13);
		this->languageLabel->TabIndex = 36;
		this->languageLabel->Text = "Language";
		// 
		// tableLayoutPanel1
		// 
		this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->tableLayoutPanel1->ColumnCount = 3;
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->Controls->Add(this->label2, 0, 2);
		this->tableLayoutPanel1->Controls->Add(this->cbEncodingMode, 1, 2);
		this->tableLayoutPanel1->Controls->Add(this->encoderProfile, 1, 1);
		this->tableLayoutPanel1->Controls->Add(this->language, 1, 0);
		this->tableLayoutPanel1->Controls->Add(this->languageLabel, 0, 0);
		this->tableLayoutPanel1->Controls->Add(this->label1, 0, 1);
		this->tableLayoutPanel1->Controls->Add(this->cbFirstTrackOnly, 1, 3);
		this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tableLayoutPanel1->Location = new System::Drawing::Point(0, 0);
		this->tableLayoutPanel1->Name = "tableLayoutPanel1";
		this->tableLayoutPanel1->RowCount = 4;
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30));
		this->tableLayoutPanel1->Size = new System::Drawing::Size(380, 120);
		this->tableLayoutPanel1->TabIndex = 44;
		// 
		// label2
		// 
		this->label2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->label2->AutoSize = true;
		this->label2->Location = new System::Drawing::Point(3, 68);
		this->label2->Name = "label2";
		this->label2->Size = new System::Drawing::Size(55, 13);
		this->label2->TabIndex = 51;
		this->label2->Text = "Encode";
		// 
		// cbEncodingMode
		// 
		this->tableLayoutPanel1->SetColumnSpan(this->cbEncodingMode, 2);
		this->cbEncodingMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbEncodingMode->FormattingEnabled = true;
		this->cbEncodingMode->Location = new System::Drawing::Point(64, 63);
		this->cbEncodingMode->Name = "cbEncodingMode";
		this->cbEncodingMode->Size = new System::Drawing::Size(312, 21);
		this->cbEncodingMode->TabIndex = 49;
		this->cbEncodingMode->SelectedIndexChanged += new System::EventHandler(this, &OneClickAudioControl::cbEncodingMode_SelectedIndexChanged);
		// 
		// encoderProfile
		// 
		this->tableLayoutPanel1->SetColumnSpan(this->encoderProfile, 2);
		this->encoderProfile->Location = new System::Drawing::Point(64, 33);
		this->encoderProfile->Name = "encoderProfile";
		this->encoderProfile->setProfileSet("Audio");
		this->encoderProfile->Size = new System::Drawing::Size(313, 22);
		this->encoderProfile->TabIndex = 48;
		// 
		// label1
		// 
		this->label1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->label1->AutoSize = true;
		this->label1->Location = new System::Drawing::Point(3, 38);
		this->label1->Name = "label1";
		this->label1->Size = new System::Drawing::Size(55, 13);
		this->label1->TabIndex = 50;
		this->label1->Text = "Encoder";
		// 
		// cbFirstTrackOnly
		// 
		this->cbFirstTrackOnly->AutoSize = true;
		this->tableLayoutPanel1->SetColumnSpan(this->cbFirstTrackOnly, 2);
		this->cbFirstTrackOnly->Location = new System::Drawing::Point(64, 93);
		this->cbFirstTrackOnly->Name = "cbFirstTrackOnly";
		this->cbFirstTrackOnly->Size = new System::Drawing::Size(129, 17);
		this->cbFirstTrackOnly->TabIndex = 52;
		this->cbFirstTrackOnly->Text = "use only the first track";
		this->cbFirstTrackOnly->UseVisualStyleBackColor = true;
		// 
		// OneClickAudioControl
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->Controls->Add(this->tableLayoutPanel1);
		this->Name = "OneClickAudioControl";
		this->Size = new System::Drawing::Size(380, 120);
		this->tableLayoutPanel1->ResumeLayout(false);
		this->tableLayoutPanel1->PerformLayout();
		this->ResumeLayout(false);

	}

	void OneClickAudioControl::InitializeInstanceFields()
	{
		delete components;
	}
}
