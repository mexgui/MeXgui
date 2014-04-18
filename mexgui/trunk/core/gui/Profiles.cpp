#include "Profiles.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::gui;
namespace MeGUI
{
	namespace core
	{
		namespace plugins
		{
			namespace interfaces
			{

				PropertyEqualityIgnoreAttribute::PropertyEqualityIgnoreAttribute()
				{
				}

				bool PropertyEqualityTester::AreEqual(object *a, object *b)
				{
					// If they are the same object or are both null
					if (a == b)
						return true;

					// If only one is null
					if (a == 0 || b == 0 || (a->GetType() != b->GetType()))
						return false;

					Type *t = a->GetType();
					for (unknown::const_iterator info = t->GetProperties().begin(); info != t->GetProperties().end(); ++info)
					{
						if ((*info)->IsDefined(PropertyEqualityIgnoreAttribute::typeid, true))
							continue;

						object *aVal = 0, *bVal = 0;
						try
						{
							aVal = (*info)->GetValue(a, 0);
						}
						catch (...)
						{
						}
						try
						{
							bVal = (*info)->GetValue(b, 0);
						}
						catch (...)
						{
						}
						if (!ArrayEqual(aVal, bVal))
							return false;
					}
					return true;
				}

				bool PropertyEqualityTester::ArrayEqual(object *a, object *b)
				{
					if (a == b)
						return true;

					if (a == 0 || b == 0 || (a->GetType() != b->GetType()))
						return false;

					if (!a->GetType()->IsArray)
						return a->Equals(b);

//ORIGINAL LINE: object[] arrayA = (object[])a;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
					object *arrayA = static_cast<object[]>(a);
//ORIGINAL LINE: object[] arrayB = (object[])b;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
					object *arrayB = static_cast<object[]>(b);

					if (sizeof(arrayA) / sizeof(arrayA[0]) != sizeof(arrayB) / sizeof(arrayB[0]))
						return false;

					for (int i = 0; i < sizeof(arrayA) / sizeof(arrayA[0]); i++)
					{
						if (!ArrayEqual(arrayA[i], arrayB[i]))
							return false;
					}
					return true;
				}
			}
		}
	}
}
