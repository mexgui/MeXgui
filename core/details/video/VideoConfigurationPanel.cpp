#include "VideoConfigurationPanel.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


using namespace MeXgui::core::plugins::interfaces;
namespace MeXgui
{
	namespace core
	{
		namespace details
		{
			namespace video
			{

				VideoConfigurationPanel::VideoConfigurationPanel()
				{
					InitializeInstanceFields();
				}

				VideoConfigurationPanel::VideoConfigurationPanel(MainForm *mainForm, VideoInfo *info)
				{
					InitializeInstanceFields();
					loaded = false;
					InitializeComponent();

					input = info->getVideoInput();
					output = info->getVideoOutput();
				}

				void VideoConfigurationPanel::VideoConfigurationPanel_Load()
				{
					loaded = true;
					doCodecSpecificLoadAdjustments();
					genericUpdate();
				}

				QString VideoConfigurationPanel::getCommandline()
				{
					return "";
				}

				void VideoConfigurationPanel::doCodecSpecificAdjustments()
				{
				}

				void VideoConfigurationPanel::doCodecSpecificLoadAdjustments()
				{
				}

				bool VideoConfigurationPanel::isValidSettings(VideoCodecSettings *settings)
				{
					throw std::exception("A bug in the program -- ProfilableConfigurationDialog.isValidSettings(GenericSettings) is not overridden");
				}

				MeXgui::VideoCodecSettings *VideoConfigurationPanel::defaultSettings()
				{
					throw std::exception("A bug in the program -- ProfilableConfigurationDialog.defaultSettings() is not overridden");
				}

				void VideoConfigurationPanel::showCommandLine()
				{
					if (!loaded)
						return;
					if (updating)
						return;
					updating = true;

					doCodecSpecificAdjustments();

					this->commandline->Text = encoderPath + " " + getCommandline();
					updating = false;
				}

				void VideoConfigurationPanel::genericUpdate()
				{
					showCommandLine();
				}

				const bool &VideoConfigurationPanel::getAdvancedToolTips() const
				{
					return advancedToolTips;
				}

				void VideoConfigurationPanel::setAdvancedToolTips(const bool &value)
				{
					advancedToolTips = value;
				}

				const double &VideoConfigurationPanel::getBytesPerFrame() const
				{
					return bytesPerFrame;
				}

				void VideoConfigurationPanel::setBytesPerFrame(const double &value)
				{
					bytesPerFrame = value;
				}

				void VideoConfigurationPanel::InitializeComponent()
				{
					this->components = new System::ComponentModel::Container();
					this->tabControl1 = new System::Windows::Forms::TabControl();
					this->mainTabPage = new System::Windows::Forms::TabPage();
					this->commandline = new System::Windows::Forms::TextBox();
					this->tooltipHelp = new System::Windows::Forms::ToolTip(this->components);
					this->tabControl1->SuspendLayout();
					this->SuspendLayout();
					// 
					// tabControl1
					// 
					this->tabControl1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->tabControl1->Controls->Add(this->mainTabPage);
					this->tabControl1->Location = new System::Drawing::Point(0, 0);
					this->tabControl1->Name = "tabControl1";
					this->tabControl1->SelectedIndex = 0;
					this->tabControl1->Size = new System::Drawing::Size(368, 344);
					this->tabControl1->TabIndex = 39;
					// 
					// mainTabPage
					// 
					this->mainTabPage->Location = new System::Drawing::Point(4, 22);
					this->mainTabPage->Name = "mainTabPage";
					this->mainTabPage->Padding = new System::Windows::Forms::Padding(3);
					this->mainTabPage->Size = new System::Drawing::Size(360, 318);
					this->mainTabPage->TabIndex = 0;
					this->mainTabPage->Text = "Main";
					this->mainTabPage->UseVisualStyleBackColor = true;
					// 
					// commandline
					// 
					this->commandline->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->commandline->Location = new System::Drawing::Point(3, 350);
					this->commandline->Multiline = true;
					this->commandline->Name = "commandline";
					this->commandline->ReadOnly = true;
					this->commandline->Size = new System::Drawing::Size(365, 59);
					this->commandline->TabIndex = 41;
					// 
					// tooltipHelp
					// 
					this->tooltipHelp->AutoPopDelay = 30000;
					this->tooltipHelp->InitialDelay = 500;
					this->tooltipHelp->IsBalloon = true;
					this->tooltipHelp->ReshowDelay = 100;
					this->tooltipHelp->ShowAlways = true;
					// 
					// VideoConfigurationPanel
					// 
					this->Controls->Add(this->commandline);
					this->Controls->Add(this->tabControl1);
					this->Name = "VideoConfigurationPanel";
					this->Size = new System::Drawing::Size(372, 409);
					this->Load += new System::EventHandler(this, &VideoConfigurationPanel::VideoConfigurationPanel_Load);
					this->tabControl1->ResumeLayout(false);
					this->ResumeLayout(false);
					this->PerformLayout();

				}

				void VideoConfigurationPanel::InitializeInstanceFields()
				{
					updating = false;
					lastEncodingMode = 0;
					input = "input"
					output = "output"
					encoderPath = "program";
				}
			}
		}
	}
}
