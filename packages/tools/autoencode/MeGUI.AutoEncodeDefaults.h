#pragma once

#include "AutoEncodeDefaultsSettings.h"
#include "Properties.Settings.h"
#include "core/gui/MainForm.h"
#include "core/details/CodecManager.h"
#include "core/util/LogItem.h"
#include "core/gui/TargetSizeSCBox.h"
#include "core/util/FileSize.h"
#include <cctype>
#include <stdexcept>
#include "stringconverter.h"

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



using namespace MeXgui::core::util;

namespace MeXgui
{
	class AutoEncodeDefaults : public System::Windows::Forms::Form
	{
		public:
		~AutoEncodeDefaults()
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
		AutoEncodeDefaults();

		const AutoEncodeDefaultsSettings &getSettings() const;
		void setSettings(const AutoEncodeDefaultsSettings &value);

	private:
		void FileSizeRadio_CheckedChanged();
		void textField_KeyPress(object *sender, KeyPressEventArgs *e);

		void container_SelectedIndexChanged();


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


		System::Windows::Forms::GroupBox *AutomaticEncodingGroup;
		System::Windows::Forms::RadioButton *noTargetRadio;
		System::Windows::Forms::RadioButton *averageBitrateRadio;
		System::Windows::Forms::RadioButton *FileSizeRadio;
		System::Windows::Forms::TextBox *projectedBitrateKBits;
		System::Windows::Forms::Label *AverageBitrateLabel;
		System::Windows::Forms::Button *cancelButton;
		System::Windows::Forms::Button *saveButton;
		System::Windows::Forms::GroupBox *OutputGroupBox;
		System::Windows::Forms::ComboBox *container;
		System::Windows::Forms::Label *containerLabel;
		System::Windows::Forms::CheckBox *addSubsNChapters;
		MeXgui::core::gui::TargetSizeSCBox *fileSize;
		MeXgui::core::gui::TargetSizeSCBox *splitSize;
		System::Windows::Forms::Label *label1;
		System::Windows::Forms::ComboBox *device;
		System::Windows::Forms::Label *DeviceLabel;

	private:
		void InitializeInstanceFields();
	};
}
