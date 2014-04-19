#pragma once

#include "core/gui/MainForm.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "packages/tools/fileindexer/FileIndexerWindow.h"
#include <QString>
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

//using namespace System::Diagnostics;



//using namespace System::Text;

//using namespace System::Windows;



using namespace Utils::MessageBoxExLib;

namespace MeXgui
{
	enum DuplicateResponse
	{
		OVERWRITE,
		RENAME,
		SKIP,
		ABORT
	};

	class DialogManager
	{
	private:
		MainForm *mainForm;

	public:
		DialogManager(MainForm *mainForm);

		/// <summary>
		/// Creates a message box with the given text, title and icon. Also creates a 'don't show me again' checkbox
		/// </summary>
		/// <param name="text">The text to display</param>
		/// <param name="caption">The window title</param>
		/// <param name="icon">The icon to display</param>
		/// <returns>The newly created message box</returns>
	private:
		MessageBoxEx *createMessageBox(const QString &text, const QString &caption, MessageBoxIcon *icon);
		/// <summary>
		/// Shows a message dialog (without a question) with a 'don't ask again' checkbox
		/// </summary>
		/// <param name="text">The text to display</param>
		/// <param name="caption">The window title</param>
		/// <param name="icon">The icon to display</param>
		/// <returns>Whether to show this again</returns>
		bool showMessage(const QString &text, const QString &caption, MessageBoxIcon *icon);
		/// <summary>
		/// Shows a custom dialog built on the MessageBoxEx system
		/// </summary>
		/// <param name="text">The text to display</param>
		/// <param name="caption">The window title to display</param>
		/// <param name="icon">The icon to display</param>
		/// <param name="askAgain">Returns whether to show this dialog again</param>
		/// <returns>true if the user pressed yes, false otherwise</returns>
		bool askAbout(const QString &text, const QString &caption, MessageBoxIcon *icon, bool &askAgain);

		/// <summary>
		/// Shows a custom dialog built on the MessageBoxEx system
		/// </summary>
		/// <param name="text">The text to display</param>
		/// <param name="caption">The window title to display</param>
		/// <param name="button1Text">The text on the first button</param>
		/// <param name="button2Text">The text on the second button</param>
		/// <param name="icon">The icon to display</param>
		/// <param name="askAgain">Returns whether to ask again</param>
		/// <returns>true if button 1 was pressed, false otherwise</returns>
		bool askAbout(const QString &text, const QString &caption, const QString &button1Text, const QString &button2Text, MessageBoxIcon *icon, bool &askAgain);

		/// <summary>
		/// Shows a custom dialog built on the MessageBoxEx system
		/// </summary>
		/// <param name="text">The text to display</param>
		/// <param name="caption">The window title to display</param>
		/// <param name="button1Text">The text on the first button</param>
		/// <param name="button2Text">The text on the second button</param>
		/// <param name="button2Text">The text on the third button</param>
		/// <param name="icon">The icon to display</param>
		/// <returns>0, 1 or 2 depending on the button pressed</returns>
		int askAbout3(const QString &text, const QString &caption, const QString &button1Text, const QString &button2Text, const QString &button3Text, MessageBoxIcon *icon);

	public:
		bool overwriteJobOutput(const QString &outputname);

		bool overwriteProfile(const QString &profname);

		bool useOneClick();

		int AVSCreatorOpen(const QString &videoInput);

		bool createJobs(const QString &error);

		bool addConvertToYV12(const QString &colorspace);

		bool DeleteIntermediateFiles(QVector<QString> &arrFiles);
	};
}
