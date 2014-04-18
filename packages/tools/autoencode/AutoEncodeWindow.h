#pragma once

#include "packages/audio/AudioJob.h"
#include "core/gui/MeXgui.MainForm.h"
#include "core/util/JobUtil.h"
#include "core/util/VideoUtil.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include "core/util/LogItem.h"
#include "core/details/mux/MuxProvider.h"
#include "core/plugins/interfaces/IMuxing.h"
#include "core/gui/MeXgui.HelpButton.h"
#include "core/gui/TargetSizeSCBox.h"
#include "core/gui/MeXgui.FileBar.h"
#include "core/util/FileSize.h"
#include "core/details/CodecManager.h"
#include "core/util/FileUtil.h"
#include "core/details/Streams.h"
#include "core/util/AudioUtil.h"
#include "packages/tools/calculator/CalcData.h"
#include "packages/audio/AudioCodecSettings.h"
#include "core/util/LanguageSelectionContainer.h"
#include "core/gui/MeXgui.AdaptiveMuxWindow.h"
#include "core/plugins/interfaces/IPackage.h"
#include "core/details/video/VideoCodecSettings.h"
#include <QString>
#include <QMap>
#include <QVector>
#include <cctype>
#include <stdexcept>
#include "stringconverter.h"

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







//using namespace System::Text;



using namespace MeXgui::core::details;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::calculator;

namespace MeXgui
{
	/// <summary>
	/// Summary description for AutoEncode.
	/// </summary>
	class AutoEncodeWindow : public System::Windows::Forms::Form
	{
	private:
		QVector<AudioJob*> audioStreams;
		bool prerender;
		MainForm *mainForm;
		JobUtil *jobUtil;
		VideoUtil *vUtil;
		VideoInfo *vInfo;
		LogItem *log;
		bool isBitrateMode;

		System::Windows::Forms::GroupBox *AutomaticEncodingGroup;
		System::Windows::Forms::RadioButton *FileSizeRadio;
		System::Windows::Forms::Label *AverageBitrateLabel;
		System::Windows::Forms::GroupBox *OutputGroupBox;
		System::Windows::Forms::Button *queueButton;
		System::Windows::Forms::Button *cancelButton;
		System::Windows::Forms::TextBox *projectedBitrateKBits;
		System::Windows::Forms::CheckBox *addSubsNChapters;
		System::Windows::Forms::RadioButton *averageBitrateRadio;
		RadioButton *noTargetRadio;
		Label *muxedOutputLabel;
		Label *containerLabel;
		ComboBox *container;
		ToolTip *defaultToolTip;
		MuxProvider *muxProvider;
		VideoStream *videoStream;

		MeXgui::core::gui::HelpButton *helpButton1;
		MeXgui::core::gui::TargetSizeSCBox *splitting;
		MeXgui::core::gui::TargetSizeSCBox *targetSize;
		TextBox *videoSize;
		Label *label2;
	protected:
		FileBar *muxedOutput;
	private:
		Label *DeviceLabel;
		ComboBox *device;


		IContainer *components;
		public:
		~AutoEncodeWindow()
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
		AutoEncodeWindow();
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AutoEncodeWindow(VideoStream videoStream, List<AudioJob> audioStreams, MainForm mainForm, bool prerender, VideoInfo vInfo) : this()
		AutoEncodeWindow(VideoStream *videoStream, QVector<AudioJob*> &audioStreams, MainForm *mainForm, bool prerender, VideoInfo *vInfo);
		/// <summary>
		/// does the final initialization of the dialog
		/// gets all audio types from the audio streams, then asks the muxprovider for a list of containers it can mux the video and audio streams into
		/// if there is no muxer that can deliver any container for the video / audio combination, we can abort right away
		/// </summary>
		/// <returns>true if the given video/audio combination can be muxed to at least a single container, false if not</returns>
		bool init();


		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
	private:
		void Dispose(bool disposing);
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent();
		/// <summary>
		/// adjusts the output extension when the container is being changed
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void container_SelectedIndexChanged();
		/// <summary>
		/// handles the selection of the output format
		/// in case of avi, if an encodeable audio stream is already present,
		/// the selection of additional streams needs to be completely disabled
		/// if not, it an be left enabled bt the text has to indicate the fact
		/// that you can only add an audio track and nothing else
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void outputFormat_CheckedChanged();
		/// <summary>
		/// separates encodable from muxable audio streams
		/// in addition to returning the two types separately an array of SubStreams is returned
		/// which is plugged into the muxer.. it contains the names of all the audio files
		/// that have to be muxed
		/// </summary>
		/// <param name="encodable">encodeable audio streams</param>
		/// <param name="muxable">muxable Audio Streams with the path filled out and a blank language</param>
		void separateEncodableAndMuxableAudioStreams(AudioJob encodable[], MuxStream muxable[], AudioEncoderType muxTypes[]);
		/// <summary>
		/// sets the projected video bitrate field in the GUI
		/// </summary>
		void setVideoBitrate();

		CalcData *GetCalcData();

		AudioBitrateCalculationStream *getAudioStreamsForBitrate();

		/// <summary>
		/// sets the size of the output given the desired bitrate
		/// </summary>
		void setTargetSize();
		/// <summary>
		/// sets the projected audio size for all audio streams that use CBR mode
		/// </summary>
		void setAudioSize();
		/// <summary>
		/// handles the go button for automated encoding
		/// checks if we're in automated 2 pass video mode
		/// then the video and audio configuration is checked, and if it checks out
		/// the audio job, video jobs and muxing job are generated, audio and video job are linked
		/// and encoding is started
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void queueButton_Click();

		/// <summary>
		/// Reallocates the audio array so that it only has the files to be muxed and not the files to be encoded, then muxed
		/// </summary>
		/// <param name="audio">All files to be muxed (including the ones which will be encoded first)</param>
		/// <param name="aStreams">All files being encoded (these will be removed from the audio array)</param>
		void removeStreamsToBeEncoded(MuxStream audio[], AudioJob aStreams[]);
		void textField_KeyPress(object *sender, KeyPressEventArgs *e);

		void containerOverhead_ValueChanged();
		void projectedBitrate_TextChanged();


		void calculationMode_CheckedChanged();

		void targetSize_SelectionChanged(object *sender, const QString &val);

	private:
		void InitializeInstanceFields();
	};
	class AutoEncodeTool : public ITool
	{

	public:
		const QString &getName() const;

		void Run(MainForm *info);

		const Shortcut *getShortcuts() const;



		const QString &getID() const;

	};
}
