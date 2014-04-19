#include "NumberChooser.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


namespace MeXgui
{
	namespace core
	{
		namespace gui
		{

			NumberChooser::NumberChooser()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			DialogResult *NumberChooser::show(const QString &message, const QString &title, int decimals, decimal min, decimal max, decimal defaultNum, decimal &number)
			{
				NumberChooser *n = new NumberChooser();
				n->Text = title;
				n->label1->Text = message;
				n->numericUpDown1->DecimalPlaces = decimals;
				n->numericUpDown1->Minimum = min;
				n->numericUpDown1->Maximum = max;
				n->numericUpDown1->Value = defaultNum;

				DialogResult *r = n->show();
				number = n->numericUpDown1->Value;
				return r;
			}

			void NumberChooser::NumberChooser_Shown(QObject *sender, QEvent *e)
			{
				numericUpDown1->Select(0, getstringLength());
				numericUpDown1->Focus();

			}

			const int &NumberChooser::getstringLength() const
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return Math::Round(numericUpDown1->Value, 0)->ToString()->Length + (numericUpDown1->DecimalPlaces > 0 ? 1 : 0) + numericUpDown1->DecimalPlaces;
			}

			void NumberChooser::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				System::Windows::Forms::Form::Dispose(disposing);
			}

			void NumberChooser::InitializeComponent()
			{
				System::Windows::Forms::Button *button1;
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(NumberChooser::typeid);
				this->button2 = new System::Windows::Forms::Button();
				this->label1 = new System::Windows::Forms::Label();
				this->numericUpDown1 = new System::Windows::Forms::NumericUpDown();
				button1 = new System::Windows::Forms::Button();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->numericUpDown1))->BeginInit();
				this->SuspendLayout();
				// 
				// button1
				// 
				button1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
				button1->AutoSize = true;
				button1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				button1->Location = new System::Drawing::Point(289, 78);
				button1->Name = "button1";
				button1->Size = new System::Drawing::Size(49, 23);
				button1->TabIndex = 0;
				button1->Text = "Cancel";
				button1->UseVisualStyleBackColor = true;
				// 
				// button2
				// 
				this->button2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
				this->button2->AutoSize = true;
				this->button2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->button2->DialogResult = System::Windows::Forms::DialogResult::OK;
				this->button2->Location = new System::Drawing::Point(251, 78);
				this->button2->Name = "button2";
				this->button2->Size = new System::Drawing::Size(31, 23);
				this->button2->TabIndex = 1;
				this->button2->Text = "OK";
				this->button2->UseVisualStyleBackColor = true;
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = new System::Drawing::Point(12, 9);
				this->label1->Name = "label1";
				this->label1->Size = new System::Drawing::Size(35, 13);
				this->label1->TabIndex = 2;
				this->label1->Text = "label1";
				// 
				// numericUpDown1
				// 
				this->numericUpDown1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
				this->numericUpDown1->Location = new System::Drawing::Point(12, 43);
				this->numericUpDown1->Name = "numericUpDown1";
				this->numericUpDown1->Size = new System::Drawing::Size(326, 21);
				this->numericUpDown1->TabIndex = 3;
				// 
				// NumberChooser
				// 
				this->AcceptButton = this->button2;
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = new System::Drawing::Size(350, 113);
				this->Controls->Add(this->numericUpDown1);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->button2);
				this->Controls->Add(button1);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->Name = "NumberChooser";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->Text = "NumberChooser";
				this->Shown += new System::EventHandler(this, &NumberChooser::NumberChooser_Shown);
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->numericUpDown1))->EndInit();
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void NumberChooser::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
