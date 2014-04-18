#include "MeGUI.core.gui.TextViewer.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			TextViewer::TextViewer()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			const QString &TextViewer::getContents() const
			{
				return textBox1->Text;
			}

			void TextViewer::setContents(const QString &value)
			{
				textBox1->Text = value;
			}

			const bool &TextViewer::getWrap() const
			{
				return textBox1->WordWrap;
			}

			void TextViewer::setWrap(const bool &value)
			{
				textBox1->WordWrap = value;
			}

			void TextViewer::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				System::Windows::Forms::Form::Dispose(disposing);
			}

			void TextViewer::InitializeComponent()
			{
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(TextViewer::typeid);
				this->button2 = new System::Windows::Forms::Button();
				this->textBox1 = new System::Windows::Forms::TextBox();
				this->SuspendLayout();
				// 
				// button2
				// 
				this->button2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
				this->button2->DialogResult = System::Windows::Forms::DialogResult::OK;
				this->button2->Location = new System::Drawing::Point(583, 363);
				this->button2->Name = "button2";
				this->button2->Size = new System::Drawing::Size(75, 23);
				this->button2->TabIndex = 1;
				this->button2->Text = "OK";
				this->button2->UseVisualStyleBackColor = true;
				// 
				// textBox1
				// 
				this->textBox1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
				this->textBox1->Font = new System::Drawing::Font("Lucida Console", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->textBox1->Location = new System::Drawing::Point(12, 12);
				this->textBox1->Multiline = true;
				this->textBox1->Name = "textBox1";
				this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Both;
				this->textBox1->Size = new System::Drawing::Size(646, 335);
				this->textBox1->TabIndex = 2;
				// 
				// TextViewer
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = new System::Drawing::Size(670, 398);
				this->Controls->Add(this->textBox1);
				this->Controls->Add(this->button2);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->Name = "TextViewer";
				this->Text = "Text Viewer";
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void TextViewer::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
