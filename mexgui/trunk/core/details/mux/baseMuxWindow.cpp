#include "baseMuxWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::details::mux;
using namespace MeGUI::core::util;

namespace MeGUI
{

	baseMuxWindow::baseMuxWindow()
	{
		//
		// Required for Windows Form Designer support
		//
		InitializeComponent();

		audioTracks = std::vector<MuxStreamControl*>();
		audioTracks.push_back(muxStreamControl2);
		subtitleTracks = std::vector<MuxStreamControl*>();
		subtitleTracks.push_back(muxStreamControl1);

		splitting->setMinimumFileSize(FileSize(MB, 1));
		subtitleTracks[0]->input->FileSelected += new MeGUI::FileBarEventHandler(this, &baseMuxWindow::Subtitle_FileSelected);
		audioTracks[0]->input->FileSelected += new MeGUI::FileBarEventHandler(this, &baseMuxWindow::Audio_FileSelected);
	}

	baseMuxWindow::baseMuxWindow(MainForm *mainForm, IMuxing *muxer)
	{
		this->mainForm = mainForm;
		this->settings = mainForm->getSettings();
		this->muxer = muxer;

		muxProvider = mainForm->getMuxProvider();
		cbType->Items->Add("Standard");
		cbType->Items->AddRange(muxProvider->GetSupportedDevices(static_cast<ContainerType*>(cbContainer->SelectedItem)).ToArray());
		cbType->SelectedIndex = 0;
	}

	void baseMuxWindow::Dispose(bool disposing)
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

	void baseMuxWindow::setConfig(const std::string &videoInput, const std::string &videoName, Nullable<decimal> framerate, MuxStream audioStreams[], MuxStream subtitleStreams[], const std::string &chapterFile, const std::string &output, Nullable<FileSize> splitSize, Nullable<Dar> dar, const std::string &deviceType)
	{
		this->dar = dar;
		vInput->setFilename(videoInput);
		fps->setValue(framerate);
		this->videoName->Text = videoName;

		int index = 0;
		for (MeGUI::core::details::MuxStream::const_iterator stream = audioStreams->begin(); stream != audioStreams->end(); ++stream)
		{
			if (audioTracks.size() == index)
				AudioAddTrack();
			audioTracks[index]->setStream(*stream);
			index++;
		}

		index = 0;
		for (MeGUI::core::details::MuxStream::const_iterator stream = subtitleStreams->begin(); stream != subtitleStreams->end(); ++stream)
		{
			if (subtitleTracks.size() == index)
				SubtitleAddTrack();
			subtitleTracks[index]->setStream(*stream);
			index++;
		}

		chapters->setFilename(chapterFile);
		this->output->setFilename(output);
		this->splitting->setValue(splitSize);
		this->muxButton->Text = "Update";
		this->chkCloseOnQueue->Visible = false;
		this->cbType->Text = deviceType;
		checkIO();
	}

	void baseMuxWindow::getAdditionalStreams(MuxStream aStreams[], MuxStream sStreams[], std::string &chapterFile)
	{
		aStreams = getStreams(audioTracks);
		sStreams = getStreams(subtitleTracks);
		chapterFile = chapters->getFilename();
	}

	MuxStream *baseMuxWindow::getStreams(std::vector<MuxStreamControl*> &controls)
	{
		std::vector<MuxStream*> streams = std::vector<MuxStream*>();
		for (std::vector<MuxStreamControl*>::const_iterator t = controls.begin(); t != controls.end(); ++t)
		{
			if ((*t)->getStream() != 0)
				streams.push_back((*t)->getStream());
		}
		return streams.ToArray();
	}

	void baseMuxWindow::InitializeComponent()
	{
		this->components = new System::ComponentModel::Container();
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(baseMuxWindow::typeid);
		this->muxButton = new System::Windows::Forms::Button();
		this->videoGroupbox = new System::Windows::Forms::GroupBox();
		this->tableLayoutPanel2 = new System::Windows::Forms::TableLayoutPanel();
		this->videoInputLabel = new System::Windows::Forms::Label();
		this->videoName = new System::Windows::Forms::TextBox();
		this->fps = new MeGUI::core::gui::FPSChooser();
		this->videoNameLabel = new System::Windows::Forms::Label();
		this->vInput = new MeGUI::FileBar();
		this->MuxFPSLabel = new System::Windows::Forms::Label();
		this->removeVideoTrack = new System::Windows::Forms::Button();
		this->chaptersGroupbox = new System::Windows::Forms::GroupBox();
		this->tableLayoutPanel3 = new System::Windows::Forms::TableLayoutPanel();
		this->chaptersInputLabel = new System::Windows::Forms::Label();
		this->chapters = new MeGUI::FileBar();
		this->outputGroupbox = new System::Windows::Forms::GroupBox();
		this->tableLayoutPanel4 = new System::Windows::Forms::TableLayoutPanel();
		this->lbContainer = new System::Windows::Forms::Label();
		this->label1 = new System::Windows::Forms::Label();
		this->muxedOutputLabel = new System::Windows::Forms::Label();
		this->splitting = new MeGUI::core::gui::TargetSizeSCBox();
		this->splittingLabel = new System::Windows::Forms::Label();
		this->output = new MeGUI::FileBar();
		this->cbType = new System::Windows::Forms::ComboBox();
		this->cbContainer = new System::Windows::Forms::ComboBox();
		this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
		this->saveFileDialog = new System::Windows::Forms::SaveFileDialog();
		this->audioPanel = new System::Windows::Forms::Panel();
		this->audioMenu = new System::Windows::Forms::ContextMenuStrip(this->components);
		this->audioAddTrack = new System::Windows::Forms::ToolStripMenuItem();
		this->audioRemoveTrack = new System::Windows::Forms::ToolStripMenuItem();
		this->audio = new System::Windows::Forms::TabControl();
		this->audioPage1 = new System::Windows::Forms::TabPage();
		this->muxStreamControl2 = new MeGUI::core::details::mux::MuxStreamControl();
		this->subtitleMenu = new System::Windows::Forms::ContextMenuStrip(this->components);
		this->subtitleAddTrack = new System::Windows::Forms::ToolStripMenuItem();
		this->subtitleRemoveTrack = new System::Windows::Forms::ToolStripMenuItem();
		this->subtitlePanel = new System::Windows::Forms::Panel();
		this->subtitles = new System::Windows::Forms::TabControl();
		this->subPage1 = new System::Windows::Forms::TabPage();
		this->muxStreamControl1 = new MeGUI::core::details::mux::MuxStreamControl();
		this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
		this->helpButton1 = new MeGUI::core::gui::HelpButton();
		this->chkCloseOnQueue = new System::Windows::Forms::CheckBox();
		this->videoGroupbox->SuspendLayout();
		this->tableLayoutPanel2->SuspendLayout();
		this->chaptersGroupbox->SuspendLayout();
		this->tableLayoutPanel3->SuspendLayout();
		this->outputGroupbox->SuspendLayout();
		this->tableLayoutPanel4->SuspendLayout();
		this->audioPanel->SuspendLayout();
		this->audioMenu->SuspendLayout();
		this->audio->SuspendLayout();
		this->audioPage1->SuspendLayout();
		this->subtitleMenu->SuspendLayout();
		this->subtitlePanel->SuspendLayout();
		this->subtitles->SuspendLayout();
		this->subPage1->SuspendLayout();
		this->tableLayoutPanel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// muxButton
		// 
		this->muxButton->Location = new System::Drawing::Point(376, 568);
		this->muxButton->Margin = new System::Windows::Forms::Padding(12, 9, 12, 9);
		this->muxButton->Name = "muxButton";
		this->muxButton->Size = new System::Drawing::Size(56, 23);
		this->muxButton->TabIndex = 5;
		this->muxButton->Text = "&Queue";
		// 
		// videoGroupbox
		// 
		this->videoGroupbox->AutoSize = true;
		this->tableLayoutPanel1->SetColumnSpan(this->videoGroupbox, 4);
		this->videoGroupbox->Controls->Add(this->tableLayoutPanel2);
		this->videoGroupbox->Location = new System::Drawing::Point(3, 3);
		this->videoGroupbox->Name = "videoGroupbox";
		this->videoGroupbox->Size = new System::Drawing::Size(438, 90);
		this->videoGroupbox->TabIndex = 0;
		this->videoGroupbox->TabStop = false;
		this->videoGroupbox->Text = "Video";
		// 
		// tableLayoutPanel2
		// 
		this->tableLayoutPanel2->AutoSize = true;
		this->tableLayoutPanel2->ColumnCount = 5;
		this->tableLayoutPanel2->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel2->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 48.99329F));
		this->tableLayoutPanel2->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel2->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 51.00671F));
		this->tableLayoutPanel2->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 35));
		this->tableLayoutPanel2->Controls->Add(this->videoInputLabel, 0, 0);
		this->tableLayoutPanel2->Controls->Add(this->videoName, 3, 1);
		this->tableLayoutPanel2->Controls->Add(this->fps, 1, 1);
		this->tableLayoutPanel2->Controls->Add(this->videoNameLabel, 2, 1);
		this->tableLayoutPanel2->Controls->Add(this->vInput, 1, 0);
		this->tableLayoutPanel2->Controls->Add(this->MuxFPSLabel, 0, 1);
		this->tableLayoutPanel2->Controls->Add(this->removeVideoTrack, 4, 1);
		this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tableLayoutPanel2->Location = new System::Drawing::Point(3, 17);
		this->tableLayoutPanel2->Name = "tableLayoutPanel2";
		this->tableLayoutPanel2->RowCount = 2;
		this->tableLayoutPanel2->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50));
		this->tableLayoutPanel2->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50));
		this->tableLayoutPanel2->Size = new System::Drawing::Size(432, 70);
		this->tableLayoutPanel2->TabIndex = 0;
		// 
		// videoInputLabel
		// 
		this->videoInputLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->videoInputLabel->AutoSize = true;
		this->videoInputLabel->Location = new System::Drawing::Point(3, 11);
		this->videoInputLabel->Name = "videoInputLabel";
		this->videoInputLabel->Size = new System::Drawing::Size(62, 13);
		this->videoInputLabel->TabIndex = 0;
		this->videoInputLabel->Text = "Video Input";
		// 
		// videoName
		// 
		this->videoName->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->videoName->Location = new System::Drawing::Point(249, 42);
		this->videoName->MaxLength = 100;
		this->videoName->Name = "videoName";
		this->videoName->Size = new System::Drawing::Size(144, 21);
		this->videoName->TabIndex = 5;
		// 
		// fps
		// 
		this->fps->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->fps->Location = new System::Drawing::Point(71, 38);
		this->fps->MaximumSize = new System::Drawing::Size(1000, 29);
		this->fps->MinimumSize = new System::Drawing::Size(64, 29);
		this->fps->Name = "fps";
		this->fps->setNullString("Not set");
		this->fps->setSelectedIndex(0);
		this->fps->Size = new System::Drawing::Size(138, 29);
		this->fps->TabIndex = 3;
		this->fps->SelectionChanged += new MeGUI::StringChanged(this, &baseMuxWindow::fps_SelectionChanged);
		// 
		// videoNameLabel
		// 
		this->videoNameLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->videoNameLabel->AutoSize = true;
		this->videoNameLabel->Location = new System::Drawing::Point(212, 46);
		this->videoNameLabel->Margin = new System::Windows::Forms::Padding(0);
		this->videoNameLabel->Name = "videoNameLabel";
		this->videoNameLabel->Size = new System::Drawing::Size(34, 13);
		this->videoNameLabel->TabIndex = 4;
		this->videoNameLabel->Text = "Name";
		// 
		// vInput
		// 
		this->vInput->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->tableLayoutPanel2->SetColumnSpan(this->vInput, 4);
		this->vInput->setFilename("");
		this->vInput->setFilter("");
		this->vInput->setFilterIndex(0);
		this->vInput->setFolderMode(false);
		this->vInput->Location = new System::Drawing::Point(71, 4);
		this->vInput->Margin = new System::Windows::Forms::Padding(3, 3, 6, 3);
		this->vInput->Name = "vInput";
		this->vInput->setReadOnly(true);
		this->vInput->setSaveMode(false);
		this->vInput->Size = new System::Drawing::Size(355, 26);
		this->vInput->TabIndex = 1;
		this->vInput->setTitle("");
		this->vInput->FileSelected += new MeGUI::FileBarEventHandler(this, &baseMuxWindow::vInput_FileSelected);
		// 
		// MuxFPSLabel
		// 
		this->MuxFPSLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->MuxFPSLabel->AutoSize = true;
		this->MuxFPSLabel->Location = new System::Drawing::Point(3, 46);
		this->MuxFPSLabel->Name = "MuxFPSLabel";
		this->MuxFPSLabel->Size = new System::Drawing::Size(25, 13);
		this->MuxFPSLabel->TabIndex = 2;
		this->MuxFPSLabel->Text = "FPS";
		// 
		// removeVideoTrack
		// 
		this->removeVideoTrack->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->removeVideoTrack->Location = new System::Drawing::Point(402, 41);
		this->removeVideoTrack->Name = "removeVideoTrack";
		this->removeVideoTrack->Size = new System::Drawing::Size(24, 23);
		this->removeVideoTrack->TabIndex = 39;
		this->removeVideoTrack->Text = "X";
		this->removeVideoTrack->Click += new System::EventHandler(this, &baseMuxWindow::removeVideoTrack_Click);
		// 
		// chaptersGroupbox
		// 
		this->tableLayoutPanel1->SetColumnSpan(this->chaptersGroupbox, 4);
		this->chaptersGroupbox->Controls->Add(this->tableLayoutPanel3);
		this->chaptersGroupbox->Dock = System::Windows::Forms::DockStyle::Fill;
		this->chaptersGroupbox->Location = new System::Drawing::Point(3, 361);
		this->chaptersGroupbox->Name = "chaptersGroupbox";
		this->chaptersGroupbox->Size = new System::Drawing::Size(438, 48);
		this->chaptersGroupbox->TabIndex = 3;
		this->chaptersGroupbox->TabStop = false;
		this->chaptersGroupbox->Text = "Chapter";
		// 
		// tableLayoutPanel3
		// 
		this->tableLayoutPanel3->ColumnCount = 2;
		this->tableLayoutPanel3->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel3->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
		this->tableLayoutPanel3->Controls->Add(this->chaptersInputLabel, 0, 0);
		this->tableLayoutPanel3->Controls->Add(this->chapters, 1, 0);
		this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tableLayoutPanel3->Location = new System::Drawing::Point(3, 17);
		this->tableLayoutPanel3->Name = "tableLayoutPanel3";
		this->tableLayoutPanel3->RowCount = 1;
		this->tableLayoutPanel3->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100));
		this->tableLayoutPanel3->Size = new System::Drawing::Size(432, 28);
		this->tableLayoutPanel3->TabIndex = 0;
		// 
		// chaptersInputLabel
		// 
		this->chaptersInputLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->chaptersInputLabel->AutoSize = true;
		this->chaptersInputLabel->Location = new System::Drawing::Point(3, 7);
		this->chaptersInputLabel->Name = "chaptersInputLabel";
		this->chaptersInputLabel->Size = new System::Drawing::Size(70, 13);
		this->chaptersInputLabel->TabIndex = 0;
		this->chaptersInputLabel->Text = "Chapters File";
		// 
		// chapters
		// 
		this->chapters->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->chapters->setFilename("");
		this->chapters->setFilter("");
		this->chapters->setFilterIndex(0);
		this->chapters->setFolderMode(false);
		this->chapters->Location = new System::Drawing::Point(79, 3);
		this->chapters->Name = "chapters";
		this->chapters->setReadOnly(true);
		this->chapters->setSaveMode(false);
		this->chapters->Size = new System::Drawing::Size(350, 22);
		this->chapters->TabIndex = 1;
		this->chapters->setTitle("");
		this->chapters->FileSelected += new MeGUI::FileBarEventHandler(this, &baseMuxWindow::chapters_FileSelected);
		// 
		// outputGroupbox
		// 
		this->outputGroupbox->AutoSize = true;
		this->tableLayoutPanel1->SetColumnSpan(this->outputGroupbox, 4);
		this->outputGroupbox->Controls->Add(this->tableLayoutPanel4);
		this->outputGroupbox->Dock = System::Windows::Forms::DockStyle::Fill;
		this->outputGroupbox->Location = new System::Drawing::Point(3, 415);
		this->outputGroupbox->Name = "outputGroupbox";
		this->outputGroupbox->Size = new System::Drawing::Size(438, 141);
		this->outputGroupbox->TabIndex = 4;
		this->outputGroupbox->TabStop = false;
		this->outputGroupbox->Text = "Output";
		// 
		// tableLayoutPanel4
		// 
		this->tableLayoutPanel4->AutoSize = true;
		this->tableLayoutPanel4->ColumnCount = 2;
		this->tableLayoutPanel4->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel4->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
		this->tableLayoutPanel4->Controls->Add(this->lbContainer, 0, 4);
		this->tableLayoutPanel4->Controls->Add(this->label1, 0, 2);
		this->tableLayoutPanel4->Controls->Add(this->muxedOutputLabel, 0, 0);
		this->tableLayoutPanel4->Controls->Add(this->splitting, 1, 1);
		this->tableLayoutPanel4->Controls->Add(this->splittingLabel, 0, 1);
		this->tableLayoutPanel4->Controls->Add(this->output, 1, 0);
		this->tableLayoutPanel4->Controls->Add(this->cbType, 1, 2);
		this->tableLayoutPanel4->Controls->Add(this->cbContainer, 1, 4);
		this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tableLayoutPanel4->Location = new System::Drawing::Point(3, 17);
		this->tableLayoutPanel4->Name = "tableLayoutPanel4";
		this->tableLayoutPanel4->RowCount = 5;
		this->tableLayoutPanel4->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel4->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel4->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel4->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel4->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel4->Size = new System::Drawing::Size(432, 121);
		this->tableLayoutPanel4->TabIndex = 0;
		// 
		// lbContainer
		// 
		this->lbContainer->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->lbContainer->AutoSize = true;
		this->lbContainer->Location = new System::Drawing::Point(3, 101);
		this->lbContainer->Name = "lbContainer";
		this->lbContainer->Size = new System::Drawing::Size(54, 13);
		this->lbContainer->TabIndex = 11;
		this->lbContainer->Text = "Container";
		this->lbContainer->Visible = false;
		// 
		// label1
		// 
		this->label1->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->label1->AutoSize = true;
		this->label1->Location = new System::Drawing::Point(3, 74);
		this->label1->Name = "label1";
		this->label1->Size = new System::Drawing::Size(66, 13);
		this->label1->TabIndex = 9;
		this->label1->Text = "Device Type";
		// 
		// muxedOutputLabel
		// 
		this->muxedOutputLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->muxedOutputLabel->AutoSize = true;
		this->muxedOutputLabel->Location = new System::Drawing::Point(3, 9);
		this->muxedOutputLabel->Name = "muxedOutputLabel";
		this->muxedOutputLabel->Size = new System::Drawing::Size(76, 13);
		this->muxedOutputLabel->TabIndex = 0;
		this->muxedOutputLabel->Text = "Muxed Output";
		// 
		// splitting
		// 
		this->splitting->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->splitting->setCustomSizes(new MeGUI::core::util::FileSize[0]);
		this->splitting->Location = new System::Drawing::Point(85, 35);
		this->splitting->MaximumSize = new System::Drawing::Size(1000, 29);
		this->splitting->MinimumSize = new System::Drawing::Size(64, 29);
		this->splitting->Name = "splitting";
		this->splitting->setNullString("No splitting");
		this->splitting->setSelectedIndex(0);
		this->splitting->Size = new System::Drawing::Size(344, 29);
		this->splitting->TabIndex = 3;
		// 
		// splittingLabel
		// 
		this->splittingLabel->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->splittingLabel->AutoSize = true;
		this->splittingLabel->Location = new System::Drawing::Point(3, 43);
		this->splittingLabel->Name = "splittingLabel";
		this->splittingLabel->Size = new System::Drawing::Size(45, 13);
		this->splittingLabel->TabIndex = 2;
		this->splittingLabel->Text = "Splitting";
		// 
		// output
		// 
		this->output->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->output->setFilename("");
		this->output->setFilter("");
		this->output->setFilterIndex(0);
		this->output->setFolderMode(false);
		this->output->Location = new System::Drawing::Point(85, 3);
		this->output->Name = "output";
		this->output->setReadOnly(false);
		this->output->setSaveMode(true);
		this->output->Size = new System::Drawing::Size(344, 26);
		this->output->TabIndex = 1;
		this->output->setTitle("");
		this->output->Click += new System::EventHandler(this, &baseMuxWindow::output_Click);
		// 
		// cbType
		// 
		this->cbType->Dock = System::Windows::Forms::DockStyle::Left;
		this->cbType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbType->FormattingEnabled = true;
		this->cbType->Location = new System::Drawing::Point(85, 70);
		this->cbType->Name = "cbType";
		this->cbType->Size = new System::Drawing::Size(121, 21);
		this->cbType->TabIndex = 7;
		this->cbType->SelectedIndexChanged += new System::EventHandler(this, &baseMuxWindow::cbType_SelectedIndexChanged);
		// 
		// cbContainer
		// 
		this->cbContainer->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbContainer->FormattingEnabled = true;
		this->cbContainer->Location = new System::Drawing::Point(85, 97);
		this->cbContainer->Name = "cbContainer";
		this->cbContainer->Size = new System::Drawing::Size(121, 21);
		this->cbContainer->TabIndex = 10;
		this->cbContainer->Visible = false;
		this->cbContainer->SelectedIndexChanged += new System::EventHandler(this, &baseMuxWindow::cbContainer_SelectedIndexChanged);
		// 
		// audioPanel
		// 
		this->tableLayoutPanel1->SetColumnSpan(this->audioPanel, 4);
		this->audioPanel->ContextMenuStrip = this->audioMenu;
		this->audioPanel->Controls->Add(this->audio);
		this->audioPanel->Dock = System::Windows::Forms::DockStyle::Fill;
		this->audioPanel->Location = new System::Drawing::Point(3, 99);
		this->audioPanel->Name = "audioPanel";
		this->audioPanel->Size = new System::Drawing::Size(438, 125);
		this->audioPanel->TabIndex = 1;
		// 
		// audioMenu
		// 
		this->audioMenu->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->audioAddTrack, this->audioRemoveTrack});
		this->audioMenu->Name = "audioMenu";
		this->audioMenu->Size = new System::Drawing::Size(147, 48);
		this->audioMenu->Opening += new System::ComponentModel::CancelEventHandler(this, &baseMuxWindow::audioMenu_Opening);
		// 
		// audioAddTrack
		// 
		this->audioAddTrack->Name = "audioAddTrack";
		this->audioAddTrack->Size = new System::Drawing::Size(146, 22);
		this->audioAddTrack->Text = "Add track";
		this->audioAddTrack->Click += new System::EventHandler(this, &baseMuxWindow::audioAddTrack_Click);
		// 
		// audioRemoveTrack
		// 
		this->audioRemoveTrack->Name = "audioRemoveTrack";
		this->audioRemoveTrack->Size = new System::Drawing::Size(146, 22);
		this->audioRemoveTrack->Text = "Remove track";
		this->audioRemoveTrack->Click += new System::EventHandler(this, &baseMuxWindow::audioRemoveTrack_Click);
		// 
		// audio
		// 
		this->audio->Controls->Add(this->audioPage1);
		this->audio->Dock = System::Windows::Forms::DockStyle::Fill;
		this->audio->Location = new System::Drawing::Point(0, 0);
		this->audio->Name = "audio";
		this->audio->SelectedIndex = 0;
		this->audio->Size = new System::Drawing::Size(438, 125);
		this->audio->TabIndex = 0;
		// 
		// audioPage1
		// 
		this->audioPage1->Controls->Add(this->muxStreamControl2);
		this->audioPage1->Location = new System::Drawing::Point(4, 22);
		this->audioPage1->Name = "audioPage1";
		this->audioPage1->Padding = new System::Windows::Forms::Padding(3);
		this->audioPage1->Size = new System::Drawing::Size(430, 99);
		this->audioPage1->TabIndex = 0;
		this->audioPage1->Text = "Audio 1";
		this->audioPage1->UseVisualStyleBackColor = true;
		// 
		// muxStreamControl2
		// 
		this->muxStreamControl2->Dock = System::Windows::Forms::DockStyle::Fill;
		this->muxStreamControl2->setFilter("");
		this->muxStreamControl2->Location = new System::Drawing::Point(3, 3);
		this->muxStreamControl2->Name = "muxStreamControl2";
		this->muxStreamControl2->setShowDefaultSubtitleStream(false);
		this->muxStreamControl2->setShowDelay(true);
		this->muxStreamControl2->setShowForceSubtitleStream(false);
		this->muxStreamControl2->Size = new System::Drawing::Size(424, 93);
		this->muxStreamControl2->TabIndex = 0;
		this->muxStreamControl2->FileUpdated += new System::EventHandler(this, &baseMuxWindow::muxStreamControl2_FileUpdated);
		// 
		// subtitleMenu
		// 
		this->subtitleMenu->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->subtitleAddTrack, this->subtitleRemoveTrack});
		this->subtitleMenu->Name = "subtitleMenu";
		this->subtitleMenu->Size = new System::Drawing::Size(147, 48);
		this->subtitleMenu->Opening += new System::ComponentModel::CancelEventHandler(this, &baseMuxWindow::subtitleMenu_Opening);
		// 
		// subtitleAddTrack
		// 
		this->subtitleAddTrack->Name = "subtitleAddTrack";
		this->subtitleAddTrack->Size = new System::Drawing::Size(146, 22);
		this->subtitleAddTrack->Text = "Add track";
		this->subtitleAddTrack->Click += new System::EventHandler(this, &baseMuxWindow::subtitleAddTrack_Click);
		// 
		// subtitleRemoveTrack
		// 
		this->subtitleRemoveTrack->Name = "subtitleRemoveTrack";
		this->subtitleRemoveTrack->Size = new System::Drawing::Size(146, 22);
		this->subtitleRemoveTrack->Text = "Remove track";
		this->subtitleRemoveTrack->Click += new System::EventHandler(this, &baseMuxWindow::subtitleRemoveTrack_Click);
		// 
		// subtitlePanel
		// 
		this->tableLayoutPanel1->SetColumnSpan(this->subtitlePanel, 4);
		this->subtitlePanel->ContextMenuStrip = this->subtitleMenu;
		this->subtitlePanel->Controls->Add(this->subtitles);
		this->subtitlePanel->Dock = System::Windows::Forms::DockStyle::Fill;
		this->subtitlePanel->Location = new System::Drawing::Point(3, 230);
		this->subtitlePanel->Name = "subtitlePanel";
		this->subtitlePanel->Size = new System::Drawing::Size(438, 125);
		this->subtitlePanel->TabIndex = 2;
		// 
		// subtitles
		// 
		this->subtitles->Controls->Add(this->subPage1);
		this->subtitles->Dock = System::Windows::Forms::DockStyle::Fill;
		this->subtitles->Location = new System::Drawing::Point(0, 0);
		this->subtitles->Name = "subtitles";
		this->subtitles->SelectedIndex = 0;
		this->subtitles->Size = new System::Drawing::Size(438, 125);
		this->subtitles->TabIndex = 0;
		// 
		// subPage1
		// 
		this->subPage1->Controls->Add(this->muxStreamControl1);
		this->subPage1->Location = new System::Drawing::Point(4, 22);
		this->subPage1->Name = "subPage1";
		this->subPage1->Padding = new System::Windows::Forms::Padding(3);
		this->subPage1->Size = new System::Drawing::Size(430, 99);
		this->subPage1->TabIndex = 0;
		this->subPage1->Text = "Subtitle 1";
		this->subPage1->UseVisualStyleBackColor = true;
		// 
		// muxStreamControl1
		// 
		this->muxStreamControl1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->muxStreamControl1->setFilter("");
		this->muxStreamControl1->Location = new System::Drawing::Point(3, 3);
		this->muxStreamControl1->Name = "muxStreamControl1";
		this->muxStreamControl1->setShowDefaultSubtitleStream(false);
		this->muxStreamControl1->setShowDelay(false);
		this->muxStreamControl1->setShowForceSubtitleStream(false);
		this->muxStreamControl1->Size = new System::Drawing::Size(424, 93);
		this->muxStreamControl1->TabIndex = 0;
		this->muxStreamControl1->FileUpdated += new System::EventHandler(this, &baseMuxWindow::muxStreamControl1_FileUpdated);
		// 
		// tableLayoutPanel1
		// 
		this->tableLayoutPanel1->AutoSize = true;
		this->tableLayoutPanel1->ColumnCount = 4;
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->Controls->Add(this->helpButton1, 0, 5);
		this->tableLayoutPanel1->Controls->Add(this->audioPanel, 0, 1);
		this->tableLayoutPanel1->Controls->Add(this->subtitlePanel, 0, 2);
		this->tableLayoutPanel1->Controls->Add(this->chaptersGroupbox, 0, 3);
		this->tableLayoutPanel1->Controls->Add(this->outputGroupbox, 0, 4);
		this->tableLayoutPanel1->Controls->Add(this->videoGroupbox, 0, 0);
		this->tableLayoutPanel1->Controls->Add(this->chkCloseOnQueue, 2, 5);
		this->tableLayoutPanel1->Controls->Add(this->muxButton, 3, 5);
		this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tableLayoutPanel1->Location = new System::Drawing::Point(0, 0);
		this->tableLayoutPanel1->Name = "tableLayoutPanel1";
		this->tableLayoutPanel1->RowCount = 6;
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel1->Size = new System::Drawing::Size(444, 597);
		this->tableLayoutPanel1->TabIndex = 0;
		// 
		// helpButton1
		// 
		this->helpButton1->setArticleName("Manual mux window");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(12, 568);
		this->helpButton1->Margin = new System::Windows::Forms::Padding(12, 9, 12, 9);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(35, 23);
		this->helpButton1->TabIndex = 8;
		// 
		// chkCloseOnQueue
		// 
		this->chkCloseOnQueue->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left)));
		this->chkCloseOnQueue->AutoSize = true;
		this->chkCloseOnQueue->Checked = true;
		this->chkCloseOnQueue->CheckState = System::Windows::Forms::CheckState::Checked;
		this->chkCloseOnQueue->Location = new System::Drawing::Point(281, 568);
		this->chkCloseOnQueue->Margin = new System::Windows::Forms::Padding(12, 9, 12, 9);
		this->chkCloseOnQueue->Name = "chkCloseOnQueue";
		this->chkCloseOnQueue->Size = new System::Drawing::Size(71, 23);
		this->chkCloseOnQueue->TabIndex = 9;
		this->chkCloseOnQueue->Text = "and close";
		this->chkCloseOnQueue->UseVisualStyleBackColor = true;
		// 
		// baseMuxWindow
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->ClientSize = new System::Drawing::Size(444, 597);
		this->Controls->Add(this->tableLayoutPanel1);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = "baseMuxWindow";
		this->Text = "Mux";
		this->videoGroupbox->ResumeLayout(false);
		this->videoGroupbox->PerformLayout();
		this->tableLayoutPanel2->ResumeLayout(false);
		this->tableLayoutPanel2->PerformLayout();
		this->chaptersGroupbox->ResumeLayout(false);
		this->tableLayoutPanel3->ResumeLayout(false);
		this->tableLayoutPanel3->PerformLayout();
		this->outputGroupbox->ResumeLayout(false);
		this->outputGroupbox->PerformLayout();
		this->tableLayoutPanel4->ResumeLayout(false);
		this->tableLayoutPanel4->PerformLayout();
		this->audioPanel->ResumeLayout(false);
		this->audioMenu->ResumeLayout(false);
		this->audio->ResumeLayout(false);
		this->audioPage1->ResumeLayout(false);
		this->subtitleMenu->ResumeLayout(false);
		this->subtitlePanel->ResumeLayout(false);
		this->subtitles->ResumeLayout(false);
		this->subPage1->ResumeLayout(false);
		this->tableLayoutPanel1->ResumeLayout(false);
		this->tableLayoutPanel1->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void baseMuxWindow::Subtitle_FileSelected(object *sender, System::EventArgs *e)
	{
		for (std::vector<MuxStreamControl*>::const_iterator oTrack = subtitleTracks.begin(); oTrack != subtitleTracks.end(); ++oTrack)
		{
			if ((*oTrack)->input->Filename->empty())
				return;
		}
		SubtitleAddTrack();
	}

	void baseMuxWindow::Audio_FileSelected(object *sender, System::EventArgs *e)
	{
		for (std::vector<MuxStreamControl*>::const_iterator oTrack = audioTracks.begin(); oTrack != audioTracks.end(); ++oTrack)
		{
			if ((*oTrack)->input->Filename->empty())
				return;
		}
		AudioAddTrack();
	}

	void baseMuxWindow::checkIO()
	{
		if (vInput->getFilename().empty())
		{
			muxButton->DialogResult = System::Windows::Forms::DialogResult::None;
			return;
		}
		else if (output->getFilename().empty())
		{
			muxButton->DialogResult = System::Windows::Forms::DialogResult::None;
			return;
		}
		else if (MainForm::verifyOutputFile(output->getFilename()) != "")
		{
			muxButton->DialogResult = System::Windows::Forms::DialogResult::None;
			return;
		}
		else if (!fpgetValue()ue::HasValue && isFPSRequired())
		{
			muxButton->DialogResult = System::Windows::Forms::DialogResult::None;
			return;
		}
		else
			muxButton->DialogResult = System::Windows::Forms::DialogResult::OK;
	}

	void baseMuxWindow::chkDefaultStream_CheckedChanged(object *sender, EventArgs *e)
	{
		if ((static_cast<CheckBox*>(sender))->Checked == false)
			return;

		for (std::vector<MuxStreamControl*>::const_iterator oTrack = subtitleTracks.begin(); oTrack != subtitleTracks.end(); ++oTrack)
		{
			if (sender != (*oTrack)->chkDefaultStream && (*oTrack)->chkDefaultStream->Checked == true)
				(*oTrack)->chkDefaultStream->Checked = false;
		}
	}

	void baseMuxWindow::splitSize_KeyPress(object *sender, System::Windows::Forms::KeyPressEventArgs *e)
	{
		if (!isdigit(e->KeyChar) && static_cast<int>(Keys::Back) != static_cast<int>(e->KeyChar))
			e->Handled = true;
	}

	bool baseMuxWindow::isFPSRequired()
	{
		try
		{
			if (vInput->getFilename().length() > 0)
				return (VideoUtil::guessVideoType(vInput->getFilename())->getContainerType() == 0);
			return true;
		}
		catch (NullReferenceException *e1) // This will throw if it can't guess the video type
		{
			return true;
		}
	}

	void baseMuxWindow::vInput_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		try
		{
			fps->setValue(static_cast<decimal>((new MediaInfoFile(vInput->getFilename()))->getVideoInfo()->FPS));
		}
		catch (std::exception &e1)
		{
			fps->setValue(Nullable<decimal>());
		}

		if (output->getFilename().empty())
			chooseOutputFilename();

		fileUpdated();
		checkIO();
	}

	void baseMuxWindow::ChangeOutputExtension()
	{
	}

	void baseMuxWindow::chooseOutputFilename()
	{
		std::string projectPath;
		std::string fileNameNoPath = Path::GetFileName(vInput->getFilename());
		if ((projectPath = mainForm->getSettings()->getDefaultOutputDir())->empty())
			projectPath = Path::GetDirectoryName(vInput->getFilename());
		output->setFilename(FileUtil::AddToFileName(Path::Combine(projectPath, fileNameNoPath), "-muxed"));
		ChangeOutputExtension();
	}

	void baseMuxWindow::chapters_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		fileUpdated();
	}

	void baseMuxWindow::fps_SelectionChanged(object *sender, const std::string &val)
	{
		checkIO();
	}

	void baseMuxWindow::fileUpdated()
	{
	}

	void baseMuxWindow::upDeviceTypes()
	{
	}

	void baseMuxWindow::audioAddTrack_Click(object *sender, EventArgs *e)
	{
		AudioAddTrack();
	}

	void baseMuxWindow::AudioAddTrack()
	{
		TabPage *p = new TabPage("Audio " + (audioTracks.size() + 1));
		p->UseVisualStyleBackColor = audio->TabPages[0]->UseVisualStyleBackColor;
		p->Padding = audio->TabPages[0]->Padding;

		MuxStreamControl *a = new MuxStreamControl();
		a->Dock = audioTracks[0]->Dock;
		a->Padding = audioTracks[0]->Padding;
		a->setShowDelay(audioTracks[0]->getShowDelay());
		a->setFilter(audioTracks[0]->getFilter());
		a->FileUpdated += new System::EventHandler(this, &baseMuxWindow::muxStreamControl2_FileUpdated);
		a->input->FileSelected += new MeGUI::FileBarEventHandler(this, &baseMuxWindow::Audio_FileSelected);

		audio->TabPages->Add(p);
		p->Controls->Add(a);
		audioTracks.push_back(a);
	}

	void baseMuxWindow::audioRemoveTrack_Click(object *sender, EventArgs *e)
	{
		AudioRemoveTrack();
	}

	void baseMuxWindow::AudioRemoveTrack()
	{
		audio->TabPages->RemoveAt(audio->TabPages->Count - 1);
		audioTracks.pop_back();
	}

	void baseMuxWindow::subtitleAddTrack_Click(object *sender, EventArgs *e)
	{
		SubtitleAddTrack();
	}

	void baseMuxWindow::SubtitleAddTrack()
	{
		TabPage *p = new TabPage("Subtitle " + (subtitleTracks.size() + 1));
		p->UseVisualStyleBackColor = subtitles->TabPages[0]->UseVisualStyleBackColor;
		p->Padding = subtitles->TabPages[0]->Padding;

		MuxStreamControl *a = new MuxStreamControl();
		a->Dock = subtitleTracks[0]->Dock;
		a->Padding = subtitleTracks[0]->Padding;
		a->setShowDelay(subtitleTracks[0]->getShowDelay());
		a->setShowDefaultSubtitleStream(subtitleTracks[0]->getShowDefaultSubtitleStream());
		a->setShowForceSubtitleStream(subtitleTracks[0]->getShowForceSubtitleStream());
		a->chkDefaultStream->CheckedChanged += new System::EventHandler(this, &baseMuxWindow::chkDefaultStream_CheckedChanged);
		a->input->FileSelected += new MeGUI::FileBarEventHandler(this, &baseMuxWindow::Subtitle_FileSelected);
		a->setFilter(subtitleTracks[0]->getFilter());
		a->FileUpdated += new System::EventHandler(this, &baseMuxWindow::muxStreamControl1_FileUpdated);

		subtitles->TabPages->Add(p);
		p->Controls->Add(a);
		subtitleTracks.push_back(a);
	}

	void baseMuxWindow::subtitleRemoveTrack_Click(object *sender, EventArgs *e)
	{
		SubtitleRemoveTrack();
	}

	void baseMuxWindow::SubtitleRemoveTrack()
	{
		subtitles->TabPages->RemoveAt(subtitles->TabPages->Count - 1);
		subtitleTracks.pop_back();
	}

	void baseMuxWindow::audioMenu_Opening(object *sender, CancelEventArgs *e)
	{
		audioRemoveTrack->Enabled = audioTracks.size() > 1;
	}

	void baseMuxWindow::subtitleMenu_Opening(object *sender, CancelEventArgs *e)
	{
		subtitleRemoveTrack->Enabled = subtitleTracks.size() > 1;
	}

	void baseMuxWindow::muxStreamControl1_FileUpdated(object *sender, EventArgs *e)
	{
		fileUpdated();
	}

	void baseMuxWindow::muxStreamControl2_FileUpdated(object *sender, EventArgs *e)
	{
		fileUpdated();
	}

	void baseMuxWindow::cbContainer_SelectedIndexChanged(object *sender, EventArgs *e)
	{
		upDeviceTypes();
	}

	void baseMuxWindow::output_Click(object *sender, EventArgs *e)
	{
		checkIO();
		fileUpdated();
	}

	void baseMuxWindow::removeVideoTrack_Click(object *sender, EventArgs *e)
	{
		vInput->setFilename("");
		videoName->Text = "";
		fps->setValue(Nullable<decimal>());
	}

	void baseMuxWindow::cbType_SelectedIndexChanged(object *sender, EventArgs *e)
	{
		if (muxer == 0 || muxer->getMuxerType() != TSMUXER)
			return;

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (!(cbType->SelectedItem->ToString())->empty() && cbType->SelectedItem->ToString() != "Standard")
			chaptersGroupbox->Enabled = true;
		else
			chaptersGroupbox->Enabled = false;
	}
}
