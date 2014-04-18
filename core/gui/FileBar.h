#pragma once

#include "core/util/DragDropUtil.h"
#include "core/util/NotifyCounter.h"
#include "core/util/LogItem.h"
#include "FileBar.h"
#include <QString>

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



//using namespace System::Data;





//using namespace System::Text;



using namespace MeGUI::core::util;

namespace MeGUI
{
	typedef void (*FileBarEventHandler)(FileBar *sender, FileBarQEvent *args);

	class FileBarEvent : public QEvent
	{
	public:
		const QString OldFileName;
		const QString NewFileName;
		FileBarEvent(const QString &oldName, const QString &newName);
	};


	class FileBar : public UserControl
	{
	private:
		QString oldName;
		public:
		~FileBar()
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
		FileBar();

	private:
		bool saveMode;
	public:
		const bool &getSaveMode() const;
		void setSaveMode(const bool &value);

		const bool &getReadOnly() const;
		void setReadOnly(const bool &value);

	private:
		QString title;

	public:
		const QString &getTitle() const;
		void setTitle(const QString &value);

	private:
		NotifyCounter *raiseEvent;

	public:
		const QString &getFilename() const;
		void setFilename(const QString &value);

	private:
		bool folderMode;

	public:
		const bool &getFolderMode() const;
		void setFolderMode(const bool &value);

	private:
		QString filter;

	public:
		const QString &getFilter() const;
		void setFilter(const QString &value);

	private:
		int filterIndex;

	public:
		const int &getFilterIndex() const;
		void setFilterIndex(const int &value);

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event FileBarEventHandler FileSelected;

	private:
		void openButton_Click(QObject *sender, QEvent *e);

	public:
		void PerformClick();

	private:
		void setFilename(const QString &filename);

		void triggerEvent();

		void filename_TextChanged(QObject *sender, QEvent *e);


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


		System::Windows::Forms::TextBox *filename;
		System::Windows::Forms::Button *openButton;
		System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;

	private:
		void InitializeInstanceFields();
	};
}
