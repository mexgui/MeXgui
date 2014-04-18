#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
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





//using namespace System::Linq;

//using namespace System::Text;



namespace MeXgui
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

		const QVector<ChapterInfo*> &getSelectedMultipleChapterInfo() const;

		const int &getChapterCount() const;

	private:
		void btnOK_Click();

		void btnSortName_CheckedChanged();

		void btnSortDuration_CheckedChanged();


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
