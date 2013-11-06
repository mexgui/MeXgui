#pragma once

#include "core/details/TrackInfo.h"
#include "core/util/LogItem.h"
#include "core/gui/MeGUI.MainForm.h"
#include <string>
#include <vector>
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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;

using namespace MeGUI::core::util;

namespace MeGUI
{
	class MkvInfo
	{
	private:
		bool _bHasChapters, _bMuxable;
		std::string _strResult, _strFile;
		std::vector<TrackInfo*> _oTracks;
		LogItem *_oLog;

	public:
		MkvInfo(const std::string &strFile, LogItem *&oLog);

		const bool &getHasChapters() const;

		const bool &getIsMuxable() const;

	private:
		void getInfo();

	public:
		bool extractChapters(const std::string &strChapterFile);

	private:
		void parseResult();

		void backgroundWorker_ErrorDataReceived(object *sender, DataReceivedEventArgs *e);

		void backgroundWorker_OutputDataReceived(object *sender, DataReceivedEventArgs *e);

	private:
		void InitializeInstanceFields();
	};
}
