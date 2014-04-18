#pragma once

#include "core/util/LogItem.h"
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

//using namespace System::Diagnostics;



//using namespace System::Text;



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
				const QVector<NiceComboBoxItem*> Items;

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
				const QString &getSelectedText() const;

				NiceComboBox();

			private:
				NiceComboBoxItem *selectedItem;

				void dropDownButton_Click(QObject *sender, QEvent *e);

				/// <summary>
				/// Generates a list of menu items from their descriptors
				/// </summary>
				/// <param name="items"></param>
				/// <returns></returns>
				ToolStripItem *createMenu(QVector<NiceComboBoxItem*> &items);

				void item_Click(QObject *sender, QEvent *e);


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
			
			
			
			/// <summary>
			/// A base class for a nicer ComboBox imitator. It works by displaying a context menu next
			/// to a text-field. This class isn't expected to be useful on its own. Derived classes such
			/// as StandardAndCustomComboBox provide more specific, and useful, functionality.
			/// </summary>

			typedef void (*NiceComboBoxItemClicked)(NiceComboBoxNormalItem *item, QEvent *e);

			class NiceComboBoxItem
			{
			public:
				QString Name;
				object *Tag;
			private:
				bool ticked;
			public:
				const bool &getTicked() const;
				void setTicked(const bool &value);

				NiceComboBoxItem(const QString &name, object *tag);
			};

			/// <summary>
			/// This represents a clickable item, which can either be selected or
			/// can have an event handler for when it is clicked. It is not a separator,
			/// and it may not have a submenu
			/// </summary>
			class NiceComboBoxNormalItem : public NiceComboBoxItem
			{
			public:
				bool Selectable;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event NiceComboBoxItemClicked ItemClicked;

				void OnClick();

				NiceComboBoxNormalItem(const QString &name, object *tag);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public NiceComboBoxNormalItem(string name, object tag, NiceComboBoxItemClicked handler) :this(name, tag)
				NiceComboBoxNormalItem(const QString &name, object *tag, NiceComboBoxItemClicked handler);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public NiceComboBoxNormalItem(object stringableObject) : this(stringableObject.ToString(), stringableObject)
				NiceComboBoxNormalItem(object *stringableObject);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public NiceComboBoxNormalItem(object stringableObject, NiceComboBoxItemClicked handler) : this(stringableObject.ToString(), stringableObject, handler)
				NiceComboBoxNormalItem(object *stringableObject, NiceComboBoxItemClicked handler);

			private:
				void InitializeInstanceFields();
			};

			/// <summary>
			/// An item which may hold a submenu. Can't be clicked.
			/// </summary>
			class NiceComboBoxSubMenuItem : public NiceComboBoxItem
			{
			public:
				QVector<NiceComboBoxItem*> SubItems;

//ORIGINAL LINE: public NiceComboBoxSubMenuItem(string name, object tag, params NiceComboBoxItem[] subItems) :base(name, tag)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
				NiceComboBoxSubMenuItem(const QString &name, object *tag, ...);

//ORIGINAL LINE: public NiceComboBoxSubMenuItem(object stringableObject, params NiceComboBoxItem[] subItems) : this(stringableObject.ToString(), stringableObject, subItems)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
				NiceComboBoxSubMenuItem(object *stringableObject, ...);
			};

			/// <summary>
			/// A separator. Can't be clicked.
			/// </summary>
			class NiceComboBoxSeparator : public NiceComboBoxItem
			{
			public:
				NiceComboBoxSeparator();
			};
		}
	}
}
