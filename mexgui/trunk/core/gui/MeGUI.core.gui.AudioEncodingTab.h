#pragma once

#include "core/details/mux/MuxProvider.h"
#include "core/util/Util.h"
#include "packages/audio/AudioJob.h"
#include "packages/audio/AudioCodecSettings.h"
#include "core/util/PrettyFormatting.h"
#include "core/util/Exceptions.h"
#include "MeGUI.MainForm.h"
#include "core/details/CodecManager.h"
#include "FileBar.h"
#include "MeGUI.FileBar.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/LogItem.h"
#include "core/util/FileUtil.h"
#include "MeGUI.core.gui.ConfigableProfilesControl.h"
#include <string>
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
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details::video;
using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class AudioEncodingTab : public UserControl
			{
			private:
				MeGUI::AudioEncoderProvider *audioEncoderProvider;

				/// <summary>
				/// This delegate is called when a job has been successfully configured and the queue button is pressed
				/// </summary>
			public:
				Setter<MeGUI::AudioJob*> QueueJob;

				public:
				~AudioEncodingTab()
				{
					this->Dispose(true);
				}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:
				void Finalize()
				{
					this->Dispose(false);
				}

				const std::string &getQueueButtonText() const;
				void setQueueButtonText(const std::string &value);

				const std::string &getAudioContainer() const;
				void setAudioContainer(const std::string &value);

				const MeGUI::AudioEncoderProvider &getAudioEncoderProvider() const;
			private:
				const std::string &getAudioInput() const;
				void setAudioInput(const std::string &value);
				const std::string &getAudioOutput() const;
				void setAudioOutput(const std::string &value);

				/// <summary>
				/// returns the audio codec settings for the currently active audio codec
				/// </summary>
			public:
				const AudioCodecSettings &getAudCodecSettings() const;
				private:
				void setAudCodecSettings(const AudioCodecSettings &value);

				std::string verifyAudioSettings();


				AudioEncodingTab();


			private:
				void audioInput_FileSelected(FileBar *sender, FileBarEventArgs *args);

				bool bInitialStart;
				void audioContainer_SelectedIndexChanged(object *sender, EventArgs *e);

				void deleteAudioButton_Click(object *sender, EventArgs *e);

				void queueAudioButton_Click(object *sender, EventArgs *e);

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const MeGUI::AudioJob &getAudioJob() const;
				void setAudioJob(const MeGUI::AudioJob &value);

				void openAudioFile(const std::string &fileName);

				const Size &getFileTypeComboBoxSize() const;
				void setFileTypeComboBoxSize(const Size &value);

				void Reset();


			private:
				AudioEncoderType *lastCodec;
				void audioProfile_SelectedProfileChanged(object *sender, EventArgs *e);



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


				FileBar *cuts;
				System::Windows::Forms::Label *label1;
				FileBar *audioOutput;
				FileBar *audioInput;
				System::Windows::Forms::ComboBox *audioContainer;
				System::Windows::Forms::Label *audioContainerLabel;
				System::Windows::Forms::Button *queueAudioButton;
				System::Windows::Forms::Label *audioInputLabel;
				System::Windows::Forms::Label *audioOutputLabel;
				System::Windows::Forms::Button *deleteAudioButton;
				System::Windows::Forms::Label *label2;
				System::Windows::Forms::NumericUpDown *delay;
				System::Windows::Forms::Label *label3;
				ConfigableProfilesControl *audioProfile;
				System::Windows::Forms::Label *label4;
				System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;
				System::Windows::Forms::FlowLayoutPanel *flowLayoutPanel1;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
