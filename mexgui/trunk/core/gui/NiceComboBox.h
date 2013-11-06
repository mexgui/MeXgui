#pragma once

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
			/// <summary>
			/// A base class for a nicer ComboBox imitator. It works by displaying a context menu next
			/// to a text-field. This class isn't expected to be useful on its own. Derived classes such
			/// as StandardAndCustomComboBox provide more specific, and useful, functionality.
			/// </summary>

			typedef void (*NiceComboBoxItemClicked)(NiceComboBoxNormalItem *item, EventArgs *e);

			class NiceComboBoxItem
			{
			public:
				std::string Name;
				object *Tag;
			private:
				bool ticked;
			public:
				const bool &getTicked() const;
				void setTicked(const bool &value);

				NiceComboBoxItem(const std::string &name, object *tag);
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

				NiceComboBoxNormalItem(const std::string &name, object *tag);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public NiceComboBoxNormalItem(string name, object tag, NiceComboBoxItemClicked handler) :this(name, tag)
				NiceComboBoxNormalItem(const std::string &name, object *tag, NiceComboBoxItemClicked handler);

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
				std::vector<NiceComboBoxItem*> SubItems;

//ORIGINAL LINE: public NiceComboBoxSubMenuItem(string name, object tag, params NiceComboBoxItem[] subItems) :base(name, tag)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
				NiceComboBoxSubMenuItem(const std::string &name, object *tag, ...);

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
