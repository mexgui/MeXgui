#pragma once

#include "core/details/ProfileManager.h"
#include "core/details/video/VideoConfigurationPanel.h"
#include "xvidSettings.h"
#include "core/details/video/VideoCodecSettings.h"
#include "XviDEncoder.h"
#include "MeGUI.Properties.Settings.h"
#include "core/util/LogItem.h"
#include "core/gui/FileSCBox.h"
#include "core/plugins/interfaces/ISettingsProvider.h"
#include <string>
#include <cctype>
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

using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{
	namespace packages
	{
		namespace video
		{
			namespace xvid
			{
				class xvidConfigurationPanel : public MeGUI::core::details::video::VideoConfigurationPanel, Editable<xvidSettings*>
				{

					public:
					~xvidConfigurationPanel()
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
					xvidConfigurationPanel();
				private:
					void doCheckBoxAdjustments();
					/// <summary>
					/// Returns whether the given mode is a bitrate or quality-based mode
					/// </summary>
					/// <param name="mode">selected encoding mode</param>
					/// <returns>true if the mode is a bitrate mode, false otherwise</returns>
					bool isBitrateMode(int mode);
					void doDropDownAdjustments();

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
					/// Returns whether settings is xvidSettings
					/// </summary>
					/// <param name="settings">The settings to check</param>
					/// <returns>Whether the settings are valid</returns>
					virtual bool isValidSettings(VideoCodecSettings *settings);

					/// <summary>
					/// Returns a new instance of xvidSettings.
					/// </summary>
					/// <returns>A new instance of xvidSettings</returns>
					virtual VideoCodecSettings *defaultSettings();

					/// <summary>
					/// gets / sets the settings currently displayed on the GUI
					/// </summary>
				public:
					const xvidSettings &getSettings() const;
					void setSettings(const xvidSettings &value);
				private:
					void updateEvent(object *sender, EventArgs *e);
					void textField_KeyPress(object *sender, KeyPressEventArgs *e);
					void logfileOpenButton_Click(object *sender, System::EventArgs *e);

					void cqmComboBox1_SelectionChanged(object *sender, const std::string &val);

					void xvidProfile_SelectedIndexChanged(object *sender, EventArgs *e);

					void xvidVbvBuffer_TextChanged(object *sender, EventArgs *e);

					void xvidVbvMaxRate_TextChanged(object *sender, EventArgs *e);

					void xvidVbvPeakRate_TextChanged(object *sender, EventArgs *e);


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


					System::Windows::Forms::GroupBox *xvidOtherGroupBox;
					System::Windows::Forms::CheckBox *xvidInterlaced;
					System::Windows::Forms::CheckBox *xvidTrellisQuant;
					System::Windows::Forms::Label *fourCCLabel;
					System::Windows::Forms::ComboBox *fourCC;
					System::Windows::Forms::GroupBox *xvidCodecToolsGroupBox;
					System::Windows::Forms::CheckBox *xvidUseVHQForBframes;
					System::Windows::Forms::Label *xvidUseVHQForBframesLabel;
					System::Windows::Forms::CheckBox *xvidClosedGop;
					System::Windows::Forms::Label *xvidClosedGopLabel;
					System::Windows::Forms::Label *xvidQuantTypeLabel;
					System::Windows::Forms::CheckBox *xvidChromaMotion;
					System::Windows::Forms::Label *xvidChromaMotionLabel;
					System::Windows::Forms::CheckBox *xvidCartoonMode;
					System::Windows::Forms::Label *xvidCartoonModeLabel;
					System::Windows::Forms::CheckBox *xvidGMC;
					System::Windows::Forms::Label *xvidGMCLabel;
					System::Windows::Forms::CheckBox *xvidQpel;
					System::Windows::Forms::Label *xvidQPelLabel;
					System::Windows::Forms::ComboBox *xvidVHQ;
					System::Windows::Forms::Label *xvidVHQLabel;
					System::Windows::Forms::GroupBox *xvidGeneralOptionsGroupBox;
					System::Windows::Forms::Label *xvidBitrateQuantLabel;
					System::Windows::Forms::CheckBox *xvidTurbo;
					System::Windows::Forms::ComboBox *xvidEncodingMode;
					System::Windows::Forms::Label *xvidModeLabel;
					System::Windows::Forms::GroupBox *xvidOtherOptionsGroupbox;
					System::Windows::Forms::NumericUpDown *xvidFrameDropRatio;
					System::Windows::Forms::Label *xvidFrameDropRatioLabel;
					System::Windows::Forms::CheckBox *xvidHQAC;
					System::Windows::Forms::Label *xvidHQACLabel;
					System::Windows::Forms::Label *xvidChromaOptimizerLabel;
					System::Windows::Forms::CheckBox *xvidChromaOptimizer;
					System::Windows::Forms::Label *xvidBframeThresholdLabel;
					System::Windows::Forms::NumericUpDown *xvidBframeThreshold;
					System::Windows::Forms::GroupBox *xvidRCGroupbox;
					System::Windows::Forms::NumericUpDown *xvidLowBitrateImprovement;
					System::Windows::Forms::NumericUpDown *xvidHighBitrateDegradation;
					System::Windows::Forms::Label *xvidLowBitrateImprovementLabel;
					System::Windows::Forms::Label *xvidHighBitrateDegradationLabel;
					System::Windows::Forms::NumericUpDown *xvidMaxOverflowDegradation;
					System::Windows::Forms::NumericUpDown *xvidMaxOverflowImprovement;
					System::Windows::Forms::NumericUpDown *xvidOverflowControlStrength;
					System::Windows::Forms::Label *xvidMaxOverflowDegradationLabel;
					System::Windows::Forms::Label *xvidMaxOverflowImprovementLabel;
					System::Windows::Forms::Label *xvidOverflowControlStrengthLabel;
					System::Windows::Forms::NumericUpDown *xvidKeyframeReduction;
					System::Windows::Forms::TextBox *xvidKeyframeTreshold;
					System::Windows::Forms::NumericUpDown *xvidIframeBoost;
					System::Windows::Forms::Label *xvidKeyframeReductionLabel;
					System::Windows::Forms::Label *xvidKeyframeTresholdLabel;
					System::Windows::Forms::Label *xvidIframeBoostLabel;
					System::Windows::Forms::GroupBox *xvidQuantizerGroupbox;
					System::Windows::Forms::NumericUpDown *xvidCreditsQuantizer;
					System::Windows::Forms::Label *xvidCreditsQuantizerLabel;
					System::Windows::Forms::NumericUpDown *xvidBframeQuantOffset;
					System::Windows::Forms::NumericUpDown *xvidBframeQuantRatio;
					System::Windows::Forms::Label *xvidBframeQuantOffsetLabel;
					System::Windows::Forms::Label *xvidBframeQuantRatioLabel;
					System::Windows::Forms::NumericUpDown *xvidMaxBQuant;
					System::Windows::Forms::NumericUpDown *xvidMinBQuant;
					System::Windows::Forms::NumericUpDown *xvidMinPQuant;
					System::Windows::Forms::NumericUpDown *xvidMaxPQuant;
					System::Windows::Forms::Label *xvidMaxBQuantLabel;
					System::Windows::Forms::Label *xvidMinBQuantLabel;
					System::Windows::Forms::Label *xvidMaxPQuantLabel;
					System::Windows::Forms::Label *xvidMinPQuantLabel;
					System::Windows::Forms::NumericUpDown *xvidMaxIQuant;
					System::Windows::Forms::NumericUpDown *xvidMinIQuant;
					System::Windows::Forms::Label *xvidMaxIQuantLabel;
					System::Windows::Forms::Label *xvidMinIQuantLabel;
					System::Windows::Forms::GroupBox *xvidCBRRcGroupBox;
					System::Windows::Forms::TextBox *xvidRCBufferSize;
					System::Windows::Forms::Label *xvidRCBufferSizeLabel;
					System::Windows::Forms::Label *xvidRCAveragingPeriodLabel;
					System::Windows::Forms::TextBox *xvidRCAveragingPeriod;
					System::Windows::Forms::Label *xvidRCDelayFactorLabel;
					System::Windows::Forms::TextBox *xvidRCDelayFactor;
					System::Windows::Forms::OpenFileDialog *openFileDialog;
					System::Windows::Forms::SaveFileDialog *saveFileDialog;
					System::Windows::Forms::TabPage *advancedTabPage;
					System::Windows::Forms::Label *xvidThreadsLabel;
					System::Windows::Forms::NumericUpDown *nbThreads;
					System::Windows::Forms::NumericUpDown *xvidBitrateQuantizer;
					MeGUI::core::gui::FileSCBox *cqmComboBox1;
					System::Windows::Forms::GroupBox *quantizerMatrixGroupbox;
					System::Windows::Forms::TextBox *xvidCustomCommandlineOptions;
					System::Windows::Forms::Label *xvidCustomCommandlineOptionsLabel;
					System::Windows::Forms::TextBox *xvidKeyframeInterval;
					System::Windows::Forms::Label *xvidKeyframeIntervalLabel;
					System::Windows::Forms::NumericUpDown *xvidNbBFrames;
					System::Windows::Forms::Label *xvidNbBframesLabel;
					System::Windows::Forms::CheckBox *xvidPackedBitstream;
					System::Windows::Forms::Label *xvidPackedBitstreamLabel;
					System::Windows::Forms::ComboBox *xvidMotionSearchPrecision;
					System::Windows::Forms::Label *xvidMotionSearchPrecisionLabel;
					System::Windows::Forms::TextBox *logfile;
					System::Windows::Forms::Button *logfileOpenButton;
					System::Windows::Forms::Label *logfileLabel;
					System::Windows::Forms::GroupBox *gbx264CustomCmd;
					System::Windows::Forms::TextBox *customCommandlineOptions;
					System::Windows::Forms::ComboBox *xvidProfile;
					System::Windows::Forms::Label *xvidProfileLabel;
					System::Windows::Forms::TextBox *xvidVbvPeakRate;
					System::Windows::Forms::TextBox *xvidVbvMaxRate;
					System::Windows::Forms::TextBox *xvidVbvBuffer;
					System::Windows::Forms::Label *xvidVbvPeakRateLabel;
					System::Windows::Forms::Label *xvidVbvMaxRateLabel;
					System::Windows::Forms::Label *xvidVbvBufferLabel;
					System::Windows::Forms::Label *label1;
					System::Windows::Forms::ComboBox *HVSMasking;

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
