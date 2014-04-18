#pragma once

#include "core/gui/MeGUI.MainForm.h"
#include "core/util/VideoUtil.h"
#include "core/util/JobUtil.h"
#include "core/util/LogItem.h"
#include "core/util/Drives.h"
#include "SubtitleIndexJob.h"
#include "core/util/IFOparser.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/FileBar.h"
#include "core/gui/MeGUI.FileBar.h"
#include "core/gui/MeGUI.core.gui.HelpButton.h"
#include <string>
#include <vector>
#include <algorithm>

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
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;

namespace MeGUI
{
	class VobSubIndexWindow : public System::Windows::Forms::Form
	{
	private:
		bool dialogMode;
		bool configured;
		MainForm *mainForm;
		VideoUtil *vUtil;
		JobUtil *jobUtil;
		public:
		~VobSubIndexWindow()
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
		VobSubIndexWindow(MainForm *mainForm);

	protected:
		virtual void OnClosing(CancelEventArgs *e);
	private:
		void queueButton_Click(object *sender, EventArgs *e);
		void openVideo(const std::string &fileName);
		void checkIndexIO();

		SubtitleIndexJob *generateJob();
	public:
		void setConfig(const std::string &input, const std::string &output, bool indexAllTracks, std::vector<int> &trackIDs, int pgc);
		/// <summary>
		/// gets the index job created from the current configuration
		/// </summary>
		const SubtitleIndexJob &getJob() const;

	private:
		void input_FileSelected(FileBar *sender, FileBarEventArgs *args);

		void output_FileSelected(FileBar *sender, FileBarEventArgs *args);

		void chkShowAllStreams_CheckedChanged(object *sender, EventArgs *e);

		void pgc_ValueChanged(object *sender, EventArgs *e);


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


		System::Windows::Forms::GroupBox *inputGroupbox;
		System::Windows::Forms::Label *inputLabel;
		System::Windows::Forms::GroupBox *outputGroupbox;
		System::Windows::Forms::Label *nameLabel;
		System::Windows::Forms::GroupBox *subtitleGroupbox;
		System::Windows::Forms::RadioButton *demuxSelectedTracks;
		System::Windows::Forms::RadioButton *keepAllTracks;
		System::Windows::Forms::CheckBox *closeOnQueue;
		System::Windows::Forms::Button *queueButton;
		System::Windows::Forms::Label *pgcLabel;
		System::Windows::Forms::NumericUpDown *pgc;
		System::Windows::Forms::CheckedListBox *subtitleTracks;
		MeGUI::core::gui::HelpButton *helpButton1;
		FileBar *input;
		FileBar *output;
		System::Windows::Forms::CheckBox *chkShowAllStreams;


	private:
		void InitializeInstanceFields();
	};
}
