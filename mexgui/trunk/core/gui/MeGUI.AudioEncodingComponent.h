#pragma once

#include "MeGUI.core.gui.AudioEncodingTab.h"
#include "MeGUI.MainForm.h"
#include "packages/audio/AudioJob.h"
#include "core/util/LogItem.h"
#include <string>
#include <vector>

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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details::video;
using namespace MeGUI::core::gui;
using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{
	class AudioEncodingComponent : public UserControl
	{
	private:
		std::vector<AudioEncodingTab*> tabs;

		public:
		~AudioEncodingComponent()
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
		AudioEncodingComponent();

		void AddTab();

		/// <summary>
		/// returns the audio streams registered
		/// </summary>
		const std::vector<AudioJob*> &getAudioStreams() const;

		/// <summary>
		/// Returns null if all audio configurations are valid or incomplete. Returns
		/// an error message if any audio configuration issues a serious (not just incomplete)
		/// error message
		/// </summary>
		/// <returns></returns>
		std::string verifyAudioSettings();

		void Reset();

//ORIGINAL LINE: internal void openAudioFile(params string[] files)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		void openAudioFile(...);

	private:
		void newTrackToolStripMenuItem_Click(object *sender, EventArgs *e);

		void removeTrackToolStripMenuItem_Click(object *sender, EventArgs *e);

		void RemoveTab();

		void contextMenuStrip1_Opening(object *sender, CancelEventArgs *e);


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


		System::Windows::Forms::GroupBox *groupBox1;
		System::Windows::Forms::TabControl *tabControl1;
		System::Windows::Forms::TabPage *tabPage1;
		MeGUI::core::gui::AudioEncodingTab *audioEncodingTab1;
		System::Windows::Forms::ContextMenuStrip *contextMenuStrip1;
		System::Windows::Forms::ToolStripMenuItem *newTrackToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem *removeTrackToolStripMenuItem;



	private:
		void InitializeInstanceFields();
	};
}
