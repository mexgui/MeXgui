#include "Util.h"

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

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename TException> where TException : Exception
			void Util::CatchAndTellUser(const std::string &processDescription, Action action)
			{
				try
				{
					action();
				}
				catch (TException *e)
				{
					MessageBox::Show(processDescription + ". Error message: " + e->Message, "Error occurred", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename TException> where TException : Exception
			void Util::CatchAndTellUser(Action action)
			{
				CatchAndTellUser<TException>("An error occurred", action);
			}

			void Util::CatchExceptionsAndTellUser(const std::string &processDescription, Action action)
			{
				CatchAndTellUser<std::exception>(processDescription, action);
			}

			void Util::CatchExceptionsAndTellUser(Action action)
			{
				CatchAndTellUser<std::exception>(action);
			}

			void Util::ThreadSafeRun(Control *c, MethodInvoker *m)
			{
				if (c != 0 && c->InvokeRequired)
					c->Invoke(m);
				else
					m();
			}

			void Util::XmlSerialize(object *o, const std::string &path)
			{
				FileUtil::ensureDirectoryExists(Path::GetDirectoryName(path));
				XmlSerializer *ser = new XmlSerializer(o->GetType());
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (Stream s = File.Open(path, System.IO.FileMode.Create, System.IO.FileAccess.Write))
				Stream *s = File->Open(path, System::IO::FileMode::Create, System::IO::FileAccess::Write);
				try
				{
					try
					{
						ser->Serialize(s, o);
					}
					catch (std::exception &e)
					{
						s->Close();
						try
						{
							File::Delete(path);
						}
						catch (IOException *e1)
						{
						}
						LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
						_oLog->LogValue("XmlSerialize: " + path, e, Error);
					}
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (s != 0)
						s.Dispose();
				}
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class, new()
			T Util::XmlDeserializeOrDefault(const std::string &path)
			{
				XmlSerializer *ser = new XmlSerializer(T::typeid);
				if (File::Exists(path))
				{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (Stream s = File.OpenRead(path))
					Stream *s = File::OpenRead(path);
					try
					{
						try
						{
							return static_cast<T>(ser->Deserialize(s));
						}
						catch (std::exception &e1)
						{
							s->Close();
							MessageBox::Show("File '" + path + "' could not be loaded!\n\nIt will be moved to the backup directory.", "Error loading File", MessageBoxButtons::OK, MessageBoxIcon::Error);
							FileUtil::BackupFile(path, true);
							return 0;
						}
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (s != 0)
							s.Dispose();
					}
				}
				else
					return new T();
			}

			object *Util::XmlDeserialize(const std::string &path, Type *t, bool bSilentError)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				MethodInfo *ms = (MethodInfo)Array->Find(Util::typeid::GetMember("XmlDeserialize"), delegate(MemberInfo m)
				{
					return (dynamic_cast<MethodInfo*>(m) != 0) && (dynamic_cast<MethodInfo*>(m))->IsGenericMethod;
				}
			   );
				ms = ms->MakeGenericMethod(t);
				return ms->Invoke(0, new object[] {path, bSilentError});
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class
			T Util::XmlDeserialize(const std::string &path, bool bSilentError)
			{
				XmlSerializer *ser = new XmlSerializer(T::typeid);
				if (File::Exists(path))
				{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (Stream s = File.OpenRead(path))
					Stream *s = File::OpenRead(path);
					try
					{
						try
						{
							return static_cast<T>(ser->Deserialize(s));
						}
						catch (std::exception &e)
						{
							s->Close();
							if (!bSilentError)
							{
								MessageBox::Show("File '" + path + "' could not be loaded!\n\nIt will be moved to the backup directory.", "Error loading File", MessageBoxButtons::OK, MessageBoxIcon::Error);
								FileUtil::BackupFile(path, true);
							}
							LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
							_oLog->LogValue("XmlDeserialize: " + path, e, Error);
							return 0;
						}
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (s != 0)
							s.Dispose();
					}
				}
				else
					return 0;
			}

System::Text::RegularExpressions::Regex *const Util::_cleanUpStringRegex = new System::Text::RegularExpressions::Regex("\\n[^\\n]+\\r", System::Text::RegularExpressions::RegexOptions::Compiled | System::Text::RegularExpressions::RegexOptions::CultureInvariant);

			std::string Util::cleanUpString(const std::string &s)
			{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				return _cleanUpStringRegex->Replace(s.Replace("\r\n", "\n"), "\r\n");
			}

			void Util::ensureExists(const std::string &file)
			{
				if (file == "" || !System::IO::File::Exists(file))
					throw new MissingFileException(file);
			}

			void Util::ensureExistsIfNeeded(const std::string &file)
			{
				if (!file.empty())
					ensureExists(file);
			}

			std::string Util::ToString(Nullable<TimeSpan*> t1)
			{
				if (!t1.HasValue)
					return 0;
				TimeSpan *t = t1.Value;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return (new TimeSpan(t->Hours, t->Minutes, t->Seconds))->ToString();
			}

			std::string Util::ToString(Nullable<decimal> d, bool bNoDecimalPlaces)
			{
				if (!d.HasValue)
					return 0;
				if (bNoDecimalPlaces)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return d.Value->ToString("0");
				else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return d.Value->ToString("0.00");
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class
			std::string Util::ToStringOrNull(T t)
			{
				if (t == 0)
					return 0;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return t->ToString();
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class
			std::string Util::ToStringOrNull(T?  *t)
			{
				if (t == 0)
					return 0;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return t->Value->ToString();
			}

			int Util::CountStrings(const std::string &src, wchar_t find)
			{
				int ret = 0;
				for (std::string::const_iterator s = src.begin(); s != src.end(); ++s)
				{
					if (*s == find)
					{
						++ret;
					}
				}
				return ret;
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : IIDable
			T Util::ByID(IEnumerable<T> *i, const std::string &id)
			{
				for (IEnumerable<T>::const_iterator t = i->begin(); t != i->end(); ++t)
					if ((*t)->ID == id)
						return t;

				return T();
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class
			std::vector<T> Util::Unique(std::vector<T> &l, Delegate<bool, T, T> cmp)
			{
				for (int i = 0; i < l.size(); ++i)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					if (l.FindIndex(0, i, delegate(T t) {return cmp(t, l[i]);}) >= 0)
					{
						l.RemoveAt(i);
						--i;
					}
				}
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return l.FindAll(delegate(T t)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					return l.FindIndex(delegate(T t2)
					{
						return cmp(t, t2);
					}
				   ) == l.find(t);
				}
			   );
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class
			std::vector<T> Util::Unique(std::vector<T> &l)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return Unique(l, delegate(T t1, T t2)
				{
					return t1->Equals(t2);
				}
			   );
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class, IIDable
			std::vector<T> Util::UniqueByIDs(std::vector<T> &l)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return Unique(l, delegate(T t1, T t2)
				{
					return t1->ID == t2::ID;
				}
			   );
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class, IIDable
			std::vector<T> Util::RemoveDuds(std::vector<T> &ps)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				ps = ps.FindAll(delegate(T p)
				{
					return p != 0;
				}
			   );

				// eliminate duplicate names
				return Util::UniqueByIDs(ps);
			}

template<typename To>
			IEnumerable<To> *Util::CastAll(IEnumerable *i)
			{
				for (IEnumerable::const_iterator t = i->begin(); t != i->end(); ++t)
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
					yield return t;
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename From, typename To> where To : class
			IEnumerable<To> *Util::CastAll(IEnumerable<From> *i)
			{
				for (IEnumerable<From>::const_iterator f = i->begin(); f != i->end(); ++f)
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
					yield return dynamic_cast<To*>(*f);
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename From, typename To> where To : class
			std::vector<To> Util::CastAll(std::vector<From> &i)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return i.ConvertAll<To>(delegate(From f)
				{
					return dynamic_cast<To*>(f);
				}
			   );
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename From, typename To> where To : class
			To *Util::CastAll(From fr[])
			{
				if (fr == 0)
					return 0;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return Array::ConvertAll<From, To>(fr, delegate(From f)
				{
					return dynamic_cast<To*>(f);
				}
			   );
			}

template<typename To>
			To *Util::CastAll(object os[])
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return Array::ConvertAll<object*, To>(os, delegate(object o)
				{
					return static_cast<To>(o);
				}
			   );
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T, typename TC> where TC : TypeConverter
			void Util::RegisterTypeConverter()
			{
				Attribute attr[1];
				TypeConverterAttribute *vConv = new TypeConverterAttribute(TC::typeid);
				attr[0] = vConv;
				TypeDescriptor::AddAttributes(T::typeid, attr);
			}

template<typename T>
			T *Util::ToArray(IEnumerable<T> *i)
			{
				return (std::vector<T>(i))->ToArray();
			}

			object *Util::ToArray(IEnumerable *i)
			{
				std::vector<object*> l = std::vector<object*>();
				for (IEnumerable::const_iterator o = i->begin(); o != i->end(); ++o)
					l.push_back(*o);
				return l.ToArray();
			}

template<typename T>
			IEnumerable<T> *Util::Append(...)
			{
				for (unknown::const_iterator list = lists.begin(); list != lists.end(); ++list)
					for (IEnumerable::const_iterator t = list->begin(); t != list->end(); ++t)
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						yield return t;
			}

template<typename TIn, typename TOut>
			IEnumerable<TOut> *Util::ConvertAll(IEnumerable<TIn> *input, Converter<TIn, TOut> c)
			{
				for (IEnumerable<TIn>::const_iterator t = input->begin(); t != input->end(); ++t)
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
					yield return c(*t);
			}

			void Util::clampedSet(NumericUpDown *box, decimal value)
			{
				box->Value = clamp(value, box->Minimum, box->Maximum);
			}

			decimal Util::clamp(decimal val, decimal min, decimal max)
			{
				assert(max >= min);
				if (val < min)
					return min;
				if (val > max)
					return max;
				return val;
			}

			int Util::clamp(int val, int min, int max)
			{
				return static_cast<int>(clamp(static_cast<decimal>(val), min, max));
			}

			unsigned int Util::clamp(unsigned int val, unsigned int min, unsigned int max)
			{
				return static_cast<unsigned int>(clamp(static_cast<decimal>(val), min, max));
			}

			unsigned long long Util::clamp(unsigned long long val, unsigned long long min, unsigned long long max)
			{
				return static_cast<unsigned long long>(clamp(static_cast<decimal>(val), min, max));
			}

			long long Util::clamp(long long val, long long min, long long max)
			{
				return static_cast<long long>(clamp(static_cast<decimal>(val), min, max));
			}

			unsigned long long Util::clamp(long long val, unsigned long long min, unsigned long long max)
			{
				return static_cast<unsigned long long>(clamp(static_cast<decimal>(val), min, max));
			}

			unsigned long long Util::clampPositive(long long val)
			{
				if (val < 0)
					return 0u;
				return static_cast<unsigned long long>(val);
			}

			unsigned int Util::clampPositive(int val)
			{
				return static_cast<unsigned int>(clampPositive(static_cast<long long>(val)));
			}

template<typename T>
			void Util::ChangeItemsKeepingSelectedSame(ComboBox *box, T newItems[])
			{
				T sel = static_cast<T>(box->SelectedItem);
				if (Array->find(newItems, sel) < 0 || sel == 0)
					sel = newItems[0];

				box->Items->Clear();
				box->Items->AddRange(Util::CastAll<T, object*>(newItems));
				box->SelectedItem = sel;
			}

			int Util::convertTimecodeToFrameNumber(int timeCode, double framerate)
			{
				double millisecondsPerFrame = static_cast<double>(1000 / framerate);
				double frameNumber = static_cast<double>(timeCode) / millisecondsPerFrame;
				return static_cast<int>(frameNumber);

			}

			std::string Util::converFrameNumberToTimecode(int frameNumber, double framerate)
			{
				double millisecondsPerFrame = static_cast<double>(1000 / framerate);
				int milliseconds = static_cast<int>(millisecondsPerFrame * static_cast<double>(frameNumber));
				int hours = milliseconds / (3600 * 1000);
				milliseconds -= hours * 3600 * 1000;
				int minutes = milliseconds / (60 * 1000);
				milliseconds -= minutes * 60 * 1000;
				int seconds = milliseconds / 1000;
				milliseconds -= seconds * 1000;
				std::string retval = "";
				if (hours < 10)
					retval += "0";
				retval += hours + ":";
				if (minutes < 10)
					retval += "0";
				retval += minutes + ":";
				if (seconds < 10)
					retval += "0";
				retval += seconds + ".";
				if (milliseconds < 100)
					retval += "0";
				if (milliseconds < 10)
					retval += "0";
				retval += milliseconds;
				return retval;
			}

			int Util::getTimeCode(const std::string &timecode)
			{
				if (timecode.Equals(""))
					return -1;
				else if (timecode.length() == 12) // must be 12 chars
				{
					wchar_t separator[1] = {':'};
//ORIGINAL LINE: string[] subItems = timecode.Split(separator);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					std::string *subItems = timecode.Split(separator);
					if (sizeof(subItems) / sizeof(subItems[0]) == 3)
					{
						int hours, minutes, seconds, milliseconds;
						try
						{
							hours = int::Parse(subItems[0]);
							minutes = int::Parse(subItems[1]);
							separator = new wchar_t[] {'.'};
//ORIGINAL LINE: string[] str = subItems[2].Split(separator);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
							std::string *str = subItems[2].Split(separator);
							if (sizeof(str) / sizeof(str[0]) == 2)
							{
								seconds = int::Parse(str[0]);
								milliseconds = int::Parse(str[1]);
							}
							else
								return -1;
							if (hours > 24 || minutes > 59 || seconds > 59)
								return -1;
							int retval = milliseconds + seconds * 1000 + minutes * 60 * 1000 + hours * 60 * 60 * 1000;
							return retval;
						}
						catch (std::exception &e) // integer parsing error
						{
							LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
							_oLog->LogValue("getTimeCode: " + timecode, e, Error);
							return -1;
						}
					}
					else
						return -1;
				}
				else // incorrect length
					return -1;
			}
		}
	}
}
