#include "MeXgui.packages.audio.vorbis.OggVorbisConfigurationPanel.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


namespace MeXgui
{
	namespace packages
	{
		namespace audio
		{
			namespace vorbis
			{

				OggVorbisConfigurationPanel::OggVorbisConfigurationPanel() : MeXgui::core::details::audio::AudioConfigurationPanel()
				{
					InitializeInstanceFields();
					InitializeComponent();
					vQuality_ValueChanged(0, 0);
				}

				const MeXgui::AudioCodecSettings &OggVorbisConfigurationPanel::getCodecSettings() const
				{
					OggVorbisSettings *nas = new OggVorbisSettings();
					nas->Quality = static_cast<Decimal>(vQuality->Value) * 10.0 / vQuality->Maximum;
					return nas;
				}

				void OggVorbisConfigurationPanel::setCodecSettings(const AudioCodecSettings &value)
				{
					OggVorbisSettings *nas = dynamic_cast<OggVorbisSettings*>(value);
					vQuality->Value = static_cast<int>(nas->Quality / 10.0 * static_cast<Decimal>(vQuality->Maximum));
				}

				void OggVorbisConfigurationPanel::vQuality_ValueChanged()
				{
					Decimal q = (static_cast<Decimal>(vQuality->Value)) * 10.0 / vQuality->Maximum;
					label1->Text = QString::Format("Variable Bitrate (Q={0}) ", q);
				}

				const MeXgui::OggVorbisSettings &OggVorbisConfigurationPanel::getSettings() const
				{
					return static_cast<OggVorbisSettings*>(Settings);
				}

				void OggVorbisConfigurationPanel::setSettings(const OggVorbisSettings &value)
				{
					setSettings(value);
				}

				void OggVorbisConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeXgui::core::details::audio::AudioConfigurationPanel::Dispose(disposing);
				}

				void OggVorbisConfigurationPanel::InitializeComponent()
				{
					this->vQuality = new System::Windows::Forms::TrackBar();
					this->label1 = new System::Windows::Forms::Label();
					this->encoderGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->vQuality))->BeginInit();
					this->SuspendLayout();
					// 
					// encoderGroupBox
					// 
					this->encoderGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->encoderGroupBox->Controls->Add(this->vQuality);
					this->encoderGroupBox->Controls->Add(this->label1);
					this->encoderGroupBox->Location = new System::Drawing::Point(0, 140);
					this->encoderGroupBox->Size = new System::Drawing::Size(394, 83);
					this->encoderGroupBox->TabIndex = 1;
					this->encoderGroupBox->Text = " Ogg Vorbis Options ";
					// 
					// besweetOptionsGroupbox
					// 
					this->besweetOptionsGroupbox->TabIndex = 0;
					// 
					// vQuality
					// 
					this->vQuality->Dock = System::Windows::Forms::DockStyle::Bottom;
					this->vQuality->Location = new System::Drawing::Point(3, 39);
					this->vQuality->Maximum = 1000;
					this->vQuality->Minimum = -200;
					this->vQuality->Name = "vQuality";
					this->vQuality->Size = new System::Drawing::Size(388, 45);
					this->vQuality->TabIndex = 1;
					this->vQuality->TickFrequency = 25;
					this->vQuality->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
					this->vQuality->ValueChanged += new System::EventHandler(this, &OggVorbisConfigurationPanel::vQuality_ValueChanged);
					// 
					// label1
					// 
					this->label1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->label1->AutoSize = true;
					this->label1->Location = new System::Drawing::Point(10, 15);
					this->label1->Name = "label1";
					this->label1->Size = new System::Drawing::Size(33, 12);
					this->label1->TabIndex = 0;
					this->label1->Text = "label1";
					// 
					// OggVorbisConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 12);
					this->Name = "OggVorbisConfigurationPanel";
					this->Size = new System::Drawing::Size(394, 250);
					this->encoderGroupBox->ResumeLayout(false);
					this->encoderGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->vQuality))->EndInit();
					this->ResumeLayout(false);

				}

				void OggVorbisConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
