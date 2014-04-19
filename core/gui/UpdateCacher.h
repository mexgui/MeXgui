#pragma once

#include "UpdateWindow.h"
#include "MainForm.h"
#include "core/util/LogItem.h"
#include "core/util/FileUtil.h"
#include "core/util/HttpProxy.h"
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





//using namespace System::Net;

//using namespace System::Text;

//using namespace System::Threading;

using namespace ICSharpCode::SharpZipLib::Zip;
using namespace SevenZip;

using namespace MeXgui::core::util;


namespace MeXgui
{
	class UpdateCacher
	{
	public:
		static void flushOldCachedFilesAsync(QVector<QString> &urls, UpdateWindow *oUpdate);

	private:
		static void ensureSensibleCacheFolderExists();

	public:
		static UpdateWindow::ErrorState DownloadFile(const QString &url, Uri *serverAddress, Stream *&str, DownloadProgressChangedEventHandler *wc_DownloadProgressChanged, UpdateWindow *oUpdate);

		static void FlushFile(const QString &p, UpdateWindow *oUpdate);
	};
}
