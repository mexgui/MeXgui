#pragma once

#include "core/details/video/VideoCodecSettings.h"
#include "MeGUI.MainForm.h"
#include "VideoPlayer.h"
#include <string>
#include "stringconverter.h"

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
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace MeGUI
{
	class ZonesControl : public UserControl
	{
		typedef void (*UpdateConfigGUI)(); // handles the events triggered when a new commandline is needed

		public:
		~ZonesControl()
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
		ZonesControl();
	private:
		MeGUI::MainForm *mainForm;

	public:
		const MeGUI::MainForm &getMainForm() const;
		void setMainForm(const MeGUI::MainForm &value);

	private:
		void updateGUI();
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event UpdateConfigGUI UpdateGUIEvent;
//ORIGINAL LINE: private Zone[] zones;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		Zone *zones;
		std::string input;
		VideoPlayer *player;
		int introEndFrame, creditsStartFrame;
		void zoneMode_SelectedIndexChanged(object *sender, System::EventArgs *e);

		void removeZoneButton_Click(object *sender, System::EventArgs *e);

		void clearZonesButton_Click(object *sender, System::EventArgs *e);
		void addZoneButton_Click(object *sender, System::EventArgs *e);
		/// <summary>
		/// shows the zones given as argument in the GUI
		/// first clears the listview of any items, then add one item after the other
		/// </summary>
		/// <param name="zones">the zones to be displayed</param>
		void showZones(Zone zones[]);

		void zoneListView_SelectedIndexChanged(object *sender, System::EventArgs *e);
		void updateZoneButton_Click(object *sender, System::EventArgs *e);
		/// <summary>
		/// handler for the ZoneSet event
		/// updates zone start / end and adds the zone
		/// </summary>
		/// <param name="start"></param>
		/// <param name="end"></param>
		void player_ZoneSet(int start, int end);
		/// <summary>
		/// handler for the WindowClosed event
		/// sets the player back to null so that the next time preview is pressed
		/// we open a new window
		/// </summary>
		void player_Closed(object *sender, EventArgs *e);
		void showVideoButton_Click(object *sender, System::EventArgs *e);
		/// <summary>
		/// Gets or sets the ending frame of the intro section
		/// </summary>
	public:
		const int &getIntroEndFrame() const;
		void setIntroEndFrame(const int &value);

		/// <summary>
		/// Gets or sets the starting frame of the credits.
		/// </summary>
		const int &getCreditsStartFrame() const;
		void setCreditsStartFrame(const int &value);

		/// <summary>
		/// Gets or sets the currently configured zones. Setting triggers a display update.
		/// </summary>
		const Zone *getZones() const;
		void setZones(Zone value[]);
		/// <summary>
		/// Sets the input video file, used for previewing
		/// </summary>
		void setInput(const std::string &value);
		const std::string &getInput() const;

		void closePlayer();

	private:
		void ZonesControl_Load(object *sender, EventArgs *e);


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


		System::Windows::Forms::GroupBox *zonesGroupbox;
		System::Windows::Forms::NumericUpDown *zoneModifier;
		System::Windows::Forms::Label *modifierLabel;
		System::Windows::Forms::Label *zoneLabel;
		System::Windows::Forms::ComboBox *zoneMode;
		System::Windows::Forms::TextBox *endFrame;
		System::Windows::Forms::TextBox *startFrame;
		System::Windows::Forms::ListView *zoneListView;
		System::Windows::Forms::ColumnHeader *startFrameColumn;
		System::Windows::Forms::ColumnHeader *endFrameColumn;
		System::Windows::Forms::ColumnHeader *modeColumn;
		System::Windows::Forms::ColumnHeader *modifierColumn;
		System::Windows::Forms::Label *startFrameLabel;
		System::Windows::Forms::Label *endFrameLabel;
		System::Windows::Forms::Button *addZoneButton;
		System::Windows::Forms::Button *clearZonesButton;
		System::Windows::Forms::Button *updateZoneButton;
		System::Windows::Forms::Button *showVideoButton;
		System::Windows::Forms::Button *removeZoneButton;
		System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;
		System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel1;

	private:
		void InitializeInstanceFields();
	};
}
