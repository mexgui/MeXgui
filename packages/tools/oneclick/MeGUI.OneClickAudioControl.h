#pragma once

#include "core/util/LanguageSelectionContainer.h"
#include "core/util/EnumProxy.h"
#include "OneClickSettings.h"
#include "core/gui/MeXgui.MainForm.h"
#include "core/plugins/interfaces/Profile.h"
#include "core/util/LogItem.h"
#include "core/gui/MeXgui.ConfigableProfilesControl.h"
#include <QString>
#include <QVector>

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





using namespace MeXgui::core::gui;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;


namespace MeXgui
{
	class OneClickAudioControl : public UserControl
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler LanguageChanged;

		public:
		~OneClickAudioControl()
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
		OneClickAudioControl();

		void SetProfileNameOrWarn(const QString &fqname);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
		const AudioEncodingMode &getEncodingMode() const;
		void setEncodingMode(const AudioEncodingMode &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
		const Profile &getEncoderProfile() const;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
		const QString &getLanguage() const;
		void setLanguage(const QString &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
		const bool &getUseFirstTrackOnly() const;
		void setUseFirstTrackOnly(const bool &value);

	private:
		void cbEncodingMode_SelectedIndexChanged();

		void language_SelectedIndexChanged();

	public:
		void SetDefault();


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


	protected:
		System::Windows::Forms::ComboBox *language;
		System::Windows::Forms::Label *languageLabel;
	private:
		System::Windows::Forms::TableLayoutPanel *tableLayoutPanel1;
		core::gui::ConfigableProfilesControl *encoderProfile;
		System::Windows::Forms::ComboBox *cbEncodingMode;
	protected:
		System::Windows::Forms::Label *label2;
		System::Windows::Forms::Label *label1;
	private:
		System::Windows::Forms::CheckBox *cbFirstTrackOnly;

	private:
		void InitializeInstanceFields();
	};
}
