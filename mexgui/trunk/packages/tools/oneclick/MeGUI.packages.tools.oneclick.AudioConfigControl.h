#pragma once

#include "core/gui/MeGUI.MainForm.h"
#include "core/util/LogItem.h"
#include "packages/audio/AudioCodecSettings.h"
#include "MeGUI.Properties.Settings.h"
#include "core/util/PrettyFormatting.h"
#include "OneClickSettings.h"
#include "core/gui/MeGUI.core.gui.ConfigableProfilesControl.h"
#include <string>

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
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details::video;
using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace oneclick
			{
				class AudioConfigControl : public UserControl
				{
				private:
					MainForm *mainForm;

					public:
					~AudioConfigControl()
					{
						this->Dispose(true);
					}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
					private:
					void Finalize()
					{
						this->Dispose(false);
					}

					void initAudioHandler();

					void audioCodec_SelectedIndexChanged(object *sender, EventArgs *e);

					void ProfileChanged(object *o, EventArgs *e);

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//					public event EventHandler SomethingChanged;

					void dontEncodeAudio_CheckedChanged(object *sender, EventArgs *e);

					void raiseEvent();

				public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					const AudioCodecSettings &getSettings() const;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					void setDelayEnabled(const bool &value);
					const bool &getDelayEnabled() const;

					void openAudioFile(const std::string &p);

					AudioConfigControl();

					void initHandler();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					const MeGUI::AudioEncodingMode &getAudioEncodingMode() const;
					void setAudioEncodingMode(const MeGUI::AudioEncodingMode &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					void DisableDontEncode(bool bDisable);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					bool IsDontEncodePossible();

					void SelectProfileNameOrWarn(const std::string &fqname);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					const int &getDelay() const;
					void setDelay(const int &value);


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


					System::Windows::Forms::Label *label3;
					System::Windows::Forms::NumericUpDown *delay;
					System::Windows::Forms::Label *label2;
					MeGUI::core::gui::ConfigableProfilesControl *audioProfile;
					System::Windows::Forms::Label *label1;
					System::Windows::Forms::ComboBox *cbAudioEncoding;
					System::Windows::Forms::Label *label4;

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
