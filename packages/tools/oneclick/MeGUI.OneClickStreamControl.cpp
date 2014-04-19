#include "OneClickStreamControl.h"




//using namespace System::Collections::Generic;




using namespace MeXgui::core::gui;
using namespace MeXgui::core::util;

namespace MeXgui
{

	OneClickStreamControl::OneClickStreamControl()
	{
		InitializeInstanceFields();
		InitializeComponent();
		subtitleLanguage->Items->AddRange((QVector<QString>(LanguageSelectionContainer::getLanguages().Keys))->ToArray());
		cbEncodingMode->Items->AddRange(EnumProxy::CreateArray(OneClickSettings::SupportedModes));
		initProfileHandler();
	}

	void OneClickStreamControl::enableDragDrop()
	{
		// only enable drag&drop when the main form is visible
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		DragDropUtil::RegisterSingleFileDragDrop(input, setFileName, delegate()
		{
			return getFilter();
		}
	   );
	}

	void OneClickStreamControl::initProfileHandler()
	{
		if (MainForm::Instance != 0)
			encoderProfile->setManager(MainForm::Instance->getProfiles());
	}

	void OneClickStreamControl::SelectProfileNameOrWarn(const QString &fqname)
	{
		encoderProfile->SetProfileNameOrWarn(fqname);
	}

	const AudioEncodingMode &OneClickStreamControl::getEncodingMode() const
	{
		return static_cast<AudioEncodingMode>(cbEncodingMode->SelectedIndex);
	}

	void OneClickStreamControl::setEncodingMode(const AudioEncodingMode &value)
	{
		cbEncodingMode->SelectedIndex = static_cast<int>(value);
	}

	const AudioCodecSettings &OneClickStreamControl::getEncoderProfileSettings() const
	{
		return static_cast<AudioCodecSettings*>(encoderProfile->getSelectedProfile()->BaseSettings);
	}

	const QString &OneClickStreamControl::getEncoderProfile() const
	{
		return encoderProfile->getSelectedProfile()->getFQName();
	}

	const OneClickStream &OneClickStreamControl::getStream() const
	{
		if (input->getSelectedText().empty())
			return 0;

		return new OneClickStream(input->getSelectedText(), Unknown, 0, 0, 0, subtitleLanguage->Text, subName->Text, static_cast<int>(delay->Value), chkDefaultStream->Checked, chkForceStream->Checked, static_cast<AudioCodecSettings*>(encoderProfile->getSelectedProfile()->BaseSettings), static_cast<AudioEncodingMode>(cbEncodingMode->SelectedIndex));
	}

	void OneClickStreamControl::setStream(const OneClickStream &value)
	{
		if (value == 0)
		{
			removeTrack_Click(0, 0);
			return;
		}

		MeXgui::core::gui::NiceComboBoxItem *oItem = new core::gui::NiceComboBoxItem(value->getDemuxFilePath(), value);
		input->setSelectedItem(oItem);
		if (!value->getLanguage().empty())
		{
			if (!(LanguageSelectionContainer::lookupISOCode(value->getLanguage())).empty())
				subtitleLanguage->Text = LanguageSelectionContainer::lookupISOCode(value->getLanguage());
			else
				subtitleLanguage->Text = value->getLanguage();
		}
		else
			subtitleLanguage->Text = defaultLanguage;
		subName->Text = value->getName();
		delay->Value = value->getDelay();
		chkDefaultStream->Checked = value->getDefaultStream();
		chkForceStream->Checked = value->getForcedStream();
	}

	void OneClickStreamControl::setDefaultLanguage(const QString &value)
	{
		defaultLanguage = value;
	}

	const QString &OneClickStreamControl::getDefaultLanguage() const
	{
		return defaultLanguage;
	}

	void OneClickStreamControl::setShowDelay(const bool &value)
	{
		showDelay = value;
		delayLabel->Visible = value;
		delay->Visible = value;
		if (!value)
			delay->Value = 0;
	}

	const bool &OneClickStreamControl::getShowDelay() const
	{
		return showDelay;
	}

	void OneClickStreamControl::setShowDefaultStream(const bool &value)
	{
		showDefaultStream = value;
		chkDefaultStream->Visible = value;
		if (!value)
			chkDefaultStream->Checked = false;
	}

	const bool &OneClickStreamControl::getShowDefaultStream() const
	{
		return showDefaultStream;
	}

	void OneClickStreamControl::setShowForceStream(const bool &value)
	{
		showForceStream = value;
		chkForceStream->Visible = value;
		if (!value)
			chkForceStream->Checked = false;
	}

	const bool &OneClickStreamControl::getShowForceStream() const
	{
		return showForceStream;
	}

	const QString &OneClickStreamControl::getFilter() const
	{
		return input->getFilter();
	}

	void OneClickStreamControl::setFilter(const QString &value)
	{
		input->setFilter(value);
	}

	const object &OneClickStreamControl::getStandardStreams() const
	{
		return input->getStandardItems();
	}

	void OneClickStreamControl::setStandardStreams(const object &value[])
	{
		input->setStandardItems(value);
	}

	const object &OneClickStreamControl::getCustomStreams() const
	{
		return input->getCustomItems();
	}

	void OneClickStreamControl::setCustomStreams(const object &value[])
	{
		input->setCustomItems(value);
	}

	const int &OneClickStreamControl::getSelectedStreamIndex() const
	{
		return input->getSelectedIndex();
	}

	void OneClickStreamControl::setSelectedStreamIndex(const int &value)
	{
		input->setSelectedIndex(value);
	}

	const MeXgui::core::gui::SCItem &OneClickStreamControl::getSelectedItem() const
	{
		return input->getSelectedSCItem();
	}

	const OneClickStream &OneClickStreamControl::getSelectedStream() const
	{
		if (input->getSelectedObject() != 0 && !input->getSelectedText().empty() && !input->getSelectedText().Equals("None") && input->getSelectedSCItem()->IsStandard)
		{
			OneClickStream *oStream = static_cast<OneClickStream*>(input->getSelectedObject());
			oStream->setLanguage(subtitleLanguage->Text);
			oStream->setName(subName->Text);
			oStream->setDelay(static_cast<int>(delay->Value));
			oStream->setDefaultStream((static_cast<OneClickStream*>(input->getSelectedObject()))->getDefaultStream());
			oStream->setForcedStream((static_cast<OneClickStream*>(input->getSelectedObject()))->getForcedStream());
			oStream->setEncoderSettings(static_cast<AudioCodecSettings*>(encoderProfile->getSelectedProfile()->BaseSettings));
			oStream->setEncodingMode(static_cast<AudioEncodingMode>(cbEncodingMode->SelectedIndex));
			return oStream;
		}
		else
			return new OneClickStream(input->getSelectedText(), Unknown, 0, 0, 0, subtitleLanguage->Text, subName->Text, static_cast<int>(delay->Value), chkDefaultStream->Checked, chkForceStream->Checked, static_cast<AudioCodecSettings*>(encoderProfile->getSelectedProfile()->BaseSettings), static_cast<AudioEncodingMode>(cbEncodingMode->SelectedIndex));
	}

	const QString &OneClickStreamControl::getSelectedFile() const
	{
		return input->getSelectedText();
	}

	void OneClickStreamControl::SetLanguage(const QString &lang)
	{
		subtitleLanguage->SelectedItem = lang;
	}

	void OneClickStreamControl::removeTrack_Click()
	{
		input->Text = "";
		subtitleLanguage->SelectedIndex = -1;
		subName->Text = "";
		delay->Value = 0;
		raiseEvent();
	}

	void OneClickStreamControl::raiseEvent()
	{
		FileUpdated(this, new EventArgs());

		SomethingChanged(this, 0);
	}

	void OneClickStreamControl::chkForceStream_CheckedChanged()
	{
		if (dynamic_cast<OneClickStream*>(input->getSelectedObject()) != 0)
			(static_cast<OneClickStream*>(input->getSelectedObject()))->setForcedStream(chkForceStream->Checked);

		QString strForceName = MeXgui::MainForm::Instance->getSettings()->getAppendToForcedStreams();
		if (strForceName.empty())
			return;

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (chkForceStream->Checked && !subName->Text->EndsWith(strForceName))
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if (!subName->Text->empty() && !subName->Text->EndsWith(" "))
				subName->Text += " ";
			subName->Text += strForceName;
		}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		else if (!chkForceStream->Checked && subName->Text->EndsWith(strForceName))
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimEnd' method:
			subName->Text = (subName->Text->substr(0, subName->Text->Length - strForceName.length()))->TrimEnd();
		}
	}

	void OneClickStreamControl::chkDefaultStream_CheckedChanged()
	{
		if (dynamic_cast<OneClickStream*>(input->getSelectedObject()) != 0)
			(static_cast<OneClickStream*>(input->getSelectedObject()))->setDefaultStream(chkDefaultStream->Checked);
	}

	void OneClickStreamControl::setFileName(const QString &strFileName)
	{
		input->AddCustomItem(strFileName);
		input->setSelectedObject(strFileName);
	}

	void OneClickStreamControl::input_SelectionChanged(object *sender, const QString &val)
	{
		// get language
		bool bFound = false;
		for (QMap<QString, QString>::const_iterator strLanguage = LanguageSelectionContainer::getLanguages().begin(); strLanguage != LanguageSelectionContainer::getLanguages().end(); ++strLanguage)
		{
			if (input->getSelectedText().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
			{
				SetLanguage(strLanguage->first);
				bFound = true;
				break;
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (!bFound && input->getSelectedText().ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".idx"))
		{
			QVector<SubtitleInfo*> subTracks;
			idxReader::readFileProperties(input->getSelectedText(), subTracks);
			if (subTracks.size() > 0)
			{
				SetLanguage(LanguageSelectionContainer::Short2FullLanguageName(subTracks[0]->getName()));
				bFound = true;
			}
		}
		if (!bFound && this->getSelectedItem() != 0 && this->getSelectedStreamIndex() > 0)
			SetLanguage(defaultLanguage);

		// get delay & track name
		delay->Value = 0;
		if (this->getSelectedItem() != 0 && this->getSelectedStreamIndex() > 0 && dynamic_cast<OneClickStream*>(this->getSelectedItem()->Tag) != 0)
		{
			delay->Value = (static_cast<OneClickStream*>(this->getSelectedItem()->Tag))->getDelay();
			subName->Text = (static_cast<OneClickStream*>(this->getSelectedItem()->Tag))->getName();
		}
		if (PrettyFormatting::getDelayAndCheck(input->getSelectedText()).HasValue)
			Nullable<int> tempVar = PrettyFormatting.getDelayAndCheck(input.getSelectedText());
			delay->Value = tempVar::HasValue ? tempVar : 0;

		if (showDefaultStream)
			chkDefaultStream->Checked = this->getSelectedStream()->getDefaultStream();

		if (showForceStream)
			chkForceStream->Checked = this->getSelectedStream()->getForcedStream();

		raiseEvent();
	}

	void OneClickStreamControl::encoderProfile_SelectedProfileChanged()
	{
		raiseEvent();
	}

	void OneClickStreamControl::cbEncodingMode_SelectedIndexChanged()
	{
		encoderProfile->Enabled = !cbEncodingMode->SelectedText->Equals("never");
		raiseEvent();
	}

	void OneClickStreamControl::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		UserControl::Dispose(disposing);
	}

	void OneClickStreamControl::InitializeComponent()
	{
		this->subName = new System::Windows::Forms::TextBox();
		this->SubNamelabel = new System::Windows::Forms::Label();
		this->subtitleLanguage = new System::Windows::Forms::ComboBox();
		this->subtitleLanguageLabel = new System::Windows::Forms::Label();
		this->subtitleInputLabel = new System::Windows::Forms::Label();
		this->delayLabel = new System::Windows::Forms::Label();
		this->delay = new System::Windows::Forms::NumericUpDown();
		this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
		this->label2 = new System::Windows::Forms::Label();
		this->cbEncodingMode = new System::Windows::Forms::ComboBox();
		this->encoderProfile = new MeXgui::core::gui::ConfigableProfilesControl();
		this->chkDefaultStream = new System::Windows::Forms::CheckBox();
		this->chkForceStream = new System::Windows::Forms::CheckBox();
		this->removeSubtitleTrack = new QPushButton;
		this->input = new MeXgui::core::gui::FileSCBox();
		this->label1 = new System::Windows::Forms::Label();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->delay))->BeginInit();
		this->tableLayoutPanel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// subName
		// 
		this->tableLayoutPanel1->SetColumnSpan(this->subName, 2);
		this->subName->Location = new System::Drawing::Point(232, 33);
		this->subName->MaxLength = 100;
		this->subName->Name = "subName";
		this->subName->Size = new System::Drawing::Size(168, 20);
		this->subName->TabIndex = 40;
		// 
		// SubNamelabel
		// 
		this->SubNamelabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->SubNamelabel->AutoSize = true;
		this->SubNamelabel->Location = new System::Drawing::Point(191, 38);
		this->SubNamelabel->Name = "SubNamelabel";
		this->SubNamelabel->Size = new System::Drawing::Size(35, 13);
		this->SubNamelabel->TabIndex = 39;
		this->SubNamelabel->Text = "Name";
		// 
		// subtitleLanguage
		// 
		this->subtitleLanguage->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->subtitleLanguage->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->subtitleLanguage->Location = new System::Drawing::Point(64, 34);
		this->subtitleLanguage->Name = "subtitleLanguage";
		this->subtitleLanguage->Size = new System::Drawing::Size(121, 21);
		this->subtitleLanguage->Sorted = true;
		this->subtitleLanguage->TabIndex = 37;
		// 
		// subtitleLanguageLabel
		// 
		this->subtitleLanguageLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->subtitleLanguageLabel->AutoSize = true;
		this->subtitleLanguageLabel->Location = new System::Drawing::Point(3, 38);
		this->subtitleLanguageLabel->Name = "subtitleLanguageLabel";
		this->subtitleLanguageLabel->Size = new System::Drawing::Size(55, 13);
		this->subtitleLanguageLabel->TabIndex = 36;
		this->subtitleLanguageLabel->Text = "Language";
		// 
		// subtitleInputLabel
		// 
		this->subtitleInputLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->subtitleInputLabel->AutoSize = true;
		this->subtitleInputLabel->Location = new System::Drawing::Point(3, 8);
		this->subtitleInputLabel->Name = "subtitleInputLabel";
		this->subtitleInputLabel->Size = new System::Drawing::Size(55, 13);
		this->subtitleInputLabel->TabIndex = 33;
		this->subtitleInputLabel->Text = "Input";
		// 
		// delayLabel
		// 
		this->delayLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->delayLabel->AutoSize = true;
		this->delayLabel->Location = new System::Drawing::Point(3, 68);
		this->delayLabel->Name = "delayLabel";
		this->delayLabel->Size = new System::Drawing::Size(55, 13);
		this->delayLabel->TabIndex = 43;
		this->delayLabel->Text = "Delay";
		// 
		// delay
		// 
		this->delay->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->delay->Location = new System::Drawing::Point(64, 65);
		this->delay->Maximum = decimal(new int[4] {2147483647, 0, 0, 0});
		this->delay->Minimum = decimal(new int[4] {-2147483648, 0, 0, -2147483648});
		this->delay->Name = "delay";
		this->delay->Size = new System::Drawing::Size(121, 20);
		this->delay->TabIndex = 42;
		// 
		// tableLayoutPanel1
		// 
		this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->tableLayoutPanel1->ColumnCount = 6;
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->Controls->Add(this->label2, 0, 4);
		this->tableLayoutPanel1->Controls->Add(this->cbEncodingMode, 1, 4);
		this->tableLayoutPanel1->Controls->Add(this->encoderProfile, 1, 3);
		this->tableLayoutPanel1->Controls->Add(this->delayLabel, 0, 2);
		this->tableLayoutPanel1->Controls->Add(this->subName, 3, 1);
		this->tableLayoutPanel1->Controls->Add(this->delay, 1, 2);
		this->tableLayoutPanel1->Controls->Add(this->SubNamelabel, 2, 1);
		this->tableLayoutPanel1->Controls->Add(this->subtitleLanguage, 1, 1);
		this->tableLayoutPanel1->Controls->Add(this->subtitleLanguageLabel, 0, 1);
		this->tableLayoutPanel1->Controls->Add(this->chkDefaultStream, 3, 2);
		this->tableLayoutPanel1->Controls->Add(this->chkForceStream, 4, 2);
		this->tableLayoutPanel1->Controls->Add(this->removeSubtitleTrack, 5, 1);
		this->tableLayoutPanel1->Controls->Add(this->input, 1, 0);
		this->tableLayoutPanel1->Controls->Add(this->subtitleInputLabel, 0, 0);
		this->tableLayoutPanel1->Controls->Add(this->label1, 0, 3);
		this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tableLayoutPanel1->Location = new System::Drawing::Point(0, 0);
		this->tableLayoutPanel1->Name = "tableLayoutPanel1";
		this->tableLayoutPanel1->RowCount = 5;
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30));
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20));
		this->tableLayoutPanel1->Size = new System::Drawing::Size(434, 150);
		this->tableLayoutPanel1->TabIndex = 44;
		// 
		// label2
		// 
		this->label2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->label2->AutoSize = true;
		this->label2->Location = new System::Drawing::Point(3, 128);
		this->label2->Name = "label2";
		this->label2->Size = new System::Drawing::Size(55, 13);
		this->label2->TabIndex = 51;
		this->label2->Text = "Encode";
		// 
		// cbEncodingMode
		// 
		this->cbEncodingMode->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->tableLayoutPanel1->SetColumnSpan(this->cbEncodingMode, 3);
		this->cbEncodingMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbEncodingMode->FormattingEnabled = true;
		this->cbEncodingMode->Location = new System::Drawing::Point(64, 123);
		this->cbEncodingMode->Name = "cbEncodingMode";
		this->cbEncodingMode->Size = new System::Drawing::Size(253, 21);
		this->cbEncodingMode->TabIndex = 49;
		this->cbEncodingMode->SelectedIndexChanged += new System::EventHandler(this, &OneClickStreamControl::cbEncodingMode_SelectedIndexChanged);
		// 
		// encoderProfile
		// 
		this->encoderProfile->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->tableLayoutPanel1->SetColumnSpan(this->encoderProfile, 5);
		this->encoderProfile->Location = new System::Drawing::Point(64, 93);
		this->encoderProfile->Name = "encoderProfile";
		this->encoderProfile->setProfileSet("Audio");
		this->encoderProfile->Size = new System::Drawing::Size(367, 22);
		this->encoderProfile->TabIndex = 48;
		this->encoderProfile->SelectedProfileChanged += new System::EventHandler(this, &OneClickStreamControl::encoderProfile_SelectedProfileChanged);
		// 
		// chkDefaultStream
		// 
		this->chkDefaultStream->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->chkDefaultStream->AutoSize = true;
		this->chkDefaultStream->Location = new System::Drawing::Point(232, 66);
		this->chkDefaultStream->Name = "chkDefaultStream";
		this->chkDefaultStream->Size = new System::Drawing::Size(85, 17);
		this->chkDefaultStream->TabIndex = 44;
		this->chkDefaultStream->Text = "default track";
		this->chkDefaultStream->UseVisualStyleBackColor = true;
		this->chkDefaultStream->Visible = false;
		this->chkDefaultStream->CheckedChanged += new System::EventHandler(this, &OneClickStreamControl::chkDefaultStream_CheckedChanged);
		// 
		// chkForceStream
		// 
		this->chkForceStream->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->chkForceStream->AutoSize = true;
		this->tableLayoutPanel1->SetColumnSpan(this->chkForceStream, 2);
		this->chkForceStream->Location = new System::Drawing::Point(323, 66);
		this->chkForceStream->Name = "chkForceStream";
		this->chkForceStream->Size = new System::Drawing::Size(83, 17);
		this->chkForceStream->TabIndex = 45;
		this->chkForceStream->Text = "forced track";
		this->chkForceStream->UseVisualStyleBackColor = true;
		this->chkForceStream->Visible = false;
		this->chkForceStream->CheckedChanged += new System::EventHandler(this, &OneClickStreamControl::chkForceStream_CheckedChanged);
		// 
		// removeSubtitleTrack
		// 
		this->removeSubtitleTrack->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->removeSubtitleTrack->Location = new System::Drawing::Point(407, 33);
		this->removeSubtitleTrack->Margin = new System::Windows::Forms::Padding(0);
		this->removeSubtitleTrack->Name = "removeSubtitleTrack";
		this->removeSubtitleTrack->Size = new System::Drawing::Size(22, 23);
		this->removeSubtitleTrack->TabIndex = 46;
		this->removeSubtitleTrack->Text = "X";
		// 
		// input
		// 
		this->input->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->tableLayoutPanel1->SetColumnSpan(this->input, 5);
		this->input->setFilter("All files (*.*)|*.*");
		this->input->Location = new System::Drawing::Point(64, 3);
		this->input->MaximumSize = new System::Drawing::Size(1000, 29);
		this->input->MinimumSize = new System::Drawing::Size(64, 29);
		this->input->Name = "input";
		this->input->setSelectedIndex(-1);
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete this->input->getSelectedItem();
		this->input->Size = new System::Drawing::Size(367, 29);
		this->input->TabIndex = 47;
		this->input->setType(MeXgui::core::gui::FileSCBox::OC_FILE);
		this->input->SelectionChanged += new MeXgui::StringChanged(this, &OneClickStreamControl::input_SelectionChanged);
		// 
		// label1
		// 
		this->label1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->label1->AutoSize = true;
		this->label1->Location = new System::Drawing::Point(3, 98);
		this->label1->Name = "label1";
		this->label1->Size = new System::Drawing::Size(55, 13);
		this->label1->TabIndex = 50;
		this->label1->Text = "Encoder";
		// 
		// OneClickStreamControl
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->Controls->Add(this->tableLayoutPanel1);
		this->Name = "OneClickStreamControl";
		this->Size = new System::Drawing::Size(434, 150);
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->delay))->EndInit();
		this->tableLayoutPanel1->ResumeLayout(false);
		this->tableLayoutPanel1->PerformLayout();
		this->ResumeLayout(false);

	}

	void OneClickStreamControl::InitializeInstanceFields()
	{
		delete components;
	}
}
