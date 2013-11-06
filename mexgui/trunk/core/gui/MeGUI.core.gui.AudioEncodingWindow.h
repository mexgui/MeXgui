#pragma once

#include "core/details/PackageSystem.h"
#include "core/plugins/interfaces/Job.h"
#include "core/util/GenericRegisterer.h"
#include "packages/audio/AudioJob.h"
#include "MeGUI.core.gui.AudioEncodingTab.h"

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

using namespace MeGUI::core::details;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class AudioEncodingWindow : public System::Windows::Forms::Form
			{
			public:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				static readonly IDable<ReconfigureJob> Configurer = new IDable<ReconfigureJob>("audio_reconfigure", delegate(Job j)
				{
					if (!(dynamic_cast<AudioJob*>(j) != nullptr_Renamed))
						return nullptr_Renamed;
						AudioEncodingWindow *w = new AudioEncodingWindow();
						w->audioEncodingTab1->AudioJob = static_cast<AudioJob*>(j);
						if (w->ShowDialog() == System::Windows::Forms::DialogResult::OK)
							j = w->audioEncodingTab1->AudioJob;
							return j;
				}
			   );

				AudioEncodingWindow()
				{
					InitializeComponent();
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					audioEncodingTab1->QueueJob = delegate(AudioJob j)
					{
						this->DialogResult = System::Windows::Forms::DialogResult::OK;
					};
				}


				/// <summary>
				/// Required designer variable.
				/// </summary>
			private:
				System::ComponentModel::IContainer components = nullptr_Renamed;

				/// <summary>
				/// Clean up any resources being used.
				/// </summary>
				/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
			protected:
				void Dispose(bool disposing)
				{
					if (disposing && (components != nullptr_Renamed))
					{
						delete components;
					}
					System::Windows::Forms::Form::Dispose(disposing);
				}


				/// <summary>
				/// Required method for Designer support - do not modify
				/// the contents of this method with the code editor.
				/// </summary>
			private:
				void InitializeComponent()
				{
					System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(AudioEncodingWindow::typeid);
					this->button1 = new System::Windows::Forms::Button();
					this->audioEncodingTab1 = new MeGUI::core::gui::AudioEncodingTab();
					this->SuspendLayout();
					// 
					// button1
					// 
					this->button1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
					this->button1->Location = new System::Drawing::Point(302, 155);
					this->button1->Name = "button1";
					this->button1->Size = new System::Drawing::Size(60, 23);
					this->button1->TabIndex = 1;
					this->button1->Text = "Cancel";
					this->button1->UseVisualStyleBackColor = true;
					// 
					// audioEncodingTab1
					// 
					this->audioEncodingTab1->setAudioContainer("");
					this->audioEncodingTab1->Dock = System::Windows::Forms::DockStyle::Bottom;
					this->audioEncodingTab1->Location = new System::Drawing::Point(0, 12);
					this->audioEncodingTab1->Name = "audioEncodingTab1";
					this->audioEncodingTab1->setQueueButtonText("Update");
					this->audioEncodingTab1->Size = new System::Drawing::Size(431, 173);
					this->audioEncodingTab1->TabIndex = 0;
					// 
					// AudioEncodingWindow
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->ClientSize = new System::Drawing::Size(431, 185);
					this->Controls->Add(this->button1);
					this->Controls->Add(this->audioEncodingTab1);
					this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
					this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
					this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
					this->MaximumSize = new System::Drawing::Size(1000, 214);
					this->MinimumSize = new System::Drawing::Size(437, 214);
					this->Name = "AudioEncodingWindow";
					this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
					this->Text = "Audio Encoding Window";
					this->ResumeLayout(false);

				}


				AudioEncodingTab audioEncodingTab1;
				System::Windows::Forms::Button button1;

			private:
				void InitializeInstanceFields();

public:
				AudioEncodingWindow()
				{
					InitializeInstanceFields();
				}
			};
		}
	}
}
