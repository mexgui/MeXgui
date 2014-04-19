#pragma once

#include "core/details/mux/MuxProvider.h"
#include "core/util/Util.h"
#include "packages/audio/AudioJob.h"
#include "packages/audio/AudioCodecSettings.h"
#include "core/util/PrettyFormatting.h"
#include "core/util/Exceptions.h"
#include "MainForm.h"
#include "core/details/CodecManager.h"
#include "FileBar.h"
#include "FileBar.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/LogItem.h"
#include "core/util/FileUtil.h"
#include "ConfigableProfilesControl.h"
#include <QString>
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





//using namespace System::Data;



//using namespace System::Text;

//using namespace System::Text::RegularExpressions;



using namespace MeXgui::core::details::video;
using namespace MeXgui::core::util;

namespace MeXgui
{
	namespace core
	{
		namespace gui
		{
			class AudioEncodingTab : public UserControl
			{
			private:
				MeXgui::AudioEncoderProvider *audioEncoderProvider;

				/// <summary>
				/// This delegate is called when a job has been successfully configured and the queue button is pressed
				/// </summary>
			public:
				Setter<MeXgui::AudioJob*> QueueJob;

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

				const QString &getQueueButtonText() const;
				void setQueueButtonText(const QString &value);

				const QString &getAudioContainer() const;
				void setAudioContainer(const QString &value);

				const MeXgui::AudioEncoderProvider &getAudioEncoderProvider() const;
			private:
				const QString &getAudioInput() const;
				void setAudioInput(const QString &value);
				const QString &getAudioOutput() const;
				void setAudioOutput(const QString &value);

				/// <summary>
				/// returns the audio codec settings for the currently active audio codec
				/// </summary>
			public:
				const AudioCodecSettings &getAudCodecSettings() const;
				private:
				void setAudCodecSettings(const AudioCodecSettings &value);

				QString verifyAudioSettings();


				AudioEncodingTab();


			private:
				void audioInput_FileSelected(FileBar *sender, FileBarQEvent *args);

				bool bInitialStart;
				void audioContainer_SelectedIndexChanged(QObject *sender, QEvent *e);

				void deleteAudioButton_Click(QObject *sender, QEvent *e);

				void queueAudioButton_Click(QObject *sender, QEvent *e);

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const MeXgui::AudioJob &getAudioJob() const;
				void setAudioJob(const MeXgui::AudioJob &value);

				void openAudioFile(const QString &fileName);

				const Size &getFileTypeComboBoxSize() const;
				void setFileTypeComboBoxSize(const Size &value);

				void Reset();


			private:
				AudioEncoderType *lastCodec;
				void audioProfile_SelectedProfileChanged(QObject *sender, QEvent *e);



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
