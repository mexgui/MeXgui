#pragma once

#include "core/gui/VideoPlayer.h"
#include "core/gui/MeGUI.MainForm.h"
#include "ChapterInfo.h"
#include "core/gui/MeGUI.core.gui.HelpButton.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include "core/util/FileUtil.h"
#include "core/util/Drives.h"
#include "core/util/LogItem.h"
#include "ChapterExtractor.h"
#include "DvdExtractor.h"
#include "MplsExtractor.h"
#include "TextExtractor.h"
#include "BlurayExtractor.h"
#include "core/util/Util.h"
#include "core/util/VistaStuff.h"
#include "core/plugins/interfaces/IPackage.h"
#include <string>
#include <vector>
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
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::util;

namespace MeGUI
{

	/// <summary>
	/// Summary description for ChapterCreator.
	/// </summary>
	class ChapterCreator : public System::Windows::Forms::Form
	{

	private:
//ORIGINAL LINE: private Chapter[] chapters;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		Chapter *chapters;
		std::string videoInput;
		VideoPlayer *player;
		int introEndFrame, creditsStartFrame;
		MainForm *mainForm;
		ChapterInfo *pgc;
		int intIndex;

		System::Windows::Forms::GroupBox *chaptersGroupbox;
		System::Windows::Forms::Button *addZoneButton;
		System::Windows::Forms::Button *clearZonesButton;
		System::Windows::Forms::Button *showVideoButton;
		System::Windows::Forms::Button *removeZoneButton;
		System::Windows::Forms::ColumnHeader *timecodeColumn;
		System::Windows::Forms::ColumnHeader *nameColumn;
		System::Windows::Forms::Label *startTimeLabel;
		System::Windows::Forms::Label *chapterNameLabel;
		System::Windows::Forms::Button *saveButton;
		System::Windows::Forms::TextBox *startTime;
		System::Windows::Forms::TextBox *chapterName;
		System::Windows::Forms::ListView *chapterListView;
		System::Windows::Forms::OpenFileDialog *openFileDialog;
		System::Windows::Forms::SaveFileDialog *saveFileDialog;
		System::Windows::Forms::GroupBox *gbInput;
		System::Windows::Forms::RadioButton *rbFromFile;
		System::Windows::Forms::RadioButton *rbFromDisk;
		System::Windows::Forms::Button *btInput;
		System::Windows::Forms::TextBox *input;
		MeGUI::core::gui::HelpButton *helpButton1;
		System::Windows::Forms::CheckBox *closeOnQueue;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container *components;
		public:
		~ChapterCreator()
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
		ChapterCreator(MainForm *mainForm);
	protected:
		virtual void OnClosing(CancelEventArgs *e);
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
	private:
		void Dispose(bool disposing);
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent();
		/// <summary>
		/// shows an array of chapters in the GUI
		/// </summary>
		/// <param name="chaps">the chapters to be shown</param>
		void showChapters(Chapter chaps[]);

		void FreshChapterView();

		void updateTimeLine();
		void removeZoneButton_Click(object *sender, System::EventArgs *e);

		void clearZonesButton_Click(object *sender, System::EventArgs *e);

		void chapterListView_SelectedIndexChanged(object *sender, System::EventArgs *e);

		void addZoneButton_Click(object *sender, System::EventArgs *e);
		void saveButton_Click(object *sender, System::EventArgs *e);

		void btInput_Click(object *sender, EventArgs *e);

		void showVideoButton_Click(object *sender, System::EventArgs *e);

		/// <summary>
		/// sets the video input to be used for a zone preview
		/// </summary>
	public:
		void setVideoInput(const std::string &value);
		/// <summary>
		/// gets / sets the start frame of the credits
		/// </summary>
		const int &getCreditsStartFrame() const;
		void setCreditsStartFrame(const int &value);
		/// <summary>
		/// gets / sets the end frame of the intro
		/// </summary>
		const int &getIntroEndFrame() const;
		void setIntroEndFrame(const int &value);
	private:
		void player_Closed(object *sender, EventArgs *e);

		void player_ChapterSet(int frameNumber);

		void ChapterCreator_Load(object *sender, EventArgs *e);

		void chapterName_TextChanged(object *sender, EventArgs *e);

	private:
		void InitializeInstanceFields();
	};
	class Chapter
	{
	public:
		std::string timecode;
		TimeSpan *StartTime;
		std::string name;

		//add-on
	private:
		TimeSpan *privateTime;
	public:
		const TimeSpan &getTime() const;
		void setTime(const TimeSpan &value);
	private:
		std::string privateName;
	public:
		const std::string &getName() const;
		void setName(const std::string &value);

		//public string Lang { get; set; }
		virtual std::string ToString();
	};

	class ChapterCreatorTool : public MeGUI::core::plugins::interfaces::ITool
	{


	public:
		const std::string &getName() const;

		void Run(MainForm *info);

		const Shortcut *getShortcuts() const;



		const std::string &getID() const;

	};
}
