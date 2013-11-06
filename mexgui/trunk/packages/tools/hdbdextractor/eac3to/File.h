#pragma once

#include <string>

// ****************************************************************************
// 
// Copyright (C) 2005-2008  Doom9 & al
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

namespace eac3to
{
	/// <summary>A File</summary>
	class File
	{
	private:
		int privateIndex;
	public:
		const int &getIndex() const;
		void setIndex(const int &value);
		const std::string &getName() const;
		const std::string &getExtension() const;
	private:
		std::string privateFullName;
	public:
		const std::string &getFullName() const;
		void setFullName(const std::string &value);

		File();

		File(const std::string &fileName, int index);

		virtual std::string ToString();
	};
}
