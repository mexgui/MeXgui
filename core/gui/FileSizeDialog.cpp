#include "MeGUI.core.gui.FileSizeDialog.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			FileSizeDialog::FileSizeDialog()
			{
				InitializeInstanceFields();
				InitializeComponent();
				setCurrentUnit(MB);
			}

			const MeGUI::core::util::FileSize &FileSizeDialog::getMaximum() const
			{
				return maxVal;
			}

			void FileSizeDialog::setMaximum(const FileSize &value)
			{
				maxVal = value;
			}

			const MeGUI::core::util::FileSize &FileSizeDialog::getMinimum() const
			{
				return minVal;
			}

			void FileSizeDialog::setMinimum(const FileSize &value)
			{
				minVal = value;
			}

			const MeGUI::core::util::FileSize &FileSizeDialog::getValue() const
			{
				return readValue(getCurrentUnit());
			}

			void FileSizeDialog::setValue(const FileSize &value)
			{
				Unit u = value.getBestUnit();
				setCurrentUnit(u);
				adjustDP();
				number->Value = value.InUnitsExact(u);
			}

			MeGUI::core::util::FileSize FileSizeDialog::readValue(Unit u)
			{
				return FileSize(u, number->Value);
			}

			const MeGUI::core::util::Unit &FileSizeDialog::getCurrentUnit() const
			{
				if (units->SelectedIndex < 0)
					return B;
				return static_cast<Unit>(units->SelectedIndex);
			}

			void FileSizeDialog::setCurrentUnit(const Unit &value)
			{
				units->SelectedIndex = static_cast<unsigned short>(value);
			}

			void FileSizeDialog::adjustDP()
			{
				if (getCurrentUnit() == B)
				{
					number->DecimalPlaces = 0;
					number->Increment = 1;
				}
				else
				{
					number->DecimalPlaces = 1;
					number->Increment = 0.1;
				}
				number->Maximum = maxVal.InUnitsExact(getCurrentUnit());
				number->Minimum = minVal.InUnitsExact(getCurrentUnit());
			}

			void FileSizeDialog::FileSizeDialog_Shown(QObject *sender, QEvent *e)
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				number->Select(0, number->Value->ToString()->Length);
				number->Focus();
			}

			void FileSizeDialog::number_KeyPress(QObject *sender, KeyPressQEvent *e)
			{
				if (e->KeyChar == '\r')
					okButton->PerformClick();
			}

			void FileSizeDialog::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				System::Windows::Forms::Form::Dispose(disposing);
			}

			void FileSizeDialog::InitializeComponent()
			{
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(FileSizeDialog::typeid);
				this->number = new System::Windows::Forms::NumericUpDown();
				this->units = new System::Windows::Forms::ComboBox();
				this->okButton = new System::Windows::Forms::Button();
				this->cancelButton = new System::Windows::Forms::Button();
				this->label1 = new System::Windows::Forms::Label();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->number))->BeginInit();
				this->SuspendLayout();
				// 
				// number
				// 
				this->number->Location = new System::Drawing::Point(15, 47);
				this->number->Maximum = decimal(new int[4] {-559939585, 902409669, 54, 0});
				this->number->Name = "number";
				this->number->Size = new System::Drawing::Size(226, 21);
				this->number->TabIndex = 0;
				this->number->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, &FileSizeDialog::number_KeyPress);
				// 
				// units
				// 
				this->units->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				this->units->Items->AddRange(new object[4] {"B", "KB", "MB", "GB"});
				this->units->Location = new System::Drawing::Point(245, 47);
				this->units->Name = "units";
				this->units->Size = new System::Drawing::Size(73, 21);
				this->units->TabIndex = 1;
				// 
				// okButton
				// 
				this->okButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
				this->okButton->AutoSize = true;
				this->okButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
				this->okButton->Location = new System::Drawing::Point(237, 88);
				this->okButton->Name = "okButton";
				this->okButton->Size = new System::Drawing::Size(31, 23);
				this->okButton->TabIndex = 2;
				this->okButton->Text = "OK";
				this->okButton->UseVisualStyleBackColor = true;
				// 
				// cancelButton
				// 
				this->cancelButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
				this->cancelButton->AutoSize = true;
				this->cancelButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				this->cancelButton->Location = new System::Drawing::Point(275, 88);
				this->cancelButton->Name = "cancelButton";
				this->cancelButton->Size = new System::Drawing::Size(49, 23);
				this->cancelButton->TabIndex = 3;
				this->cancelButton->Text = "Cancel";
				this->cancelButton->UseVisualStyleBackColor = true;
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = new System::Drawing::Point(12, 19);
				this->label1->Name = "label1";
				this->label1->Size = new System::Drawing::Size(81, 13);
				this->label1->TabIndex = 6;
				this->label1->Text = "Enter a filesize:";
				// 
				// FileSizeDialog
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = new System::Drawing::Size(336, 123);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->cancelButton);
				this->Controls->Add(this->okButton);
				this->Controls->Add(this->number);
				this->Controls->Add(this->units);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->MaximizeBox = false;
				this->MinimizeBox = false;
				this->Name = "FileSizeDialog";
				this->Text = "Filesize dialog";
				this->Shown += new System::EventHandler(this, &FileSizeDialog::FileSizeDialog_Shown);
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->number))->EndInit();
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void FileSizeDialog::InitializeInstanceFields()
			{
				maxVal = FileSize(quint64::MaxValue);
				minVal = FileSize::Empty;
				delete components;
			}
		}
	}
}
