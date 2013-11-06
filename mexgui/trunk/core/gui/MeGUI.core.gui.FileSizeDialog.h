#pragma once

#include "core/util/FileSize.h"
#include "core/util/LogItem.h"

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

using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class FileSizeDialog : public System::Windows::Forms::Form
			{
				public:
				~FileSizeDialog()
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
				FileSizeDialog();

			private:
				FileSize maxVal;

				/// <summary>
				/// Gets / sets maximum allowed filesize
				/// </summary>
			public:
				const FileSize &getMaximum() const;
				void setMaximum(const FileSize &value);

			private:
				FileSize minVal;

				/// <summary>
				/// Gets / sets minimum allowed displayable filesize
				/// </summary>
			public:
				const FileSize &getMinimum() const;
				void setMinimum(const FileSize &value);

				/// <summary>
				/// Gets / sets the value displayed by the component
				/// </summary>
				const FileSize &getValue() const;
				void setValue(const FileSize &value);

				/// <summary>
				/// Reads the value off the GUI, using the given Unit
				/// </summary>
				/// <param name="u"></param>
				/// <returns></returns>
			private:
				FileSize readValue(Unit u);

				/// <summary>
				/// Reads / writes the current unit from the GUI
				/// </summary>
				const Unit &getCurrentUnit() const;
				void setCurrentUnit(const Unit &value);

				/// <summary>
				/// Adjusts the number of decimal places depending on the 
				/// </summary>
				void adjustDP();

				void FileSizeDialog_Shown(object *sender, EventArgs *e);

				void number_KeyPress(object *sender, KeyPressEventArgs *e);


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


				System::Windows::Forms::NumericUpDown *number;
				System::Windows::Forms::ComboBox *units;
				System::Windows::Forms::Button *okButton;
				System::Windows::Forms::Button *cancelButton;
				System::Windows::Forms::Label *label1;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
