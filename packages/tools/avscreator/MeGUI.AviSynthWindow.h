#pragma once

#include "core/gui/VideoPlayer.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include "core/util/DAR.h"
#include "core/gui/MeXgui.MainForm.h"
#include "AviSynthWindow.h"
#include "core/gui/SourceDetector.h"
#include "core/util/LogItem.h"
#include "ScriptServer.h"
#include "core/util/DeinterlaceFilter.h"
#include "core/gui/FileBar.h"
#include "core/gui/MeXgui.FileBar.h"
#include "core/util/EnumProxy.h"
#include "AviSynthSettings.h"
#include "packages/tools/oneclick/MeXgui.OneClickWindow.h"
#include "packages/tools/fileindexer/MeXgui.FileIndexerWindow.h"
#include "core/util/DirectShow.h"
#include "core/util/VideoUtil.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/Resolution.h"
#include "core/util/Autocrop.h"
#include "MeXgui.Properties.Settings.h"
#include "core/gui/MeXgui.HelpButton.h"
#include "core/gui/MeXgui.ConfigableProfilesControl.h"
#include "core/gui/ARChooser.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include <QString>
#include <QVector>
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




//using namespace System::Collections::Generic;



//using namespace System::Globalization;



//using namespace System::Text;



using namespace MeXgui::core::util;



namespace MeXgui
{
	class AviSynthWindow : public System::Windows::Forms::Form
	{
	private:
		QString originalScript;
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
		QString indexFile;
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
		void ProfileChanged();

		/// <summary>
		/// constructor that first initializes everything using the default constructor
		/// then opens a preview window with the video given as parameter
		/// </summary>
		/// <param name="videoInput">the DGIndex script to be loaded</param>
	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AviSynthWindow(MainForm mainForm, string videoInput) : this(mainForm)
		AviSynthWindow(MainForm *mainForm, const QString &videoInput);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AviSynthWindow(MainForm mainForm, string videoInput, string indexFile) : this(mainForm)
		AviSynthWindow(MainForm *mainForm, const QString &videoInput, const QString &indexFile);

	protected:
		virtual void OnClosing(CancelEventArgs *e);

	private:
		void input_FileSelected(FileBar *sender, FileBarEventArgs *args);

		void openDLLButton_Click();

		void previewButton_Click();

		void saveButton_Click();

		QString generateScript();

		AviSynthSettings *GetProfileSettings();

		void showScript(bool bForce);

		/// <summary>
		/// Opens a video source using the correct method based on the extension of the file name
		/// </summary>
		/// <param name="videoInput"></param>
		void openVideoSource(const QString &videoInput, const QString &indexFileTemp);

		/// <summary>
		/// writes the AviSynth script currently shown in the GUI to the given path
		/// </summary>
		/// <param name="path">path and name of the AviSynth script to be written</param>
		void writeScript(const QString &path);

		/// <summary>
		/// Set the correct states of the interface elements that are only valid for certain inputs
		/// </summary>
		void setSourceInterface();

		/// <summary>
		/// check whether or not it's an NV file compatible (for DGxNV tools)
		/// </summary>
		void checkNVCompatibleFile(const QString &input);

		const SourceInfo &getDeintInfo() const;
		void setDeintInfo(const SourceInfo &value);

		/// <summary>
		/// Check whether direct show can render the avi and then open it through an avisynth script.
		/// The avs is being used in order to allow more preview flexibility later.
		/// </summary>
		/// <param name="fileName">Input video file</param>     
		void openDirectShow(const QString &fileName);

		/// <summary>
		/// Create a temporary avs to wrap the frameserver file then open it as for any other avs
		/// </summary>
		/// <param name="fileName">Name of the .vdr file</param>
		void openVDubFrameServer(const QString &fileName);

		/// <summary>
		/// Create a temporary avs to wrap the frameserver file then open it as for any other avs
		/// </summary>
		/// <param name="fileName">Name of the avs script</param>
		void openAVSScript(const QString &fileName);

		void enableControls(bool enable);

		void openVideo(const QString &videoInput);

		bool showOriginal();

		/// <summary>
		/// opens a given script
		/// </summary>
		/// <param name="videoInput">the script to be opened</param>
		void openVideo(const QString &videoInputScript, const QString &strSourceFileName, bool inlineAvs);

		void calcAspectError();


		void changeNumericUpDownColor(NumericUpDown *oControl, bool bMarkRed);

		void sendCropValues();

		void deinterlace_CheckedChanged();

		void noiseFilter_CheckedChanged();


		/// <summary>
		/// gets the autocrop values
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void autoCropButton_Click();

		void setCropValues(CropValues *cropValues);



		void setSettings(const AviSynthSettings &value);

		const CropValues &getCropping() const;

		const mod16Method &getMod16Method() const;


		void analyseButton_Click();

	public:
		void finishedAnalysis(SourceInfo *info, bool error, const QString &errorMessage);

		void analyseUpdate(int amountDone, int total);

	private:
		void deintSourceType_SelectedIndexChanged();

		void reopenOriginal_Click();

		void chAutoPreview_CheckedChanged();

		void nvDeInt_CheckedChanged();

		void nvDeInt_Click();

		void openSubtitlesButton_Click();

		QString CharsetValue();

		void inputDARChanged(object *sender, const QString &val);

		void updateEverything();

		void updateEverything(bool bShowScript, bool bForceScript, bool bResizeEnabled);

		void setModType();

		void setCrop();

		void setOutputResolution(bool bResizeEnabled);

		void checkControls();

		void refreshScript();

		void AviSynthWindow_Shown();

		void resize_CheckedChanged();


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

		QVector<Control*> controlsToDisable;
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
		MeXgui::core::gui::ARChooser *arChooser;
		MeXgui::core::gui::ConfigableProfilesControl *avsProfile;
		Label *label6;
		CheckBox *chAutoPreview;
		GroupBox *gbOutput;
		Label *label7;
		FileBar *videoOutput;
		FileBar *input;
		CheckBox *onSaveLoadScript;
		Button *saveButton;
		Button *previewAvsButton;
		MeXgui::core::gui::HelpButton *helpButton1;
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
