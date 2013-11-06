#include "MeGUI.core.gui.HelpButton.h"

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
	namespace core
	{
		namespace gui
		{

const std::string HelpButton::BaseURL = "http://mewiki.project357.com/wiki/MeGUI/";

			HelpButton::HelpButton()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			void HelpButton::HelpButton_Click(object *sender, EventArgs *e)
			{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				System::Diagnostics::Process::Start(BaseURL + articleName.Replace(' ', '_'));
			}

			const std::string &HelpButton::getArticleName() const
			{
				return articleName;
			}

			void HelpButton::setArticleName(const std::string &value)
			{
				articleName = value;
			}

			void HelpButton::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				UserControl::Dispose(disposing);
			}

			void HelpButton::InitializeComponent()
			{
				this->button1 = new System::Windows::Forms::Button();
				this->SuspendLayout();
				// 
				// button1
				// 
				this->button1->AutoSize = true;
				this->button1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->button1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->button1->Location = new System::Drawing::Point(0, 0);
				this->button1->Name = "button1";
				this->button1->Size = new System::Drawing::Size(39, 23);
				this->button1->TabIndex = 0;
				this->button1->Text = "&Help";
				this->button1->UseVisualStyleBackColor = true;
				this->button1->Click += new System::EventHandler(this, &HelpButton::HelpButton_Click);
				// 
				// HelpButton
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->Controls->Add(this->button1);
				this->Name = "HelpButton";
				this->Size = new System::Drawing::Size(39, 23);
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void HelpButton::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
