#pragma once

#include "core/details/mux/MuxJob.h"
#include "CommandlineJobProcessor.h"
#include "core/util/FileSize.h"
#include "core/details/Streams.h"
#include "core/details/mux/MuxSettings.h"
#include "core/util/Util.h"
#include <string>
#include <vector>

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
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{
	typedef void (*MuxerOutputCallback)(const std::string &line, int type);

	class CommandlineMuxer : public CommandlineJobProcessor<MuxJob*>
	{
	protected:
		virtual void setProjectedFileSize();

		virtual void checkJobIO();

	private:
		void ensureInputFilesExistIfNeeded(MuxSettings *settings);
	};
}
