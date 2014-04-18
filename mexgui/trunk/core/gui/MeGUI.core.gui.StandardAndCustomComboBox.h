#pragma once

#include "MeGUI.core.gui.NiceComboBox.h"
#include "NiceComboBox.h"
#include "core/util/Util.h"
#include "core/util/LogItem.h"
#include "FileSCBox.h"
#include "StandardAndCustomComboBox.h"
#include <string>
#include <vector>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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
//using namespace System::Configuration;
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
			class StandardAndCustomComboBox : public MeGUI::core::gui::NiceComboBox
			{
			private:
				NiceComboBoxNormalItem *clearItem;
				int numStandardItems, numCustomItems, numOpener;
			protected:
				Getter<object*> Getter;
				Getter<object*> GetterFolder;
				bool bSaveEveryItem;

				public:
				~StandardAndCustomComboBox()
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
				StandardAndCustomComboBox();

				StandardAndCustomComboBox(const std::string &clearText, const std::string &chooseNewText);

				void SetFileSCBoxType(const std::string &chooseNewText, const std::string &chooseNewFolder, MeGUI::core::gui::FileSCBox::FileSCBoxType oType);

				void SetTargetSizeSCBoxType(const std::string &clearText, const std::string &chooseCustomSize);

				void AddStandardItem(object *o);

				void AddCustomItem(object *name);

			private:
				void clearStandardItems();

				void clearCustomItems();

				int getCustomItemStart();

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const object *getCustomItems() const;
				void setCustomItems(object value[]);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const object *getStandardItems() const;
				void setStandardItems(object value[]);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const object &getSelectedObject() const;
				void setSelectedObject(const object &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const SCItem &getSelectedSCItem() const;



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


			private:
				void InitializeInstanceFields();
			};
		}
	}
}
