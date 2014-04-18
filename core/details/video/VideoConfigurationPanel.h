#pragma once

#include "core/plugins/interfaces/ISettingsProvider.h"
#include "core/gui/MeXgui.MainForm.h"
#include "core/util/LogItem.h"
#include "VideoCodecSettings.h"
#include <QString>
#include <stdexcept>

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



using namespace MeXgui::core::plugins::interfaces;

namespace MeXgui
{
	namespace core
	{
		namespace details
		{
			namespace video
			{
				class VideoConfigurationPanel : public UserControl
				{
				protected:
					bool updating;
				private:
					double bytesPerFrame;
					bool advancedToolTips;
				protected:
					int lastEncodingMode;

				private:
					bool loaded;
				protected:
					QString input, output, encoderPath;
					ToolTip *tooltipHelp;
				private:
					IContainer *components;
				public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public VideoConfigurationPanel() : this(nullptr, new VideoInfo())
					VideoConfigurationPanel();


					VideoConfigurationPanel(MainForm *mainForm, VideoInfo *info);

				private:
					void VideoConfigurationPanel_Load();


					/// <summary>
					/// Generates the commandline
					/// </summary>
					/// <returns></returns>
				protected:
					virtual QString getCommandline();

					/// <summary>
					/// The method by which codecs can do their pre-commandline generation adjustments (eg tri-state adjustment).
					/// </summary>
					virtual void doCodecSpecificAdjustments();

					/// <summary>
					/// The method by which codecs can add things to the Load event
					/// </summary>
					virtual void doCodecSpecificLoadAdjustments();

					/// <summary>
					/// Returns whether settings is a valid settings object for this instance. Should be implemented by one line:
					/// return (settings is xxxxSettings);
					/// </summary>
					/// <param name="settings">The settings to check</param>
					/// <returns>Whether the settings are valid</returns>
					virtual bool isValidSettings(VideoCodecSettings *settings);

					/// <summary>
					/// Returns a new instance of the codec settings. This must be specific to the type of the config dialog, so
					/// that it can be set with the Settings.set property.
					/// </summary>
					/// <returns>A new instance of xxxSettings</returns>
					virtual VideoCodecSettings *defaultSettings();
					void showCommandLine();
					void genericUpdate();

				public:
					const bool &getAdvancedToolTips() const;
					void setAdvancedToolTips(const bool &value);

					const double &getBytesPerFrame() const;
					void setBytesPerFrame(const double &value);





				protected:
					TabControl *tabControl1;
					TextBox *commandline;
					TabPage *mainTabPage;


				private:
					void InitializeComponent();

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
