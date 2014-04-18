#pragma once

#include "core/plugins/interfaces/IMediaFile.h"
#include "MeGUI.MainForm.h"
#include "ARChooser.h"
#include "MeGUI.core.gui.VideoPlayerControl.h"
#include "packages/reader/avs/AvsReader.h"
#include "packages/tools/avscreator/AvisynthWrapper.h"
#include "core/util/LogItem.h"
#include "core/util/DAR.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include "core/util/Util.h"
#include "core/util/VideoUtil.h"
#include "MeGUI.core.gui.NumberChooser.h"
#include <QString>
#include <cmath>
#include <stdexcept>
#include "stringconverter.h"

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
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














//using namespace System::Threading;



using namespace MeGUI::core::gui;
using namespace MeGUI::core::util;

namespace MeGUI
{
	typedef void (*IntroCreditsFrameSetCallback)(int frameNumber, bool isCredits);
	typedef void (*ZoneSetCallback)(int start, int end);
	typedef void (*ChapterSetCallback)(int frameNumber);
	typedef void (*SimpleDelegate)();
	enum PREVIEWTYPE
	{
		REGULAR,
		CREDITS,
		ZONES,
		CHAPTERS
	};
	/// <summary>
	/// The video player is used to preview an AviSynth script or DGIndex project. 
	/// It can also be used to set the credits and intro and is used to generate zones visually
	/// </summary>
	class VideoPlayer : public System::Windows::Forms::Form
	{


//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event IntroCreditsFrameSetCallback IntroCreditsFrameSet; // event to update the status in the GUI
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event ZoneSetCallback ZoneSet;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event ChapterSetCallback ChapterSet;

	private:
		IMediaFile *file;
		IVideoReader *reader;
		bool hasAR;
		int creditsStartFrame, introEndFrame;
		int zoneStart, zoneEnd; // zone start and end frames
		int formHeightDelta; // height delta of the form versus the size of the VideoPlayerControl (the reference for the gui size)
		static const int defaultSpacing = 8; // default spacing from GUI elements
		int videoWindowWidth, videoWindowHeight;
		PREVIEWTYPE viewerType;
		static bool sizeLock; // recursion lock for resize event handler
		int zoomWidth;
		int zoomMaxWidth; // max width so that it can be seen completly on the screen
		int zoomFactor; // relation between zoomWidth and zoomMaxWidth (0-100%)
		int zoomFactorStepSize; // during zoom in/out this step size wil be used
		int buttonPanelMinWidth;
		bool bOriginalSize;
		QString totalTime;
		QString currentTime;
		MainForm *mainForm;
		QString strFileName; // the video file name
		bool bInlineAVS;

		System::Windows::Forms::Button *playButton;
		System::Windows::Forms::Button *nextFrameButton;
		System::Windows::Forms::Button *previousFrameButton;
		System::Windows::Forms::Button *ffButton;
		System::Windows::Forms::Button *fwdButton;
		System::Windows::Forms::Button *creditsStartButton;
		System::Windows::Forms::Panel *buttonPanel;
		System::Windows::Forms::Button *zoneStartButton;
		System::Windows::Forms::Button *zoneEndButton;
		System::Windows::Forms::Button *setZoneButton;
		System::Windows::Forms::ContextMenu *contextMenu1;
		System::Windows::Forms::MenuItem *mnuZoneStart;
		System::Windows::Forms::MenuItem *mnuZoneEnd;
		System::Windows::Forms::MenuItem *mnuIntroEnd;
		System::Windows::Forms::MenuItem *mnuCreditsStart;
		System::Windows::Forms::Button *introEndButton;
		System::Windows::Forms::ToolTip *defaultToolTip;
		System::Windows::Forms::Button *chapterButton;
		Button *originalSizeButton;
		CheckBox *showPAR;
		ARChooser *arChooser;
		Button *zoomInButton;
		Button *zoomOutButton;
		Button *btnReloadVideo;
		Button *btnFitScreen;
		TrackBar *positionSlider;
		Panel *videoPanel;
		VideoPlayerControl *videoPreview;
		System::ComponentModel::IContainer *components;
		public:
		~VideoPlayer()
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
		VideoPlayer();

		void setAllowClose(const bool &value);
		const bool &getAllowClose() const;

		/// <summary>
		/// loads the video, sets up the proper window size and enables / disables the GUI buttons depending on the
		/// preview type set
		/// </summary>
		/// <param name="path">path of the video file to be loaded</param>
		/// <param name="type">type of window</param>
		/// <returns>true if the video could be opened, false if not</returns>
		bool loadVideo(MainForm *mainForm, const QString &path, PREVIEWTYPE type, bool hasAR);

		/// <summary>
		/// loads the video, sets up the proper window size and enables / disables the GUI buttons depending on the
		/// preview type set
		/// </summary>
		/// <param name="path">path of the video file to be loaded</param>
		/// <param name="type">type of window</param>
		/// <param name="inlineAvs">true if path contain not filename but avsynth script to be parsed</param>
		/// <param name="startFrame">Select a specific frame to start off with or -1 for middle of video</param>
		/// <returns>true if the video could be opened, false if not</returns>
		bool loadVideo(MainForm *mainForm, const QString &path, PREVIEWTYPE type, bool hasAR, bool inlineAvs, int startFrame, bool originalSize);

		/// <summary>
		/// reloads the video, sets up the proper window size and enables / disables the GUI buttons depending on the
		/// preview type set
		/// </summary>
		/// <returns>true if the video could be opened, false if not</returns>
		bool reloadVideo();
		/// <summary>
		/// disables intro and credits setting
		/// </summary>
		void disableIntroAndCredits();
		/// <summary>
		/// Reset the video preview to the size of the input stream
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
	private:
		void originalSizeButton_Click(QObject *sender, QEvent *e);
		/// <summary>
		/// Reset the video preview to fit the input stream
		/// </summary>
	public:
		void SetScreenSize();
		/// <summary>
		/// Reset the video preview to fit the input stream
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
	private:
		void btnFitScreen_Click(QObject *sender, QEvent *e);
		void setZoomButtons();
		void zoomInButton_Click(QObject *sender, QEvent *e);
		void zoomOutButton_Click(QObject *sender, QEvent *e);
		/// <summary>
		/// sets the maximum zoom width so that the video fits the screen including controls
		/// </summary>
		void SetMaxZoomWidth();
		void doInitialAdjustment();
		/// <summary>
		/// adjusts the size of the GUI to match the source video
		/// </summary>
		void adjustSize();
		void formResized(QObject *sender, QEvent *e);
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		void Dispose(bool disposing);
		/// <summary>
		/// performs additional tasks when the window is closed
		/// ensures that if the AviReader/d2vreader is valid, access to the file is properly closed
		/// </summary>
		/// <param name="e"></param>
	protected:
		virtual void OnClosing(CancelQEvent *e);
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
	private:
		void InitializeComponent();
		/// <summary>
		/// Sets the Position property on the videoPreview Control via gotoFrame to render the new frame.
		/// The PositionChanged-EventHandler then updates the window's title
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void positionSlider_Scroll(QObject *sender, System::QEvent *e);
		/// <summary>
		/// sets the text in the title bar in function of the position, credits and zone settings
		/// </summary>
		void setTitleText();
	public:
		void crop(CropValues *cropping);
		/// <summary>
		/// sets the cropping values for this player
		/// </summary>
		/// <param name="left">number of pixels to crop from the left</param>
		/// <param name="top">number of pixels to crop from the top</param>
		/// <param name="right">number of pixels to crop from the right</param>
		/// <param name="bottom">number of pixels to crop from the bottom</param>
		void crop(int left, int top, int right, int bottom);
		/// <summary>
		/// handles the play button
		/// starts video playback or stops it
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
	private:
		void playButton_Click(QObject *sender, System::QEvent *e);

		void previousFrameButton_Click(QObject *sender, System::QEvent *e);

		void nextFrameButton_Click(QObject *sender, System::QEvent *e);

		void fwdButton_Click(QObject *sender, System::QEvent *e);

		void ffButton_Click(QObject *sender, System::QEvent *e);
		/// <summary>
		/// fires an event indicating the credits start position has been set.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void creditsStartButton_Click(QObject *sender, System::QEvent *e);
		/// <summary>
		/// fires an event indicating that the intro end position has been set
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void introEndButton_Click(QObject *sender, System::QEvent *e);
		void zoneEndButton_Click(QObject *sender, System::QEvent *e);

		void zoneStartButton_Click(QObject *sender, System::QEvent *e);

		void setZoneButton_Click(QObject *sender, System::QEvent *e);
		void chapterButton_Click(QObject *sender, System::QEvent *e);
		void mnuIntroEnd_Click(QObject *sender, System::QEvent *e);

		void mnuCreditsStart_Click(QObject *sender, System::QEvent *e);

		void mnuZoneStart_Click(QObject *sender, System::QEvent *e);

		void mnuZoneEnd_Click(QObject *sender, System::QEvent *e);
		void contextMenu1_Popup(QObject *sender, System::QEvent *e);
	public:
		const Nullable<Dar> &getDAR() const;
		void setDAR(const Nullable<Dar> &value);

		/// <summary>
		/// returns the underlying video reader
		/// </summary>
		/// <returns>the VideoReader object used by this window for the preview</returns>
		const IVideoReader &getReader() const;
		/// <summary>
		/// returns the underlying media file
		/// </summary>
		/// <returns>the IMediaFile used by this window for the preview</returns>
		const IMediaFile &getFile() const;
		/// <summary>
		/// gets /sets the frame where the credits start
		/// </summary>
		const int &getCreditsStart() const;
		void setCreditsStart(const int &value);
		/// <summary>
		/// gets / sets the frame where the intro ends
		/// </summary>
		const int &getIntroEnd() const;
		void setIntroEnd(const int &value);
		/// <summary>
		/// gets / sets the frame where the current zone starts
		/// </summary>
		const int &getZoneStart() const;
		void setZoneStart(const int &value);
		/// <summary>
		/// gets / sets the frame where the current zone starts
		/// </summary>
		const int &getZoneEnd() const;
		void setZoneEnd(const int &value);
		/// <summary>
		/// gets the framerate of the video that is currently loaded
		/// </summary>
		const double &getFramerate() const;
		/// <summary>
		/// gets / sets the frame currently visible
		/// </summary>
		const int &getCurrentFrame() const;
		void setCurrentFrame(const int &value);
		const int &getFrameCount() const;

	private:
		void resize(int targetWidth, bool PAR);

		void showPAR_CheckedChanged(QObject *sender, QEvent *e);

		void goToFrameButton_Click(QObject *sender, QEvent *e);

		void arChooser_SelectionChanged(QObject *sender, const QString &val);

		void nextFrameButton_KeyDown(QObject *sender, KeyQEvent *e);

		void previousFrameButton_KeyDown(QObject *sender, KeyQEvent *e);

		void videoPreview_PositionChanged(QObject *sender, QEvent *e);

		void btnReloadVideo_Click(QObject *sender, QEvent *e);

		void VideoPlayer_Shown(QObject *sender, QEvent *e);

	private:
		void InitializeInstanceFields();
	};
}
