#include "MeGUI.AudioEncodingComponent.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details::video;
using namespace MeGUI::core::gui;
using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{

	AudioEncodingComponent::AudioEncodingComponent()
	{
		InitializeInstanceFields();
		InitializeComponent();

		if (MainForm::Instance != 0)
		{
			tabs.push_back(audioEncodingTab1);

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			audioEncodingTab1->QueueJob = delegate(AudioJob a)
			{
				MainForm::Instance->getJobs()->addJobsToQueue(a);
			};

			audioEncodingTab1->setAudioContainer(MainForm::Instance->getSettings()->getMainAudioFormat());
		}
	}

	void AudioEncodingComponent::AddTab()
	{
		AudioEncodingTab *a = new AudioEncodingTab();
		tabs.push_back(a);
		a->setAudioContainer(MainForm::Instance->getSettings()->getMainAudioFormat());
		a->Dock = System::Windows::Forms::DockStyle::Fill;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		a->QueueJob = delegate(AudioJob aJob)
		{
			MainForm::Instance->getJobs()->addJobsToQueue(aJob);
		};

		TabPage *p = new TabPage("Track " + tabs.size());
		tabControl1->TabPages->Add(p);
		p->Controls->Add(a);
		p->Padding = tabControl1->TabPages[0]->Padding;
		a->setFileTypeComboBoxSize(tabs[0]->getFileTypeComboBoxSize()); // has to go after padding
		p->UseVisualStyleBackColor = tabControl1->TabPages[0]->UseVisualStyleBackColor;

	}

	const std::vector<AudioJob*> &AudioEncodingComponent::getAudioStreams() const
	{
		std::vector<AudioJob*> streams = std::vector<AudioJob*>();
		for (std::vector<AudioEncodingTab*>::const_iterator t = tabs.begin(); t != tabs.end(); ++t)
		{
			AudioJob *a = (*t)->getAudioJob();
			if (a != 0)
				streams.push_back(a);
		}
		return streams;
	}

	std::string AudioEncodingComponent::verifyAudioSettings()
	{
		for (std::vector<AudioEncodingTab*>::const_iterator t = tabs.begin(); t != tabs.end(); ++t)
		{
			AudioJob *a = (*t)->getAudioJob();
			if (a == 0)
				continue;
			std::string s = (*t)->verifyAudioSettings();
			if (s != "")
				return s;
		}
		return 0;
	}

	void AudioEncodingComponent::Reset()
	{
		for (std::vector<AudioEncodingTab*>::const_iterator t = tabs.begin(); t != tabs.end(); ++t)
			(*t)->Reset();
	}

	void AudioEncodingComponent::openAudioFile(...)
	{
		if (files->Length == 0)
			return;

		tabs.clear();
		tabControl1->TabPages->Clear();

		for (int i = 0; i < files->Length; ++i)
		{
			assert(i <= tabs.size());

			if (i == tabs.size())
				AddTab();

			tabs[i]->openAudioFile(files[i]);
		}
		tabControl1->SelectedIndex = files->Length - 1;
	}

	void AudioEncodingComponent::newTrackToolStripMenuItem_Click(object *sender, EventArgs *e)
	{
		AddTab();
	}

	void AudioEncodingComponent::removeTrackToolStripMenuItem_Click(object *sender, EventArgs *e)
	{
		RemoveTab();
	}

	void AudioEncodingComponent::RemoveTab()
	{
		tabs.RemoveAt(tabControl1->SelectedIndex);
		tabControl1->TabPages->RemoveAt(tabControl1->SelectedIndex);

		for (int i = 0; i < tabControl1->TabPages->Count; ++i)
			tabControl1->TabPages[i]->Text = "Track " + (i + 1);
	}

	void AudioEncodingComponent::contextMenuStrip1_Opening(object *sender, CancelEventArgs *e)
	{
		if (tabs.size() == 1)
			removeTrackToolStripMenuItem->Enabled = false;
		else
			removeTrackToolStripMenuItem->Enabled = true;
	}

	void AudioEncodingComponent::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		UserControl::Dispose(disposing);
	}

	void AudioEncodingComponent::InitializeComponent()
	{
		this->components = new System::ComponentModel::Container();
		this->groupBox1 = new System::Windows::Forms::GroupBox();
		this->contextMenuStrip1 = new System::Windows::Forms::ContextMenuStrip(this->components);
		this->newTrackToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
		this->removeTrackToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
		this->tabControl1 = new System::Windows::Forms::TabControl();
		this->tabPage1 = new System::Windows::Forms::TabPage();
		this->audioEncodingTab1 = new MeGUI::core::gui::AudioEncodingTab();
		this->groupBox1->SuspendLayout();
		this->contextMenuStrip1->SuspendLayout();
		this->tabControl1->SuspendLayout();
		this->tabPage1->SuspendLayout();
		this->SuspendLayout();
		// 
		// groupBox1
		// 
		this->groupBox1->ContextMenuStrip = this->contextMenuStrip1;
		this->groupBox1->Controls->Add(this->tabControl1);
		this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->groupBox1->Location = new System::Drawing::Point(0, 0);
		this->groupBox1->Name = "groupBox1";
		this->groupBox1->Size = new System::Drawing::Size(515, 230);
		this->groupBox1->TabIndex = 0;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = "Audio";
		// 
		// contextMenuStrip1
		// 
		this->contextMenuStrip1->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->newTrackToolStripMenuItem, this->removeTrackToolStripMenuItem});
		this->contextMenuStrip1->Name = "contextMenuStrip1";
		this->contextMenuStrip1->Size = new System::Drawing::Size(141, 48);
		this->contextMenuStrip1->Opening += new System::ComponentModel::CancelEventHandler(this, &AudioEncodingComponent::contextMenuStrip1_Opening);
		// 
		// newTrackToolStripMenuItem
		// 
		this->newTrackToolStripMenuItem->Name = "newTrackToolStripMenuItem";
		this->newTrackToolStripMenuItem->Size = new System::Drawing::Size(140, 22);
		this->newTrackToolStripMenuItem->Text = "New track";
		this->newTrackToolStripMenuItem->Click += new System::EventHandler(this, &AudioEncodingComponent::newTrackToolStripMenuItem_Click);
		// 
		// removeTrackToolStripMenuItem
		// 
		this->removeTrackToolStripMenuItem->Name = "removeTrackToolStripMenuItem";
		this->removeTrackToolStripMenuItem->Size = new System::Drawing::Size(140, 22);
		this->removeTrackToolStripMenuItem->Text = "Remove track";
		this->removeTrackToolStripMenuItem->Click += new System::EventHandler(this, &AudioEncodingComponent::removeTrackToolStripMenuItem_Click);
		// 
		// tabControl1
		// 
		this->tabControl1->Controls->Add(this->tabPage1);
		this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tabControl1->Location = new System::Drawing::Point(3, 16);
		this->tabControl1->Name = "tabControl1";
		this->tabControl1->SelectedIndex = 0;
		this->tabControl1->Size = new System::Drawing::Size(509, 211);
		this->tabControl1->TabIndex = 1;
		// 
		// tabPage1
		// 
		this->tabPage1->Controls->Add(this->audioEncodingTab1);
		this->tabPage1->Location = new System::Drawing::Point(4, 22);
		this->tabPage1->Name = "tabPage1";
		this->tabPage1->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage1->Size = new System::Drawing::Size(501, 185);
		this->tabPage1->TabIndex = 0;
		this->tabPage1->Text = "Track 1";
		// 
		// audioEncodingTab1
		// 
		this->audioEncodingTab1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->audioEncodingTab1->Location = new System::Drawing::Point(3, 3);
		this->audioEncodingTab1->Name = "audioEncodingTab1";
		this->audioEncodingTab1->Size = new System::Drawing::Size(495, 179);
		this->audioEncodingTab1->TabIndex = 0;
		// 
		// AudioEncodingComponent
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->AutoScroll = true;
		this->Controls->Add(this->groupBox1);
		this->Name = "AudioEncodingComponent";
		this->Size = new System::Drawing::Size(515, 230);
		this->groupBox1->ResumeLayout(false);
		this->contextMenuStrip1->ResumeLayout(false);
		this->tabControl1->ResumeLayout(false);
		this->tabPage1->ResumeLayout(false);
		this->ResumeLayout(false);

	}

	void AudioEncodingComponent::InitializeInstanceFields()
	{
		tabs = std::vector<AudioEncodingTab*>();
		delete components;
	}
}
