#pragma once

#include "core/util/EnumProxy.h"
#include "AudioCodecSettings.h"
#include "MeXgui.Properties.Settings.h"
#include "core/util/LogItem.h"
#include <cctype>

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




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;



namespace MeXgui
{
	namespace core
	{
		namespace details
		{
			namespace audio
			{
				class AudioConfigurationPanel : public UserControl
				{
				private:
//ORIGINAL LINE: private EnumProxy[] _avisynthChannelSet;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
					EnumProxy *_avisynthChannelSet;


					public:
					~AudioConfigurationPanel()
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
					AudioConfigurationPanel();



				protected:
					void showCommandLine();



					const virtual bool &getIsMultichanelSupported() const;

					const virtual bool &getIsMultichanelRequed() const;

					/// <summary>
					/// Must collect data from UI / Fill UI from Data
					/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
					const virtual AudioCodecSettings &getCodecSettings() const;
					virtual void setCodecSettings(const AudioCodecSettings &value);


					/// <summary>
					/// gets / sets the settings that are being shown in this configuration dialog
					/// </summary>
				public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					const AudioCodecSettings &getSettings() const;
					void setSettings(const AudioCodecSettings &value);

					/// <summary>
					/// handles entires into textfiels, blocks entry of non digit characters
					/// </summary>
					/// <param name="sender"></param>
					/// <param name="e"></param>
				private:
					void textField_KeyPress(object *sender, KeyPressEventArgs *e);
					void besweetDelay_TextChanged();

					void applyDRC_CheckedChanged();

					void autoGain_CheckedChanged();


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


				protected:
					System::Windows::Forms::GroupBox *encoderGroupBox;
				private:
					System::Windows::Forms::CheckBox *autoGain;
					System::Windows::Forms::ComboBox *besweetDownmixMode;
					System::Windows::Forms::Label *BesweetChannelsLabel;
				protected:
					System::Windows::Forms::GroupBox *besweetOptionsGroupbox;
				private:
					System::Windows::Forms::CheckBox *applyDRC;
					System::Windows::Forms::NumericUpDown *normalize;
					System::Windows::Forms::Label *lbSampleRate;
					System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;
					System::Windows::Forms::ComboBox *primaryDecoding;
					System::Windows::Forms::Label *label1;
					System::Windows::Forms::ComboBox *cbSampleRate;


				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
