#pragma once

#include <QString>
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




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{
	namespace core
	{
		namespace util
		{
			// The base class for MeXgui-triggered exceptions
			class MeXguiException : public std::exception
			{
			public:
				MeXguiException(const QString &message);

				MeXguiException(std::exception &inner);

				MeXguiException(const QString &message, std::exception &inner);

			};

			class JobRunException : public MeXguiException
			{
			public:
				JobRunException(const QString &message);

				JobRunException(std::exception &inner);

				JobRunException(const QString &message, std::exception &inner);
			};

			class MissingFileException : public JobRunException
			{
			public:
				QString filename;

				MissingFileException(const QString &file);
			};

			class EncoderMissingException : public MissingFileException
			{
			public:
				EncoderMissingException(const QString &file);
			};
		}
	}
}
