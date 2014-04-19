#pragma once

#include "core/gui/MainForm.h"
#include "core/details/mux/MuxProvider.h"
#include "core/details/CodecManager.h"
#include "core/details/video/VideoCodecSettings.h"
#include "packages/audio/AudioJob.h"
#include "packages.tools.calculator.AudioTrackSizeTab.h"
#include "core/util/LogItem.h"
#include "packages.tools.calculator.ExtraSizeTab.h"
#include "core/details/Streams.h"
#include "core/util/FileSize.h"
#include "CalcData.h"
#include "core/gui/HelpButton.h"
#include "core/gui/TargetSizeSCBox.h"
#include "core/gui/FPSChooser.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include <QString>
#include <QVector>
#include <stdexcept>
#include "stringconverter.h"

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
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




//using namespace System::Linq;

//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;







using namespace MeXgui::core::details;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::calculator;
using namespace MeXgui::Properties;


//using namespace System::Text;

namespace MeXgui
{
	class Calculator : public System::Windows::Forms::Form
	{
	private:
		bool updatingContainers;
		MainForm *mainForm;
		MuxProvider *muxProvider;
		CodecManager *codecs;
		bool isUpdating;
		bool calculating;

		public:
		~Calculator()
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
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public Calculator(MainForm mainForm) : this()
		Calculator(MainForm *mainForm);

		/// <summary>
		/// sets video, audio and codec defaults
		/// </summary>
		/// <param name="nbFrames">number of frames of the video source</param>
		/// <param name="framerate">framerate of the video source</param>
		/// <param name="codec">codec selected</param>
		/// <param name="container">container</param>
		/// <param name="audio1Bitrate">bitrate of the first audio track</param>
		/// <param name="audio2Bitrate">bitrate of the second audio track</param>
		void SetDefaults(quint64 nbFrames, double framerate, int hRes, int vRes, VideoCodecSettings *vSettings, QVector<AudioJob*> &audioStreams);


		const VideoEncoderType &getSelectedVCodec() const;

		const int &getVideoBitrate() const;


	private:
		void audio_SelectedIndexChanged();

		void textField_TextChanged();

		void time_ValueChanged();

		/// <summary>
		/// handles the change in between bitrate and size calculation mode
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void calculationMode_CheckedChanged();

		/// <summary>
		/// handles codec selection change
		/// the choice is not limited for any codec
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void codec_CheckedChanged();

		void bframes_CheckedChanged();

		void targetSize_SelectionChanged(object *sender, const QString &val);

		void fpsChooser_SelectionChanged(object *sender, const QString &val);

		void addExtraToolStripMenuItem_Click();

		void addAudioToolStripMenuItem_Click();

		void addAudioLink_Clicked();

		/// <summary>
		/// Switches between showing h m s and total seconds
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void picTime_Click();


	protected:
		void SetAudioLength();

		void UpdateTotalFrames();

		void UpdateTotalSeconds();

		/// <summary>
		/// Determines which containers can be selected based on video and audio streams
		/// </summary>
		void UpdateContainers();

		AudioTrackSizeTab *AddAudio();

		ExtraSizeTab *AddExtra();

		void TagIndexes();

		void AddAutoSelectHandler(Control *control);

		/// <summary>
		/// Gets the audio streams by finding them in the form
		/// </summary>
		/// <returns></returns>
		IEnumerable<AudioBitrateCalculationStream*> *GetAudioStreams();

		/// <summary>
		/// Gets the total extra size by finding the extras and summing their sizes
		/// </summary>
		/// <returns>Total size of extra data</returns>
		FileSize GetTotalExtraSize();

		/// <summary>
		/// Gets the audio types used by the audio streams
		/// </summary>
		/// <returns></returns>
		IEnumerable<MuxableType*> *GetAudioTypes();

		/// <summary>
		/// Calculates by the selected method
		/// </summary>
		void Calculate();


	private:
		System::Windows::Forms::GroupBox *videoGroupbox;
		System::Windows::Forms::NumericUpDown *hours;
		System::Windows::Forms::NumericUpDown *minutes;
		System::Windows::Forms::NumericUpDown *seconds;
		System::Windows::Forms::Label *hoursLabel;
		System::Windows::Forms::Label *minutesLabel;
		System::Windows::Forms::Label *secondsLabel;
		System::Windows::Forms::Label *framerateLabel;
		System::Windows::Forms::Label *totalSecondsLabel;
		System::Windows::Forms::Button *applyButton;
		System::Windows::Forms::GroupBox *sizeGroupbox;
		System::Windows::Forms::RadioButton *averageBitrateRadio;
		System::Windows::Forms::RadioButton *fileSizeRadio;
		System::Windows::Forms::Label *AverageBitrateLabel;
		System::Windows::Forms::Label *nbFramesLabel;
		System::Windows::Forms::Button *cancelButton;
		System::Windows::Forms::OpenFileDialog *openFileDialog;
		System::Windows::Forms::CheckBox *bframes;
		ComboBox *videoCodec;
		ComboBox *containerFormat;
		NumericUpDown *nbFrames;
		NumericUpDown *totalSeconds;
		NumericUpDown *projectedBitrate;
		MeXgui::core::gui::HelpButton *helpButton1;
		MeXgui::core::gui::TargetSizeSCBox *targetSize;
		MeXgui::core::gui::FPSChooser *fpsChooser;
		ContextMenuStrip *contextMenuStrip1;
		ToolStripMenuItem *addAudioToolStripMenuItem;
		ToolStripMenuItem *addExtraToolStripMenuItem;
		Label *label7;
		Label *label9;
		NumericUpDown *height;
		Label *label10;
		NumericUpDown *width;
		Label *label8;
		TrackBar *complexity;
		Label *label2;
		RadioButton *bppRadio;
		NumericUpDown *bpp;
		TextBox *videoSize;
		Label *label3;
		RadioButton *qEstRadio;
		NumericUpDown *qest;
		GroupBox *containerGroupbox;
		GroupBox *audioExtraGroupbox;
		FlowLayoutPanel *audioExtraFlow;
		LinkLabel *addAudioLink;
		PictureBox *picTime;
		ToolTip *addToolTip;
		ToolTip *toolTip1;
		TextBox *timeText;


	public:
		Calculator();

		/// <summary>
		/// Required designer variable.
		/// </summary>
	private:
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

	private:
		void InitializeInstanceFields();
	};
}