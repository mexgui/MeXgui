#include "MeGUI.core.gui.InputBox.h"

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

			InputBox::InputBox()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			void InputBox::btnOk_Click(object *sender, EventArgs *e)
			{
				DialogResult = System::Windows::Forms::DialogResult::OK;
				Close();
			}

			void InputBox::btnCancel_Click(object *sender, EventArgs *e)
			{
				DialogResult = System::Windows::Forms::DialogResult::Cancel;
				Close();
			}

			std::string InputBox::Show(const std::string &message, const std::string &title, const std::string &defaultText)
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (InputBox box = new InputBox())
				InputBox *box = new InputBox();
				try
				{
					box->lblMessage->Text = message;
					box->text->Text = defaultText;
					box->Text = title;
					if (box->ShowDialog() == System::Windows::Forms::DialogResult::OK)
						return box->text->Text;
					return 0;
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (box != 0)
						box.Dispose();
				}
			}

			void InputBox::text_KeyPress(object *sender, KeyPressEventArgs *e)
			{
				if (e->KeyChar == 13)
				{
					btnOk_Click(0, 0);
				}
				else if (e->KeyChar == 27)
				{
					btnCancel_Click(0, 0);
				}
			}

			void InputBox::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				System::Windows::Forms::Form::Dispose(disposing);
			}

			void InputBox::InitializeComponent()
			{
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(InputBox::typeid);
				this->btnOk = new System::Windows::Forms::Button();
				this->btnCancel = new System::Windows::Forms::Button();
				this->text = new System::Windows::Forms::TextBox();
				this->lblMessage = new System::Windows::Forms::Label();
				this->SuspendLayout();
				// 
				// btnOk
				// 
				this->btnOk->Location = new System::Drawing::Point(263, 12);
				this->btnOk->Name = "btnOk";
				this->btnOk->Size = new System::Drawing::Size(75, 23);
				this->btnOk->TabIndex = 1;
				this->btnOk->Text = "Ok";
				this->btnOk->UseVisualStyleBackColor = true;
				this->btnOk->Click += new System::EventHandler(this, &InputBox::btnOk_Click);
				// 
				// btnCancel
				// 
				this->btnCancel->Location = new System::Drawing::Point(263, 41);
				this->btnCancel->Name = "btnCancel";
				this->btnCancel->Size = new System::Drawing::Size(75, 23);
				this->btnCancel->TabIndex = 2;
				this->btnCancel->Text = "Cancel";
				this->btnCancel->UseVisualStyleBackColor = true;
				this->btnCancel->Click += new System::EventHandler(this, &InputBox::btnCancel_Click);
				// 
				// text
				// 
				this->text->Location = new System::Drawing::Point(12, 93);
				this->text->Name = "text";
				this->text->Size = new System::Drawing::Size(326, 21);
				this->text->TabIndex = 0;
				this->text->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, &InputBox::text_KeyPress);
				// 
				// lblMessage
				// 
				this->lblMessage->AutoSize = true;
				this->lblMessage->Location = new System::Drawing::Point(12, 9);
				this->lblMessage->Name = "lblMessage";
				this->lblMessage->Size = new System::Drawing::Size(35, 13);
				this->lblMessage->TabIndex = 3;
				this->lblMessage->Text = "label1";
				// 
				// InputBox
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = new System::Drawing::Size(350, 125);
				this->Controls->Add(this->lblMessage);
				this->Controls->Add(this->text);
				this->Controls->Add(this->btnCancel);
				this->Controls->Add(this->btnOk);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->Name = "InputBox";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
				this->Text = "InputBox";
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void InputBox::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
