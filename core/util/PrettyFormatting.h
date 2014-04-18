#pragma once

#include <QString>
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




//using namespace System::Collections::Generic;



//using namespace System::Text;

//using namespace System::Text::RegularExpressions;



namespace MeXgui
{
	namespace core
	{
		namespace util
		{
			class PrettyFormatting
			{
			public:
				static QString ExtractWorkingName(const QString &fileName, const QString &strLeading, const QString &strReplace, const QString &strReplaceWith);

			private:
				static Regex *const delayRegex;

				/// <summary>
				/// Gets the delay from the filename, but warns the user if this delay is larger than
				/// 10 seconds.
				/// </summary>
				/// <param name="filename"></param>
				/// <returns>The delay, or null if no valid delay was found</returns>
			public:
				static Nullable<int> getDelayAndCheck(const QString &filename);

				/// <summary>
				/// gets the delay from an audio filename
				/// </summary>
				/// <param name="fileName">file name to be analyzed</param>
				/// <returns>the delay in milliseconds</returns>
				static Nullable<int> getDelay(const QString &fileName);

				/// <summary>
				/// replaces the delay in the audio filename with a new delay
				/// </summary>
				/// <param name="fileName"></param>
				/// <param name="p"></param>
				/// <returns></returns>
				static QString ReplaceDelay(const QString &fileName, int delay);

				/// <summary>
				/// replace the fps value by something more mkvmerge compliant
				/// </summary>
				/// <param name="fpsIn">the input fps</param>
				/// <returns>the output fps formated</returns>
				static QString ReplaceFPSValue(const QString &fpsIn);
			};
		}
	}
}
