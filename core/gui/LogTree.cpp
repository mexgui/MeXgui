#include "MeGUI.core.gui.LogTree.h"




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

			LogTree::LogTree() : Log(new LogItem("Log", ImageType::NoImage))
			{
				InitializeInstanceFields();
				InitializeComponent();

				ImageList *i = new ImageList();
				i->Images->Add(System::Drawing::SystemIcons::Error);
				i->Images->Add(System::Drawing::SystemIcons::Warning);
				i->Images->Add(System::Drawing::SystemIcons::Information);
				treeView->ImageList = i;

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Log->SubItemAdded += delegate(object sender, QEvent<LogItem*> args)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Util::ThreadSafeRun(treeView, delegate
					{
						treeView->Nodes->Add(register_Renamed(args::Data));
					}
				   );
				};
			}

			TreeNode *LogTree::register_Renamed(LogItem *log)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				QVector<TreeNode*> subNodes = log->getSubEvents().ConvertAll<TreeNode*>(delegate(LogItem e)
				{
					return register_Renamed(e);
				}
			   );

				TreeNode *node = new TreeNode(log->getText(), static_cast<int>(log->getType()), static_cast<int>(log->getType()), subNodes.ToArray());
				node->Tag = log;

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				log->SubItemAdded += delegate(object sender, QEvent<LogItem*> args)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Util::ThreadSafeRun(treeView, delegate
					{
						node->Nodes->Add(register_Renamed(args::Data));
					}
				   );
				};

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				log->TypeChanged += delegate(object sender, QEvent<ImageType> args)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Util::ThreadSafeRun(treeView, delegate
					{
						node->SelectedImageIndex = node->ImageIndex = static_cast<int>(args::Data);
					}
				   );
				};
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				log->Expanded += delegate(object sender, QEvent e)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Util::ThreadSafeRun(treeView, delegate
					{
						node->Expand();
					}
				   );
				};
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				log->Collapsed += delegate(object sender, QEvent e)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Util::ThreadSafeRun(treeView, delegate
					{
						node->Collapse();
					}
				   );
				};

				return node;
			}

			void LogTree::ofIndividualNodeToolStripMenuItem_Click(QObject *sender, QEvent *e)
			{
				show(getselectedLogItem(), false);
			}

			void LogTree::ofBranchToolStripMenuItem_Click(QObject *sender, QEvent *e)
			{
				show(getselectedLogItem(), true);
			}

			void LogTree::editLog_Click(QObject *sender, QEvent *e)
			{
				show(Log, true);
			}

			const MeGUI::core::util::LogItem &LogTree::getselectedLogItem() const
			{
				if (treeView->SelectedNode == 0)
					return 0;

				return (dynamic_cast<LogItem*>(treeView->SelectedNode->Tag));
			}

			void LogTree::show(LogItem *l, bool subnodes)
			{
				if (l == 0)
					return;

				TextViewer *t = new TextViewer();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				t->setContents(l->ToString(subnodes));
				t->setWrap(false);
				t->show();
			}

			void LogTree::saveLog_Click(QObject *sender, QEvent *e)
			{
				save(Log);
			}

			void LogTree::saveBranch_Click(QObject *sender, QEvent *e)
			{
				LogItem *i = getselectedLogItem();
				if (i == 0)
				{
					MessageBox::Show("No log branch selected", "Can't save file", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}
				save(i);
			}

			void LogTree::save(LogItem *i)
			{
				if (saveDialog->show() != DialogResult::OK)
					return;

				try
				{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					File::WriteAllText(saveDialog->FileName, i->ToString());
					MessageBox::Show("File saved successfully", "Success", MessageBoxButtons::OK, MessageBoxIcon::None);
				}
				catch (IOException *ie)
				{
					MessageBox::Show("Error saving file: " + ie->Message, "Error saving file", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}

			}

			void LogTree::expandOrCollapseAll(LogItem *i, bool expand)
			{
				 if (expand)
					 i->Expand();
				 else
					 i->Collapse();

				 for (QVector<LogItem*>::const_iterator i2 = i->getSubEvents().begin(); i2 != i->getSubEvents().end(); ++i2)
					 expandOrCollapseAll(*i2, expand);
			}

			void LogTree::expandAll(LogItem *i)
			{
				expandOrCollapseAll(i, true);
			}

			void LogTree::collapseAll(LogItem *i)
			{
				expandOrCollapseAll(i, false);
			}

			void LogTree::expandLog_Click(QObject *sender, QEvent *e)
			{
				expandAll(Log);
			}

			void LogTree::expandBranch_Click(QObject *sender, QEvent *e)
			{
				expandAll(getselectedLogItem());
			}

			void LogTree::collapseLog_Click(QObject *sender, QEvent *e)
			{
				collapseAll(Log);
			}

			void LogTree::collapseBranch_Click(QObject *sender, QEvent *e)
			{
				collapseAll(getselectedLogItem());
			}

			void LogTree::LogTree_Load(QObject *sender, QEvent *e)
			{

				if (VistaStuff::getIsVistaOrNot())
				{
					VistaStuff::SetWindowTheme(treeView->Handle, "explorer", 0);
				}
			}

			void LogTree::resetOverlayIcon_Click(QObject *sender, QEvent *e)
			{
			   MainForm::Instance->setOverlayIcon(0);
			}

			void LogTree::contextMenu_Opening(QObject *sender, CancelQEvent *e)
			{
				if (MainForm::Instance->getIsOverlayIconActive())
					resetOverlayIcon->Visible = true;
				else
					resetOverlayIcon->Visible = false;
			}

			void LogTree::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				UserControl::Dispose(disposing);
			}

			void LogTree::InitializeComponent()
			{
				this->components = new System::ComponentModel::Container();
				this->treeView = new System::Windows::Forms::TreeView();
				this->contextMenu = new System::Windows::Forms::ContextMenuStrip(this->components);
				this->editTextToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->editIndividualNode = new System::Windows::Forms::ToolStripMenuItem();
				this->editBranch = new System::Windows::Forms::ToolStripMenuItem();
				this->editLog = new System::Windows::Forms::ToolStripMenuItem();
				this->saveToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->saveBranch = new System::Windows::Forms::ToolStripMenuItem();
				this->saveLog = new System::Windows::Forms::ToolStripMenuItem();
				this->expandAllSubitemsToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->expandLog = new System::Windows::Forms::ToolStripMenuItem();
				this->expandBranch = new System::Windows::Forms::ToolStripMenuItem();
				this->collapseAllSubitemsToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->collapseLog = new System::Windows::Forms::ToolStripMenuItem();
				this->collapseBranch = new System::Windows::Forms::ToolStripMenuItem();
				this->saveDialog = new System::Windows::Forms::SaveFileDialog();
				this->resetOverlayIcon = new System::Windows::Forms::ToolStripMenuItem();
				this->contextMenu->SuspendLayout();
				this->SuspendLayout();
				// 
				// treeView
				// 
				this->treeView->ContextMenuStrip = this->contextMenu;
				this->treeView->Dock = System::Windows::Forms::DockStyle::Fill;
				this->treeView->Location = new System::Drawing::Point(0, 0);
				this->treeView->Name = "treeView";
				this->treeView->Size = new System::Drawing::Size(596, 478);
				this->treeView->TabIndex = 0;
				// 
				// contextMenu
				// 
				this->contextMenu->Items->AddRange(new System::Windows::Forms::ToolStripItem[5] {this->editTextToolStripMenuItem, this->saveToolStripMenuItem, this->expandAllSubitemsToolStripMenuItem, this->collapseAllSubitemsToolStripMenuItem, this->resetOverlayIcon});
				this->contextMenu->Name = "contextMenuStrip1";
				this->contextMenu->Size = new System::Drawing::Size(200, 136);
				this->contextMenu->Opening += new System::ComponentModel::CancelEventHandler(this, &LogTree::contextMenu_Opening);
				// 
				// editTextToolStripMenuItem
				// 
				this->editTextToolStripMenuItem->DropDownItems->AddRange(new System::Windows::Forms::ToolStripItem[3] {this->editIndividualNode, this->editBranch, this->editLog});
				this->editTextToolStripMenuItem->Name = "editTextToolStripMenuItem";
				this->editTextToolStripMenuItem->Size = new System::Drawing::Size(185, 22);
				this->editTextToolStripMenuItem->Text = "Edit text";
				// 
				// editIndividualNode
				// 
				this->editIndividualNode->Name = "editIndividualNode";
				this->editIndividualNode->Size = new System::Drawing::Size(111, 22);
				this->editIndividualNode->Text = "node";
				this->editIndividualNode->Click += new System::EventHandler(this, &LogTree::ofIndividualNodeToolStripMenuItem_Click);
				// 
				// editBranch
				// 
				this->editBranch->Name = "editBranch";
				this->editBranch->Size = new System::Drawing::Size(111, 22);
				this->editBranch->Text = "branch";
				this->editBranch->Click += new System::EventHandler(this, &LogTree::ofBranchToolStripMenuItem_Click);
				// 
				// editLog
				// 
				this->editLog->Name = "editLog";
				this->editLog->Size = new System::Drawing::Size(111, 22);
				this->editLog->Text = "log";
				this->editLog->Click += new System::EventHandler(this, &LogTree::editLog_Click);
				// 
				// saveToolStripMenuItem
				// 
				this->saveToolStripMenuItem->DropDownItems->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->saveBranch, this->saveLog});
				this->saveToolStripMenuItem->Name = "saveToolStripMenuItem";
				this->saveToolStripMenuItem->Size = new System::Drawing::Size(185, 22);
				this->saveToolStripMenuItem->Text = "Save";
				// 
				// saveBranch
				// 
				this->saveBranch->Name = "saveBranch";
				this->saveBranch->Size = new System::Drawing::Size(111, 22);
				this->saveBranch->Text = "branch";
				this->saveBranch->Click += new System::EventHandler(this, &LogTree::saveBranch_Click);
				// 
				// saveLog
				// 
				this->saveLog->Name = "saveLog";
				this->saveLog->Size = new System::Drawing::Size(111, 22);
				this->saveLog->Text = "log";
				this->saveLog->Click += new System::EventHandler(this, &LogTree::saveLog_Click);
				// 
				// expandAllSubitemsToolStripMenuItem
				// 
				this->expandAllSubitemsToolStripMenuItem->DropDownItems->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->expandLog, this->expandBranch});
				this->expandAllSubitemsToolStripMenuItem->Name = "expandAllSubitemsToolStripMenuItem";
				this->expandAllSubitemsToolStripMenuItem->Size = new System::Drawing::Size(185, 22);
				this->expandAllSubitemsToolStripMenuItem->Text = "Expand all subitems";
				// 
				// expandLog
				// 
				this->expandLog->Name = "expandLog";
				this->expandLog->Size = new System::Drawing::Size(125, 22);
				this->expandLog->Text = "of log";
				this->expandLog->Click += new System::EventHandler(this, &LogTree::expandLog_Click);
				// 
				// expandBranch
				// 
				this->expandBranch->Name = "expandBranch";
				this->expandBranch->Size = new System::Drawing::Size(125, 22);
				this->expandBranch->Text = "of branch";
				this->expandBranch->Click += new System::EventHandler(this, &LogTree::expandBranch_Click);
				// 
				// collapseAllSubitemsToolStripMenuItem
				// 
				this->collapseAllSubitemsToolStripMenuItem->DropDownItems->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->collapseLog, this->collapseBranch});
				this->collapseAllSubitemsToolStripMenuItem->Name = "collapseAllSubitemsToolStripMenuItem";
				this->collapseAllSubitemsToolStripMenuItem->Size = new System::Drawing::Size(185, 22);
				this->collapseAllSubitemsToolStripMenuItem->Text = "Collapse all subitems";
				// 
				// collapseLog
				// 
				this->collapseLog->Name = "collapseLog";
				this->collapseLog->Size = new System::Drawing::Size(125, 22);
				this->collapseLog->Text = "of log";
				this->collapseLog->Click += new System::EventHandler(this, &LogTree::collapseLog_Click);
				// 
				// collapseBranch
				// 
				this->collapseBranch->Name = "collapseBranch";
				this->collapseBranch->Size = new System::Drawing::Size(125, 22);
				this->collapseBranch->Text = "of branch";
				this->collapseBranch->Click += new System::EventHandler(this, &LogTree::collapseBranch_Click);
				// 
				// saveDialog
				// 
				this->saveDialog->Filter = "Log files (*.log)|*.log|All files (*.*)|*.*";
				this->saveDialog->FilterIndex = 0;
				this->saveDialog->Title = "Select output file";
				// 
				// resetOverlayIcon
				// 
				this->resetOverlayIcon->Name = "resetOverlayIcon";
				this->resetOverlayIcon->Size = new System::Drawing::Size(199, 22);
				this->resetOverlayIcon->Text = "Reset Overlay Error Icon";
				this->resetOverlayIcon->ToolTipText = "Removes the applied error or warning icon from the taskbar";
				this->resetOverlayIcon->Click += new System::EventHandler(this, &LogTree::resetOverlayIcon_Click);
				// 
				// LogTree
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->Controls->Add(this->treeView);
				this->Name = "LogTree";
				this->Size = new System::Drawing::Size(596, 478);
				this->Load += new System::EventHandler(this, &LogTree::LogTree_Load);
				this->contextMenu->ResumeLayout(false);
				this->ResumeLayout(false);

			}

			void LogTree::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
