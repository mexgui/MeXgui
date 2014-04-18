#pragma once

#include "Util.h"
#include "FileUtil.h"
#include <string>

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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			typedef void (*SingleFileReceiver)(const std::string &file);
			typedef void (*MultiFileReceiver)(std::string& files[]);

			class DragDropUtil
			{
			public:
				static void RegisterSingleFileDragDrop(Control *c, SingleFileReceiver r);

				static void RegisterSingleFileDragDrop(Control *c, SingleFileReceiver r, const std::string &filter);

				static void RegisterSingleFileDragDrop(Control *c, SingleFileReceiver r, Getter<std::string> filter);

				static void RegisterMultiFileDragDrop(Control *c, MultiFileReceiver r);

				static void RegisterMultiFileDragDrop(Control *c, MultiFileReceiver r, const std::string &filter);

				static void RegisterMultiFileDragDrop(Control *c, MultiFileReceiver r, Getter<std::string> filter);
			};
		}
	}
}
