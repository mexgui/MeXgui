#pragma once

#include "NiceComboBox.h"
#include "NiceComboBox.h"
#include "core/util/Util.h"
#include "core/util/LogItem.h"
#include "FileSCBox.h"
#include "StandardAndCustomComboBox.h"
#include <QString>
#include <QVector>

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




//using namespace System::Collections::Generic;



//using namespace System::Configuration;

//using namespace System::Data;



//using namespace System::Text;



using namespace MeXgui::core::util;

namespace MeXgui
{
	namespace core
	{
		namespace gui
		{
			/// <summary>
			/// Represents a drop-down ComboBox which has both standard and custom values.
			/// Examples are CQMs (for x264, the standard two are "flat" and "jvt", and
			/// custom ones are user-selected files) and file-sizes (standard is "1 CD", "2 CD",
			/// custom is "100MB", etc).
			/// 
			/// There are three separated sections, with the Standard at the top, the custom 
			/// in the middle, and one or two buttons at the bottom to choose a new custom 
			/// option, and to clear all custom options.
			/// 
			/// Known derived classes are FileSCBox, which opens an OpenFileDialog as the
			/// new custom option, and FileSizeSCBox, which lets the user choose a non-custom
			/// filesize.
			/// </summary>

			class SCItem
			{
			public:
				object *Tag;
				bool IsStandard;

				SCItem(object *tag, bool isStandard);

				virtual QString ToString();
			};

			template<typename T>
			class Named
			{
			public:
				T Data;
				QString Name;

				Named(const QString &name, T data)
				{
					Data = data;
					Name = name;
				}

				virtual bool Equals(object *obj)
				{
					return ((static_cast<dynamic_cast<Named<T*>*>(obj)*>(!) = 0) && (static_cast<Named<T>*>(obj))->Data->Equals(Data)) || (dynamic_cast<T>(obj) != 0 && (static_cast<T>(obj))->Equals(Data));
				}

				virtual int GetHashCode()
				{
					return 0;
				}

				virtual QString ToString()
				{
					return Name;
				}
			};
			
			
			class StandardAndCustomComboBox : public MeXgui::core::gui::NiceComboBox
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

				StandardAndCustomComboBox(const QString &clearText, const QString &chooseNewText);

				void SetFileSCBoxType(const QString &chooseNewText, const QString &chooseNewFolder, MeXgui::core::gui::FileSCBox::FileSCBoxType oType);

				void SetTargetSizeSCBoxType(const QString &clearText, const QString &chooseCustomSize);

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
