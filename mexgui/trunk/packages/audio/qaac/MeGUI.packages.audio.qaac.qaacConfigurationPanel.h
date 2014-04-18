#pragma once

#include "core/details/ProfileManager.h"
#include "QaacSettings.h"
#include "packages/audio/MeGUI.core.details.audio.AudioConfigurationPanel.h"
#include "core/util/EnumProxy.h"
#include "packages/audio/AudioCodecSettings.h"
#include "MeGUI.Properties.Settings.h"
#include "core/util/LogItem.h"
#include <string>
#include <cmath>

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

using namespace MeGUI::core::plugins::interfaces;



using namespace MeGUI::core::details::audio;


namespace MeGUI
{
	namespace packages
	{
		namespace audio
		{
			namespace qaac
			{
				class qaacConfigurationPanel : public MeGUI::core::details::audio::AudioConfigurationPanel, Editable<QaacSettings*>
				{

					public:
					~qaacConfigurationPanel()
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
					qaacConfigurationPanel();


					/// <summary>
					/// gets / sets the settings that are being shown in this configuration dialog
					/// </summary>
				protected:
					const virtual AudioCodecSettings &getCodecSettings() const;
					virtual void setCodecSettings(const AudioCodecSettings &value);

				private:
					const QaacSettings &getSettings() = Editable::Settings::get const;
					void setSettings(const QaacSettings &value) = Editable::Settings::set;


					void trackBar1_ValueChanged(object *sender, EventArgs *e);

					void cbMode_SelectedIndexChanged(object *sender, EventArgs *e);

					void cbProfile_SelectedIndexChanged(object *sender, EventArgs *e);



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


				public:
					System::Windows::Forms::ComboBox *cbProfile;
					System::Windows::Forms::Label *label3;
					System::Windows::Forms::TrackBar *trackBar;
					System::Windows::Forms::ComboBox *cbMode;
					System::Windows::Forms::Label *label2;
				private:
					System::Windows::Forms::CheckBox *chNoDelay;

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
