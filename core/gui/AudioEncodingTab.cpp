#include "MeGUI.core.gui.AudioEncodingTab.h"




//using namespace System::Collections::Generic;





//using namespace System::Data;



//using namespace System::Text;

//using namespace System::Text::RegularExpressions;


using namespace MeGUI::core::details::video;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			const QString &AudioEncodingTab::getQueueButtonText() const
			{
				return queueAudioButton->Text;
			}

			void AudioEncodingTab::setQueueButtonText(const QString &value)
			{
				queueAudioButton->Text = value;
			}

			const QString &AudioEncodingTab::getAudioContainer() const
			{
				return audioContainer->Text;
			}

			void AudioEncodingTab::setAudioContainer(const QString &value)
			{
				audioContainer->Text = value;
			}

			const MeGUI::AudioEncoderProvider &AudioEncodingTab::getAudioEncoderProvider() const
			{
				return audioEncoderProvider;
			}

			const QString &AudioEncodingTab::getAudioInput() const
			{
				return audioInput->getFilename();
			}

			void AudioEncodingTab::setAudioInput(const QString &value)
			{
				audioInput->setFilename(value);
			}

			const QString &AudioEncodingTab::getAudioOutput() const
			{
				return audioOutput->getFilename();
			}

			void AudioEncodingTab::setAudioOutput(const QString &value)
			{
				audioOutput->setFilename(value);
			}

			const MeGUI::AudioCodecSettings &AudioEncodingTab::getAudCodecSettings() const
			{
				return static_cast<AudioCodecSettings*>(audioProfile->getSelectedProfile()->BaseSettings);
			}

			void AudioEncodingTab::setAudCodecSettings(const AudioCodecSettings &value)
			{
				audioProfile->SetSettings(value);
			}

			QString AudioEncodingTab::verifyAudioSettings()
			{
				Nullable<int> tempVar = PrettyFormatting.getDelay(getAudioInput());
				int inputDelay = tempVar::HasValue ? tempVar : 0;
				Nullable<int> delay = PrettyFormatting::getDelay(getAudioOutput());
				if (delay.HasValue && delay.Value != (inputDelay - static_cast<int>(this->delay->Value)))
				{
					if (MessageBox::Show(QString::Format("The output filename suggests the audio delay is {0}ms. " + "However, the input delay is {1}ms and the delay correction is {2}ms, " + "so a delay of {3}ms is more appropriate. Do you want MeGUI to correct " + "the output filename before adding the job?", delay.Value, inputDelay, this->delay->Value, (inputDelay - static_cast<int>(this->delay->Value))), "Output filename suggests wrong delay", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == DialogResult::Yes)
						setAudioOutput(PrettyFormatting::ReplaceDelay(getAudioOutput(), (inputDelay - static_cast<int>(this->delay->Value))));
				}

				MeGUI::AudioJob *stream;

				try
				{
					stream = getAudioJob();
				}
				catch (MeGUIException *m)
				{
					return m->what();
				}

				if (stream == 0)
					return "Audio input, audio output, and audio settings must all be configured";

				QString fileErr = MainForm::verifyOutputFile(this->getAudioOutput());
				if (fileErr != "")
				{
					return "Problem with audio output filename:\n" + fileErr;
				}
				AudioType *aot = dynamic_cast<AudioType*>(this->audioContainer->SelectedItem);
				// test output file extension
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				if (!Path::GetExtension(this->getAudioOutput())->Replace(".", "")->Equals(aot->getExtension(), StringComparison::InvariantCultureIgnoreCase))
				{
					return "Audio output filename does not have the correct extension.\nBased on current settings, it should be " + aot->getExtension();
				}
				return 0;
			}

			AudioEncodingTab::AudioEncodingTab()
			{
				InitializeInstanceFields();
				InitializeComponent();
				if (MainForm::Instance != 0) // Fix to allow VS2008 designer to load Form1
					audioProfile->setManager(MainForm::Instance->getProfiles());
			}

			void AudioEncodingTab::audioInput_FileSelected(FileBar *sender, FileBarQEvent *args)
			{
				if (audioInput->getFilename().empty())
					return;

				MediaInfoFile *iFile = new MediaInfoFile(audioInput->getFilename());
				if (!iFile->getHasAudio())
				{
					audioInput->setFilename("");
					audioOutput->setFilename("");
					MessageBox::Show("This file cannot be processed", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				else
					openAudioFile(audioInput->getFilename());
			}

			void AudioEncodingTab::audioContainer_SelectedIndexChanged(QObject *sender, QEvent *e)
			{
				AudioType *currentType = static_cast<AudioType*>(audioContainer->SelectedItem);
				audioOutput->setFilter(currentType->getOutputFilterString());
				setAudioOutput(Path::ChangeExtension(getAudioOutput(), currentType->getExtension()));
				if (!audioInput->getFilename().empty())
					if (audioInput->getFilename().Equals(audioOutput->getFilename()) || File::Exists(getAudioOutput()))
						setAudioOutput(Path::Combine(Path::GetDirectoryName(getAudioOutput()), Path::GetFileNameWithoutExtension(getAudioOutput()) + "_new." + currentType->getExtension()));
				if (!bInitialStart)
					MainForm::Instance->getSettings()->setMainAudioFormat(audioContainer->Text);
				else
					bInitialStart = false;
			}

			void AudioEncodingTab::deleteAudioButton_Click(QObject *sender, QEvent *e)
			{
				Reset();
			}

			void AudioEncodingTab::queueAudioButton_Click(QObject *sender, QEvent *e)
			{
				QString settingsError = verifyAudioSettings();
				if (settingsError != "")
				{
					MessageBox::Show(settingsError, "Unsupported configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
					return;
				}
				QueueJob(getAudioJob());
			}

			const MeGUI::AudioJob &AudioEncodingTab::getAudioJob() const
			{
				if (getAudioInput().empty() || getAudioOutput().empty() || getAudCodecSettings() == 0)
					return 0;

				return new AudioJob(this->getAudioInput(), this->getAudioOutput(), this->cuts->getFilename(), this->getAudCodecSettings(), static_cast<int>(delay->Value), 0, 0);
			}

			void AudioEncodingTab::setAudioJob(const MeGUI::AudioJob &value)
			{
				setAudioInput(value->Input);
				setAudioOutput(value->Output);
				setAudCodecSettings(value->Settings);
				cuts->setFilename(value->CutFile);
				delay->Value = value->Delay;
			}

			void AudioEncodingTab::openAudioFile(const QString &fileName)
			{
				setAudioInput(fileName);
				Nullable<int> tempVar = PrettyFormatting.getDelayAndCheck(fileName);
				delay->Value = tempVar::HasValue ? tempVar : 0;

				try
				{
					setAudioOutput(FileUtil::AddToFileName(PrettyFormatting::ReplaceDelay(fileName, 0), MainForm::Instance->getSettings()->getAudioExtension()));
				}
				catch (std::exception &e)
				{
				   throw new ApplicationException("The value detected as delay in your filename seems to be too high/low for MeGUI." + "Try to recreate it with the appropriate tools." + e.what(), e);
				}

				QString projectPath;
				if (!(projectPath = MainForm::Instance->getSettings()->getDefaultOutputDir())->empty())
					setAudioOutput(Path::Combine(projectPath, Path::GetFileName(getAudioOutput())));

				audioContainer_SelectedIndexChanged(0, 0);
			}

			const Size &AudioEncodingTab::getFileTypeComboBoxSize() const
			{
				return audioContainer->Size;
			}

			void AudioEncodingTab::setFileTypeComboBoxSize(const Size &value)
			{
				audioContainer->Size = value;
			}

			void AudioEncodingTab::Reset()
			{
				this->setAudioInput("");
				this->cuts->setFilename("");
				this->setAudioOutput("");
				this->delay->Value = 0;
			}

			void AudioEncodingTab::audioProfile_SelectedProfileChanged(QObject *sender, QEvent *e)
			{
				if (lastCodec == getAudCodecSettings()->getEncoderType())
					return;

				lastCodec = getAudCodecSettings()->getEncoderType();
				Util::ChangeItemsKeepingSelectedSame(audioContainer, getAudioEncoderProvider()->GetSupportedOutput(lastCodec));
			}

			void AudioEncodingTab::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				UserControl::Dispose(disposing);
			}

			void AudioEncodingTab::InitializeComponent()
			{
				this->label1 = new System::Windows::Forms::Label();
				this->audioContainer = new System::Windows::Forms::ComboBox();
				this->audioContainerLabel = new System::Windows::Forms::Label();
				this->queueAudioButton = new System::Windows::Forms::Button();
				this->audioInputLabel = new System::Windows::Forms::Label();
				this->audioOutputLabel = new System::Windows::Forms::Label();
				this->deleteAudioButton = new System::Windows::Forms::Button();
				this->label2 = new System::Windows::Forms::Label();
				this->delay = new System::Windows::Forms::NumericUpDown();
				this->label3 = new System::Windows::Forms::Label();
				this->label4 = new System::Windows::Forms::Label();
				this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
				this->audioProfile = new MeGUI::core::gui::ConfigableProfilesControl();
				this->audioOutput = new MeGUI::FileBar();
				this->cuts = new MeGUI::FileBar();
				this->audioInput = new MeGUI::FileBar();
				this->flowLayoutPanel1 = new System::Windows::Forms::FlowLayoutPanel();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->delay))->BeginInit();
				this->tableLayoutPanel1->SuspendLayout();
				this->flowLayoutPanel1->SuspendLayout();
				this->SuspendLayout();
				// 
				// label1
				// 
				this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->label1->Location = new System::Drawing::Point(3, 28);
				this->label1->Name = "label1";
				this->label1->Size = new System::Drawing::Size(86, 28);
				this->label1->TabIndex = 17;
				this->label1->Text = "Cuts";
				this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				// 
				// audioContainer
				// 
				this->audioContainer->Dock = System::Windows::Forms::DockStyle::Fill;
				this->audioContainer->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				this->audioContainer->FormattingEnabled = true;
				this->audioContainer->Location = new System::Drawing::Point(95, 115);
				this->audioContainer->Name = "audioContainer";
				this->audioContainer->Size = new System::Drawing::Size(143, 21);
				this->audioContainer->TabIndex = 25;
				this->audioContainer->SelectedIndexChanged += new System::EventHandler(this, &AudioEncodingTab::audioContainer_SelectedIndexChanged);
				// 
				// audioContainerLabel
				// 
				this->audioContainerLabel->Dock = System::Windows::Forms::DockStyle::Top;
				this->audioContainerLabel->Location = new System::Drawing::Point(3, 112);
				this->audioContainerLabel->Name = "audioContainerLabel";
				this->audioContainerLabel->Size = new System::Drawing::Size(86, 28);
				this->audioContainerLabel->TabIndex = 24;
				this->audioContainerLabel->Text = "Extension ";
				this->audioContainerLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				// 
				// queueAudioButton
				// 
				this->queueAudioButton->Anchor = System::Windows::Forms::AnchorStyles::Right;
				this->queueAudioButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->queueAudioButton->Location = new System::Drawing::Point(112, 3);
				this->queueAudioButton->Name = "queueAudioButton";
				this->queueAudioButton->Size = new System::Drawing::Size(60, 23);
				this->queueAudioButton->TabIndex = 27;
				this->queueAudioButton->Text = "Queue";
				this->queueAudioButton->Click += new System::EventHandler(this, &AudioEncodingTab::queueAudioButton_Click);
				// 
				// audioInputLabel
				// 
				this->audioInputLabel->Dock = System::Windows::Forms::DockStyle::Fill;
				this->audioInputLabel->Location = new System::Drawing::Point(3, 0);
				this->audioInputLabel->Name = "audioInputLabel";
				this->audioInputLabel->Size = new System::Drawing::Size(86, 28);
				this->audioInputLabel->TabIndex = 15;
				this->audioInputLabel->Text = "Audio Input";
				this->audioInputLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				// 
				// audioOutputLabel
				// 
				this->audioOutputLabel->Dock = System::Windows::Forms::DockStyle::Fill;
				this->audioOutputLabel->Location = new System::Drawing::Point(3, 56);
				this->audioOutputLabel->Name = "audioOutputLabel";
				this->audioOutputLabel->Size = new System::Drawing::Size(86, 28);
				this->audioOutputLabel->TabIndex = 19;
				this->audioOutputLabel->Text = "Audio Output";
				this->audioOutputLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				// 
				// deleteAudioButton
				// 
				this->deleteAudioButton->Anchor = System::Windows::Forms::AnchorStyles::Right;
				this->deleteAudioButton->Location = new System::Drawing::Point(58, 3);
				this->deleteAudioButton->Name = "deleteAudioButton";
				this->deleteAudioButton->Size = new System::Drawing::Size(48, 23);
				this->deleteAudioButton->TabIndex = 26;
				this->deleteAudioButton->Text = "X";
				this->deleteAudioButton->Click += new System::EventHandler(this, &AudioEncodingTab::deleteAudioButton_Click);
				// 
				// label2
				// 
				this->label2->Dock = System::Windows::Forms::DockStyle::Top;
				this->label2->Location = new System::Drawing::Point(244, 112);
				this->label2->Name = "label2";
				this->label2->Size = new System::Drawing::Size(34, 28);
				this->label2->TabIndex = 28;
				this->label2->Text = "Delay";
				this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				// 
				// delay
				// 
				this->delay->Dock = System::Windows::Forms::DockStyle::Fill;
				this->delay->Location = new System::Drawing::Point(284, 115);
				this->delay->Maximum = decimal(new int[4] {2147483647, 0, 0, 0});
				this->delay->Minimum = decimal(new int[4] {-2147483648, 0, 0, -2147483648});
				this->delay->Name = "delay";
				this->delay->Size = new System::Drawing::Size(143, 20);
				this->delay->TabIndex = 29;
				// 
				// label3
				// 
				this->label3->Dock = System::Windows::Forms::DockStyle::Top;
				this->label3->Location = new System::Drawing::Point(433, 112);
				this->label3->Name = "label3";
				this->label3->Size = new System::Drawing::Size(20, 28);
				this->label3->TabIndex = 30;
				this->label3->Text = "ms";
				this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				// 
				// label4
				// 
				this->label4->Dock = System::Windows::Forms::DockStyle::Fill;
				this->label4->Location = new System::Drawing::Point(3, 84);
				this->label4->Name = "label4";
				this->label4->Size = new System::Drawing::Size(86, 28);
				this->label4->TabIndex = 19;
				this->label4->Text = "Encoder settings";
				this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				// 
				// tableLayoutPanel1
				// 
				this->tableLayoutPanel1->ColumnCount = 5;
				this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
				this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50));
				this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
				this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50));
				this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
				this->tableLayoutPanel1->Controls->Add(this->audioInputLabel, 0, 0);
				this->tableLayoutPanel1->Controls->Add(this->audioContainer, 1, 4);
				this->tableLayoutPanel1->Controls->Add(this->label3, 4, 4);
				this->tableLayoutPanel1->Controls->Add(this->audioProfile, 1, 3);
				this->tableLayoutPanel1->Controls->Add(this->delay, 3, 4);
				this->tableLayoutPanel1->Controls->Add(this->label1, 0, 1);
				this->tableLayoutPanel1->Controls->Add(this->label2, 2, 4);
				this->tableLayoutPanel1->Controls->Add(this->audioOutputLabel, 0, 2);
				this->tableLayoutPanel1->Controls->Add(this->label4, 0, 3);
				this->tableLayoutPanel1->Controls->Add(this->audioContainerLabel, 0, 4);
				this->tableLayoutPanel1->Controls->Add(this->audioOutput, 1, 2);
				this->tableLayoutPanel1->Controls->Add(this->cuts, 1, 1);
				this->tableLayoutPanel1->Controls->Add(this->audioInput, 1, 0);
				this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 3, 5);
				this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tableLayoutPanel1->Location = new System::Drawing::Point(0, 0);
				this->tableLayoutPanel1->Name = "tableLayoutPanel1";
				this->tableLayoutPanel1->RowCount = 6;
				this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
				this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
				this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
				this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
				this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20));
				this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
				this->tableLayoutPanel1->Size = new System::Drawing::Size(456, 173);
				this->tableLayoutPanel1->TabIndex = 32;
				// 
				// audioProfile
				// 
				this->tableLayoutPanel1->SetColumnSpan(this->audioProfile, 4);
				this->audioProfile->Dock = System::Windows::Forms::DockStyle::Fill;
				this->audioProfile->Location = new System::Drawing::Point(95, 87);
				this->audioProfile->Name = "audioProfile";
				this->audioProfile->setProfileSet("Audio");
				this->audioProfile->Size = new System::Drawing::Size(358, 22);
				this->audioProfile->TabIndex = 31;
				this->audioProfile->SelectedProfileChanged += new System::EventHandler(this, &AudioEncodingTab::audioProfile_SelectedProfileChanged);
				// 
				// audioOutput
				// 
				this->tableLayoutPanel1->SetColumnSpan(this->audioOutput, 4);
				this->audioOutput->Dock = System::Windows::Forms::DockStyle::Fill;
				this->audioOutput->setFilename("");
				this->audioOutput->setFilter("");
				this->audioOutput->setFilterIndex(0);
				this->audioOutput->setFolderMode(false);
				this->audioOutput->Location = new System::Drawing::Point(95, 59);
				this->audioOutput->Name = "audioOutput";
				this->audioOutput->setReadOnly(false);
				this->audioOutput->setSaveMode(true);
				this->audioOutput->Size = new System::Drawing::Size(358, 22);
				this->audioOutput->TabIndex = 20;
				this->audioOutput->setTitle("Enter name of output");
				// 
				// cuts
				// 
				this->tableLayoutPanel1->SetColumnSpan(this->cuts, 4);
				this->cuts->Dock = System::Windows::Forms::DockStyle::Fill;
				this->cuts->setFilename("");
				this->cuts->setFilter("MeGUI cutlist files (*.clt)|*.clt");
				this->cuts->setFilterIndex(0);
				this->cuts->setFolderMode(false);
				this->cuts->Location = new System::Drawing::Point(95, 31);
				this->cuts->Name = "cuts";
				this->cuts->setReadOnly(true);
				this->cuts->setSaveMode(false);
				this->cuts->Size = new System::Drawing::Size(358, 22);
				this->cuts->TabIndex = 18;
				this->cuts->setTitle("Select a file with cuts");
				// 
				// audioInput
				// 
				this->audioInput->AllowDrop = true;
				this->tableLayoutPanel1->SetColumnSpan(this->audioInput, 4);
				this->audioInput->Dock = System::Windows::Forms::DockStyle::Fill;
				this->audioInput->setFilename("");
				this->audioInput->setFilter("All files (*.*)|*.*");
				this->audioInput->setFilterIndex(0);
				this->audioInput->setFolderMode(false);
				this->audioInput->Location = new System::Drawing::Point(95, 3);
				this->audioInput->Name = "audioInput";
				this->audioInput->setReadOnly(true);
				this->audioInput->setSaveMode(false);
				this->audioInput->Size = new System::Drawing::Size(358, 22);
				this->audioInput->TabIndex = 16;
				this->audioInput->setTitle("Select your audio input");
				this->audioInput->FileSelected += new MeGUI::FileBarEventHandler(this, &AudioEncodingTab::audioInput_FileSelected);
				// 
				// flowLayoutPanel1
				// 
				this->flowLayoutPanel1->AutoSize = true;
				this->flowLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->tableLayoutPanel1->SetColumnSpan(this->flowLayoutPanel1, 2);
				this->flowLayoutPanel1->Controls->Add(this->queueAudioButton);
				this->flowLayoutPanel1->Controls->Add(this->deleteAudioButton);
				this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->flowLayoutPanel1->FlowDirection = System::Windows::Forms::FlowDirection::RightToLeft;
				this->flowLayoutPanel1->Location = new System::Drawing::Point(281, 140);
				this->flowLayoutPanel1->Margin = new System::Windows::Forms::Padding(0);
				this->flowLayoutPanel1->Name = "flowLayoutPanel1";
				this->flowLayoutPanel1->Size = new System::Drawing::Size(175, 33);
				this->flowLayoutPanel1->TabIndex = 32;
				// 
				// AudioEncodingTab
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->Controls->Add(this->tableLayoutPanel1);
				this->Name = "AudioEncodingTab";
				this->Size = new System::Drawing::Size(456, 173);
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->delay))->EndInit();
				this->tableLayoutPanel1->ResumeLayout(false);
				this->tableLayoutPanel1->PerformLayout();
				this->flowLayoutPanel1->ResumeLayout(false);
				this->ResumeLayout(false);

			}

			void AudioEncodingTab::InitializeInstanceFields()
			{
				audioEncoderProvider = new AudioEncoderProvider();
				bInitialStart = true;
				delete lastCodec;
				delete components;
			}
		}
	}
}
