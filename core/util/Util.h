#pragma once

#include "FileUtil.h"
#include "LogItem.h"
#include "core/gui/MainForm.h"
#include "Exceptions.h"
#include <QString>
#include <QVector>
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






//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;



//using namespace System::Globalization;



//using namespace System::Reflection;

//using namespace System::Text;



//using namespace System::Xml::Serialization;

namespace MeXgui
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
				static void CatchAndTellUser(const QString &processDescription, Action action);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename TException> where TException : Exception
				static void CatchAndTellUser(Action action);

				static void CatchExceptionsAndTellUser(const QString &processDescription, Action action);

				static void CatchExceptionsAndTellUser(Action action);

				static void ThreadSafeRun(Control *c, MethodInvoker *m);

				static void XmlSerialize(object *o, const QString &path);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class, new()
				static T XmlDeserializeOrDefault(const QString &path);

				static object *XmlDeserialize(const QString &path, Type *t, bool bSilentError);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static T XmlDeserialize(const QString &path, bool bSilentError);


			private:
				static System::Text::RegularExpressions::Regex *const _cleanUpStringRegex;
			public:
				static QString cleanUpString(const QString &s);

				static void ensureExists(const QString &file);

				static void ensureExistsIfNeeded(const QString &file);

				static QString ToString(Nullable<TimeSpan*> t1);

				/// <summary>
				/// Formats the decimal according to what looks nice in MeXgui 
				/// (ensures consistency and not too many decimal places)
				/// </summary>
				/// <param name="d"></param>
				/// <returns></returns>
				static QString ToString(Nullable<decimal> d, bool bNoDecimalPlaces);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static QString ToStringOrNull(T t);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static QString ToStringOrNull(T?  *t);
				static int CountStrings(const QString &src, wchar_t find);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : IIDable
				static T ByID(IEnumerable<T> *i, const QString &id);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static QVector<T> Unique(QVector<T> &l, Delegate<bool, T, T> cmp);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class
				static QVector<T> Unique(QVector<T> &l);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class, IIDable
				static QVector<T> UniqueByIDs(QVector<T> &l);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename T> where T : class, IIDable
				static QVector<T> RemoveDuds(QVector<T> &ps);


				template<typename To>
				static IEnumerable<To> *CastAll(IEnumerable *i);


//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename From, typename To> where To : class
				static IEnumerable<To> *CastAll(IEnumerable<From> *i);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename From, typename To> where To : class
				static QVector<To> CastAll(QVector<From> &i);

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

				static quint64 clamp(quint64 val, quint64 min, quint64 max);

				static qint64 clamp(qint64 val, qint64 min, qint64 max);

				static quint64 clamp(qint64 val, quint64 min, quint64 max);

				static quint64 clampPositive(qint64 val);
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
				static QString converFrameNumberToTimecode(int frameNumber, double framerate);
				/// <summary>
				/// converts a string timecode into number of milliseconds
				/// </summary>
				/// <param name="timecode">the time string to be analyzed</param>
				/// <returns>the time in milliseconds from the string or -1 if there was an error parsing</returns>
				static int getTimeCode(const QString &timecode);
			};

			template<typename TIn, typename TOut>
			typedef TOut *(*Converter)(TIn *iinput);
		}
	}
}
