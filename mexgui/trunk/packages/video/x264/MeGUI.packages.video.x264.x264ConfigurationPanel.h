#pragma once

#include "core/details/ProfileManager.h"
#include "core/details/video/VideoConfigurationPanel.h"
#include "x264Settings.h"
#include "x264Device.h"
#include "core/gui/MeGUI.MainForm.h"
#include "packages/tools/avclevelschecker/AVCLevels.h"
#include "core/util/EnumProxy.h"
#include "core/details/video/VideoCodecSettings.h"
#include "x264Encoder.h"
#include "MeGUI.Properties.Settings.h"
#include "core/util/LogItem.h"
#include "core/gui/FileSCBox.h"
#include "core/gui/MeGUI.core.gui.HelpButton.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include <string>
#include <vector>
#include <cctype>
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
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml;

using namespace MeGUI::core::details::video;
using namespace MeGUI::core::gui;
using namespace MeGUI::core::plugins::interfaces;


namespace MeGUI
{
	namespace packages
	{
		namespace video
		{
			namespace x264
			{
				class x264ConfigurationPanel : public MeGUI::core::details::video::VideoConfigurationPanel, Editable<x264Settings*>
				{
				public:
					static bool levelEnforced; // flag to prevent recursion in EnforceLevels. There's probably a better way to do this.
				private:
					XmlDocument *ContextHelp;
					std::vector<x264Device*> x264DeviceList;
					x264Device *oTargetDevice;
					bool updateDevice, updateDeviceBlocked;


					public:
					~x264ConfigurationPanel()
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
					x264ConfigurationPanel();
				private:
					void doCheckBoxAdjustments();
					void doDeviceSpecificAdjustments();

					void doMacroBlockAdjustments();

					void doTrellisAdjustments();

					void doSubmeAdjustments();

					void doTuningsAdjustments();

					void doPresetsAdjustments();
					void setNonQPOptionsEnabled(bool enabled);
					/// <summary>
					/// Returns whether the given mode is a bitrate or quality-based mode
					/// </summary>
					/// <param name="mode">selected encoding mode</param>
					/// <returns>true if the mode is a bitrate mode, false otherwise</returns>
					bool isBitrateMode(int mode);
					void doEncodingModeAdjustments();
					/// <summary>
					/// adjust the mb selection dropdown in function of the selected profile and the activated
					/// mb options
					/// </summary>
				public:
					void doMBOptionsAdjustments();
				protected:
					virtual std::string getCommandline();
					/// <summary>
					/// Does all the necessary adjustments after a GUI change has been made.
					/// </summary>
					virtual void doCodecSpecificAdjustments();

					/// <summary>
					/// The method by which codecs can add things to the Load event
					/// </summary>
					virtual void doCodecSpecificLoadAdjustments();

					/// <summary>
					/// Returns whether settings is lavcSettings
					/// </summary>
					/// <param name="settings">The settings to check</param>
					/// <returns>Whether the settings are valid</returns>
					virtual bool isValidSettings(VideoCodecSettings *settings);

					/// <summary>
					/// Returns a new instance of lavcSettings.
					/// </summary>
					/// <returns>A new instance of lavcSettings</returns>
					virtual VideoCodecSettings *defaultSettings();

					/// <summary>
					/// gets / sets the settings currently displayed on the GUI
					/// </summary>
				public:
					const x264Settings &getSettings() const;
					void setSettings(const x264Settings &value);
				private:
					void updateEvent(object *sender, EventArgs *e);
					void textField_KeyPress(object *sender, KeyPressEventArgs *e);
					void logfileOpenButton_Click(object *sender, System::EventArgs *e);
					std::string SelectHelpText(const std::string &node);
					void SetToolTips();
					void x264DialogTriStateAdjustment();

					void cqmComboBox1_SelectionChanged(object *sender, const std::string &val);

					void VisitLink();

					void cbAQMode_SelectedIndexChanged(object *sender, EventArgs *e);

					void useQPFile_CheckedChanged(object *sender, EventArgs *e);

					void qpfileOpenButton_Click(object *sender, EventArgs *e);

					void tbx264Presets_Scroll(object *sender, EventArgs *e);

					void advancedSettings_CheckedChanged(object *sender, EventArgs *e);

					void dSettings_Click(object *sender, EventArgs *e);

					void btPresetSettings_Click(object *sender, EventArgs *e);

					void x264Tunes_SelectedIndexChanged(object *sender, EventArgs *e);

					void avcProfile_SelectedIndexChanged(object *sender, EventArgs *e);

					void cbTarget_SelectionChangeCommitted(object *sender, EventArgs *e);

					void pictureBox1_Click(object *sender, EventArgs *e);

					void targetDevice_SelectedIndexChanged(object *sender, EventArgs *e);

					x264Settings::x264PsyTuningModes getPsyTuning();

					AVCLevels::Levels getAVCLevel();

					void avcLevel_SelectedIndexChanged(object *sender, EventArgs *e);

					void x264VBVBufferSize_ValueChanged(object *sender, EventArgs *e);

					void x264VBVMaxRate_ValueChanged(object *sender, EventArgs *e);

					void ch10BitsEncoder_CheckedChanged(object *sender, EventArgs *e);


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


					System::Windows::Forms::GroupBox *x264CodecGeneralGroupbox;
					System::Windows::Forms::ComboBox *x264EncodingMode;
					System::Windows::Forms::Label *x264BitrateQuantizerLabel;
					System::Windows::Forms::TabPage *FrameTypeTabPage;
					System::Windows::Forms::TabPage *RCTabPage;
					System::Windows::Forms::GroupBox *gbGOPSize;
					System::Windows::Forms::Label *x264KeyframeIntervalLabel;
					System::Windows::Forms::NumericUpDown *x264KeyframeInterval;
					System::Windows::Forms::NumericUpDown *x264MinGOPSize;
					System::Windows::Forms::Label *x264MinGOPSizeLabel;
					System::Windows::Forms::GroupBox *quantizerMatrixGroupbox;
					System::Windows::Forms::GroupBox *x264QuantizerGroupBox;
					System::Windows::Forms::NumericUpDown *x264CreditsQuantizer;
					System::Windows::Forms::Label *x264CreditsQuantizerLabel;
					System::Windows::Forms::NumericUpDown *x264ChromaQPOffset;
					System::Windows::Forms::Label *x264ChromaQPOffsetLabel;
					System::Windows::Forms::NumericUpDown *x264MaxQuantDelta;
					System::Windows::Forms::NumericUpDown *x264MaximumQuantizer;
					System::Windows::Forms::NumericUpDown *x264MinimimQuantizer;
					System::Windows::Forms::Label *x264MinimimQuantizerLabel;
					System::Windows::Forms::Label *customCommandlineOptionsLabel;
					System::Windows::Forms::SaveFileDialog *saveFileDialog;
					System::Windows::Forms::OpenFileDialog *openFileDialog;
					System::Windows::Forms::Label *label3;
					System::Windows::Forms::Label *label2;
					System::Windows::Forms::NumericUpDown *deadzoneIntra;
					System::Windows::Forms::NumericUpDown *deadzoneInter;
					System::Windows::Forms::NumericUpDown *x264BitrateQuantizer;
					MeGUI::core::gui::FileSCBox *cqmComboBox1;
					System::Windows::Forms::NumericUpDown *x264IPFrameFactor;
					System::Windows::Forms::Label *lbQuantizersRatio;
					System::Windows::Forms::NumericUpDown *x264PBFrameFactor;
					System::Windows::Forms::Label *lbx264DeadZones;
					System::Windows::Forms::GroupBox *gbAQ;
					System::Windows::Forms::NumericUpDown *numAQStrength;
					System::Windows::Forms::Label *lbAQStrength;
					System::Windows::Forms::ComboBox *cbAQMode;
					System::Windows::Forms::Label *lbAQMode;
					MeGUI::core::gui::HelpButton *helpButton1;
					System::Windows::Forms::GroupBox *gbPresets;
					System::Windows::Forms::TrackBar *tbx264Presets;
					System::Windows::Forms::Label *lbPreset;
					System::Windows::Forms::GroupBox *gbTunes;
					System::Windows::Forms::ComboBox *x264Tunes;
					System::Windows::Forms::TabPage *AnalysisTabPage;
					System::Windows::Forms::PictureBox *pictureBox1;
					System::Windows::Forms::CheckBox *advancedSettings;
					System::Windows::Forms::GroupBox *gbH264Features;
					System::Windows::Forms::NumericUpDown *x264BetaDeblock;
					System::Windows::Forms::NumericUpDown *x264AlphaDeblock;
					System::Windows::Forms::CheckBox *x264DeblockActive;
					System::Windows::Forms::Label *x264BetaDeblockLabel;
					System::Windows::Forms::Label *x264AlphaDeblockLabel;
					System::Windows::Forms::GroupBox *x264GeneralBFramesgGroupbox;
					System::Windows::Forms::Label *x264AdaptiveBframesLabel;
					System::Windows::Forms::ComboBox *x264NewAdaptiveBframes;
					System::Windows::Forms::Label *x264NumberOfBFramesLabel;
					System::Windows::Forms::NumericUpDown *x264NumberOfBFrames;
					System::Windows::Forms::Label *PsyTrellisLabel;
					System::Windows::Forms::Label *PsyRDLabel;
					System::Windows::Forms::Label *x264NumberOfRefFramesLabel;
					System::Windows::Forms::Label *trellisLabel;
					System::Windows::Forms::CheckBox *cabac;
					System::Windows::Forms::GroupBox *gbFTOther;
					System::Windows::Forms::NumericUpDown *x264NumberOfRefFrames;
					System::Windows::Forms::Label *label6;
					System::Windows::Forms::NumericUpDown *x264SCDSensitivity;
					System::Windows::Forms::NumericUpDown *NoiseReduction;
					System::Windows::Forms::Label *NoiseReductionLabel;
					System::Windows::Forms::CheckBox *scenecut;
					System::Windows::Forms::Label *lbExtraIFframes;
					System::Windows::Forms::CheckBox *x264WeightedBPrediction;
					System::Windows::Forms::NumericUpDown *x264BframeBias;
					System::Windows::Forms::Label *x264BframeBiasLabel;
					System::Windows::Forms::GroupBox *x264RCGroupbox;
					System::Windows::Forms::Label *x264RateTolLabel;
					System::Windows::Forms::NumericUpDown *x264VBVInitialBuffer;
					System::Windows::Forms::Label *x264VBVInitialBufferLabel;
					System::Windows::Forms::NumericUpDown *x264VBVMaxRate;
					System::Windows::Forms::NumericUpDown *x264TempQuantBlur;
					System::Windows::Forms::NumericUpDown *x264TempFrameComplexityBlur;
					System::Windows::Forms::NumericUpDown *x264QuantizerCompression;
					System::Windows::Forms::NumericUpDown *x264VBVBufferSize;
					System::Windows::Forms::Label *x264TempQuantBlurLabel;
					System::Windows::Forms::Label *x264TempFrameComplexityBlurLabel;
					System::Windows::Forms::Label *x264QuantizerCompressionLabel;
					System::Windows::Forms::Label *x264VBVMaxRateLabel;
					System::Windows::Forms::Label *x264VBVBufferSizeLabel;
					System::Windows::Forms::NumericUpDown *x264RateTol;
					System::Windows::Forms::TabPage *MiscTabPage;
					System::Windows::Forms::GroupBox *gbx264CustomCmd;
					System::Windows::Forms::TextBox *customCommandlineOptions;
					System::Windows::Forms::GroupBox *x264OtherOptionsGroupbox;
					System::Windows::Forms::ComboBox *x264SubpelRefinement;
					System::Windows::Forms::Label *x264SubpelRefinementLabel;
					System::Windows::Forms::CheckBox *x264ChromaMe;
					System::Windows::Forms::Label *x264MERangeLabel;
					System::Windows::Forms::Label *x264METypeLabel;
					System::Windows::Forms::ComboBox *x264METype;
					System::Windows::Forms::NumericUpDown *x264MERange;
					System::Windows::Forms::GroupBox *x264MBGroupbox;
					System::Windows::Forms::Label *label1;
					System::Windows::Forms::ComboBox *macroblockOptions;
					System::Windows::Forms::CheckBox *adaptiveDCT;
					System::Windows::Forms::CheckBox *x264I4x4mv;
					System::Windows::Forms::CheckBox *x264I8x8mv;
					System::Windows::Forms::CheckBox *x264P4x4mv;
					System::Windows::Forms::CheckBox *x264B8x8mv;
					System::Windows::Forms::CheckBox *x264P8x8mv;
					System::Windows::Forms::GroupBox *x264QuantOptionsGroupbox;
					System::Windows::Forms::ComboBox *x264BframePredictionMode;
					System::Windows::Forms::Label *x264BframePredictionModeLabel;
					System::Windows::Forms::Label *label4;
					System::Windows::Forms::NumericUpDown *PsyTrellis;
					System::Windows::Forms::Label *label5;
					System::Windows::Forms::NumericUpDown *PsyRD;
					System::Windows::Forms::CheckBox *noDCTDecimateOption;
					System::Windows::Forms::CheckBox *noFastPSkip;
					System::Windows::Forms::ComboBox *trellis;
					System::Windows::Forms::Label *label7;
					System::Windows::Forms::GroupBox *gbQPFile;
					System::Windows::Forms::Button *qpfileOpenButton;
					System::Windows::Forms::TextBox *qpfile;
					System::Windows::Forms::CheckBox *useQPFile;
					System::Windows::Forms::Label *label8;
					System::Windows::Forms::NumericUpDown *lookahead;
					System::Windows::Forms::CheckBox *mbtree;
					System::Windows::Forms::CheckBox *nopsy;
					System::Windows::Forms::GroupBox *gbInOut;
					System::Windows::Forms::CheckBox *ssim;
					System::Windows::Forms::CheckBox *psnr;
					System::Windows::Forms::GroupBox *gbVUI;
					System::Windows::Forms::CheckBox *x264MixedReferences;
					System::Windows::Forms::GroupBox *gbSlicing;
					System::Windows::Forms::NumericUpDown *slicesnb;
					System::Windows::Forms::Label *label9;
					System::Windows::Forms::Label *label10;
					System::Windows::Forms::Label *label11;
					System::Windows::Forms::NumericUpDown *maxSliceSizeBytes;
					System::Windows::Forms::NumericUpDown *maxSliceSizeMB;
					System::Windows::Forms::GroupBox *gbAdjust;
					System::Windows::Forms::Button *btPresetSettings;
					System::Windows::Forms::Button *dSettings;
					System::Windows::Forms::Label *label12;
					System::Windows::Forms::ComboBox *cbBPyramid;
					System::Windows::Forms::ComboBox *x264WeightedPPrediction;
					System::Windows::Forms::Label *lblWeightedP;
					System::Windows::Forms::GroupBox *x264Bluray;
					System::Windows::Forms::CheckBox *x264aud;
					System::Windows::Forms::GroupBox *gbOther;
					System::Windows::Forms::CheckBox *threadin;
					System::Windows::Forms::Label *x264NbThreadsLabel;
					System::Windows::Forms::NumericUpDown *x264NbThreads;
					System::Windows::Forms::TextBox *logfile;
					System::Windows::Forms::Label *logfileLabel;
					System::Windows::Forms::Button *logfileOpenButton;
					System::Windows::Forms::ComboBox *cbTarget;
					System::Windows::Forms::CheckBox *x264SlowFirstpass;
					System::Windows::Forms::Label *x264hrdLabel;
					System::Windows::Forms::ComboBox *x264hrd;
					System::Windows::Forms::CheckBox *picStruct;
					System::Windows::Forms::CheckBox *fakeInterlaced;
					System::Windows::Forms::GroupBox *avcProfileGroupbox;
					System::Windows::Forms::ComboBox *avcProfile;
					System::Windows::Forms::GroupBox *avcLevelGroupbox;
					System::Windows::Forms::ComboBox *avcLevel;
					System::Windows::Forms::CheckBox *nonDeterministic;
					System::Windows::Forms::Label *colorMatrixLabel;
					System::Windows::Forms::Label *transferLabel;
					System::Windows::Forms::Label *colorPrimLabel;
					System::Windows::Forms::ComboBox *colorMatrix;
					System::Windows::Forms::ComboBox *transfer;
					System::Windows::Forms::ComboBox *colorPrim;
					System::Windows::Forms::Label *pullDownLabel;
					System::Windows::Forms::ComboBox *x264PullDown;
					System::Windows::Forms::ComboBox *sampleAR;
					System::Windows::Forms::Label *sampleARLabel;
					System::Windows::Forms::ComboBox *cbInterlaceMode;
					System::Windows::Forms::Label *lblInterlacedMode;
					System::Windows::Forms::GroupBox *deviceGroupbox;
					System::Windows::Forms::ComboBox *targetDevice;
					System::Windows::Forms::CheckBox *chkBlurayCompat;
					System::Windows::Forms::CheckBox *chkOpenGop;
					System::Windows::Forms::Label *label16;
					System::Windows::Forms::Label *label15;
					System::Windows::Forms::Label *label14;
					System::Windows::Forms::Label *label13;
					System::Windows::Forms::Label *label17;
					System::Windows::Forms::Label *label18;
					System::Windows::Forms::ComboBox *x264Range;
					System::Windows::Forms::Label *label19;
					System::Windows::Forms::ComboBox *cbGOPCalculation;
					System::Windows::Forms::CheckBox *chkTuneZeroLatency;
					System::Windows::Forms::CheckBox *chkTuneFastDecode;
					System::Windows::Forms::CheckBox *stitchable;
					System::Windows::Forms::CheckBox *ch10BitsEncoder;

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
