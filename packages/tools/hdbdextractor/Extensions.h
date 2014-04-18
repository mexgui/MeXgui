#pragma once

#include <QString>
#include <QMap>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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

//using namespace System::Reflection;


namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace hdbdextractor
			{
				class StringValueAttribute : public System::Attribute
				{
							private:
								QString privateValue;
							public:
								const QString &getValue() const;
								void setValue(const QString &value);

					StringValueAttribute(const QString &value);
				};

				class Extensions
				{
				private:
					static QMap<Enum*, StringValueAttribute*> stringValues;

				public:
					static QString GetStringValue(Enum *value);

					/// <summary>Given a set of words separated by a space return a word which starts with an uppercase.</summary>
					/// <param name="value"></param>
					/// <returns></returns>
					static QString ToPascal(const QString &value);

					/// <summary>Given a set of words separated by a space or an underscore return a lower Camel cased word.</summary>
					/// <param name="value"></param>
					/// <returns></returns>
					static QString ToCamel(const QString &value);

					/// <summary>Given a word or a phrase make the first letter of the phrase and the first letter after a point Upper case and all the rest lower case.</summary>
					/// <param name="value"></param>
					/// <returns></returns>
					static QString Capitalize(const QString &value);

					/// <summary>Given a word or a phrase make the first letter of each word uppercase.</summary>
					/// <param name="value"></param>
					/// <returns></returns>
					static QString CapitalizeAll(const QString &value);
				};
			}
		}
	}
}
