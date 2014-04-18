#include "MeGUI.packages.tools.calculator.AudioTrackSizeTab.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace MediaInfoWrapper;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace calculator
			{

				AudioTrackSizeTab::AudioTrackSizeTab() : filter(VideoUtil::GenerateCombinedFilter(ContainerManager::AudioTypes->ValuesArray))
				{
					InitializeInstanceFields();
					InitializeComponent();
					this->audio1Type->Items->AddRange(ContainerManager::AudioTypes->getValuesArray());

					DragDropUtil::RegisterSingleFileDragDrop(this, new SingleFileReceiver(this, &AudioTrackSizeTab::selectAudioFile), this->filter);
				}

				void AudioTrackSizeTab::SetAudioJob(AudioJob *job)
				{
					audio1Bitrate->Value = job->Settings->getBitrate();
					if (job->getType() != 0 && audio1Type->Items->Contains(job->getType()))
						audio1Type->SelectedItem = job->getType();
				}

				const long long &AudioTrackSizeTab::getPlayLength() const
				{
					return length;
				}

				void AudioTrackSizeTab::setPlayLength(const long long &value)
				{
					length = value;
					audio1Bitrate_ValueChanged(0, 0);
				}

				void AudioTrackSizeTab::audio1Bitrate_ValueChanged(object *sender, EventArgs *e)
				{
					if (length <= 0)
						return;

					if (updating)
						return;

					updating = true;

					int bitrate = static_cast<int>(audio1Bitrate->Value);
					if (bitrate > 0 && audio1Type->SelectedIndex == -1)
						audio1Type->SelectedItem = AudioType::VBRMP3;
					double bytesPerSecond = static_cast<double>(bitrate) * 1000.0 / 8.0;
					FileSize f = FileSize(static_cast<unsigned long long>(length * bytesPerSecond));
					//size.CertainValue = f;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					size->Text = f.ToString();
					raiseEvent();
					updating = false;
				}

				void AudioTrackSizeTab::raiseEvent()
				{
					SomethingChanged(this, EventArgs::Empty);
				}

				void AudioTrackSizeTab::selectAudioFile(const std::string &file)
				{
					Nullable<FileSize> tempVar = FileSize.Of2(file);
					FileSize f = tempVar::HasValue ? tempVar : FileSize::Empty;
					//size.CertainValue = f;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					size->Text = f.ToString();
					audio1Bitrate->Value = (length > 0) ? static_cast<long long>(f.getBytes() * 8) / 1000LL / length : 0;
					name->Text = System::IO::Path::GetFileName(file);

					AudioType *aud2Type = VideoUtil::guessAudioType(file);
					if (audio1Type->Items->Contains(aud2Type))
						audio1Type->SelectedItem = aud2Type;

					//MediaInfo info;
					//try
					//{
					//    info = new MediaInfo(file);
					//    MediaInfoWrapper.AudioTrack atrack = info.Audio[0];
					//    //this.length = atrack.Duration
					//    if (atrack.Format == "DTS" && (atrack.BitRate == "768000" || atrack.BitRate == "1536000"))
					//    {
					//        audio1Bitrate.Value = (Convert.ToInt32(atrack.BitRate) / 1000);
					//    }
					//}
					//catch (Exception i)
					//{
					//    MessageBox.Show("The following error ocurred when trying to get Media info for file " + file + "\r\n" + i.Message, "Error parsing mediainfo data", MessageBoxButtons.OK);                
					//}

				}

				void AudioTrackSizeTab::selectButton_Click(object *sender, EventArgs *e)
				{
					openFileDialog->Filter = this->filter;
					if (openFileDialog->ShowDialog() == DialogResult::OK)
					{
						selectAudioFile(openFileDialog->FileName);
					}
				}

				const MeGUI::core::details::AudioBitrateCalculationStream &AudioTrackSizeTab::getStream() const
				{
					if (audio1Type->SelectedIndex > -1)
					{
						AudioBitrateCalculationStream *stream = new AudioBitrateCalculationStream();
						stream->Type = stream->AType = dynamic_cast<AudioType*>(audio1Type->SelectedItem);
						//stream.Size = size.CertainValue;
						stream->Size = FileSize::Parse(size->Text);
						return stream;
					}
					return 0;
				}

				void AudioTrackSizeTab::size_SelectionChanged(object *sender, const std::string &val)
				{
					if (length <= 0)
						return;

					if (updating)
						return;

					updating = true;

					FileSize s = FileSize::Parse(size->Text); //size.CertainValue;
					if (s > FileSize::Empty && audio1Type->SelectedIndex == -1)
						audio1Type->SelectedItem = AudioType::VBRMP3;

					double bytesPerSecond = static_cast<double>(s.getBytes()) / static_cast<double>(length);
					int bitrate = static_cast<int>(bytesPerSecond * 8.0 / 1000.0);

					if (bitrate > audio1Bitrate->Maximum)
						audio1Bitrate->Maximum = bitrate;

					audio1Bitrate->Value = bitrate;
					raiseEvent();

					updating = false;
				}

				void AudioTrackSizeTab::audio1Type_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					bool en = audio1Type->SelectedIndex > -1;
					audio1Bitrate->Enabled = en;
					size->Enabled = en;

					raiseEvent();
				}

				void AudioTrackSizeTab::removeLink_LinkClicked(object *sender, EventArgs *e)
				{
					if (this->Parent != 0)
						this->Parent->Controls->Remove(this);
				}

				void AudioTrackSizeTab::AudioTrackSizeTab_Enter(object *sender, EventArgs *e)
				{
					selectButton->Focus();
				}

				void AudioTrackSizeTab::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					UserControl::Dispose(disposing);
				}

				void AudioTrackSizeTab::InitializeComponent()
				{
					this->components = new System::ComponentModel::Container();
					System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(AudioTrackSizeTab::typeid);
					this->label2 = new System::Windows::Forms::Label();
					this->label1 = new System::Windows::Forms::Label();
					this->audio1Bitrate = new System::Windows::Forms::NumericUpDown();
					this->selectButton = new System::Windows::Forms::Button();
					this->audio1Type = new System::Windows::Forms::ComboBox();
					this->audio1TypeLabel = new System::Windows::Forms::Label();
					this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
					this->audioLabel = new System::Windows::Forms::Label();
					this->name = new System::Windows::Forms::TextBox();
					this->size = new System::Windows::Forms::TextBox();
					this->removeLink = new System::Windows::Forms::LinkLabel();
					this->removalToolTip = new System::Windows::Forms::ToolTip(this->components);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->audio1Bitrate))->BeginInit();
					this->SuspendLayout();
					// 
					// label2
					// 
					this->label2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->label2->AutoSize = true;
					this->label2->Location = new System::Drawing::Point(354, 8);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(27, 13);
					this->label2->TabIndex = 22;
					this->label2->Text = "Size";
					// 
					// label1
					// 
					this->label1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->label1->AutoSize = true;
					this->label1->Location = new System::Drawing::Point(279, 8);
					this->label1->Name = "label1";
					this->label1->Size = new System::Drawing::Size(37, 13);
					this->label1->TabIndex = 20;
					this->label1->Text = "Bitrate";
					// 
					// audio1Bitrate
					// 
					this->audio1Bitrate->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->audio1Bitrate->Enabled = false;
					this->audio1Bitrate->Increment = decimal(new int[4] {16, 0, 0, 0});
					this->audio1Bitrate->Location = new System::Drawing::Point(282, 28);
					this->audio1Bitrate->Maximum = decimal(new int[4] {100000, 0, 0, 0});
					this->audio1Bitrate->Name = "audio1Bitrate";
					this->audio1Bitrate->Size = new System::Drawing::Size(66, 20);
					this->audio1Bitrate->TabIndex = 2;
					this->audio1Bitrate->ThousandsSeparator = true;
					this->audio1Bitrate->ValueChanged += new System::EventHandler(this, &AudioTrackSizeTab::audio1Bitrate_ValueChanged);
					// 
					// selectButton
					// 
					this->selectButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->selectButton->Location = new System::Drawing::Point(160, 27);
					this->selectButton->Name = "selectButton";
					this->selectButton->Size = new System::Drawing::Size(24, 21);
					this->selectButton->TabIndex = 0;
					this->selectButton->Text = "...";
					this->selectButton->Click += new System::EventHandler(this, &AudioTrackSizeTab::selectButton_Click);
					// 
					// audio1Type
					// 
					this->audio1Type->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->audio1Type->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->audio1Type->Location = new System::Drawing::Point(197, 27);
					this->audio1Type->Name = "audio1Type";
					this->audio1Type->Size = new System::Drawing::Size(75, 21);
					this->audio1Type->TabIndex = 1;
					this->audio1Type->SelectedIndexChanged += new System::EventHandler(this, &AudioTrackSizeTab::audio1Type_SelectedIndexChanged);
					// 
					// audio1TypeLabel
					// 
					this->audio1TypeLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->audio1TypeLabel->Location = new System::Drawing::Point(194, 8);
					this->audio1TypeLabel->Name = "audio1TypeLabel";
					this->audio1TypeLabel->Size = new System::Drawing::Size(40, 16);
					this->audio1TypeLabel->TabIndex = 26;
					this->audio1TypeLabel->Text = "Type";
					// 
					// audioLabel
					// 
					this->audioLabel->Location = new System::Drawing::Point(30, 8);
					this->audioLabel->Name = "audioLabel";
					this->audioLabel->Size = new System::Drawing::Size(40, 16);
					this->audioLabel->TabIndex = 31;
					this->audioLabel->Text = "Audio";
					// 
					// name
					// 
					this->name->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->name->Location = new System::Drawing::Point(8, 28);
					this->name->Name = "name";
					this->name->ReadOnly = true;
					this->name->Size = new System::Drawing::Size(150, 20);
					this->name->TabIndex = 32;
					this->name->TabStop = false;
					this->name->Enter += new System::EventHandler(this, &AudioTrackSizeTab::selectButton_Click);
					// 
					// size
					// 
					this->size->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->size->Location = new System::Drawing::Point(357, 28);
					this->size->Name = "size";
					this->size->ReadOnly = true;
					this->size->Size = new System::Drawing::Size(70, 20);
					this->size->TabIndex = 3;
					this->size->TabStop = false;
					// 
					// removeLink
					// 
					this->removeLink->Cursor = System::Windows::Forms::Cursors::Hand;
					this->removeLink->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("removeLink.Image")));
					this->removeLink->Location = new System::Drawing::Point(5, 3);
					this->removeLink->Name = "removeLink";
					this->removeLink->Padding = new System::Windows::Forms::Padding(16, 0, 3, 3);
					this->removeLink->Size = new System::Drawing::Size(27, 23);
					this->removeLink->TabIndex = 4;
					this->removeLink->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->removalToolTip->SetToolTip(this->removeLink, "Audio track");
					this->removeLink->LinkClicked += new System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &AudioTrackSizeTab::removeLink_LinkClicked);
					this->removeLink->Click += new System::EventHandler(this, &AudioTrackSizeTab::removeLink_LinkClicked);
					// 
					// removalToolTip
					// 
					this->removalToolTip->AutomaticDelay = 300;
					this->removalToolTip->ToolTipTitle = "Remove";
					// 
					// AudioTrackSizeTab
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->Controls->Add(this->removeLink);
					this->Controls->Add(this->size);
					this->Controls->Add(this->name);
					this->Controls->Add(this->audioLabel);
					this->Controls->Add(this->label2);
					this->Controls->Add(this->label1);
					this->Controls->Add(this->audio1Bitrate);
					this->Controls->Add(this->selectButton);
					this->Controls->Add(this->audio1Type);
					this->Controls->Add(this->audio1TypeLabel);
					this->Name = "AudioTrackSizeTab";
					this->Size = new System::Drawing::Size(435, 50);
					this->Enter += new System::EventHandler(this, &AudioTrackSizeTab::AudioTrackSizeTab_Enter);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->audio1Bitrate))->EndInit();
					this->ResumeLayout(false);
					this->PerformLayout();

				}

				void AudioTrackSizeTab::InitializeInstanceFields()
				{
					updating = false;
					delete components;
				}
			}
		}
	}
}
