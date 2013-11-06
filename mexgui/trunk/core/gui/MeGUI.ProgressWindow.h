#pragma once

#include "ProgressTaskbar.h"
#include "core/details/StatusUpdate.h"
#include "core/util/Util.h"
#include "core/plugins/interfaces/Job.h"
#include "MeGUI.core.gui.HelpButton.h"
#include <string>
#include <stdexcept>

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


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::util;

namespace MeGUI
{
	class ProgressWindow : public System::Windows::Forms::Form
	{
	private:
		bool isUserClosing;

		/// <summary>
		/// default constructor, initializes the GUI components
		/// </summary>
		public:
		~ProgressWindow()
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
		ProgressWindow();
		/// <summary>
		/// handles the onclosing event
		/// ensures that if the user closed the window, it will only be hidden
		/// whereas if the system closed it, it is allowed to close
		/// </summary>
		/// <param name="e"></param>
	protected:
		virtual void OnClosing(CancelEventArgs *e);

		/// <summary>
		/// catches the StatusUpdate event fired from Form1 and updates the GUI accordingly
		/// </summary>
		/// <param name="su"></param>
	public:
		void UpdateStatus(StatusUpdate *su);

		/// <summary>
		/// calculates the remaining encoding time from the elapsed timespan and the percentage the job is done
		/// </summary>
		/// <param name="span">timespan elapsed since the start of the job</param>
		/// <param name="percentageDone">percentage the job is currently done</param>
		/// <returns>presentable string in hh:mm:ss format</returns>
	private:
		std::string getTimeString(TimeSpan *span, decimal percentageDone);

		bool isSettingPriority;
		/// <summary>
		/// sets the priority
		/// </summary>
		/// <param name="priority"></param>
	public:
		void setPriority(ProcessPriority priority);
		/// <summary>
		///  handles the abort button
		///  fires an Abort() event to the main GUI, which looks up the encoder and makes it stop
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
	private:
		void abortButton_Click(object *sender, System::EventArgs *e);
		/// <summary>Handles changes in the priority dropdwon</summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void priority_SelectedIndexChanged(object *sender, System::EventArgs *e);

		bool WarnPriority(ProcessPriority priority);
		/// <summary>
		/// gets / sets whether the user closed this window or if the system is closing it
		/// </summary>
	public:
		const bool &getIsUserAbort() const;
		void setIsUserAbort(const bool &value);


		/// <summary>
		/// Required designer variable.
		/// </summary>
	private:
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

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event AbortCallback Abort; // event fired if the abort button has been pressed
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event PriorityChangedCallback PriorityChanged; // event fired if the priority dropdown has changed
		System::Windows::Forms::Label *currentVideoFrameLabel;
		System::Windows::Forms::TextBox *currentVideoFrame;
		System::Windows::Forms::GroupBox *groupBox1;
		System::Windows::Forms::Button *abortButton;
		System::Windows::Forms::Label *videoDataLabel;
		System::Windows::Forms::TextBox *videoData;
		System::Windows::Forms::Label *fpsLabel;
		System::Windows::Forms::TextBox *fps;
		System::Windows::Forms::Label *timeElapsedLabel;
		System::Windows::Forms::TextBox *timeElapsed;
		System::Windows::Forms::Label *totalTimeLabel;
		System::Windows::Forms::TextBox *totalTime;
		System::Windows::Forms::Label *progressLabel;
		System::Windows::Forms::ProgressBar *progress;
		System::Windows::Forms::Label *priorityLabel;
		System::Windows::Forms::ComboBox *priority;
		System::Windows::Forms::TextBox *positionInClip;
		System::Windows::Forms::Label *currentPositionLabel;
		System::Windows::Forms::StatusStrip *statusStrip1;
		System::Windows::Forms::ToolStripStatusLabel *statusLabel;
		MeGUI::core::gui::HelpButton *helpButton1;
		ITaskbarList3 *taskbarProgress;
		System::Windows::Forms::ToolStripStatusLabel *jobNameLabel;

	private:
		void InitializeInstanceFields();
	};
}
