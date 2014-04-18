#include "EnumProxy.h"




//using namespace System::Collections::Generic;

//using namespace System::Reflection;

//using namespace System::Text;

namespace MeXgui
{

	const QString &EnumTitleAttribute::getText() const
	{
		return this->text;
	}

	const object &EnumTitleAttribute::getTag() const
	{
		return this->tag;
	}

	QString EnumTitleAttribute::ToString()
	{
		return getText();
	}

	EnumTitleAttribute::EnumTitleAttribute(const QString &text, object *tag)
	{
		this->text = text;
		this->tag = tag;
	}

	EnumTitleAttribute::EnumTitleAttribute(const QString &text)
	{
	}

QMap<object*, EnumProxy*> EnumProxy::cache = QMap<object*const , EnumProxy*>();
object *const EnumProxy::lockObject = new object();

	EnumProxy *EnumProxy::Create(object *v)
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock (lockObject)
		{
			if (cache.find(v) != cache.end())
				return cache[v];
			else
			{
				EnumProxy *p = new EnumProxy(v);
				cache.insert(make_pair(v, p));
				return p;
			}
		}
	}

	EnumProxy::EnumProxy(object *v)
	{
		this->realValue = v;
		System::Type *t = v->GetType();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		FieldInfo *fi = t->GetField(v->ToString());
//ORIGINAL LINE: object[] attr = fi.GetCustomAttributes(typeof(EnumTitleAttribute), false);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		object *attr = fi->GetCustomAttributes(EnumTitleAttribute::typeid, false);
		if (0 == attr || sizeof(attr) / sizeof(attr[0]) == 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			this->attribute = new EnumTitleAttribute(v->ToString());
		else
			this->attribute = dynamic_cast<EnumTitleAttribute*>(attr[0]);
	}

	QString EnumProxy::ToString()
	{
		return this->attribute->getText();
	}

	const object &EnumProxy::getRealValue() const
	{
		return this->realValue;
	}

	const object &EnumProxy::getTag() const
	{
		return this->attribute->getTag();
	}

	EnumProxy *EnumProxy::CreateArray(System::Collections::IList *list)
	{
		EnumProxy arr[list->Count];
		for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		{
			arr[i] = Create(list[i]);
		}
		return arr;
	}

	EnumProxy *EnumProxy::CreateArray(System::Type *enumType)
	{
		if (enumType == 0)
			throw new ArgumentNullException("enumType");
		if (!enumType->IsEnum)
			throw new ArgumentException("enumType must be Enum", "enumType");
//ORIGINAL LINE: FieldInfo[] enumItems = enumType.GetFields(BindingFlags.Public | BindingFlags.Static);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		FieldInfo *enumItems = enumType->GetFields(BindingFlags::Public | BindingFlags::Static);
		EnumProxy arr[sizeof(enumItems) / sizeof(enumItems[0])];
		for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		{
			arr[i] = Create(enumItems[i]->GetValue(0));
		}
		return arr;
	}

	int EnumProxy::IndexOf(System::Collections::IList *values, object *valueToFind)
	{
		for (int i = 0; i < values->Count; i++)
		{
			if (static_cast<int>(valueToFind) == static_cast<int>((dynamic_cast<EnumProxy*>(values[i]))->getRealValue()))
				return i;
		}
		return -1;
	}
}
