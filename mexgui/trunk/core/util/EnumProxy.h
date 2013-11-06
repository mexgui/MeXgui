#pragma once

#include <string>
#include <map>

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
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[AttributeUsage(AttributeTargets::Field)]
	class EnumTitleAttribute : public Attribute
	{
	private:
		std::string text;
		object *tag;

	public:
		const std::string &getText() const;
		const object &getTag() const;
		virtual std::string ToString();
		EnumTitleAttribute(const std::string &text, object *tag);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public EnumTitleAttribute(string text):this(text, nullptr)
		EnumTitleAttribute(const std::string &text);


	};

	class EnumProxy
	{
	private:
		object *realValue;
		static const std::map<object*, EnumProxy*> cache;
		static object *const lockObject;
		EnumTitleAttribute *attribute;

	public:
		static EnumProxy *Create(object *v);

	private:
		EnumProxy(object *v);

	public:
		virtual std::string ToString();

		const object &getRealValue() const;

		const object &getTag() const;


		static EnumProxy *CreateArray(System::Collections::IList *list);

		static EnumProxy *CreateArray(System::Type *enumType);

		static int IndexOf(System::Collections::IList *values, object *valueToFind);
	};
}
