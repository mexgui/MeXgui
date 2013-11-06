#include "SettingsForm.h"

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
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace MeGUI
{

	SettingsForm::SettingsForm()
	{
		InitializeInstanceFields();
		InitializeComponent();
		std::vector<std::string> keys = std::vector<std::string>(LanguageSelectionContainer::getLanguages().Keys);
		defaultLanguage2->DataSource = defaultLanguage1->DataSource = keys;
		defaultLanguage2->BindingContext = new BindingContext();
		defaultLanguage1->BindingContext = new BindingContext();
		SetToolTips();
	#if defined(x86)
		if (!OSInfo::isWow64())
			chkEnable64bitX264->Enabled = chkEnable64bitX264->Checked = false;
	#endif
	#if defined(x64)
		chkEnable64bitX264->Enabled = false;
		chkEnable64bitX264->Checked = true;
		chkEnable64bitX264->Visible = false;
	#endif
		ffmsThreads->Maximum = System::Environment::ProcessorCount;
	}

	void SettingsForm::SetToolTips()
	{
		try
		{
			std::string p = System::IO::Path::Combine(Application::StartupPath, "Data");
			p = System::IO::Path::Combine(p, "ContextHelp.xml");
			ContextHelp->Load(p);
		}
		catch (...)
		{
			MessageBox::Show("The ContextHelp.xml file could not be found. Please check in the 'Data' directory to see if it exists. Help tooltips will not be available.", "File Not Found", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}
		toolTipHelp->SetToolTip(chkAlwaysMuxMKV, SelectHelpText("alwaysmuxmkv"));
		toolTipHelp->SetToolTip(ffmsThreads, SelectHelpText("ffmsthreads"));
		toolTipHelp->SetToolTip(cbUseITUValues, SelectHelpText("useituvalues"));
	}

	std::string SettingsForm::SelectHelpText(const std::string &node)
	{
		StringBuilder *HelpText = new StringBuilder(64);

		std::string xpath = "/ContextHelp/Form[@name='SettingsForm']/" + node;
		XmlNodeList *nl = ContextHelp->SelectNodes(xpath); // Return the details for the specified node

		if (nl->Count == 1) // if it finds the required HelpText, count should be 1
		{
			HelpText->Append(nl[0]->Attributes["name"]->Value);
			HelpText->AppendLine();
			HelpText->AppendLine(nl[0]["Basic"]->InnerText);
		}
		else // If count isn't 1, then theres no valid data.
			HelpText->Append("Error: No data available");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return (HelpText->ToString());
	}

	void SettingsForm::Dispose(bool disposing)
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

	void SettingsForm::InitializeComponent()
	{
		this->components = new System::ComponentModel::Container();
		System::Windows::Forms::GroupBox *groupBox1;
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(SettingsForm::typeid);
		this->rbCloseMeGUI = new System::Windows::Forms::RadioButton();
		this->command = new System::Windows::Forms::TextBox();
		this->runCommand = new System::Windows::Forms::RadioButton();
		this->shutdown = new System::Windows::Forms::RadioButton();
		this->donothing = new System::Windows::Forms::RadioButton();
		this->saveButton = new System::Windows::Forms::Button();
		this->cancelButton = new System::Windows::Forms::Button();
		this->otherGroupBox = new System::Windows::Forms::GroupBox();
		this->cbOpenAVSinThread = new System::Windows::Forms::CheckBox();
		this->cbUseITUValues = new System::Windows::Forms::CheckBox();
		this->cbAutoStartQueueStartup = new System::Windows::Forms::CheckBox();
		this->forcerawavcuse = new System::Windows::Forms::CheckBox();
		this->audiosamplesperupdate = new System::Windows::Forms::NumericUpDown();
		this->label6 = new System::Windows::Forms::Label();
		this->acceptableFPSError = new System::Windows::Forms::NumericUpDown();
		this->label15 = new System::Windows::Forms::Label();
		this->resetDialogs = new System::Windows::Forms::Button();
		this->configSourceDetector = new System::Windows::Forms::Button();
		this->chkboxUseAdvancedTooltips = new System::Windows::Forms::CheckBox();
		this->openProgressWindow = new System::Windows::Forms::CheckBox();
		this->deleteIntermediateFiles = new System::Windows::Forms::CheckBox();
		this->deleteAbortedOutput = new System::Windows::Forms::CheckBox();
		this->deleteCompletedJobs = new System::Windows::Forms::CheckBox();
		this->openScript = new System::Windows::Forms::CheckBox();
		this->autostartQueue = new System::Windows::Forms::CheckBox();
		this->priority = new System::Windows::Forms::ComboBox();
		this->priorityLabel = new System::Windows::Forms::Label();
		this->openExecutableDialog = new System::Windows::Forms::OpenFileDialog();
		this->openFolderDialog = new System::Windows::Forms::FolderBrowserDialog();
		this->tabControl1 = new System::Windows::Forms::TabControl();
		this->tabPage1 = new System::Windows::Forms::TabPage();
		this->groupBox3 = new System::Windows::Forms::GroupBox();
		this->defaultLanguage2 = new System::Windows::Forms::ComboBox();
		this->defaultLanguage1 = new System::Windows::Forms::ComboBox();
		this->gbDefaultOutput = new System::Windows::Forms::GroupBox();
		this->targetSizeSCBox1 = new MeGUI::core::gui::TargetSizeSCBox();
		this->btnClearOutputDirecoty = new System::Windows::Forms::Button();
		this->clearDefaultOutputDir = new System::Windows::Forms::Button();
		this->defaultOutputDir = new MeGUI::FileBar();
		this->tabPage3 = new System::Windows::Forms::TabPage();
		this->groupBox2 = new System::Windows::Forms::GroupBox();
		this->label1 = new System::Windows::Forms::Label();
		this->cbHttpProxyMode = new System::Windows::Forms::ComboBox();
		this->txt_httpproxyport = new System::Windows::Forms::TextBox();
		this->txt_httpproxypwd = new System::Windows::Forms::TextBox();
		this->txt_httpproxyuid = new System::Windows::Forms::TextBox();
		this->txt_httpproxyaddress = new System::Windows::Forms::TextBox();
		this->label21 = new System::Windows::Forms::Label();
		this->label20 = new System::Windows::Forms::Label();
		this->label19 = new System::Windows::Forms::Label();
		this->label18 = new System::Windows::Forms::Label();
		this->gbVideoPreview = new System::Windows::Forms::GroupBox();
		this->chkEnsureCorrectPlaybackSpeed = new System::Windows::Forms::CheckBox();
		this->cbAddTimePos = new System::Windows::Forms::CheckBox();
		this->chAlwaysOnTop = new System::Windows::Forms::CheckBox();
		this->autoUpdateGroupBox = new System::Windows::Forms::GroupBox();
		this->cbAutoUpdateServerSubList = new System::Windows::Forms::ComboBox();
		this->backupfiles = new System::Windows::Forms::CheckBox();
		this->configureServersButton = new System::Windows::Forms::Button();
		this->useAutoUpdateCheckbox = new System::Windows::Forms::CheckBox();
		this->outputExtensions = new System::Windows::Forms::GroupBox();
		this->videoExtension = new System::Windows::Forms::TextBox();
		this->label11 = new System::Windows::Forms::Label();
		this->label12 = new System::Windows::Forms::Label();
		this->audioExtension = new System::Windows::Forms::TextBox();
		this->autoModeGroupbox = new System::Windows::Forms::GroupBox();
		this->chkAlwaysMuxMKV = new System::Windows::Forms::CheckBox();
		this->configAutoEncodeDefaults = new System::Windows::Forms::Button();
		this->keep2ndPassLogFile = new System::Windows::Forms::CheckBox();
		this->keep2ndPassOutput = new System::Windows::Forms::CheckBox();
		this->label13 = new System::Windows::Forms::Label();
		this->nbPasses = new System::Windows::Forms::NumericUpDown();
		this->tabPage2 = new System::Windows::Forms::TabPage();
		this->groupBox6 = new System::Windows::Forms::GroupBox();
		this->chUse10BitsX264 = new System::Windows::Forms::CheckBox();
		this->chx264ExternalMuxer = new System::Windows::Forms::CheckBox();
		this->useQAAC = new System::Windows::Forms::CheckBox();
		this->lblForcedName = new System::Windows::Forms::Label();
		this->txtForcedName = new System::Windows::Forms::TextBox();
		this->lblffmsThreads = new System::Windows::Forms::Label();
		this->ffmsThreads = new System::Windows::Forms::NumericUpDown();
		this->chkSelectHDTracks = new System::Windows::Forms::CheckBox();
		this->chkEnable64bitX264 = new System::Windows::Forms::CheckBox();
		this->groupBox5 = new System::Windows::Forms::GroupBox();
		this->useNeroAacEnc = new System::Windows::Forms::CheckBox();
		this->lblNero = new System::Windows::Forms::Label();
		this->neroaacencLocation = new MeGUI::FileBar();
		this->groupBox4 = new System::Windows::Forms::GroupBox();
		this->btnClearMP4TempDirectory = new System::Windows::Forms::Button();
		this->tempDirMP4 = new MeGUI::FileBar();
		this->vobGroupBox = new System::Windows::Forms::GroupBox();
		this->useDGIndexNV = new System::Windows::Forms::CheckBox();
		this->cbAutoLoadDG = new System::Windows::Forms::CheckBox();
		this->percentLabel = new System::Windows::Forms::Label();
		this->forceFilmPercentage = new System::Windows::Forms::NumericUpDown();
		this->autoForceFilm = new System::Windows::Forms::CheckBox();
		this->audioExtLabel = new System::Windows::Forms::Label();
		this->videoExtLabel = new System::Windows::Forms::Label();
		this->autoEncodeDefaultsButton = new System::Windows::Forms::Button();
		this->toolTipHelp = new System::Windows::Forms::ToolTip(this->components);
		this->helpButton1 = new MeGUI::core::gui::HelpButton();
		groupBox1 = new System::Windows::Forms::GroupBox();
		groupBox1->SuspendLayout();
		this->otherGroupBox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->audiosamplesperupdate))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->acceptableFPSError))->BeginInit();
		this->tabControl1->SuspendLayout();
		this->tabPage1->SuspendLayout();
		this->groupBox3->SuspendLayout();
		this->gbDefaultOutput->SuspendLayout();
		this->tabPage3->SuspendLayout();
		this->groupBox2->SuspendLayout();
		this->gbVideoPreview->SuspendLayout();
		this->autoUpdateGroupBox->SuspendLayout();
		this->outputExtensions->SuspendLayout();
		this->autoModeGroupbox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->nbPasses))->BeginInit();
		this->tabPage2->SuspendLayout();
		this->groupBox6->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->ffmsThreads))->BeginInit();
		this->groupBox5->SuspendLayout();
		this->groupBox4->SuspendLayout();
		this->vobGroupBox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->forceFilmPercentage))->BeginInit();
		this->SuspendLayout();
		// 
		// groupBox1
		// 
		groupBox1->Controls->Add(this->rbCloseMeGUI);
		groupBox1->Controls->Add(this->command);
		groupBox1->Controls->Add(this->runCommand);
		groupBox1->Controls->Add(this->shutdown);
		groupBox1->Controls->Add(this->donothing);
		groupBox1->Location = new System::Drawing::Point(4, 187);
		groupBox1->Name = "groupBox1";
		groupBox1->Size = new System::Drawing::Size(217, 95);
		groupBox1->TabIndex = 2;
		groupBox1->TabStop = false;
		groupBox1->Text = " After encoding ";
		// 
		// rbCloseMeGUI
		// 
		this->rbCloseMeGUI->AutoSize = true;
		this->rbCloseMeGUI->Location = new System::Drawing::Point(123, 43);
		this->rbCloseMeGUI->Name = "rbCloseMeGUI";
		this->rbCloseMeGUI->Size = new System::Drawing::Size(84, 17);
		this->rbCloseMeGUI->TabIndex = 4;
		this->rbCloseMeGUI->TabStop = true;
		this->rbCloseMeGUI->Text = "close MeGUI";
		this->rbCloseMeGUI->UseVisualStyleBackColor = true;
		// 
		// command
		// 
		this->command->Enabled = false;
		this->command->Location = new System::Drawing::Point(10, 64);
		this->command->Name = "command";
		this->command->Size = new System::Drawing::Size(197, 21);
		this->command->TabIndex = 3;
		// 
		// runCommand
		// 
		this->runCommand->AutoSize = true;
		this->runCommand->Location = new System::Drawing::Point(11, 43);
		this->runCommand->Name = "runCommand";
		this->runCommand->Size = new System::Drawing::Size(96, 17);
		this->runCommand->TabIndex = 2;
		this->runCommand->Text = "Run command:";
		this->runCommand->UseVisualStyleBackColor = true;
		this->runCommand->CheckedChanged += new System::EventHandler(this, &SettingsForm::runCommand_CheckedChanged);
		// 
		// shutdown
		// 
		this->shutdown->AutoSize = true;
		this->shutdown->Location = new System::Drawing::Point(123, 21);
		this->shutdown->Name = "shutdown";
		this->shutdown->Size = new System::Drawing::Size(73, 17);
		this->shutdown->TabIndex = 1;
		this->shutdown->Text = "Shutdown";
		this->shutdown->UseVisualStyleBackColor = true;
		// 
		// donothing
		// 
		this->donothing->AutoSize = true;
		this->donothing->Checked = true;
		this->donothing->Location = new System::Drawing::Point(11, 20);
		this->donothing->Name = "donothing";
		this->donothing->Size = new System::Drawing::Size(77, 17);
		this->donothing->TabIndex = 0;
		this->donothing->TabStop = true;
		this->donothing->Text = "Do nothing";
		this->donothing->UseVisualStyleBackColor = true;
		// 
		// saveButton
		// 
		this->saveButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->saveButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->saveButton->Location = new System::Drawing::Point(359, 418);
		this->saveButton->Name = "saveButton";
		this->saveButton->Size = new System::Drawing::Size(48, 23);
		this->saveButton->TabIndex = 2;
		this->saveButton->Text = "Save";
		// 
		// cancelButton
		// 
		this->cancelButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->cancelButton->Location = new System::Drawing::Point(430, 418);
		this->cancelButton->Name = "cancelButton";
		this->cancelButton->Size = new System::Drawing::Size(48, 23);
		this->cancelButton->TabIndex = 3;
		this->cancelButton->Text = "Cancel";
		// 
		// otherGroupBox
		// 
		this->otherGroupBox->Controls->Add(this->cbOpenAVSinThread);
		this->otherGroupBox->Controls->Add(this->cbUseITUValues);
		this->otherGroupBox->Controls->Add(this->cbAutoStartQueueStartup);
		this->otherGroupBox->Controls->Add(this->forcerawavcuse);
		this->otherGroupBox->Controls->Add(this->audiosamplesperupdate);
		this->otherGroupBox->Controls->Add(this->label6);
		this->otherGroupBox->Controls->Add(this->acceptableFPSError);
		this->otherGroupBox->Controls->Add(this->label15);
		this->otherGroupBox->Controls->Add(this->resetDialogs);
		this->otherGroupBox->Controls->Add(this->configSourceDetector);
		this->otherGroupBox->Controls->Add(this->chkboxUseAdvancedTooltips);
		this->otherGroupBox->Controls->Add(this->openProgressWindow);
		this->otherGroupBox->Controls->Add(this->deleteIntermediateFiles);
		this->otherGroupBox->Controls->Add(this->deleteAbortedOutput);
		this->otherGroupBox->Controls->Add(this->deleteCompletedJobs);
		this->otherGroupBox->Controls->Add(this->openScript);
		this->otherGroupBox->Controls->Add(this->autostartQueue);
		this->otherGroupBox->Controls->Add(this->priority);
		this->otherGroupBox->Controls->Add(this->priorityLabel);
		this->otherGroupBox->Location = new System::Drawing::Point(2, 6);
		this->otherGroupBox->Name = "otherGroupBox";
		this->otherGroupBox->Size = new System::Drawing::Size(467, 275);
		this->otherGroupBox->TabIndex = 1;
		this->otherGroupBox->TabStop = false;
		this->otherGroupBox->Tag = "";
		this->otherGroupBox->Text = " Main Settings ";
		// 
		// cbOpenAVSinThread
		// 
		this->cbOpenAVSinThread->Checked = true;
		this->cbOpenAVSinThread->CheckState = System::Windows::Forms::CheckState::Checked;
		this->cbOpenAVSinThread->Location = new System::Drawing::Point(300, 92);
		this->cbOpenAVSinThread->Name = "cbOpenAVSinThread";
		this->cbOpenAVSinThread->Size = new System::Drawing::Size(144, 17);
		this->cbOpenAVSinThread->TabIndex = 21;
		this->cbOpenAVSinThread->Text = "Improved AVS opening";
		// 
		// cbUseITUValues
		// 
		this->cbUseITUValues->Checked = true;
		this->cbUseITUValues->CheckState = System::Windows::Forms::CheckState::Checked;
		this->cbUseITUValues->Location = new System::Drawing::Point(300, 207);
		this->cbUseITUValues->Name = "cbUseITUValues";
		this->cbUseITUValues->Size = new System::Drawing::Size(144, 17);
		this->cbUseITUValues->TabIndex = 20;
		this->cbUseITUValues->Text = "Use ITU Aspect Ratio";
		// 
		// cbAutoStartQueueStartup
		// 
		this->cbAutoStartQueueStartup->AutoSize = true;
		this->cbAutoStartQueueStartup->Location = new System::Drawing::Point(13, 207);
		this->cbAutoStartQueueStartup->Name = "cbAutoStartQueueStartup";
		this->cbAutoStartQueueStartup->Size = new System::Drawing::Size(203, 17);
		this->cbAutoStartQueueStartup->TabIndex = 19;
		this->cbAutoStartQueueStartup->Text = "Process queue on application startup";
		this->cbAutoStartQueueStartup->UseVisualStyleBackColor = true;
		// 
		// forcerawavcuse
		// 
		this->forcerawavcuse->Location = new System::Drawing::Point(13, 184);
		this->forcerawavcuse->Name = "forcerawavcuse";
		this->forcerawavcuse->Size = new System::Drawing::Size(258, 17);
		this->forcerawavcuse->TabIndex = 18;
		this->forcerawavcuse->Text = "Force Video File Extension for QT compatibility";
		this->forcerawavcuse->UseVisualStyleBackColor = true;
		// 
		// audiosamplesperupdate
		// 
		this->audiosamplesperupdate->Location = new System::Drawing::Point(357, 17);
		this->audiosamplesperupdate->Maximum = decimal(new int[4] {100000000, 0, 0, 0});
		this->audiosamplesperupdate->Minimum = decimal(new int[4] {1, 0, 0, 0});
		this->audiosamplesperupdate->Name = "audiosamplesperupdate";
		this->audiosamplesperupdate->Size = new System::Drawing::Size(95, 21);
		this->audiosamplesperupdate->TabIndex = 3;
		this->audiosamplesperupdate->Value = decimal(new int[4] {1, 0, 0, 0});
		// 
		// label6
		// 
		this->label6->Location = new System::Drawing::Point(249, 17);
		this->label6->Name = "label6";
		this->label6->Size = new System::Drawing::Size(102, 42);
		this->label6->TabIndex = 2;
		this->label6->Text = "Samples between audio progress updates";
		// 
		// acceptableFPSError
		// 
		this->acceptableFPSError->DecimalPlaces = 3;
		this->acceptableFPSError->Increment = decimal(new int[4] {1, 0, 0, 196608});
		this->acceptableFPSError->Location = new System::Drawing::Point(150, 47);
		this->acceptableFPSError->Maximum = decimal(new int[4] {5, 0, 0, 0});
		this->acceptableFPSError->Minimum = decimal(new int[4] {1, 0, 0, 196608});
		this->acceptableFPSError->Name = "acceptableFPSError";
		this->acceptableFPSError->Size = new System::Drawing::Size(79, 21);
		this->acceptableFPSError->TabIndex = 7;
		this->acceptableFPSError->Value = decimal(new int[4] {1, 0, 0, 196608});
		// 
		// label15
		// 
		this->label15->Location = new System::Drawing::Point(9, 47);
		this->label15->Name = "label15";
		this->label15->Size = new System::Drawing::Size(130, 32);
		this->label15->TabIndex = 6;
		this->label15->Text = "Acceptable FPS rounding error (bitrate calculator)";
		// 
		// resetDialogs
		// 
		this->resetDialogs->Location = new System::Drawing::Point(13, 230);
		this->resetDialogs->Name = "resetDialogs";
		this->resetDialogs->Size = new System::Drawing::Size(149, 23);
		this->resetDialogs->TabIndex = 16;
		this->resetDialogs->Text = "Reset All Dialogs";
		this->resetDialogs->UseVisualStyleBackColor = true;
		this->resetDialogs->Click += new System::EventHandler(this, &SettingsForm::resetDialogs_Click);
		// 
		// configSourceDetector
		// 
		this->configSourceDetector->Location = new System::Drawing::Point(298, 230);
		this->configSourceDetector->Name = "configSourceDetector";
		this->configSourceDetector->Size = new System::Drawing::Size(154, 23);
		this->configSourceDetector->TabIndex = 17;
		this->configSourceDetector->Text = "Configure Source Detector";
		this->configSourceDetector->UseVisualStyleBackColor = true;
		this->configSourceDetector->Click += new System::EventHandler(this, &SettingsForm::configSourceDetector_Click);
		// 
		// chkboxUseAdvancedTooltips
		// 
		this->chkboxUseAdvancedTooltips->Location = new System::Drawing::Point(13, 115);
		this->chkboxUseAdvancedTooltips->Name = "chkboxUseAdvancedTooltips";
		this->chkboxUseAdvancedTooltips->Size = new System::Drawing::Size(152, 17);
		this->chkboxUseAdvancedTooltips->TabIndex = 8;
		this->chkboxUseAdvancedTooltips->Text = "Use Advanced ToolTips";
		// 
		// openProgressWindow
		// 
		this->openProgressWindow->Checked = true;
		this->openProgressWindow->CheckState = System::Windows::Forms::CheckState::Checked;
		this->openProgressWindow->Location = new System::Drawing::Point(300, 184);
		this->openProgressWindow->Name = "openProgressWindow";
		this->openProgressWindow->Size = new System::Drawing::Size(144, 17);
		this->openProgressWindow->TabIndex = 15;
		this->openProgressWindow->Text = "Open Progress Window";
		// 
		// deleteIntermediateFiles
		// 
		this->deleteIntermediateFiles->Location = new System::Drawing::Point(300, 161);
		this->deleteIntermediateFiles->Name = "deleteIntermediateFiles";
		this->deleteIntermediateFiles->Size = new System::Drawing::Size(152, 17);
		this->deleteIntermediateFiles->TabIndex = 13;
		this->deleteIntermediateFiles->Text = "Delete intermediate files";
		// 
		// deleteAbortedOutput
		// 
		this->deleteAbortedOutput->Location = new System::Drawing::Point(13, 161);
		this->deleteAbortedOutput->Name = "deleteAbortedOutput";
		this->deleteAbortedOutput->Size = new System::Drawing::Size(184, 17);
		this->deleteAbortedOutput->TabIndex = 12;
		this->deleteAbortedOutput->Text = "Delete Output of aborted jobs";
		// 
		// deleteCompletedJobs
		// 
		this->deleteCompletedJobs->Location = new System::Drawing::Point(300, 138);
		this->deleteCompletedJobs->Name = "deleteCompletedJobs";
		this->deleteCompletedJobs->Size = new System::Drawing::Size(144, 17);
		this->deleteCompletedJobs->TabIndex = 11;
		this->deleteCompletedJobs->Text = "Delete completed Jobs";
		// 
		// openScript
		// 
		this->openScript->Location = new System::Drawing::Point(13, 138);
		this->openScript->Name = "openScript";
		this->openScript->Size = new System::Drawing::Size(248, 17);
		this->openScript->TabIndex = 10;
		this->openScript->Text = "Open Preview after AviSynth script selection";
		// 
		// autostartQueue
		// 
		this->autostartQueue->Location = new System::Drawing::Point(300, 115);
		this->autostartQueue->Name = "autostartQueue";
		this->autostartQueue->Size = new System::Drawing::Size(112, 17);
		this->autostartQueue->TabIndex = 9;
		this->autostartQueue->Text = "Autostart Queue";
		// 
		// priority
		// 
		this->priority->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->priority->Items->AddRange(new object[5] {"Low", "Below Normal", "Normal", "Above Normal", "High"});
		this->priority->Location = new System::Drawing::Point(150, 16);
		this->priority->Name = "priority";
		this->priority->Size = new System::Drawing::Size(80, 21);
		this->priority->TabIndex = 1;
		// 
		// priorityLabel
		// 
		this->priorityLabel->Location = new System::Drawing::Point(8, 19);
		this->priorityLabel->Name = "priorityLabel";
		this->priorityLabel->Size = new System::Drawing::Size(88, 13);
		this->priorityLabel->TabIndex = 0;
		this->priorityLabel->Text = "Default Priority";
		this->priorityLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// tabControl1
		// 
		this->tabControl1->Controls->Add(this->tabPage1);
		this->tabControl1->Controls->Add(this->tabPage3);
		this->tabControl1->Controls->Add(this->tabPage2);
		this->tabControl1->Dock = System::Windows::Forms::DockStyle::Top;
		this->tabControl1->Location = new System::Drawing::Point(0, 0);
		this->tabControl1->Name = "tabControl1";
		this->tabControl1->SelectedIndex = 0;
		this->tabControl1->Size = new System::Drawing::Size(483, 413);
		this->tabControl1->TabIndex = 0;
		// 
		// tabPage1
		// 
		this->tabPage1->Controls->Add(this->groupBox3);
		this->tabPage1->Controls->Add(this->gbDefaultOutput);
		this->tabPage1->Controls->Add(this->otherGroupBox);
		this->tabPage1->Location = new System::Drawing::Point(4, 22);
		this->tabPage1->Name = "tabPage1";
		this->tabPage1->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage1->Size = new System::Drawing::Size(475, 387);
		this->tabPage1->TabIndex = 0;
		this->tabPage1->Text = "Main Configuration";
		this->tabPage1->UseVisualStyleBackColor = true;
		// 
		// groupBox3
		// 
		this->groupBox3->Controls->Add(this->defaultLanguage2);
		this->groupBox3->Controls->Add(this->defaultLanguage1);
		this->groupBox3->Location = new System::Drawing::Point(2, 287);
		this->groupBox3->Name = "groupBox3";
		this->groupBox3->Size = new System::Drawing::Size(174, 92);
		this->groupBox3->TabIndex = 8;
		this->groupBox3->TabStop = false;
		this->groupBox3->Text = " Default Languages ";
		// 
		// defaultLanguage2
		// 
		this->defaultLanguage2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->defaultLanguage2->Location = new System::Drawing::Point(13, 56);
		this->defaultLanguage2->Name = "defaultLanguage2";
		this->defaultLanguage2->Size = new System::Drawing::Size(152, 21);
		this->defaultLanguage2->Sorted = true;
		this->defaultLanguage2->TabIndex = 7;
		// 
		// defaultLanguage1
		// 
		this->defaultLanguage1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->defaultLanguage1->Location = new System::Drawing::Point(13, 29);
		this->defaultLanguage1->Name = "defaultLanguage1";
		this->defaultLanguage1->Size = new System::Drawing::Size(152, 21);
		this->defaultLanguage1->Sorted = true;
		this->defaultLanguage1->TabIndex = 2;
		// 
		// gbDefaultOutput
		// 
		this->gbDefaultOutput->Controls->Add(this->targetSizeSCBox1);
		this->gbDefaultOutput->Controls->Add(this->btnClearOutputDirecoty);
		this->gbDefaultOutput->Controls->Add(this->clearDefaultOutputDir);
		this->gbDefaultOutput->Controls->Add(this->defaultOutputDir);
		this->gbDefaultOutput->Location = new System::Drawing::Point(182, 287);
		this->gbDefaultOutput->Name = "gbDefaultOutput";
		this->gbDefaultOutput->Size = new System::Drawing::Size(287, 92);
		this->gbDefaultOutput->TabIndex = 7;
		this->gbDefaultOutput->TabStop = false;
		this->gbDefaultOutput->Text = " Default Output Directory + Custom File Size Values ";
		// 
		// targetSizeSCBox1
		// 
		this->targetSizeSCBox1->setCustomSizes(new MeGUI::core::util::FileSize[0]);
		this->targetSizeSCBox1->Location = new System::Drawing::Point(8, 56);
		this->targetSizeSCBox1->MaximumSize = new System::Drawing::Size(1000, 28);
		this->targetSizeSCBox1->MinimumSize = new System::Drawing::Size(64, 28);
		this->targetSizeSCBox1->Name = "targetSizeSCBox1";
		this->targetSizeSCBox1->setNullString("Modify custom file size values");
		this->targetSizeSCBox1->setSaveCustomValues(true);
		this->targetSizeSCBox1->setSelectedIndex(0);
		this->targetSizeSCBox1->Size = new System::Drawing::Size(273, 28);
		this->targetSizeSCBox1->TabIndex = 44;
		// 
		// btnClearOutputDirecoty
		// 
		this->btnClearOutputDirecoty->Anchor = System::Windows::Forms::AnchorStyles::Left;
		this->btnClearOutputDirecoty->Location = new System::Drawing::Point(257, 25);
		this->btnClearOutputDirecoty->Name = "btnClearOutputDirecoty";
		this->btnClearOutputDirecoty->Size = new System::Drawing::Size(24, 23);
		this->btnClearOutputDirecoty->TabIndex = 43;
		this->btnClearOutputDirecoty->Text = "x";
		this->btnClearOutputDirecoty->Click += new System::EventHandler(this, &SettingsForm::btnClearOutputDirecoty_Click);
		// 
		// clearDefaultOutputDir
		// 
		this->clearDefaultOutputDir->Location = new System::Drawing::Point(430, 29);
		this->clearDefaultOutputDir->Name = "clearDefaultOutputDir";
		this->clearDefaultOutputDir->Size = new System::Drawing::Size(24, 26);
		this->clearDefaultOutputDir->TabIndex = 41;
		this->clearDefaultOutputDir->Text = "x";
		this->clearDefaultOutputDir->Click += new System::EventHandler(this, &SettingsForm::clearDefaultOutputDir_Click);
		// 
		// defaultOutputDir
		// 
		this->defaultOutputDir->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->defaultOutputDir->setFilename("");
		this->defaultOutputDir->setFilter("");
		this->defaultOutputDir->setFilterIndex(0);
		this->defaultOutputDir->setFolderMode(true);
		this->defaultOutputDir->Location = new System::Drawing::Point(8, 24);
		this->defaultOutputDir->Name = "defaultOutputDir";
		this->defaultOutputDir->setReadOnly(true);
		this->defaultOutputDir->setSaveMode(false);
		this->defaultOutputDir->Size = new System::Drawing::Size(243, 26);
		this->defaultOutputDir->TabIndex = 40;
		this->defaultOutputDir->setTitle("");
		// 
		// tabPage3
		// 
		this->tabPage3->Controls->Add(this->groupBox2);
		this->tabPage3->Controls->Add(this->gbVideoPreview);
		this->tabPage3->Controls->Add(groupBox1);
		this->tabPage3->Controls->Add(this->autoUpdateGroupBox);
		this->tabPage3->Controls->Add(this->outputExtensions);
		this->tabPage3->Controls->Add(this->autoModeGroupbox);
		this->tabPage3->Location = new System::Drawing::Point(4, 22);
		this->tabPage3->Name = "tabPage3";
		this->tabPage3->Size = new System::Drawing::Size(475, 387);
		this->tabPage3->TabIndex = 2;
		this->tabPage3->Text = "Extra Configuration";
		this->tabPage3->UseVisualStyleBackColor = true;
		// 
		// groupBox2
		// 
		this->groupBox2->Controls->Add(this->label1);
		this->groupBox2->Controls->Add(this->cbHttpProxyMode);
		this->groupBox2->Controls->Add(this->txt_httpproxyport);
		this->groupBox2->Controls->Add(this->txt_httpproxypwd);
		this->groupBox2->Controls->Add(this->txt_httpproxyuid);
		this->groupBox2->Controls->Add(this->txt_httpproxyaddress);
		this->groupBox2->Controls->Add(this->label21);
		this->groupBox2->Controls->Add(this->label20);
		this->groupBox2->Controls->Add(this->label19);
		this->groupBox2->Controls->Add(this->label18);
		this->groupBox2->Location = new System::Drawing::Point(227, 243);
		this->groupBox2->Name = "groupBox2";
		this->groupBox2->Size = new System::Drawing::Size(240, 135);
		this->groupBox2->TabIndex = 5;
		this->groupBox2->TabStop = false;
		this->groupBox2->Text = " Auto Update Http Proxy ";
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = new System::Drawing::Point(8, 28);
		this->label1->Name = "label1";
		this->label1->Size = new System::Drawing::Size(29, 13);
		this->label1->TabIndex = 10;
		this->label1->Text = "Use:";
		// 
		// cbHttpProxyMode
		// 
		this->cbHttpProxyMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbHttpProxyMode->FormattingEnabled = true;
		this->cbHttpProxyMode->Items->AddRange(new object[4] {"None", "System Proxy", "Custom Proxy", "Custom Proxy With Login"});
		this->cbHttpProxyMode->Location = new System::Drawing::Point(55, 25);
		this->cbHttpProxyMode->Name = "cbHttpProxyMode";
		this->cbHttpProxyMode->Size = new System::Drawing::Size(179, 21);
		this->cbHttpProxyMode->TabIndex = 9;
		this->cbHttpProxyMode->SelectedIndexChanged += new System::EventHandler(this, &SettingsForm::cbHttpProxyMode_SelectedIndexChanged);
		// 
		// txt_httpproxyport
		// 
		this->txt_httpproxyport->Enabled = false;
		this->txt_httpproxyport->Location = new System::Drawing::Point(191, 52);
		this->txt_httpproxyport->Name = "txt_httpproxyport";
		this->txt_httpproxyport->Size = new System::Drawing::Size(43, 21);
		this->txt_httpproxyport->TabIndex = 6;
		// 
		// txt_httpproxypwd
		// 
		this->txt_httpproxypwd->Enabled = false;
		this->txt_httpproxypwd->Location = new System::Drawing::Point(55, 106);
		this->txt_httpproxypwd->Name = "txt_httpproxypwd";
		this->txt_httpproxypwd->PasswordChar = '*';
		this->txt_httpproxypwd->Size = new System::Drawing::Size(179, 21);
		this->txt_httpproxypwd->TabIndex = 8;
		// 
		// txt_httpproxyuid
		// 
		this->txt_httpproxyuid->Enabled = false;
		this->txt_httpproxyuid->Location = new System::Drawing::Point(55, 79);
		this->txt_httpproxyuid->Name = "txt_httpproxyuid";
		this->txt_httpproxyuid->Size = new System::Drawing::Size(179, 21);
		this->txt_httpproxyuid->TabIndex = 7;
		// 
		// txt_httpproxyaddress
		// 
		this->txt_httpproxyaddress->Enabled = false;
		this->txt_httpproxyaddress->Location = new System::Drawing::Point(55, 52);
		this->txt_httpproxyaddress->Name = "txt_httpproxyaddress";
		this->txt_httpproxyaddress->Size = new System::Drawing::Size(103, 21);
		this->txt_httpproxyaddress->TabIndex = 5;
		// 
		// label21
		// 
		this->label21->AutoSize = true;
		this->label21->Location = new System::Drawing::Point(6, 109);
		this->label21->Name = "label21";
		this->label21->Size = new System::Drawing::Size(31, 13);
		this->label21->TabIndex = 4;
		this->label21->Text = "Pwd:";
		// 
		// label20
		// 
		this->label20->AutoSize = true;
		this->label20->Location = new System::Drawing::Point(6, 82);
		this->label20->Name = "label20";
		this->label20->Size = new System::Drawing::Size(36, 13);
		this->label20->TabIndex = 3;
		this->label20->Text = "Login:";
		// 
		// label19
		// 
		this->label19->AutoSize = true;
		this->label19->Location = new System::Drawing::Point(164, 55);
		this->label19->Name = "label19";
		this->label19->Size = new System::Drawing::Size(31, 13);
		this->label19->TabIndex = 2;
		this->label19->Text = "Port:";
		// 
		// label18
		// 
		this->label18->AutoSize = true;
		this->label18->Location = new System::Drawing::Point(6, 55);
		this->label18->Name = "label18";
		this->label18->Size = new System::Drawing::Size(43, 13);
		this->label18->TabIndex = 1;
		this->label18->Text = "Server:";
		// 
		// gbVideoPreview
		// 
		this->gbVideoPreview->Controls->Add(this->chkEnsureCorrectPlaybackSpeed);
		this->gbVideoPreview->Controls->Add(this->cbAddTimePos);
		this->gbVideoPreview->Controls->Add(this->chAlwaysOnTop);
		this->gbVideoPreview->Location = new System::Drawing::Point(4, 288);
		this->gbVideoPreview->Name = "gbVideoPreview";
		this->gbVideoPreview->Size = new System::Drawing::Size(217, 90);
		this->gbVideoPreview->TabIndex = 4;
		this->gbVideoPreview->TabStop = false;
		this->gbVideoPreview->Text = " Video Preview ";
		// 
		// chkEnsureCorrectPlaybackSpeed
		// 
		this->chkEnsureCorrectPlaybackSpeed->AutoSize = true;
		this->chkEnsureCorrectPlaybackSpeed->Location = new System::Drawing::Point(8, 63);
		this->chkEnsureCorrectPlaybackSpeed->Name = "chkEnsureCorrectPlaybackSpeed";
		this->chkEnsureCorrectPlaybackSpeed->Size = new System::Drawing::Size(173, 17);
		this->chkEnsureCorrectPlaybackSpeed->TabIndex = 2;
		this->chkEnsureCorrectPlaybackSpeed->Text = "Ensure correct playback speed";
		this->chkEnsureCorrectPlaybackSpeed->UseVisualStyleBackColor = true;
		// 
		// cbAddTimePos
		// 
		this->cbAddTimePos->AutoSize = true;
		this->cbAddTimePos->Location = new System::Drawing::Point(8, 40);
		this->cbAddTimePos->Name = "cbAddTimePos";
		this->cbAddTimePos->Size = new System::Drawing::Size(110, 17);
		this->cbAddTimePos->TabIndex = 1;
		this->cbAddTimePos->Text = "Add Time Position";
		this->cbAddTimePos->UseVisualStyleBackColor = true;
		// 
		// chAlwaysOnTop
		// 
		this->chAlwaysOnTop->AutoSize = true;
		this->chAlwaysOnTop->Location = new System::Drawing::Point(8, 17);
		this->chAlwaysOnTop->Name = "chAlwaysOnTop";
		this->chAlwaysOnTop->Size = new System::Drawing::Size(169, 17);
		this->chAlwaysOnTop->TabIndex = 0;
		this->chAlwaysOnTop->Text = "Set the Form \"Always on Top\"";
		this->chAlwaysOnTop->UseVisualStyleBackColor = true;
		// 
		// autoUpdateGroupBox
		// 
		this->autoUpdateGroupBox->Controls->Add(this->cbAutoUpdateServerSubList);
		this->autoUpdateGroupBox->Controls->Add(this->backupfiles);
		this->autoUpdateGroupBox->Controls->Add(this->configureServersButton);
		this->autoUpdateGroupBox->Controls->Add(this->useAutoUpdateCheckbox);
		this->autoUpdateGroupBox->Location = new System::Drawing::Point(227, 104);
		this->autoUpdateGroupBox->Name = "autoUpdateGroupBox";
		this->autoUpdateGroupBox->Size = new System::Drawing::Size(240, 133);
		this->autoUpdateGroupBox->TabIndex = 3;
		this->autoUpdateGroupBox->TabStop = false;
		this->autoUpdateGroupBox->Text = " Auto Update ";
		// 
		// cbAutoUpdateServerSubList
		// 
		this->cbAutoUpdateServerSubList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbAutoUpdateServerSubList->FormattingEnabled = true;
		this->cbAutoUpdateServerSubList->Items->AddRange(new object[3] {"Use stable update server", "Use development update server", "Use custom update server"});
		this->cbAutoUpdateServerSubList->Location = new System::Drawing::Point(9, 47);
		this->cbAutoUpdateServerSubList->Name = "cbAutoUpdateServerSubList";
		this->cbAutoUpdateServerSubList->Size = new System::Drawing::Size(176, 21);
		this->cbAutoUpdateServerSubList->TabIndex = 5;
		// 
		// backupfiles
		// 
		this->backupfiles->AutoSize = true;
		this->backupfiles->Checked = true;
		this->backupfiles->CheckState = System::Windows::Forms::CheckState::Checked;
		this->backupfiles->Location = new System::Drawing::Point(9, 103);
		this->backupfiles->Name = "backupfiles";
		this->backupfiles->Size = new System::Drawing::Size(187, 17);
		this->backupfiles->TabIndex = 4;
		this->backupfiles->Text = "Always backup files when needed";
		this->backupfiles->UseVisualStyleBackColor = true;
		this->backupfiles->CheckedChanged += new System::EventHandler(this, &SettingsForm::backupfiles_CheckedChanged);
		// 
		// configureServersButton
		// 
		this->configureServersButton->AutoSize = true;
		this->configureServersButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->configureServersButton->Location = new System::Drawing::Point(9, 74);
		this->configureServersButton->Name = "configureServersButton";
		this->configureServersButton->Size = new System::Drawing::Size(115, 23);
		this->configureServersButton->TabIndex = 1;
		this->configureServersButton->Text = "Configure servers...";
		this->configureServersButton->UseVisualStyleBackColor = true;
		this->configureServersButton->Click += new System::EventHandler(this, &SettingsForm::configureServersButton_Click);
		// 
		// useAutoUpdateCheckbox
		// 
		this->useAutoUpdateCheckbox->AutoSize = true;
		this->useAutoUpdateCheckbox->Location = new System::Drawing::Point(9, 22);
		this->useAutoUpdateCheckbox->Name = "useAutoUpdateCheckbox";
		this->useAutoUpdateCheckbox->Size = new System::Drawing::Size(105, 17);
		this->useAutoUpdateCheckbox->TabIndex = 0;
		this->useAutoUpdateCheckbox->Text = "Use AutoUpdate";
		this->useAutoUpdateCheckbox->UseVisualStyleBackColor = true;
		// 
		// outputExtensions
		// 
		this->outputExtensions->Controls->Add(this->videoExtension);
		this->outputExtensions->Controls->Add(this->label11);
		this->outputExtensions->Controls->Add(this->label12);
		this->outputExtensions->Controls->Add(this->audioExtension);
		this->outputExtensions->Location = new System::Drawing::Point(3, 104);
		this->outputExtensions->Name = "outputExtensions";
		this->outputExtensions->Size = new System::Drawing::Size(218, 77);
		this->outputExtensions->TabIndex = 1;
		this->outputExtensions->TabStop = false;
		this->outputExtensions->Text = " Optional output extensions ";
		// 
		// videoExtension
		// 
		this->videoExtension->Location = new System::Drawing::Point(11, 20);
		this->videoExtension->Name = "videoExtension";
		this->videoExtension->Size = new System::Drawing::Size(120, 21);
		this->videoExtension->TabIndex = 0;
		// 
		// label11
		// 
		this->label11->AutoSize = true;
		this->label11->Location = new System::Drawing::Point(137, 51);
		this->label11->Name = "label11";
		this->label11->Size = new System::Drawing::Size(34, 13);
		this->label11->TabIndex = 3;
		this->label11->Text = "Audio";
		// 
		// label12
		// 
		this->label12->AutoSize = true;
		this->label12->Location = new System::Drawing::Point(137, 23);
		this->label12->Name = "label12";
		this->label12->Size = new System::Drawing::Size(33, 13);
		this->label12->TabIndex = 1;
		this->label12->Text = "Video";
		// 
		// audioExtension
		// 
		this->audioExtension->Location = new System::Drawing::Point(11, 48);
		this->audioExtension->Name = "audioExtension";
		this->audioExtension->Size = new System::Drawing::Size(120, 21);
		this->audioExtension->TabIndex = 2;
		// 
		// autoModeGroupbox
		// 
		this->autoModeGroupbox->Controls->Add(this->chkAlwaysMuxMKV);
		this->autoModeGroupbox->Controls->Add(this->configAutoEncodeDefaults);
		this->autoModeGroupbox->Controls->Add(this->keep2ndPassLogFile);
		this->autoModeGroupbox->Controls->Add(this->keep2ndPassOutput);
		this->autoModeGroupbox->Controls->Add(this->label13);
		this->autoModeGroupbox->Controls->Add(this->nbPasses);
		this->autoModeGroupbox->Location = new System::Drawing::Point(4, 3);
		this->autoModeGroupbox->Name = "autoModeGroupbox";
		this->autoModeGroupbox->Size = new System::Drawing::Size(463, 95);
		this->autoModeGroupbox->TabIndex = 0;
		this->autoModeGroupbox->TabStop = false;
		this->autoModeGroupbox->Text = " Automated Encoding ";
		// 
		// chkAlwaysMuxMKV
		// 
		this->chkAlwaysMuxMKV->AutoSize = true;
		this->chkAlwaysMuxMKV->Checked = true;
		this->chkAlwaysMuxMKV->CheckState = System::Windows::Forms::CheckState::Checked;
		this->chkAlwaysMuxMKV->Location = new System::Drawing::Point(232, 70);
		this->chkAlwaysMuxMKV->Name = "chkAlwaysMuxMKV";
		this->chkAlwaysMuxMKV->Size = new System::Drawing::Size(226, 17);
		this->chkAlwaysMuxMKV->TabIndex = 21;
		this->chkAlwaysMuxMKV->Text = "Always mux mkv encoding with mkvmerge";
		this->chkAlwaysMuxMKV->UseVisualStyleBackColor = true;
		// 
		// configAutoEncodeDefaults
		// 
		this->configAutoEncodeDefaults->AutoSize = true;
		this->configAutoEncodeDefaults->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->configAutoEncodeDefaults->Location = new System::Drawing::Point(14, 47);
		this->configAutoEncodeDefaults->Name = "configAutoEncodeDefaults";
		this->configAutoEncodeDefaults->Size = new System::Drawing::Size(179, 23);
		this->configAutoEncodeDefaults->TabIndex = 5;
		this->configAutoEncodeDefaults->Text = "Configure AutoEncode defaults...";
		this->configAutoEncodeDefaults->UseVisualStyleBackColor = true;
		this->configAutoEncodeDefaults->Click += new System::EventHandler(this, &SettingsForm::autoEncodeDefaultsButton_Click);
		// 
		// keep2ndPassLogFile
		// 
		this->keep2ndPassLogFile->AutoSize = true;
		this->keep2ndPassLogFile->Checked = true;
		this->keep2ndPassLogFile->CheckState = System::Windows::Forms::CheckState::Checked;
		this->keep2ndPassLogFile->Location = new System::Drawing::Point(232, 22);
		this->keep2ndPassLogFile->Name = "keep2ndPassLogFile";
		this->keep2ndPassLogFile->Size = new System::Drawing::Size(176, 17);
		this->keep2ndPassLogFile->TabIndex = 4;
		this->keep2ndPassLogFile->Text = "Overwrite Stats File in 3rd pass";
		this->keep2ndPassLogFile->UseVisualStyleBackColor = true;
		// 
		// keep2ndPassOutput
		// 
		this->keep2ndPassOutput->AutoSize = true;
		this->keep2ndPassOutput->Checked = true;
		this->keep2ndPassOutput->CheckState = System::Windows::Forms::CheckState::Checked;
		this->keep2ndPassOutput->Location = new System::Drawing::Point(232, 47);
		this->keep2ndPassOutput->Name = "keep2ndPassOutput";
		this->keep2ndPassOutput->Size = new System::Drawing::Size(207, 17);
		this->keep2ndPassOutput->TabIndex = 3;
		this->keep2ndPassOutput->Text = "Keep 2nd pass Output in 3 pass mode";
		this->keep2ndPassOutput->UseVisualStyleBackColor = true;
		// 
		// label13
		// 
		this->label13->Location = new System::Drawing::Point(11, 22);
		this->label13->Name = "label13";
		this->label13->Size = new System::Drawing::Size(100, 13);
		this->label13->TabIndex = 0;
		this->label13->Text = "Number of passes";
		// 
		// nbPasses
		// 
		this->nbPasses->Location = new System::Drawing::Point(117, 20);
		this->nbPasses->Maximum = decimal(new int[4] {3, 0, 0, 0});
		this->nbPasses->Minimum = decimal(new int[4] {2, 0, 0, 0});
		this->nbPasses->Name = "nbPasses";
		this->nbPasses->Size = new System::Drawing::Size(40, 21);
		this->nbPasses->TabIndex = 1;
		this->nbPasses->Value = decimal(new int[4] {2, 0, 0, 0});
		// 
		// tabPage2
		// 
		this->tabPage2->Controls->Add(this->groupBox6);
		this->tabPage2->Controls->Add(this->groupBox5);
		this->tabPage2->Controls->Add(this->groupBox4);
		this->tabPage2->Controls->Add(this->vobGroupBox);
		this->tabPage2->Location = new System::Drawing::Point(4, 22);
		this->tabPage2->Name = "tabPage2";
		this->tabPage2->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage2->Size = new System::Drawing::Size(475, 387);
		this->tabPage2->TabIndex = 1;
		this->tabPage2->Text = "External Program Configuration";
		this->tabPage2->UseVisualStyleBackColor = true;
		// 
		// groupBox6
		// 
		this->groupBox6->Controls->Add(this->chUse10BitsX264);
		this->groupBox6->Controls->Add(this->chx264ExternalMuxer);
		this->groupBox6->Controls->Add(this->useQAAC);
		this->groupBox6->Controls->Add(this->lblForcedName);
		this->groupBox6->Controls->Add(this->txtForcedName);
		this->groupBox6->Controls->Add(this->lblffmsThreads);
		this->groupBox6->Controls->Add(this->ffmsThreads);
		this->groupBox6->Controls->Add(this->chkSelectHDTracks);
		this->groupBox6->Controls->Add(this->chkEnable64bitX264);
		this->groupBox6->Location = new System::Drawing::Point(4, 249);
		this->groupBox6->Name = "groupBox6";
		this->groupBox6->Size = new System::Drawing::Size(467, 132);
		this->groupBox6->TabIndex = 33;
		this->groupBox6->TabStop = false;
		this->groupBox6->Text = " Misc ";
		// 
		// chUse10BitsX264
		// 
		this->chUse10BitsX264->AutoSize = true;
		this->chUse10BitsX264->Location = new System::Drawing::Point(234, 49);
		this->chUse10BitsX264->Name = "chUse10BitsX264";
		this->chUse10BitsX264->Size = new System::Drawing::Size(166, 17);
		this->chUse10BitsX264->TabIndex = 50;
		this->chUse10BitsX264->Text = "x264: enable 10 Bits Encoder";
		this->chUse10BitsX264->UseVisualStyleBackColor = true;
		this->chUse10BitsX264->CheckedChanged += new System::EventHandler(this, &SettingsForm::chUse10BitsX264_CheckedChanged);
		// 
		// chx264ExternalMuxer
		// 
		this->chx264ExternalMuxer->AutoSize = true;
		this->chx264ExternalMuxer->Checked = true;
		this->chx264ExternalMuxer->CheckState = System::Windows::Forms::CheckState::Checked;
		this->chx264ExternalMuxer->Location = new System::Drawing::Point(234, 31);
		this->chx264ExternalMuxer->Name = "chx264ExternalMuxer";
		this->chx264ExternalMuxer->Size = new System::Drawing::Size(208, 17);
		this->chx264ExternalMuxer->TabIndex = 49;
		this->chx264ExternalMuxer->Text = "x264: use external muxer (MKV, MP4)";
		this->chx264ExternalMuxer->UseVisualStyleBackColor = true;
		// 
		// useQAAC
		// 
		this->useQAAC->AutoSize = true;
		this->useQAAC->Location = new System::Drawing::Point(13, 39);
		this->useQAAC->Name = "useQAAC";
		this->useQAAC->Size = new System::Drawing::Size(90, 17);
		this->useQAAC->TabIndex = 48;
		this->useQAAC->Text = "Enable QAAC";
		this->useQAAC->UseVisualStyleBackColor = true;
		this->useQAAC->CheckedChanged += new System::EventHandler(this, &SettingsForm::useQAAC_CheckedChanged);
		// 
		// lblForcedName
		// 
		this->lblForcedName->AutoSize = true;
		this->lblForcedName->Location = new System::Drawing::Point(11, 103);
		this->lblForcedName->Name = "lblForcedName";
		this->lblForcedName->Size = new System::Drawing::Size(164, 13);
		this->lblForcedName->TabIndex = 33;
		this->lblForcedName->Text = "Add text to forced track names: ";
		// 
		// txtForcedName
		// 
		this->txtForcedName->Location = new System::Drawing::Point(180, 100);
		this->txtForcedName->Name = "txtForcedName";
		this->txtForcedName->Size = new System::Drawing::Size(281, 21);
		this->txtForcedName->TabIndex = 32;
		// 
		// lblffmsThreads
		// 
		this->lblffmsThreads->AutoSize = true;
		this->lblffmsThreads->Location = new System::Drawing::Point(11, 17);
		this->lblffmsThreads->Name = "lblffmsThreads";
		this->lblffmsThreads->Size = new System::Drawing::Size(106, 13);
		this->lblffmsThreads->TabIndex = 31;
		this->lblffmsThreads->Text = "FFMS Thread Count:";
		// 
		// ffmsThreads
		// 
		this->ffmsThreads->Location = new System::Drawing::Point(123, 15);
		this->ffmsThreads->Maximum = decimal(new int[4] {1, 0, 0, 0});
		this->ffmsThreads->Minimum = decimal(new int[4] {1, 0, 0, -2147483648});
		this->ffmsThreads->Name = "ffmsThreads";
		this->ffmsThreads->Size = new System::Drawing::Size(38, 21);
		this->ffmsThreads->TabIndex = 30;
		this->ffmsThreads->Value = decimal(new int[4] {1, 0, 0, 0});
		// 
		// chkSelectHDTracks
		// 
		this->chkSelectHDTracks->AutoSize = true;
		this->chkSelectHDTracks->Checked = true;
		this->chkSelectHDTracks->CheckState = System::Windows::Forms::CheckState::Checked;
		this->chkSelectHDTracks->Location = new System::Drawing::Point(12, 72);
		this->chkSelectHDTracks->Name = "chkSelectHDTracks";
		this->chkSelectHDTracks->Size = new System::Drawing::Size(234, 17);
		this->chkSelectHDTracks->TabIndex = 29;
		this->chkSelectHDTracks->Text = "HD Streams Extractor: select default tracks";
		this->chkSelectHDTracks->UseVisualStyleBackColor = true;
		// 
		// chkEnable64bitX264
		// 
		this->chkEnable64bitX264->AutoSize = true;
		this->chkEnable64bitX264->Checked = true;
		this->chkEnable64bitX264->CheckState = System::Windows::Forms::CheckState::Checked;
		this->chkEnable64bitX264->Location = new System::Drawing::Point(234, 13);
		this->chkEnable64bitX264->Name = "chkEnable64bitX264";
		this->chkEnable64bitX264->Size = new System::Drawing::Size(148, 17);
		this->chkEnable64bitX264->TabIndex = 28;
		this->chkEnable64bitX264->Text = "x264: enable 64 bit mode";
		this->chkEnable64bitX264->UseVisualStyleBackColor = true;
		// 
		// groupBox5
		// 
		this->groupBox5->Controls->Add(this->useNeroAacEnc);
		this->groupBox5->Controls->Add(this->lblNero);
		this->groupBox5->Controls->Add(this->neroaacencLocation);
		this->groupBox5->Location = new System::Drawing::Point(4, 8);
		this->groupBox5->Name = "groupBox5";
		this->groupBox5->Size = new System::Drawing::Size(467, 70);
		this->groupBox5->TabIndex = 32;
		this->groupBox5->TabStop = false;
		this->groupBox5->Text = "                                        ";
		// 
		// useNeroAacEnc
		// 
		this->useNeroAacEnc->AutoSize = true;
		this->useNeroAacEnc->Location = new System::Drawing::Point(12, -1);
		this->useNeroAacEnc->Name = "useNeroAacEnc";
		this->useNeroAacEnc->Size = new System::Drawing::Size(119, 17);
		this->useNeroAacEnc->TabIndex = 46;
		this->useNeroAacEnc->Text = "Enable NeroAacEnc";
		this->useNeroAacEnc->UseVisualStyleBackColor = true;
		this->useNeroAacEnc->CheckedChanged += new System::EventHandler(this, &SettingsForm::useNeroAacEnc_CheckedChanged);
		// 
		// lblNero
		// 
		this->lblNero->AutoSize = true;
		this->lblNero->Enabled = false;
		this->lblNero->Location = new System::Drawing::Point(11, 31);
		this->lblNero->Name = "lblNero";
		this->lblNero->Size = new System::Drawing::Size(47, 13);
		this->lblNero->TabIndex = 45;
		this->lblNero->Text = "Location";
		// 
		// neroaacencLocation
		// 
		this->neroaacencLocation->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->neroaacencLocation->Enabled = false;
		this->neroaacencLocation->setFilename("");
		this->neroaacencLocation->setFilter("NeroAacEnc|neroaacenc.exe");
		this->neroaacencLocation->setFilterIndex(0);
		this->neroaacencLocation->setFolderMode(false);
		this->neroaacencLocation->Location = new System::Drawing::Point(64, 26);
		this->neroaacencLocation->Name = "neroaacencLocation";
		this->neroaacencLocation->setReadOnly(true);
		this->neroaacencLocation->setSaveMode(false);
		this->neroaacencLocation->Size = new System::Drawing::Size(399, 26);
		this->neroaacencLocation->TabIndex = 44;
		this->neroaacencLocation->setTitle("");
		// 
		// groupBox4
		// 
		this->groupBox4->Controls->Add(this->btnClearMP4TempDirectory);
		this->groupBox4->Controls->Add(this->tempDirMP4);
		this->groupBox4->Location = new System::Drawing::Point(5, 166);
		this->groupBox4->Name = "groupBox4";
		this->groupBox4->Size = new System::Drawing::Size(467, 77);
		this->groupBox4->TabIndex = 31;
		this->groupBox4->TabStop = false;
		this->groupBox4->Text = "Temp Directory for MP4 Muxer";
		// 
		// btnClearMP4TempDirectory
		// 
		this->btnClearMP4TempDirectory->Location = new System::Drawing::Point(436, 34);
		this->btnClearMP4TempDirectory->Name = "btnClearMP4TempDirectory";
		this->btnClearMP4TempDirectory->Size = new System::Drawing::Size(24, 23);
		this->btnClearMP4TempDirectory->TabIndex = 42;
		this->btnClearMP4TempDirectory->Text = "x";
		this->btnClearMP4TempDirectory->Click += new System::EventHandler(this, &SettingsForm::btnClearMP4TempDirectory_Click);
		// 
		// tempDirMP4
		// 
		this->tempDirMP4->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->tempDirMP4->setFilename("");
		this->tempDirMP4->setFilter("");
		this->tempDirMP4->setFilterIndex(0);
		this->tempDirMP4->setFolderMode(true);
		this->tempDirMP4->Location = new System::Drawing::Point(13, 33);
		this->tempDirMP4->Name = "tempDirMP4";
		this->tempDirMP4->setReadOnly(true);
		this->tempDirMP4->setSaveMode(false);
		this->tempDirMP4->Size = new System::Drawing::Size(418, 26);
		this->tempDirMP4->TabIndex = 41;
		this->tempDirMP4->setTitle("");
		this->tempDirMP4->FileSelected += new MeGUI::FileBarEventHandler(this, &SettingsForm::tempDirMP4_FileSelected);
		// 
		// vobGroupBox
		// 
		this->vobGroupBox->Controls->Add(this->useDGIndexNV);
		this->vobGroupBox->Controls->Add(this->cbAutoLoadDG);
		this->vobGroupBox->Controls->Add(this->percentLabel);
		this->vobGroupBox->Controls->Add(this->forceFilmPercentage);
		this->vobGroupBox->Controls->Add(this->autoForceFilm);
		this->vobGroupBox->Location = new System::Drawing::Point(4, 84);
		this->vobGroupBox->Name = "vobGroupBox";
		this->vobGroupBox->Size = new System::Drawing::Size(467, 76);
		this->vobGroupBox->TabIndex = 29;
		this->vobGroupBox->TabStop = false;
		this->vobGroupBox->Text = " DGIndex Tools";
		// 
		// useDGIndexNV
		// 
		this->useDGIndexNV->AutoSize = true;
		this->useDGIndexNV->Location = new System::Drawing::Point(12, 24);
		this->useDGIndexNV->Name = "useDGIndexNV";
		this->useDGIndexNV->Size = new System::Drawing::Size(116, 17);
		this->useDGIndexNV->TabIndex = 47;
		this->useDGIndexNV->Text = "Enable DGIndexNV";
		this->useDGIndexNV->UseVisualStyleBackColor = true;
		// 
		// cbAutoLoadDG
		// 
		this->cbAutoLoadDG->AutoSize = true;
		this->cbAutoLoadDG->Location = new System::Drawing::Point(225, 51);
		this->cbAutoLoadDG->Name = "cbAutoLoadDG";
		this->cbAutoLoadDG->Size = new System::Drawing::Size(179, 17);
		this->cbAutoLoadDG->TabIndex = 7;
		this->cbAutoLoadDG->Text = "autoload VOB files incrementally";
		this->cbAutoLoadDG->UseVisualStyleBackColor = true;
		// 
		// percentLabel
		// 
		this->percentLabel->Location = new System::Drawing::Point(397, 28);
		this->percentLabel->Margin = new System::Windows::Forms::Padding(3);
		this->percentLabel->Name = "percentLabel";
		this->percentLabel->Size = new System::Drawing::Size(50, 13);
		this->percentLabel->TabIndex = 4;
		this->percentLabel->Text = "Percent";
		this->percentLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// forceFilmPercentage
		// 
		this->forceFilmPercentage->Location = new System::Drawing::Point(351, 24);
		this->forceFilmPercentage->Name = "forceFilmPercentage";
		this->forceFilmPercentage->Size = new System::Drawing::Size(40, 21);
		this->forceFilmPercentage->TabIndex = 3;
		this->forceFilmPercentage->Value = decimal(new int[4] {95, 0, 0, 0});
		// 
		// autoForceFilm
		// 
		this->autoForceFilm->Location = new System::Drawing::Point(225, 24);
		this->autoForceFilm->Name = "autoForceFilm";
		this->autoForceFilm->Size = new System::Drawing::Size(120, 17);
		this->autoForceFilm->TabIndex = 2;
		this->autoForceFilm->Text = "Auto Force Film at";
		// 
		// audioExtLabel
		// 
		this->audioExtLabel->AutoSize = true;
		this->audioExtLabel->Location = new System::Drawing::Point(137, 51);
		this->audioExtLabel->Name = "audioExtLabel";
		this->audioExtLabel->Size = new System::Drawing::Size(34, 13);
		this->audioExtLabel->TabIndex = 24;
		this->audioExtLabel->Text = "Audio";
		// 
		// videoExtLabel
		// 
		this->videoExtLabel->AutoSize = true;
		this->videoExtLabel->Location = new System::Drawing::Point(137, 24);
		this->videoExtLabel->Name = "videoExtLabel";
		this->videoExtLabel->Size = new System::Drawing::Size(34, 13);
		this->videoExtLabel->TabIndex = 23;
		this->videoExtLabel->Text = "Video";
		// 
		// autoEncodeDefaultsButton
		// 
		this->autoEncodeDefaultsButton->Location = new System::Drawing::Point(11, 51);
		this->autoEncodeDefaultsButton->Name = "autoEncodeDefaultsButton";
		this->autoEncodeDefaultsButton->Size = new System::Drawing::Size(114, 23);
		this->autoEncodeDefaultsButton->TabIndex = 4;
		this->autoEncodeDefaultsButton->Text = "Configure Defaults";
		this->autoEncodeDefaultsButton->UseVisualStyleBackColor = true;
		// 
		// toolTipHelp
		// 
		this->toolTipHelp->AutoPopDelay = 30000;
		this->toolTipHelp->InitialDelay = 500;
		this->toolTipHelp->IsBalloon = true;
		this->toolTipHelp->ReshowDelay = 100;
		this->toolTipHelp->ShowAlways = true;
		// 
		// helpButton1
		// 
		this->helpButton1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->helpButton1->setArticleName("Settings");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(21, 418);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 1;
		// 
		// SettingsForm
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->ClientSize = new System::Drawing::Size(483, 446);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->tabControl1);
		this->Controls->Add(this->cancelButton);
		this->Controls->Add(this->saveButton);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = "SettingsForm";
		this->ShowInTaskbar = false;
		this->Text = "Settings";
		groupBox1->ResumeLayout(false);
		groupBox1->PerformLayout();
		this->otherGroupBox->ResumeLayout(false);
		this->otherGroupBox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->audiosamplesperupdate))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->acceptableFPSError))->EndInit();
		this->tabControl1->ResumeLayout(false);
		this->tabPage1->ResumeLayout(false);
		this->groupBox3->ResumeLayout(false);
		this->gbDefaultOutput->ResumeLayout(false);
		this->tabPage3->ResumeLayout(false);
		this->groupBox2->ResumeLayout(false);
		this->groupBox2->PerformLayout();
		this->gbVideoPreview->ResumeLayout(false);
		this->gbVideoPreview->PerformLayout();
		this->autoUpdateGroupBox->ResumeLayout(false);
		this->autoUpdateGroupBox->PerformLayout();
		this->outputExtensions->ResumeLayout(false);
		this->outputExtensions->PerformLayout();
		this->autoModeGroupbox->ResumeLayout(false);
		this->autoModeGroupbox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->nbPasses))->EndInit();
		this->tabPage2->ResumeLayout(false);
		this->groupBox6->ResumeLayout(false);
		this->groupBox6->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->ffmsThreads))->EndInit();
		this->groupBox5->ResumeLayout(false);
		this->groupBox5->PerformLayout();
		this->groupBox4->ResumeLayout(false);
		this->vobGroupBox->ResumeLayout(false);
		this->vobGroupBox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->forceFilmPercentage))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void SettingsForm::configSourceDetector_Click(object *sender, EventArgs *e)
	{
		SourceDetectorConfigWindow *sdcWindow = new SourceDetectorConfigWindow();
		sdcWindow->setSettings(sdSettings);
		if (sdcWindow->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			sdSettings = sdcWindow->getSettings();
	}

	void SettingsForm::resetDialogs_Click(object *sender, EventArgs *e)
	{
		internalSettings->setDialogSettings(new DialogSettings());
		MessageBox::Show(this, "Successfully reset all dialogs", "Success", MessageBoxButtons::OK, MessageBoxIcon::None);
	}

	void SettingsForm::runCommand_CheckedChanged(object *sender, EventArgs *e)
	{
		command->Enabled = runCommand->Checked;
	}

	void SettingsForm::autoEncodeDefaultsButton_Click(object *sender, EventArgs *e)
	{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (AutoEncodeDefaults aed = new AutoEncodeDefaults())
		AutoEncodeDefaults *aed = new AutoEncodeDefaults();
		try
		{
			aed->setSettings(this->autoEncodeDefaults);
			DialogResult *dr = aed->ShowDialog();
			if (dr == System::Windows::Forms::DialogResult::OK)
			{
				this->autoEncodeDefaults = aed->getSettings();
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (aed != 0)
				aed.Dispose();
		}
	}

	void SettingsForm::configureServersButton_Click(object *sender, EventArgs *e)
	{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (MeGUI.core.gui.AutoUpdateServerConfigWindow w = new MeGUI.core.gui.AutoUpdateServerConfigWindow())
		MeGUI::core::gui::AutoUpdateServerConfigWindow *w = new MeGUI::core::gui::AutoUpdateServerConfigWindow();
		try
		{
			w->setServerList(internalSettings->getAutoUpdateServerLists());
			w->setServerListIndex(cbAutoUpdateServerSubList->SelectedIndex);
			if (w->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				internalSettings->setAutoUpdateServerLists(w->getServerList());
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (w != 0)
				w.Dispose();
		}
	}

	void SettingsForm::cbHttpProxyMode_SelectedIndexChanged(object *sender, EventArgs *e)
	{
		ProxyMode httpProxyMode = static_cast<ProxyMode>(this->cbHttpProxyMode->SelectedIndex);

		txt_httpproxyaddress->Enabled = httpProxyMode == CustomProxy || httpProxyMode == CustomProxyWithLogin;
		txt_httpproxyport->Enabled = httpProxyMode == CustomProxy || httpProxyMode == CustomProxyWithLogin;
		txt_httpproxyuid->Enabled = httpProxyMode == CustomProxyWithLogin;
		txt_httpproxypwd->Enabled = httpProxyMode == CustomProxyWithLogin;
	}

	void SettingsForm::clearDefaultOutputDir_Click(object *sender, EventArgs *e)
	{
		defaultOutputDir->setFilename("");
	}

	const MeGUISettings &SettingsForm::getSettings() const
	{
		MeGUISettings *settings = internalSettings;
		settings->setAudioSamplesPerUpdate(static_cast<unsigned long long>(audiosamplesperupdate->Value));
		settings->setAcceptableFPSError(acceptableFPSError->Value);
		settings->setAutoUpdate(useAutoUpdateCheckbox->Checked);
		settings->setSourceDetectorSettings(sdSettings);
		settings->setNeroAacEncPath(neroaacencLocation->getFilename());
		settings->setVideoExtension(videoExtension->Text);
		settings->setAudioExtension(audioExtension->Text);
		settings->setUseAdvancedTooltips(chkboxUseAdvancedTooltips->Checked);
		settings->setDefaultLanguage1(defaultLanguage1->Text);
		settings->setDefaultLanguage2(defaultLanguage2->Text);
		settings->setAutoForceFilm(autoForceFilm->Checked);
		settings->setAutoLoadDG(cbAutoLoadDG->Checked);
		settings->setEnsureCorrectPlaybackSpeed(chkEnsureCorrectPlaybackSpeed->Checked);
		settings->setForceFilmThreshold(forceFilmPercentage->Value);
		settings->setDefaultPriority(static_cast<ProcessPriority>(priority->SelectedIndex));
		settings->setOpenAVSInThread(cbOpenAVSinThread->Checked);
		if (cbOpenAVSinThread->CheckState == CheckState->Checked)
			settings->setOpenAVSInThreadDuringSession(true);
		else
			settings->setOpenAVSInThreadDuringSession(false);
		settings->setAutoStartQueue(this->autostartQueue->Checked);
		settings->setAutoStartQueueStartup(this->cbAutoStartQueueStartup->Checked);
		settings->setAlwaysMuxMKV(this->chkAlwaysMuxMKV->Checked);
		if (donothing->Checked)
			settings->setAfterEncoding(DoNothing);
		else if (shutdown->Checked)
			settings->setAfterEncoding(Shutdown);
		else if (rbCloseMeGUI->Checked)
			settings->setAfterEncoding(CloseMeGUI);
		else
		{
			settings->setAfterEncoding(RunCommand);
			settings->setAfterEncodingCommand(command->Text);
		}
		settings->setAutoOpenScript(openScript->Checked);
		settings->setDeleteCompletedJobs(deleteCompletedJobs->Checked);
		settings->setDeleteIntermediateFiles(deleteIntermediateFiles->Checked);
		settings->setDeleteAbortedOutput(deleteAbortedOutput->Checked);
		settings->setOpenProgressWindow(openProgressWindow->Checked);
		settings->setKeep2of3passOutput(keep2ndPassOutput->Checked);
		settings->setOverwriteStats(keep2ndPassLogFile->Checked);
		settings->setNbPasses(static_cast<int>(nbPasses->Value));
		settings->setAutoSelectHDStreams(chkSelectHDTracks->Checked);
		settings->setAedSettings(this->autoEncodeDefaults);
		settings->setAlwaysOnTop(chAlwaysOnTop->Checked);
		settings->setHttpProxyMode(static_cast<ProxyMode>(this->cbHttpProxyMode->SelectedIndex));
		settings->setHttpProxyAddress(txt_httpproxyaddress->Text);
		settings->setHttpProxyPort(txt_httpproxyport->Text);
		settings->setHttpProxyUid(txt_httpproxyuid->Text);
		settings->setHttpProxyPwd(txt_httpproxypwd->Text);
		settings->setDefaultOutputDir(defaultOutputDir->getFilename());
		settings->setTempDirMP4(tempDirMP4->getFilename());
		settings->setAddTimePosition(cbAddTimePos->Checked);
		settings->setAlwaysBackUpFiles(backupfiles->Checked);
		settings->setForceRawAVCExtension(forcerawavcuse->Checked);
		settings->setAutoUpdateServerSubList(cbAutoUpdateServerSubList->SelectedIndex);
		settings->setUse64bitX264(chkEnable64bitX264->Checked);
		settings->setFFMSThreads(Decimal::ToInt32(ffmsThreads->Value));
		settings->setAppendToForcedStreams(txtForcedName->Text);
		settings->setUseITUValues(cbUseITUValues->Checked);
		settings->setUseNeroAacEnc(useNeroAacEnc->Checked);
		settings->setUseDGIndexNV(useDGIndexNV->Checked);
		settings->setUseQAAC(useQAAC->Checked);
		settings->setUseExternalMuxerX264(chx264ExternalMuxer->Checked);
		settings->setUse10bitsX264(chUse10BitsX264->Checked);
		return settings;
	}

	void SettingsForm::setSettings(const MeGUISettings &value)
	{
		internalSettings = value;
		MeGUISettings *settings = value;
		audiosamplesperupdate->Value = settings->getAudioSamplesPerUpdate();
		acceptableFPSError->Value = settings->getAcceptableFPSError();
		useAutoUpdateCheckbox->Checked = settings->getAutoUpdate();
		neroaacencLocation->setFilename(settings->getNeroAacEncPath());
		sdSettings = settings->getSourceDetectorSettings();
		chkboxUseAdvancedTooltips->Checked = settings->getUseAdvancedTooltips();
		videoExtension->Text = settings->getVideoExtension();
		audioExtension->Text = settings->getAudioExtension();
		chkEnsureCorrectPlaybackSpeed->Checked = settings->getEnsureCorrectPlaybackSpeed();
		int index = this->defaultLanguage1->Items->find(settings->getDefaultLanguage1());
		if (index != -1)
			defaultLanguage1->SelectedIndex = index;
		index = defaultLanguage2->Items->find(settings->getDefaultLanguage2());
		if (index != -1)
			defaultLanguage2->SelectedIndex = index;
		autoForceFilm->Checked = settings->getAutoForceFilm();
		cbAutoLoadDG->Checked = settings->getAutoLoadDG();
		forceFilmPercentage->Value = settings->getForceFilmThreshold();
		priority->SelectedIndex = static_cast<int>(settings->getDefaultPriority());
		cbOpenAVSinThread->Checked = settings->getOpenAVSInThread();
		if (settings->getOpenAVSInThread() && !settings->getOpenAVSInThreadDuringSession())
			cbOpenAVSinThread->CheckState = CheckState::Indeterminate;
		autostartQueue->Checked = settings->getAutoStartQueue();
		cbAutoStartQueueStartup->Checked = settings->getAutoStartQueueStartup();
		chkAlwaysMuxMKV->Checked = settings->getAlwaysMuxMKV();
		donothing->Checked = settings->getAfterEncoding() == DoNothing;
		shutdown->Checked = settings->getAfterEncoding() == Shutdown;
		runCommand->Checked = settings->getAfterEncoding() == RunCommand;
		rbCloseMeGUI->Checked = settings->getAfterEncoding() == CloseMeGUI;
		command->Text = settings->getAfterEncodingCommand();
		deleteCompletedJobs->Checked = settings->getDeleteCompletedJobs();
		openScript->Checked = settings->getAutoOpenScript();
		deleteIntermediateFiles->Checked = settings->getDeleteIntermediateFiles();
		deleteAbortedOutput->Checked = settings->getDeleteAbortedOutput();
		openProgressWindow->Checked = settings->getOpenProgressWindow();
		keep2ndPassOutput->Checked = settings->getKeep2of3passOutput();
		keep2ndPassLogFile->Checked = settings->getOverwriteStats();
		nbPasses->Value = static_cast<decimal>(settings->getNbPasses());
		chkSelectHDTracks->Checked = settings->getAutoSelectHDStreams();
		this->autoEncodeDefaults = settings->getAedSettings();
		chAlwaysOnTop->Checked = settings->getAlwaysOnTop();
		cbHttpProxyMode->SelectedIndex = static_cast<int>(settings->getHttpProxyMode());
		txt_httpproxyaddress->Text = settings->getHttpProxyAddress();
		txt_httpproxyport->Text = settings->getHttpProxyPort();
		txt_httpproxyuid->Text = settings->getHttpProxyUid();
		txt_httpproxypwd->Text = settings->getHttpProxyPwd();
		defaultOutputDir->setFilename(settings->getDefaultOutputDir());
		tempDirMP4->setFilename(settings->getTempDirMP4());
		cbAddTimePos->Checked = settings->getAddTimePosition();
		backupfiles->Checked = settings->getAlwaysBackUpFiles();
		forcerawavcuse->Checked = settings->getForceRawAVCExtension();
		cbAutoUpdateServerSubList->SelectedIndex = settings->getAutoUpdateServerSubList();
		chkEnable64bitX264->Checked = settings->getUse64bitX264();
		txtForcedName->Text = settings->getAppendToForcedStreams();
		if (ffmsThreads->Maximum < settings->getFFMSThreads())
			ffmsThreads->Value = ffmsThreads->Maximum;
		else
			ffmsThreads->Value = settings->getFFMSThreads();
		cbUseITUValues->Checked = settings->getUseITUValues();
		useNeroAacEnc->Checked = settings->getUseNeroAacEnc();
		useDGIndexNV->Checked = settings->getUseDGIndexNV();
		useQAAC->Checked = settings->getUseQAAC();
		chx264ExternalMuxer->Checked = settings->getUseExternalMuxerX264();
		chUse10BitsX264->Checked = settings->getUse10bitsX264();
	}

	void SettingsForm::backupfiles_CheckedChanged(object *sender, EventArgs *e)
	{
		if (!backupfiles->Checked)
		{
			std::string meguiToolsFolder = Application::ExecutablePath->substr(0, Application::ExecutablePath->rfind('\\'));
			std::string meguiAvisynthFolder = MainForm::Instance->getSettings()->getAvisynthPluginsPath() + "\\";
			if (Directory::Exists(meguiToolsFolder))
			{
				try
				{ // remove all backup files found
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Array::ForEach(Directory::GetFiles(meguiToolsFolder, "*.backup", SearchOption::AllDirectories), delegate(std::string path)
					{
						File::Delete(path);
					}
				   );
				}
				catch (std::exception &ex)
				{
					MessageBox::Show(ex.what(), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			if (Directory::Exists(meguiAvisynthFolder))
			{
				try
				{ // remove all backup files found
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Array::ForEach(Directory::GetFiles(meguiAvisynthFolder, "*.backup", SearchOption::AllDirectories), delegate(std::string path)
					{
						File::Delete(path);
					}
				   );
				}
				catch (std::exception &ex)
				{
					MessageBox::Show(ex.what(), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}
	}

	void SettingsForm::btnClearMP4TempDirectory_Click(object *sender, EventArgs *e)
	{
		tempDirMP4->setFilename("");
	}

	void SettingsForm::btnClearOutputDirecoty_Click(object *sender, EventArgs *e)
	{
		defaultOutputDir->setFilename("");
	}

	void SettingsForm::tempDirMP4_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		if (System::IO::Path::GetPathRoot(tempDirMP4->getFilename())->Equals(tempDirMP4->getFilename(), StringComparison::CurrentCultureIgnoreCase))
		{
			// mp4box has in some builds problems if the tmp directory is in the root of a drive
			MessageBox::Show("A root folder cannot be selected!", "Wrong path", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			tempDirMP4->setFilename("");
		}
	}

	void SettingsForm::useNeroAacEnc_CheckedChanged(object *sender, EventArgs *e)
	{
		neroaacencLocation->Enabled = lblNero->Enabled = useNeroAacEnc->Checked;
		if (useNeroAacEnc->Checked && !internalSettings->getUseNeroAacEnc())
			MessageBox::Show("You have to restart MeGUI in order to get access to NeroAacEnc", "Restart required", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	void SettingsForm::useQAAC_CheckedChanged(object *sender, EventArgs *e)
	{
		if (!useQAAC->Checked || internalSettings->getUseQAAC())
			return;

		if (!File::Exists(getSettings()->getQaacPath()))
		{
			// qaac.exe is not available. Therefore an update check is necessary
			if (MessageBox::Show("The QAAC component is not installed.\n\nDo you want to search now online for updates?", "MeGUI component missing", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes)
			{
				MessageBox::Show("The updater will now be started. Please retart MeGUI after the update process has finished in order to get access to QAAC.", "Restart after update required", MessageBoxButtons::OK, MessageBoxIcon::Information);
				MainForm::Instance->startUpdateCheck();
			}
			else
				MessageBox::Show("You have selected to not update QAAC. Therefore QAAC will not be available. Run the updater on your own if you want to enable QAAC later.", "QAAC not enabled", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else
			MessageBox::Show("You have to restart MeGUI in order to get access to QAAC.", "Restart required", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	void SettingsForm::chUse10BitsX264_CheckedChanged(object *sender, EventArgs *e)
	{
		if (!chUse10BitsX264->Checked || internalSettings->getUse10bitsX264())
			return;

		if (!File::Exists(getSettings()->getX26410BitsPath()))
		{
			// x264-10b is not available. Therefore an update check is necessary
			if (MessageBox::Show("The x264 10bit component is not installed.\n\nDo you want to search now online for updates?", "MeGUI component missing", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes)
				MainForm::Instance->startUpdateCheck();
			else
				MessageBox::Show("You have selected to not update x264 10bit. Therefore it will not be available. Run the updater on your own if you want to enable it later.", "x264 10bit not enabled", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

	void SettingsForm::InitializeInstanceFields()
	{
		internalSettings = new MeGUISettings();
		ContextHelp = new XmlDocument();
	}
}
