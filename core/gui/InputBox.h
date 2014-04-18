#pragma once

#include "core/util/LogItem.h"
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



namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class InputBox : public System::Windows::Forms::Form
			{
				public:
				~InputBox()
				{
					this->Dispose(true);
				}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:
				void Finalize()
				{
					this->Dispose(false);
				}

			private:
				InputBox();

				void btnOk_Click(QObject *sender, QEvent *e);

				void btnCancel_Click(QObject *sender, QEvent *e);

			public:
				static QString Show(const QString &message, const QString &title, const QString &defaultText);

			private:
				void text_KeyPress(QObject *sender, KeyPressQEvent *e);


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


				System::Windows::Forms::Button *btnOk;
				System::Windows::Forms::Button *btnCancel;
				System::Windows::Forms::TextBox *text;
				System::Windows::Forms::Label *lblMessage;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
