#include "MediaInfoWrapperTest.MediaInfoForm.h"

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
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
using namespace MediaInfoWrapper;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace MediaInfoWrapperTest
{

	MediaInfoForm::MediaInfoForm()
	{
		 InitializeInstanceFields();
		 InitializeComponent();
		 this->Text = "Media Information (Thanks to MediaInfo.dll)";

	}

	MediaInfoForm::MediaInfoForm(const std::string &filepath)
	{

		InitializeInstanceFields();
		InitializeComponent();
		this->Text = "Media Information (Thanks to MediaInfo.dll)";
		FileName = filepath;
	}

	void MediaInfoForm::Form1_Load(object *sender, EventArgs *e)
	{


	}

	void MediaInfoForm::toolStripButton1_Click(object *sender, EventArgs *e)
	{
		OpenFileDialog *O = new OpenFileDialog();
		O->RestoreDirectory = true;
		O->ShowDialog();
		if (O->FileName == "")
			return;

			FileName = O->FileName;
			toolStripTextBox1->Text = FileName;
			M = new MediaInfo(FileName);
			T->Text = M->getInfoStandard();


	}

	void MediaInfoForm::toolStripButton2_Click(object *sender, EventArgs *e)
	{
		if (File::Exists(FileName))
			T->Text = M->getInfoStandard();
	}

	void MediaInfoForm::toolStripButton3_Click(object *sender, EventArgs *e)
	{

		if (File::Exists(FileName))
			T->Text = InfoCustom(FileName);
	}

	void MediaInfoForm::toolStripButton4_Click(object *sender, EventArgs *e)
	{
		T->Text = MediaInfo::Capacities();

	}

	void MediaInfoForm::toolStripButton5_Click(object *sender, EventArgs *e)
	{
		T->Text = MediaInfo::KnownCodecs();
	}

	void MediaInfoForm::toolStripButton6_Click(object *sender, EventArgs *e)
	{
		if (File::Exists(FileName))
			T->Text = M->getInfoComplete();
	}

	void MediaInfoForm::toolStripTextBox1_KeyDown(object *sender, KeyEventArgs *e)
	{
		if (e->KeyCode == Keys::Enter)
		{
			if (System::IO::File::Exists(toolStripTextBox1->Text))
				FileName = toolStripTextBox1->Text;
				M = new MediaInfo(FileName);
				T->Text = M->getInfoStandard();


		}
	}

	std::string MediaInfoForm::InfoCustom(const std::string &filepath)
	{

		M = new MediaInfo(filepath);
		std::string s = "";

		s += "General" + "\r\n";
		s += ListEveryAvailablePropery<GeneralTrack*>(this, &M->getGeneral());
		s += "\r\n";
		s += "Video" + "\r\n";
		s += ListEveryAvailablePropery<VideoTrack*>(this, &M->getVideo());
		s += "\r\n";
		s += "Audio" + "\r\n";
		s += ListEveryAvailablePropery<AudioTrack*>(this, &M->getAudio());
		s += "\r\n";
		s += "Text" + "\r\n";
		s += ListEveryAvailablePropery<TextTrack*>(this, &M->getText());
		s += "\r\n";
		s += "Chapters" + "\r\n";
		s += ListEveryAvailablePropery<ChaptersTrack*>(this, &M->getChapters());

		return s;

	}

template<typename T1>
	std::string MediaInfoForm::ListEveryAvailablePropery(std::vector<T1> &L)
	{
		std::string s = "";
		for (std::vector<T1>::const_iterator track = L.begin(); track != L.end(); ++track)
		{
			for (unknown::const_iterator p = track->GetType()->GetProperties().begin(); p != track->GetType()->GetProperties().end(); ++p)
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				s += ((*p)->GetValue(*track, 0)->ToString() == "") ? (*p)->Name + " : Not available" + "\r\n" : (*p)->Name + " : " + (*p)->GetValue(*track, 0) + "\r\n";
			}
		}
		return s;
	}

	void MediaInfoForm::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void MediaInfoForm::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(MediaInfoForm::typeid);
		this->toolStripContainer1 = new System::Windows::Forms::ToolStripContainer();
		this->T = new System::Windows::Forms::RichTextBox();
		this->toolStrip1 = new System::Windows::Forms::ToolStrip();
		this->toolStripTextBox1 = new System::Windows::Forms::ToolStripTextBox();
		this->toolStripButton1 = new System::Windows::Forms::ToolStripButton();
		this->toolStripButton2 = new System::Windows::Forms::ToolStripButton();
		this->toolStripButton6 = new System::Windows::Forms::ToolStripButton();
		this->toolStripButton3 = new System::Windows::Forms::ToolStripButton();
		this->toolStripButton4 = new System::Windows::Forms::ToolStripButton();
		this->toolStripButton5 = new System::Windows::Forms::ToolStripButton();
		this->toolStripContainer1->ContentPanel->SuspendLayout();
		this->toolStripContainer1->TopToolStripPanel->SuspendLayout();
		this->toolStripContainer1->SuspendLayout();
		this->toolStrip1->SuspendLayout();
		this->SuspendLayout();
		// 
		// toolStripContainer1
		// 
		// 
		// toolStripContainer1.ContentPanel
		// 
		this->toolStripContainer1->ContentPanel->Controls->Add(this->T);
		this->toolStripContainer1->ContentPanel->Size = new System::Drawing::Size(445, 436);
		this->toolStripContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->toolStripContainer1->Location = new System::Drawing::Point(0, 0);
		this->toolStripContainer1->Name = "toolStripContainer1";
		this->toolStripContainer1->Size = new System::Drawing::Size(445, 461);
		this->toolStripContainer1->TabIndex = 0;
		this->toolStripContainer1->Text = "toolStripContainer1";
		// 
		// toolStripContainer1.TopToolStripPanel
		// 
		this->toolStripContainer1->TopToolStripPanel->Controls->Add(this->toolStrip1);
		// 
		// T
		// 
		this->T->Dock = System::Windows::Forms::DockStyle::Fill;
		this->T->Location = new System::Drawing::Point(0, 0);
		this->T->Name = "T";
		this->T->Size = new System::Drawing::Size(445, 436);
		this->T->TabIndex = 0;
		this->T->Text = "";
		// 
		// toolStrip1
		// 
		this->toolStrip1->Dock = System::Windows::Forms::DockStyle::None;
		this->toolStrip1->Items->AddRange(new System::Windows::Forms::ToolStripItem[7] {this->toolStripTextBox1, this->toolStripButton1, this->toolStripButton2, this->toolStripButton6, this->toolStripButton3, this->toolStripButton4, this->toolStripButton5});
		this->toolStrip1->Location = new System::Drawing::Point(0, 0);
		this->toolStrip1->Name = "toolStrip1";
		this->toolStrip1->Size = new System::Drawing::Size(445, 25);
		this->toolStrip1->Stretch = true;
		this->toolStrip1->TabIndex = 0;
		// 
		// toolStripTextBox1
		// 
		this->toolStripTextBox1->Name = "toolStripTextBox1";
		this->toolStripTextBox1->Size = new System::Drawing::Size(100, 25);
		this->toolStripTextBox1->KeyDown += new System::Windows::Forms::KeyEventHandler(this, &MediaInfoForm::toolStripTextBox1_KeyDown);
		// 
		// toolStripButton1
		// 
		this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->toolStripButton1->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("toolStripButton1.Image")));
		this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton1->Name = "toolStripButton1";
		this->toolStripButton1->Size = new System::Drawing::Size(37, 22);
		this->toolStripButton1->Text = "Open";
		this->toolStripButton1->Click += new System::EventHandler(this, &MediaInfoForm::toolStripButton1_Click);
		// 
		// toolStripButton2
		// 
		this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->toolStripButton2->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("toolStripButton2.Image")));
		this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton2->Name = "toolStripButton2";
		this->toolStripButton2->Size = new System::Drawing::Size(55, 22);
		this->toolStripButton2->Text = "Standard";
		this->toolStripButton2->Click += new System::EventHandler(this, &MediaInfoForm::toolStripButton2_Click);
		// 
		// toolStripButton6
		// 
		this->toolStripButton6->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->toolStripButton6->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("toolStripButton6.Image")));
		this->toolStripButton6->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton6->Name = "toolStripButton6";
		this->toolStripButton6->Size = new System::Drawing::Size(56, 22);
		this->toolStripButton6->Text = "Complete";
		this->toolStripButton6->Click += new System::EventHandler(this, &MediaInfoForm::toolStripButton6_Click);
		// 
		// toolStripButton3
		// 
		this->toolStripButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->toolStripButton3->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("toolStripButton3.Image")));
		this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton3->Name = "toolStripButton3";
		this->toolStripButton3->Size = new System::Drawing::Size(47, 22);
		this->toolStripButton3->Text = "Custom";
		this->toolStripButton3->Click += new System::EventHandler(this, &MediaInfoForm::toolStripButton3_Click);
		// 
		// toolStripButton4
		// 
		this->toolStripButton4->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->toolStripButton4->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("toolStripButton4.Image")));
		this->toolStripButton4->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton4->Name = "toolStripButton4";
		this->toolStripButton4->Size = new System::Drawing::Size(60, 22);
		this->toolStripButton4->Text = "Capacities";
		this->toolStripButton4->Click += new System::EventHandler(this, &MediaInfoForm::toolStripButton4_Click);
		// 
		// toolStripButton5
		// 
		this->toolStripButton5->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->toolStripButton5->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("toolStripButton5.Image")));
		this->toolStripButton5->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton5->Name = "toolStripButton5";
		this->toolStripButton5->Size = new System::Drawing::Size(46, 22);
		this->toolStripButton5->Text = "Codecs";
		this->toolStripButton5->Click += new System::EventHandler(this, &MediaInfoForm::toolStripButton5_Click);
		// 
		// Form1
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = new System::Drawing::Size(445, 461);
		this->Controls->Add(this->toolStripContainer1);
		this->Name = "Form1";
		this->Text = "Form1";
		this->Load += new System::EventHandler(this, &MediaInfoForm::Form1_Load);
		this->toolStripContainer1->ContentPanel->ResumeLayout(false);
		this->toolStripContainer1->TopToolStripPanel->ResumeLayout(false);
		this->toolStripContainer1->TopToolStripPanel->PerformLayout();
		this->toolStripContainer1->ResumeLayout(false);
		this->toolStripContainer1->PerformLayout();
		this->toolStrip1->ResumeLayout(false);
		this->toolStrip1->PerformLayout();
		this->ResumeLayout(false);

	}

	void MediaInfoForm::InitializeInstanceFields()
	{
		FileName = "";
		delete components;
	}
}
