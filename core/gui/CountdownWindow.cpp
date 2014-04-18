#include "MeGUI.core.gui.CountdownWindow.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			CountdownWindow::CountdownWindow()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			CountdownWindow::CountdownWindow(int countdown)
			{
				InitializeInstanceFields();
				this->countdown = countdown;
				InitializeComponent();
			}

			void CountdownWindow::CountdownWindow_Load(QObject *sender, QEvent *e)
			{
				//bool b = this.TopMost;
				this->Activate();
				this->Focus();
				this->BringToFront();
				remain = countdown;
				SetProgressBar(0, 1, 0);
				SetButtonText(StringConverterHelper::toString(remain));
				timer->Enabled = true;
			}

			void CountdownWindow::SetProgressBar(int minValue, int maxValue, int currentValue)
			{
				if (this->progressBar->InvokeRequired)
				{
					UpdateProgressBar d = new UpdateProgressBar(this, &CountdownWindow::SetProgressBar);
					this->Invoke(d, minValue, maxValue, currentValue);
				}
				else
				{
					this->progressBar->Minimum = static_cast<int>(minValue);
					this->progressBar->Maximum = static_cast<int>(maxValue);
					this->progressBar->Value = static_cast<int>(currentValue);
				}
			}

			void CountdownWindow::SetButtonText(const QString &text)
			{
				if (this->cancelButton->InvokeRequired)
				{
					UpdateCancelButton d = new UpdateCancelButton(this, &CountdownWindow::SetButtonText);
					this->Invoke(d, text);
				}
				else
				{
					this->cancelButton->Text = QString::Format("Cancel ({0})", text);
				}
			}

			void CountdownWindow::TimerTick(QObject *sender, System::QEvent *e)
			{
				remain--;
				if (remain > 0)
				{
					SetProgressBar(0, countdown, countdown - remain);
					SetButtonText(StringConverterHelper::toString(remain));
				}
				else
				{
					SetProgressBar(0, 1, 1);
					SetButtonText("0");
					System::Windows::Forms::Form::DialogResult = System::Windows::Forms::DialogResult::OK;
				}
			}

			void CountdownWindow::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				System::Windows::Forms::Form::Dispose(disposing);
			}

			void CountdownWindow::InitializeComponent()
			{
				this->components = new System::ComponentModel::Container();
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(CountdownWindow::typeid);
				this->label1 = new System::Windows::Forms::Label();
				this->cancelButton = new System::Windows::Forms::Button();
				this->progressBar = new System::Windows::Forms::ProgressBar();
				this->timer = new System::Windows::Forms::Timer(this->components);
				this->SuspendLayout();
				// 
				// label1
				// 
				this->label1->Location = new System::Drawing::Point(12, 12);
				this->label1->Name = "label1";
				this->label1->Size = new System::Drawing::Size(330, 32);
				this->label1->TabIndex = 5;
				this->label1->Text = "MeGUI has finished processing the job queue and is about to shut down your comput" + "er.";
				// 
				// cancelButton
				// 
				this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				this->cancelButton->Location = new System::Drawing::Point(128, 97);
				this->cancelButton->Name = "cancelButton";
				this->cancelButton->Size = new System::Drawing::Size(100, 25);
				this->cancelButton->TabIndex = 4;
				this->cancelButton->Text = "Cancel";
				this->cancelButton->UseVisualStyleBackColor = true;
				// 
				// progressBar
				// 
				this->progressBar->Location = new System::Drawing::Point(15, 57);
				this->progressBar->Name = "progressBar";
				this->progressBar->Size = new System::Drawing::Size(320, 19);
				this->progressBar->TabIndex = 3;
				// 
				// timer
				// 
				this->timer->Interval = 1000;
				this->timer->Tick += new System::EventHandler(this, &CountdownWindow::TimerTick);
				// 
				// CountdownWindow
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = new System::Drawing::Size(347, 134);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->cancelButton);
				this->Controls->Add(this->progressBar);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->MaximizeBox = false;
				this->MinimizeBox = false;
				this->Name = "CountdownWindow";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->Text = "About to shut down";
				this->TopMost = true;
				this->Load += new System::EventHandler(this, &CountdownWindow::CountdownWindow_Load);
				this->ResumeLayout(false);

			}

			void CountdownWindow::InitializeInstanceFields()
			{
				countdown = 15;
				remain = 15;
				delete components;
			}
		}
	}
}
