#pragma once

#include "core/util/LogItem.h"
#include "MeGUI.OneClickStreamControl.h"
#include "OneClickSettings.h"
#include "core/details/CodecManager.h"
#include "core/util/VideoUtil.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/details/mux/MuxProvider.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/details/video/VideoCodecSettings.h"
#include "core/details/MeGUISettings.h"
#include "core/util/EnumProxy.h"
#include "core/util/DragDropUtil.h"
#include "core/util/PrettyFormatting.h"
#include "core/gui/FileBar.h"
#include "core/gui/MeGUI.FileBar.h"
#include "OneClickWindow.h"
#include "OneClickProcessing.h"
#include "core/gui/MeGUI.core.gui.InputBox.h"
#include "OneClickStream.h"
#include "core/details/AudioTrackInfo.h"
#include "core/details/SubtitleTrackInfo.h"
#include "core/util/FileUtil.h"
#include "core/details/MeGUI.core.details.JobChain.h"
#include "OneClickPostprocessingProperties.h"
#include "packages/tools/avscreator/AviSynthSettings.h"
#include "core/util/IFOparser.h"
#include "packages/demuxer/pgcdemux/PgcDemuxJob.h"
#include "core/details/MeGUI.core.details.SequentialChain.h"
#include "packages/tools/hdbdextractor/HDStreamsExJob.h"
#include "packages/tools/fileindexer/MeGUI.FileIndexerWindow.h"
#include "core/details/mux/MuxJob.h"
#include "core/details/TrackInfo.h"
#include "core/details/Streams.h"
#include "OneClickAudioTrack.h"
#include "packages/audio/AudioJob.h"
#include "packages/tools/vobsub/SubtitleIndexJob.h"
#include "packages/demuxer/mkvextract/MkvExtractJob.h"
#include "packages/tools/fileindexer/IndexJob.h"
#include "packages/tools/fileindexer/D2VIndexJob.h"
#include "packages/tools/fileindexer/DGAIndexJob.h"
#include "OneClickPostProcessingJob.h"
#include "packages/tools/fileindexer/DGIIndexJob.h"
#include "packages/tools/fileindexer/FFMSIndexJob.h"
#include "OneClickAudioControl.h"
#include "core/plugins/interfaces/Profile.h"
#include "core/gui/MeGUI.core.gui.HelpButton.h"
#include "core/gui/MeGUI.core.gui.ConfigableProfilesControl.h"
#include "core/gui/FileSCBox.h"
#include "core/gui/ARChooser.h"
#include "core/gui/TargetSizeSCBox.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include "core/util/DAR.h"
#include "core/util/FileSize.h"
#include <string>
#include <vector>
#include <algorithm>
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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::tools::oneclick;


namespace MeGUI
{
	class OneClickWindow : public System::Windows::Forms::Form
	{
	private:
		LogItem *_oLog;
		std::vector<OneClickStreamControl*> audioTracks;
		std::vector<OneClickStreamControl*> subtitleTracks;
		OneClickSettings *_oSettings;
		bool bLock;

		/// <summary>
		/// whether the current processing should be done without user interaction
		/// </summary>
		bool bAutomatedProcessing;

		/// <summary>
		/// whether the current processing is a part of batch processing
		/// </summary>
		bool bBatchProcessing;

		/// <summary>
		/// whether we ignore the restrictions on container output type set by the profile
		/// </summary>
		bool ignoreRestrictions;

		/// <summary>
		/// the restrictions from above: the only containers we may use
		/// </summary>
//ORIGINAL LINE: private ContainerType[] acceptableContainerTypes;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		ContainerType *acceptableContainerTypes;

		VideoUtil *vUtil;
		MainForm *mainForm;
		MuxProvider *muxProvider;
		MediaInfoFile *_videoInputInfo;

		/// <summary>
		/// whether the user has selected an output filename
		/// </summary>
		bool outputChosen;

		public:
		~OneClickWindow()
		{
			this->Dispose(true);
		}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
		private:
		void Finalize()
		{
			this->Dispose(false);
		}

		void initOneClickHandler();

		void initTabs();

		void OneClickProfileChanged(object *sender, EventArgs *e);
		const VideoCodecSettings &getVideoSettings() const;
		void initAudioHandler();

	public:
		OneClickWindow(MainForm *mainForm);

	private:
		void cbGUIMode_SelectedIndexChanged(object *sender, EventArgs *e);

		void containerFormat_SelectedIndexChanged(object *sender, EventArgs *e);

		void updateWorkingName(const std::string &strInputFile);

		void updateFilename();

		void input_SelectionChanged(object *sender, const std::string &val);

		void setOutput(const std::string &strFileName);

		void output_FileSelected(FileBar *sender, FileBarEventArgs *args);

		void setWorkingDirectory(const std::string &strFolder);

		void workingDirectory_FileSelected(FileBar *sender, FileBarEventArgs *args);

		void workingName_TextChanged(object *sender, EventArgs *e);

	public:
		void setInput(const std::string &strFileorFolderName);

		void setInput(std::string& strFileorFolderName[]);

	private:
		void openInput(const std::string &fileName);

	public:
		void setOpenFailure();

		void setBatchProcessing(std::vector<OneClickFilesToProcess*> &arrFilesToProcess, OneClickSettings *oSettings);

		void setInputData(MediaInfoFile *iFile, std::vector<OneClickFilesToProcess*> &arrFilesToProcess);

	private:
		bool beingCalled;
		void updatePossibleContainers();

		void SetOneClickProfile(OneClickSettings *settings);

		void goButton_Click(object *sender, EventArgs *e);

		void createOneClickJob(std::vector<OneClickFilesToProcess*> &arrFilesToProcess);

		bool verifyInputSettings(MediaInfoFile *oVideoInputInfo, const std::string &strWorkingDirectory);



		std::string verifyStreamSettings();

		void audio1_SomethingChanged(object *sender, EventArgs *e);

		void ProfileChanged(object *sender, EventArgs *e);

		void keepInputResolution_CheckedChanged(object *sender, EventArgs *e);

		void chkDontEncodeVideo_CheckedChanged(object *sender, EventArgs *e);


		// Subtitle Track Handling
		void subtitleMenu_Opening(object *sender, CancelEventArgs *e);

		void subtitleAddTrack_Click(object *sender, EventArgs *e);

		void subtitleRemoveTrack_Click(object *sender, EventArgs *e);

		void SubtitleAddTrack(bool bChangeFocus);

		void SubtitleRemoveTrack(int iTabPageIndex);

		void chkDefaultStream_CheckedChanged(object *sender, EventArgs *e);

		int iSelectedSubtitleTabPage;
		void subtitlesTab_MouseClick(object *sender, MouseEventArgs *e);

		void oneClickSubtitleStreamControl_FileUpdated(object *sender, EventArgs *e);

		void SubtitleResetTrack(std::vector<OneClickStream*> &arrSubtitleTrackInfo, OneClickSettings *settings);

		void subtitlesTab_MouseDoubleClick(object *sender, MouseEventArgs *e);


		// Audio Track Handling
		void audioMenu_Opening(object *sender, CancelEventArgs *e);

		void audioAddTrack_Click(object *sender, EventArgs *e);

		void audioRemoveTrack_Click(object *sender, EventArgs *e);

		void AudioAddTrack(bool bChangeFocus);

		void AudioRemoveTrack(int iTabPageIndex);

		int iSelectedAudioTabPage;
		void audioTab_MouseClick(object *sender, MouseEventArgs *e);

		void oneClickAudioStreamControl_FileUpdated(object *sender, EventArgs *e);

		void AudioResetTrack(std::vector<OneClickStream*> &arrAudioTrackInfo, OneClickSettings *settings);

		void ResetAudioSettings(OneClickSettings *settings);

		void audioTab_MouseDoubleClick(object *sender, MouseEventArgs *e);

		void OneClickWindow_Shown(object *sender, EventArgs *e);

		void audioTab_SelectedIndexChanged(object *sender, EventArgs *e);

		void audioTab_KeyUp(object *sender, KeyEventArgs *e);

		void subtitlesTab_SelectedIndexChanged(object *sender, EventArgs *e);

		void subtitlesTab_KeyUp(object *sender, KeyEventArgs *e);

		bool isDontEncodeAudioPossible(MediaInfoFile *iFile, bool bIsStandardTrack, ContainerType *inputContainer);


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


		System::Windows::Forms::TabPage *tabPage1;
		System::Windows::Forms::TabControl *tabControl1;
		System::Windows::Forms::OpenFileDialog *openFileDialog;
		System::Windows::Forms::TabPage *encoderConfigTab;
		System::Windows::Forms::Button *goButton;
		MeGUI::core::gui::HelpButton *helpButton1;
		System::Windows::Forms::CheckBox *openOnQueue;
		System::Windows::Forms::TabControl *subtitlesTab;
		System::Windows::Forms::ContextMenuStrip *subtitleMenu;
		System::Windows::Forms::ToolStripMenuItem *subtitleAddTrack;
		System::Windows::Forms::ToolStripMenuItem *subtitleRemoveTrack;
		System::Windows::Forms::TabPage *subPage0;
		OneClickStreamControl *oneClickSubtitleStreamControl1;
		System::Windows::Forms::TabControl *audioTab;
		System::Windows::Forms::ContextMenuStrip *audioMenu;
		System::Windows::Forms::ToolStripMenuItem *audioAddTrack;
		System::Windows::Forms::ToolStripMenuItem *audioRemoveTrack;
		System::Windows::Forms::TabPage *audioPage0;
		OneClickStreamControl *oneClickAudioStreamControl1;
		System::Windows::Forms::TabControl *outputTab;
		System::Windows::Forms::TabPage *tabPage4;
		core::gui::ConfigableProfilesControl *oneclickProfile;
		System::Windows::Forms::Label *label3;
		FileBar *output;
		System::Windows::Forms::Label *outputLabel;
		System::Windows::Forms::TabControl *videoTab;
		System::Windows::Forms::TabPage *tabPage3;
		core::gui::FileSCBox *input;
		System::Windows::Forms::Label *inputLabel;
		System::Windows::Forms::GroupBox *videoGroupBox;
		System::Windows::Forms::CheckBox *chkDontEncodeVideo;
		System::Windows::Forms::CheckBox *usechaptersmarks;
		System::Windows::Forms::Label *label4;
		core::gui::ConfigableProfilesControl *videoProfile;
		System::Windows::Forms::CheckBox *addPrerenderJob;
		System::Windows::Forms::GroupBox *groupBox1;
		System::Windows::Forms::ComboBox *devicetype;
		System::Windows::Forms::Label *deviceLabel;
		System::Windows::Forms::Label *containerFormatLabel;
		System::Windows::Forms::ComboBox *containerFormat;
		core::gui::TargetSizeSCBox *splitting;
		System::Windows::Forms::GroupBox *locationGroupBox;
		FileBar *chapterFile;
		FileBar *workingDirectory;
		System::Windows::Forms::Label *chapterLabel;
		System::Windows::Forms::Label *workingDirectoryLabel;
		System::Windows::Forms::TextBox *workingName;
		System::Windows::Forms::Label *projectNameLabel;
		System::Windows::Forms::GroupBox *avsBox;
		System::Windows::Forms::CheckBox *keepInputResolution;
		System::Windows::Forms::CheckBox *autoCrop;
		core::gui::ConfigableProfilesControl *avsProfile;
		core::gui::ARChooser *ar;
		System::Windows::Forms::CheckBox *autoDeint;
		System::Windows::Forms::CheckBox *signalAR;
		System::Windows::Forms::Label *outputResolutionLabel;
		System::Windows::Forms::NumericUpDown *horizontalResolution;
		System::Windows::Forms::Label *label2;
		System::Windows::Forms::Label *ARLabel;
		core::gui::TargetSizeSCBox *fileSize;
		System::Windows::Forms::Label *filesizeLabel;
		System::Windows::Forms::ComboBox *cbGUIMode;
		System::Windows::Forms::TabPage *tabPage2;
		System::Windows::Forms::TabPage *tabPage5;

	private:
		void InitializeInstanceFields();
	};
}
