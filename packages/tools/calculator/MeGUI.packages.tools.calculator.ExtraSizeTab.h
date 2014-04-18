#pragma once

#include "core/util/LogItem.h"
#include "core/util/FileSize.h"
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



using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

using namespace MediaInfoWrapper;

namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace calculator
			{
				class ExtraSizeTab : public UserControl
				{
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//					public event EventHandler SomethingChanged;

					public:
					~ExtraSizeTab()
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
					ExtraSizeTab();

				private:
					void raiseEvent();

					void selectExtraFile(const QString &file);

								MeXgui::core::util::FileSize privateFileSize;
							public:
								const MeXgui::core::util::FileSize &getFileSize() const;
								void setFileSize(const MeXgui::core::util::FileSize &value);

				private:
					const QString filter;

					void selectButton_Click();

					void removeLink_LinkClicked();

					void selectButton_Enter();


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


					System::Windows::Forms::Label *label2;
					System::Windows::Forms::Button *selectButton;
					System::Windows::Forms::OpenFileDialog *openFileDialog;
					System::Windows::Forms::Label *audioLabel;
					System::Windows::Forms::TextBox *name;
					System::Windows::Forms::TextBox *size;
					System::Windows::Forms::LinkLabel *removeLink;
					System::Windows::Forms::ToolTip *removalToolTip;

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
