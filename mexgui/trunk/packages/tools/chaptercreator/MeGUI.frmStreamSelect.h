#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
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
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace MeGUI
{
	class frmStreamSelect : public System::Windows::Forms::Form
	{
		public:
		~frmStreamSelect()
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
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public frmStreamSelect(ChapterExtractor extractor) : this(extractor, SelectionMode.One)
		frmStreamSelect(ChapterExtractor *extractor);

		frmStreamSelect(ChapterExtractor *extractor, SelectionMode *selectionMode);

		const ChapterInfo &getSelectedSingleChapterInfo() const;

		const std::vector<ChapterInfo*> &getSelectedMultipleChapterInfo() const;

		const int &getChapterCount() const;

	private:
		void btnOK_Click(object *sender, EventArgs *e);

		void btnSortName_CheckedChanged(object *sender, EventArgs *e);

		void btnSortDuration_CheckedChanged(object *sender, EventArgs *e);


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


	System::Windows::Forms::Button *btnOK;
	System::Windows::Forms::ListBox *listBox1;
	System::Windows::Forms::RadioButton *btnSortDuration;
	System::Windows::Forms::RadioButton *btnSortName;
	System::Windows::Forms::Button *btnCancel;

	private:
		void InitializeInstanceFields();
	};
}
