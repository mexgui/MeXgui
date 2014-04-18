#pragma once

#include "MeGUI.core.gui.ProfilePorter.h"
#include "ProfileImporter.h"
#include "MeGUI.MainForm.h"
#include "core/util/FileUtil.h"
#include "core/details/ProfileManager.h"
#include "core/plugins/interfaces/Profile.h"
#include "core/util/LogItem.h"
#include "core/util/Util.h"
#include <QString>
#include <QMap>
#include <QVector>

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




//using namespace System::Collections::Generic;



//using namespace System::Data;





//using namespace System::Text;



//using namespace System::Xml;

using namespace ICSharpCode::SharpZipLib::Zip;

using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class ProfileImporter : public MeGUI::core::gui::ProfilePorter
			{
				public:
				~ProfileImporter()
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
				static QString askForZipFile();

				DirectoryInfo *tempFolder;
				DirectoryInfo *extraFiles;
				MainForm *mainForm;
				XmlDocument *ContextHelp;

			public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public ProfileImporter(MainForm mf, bool bSilentError) :this(mf, askForZipFile(), bSilentError)
				ProfileImporter(MainForm *mf, bool bSilentError);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public ProfileImporter(MainForm mf, string filename, bool bSilentError) : this(mf, File.OpenRead(filename), bSilentError)
				ProfileImporter(MainForm *mf, const QString &filename, bool bSilentError);

				ProfileImporter(MainForm *mf, Stream *s, bool bSilentError);

				bool ErrorDuringInit();

				void AutoImport();

			private:
				std::QMap<QString, QString> createInitSubTable();

				const QVector<QString> &getextraFilesList() const;

				void import_Click(QObject *sender, QEvent *e);

				void checkAllToolStripMenuItem_Click(QObject *sender, QEvent *e);

				void checkNoneToolStripMenuItem_Click(QObject *sender, QEvent *e);

				QString SelectHelpText(const QString &node);

				void SetToolTips();

				void ProfileImporter_Shown(QObject *sender, QEvent *e);


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


				System::Windows::Forms::ContextMenuStrip *statusCheck;
				System::Windows::Forms::ToolStripMenuItem *checkAllToolStripMenuItem;
				System::Windows::Forms::ToolStripMenuItem *checkNoneToolStripMenuItem;
				System::Windows::Forms::ToolTip *PresetImporterToolTip;


			private:
				void InitializeInstanceFields();
			};
		}
	}
}
