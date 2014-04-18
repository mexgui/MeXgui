#include "ChapterCreator.h"






//using namespace System::Collections::Generic;







//using namespace System::Linq;


using namespace MeXgui::core::util;

namespace MeXgui
{

	ChapterCreator::ChapterCreator(MainForm *mainForm)
	{
		//
		// Required for Windows Form Designer support
		//
		InitializeInstanceFields();
		InitializeComponent();
		intIndex = 0;
		chapters = new Chapter[0];
		this->mainForm = mainForm;
		pgc = new ChapterInfo(new object[] {Chapters = QVector<Chapter>(), FramesPerSecond = 25.0, LangCode = ""});
	}

	void ChapterCreator::OnClosing(CancelEventArgs *e)
	{
		if (player != 0)
			player->Close();
		System::Windows::Forms::Form::OnClosing(e);
	}

	void ChapterCreator::Dispose(bool disposing)
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

	void ChapterCreator::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(ChapterCreator::typeid);
		this->chaptersGroupbox = new System::Windows::Forms::GroupBox();
		this->chapterName = new System::Windows::Forms::TextBox();
		this->chapterNameLabel = new System::Windows::Forms::Label();
		this->chapterListView = new System::Windows::Forms::ListView();
		this->timecodeColumn = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
		this->nameColumn = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
		this->startTime = new System::Windows::Forms::TextBox();
		this->startTimeLabel = new System::Windows::Forms::Label();
		this->addZoneButton = new QPushButton;
		this->clearZonesButton = new QPushButton;
		this->showVideoButton = new QPushButton;
		this->removeZoneButton = new QPushButton;
		this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
		this->saveFileDialog = new System::Windows::Forms::SaveFileDialog();
		this->gbInput = new System::Windows::Forms::GroupBox();
		this->btInput = new QPushButton;
		this->input = new System::Windows::Forms::TextBox();
		this->rbFromFile = new System::Windows::Forms::RadioButton();
		this->rbFromDisk = new System::Windows::Forms::RadioButton();
		this->saveButton = new QPushButton;
		this->helpButton1 = new MeXgui::core::gui::HelpButton();
		this->closeOnQueue = new System::Windows::Forms::CheckBox();
		this->chaptersGroupbox->SuspendLayout();
		this->gbInput->SuspendLayout();
		this->SuspendLayout();
		// 
		// chaptersGroupbox
		// 
		this->chaptersGroupbox->Controls->Add(this->chapterName);
		this->chaptersGroupbox->Controls->Add(this->chapterNameLabel);
		this->chaptersGroupbox->Controls->Add(this->chapterListView);
		this->chaptersGroupbox->Controls->Add(this->startTime);
		this->chaptersGroupbox->Controls->Add(this->startTimeLabel);
		this->chaptersGroupbox->Controls->Add(this->addZoneButton);
		this->chaptersGroupbox->Controls->Add(this->clearZonesButton);
		this->chaptersGroupbox->Controls->Add(this->showVideoButton);
		this->chaptersGroupbox->Controls->Add(this->removeZoneButton);
		this->chaptersGroupbox->Location = new System::Drawing::Point(4, 86);
		this->chaptersGroupbox->Name = "chaptersGroupbox";
		this->chaptersGroupbox->Size = new System::Drawing::Size(458, 336);
		this->chaptersGroupbox->TabIndex = 23;
		this->chaptersGroupbox->TabStop = false;
		this->chaptersGroupbox->Text = "Chapters";
		// 
		// chapterName
		// 
		this->chapterName->Location = new System::Drawing::Point(75, 305);
		this->chapterName->Name = "chapterName";
		this->chapterName->Size = new System::Drawing::Size(306, 21);
		this->chapterName->TabIndex = 38;
		this->chapterName->Text = "Chapter 01";
		this->chapterName->TextChanged += new System::EventHandler(this, &ChapterCreator::chapterName_TextChanged);
		// 
		// chapterNameLabel
		// 
		this->chapterNameLabel->Location = new System::Drawing::Point(13, 308);
		this->chapterNameLabel->Name = "chapterNameLabel";
		this->chapterNameLabel->Size = new System::Drawing::Size(56, 17);
		this->chapterNameLabel->TabIndex = 37;
		this->chapterNameLabel->Text = "Name :";
		// 
		// chapterListView
		// 
		this->chapterListView->Columns->AddRange(new System::Windows::Forms::ColumnHeader[2] {this->timecodeColumn, this->nameColumn});
		this->chapterListView->FullRowSelect = true;
		this->chapterListView->HideSelection = false;
		this->chapterListView->Location = new System::Drawing::Point(16, 24);
		this->chapterListView->Name = "chapterListView";
		this->chapterListView->Size = new System::Drawing::Size(365, 240);
		this->chapterListView->TabIndex = 36;
		this->chapterListView->UseCompatibleStateImageBehavior = false;
		this->chapterListView->View = System::Windows::Forms::View::Details;
		this->chapterListView->SelectedIndexChanged += new System::EventHandler(this, &ChapterCreator::chapterListView_SelectedIndexChanged);
		// 
		// timecodeColumn
		// 
		this->timecodeColumn->Text = "Timecode";
		this->timecodeColumn->Width = 100;
		// 
		// nameColumn
		// 
		this->nameColumn->Text = "Name";
		this->nameColumn->Width = 250;
		// 
		// startTime
		// 
		this->startTime->Location = new System::Drawing::Point(75, 274);
		this->startTime->Name = "startTime";
		this->startTime->Size = new System::Drawing::Size(306, 21);
		this->startTime->TabIndex = 23;
		this->startTime->Text = "00:00:00.000";
		// 
		// startTimeLabel
		// 
		this->startTimeLabel->Location = new System::Drawing::Point(13, 277);
		this->startTimeLabel->Name = "startTimeLabel";
		this->startTimeLabel->Size = new System::Drawing::Size(64, 16);
		this->startTimeLabel->TabIndex = 24;
		this->startTimeLabel->Text = "Start Time :";
		// 
		// addZoneButton
		// 
		this->addZoneButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->addZoneButton->Location = new System::Drawing::Point(392, 24);
		this->addZoneButton->Name = "addZoneButton";
		this->addZoneButton->Size = new System::Drawing::Size(55, 23);
		this->addZoneButton->TabIndex = 33;
		this->addZoneButton->Text = "&Add";
		this->addZoneButton->Click += new System::EventHandler(this, &ChapterCreator::addZoneButton_Click);
		// 
		// clearZonesButton
		// 
		this->clearZonesButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->clearZonesButton->Location = new System::Drawing::Point(392, 82);
		this->clearZonesButton->Name = "clearZonesButton";
		this->clearZonesButton->Size = new System::Drawing::Size(55, 23);
		this->clearZonesButton->TabIndex = 29;
		this->clearZonesButton->Text = "&Clear";
		this->clearZonesButton->Click += new System::EventHandler(this, &ChapterCreator::clearZonesButton_Click);
		// 
		// showVideoButton
		// 
		this->showVideoButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->showVideoButton->Enabled = false;
		this->showVideoButton->Location = new System::Drawing::Point(392, 111);
		this->showVideoButton->Name = "showVideoButton";
		this->showVideoButton->Size = new System::Drawing::Size(55, 23);
		this->showVideoButton->TabIndex = 34;
		this->showVideoButton->Text = "&Preview";
		this->showVideoButton->Click += new System::EventHandler(this, &ChapterCreator::showVideoButton_Click);
		// 
		// removeZoneButton
		// 
		this->removeZoneButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->removeZoneButton->Location = new System::Drawing::Point(392, 53);
		this->removeZoneButton->Name = "removeZoneButton";
		this->removeZoneButton->Size = new System::Drawing::Size(55, 23);
		this->removeZoneButton->TabIndex = 32;
		this->removeZoneButton->Text = "&Remove";
		this->removeZoneButton->Click += new System::EventHandler(this, &ChapterCreator::removeZoneButton_Click);
		// 
		// openFileDialog
		// 
		this->openFileDialog->DefaultExt = "txt";
		this->openFileDialog->Filter = "Blu-ray Playlist Files (*.mpls)|*.mpls|IFO Files (*.ifo)|*.ifo|Chapter Files (*.t" + "xt)|*.txt|All Files supported (*.ifo;*.txt;*.mpls)|*.ifo;*.mpls;*.txt";
		this->openFileDialog->FilterIndex = 4;
		// 
		// saveFileDialog
		// 
		this->saveFileDialog->DefaultExt = "txt";
		this->saveFileDialog->Filter = "Chapter Files (*.txt)|*.txt|Matroska Chapters files (*.xml)|*.xml|x264 qp Files (*.qpf)|*.qpf|All supported Files (*.txt;*.xml;*.qpf)|*.txt;*.xml;*.qpf";
		this->saveFileDialog->FilterIndex = 4;
		// 
		// gbInput
		// 
		this->gbInput->Controls->Add(this->btInput);
		this->gbInput->Controls->Add(this->input);
		this->gbInput->Controls->Add(this->rbFromFile);
		this->gbInput->Controls->Add(this->rbFromDisk);
		this->gbInput->Location = new System::Drawing::Point(4, 4);
		this->gbInput->Name = "gbInput";
		this->gbInput->Size = new System::Drawing::Size(458, 76);
		this->gbInput->TabIndex = 24;
		this->gbInput->TabStop = false;
		this->gbInput->Text = "Input";
		// 
		// btInput
		// 
		this->btInput->Location = new System::Drawing::Point(392, 20);
		this->btInput->Name = "btInput";
		this->btInput->Size = new System::Drawing::Size(55, 23);
		this->btInput->TabIndex = 10;
		this->btInput->Text = "...";
		this->btInput->UseVisualStyleBackColor = true;
		this->btInput->Click += new System::EventHandler(this, &ChapterCreator::btInput_Click);
		// 
		// input
		// 
		this->input->Location = new System::Drawing::Point(18, 20);
		this->input->Name = "input";
		this->input->ReadOnly = true;
		this->input->Size = new System::Drawing::Size(363, 21);
		this->input->TabIndex = 9;
		// 
		// rbFromFile
		// 
		this->rbFromFile->AutoSize = true;
		this->rbFromFile->Checked = true;
		this->rbFromFile->Location = new System::Drawing::Point(124, 45);
		this->rbFromFile->Name = "rbFromFile";
		this->rbFromFile->Size = new System::Drawing::Size(68, 17);
		this->rbFromFile->TabIndex = 8;
		this->rbFromFile->TabStop = true;
		this->rbFromFile->Text = "From File";
		this->rbFromFile->UseVisualStyleBackColor = true;
		// 
		// rbFromDisk
		// 
		this->rbFromDisk->AutoSize = true;
		this->rbFromDisk->Location = new System::Drawing::Point(25, 45);
		this->rbFromDisk->Name = "rbFromDisk";
		this->rbFromDisk->Size = new System::Drawing::Size(71, 17);
		this->rbFromDisk->TabIndex = 7;
		this->rbFromDisk->Text = "From Disk";
		this->rbFromDisk->UseVisualStyleBackColor = true;
		// 
		// saveButton
		// 
		this->saveButton->Location = new System::Drawing::Point(396, 428);
		this->saveButton->Name = "saveButton";
		this->saveButton->Size = new System::Drawing::Size(55, 23);
		this->saveButton->TabIndex = 41;
		this->saveButton->Text = "&Save";
		this->saveButton->Click += new System::EventHandler(this, &ChapterCreator::saveButton_Click);
		// 
		// helpButton1
		// 
		this->helpButton1->setArticleName("Chapter Creator");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(12, 428);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 42;
		// 
		// closeOnQueue
		// 
		this->closeOnQueue->Checked = true;
		this->closeOnQueue->CheckState = System::Windows::Forms::CheckState::Checked;
		this->closeOnQueue->Location = new System::Drawing::Point(313, 428);
		this->closeOnQueue->Name = "closeOnQueue";
		this->closeOnQueue->Size = new System::Drawing::Size(72, 24);
		this->closeOnQueue->TabIndex = 43;
		this->closeOnQueue->Text = "and close";
		// 
		// ChapterCreator
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->ClientSize = new System::Drawing::Size(468, 458);
		this->Controls->Add(this->closeOnQueue);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->saveButton);
		this->Controls->Add(this->gbInput);
		this->Controls->Add(this->chaptersGroupbox);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = "ChapterCreator";
		this->Text = "MeXgui - Chapter Creator";
		this->Load += new System::EventHandler(this, &ChapterCreator::ChapterCreator_Load);
		this->chaptersGroupbox->ResumeLayout(false);
		this->chaptersGroupbox->PerformLayout();
		this->gbInput->ResumeLayout(false);
		this->gbInput->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void ChapterCreator::showChapters(Chapter chaps[])
	{
		this->chapterListView->Items->Clear();
		for (MeXgui::Chapter::const_iterator chap = chaps->begin(); chap != chaps->end(); ++chap)
		{
			ListViewItem *item = new ListViewItem(new QString[] {(*chap).timecode, (*chap).name});
			item->Tag = *chap;
			chapterListView->Items->Add(item);
			if (item->Index % 2 != 0)
				item->BackColor = Color::White;
			else
				item->BackColor = Color::WhiteSmoke;
		}
	}

	void ChapterCreator::FreshChapterView()
	{
		this->Cursor = Cursors::WaitCursor;
		try
		{
			this->chapterListView->Items->Clear();
			//fill list
			for (QVector<Chapter>::const_iterator c = pgc->getChapters().begin(); c != pgc->getChapters().end(); ++c)
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				ListViewItem *item = new ListViewItem(new QString[] {(*c).getTime()->ToString(), (*c).getName()});
				chapterListView->Items->Add(item);
				if (item->Index % 2 != 0)
					item->BackColor = Color::White;
				else
					item->BackColor = Color::WhiteSmoke;
			}
		}
		catch (std::exception &ex)
		{
			MessageBox::Show(ex.what());
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			this->Cursor = Cursors::Default;
		}
	}

	void ChapterCreator::updateTimeLine()
	{
		for (int i = 0; i < chapterListView->Items->Count; i++)
		{
			if (chapterListView->Items[i]->SubItems[0]->Text->Length == 8)
				chapterListView->Items[i]->SubItems[0]->Text = chapterListView->Items[i]->SubItems[0]->Text + ".000";
			else
				chapterListView->Items[i]->SubItems[0]->Text = chapterListView->Items[i]->SubItems[0]->Text->substr(0, 12);
		}
	}

	void ChapterCreator::removeZoneButton_Click()
	{
		if (chapterListView->Items->Count < 1 || pgc->getChapters().size() < 1)
			return;
		if (chapterListView->SelectedIndices->Count == 0)
			return;
		intIndex = chapterListView->SelectedIndices[0];
		pgc->getChapters().Remove(pgc->getChapters()[intIndex]);
		if (intIndex != 0)
			intIndex--;
		FreshChapterView();
		updateTimeLine();
	}

	void ChapterCreator::clearZonesButton_Click()
	{
		pgc->getChapters().clear();
		FreshChapterView();
		intIndex = 0;
	}

	void ChapterCreator::chapterListView_SelectedIndexChanged()
	{
		if (chapterListView->Items->Count < 1)
			return;

		chapterName->TextChanged -= new System::EventHandler(this, &ChapterCreator::chapterName_TextChanged);
		startTime->TextChanged -= new System::EventHandler(this, &ChapterCreator::chapterName_TextChanged);
		ListView *lv = static_cast<ListView*>(sender);

		if (lv->SelectedItems->Count == 1)
			intIndex = lv->SelectedItems[0]->Index;
		if (pgc->getChapters().size() > 0)
		{
			this->startTime->Text = FileUtil::ToShortString(pgc->getChapters()[intIndex].getTime());
			this->chapterName->Text = pgc->getChapters()[intIndex].getName();
		}

		chapterName->TextChanged += new System::EventHandler(this, &ChapterCreator::chapterName_TextChanged);
		startTime->TextChanged += new System::EventHandler(this, &ChapterCreator::chapterName_TextChanged);
	}

	void ChapterCreator::addZoneButton_Click()
	{
		Chapter c;
		if (chapterListView->Items->Count != 0)
			 intIndex = chapterListView->Items->Count;
		else
			intIndex = 0;
		TimeSpan *ts = new TimeSpan(0);
		try
		{ //try to get a valid time input
			 ts = TimeSpan::Parse(startTime->Text);
		}
		catch (std::exception &parse)
		{ //invalid time input
			startTime->Focus();
			startTime->SelectAll();
			MessageBox::Show("Cannot parse the timecode you have entered.\nIt must be given in the hh:mm:ss.ccc format" + "\r\n" + parse.what(), "Incorrect timecode", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return;
		}
		//create a new chapter
		c = Chapter(new object[] {Time = ts, Name = chapterName->Text});
		pgc->getChapters().Insert(intIndex, c);
		FreshChapterView();
		updateTimeLine();
	}

	void ChapterCreator::saveButton_Click()
	{
		if ((Path::GetFileNameWithoutExtension(input->Text))->empty())
			saveFileDialog->FileName = "Chapter Information.txt";
		else
			saveFileDialog->FileName = Path::GetFileNameWithoutExtension(input->Text) + " - Chapter Information.txt";
		if (this->saveFileDialog->show() == System::Windows::Forms::DialogResult::OK)
		{
			QString ext = Path::GetExtension(saveFileDialog->FileName)->ToLower(System::Globalization::CultureInfo::InvariantCulture);
			if (Drives::ableToWriteOnThisDrive(Path::GetPathRoot(saveFileDialog->FileName)))
			{
				if (ext == ".qpf")
					pgc->SaveQpfile(saveFileDialog->FileName);
				else if (ext == ".xml")
					pgc->SaveXml(saveFileDialog->FileName);
				else
					pgc->SaveText(saveFileDialog->FileName);
			}
			else
				MessageBox::Show("MeXgui cannot write on the disc " + Path::GetPathRoot(saveFileDialog->FileName) + "\n" + "Please, select another output path to save your project...", "Configuration Incomplete", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}

		if (this->closeOnQueue->Checked)
			this->Close();
	}

	void ChapterCreator::btInput_Click()
	{
		if (rbFromFile->Checked)
		{
			openFileDialog->Filter = "IFO Files (*.ifo)|*.ifo|MPLS Files (*.mpls)|*.mpls|Text Files (*.txt)|*.txt|All Files supported (*.ifo,*.mpls,*.txt)|*.ifo;*.mpls;*.txt";
			openFileDialog->FilterIndex = 4;

		   if (this->openFileDialog->show() == System::Windows::Forms::DialogResult::OK)
		   {
				input->Text = openFileDialog->FileName;

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
				if (input->Text->ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith("ifo"))
				{
					ChapterExtractor *ex = new DvdExtractor();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (frmStreamSelect frm = new frmStreamSelect(ex))
					frmStreamSelect *frm = new frmStreamSelect(ex);
					try
					{
						if (dynamic_cast<DvdExtractor*>(ex) != 0)
							frm->Text = "Select your PGC";
						else
							frm->Text = "Select your Playlist";
						ex->GetStreams(input->Text);
						if (frm->getChapterCount() == 1 || frm->show(this) == System::Windows::Forms::DialogResult::OK)
						{
							pgc = frm->getSelectedSingleChapterInfo();
							if (pgc->getFramesPerSecond() == 0)
								pgc->setFramesPerSecond(25.0);
							if (pgc->getLangCode().empty())
								pgc->setLangCode("und");
						}
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (frm != 0)
							frm.Dispose();
					}
					FreshChapterView();
					updateTimeLine();
				}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
				else if (input->Text->ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith("mpls"))
				{
					ChapterExtractor *ex = new MplsExtractor();
					pgc = ex->GetStreams(input->Text)[0];
					FreshChapterView();
					updateTimeLine();
				}
				else
				{
					ChapterExtractor *ex = new TextExtractor();
					pgc = ex->GetStreams(input->Text)[0];
					FreshChapterView();
					updateTimeLine();
				}
		   }
		}
		else
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (FolderBrowserDialog d = new FolderBrowserDialog())
			FolderBrowserDialog *d = new FolderBrowserDialog();
			try
			{
				d->ShowNewFolderButton = false;
				d->Description = "Select DVD, BluRay disc, or folder.";
				if (d->show() == System::Windows::Forms::DialogResult::OK)
				{
					input->Text = d->SelectedPath;
					try
					{
						ChapterExtractor *ex = Directory::Exists(Path::Combine(input->Text, "VIDEO_TS")) ? new dynamic_cast<ChapterExtractor*>(DvdExtractor()) : File::Exists(Path::Combine(input->Text, "VIDEO_TS.IFO")) ? new dynamic_cast<ChapterExtractor*>(DvdExtractor()) : Directory::Exists(Path::Combine(Path::Combine(input->Text, "BDMV"), "PLAYLIST")) ? new dynamic_cast<ChapterExtractor*>(BlurayExtractor()) : 0;

						if (ex == 0)
							throw std::exception("The location was not detected as DVD, or Blu-Ray.");

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//						using (frmStreamSelect frm = new frmStreamSelect(ex))
						frmStreamSelect *frm = new frmStreamSelect(ex);
						try
						{
							if (dynamic_cast<DvdExtractor*>(ex) != 0)
								frm->Text = "Select your Title";
							else
								frm->Text = "Select your Playlist";
							ex->GetStreams(input->Text);
							if (frm->getChapterCount() == 1 || frm->show(this) == System::Windows::Forms::DialogResult::OK)
							{
								pgc = frm->getSelectedSingleChapterInfo();
								if (pgc->getFramesPerSecond() == 0)
									pgc->setFramesPerSecond(25.0);
								if (pgc->getLangCode().empty())
									pgc->setLangCode("und");
							}
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
						finally
						{
							if (frm != 0)
								frm.Dispose();
						}
						FreshChapterView();
						updateTimeLine();
					}
					catch (std::exception &ex)
					{
						MessageBox::Show(ex.what());
					}
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (d != 0)
					d.Dispose();
			}
		}

		if (chapterListView->Items->Count != 0)
			chapterListView->Items[0]->Selected = true;
	}

	void ChapterCreator::showVideoButton_Click()
	{
		if (!this->videoInput.Equals(""))
		{
			if (player == 0)
			{
				player = new VideoPlayer();
				bool videoLoaded = player->loadVideo(mainForm, videoInput, CHAPTERS, false);
				if (videoLoaded)
				{
					player->Closed += new EventHandler(this, &ChapterCreator::player_Closed);
					player->ChapterSet += new ChapterSetCallback(this, &ChapterCreator::player_ChapterSet);
					if (introEndFrame > 0)
						player->setIntroEnd(this->introEndFrame);
					if (creditsStartFrame > 0)
						player->setCreditsStart(this->creditsStartFrame);
					player->Show();
					player->SetScreenSize();
					this->TopMost = player->TopMost = true;
					if (!mainForm->getSettings()->getAlwaysOnTop())
						this->TopMost = player->TopMost = false;
				}
				else
					return;
			}
			if (chapterListView->SelectedItems->Count == 1 && chapterListView->SelectedItems[0]->Tag != 0) // a zone has been selected, show that zone
			{
				Chapter chap = static_cast<Chapter>(chapterListView->SelectedItems[0]->Tag);
				int time = Util::getTimeCode(chap.timecode);
				double framerate = player->getFramerate();
				int frameNumber = Util::convertTimecodeToFrameNumber(time, framerate);
				player->setCurrentFrame(frameNumber);

			}
			else // no chapter has been selected.. but if start time is configured, show the frame in the preview
			{
				if (!startTime->Text->Equals(""))
				{
					int time = Util::getTimeCode(startTime->Text);
					double framerate = player->getFramerate();
					int frameNumber = Util::convertTimecodeToFrameNumber(time, framerate);
					player->setCurrentFrame(frameNumber);
				}
			}
		}
		else
			MessageBox::Show("Please configure video input first", "No video input found", MessageBoxButtons::OK, MessageBoxIcon::Stop);
	}

	void ChapterCreator::setVideoInput(const QString &value)
	{
		this->videoInput = value;
		showVideoButton->Enabled = true;
	}

	const int &ChapterCreator::getCreditsStartFrame() const
	{
		return this->creditsStartFrame;
	}

	void ChapterCreator::setCreditsStartFrame(const int &value)
	{
		creditsStartFrame = value;
	}

	const int &ChapterCreator::getIntroEndFrame() const
	{
		return this->introEndFrame;
	}

	void ChapterCreator::setIntroEndFrame(const int &value)
	{
		introEndFrame = value;
	}

	void ChapterCreator::player_Closed()
	{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete player;
	}

	void ChapterCreator::player_ChapterSet(int frameNumber)
	{
		QString strChapter;
		startTime->Text = Util::converFrameNumberToTimecode(frameNumber, player->getFramerate());
		if (chapterListView->SelectedIndices->Count == 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			strChapter = "Chapter " + (chapterListView->Items->Count + 1).ToString("00");
		else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			strChapter = "Chapter " + (chapterListView->SelectedIndices[0] + 1)->ToString("00");
		if (!chapterName->Text->Equals(strChapter))
			chapterName->Text = strChapter;
		if (chapterListView->SelectedIndices->Count == 0)
			addZoneButton_Click(0, 0);
	}

	void ChapterCreator::ChapterCreator_Load()
	{

		if (VistaStuff::getIsVistaOrNot())
		{
			VistaStuff::SetWindowTheme(chapterListView->Handle, "explorer", 0);
		}
	}

	void ChapterCreator::chapterName_TextChanged()
	{
		try
		{
			if (chapterListView->SelectedIndices->Count == 0)
				return;
			intIndex = chapterListView->SelectedIndices[0];
			pgc->getChapters()[intIndex] = Chapter(new object[] {Time = TimeSpan::Parse(startTime->Text), Name = chapterName->Text});
			chapterListView->SelectedItems[0]->SubItems[0]->Text = startTime->Text;
			chapterListView->SelectedItems[0]->SubItems[1]->Text = chapterName->Text;
		}
		catch (std::exception &parse)
		{ //invalid time input
			startTime->Focus();
			startTime->SelectAll();
			MessageBox::Show("Cannot parse the timecode you have entered.\nIt must be given in the hh:mm:ss.ccc format" + "\r\n" + parse.what(), "Incorrect timecode", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return;
		}
	}

	void ChapterCreator::InitializeInstanceFields()
	{
		introEndFrame = 0
		creditsStartFrame = 0;
		delete components;
	}

	const TimeSpan &Chapter::getTime() const
	{
		return privateTime;
	}

	void Chapter::setTime(const TimeSpan &value)
	{
		privateTime = value;
	}

	const QString &Chapter::getName() const
	{
		return privateName;
	}

	void Chapter::setName(const QString &value)
	{
		privateName = value;
	}

	QString Chapter::ToString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return getTime()->ToString() + ": " + getName();
	}

	const QString &ChapterCreatorTool::getName() const
	{
		return "Chapter Creator";
	}

	void ChapterCreatorTool::Run(MainForm *info)
	{
		ChapterCreator *cc = new ChapterCreator(info);
		cc->setVideoInput(info->getVideo()->getInfo()->getVideoInput());
		cc->setCreditsStartFrame(info->getVideo()->getInfo()->getCreditsStartFrame());
		cc->setIntroEndFrame(info->getVideo()->getInfo()->getIntroEndFrame());
		cc->Show();
	}

	const Shortcut &ChapterCreatorTool::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlH};
	}

	const QString &ChapterCreatorTool::getID() const
	{
		return "chapter_creator";
	}
}
