#include "MeGUI.core.gui.WorkerSummary.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


using namespace MeGUI::core::util;
using namespace MeGUI::core::details;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			WorkerSummary::WorkerSummary(JobControl *jobs)
			{
				InitializeInstanceFields();
				InitializeComponent();
				panel1->Controls->Clear(); // they're just there for the designer
				panel1->Dock = DockStyle->Top;
				int width = panel1->Width;
				panel1->Dock = DockStyle::None;
				panel1->Height = 0;
				panel1->Width = width;
				panel1->Location = new Point(0, 0);
				panel1->Anchor = AnchorStyles->Top | AnchorStyles->Left | AnchorStyles::Right;
				this->jobs = jobs;
			}

			void WorkerSummary::Rename(const QString &workerName, const QString &newName)
			{
				IndividualWorkerSummary *i = displays[workerName];
				displays.erase(workerName);
				displays[newName] = i;
			}

			void WorkerSummary::RefreshInfo()
			{
				if (InvokeRequired)
				{
					Invoke(new MethodInvoker(RefreshInfo));
					return;
				}
				if (!Visible)
					return;
				for (std::QMap<QString, IndividualWorkerSummary*>::const_iterator i = displays.begin(); i != displays.end(); ++i)
					i->second->RefreshInfo();
			}

			void WorkerSummary::Add(JobWorker *w)
			{
				IndividualWorkerSummary *i = new IndividualWorkerSummary();
				i->setWorker(w);
				i->Dock = DockStyle::Bottom;
				panel1->Controls->Add(i);
				displays[w->getName()] = i;
				RefreshInfo();
			}

			void WorkerSummary::Remove(const QString &name)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Util::ThreadSafeRun(panel1, delegate
				{
					panel1->Controls->Remove(displays[name]);
				}
			   );
				displays.erase(name);
				RefreshInfo();
			}

			void WorkerSummary::WorkerSummary_VisibleChanged(QObject *sender, QEvent *e)
			{
				if (Visible)
					RefreshInfo();
			}

			void WorkerSummary::RefreshInfo(const QString &name)
			{
				if (InvokeRequired)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Invoke(new MethodInvoker(delegate
					{
						RefreshInfo(name);
					}
				   ));
					return;
				}
				if (Visible && displays.find(name) != displays.end())
					displays[name]->RefreshInfo();
			}

			void WorkerSummary::OnClosing(CancelQEvent *e)
			{
				e->Cancel = true;
				Hide();
			}

			void WorkerSummary::newWorkerToolStripMenuItem_Click(QObject *sender, QEvent *e)
			{
				jobs->RequestNewWorker();
			}

			void WorkerSummary::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				System::Windows::Forms::Form::Dispose(disposing);
			}

			void WorkerSummary::InitializeComponent()
			{
				this->components = new System::ComponentModel::Container();
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(WorkerSummary::typeid);
				this->panel1 = new System::Windows::Forms::Panel();
				this->individualWorkerSummary3 = new MeGUI::core::gui::IndividualWorkerSummary();
				this->individualWorkerSummary2 = new MeGUI::core::gui::IndividualWorkerSummary();
				this->individualWorkerSummary1 = new MeGUI::core::gui::IndividualWorkerSummary();
				this->contextMenuStrip1 = new System::Windows::Forms::ContextMenuStrip(this->components);
				this->newWorkerToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->panel1->SuspendLayout();
				this->contextMenuStrip1->SuspendLayout();
				this->SuspendLayout();
				// 
				// panel1
				// 
				this->panel1->AutoSize = true;
				this->panel1->Controls->Add(this->individualWorkerSummary3);
				this->panel1->Controls->Add(this->individualWorkerSummary2);
				this->panel1->Controls->Add(this->individualWorkerSummary1);
				this->panel1->Location = new System::Drawing::Point(0, 4);
				this->panel1->Name = "panel1";
				this->panel1->Padding = new System::Windows::Forms::Padding(3);
				this->panel1->Size = new System::Drawing::Size(348, 147);
				this->panel1->TabIndex = 0;
				// 
				// individualWorkerSummary3
				// 
				this->individualWorkerSummary3->AutoSize = true;
				this->individualWorkerSummary3->Dock = System::Windows::Forms::DockStyle::Top;
				this->individualWorkerSummary3->Location = new System::Drawing::Point(3, 97);
				this->individualWorkerSummary3->MaximumSize = new System::Drawing::Size(1000, 47);
				this->individualWorkerSummary3->MinimumSize = new System::Drawing::Size(200, 47);
				this->individualWorkerSummary3->Name = "individualWorkerSummary3";
				this->individualWorkerSummary3->Size = new System::Drawing::Size(342, 47);
				this->individualWorkerSummary3->TabIndex = 2;
				// 
				// individualWorkerSummary2
				// 
				this->individualWorkerSummary2->AutoSize = true;
				this->individualWorkerSummary2->Dock = System::Windows::Forms::DockStyle::Top;
				this->individualWorkerSummary2->Location = new System::Drawing::Point(3, 50);
				this->individualWorkerSummary2->MaximumSize = new System::Drawing::Size(1000, 47);
				this->individualWorkerSummary2->MinimumSize = new System::Drawing::Size(200, 47);
				this->individualWorkerSummary2->Name = "individualWorkerSummary2";
				this->individualWorkerSummary2->Size = new System::Drawing::Size(342, 47);
				this->individualWorkerSummary2->TabIndex = 1;
				// 
				// individualWorkerSummary1
				// 
				this->individualWorkerSummary1->AutoSize = true;
				this->individualWorkerSummary1->Dock = System::Windows::Forms::DockStyle::Top;
				this->individualWorkerSummary1->Location = new System::Drawing::Point(3, 3);
				this->individualWorkerSummary1->MaximumSize = new System::Drawing::Size(1000, 47);
				this->individualWorkerSummary1->MinimumSize = new System::Drawing::Size(200, 47);
				this->individualWorkerSummary1->Name = "individualWorkerSummary1";
				this->individualWorkerSummary1->Size = new System::Drawing::Size(342, 47);
				this->individualWorkerSummary1->TabIndex = 0;
				// 
				// contextMenuStrip1
				// 
				this->contextMenuStrip1->Items->AddRange(new System::Windows::Forms::ToolStripItem[1] {this->newWorkerToolStripMenuItem});
				this->contextMenuStrip1->Name = "contextMenuStrip1";
				this->contextMenuStrip1->Size = new System::Drawing::Size(138, 26);
				// 
				// newWorkerToolStripMenuItem
				// 
				this->newWorkerToolStripMenuItem->Name = "newWorkerToolStripMenuItem";
				this->newWorkerToolStripMenuItem->Size = new System::Drawing::Size(137, 22);
				this->newWorkerToolStripMenuItem->Text = "New worker";
				this->newWorkerToolStripMenuItem->Click += new System::EventHandler(this, &WorkerSummary::newWorkerToolStripMenuItem_Click);
				// 
				// WorkerSummary
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->AutoScroll = true;
				this->ClientSize = new System::Drawing::Size(352, 155);
				this->ContextMenuStrip = this->contextMenuStrip1;
				this->Controls->Add(this->panel1);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->Name = "WorkerSummary";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
				this->Text = "WorkerSummary";
				this->VisibleChanged += new System::EventHandler(this, &WorkerSummary::WorkerSummary_VisibleChanged);
				this->panel1->ResumeLayout(false);
				this->panel1->PerformLayout();
				this->contextMenuStrip1->ResumeLayout(false);
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void WorkerSummary::InitializeInstanceFields()
			{
				displays = std::QMap<QString, IndividualWorkerSummary*>();
				delete components;
			}
		}
	}
}
