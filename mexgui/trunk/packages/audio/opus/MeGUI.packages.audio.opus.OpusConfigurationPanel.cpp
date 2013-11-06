#include "MeGUI.packages.audio.opus.OpusConfigurationPanel.h"

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
			namespace opus
			{

				OpusConfigurationPanel::OpusConfigurationPanel() : MeGUI::core::details::audio::AudioConfigurationPanel()
				{
					InitializeInstanceFields();
					InitializeComponent();
					cbMode->Items->AddRange(EnumProxy::CreateArray(OpusSettings::SupportedModes));
					trackBar_ValueChanged(0, 0);
				}

				void OpusConfigurationPanel::InitializeComponent()
				{
					this->trackBar = new System::Windows::Forms::TrackBar();
					this->cbMode = new System::Windows::Forms::ComboBox();
					this->label2 = new System::Windows::Forms::Label();
					this->encoderGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->trackBar))->BeginInit();
					this->SuspendLayout();
					// 
					// encoderGroupBox
					// 
					this->encoderGroupBox->Controls->Add(this->label2);
					this->encoderGroupBox->Controls->Add(this->trackBar);
					this->encoderGroupBox->Controls->Add(this->cbMode);
					this->encoderGroupBox->Size = new System::Drawing::Size(390, 134);
					this->encoderGroupBox->Text = "Opus Options";
					// 
					// trackBar
					// 
					this->trackBar->Location = new System::Drawing::Point(8, 58);
					this->trackBar->Maximum = 512;
					this->trackBar->Minimum = 6;
					this->trackBar->Name = "trackBar";
					this->trackBar->Size = new System::Drawing::Size(387, 45);
					this->trackBar->TabIndex = 4;
					this->trackBar->TickFrequency = 8;
					this->trackBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
					this->trackBar->Value = 64;
					this->trackBar->ValueChanged += new System::EventHandler(this, &OpusConfigurationPanel::trackBar_ValueChanged);
					// 
					// cbMode
					// 
					this->cbMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbMode->FormattingEnabled = true;
					this->cbMode->Location = new System::Drawing::Point(84, 31);
					this->cbMode->Name = "cbMode";
					this->cbMode->Size = new System::Drawing::Size(121, 21);
					this->cbMode->TabIndex = 3;
					// 
					// label2
					// 
					this->label2->AutoSize = true;
					this->label2->Location = new System::Drawing::Point(39, 34);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(34, 13);
					this->label2->TabIndex = 5;
					this->label2->Text = "Mode";
					// 
					// OpusConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->Name = "OpusConfigurationPanel";
					this->Size = new System::Drawing::Size(394, 300);
					this->encoderGroupBox->ResumeLayout(false);
					this->encoderGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->trackBar))->EndInit();
					this->ResumeLayout(false);

				}

				const MeGUI::AudioCodecSettings &OpusConfigurationPanel::getCodecSettings() const
				{
					OpusSettings *oas = new OpusSettings();
					if (cbMode->SelectedIndex == 0)
						oas->setBitrateMode(VBR);
					if (cbMode->SelectedIndex == 1)
						oas->setBitrateMode(VBR);
					if (cbMode->SelectedIndex == 2)
						oas->setBitrateMode(CBR);
					oas->setMode(static_cast<OpusMode>((dynamic_cast<EnumProxy*>(cbMode->SelectedItem))->getRealValue()));
					oas->setBitrate(static_cast<int>(trackBar->Value));
					return oas;
				}

				void OpusConfigurationPanel::setCodecSettings(const AudioCodecSettings &value)
				{
					OpusSettings *oas = dynamic_cast<OpusSettings*>(value);
					if (cbMode->SelectedIndex == 0)
						oas->setBitrateMode(VBR);
					if (cbMode->SelectedIndex == 1)
						oas->setBitrateMode(VBR);
					if (cbMode->SelectedIndex == 2)
						oas->setBitrateMode(CBR);
					cbMode->SelectedItem = EnumProxy::Create(oas->getMode());
					trackBar->Value = __max(__min(oas->getBitrate(), trackBar->Maximum), trackBar->Minimum);
				}

				const MeGUI::OpusSettings &OpusConfigurationPanel::getSettings() const
				{
					return static_cast<OpusSettings*>(Settings);
				}

				void OpusConfigurationPanel::setSettings(const OpusSettings &value)
				{
					setSettings(value);
				}

				void OpusConfigurationPanel::trackBar_ValueChanged(object *sender, EventArgs *e)
				{
					switch (cbMode->SelectedIndex)
					{
						case 0: // VBR
							encoderGroupBox->Text = std::string::Format("OPUS Options - Variable Bitrate @ {0} kbit/s", trackBar->Value);
							break;
						case 1: // CVBR
							encoderGroupBox->Text = std::string::Format("OPUS Options - Constrained Variable Bitrate @ {0} kbit/s", trackBar->Value);
							break;
						case 2: // CBR
							encoderGroupBox->Text = std::string::Format("OPUS Options - Hard Constant Bitrate  @ {0} kbit/s", trackBar->Value);
							break;
					}
				}

				void OpusConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeGUI::core::details::audio::AudioConfigurationPanel::Dispose(disposing);
				}

				void OpusConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
