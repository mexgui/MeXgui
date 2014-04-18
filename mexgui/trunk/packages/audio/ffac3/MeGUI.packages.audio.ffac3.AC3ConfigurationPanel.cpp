#include "MeGUI.packages.audio.ffac3.AC3ConfigurationPanel.h"

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
namespace MeGUI
{
	namespace packages
	{
		namespace audio
		{
			namespace ffac3
			{

				AC3ConfigurationPanel::AC3ConfigurationPanel() : MeGUI::core::details::audio::AudioConfigurationPanel()
				{
					InitializeInstanceFields();
					InitializeComponent();
					comboBox1->Items->AddRange(AC3Settings::SupportedBitrates);
				}

				const MeGUI::AudioCodecSettings &AC3ConfigurationPanel::getCodecSettings() const
				{
					AC3Settings *nas = new AC3Settings();
					nas->setBitrate(static_cast<int>(comboBox1->SelectedItem));
					return nas;
				}

				void AC3ConfigurationPanel::setCodecSettings(const AudioCodecSettings &value)
				{
					AC3Settings *nas = dynamic_cast<AC3Settings*>(value);
					comboBox1->SelectedItem = nas->getBitrate();
				}

				const MeGUI::AC3Settings &AC3ConfigurationPanel::getSettings() const
				{
					return static_cast<AC3Settings*>(Settings);
				}

				void AC3ConfigurationPanel::setSettings(const AC3Settings &value)
				{
					setSettings(value);
				}

				void AC3ConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeGUI::core::details::audio::AudioConfigurationPanel::Dispose(disposing);
				}

				void AC3ConfigurationPanel::InitializeComponent()
				{
					this->label2 = new System::Windows::Forms::Label();
					this->comboBox1 = new System::Windows::Forms::ComboBox();
					this->encoderGroupBox->SuspendLayout();
					this->SuspendLayout();
					// 
					// encoderGroupBox
					// 
					this->encoderGroupBox->Controls->Add(this->label2);
					this->encoderGroupBox->Controls->Add(this->comboBox1);
					this->encoderGroupBox->Location = new System::Drawing::Point(0, 140);
					this->encoderGroupBox->Size = new System::Drawing::Size(394, 54);
					this->encoderGroupBox->Text = " AC3 Options ";
					// 
					// label2
					// 
					this->label2->AutoSize = true;
					this->label2->Location = new System::Drawing::Point(6, 18);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(69, 12);
					this->label2->TabIndex = 5;
					this->label2->Text = "Bitrate (kbps)";
					// 
					// comboBox1
					// 
					this->comboBox1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->comboBox1->FormattingEnabled = true;
					this->comboBox1->Location = new System::Drawing::Point(106, 16);
					this->comboBox1->Name = "comboBox1";
					this->comboBox1->Size = new System::Drawing::Size(282, 20);
					this->comboBox1->TabIndex = 3;
					// 
					// AC3ConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 12);
					this->Name = "AC3ConfigurationPanel";
					this->Size = new System::Drawing::Size(394, 221);
					this->encoderGroupBox->ResumeLayout(false);
					this->encoderGroupBox->PerformLayout();
					this->ResumeLayout(false);

				}

				void AC3ConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
