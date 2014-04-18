#pragma once

#include "core/gui/VideoPlayer.h"
#include "core/gui/MeXgui.MainForm.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include "VideoCodecSettings.h"
#include "core/details/mux/MuxProvider.h"
#include "core/details/CodecManager.h"
#include "core/gui/FileBar.h"
#include "core/gui/MeXgui.FileBar.h"
#include "core/details/MeXgui.JobChain.h"
#include "core/details/mux/MuxJob.h"
#include "core/details/MeXgui.SequentialChain.h"
#include "core/util/LogItem.h"
#include "core/util/AudioUtil.h"
#include "packages/tools/avscreator/AviSynthJob.h"
#include "core/util/Util.h"
#include "core/gui/MeXgui.ZonesWindow.h"
#include "core/gui/MeXgui.ConfigableProfilesControl.h"
#include <QString>

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




//using namespace System::Collections::Generic;



//using namespace System::Data;





//using namespace System::Text;



using namespace MeXgui::core::details;
using namespace MeXgui::core::details::video;
using namespace MeXgui::core::gui;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::video;

namespace MeXgui
{
	class VideoEncodingComponent : public UserControl
	{
	private:
		VideoPlayer *player; // window that shows a preview of the video
		MainForm *mainForm;

		VideoInfo *info;
	public:
		double FrameRate;
		public:
		~VideoEncodingComponent()
		{
			this->Dispose(true);
		}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
		private:
		void Finalize()
		{
			this->Dispose(false);
		}

	private:
		void initVideoInfo();
	public:
		const VideoInfo &getInfo() const;
		const QString &getFileType() const;
		void setFileType(const QString &value);


		const VideoCodecSettings &getCurrentSettings() const;

	private:
		MeXgui::VideoEncoderProvider *videoEncoderProvider;
	public:
		VideoEncodingComponent();
		const QString &getVideoInput() const;
		void setVideoInput(const QString &value);
		const QString &getVideoOutput() const;
		void setVideoOutput(const QString &value);
		const VideoType &getCurrentVideoOutputType() const;
		const bool &getPrerenderJob() const;
		void setPrerenderJob(const bool &value);
	private:
		void videoInput_FileSelected(FileBar *sender, FileBarEventArgs *args);

		void videoOutput_FileSelected(FileBar *sender, FileBarEventArgs *args);
		/// <summary>
		/// opens the AviSynth preview for a given AviSynth script
		/// gets the properties of the video, registers the callbacks, updates the video bitrate (we know the lenght of the video now) and updates the commandline
		/// with the scriptname
		/// </summary>
		/// <param name="fileName">the AviSynth script to be opened</param>
		void openAvisynthScript(const QString &fileName);


		void VideoInput_DoubleClick();
		void queueVideoButton_Click();

		bool bInitialStart;
		void fileType_SelectedIndexChanged();
		/// <summary>
		/// enables / disables output fields depending on the codec configuration
		/// </summary>
		void updateIOConfig();
		/// <summary>
		/// verifies the input, output and logfile configuration
		/// based on the codec and encoding mode certain fields must be filled out
		/// </summary>
		/// <returns>null if no error; otherwise string error message</returns>
	public:
		QString verifyVideoSettings();
		const MuxableType &getCurrentMuxableVideoType() const;
		void openVideoFile(const QString &fileName);
	private:
		bool isFirstPass();


	public:
		void ClosePlayer();

		void hidePlayer();

		void showPlayer();
		/// <summary>
		/// callback for the video player window closing
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
	private:
		void player_Closed();
		/// <summary>
		/// sets the intro end / credits start frame
		/// </summary>
		/// <param name="frameNumber">the frame number</param>
		/// <param name="isCredits">true if the credits start frame is to be set, false if the intro end is to be set</param>
		void player_IntroCreditsFrameSet(int frameNumber, bool isCredits);
		/// <summary>
		/// iterates through all zones and makes sure we get no intersection by applying the current credits settings
		/// </summary>
		/// <param name="creditsStartFrame">the credits start frame</param>
		/// <returns>returns true if there is no intersetion between zones and credits and false if there is an intersection</returns>
		bool validateCredits(int creditsStartFrame);
		/// <summary>
		/// iteratees through all zones and makes sure we get no intersection by applying the current intro settings
		/// </summary>
		/// <param name="introEndFrame">the frame where the intro ends</param>
		/// <returns>true if the intro zone does not interesect with a zone, false otherwise</returns>
		bool validateIntro(int introEndFrame);
	public:
		const MeXgui::VideoEncoderProvider &getVideoEncoderProvider() const;

		void Reset();

	private:
		void addAnalysisPass_Click();

		VideoEncoderType *lastCodec;
		void videoProfile_SelectedProfileChanged();

		void editZonesButton_Click();

		void videopreview_Click();


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


		System::Windows::Forms::Label *videoOutputLabel;
		System::Windows::Forms::Label *videoInputLabel;
		System::Windows::Forms::Button *queueVideoButton;
		System::Windows::Forms::Button *addAnalysisPass;
		FileBar *videoInput;
		FileBar *videoOutput;
		System::Windows::Forms::GroupBox *groupBox1;
		System::Windows::Forms::Label *label1;
		MeXgui::core::gui::ConfigableProfilesControl *videoProfile;
		System::Windows::Forms::Label *label2;
		System::Windows::Forms::Button *editZonesButton;
		System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;
		System::Windows::Forms::ComboBox *fileType;
		System::Windows::Forms::Button *videopreview;
		System::Windows::Forms::CheckBox *addPrerenderJob;


	private:
		void InitializeInstanceFields();
	};
}
