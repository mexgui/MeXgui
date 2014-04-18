#pragma once

#include <string>
#include <stdexcept>

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
//using namespace System::Text;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			// The base class for MeGUI-triggered exceptions
			class MeGUIException : public std::exception
			{
			public:
				MeGUIException(const std::string &message);

				MeGUIException(std::exception &inner);

				MeGUIException(const std::string &message, std::exception &inner);

			};

			class JobRunException : public MeGUIException
			{
			public:
				JobRunException(const std::string &message);

				JobRunException(std::exception &inner);

				JobRunException(const std::string &message, std::exception &inner);
			};

			class MissingFileException : public JobRunException
			{
			public:
				std::string filename;

				MissingFileException(const std::string &file);
			};

			class EncoderMissingException : public MissingFileException
			{
			public:
				EncoderMissingException(const std::string &file);
			};
		}
	}
}
