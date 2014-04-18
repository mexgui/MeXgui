#pragma once

#include "core/details/JobWorker.h"
#include "JobWorker.h"
#include "MeGUI.core.gui.JobWorker.h"
#include "core/util/LogItem.h"
#include "JobWorkerWindow.h"
#include <QString>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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








namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class IndividualWorkerSummary : public UserControl
			{
			private:
				JobWorker *w;

				public:
				~IndividualWorkerSummary()
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
				IndividualWorkerSummary();

				void setWorker(const JobWorker &value);

				void RefreshInfo();

			private:
				void startEncodingToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void abortToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void renameToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void stopToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void shutDownToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void shutDownLaterToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void showProgressWindowToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void showQueueToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void contextMenuStrip1_Opening(QObject *sender, CancelQEvent *e);


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


				System::Windows::Forms::GroupBox *workerNameAndJob;
				System::Windows::Forms::ProgressBar *progressBar1;
				System::Windows::Forms::ContextMenuStrip *contextMenuStrip1;
				System::Windows::Forms::ToolStripMenuItem *startEncodingToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *abortToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *renameToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *stopToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *shutDownToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *showProgressWindowToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *showQueueToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *shutDownLaterToolStripMenuItem;
				System::Windows::Forms::ToolStripSeparator *toolStripSeparator1;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
