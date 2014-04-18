#pragma once

#include "core/util/NotifyCounter.h"
#include "core/util/FileSize.h"
#include "FileSizeBar.h"
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




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;



using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			typedef void (*FileSizeEventHandler)(FileSizeBar *sender, FileSizeQEvent *args);

			class FileSizeQEvent : public QEvent
			{
			public:
				const FileSize Value;
				FileSizeQEvent(FileSize value);
			};
			
			class FileSizeBar : public UserControl
			{
				/// <summary>
				/// For making sure that only one person is making a change at once
				/// </summary>
			private:
				NotifyCounter *changeCounter;

				FileSize maxVal;

				/// <summary>
				/// Gets / sets maximum allowed filesize
				/// </summary>
				public:
				~FileSizeBar()
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

			private:
				Unit lastUnit;

			public:
				FileSizeBar();

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
			public:
				const Unit &getCurrentUnit() const;
				void setCurrentUnit(const Unit &value);

				/// <summary>
				/// Adjusts the number of decimal places depending on the 
				/// </summary>
			private:
				void adjustDP();

				/// <summary>
				/// Triggered when the value is changed
				/// </summary>
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event FileSizeEventHandler ValueChanged;

				/// <summary>
				/// Triggers the above event
				/// </summary>
				void triggerChangedEvent();


				void units_SelectedIndexChanged(QObject *sender, QEvent *e);

				void number_ValueChanged(QObject *sender, QEvent *e);

				void FileSizeBar_EnabledChanged(QObject *sender, QEvent *e);


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


				System::Windows::Forms::ComboBox *units;
				System::Windows::Forms::NumericUpDown *number;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
