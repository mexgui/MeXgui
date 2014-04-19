#include "packages.audio.lame.lameConfigurationPanel.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


namespace MeXgui
{
	namespace packages
	{
		namespace audio
		{
			namespace lame
			{

				lameConfigurationPanel::lameConfigurationPanel() : MeXgui::core::details::audio::AudioConfigurationPanel()
				{
					InitializeInstanceFields();
					InitializeComponent();
					cbrBitrate->DataSource = MP3Settings::SupportedBitrates;
					cbrBitrate->BindingContext = new BindingContext();
					cbrBitrate->SelectedItem = 128;
				}

				const bool &lameConfigurationPanel::getIsMultichanelSupported() const
				{
					return false;
				}

				const MeXgui::AudioCodecSettings &lameConfigurationPanel::getCodecSettings() const
				{
					MP3Settings *ms = new MP3Settings();
					if (vbrMode->Checked)
						ms->setBitrateMode(VBR);
					else if (abrMode->Checked)
						ms->setBitrateMode(ABR);
					else
						ms->setBitrateMode(CBR);
					ms->setBitrate(static_cast<int>(cbrBitrate->SelectedItem));
					ms->setAbrBitrate(static_cast<int>(abrValue->Value));
					ms->setQuality(static_cast<int>(vbrValue->Value));
					return ms;
				}

				void lameConfigurationPanel::setCodecSettings(const AudioCodecSettings &value)
				{
					MP3Settings *ms = dynamic_cast<MP3Settings*>(value);
					if (ms->getBitrateMode() == ABR)
						abrMode->Checked = true;
					else if (ms->getBitrateMode() == VBR)
						vbrMode->Checked = true;
					else
						cbrMode->Checked = true;
					cbrBitrate->SelectedItem = ms->getBitrate();
					if (ms->getAbrBitrate() < 8 || ms->getAbrBitrate() > 320)
						abrValue->Value = 128;
					else
						abrValue->Value = ms->getAbrBitrate();
					vbrValue->Value = ms->getQuality();
				}

				void lameConfigurationPanel::textField_KeyPress(object *sender, KeyPressEventArgs *e)
				{
					if (!isdigit(e->KeyChar) && static_cast<int>(Keys::Back) != static_cast<int>(e->KeyChar))
						e->Handled = true;
				}

				const MeXgui::MP3Settings &lameConfigurationPanel::getSettings() const
				{
					return static_cast<MP3Settings*>(Settings);
				}

				void lameConfigurationPanel::setSettings(const MP3Settings &value)
				{
					setSettings(value);
				}

				void lameConfigurationPanel::cbrMode_CheckedChanged()
				{
					cbrBitrate->Enabled = true;
					vbrValue->Enabled = abrValue->Enabled = false;
				}

				void lameConfigurationPanel::abrMode_CheckedChanged()
				{
					abrValue->Enabled = true;
					vbrValue->Enabled = cbrBitrate->Enabled = false;
				}

				void lameConfigurationPanel::vbrMode_CheckedChanged()
				{
					vbrValue->Enabled = true;
					abrValue->Enabled = cbrBitrate->Enabled = false;
				}

				void lameConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeXgui::core::details::audio::AudioConfigurationPanel::Dispose(disposing);
				}

				void lameConfigurationPanel::InitializeComponent()
				{
					this->cbrMode = new System::Windows::Forms::RadioButton();
					this->abrMode = new System::Windows::Forms::RadioButton();
					this->vbrMode = new System::Windows::Forms::RadioButton();
					this->vbrValue = new System::Windows::Forms::NumericUpDown();
					this->abrValue = new System::Windows::Forms::NumericUpDown();
					this->cbrBitrate = new System::Windows::Forms::ComboBox();
					this->encoderGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->vbrValue))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->abrValue))->BeginInit();
					this->SuspendLayout();
					// 
					// encoderGroupBox
					// 
					this->encoderGroupBox->Controls->Add(this->cbrBitrate);
					this->encoderGroupBox->Controls->Add(this->abrValue);
					this->encoderGroupBox->Controls->Add(this->vbrValue);
					this->encoderGroupBox->Controls->Add(this->vbrMode);
					this->encoderGroupBox->Controls->Add(this->abrMode);
					this->encoderGroupBox->Controls->Add(this->cbrMode);
					this->encoderGroupBox->Location = new System::Drawing::Point(0, 140);
					this->encoderGroupBox->Size = new System::Drawing::Size(394, 103);
					this->encoderGroupBox->Text = "  Lame MP3 Encoding Mode  ";
					// 
					// cbrMode
					// 
					this->cbrMode->AutoSize = true;
					this->cbrMode->Location = new System::Drawing::Point(6, 18);
					this->cbrMode->Name = "cbrMode";
					this->cbrMode->Size = new System::Drawing::Size(47, 16);
					this->cbrMode->TabIndex = 0;
					this->cbrMode->TabStop = true;
					this->cbrMode->Text = "CBR";
					this->cbrMode->UseVisualStyleBackColor = true;
					this->cbrMode->CheckedChanged += new System::EventHandler(this, &lameConfigurationPanel::cbrMode_CheckedChanged);
					// 
					// abrMode
					// 
					this->abrMode->AutoSize = true;
					this->abrMode->Location = new System::Drawing::Point(6, 42);
					this->abrMode->Name = "abrMode";
					this->abrMode->Size = new System::Drawing::Size(47, 16);
					this->abrMode->TabIndex = 1;
					this->abrMode->TabStop = true;
					this->abrMode->Text = "ABR";
					this->abrMode->UseVisualStyleBackColor = true;
					this->abrMode->CheckedChanged += new System::EventHandler(this, &lameConfigurationPanel::abrMode_CheckedChanged);
					// 
					// vbrMode
					// 
					this->vbrMode->AutoSize = true;
					this->vbrMode->Location = new System::Drawing::Point(6, 66);
					this->vbrMode->Name = "vbrMode";
					this->vbrMode->Size = new System::Drawing::Size(47, 16);
					this->vbrMode->TabIndex = 2;
					this->vbrMode->TabStop = true;
					this->vbrMode->Text = "VBR";
					this->vbrMode->UseVisualStyleBackColor = true;
					this->vbrMode->CheckedChanged += new System::EventHandler(this, &lameConfigurationPanel::vbrMode_CheckedChanged);
					// 
					// vbrValue
					// 
					this->vbrValue->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->vbrValue->Location = new System::Drawing::Point(112, 66);
					this->vbrValue->Maximum = decimal(new int[4] {9, 0, 0, 0});
					this->vbrValue->Name = "vbrValue";
					this->vbrValue->Size = new System::Drawing::Size(276, 22);
					this->vbrValue->TabIndex = 8;
					this->vbrValue->Value = decimal(new int[4] {4, 0, 0, 0});
					// 
					// abrValue
					// 
					this->abrValue->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->abrValue->Increment = decimal(new int[4] {16, 0, 0, 0});
					this->abrValue->Location = new System::Drawing::Point(112, 42);
					this->abrValue->Maximum = decimal(new int[4] {320, 0, 0, 0});
					this->abrValue->Minimum = decimal(new int[4] {8, 0, 0, 0});
					this->abrValue->Name = "abrValue";
					this->abrValue->Size = new System::Drawing::Size(276, 22);
					this->abrValue->TabIndex = 9;
					this->abrValue->Value = decimal(new int[4] {128, 0, 0, 0});
					// 
					// cbrBitrate
					// 
					this->cbrBitrate->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->cbrBitrate->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbrBitrate->Location = new System::Drawing::Point(112, 17);
					this->cbrBitrate->Name = "cbrBitrate";
					this->cbrBitrate->Size = new System::Drawing::Size(276, 20);
					this->cbrBitrate->TabIndex = 10;
					// 
					// lameConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 12);
					this->Name = "lameConfigurationPanel";
					this->Size = new System::Drawing::Size(394, 265);
					this->encoderGroupBox->ResumeLayout(false);
					this->encoderGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->vbrValue))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->abrValue))->EndInit();
					this->ResumeLayout(false);

				}

				void lameConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
