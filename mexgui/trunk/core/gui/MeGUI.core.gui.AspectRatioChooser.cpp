#include "MeGUI.core.gui.AspectRatioChooser.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			AspectRatioChooser::AspectRatioChooser()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			DialogResult *AspectRatioChooser::ShowDialog(Dar defaultDar, Dar &newDar)
			{
				AspectRatioChooser *n = new AspectRatioChooser();
				n->SetValues(defaultDar);
				if (defaultDar.getY() < 1)
					n->radioButton2->Checked = true;
				else
					n->radioButton1->Checked = true;

				DialogResult *r = n->ShowDialog();
				if (n->radioButton1->Checked)
					newDar = Dar(n->numericUpDown1->Value);
				else
					newDar = Dar(static_cast<unsigned long long>(n->numericUpDown2->Value), static_cast<unsigned long long>(n->numericUpDown3->Value));
				return r;
			}

			void AspectRatioChooser::SetValues(Dar ar)
			{
				bDisableEvents = true;
				if (ar.getAR() >= numericUpDown1->Minimum && ar.getAR() <= numericUpDown1->Maximum)
					numericUpDown1->Value = ar.getAR();
				if (ar.getX() >= numericUpDown2->Minimum && ar.getX() <= numericUpDown2->Maximum)
					numericUpDown2->Value = ar.getX();
				if (ar.getY() >= numericUpDown3->Minimum && ar.getY() <= numericUpDown3->Maximum)
					numericUpDown3->Value = ar.getY();
				bDisableEvents = false;
			}

			void AspectRatioChooser::radioButton_CheckedChanged(object *sender, EventArgs *e)
			{
				numericUpDown1->Enabled = radioButton1->Checked;
				numericUpDown2->Enabled = numericUpDown3->Enabled = !radioButton1->Checked;
			}

			void AspectRatioChooser::numericUpDown2_ValueChanged(object *sender, EventArgs *e)
			{
				if (bDisableEvents)
					return;
				bDisableEvents = true;
				Dar ar = Dar(static_cast<unsigned long long>(numericUpDown2->Value), static_cast<unsigned long long>(numericUpDown3->Value));
				if (ar.getAR() >= numericUpDown1->Minimum && ar.getAR() <= numericUpDown1->Maximum)
					numericUpDown1->Value = ar.getAR();
				bDisableEvents = false;
			}

			void AspectRatioChooser::numericUpDown1_ValueChanged(object *sender, EventArgs *e)
			{
				if (bDisableEvents)
					return;
				bDisableEvents = true;
				Dar ar = Dar(numericUpDown1->Value);
				if (ar.getX() >= numericUpDown2->Minimum && ar.getX() <= numericUpDown2->Maximum)
					numericUpDown2->Value = ar.getX();
				if (ar.getY() >= numericUpDown3->Minimum && ar.getY() <= numericUpDown3->Maximum)
					numericUpDown3->Value = ar.getY();
				bDisableEvents = false;
			}

			void AspectRatioChooser::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				System::Windows::Forms::Form::Dispose(disposing);
			}

			void AspectRatioChooser::InitializeComponent()
			{
				System::Windows::Forms::Button *button1;
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(AspectRatioChooser::typeid);
				this->button2 = new System::Windows::Forms::Button();
				this->numericUpDown1 = new System::Windows::Forms::NumericUpDown();
				this->radioButton1 = new System::Windows::Forms::RadioButton();
				this->radioButton2 = new System::Windows::Forms::RadioButton();
				this->numericUpDown2 = new System::Windows::Forms::NumericUpDown();
				this->numericUpDown3 = new System::Windows::Forms::NumericUpDown();
				this->label1 = new System::Windows::Forms::Label();
				button1 = new System::Windows::Forms::Button();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->numericUpDown1))->BeginInit();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->numericUpDown2))->BeginInit();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->numericUpDown3))->BeginInit();
				this->SuspendLayout();
				// 
				// button1
				// 
				button1->AutoSize = true;
				button1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				button1->Location = new System::Drawing::Point(142, 90);
				button1->Name = "button1";
				button1->Size = new System::Drawing::Size(49, 23);
				button1->TabIndex = 0;
				button1->Text = "Cancel";
				button1->UseVisualStyleBackColor = true;
				// 
				// button2
				// 
				this->button2->AutoSize = true;
				this->button2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->button2->DialogResult = System::Windows::Forms::DialogResult::OK;
				this->button2->Location = new System::Drawing::Point(104, 90);
				this->button2->Name = "button2";
				this->button2->Size = new System::Drawing::Size(31, 23);
				this->button2->TabIndex = 1;
				this->button2->Text = "OK";
				this->button2->UseVisualStyleBackColor = true;
				// 
				// numericUpDown1
				// 
				this->numericUpDown1->DecimalPlaces = 3;
				this->numericUpDown1->Increment = decimal(new int[4] {1, 0, 0, 65536});
				this->numericUpDown1->Location = new System::Drawing::Point(34, 24);
				this->numericUpDown1->Maximum = decimal(new int[4] {10, 0, 0, 0});
				this->numericUpDown1->Minimum = decimal(new int[4] {1, 0, 0, 65536});
				this->numericUpDown1->Name = "numericUpDown1";
				this->numericUpDown1->Size = new System::Drawing::Size(157, 21);
				this->numericUpDown1->TabIndex = 3;
				this->numericUpDown1->Value = decimal(new int[4] {1, 0, 0, 0});
				this->numericUpDown1->ValueChanged += new System::EventHandler(this, &AspectRatioChooser::numericUpDown1_ValueChanged);
				// 
				// radioButton1
				// 
				this->radioButton1->AutoSize = true;
				this->radioButton1->Location = new System::Drawing::Point(13, 26);
				this->radioButton1->Name = "radioButton1";
				this->radioButton1->Size = new System::Drawing::Size(14, 13);
				this->radioButton1->TabIndex = 4;
				this->radioButton1->TabStop = true;
				this->radioButton1->UseVisualStyleBackColor = true;
				this->radioButton1->CheckedChanged += new System::EventHandler(this, &AspectRatioChooser::radioButton_CheckedChanged);
				// 
				// radioButton2
				// 
				this->radioButton2->AutoSize = true;
				this->radioButton2->Location = new System::Drawing::Point(13, 53);
				this->radioButton2->Name = "radioButton2";
				this->radioButton2->Size = new System::Drawing::Size(14, 13);
				this->radioButton2->TabIndex = 5;
				this->radioButton2->TabStop = true;
				this->radioButton2->UseVisualStyleBackColor = true;
				this->radioButton2->CheckedChanged += new System::EventHandler(this, &AspectRatioChooser::radioButton_CheckedChanged);
				// 
				// numericUpDown2
				// 
				this->numericUpDown2->Location = new System::Drawing::Point(34, 51);
				this->numericUpDown2->Maximum = decimal(new int[4] {999999999, 0, 0, 0});
				this->numericUpDown2->Minimum = decimal(new int[4] {1, 0, 0, 0});
				this->numericUpDown2->Name = "numericUpDown2";
				this->numericUpDown2->Size = new System::Drawing::Size(70, 21);
				this->numericUpDown2->TabIndex = 6;
				this->numericUpDown2->Value = decimal(new int[4] {1, 0, 0, 0});
				this->numericUpDown2->ValueChanged += new System::EventHandler(this, &AspectRatioChooser::numericUpDown2_ValueChanged);
				// 
				// numericUpDown3
				// 
				this->numericUpDown3->Location = new System::Drawing::Point(121, 51);
				this->numericUpDown3->Maximum = decimal(new int[4] {100000000, 0, 0, 0});
				this->numericUpDown3->Minimum = decimal(new int[4] {1, 0, 0, 0});
				this->numericUpDown3->Name = "numericUpDown3";
				this->numericUpDown3->Size = new System::Drawing::Size(70, 21);
				this->numericUpDown3->TabIndex = 7;
				this->numericUpDown3->Value = decimal(new int[4] {1, 0, 0, 0});
				this->numericUpDown3->ValueChanged += new System::EventHandler(this, &AspectRatioChooser::numericUpDown2_ValueChanged);
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = new System::Drawing::Point(107, 54);
				this->label1->Name = "label1";
				this->label1->Size = new System::Drawing::Size(11, 13);
				this->label1->TabIndex = 8;
				this->label1->Text = ":";
				// 
				// AspectRatioChooser
				// 
				this->AcceptButton = this->button2;
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = new System::Drawing::Size(202, 123);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->numericUpDown3);
				this->Controls->Add(this->numericUpDown2);
				this->Controls->Add(this->radioButton2);
				this->Controls->Add(this->radioButton1);
				this->Controls->Add(this->numericUpDown1);
				this->Controls->Add(this->button2);
				this->Controls->Add(button1);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->Name = "AspectRatioChooser";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
				this->Text = "Custom Aspect Ratio";
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->numericUpDown1))->EndInit();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->numericUpDown2))->EndInit();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->numericUpDown3))->EndInit();
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void AspectRatioChooser::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
