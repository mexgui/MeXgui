#include "MeXgui.VobSubIndexWindow.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;





//using namespace System::Text;


using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;

namespace MeXgui
{

	VobSubIndexWindow::VobSubIndexWindow(MainForm *mainForm)
	{
		InitializeInstanceFields();
		InitializeComponent();
		this->mainForm = mainForm;
		this->vUtil = new VideoUtil(mainForm);
		this->jobUtil = new JobUtil(mainForm);
	}

	void VobSubIndexWindow::OnClosing(CancelEventArgs *e)
	{
		System::Windows::Forms::Form::OnClosing(e);
	}

	void VobSubIndexWindow::queueButton_Click()
	{
		if (Drives::ableToWriteOnThisDrive(Path::GetPathRoot(output->getFilename())))
		{
			if (configured)
			{
				if (!dialogMode)
				{
					SubtitleIndexJob *job = generateJob();
					mainForm->getJobs()->addJobsToQueue(job);
					if (this->closeOnQueue->Checked)
						this->Close();
				}
			}
			else
				MessageBox::Show("You must select an Input and Output file to continue", "Configuration incomplete", MessageBoxButtons::OK);
		}
		else
			MessageBox::Show("MeXgui cannot write on " + Path::GetPathRoot(output->getFilename()) + ". Please, select another output path.", "Configuration Incomplete", MessageBoxButtons::OK);
	}

	void VobSubIndexWindow::openVideo(const QString &fileName)
	{
		input->setFilename(fileName);
		subtitleTracks->Items->Clear();
		unsigned int nbPGC = IFOparser::getPGCnb(fileName);
		pgc->Maximum = nbPGC;
		subtitleTracks->Items->AddRange(IFOparser::GetSubtitlesStreamsInfos(input->getFilename(), static_cast<int>(pgc->Value), chkShowAllStreams->Checked));
		demuxSelectedTracks->Checked = !keepAllTracks->Checked;
	}

	void VobSubIndexWindow::checkIndexIO()
	{
		configured = (!input->getFilename().Equals("") && !output->getFilename().Equals(""));
		if (configured && dialogMode)
			queueButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		else
			queueButton->DialogResult = System::Windows::Forms::DialogResult::None;
	}

	SubtitleIndexJob *VobSubIndexWindow::generateJob()
	{
		QVector<int> trackIDs = QVector<int>();
		for (unknown::const_iterator s = subtitleTracks->CheckedItems.begin(); s != subtitleTracks->CheckedItems.end(); ++s)
		{
			trackIDs.push_back(int::Parse((*s).substr(1,2)));
		}
		return new SubtitleIndexJob(input->getFilename(), output->getFilename(), keepAllTracks->Checked, trackIDs, static_cast<int>(pgc->Value));
	}

	void VobSubIndexWindow::setConfig(const QString &input, const QString &output, bool indexAllTracks, QVector<int> &trackIDs, int pgc)
	{
		this->dialogMode = true;
		queueButton->Text = "Update";
		this->input->setFilename(input);
		openVideo(input);
		this->output->setFilename(output);
		checkIndexIO();
		if (indexAllTracks)
			keepAllTracks->Checked = true;
		else
		{
			demuxSelectedTracks->Checked = true;
			int index = 0;
			QVector<int> checkedItems = QVector<int>();
			for (unknown::const_iterator item = subtitleTracks->Items.begin(); item != subtitleTracks->Items.end(); ++item)
			{
				SubtitleInfo *si = static_cast<SubtitleInfo*>(*item);
				if (std::find(trackIDs.begin(), trackIDs.end(), si->getIndex()) != trackIDs.end())
					checkedItems.push_back(index);
				index++;
			}
			for (QVector<int>::const_iterator idx = checkedItems.begin(); idx != checkedItems.end(); ++idx)
			{
				subtitleTracks->SetItemChecked(*idx, true);
			}
		}
		this->pgc->Value = pgc;
	}

	const SubtitleIndexJob &VobSubIndexWindow::getJob() const
	{
		return generateJob();
	}

	void VobSubIndexWindow::input_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		openVideo(input->getFilename());
		output->setFilename(Path::ChangeExtension(input->getFilename(), ".idx"));
		checkIndexIO();
	}

	void VobSubIndexWindow::output_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		checkIndexIO();
	}

	void VobSubIndexWindow::chkShowAllStreams_CheckedChanged()
	{
		if (input->getFilename().empty())
			return;
		openVideo(input->getFilename());
		checkIndexIO();
	}

	void VobSubIndexWindow::pgc_ValueChanged()
	{
		if (input->getFilename().empty())
			return;
		openVideo(input->getFilename());
		checkIndexIO();
	}

	void VobSubIndexWindow::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void VobSubIndexWindow::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(VobSubIndexWindow::typeid);
		this->inputGroupbox = new System::Windows::Forms::GroupBox();
		this->pgc = new System::Windows::Forms::NumericUpDown();
		this->pgcLabel = new System::Windows::Forms::Label();
		this->inputLabel = new System::Windows::Forms::Label();
		this->outputGroupbox = new System::Windows::Forms::GroupBox();
		this->nameLabel = new System::Windows::Forms::Label();
		this->subtitleGroupbox = new System::Windows::Forms::GroupBox();
		this->chkShowAllStreams = new System::Windows::Forms::CheckBox();
		this->subtitleTracks = new System::Windows::Forms::CheckedListBox();
		this->demuxSelectedTracks = new System::Windows::Forms::RadioButton();
		this->keepAllTracks = new System::Windows::Forms::RadioButton();
		this->closeOnQueue = new System::Windows::Forms::CheckBox();
		this->queueButton = new QPushButton;
		this->helpButton1 = new MeXgui::core::gui::HelpButton();
		this->output = new MeXgui::FileBar();
		this->input = new MeXgui::FileBar();
		this->inputGroupbox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->pgc))->BeginInit();
		this->outputGroupbox->SuspendLayout();
		this->subtitleGroupbox->SuspendLayout();
		this->SuspendLayout();
		// 
		// inputGroupbox
		// 
		this->inputGroupbox->Controls->Add(this->input);
		this->inputGroupbox->Controls->Add(this->pgc);
		this->inputGroupbox->Controls->Add(this->pgcLabel);
		this->inputGroupbox->Controls->Add(this->inputLabel);
		this->inputGroupbox->Location = new System::Drawing::Point(2, 2);
		this->inputGroupbox->Name = "inputGroupbox";
		this->inputGroupbox->Size = new System::Drawing::Size(424, 70);
		this->inputGroupbox->TabIndex = 1;
		this->inputGroupbox->TabStop = false;
		this->inputGroupbox->Text = "Input";
		// 
		// pgc
		// 
		this->pgc->Location = new System::Drawing::Point(120, 45);
		this->pgc->Maximum = decimal(new int[4] {99, 0, 0, 0});
		this->pgc->Minimum = decimal(new int[4] {1, 0, 0, 0});
		this->pgc->Name = "pgc";
		this->pgc->Size = new System::Drawing::Size(50, 21);
		this->pgc->TabIndex = 4;
		this->pgc->Value = decimal(new int[4] {1, 0, 0, 0});
		this->pgc->ValueChanged += new System::EventHandler(this, &VobSubIndexWindow::pgc_ValueChanged);
		// 
		// pgcLabel
		// 
		this->pgcLabel->AutoSize = true;
		this->pgcLabel->Location = new System::Drawing::Point(16, 47);
		this->pgcLabel->Name = "pgcLabel";
		this->pgcLabel->Size = new System::Drawing::Size(27, 13);
		this->pgcLabel->TabIndex = 3;
		this->pgcLabel->Text = "PGC";
		// 
		// inputLabel
		// 
		this->inputLabel->Location = new System::Drawing::Point(16, 20);
		this->inputLabel->Name = "inputLabel";
		this->inputLabel->Size = new System::Drawing::Size(100, 13);
		this->inputLabel->TabIndex = 0;
		this->inputLabel->Text = "Input";
		// 
		// outputGroupbox
		// 
		this->outputGroupbox->Controls->Add(this->output);
		this->outputGroupbox->Controls->Add(this->nameLabel);
		this->outputGroupbox->Location = new System::Drawing::Point(2, 309);
		this->outputGroupbox->Name = "outputGroupbox";
		this->outputGroupbox->Size = new System::Drawing::Size(424, 49);
		this->outputGroupbox->TabIndex = 13;
		this->outputGroupbox->TabStop = false;
		this->outputGroupbox->Text = "Output";
		// 
		// nameLabel
		// 
		this->nameLabel->Location = new System::Drawing::Point(16, 20);
		this->nameLabel->Name = "nameLabel";
		this->nameLabel->Size = new System::Drawing::Size(100, 13);
		this->nameLabel->TabIndex = 3;
		this->nameLabel->Text = "Ouput";
		// 
		// subtitleGroupbox
		// 
		this->subtitleGroupbox->Controls->Add(this->chkShowAllStreams);
		this->subtitleGroupbox->Controls->Add(this->subtitleTracks);
		this->subtitleGroupbox->Controls->Add(this->demuxSelectedTracks);
		this->subtitleGroupbox->Controls->Add(this->keepAllTracks);
		this->subtitleGroupbox->Location = new System::Drawing::Point(2, 78);
		this->subtitleGroupbox->Name = "subtitleGroupbox";
		this->subtitleGroupbox->Size = new System::Drawing::Size(424, 225);
		this->subtitleGroupbox->TabIndex = 14;
		this->subtitleGroupbox->TabStop = false;
		this->subtitleGroupbox->Text = "Subtitles";
		// 
		// chkShowAllStreams
		// 
		this->chkShowAllStreams->AutoSize = true;
		this->chkShowAllStreams->Location = new System::Drawing::Point(262, 25);
		this->chkShowAllStreams->Name = "chkShowAllStreams";
		this->chkShowAllStreams->Size = new System::Drawing::Size(144, 17);
		this->chkShowAllStreams->TabIndex = 10;
		this->chkShowAllStreams->Text = "Show all subtitle streams";
		this->chkShowAllStreams->UseVisualStyleBackColor = true;
		this->chkShowAllStreams->CheckedChanged += new System::EventHandler(this, &VobSubIndexWindow::chkShowAllStreams_CheckedChanged);
		// 
		// subtitleTracks
		// 
		this->subtitleTracks->CheckOnClick = true;
		this->subtitleTracks->FormattingEnabled = true;
		this->subtitleTracks->Location = new System::Drawing::Point(50, 72);
		this->subtitleTracks->Name = "subtitleTracks";
		this->subtitleTracks->Size = new System::Drawing::Size(356, 148);
		this->subtitleTracks->TabIndex = 9;
		// 
		// demuxSelectedTracks
		// 
		this->demuxSelectedTracks->Checked = true;
		this->demuxSelectedTracks->Location = new System::Drawing::Point(10, 46);
		this->demuxSelectedTracks->Name = "demuxSelectedTracks";
		this->demuxSelectedTracks->Size = new System::Drawing::Size(336, 24);
		this->demuxSelectedTracks->TabIndex = 8;
		this->demuxSelectedTracks->TabStop = true;
		this->demuxSelectedTracks->Text = "Select subtitle streams";
		// 
		// keepAllTracks
		// 
		this->keepAllTracks->Location = new System::Drawing::Point(10, 20);
		this->keepAllTracks->Name = "keepAllTracks";
		this->keepAllTracks->Size = new System::Drawing::Size(160, 24);
		this->keepAllTracks->TabIndex = 7;
		this->keepAllTracks->Text = "Keep all subtitle streams";
		// 
		// closeOnQueue
		// 
		this->closeOnQueue->Checked = true;
		this->closeOnQueue->CheckState = System::Windows::Forms::CheckState::Checked;
		this->closeOnQueue->Location = new System::Drawing::Point(272, 364);
		this->closeOnQueue->Name = "closeOnQueue";
		this->closeOnQueue->Size = new System::Drawing::Size(72, 24);
		this->closeOnQueue->TabIndex = 16;
		this->closeOnQueue->Text = "and close";
		// 
		// queueButton
		// 
		this->queueButton->Location = new System::Drawing::Point(352, 364);
		this->queueButton->Name = "queueButton";
		this->queueButton->Size = new System::Drawing::Size(74, 23);
		this->queueButton->TabIndex = 15;
		this->queueButton->Text = "Queue";
		this->queueButton->Click += new System::EventHandler(this, &VobSubIndexWindow::queueButton_Click);
		// 
		// helpButton1
		// 
		this->helpButton1->setArticleName("Tools/VobSubber");
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(7, 364);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(47, 23);
		this->helpButton1->TabIndex = 17;
		// 
		// output
		// 
		this->output->setFilename("");
		this->output->setFilter("VobSub Files|*.idx");
		this->output->setFilterIndex(0);
		this->output->setFolderMode(false);
		this->output->Location = new System::Drawing::Point(120, 17);
		this->output->Name = "output";
		this->output->setReadOnly(true);
		this->output->setSaveMode(true);
		this->output->Size = new System::Drawing::Size(286, 26);
		this->output->TabIndex = 5;
		this->output->setTitle("Choose an output file");
		this->output->FileSelected += new MeXgui::FileBarEventHandler(this, &VobSubIndexWindow::output_FileSelected);
		// 
		// input
		// 
		this->input->setFilename("");
		this->input->setFilter("IFO Files|*.ifo");
		this->input->setFilterIndex(0);
		this->input->setFolderMode(false);
		this->input->Location = new System::Drawing::Point(120, 13);
		this->input->Name = "input";
		this->input->setReadOnly(true);
		this->input->setSaveMode(false);
		this->input->Size = new System::Drawing::Size(286, 26);
		this->input->TabIndex = 5;
		this->input->setTitle("");
		this->input->FileSelected += new MeXgui::FileBarEventHandler(this, &VobSubIndexWindow::input_FileSelected);
		// 
		// VobSubIndexWindow
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = new System::Drawing::Size(434, 393);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->closeOnQueue);
		this->Controls->Add(this->queueButton);
		this->Controls->Add(this->subtitleGroupbox);
		this->Controls->Add(this->outputGroupbox);
		this->Controls->Add(this->inputGroupbox);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = "VobSubIndexWindow";
		this->Text = "MeXgui - VobSub Indexer";
		this->inputGroupbox->ResumeLayout(false);
		this->inputGroupbox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->pgc))->EndInit();
		this->outputGroupbox->ResumeLayout(false);
		this->subtitleGroupbox->ResumeLayout(false);
		this->subtitleGroupbox->PerformLayout();
		this->ResumeLayout(false);

	}

	void VobSubIndexWindow::InitializeInstanceFields()
	{
		dialogMode = false;
		configured = false;
		delete components;
	}
}
