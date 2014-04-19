#pragma once

#include "MainForm.h"
#include "core/details/video/VideoCodecSettings.h"
#include "ZonesControl.h"
#include <QString>

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



namespace MeXgui
{
	namespace core
	{
		namespace gui
		{
			class ZonesWindow : public System::Windows::Forms::Form
			{
				public:
				~ZonesWindow()
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
				ZonesWindow(MainForm *mf, const QString &input);

				const Zone *getZones() const;
				void setZones(Zone value[]);


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


				ZonesControl *zonesControl1;
				System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel1;
				System::Windows::Forms::Button *button2;
				System::Windows::Forms::Button *button1;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
