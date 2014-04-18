#pragma once

#include "FileUtil.h"
#include "LogItem.h"
#include "core/gui/MeGUI.MainForm.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <stdexcept>

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
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			template<typename R>
			typedef R *(*Delegate)();
			template<typename R, typename P1>
			typedef R *(*Delegate)(P1 *p1);
			template<typename R, typename P1, typename P2>
			typedef R *(*Delegate)(P1 *p1, P2 *p2);
			template<typename R, typename P1, typename P2, typename P3>
			typedef R *(*Delegate)(P1 *p1, P2 *p2, P3 *p3);
			template<typename R, typename P1, typename P2, typename P3, typename P4>
			typedef R *(*Delegate)(P1 *p1, P2 *P2, P3 *p3);

			template<typename T1, typename T2>
			class Pair
			{
			public:
				T1 fst;
				T2 snd;
				Pair(T1 f, T2 s)
				{
					fst = f;
					snd = s;
				}

				Pair()
				{
				}
			};

			template<typename T>
			typedef T *(*Getter)();
			template<typename T>
			typedef void (*Setter)(T *thing);

			typedef void (*Action)();

			class Util
			{
            public:
//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename TException> where TException : Exception
				static void CatchAndTellUser(const std::string &processDescription, Action action);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename TException> where TException : Exception
				static void CatchAndTellUser(Action action);

				static void CatchExceptionsAndTellUser(const std::string &processDescription, Action action);

				static void CatchExceptionsAndTellUser(Action action);

				static void ThreadSafeRun(Control *c, MethodInvoker *m);

				static void XmlSerialize(object *o, const std::string &path);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class, new()
				static T XmlDeserializeOrDefault(const std::string &path);

				static object *XmlDeserialize(const std::string &path, Type *t, bool bSilentError);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static T XmlDeserialize(const std::string &path, bool bSilentError);


			private:
				static System::Text::RegularExpressions::Regex *const _cleanUpStringRegex;
			public:
				static std::string cleanUpString(const std::string &s);

				static void ensureExists(const std::string &file);

				static void ensureExistsIfNeeded(const std::string &file);

				static std::string ToString(Nullable<TimeSpan*> t1);

				/// <summary>
				/// Formats the decimal according to what looks nice in MeGUI 
				/// (ensures consistency and not too many decimal places)
				/// </summary>
				/// <param name="d"></param>
				/// <returns></returns>
				static std::string ToString(Nullable<decimal> d, bool bNoDecimalPlaces);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static std::string ToStringOrNull(T t);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static std::string ToStringOrNull(T?  *t);
				static int CountStrings(const std::string &src, wchar_t find);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : IIDable
				static T ByID(IEnumerable<T> *i, const std::string &id);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static std::vector<T> Unique(std::vector<T> &l, Delegate<bool, T, T> cmp);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static std::vector<T> Unique(std::vector<T> &l);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class, IIDable
				static std::vector<T> UniqueByIDs(std::vector<T> &l);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class, IIDable
				static std::vector<T> RemoveDuds(std::vector<T> &ps);


				template<typename To>
				static IEnumerable<To> *CastAll(IEnumerable *i);


//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename From, typename To> where To : class
				static IEnumerable<To> *CastAll(IEnumerable<From> *i);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename From, typename To> where To : class
				static std::vector<To> CastAll(std::vector<From> &i);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename From, typename To> where To : class
				static To *CastAll(From fr[]);

				template<typename To>
				static To *CastAll(object os[]);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T, typename TC> where TC : TypeConverter
				static void RegisterTypeConverter();

				template<typename T>
				static T *ToArray(IEnumerable<T> *i);

				static object *ToArray(IEnumerable *i);

				template<typename T>
//ORIGINAL LINE: public static IEnumerable<T> Append<T>(params IEnumerable<T>[] lists)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
				static IEnumerable<T> *Append(...);

				template<typename TIn, typename TOut>
				static IEnumerable<TOut> *ConvertAll(IEnumerable<TIn> *input, Converter<TIn, TOut> c);

				static void clampedSet(NumericUpDown *box, decimal value);

				static decimal clamp(decimal val, decimal min, decimal max);

				static int clamp(int val, int min, int max);

				static unsigned int clamp(unsigned int val, unsigned int min, unsigned int max);

				static unsigned long long clamp(unsigned long long val, unsigned long long min, unsigned long long max);

				static long long clamp(long long val, long long min, long long max);

				static unsigned long long clamp(long long val, unsigned long long min, unsigned long long max);

				static unsigned long long clampPositive(long long val);
				static unsigned int clampPositive(int val);


				template<typename T>
				static void ChangeItemsKeepingSelectedSame(ComboBox *box, T newItems[]);

				/// <summary>
				/// convers a timecode to a framenumber
				/// </summary>
				/// <param name="timeCode">position in the movie in milliseconds</param>
				/// <param name="framerate">framerate of the movie</param>
				/// <returns>the frame corresponding to the timecode</returns>
				static int convertTimecodeToFrameNumber(int timeCode, double framerate);
				/// <summary>
				/// converts a framenumber into a chapter format compatible timecode given the framerate of the video
				/// </summary>
				/// <param name="frameNumber">the position of the video</param>
				/// <param name="framerate">the framerate of the video</param>
				/// <returns>the chapter compatible timecode</returns>
				static std::string converFrameNumberToTimecode(int frameNumber, double framerate);
				/// <summary>
				/// converts a string timecode into number of milliseconds
				/// </summary>
				/// <param name="timecode">the time string to be analyzed</param>
				/// <returns>the time in milliseconds from the string or -1 if there was an error parsing</returns>
				static int getTimeCode(const std::string &timecode);
			};

			template<typename TIn, typename TOut>
			typedef TOut *(*Converter)(TIn *iinput);
		}
	}
}
