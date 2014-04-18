#pragma once

#include "core/details/MeGUI.JobControl.h"
#include "MeGUI.core.gui.IndividualWorkerSummary.h"
#include "core/details/JobWorker.h"
#include "JobWorker.h"
#include "MeGUI.core.gui.JobWorker.h"
#include "core/util/Util.h"
#include "core/util/LogItem.h"
#include <QString>
#include <QMap>

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
			class WorkerSummary : public System::Windows::Forms::Form
			{
				public:
				~WorkerSummary()
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
				WorkerSummary(JobControl *jobs);

			private:
				JobControl *jobs;
				std::QMap<QString, IndividualWorkerSummary*> displays;

			public:
				void Rename(const QString &workerName, const QString &newName);

				void RefreshInfo();

				void Add(JobWorker *w);

				void Remove(const QString &name);

			private:
				void WorkerSummary_VisibleChanged(QObject *sender, QEvent *e);

			public:
				void RefreshInfo(const QString &name);

			protected:
				virtual void OnClosing(CancelQEvent *e);

			private:
				void newWorkerToolStripMenuItem_Click(QObject *sender, QEvent *e);



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


				System::Windows::Forms::Panel *panel1;
				IndividualWorkerSummary *individualWorkerSummary3;
				IndividualWorkerSummary *individualWorkerSummary2;
				IndividualWorkerSummary *individualWorkerSummary1;
				System::Windows::Forms::ContextMenuStrip *contextMenuStrip1;
				System::Windows::Forms::ToolStripMenuItem *newWorkerToolStripMenuItem;



			private:
				void InitializeInstanceFields();
			};
		}
	}
}
