#pragma once

#include "core/util/LogItem.h"
#include "core/details/AudioTrackInfo.h"
#include "core/gui/MeXgui.MainForm.h"
#include "core/util/VideoUtil.h"
#include "core/util/JobUtil.h"
#include "core/gui/FileBar.h"
#include "core/gui/MeXgui.FileBar.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/Drives.h"
#include "core/details/MeXgui.JobChain.h"
#include "packages/demuxer/pgcdemux/PgcDemuxJob.h"
#include "core/details/MeXgui.SequentialChain.h"
#include "FFMSIndexJob.h"
#include "packages/demuxer/mkvextract/MkvExtractJob.h"
#include "D2VIndexJob.h"
#include "DGIIndexJob.h"
#include "DGAIndexJob.h"
#include "core/gui/MeXgui.HelpButton.h"
#include <QString>
#include <QVector>
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


namespace MeXgui
{
	class FileIndexerWindow : public System::Windows::Forms::Form
	{
	public:
		enum IndexType
		{
			D2V,
			DGA,
			DGI,
			FFMS,
			AVISOURCE,
			NONE
		};

	private:
		LogItem *_oLog;
		IndexType IndexerUsed;
		QString strVideoCodec;
		QString strVideoScanType;
		QString strContainerFormat;
		QVector<AudioTrackInfo*> audioTracks;
		bool dialogMode; // $%£%$^>*"%$%%$#{"!!! Affects the public behaviour!
		bool configured;
		MainForm *mainForm;
		VideoUtil *vUtil;
		JobUtil *jobUtil;

		public:
		~FileIndexerWindow()
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
		void setConfig(const QString &input, const QString &projectName, int demuxType, bool showCloseOnQueue, bool closeOnQueue, bool loadOnComplete, bool updateMode);

		FileIndexerWindow(MainForm *mainForm);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public FileIndexerWindow(MainForm mainForm, string fileName) : this(mainForm)
		FileIndexerWindow(MainForm *mainForm, const QString &fileName);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public FileIndexerWindow(MainForm mainForm, string fileName, bool autoReturn) : this(mainForm, fileName)
		FileIndexerWindow(MainForm *mainForm, const QString &fileName, bool autoReturn);

	private:
		void CheckDGIIndexer();

		void changeIndexer(IndexType dgType);
		void pickOutputButton_Click();

		void input_FileSelected(FileBar *sender, FileBarEventArgs *args);
		void openVideo(const QString &fileName);

		void generateAudioList();

		/// <summary>
		/// recommend input settings based upon the input file
		/// </summary>
		void recommendSettings();

		/// <summary>
		/// sets the output file name
		/// </summary>
		void setOutputFileName();

		/// <summary>
		/// creates a project
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void queueButton_Click();
		void checkIndexIO();
		D2VIndexJob *generateD2VIndexJob(const QString &videoInput);
		DGIIndexJob *generateDGNVIndexJob(const QString &videoInput);
		DGAIndexJob *generateDGAIndexJob(const QString &videoInput);
		FFMSIndexJob *generateFFMSIndexJob(const QString &videoInput);

		void rbtracks_CheckedChanged();

		void btnFFMS_Click();

		void btnDGI_Click();

		void btnDGA_Click();

		void btnD2V_Click();


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

		System::Windows::Forms::GroupBox *gbAudio;
		System::Windows::Forms::GroupBox *gbOutput;
		System::Windows::Forms::Label *inputLabel;
		System::Windows::Forms::TextBox *output;
		System::Windows::Forms::Label *outputLabel;
		System::Windows::Forms::SaveFileDialog *saveProjectDialog;
		System::Windows::Forms::Button *pickOutputButton;
		System::Windows::Forms::GroupBox *gbInput;
		System::Windows::Forms::RadioButton *demuxTracks;
		System::Windows::Forms::RadioButton *demuxNoAudiotracks;
		System::Windows::Forms::Button *queueButton;
		System::Windows::Forms::CheckBox *loadOnComplete;
		System::Windows::Forms::CheckBox *closeOnQueue;
		MeXgui::core::gui::HelpButton *helpButton1;
		System::Windows::Forms::CheckedListBox *AudioTracks;
		System::Windows::Forms::RadioButton *demuxAll;
		FileBar *input;
		System::Windows::Forms::CheckBox *demuxVideo;
		System::Windows::Forms::GroupBox *gbIndexer;
		System::Windows::Forms::RadioButton *btnDGI;
		System::Windows::Forms::RadioButton *btnD2V;
		System::Windows::Forms::RadioButton *btnFFMS;
		System::Windows::Forms::RadioButton *btnDGA;
		System::Windows::Forms::GroupBox *gbFileInformation;
		System::Windows::Forms::Label *lblContainer;
		System::Windows::Forms::Label *lblScanType;
		System::Windows::Forms::Label *lblCodec;
		System::Windows::Forms::TextBox *txtCodecInformation;
		System::Windows::Forms::TextBox *txtContainerInformation;
		System::Windows::Forms::TextBox *txtScanTypeInformation;
		System::Windows::Forms::Label *lblPGC;
		System::Windows::Forms::ComboBox *cbPGC;

	private:
		void InitializeInstanceFields();
	};
}
