#include "MeGUI.MuxWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;
using namespace MeGUI::core::details;

namespace MeGUI
{

IDable<MeGUI::core::details::ReconfigureJob> *const MuxWindow::Configurer = new IDable<MeGUI::core::details::ReconfigureJob>("mux_reconfigure", new ReconfigureJob(ReconfigureJob));

	MeGUI::Job *MuxWindow::ReconfigureJob(MeGUI::Job *j)
	{
		if (!(dynamic_cast<MuxJob*>(j) != 0))
			return 0;

		MuxJob *m = static_cast<MuxJob*>(j);
		MuxWindow *w = new MuxWindow(MainForm::Instance->getMuxProvider()->GetMuxer(m->getMuxType()), MainForm::Instance);

		w->setJob(m);
		if (w->ShowDialog() == DialogResult::OK)
			return w->getJob();
		else
			return m;
	}

	MuxWindow::MuxWindow(IMuxing *muxer, MainForm *mainForm) : baseMuxWindow(mainForm, muxer)
	{
		InitializeInstanceFields();
		InitializeComponent();
		this->muxer = muxer;
		if (muxer->GetSupportedAudioTypes()->Count == 0)
			audio->Enabled = false;
		if (muxer->GetSupportedChapterTypes()->Count == 0)
			chaptersGroupbox->Enabled = false;
		if (muxer->GetSupportedSubtitleTypes()->Count == 0)
			subtitles->Enabled = false;
		else if (this->muxer->getMuxerType() == MKVMERGE)
		{
			subtitleTracks[0]->ShowDefaultSubtitleStream = true;
			subtitleTracks[0]->ShowDelay = true;
			subtitleTracks[0]->chkDefaultStream->CheckedChanged += new System::EventHandler(this, &baseMuxWindow::chkDefaultStream_CheckedChanged);
			subtitleTracks[0]->chkDefaultStream->Checked = true;
			subtitleTracks[0]->ShowForceSubtitleStream = true;
		}
		if (muxer->GetSupportedChapterTypes()->Count == 0)
			chaptersGroupbox->Enabled = false;
		if (muxer->GetSupportedDeviceTypes()->Count == 0)
			cbType->Enabled = false;
		muxedInput->setFilter(muxer->GetMuxedInputFilter());

		audioTracks[0]->Filter = muxer->GetAudioInputFilter();
		output->setFilter(muxer->GetOutputTypeFilter());
		subtitleTracks[0]->Filter = muxer->GetSubtitleInputFilter();
		vInput->setFilter(muxer->GetVideoInputFilter());
		chapters->setFilter(muxer->GetChapterInputFilter());

		baseMuxWindow::muxButton::Click += new System::EventHandler(this, &MuxWindow::muxButton_Click);

		this->Text = "MeGUI - " + muxer->getName();

		cbType->Items->Clear();
		cbType->Items->Add("Standard");
		cbType->Items->AddRange(muxer->GetSupportedDeviceTypes()->ToArray());
		this->cbType->SelectedIndex = 0;
		for (unknown::const_iterator o = cbType->Items.begin(); o != cbType->Items.end(); ++o) // I know this is ugly, but using the DeviceOutputType doesn't work unless we're switching to manual serialization
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if ((*o)->ToString()->Equals(mainForm->getSettings()->getAedSettings()->getDeviceOutputType()))
			{
				cbType->SelectedItem = *o;
				break;
			}
		}
	}

	void MuxWindow::muxButton_Click(object *sender, System::EventArgs *e)
	{
		if (muxButton->DialogResult != DialogResult::OK)
		{
			if (vInput->getFilename().empty())
			{
				MessageBox::Show("You must configure a video input file", "Missing input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				return;
			}
			else if (output->getFilename().empty())
			{
				MessageBox::Show("You must configure an output file", "Missing input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				return;
			}
			else if (MainForm::verifyOutputFile(output->getFilename()) != "")
			{
				MessageBox::Show("Invalid output file", "Invalid output", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			else if (!fps->getValue().HasValue)
			{
				MessageBox::Show("You must select a framerate", "Missing input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				return;
			}
		}
		else
		{
			if (this->muxButton->Text->Equals("Update"))
			{
				this->Close();
			}
			else
			{
				MuxJob *job = this->getJob();
				mainForm->getJobs()->addJobsToQueue(job);
				if (chkCloseOnQueue->Checked)
					this->Close();
				else
					output->setFilename("");
			}
		}
	}

	MuxJob *MuxWindow::generateMuxJob()
	{
		MuxJob *job = new MuxJob();
		std::string chapters;
//ORIGINAL LINE: MuxStream[] aStreams, sStreams;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		MuxStream *aStreams, *sStreams;
		getAdditionalStreams(aStreams, sStreams, chapters);
		job->getSettings()->getAudioStreams().AddRange(aStreams);
		job->getSettings()->getSubtitleStreams().AddRange(sStreams);
		job->getSettings()->setChapterFile(this->chapters->getFilename());
		job->getSettings()->setVideoName(this->videoName->Text);
		job->getSettings()->setVideoInput(vInput->getFilename());
		job->getSettings()->setMuxedOutput(output->getFilename());
		job->getSettings()->setMuxedInput(this->muxedInput->getFilename());
		job->getSettings()->setDAR(baseMuxWindow::dar);
		job->getSettings()->setDeviceType(this->cbType->Text);

		if (job->getSettings()->getVideoInput().empty())
			job->Input = job->getSettings()->getMuxedInput();
		else
			job->Input = job->getSettings()->getVideoInput();

		job->Output = job->getSettings()->getMuxedOutput();
		job->setMuxType(muxer->getMuxerType());
		job->setContainerType(getContainerType(job->getSettings()->getMuxedOutput()));
		job->getSettings()->setFramerate(fps->getValue());

		assert(!splitting->getValue().HasValue || splitting->getValue().Value >= FileSize(MB, 1));
		job->getSettings()->setSplitSize(splitting->getValue());
		return job;
	}

	const MuxJob &MuxWindow::getJob() const
	{
		return generateMuxJob();
	}

	void MuxWindow::setJob(const MuxJob &value)
	{
		setConfig(value->getSettings()->getVideoInput(), value->getSettings()->getVideoName(), value->getSettings()->getMuxedInput(), value->getSettings()->getFramerate(), value->getSettings()->getAudioStreams().ToArray(), value->getSettings()->getSubtitleStreams().ToArray(), value->getSettings()->getChapterFile(), value->getSettings()->getMuxedOutput(), value->getSettings()->getSplitSize(), value->getSettings()->getDAR(), value->getSettings()->getDeviceType());
	}

	void MuxWindow::setConfig(const std::string &videoInput, const std::string &videoName, const std::string &muxedInput, Nullable<decimal> framerate, MuxStream audioStreams[], MuxStream subtitleStreams[], const std::string &chapterFile, const std::string &output, Nullable<FileSize> splitSize, Nullable<Dar> dar, const std::string &deviceType)
	{
		baseMuxWindow::setConfig(videoInput, videoName, framerate, audioStreams, subtitleStreams, chapterFile, output, splitSize, dar, deviceType);
		this->muxedInput->setFilename(muxedInput);
		this->checkIO();
	}

	void MuxWindow::ChangeOutputExtension()
	{
		for (unknown::const_iterator t = muxer->GetSupportedContainers().begin(); t != muxer->GetSupportedContainers().end(); ++t)
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if (output->getFilename().ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith((*t)->getExtension()->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
				return;
		}
		output->setFilename(Path::ChangeExtension(output->getFilename(), muxer->GetSupportedContainers()[0]->Extension));
	}

	ContainerType *MuxWindow::getContainerType(const std::string &outputFilename)
	{
		assert(outputFilename != "");
		for (unknown::const_iterator t = muxer->GetSupportedContainers().begin(); t != muxer->GetSupportedContainers().end(); ++t)
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if (outputFilename.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith((*t)->getExtension()->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
				return t;
		}
		assert(false);
		return 0;
	}

	bool MuxWindow::isFPSRequired()
	{
		if (vInput->getFilename().length() > 0)
			return baseMuxWindow::isFPSRequired();
		else if (muxedInput->getFilename().length() > 0)
			return false;
		else
			return true;
	}

	void MuxWindow::muxedInput_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		checkIO();
		fileUpdated();
	}

	void MuxWindow::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		baseMuxWindow::Dispose(disposing);
	}

	void MuxWindow::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(MuxWindow::typeid);
		this->label1 = new System::Windows::Forms::Label();
		this->muxedInput = new MeGUI::FileBar();
		this->SuspendLayout();
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = new System::Drawing::Point(14, 53);
		this->label1->Name = "label1";
		this->label1->Size = new System::Drawing::Size(68, 13);
		this->label1->TabIndex = 2;
		this->label1->Text = "Muxed Input";
		// 
		// muxedInput
		// 
		this->muxedInput->setFilename("");
		this->muxedInput->setFilter("");
		this->muxedInput->setFilterIndex(0);
		this->muxedInput->setFolderMode(false);
		this->muxedInput->Location = new System::Drawing::Point(118, 45);
		this->muxedInput->Name = "muxedInput";
		this->muxedInput->setReadOnly(true);
		this->muxedInput->setSaveMode(false);
		this->muxedInput->Size = new System::Drawing::Size(289, 26);
		this->muxedInput->TabIndex = 3;
		this->muxedInput->setTitle("");
		this->muxedInput->FileSelected += new MeGUI::FileBarEventHandler(this, &MuxWindow::muxedInput_FileSelected);
		// 
		// MuxWindow
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->AutoSize = true;
		this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->ClientSize = new System::Drawing::Size(444, 562);
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->Name = "MuxWindow";
		this->Text = "MeGUI - Muxer";
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void MuxWindow::InitializeInstanceFields()
	{
		delete components;
	}
}
