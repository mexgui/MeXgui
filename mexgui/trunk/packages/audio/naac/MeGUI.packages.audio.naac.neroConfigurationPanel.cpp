#include "MeGUI.packages.audio.naac.neroConfigurationPanel.h"

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
namespace MeGUI
{
	namespace packages
	{
		namespace audio
		{
			namespace naac
			{

				neroConfigurationPanel::neroConfigurationPanel() : MeGUI::core::details::audio::AudioConfigurationPanel()
				{
					//
					// Required for Windows Form Designer support
					//
					InitializeInstanceFields();
					InitializeComponent();
					comboBox1->Items->AddRange(EnumProxy::CreateArray(NeroAACSettings::SupportedProfiles));
					rbtnABR_CheckedChanged(0, 0);
					vBitrate_ValueChanged(0, 0);
				}

				void neroConfigurationPanel::InitializeComponent()
				{
					this->vQuality = new System::Windows::Forms::TrackBar();
					this->rbtnVBR = new System::Windows::Forms::RadioButton();
					this->vBitrate = new System::Windows::Forms::TrackBar();
					this->rbtnCBR = new System::Windows::Forms::RadioButton();
					this->rbtnABR = new System::Windows::Forms::RadioButton();
					this->comboBox1 = new System::Windows::Forms::ComboBox();
					this->label1 = new System::Windows::Forms::Label();
					this->encoderGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->vQuality))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->vBitrate))->BeginInit();
					this->SuspendLayout();
					// 
					// encoderGroupBox
					// 
					this->encoderGroupBox->Controls->Add(this->label1);
					this->encoderGroupBox->Controls->Add(this->comboBox1);
					this->encoderGroupBox->Controls->Add(this->vQuality);
					this->encoderGroupBox->Controls->Add(this->rbtnVBR);
					this->encoderGroupBox->Controls->Add(this->vBitrate);
					this->encoderGroupBox->Controls->Add(this->rbtnCBR);
					this->encoderGroupBox->Controls->Add(this->rbtnABR);
					this->encoderGroupBox->Location = new System::Drawing::Point(0, 140);
					this->encoderGroupBox->Size = new System::Drawing::Size(394, 210);
					this->encoderGroupBox->TabIndex = 1;
					this->encoderGroupBox->Text = " NeroDigital AAC Options ";
					// 
					// besweetOptionsGroupbox
					// 
					this->besweetOptionsGroupbox->TabIndex = 0;
					// 
					// vQuality
					// 
					this->vQuality->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->vQuality->Location = new System::Drawing::Point(3, 123);
					this->vQuality->Maximum = 100;
					this->vQuality->Name = "vQuality";
					this->vQuality->Size = new System::Drawing::Size(388, 45);
					this->vQuality->TabIndex = 4;
					this->vQuality->TickFrequency = 5;
					this->vQuality->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
					this->vQuality->ValueChanged += new System::EventHandler(this, &neroConfigurationPanel::vBitrate_ValueChanged);
					// 
					// rbtnVBR
					// 
					this->rbtnVBR->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->rbtnVBR->Location = new System::Drawing::Point(13, 106);
					this->rbtnVBR->Name = "rbtnVBR";
					this->rbtnVBR->Size = new System::Drawing::Size(267, 22);
					this->rbtnVBR->TabIndex = 3;
					this->rbtnVBR->Text = "Variable Bitrate";
					this->rbtnVBR->CheckedChanged += new System::EventHandler(this, &neroConfigurationPanel::rbtnABR_CheckedChanged);
					// 
					// vBitrate
					// 
					this->vBitrate->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->vBitrate->Location = new System::Drawing::Point(3, 59);
					this->vBitrate->Maximum = 640;
					this->vBitrate->Minimum = 16;
					this->vBitrate->Name = "vBitrate";
					this->vBitrate->Size = new System::Drawing::Size(388, 45);
					this->vBitrate->TabIndex = 2;
					this->vBitrate->TickFrequency = 8;
					this->vBitrate->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
					this->vBitrate->Value = 16;
					this->vBitrate->ValueChanged += new System::EventHandler(this, &neroConfigurationPanel::vBitrate_ValueChanged);
					// 
					// rbtnCBR
					// 
					this->rbtnCBR->Location = new System::Drawing::Point(13, 39);
					this->rbtnCBR->Name = "rbtnCBR";
					this->rbtnCBR->Size = new System::Drawing::Size(320, 22);
					this->rbtnCBR->TabIndex = 1;
					this->rbtnCBR->Text = "Constant Bitrate";
					this->rbtnCBR->CheckedChanged += new System::EventHandler(this, &neroConfigurationPanel::rbtnABR_CheckedChanged);
					// 
					// rbtnABR
					// 
					this->rbtnABR->Location = new System::Drawing::Point(13, 22);
					this->rbtnABR->Name = "rbtnABR";
					this->rbtnABR->Size = new System::Drawing::Size(302, 16);
					this->rbtnABR->TabIndex = 0;
					this->rbtnABR->Text = "Adaptive Bitrate";
					this->rbtnABR->CheckedChanged += new System::EventHandler(this, &neroConfigurationPanel::rbtnABR_CheckedChanged);
					// 
					// comboBox1
					// 
					this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->comboBox1->FormattingEnabled = true;
					this->comboBox1->Location = new System::Drawing::Point(106, 165);
					this->comboBox1->Name = "comboBox1";
					this->comboBox1->Size = new System::Drawing::Size(266, 20);
					this->comboBox1->TabIndex = 6;
					// 
					// label1
					// 
					this->label1->AutoSize = true;
					this->label1->Location = new System::Drawing::Point(6, 168);
					this->label1->Name = "label1";
					this->label1->Size = new System::Drawing::Size(63, 12);
					this->label1->TabIndex = 5;
					this->label1->Text = "AAC Profile";
					// 
					// neroConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 12);
					this->Name = "neroConfigurationPanel";
					this->Size = new System::Drawing::Size(394, 379);
					this->encoderGroupBox->ResumeLayout(false);
					this->encoderGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->vQuality))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->vBitrate))->EndInit();
					this->ResumeLayout(false);

				}

				const MeGUI::AudioCodecSettings &neroConfigurationPanel::getCodecSettings() const
				{
					NeroAACSettings *nas = new NeroAACSettings();
					if (rbtnABR->Checked)
						nas->setBitrateMode(ABR);
					if (rbtnCBR->Checked)
						nas->setBitrateMode(CBR);
					if (rbtnVBR->Checked)
						nas->setBitrateMode(VBR);
					nas->setBitrate(vBitrate->Value);
					nas->setQuality(static_cast<Decimal>(vQuality->Value) / vQuality->Maximum);
					nas->setProfile(static_cast<AacProfile>((dynamic_cast<EnumProxy*>(comboBox1->SelectedItem))->getRealValue()));
					return nas;
				}

				void neroConfigurationPanel::setCodecSettings(const AudioCodecSettings &value)
				{
					NeroAACSettings *nas = static_cast<NeroAACSettings*>(value);
					vBitrate->Value = __max(__min(nas->getBitrate(), vBitrate->Maximum), vBitrate->Minimum);
					vQuality->Value = static_cast<int>(nas->getQuality() * static_cast<Decimal>(vQuality->Maximum));
					rbtnABR->Checked = nas->getBitrateMode() == ABR;
					rbtnCBR->Checked = nas->getBitrateMode() == CBR;
					rbtnVBR->Checked = nas->getBitrateMode() == VBR;
					comboBox1->SelectedItem = EnumProxy::Create(nas->getProfile());
				}

				void neroConfigurationPanel::rbtnABR_CheckedChanged(object *sender, EventArgs *e)
				{
					vBitrate->Enabled = !(vQuality->Enabled = rbtnVBR->Checked);
					vBitrate_ValueChanged(sender, e);
				}

				void neroConfigurationPanel::vBitrate_ValueChanged(object *sender, EventArgs *e)
				{
					if (rbtnVBR->Checked)
					{
						rbtnABR->Text = "Adaptive Bitrate";
						rbtnCBR->Text = "Constant Bitrate";
						Decimal q = (static_cast<Decimal>(vQuality->Value)) / vQuality->Maximum;
						rbtnVBR->Text = std::string::Format("Variable Bitrate (Q={0}) ", q);
					}
					else if (rbtnABR->Checked)
					{
						rbtnABR->Text = std::string::Format("Adaptive Bitrate @ {0} kbit/s", vBitrate->Value);
						rbtnCBR->Text = "Constant Bitrate";
						rbtnVBR->Text = "Variable Bitrate";
					}
					else
					{
						rbtnABR->Text = "Adaptive Bitrate";
						rbtnCBR->Text = std::string::Format("Constant Bitrate @ {0} kbit/s", vBitrate->Value);
						rbtnVBR->Text = "Variable Bitrate";
					}
				}

				const MeGUI::NeroAACSettings &neroConfigurationPanel::getSettings() const
				{
					return static_cast<NeroAACSettings*>(Settings);
				}

				void neroConfigurationPanel::setSettings(const NeroAACSettings &value)
				{
					setSettings(value);
				}

				void neroConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeGUI::core::details::audio::AudioConfigurationPanel::Dispose(disposing);
				}

				void neroConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
