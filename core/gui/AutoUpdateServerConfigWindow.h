#pragma once

#include "core/util/LogItem.h"
#include "InputBox.h"
#include "MainForm.h"
#include "UpdateWindow.h"
#include "HelpButton.h"
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



namespace MeXgui
{
	namespace core
	{
		namespace gui
		{
			class AutoUpdateServerConfigWindow : public System::Windows::Forms::Form
			{
			private:
//ORIGINAL LINE: private string[][] serverLists;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				QString **serverLists;
				QString oldTitle;
				int oldIndex;

				public:
				~AutoUpdateServerConfigWindow()
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
				AutoUpdateServerConfigWindow();

			private:
				void addServerButton_Click(QObject *sender, QEvent *e);

				void removeSelectedServersButton_Click(QObject *sender, QEvent *e);

			public:
				const int &getServerListIndex() const;
				void setServerListIndex(const int &value);

				const QString **getServerList() const;
				void setServerList(QString value[][]);

			private:
				const QString *getlittleServerList() const;
				void setlittleServerList(QString value[]);

				void subList_SelectedIndexChanged(QObject *sender, QEvent *e);


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


				System::Windows::Forms::ListBox *serverList;
				System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel1;
				System::Windows::Forms::Button *addServerButton;
				System::Windows::Forms::Button *removeSelectedServersButton;
				System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel2;
				System::Windows::Forms::Button *cancelButton;
				System::Windows::Forms::Button *okButton;
				System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel3;
				System::Windows::Forms::Label *label1;
				System::Windows::Forms::ComboBox *subList;
				HelpButton *helpButton1;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
