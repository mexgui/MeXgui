#include "MeGUI.packages.audio.qaac.qaacConfigurationPanel.h"

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
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::details::audio;
namespace MeGUI
{
	namespace packages
	{
		namespace audio
		{
			namespace qaac
			{

				qaacConfigurationPanel::qaacConfigurationPanel() : MeGUI::core::details::audio::AudioConfigurationPanel()
				{
					InitializeInstanceFields();
					InitializeComponent();
					cbMode->Items->AddRange(EnumProxy::CreateArray(QaacSettings::SupportedModes));
					cbProfile->Items->AddRange(EnumProxy::CreateArray(QaacSettings::SupportedProfiles));
				}

				const MeGUI::AudioCodecSettings &qaacConfigurationPanel::getCodecSettings() const
				{
					QaacSettings *qas = new QaacSettings();
					switch (static_cast<QaacMode>((dynamic_cast<EnumProxy*>(cbMode->SelectedItem))->getRealValue()))
					{
						case ABR:
							qas->setBitrateMode(ABR);
							break;
						case CBR:
							qas->setBitrateMode(CBR);
							break;
						default:
							qas->setBitrateMode(VBR);
							break;
					}
					qas->setNoDelay(chNoDelay->Checked);
					qas->setMode(static_cast<QaacMode>((dynamic_cast<EnumProxy*>(cbMode->SelectedItem))->getRealValue()));
					qas->setProfile(static_cast<QaacProfile>((dynamic_cast<EnumProxy*>(cbProfile->SelectedItem))->getRealValue()));
					if (qas->getMode() == TVBR)
						qas->setQuality(static_cast<short>(trackBar->Value));
					else
						qas->setBitrate(static_cast<int>(trackBar->Value));
					return qas;
				}

				void qaacConfigurationPanel::setCodecSettings(const AudioCodecSettings &value)
				{
					QaacSettings *qas = dynamic_cast<QaacSettings*>(value);
					cbMode->SelectedItem = EnumProxy::Create(qas->getMode());
					cbProfile->SelectedItem = EnumProxy::Create(qas->getProfile());
					if (qas->getMode() == TVBR)
						trackBar->Value = __max(__min(qas->getQuality(), trackBar->Maximum), trackBar->Minimum);
					else
						trackBar->Value = __max(__min(qas->getBitrate(), trackBar->Maximum), trackBar->Minimum);
					chNoDelay->Checked = qas->getNoDelay();
				}

				const MeGUI::QaacSettings &qaacConfigurationPanel::getSettings() const
				{
					return static_cast<QaacSettings*>(Settings);
				}

				void qaacConfigurationPanel::setSettings(const QaacSettings &value)
				{
					setSettings(value);
				}

				void qaacConfigurationPanel::trackBar1_ValueChanged(object *sender, EventArgs *e)
				{
					switch (static_cast<QaacMode>((dynamic_cast<EnumProxy*>(cbMode->SelectedItem))->getRealValue()))
					{
						case TVBR:
							trackBar->Minimum = 0;
							trackBar->Maximum = 127;
							trackBar->TickFrequency = 1;
							encoderGroupBox->Text = std::string::Format("QAAC Options - (Q={0})", trackBar->Value);
							break;
						case CVBR:
							trackBar->Minimum = 0;
							trackBar->Maximum = 320;
							trackBar->TickFrequency = 20;
							encoderGroupBox->Text = std::string::Format("QAAC Options - Constrained Variable Bitrate @ {0} kbit/s", trackBar->Value);
							break;
						case ABR:
							trackBar->Minimum = 0;
							trackBar->Maximum = 320;
							trackBar->TickFrequency = 20;
							encoderGroupBox->Text = std::string::Format("QAAC Options - Average Bitrate @ {0} kbit/s", trackBar->Value);
							break;
						case CBR:
							trackBar->Minimum = 0;
							trackBar->Maximum = 320;
							trackBar->TickFrequency = 20;
							encoderGroupBox->Text = std::string::Format("QAAC Options - Constant Bitrate  @ {0} kbit/s", trackBar->Value);
							break;
					}
					if (cbProfile->SelectedIndex == 2)
						encoderGroupBox->Text = std::string::Format("QAAC Options");
				}

				void qaacConfigurationPanel::cbMode_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					trackBar1_ValueChanged(sender, e);
				}

				void qaacConfigurationPanel::cbProfile_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					switch (cbProfile->SelectedIndex)
					{
						case 2:
							trackBar->Enabled = false;
							cbMode->Enabled = false;
							break;
						default:
							trackBar->Enabled = true;
							cbMode->Enabled = true;
							break;
					}

					if (cbProfile->SelectedIndex == 1)
					{
						QaacMode qMode = static_cast<QaacMode>((dynamic_cast<EnumProxy*>(cbMode->SelectedItem))->getRealValue());
						cbMode->Items->Remove(EnumProxy::Create(TVBR));
						if (qMode == TVBR)
							cbMode->SelectedItem = EnumProxy::Create(CVBR);
					}
					else if (cbMode->Items->Count == 3)
						cbMode->Items->Insert(0, EnumProxy::Create(TVBR));

					cbMode_SelectedIndexChanged(sender, e);
				}

				void qaacConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeGUI::core::details::audio::AudioConfigurationPanel::Dispose(disposing);
				}

				void qaacConfigurationPanel::InitializeComponent()
				{
					this->label2 = new System::Windows::Forms::Label();
					this->cbMode = new System::Windows::Forms::ComboBox();
					this->trackBar = new System::Windows::Forms::TrackBar();
					this->label3 = new System::Windows::Forms::Label();
					this->cbProfile = new System::Windows::Forms::ComboBox();
					this->chNoDelay = new System::Windows::Forms::CheckBox();
					this->encoderGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->trackBar))->BeginInit();
					this->SuspendLayout();
					// 
					// encoderGroupBox
					// 
					this->encoderGroupBox->Controls->Add(this->chNoDelay);
					this->encoderGroupBox->Controls->Add(this->cbProfile);
					this->encoderGroupBox->Controls->Add(this->label3);
					this->encoderGroupBox->Controls->Add(this->trackBar);
					this->encoderGroupBox->Controls->Add(this->cbMode);
					this->encoderGroupBox->Controls->Add(this->label2);
					this->encoderGroupBox->Size = new System::Drawing::Size(390, 131);
					this->encoderGroupBox->Text = "QAAC Options";
					// 
					// label2
					// 
					this->label2->AutoSize = true;
					this->label2->Location = new System::Drawing::Point(37, 26);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(34, 13);
					this->label2->TabIndex = 0;
					this->label2->Text = "Mode";
					// 
					// cbMode
					// 
					this->cbMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbMode->FormattingEnabled = true;
					this->cbMode->Location = new System::Drawing::Point(88, 23);
					this->cbMode->Name = "cbMode";
					this->cbMode->Size = new System::Drawing::Size(121, 21);
					this->cbMode->TabIndex = 1;
					this->cbMode->SelectedIndexChanged += new System::EventHandler(this, &qaacConfigurationPanel::cbMode_SelectedIndexChanged);
					// 
					// trackBar
					// 
					this->trackBar->Location = new System::Drawing::Point(6, 50);
					this->trackBar->Maximum = 127;
					this->trackBar->Name = "trackBar";
					this->trackBar->Size = new System::Drawing::Size(387, 45);
					this->trackBar->TabIndex = 2;
					this->trackBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
					this->trackBar->Value = 90;
					this->trackBar->ValueChanged += new System::EventHandler(this, &qaacConfigurationPanel::trackBar1_ValueChanged);
					// 
					// label3
					// 
					this->label3->AutoSize = true;
					this->label3->Location = new System::Drawing::Point(37, 98);
					this->label3->Name = "label3";
					this->label3->Size = new System::Drawing::Size(36, 13);
					this->label3->TabIndex = 3;
					this->label3->Text = "Profile";
					// 
					// cbProfile
					// 
					this->cbProfile->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbProfile->FormattingEnabled = true;
					this->cbProfile->Location = new System::Drawing::Point(88, 95);
					this->cbProfile->Name = "cbProfile";
					this->cbProfile->Size = new System::Drawing::Size(121, 21);
					this->cbProfile->TabIndex = 4;
					this->cbProfile->SelectedIndexChanged += new System::EventHandler(this, &qaacConfigurationPanel::cbProfile_SelectedIndexChanged);
					// 
					// chNoDelay
					// 
					this->chNoDelay->AutoSize = true;
					this->chNoDelay->Location = new System::Drawing::Point(274, 97);
					this->chNoDelay->Name = "chNoDelay";
					this->chNoDelay->Size = new System::Drawing::Size(70, 17);
					this->chNoDelay->TabIndex = 5;
					this->chNoDelay->Text = "No Delay";
					this->chNoDelay->UseVisualStyleBackColor = true;
					// 
					// qaacConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->Name = "qaacConfigurationPanel";
					this->Size = new System::Drawing::Size(394, 300);
					this->encoderGroupBox->ResumeLayout(false);
					this->encoderGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->trackBar))->EndInit();
					this->ResumeLayout(false);

				}

				void qaacConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
