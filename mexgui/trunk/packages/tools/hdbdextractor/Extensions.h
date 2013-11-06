#pragma once

#include <string>
#include <map>

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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;


namespace MeGUI
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
								std::string privateValue;
							public:
								const std::string &getValue() const;
								void setValue(const std::string &value);

					StringValueAttribute(const std::string &value);
				};

				class Extensions
				{
				private:
					static std::map<Enum*, StringValueAttribute*> stringValues;

				public:
					static std::string GetStringValue(Enum *value);

					/// <summary>Given a set of words separated by a space return a word which starts with an uppercase.</summary>
					/// <param name="value"></param>
					/// <returns></returns>
					static std::string ToPascal(const std::string &value);

					/// <summary>Given a set of words separated by a space or an underscore return a lower Camel cased word.</summary>
					/// <param name="value"></param>
					/// <returns></returns>
					static std::string ToCamel(const std::string &value);

					/// <summary>Given a word or a phrase make the first letter of the phrase and the first letter after a point Upper case and all the rest lower case.</summary>
					/// <param name="value"></param>
					/// <returns></returns>
					static std::string Capitalize(const std::string &value);

					/// <summary>Given a word or a phrase make the first letter of each word uppercase.</summary>
					/// <param name="value"></param>
					/// <returns></returns>
					static std::string CapitalizeAll(const std::string &value);
				};
			}
		}
	}
}
