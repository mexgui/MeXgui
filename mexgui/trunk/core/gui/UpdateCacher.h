#pragma once

#include "MeGUI.UpdateWindow.h"
#include "MeGUI.MainForm.h"
#include "core/util/LogItem.h"
#include "core/util/FileUtil.h"
#include "core/util/HttpProxy.h"
#include <string>
#include <vector>

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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Net;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;

using namespace ICSharpCode::SharpZipLib::Zip;
using namespace SevenZip;

using namespace MeGUI::core::util;


namespace MeGUI
{
	class UpdateCacher
	{
	public:
		static void flushOldCachedFilesAsync(std::vector<std::string> &urls, UpdateWindow *oUpdate);

	private:
		static void ensureSensibleCacheFolderExists();

	public:
		static UpdateWindow::ErrorState DownloadFile(const std::string &url, Uri *serverAddress, Stream *&str, DownloadProgressChangedEventHandler *wc_DownloadProgressChanged, UpdateWindow *oUpdate);

		static void FlushFile(const std::string &p, UpdateWindow *oUpdate);
	};
}
