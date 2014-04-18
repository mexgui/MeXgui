#pragma once

#include "core/util/DAR.h"
#include "core/util/LogItem.h"

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
using namespace MeGUI::core::util;


namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class AspectRatioChooser : public System::Windows::Forms::Form
			{
			private:
				bool bDisableEvents;

				public:
				~AspectRatioChooser()
				{
					this->Dispose(true);
				}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:
				void Finalize()
				{
					this->Dispose(false);
				}

				AspectRatioChooser();

			public:
				static DialogResult *ShowDialog(Dar defaultDar, Dar &newDar);

				void SetValues(Dar ar);

			private:
				void radioButton_CheckedChanged(object *sender, EventArgs *e);

				void numericUpDown2_ValueChanged(object *sender, EventArgs *e);

				void numericUpDown1_ValueChanged(object *sender, EventArgs *e);


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


				System::Windows::Forms::NumericUpDown *numericUpDown1;
				System::Windows::Forms::Button *button2;
				System::Windows::Forms::RadioButton *radioButton1;
				System::Windows::Forms::RadioButton *radioButton2;
				System::Windows::Forms::NumericUpDown *numericUpDown2;
				System::Windows::Forms::NumericUpDown *numericUpDown3;
				System::Windows::Forms::Label *label1;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
