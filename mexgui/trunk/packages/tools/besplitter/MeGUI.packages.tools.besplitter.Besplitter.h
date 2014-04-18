#pragma once

#include "core/gui/MeGUI.MainForm.h"
#include "core/details/CodecManager.h"
#include "core/util/VideoUtil.h"
#include "core/util/LogItem.h"
#include "core/util/FilmCutter.h"
#include "AudioSplitJob.h"
#include "AudioJoinJob.h"
#include "core/details/MeGUI.core.details.SequentialChain.h"
#include "core/gui/FileBar.h"
#include "core/gui/MeGUI.FileBar.h"
#include "core/gui/MeGUI.core.gui.HelpButton.h"
#include <string>
#include <stdexcept>

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
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{
				class Besplitter : public System::Windows::Forms::Form
				{
				private:
					MainForm *info;
//ORIGINAL LINE: OutputFileType[] filters;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
					OutputFileType *filters;

					public:
					~Besplitter()
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
					Besplitter(MainForm *info);

				private:
					void goButton_Click(object *sender, EventArgs *e);

					static std::string *generateNumberedFilenames(const std::string &prefix, const std::string &ext, int num);

					static std::string getAcceptableFilename(const std::string &p, int p_2);

					void input_FileSelected(FileBar *sender, FileBarEventArgs *args);




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


					System::Windows::Forms::Label *label1;
					System::Windows::Forms::Label *label2;
					System::Windows::Forms::Label *label3;
					FileBar *input;
					FileBar *cuts;
					FileBar *output;
					System::Windows::Forms::Button *goButton;
					MeGUI::core::gui::HelpButton *helpButton1;

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
