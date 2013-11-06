#pragma once

#include "core/details/ProfileManager.h"
#include "AviSynthSettings.h"
#include "ScriptServer.h"
#include "core/details/MeGUISettings.h"
#include "MeGUI.Properties.Settings.h"
#include "AviSynthWindow.h"
#include "core/util/EnumProxy.h"
#include "core/util/LogItem.h"
#include "core/gui/FileBar.h"
#include "core/gui/MeGUI.FileBar.h"
#include <string>

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
//using namespace System::Windows::Forms;


namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class AviSynthProfileConfigPanel : public UserControl, Editable<AviSynthSettings*>
			{
				public:
				~AviSynthProfileConfigPanel()
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
				AviSynthProfileConfigPanel();


				const AviSynthSettings &getSettings() const;
				void setSettings(const AviSynthSettings &value);


			private:
				void signalAR_CheckedChanged(object *sender, EventArgs *e);

				void insert_Click(object *sender, EventArgs *e);

				void dllBar_FileSelected(FileBar *sender, FileBarEventArgs *args);

				void noiseFilter_CheckedChanged(object *sender, EventArgs *e);

				void resize_CheckedChanged(object *sender, EventArgs *e);


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


				System::Windows::Forms::TabControl *tabControl1;
				System::Windows::Forms::TabPage *templatePage;
				System::Windows::Forms::Button *insertCrop;
				System::Windows::Forms::Button *insertInput;
				System::Windows::Forms::Button *insertDeinterlace;
				System::Windows::Forms::Button *insertDenoise;
				System::Windows::Forms::Button *insertResize;
				System::Windows::Forms::TextBox *avisynthScript;
				System::Windows::Forms::Label *label1;
				System::Windows::Forms::TabPage *extraSetupPage;
				System::Windows::Forms::ComboBox *mod16Box;
				System::Windows::Forms::CheckBox *signalAR;
				System::Windows::Forms::GroupBox *mpegOptGroupBox;
				System::Windows::Forms::CheckBox *colourCorrect;
				System::Windows::Forms::CheckBox *mpeg2Deblocking;
				System::Windows::Forms::GroupBox *filtersGroupbox;
				System::Windows::Forms::ComboBox *noiseFilterType;
				System::Windows::Forms::CheckBox *resize;
				System::Windows::Forms::CheckBox *noiseFilter;
				System::Windows::Forms::ComboBox *resizeFilterType;
				FileBar *dllBar;
				System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel1;
				System::Windows::Forms::CheckBox *dss2;
				System::Windows::Forms::GroupBox *groupBox2;
				System::Windows::Forms::GroupBox *groupBox1;
				System::Windows::Forms::CheckBox *upsize;
				System::Windows::Forms::Label *label2;
				System::Windows::Forms::ComboBox *modValueBox;
				System::Windows::Forms::Label *acceptableAspectErrorLabel;
				System::Windows::Forms::NumericUpDown *acceptableAspectError;


			private:
				void InitializeInstanceFields();
			};
		}
	}
}
