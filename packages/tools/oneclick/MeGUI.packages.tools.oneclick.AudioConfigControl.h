#pragma once

#include "core/gui/MainForm.h"
#include "core/util/LogItem.h"
#include "packages/audio/AudioCodecSettings.h"
#include "Properties.Settings.h"
#include "core/util/PrettyFormatting.h"
#include "OneClickSettings.h"
#include "core/gui/ConfigableProfilesControl.h"
#include <QString>

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



using namespace MeXgui::core::details::video;
using namespace MeXgui::core::util;

namespace MeXgui
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

					void audioCodec_SelectedIndexChanged();

					void ProfileChanged(object *o, EventArgs *e);

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//					public event EventHandler SomethingChanged;

					void dontEncodeAudio_CheckedChanged();

					void raiseEvent();

				public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					const AudioCodecSettings &getSettings() const;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					void setDelayEnabled(const bool &value);
					const bool &getDelayEnabled() const;

					void openAudioFile(const QString &p);

					AudioConfigControl();

					void initHandler();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					const MeXgui::AudioEncodingMode &getAudioEncodingMode() const;
					void setAudioEncodingMode(const MeXgui::AudioEncodingMode &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					void DisableDontEncode(bool bDisable);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					bool IsDontEncodePossible();

					void SelectProfileNameOrWarn(const QString &fqname);

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
					MeXgui::core::gui::ConfigableProfilesControl *audioProfile;
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
