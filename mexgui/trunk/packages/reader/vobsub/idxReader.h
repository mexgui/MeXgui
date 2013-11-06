#pragma once

#include "core/util/VideoUtil.h"
#include <string>
#include <vector>
#include <stdexcept>
#include "stringconverter.h"

// ****************************************************************************
// 
// Copyright (C) 2005-2011  Doom9 & al
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
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::util;

namespace MeGUI
{
	/// <summary>
	/// Summary description for idxReader.
	/// </summary>
	class idxReader
	{
	private:
		std::string fileName;

		/// <summary>
		/// initializes the idx reader
		/// </summary>
		/// <param name="fileName">the idx file that this reader will process</param>
	public:
		idxReader(const std::string &fileName);

		/// <summary>
		/// reads the idx file, which is essentially a text file
		/// the first few lines contain the video properties in plain text and the 
		/// last line contains index, language and timestamp from subtitles
		/// this method reads indexes and languages and store it internally, then 
		/// closes the idx file again
		/// </summary>
		static void readFileProperties(const std::string &infoFile, std::vector<SubtitleInfo*> &subtitles);

		/// <summary>
		/// reads the idx file to retrieve the default Language Index Value
		/// </summary>
		static int defaultLangIdx(const std::string &idxFile);

	};
}
