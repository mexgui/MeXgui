#include "Tuples.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

template<typename A, typename B, typename C, typename D, typename E, typename F>
			MeGUI::core::util::Tuple<A, B, C, D, E, F> *Tuple::Create(A a, B b, C c, D d, E e, F f)
			{
				return new Tuple<A, B, C, D, E, F>(a, b, c, d, e, f);
			}

template<typename A, typename B, typename C, typename D, typename E>
			MeGUI::core::util::Tuple<A, B, C, D, E> *Tuple::Create(A a, B b, C c, D d, E e)
			{
				return new Tuple<A, B, C, D, E>(a, b, c, d, e);
			}

template<typename A, typename B, typename C, typename D>
			MeGUI::core::util::Tuple<A, B, C, D> *Tuple::Create(A a, B b, C c, D d)
			{
				return new Tuple<A, B, C, D>(a, b, c, d);
			}

template<typename A, typename B, typename C>
			MeGUI::core::util::Tuple<A, B, C> *Tuple::Create(A a, B b, C c)
			{
				return new Tuple<A, B, C>(a, b, c);
			}

template<typename A, typename B>
			MeGUI::core::util::Tuple<A, B> *Tuple::Create(A a, B b)
			{
				return new Tuple<A, B>(a, b);
			}
		}
	}
}
