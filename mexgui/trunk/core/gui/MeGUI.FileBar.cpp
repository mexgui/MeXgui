#include "MeGUI.FileBar.h"

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
using namespace MeGUI::core::util;

namespace MeGUI
{

	FileBar::FileBar()
	{
		InitializeInstanceFields();
		InitializeComponent();
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		DragDropUtil::RegisterSingleFileDragDrop(filename, setFilename, delegate()
		{
			return getFilter();
		}
	   );
	}

	const bool &FileBar::getSaveMode() const
	{
		return saveMode;
	}

	void FileBar::setSaveMode(const bool &value)
	{
		saveMode = value;
		filename->AllowDrop = !value;
	}

	const bool &FileBar::getReadOnly() const
	{
		return filename->ReadOnly;
	}

	void FileBar::setReadOnly(const bool &value)
	{
		filename->ReadOnly = value;
	}

	const std::string &FileBar::getTitle() const
	{
		return title;
	}

	void FileBar::setTitle(const std::string &value)
	{
		title = value;
	}

	const std::string &FileBar::getFilename() const
	{
		return filename->Text;
	}

	void FileBar::setFilename(const std::string &value)
	{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (IDisposable wrapper = raiseEvent.Wrap())
		IDisposable *wrapper = raiseEvent->Wrap();
		try
		{
			filename->Text = value;
			oldName = value;
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (wrapper != 0)
				wrapper.Dispose();
		}
	}

	const bool &FileBar::getFolderMode() const
	{
		return folderMode;
	}

	void FileBar::setFolderMode(const bool &value)
	{
		folderMode = value;
	}

	const std::string &FileBar::getFilter() const
	{
		return filter;
	}

	void FileBar::setFilter(const std::string &value)
	{
		filter = value;
	}

	const int &FileBar::getFilterIndex() const
	{
		return filterIndex;
	}

	void FileBar::setFilterIndex(const int &value)
	{
		filterIndex = value;
	}

	void FileBar::openButton_Click(object *sender, EventArgs *e)
	{
		if (folderMode)
		{
			FolderBrowserDialog *dialog = new FolderBrowserDialog();
			if (dialog->ShowDialog() == DialogResult::OK)
				setFilename(dialog->SelectedPath);
		}
		else
		{
			FileDialog *dialog = saveMode ? static_cast<FileDialog*>(new SaveFileDialog()): static_cast<FileDialog*>(new OpenFileDialog());

			dialog->Filter = filter;
			dialog->FilterIndex = filterIndex;
			dialog->Title = title;
			if (!getFilename().empty())
			{
				try
				{
					dialog->InitialDirectory = Path::GetDirectoryName(getFilename());
					dialog->FileName = Path::GetFileName(getFilename());
				}
				catch (...)
				{
				}
			}
			if (dialog->ShowDialog() == DialogResult::OK)
				setFilename(dialog->FileName);
		}
	}

	void FileBar::PerformClick()
	{
		openButton->PerformClick();
	}

	void FileBar::setFilename(const std::string &filename)
	{
		oldName = this->filename->Text;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (IDisposable a = raiseEvent.Wrap())
		IDisposable *a = raiseEvent->Wrap();
		try
		{
			this->filename->Text = filename;
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (a != 0)
				a.Dispose();
		}
		triggerEvent();
	}

	void FileBar::triggerEvent()
	{
		if (raiseEvent->getReady())
			FileSelected(this, new FileBarEventArgs(oldName, filename->Text));
		oldName = filename->Text;
	}

	void FileBar::filename_TextChanged(object *sender, EventArgs *e)
	{
		setFilename(filename->Text);
		triggerEvent();
	}

	void FileBar::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		UserControl::Dispose(disposing);
	}

	void FileBar::InitializeComponent()
	{
		this->filename = new System::Windows::Forms::TextBox();
		this->openButton = new System::Windows::Forms::Button();
		this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
		this->tableLayoutPanel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// filename
		// 
		this->filename->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->filename->Location = new System::Drawing::Point(0, 3);
		this->filename->Margin = new System::Windows::Forms::Padding(0);
		this->filename->Name = "filename";
		this->filename->ReadOnly = true;
		this->filename->Size = new System::Drawing::Size(239, 20);
		this->filename->TabIndex = 5;
		this->filename->TextChanged += new System::EventHandler(this, &FileBar::filename_TextChanged);
		// 
		// openButton
		// 
		this->openButton->Anchor = System::Windows::Forms::AnchorStyles::Right;
		this->openButton->AutoSize = true;
		this->openButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->openButton->Location = new System::Drawing::Point(242, 1);
		this->openButton->Margin = new System::Windows::Forms::Padding(3, 1, 1, 1);
		this->openButton->Name = "openButton";
		this->openButton->Size = new System::Drawing::Size(26, 23);
		this->openButton->TabIndex = 1;
		this->openButton->Text = "...";
		this->openButton->Click += new System::EventHandler(this, &FileBar::openButton_Click);
		// 
		// tableLayoutPanel1
		// 
		this->tableLayoutPanel1->ColumnCount = 2;
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->Controls->Add(this->filename, 0, 0);
		this->tableLayoutPanel1->Controls->Add(this->openButton, 1, 0);
		this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tableLayoutPanel1->Location = new System::Drawing::Point(0, 0);
		this->tableLayoutPanel1->Margin = new System::Windows::Forms::Padding(0);
		this->tableLayoutPanel1->Name = "tableLayoutPanel1";
		this->tableLayoutPanel1->RowCount = 1;
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100));
		this->tableLayoutPanel1->Size = new System::Drawing::Size(269, 26);
		this->tableLayoutPanel1->TabIndex = 7;
		// 
		// FileBar
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->Controls->Add(this->tableLayoutPanel1);
		this->Name = "FileBar";
		this->Size = new System::Drawing::Size(269, 26);
		this->tableLayoutPanel1->ResumeLayout(false);
		this->tableLayoutPanel1->PerformLayout();
		this->ResumeLayout(false);

	}

	void FileBar::InitializeInstanceFields()
	{
		saveMode = false;
		raiseEvent = new NotifyCounter();
		delete components;
	}
}
