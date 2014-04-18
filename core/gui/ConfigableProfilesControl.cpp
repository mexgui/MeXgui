#include "MeGUI.core.gui.ConfigableProfilesControl.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			ConfigableProfilesControl::ConfigableProfilesControl()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			void ConfigableProfilesControl::config_Click(QObject *sender, QEvent *e)
			{
				getManager()->Configure(getSelectedProfile());
				//RefreshProfiles();
			}

			void ConfigableProfilesControl::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				MeGUI::core::gui::SimpleProfilesControl::Dispose(disposing);
			}

			void ConfigableProfilesControl::InitializeComponent()
			{
				this->config = new System::Windows::Forms::Button();
				this->SuspendLayout();
				// 
				// config
				// 
				this->config->Anchor = System::Windows::Forms::AnchorStyles::None;
				this->config->AutoSize = true;
				this->config->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->config->Location = new System::Drawing::Point(194, 0);
				this->config->Margin = new System::Windows::Forms::Padding(0);
				this->config->Name = "config";
				this->config->Size = new System::Drawing::Size(47, 22);
				this->config->TabIndex = 1;
				this->config->Text = "Config";
				this->config->UseVisualStyleBackColor = true;
				this->config->Click += new System::EventHandler(this, &ConfigableProfilesControl::config_Click);
				this->tableLayoutPanel1->Controls->Add(this->config);
				this->tableLayoutPanel1->SetCellPosition(this->config, new System::Windows::Forms::TableLayoutPanelCellPosition(1, 0));
				// 
				// ConfigableProfilesControl
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->Name = "ConfigableProfilesControl";
				this->Size = new System::Drawing::Size(241, 22);
				this->ResumeLayout(false);

			}

			void ConfigableProfilesControl::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
