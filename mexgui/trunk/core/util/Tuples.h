#pragma once

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
//using namespace System::Text;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			class Tuple
			{
            public:
				template<typename A, typename B, typename C, typename D, typename E, typename F>
				static Tuple<A, B, C, D, E, F> *Create(A a, B b, C c, D d, E e, F f);
				template<typename A, typename B, typename C, typename D, typename E>
				static Tuple<A, B, C, D, E> *Create(A a, B b, C c, D d, E e);
				template<typename A, typename B, typename C, typename D>
				static Tuple<A, B, C, D> *Create(A a, B b, C c, D d);
				template<typename A, typename B, typename C>
				static Tuple<A, B, C> *Create(A a, B b, C c);
				template<typename A, typename B>
				static Tuple<A, B> *Create(A a, B b);
			};

			template<typename A, typename B>
			class Tuple
			{
			public:
				A a;
				B b;

				Tuple(A a, B b)
				{
					this->a = a;
					this->b = b;
				}
				void get_Renamed(A &_a, B &_b)
				{
					_a = a;
					_b = b;
				}

			};

			template<typename A, typename B, typename C>
			class Tuple
			{
			public:
				A a;
				B b;
				C c;

				Tuple(A a, B b, C c)
				{
					this->a = a;
					this->b = b;
					this->c = c;
				}
				void get_Renamed(A &_a, B &_b, C &_c)
				{
					_a = a;
					_b = b;
					_c = c;
				}
			};
			template<typename A, typename B, typename C, typename D>
			class Tuple
			{
			public:
				A a;
				B b;
				C c;
				D d;

				Tuple(A a, B b, C c, D d)
				{
					this->a = a;
					this->b = b;
					this->c = c;
					this->d = d;
				}
				void get_Renamed(A &_a, B &_b, C &_c, D &_d)
				{
					_a = a;
					_b = b;
					_c = c;
					_d = d;
				}
			};

			template<typename A, typename B, typename C, typename D, typename E>
			class Tuple
			{
			public:
				A a;
				B b;
				C c;
				D d;
				E e;

				Tuple(A a, B b, C c, D d, E e)
				{
					this->a = a;
					this->b = b;
					this->c = c;
					this->d = d;
					this->e = e;
				}

				void get_Renamed(A &_a, B &_b, C &_c, D &_d, E &_e)
				{
					_a = a;
					_b = b;
					_c = c;
					_d = d;
					_e = e;
				}
			};
			template<typename A, typename B, typename C, typename D, typename E, typename F>
			class Tuple
			{
			public:
				A a;
				B b;
				C c;
				D d;
				E e;
				F f;


				Tuple(A a, B b, C c, D d, E e, F f)
				{
					this->a = a;
					this->b = b;
					this->c = c;
					this->d = d;
					this->e = e;
					this->f = f;
				}

				void get_Renamed(A &_a, B &_b, C &_c, D &_d, E &_e, F &_f)
				{
					_a = a;
					_b = b;
					_c = c;
					_d = d;
					_e = e;
					_f = f;
				}
			};
		}
	}
}
