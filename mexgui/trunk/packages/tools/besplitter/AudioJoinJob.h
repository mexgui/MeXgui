#pragma once

#include "core/plugins/interfaces/Job.h"
#include <string>

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

namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{
				class AudioJoinJob : public Job
				{
				private:
					TimeSpan *cliplength;

				public:
					const TimeSpan &getClipLength() const;
					void setClipLength(const TimeSpan &value);


				private:
//ORIGINAL LINE: private string[] inputFiles;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
					std::string *inputFiles;

				public:
					const std::string *getInputFiles() const;
					void setInputFiles(std::string value[]);

					std::string generateJoinCommandline(const std::string &tempFilename);

					AudioJoinJob();

					AudioJoinJob(std::string& inputFiles[], const std::string &output);

					const virtual std::string &getCodecString() const;

					const virtual std::string &getEncodingMode() const;

				};
			}
		}
	}
}
