#include "MeGUI.packages.audio.aften.AftenConfigurationPanel.h"

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
			namespace aften
			{

				AftenConfigurationPanel::AftenConfigurationPanel() : MeGUI::core::details::audio::AudioConfigurationPanel()
				{
					 InitializeInstanceFields();
					 InitializeComponent();
					 comboBox1->Items->AddRange(AftenSettings::SupportedBitrates);
				}

				const MeGUI::AudioCodecSettings &AftenConfigurationPanel::getCodecSettings() const
				{
					AftenSettings *nas = new AftenSettings();
					nas->setBitrate(static_cast<int>(comboBox1->SelectedItem));
					return nas;
				}

				void AftenConfigurationPanel::setCodecSettings(const AudioCodecSettings &value)
				{
					AftenSettings *nas = dynamic_cast<AftenSettings*>(value);
					comboBox1->SelectedItem = nas->getBitrate();
				}

				const MeGUI::AftenSettings &AftenConfigurationPanel::getSettings() const
				{
					return static_cast<AftenSettings*>(Settings);
				}

				void AftenConfigurationPanel::setSettings(const AftenSettings &value)
				{
					setSettings(value);
				}

				void AftenConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeGUI::core::details::audio::AudioConfigurationPanel::Dispose(disposing);
				}

				void AftenConfigurationPanel::InitializeComponent()
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
					this->encoderGroupBox->Size = new System::Drawing::Size(393, 55);
					this->encoderGroupBox->Text = " Aften Options ";
					// 
					// label2
					// 
					this->label2->AutoSize = true;
					this->label2->Location = new System::Drawing::Point(6, 20);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(69, 12);
					this->label2->TabIndex = 8;
					this->label2->Text = "Bitrate (kbps)";
					// 
					// comboBox1
					// 
					this->comboBox1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->comboBox1->FormattingEnabled = true;
					this->comboBox1->Location = new System::Drawing::Point(103, 18);
					this->comboBox1->Name = "comboBox1";
					this->comboBox1->Size = new System::Drawing::Size(285, 20);
					this->comboBox1->TabIndex = 6;
					// 
					// AftenConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 12);
					this->Name = "AftenConfigurationPanel";
					this->Size = new System::Drawing::Size(394, 221);
					this->encoderGroupBox->ResumeLayout(false);
					this->encoderGroupBox->PerformLayout();
					this->ResumeLayout(false);

				}

				void AftenConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
