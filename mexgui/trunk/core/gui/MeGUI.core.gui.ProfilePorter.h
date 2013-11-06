#pragma once

#include "core/plugins/interfaces/Profile.h"
#include "StandardAndCustomComboBox.h"
#include "core/util/Util.h"
#include "core/util/FileUtil.h"
#include "core/util/LogItem.h"
#include "MeGUI.MainForm.h"
#include <string>
#include <map>
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
//using namespace System::Collections;
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

using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class ProfilePorter : public System::Windows::Forms::Form
			{
				public:
				~ProfilePorter()
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
				ProfilePorter();

			private:
				static object *profilesToObjects(Profile ps[]);

				static Profile *objectsToProfiles(IEnumerable *objects);

			protected:
				const Profile *getProfiles() const;
				void setProfiles(Profile value[]);

				const std::vector<Profile*> &getSelectedAndRequiredProfiles() const;

				std::map<std::string, std::string> copyExtraFilesToFolder(std::vector<std::string> &extraFiles, const std::string &folder);

				static void fixFileNames(std::vector<Profile*> &ps, std::map<std::string, std::string> &subTable);

				static std::string getZippedExtraFileName(const std::string &p);

			private:
				void cancelButton_Click(object *sender, EventArgs *e);



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


			protected:
				System::Windows::Forms::Label *label1;
				System::Windows::Forms::Button *button2;
			public:
				System::Windows::Forms::CheckedListBox *profileList;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}