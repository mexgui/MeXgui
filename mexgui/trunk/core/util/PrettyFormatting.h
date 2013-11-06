#pragma once

#include <string>
#include <cmath>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2012  Doom9 & al
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
//using namespace System::Text::RegularExpressions;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			class PrettyFormatting
			{
			public:
				static std::string ExtractWorkingName(const std::string &fileName, const std::string &strLeading, const std::string &strReplace, const std::string &strReplaceWith);

			private:
				static Regex *const delayRegex;

				/// <summary>
				/// Gets the delay from the filename, but warns the user if this delay is larger than
				/// 10 seconds.
				/// </summary>
				/// <param name="filename"></param>
				/// <returns>The delay, or null if no valid delay was found</returns>
			public:
				static Nullable<int> getDelayAndCheck(const std::string &filename);

				/// <summary>
				/// gets the delay from an audio filename
				/// </summary>
				/// <param name="fileName">file name to be analyzed</param>
				/// <returns>the delay in milliseconds</returns>
				static Nullable<int> getDelay(const std::string &fileName);

				/// <summary>
				/// replaces the delay in the audio filename with a new delay
				/// </summary>
				/// <param name="fileName"></param>
				/// <param name="p"></param>
				/// <returns></returns>
				static std::string ReplaceDelay(const std::string &fileName, int delay);

				/// <summary>
				/// replace the fps value by something more mkvmerge compliant
				/// </summary>
				/// <param name="fpsIn">the input fps</param>
				/// <returns>the output fps formated</returns>
				static std::string ReplaceFPSValue(const std::string &fpsIn);
			};
		}
	}
}
