#pragma once

#include "MuxStreamControl.h"
#include "core/util/DAR.h"
#include "core/gui/MainForm.h"
#include "core/details/MeXguiSettings.h"
#include "MuxProvider.h"
#include "core/plugins/interfaces/IMuxing.h"
#include "core/gui/FileBar.h"
#include "core/gui/TargetSizeSCBox.h"
#include "core/gui/FPSChooser.h"
#include "core/gui/HelpButton.h"
#include "core/util/FileSize.h"
#include "core/gui/FileBar.h"
#include "core/details/CodecManager.h"
#include "core/details/Streams.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include "core/util/LogItem.h"
#include "core/util/VideoUtil.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/FileUtil.h"
#include <QString>
#include <QVector>
#include <cctype>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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









using namespace MeXgui::core::details;
using namespace MeXgui::core::details::mux;
using namespace MeXgui::core::util;

namespace MeXgui
{
	/// <summary>
	/// Summary description for 
	/// </summary>
	class baseMuxWindow : public System::Windows::Forms::Form
	{
	protected:
		QVector<MuxStreamControl*> audioTracks;
		QVector<MuxStreamControl*> subtitleTracks;


		Nullable<Dar> dar;
		QString audioFilter, videoInputFilter, subtitleFilter, chaptersFilter, outputFilter;
		MainForm *mainForm;
	private:
		MeXguiSettings *settings;
	protected:
		Label *videoInputLabel;
		OpenFileDialog *openFileDialog;
		Button *muxButton;
		Label *MuxFPSLabel;
		Label *chaptersInputLabel;
		Label *muxedOutputLabel;
		SaveFileDialog *saveFileDialog;
		GroupBox *videoGroupbox;
		GroupBox *outputGroupbox;
		GroupBox *chaptersGroupbox;
		TextBox *videoName;
		Label *videoNameLabel;
	private:
		MuxProvider *muxProvider;
	protected:
		Panel *audioPanel;
		IMuxing *muxer;

		TabControl *audio;
	private:
		TabPage *audioPage1;
		MeXgui::core::details::mux::MuxStreamControl *muxStreamControl2;
		ContextMenuStrip *audioMenu;
		ContextMenuStrip *subtitleMenu;
		ToolStripMenuItem *audioAddTrack;
		ToolStripMenuItem *audioRemoveTrack;
		ToolStripMenuItem *subtitleAddTrack;
		ToolStripMenuItem *subtitleRemoveTrack;
	protected:
		Panel *subtitlePanel;
		TabControl *subtitles;
	private:
		TabPage *subPage1;
		MeXgui::core::details::mux::MuxStreamControl *muxStreamControl1;
	protected:
		FileBar *vInput;
		FileBar *chapters;
		Label *splittingLabel;
		MeXgui::core::gui::TargetSizeSCBox *splitting;
		FileBar *output;
		MeXgui::core::gui::FPSChooser *fps;
	private:
		TableLayoutPanel *tableLayoutPanel1;
		TableLayoutPanel *tableLayoutPanel2;
		TableLayoutPanel *tableLayoutPanel3;
		TableLayoutPanel *tableLayoutPanel4;
		MeXgui::core::gui::HelpButton *helpButton1;
	protected:
		ComboBox *cbType;
		Label *label1;
		ComboBox *cbContainer;
		Label *lbContainer;
		Button *removeVideoTrack;
		CheckBox *chkCloseOnQueue;
	private:
		IContainer *components;
		public:
		~baseMuxWindow()
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
		baseMuxWindow();
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public baseMuxWindow(MainForm mainForm, IMuxing muxer) : this()
		baseMuxWindow(MainForm *mainForm, IMuxing *muxer);
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
	private:
		void Dispose(bool disposing);
		/// <summary>
		/// sets the configuration of the GUI
		/// used when a job is loaded (jobs have everything already filled out)
		/// </summary>
		/// <param name="videoInput">the video input (raw or mp4)</param>
		/// <param name="framerate">framerate of the input</param>
		/// <param name="audioStreams">the audiostreams</param>
		/// <param name="subtitleStreams">the subtitle streams</param>
		/// <param name="output">name of the output</param>
		/// <param name="splitSize">split size of the output</param>
	public:
		void setConfig(const QString &videoInput, const QString &videoName, Nullable<decimal> framerate, MuxStream audioStreams[], MuxStream subtitleStreams[], const QString &chapterFile, const QString &output, Nullable<FileSize> splitSize, Nullable<Dar> dar, const QString &deviceType);
		/// <summary>
		/// gets the additionally configured stream configuration from this window
		/// this method is used when the muxwindow is created from the AutoEncodeWindow in order to configure audio languages
		/// add subtitles and chapters
		/// </summary>
		/// <param name="aStreams">the configured audio streams(language assignments)</param>
		/// <param name="sStreams">the newly added subtitle streams</param>
		/// <param name="chapterFile">the assigned chapter file</param>
		void getAdditionalStreams(MuxStream aStreams[], MuxStream sStreams[], QString &chapterFile);

	private:
		MuxStream *getStreams(QVector<MuxStreamControl*> &controls);
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent();
	protected:
		virtual void Subtitle_FileSelected();
		virtual void Audio_FileSelected();
		virtual void checkIO();

		void chkDefaultStream_CheckedChanged();

	private:
		void splitSize_KeyPress(object *sender, System::Windows::Forms::KeyPressEventArgs *e);
	protected:
		virtual bool isFPSRequired();

	private:
		void vInput_FileSelected(FileBar *sender, FileBarEventArgs *args);

	protected:
		virtual void ChangeOutputExtension();

	private:
		void chooseOutputFilename();

		void chapters_FileSelected(FileBar *sender, FileBarEventArgs *args);
		void fps_SelectionChanged(object *sender, const QString &val);
	protected:
		virtual void fileUpdated();
		virtual void upDeviceTypes();


	private:
		void audioAddTrack_Click();

	protected:
		void AudioAddTrack();

	private:
		void audioRemoveTrack_Click();

	protected:
		void AudioRemoveTrack();

	private:
		void subtitleAddTrack_Click();

	protected:
		void SubtitleAddTrack();

	private:
		void subtitleRemoveTrack_Click();

	protected:
		void SubtitleRemoveTrack();

	private:
		void audioMenu_Opening(object *sender, CancelEventArgs *e);

		void subtitleMenu_Opening(object *sender, CancelEventArgs *e);

		void muxStreamControl1_FileUpdated();

		void muxStreamControl2_FileUpdated();

		void cbContainer_SelectedIndexChanged();

		void output_Click();

		void removeVideoTrack_Click();

		void cbType_SelectedIndexChanged();
	};
}
