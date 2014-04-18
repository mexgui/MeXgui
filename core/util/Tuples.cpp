#include "Tuples.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
namespace MeXgui
{
	namespace core
	{
		namespace util
		{

template<typename A, typename B, typename C, typename D, typename E, typename F>
			MeXgui::core::util::Tuple<A, B, C, D, E, F> *Tuple::Create(A a, B b, C c, D d, E e, F f)
			{
				return new Tuple<A, B, C, D, E, F>(a, b, c, d, e, f);
			}

template<typename A, typename B, typename C, typename D, typename E>
			MeXgui::core::util::Tuple<A, B, C, D, E> *Tuple::Create(A a, B b, C c, D d, E e)
			{
				return new Tuple<A, B, C, D, E>(a, b, c, d, e);
			}

template<typename A, typename B, typename C, typename D>
			MeXgui::core::util::Tuple<A, B, C, D> *Tuple::Create(A a, B b, C c, D d)
			{
				return new Tuple<A, B, C, D>(a, b, c, d);
			}

template<typename A, typename B, typename C>
			MeXgui::core::util::Tuple<A, B, C> *Tuple::Create(A a, B b, C c)
			{
				return new Tuple<A, B, C>(a, b, c);
			}

template<typename A, typename B>
			MeXgui::core::util::Tuple<A, B> *Tuple::Create(A a, B b)
			{
				return new Tuple<A, B>(a, b);
			}
		}
	}
}
