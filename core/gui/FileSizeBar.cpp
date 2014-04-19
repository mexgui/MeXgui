#include "FileSizeBar.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace core
	{
		namespace gui
		{

			FileSizeEvent::FileSizeEvent(FileSize value) : QEvent(), Value(value)
			{
			}
			
			const MeXgui::core::util::FileSize &FileSizeBar::getMaximum() const
			{
				return maxVal;
			}

			void FileSizeBar::setMaximum(const FileSize &value)
			{
				maxVal = value;
			}

			const MeXgui::core::util::FileSize &FileSizeBar::getMinimum() const
			{
				return minVal;
			}

			void FileSizeBar::setMinimum(const FileSize &value)
			{
				minVal = value;
			}

			FileSizeBar::FileSizeBar()
			{
				InitializeInstanceFields();
				InitializeComponent();
				setCurrentUnit(B);
				lastUnit = getCurrentUnit();
				adjustDP();
			}

			const MeXgui::core::util::FileSize &FileSizeBar::getValue() const
			{
				return readValue(getCurrentUnit());
			}

			void FileSizeBar::setValue(const FileSize &value)
			{
				Unit u = value.getBestUnit();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (IDisposable a = changeCounter.Wrap())
				IDisposable *a = changeCounter->Wrap();
				try
				{
					setCurrentUnit(u);
					adjustDP();
					number->Value = value.InUnitsExact(u);
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (a != 0)
						a.Dispose();
				}
			}

			MeXgui::core::util::FileSize FileSizeBar::readValue(Unit u)
			{
				return FileSize(u, number->Value);
			}

			const MeXgui::core::util::Unit &FileSizeBar::getCurrentUnit() const
			{
				if (units->SelectedIndex < 0)
					return B;
				return static_cast<Unit>(units->SelectedIndex);
			}

			void FileSizeBar::setCurrentUnit(const Unit &value)
			{
				units->SelectedIndex = static_cast<unsigned short>(value);
			}

			void FileSizeBar::adjustDP()
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

			void FileSizeBar::triggerChangedEvent()
			{
				if (changeCounter->getReady())
					ValueChanged(this, new FileSizeQEvent(getValue()));
			}

			void FileSizeBar::units_SelectedIndexChanged(QObject *sender, QEvent *e)
			{
				if (!changeCounter->getReady())
					return;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (IDisposable a = changeCounter.Wrap())
				IDisposable *a = changeCounter->Wrap();
				try
				{
					FileSize f = readValue(lastUnit);
					adjustDP();
					number->Value = f.InUnitsExact(getCurrentUnit());
					lastUnit = getCurrentUnit();
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (a != 0)
						a.Dispose();
				}
				triggerChangedEvent();
			}

			void FileSizeBar::number_ValueChanged(QObject *sender, QEvent *e)
			{
				triggerChangedEvent();
			}

			void FileSizeBar::FileSizeBar_EnabledChanged(QObject *sender, QEvent *e)
			{
				units->Enabled = Enabled;
				number->Enabled = Enabled;
				number->ReadOnly = !Enabled;
			}

			void FileSizeBar::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				UserControl::Dispose(disposing);
			}

			void FileSizeBar::InitializeComponent()
			{
				this->units = new System::Windows::Forms::ComboBox();
				this->number = new System::Windows::Forms::NumericUpDown();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->number))->BeginInit();
				this->SuspendLayout();
				// 
				// units
				// 
				this->units->Dock = System::Windows::Forms::DockStyle::Right;
				this->units->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				this->units->Items->AddRange(new object[4] {"B", "KB", "MB", "GB"});
				this->units->Location = new System::Drawing::Point(143, 0);
				this->units->Name = "units";
				this->units->Size = new System::Drawing::Size(42, 21);
				this->units->TabIndex = 0;
				this->units->SelectedIndexChanged += new System::EventHandler(this, &FileSizeBar::units_SelectedIndexChanged);
				// 
				// number
				// 
				this->number->Dock = System::Windows::Forms::DockStyle::Fill;
				this->number->Location = new System::Drawing::Point(0, 0);
				this->number->Maximum = decimal(new int[4] {-559939585, 902409669, 54, 0});
				this->number->Name = "number";
				this->number->Size = new System::Drawing::Size(143, 20);
				this->number->TabIndex = 1;
				this->number->ValueChanged += new System::EventHandler(this, &FileSizeBar::number_ValueChanged);
				// 
				// FileSizeBar
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->Controls->Add(this->number);
				this->Controls->Add(this->units);
				this->Name = "FileSizeBar";
				this->Size = new System::Drawing::Size(185, 24);
				this->EnabledChanged += new System::EventHandler(this, &FileSizeBar::FileSizeBar_EnabledChanged);
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->number))->EndInit();
				this->ResumeLayout(false);

			}

			void FileSizeBar::InitializeInstanceFields()
			{
				changeCounter = new NotifyCounter();
				maxVal = FileSize(quint64::MaxValue);
				minVal = FileSize::Empty;
				delete components;
			}
		}
	}
}
