#include "MeGUI.packages.tools.oneclick.AudioConfigControl.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details::video;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace oneclick
			{

				void AudioConfigControl::initAudioHandler()
				{
					audioProfile->setManager(mainForm->getProfiles());
				}

				void AudioConfigControl::audioCodec_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					raiseEvent();
				}

				void AudioConfigControl::ProfileChanged(object *o, EventArgs *e)
				{
					raiseEvent();
				}

				void AudioConfigControl::dontEncodeAudio_CheckedChanged(object *sender, EventArgs *e)
				{
					audioProfile->Enabled = !cbAudioEncoding->SelectedText->Equals("never");
					raiseEvent();
				}

				void AudioConfigControl::raiseEvent()
				{
					SomethingChanged(this, 0);
				}

				const MeGUI::AudioCodecSettings &AudioConfigControl::getSettings() const
				{
					return static_cast<AudioCodecSettings*>(audioProfile->getSelectedProfile()->BaseSettings);
				}

				void AudioConfigControl::setDelayEnabled(const bool &value)
				{
					delay->Enabled = value;
				}

				const bool &AudioConfigControl::getDelayEnabled() const
				{
					return delay->Enabled;
				}

				void AudioConfigControl::openAudioFile(const std::string &p)
				{
					Nullable<int> tempVar = PrettyFormatting.getDelayAndCheck(p);
					delay->Value = tempVar::HasValue ? tempVar : 0;
				}

				AudioConfigControl::AudioConfigControl()
				{
					InitializeInstanceFields();
					InitializeComponent();
				}

				void AudioConfigControl::initHandler()
				{
					initAudioHandler();
				}

				const MeGUI::AudioEncodingMode &AudioConfigControl::getAudioEncodingMode() const
				{
					return static_cast<MeGUI::AudioEncodingMode>(cbAudioEncoding->SelectedIndex);
				}

				void AudioConfigControl::setAudioEncodingMode(const MeGUI::AudioEncodingMode &value)
				{
					cbAudioEncoding->SelectedIndex = static_cast<int>(value);
				}

				void AudioConfigControl::DisableDontEncode(bool bDisable)
				{
					if (bDisable)
					{
						cbAudioEncoding->SelectedItem = Always;
						cbAudioEncoding->Enabled = false;
					}
					else
						cbAudioEncoding->Enabled = true;
				}

				bool AudioConfigControl::IsDontEncodePossible()
				{
					return cbAudioEncoding->Enabled;
				}

				void AudioConfigControl::SelectProfileNameOrWarn(const std::string &fqname)
				{
					audioProfile->SetProfileNameOrWarn(fqname);
				}

				const int &AudioConfigControl::getDelay() const
				{
					return static_cast<int>(delay->Value);
				}

				void AudioConfigControl::setDelay(const int &value)
				{
					delay->Value = value;
				}

				void AudioConfigControl::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					UserControl::Dispose(disposing);
				}

				void AudioConfigControl::InitializeComponent()
				{
					this->label3 = new System::Windows::Forms::Label();
					this->delay = new System::Windows::Forms::NumericUpDown();
					this->label2 = new System::Windows::Forms::Label();
					this->label1 = new System::Windows::Forms::Label();
					this->cbAudioEncoding = new System::Windows::Forms::ComboBox();
					this->label4 = new System::Windows::Forms::Label();
					this->audioProfile = new MeGUI::core::gui::ConfigableProfilesControl();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->delay))->BeginInit();
					this->SuspendLayout();
					// 
					// label3
					// 
					this->label3->AutoSize = true;
					this->label3->Location = new System::Drawing::Point(249, 68);
					this->label3->Name = "label3";
					this->label3->Size = new System::Drawing::Size(20, 13);
					this->label3->TabIndex = 44;
					this->label3->Text = "ms";
					// 
					// delay
					// 
					this->delay->Location = new System::Drawing::Point(107, 64);
					this->delay->Maximum = decimal(new int[4] {2147483647, 0, 0, 0});
					this->delay->Minimum = decimal(new int[4] {-2147483648, 0, 0, -2147483648});
					this->delay->Name = "delay";
					this->delay->Size = new System::Drawing::Size(136, 20);
					this->delay->TabIndex = 43;
					// 
					// label2
					// 
					this->label2->AutoSize = true;
					this->label2->Location = new System::Drawing::Point(0, 68);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(34, 13);
					this->label2->TabIndex = 42;
					this->label2->Text = "Delay";
					// 
					// label1
					// 
					this->label1->AutoSize = true;
					this->label1->Location = new System::Drawing::Point(3, 8);
					this->label1->Name = "label1";
					this->label1->Size = new System::Drawing::Size(38, 13);
					this->label1->TabIndex = 39;
					this->label1->Text = "Codec";
					this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// cbAudioEncoding
					// 
					this->cbAudioEncoding->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbAudioEncoding->FormattingEnabled = true;
					this->cbAudioEncoding->Items->AddRange(new object[3] {"always", "if codec does not match", "never"});
					this->cbAudioEncoding->Location = new System::Drawing::Point(188, 31);
					this->cbAudioEncoding->Name = "cbAudioEncoding";
					this->cbAudioEncoding->Size = new System::Drawing::Size(178, 21);
					this->cbAudioEncoding->TabIndex = 46;
					this->cbAudioEncoding->SelectedIndexChanged += new System::EventHandler(this, &AudioConfigControl::dontEncodeAudio_CheckedChanged);
					// 
					// label4
					// 
					this->label4->AutoSize = true;
					this->label4->Location = new System::Drawing::Point(104, 34);
					this->label4->Name = "label4";
					this->label4->Size = new System::Drawing::Size(78, 13);
					this->label4->TabIndex = 47;
					this->label4->Text = "encode audio: ";
					// 
					// audioProfile
					// 
					this->audioProfile->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->audioProfile->Location = new System::Drawing::Point(107, 3);
					this->audioProfile->Name = "audioProfile";
					this->audioProfile->setProfileSet("Audio");
					this->audioProfile->Size = new System::Drawing::Size(295, 22);
					this->audioProfile->TabIndex = 45;
					this->audioProfile->SelectedProfileChanged += new System::EventHandler(this, &AudioConfigControl::ProfileChanged);
					// 
					// AudioConfigControl
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->Controls->Add(this->label4);
					this->Controls->Add(this->cbAudioEncoding);
					this->Controls->Add(this->audioProfile);
					this->Controls->Add(this->label3);
					this->Controls->Add(this->delay);
					this->Controls->Add(this->label2);
					this->Controls->Add(this->label1);
					this->Name = "AudioConfigControl";
					this->Size = new System::Drawing::Size(416, 90);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->delay))->EndInit();
					this->ResumeLayout(false);
					this->PerformLayout();

				}

				void AudioConfigControl::InitializeInstanceFields()
				{
					mainForm = MainForm::Instance;
					delete components;
				}
			}
		}
	}
}
