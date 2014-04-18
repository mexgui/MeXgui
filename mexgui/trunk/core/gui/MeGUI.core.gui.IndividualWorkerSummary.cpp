#include "MeGUI.core.gui.IndividualWorkerSummary.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			IndividualWorkerSummary::IndividualWorkerSummary()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			void IndividualWorkerSummary::setWorker(const JobWorker &value)
			{
				w = value;
			}

			void IndividualWorkerSummary::RefreshInfo()
			{
				workerNameAndJob->Text = std::string::Format("{0}: {1}", w->getName(), w->getStatusString());
				progressBar1->Value = static_cast<int>(w->getProgress());
			}

			void IndividualWorkerSummary::startEncodingToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				w->StartEncoding(true);
				RefreshInfo();
			}

			void IndividualWorkerSummary::abortToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				w->UserRequestedAbort();
			}

			void IndividualWorkerSummary::renameToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				w->UserRequestedRename();
			}

			void IndividualWorkerSummary::stopToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				if (stopToolStripMenuItem->Checked)
					w->SetRunning();
				else
					w->SetStopping();
			}

			void IndividualWorkerSummary::shutDownToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				w->UserRequestShutDown();
			}

			void IndividualWorkerSummary::shutDownLaterToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				w->ShutDownWhenFinished();
			}

			void IndividualWorkerSummary::showProgressWindowToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				if (showProgressWindowToolStripMenuItem->Checked)
					w->HideProcessWindow();
				else
					w->ShowProcessWindow();
			}

			void IndividualWorkerSummary::showQueueToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				if (showQueueToolStripMenuItem->Checked)
					w->Hide();
				else
					w->Show();
			}

			void IndividualWorkerSummary::contextMenuStrip1_Opening(object *sender, CancelEventArgs *e)
			{
				startEncodingToolStripMenuItem->Enabled = !w->getIsEncoding();
				abortToolStripMenuItem->Enabled = w->getIsEncoding();

				stopToolStripMenuItem->Enabled = w->getIsEncoding();
				stopToolStripMenuItem->Checked = w->getStatus() == Stopping;

				shutDownLaterToolStripMenuItem->Enabled = (w->getLocalJobCount() > 0 || w->getStatus() != Idle);
				shutDownLaterToolStripMenuItem->Checked = w->getMode() == CloseOnLocalListCompleted;

				showProgressWindowToolStripMenuItem->Enabled = w->getIsProgressWindowAvailable();
				showProgressWindowToolStripMenuItem->Checked = w->getIsProgressWindowVisible();

				showQueueToolStripMenuItem->Checked = w->Visible;
			}

			void IndividualWorkerSummary::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				UserControl::Dispose(disposing);
			}

			void IndividualWorkerSummary::InitializeComponent()
			{
				this->components = new System::ComponentModel::Container();
				this->workerNameAndJob = new System::Windows::Forms::GroupBox();
				this->progressBar1 = new System::Windows::Forms::ProgressBar();
				this->contextMenuStrip1 = new System::Windows::Forms::ContextMenuStrip(this->components);
				this->startEncodingToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->stopToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->abortToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->shutDownLaterToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->shutDownToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->showProgressWindowToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->showQueueToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->renameToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->toolStripSeparator1 = new System::Windows::Forms::ToolStripSeparator();
				this->workerNameAndJob->SuspendLayout();
				this->contextMenuStrip1->SuspendLayout();
				this->SuspendLayout();
				// 
				// workerNameAndJob
				// 
				this->workerNameAndJob->Controls->Add(this->progressBar1);
				this->workerNameAndJob->Dock = System::Windows::Forms::DockStyle::Fill;
				this->workerNameAndJob->Location = new System::Drawing::Point(0, 0);
				this->workerNameAndJob->Name = "workerNameAndJob";
				this->workerNameAndJob->Padding = new System::Windows::Forms::Padding(5);
				this->workerNameAndJob->Size = new System::Drawing::Size(292, 47);
				this->workerNameAndJob->TabIndex = 0;
				this->workerNameAndJob->TabStop = false;
				this->workerNameAndJob->Text = "[Name]: [status]";
				// 
				// progressBar1
				// 
				this->progressBar1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->progressBar1->Location = new System::Drawing::Point(5, 18);
				this->progressBar1->Name = "progressBar1";
				this->progressBar1->Size = new System::Drawing::Size(282, 24);
				this->progressBar1->TabIndex = 0;
				// 
				// contextMenuStrip1
				// 
				this->contextMenuStrip1->Items->AddRange(new System::Windows::Forms::ToolStripItem[9] {this->startEncodingToolStripMenuItem, this->stopToolStripMenuItem, this->abortToolStripMenuItem, this->shutDownLaterToolStripMenuItem, this->shutDownToolStripMenuItem, this->toolStripSeparator1, this->showProgressWindowToolStripMenuItem, this->showQueueToolStripMenuItem, this->renameToolStripMenuItem});
				this->contextMenuStrip1->Name = "contextMenuStrip1";
				this->contextMenuStrip1->Size = new System::Drawing::Size(288, 208);
				this->contextMenuStrip1->Opening += new System::ComponentModel::CancelEventHandler(this, &IndividualWorkerSummary::contextMenuStrip1_Opening);
				// 
				// startEncodingToolStripMenuItem
				// 
				this->startEncodingToolStripMenuItem->Name = "startEncodingToolStripMenuItem";
				this->startEncodingToolStripMenuItem->Size = new System::Drawing::Size(287, 22);
				this->startEncodingToolStripMenuItem->Text = "Start worker";
				this->startEncodingToolStripMenuItem->Click += new System::EventHandler(this, &IndividualWorkerSummary::startEncodingToolStripMenuItem_Click);
				// 
				// stopToolStripMenuItem
				// 
				this->stopToolStripMenuItem->Name = "stopToolStripMenuItem";
				this->stopToolStripMenuItem->Size = new System::Drawing::Size(287, 22);
				this->stopToolStripMenuItem->Text = "Stop worker after the current job";
				this->stopToolStripMenuItem->Click += new System::EventHandler(this, &IndividualWorkerSummary::stopToolStripMenuItem_Click);
				// 
				// abortToolStripMenuItem
				// 
				this->abortToolStripMenuItem->Name = "abortToolStripMenuItem";
				this->abortToolStripMenuItem->Size = new System::Drawing::Size(287, 22);
				this->abortToolStripMenuItem->Text = "Abort job and stop worker immediately";
				this->abortToolStripMenuItem->Click += new System::EventHandler(this, &IndividualWorkerSummary::abortToolStripMenuItem_Click);
				// 
				// shutDownLaterToolStripMenuItem
				// 
				this->shutDownLaterToolStripMenuItem->Name = "shutDownLaterToolStripMenuItem";
				this->shutDownLaterToolStripMenuItem->Size = new System::Drawing::Size(287, 22);
				this->shutDownLaterToolStripMenuItem->Text = "Delete worker when finished local queue";
				this->shutDownLaterToolStripMenuItem->Click += new System::EventHandler(this, &IndividualWorkerSummary::shutDownLaterToolStripMenuItem_Click);
				// 
				// shutDownToolStripMenuItem
				// 
				this->shutDownToolStripMenuItem->Name = "shutDownToolStripMenuItem";
				this->shutDownToolStripMenuItem->Size = new System::Drawing::Size(287, 22);
				this->shutDownToolStripMenuItem->Text = "Delete worker now";
				this->shutDownToolStripMenuItem->Click += new System::EventHandler(this, &IndividualWorkerSummary::shutDownToolStripMenuItem_Click);
				// 
				// showProgressWindowToolStripMenuItem
				// 
				this->showProgressWindowToolStripMenuItem->Name = "showProgressWindowToolStripMenuItem";
				this->showProgressWindowToolStripMenuItem->Size = new System::Drawing::Size(287, 22);
				this->showProgressWindowToolStripMenuItem->Text = "Show progress window";
				this->showProgressWindowToolStripMenuItem->Click += new System::EventHandler(this, &IndividualWorkerSummary::showProgressWindowToolStripMenuItem_Click);
				// 
				// showQueueToolStripMenuItem
				// 
				this->showQueueToolStripMenuItem->Name = "showQueueToolStripMenuItem";
				this->showQueueToolStripMenuItem->Size = new System::Drawing::Size(287, 22);
				this->showQueueToolStripMenuItem->Text = "Show queue";
				this->showQueueToolStripMenuItem->Click += new System::EventHandler(this, &IndividualWorkerSummary::showQueueToolStripMenuItem_Click);
				// 
				// renameToolStripMenuItem
				// 
				this->renameToolStripMenuItem->Name = "renameToolStripMenuItem";
				this->renameToolStripMenuItem->Size = new System::Drawing::Size(287, 22);
				this->renameToolStripMenuItem->Text = "Rename worker";
				this->renameToolStripMenuItem->Click += new System::EventHandler(this, &IndividualWorkerSummary::renameToolStripMenuItem_Click);
				// 
				// toolStripSeparator1
				// 
				this->toolStripSeparator1->Name = "toolStripSeparator1";
				this->toolStripSeparator1->Size = new System::Drawing::Size(284, 6);
				// 
				// IndividualWorkerSummary
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->AutoSize = true;
				this->ContextMenuStrip = this->contextMenuStrip1;
				this->Controls->Add(this->workerNameAndJob);
				this->MaximumSize = new System::Drawing::Size(1000, 47);
				this->MinimumSize = new System::Drawing::Size(0, 47);
				this->Name = "IndividualWorkerSummary";
				this->Size = new System::Drawing::Size(292, 47);
				this->workerNameAndJob->ResumeLayout(false);
				this->contextMenuStrip1->ResumeLayout(false);
				this->ResumeLayout(false);

			}

			void IndividualWorkerSummary::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
