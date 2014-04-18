#pragma once

#include "NiceComboBox.h"
#include "StandardAndCustomComboBox.h"
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
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class NiceComboBox : public UserControl
			{
				/// <summary>
				/// A list of all the items.
				/// </summary>
			public:
				const std::vector<NiceComboBoxItem*> Items;

				/// <summary>
				/// Raised when the selected item is changed, either by the user, or by a call to 
				/// SelectedIndex.set or SelectedItem.set
				/// </summary>
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event StringChanged SelectionChanged;

				/// <summary>
				/// Temporary Item if the value should not be stored permanently
				/// </summary>
				SCItem *oTemporaryItem;

				/// <summary>
				/// Index of the selected item, or -1 if the selected item isn't on the list
				/// or if it is in a submenu.
				/// </summary>
				public:
				~NiceComboBox()
				{
					this->Dispose(true);
				}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:
				void Finalize()
				{
					this->Dispose(false);
				}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
				const int &getSelectedIndex() const;
				void setSelectedIndex(const int &value);

				/// <summary>
				/// Gets / sets the selected item. The text is guaranteed to 
				/// be displayed, but the item will not be added to the drop-down menu
				/// if it isn't already there.
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
				const NiceComboBoxItem &getSelectedItem() const;
				void setSelectedItem(const NiceComboBoxItem &value);

				/// <summary>
				/// Returns the currently displayed text
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
				const std::string &getSelectedText() const;

				NiceComboBox();

			private:
				NiceComboBoxItem *selectedItem;

				void dropDownButton_Click(object *sender, EventArgs *e);

				/// <summary>
				/// Generates a list of menu items from their descriptors
				/// </summary>
				/// <param name="items"></param>
				/// <returns></returns>
				ToolStripItem *createMenu(std::vector<NiceComboBoxItem*> &items);

				void item_Click(object *sender, EventArgs *e);


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


				System::Windows::Forms::Button *dropDownButton;
				System::Windows::Forms::TextBox *textBox1;
				System::Windows::Forms::ContextMenuStrip *contextMenuStrip1;
				System::Windows::Forms::ToolStripMenuItem *helloToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *hiToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *hereToolStripMenuItem;
				System::Windows::Forms::ToolStripSeparator *toolStripSeparator1;
				System::Windows::Forms::ToolStripTextBox *toolStripTextBox1;
				System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
