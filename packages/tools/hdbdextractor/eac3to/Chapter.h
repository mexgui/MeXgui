#pragma once

#include <QString>

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




namespace eac3to
{
	/// <summary>A Chapter</summary>
	class Chapter
	{
	public:
		Chapter();

		/// <summary>Chapter Number</summary>
	private:
		int privateNumber;
	public:
		const int &getNumber() const;
		void setNumber(const int &value);
		/// <summary>Chapter TimeStamp</summary>
	private:
		DateTime privateTime;
	public:
		const DateTime &getTime() const;
		void setTime(const DateTime &value);
		/// <summary>Chapter Name</summary>
	private:
		QString privateName;
	public:
		const QString &getName() const;
		void setName(const QString &value);
	};
}
