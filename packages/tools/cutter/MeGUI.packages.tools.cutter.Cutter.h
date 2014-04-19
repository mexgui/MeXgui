#pragma once

#include "core/gui/VideoPlayer.h"
#include "core/util/FilmCutter.h"
#include "core/gui/MainForm.h"
#include "core/util/EnumProxy.h"
#include "core/util/LogItem.h"
#include "core/gui/HelpButton.h"
#include <QString>
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



using namespace MeXgui::core::util;

namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace cutter
			{
				class Cutter : public System::Windows::Forms::Form
				{
				private:
					bool cutsAdded;

					VideoPlayer *player;
					Cuts *cuts;
					QString scriptName;

					public:
					~Cutter()
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
					Cutter(MainForm *mainForm, const QString &scriptName);

				private:
					void openPreview(MainForm *mainForm);

					/// <summary>
					/// handler for the ZoneSet event
					/// updates zone start / end and adds the zone
					/// </summary>
					/// <param name="start"></param>
					/// <param name="end"></param>
					void player_ZoneSet(int start, int end);

					void addZoneButton_Click();

					bool addSelectedSection();

					void updateListView();

					void clearZonesButton_Click();

					void updateZoneButton_Click();

					void removeSelectedZones();


					void sections_ItemSelectionChanged(object *sender, ListViewItemSelectionChangedEventArgs *e);


					void removeZoneButton_Click();

				protected:
					virtual void OnClosing(CancelEventArgs *e);

				private:
					void closeButton_Click();

					void transitionStyle_SelectedIndexChanged();

					void addCutsToScript_Click();

					void saveCuts_Click();

					void doAllClose_Click();

					void sections_SelectedIndexChanged();


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


					System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel1;
					System::Windows::Forms::Button *addZoneButton;
					System::Windows::Forms::Button *clearZonesButton;
					System::Windows::Forms::Button *updateZoneButton;
					System::Windows::Forms::Button *removeZoneButton;
					System::Windows::Forms::Label *startFrameLabel;
					System::Windows::Forms::Label *endFrameLabel;
					System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;
					System::Windows::Forms::Label *label1;
					System::Windows::Forms::ComboBox *transitionStyle;
					System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel2;
					System::Windows::Forms::Button *closeButton;
					System::Windows::Forms::Button *saveCuts;
					System::Windows::Forms::NumericUpDown *startFrame;
					System::Windows::Forms::NumericUpDown *endFrame;
					System::Windows::Forms::Button *addCutsToScript;
					System::Windows::Forms::Label *avsScript;
					System::Windows::Forms::GroupBox *groupBox1;
					System::Windows::Forms::ListView *sections;
					System::Windows::Forms::ColumnHeader *columnHeader1;
					System::Windows::Forms::ColumnHeader *columnHeader2;
					System::Windows::Forms::Button *doAllClose;
					MeXgui::core::gui::HelpButton *helpButton1;

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
