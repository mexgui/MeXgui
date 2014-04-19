#include "CountdownWindow.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


namespace MeXgui
{
	namespace core
	{
		namespace gui
		{

         CountdownWindow::CountdownWindow(QWidget *parent):
            QDialog(parent),
            ui(new Ui::CountdownWindow)
        {
            ui->setupUi(this);

            InitializeInstanceFields();

        }


			CountdownWindow::CountdownWindow(int countdown)
			{
				InitializeInstanceFields();
				this->countdown = countdown;
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

			void CountdownWindow::InitializeInstanceFields()
			{
				countdown = 15;
				remain = 15;
				delete components;
			}
		}
	}
}
