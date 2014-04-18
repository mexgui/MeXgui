#pragma once

#include "core/gui/VideoPlayer.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include "core/util/DAR.h"
#include "core/gui/MeGUI.MainForm.h"
#include "AviSynthWindow.h"
#include "core/gui/SourceDetector.h"
#include "core/util/LogItem.h"
#include "ScriptServer.h"
#include "core/util/DeinterlaceFilter.h"
#include "core/gui/FileBar.h"
#include "core/gui/MeGUI.FileBar.h"
#include "core/util/EnumProxy.h"
#include "AviSynthSettings.h"
#include "packages/tools/oneclick/MeGUI.OneClickWindow.h"
#include "packages/tools/fileindexer/MeGUI.FileIndexerWindow.h"
#include "core/util/DirectShow.h"
#include "core/util/VideoUtil.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/Resolution.h"
#include "core/util/Autocrop.h"
#include "MeGUI.Properties.Settings.h"
#include "core/gui/MeGUI.core.gui.HelpButton.h"
#include "core/gui/MeGUI.core.gui.ConfigableProfilesControl.h"
#include "core/gui/ARChooser.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

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
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::util;



namespace MeGUI
{
	class AviSynthWindow : public System::Windows::Forms::Form
	{
	private:
		std::string originalScript;
		bool originalInlineAvs;
		bool isPreviewMode;
		bool eventsOn;
		VideoPlayer *player;
		IMediaFile *file;
		IVideoReader *reader;
		StringBuilder *script;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event OpenScriptCallback OpenScript;
		Nullable<Dar> suggestedDar;
		MainForm *mainForm;
		PossibleSources sourceType;
		SourceDetector *detector;
		std::string indexFile;
		int scriptRefresh; // >= 1 enabled; < 1 disabled
		bool bAllowUpsizing;
		LogItem *_oLog;

		public:
		~AviSynthWindow()
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
		AviSynthWindow(MainForm *mainForm);

	private:
		void ProfileChanged(object *sender, EventArgs *e);

		/// <summary>
		/// constructor that first initializes everything using the default constructor
		/// then opens a preview window with the video given as parameter
		/// </summary>
		/// <param name="videoInput">the DGIndex script to be loaded</param>
	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AviSynthWindow(MainForm mainForm, string videoInput) : this(mainForm)
		AviSynthWindow(MainForm *mainForm, const std::string &videoInput);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AviSynthWindow(MainForm mainForm, string videoInput, string indexFile) : this(mainForm)
		AviSynthWindow(MainForm *mainForm, const std::string &videoInput, const std::string &indexFile);

	protected:
		virtual void OnClosing(CancelEventArgs *e);

	private:
		void input_FileSelected(FileBar *sender, FileBarEventArgs *args);

		void openDLLButton_Click(object *sender, System::EventArgs *e);

		void previewButton_Click(object *sender, System::EventArgs *e);

		void saveButton_Click(object *sender, System::EventArgs *e);

		std::string generateScript();

		AviSynthSettings *GetProfileSettings();

		void showScript(bool bForce);

		/// <summary>
		/// Opens a video source using the correct method based on the extension of the file name
		/// </summary>
		/// <param name="videoInput"></param>
		void openVideoSource(const std::string &videoInput, const std::string &indexFileTemp);

		/// <summary>
		/// writes the AviSynth script currently shown in the GUI to the given path
		/// </summary>
		/// <param name="path">path and name of the AviSynth script to be written</param>
		void writeScript(const std::string &path);

		/// <summary>
		/// Set the correct states of the interface elements that are only valid for certain inputs
		/// </summary>
		void setSourceInterface();

		/// <summary>
		/// check whether or not it's an NV file compatible (for DGxNV tools)
		/// </summary>
		void checkNVCompatibleFile(const std::string &input);

		const SourceInfo &getDeintInfo() const;
		void setDeintInfo(const SourceInfo &value);

		/// <summary>
		/// Check whether direct show can render the avi and then open it through an avisynth script.
		/// The avs is being used in order to allow more preview flexibility later.
		/// </summary>
		/// <param name="fileName">Input video file</param>     
		void openDirectShow(const std::string &fileName);

		/// <summary>
		/// Create a temporary avs to wrap the frameserver file then open it as for any other avs
		/// </summary>
		/// <param name="fileName">Name of the .vdr file</param>
		void openVDubFrameServer(const std::string &fileName);

		/// <summary>
		/// Create a temporary avs to wrap the frameserver file then open it as for any other avs
		/// </summary>
		/// <param name="fileName">Name of the avs script</param>
		void openAVSScript(const std::string &fileName);

		void enableControls(bool enable);

		void openVideo(const std::string &videoInput);

		bool showOriginal();

		/// <summary>
		/// opens a given script
		/// </summary>
		/// <param name="videoInput">the script to be opened</param>
		void openVideo(const std::string &videoInputScript, const std::string &strSourceFileName, bool inlineAvs);

		void calcAspectError();


		void changeNumericUpDownColor(NumericUpDown *oControl, bool bMarkRed);

		void sendCropValues();

		void deinterlace_CheckedChanged(object *sender, EventArgs *e);

		void noiseFilter_CheckedChanged(object *sender, EventArgs *e);


		/// <summary>
		/// gets the autocrop values
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void autoCropButton_Click(object *sender, EventArgs *e);

		void setCropValues(CropValues *cropValues);



		void setSettings(const AviSynthSettings &value);

		const CropValues &getCropping() const;

		const mod16Method &getMod16Method() const;


		void analyseButton_Click(object *sender, EventArgs *e);

	public:
		void finishedAnalysis(SourceInfo *info, bool error, const std::string &errorMessage);

		void analyseUpdate(int amountDone, int total);

	private:
		void deintSourceType_SelectedIndexChanged(object *sender, EventArgs *e);

		void reopenOriginal_Click(object *sender, EventArgs *e);

		void chAutoPreview_CheckedChanged(object *sender, EventArgs *e);

		void nvDeInt_CheckedChanged(object *sender, EventArgs *e);

		void nvDeInt_Click(object *sender, EventArgs *e);

		void openSubtitlesButton_Click(object *sender, EventArgs *e);

		std::string CharsetValue();

		void inputDARChanged(object *sender, const std::string &val);

		void updateEverything(object *sender, EventArgs *e);

		void updateEverything(bool bShowScript, bool bForceScript, bool bResizeEnabled);

		void setModType();

		void setCrop();

		void setOutputResolution(bool bResizeEnabled);

		void checkControls();

		void refreshScript(object *sender, EventArgs *e);

		void AviSynthWindow_Shown(object *sender, EventArgs *e);

		void resize_CheckedChanged(object *sender, EventArgs *e);


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


		GroupBox *resNCropGroupbox;
		CheckBox *crop;
		Button *autoCropButton;
		TabControl *tabControl1;
		TabPage *optionsTab;
		TabPage *editTab;
		GroupBox *videoGroupBox;
		Label *videoInputLabel;
		Label *inputDARLabel;
		Label *tvTypeLabel;
		SaveFileDialog *saveAvisynthScriptDialog;
		TextBox *avisynthScript;
		NumericUpDown *horizontalResolution;
		NumericUpDown *verticalResolution;
		NumericUpDown *cropLeft;
		NumericUpDown *cropRight;
		NumericUpDown *cropBottom;
		NumericUpDown *cropTop;
		OpenFileDialog *openFilterDialog;
		OpenFileDialog *openSubsDialog;
		CheckBox *suggestResolution;
		CheckBox *signalAR;

		std::vector<Control*> controlsToDisable;
		TabPage *filterTab;
		GroupBox *deinterlacingGroupBox;
		CheckBox *deintIsAnime;
		Button *analyseButton;
		CheckBox *deinterlace;
		ComboBox *deinterlaceType;
		GroupBox *filtersGroupbox;
		ComboBox *noiseFilterType;
		CheckBox *noiseFilter;
		ComboBox *resizeFilterType;
		Label *resizeFilterLabel;
		CheckBox *resize;
		ComboBox *mod16Box;
		Label *label1;
		Button *openDLLButton;
		TextBox *dllPath;
		ComboBox *deintFieldOrder;
		ComboBox *deintSourceType;
		NumericUpDown *deintM;
		StatusStrip *statusStrip1;
		ToolStripProgressBar *deintProgressBar;
		ToolStripStatusLabel *deintStatusLabel;
		Button *reopenOriginal;
		MeGUI::core::gui::ARChooser *arChooser;
		MeGUI::core::gui::ConfigableProfilesControl *avsProfile;
		Label *label6;
		CheckBox *chAutoPreview;
		GroupBox *gbOutput;
		Label *label7;
		FileBar *videoOutput;
		FileBar *input;
		CheckBox *onSaveLoadScript;
		Button *saveButton;
		Button *previewAvsButton;
		MeGUI::core::gui::HelpButton *helpButton1;
		TabControl *tabSources;
		TabPage *tabPage1;
		GroupBox *mpegOptGroupBox;
		CheckBox *colourCorrect;
		CheckBox *mpeg2Deblocking;
		TabPage *tabPage2;
		GroupBox *aviOptGroupBox;
		NumericUpDown *fpsBox;
		Label *fpsLabel;
		CheckBox *flipVertical;
		TabPage *tabPage3;
		GroupBox *dgOptions;
		ComboBox *cbNvDeInt;
		CheckBox *nvDeInt;
		Label *SubtitlesLabel;
		Button *openSubtitlesButton;
		TextBox *SubtitlesPath;
		CheckBox *dss2;
		Label *label8;
		ComboBox *cbCharset;
		CheckBox *nvResize;
		ComboBox *modValueBox;
		Label *lblAR;
		Label *lblAspectError;

	private:
		void InitializeInstanceFields();
	};
}
