#pragma once

#include "core/details/ProfileManager.h"
#include "OneClickSettings.h"
#include "core/gui/MainForm.h"
#include "OneClickAudioControl.h"
#include "core/details/CodecManager.h"
#include "core/util/LanguageSelectionContainer.h"
#include "Properties.Settings.h"
#include "OneClickAudioControl.h"
#include "core/gui/ConfigableProfilesControl.h"
#include "core/gui/TargetSizeSCBox.h"
#include "core/gui/FileBar.h"
#include "core/util/FileSize.h"
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




namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace oneclick
			{
				class OneClickConfigPanel : public UserControl, Editable<OneClickSettings*>
				{
				private:
					MainForm *mainForm;
					QVector<OneClickAudioControl*> audioConfigurations;

					public:
					~OneClickConfigPanel()
					{
						this->Dispose(true);
					}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
					private:
					void Finalize()
					{
						this->Dispose(false);
					}

					void initAvsHandler();
					void initVideoHandler();

				public:
					OneClickConfigPanel();


					const OneClickSettings &getSettings() const;
					void setSettings(const OneClickSettings &value);


				private:
					const QString *getContainerCandidates() const;
					void setContainerCandidates(QString value[]);

					void keepInputResolution_CheckedChanged();

					void videoProfile_SelectedProfileChanged();

					void chkDontEncodeVideo_CheckedChanged();

					void btnAddAudio_Click();

					void btnRemoveAudio_Click();

					void btnAudioUp_Click();

					void btnAudioDown_Click();

					void lbDefaultAudio_SelectedIndexChanged();

					void lbNonDefaultAudio_SelectedIndexChanged();

					void btnAddSubtitle_Click();

					void btnRemoveSubtitle_Click();

					void btnSubtitleUp_Click();

					void btnSubtitleDown_Click();

					void lbDefaultSubtitle_SelectedIndexChanged();

					void lbNonDefaultSubtitle_SelectedIndexChanged();

					void btnIndexerUp_Click();

					void btnIndexerDown_Click();

					void lbIndexerPriority_MouseClick(object *sender, MouseEventArgs *e);

					int iSelectedAudioTabPage;
					void audioTab_MouseClick(object *sender, MouseEventArgs *e);

					void audioAddTrack_Click();

					void audioRemoveTrack_Click();

					void AudioAddTrack(OneClickAudioSettings *oSettings);

					void AudioResetTrack();

					void audio1_LanguageChanged();

					void AudioRemoveTrack(int iTabPageIndex);

					void audioTab_SelectedIndexChanged();

					void audioTab_KeyUp(object *sender, KeyEventArgs *e);

					void audioTab_VisibleChanged();

					void audioTab_MouseDoubleClick(object *sender, MouseEventArgs *e);

					void audioMenu_Opening(object *sender, System::ComponentModel::CancelEventArgs *e);

					void deleteOutput_Click();

					void deleteWorking_Click();


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


					System::Windows::Forms::GroupBox *otherGroupBox;
					System::Windows::Forms::CheckBox *autoDeint;
					System::Windows::Forms::CheckBox *signalAR;
					System::Windows::Forms::NumericUpDown *horizontalResolution;
					System::Windows::Forms::Label *outputResolutionLabel;
					System::Windows::Forms::CheckBox *preprocessVideo;
					System::Windows::Forms::TabControl *tabControl1;
					System::Windows::Forms::TabPage *tabPage1;
					System::Windows::Forms::TabPage *tabPage2;
					MeXgui::core::gui::ConfigableProfilesControl *avsProfile;
					System::Windows::Forms::CheckBox *autoCrop;
					System::Windows::Forms::CheckBox *keepInputResolution;
					System::Windows::Forms::TabPage *tabPage3;
					System::Windows::Forms::GroupBox *extraGroupbox;
					System::Windows::Forms::TabPage *tabPage4;
					System::Windows::Forms::GroupBox *groupBox1;
					System::Windows::Forms::ListBox *lbDefaultAudio;
					System::Windows::Forms::ListBox *lbNonDefaultAudio;
					System::Windows::Forms::Button *btnAudioDown;
					System::Windows::Forms::Button *btnAudioUp;
					System::Windows::Forms::Button *btnRemoveAudio;
					System::Windows::Forms::Button *btnAddAudio;
					System::Windows::Forms::GroupBox *groupBox2;
					System::Windows::Forms::Button *btnSubtitleDown;
					System::Windows::Forms::Button *btnSubtitleUp;
					System::Windows::Forms::Button *btnRemoveSubtitle;
					System::Windows::Forms::Button *btnAddSubtitle;
					System::Windows::Forms::ListBox *lbNonDefaultSubtitle;
					System::Windows::Forms::ListBox *lbDefaultSubtitle;
					System::Windows::Forms::TabPage *tabPage5;
					System::Windows::Forms::GroupBox *groupBox3;
					System::Windows::Forms::ListBox *lbIndexerPriority;
					System::Windows::Forms::GroupBox *groupBox4;
					System::Windows::Forms::Label *label6;
					System::Windows::Forms::Label *label5;
					System::Windows::Forms::TextBox *txtWorkingNameReplaceWith;
					System::Windows::Forms::TextBox *txtWorkingNameDelete;
					System::Windows::Forms::Label *label7;
					System::Windows::Forms::ComboBox *cbLanguageSelect;
					System::Windows::Forms::GroupBox *groupBox5;
					FileBar *outputDirectory;
					System::Windows::Forms::Label *label8;
					FileBar *workingDirectory;
					System::Windows::Forms::Label *workingDirectoryLabel;
					System::Windows::Forms::Button *btnIndexerDown;
					System::Windows::Forms::Button *btnIndexerUp;
					System::Windows::Forms::TabControl *audioTab;
					System::Windows::Forms::TabPage *audioPage0;
					OneClickAudioControl *oneClickAudioControl1;
					System::Windows::Forms::ContextMenuStrip *audioMenu;
					System::Windows::Forms::ToolStripMenuItem *audioAddTrack;
					System::Windows::Forms::ToolStripMenuItem *audioRemoveTrack;
					System::Windows::Forms::TabPage *audioPageAdd;
					System::Windows::Forms::GroupBox *groupBox6;
					System::Windows::Forms::CheckBox *chkDontEncodeVideo;
					System::Windows::Forms::CheckBox *usechaptersmarks;
					core::gui::ConfigableProfilesControl *videoProfile;
					System::Windows::Forms::Label *videoCodecLabel;
					System::Windows::Forms::GroupBox *groupBox8;
					core::gui::TargetSizeSCBox *splitSize;
					core::gui::TargetSizeSCBox *fileSize;
					System::Windows::Forms::Label *label2;
					System::Windows::Forms::Label *filesizeLabel;
					System::Windows::Forms::GroupBox *groupBox7;
					System::Windows::Forms::CheckedListBox *containerTypeList;
					System::Windows::Forms::Label *containerFormatLabel;
					System::Windows::Forms::Label *label1;
					System::Windows::Forms::TextBox *txtLeadingName;
					System::Windows::Forms::Button *deleteWorking;
					System::Windows::Forms::Button *deleteOutput;
					System::Windows::Forms::CheckBox *chkDisableIntermediateMKV;
					System::Windows::Forms::ComboBox *cbUnknownLanguage;
					System::Windows::Forms::Label *label4;

				private:
					void InitializeInstanceFields();
				};
			}
		}
	}
}
