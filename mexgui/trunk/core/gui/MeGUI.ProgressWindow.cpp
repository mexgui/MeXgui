#include "MeGUI.ProgressWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;

namespace MeGUI
{

	ProgressWindow::ProgressWindow()
	{
		InitializeInstanceFields();
		InitializeComponent();
		isUserClosing = true;

		if ((Environment::OSVersion::Version->Major == 6 && Environment::OSVersion::Version::Minor >= 1) || Environment::OSVersion::Version::Major > 6)
			taskbarProgress = static_cast<ITaskbarList3*>(new ProgressTaskbar());
	}

	void ProgressWindow::OnClosing(CancelEventArgs *e)
	{
		if (this->getIsUserAbort())
		{
			e->Cancel = true;
			this->Hide();
		}
		else
		{
			System::Windows::Forms::Form::OnClosing(e);
		}
	}

	void ProgressWindow::UpdateStatus(StatusUpdate *su)
	{
		try
		{
			// possible to abort job
			abortButton->Enabled = (su->getJobStatus() == PROCESSING);

			// Current position
			std::string tempVar = Util.ToString(su.getClipPosition());
			std::string tempVar2 = Util.ToString(su.getClipLength());
			positionInClip->Text = ((tempVar != 0) ? tempVar : "---") + " / " + ((tempVar2 != 0) ? tempVar2 : "---");

			// Current frame
			std::string tempVar3 = Util.ToString(su.getNbFramesDone(), true);
			std::string tempVar4 = Util.ToString(su.getNbFramesTotal(), true);
			currentVideoFrame->Text = ((tempVar3 != 0) ? tempVar3 : "---") + " / " + ((tempVar4 != 0) ? tempVar4 : "---");

			// Data
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			videoData->Text = (su->getCurrentFileSize().HasValue ? su->getCurrentFileSize().Value->ToString() : "---") + " / " + (su->getProjectedFileSize().HasValue ? su->getProjectedFileSize().Value->ToString() : "---");

			// Processing speed
			std::string tempVar5 = su.getProcessingSpeed();
			fps->Text = (tempVar5 != 0) ? tempVar5 : "---";

			// Time elapsed 
			// Now we use TotalHours to avoid 24h+ resets...
			if (su->getTimeElapsed()->TotalHours > 24)
				timeElapsed->Text = std::string::Format("{0:00}:{1:00}:{2:00}:{3:00}", static_cast<int>(su->getTimeElapsed()->TotalDays), su->getTimeElapsed()->Hours, su->getTimeElapsed()->Minutes, su->getTimeElapsed()->Seconds);
			else
				timeElapsed->Text = std::string::Format("{0:00}:{1:00}:{2:00}", static_cast<int>(su->getTimeElapsed()->Hours), su->getTimeElapsed()->Minutes, su->getTimeElapsed()->Seconds);

			// Estimated time
			// go back to the old function ;-)
			Nullable<decimal> tempVar6 = su.getPercentageDoneExact();
			totalTime->Text = getTimeString(su->getTimeElapsed(), tempVar6::HasValue ? tempVar6 : 0);

			Nullable<decimal> tempVar7 = su.getPercentageDoneExact();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			this->Text = "Status: " + (tempVar7::HasValue ? tempVar7 : 0)->ToString("0.00") + " %";
			std::string tempVar8 = su.getStatus();
			statusLabel->Text = (tempVar8 != 0) ? tempVar8 : "";

			jobNameLabel->Text = "[" + su->getJobName() + "]";

			progress->Value = su->getPercentageDone();

			if ((Environment::OSVersion::Version->Major == 6 && Environment::OSVersion::Version::Minor >= 1) || Environment::OSVersion::Version::Major > 6)
				taskbarProgress->SetProgressValue(this->Handle, static_cast<unsigned long long>(su->getPercentageDone()), 100);
		}
		catch (std::exception &e1)
		{
		}
	}

	std::string ProgressWindow::getTimeString(TimeSpan *span, decimal percentageDone)
	{
		if (percentageDone == 0)
			return "---";
		else
		{
			long long ratio = static_cast<long long>(static_cast<decimal>(span->Ticks) / percentageDone * 100);
			TimeSpan *t = new TimeSpan(ratio - span->Ticks);
			std::string retval = "";
			if (t->TotalHours > 24)
			{
				retval += std::string::Format("{0:00}:{1:00}:{2:00}:{3:00}", static_cast<int>(t->TotalDays), t->Hours, t->Minutes, t->Seconds);
			}
			else
			{
				retval += std::string::Format("{0:00}:{1:00}:{2:00}", static_cast<int>(t->Hours), t->Minutes, t->Seconds);
			}
			return retval;
		}
	}

	void ProgressWindow::setPriority(ProcessPriority priority)
	{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		Util::ThreadSafeRun(this->priority, delegate
		{
			isSettingPriority = true;
			this->priority->SelectedIndex = static_cast<int>(priority);
			isSettingPriority = false;
		}
	   );
	}

	void ProgressWindow::abortButton_Click(object *sender, System::EventArgs *e)
	{
		Abort();
	}

	void ProgressWindow::priority_SelectedIndexChanged(object *sender, System::EventArgs *e)
	{
		if (PriorityChanged != 0 && !isSettingPriority)
		{
			if (!WarnPriority(static_cast<ProcessPriority>(priority->SelectedIndex)))
			{
				// priority.Tag contains previous SelectedIndex
				setPriority(static_cast<ProcessPriority>(priority->Tag));
				return;
			}
			else
			{
				PriorityChanged(static_cast<ProcessPriority>(priority->SelectedIndex));
			}

			priority->Tag = priority->SelectedIndex;
		}
	}

	bool ProgressWindow::WarnPriority(ProcessPriority priority)
	{
		if (priority == HIGH)
		{
			// when user selected 'HIGH' priority
			DialogResult *res = MessageBox::Show("On Windows System, running processes at high priority causes them to compete against the window manager and compositor processes. Are you sure you want to proceed?", "MeGUI", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
			return res == System::Windows::Forms::DialogResult::Yes;
		}
		else
			return true;
	}

	const bool &ProgressWindow::getIsUserAbort() const
	{
		return isUserClosing;
	}

	void ProgressWindow::setIsUserAbort(const bool &value)
	{
		isUserClosing = value;
	}

	void ProgressWindow::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void ProgressWindow::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(ProgressWindow::typeid);
		this->currentVideoFrameLabel = new System::Windows::Forms::Label();
		this->currentVideoFrame = new System::Windows::Forms::TextBox();
		this->groupBox1 = new System::Windows::Forms::GroupBox();
		this->totalTime = new System::Windows::Forms::TextBox();
		this->totalTimeLabel = new System::Windows::Forms::Label();
		this->timeElapsed = new System::Windows::Forms::TextBox();
		this->timeElapsedLabel = new System::Windows::Forms::Label();
		this->fps = new System::Windows::Forms::TextBox();
		this->fpsLabel = new System::Windows::Forms::Label();
		this->videoData = new System::Windows::Forms::TextBox();
		this->videoDataLabel = new System::Windows::Forms::Label();
		this->currentPositionLabel = new System::Windows::Forms::Label();
		this->positionInClip = new System::Windows::Forms::TextBox();
		this->abortButton = new System::Windows::Forms::Button();
		this->progressLabel = new System::Windows::Forms::Label();
		this->progress = new System::Windows::Forms::ProgressBar();
		this->priorityLabel = new System::Windows::Forms::Label();
		this->priority = new System::Windows::Forms::ComboBox();
		this->statusStrip1 = new System::Windows::Forms::StatusStrip();
		this->jobNameLabel = new System::Windows::Forms::ToolStripStatusLabel();
		this->statusLabel = new System::Windows::Forms::ToolStripStatusLabel();
		this->helpButton1 = new MeGUI::core::gui::HelpButton();
		this->groupBox1->SuspendLayout();
		this->statusStrip1->SuspendLayout();
		this->SuspendLayout();
		// 
		// currentVideoFrameLabel
		// 
		this->currentVideoFrameLabel->AutoSize = true;
		this->currentVideoFrameLabel->Location = new System::Drawing::Point(8, 44);
		this->currentVideoFrameLabel->Name = "currentVideoFrameLabel";
		this->currentVideoFrameLabel->Size = new System::Drawing::Size(118, 13);
		this->currentVideoFrameLabel->TabIndex = 2;
		this->currentVideoFrameLabel->Text = "Current / Total frames:";
		// 
		// currentVideoFrame
		// 
		this->currentVideoFrame->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->currentVideoFrame->Location = new System::Drawing::Point(173, 41);
		this->currentVideoFrame->Name = "currentVideoFrame";
		this->currentVideoFrame->ReadOnly = true;
		this->currentVideoFrame->Size = new System::Drawing::Size(130, 21);
		this->currentVideoFrame->TabIndex = 17;
		this->currentVideoFrame->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
		// 
		// groupBox1
		// 
		this->groupBox1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->groupBox1->Controls->Add(this->totalTime);
		this->groupBox1->Controls->Add(this->totalTimeLabel);
		this->groupBox1->Controls->Add(this->timeElapsed);
		this->groupBox1->Controls->Add(this->timeElapsedLabel);
		this->groupBox1->Controls->Add(this->fps);
		this->groupBox1->Controls->Add(this->fpsLabel);
		this->groupBox1->Controls->Add(this->videoData);
		this->groupBox1->Controls->Add(this->videoDataLabel);
		this->groupBox1->Controls->Add(this->currentPositionLabel);
		this->groupBox1->Controls->Add(this->currentVideoFrame);
		this->groupBox1->Controls->Add(this->currentVideoFrameLabel);
		this->groupBox1->Controls->Add(this->positionInClip);
		this->groupBox1->Location = new System::Drawing::Point(8, 8);
		this->groupBox1->Name = "groupBox1";
		this->groupBox1->Size = new System::Drawing::Size(309, 177);
		this->groupBox1->TabIndex = 3;
		this->groupBox1->TabStop = false;
		// 
		// totalTime
		// 
		this->totalTime->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->totalTime->Location = new System::Drawing::Point(173, 149);
		this->totalTime->Name = "totalTime";
		this->totalTime->ReadOnly = true;
		this->totalTime->Size = new System::Drawing::Size(130, 21);
		this->totalTime->TabIndex = 25;
		this->totalTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
		// 
		// totalTimeLabel
		// 
		this->totalTimeLabel->AutoSize = true;
		this->totalTimeLabel->Location = new System::Drawing::Point(8, 152);
		this->totalTimeLabel->Name = "totalTimeLabel";
		this->totalTimeLabel->Size = new System::Drawing::Size(82, 13);
		this->totalTimeLabel->TabIndex = 10;
		this->totalTimeLabel->Text = "Time remaining:";
		// 
		// timeElapsed
		// 
		this->timeElapsed->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->timeElapsed->Location = new System::Drawing::Point(173, 122);
		this->timeElapsed->Name = "timeElapsed";
		this->timeElapsed->ReadOnly = true;
		this->timeElapsed->Size = new System::Drawing::Size(130, 21);
		this->timeElapsed->TabIndex = 23;
		this->timeElapsed->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
		// 
		// timeElapsedLabel
		// 
		this->timeElapsedLabel->AutoSize = true;
		this->timeElapsedLabel->Location = new System::Drawing::Point(8, 125);
		this->timeElapsedLabel->Name = "timeElapsedLabel";
		this->timeElapsedLabel->Size = new System::Drawing::Size(73, 13);
		this->timeElapsedLabel->TabIndex = 8;
		this->timeElapsedLabel->Text = "Time elapsed:";
		// 
		// fps
		// 
		this->fps->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->fps->Location = new System::Drawing::Point(173, 95);
		this->fps->Name = "fps";
		this->fps->ReadOnly = true;
		this->fps->Size = new System::Drawing::Size(130, 21);
		this->fps->TabIndex = 21;
		this->fps->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
		// 
		// fpsLabel
		// 
		this->fpsLabel->AutoSize = true;
		this->fpsLabel->Location = new System::Drawing::Point(8, 98);
		this->fpsLabel->Name = "fpsLabel";
		this->fpsLabel->Size = new System::Drawing::Size(85, 13);
		this->fpsLabel->TabIndex = 6;
		this->fpsLabel->Text = "Processing rate:";
		// 
		// videoData
		// 
		this->videoData->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->videoData->Location = new System::Drawing::Point(173, 68);
		this->videoData->Name = "videoData";
		this->videoData->ReadOnly = true;
		this->videoData->Size = new System::Drawing::Size(130, 21);
		this->videoData->TabIndex = 19;
		this->videoData->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
		// 
		// videoDataLabel
		// 
		this->videoDataLabel->AutoSize = true;
		this->videoDataLabel->Location = new System::Drawing::Point(8, 71);
		this->videoDataLabel->Name = "videoDataLabel";
		this->videoDataLabel->Size = new System::Drawing::Size(139, 13);
		this->videoDataLabel->TabIndex = 4;
		this->videoDataLabel->Text = "Current / Projected filesize:";
		// 
		// currentPositionLabel
		// 
		this->currentPositionLabel->AutoSize = true;
		this->currentPositionLabel->Location = new System::Drawing::Point(8, 17);
		this->currentPositionLabel->Name = "currentPositionLabel";
		this->currentPositionLabel->Size = new System::Drawing::Size(144, 13);
		this->currentPositionLabel->TabIndex = 0;
		this->currentPositionLabel->Text = "Position in clip / Total length:";
		// 
		// positionInClip
		// 
		this->positionInClip->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->positionInClip->Location = new System::Drawing::Point(173, 14);
		this->positionInClip->Name = "positionInClip";
		this->positionInClip->ReadOnly = true;
		this->positionInClip->Size = new System::Drawing::Size(130, 21);
		this->positionInClip->TabIndex = 15;
		this->positionInClip->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
		// 
		// abortButton
		// 
		this->abortButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->abortButton->Location = new System::Drawing::Point(239, 252);
		this->abortButton->Name = "abortButton";
		this->abortButton->Size = new System::Drawing::Size(75, 23);
		this->abortButton->TabIndex = 6;
		this->abortButton->Text = "Abort";
		this->abortButton->Click += new System::EventHandler(this, &ProgressWindow::abortButton_Click);
		// 
		// progressLabel
		// 
		this->progressLabel->Location = new System::Drawing::Point(12, 195);
		this->progressLabel->Name = "progressLabel";
		this->progressLabel->Size = new System::Drawing::Size(100, 15);
		this->progressLabel->TabIndex = 1;
		this->progressLabel->Text = "Progress";
		// 
		// progress
		// 
		this->progress->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->progress->Location = new System::Drawing::Point(122, 191);
		this->progress->Name = "progress";
		this->progress->Size = new System::Drawing::Size(195, 23);
		this->progress->TabIndex = 1;
		// 
		// priorityLabel
		// 
		this->priorityLabel->Location = new System::Drawing::Point(12, 223);
		this->priorityLabel->Name = "priorityLabel";
		this->priorityLabel->Size = new System::Drawing::Size(100, 15);
		this->priorityLabel->TabIndex = 3;
		this->priorityLabel->Text = "Priority";
		// 
		// priority
		// 
		this->priority->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->priority->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->priority->Items->AddRange(new object[5] {"LOW", "BELOW NORMAL", "NORMAL", "ABOVE NORMAL", "HIGH"});
		this->priority->Location = new System::Drawing::Point(122, 220);
		this->priority->Name = "priority";
		this->priority->Size = new System::Drawing::Size(122, 21);
		this->priority->TabIndex = 2;
		this->priority->SelectedIndexChanged += new System::EventHandler(this, &ProgressWindow::priority_SelectedIndexChanged);
		// 
		// statusStrip1
		// 
		this->statusStrip1->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->jobNameLabel, this->statusLabel});
		this->statusStrip1->Location = new System::Drawing::Point(0, 284);
		this->statusStrip1->Name = "statusStrip1";
		this->statusStrip1->Size = new System::Drawing::Size(326, 22);
		this->statusStrip1->SizingGrip = false;
		this->statusStrip1->TabIndex = 7;
		this->statusStrip1->Text = "statusStrip1";
		// 
		// jobNameLabel
		// 
		this->jobNameLabel->Name = "jobNameLabel";
		this->jobNameLabel->Size = new System::Drawing::Size(38, 17);
		this->jobNameLabel->Text = "[job1]";
		// 
		// statusLabel
		// 
		this->statusLabel->Name = "statusLabel";
		this->statusLabel->Size = new System::Drawing::Size(45, 17);
		this->statusLabel->Text = "Status: ";
		// 
		// helpButton1
		// 
		this->helpButton1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
		this->helpButton1->setArticleName("Status Window");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(12, 252);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 5;
		// 
		// ProgressWindow
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->ClientSize = new System::Drawing::Size(326, 306);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->statusStrip1);
		this->Controls->Add(this->priority);
		this->Controls->Add(this->priorityLabel);
		this->Controls->Add(this->progress);
		this->Controls->Add(this->progressLabel);
		this->Controls->Add(this->abortButton);
		this->Controls->Add(this->groupBox1);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimumSize = new System::Drawing::Size(332, 330);
		this->Name = "ProgressWindow";
		this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
		this->Text = "Status";
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		this->statusStrip1->ResumeLayout(false);
		this->statusStrip1->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void ProgressWindow::InitializeInstanceFields()
	{
		isSettingPriority = false;
		delete components;
	}
}
