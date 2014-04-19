#pragma once

#include "core/util/LogItem.h"
#include "OneClickStreamControl.h"
#include "OneClickSettings.h"
#include "core/details/CodecManager.h"
#include "core/util/VideoUtil.h"
#include "core/gui/MainForm.h"
#include "core/details/mux/MuxProvider.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/details/video/VideoCodecSettings.h"
#include "core/details/MeXguiSettings.h"
#include "core/util/EnumProxy.h"
#include "core/util/DragDropUtil.h"
#include "core/util/PrettyFormatting.h"
#include "core/gui/FileBar.h"
#include "core/gui/FileBar.h"
#include "OneClickWindow.h"
#include "OneClickProcessing.h"
#include "core/gui/InputBox.h"
#include "OneClickStream.h"
#include "core/details/AudioTrackInfo.h"
#include "core/details/SubtitleTrackInfo.h"
#include "core/util/FileUtil.h"
#include "core/details/JobChain.h"
#include "OneClickPostprocessingProperties.h"
#include "packages/tools/avscreator/AviSynthSettings.h"
#include "core/util/IFOparser.h"
#include "packages/demuxer/pgcdemux/PgcDemuxJob.h"
#include "core/details/SequentialChain.h"
#include "packages/tools/hdbdextractor/HDStreamsExJob.h"
#include "packages/tools/fileindexer/FileIndexerWindow.h"
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
#include "core/gui/HelpButton.h"
#include "core/gui/ConfigableProfilesControl.h"
#include "core/gui/FileSCBox.h"
#include "core/gui/ARChooser.h"
#include "core/gui/TargetSizeSCBox.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include "core/util/DAR.h"
#include "core/util/FileSize.h"
#include <QString>
#include <QVector>
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




//using namespace System::Collections::Generic;







//using namespace System::Text;



using namespace MeXgui::core::details;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::oneclick;


namespace MeXgui
{
	class OneClickWindow : public System::Windows::Forms::Form
	{
	private:
		LogItem *_oLog;
		QVector<OneClickStreamControl*> audioTracks;
		QVector<OneClickStreamControl*> subtitleTracks;
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

		void OneClickProfileChanged();
		const VideoCodecSettings &getVideoSettings() const;
		void initAudioHandler();

	public:
		OneClickWindow(MainForm *mainForm);

	private:
		void cbGUIMode_SelectedIndexChanged();

		void containerFormat_SelectedIndexChanged();

		void updateWorkingName(const QString &strInputFile);

		void updateFilename();

		void input_SelectionChanged(object *sender, const QString &val);

		void setOutput(const QString &strFileName);

		void output_FileSelected(FileBar *sender, FileBarEventArgs *args);

		void setWorkingDirectory(const QString &strFolder);

		void workingDirectory_FileSelected(FileBar *sender, FileBarEventArgs *args);

		void workingName_TextChanged();

	public:
		void setInput(const QString &strFileorFolderName);

		void setInput(QString& strFileorFolderName[]);

	private:
		void openInput(const QString &fileName);

	public:
		void setOpenFailure();

		void setBatchProcessing(QVector<OneClickFilesToProcess*> &arrFilesToProcess, OneClickSettings *oSettings);

		void setInputData(MediaInfoFile *iFile, QVector<OneClickFilesToProcess*> &arrFilesToProcess);

	private:
		bool beingCalled;
		void updatePossibleContainers();

		void SetOneClickProfile(OneClickSettings *settings);

		void goButton_Click();

		void createOneClickJob(QVector<OneClickFilesToProcess*> &arrFilesToProcess);

		bool verifyInputSettings(MediaInfoFile *oVideoInputInfo, const QString &strWorkingDirectory);



		QString verifyStreamSettings();

		void audio1_SomethingChanged();

		void ProfileChanged();

		void keepInputResolution_CheckedChanged();

		void chkDontEncodeVideo_CheckedChanged();


		// Subtitle Track Handling
		void subtitleMenu_Opening(object *sender, CancelEventArgs *e);

		void subtitleAddTrack_Click();

		void subtitleRemoveTrack_Click();

		void SubtitleAddTrack(bool bChangeFocus);

		void SubtitleRemoveTrack(int iTabPageIndex);

		void chkDefaultStream_CheckedChanged();

		int iSelectedSubtitleTabPage;
		void subtitlesTab_MouseClick(object *sender, MouseEventArgs *e);

		void oneClickSubtitleStreamControl_FileUpdated();

		void SubtitleResetTrack(QVector<OneClickStream*> &arrSubtitleTrackInfo, OneClickSettings *settings);

		void subtitlesTab_MouseDoubleClick(object *sender, MouseEventArgs *e);


		// Audio Track Handling
		void audioMenu_Opening(object *sender, CancelEventArgs *e);

		void audioAddTrack_Click();

		void audioRemoveTrack_Click();

		void AudioAddTrack(bool bChangeFocus);

		void AudioRemoveTrack(int iTabPageIndex);

		int iSelectedAudioTabPage;
		void audioTab_MouseClick(object *sender, MouseEventArgs *e);

		void oneClickAudioStreamControl_FileUpdated();

		void AudioResetTrack(QVector<OneClickStream*> &arrAudioTrackInfo, OneClickSettings *settings);

		void ResetAudioSettings(OneClickSettings *settings);

		void audioTab_MouseDoubleClick(object *sender, MouseEventArgs *e);

		void OneClickWindow_Shown();

		void audioTab_SelectedIndexChanged();

		void audioTab_KeyUp(object *sender, KeyEventArgs *e);

		void subtitlesTab_SelectedIndexChanged();

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
		MeXgui::core::gui::HelpButton *helpButton1;
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
