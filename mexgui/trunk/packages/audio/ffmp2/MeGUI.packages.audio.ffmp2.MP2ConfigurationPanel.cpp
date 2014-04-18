#include "MeGUI.packages.audio.ffmp2.MP2ConfigurationPanel.h"

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
			namespace ffmp2
			{

				MP2ConfigurationPanel::MP2ConfigurationPanel() : MeGUI::core::details::audio::AudioConfigurationPanel()
				{
					InitializeInstanceFields();
					InitializeComponent();
					comboBox1->Items->AddRange(MP2Settings::SupportedBitrates);
				}

				const bool &MP2ConfigurationPanel::getIsMultichanelSupported() const
				{
					return false;
				}

				const MeGUI::AudioCodecSettings &MP2ConfigurationPanel::getCodecSettings() const
				{
					MP2Settings *nas = new MP2Settings();
					nas->setBitrate(static_cast<int>(comboBox1->SelectedItem));
					return nas;
				}

				void MP2ConfigurationPanel::setCodecSettings(const AudioCodecSettings &value)
				{
					MP2Settings *nas = dynamic_cast<MP2Settings*>(value);
					comboBox1->SelectedItem = nas->getBitrate();
				}

				const MeGUI::MP2Settings &MP2ConfigurationPanel::getSettings() const
				{
					return static_cast<MP2Settings*>(Settings);
				}

				void MP2ConfigurationPanel::setSettings(const MP2Settings &value)
				{
					setSettings(value);
				}

				void MP2ConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeGUI::core::details::audio::AudioConfigurationPanel::Dispose(disposing);
				}

				void MP2ConfigurationPanel::InitializeComponent()
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
					this->encoderGroupBox->Size = new System::Drawing::Size(394, 52);
					this->encoderGroupBox->Text = " MP2 Encoder Options ";
					// 
					// label2
					// 
					this->label2->AutoSize = true;
					this->label2->Location = new System::Drawing::Point(6, 17);
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
					this->comboBox1->Location = new System::Drawing::Point(106, 14);
					this->comboBox1->Name = "comboBox1";
					this->comboBox1->Size = new System::Drawing::Size(285, 20);
					this->comboBox1->TabIndex = 3;
					// 
					// MP2ConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 12);
					this->Name = "MP2ConfigurationPanel";
					this->Size = new System::Drawing::Size(394, 212);
					this->encoderGroupBox->ResumeLayout(false);
					this->encoderGroupBox->PerformLayout();
					this->ResumeLayout(false);

				}

				void MP2ConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
