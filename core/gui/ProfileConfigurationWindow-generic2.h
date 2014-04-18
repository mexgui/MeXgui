#pragma once

#include "Profiles.h"
#include "core/plugins/interfaces/Profile.h"
#include "core/details/ProfileManager.h"
#include "MeGUI.Properties.Settings.h"
#include "MeGUI.MainForm.h"
#include "core/util/LogItem.h"
#include "MeGUI.core.gui.InputBox.h"
#include "core/util/Tuples.h"
#include "core/util/Util.h"
#include <QString>
#include <cmath>

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

//using namespace System::Diagnostics;



//using namespace System::Text;



using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;


namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
			template<typename TSettings, typename TPanel> where TPanel : Control, Editable<TSettings>
			class ProfileConfigurationWindow : public Formwhere TSettings : GenericSettings, new()
			{
				public:
				~ProfileConfigurationWindow()
				{
					this->Dispose(true);
				}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:
				void Finalize()
				{
					this->Dispose(false);
				}

			private:
				const GenericProfile<TSettings> &getscratchPadProfile() const
				{
					return byName(ProfileManager::ScratchPadName);
				}

				TPanel s;
				bool bCloseFormWithoutSaving, bSaveSettings;

				const TSettings &getSettings() const
				{
					return s->Settings;
				}
				void setSettings(const TSettings &value)
				{
					s->Settings = value;
				}

				/// <summary>
				/// gets the name of the currently selected profile
				/// </summary>
			public:
				const QString &getCurrentProfileName() const
				{
					return getSelectedProfile()->getName();
				}



		/*        public ProfileConfigurationWindow(ProfileManager p, Control sPanel, Gettable<TSettings> s, string initialProfile)
		            : this(p, sPanel, s, initialProfile, new TSettings().getSettingsType()) { }*/

				ProfileConfigurationWindow(TPanel t, const QString &title)
				{
					InitializeInstanceFields();
					InitializeComponent();
					this->Text = title + " configuration dialog";
					this->s = t;
					System::Drawing::Size *size = Size;
					size->Height += t->Height - panel1->Height;
					size->Width += __max(t->Width - panel1->Width, 0);
					Size = size;
					t->Dock = DockStyle::Fill;
					panel1->Controls->Add(t);
					this->Icon = MainForm::Instance->Icon;
				}

			private:
				void loadDefaultsButton_Click(QObject *sender, QEvent *e)
				{
					s->Settings = new TSettings();
					putSettingsInScratchpad();
				}

				void updateButton_Click(QObject *sender, QEvent *e)
				{
					GenericProfile<TSettings> *prof = getSelectedProfile();
					prof->setSettings(s->Settings);
				}

				void newVideoProfileButton_Click(QObject *sender, QEvent *e)
				{
					QString profileName = InputBox::Show("Please give the preset a name", "Please give the preset a name", "");
					if (profileName == "")
						return;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
					profileName = profileName.Trim();
					if (profileName.length() == 0)
						return;
					GenericProfile<TSettings> *prof = new GenericProfile<TSettings>(profileName, s->Settings);
					if (byName(profileName) != 0)
						MessageBox::Show("Sorry, presets must have unique names", "Duplicate preset name", MessageBoxButtons::OK);
					else
					{
						videoProfile->Items->Add(prof);
						videoProfile->SelectedItem = prof;
					}
				}

			public:
				const GenericProfile<TSettings> &getSelectedProfile() const
				{
					return static_cast<GenericProfile<TSettings>*>(videoProfile->SelectedItem);
				}
				void setSelectedProfile(const GenericProfile<TSettings> &value)
				{
					// We can't just set videoProfile.SelectedItem = value, because the profiles in videoProfile are cloned
					for (unknown::const_iterator p = videoProfile->Items.begin(); p != videoProfile->Items.end(); ++p)
						if ((*p)->Name == value->getName())
						{
							videoProfile->SelectedItem = *p;
							return;
						}
				}

				const Tuple<IEnumerable<GenericProfile<TSettings>*>*, GenericProfile<TSettings>*> &getProfiles() const
				{
					return new Tuple<IEnumerable<GenericProfile<TSettings>*>*, GenericProfile<TSettings>*>(Util::CastAll<GenericProfile<TSettings>*>(videoProfile->Items), getSelectedProfile());
				}

				void setProfiles(const Tuple<IEnumerable<GenericProfile<TSettings>*>*, GenericProfile<TSettings>*> &value)
				{
					videoProfile->Items->Clear();
					for (IEnumerable<GenericProfile<TSettings>*>::const_iterator p = value->a->begin(); p != value->a->end(); ++p)
						videoProfile->Items->Add((*p)->clone());

					setSelectedProfile(value->b);
				}

			private:
				GenericProfile<TSettings> *byName(const QString &profileName)
				{
					for (IEnumerable<GenericProfile<TSettings>*>::const_iterator p = getProfiles()->a->begin(); p != getProfiles()->a->end(); ++p)
						if ((*p)->Name == profileName)
							return p;

					return 0;
				}

				void videoProfile_SelectedIndexChanged(QObject *sender, QEvent *e)
				{
					this->setSettings(getSelectedProfile()->getSettings());
				}

				void deleteVideoProfileButton_Click(QObject *sender, QEvent *e)
				{
					GenericProfile<TSettings> *prof = static_cast<GenericProfile<TSettings>*>(this->videoProfile->SelectedItem);
					assert(prof != 0);

					videoProfile->Items->Remove(prof);

					if (prof->getName() == ProfileManager::ScratchPadName && videoProfile->Items->Count > 0)
						videoProfile->SelectedIndex = 0;
					else
						loadDefaultsButton_Click(0, 0);
				}

				void okButton_Click(QObject *sender, QEvent *e)
				{
					bSaveSettings = true;
					this->Close();
				}

				void putSettingsInScratchpad()
				{
					TSettings s = getSettings();
					GenericProfile<TSettings> *p = getscratchPadProfile();

					if (p == 0)
					{
						p = new GenericProfile<TSettings>(ProfileManager::ScratchPadName, s);
						videoProfile->Items->Add(p);
					}

					p->setSettings(s);
					videoProfile->SelectedItem = p;
				}

				void ProfileConfigurationWindow_FormClosing(QObject *sender, FormClosingQEvent *e)
				{
					if (bCloseFormWithoutSaving == true)
						return;

					Profile *prof = getSelectedProfile();
					if (prof->getName() == ProfileManager::ScratchPadName)
						prof->BaseSettings = getSettings();
					else if (!getSettings()->Equals(prof->BaseSettings))
					{
						switch (MessageBox::Show("Profile has been changed. Update the selected profile? (Pressing No will save your changes to the scratchpad)", "Profile update", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question))
						{
							case DialogResult::Yes:
								prof->BaseSettings = getSettings();
								break;

							case DialogResult::No:
								putSettingsInScratchpad();
								break;

							case DialogResult::Cancel:
								if (bSaveSettings == true)
								{
									bSaveSettings = false;
									e->Cancel = true;
								}
								return;
						}
					}
					this->DialogResult = DialogResult::OK;
				}

				void cancelButton_Click(QObject *sender, QEvent *e)
				{
					bCloseFormWithoutSaving = true;
					this->Close();
				}


			protected:
				GroupBox *presetsGroupbox;
			private:
				Panel *panel1;
			protected:
				Button *cancelButton;
				Button *okButton;
			private:
				Button *updateButton;
				Button *loadDefaultsButton;
				ComboBox *videoProfile;
				Button *newVideoProfileButton;
				Button *deleteVideoProfileButton;


				/// <summary>
				/// Required designer variable.
				/// </summary>
				System::ComponentModel::IContainer *components;

				/// <summary>
				/// Clean up any resources being used.
				/// </summary>
				/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
				void Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					Formwhere TSettings : GenericSettings::Dispose(disposing);
				}


				/// <summary>
				/// Required method for Designer support - do not modify
				/// the contents of this method with the code editor.
				/// </summary>
				void InitializeComponent()
				{
					this->presetsGroupbox = new System::Windows::Forms::GroupBox();
					this->updateButton = new System::Windows::Forms::Button();
					this->loadDefaultsButton = new System::Windows::Forms::Button();
					this->videoProfile = new System::Windows::Forms::ComboBox();
					this->newVideoProfileButton = new System::Windows::Forms::Button();
					this->deleteVideoProfileButton = new System::Windows::Forms::Button();
					this->panel1 = new System::Windows::Forms::Panel();
					this->cancelButton = new System::Windows::Forms::Button();
					this->okButton = new System::Windows::Forms::Button();
					this->presetsGroupbox->SuspendLayout();
					this->SuspendLayout();
					// 
					// presetsGroupbox
					// 
					this->presetsGroupbox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->presetsGroupbox->Controls->Add(this->updateButton);
					this->presetsGroupbox->Controls->Add(this->loadDefaultsButton);
					this->presetsGroupbox->Controls->Add(this->videoProfile);
					this->presetsGroupbox->Controls->Add(this->newVideoProfileButton);
					this->presetsGroupbox->Controls->Add(this->deleteVideoProfileButton);
					this->presetsGroupbox->Location = new System::Drawing::Point(6, 405);
					this->presetsGroupbox->Name = "presetsGroupbox";
					this->presetsGroupbox->Size = new System::Drawing::Size(400, 48);
					this->presetsGroupbox->TabIndex = 44;
					this->presetsGroupbox->TabStop = false;
					this->presetsGroupbox->Text = "Presets";
					// 
					// updateButton
					// 
					this->updateButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->updateButton->Location = new System::Drawing::Point(235, 18);
					this->updateButton->Name = "updateButton";
					this->updateButton->Size = new System::Drawing::Size(50, 23);
					this->updateButton->TabIndex = 15;
					this->updateButton->Text = "Update";
					this->updateButton->UseVisualStyleBackColor = true;
					this->updateButton->Click += new System::EventHandler(this, &ProfileConfigurationWindow::updateButton_Click);
					// 
					// loadDefaultsButton
					// 
					this->loadDefaultsButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->loadDefaultsButton->Location = new System::Drawing::Point(291, 18);
					this->loadDefaultsButton->Name = "loadDefaultsButton";
					this->loadDefaultsButton->Size = new System::Drawing::Size(103, 23);
					this->loadDefaultsButton->TabIndex = 14;
					this->loadDefaultsButton->Text = "Load Defaults";
					this->loadDefaultsButton->UseVisualStyleBackColor = true;
					this->loadDefaultsButton->Click += new System::EventHandler(this, &ProfileConfigurationWindow::loadDefaultsButton_Click);
					// 
					// videoProfile
					// 
					this->videoProfile->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->videoProfile->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->videoProfile->Location = new System::Drawing::Point(8, 18);
					this->videoProfile->Name = "videoProfile";
					this->videoProfile->Size = new System::Drawing::Size(121, 21);
					this->videoProfile->Sorted = true;
					this->videoProfile->TabIndex = 11;
					this->videoProfile->SelectedIndexChanged += new System::EventHandler(this, &ProfileConfigurationWindow::videoProfile_SelectedIndexChanged);
					// 
					// newVideoProfileButton
					// 
					this->newVideoProfileButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->newVideoProfileButton->Location = new System::Drawing::Point(189, 18);
					this->newVideoProfileButton->Name = "newVideoProfileButton";
					this->newVideoProfileButton->Size = new System::Drawing::Size(40, 23);
					this->newVideoProfileButton->TabIndex = 12;
					this->newVideoProfileButton->Text = "New";
					this->newVideoProfileButton->Click += new System::EventHandler(this, &ProfileConfigurationWindow::newVideoProfileButton_Click);
					// 
					// deleteVideoProfileButton
					// 
					this->deleteVideoProfileButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->deleteVideoProfileButton->Location = new System::Drawing::Point(135, 18);
					this->deleteVideoProfileButton->Name = "deleteVideoProfileButton";
					this->deleteVideoProfileButton->Size = new System::Drawing::Size(48, 23);
					this->deleteVideoProfileButton->TabIndex = 13;
					this->deleteVideoProfileButton->Text = "Delete";
					this->deleteVideoProfileButton->Click += new System::EventHandler(this, &ProfileConfigurationWindow::deleteVideoProfileButton_Click);
					// 
					// panel1
					// 
					this->panel1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->panel1->Location = new System::Drawing::Point(2, 2);
					this->panel1->Name = "panel1";
					this->panel1->Size = new System::Drawing::Size(411, 399);
					this->panel1->TabIndex = 45;
					// 
					// cancelButton
					// 
					this->cancelButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
					this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
					this->cancelButton->Location = new System::Drawing::Point(358, 459);
					this->cancelButton->Name = "cancelButton";
					this->cancelButton->Size = new System::Drawing::Size(48, 23);
					this->cancelButton->TabIndex = 47;
					this->cancelButton->Text = "Cancel";
					this->cancelButton->Click += new System::EventHandler(this, &ProfileConfigurationWindow::cancelButton_Click);
					// 
					// okButton
					// 
					this->okButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
					this->okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
					this->okButton->Location = new System::Drawing::Point(312, 459);
					this->okButton->Name = "okButton";
					this->okButton->Size = new System::Drawing::Size(40, 23);
					this->okButton->TabIndex = 46;
					this->okButton->Text = "OK";
					this->okButton->Click += new System::EventHandler(this, &ProfileConfigurationWindow::okButton_Click);
					// 
					// ProfileConfigurationWindow
					// 
					this->ClientSize = new System::Drawing::Size(414, 490);
					this->Controls->Add(this->cancelButton);
					this->Controls->Add(this->okButton);
					this->Controls->Add(this->panel1);
					this->Controls->Add(this->presetsGroupbox);
					this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
					this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
					this->MaximizeBox = false;
					this->MinimizeBox = false;
					this->Name = "ProfileConfigurationWindow";
					this->FormClosing += new System::Windows::Forms::FormClosingEventHandler(this, &ProfileConfigurationWindow::ProfileConfigurationWindow_FormClosing);
					this->presetsGroupbox->ResumeLayout(false);
					this->ResumeLayout(false);

				}


			private:
				void InitializeInstanceFields()
				{
					bCloseFormWithoutSaving = false
					bSaveSettings = false;
					delete components;
				}
			};
		}
	}
}
