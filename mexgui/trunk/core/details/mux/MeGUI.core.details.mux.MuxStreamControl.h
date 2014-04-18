#pragma once

#include "core/util/LanguageSelectionContainer.h"
#include "core/details/TrackInfo.h"
#include "core/details/Streams.h"
#include "core/util/LogItem.h"
#include "core/gui/FileBar.h"
#include "core/gui/MeGUI.FileBar.h"
#include "core/util/PrettyFormatting.h"
#include "core/util/VideoUtil.h"
#include "packages/reader/vobsub/idxReader.h"
#include "core/gui/MeGUI.MainForm.h"
#include <string>
#include <map>
#include <vector>

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

using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace details
		{
			namespace mux
			{
				class MuxStreamControl : public UserControl
				{
					public:
					~MuxStreamControl()
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
					MuxStreamControl();

				private:
					TrackInfo *_trackInfo;
				public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
					const MuxStream &getStream() const;

					void setStream(const MuxStream &value);

				private:
					bool showDelay;
				public:
					void setShowDelay(const bool &value);
					const bool &getShowDelay() const;

				private:
					bool showDefaultSubtitleStream;
				public:
					void setShowDefaultSubtitleStream(const bool &value);
					const bool &getShowDefaultSubtitleStream() const;

				private:
					bool showForceSubtitleStream;
				public:
					void setShowForceSubtitleStream(const bool &value);
					const bool &getShowForceSubtitleStream() const;

					const std::string &getFilter() const;
					void setFilter(const std::string &value);

					void SetLanguage(const std::string &lang);

					void SetAutoEncodeMode();

				private:
					void removeSubtitleTrack_Click(object *sender, EventArgs *e);

					void raiseEvent();

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//					public event EventHandler FileUpdated;

					void input_FileSelected(FileBar *sender, FileBarEventArgs *args);

					void chkForceStream_CheckedChanged(object *sender, EventArgs *e);


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
					System::Windows::Forms::TextBox *subName;
					System::Windows::Forms::Label *SubNamelabel;
					System::Windows::Forms::ComboBox *subtitleLanguage;
					System::Windows::Forms::Label *subtitleLanguageLabel;
					System::Windows::Forms::Label *subtitleInputLabel;
					System::Windows::Forms::Label *delayLabel;
					System::Windows::Forms::NumericUpDown *audioDelay;
				private:
					System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;
				public:
					System::Windows::Forms::CheckBox *chkDefaultStream;
					FileBar *input;
					System::Windows::Forms::CheckBox *chkForceStream;
				protected:
					System::Windows::Forms::Button *removeSubtitleTrack;

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
