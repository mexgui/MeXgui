#include "MeGUI.frmStreamSelect.h"

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

	frmStreamSelect::frmStreamSelect(ChapterExtractor *extractor)
	{
		InitializeInstanceFields();
	}

	frmStreamSelect::frmStreamSelect(ChapterExtractor *extractor, SelectionMode *selectionMode)
	{
		InitializeInstanceFields();
		InitializeComponent();
		listBox1->SelectionMode = selectionMode;

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		extractor->StreamDetected += (sender, arg) =>
		{
			listBox1->Items->Add(arg::ProgramChain);
		};
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		extractor->ChaptersLoaded += (sender, arg) =>
		{
			for (int i = 0; i < listBox1->Items->Count; i++)
			{
				if ((static_cast<ChapterInfo*>(listBox1->Items[i]))->getSourceName() == arg::ProgramChain::SourceName)
				{
					listBox1->Items[i] = arg::ProgramChain;
					break;
				}
			}
		};
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		extractor->ExtractionComplete += (sender, arg) =>
		{
			btnSortDuration->Checked = true;
		};
	}

	const ChapterInfo &frmStreamSelect::getSelectedSingleChapterInfo() const
	{
		return listBox1->SelectedItems->Count > 0 ? dynamic_cast<ChapterInfo*>(listBox1->SelectedItem) : 0;
	}

	const std::vector<ChapterInfo*> &frmStreamSelect::getSelectedMultipleChapterInfo() const
	{
		return listBox1->SelectedItems->Count > 0 ? std::vector<ChapterInfo*>(listBox1->SelectedItems->Cast<ChapterInfo*>()) : 0;
	}

	const int &frmStreamSelect::getChapterCount() const
	{
		return listBox1->Items->Count;
	}

	void frmStreamSelect::btnOK_Click(object *sender, EventArgs *e)
	{
		if (listBox1->SelectedItems->Count >= 1)
			DialogResult = System::Windows::Forms::DialogResult::OK;
		else
			MessageBox::Show("Please select a stream", "Selection missing", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	void frmStreamSelect::btnSortName_CheckedChanged(object *sender, EventArgs *e)
	{
		if (!btnSortName->Checked || listBox1->Items->Count == 0)
			return;

		std::vector<ChapterInfo*> oSelectedList = std::vector<ChapterInfo*>(listBox1->SelectedItems->Cast<ChapterInfo*>());

		std::vector<ChapterInfo*> list = std::vector<ChapterInfo*>(listBox1->Items->Cast<ChapterInfo*>());
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		list = list.OrderBy(p => (p::Title + p::TitleNumber))->ToList();
		listBox1->Items->Clear();
		listBox1->Items->AddRange(list.ToArray());

		if (oSelectedList.size() > 0)
		{
			for (int i = 0; i < listBox1->Items->Count; i++)
			{
				for (std::vector<ChapterInfo*>::const_iterator oSelectedItem = oSelectedList.begin(); oSelectedItem != oSelectedList.end(); ++oSelectedItem)
				{
					if (static_cast<ChapterInfo*>(listBox1->Items[i]) == *oSelectedItem)
					{
						listBox1->SetSelected(i, true);
						break;
					}
				}
			}
		}
		else
			listBox1->SelectedIndex = 0;
	}

	void frmStreamSelect::btnSortDuration_CheckedChanged(object *sender, EventArgs *e)
	{
		if (!btnSortDuration->Checked || listBox1->Items->Count == 0)
			return;

		std::vector<ChapterInfo*> oSelectedList = std::vector<ChapterInfo*>(listBox1->SelectedItems->Cast<ChapterInfo*>());

		std::vector<ChapterInfo*> list = std::vector<ChapterInfo*>(listBox1->Items->Cast<ChapterInfo*>());
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		list = list.OrderByDescending(p => p::Duration)->ToList();
		listBox1->Items->Clear();
		listBox1->Items->AddRange(list.ToArray());

		if (oSelectedList.size() > 0)
		{
			for (int i = 0; i < listBox1->Items->Count; i++)
			{
				for (std::vector<ChapterInfo*>::const_iterator oSelectedItem = oSelectedList.begin(); oSelectedItem != oSelectedList.end(); ++oSelectedItem)
				{
					if (static_cast<ChapterInfo*>(listBox1->Items[i]) == *oSelectedItem)
					{
						listBox1->SetSelected(i, true);
						break;
					}
				}
			}
		}
		else
			listBox1->SelectedIndex = 0;
	}

	void frmStreamSelect::Dispose(bool disposing)
	{
	  if (disposing && (components != 0))
	  {
		delete components;
	  }
	  System::Windows::Forms::Form::Dispose(disposing);
	}

	void frmStreamSelect::InitializeComponent()
	{
			System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(frmStreamSelect::typeid);
			this->btnOK = new System::Windows::Forms::Button();
			this->listBox1 = new System::Windows::Forms::ListBox();
			this->btnSortDuration = new System::Windows::Forms::RadioButton();
			this->btnSortName = new System::Windows::Forms::RadioButton();
			this->btnCancel = new System::Windows::Forms::Button();
			this->SuspendLayout();
			// 
			// btnOK
			// 
			this->btnOK->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->btnOK->Location = new System::Drawing::Point(127, 264);
			this->btnOK->Name = "btnOK";
			this->btnOK->Size = new System::Drawing::Size(76, 22);
			this->btnOK->TabIndex = 1;
			this->btnOK->Text = "OK";
			this->btnOK->UseVisualStyleBackColor = true;
			this->btnOK->Click += new System::EventHandler(this, &frmStreamSelect::btnOK_Click);
			// 
			// listBox1
			// 
			this->listBox1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = new System::Drawing::Point(13, 41);
			this->listBox1->Name = "listBox1";
			this->listBox1->Size = new System::Drawing::Size(423, 212);
			this->listBox1->TabIndex = 2;
			this->listBox1->DoubleClick += new System::EventHandler(this, &frmStreamSelect::btnOK_Click);
			// 
			// btnSortDuration
			// 
			this->btnSortDuration->AutoSize = true;
			this->btnSortDuration->Location = new System::Drawing::Point(91, 13);
			this->btnSortDuration->Name = "btnSortDuration";
			this->btnSortDuration->Size = new System::Drawing::Size(102, 17);
			this->btnSortDuration->TabIndex = 3;
			this->btnSortDuration->Text = "sort by duration";
			this->btnSortDuration->UseVisualStyleBackColor = true;
			this->btnSortDuration->CheckedChanged += new System::EventHandler(this, &frmStreamSelect::btnSortDuration_CheckedChanged);
			// 
			// btnSortName
			// 
			this->btnSortName->AutoSize = true;
			this->btnSortName->Checked = true;
			this->btnSortName->Location = new System::Drawing::Point(253, 13);
			this->btnSortName->Name = "btnSortName";
			this->btnSortName->Size = new System::Drawing::Size(88, 17);
			this->btnSortName->TabIndex = 4;
			this->btnSortName->TabStop = true;
			this->btnSortName->Text = "sort by name";
			this->btnSortName->UseVisualStyleBackColor = true;
			this->btnSortName->CheckedChanged += new System::EventHandler(this, &frmStreamSelect::btnSortName_CheckedChanged);
			// 
			// btnCancel
			// 
			this->btnCancel->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnCancel->Location = new System::Drawing::Point(227, 264);
			this->btnCancel->Name = "btnCancel";
			this->btnCancel->Size = new System::Drawing::Size(76, 22);
			this->btnCancel->TabIndex = 6;
			this->btnCancel->Text = "Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			// 
			// frmStreamSelect
			// 
			this->AcceptButton = this->btnOK;
			this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->btnCancel;
			this->ClientSize = new System::Drawing::Size(448, 298);
			this->ControlBox = false;
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnSortName);
			this->Controls->Add(this->btnSortDuration);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->btnOK);
			this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
			this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = "frmStreamSelect";
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->Text = "Select your list";
			this->ResumeLayout(false);
			this->PerformLayout();

	}

	void frmStreamSelect::InitializeInstanceFields()
	{
		delete components;
	}
}
