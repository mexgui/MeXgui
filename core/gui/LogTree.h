#pragma once

#include "core/util/LogItem.h"
#include "core/util/Util.h"
#include "MeGUI.core.gui.TextViewer.h"
#include "core/util/VistaStuff.h"
#include "MeGUI.MainForm.h"
#include <QVector>

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************




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
			class LogTree : public UserControl
			{
				public:
				~LogTree()
				{
					this->Dispose(true);
				}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:
				void Finalize()
				{
					this->Dispose(false);
				}

			public:
				LogTree();


				LogItem *const Log;


			private:
				TreeNode *register_Renamed(LogItem *log);

				void ofIndividualNodeToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void ofBranchToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void editLog_Click(QObject *sender, QEvent *e);

				const LogItem &getselectedLogItem() const;

				void show(LogItem *l, bool subnodes);

				void saveLog_Click(QObject *sender, QEvent *e);

				void saveBranch_Click(QObject *sender, QEvent *e);

				void save(LogItem *i);

			   void expandOrCollapseAll(LogItem *i, bool expand);

				void expandAll(LogItem *i);
				void collapseAll(LogItem *i);

				void expandLog_Click(QObject *sender, QEvent *e);

				void expandBranch_Click(QObject *sender, QEvent *e);

				void collapseLog_Click(QObject *sender, QEvent *e);

				void collapseBranch_Click(QObject *sender, QEvent *e);

				void LogTree_Load(QObject *sender, QEvent *e);

				void resetOverlayIcon_Click(QObject *sender, QEvent *e);

				void contextMenu_Opening(QObject *sender, CancelQEvent *e);


				/// <summary> 
				/// Required designer variable.
				/// </summary>
				System::ComponentModel::IContainer *components;

				/// <summary> 
				/// Clean up any resources being used.
				/// </summary>
				/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
				void Dispose(bool disposing);


				/// <summary> 
				/// Required method for Designer support - do not modify 
				/// the contents of this method with the code editor.
				/// </summary>
				void InitializeComponent();


				System::Windows::Forms::TreeView *treeView;
				System::Windows::Forms::ContextMenuStrip *contextMenu;
				System::Windows::Forms::ToolStripMenuItem *editTextToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *editIndividualNode;
				System::Windows::Forms::ToolStripMenuItem *editBranch;
				System::Windows::Forms::SaveFileDialog *saveDialog;
				System::Windows::Forms::ToolStripMenuItem *saveToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *saveBranch;
				System::Windows::Forms::ToolStripMenuItem *saveLog;
				System::Windows::Forms::ToolStripMenuItem *editLog;
				System::Windows::Forms::ToolStripMenuItem *expandAllSubitemsToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *expandLog;
				System::Windows::Forms::ToolStripMenuItem *expandBranch;
				System::Windows::Forms::ToolStripMenuItem *collapseAllSubitemsToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *collapseLog;
				System::Windows::Forms::ToolStripMenuItem *collapseBranch;
				System::Windows::Forms::ToolStripMenuItem *resetOverlayIcon;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
