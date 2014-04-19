#include "VideoPlayer.h"

//using namespace System::Threading;


using namespace MeXgui::core::gui;
using namespace MeXgui::core::util;

namespace MeXgui
{

	VideoPlayer::VideoPlayer()
	{
		InitializeInstanceFields();
		InitializeComponent();
		this->Resize += new EventHandler(this, &VideoPlayer::formResized);

		decimal dpiX = 96, dpiY = 96;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Graphics graphics = this.CreateGraphics())
		Graphics *graphics = this->CreateGraphics();
		try
		{
			dpiX = static_cast<decimal>(graphics->DpiX);
			dpiY = static_cast<decimal>(graphics->DpiY);
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (graphics != 0)
				graphics.Dispose();
		}
		dpiX /= 96;
		dpiY /= 96;

		formHeightDelta = static_cast<int>((buttonPanel->Size->Height + 4 * defaultSpacing) * dpiY);
		buttonPanelMinWidth = static_cast<int>((showPAR->Location->X + showPAR->Size->Width) * dpiX);
		zoomFactor = 100;
		setZoomButtons();
		sizeLock = false;
	}

	void VideoPlayer::setAllowClose(const bool &value)
	{
		this->ControlBox = value;
	}

	const bool &VideoPlayer::getAllowClose() const
	{
		return this->ControlBox;
	}

	bool VideoPlayer::loadVideo(MainForm *mainForm, const QString &path, PREVIEWTYPE type, bool hasAR)
	{
		return loadVideo(mainForm, path, type, hasAR, false, -1, false);
	}

	bool VideoPlayer::loadVideo(MainForm *mainForm, const QString &path, PREVIEWTYPE type, bool hasAR, bool inlineAvs, int startFrame, bool originalSize)
	{
		videoPreview->UnloadVideo();
		bInlineAVS = inlineAvs;
		strFileName = path;
		bOriginalSize = originalSize;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock (this)
		{
			if (file != 0)
				delete file;
		}

		try
		{
			if (inlineAvs)
			{
				file = AvsFile::ParseScript(path);
				btnReloadVideo->Enabled = false;
			}
			else
			{
				file = mainForm->getMediaFileFactory()->Open(path);
				if (file == 0 && !(file->getVideoInfo()->HasVideo && file->getCanReadVideo()))
					throw new ArgumentException("The video stream cannot be opened");
				btnReloadVideo->Enabled = true;
			}
			reader = file->GetVideoReader();
		}
		catch (AviSynthException *e)
		{
			MessageBox::Show("AviSynth script error:\r\n" + e->Message, "AviSynth error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
		catch (ArgumentException *e)
		{
			MessageBox::Show("AviSynth script error:\r\n" + e->Message, "AviSynth error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
		catch (std::exception &e)
		{
	#warning fix up this error message to be more correct

			MessageBox::Show("The file " + path + " cannot be opened.\r\n Please make sure it's a valid AviSynth script and that AviSynth is " + " properly installed.\r\nYou can check the validity of your script and AviSynth installation by opening the file in your favorite media player.\r\n" + " If that works, try opening the video in VirtualDub(Mod) as well. If the former works and the latter doesn't, install a YV12 codec.\r\n" + "Error message for your reference: " + e.what(), "Cannot open video input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return false;
		}

		if (reader != 0 && reader->getFrameCount() > 0)
		{
			this->positionSlider->Minimum = 0;
			this->positionSlider->Maximum = reader->getFrameCount() - 1;
			this->positionSlider->TickFrequency = this->positionSlider->Maximum / 20;
			this->viewerType = type;
			this->hasAR = hasAR;
			zoomMaxWidth = 0;
			SetMaxZoomWidth();
			doInitialAdjustment();
			int iStart = 0;
			if (startFrame >= 0)
				iStart = startFrame;
			else if (MainForm::Instance->getSettings()->getOpenAVSInThreadDuringSession())
				iStart = reader->getFrameCount() / 2;
			videoPreview->LoadVideo(reader, file->getVideoInfo()->FPS, iStart);
			setTitleText();
			return true;
		}
		return false;
	}

	bool VideoPlayer::reloadVideo()
	{
		videoPreview->UnloadVideo();

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock (this)
		{
			if (file != 0)
				delete file;
		}

		try
		{
			if (bInlineAVS)
			{
				file = AvsFile::ParseScript(strFileName);
			}
			else
			{
				file = mainForm->getMediaFileFactory()->Open(strFileName);
				if (file == 0 && !(file->getVideoInfo()->HasVideo && file->getCanReadVideo()))
					throw new ArgumentException("The video stream cannot be opened");
			}
			reader = file->GetVideoReader();
		}
		catch (AviSynthException *e)
		{
			MessageBox::Show("AviSynth script error:\r\n" + e->Message, "AviSynth error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
		catch (ArgumentException *e)
		{
			MessageBox::Show("AviSynth script error:\r\n" + e->Message, "AviSynth error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
		catch (std::exception &e)
		{
	#warning fix up this error message to be more correct

			MessageBox::Show("The file " + strFileName + " cannot be opened.\r\n Please make sure it's a valid AviSynth script and that AviSynth is " + " properly installed.\r\nYou can check the validity of your script and AviSynth installation by opening the file in your favorite media player.\r\n" + " If that works, try opening the video in VirtualDub(Mod) as well. If the former works and the latter doesn't, install a YV12 codec.\r\n" + "Error message for your reference: " + e.what(), "Cannot open video input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			return false;
		}

		if (reader != 0 && reader->getFrameCount() > 0)
		{
			this->positionSlider->Minimum = 0;
			this->positionSlider->Maximum = reader->getFrameCount() - 1;
			this->positionSlider->TickFrequency = this->positionSlider->Maximum / 20;
			SetMaxZoomWidth();
			doInitialAdjustment();
			int iStart = 0;
			if (positionSlider->Value >= 0 && positionSlider->Value <= reader->getFrameCount())
				iStart = positionSlider->Value;
			else if (MainForm::Instance->getSettings()->getOpenAVSInThreadDuringSession())
				iStart = reader->getFrameCount() / 2;
			videoPreview->LoadVideo(reader, file->getVideoInfo()->FPS, iStart);
			setTitleText();
			return true;
		}
		return false;
	}

	void VideoPlayer::disableIntroAndCredits()
	{
		buttonPanel->Controls->Remove(introEndButton);
		buttonPanel->Controls->Remove(creditsStartButton);
	}

	void VideoPlayer::originalSizeButton_Click(QObject *sender, QEvent *e)
	{
		bOriginalSize = true;
		zoomWidth = static_cast<int>(file->getVideoInfo()->Width);
		zoomFactor = static_cast<int>(static_cast<double>(zoomWidth) / zoomMaxWidth * 100.0);
		setZoomButtons();
		resize(zoomWidth, showPAR->Checked);
	}

	void VideoPlayer::SetScreenSize()
	{
		if (bOriginalSize)
			originalSizeButton_Click(0, 0);
		else
			btnFitScreen_Click(0, 0);
	}

	void VideoPlayer::btnFitScreen_Click(QObject *sender, QEvent *e)
	{
		bOriginalSize = false;
		zoomWidth = zoomMaxWidth;
		zoomFactor = 100;
		setZoomButtons();
		SetMaxZoomWidth();
		resize(zoomWidth, showPAR->Checked);
	}

	void VideoPlayer::setZoomButtons()
	{
		if (zoomFactor >= 100)
		{
			zoomInButton->Enabled = false;
			zoomOutButton->Enabled = true;
		}
		else if (zoomFactor - zoomFactorStepSize > zoomFactorStepSize)
		{
			zoomInButton->Enabled = true;

			int iZoomWidth = static_cast<int>(zoomMaxWidth * (zoomFactor - zoomFactorStepSize) / 100);
			if (buttonPanel->Location->X + buttonPanelMinWidth < iZoomWidth)
				zoomOutButton->Enabled = true;
			else
				zoomOutButton->Enabled = false;
		}
		else
		{
			zoomInButton->Enabled = true;
			zoomOutButton->Enabled = false;
		}

	}

	void VideoPlayer::zoomInButton_Click(QObject *sender, QEvent *e)
	{
		if (zoomFactor > 100)
			return;

		if (zoomFactor < 100)
		{
			zoomFactor += zoomFactorStepSize;
			if (zoomFactor > 100)
				zoomFactor = 100;
			setZoomButtons();
			zoomWidth = static_cast<int>(zoomMaxWidth * zoomFactor / 100);
			resize(zoomWidth, showPAR->Checked);
		}
		else if (zoomFactor == 100)
		{
			originalSizeButton_Click(0, 0);
		}
	}

	void VideoPlayer::zoomOutButton_Click(QObject *sender, QEvent *e)
	{
		if (zoomFactor > 100)
		{
			btnFitScreen_Click(0, 0);
			return;
		}

		if (zoomFactor - zoomFactorStepSize > zoomFactorStepSize)
		{
			zoomFactor -= zoomFactorStepSize;
			int iZoomWidth = static_cast<int>(zoomMaxWidth * zoomFactor / 100);
			if (buttonPanel->Location->X + buttonPanelMinWidth < iZoomWidth)
			{
				zoomWidth = iZoomWidth;
				resize(zoomWidth, showPAR->Checked);
			}
			else
				zoomFactor += zoomFactorStepSize;
			setZoomButtons();
		}
	}

	void VideoPlayer::SetMaxZoomWidth()
	{
		Size *oSizeScreen = Screen::GetWorkingArea(this)->Size;
		int iScreenHeight = oSizeScreen->Height - 2 * SystemInformation::FixedFrameBorderSize->Height;
		int iScreenWidth = oSizeScreen->Width - 2 * SystemInformation::FixedFrameBorderSize->Width;

		// does the video fit into the screen?
		if (static_cast<int>(file->getVideoInfo()->Height) + formHeightDelta > iScreenHeight || static_cast<int>(file->getVideoInfo()->Width) > iScreenWidth)
		{
			Dar d = Dar(file->getVideoInfo()->Width, file->getVideoInfo()->Height);
			if (showPAR->Checked)
				Nullable<Dar> tempVar = arChooser.getValue();
				d = tempVar::HasValue ? tempVar : d;

			int height = 0;
			if (static_cast<int>(file->getVideoInfo()->Width) > iScreenWidth)
			{
				zoomMaxWidth = iScreenWidth;
				height = static_cast<int>(Math::Round(static_cast<decimal>(zoomMaxWidth) / d.getAR()));
				if (height + formHeightDelta > iScreenHeight)
				{
					height = iScreenHeight - formHeightDelta;
					zoomMaxWidth = static_cast<int>(Math::Round(static_cast<decimal>(height) * d.getAR()));
				}
			}
			else
			{
				height = iScreenHeight - formHeightDelta;
				zoomMaxWidth = static_cast<int>(Math::Round(static_cast<decimal>(height) * d.getAR()));
			}
			videoWindowWidth = zoomMaxWidth;
			videoWindowHeight = height;
		}
		else
		{
			zoomMaxWidth = static_cast<int>(file->getVideoInfo()->Width);
			videoWindowWidth = zoomMaxWidth;
			videoWindowHeight = static_cast<int>(file->getVideoInfo()->Height);
		}

		if (zoomFactor != 100)
		{
			zoomWidth = static_cast<int>(zoomMaxWidth * zoomFactor / 100);
			Dar d = Dar(file->getVideoInfo()->Width, file->getVideoInfo()->Height);
			if (showPAR->Checked)
				Nullable<Dar> tempVar2 = arChooser.getValue();
				d = tempVar2::HasValue ? tempVar2 : d;
			int height = static_cast<int>(Math::Round(static_cast<decimal>(zoomWidth) / d.getAR()));
			videoWindowWidth = zoomWidth;
			videoWindowHeight = static_cast<int>(height);
		}

		if (zoomMaxWidth < zoomWidth)
			if (!bOriginalSize)
				btnFitScreen_Click(0, 0);
			else
				originalSizeButton_Click(0, 0);
	}

	void VideoPlayer::doInitialAdjustment()
	{
		switch (this->viewerType)
		{
			case REGULAR:
				buttonPanel->Controls->Remove(creditsStartButton);
				buttonPanel->Controls->Remove(introEndButton);
				buttonPanel->Controls->Remove(chapterButton);
				buttonPanel->Controls->Remove(zoneStartButton);
				buttonPanel->Controls->Remove(zoneEndButton);
				buttonPanel->Controls->Remove(setZoneButton);
				break;
			case ZONES:
				buttonPanel->Controls->Remove(creditsStartButton);
				buttonPanel->Controls->Remove(introEndButton);
				buttonPanel->Controls->Remove(chapterButton);
				break;
			case CREDITS:
				buttonPanel->Controls->Remove(zoneStartButton);
				buttonPanel->Controls->Remove(zoneEndButton);
				buttonPanel->Controls->Remove(setZoneButton);
				buttonPanel->Controls->Remove(chapterButton);
				break;
			case CHAPTERS:
				buttonPanel->Controls->Remove(creditsStartButton);
				buttonPanel->Controls->Remove(introEndButton);
				buttonPanel->Controls->Remove(zoneStartButton);
				buttonPanel->Controls->Remove(zoneEndButton);
				buttonPanel->Controls->Remove(setZoneButton);
				break;
		}
	}

	void VideoPlayer::adjustSize()
	{
		if (!hasAR)
		{
			buttonPanel->Controls->Remove(arChooser);
			buttonPanel->Controls->Remove(showPAR);
		}
		SuspendLayout();

		// resize main window
		sizeLock = true;
		int iMainHeight = this->videoWindowHeight + formHeightDelta;
		int iMainWidth = this->videoWindowWidth + 2 * SystemInformation::FixedFrameBorderSize->Width + 2;
		if (bOriginalSize)
		{
			Size *oSizeScreen = Screen::GetWorkingArea(this)->Size;
			int iScreenHeight = oSizeScreen->Height - 2 * SystemInformation::FixedFrameBorderSize->Height;
			int iScreenWidth = oSizeScreen->Width - 2 * SystemInformation::FixedFrameBorderSize->Width;

			if (iMainHeight >= iScreenHeight)
				iMainHeight = iScreenHeight;

			if (iMainWidth >= iScreenWidth)
				iMainWidth = iScreenWidth;
		}
		if (iMainWidth - 2 * SystemInformation::FixedFrameBorderSize->Width - 2 < buttonPanelMinWidth)
			iMainWidth = buttonPanelMinWidth + 2 * SystemInformation::FixedFrameBorderSize->Width;
		this->Size = new Size(iMainWidth, iMainHeight);

		// resize videoPanel
		this->videoPanel->Size = new Size(iMainWidth - 2 * SystemInformation::FixedFrameBorderSize->Width, iMainHeight - formHeightDelta + 2);
		sizeLock = false;

		// resize videoPreview
		this->videoPreview->Size = new Size(this->videoWindowWidth, this->videoWindowHeight);

		// resize buttonPanel
		this->buttonPanel->Size = new Size(iMainWidth - 2 * SystemInformation::FixedFrameBorderSize->Width, buttonPanel->Height);
		this->buttonPanel->Location = new Point(1, videoPanel->Location->Y + videoPanel->Size->Height);
		ResumeLayout();
	}

	void VideoPlayer::formResized(QObject *sender, QEvent *e)
	{
		if (!sizeLock)
		{
			Control *formControl = static_cast<Control*>(sender);
			if ((formControl->Width <= this->MaximumSize->Width) && (formControl->Height <= this->MaximumSize->Height) && (formControl->Width >= this->MinimumSize->Width) && (formControl->Height >= this->MinimumSize->Height))
			{
				// Unusable without events from .NET 2.0 
				resize(formControl->Width, showPAR->Checked);
			}
		}
	}

	void VideoPlayer::Dispose(bool disposing)
	{
		if (disposing)
		{
			if (components != 0)
			{
				delete components;
			}
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void VideoPlayer::OnClosing(CancelQEvent *e)
	{
		if (!this->getAllowClose())
		{
			e->Cancel = true;
			return;
		}

		if (file != 0)
			delete file;
		System::Windows::Forms::Form::OnClosing(e);
	}

	void VideoPlayer::InitializeComponent()
	{
		this->components = new System::ComponentModel::Container();
		System::Windows::Forms::Button *goToFrameButton;
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(VideoPlayer::typeid);
		this->contextMenu1 = new System::Windows::Forms::ContextMenu();
		this->mnuIntroEnd = new System::Windows::Forms::MenuItem();
		this->mnuCreditsStart = new System::Windows::Forms::MenuItem();
		this->mnuZoneStart = new System::Windows::Forms::MenuItem();
		this->mnuZoneEnd = new System::Windows::Forms::MenuItem();
		this->playButton = new System::Windows::Forms::Button();
		this->nextFrameButton = new System::Windows::Forms::Button();
		this->previousFrameButton = new System::Windows::Forms::Button();
		this->ffButton = new System::Windows::Forms::Button();
		this->fwdButton = new System::Windows::Forms::Button();
		this->creditsStartButton = new System::Windows::Forms::Button();
		this->buttonPanel = new System::Windows::Forms::Panel();
		this->positionSlider = new System::Windows::Forms::TrackBar();
		this->btnFitScreen = new System::Windows::Forms::Button();
		this->btnReloadVideo = new System::Windows::Forms::Button();
		this->zoomOutButton = new System::Windows::Forms::Button();
		this->zoomInButton = new System::Windows::Forms::Button();
		this->arChooser = new MeXgui::core::gui::ARChooser();
		this->showPAR = new System::Windows::Forms::CheckBox();
		this->originalSizeButton = new System::Windows::Forms::Button();
		this->introEndButton = new System::Windows::Forms::Button();
		this->zoneStartButton = new System::Windows::Forms::Button();
		this->setZoneButton = new System::Windows::Forms::Button();
		this->zoneEndButton = new System::Windows::Forms::Button();
		this->chapterButton = new System::Windows::Forms::Button();
		this->defaultToolTip = new System::Windows::Forms::ToolTip(this->components);
		this->videoPanel = new System::Windows::Forms::Panel();
		this->videoPreview = new MeXgui::core::gui::VideoPlayerControl();
		goToFrameButton = new System::Windows::Forms::Button();
		this->buttonPanel->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->positionSlider))->BeginInit();
		this->videoPanel->SuspendLayout();
		this->SuspendLayout();
		// 
		// goToFrameButton
		// 
		goToFrameButton->Location = new System::Drawing::Point(4, 73);
		goToFrameButton->Name = "goToFrameButton";
		goToFrameButton->Size = new System::Drawing::Size(82, 18);
		goToFrameButton->TabIndex = 13;
		goToFrameButton->Text = "Go to frame";
		goToFrameButton->Click += new System::EventHandler(this, &VideoPlayer::goToFrameButton_Click);
		// 
		// contextMenu1
		// 
		this->contextMenu1->MenuItems->AddRange(new System::Windows::Forms::MenuItem[4] {this->mnuIntroEnd, this->mnuCreditsStart, this->mnuZoneStart, this->mnuZoneEnd});
		this->contextMenu1->Popup += new System::EventHandler(this, &VideoPlayer::contextMenu1_Popup);
		// 
		// mnuIntroEnd
		// 
		this->mnuIntroEnd->Index = 0;
		this->mnuIntroEnd->Shortcut = System::Windows::Forms::Shortcut::CtrlI;
		this->mnuIntroEnd->ShowShortcut = false;
		this->mnuIntroEnd->Text = "Go to End of &Intro";
		this->mnuIntroEnd->Click += new System::EventHandler(this, &VideoPlayer::mnuIntroEnd_Click);
		// 
		// mnuCreditsStart
		// 
		this->mnuCreditsStart->Index = 1;
		this->mnuCreditsStart->Shortcut = System::Windows::Forms::Shortcut::CtrlC;
		this->mnuCreditsStart->ShowShortcut = false;
		this->mnuCreditsStart->Text = "Go to Start of &Credits";
		this->mnuCreditsStart->Click += new System::EventHandler(this, &VideoPlayer::mnuCreditsStart_Click);
		// 
		// mnuZoneStart
		// 
		this->mnuZoneStart->Index = 2;
		this->mnuZoneStart->Shortcut = System::Windows::Forms::Shortcut::CtrlS;
		this->mnuZoneStart->ShowShortcut = false;
		this->mnuZoneStart->Text = "Go to &Start of Zone";
		this->mnuZoneStart->Click += new System::EventHandler(this, &VideoPlayer::mnuZoneStart_Click);
		// 
		// mnuZoneEnd
		// 
		this->mnuZoneEnd->Index = 3;
		this->mnuZoneEnd->Shortcut = System::Windows::Forms::Shortcut::CtrlE;
		this->mnuZoneEnd->ShowShortcut = false;
		this->mnuZoneEnd->Text = "Go to &End of Zone";
		this->mnuZoneEnd->Click += new System::EventHandler(this, &VideoPlayer::mnuZoneEnd_Click);
		// 
		// playButton
		// 
		this->playButton->Location = new System::Drawing::Point(50, 49);
		this->playButton->Name = "playButton";
		this->playButton->Size = new System::Drawing::Size(40, 18);
		this->playButton->TabIndex = 4;
		this->playButton->Text = "Play";
		this->defaultToolTip->SetToolTip(this->playButton, "play");
		this->playButton->Click += new System::EventHandler(this, &VideoPlayer::playButton_Click);
		// 
		// nextFrameButton
		// 
		this->nextFrameButton->Location = new System::Drawing::Point(120, 49);
		this->nextFrameButton->Name = "nextFrameButton";
		this->nextFrameButton->Size = new System::Drawing::Size(16, 18);
		this->nextFrameButton->TabIndex = 6;
		this->nextFrameButton->Text = ">";
		this->defaultToolTip->SetToolTip(this->nextFrameButton, "Advance by 1 frame");
		this->nextFrameButton->Click += new System::EventHandler(this, &VideoPlayer::nextFrameButton_Click);
		this->nextFrameButton->KeyDown += new System::Windows::Forms::KeyEventHandler(this, &VideoPlayer::nextFrameButton_KeyDown);
		// 
		// previousFrameButton
		// 
		this->previousFrameButton->Location = new System::Drawing::Point(4, 49);
		this->previousFrameButton->Name = "previousFrameButton";
		this->previousFrameButton->Size = new System::Drawing::Size(16, 18);
		this->previousFrameButton->TabIndex = 2;
		this->previousFrameButton->Text = "<";
		this->defaultToolTip->SetToolTip(this->previousFrameButton, "Go back 1 frame");
		this->previousFrameButton->Click += new System::EventHandler(this, &VideoPlayer::previousFrameButton_Click);
		this->previousFrameButton->KeyDown += new System::Windows::Forms::KeyEventHandler(this, &VideoPlayer::previousFrameButton_KeyDown);
		// 
		// ffButton
		// 
		this->ffButton->Location = new System::Drawing::Point(90, 49);
		this->ffButton->Name = "ffButton";
		this->ffButton->Size = new System::Drawing::Size(30, 18);
		this->ffButton->TabIndex = 5;
		this->ffButton->Text = ">>";
		this->defaultToolTip->SetToolTip(this->ffButton, "Advance 25 frames");
		this->ffButton->Click += new System::EventHandler(this, &VideoPlayer::ffButton_Click);
		// 
		// fwdButton
		// 
		this->fwdButton->Location = new System::Drawing::Point(20, 49);
		this->fwdButton->Name = "fwdButton";
		this->fwdButton->Size = new System::Drawing::Size(30, 18);
		this->fwdButton->TabIndex = 3;
		this->fwdButton->Text = "<<";
		this->defaultToolTip->SetToolTip(this->fwdButton, "Go back 25 frames");
		this->fwdButton->Click += new System::EventHandler(this, &VideoPlayer::fwdButton_Click);
		// 
		// creditsStartButton
		// 
		this->creditsStartButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->creditsStartButton->Location = new System::Drawing::Point(380, 73);
		this->creditsStartButton->Name = "creditsStartButton";
		this->creditsStartButton->Size = new System::Drawing::Size(44, 18);
		this->creditsStartButton->TabIndex = 20;
		this->creditsStartButton->Text = "Credits";
		this->defaultToolTip->SetToolTip(this->creditsStartButton, "Set the frame where the credits start");
		this->creditsStartButton->Click += new System::EventHandler(this, &VideoPlayer::creditsStartButton_Click);
		// 
		// buttonPanel
		// 
		this->buttonPanel->Controls->Add(this->positionSlider);
		this->buttonPanel->Controls->Add(this->btnFitScreen);
		this->buttonPanel->Controls->Add(this->btnReloadVideo);
		this->buttonPanel->Controls->Add(this->zoomOutButton);
		this->buttonPanel->Controls->Add(this->zoomInButton);
		this->buttonPanel->Controls->Add(this->arChooser);
		this->buttonPanel->Controls->Add(this->showPAR);
		this->buttonPanel->Controls->Add(this->originalSizeButton);
		this->buttonPanel->Controls->Add(this->introEndButton);
		this->buttonPanel->Controls->Add(this->previousFrameButton);
		this->buttonPanel->Controls->Add(this->fwdButton);
		this->buttonPanel->Controls->Add(this->playButton);
		this->buttonPanel->Controls->Add(this->ffButton);
		this->buttonPanel->Controls->Add(this->nextFrameButton);
		this->buttonPanel->Controls->Add(this->zoneStartButton);
		this->buttonPanel->Controls->Add(this->creditsStartButton);
		this->buttonPanel->Controls->Add(goToFrameButton);
		this->buttonPanel->Controls->Add(this->setZoneButton);
		this->buttonPanel->Controls->Add(this->zoneEndButton);
		this->buttonPanel->Controls->Add(this->chapterButton);
		this->buttonPanel->Location = new System::Drawing::Point(1, 225);
		this->buttonPanel->Margin = new System::Windows::Forms::Padding(0);
		this->buttonPanel->Name = "buttonPanel";
		this->buttonPanel->Size = new System::Drawing::Size(500, 97);
		this->buttonPanel->TabIndex = 8;
		// 
		// positionSlider
		// 
		this->positionSlider->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
		this->positionSlider->LargeChange = 1000;
		this->positionSlider->Location = new System::Drawing::Point(0, 3);
		this->positionSlider->Margin = new System::Windows::Forms::Padding(0);
		this->positionSlider->Minimum = -1;
		this->positionSlider->Name = "positionSlider";
		this->positionSlider->Size = new System::Drawing::Size(500, 45);
		this->positionSlider->TabIndex = 1;
		this->positionSlider->TickFrequency = 1500;
		this->positionSlider->TickStyle = System::Windows::Forms::TickStyle::Both;
		this->positionSlider->Value = -1;
		this->positionSlider->Scroll += new System::EventHandler(this, &VideoPlayer::positionSlider_Scroll);
		// 
		// btnFitScreen
		// 
		this->btnFitScreen->Location = new System::Drawing::Point(189, 49);
		this->btnFitScreen->Name = "btnFitScreen";
		this->btnFitScreen->Size = new System::Drawing::Size(26, 19);
		this->btnFitScreen->TabIndex = 9;
		this->btnFitScreen->Text = "Fit";
		this->defaultToolTip->SetToolTip(this->btnFitScreen, "resets the zoom to the maximum screen size");
		this->btnFitScreen->UseVisualStyleBackColor = true;
		this->btnFitScreen->Click += new System::EventHandler(this, &VideoPlayer::btnFitScreen_Click);
		// 
		// btnReloadVideo
		// 
		this->btnReloadVideo->Location = new System::Drawing::Point(90, 73);
		this->btnReloadVideo->Name = "btnReloadVideo";
		this->btnReloadVideo->Size = new System::Drawing::Size(79, 18);
		this->btnReloadVideo->TabIndex = 14;
		this->btnReloadVideo->Text = "Reload Video";
		this->defaultToolTip->SetToolTip(this->btnReloadVideo, "Reload the video file");
		this->btnReloadVideo->Click += new System::EventHandler(this, &VideoPlayer::btnReloadVideo_Click);
		// 
		// zoomOutButton
		// 
		this->zoomOutButton->Location = new System::Drawing::Point(215, 49);
		this->zoomOutButton->Name = "zoomOutButton";
		this->zoomOutButton->Size = new System::Drawing::Size(17, 19);
		this->zoomOutButton->TabIndex = 10;
		this->zoomOutButton->Text = "-";
		this->defaultToolTip->SetToolTip(this->zoomOutButton, "zoom out");
		this->zoomOutButton->UseVisualStyleBackColor = true;
		this->zoomOutButton->Click += new System::EventHandler(this, &VideoPlayer::zoomOutButton_Click);
		// 
		// zoomInButton
		// 
		this->zoomInButton->Location = new System::Drawing::Point(145, 49);
		this->zoomInButton->Name = "zoomInButton";
		this->zoomInButton->Size = new System::Drawing::Size(14, 19);
		this->zoomInButton->TabIndex = 7;
		this->zoomInButton->Text = "+";
		this->defaultToolTip->SetToolTip(this->zoomInButton, "zoom in");
		this->zoomInButton->UseVisualStyleBackColor = true;
		this->zoomInButton->Click += new System::EventHandler(this, &VideoPlayer::zoomInButton_Click);
		// 
		// arChooser
		// 
		this->arChooser->setCustomDARs(new MeXgui::core::util::Dar[0]);
		this->arChooser->setHasLater(false);
		this->arChooser->Location = new System::Drawing::Point(241, 45);
		this->arChooser->MaximumSize = new System::Drawing::Size(1000, 29);
		this->arChooser->MinimumSize = new System::Drawing::Size(64, 29);
		this->arChooser->Name = "arChooser";
		this->arChooser->setSelectedIndex(0);
		this->arChooser->Size = new System::Drawing::Size(170, 29);
		this->arChooser->TabIndex = 11;
		this->arChooser->SelectionChanged += new MeXgui::StringChanged(this, &VideoPlayer::arChooser_SelectionChanged);
		// 
		// showPAR
		// 
		this->showPAR->AutoSize = true;
		this->showPAR->Location = new System::Drawing::Point(415, 51);
		this->showPAR->Name = "showPAR";
		this->showPAR->Size = new System::Drawing::Size(88, 17);
		this->showPAR->TabIndex = 12;
		this->showPAR->Text = "Preview DAR";
		this->showPAR->UseVisualStyleBackColor = true;
		this->showPAR->CheckedChanged += new System::EventHandler(this, &VideoPlayer::showPAR_CheckedChanged);
		// 
		// originalSizeButton
		// 
		this->originalSizeButton->Location = new System::Drawing::Point(159, 49);
		this->originalSizeButton->Name = "originalSizeButton";
		this->originalSizeButton->Size = new System::Drawing::Size(30, 19);
		this->originalSizeButton->TabIndex = 8;
		this->originalSizeButton->Text = "1:1";
		this->defaultToolTip->SetToolTip(this->originalSizeButton, "displays the original video size");
		this->originalSizeButton->Click += new System::EventHandler(this, &VideoPlayer::originalSizeButton_Click);
		// 
		// introEndButton
		// 
		this->introEndButton->Location = new System::Drawing::Point(338, 73);
		this->introEndButton->Name = "introEndButton";
		this->introEndButton->Size = new System::Drawing::Size(38, 18);
		this->introEndButton->TabIndex = 18;
		this->introEndButton->Text = "Intro";
		this->defaultToolTip->SetToolTip(this->introEndButton, "Set the frame where the intro ends");
		this->introEndButton->Click += new System::EventHandler(this, &VideoPlayer::introEndButton_Click);
		// 
		// zoneStartButton
		// 
		this->zoneStartButton->Location = new System::Drawing::Point(172, 73);
		this->zoneStartButton->Name = "zoneStartButton";
		this->zoneStartButton->Size = new System::Drawing::Size(64, 18);
		this->zoneStartButton->TabIndex = 15;
		this->zoneStartButton->Text = "Zone Start";
		this->defaultToolTip->SetToolTip(this->zoneStartButton, "Sets the start frame of a new zone");
		this->zoneStartButton->Click += new System::EventHandler(this, &VideoPlayer::zoneStartButton_Click);
		// 
		// setZoneButton
		// 
		this->setZoneButton->Location = new System::Drawing::Point(306, 73);
		this->setZoneButton->Name = "setZoneButton";
		this->setZoneButton->Size = new System::Drawing::Size(30, 18);
		this->setZoneButton->TabIndex = 17;
		this->setZoneButton->Text = "Set";
		this->defaultToolTip->SetToolTip(this->setZoneButton, "Adds the zone to the codec configuration");
		this->setZoneButton->Click += new System::EventHandler(this, &VideoPlayer::setZoneButton_Click);
		// 
		// zoneEndButton
		// 
		this->zoneEndButton->Location = new System::Drawing::Point(239, 73);
		this->zoneEndButton->Name = "zoneEndButton";
		this->zoneEndButton->Size = new System::Drawing::Size(64, 18);
		this->zoneEndButton->TabIndex = 16;
		this->zoneEndButton->Text = "Zone End";
		this->defaultToolTip->SetToolTip(this->zoneEndButton, "Sets the end frame of a new zone");
		this->zoneEndButton->Click += new System::EventHandler(this, &VideoPlayer::zoneEndButton_Click);
		// 
		// chapterButton
		// 
		this->chapterButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->chapterButton->Location = new System::Drawing::Point(338, 73);
		this->chapterButton->Name = "chapterButton";
		this->chapterButton->Size = new System::Drawing::Size(72, 18);
		this->chapterButton->TabIndex = 19;
		this->chapterButton->Text = "Set Chapter";
		this->defaultToolTip->SetToolTip(this->chapterButton, "Sets the end frame of a new zone");
		this->chapterButton->Click += new System::EventHandler(this, &VideoPlayer::chapterButton_Click);
		// 
		// videoPanel
		// 
		this->videoPanel->AutoScroll = true;
		this->videoPanel->Controls->Add(this->videoPreview);
		this->videoPanel->Location = new System::Drawing::Point(0, 0);
		this->videoPanel->Margin = new System::Windows::Forms::Padding(0);
		this->videoPanel->Name = "videoPanel";
		this->videoPanel->Size = new System::Drawing::Size(399, 225);
		this->videoPanel->TabIndex = 11;
		// 
		// videoPreview
		// 
		this->videoPreview->setCropMargin(new System::Windows::Forms::Padding(0));
		this->videoPreview->setDisplayActualFramerate(false);
		this->videoPreview->setEnsureCorrectPlaybackSpeed(false);
		this->videoPreview->setFramerate(25);
		this->videoPreview->Location = new System::Drawing::Point(1, 1);
		this->videoPreview->Margin = new System::Windows::Forms::Padding(0);
		this->videoPreview->Name = "videoPreview";
		this->videoPreview->setPosition(-1);
		this->videoPreview->Size = new System::Drawing::Size(274, 164);
		this->videoPreview->setSpeedUp(1);
		this->videoPreview->TabIndex = 11;
		this->videoPreview->PositionChanged += new System::EventHandler(this, &VideoPlayer::videoPreview_PositionChanged);
		// 
		// VideoPlayer
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->ClientSize = new System::Drawing::Size(518, 327);
		this->Controls->Add(this->videoPanel);
		this->Controls->Add(this->buttonPanel);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->Name = "VideoPlayer";
		this->Text = "VideoPlayer";
		this->Shown += new System::EventHandler(this, &VideoPlayer::VideoPlayer_Shown);
		this->buttonPanel->ResumeLayout(false);
		this->buttonPanel->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->positionSlider))->EndInit();
		this->videoPanel->ResumeLayout(false);
		this->ResumeLayout(false);

	}

	void VideoPlayer::positionSlider_Scroll(QObject *sender, System::QEvent *e)
	{
		setCurrentFrame(positionSlider->Value);
	}

	void VideoPlayer::setTitleText()
	{
		totalTime = Util::converFrameNumberToTimecode(this->positionSlider->Maximum, file->getVideoInfo()->FPS);
		currentTime = Util::converFrameNumberToTimecode(this->positionSlider->Value, file->getVideoInfo()->FPS);
		if (this->zoneStart > -1 || this->zoneEnd > -1)
		{
			this->Text = "Pos: " + getCurrentFrame() + "/" + (getFrameCount() - 1);

			this->Text += " Zone start: " + (zoneStart > -1 ? StringConverterHelper::toString(zoneStart) : "?");
			this->Text += " end: " + (zoneEnd > -1 ? StringConverterHelper::toString(zoneEnd) : "?");
		}
		else
			this->Text = "Current position: " + getCurrentFrame() + "/" + (getFrameCount() - 1);
		if (this->introEndFrame > -1)
			this->Text += " Intro end: " + this->introEndFrame;
		if (this->creditsStartFrame > -1)
			this->Text += " Credits start: " + this->creditsStartFrame;
		if (mainForm->getSettings()->getAddTimePosition())
			this->Text += "   -   " + currentTime + "/" + totalTime;
	}

	void VideoPlayer::crop(CropValues *cropping)
	{
		crop(cropping->left, cropping->top, cropping->right, cropping->bottom);
	}

	void VideoPlayer::crop(int left, int top, int right, int bottom)
	{
		if (videoPreview->getCropMargin()->Left != left)
		{
			videoPanel->HorizontalScroll->Value = videoPanel->HorizontalScroll->Minimum;
			videoPanel->HorizontalScroll->Value = videoPanel->HorizontalScroll->Minimum;
		}
		else if (videoPreview->getCropMargin()->Right != right)
		{
			videoPanel->HorizontalScroll->Value = videoPanel->HorizontalScroll->Maximum;
			videoPanel->HorizontalScroll->Value = videoPanel->HorizontalScroll->Maximum;
		}
		if (videoPreview->getCropMargin()->Top != top)
		{
			videoPanel->VerticalScroll->Value = videoPanel->VerticalScroll->Minimum;
			videoPanel->VerticalScroll->Value = videoPanel->VerticalScroll->Minimum;
		}
		else if (videoPreview->getCropMargin()->Bottom != bottom)
		{
			videoPanel->VerticalScroll->Value = videoPanel->VerticalScroll->Maximum;
			videoPanel->VerticalScroll->Value = videoPanel->VerticalScroll->Maximum;
		}

		videoPreview->setCropMargin(new Padding(left, top, right, bottom));
	}

	void VideoPlayer::playButton_Click(QObject *sender, System::QEvent *e)
	{
		if (this->playButton->Text->Equals("Play"))
		{
			this->playButton->Text = "Stop";
			videoPreview->setEnsureCorrectPlaybackSpeed(mainForm->getSettings()->getEnsureCorrectPlaybackSpeed());
			videoPreview->Play();
		}
		else
		{
			this->playButton->Text = "Play";
			videoPreview->Stop();
		}
	}

	void VideoPlayer::previousFrameButton_Click(QObject *sender, System::QEvent *e)
	{
		videoPreview->OffsetPosition(-1);
	}

	void VideoPlayer::nextFrameButton_Click(QObject *sender, System::QEvent *e)
	{
		videoPreview->OffsetPosition(1);
	}

	void VideoPlayer::fwdButton_Click(QObject *sender, System::QEvent *e)
	{
		videoPreview->OffsetPosition(-25);
	}

	void VideoPlayer::ffButton_Click(QObject *sender, System::QEvent *e)
	{
		videoPreview->OffsetPosition(25);
	}

	void VideoPlayer::creditsStartButton_Click(QObject *sender, System::QEvent *e)
	{
		IntroCreditsFrameSet(getCurrentFrame(), true);
	}

	void VideoPlayer::introEndButton_Click(QObject *sender, System::QEvent *e)
	{
		IntroCreditsFrameSet(getCurrentFrame(), false);
	}

	void VideoPlayer::zoneEndButton_Click(QObject *sender, System::QEvent *e)
	{
		int pos = getCurrentFrame();
		if (creditsStartFrame > -1 && pos >= creditsStartFrame)
		{
			MessageBox::Show("Zone end intersects with credits zone\nPlease adjust zone end or credits zone", "Zone interesection detected", MessageBoxButtons::OK, MessageBoxIcon::Stop);
		}
		else
		{
			setZoneEnd(pos);
		}
	}

	void VideoPlayer::zoneStartButton_Click(QObject *sender, System::QEvent *e)
	{
		int pos = getCurrentFrame();
		if (pos > this->introEndFrame) // else we have an intersection with the credits which is not allowed
		{
			if (this->creditsStartFrame > -1 && pos >= creditsStartFrame) // zone starts inside credits zone, not allowed
			{
				MessageBox::Show("Zone start intersects with credits zone\nPlease adjust zone start or credits zone", "Zone interesection detected", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			}
			else
			{
				setZoneStart(pos);
			}
		}
		else
			MessageBox::Show("Zone start intersects with with intro zone\nPlease adjust zone start or intro zone.", "Zone intersection detected", MessageBoxButtons::OK, MessageBoxIcon::Stop);
	}

	void VideoPlayer::setZoneButton_Click(QObject *sender, System::QEvent *e)
	{
		if (ZoneSet != 0)
		{
			if (zoneEnd > zoneStart)
			{
				ZoneSet(this->zoneStart, this->zoneEnd);
				zoneStart = -1;
				zoneEnd = -1;
				setTitleText();
			}
			else
				MessageBox::Show("The end of a zone must be after its start", "Invalid zone configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
		}
	}

	void VideoPlayer::chapterButton_Click(QObject *sender, System::QEvent *e)
	{
		ChapterSet(getCurrentFrame());
	}

	void VideoPlayer::mnuIntroEnd_Click(QObject *sender, System::QEvent *e)
	{
		setCurrentFrame(introEndFrame);

	}

	void VideoPlayer::mnuCreditsStart_Click(QObject *sender, System::QEvent *e)
	{
		this->positionSlider->Value = this->creditsStartFrame;
		positionSlider_Scroll(0, 0);
	}

	void VideoPlayer::mnuZoneStart_Click(QObject *sender, System::QEvent *e)
	{
		 setCurrentFrame(creditsStartFrame);
	}

	void VideoPlayer::mnuZoneEnd_Click(QObject *sender, System::QEvent *e)
	{
		setCurrentFrame(zoneEnd);
	}

	void VideoPlayer::contextMenu1_Popup(QObject *sender, System::QEvent *e)
	{
		if (this->introEndFrame > -1)
			this->mnuIntroEnd->Enabled = true;
		else
			this->mnuIntroEnd->Enabled = false;
		if (this->creditsStartFrame > -1)
			this->mnuCreditsStart->Enabled = true;
		else
			this->mnuCreditsStart->Enabled = false;
		if (this->zoneStart > -1)
			this->mnuZoneStart->Enabled = true;
		else
			this->mnuZoneStart->Enabled = false;
		if (this->zoneEnd > -1)
			this->mnuZoneEnd->Enabled = true;
		else
			this->mnuZoneEnd->Enabled = false;
	}

	const Nullable<Dar> &VideoPlayer::getDAR() const
	{
		return arChooser->getValue();
	}

	void VideoPlayer::setDAR(const Nullable<Dar> &value)
	{
		arChooser->setValue(value);
	}

	const IVideoReader &VideoPlayer::getReader() const
	{
		return this->reader;
	}

	const IMediaFile &VideoPlayer::getFile() const
	{
		return this->file;
	}

	const int &VideoPlayer::getCreditsStart() const
	{
		return this->creditsStartFrame;
	}

	void VideoPlayer::setCreditsStart(const int &value)
	{
		creditsStartFrame = value;
		setTitleText();
	}

	const int &VideoPlayer::getIntroEnd() const
	{
		return this->introEndFrame;
	}

	void VideoPlayer::setIntroEnd(const int &value)
	{
		introEndFrame = value;
		setTitleText();
	}

	const int &VideoPlayer::getZoneStart() const
	{
		return this->zoneStart;
	}

	void VideoPlayer::setZoneStart(const int &value)
	{
		zoneStart = value;
		//positionSlider_Scroll(null, null);
		setTitleText();
	}

	const int &VideoPlayer::getZoneEnd() const
	{
		return this->zoneEnd;
	}

	void VideoPlayer::setZoneEnd(const int &value)
	{
		zoneEnd = value;
		setTitleText();
	}

	const double &VideoPlayer::getFramerate() const
	{
		return file->getVideoInfo()->FPS;
	}

	const int &VideoPlayer::getCurrentFrame() const
	{
		return videoPreview->getPosition();
	}

	void VideoPlayer::setCurrentFrame(const int &value)
	{
		videoPreview->setPosition(value);
	}

	const int &VideoPlayer::getFrameCount() const
	{
		return videoPreview->getFrameCount();
	}

	void VideoPlayer::resize(int targetWidth, bool PAR)
	{
		zoomWidth = targetWidth;
		Dar d = Dar(file->getVideoInfo()->Width, file->getVideoInfo()->Height);
		if (PAR)
			Nullable<Dar> tempVar = arChooser.getValue();
			d = tempVar::HasValue ? tempVar : d;

		int height = static_cast<int>(Math::Round(static_cast<decimal>(targetWidth) / d.getAR()));

		videoWindowWidth = targetWidth;
		videoWindowHeight = static_cast<int>(height);
		sizeLock = true;
		adjustSize();
		VideoPlayer_Shown(0, 0);
		sizeLock = false;
	}

	void VideoPlayer::showPAR_CheckedChanged(QObject *sender, QEvent *e)
	{
		SetMaxZoomWidth();
		resize(videoWindowWidth, showPAR->Checked);
	}

	void VideoPlayer::goToFrameButton_Click(QObject *sender, QEvent *e)
	{
		decimal val;
		bool bTopMost = this->TopMost;
		this->TopMost = false;
		if (NumberChooser::show("Enter a frame number:", "Go to frame", 0, positionSlider->Minimum, positionSlider->Maximum, positionSlider->Value, val) == System::Windows::Forms::DialogResult::OK)
		{
			positionSlider->Value = static_cast<int>(val);
			positionSlider_Scroll(0, 0);
		}
		this->TopMost = bTopMost;
	}

	void VideoPlayer::arChooser_SelectionChanged(QObject *sender, const QString &val)
	{
		SetMaxZoomWidth();
		resize(videoWindowWidth, showPAR->Checked);
	}

	void VideoPlayer::nextFrameButton_KeyDown(QObject *sender, KeyQEvent *e)
	{
		if (e->KeyCode == Keys::Right)
			videoPreview->OffsetPosition(1);
	}

	void VideoPlayer::previousFrameButton_KeyDown(QObject *sender, KeyQEvent *e)
	{
		if (e->KeyCode == Keys::Right)
			videoPreview->OffsetPosition(-1);
	}

	void VideoPlayer::videoPreview_PositionChanged(QObject *sender, QEvent *e)
	{
		positionSlider->Value = videoPreview->getPosition();
		setTitleText();
	}

	void VideoPlayer::btnReloadVideo_Click(QObject *sender, QEvent *e)
	{
		if (playButton->Text->Equals("Stop"))
		{
			this->playButton->Text = "Play";
			videoPreview->Stop();
		}
		reloadVideo();
		positionSlider->Focus();
	}

	void VideoPlayer::VideoPlayer_Shown(QObject *sender, QEvent *e)
	{
		Size *oSizeScreen = Screen::GetWorkingArea(this)->Size;
		Point *oLocation = Screen::GetWorkingArea(this)->Location;
		int iScreenHeight = oSizeScreen->Height - 2 * SystemInformation::FixedFrameBorderSize->Height;
		int iScreenWidth = oSizeScreen->Width - 2 * SystemInformation::FixedFrameBorderSize->Width;

		if (this->Size->Height >= iScreenHeight)
			this->Location = new Point(this->Location->X, oLocation->Y + 5);
		else if (this->Location->Y <= oLocation->Y)
			this->Location = new Point(this->Location->X, oLocation->Y + 5);
		else if (this->Location->Y + this->Size->Height > iScreenHeight)
			this->Location = new Point(this->Location->X, iScreenHeight - this->Size->Height);

		if (this->Size->Width >= iScreenWidth)
			this->Location = new Point(oLocation->X + 3, this->Location->Y);
		else if (this->Location->X <= oLocation->X)
			this->Location = new Point(oLocation->X + 3, this->Location->Y);
		else if (this->Location->X + this->Size->Width > iScreenWidth)
			this->Location = new Point(iScreenWidth - this->Size->Width, this->Location->Y);
	}

	void VideoPlayer::InitializeInstanceFields()
	{
		hasAR = false;
		creditsStartFrame = -1
		introEndFrame = -1;
		zoneStart = -1
		zoneEnd = -1;
		zoomFactorStepSize = 15;
		mainForm = MainForm::Instance;
	}
}
