#pragma once

#include <QString>
#include <QMap>

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

//using namespace System::Reflection;

//using namespace System::Text;

namespace MeXgui
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[AttributeUsage(AttributeTargets::Field)]
	class EnumTitleAttribute : public Attribute
	{
	private:
		QString text;
		object *tag;

	public:
		const QString &getText() const;
		const object &getTag() const;
		virtual QString ToString();
		EnumTitleAttribute(const QString &text, object *tag);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public EnumTitleAttribute(string text):this(text, nullptr)
		EnumTitleAttribute(const QString &text);


	};

	class EnumProxy
	{
	private:
		object *realValue;
		static const QMap<object*, EnumProxy*> cache;
		static object *const lockObject;
		EnumTitleAttribute *attribute;

	public:
		static EnumProxy *Create(object *v);

	private:
		EnumProxy(object *v);

	public:
		virtual QString ToString();

		const object &getRealValue() const;

		const object &getTag() const;


		static EnumProxy *CreateArray(System::Collections::IList *list);

		static EnumProxy *CreateArray(System::Type *enumType);

		static int IndexOf(System::Collections::IList *values, object *valueToFind);
	};
}
