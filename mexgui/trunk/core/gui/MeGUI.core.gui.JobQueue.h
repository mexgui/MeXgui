#pragma once

#include "core/details/TaggedJob.h"
#include "JobQueue.h"
#include "core/util/Util.h"
#include "core/util/LogItem.h"
#include "core/plugins/interfaces/Job.h"
#include "core/details/PackageSystem.h"
#include "core/util/GenericRegisterer.h"
#include "MeGUI.MainForm.h"
#include "core/util/FileUtil.h"
#include "core/util/VistaStuff.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class JobQueue : public UserControl
			{
			private:
				enum Direction
				{
					Up,
					Down
				};
		#if defined(CSC)
			private:
				static const std::string __Name;
		#else
				static const std::string __Name;
		#endif
				static System::Reflection::Assembly *const myAssembly;
				static Bitmap *const pauseImage;
				static Bitmap *const playImage;

				std::map<std::string, TaggedJob*> jobs;
				std::vector<ToolStripItem*> singleJobHandlers;
				std::vector<ToolStripItem*> multiJobHandlers;
				std::vector<Pair<ToolStripMenuItem*, MultiJobMenuGenerator>*> menuGenerators;
				MeGUI::core::gui::StartStopMode startStopMode;
				MeGUI::core::gui::PauseResumeMode pauseResumeMode;

				public:
				~JobQueue()
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
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
				const MeGUI::core::gui::StartStopMode &getStartStopMode() const;
				void setStartStopMode(const MeGUI::core::gui::StartStopMode &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
				const MeGUI::core::gui::PauseResumeMode &getPauseResumeMode() const;
				void setPauseResumeMode(const MeGUI::core::gui::PauseResumeMode &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
				const IEnumerable<TaggedJob*> &getJobList() const;

				void setJobList(const IEnumerable<TaggedJob*> &value);

				void queueJob(TaggedJob *j);

				void removeJobFromQueue(TaggedJob *job);



			private:
				void addItem(ToolStripMenuItem *item, const std::string &parent);

			public:
				void AddDynamicSubMenu(const std::string &name, const std::string &parent, MultiJobMenuGenerator gen);

				void AddMenuItem(const std::string &name, const std::string &parent);

				void AddMenuItem(const std::string &name, const std::string &parent, SingleJobHandler handler);

				void AddMenuItem(const std::string &name, const std::string &parent, MultiJobHandler handler);

				void AddButton(const std::string &name, EventHandler *handler);

				void SetStartStopButtonsTogether();



			private:
				int indexOf(TaggedJob *j);

			public:
				JobQueue();

				RequestJobDeleted RequestJobDeleted;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler AbortClicked;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler StartClicked;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler StopClicked;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler PauseClicked;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler ResumeClicked;

			private:
				std::vector<TaggedJob*> removeAllDependantJobsFromQueue(TaggedJob *job);

				void deleteJobButton_Click(object *sender, EventArgs *e);

				void processUserRequestToDelete(const std::string &name);

				void downButton_Click(object *sender, EventArgs *e);

				void upButton_Click(object *sender, EventArgs *e);

				/// <summary>
				/// moves the currently selected listviewitem up/down
				/// adapted from code by Less Smith @ KnotDot.Net
				/// </summary>
				/// <param name="lv">reference to ListView</param>
				/// <param name="moveUp">whether the currently selected item should be moved up or down</param>
				void MoveListViewItem(Direction d);

				/// <summary>
				/// swaps the contents of the two items
				/// </summary>
				/// <param name="a"></param>
				/// <param name="b"></param>
				void swapContents(ListViewItem *a, ListViewItem *b);

				/// <summary>
				/// Tells if the current selection can be moved in direction d.
				/// Checks:
				///     whether it's at the top / bottom
				///     if anything is actually selected
				///     whether the selection is contiguous
				/// </summary>
				/// <param name="d"></param>
				/// <returns></returns>
				bool isSelectionMovable(Direction d);

				/// <summary>
				/// Tells if the current selection can be edited.
				/// Checks:
				///     if one job actually selected
				///     whether the selected job is waiting or postponed
				/// </summary>
				/// <returns></returns>
				bool isSelectionEditable();

				/// <summary>
				/// Tells if the given list of indices is consecutive; if so, sets min and 
				/// max to the min and max indices
				/// </summary>
				/// <param name="indices"></param>
				/// <param name="min"></param>
				/// <param name="max"></param>
				bool consecutiveIndices(int indices[]);

				/// <summary>
				/// Updates the up/down buttons according to whether the selection CAN be moved up/down
				/// </summary>
				/// <param name="sender"></param>
				/// <param name="e"></param>
				void queueListView_ItemSelectionChanged(object *sender, ListViewItemSelectionChangedEventArgs *e);


				void editJobButton_Click(object *sender, EventArgs *e);

				/// <summary>
				/// Returns true if all selected jobs have the requested status
				/// </summary>
				/// <param name="status"></param>
				/// <returns></returns>
				bool AllJobsHaveStatus(JobStatus status);

				/// <summary>
				/// Returns true if any selected jobs have the requested status
				/// </summary>
				/// <param name="status"></param>
				/// <returns></returns>
				bool AnyJobsHaveStatus(JobStatus status);

				/// <summary>
				/// handles the doubleclick event for the listview
				/// changes the job status from waiting -> postponed to waiting
				/// from done -> waiting -> postponed -> waiting
				/// from error -> waiting -> postponed -> waiting
				/// </summary>
				/// <param name="sender"></param>
				/// <param name="e"></param>
				void queueListView_DoubleClick(object *sender, EventArgs *e);

				/// Sets the job status of the selected jobs to postponed.
				/// No selected jobs should currently be running.
				/// </summary>
				/// <param name="sender">This parameter is ignored</param>
				/// <param name="e">This parameter is ignored</param>
				void postponeMenuItem_Click(object *sender, EventArgs *e);

				/// <summary>
				/// Sets the jobs status of the selected jobs to waiting.
				/// No selected jobs should currently be running.
				/// </summary>
				/// <param name="sender">This parameter is ignored</param>
				/// <param name="e">This parameter is ignored</param>
				void waitingMenuItem_Click(object *sender, EventArgs *e);


				void queueContextMenu_Opened(object *sender, EventArgs *e);

				void abortButton_Click(object *sender, EventArgs *e);

				void startStopButton_Click(object *sender, EventArgs *e);

				void pauseButton_Click(object *sender, EventArgs *e);


			public:
				void refreshQueue();

			private:
				void stopButton_Click(object *sender, EventArgs *e);

			public:
				bool HasJob(TaggedJob *job);

			private:
				void queueListView_VisibleChanged(object *sender, EventArgs *e);

				void AbortMenuItem_Click(object *sender, EventArgs *e);

				void queueListView_KeyDown(object *sender, KeyEventArgs *e);


			public:
				void LoadComponentSettings();

				void SaveComponentSettings();


			private:
				void JobQueue_Load(object *sender, EventArgs *e);

				void queueListView_ColumnWidthChanged(object *sender, ColumnWidthChangedEventArgs *e);

				void markDependentJobs();

				void getAllDependantJobs(TaggedJob *job, std::vector<std::string> &oList);

				void outputFolderToolStripMenuItem_Click(object *sender, EventArgs *e);

				void outputFileToolStripMenuItem_Click(object *sender, EventArgs *e);

				void inputFolderToolStripMenuItem_Click(object *sender, EventArgs *e);

				void inputFileToolStripMenuItem_Click(object *sender, EventArgs *e);


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


				System::Windows::Forms::ListView *queueListView;
				System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel1;
				System::Windows::Forms::Button *startStopButton;
				System::Windows::Forms::Button *pauseButton;
				System::Windows::Forms::Button *upButton;
				System::Windows::Forms::Button *downButton;
				System::Windows::Forms::ContextMenuStrip *queueContextMenu;
				System::Windows::Forms::ToolStripMenuItem *DeleteMenuItem;
				System::Windows::Forms::ToolStripMenuItem *StatusMenuItem;
				System::Windows::Forms::ToolStripMenuItem *PostponedMenuItem;
				System::Windows::Forms::ToolStripMenuItem *WaitingMenuItem;
				System::Windows::Forms::ToolStripMenuItem *AbortMenuItem;
				System::Windows::Forms::ToolStripMenuItem *EditMenuItem;
				System::Windows::Forms::Button *stopButton;
				System::Windows::Forms::ColumnHeader *ownerHeader;
				System::Windows::Forms::ColumnHeader *jobColumHeader;
				System::Windows::Forms::ColumnHeader *inputColumnHeader;
				System::Windows::Forms::ColumnHeader *outputColumnHeader;
				System::Windows::Forms::ColumnHeader *codecHeader;
				System::Windows::Forms::ColumnHeader *modeHeader;
				System::Windows::Forms::ColumnHeader *statusColumn;
				System::Windows::Forms::ColumnHeader *startColumn;
				System::Windows::Forms::ColumnHeader *endColumn;
				System::Windows::Forms::ColumnHeader *fpsColumn;
				System::Windows::Forms::Button *editJobButton;
				System::Windows::Forms::ToolStripMenuItem *OpenMenuItem;
				System::Windows::Forms::ToolStripMenuItem *inputFileToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *inputFolderToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *outputFileToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *outputFolderToolStripMenuItem;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
