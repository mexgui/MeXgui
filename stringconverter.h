#pragma once

// ****************************************************************************
//
// Copyright (C) 2014-> Jeroi @ http://forum.doom9.org/
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

#include <QTextStream>

//This class is helper to convert different datatypes to string

class StringConverterHelper
{
private:
    StringConverterHelper();
public:

	template<typename T>
	static QString toString(const T &subject)
	{
        QTextStream ss;
        ss << subject;
        QString sss = ss.readAll();
        return sss;
	}

	template<typename T>
	static T fromString(const QString &subject)
	{
        std::stringstream ss(subject);
        T target;
        ss >> target;
		return target;
	}
};
