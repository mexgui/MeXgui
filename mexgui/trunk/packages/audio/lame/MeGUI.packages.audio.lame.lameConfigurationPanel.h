#pragma once

#include "core/details/ProfileManager.h"
#include "MP3Settings.h"
#include "packages/audio/MeGUI.core.details.audio.AudioConfigurationPanel.h"
#include "packages/audio/AudioCodecSettings.h"
#include "MeGUI.Properties.Settings.h"
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

namespace MeGUI
{
	namespace packages
	{
		namespace audio
		{
			namespace lame
			{
				class lameConfigurationPanel : public MeGUI::core::details::audio::AudioConfigurationPanel, Editable<MP3Settings*>
				{
					public:
					~lameConfigurationPanel()
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
					lameConfigurationPanel();
				protected:
					const virtual bool &getIsMultichanelSupported() const;
					/// <summary>
					/// gets / sets the settings that are being shown in this configuration dialog
					/// </summary>
					const virtual AudioCodecSettings &getCodecSettings() const;
					virtual void setCodecSettings(const AudioCodecSettings &value);
					/// <summary>
					/// handles entires into textfiels, blocks entry of non digit characters
					/// </summary>
					/// <param name="sender"></param>
					/// <param name="e"></param>
				private:
					void textField_KeyPress(object *sender, KeyPressEventArgs *e);


					const MP3Settings &getSettings() = Editable::Settings::get const;
					void setSettings(const MP3Settings &value) = Editable::Settings::set;


					void cbrMode_CheckedChanged(object *sender, EventArgs *e);

					void abrMode_CheckedChanged(object *sender, EventArgs *e);

					void vbrMode_CheckedChanged(object *sender, EventArgs *e);


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


					System::Windows::Forms::RadioButton *vbrMode;
					System::Windows::Forms::RadioButton *abrMode;
					System::Windows::Forms::RadioButton *cbrMode;
					System::Windows::Forms::NumericUpDown *abrValue;
					System::Windows::Forms::NumericUpDown *vbrValue;
					System::Windows::Forms::ComboBox *cbrBitrate;



				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
