#include "MeGUI.packages.audio.flac.FlacConfigurationPanel.h"

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
			namespace flac
			{

				FlacConfigurationPanel::FlacConfigurationPanel() : MeGUI::core::details::audio::AudioConfigurationPanel()
				{
					 InitializeInstanceFields();
					 InitializeComponent();
				}

				const MeGUI::AudioCodecSettings &FlacConfigurationPanel::getCodecSettings() const
				{
					FlacSettings *nas = new FlacSettings();
					nas->setCompressionLevel(tbQuality->Value);
					return nas;
				}

				void FlacConfigurationPanel::setCodecSettings(const AudioCodecSettings &value)
				{
					FlacSettings *nas = dynamic_cast<FlacSettings*>(value);
					tbQuality->Value = nas->getCompressionLevel();
				}

				const MeGUI::FlacSettings &FlacConfigurationPanel::getSettings() const
				{
					return static_cast<FlacSettings*>(Settings);
				}

				void FlacConfigurationPanel::setSettings(const FlacSettings &value)
				{
					setSettings(value);
				}

				void FlacConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeGUI::core::details::audio::AudioConfigurationPanel::Dispose(disposing);
				}

				void FlacConfigurationPanel::InitializeComponent()
				{
					this->tbQuality = new System::Windows::Forms::TrackBar();
					this->label4 = new System::Windows::Forms::Label();
					this->label5 = new System::Windows::Forms::Label();
					this->encoderGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->tbQuality))->BeginInit();
					this->SuspendLayout();
					// 
					// encoderGroupBox
					// 
					this->encoderGroupBox->Controls->Add(this->label5);
					this->encoderGroupBox->Controls->Add(this->label4);
					this->encoderGroupBox->Controls->Add(this->tbQuality);
					this->encoderGroupBox->Location = new System::Drawing::Point(0, 140);
					this->encoderGroupBox->Size = new System::Drawing::Size(393, 78);
					this->encoderGroupBox->Text = " Flac Options ";
					// 
					// tbQuality
					// 
					this->tbQuality->Location = new System::Drawing::Point(6, 18);
					this->tbQuality->Maximum = 8;
					this->tbQuality->Name = "tbQuality";
					this->tbQuality->Size = new System::Drawing::Size(378, 45);
					this->tbQuality->TabIndex = 10;
					this->tbQuality->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
					this->tbQuality->Value = 5;
					// 
					// label4
					// 
					this->label4->AutoSize = true;
					this->label4->Location = new System::Drawing::Point(6, 47);
					this->label4->Name = "label4";
					this->label4->Size = new System::Drawing::Size(116, 12);
					this->label4->TabIndex = 11;
					this->label4->Text = "Biggest file, fast encode";
					// 
					// label5
					// 
					this->label5->AutoSize = true;
					this->label5->Location = new System::Drawing::Point(260, 47);
					this->label5->Name = "label5";
					this->label5->Size = new System::Drawing::Size(124, 12);
					this->label5->TabIndex = 12;
					this->label5->Text = "Smallest file, slow encode";
					// 
					// FlacConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 12);
					this->Name = "FlacConfigurationPanel";
					this->Size = new System::Drawing::Size(394, 240);
					this->encoderGroupBox->ResumeLayout(false);
					this->encoderGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->tbQuality))->EndInit();
					this->ResumeLayout(false);

				}

				void FlacConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
