#pragma once

#include "core/details/MeXguiSettings.h"
#include "SourceDetectorSettings.h"
#include "packages/tools/autoencode/AutoEncodeDefaultsSettings.h"
#include "HelpButton.h"
#include "FileBar.h"
#include "TargetSizeSCBox.h"
#include "core/util/LanguageSelectionContainer.h"
#include "core/util/OSInfo.h"
#include "core/util/FileSize.h"
#include "FileBar.h"
#include "SourceDetectorConfigWindow.h"
#include "Properties.Settings.h"
#include "core/plugins/interfaces/Job.h"
#include "MainForm.h"
#include <QString>
#include <QVector>
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







//using namespace System::Text;

//using namespace System::Xml;



namespace MeXgui
{
	/// <summary>
	/// Summary description for SettingsForm.
	/// </summary>
	class SettingsForm : public System::Windows::Forms::Form
	{
	private:
		System::Windows::Forms::Button *saveButton;
		System::Windows::Forms::Button *cancelButton;
		MeXguiSettings *internalSettings;
		Button *resetDialogs;
		TabControl *tabControl1;
		TabPage *tabPage1;
		SourceDetectorSettings *sdSettings;
		System::Windows::Forms::FolderBrowserDialog *openFolderDialog;
		CheckBox *chkboxUseAdvancedTooltips;
		Button *configSourceDetector;
		System::Windows::Forms::GroupBox *otherGroupBox;
		System::Windows::Forms::ComboBox *priority;
		System::Windows::Forms::OpenFileDialog *openExecutableDialog;
		System::Windows::Forms::CheckBox *autostartQueue;
		System::Windows::Forms::CheckBox *openScript;
		System::Windows::Forms::Label *priorityLabel;
		System::Windows::Forms::CheckBox *deleteCompletedJobs;
		System::Windows::Forms::CheckBox *deleteAbortedOutput;
		System::Windows::Forms::CheckBox *deleteIntermediateFiles;
		System::Windows::Forms::CheckBox *openProgressWindow;
		AutoEncodeDefaultsSettings *autoEncodeDefaults;
		TabPage *tabPage3;
		GroupBox *autoUpdateGroupBox;
		CheckBox *useAutoUpdateCheckbox;
		GroupBox *outputExtensions;
		TextBox *videoExtension;
		Label *label11;
		Label *label12;
		TextBox *audioExtension;
		GroupBox *autoModeGroupbox;
		Label *label13;
		NumericUpDown *nbPasses;
		Label *audioExtLabel;
		Label *videoExtLabel;
		Button *autoEncodeDefaultsButton;
		TextBox *command;
		RadioButton *runCommand;
		RadioButton *shutdown;
		RadioButton *donothing;
		Button *configureServersButton;
		NumericUpDown *acceptableFPSError;
		Label *label15;
		NumericUpDown *audiosamplesperupdate;
		Label *label6;
		MeXgui::core::gui::HelpButton *helpButton1;
		CheckBox *keep2ndPassOutput;
		CheckBox *keep2ndPassLogFile;
		Button *configAutoEncodeDefaults;
		GroupBox *gbVideoPreview;
		CheckBox *chAlwaysOnTop;
		GroupBox *groupBox2;
		TextBox *txt_httpproxyuid;
		TextBox *txt_httpproxyaddress;
		Label *label21;
		Label *label20;
		Label *label19;
		Label *label18;
		TextBox *txt_httpproxypwd;
		TextBox *txt_httpproxyport;
		GroupBox *gbDefaultOutput;
		Button *clearDefaultOutputDir;
		FileBar *defaultOutputDir;
		CheckBox *cbAddTimePos;
		CheckBox *backupfiles;
		CheckBox *forcerawavcuse;
		TabPage *tabPage2;
		GroupBox *vobGroupBox;
		Label *percentLabel;
		NumericUpDown *forceFilmPercentage;
		CheckBox *autoForceFilm;
		GroupBox *groupBox4;
		Button *btnClearMP4TempDirectory;
		FileBar *tempDirMP4;
		GroupBox *groupBox5;
		GroupBox *groupBox6;
		CheckBox *cbAutoLoadDG;
		RadioButton *rbCloseMeXgui;
		CheckBox *cbAutoStartQueueStartup;
		ComboBox *cbAutoUpdateServerSubList;
		CheckBox *chkAlwaysMuxMKV;
		ToolTip *toolTipHelp;
		IContainer *components;
		CheckBox *chkEnable64bitX264;
		CheckBox *chkEnsureCorrectPlaybackSpeed;
		GroupBox *groupBox3;
		ComboBox *defaultLanguage2;
		ComboBox *defaultLanguage1;
		CheckBox *chkSelectHDTracks;
		Button *btnClearOutputDirecoty;
		NumericUpDown *ffmsThreads;
		Label *lblffmsThreads;
		Label *lblForcedName;
		TextBox *txtForcedName;
		CheckBox *cbUseITUValues;
		CheckBox *cbOpenAVSinThread;
		core::gui::TargetSizeSCBox *targetSizeSCBox1;
		FileBar *neroaacencLocation;
		CheckBox *useNeroAacEnc;
		Label *lblNero;
		CheckBox *useDGIndexNV;
		CheckBox *useQAAC;
		Label *label1;
		ComboBox *cbHttpProxyMode;
		CheckBox *chx264ExternalMuxer;
		CheckBox *chUse10BitsX264;
		XmlDocument *ContextHelp;
		public:
		~SettingsForm()
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
		SettingsForm();

		/// <summary>
		/// Sets any required tooltips
		/// </summary>
	private:
		void SetToolTips();

		/// <summary>
		/// Gets the help text
		/// </summary>
		QString SelectHelpText(const QString &node);

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		void Dispose(bool disposing);
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent();
		void configSourceDetector_Click(QObject *sender, QEvent *e);

		void resetDialogs_Click(QObject *sender, QEvent *e);

		void runCommand_CheckedChanged(QObject *sender, QEvent *e);
		/// <summary>
		/// launches the autoencode default settings window
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void autoEncodeDefaultsButton_Click(QObject *sender, QEvent *e);

		/// <summary>
		/// Launches configuration of auto-update servers
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void configureServersButton_Click(QObject *sender, QEvent *e);

		void cbHttpProxyMode_SelectedIndexChanged(QObject *sender, QEvent *e);

		void clearDefaultOutputDir_Click(QObject *sender, QEvent *e);

	public:
		const MeXguiSettings &getSettings() const;
		void setSettings(const MeXguiSettings &value);

	private:
		void backupfiles_CheckedChanged(QObject *sender, QEvent *e);

		void btnClearMP4TempDirectory_Click(QObject *sender, QEvent *e);

		void btnClearOutputDirecoty_Click(QObject *sender, QEvent *e);

		void tempDirMP4_FileSelected(FileBar *sender, FileBarQEvent *args);

		void useNeroAacEnc_CheckedChanged(QObject *sender, QEvent *e);

		void useQAAC_CheckedChanged(QObject *sender, QEvent *e);

		void chUse10BitsX264_CheckedChanged(QObject *sender, QEvent *e);

	private:
		void InitializeInstanceFields();
	};
}
