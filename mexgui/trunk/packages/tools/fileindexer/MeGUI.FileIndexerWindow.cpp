#include "MeGUI.FileIndexerWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{

	void FileIndexerWindow::setConfig(const std::string &input, const std::string &projectName, int demuxType, bool showCloseOnQueue, bool closeOnQueue, bool loadOnComplete, bool updateMode)
	{
		openVideo(input);
		if (!projectName.empty())
			this->output->Text = projectName;
		if (demuxType == 0)
			demuxNoAudiotracks->Checked = true;
		else
			demuxAll->Checked = true;
		this->loadOnComplete->Checked = loadOnComplete;
		if (updateMode)
		{
			this->dialogMode = true;
			queueButton->Text = "Update";
		}
		else
			this->dialogMode = false;
		checkIndexIO();
		if (!showCloseOnQueue)
		{
			this->closeOnQueue->Hide();
			this->Controls->Remove(this->closeOnQueue);
		}
		this->closeOnQueue->Checked = closeOnQueue;
	}

	FileIndexerWindow::FileIndexerWindow(MainForm *mainForm)
	{
		InitializeInstanceFields();
		InitializeComponent();
		this->mainForm = mainForm;
		this->vUtil = new VideoUtil(mainForm);
		this->jobUtil = new JobUtil(mainForm);
		CheckDGIIndexer();
	}

	FileIndexerWindow::FileIndexerWindow(MainForm *mainForm, const std::string &fileName)
	{
		InitializeInstanceFields();
		CheckDGIIndexer();
		openVideo(fileName);
	}

	FileIndexerWindow::FileIndexerWindow(MainForm *mainForm, const std::string &fileName, bool autoReturn)
	{
		InitializeInstanceFields();
		CheckDGIIndexer();
		openVideo(fileName);
		this->loadOnComplete->Checked = true;
		this->closeOnQueue->Checked = true;
		checkIndexIO();
	}

	void FileIndexerWindow::CheckDGIIndexer()
	{
		if (MainForm::Instance->getSettings()->IsDGIIndexerAvailable())
		{
			input->setFilter("All DGAVCIndex supported files|*.264;*.h264;*.avc;*.m2t*;*.m2ts;*.mts;*.tp;*.ts;*.trp|All DGIndex supported files|*.vob;*.mpg;*.mpeg;*.m1v;*.m2v;*.mpv;*.tp;*.ts;*.trp;*.m2t;*.m2ts;*.pva;*.vro|All DGIndexNV supported files|*.264;*.h264;*.avc;*.m2v;*.mpv;*.vc1;*.mkv;*.vob;*.mpg;*.mpeg;*.m2t;*.m2ts;*.mts;*.tp;*.ts;*.trp|All FFMS Indexer supported files|*.mkv;*.avi;*.mp4;*.flv;*.wmv;*.ogm;*.vob;*.mpg;*.m2ts;*.ts|All supported files|*.mkv;*.avi;*.mp4;*.flv;*.wmv;*.ogm;*.264;*.h264;*.avc;*.m2t*;*.m2ts;*.mts;*.tp;*.ts;*.trp;*.vob;*.mpg;*.mpeg;*.m1v;*.m2v;*.mpv;*.pva;*.vro;*.vc1|All files|*.*");
			input->setFilterIndex(5);
		}
		else
		{
			input->setFilter("All DGAVCIndex supported files|*.264;*.h264;*.avc;*.m2t*;*.m2ts;*.mts;*.tp;*.ts;*.trp|All DGIndex supported files|*.vob;*.mpg;*.mpeg;*.m1v;*.m2v;*.mpv;*.tp;*.ts;*.trp;*.m2t;*.m2ts;*.pva;*.vro|All FFMS Indexer supported files|*.mkv;*.avi;*.mp4;*.flv;*.wmv;*.ogm;*.vob;*.mpg;*.m2ts;*.ts|All supported files|*.mkv;*.avi;*.mp4;*.flv;*.wmv;*.ogm;*.264;*.h264;*.avc;*.m2t*;*.m2ts;*.mts;*.tp;*.ts;*.trp;*.vob;*.mpg;*.mpeg;*.m1v;*.m2v;*.mpv;*.pva;*.vro|All files|*.*");
			input->setFilterIndex(4);
		}
	}

	void FileIndexerWindow::changeIndexer(IndexType dgType)
	{
		switch (dgType)
		{
			case DGI:
			{
					this->saveProjectDialog->Filter = "DGIndexNV project files|*.dgi";
					if (this->demuxTracks->Checked)
						this->demuxAll->Checked = true;
					this->demuxTracks->Enabled = false;
					//this.gbAudio.Enabled = true;
					this->gbAudio->Text = " Audio Demux ";
					this->gbOutput->Enabled = true;
					this->demuxVideo->Enabled = true;
					IndexerUsed = DGI;
					btnDGI->Checked = true;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
					if (txtContainerInformation->Text->Trim()->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MATROSKA"))
						generateAudioList();
					break;
			}
			case DGA:
			{
					this->saveProjectDialog->Filter = "DGAVCIndex project files|*.dga";
					//this.gbOutput.Enabled = true;
					this->gbAudio->Enabled = true;
					this->gbAudio->Text = " Audio Demux ";
					if (this->demuxTracks->Checked)
						this->demuxAll->Checked = true;
					this->demuxTracks->Enabled = false;
					this->demuxVideo->Enabled = true;
					IndexerUsed = DGA;
					btnDGA->Checked = true;
					break;
			}
			case D2V:
			{
					this->saveProjectDialog->Filter = "DGIndex project files|*.d2v";
					this->demuxTracks->Enabled = true;
					//this.gbOutput.Enabled = true;
					this->gbAudio->Text = " Audio Demux ";
					this->gbAudio->Enabled = true;
					this->demuxVideo->Enabled = true;
					IndexerUsed = D2V;
					btnD2V->Checked = true;
					break;
			}
			case FFMS:
			{
					this->saveProjectDialog->Filter = "FFMSIndex project files|*.ffindex";
					//this.gbOutput.Enabled = false;
					this->gbAudio->Enabled = true;
					if (this->demuxTracks->Checked)
						this->demuxAll->Checked = true;
					this->demuxTracks->Enabled = true;
					this->demuxVideo->Checked = false;
					this->demuxVideo->Enabled = false;
					IndexerUsed = FFMS;
					btnFFMS->Checked = true;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
					if (txtContainerInformation->Text->Trim()->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MATROSKA"))
					{
						generateAudioList();
						this->gbAudio->Text = " Audio Demux ";
					}
					else
						this->gbAudio->Text = " Audio Encoding ";
					break;
			}
		}
		setOutputFileName();
		recommendSettings();
		if (!demuxTracks->Checked)
			rbtracks_CheckedChanged(0, 0);
	}

	void FileIndexerWindow::pickOutputButton_Click(object *sender, System::EventArgs *e)
	{
		if (!output->Text->empty())
		{
			saveProjectDialog->InitialDirectory = Path::GetDirectoryName(output->Text);
			saveProjectDialog->FileName = Path::GetFileName(output->Text);
		}
		if (saveProjectDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			output->Text = saveProjectDialog->FileName;
			checkIndexIO();
		}
	}

	void FileIndexerWindow::input_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		openVideo(input->getFilename());
		checkIndexIO();
	}

	void FileIndexerWindow::openVideo(const std::string &fileName)
	{
		this->_oLog = mainForm->getFileIndexerLog();
		if (_oLog == 0)
		{
			_oLog = mainForm->getLog()->Info("FileIndexer");
			mainForm->setFileIndexerLog(_oLog);
		}
		MediaInfoFile *iFile = new MediaInfoFile(fileName, _oLog);

		strVideoCodec = iFile->getVideoInfo()->getTrack()->getCodec();
		strVideoScanType = iFile->getVideoInfo()->getScanType();
		strContainerFormat = iFile->getContainerFileTypeString();
		audioTracks = iFile->getAudioInfo()->getTracks();

		if (strVideoCodec.empty())
			txtCodecInformation->Text = " unknown";
		else
			txtCodecInformation->Text = " " + strVideoCodec;
		if (strContainerFormat.empty())
			txtContainerInformation->Text = " unknown";
		else
			txtContainerInformation->Text = " " + strContainerFormat;
		if (strVideoScanType.empty())
			txtScanTypeInformation->Text = " unknown";
		else
			txtScanTypeInformation->Text = " " + strVideoScanType;

		cbPGC->Items->Clear();
		if (iFile->getVideoInfo()->PGCCount <= 0)
			cbPGC->Items->Add("none");
		else if (iFile->getVideoInfo()->PGCCount == 1)
			cbPGC->Items->Add("all");
		else
		{
			cbPGC->Items->Add("all");
			for (int i = 1; i < iFile->getVideoInfo()->PGCCount; i++)
				cbPGC->Items->Add(StringConverterHelper::toString(i));
		}
		cbPGC->SelectedIndex = 0;
		cbPGC->Enabled = iFile->getVideoInfo()->PGCCount > 1;

		if (input->getFilename() != fileName)
			input->setFilename(fileName);

		generateAudioList();

		btnD2V->Enabled = iFile->isD2VIndexable();
		btnDGA->Enabled = iFile->isDGAIndexable();
		btnDGI->Enabled = iFile->isDGIIndexable();
		btnFFMS->Enabled = iFile->isFFMSIndexable();

		IndexType newType = NONE;
		iFile->recommendIndexer(newType);
		if (newType == D2V || newType == DGA || newType == DGI || newType == FFMS)
		{
			gbIndexer->Enabled = gbAudio->Enabled = gbOutput->Enabled = true;
			changeIndexer(newType);
		}
		else
		{
			gbIndexer->Enabled = gbAudio->Enabled = gbOutput->Enabled = false;
			btnFFMS->Checked = btnD2V->Checked = btnDGA->Checked = btnDGI->Checked = false;
			output->Text = "";
			demuxNoAudiotracks->Checked = true;
			MessageBox::Show("No indexer for this file found. Please try open it directly in the AVS Script Creator", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

	void FileIndexerWindow::generateAudioList()
	{
		AudioTracks->Items->Clear();

		for (std::vector<AudioTrackInfo*>::const_iterator atrack = audioTracks.begin(); atrack != audioTracks.end(); ++atrack)
			AudioTracks->Items->Add(*atrack);
	}

	void FileIndexerWindow::recommendSettings()
	{
		if (AudioTracks->Items->Count > 0)
		{
			if (IndexerUsed == D2V)
			{
				if (strContainerFormat.Equals("MPEG-PS"))
				{
					demuxTracks->Enabled = true;
				}
				else
				{
					if (demuxTracks->Checked)
						demuxAll->Checked = true;
					demuxTracks->Enabled = false;
				}
			}
		}
		else
		{
			demuxNoAudiotracks->Checked = true;
			demuxTracks->Enabled = false;
		}
		AudioTracks->Enabled = demuxTracks->Checked;

		if (IndexerUsed == FFMS)
		{
			if (!strContainerFormat.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MATROSKA") && !strContainerFormat.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("AVI") && !strContainerFormat.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MPEG-4") && !strContainerFormat.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("FLASH VIDEO"))
			{
				MessageBox::Show("It is recommended to use a MKV, AVI, MP4 or FLV container to index files with the FFMS2 indexer", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
	}

	void FileIndexerWindow::setOutputFileName()
	{
		if (!this->input->getFilename().empty())
		{
			std::string projectPath = "";
			std::string fileNameNoPath = Path::GetFileName(this->input->getFilename());
			if ((projectPath = mainForm->getSettings()->getDefaultOutputDir())->empty())
				projectPath = Path::GetDirectoryName(this->input->getFilename());
			switch (IndexerUsed)
			{
				case D2V:
					output->Text = Path::Combine(projectPath, Path::ChangeExtension(fileNameNoPath, ".d2v"));
					;
					break;
				case DGA:
					output->Text = Path::Combine(projectPath, Path::ChangeExtension(fileNameNoPath, ".dga"));
					;
					break;
				case DGI:
					output->Text = Path::Combine(projectPath, Path::ChangeExtension(fileNameNoPath, ".dgi"));
					;
					break;
				case FFMS:
					output->Text = Path::Combine(projectPath, fileNameNoPath + ".ffindex");
					break;
			}
		}
	}

	void FileIndexerWindow::queueButton_Click(object *sender, System::EventArgs *e)
	{
		if (dialogMode)
			return;

		if (!configured)
		{
			MessageBox::Show("You must select the input and output file to continue", "Configuration incomplete", MessageBoxButtons::OK);
			return;
		}

		if (!Drives::ableToWriteOnThisDrive(Path::GetPathRoot(output->Text)))
		{
			MessageBox::Show("MeGUI cannot write on the disc " + Path::GetPathRoot(output->Text) + "\n" + "Please, select another output path to save your project...", "Configuration Incomplete", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		JobChain *prepareJobs = 0;
		std::string videoInput = input->getFilename();

		// create pgcdemux job if needed
		if (cbPGC->SelectedIndex > 0 && Path::GetExtension(input->getFilename().ToUpper(System::Globalization::CultureInfo::InvariantCulture)) == ".VOB")
		{
			std::string videoIFO;
			// PGC numbers are not present in VOB, so we check the main IFO
			if (Path::GetFileName(input->getFilename())->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->substr(0, 4) == "VTS_")
				videoIFO = input->getFilename().substr(0, input->getFilename().rfind("_")) + "_0.IFO";
			else
				videoIFO = Path::ChangeExtension(input->getFilename(), ".IFO");

			if (File::Exists(videoIFO))
			{
				prepareJobs = new SequentialChain(new PgcDemuxJob(videoIFO, Path::GetDirectoryName(output->Text), cbPGC->SelectedIndex));
				videoInput = Path::Combine(Path::GetDirectoryName(output->Text), "VTS_01_1.VOB");
				for (int i = 1; i < 10; i++)
				{
					std::string file = Path::Combine(Path::GetDirectoryName(output->Text), "VTS_01_" + i + ".VOB");
					if (File::Exists(file))
					{
						MessageBox::Show("The pgc demux file already exists: \n" + file + "\n\n" + "Please select another output path to save your project.", "Configuration Incomplete", MessageBoxButtons::OK, MessageBoxIcon::Warning);
						return;
					}
				}
			}
		}

		switch (IndexerUsed)
		{
			case D2V:
			{
					prepareJobs = new SequentialChain(prepareJobs, new SequentialChain(generateD2VIndexJob(videoInput)));
					mainForm->getJobs()->addJobsWithDependencies(prepareJobs, true);
					if (this->closeOnQueue->Checked)
						this->Close();
					break;
			}
			case DGI:
			{
					prepareJobs = new SequentialChain(prepareJobs, new SequentialChain(generateDGNVIndexJob(videoInput)));
					mainForm->getJobs()->addJobsWithDependencies(prepareJobs, true);
					if (this->closeOnQueue->Checked)
						this->Close();
					break;
			}
			case DGA:
			{
					prepareJobs = new SequentialChain(prepareJobs, new SequentialChain(generateDGAIndexJob(videoInput)));
					mainForm->getJobs()->addJobsWithDependencies(prepareJobs, true);
					if (this->closeOnQueue->Checked)
						this->Close();
					break;
			}
			case FFMS:
			{
					FFMSIndexJob *job = generateFFMSIndexJob(videoInput);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
					if (txtContainerInformation->Text->Trim()->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("MATROSKA") && job->getDemuxMode() > 0 && job->getAudioTracks().size() > 0)
					{
						job->setAudioTracksDemux(job->getAudioTracks());
						job->setAudioTracks(std::vector<AudioTrackInfo*>());
						MkvExtractJob *extractJob = new MkvExtractJob(videoInput, Path::GetDirectoryName(this->output->Text), job->getAudioTracksDemux());
						prepareJobs = new SequentialChain(prepareJobs, new SequentialChain(extractJob));
					}
					prepareJobs = new SequentialChain(prepareJobs, new SequentialChain(job));
					mainForm->getJobs()->addJobsWithDependencies(prepareJobs, true);
					if (this->closeOnQueue->Checked)
						this->Close();
					break;
			}
		}
	}

	void FileIndexerWindow::checkIndexIO()
	{
		configured = (!input->getFilename().Equals("") && !output->Text->Equals(""));
		if (configured && dialogMode)
			queueButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		else
			queueButton->DialogResult = System::Windows::Forms::DialogResult::None;
	}

	D2VIndexJob *FileIndexerWindow::generateD2VIndexJob(const std::string &videoInput)
	{
		int demuxType = 0;
		if (demuxTracks->Checked)
			demuxType = 1;
		else if (demuxNoAudiotracks->Checked)
			demuxType = 0;
		else
			demuxType = 2;

		std::vector<AudioTrackInfo*> audioTracks = std::vector<AudioTrackInfo*>();
		for (unknown::const_iterator ati = AudioTracks->CheckedItems.begin(); ati != AudioTracks->CheckedItems.end(); ++ati)
			audioTracks.push_back(*ati);

		return new D2VIndexJob(videoInput, this->output->Text, demuxType, audioTracks, loadOnComplete->Checked, demuxVideo->Checked);
	}

	DGIIndexJob *FileIndexerWindow::generateDGNVIndexJob(const std::string &videoInput)
	{
		int demuxType = 0;
		if (demuxTracks->Checked)
			demuxType = 1;
		else if (demuxNoAudiotracks->Checked)
			demuxType = 0;
		else
			demuxType = 2;

		std::vector<AudioTrackInfo*> audioTracks = std::vector<AudioTrackInfo*>();
		for (unknown::const_iterator ati = AudioTracks->CheckedItems.begin(); ati != AudioTracks->CheckedItems.end(); ++ati)
			audioTracks.push_back(*ati);

		return new DGIIndexJob(videoInput, this->output->Text, demuxType, audioTracks, loadOnComplete->Checked, demuxVideo->Checked);
	}

	DGAIndexJob *FileIndexerWindow::generateDGAIndexJob(const std::string &videoInput)
	{
		int demuxType = 0;
		if (demuxTracks->Checked)
			demuxType = 1;
		else if (demuxNoAudiotracks->Checked)
			demuxType = 0;
		else
			demuxType = 2;

		std::vector<AudioTrackInfo*> audioTracks = std::vector<AudioTrackInfo*>();
		for (unknown::const_iterator ati = AudioTracks->CheckedItems.begin(); ati != AudioTracks->CheckedItems.end(); ++ati)
			audioTracks.push_back(*ati);

		return new DGAIndexJob(videoInput, this->output->Text, demuxType, audioTracks, loadOnComplete->Checked, demuxVideo->Checked);
	}

	FFMSIndexJob *FileIndexerWindow::generateFFMSIndexJob(const std::string &videoInput)
	{
		int demuxType = 0;
		if (demuxTracks->Checked)
			demuxType = 1;
		else if (demuxNoAudiotracks->Checked)
			demuxType = 0;
		else
			demuxType = 2;

		std::vector<AudioTrackInfo*> audioTracks = std::vector<AudioTrackInfo*>();
		for (unknown::const_iterator ati = AudioTracks->CheckedItems.begin(); ati != AudioTracks->CheckedItems.end(); ++ati)
			audioTracks.push_back(*ati);

		return new FFMSIndexJob(videoInput, output->Text, demuxType, audioTracks, loadOnComplete->Checked);
	}

	void FileIndexerWindow::rbtracks_CheckedChanged(object *sender, EventArgs *e)
	{
		// Now defaults to starting with every track selected
		for (int i = 0; i < AudioTracks->Items->Count; i++)
			AudioTracks->SetItemChecked(i, !demuxNoAudiotracks->Checked);
		AudioTracks->Enabled = demuxTracks->Checked;
	}

	void FileIndexerWindow::btnFFMS_Click(object *sender, EventArgs *e)
	{
		changeIndexer(FFMS);
	}

	void FileIndexerWindow::btnDGI_Click(object *sender, EventArgs *e)
	{
		changeIndexer(DGI);
	}

	void FileIndexerWindow::btnDGA_Click(object *sender, EventArgs *e)
	{
		changeIndexer(DGA);
	}

	void FileIndexerWindow::btnD2V_Click(object *sender, EventArgs *e)
	{
		changeIndexer(D2V);
	}

	void FileIndexerWindow::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void FileIndexerWindow::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(FileIndexerWindow::typeid);
		this->gbInput = new System::Windows::Forms::GroupBox();
		this->input = new MeGUI::FileBar();
		this->inputLabel = new System::Windows::Forms::Label();
		this->queueButton = new System::Windows::Forms::Button();
		this->loadOnComplete = new System::Windows::Forms::CheckBox();
		this->gbAudio = new System::Windows::Forms::GroupBox();
		this->demuxAll = new System::Windows::Forms::RadioButton();
		this->AudioTracks = new System::Windows::Forms::CheckedListBox();
		this->demuxNoAudiotracks = new System::Windows::Forms::RadioButton();
		this->demuxTracks = new System::Windows::Forms::RadioButton();
		this->gbOutput = new System::Windows::Forms::GroupBox();
		this->demuxVideo = new System::Windows::Forms::CheckBox();
		this->pickOutputButton = new System::Windows::Forms::Button();
		this->output = new System::Windows::Forms::TextBox();
		this->outputLabel = new System::Windows::Forms::Label();
		this->saveProjectDialog = new System::Windows::Forms::SaveFileDialog();
		this->closeOnQueue = new System::Windows::Forms::CheckBox();
		this->gbIndexer = new System::Windows::Forms::GroupBox();
		this->btnDGA = new System::Windows::Forms::RadioButton();
		this->btnFFMS = new System::Windows::Forms::RadioButton();
		this->btnD2V = new System::Windows::Forms::RadioButton();
		this->btnDGI = new System::Windows::Forms::RadioButton();
		this->gbFileInformation = new System::Windows::Forms::GroupBox();
		this->cbPGC = new System::Windows::Forms::ComboBox();
		this->lblPGC = new System::Windows::Forms::Label();
		this->txtContainerInformation = new System::Windows::Forms::TextBox();
		this->txtScanTypeInformation = new System::Windows::Forms::TextBox();
		this->txtCodecInformation = new System::Windows::Forms::TextBox();
		this->lblScanType = new System::Windows::Forms::Label();
		this->lblCodec = new System::Windows::Forms::Label();
		this->lblContainer = new System::Windows::Forms::Label();
		this->helpButton1 = new MeGUI::core::gui::HelpButton();
		this->gbInput->SuspendLayout();
		this->gbAudio->SuspendLayout();
		this->gbOutput->SuspendLayout();
		this->gbIndexer->SuspendLayout();
		this->gbFileInformation->SuspendLayout();
		this->SuspendLayout();
		// 
		// gbInput
		// 
		this->gbInput->Controls->Add(this->input);
		this->gbInput->Controls->Add(this->inputLabel);
		this->gbInput->Location = new System::Drawing::Point(12, 6);
		this->gbInput->Name = "gbInput";
		this->gbInput->Size = new System::Drawing::Size(424, 50);
		this->gbInput->TabIndex = 0;
		this->gbInput->TabStop = false;
		this->gbInput->Text = " Input ";
		// 
		// input
		// 
		this->input->AllowDrop = true;
		this->input->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->input->setFilename("");
		this->input->setFilter("");
		this->input->setFilterIndex(0);
		this->input->setFolderMode(false);
		this->input->Location = new System::Drawing::Point(77, 10);
		this->input->Name = "input";
		this->input->setReadOnly(true);
		this->input->setSaveMode(false);
		this->input->Size = new System::Drawing::Size(329, 34);
		this->input->TabIndex = 4;
		this->input->setTitle("");
		this->input->FileSelected += new MeGUI::FileBarEventHandler(this, &FileIndexerWindow::input_FileSelected);
		// 
		// inputLabel
		// 
		this->inputLabel->Location = new System::Drawing::Point(9, 22);
		this->inputLabel->Name = "inputLabel";
		this->inputLabel->Size = new System::Drawing::Size(100, 13);
		this->inputLabel->TabIndex = 0;
		this->inputLabel->Text = "Input File";
		// 
		// queueButton
		// 
		this->queueButton->Location = new System::Drawing::Point(362, 395);
		this->queueButton->Name = "queueButton";
		this->queueButton->Size = new System::Drawing::Size(74, 23);
		this->queueButton->TabIndex = 10;
		this->queueButton->Text = "Queue";
		this->queueButton->Click += new System::EventHandler(this, &FileIndexerWindow::queueButton_Click);
		// 
		// loadOnComplete
		// 
		this->loadOnComplete->Checked = true;
		this->loadOnComplete->CheckState = System::Windows::Forms::CheckState::Checked;
		this->loadOnComplete->Location = new System::Drawing::Point(91, 395);
		this->loadOnComplete->Name = "loadOnComplete";
		this->loadOnComplete->Size = new System::Drawing::Size(144, 24);
		this->loadOnComplete->TabIndex = 11;
		this->loadOnComplete->Text = "On completion load files";
		// 
		// gbAudio
		// 
		this->gbAudio->Controls->Add(this->demuxAll);
		this->gbAudio->Controls->Add(this->AudioTracks);
		this->gbAudio->Controls->Add(this->demuxNoAudiotracks);
		this->gbAudio->Controls->Add(this->demuxTracks);
		this->gbAudio->Enabled = false;
		this->gbAudio->Location = new System::Drawing::Point(12, 187);
		this->gbAudio->Name = "gbAudio";
		this->gbAudio->Size = new System::Drawing::Size(424, 125);
		this->gbAudio->TabIndex = 8;
		this->gbAudio->TabStop = false;
		this->gbAudio->Text = " Audio Demux ";
		// 
		// demuxAll
		// 
		this->demuxAll->AutoSize = true;
		this->demuxAll->Checked = true;
		this->demuxAll->Location = new System::Drawing::Point(304, 20);
		this->demuxAll->Name = "demuxAll";
		this->demuxAll->Size = new System::Drawing::Size(100, 17);
		this->demuxAll->TabIndex = 15;
		this->demuxAll->TabStop = true;
		this->demuxAll->Text = "All Audio Tracks";
		this->demuxAll->UseVisualStyleBackColor = true;
		this->demuxAll->CheckedChanged += new System::EventHandler(this, &FileIndexerWindow::rbtracks_CheckedChanged);
		// 
		// AudioTracks
		// 
		this->AudioTracks->CheckOnClick = true;
		this->AudioTracks->Enabled = false;
		this->AudioTracks->FormattingEnabled = true;
		this->AudioTracks->Location = new System::Drawing::Point(16, 43);
		this->AudioTracks->Name = "AudioTracks";
		this->AudioTracks->Size = new System::Drawing::Size(394, 68);
		this->AudioTracks->TabIndex = 14;
		// 
		// demuxNoAudiotracks
		// 
		this->demuxNoAudiotracks->Location = new System::Drawing::Point(19, 16);
		this->demuxNoAudiotracks->Name = "demuxNoAudiotracks";
		this->demuxNoAudiotracks->Size = new System::Drawing::Size(120, 24);
		this->demuxNoAudiotracks->TabIndex = 13;
		this->demuxNoAudiotracks->Text = "No Audio";
		this->demuxNoAudiotracks->CheckedChanged += new System::EventHandler(this, &FileIndexerWindow::rbtracks_CheckedChanged);
		// 
		// demuxTracks
		// 
		this->demuxTracks->Enabled = false;
		this->demuxTracks->Location = new System::Drawing::Point(155, 16);
		this->demuxTracks->Name = "demuxTracks";
		this->demuxTracks->Size = new System::Drawing::Size(120, 24);
		this->demuxTracks->TabIndex = 7;
		this->demuxTracks->Text = "Select Audio Tracks";
		this->demuxTracks->CheckedChanged += new System::EventHandler(this, &FileIndexerWindow::rbtracks_CheckedChanged);
		// 
		// gbOutput
		// 
		this->gbOutput->Controls->Add(this->demuxVideo);
		this->gbOutput->Controls->Add(this->pickOutputButton);
		this->gbOutput->Controls->Add(this->output);
		this->gbOutput->Controls->Add(this->outputLabel);
		this->gbOutput->Enabled = false;
		this->gbOutput->Location = new System::Drawing::Point(12, 318);
		this->gbOutput->Name = "gbOutput";
		this->gbOutput->Size = new System::Drawing::Size(424, 69);
		this->gbOutput->TabIndex = 12;
		this->gbOutput->TabStop = false;
		this->gbOutput->Text = " Output ";
		// 
		// demuxVideo
		// 
		this->demuxVideo->AutoSize = true;
		this->demuxVideo->Location = new System::Drawing::Point(81, 44);
		this->demuxVideo->Name = "demuxVideo";
		this->demuxVideo->Size = new System::Drawing::Size(125, 17);
		this->demuxVideo->TabIndex = 6;
		this->demuxVideo->Text = "Demux Video Stream";
		this->demuxVideo->UseVisualStyleBackColor = true;
		// 
		// pickOutputButton
		// 
		this->pickOutputButton->Location = new System::Drawing::Point(380, 16);
		this->pickOutputButton->Name = "pickOutputButton";
		this->pickOutputButton->Size = new System::Drawing::Size(30, 23);
		this->pickOutputButton->TabIndex = 5;
		this->pickOutputButton->Text = "...";
		this->pickOutputButton->Click += new System::EventHandler(this, &FileIndexerWindow::pickOutputButton_Click);
		// 
		// output
		// 
		this->output->Location = new System::Drawing::Point(81, 17);
		this->output->Name = "output";
		this->output->ReadOnly = true;
		this->output->Size = new System::Drawing::Size(289, 21);
		this->output->TabIndex = 4;
		// 
		// outputLabel
		// 
		this->outputLabel->Location = new System::Drawing::Point(11, 21);
		this->outputLabel->Name = "outputLabel";
		this->outputLabel->Size = new System::Drawing::Size(100, 13);
		this->outputLabel->TabIndex = 3;
		this->outputLabel->Text = "Output File";
		// 
		// saveProjectDialog
		// 
		this->saveProjectDialog->Filter = "DGIndex project files|*.d2v";
		this->saveProjectDialog->Title = "Pick a name for your DGIndex project";
		// 
		// closeOnQueue
		// 
		this->closeOnQueue->Checked = true;
		this->closeOnQueue->CheckState = System::Windows::Forms::CheckState::Checked;
		this->closeOnQueue->Location = new System::Drawing::Point(281, 395);
		this->closeOnQueue->Name = "closeOnQueue";
		this->closeOnQueue->Size = new System::Drawing::Size(72, 24);
		this->closeOnQueue->TabIndex = 13;
		this->closeOnQueue->Text = "and close";
		// 
		// gbIndexer
		// 
		this->gbIndexer->Controls->Add(this->btnDGA);
		this->gbIndexer->Controls->Add(this->btnFFMS);
		this->gbIndexer->Controls->Add(this->btnD2V);
		this->gbIndexer->Controls->Add(this->btnDGI);
		this->gbIndexer->Enabled = false;
		this->gbIndexer->Location = new System::Drawing::Point(12, 135);
		this->gbIndexer->Name = "gbIndexer";
		this->gbIndexer->Size = new System::Drawing::Size(424, 46);
		this->gbIndexer->TabIndex = 15;
		this->gbIndexer->TabStop = false;
		this->gbIndexer->Text = " File Indexer ";
		// 
		// btnDGA
		// 
		this->btnDGA->AutoSize = true;
		this->btnDGA->Location = new System::Drawing::Point(115, 19);
		this->btnDGA->Name = "btnDGA";
		this->btnDGA->Size = new System::Drawing::Size(87, 17);
		this->btnDGA->TabIndex = 3;
		this->btnDGA->TabStop = true;
		this->btnDGA->Text = "DGAVCIndex";
		this->btnDGA->UseVisualStyleBackColor = true;
		this->btnDGA->Click += new System::EventHandler(this, &FileIndexerWindow::btnDGA_Click);
		// 
		// btnFFMS
		// 
		this->btnFFMS->AutoSize = true;
		this->btnFFMS->Location = new System::Drawing::Point(329, 19);
		this->btnFFMS->Name = "btnFFMS";
		this->btnFFMS->Size = new System::Drawing::Size(79, 17);
		this->btnFFMS->TabIndex = 2;
		this->btnFFMS->TabStop = true;
		this->btnFFMS->Text = "FFMSIndex";
		this->btnFFMS->UseVisualStyleBackColor = true;
		this->btnFFMS->Click += new System::EventHandler(this, &FileIndexerWindow::btnFFMS_Click);
		// 
		// btnD2V
		// 
		this->btnD2V->AutoSize = true;
		this->btnD2V->Location = new System::Drawing::Point(12, 20);
		this->btnD2V->Name = "btnD2V";
		this->btnD2V->Size = new System::Drawing::Size(67, 17);
		this->btnD2V->TabIndex = 1;
		this->btnD2V->TabStop = true;
		this->btnD2V->Text = "DGIndex";
		this->btnD2V->UseVisualStyleBackColor = true;
		this->btnD2V->Click += new System::EventHandler(this, &FileIndexerWindow::btnD2V_Click);
		// 
		// btnDGI
		// 
		this->btnDGI->AutoSize = true;
		this->btnDGI->Location = new System::Drawing::Point(229, 19);
		this->btnDGI->Name = "btnDGI";
		this->btnDGI->Size = new System::Drawing::Size(80, 17);
		this->btnDGI->TabIndex = 0;
		this->btnDGI->TabStop = true;
		this->btnDGI->Text = "DGIndexNV";
		this->btnDGI->UseVisualStyleBackColor = true;
		this->btnDGI->Click += new System::EventHandler(this, &FileIndexerWindow::btnDGI_Click);
		// 
		// gbFileInformation
		// 
		this->gbFileInformation->Controls->Add(this->cbPGC);
		this->gbFileInformation->Controls->Add(this->lblPGC);
		this->gbFileInformation->Controls->Add(this->txtContainerInformation);
		this->gbFileInformation->Controls->Add(this->txtScanTypeInformation);
		this->gbFileInformation->Controls->Add(this->txtCodecInformation);
		this->gbFileInformation->Controls->Add(this->lblScanType);
		this->gbFileInformation->Controls->Add(this->lblCodec);
		this->gbFileInformation->Controls->Add(this->lblContainer);
		this->gbFileInformation->Location = new System::Drawing::Point(12, 62);
		this->gbFileInformation->Name = "gbFileInformation";
		this->gbFileInformation->Size = new System::Drawing::Size(424, 67);
		this->gbFileInformation->TabIndex = 16;
		this->gbFileInformation->TabStop = false;
		this->gbFileInformation->Text = " File Information ";
		// 
		// cbPGC
		// 
		this->cbPGC->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbPGC->Enabled = false;
		this->cbPGC->FormattingEnabled = true;
		this->cbPGC->Location = new System::Drawing::Point(354, 34);
		this->cbPGC->Name = "cbPGC";
		this->cbPGC->Size = new System::Drawing::Size(56, 21);
		this->cbPGC->TabIndex = 7;
		// 
		// lblPGC
		// 
		this->lblPGC->AutoSize = true;
		this->lblPGC->Location = new System::Drawing::Point(351, 18);
		this->lblPGC->Name = "lblPGC";
		this->lblPGC->Size = new System::Drawing::Size(27, 13);
		this->lblPGC->TabIndex = 6;
		this->lblPGC->Text = "PGC";
		// 
		// txtContainerInformation
		// 
		this->txtContainerInformation->Enabled = false;
		this->txtContainerInformation->Location = new System::Drawing::Point(240, 34);
		this->txtContainerInformation->Name = "txtContainerInformation";
		this->txtContainerInformation->Size = new System::Drawing::Size(108, 21);
		this->txtContainerInformation->TabIndex = 5;
		// 
		// txtScanTypeInformation
		// 
		this->txtScanTypeInformation->Enabled = false;
		this->txtScanTypeInformation->Location = new System::Drawing::Point(126, 34);
		this->txtScanTypeInformation->Name = "txtScanTypeInformation";
		this->txtScanTypeInformation->Size = new System::Drawing::Size(108, 21);
		this->txtScanTypeInformation->TabIndex = 4;
		// 
		// txtCodecInformation
		// 
		this->txtCodecInformation->Enabled = false;
		this->txtCodecInformation->Location = new System::Drawing::Point(12, 34);
		this->txtCodecInformation->Name = "txtCodecInformation";
		this->txtCodecInformation->Size = new System::Drawing::Size(108, 21);
		this->txtCodecInformation->TabIndex = 3;
		// 
		// lblScanType
		// 
		this->lblScanType->AutoSize = true;
		this->lblScanType->Location = new System::Drawing::Point(123, 18);
		this->lblScanType->Name = "lblScanType";
		this->lblScanType->Size = new System::Drawing::Size(57, 13);
		this->lblScanType->TabIndex = 2;
		this->lblScanType->Text = "Scan Type";
		// 
		// lblCodec
		// 
		this->lblCodec->AutoSize = true;
		this->lblCodec->Location = new System::Drawing::Point(11, 18);
		this->lblCodec->Margin = new System::Windows::Forms::Padding(0);
		this->lblCodec->Name = "lblCodec";
		this->lblCodec->Size = new System::Drawing::Size(37, 13);
		this->lblCodec->TabIndex = 1;
		this->lblCodec->Text = "Codec";
		// 
		// lblContainer
		// 
		this->lblContainer->AutoSize = true;
		this->lblContainer->Location = new System::Drawing::Point(237, 18);
		this->lblContainer->Name = "lblContainer";
		this->lblContainer->Size = new System::Drawing::Size(54, 13);
		this->lblContainer->TabIndex = 0;
		this->lblContainer->Text = "Container";
		// 
		// helpButton1
		// 
		this->helpButton1->setArticleName("File Indexer window");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(13, 394);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 14;
		// 
		// FileIndexerWindow
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->ClientSize = new System::Drawing::Size(444, 425);
		this->Controls->Add(this->gbFileInformation);
		this->Controls->Add(this->gbIndexer);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->closeOnQueue);
		this->Controls->Add(this->gbInput);
		this->Controls->Add(this->gbOutput);
		this->Controls->Add(this->loadOnComplete);
		this->Controls->Add(this->queueButton);
		this->Controls->Add(this->gbAudio);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = "FileIndexerWindow";
		this->Text = "MeGUI - File Indexer";
		this->gbInput->ResumeLayout(false);
		this->gbAudio->ResumeLayout(false);
		this->gbAudio->PerformLayout();
		this->gbOutput->ResumeLayout(false);
		this->gbOutput->PerformLayout();
		this->gbIndexer->ResumeLayout(false);
		this->gbIndexer->PerformLayout();
		this->gbFileInformation->ResumeLayout(false);
		this->gbFileInformation->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void FileIndexerWindow::InitializeInstanceFields()
	{
		IndexerUsed = D2V;
		strVideoCodec = "";
		strVideoScanType = "";
		strContainerFormat = "";
		audioTracks = std::vector<AudioTrackInfo*>();
		dialogMode = false;
		configured = false;
		delete components;
	}
}
