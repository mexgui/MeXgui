#include "LogItem.h"




//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;

//using namespace System::Reflection;

//using namespace System::Text;



//using namespace System::Xml::Serialization;
namespace MeXgui
{
	namespace core
	{
		namespace util
		{

			void LogItem::Expand()
			{
				Expanded(this, new EventArgs());
			}

			void LogItem::Collapse()
			{
				Collapsed(this, new EventArgs());
			}

			const QString &LogItem::getText() const
			{
				return text;
			}

			const int &LogItem::getLevel() const
			{
				return iLevel;
			}

			void LogItem::setLevel(const int &value)
			{
				iLevel = value;
			}

			const MeXgui::core::util::ImageType &LogItem::getType() const
			{
				return type;
			}

			const QVector<LogItem*> &LogItem::getSubEvents() const
			{
				return subEvents;
			}

			LogItem::LogItem(const QString &name)
			{
				InitializeInstanceFields();
			}

			LogItem::LogItem(const QString &name, ImageType type)
			{
				InitializeInstanceFields();
				this->text = name;
				this->type = type;
				if (type == Warning)
					MainForm::Instance->setOverlayIcon(System::Drawing::SystemIcons::Warning);
				else if (type == Error)
					MainForm::Instance->setOverlayIcon(System::Drawing::SystemIcons::Error);
			}

			MeXgui::core::util::LogItem *LogItem::Add(LogItem *logItem)
			{
				logItem->setLevel(iLevel + 1);
				logItem->WriteLogEntry();
				subEvents.push_back(logItem);
				SubItemAdded(this, new EventArgs<LogItem*>(logItem));

				logItem->TypeChanged += new EventHandler<EventArgs<ImageType>*>(this, &LogItem::subItemTypeChanged);
				subItemTypeChanged(logItem, new EventArgs<ImageType>(logItem->getType()));

				return logItem;
			}

			MeXgui::core::util::LogItem *LogItem::LogValue(const QString &name, object *value)
			{
				return LogValue(name, value, Information);
			}

			MeXgui::core::util::LogItem *LogItem::LogValue(const QString &name, object *value, ImageType im)
			{
				return Add(AutomatedLogger::LogValue(QString::Format("[{0:G}] {1}", DateTime::Now, name), value, im));
			}

			MeXgui::core::util::LogItem *LogItem::LogEvent(const QString &eventName)
			{
				return LogEvent(eventName, Information);
			}

			MeXgui::core::util::LogItem *LogItem::LogEvent(const QString &eventName, ImageType image)
			{
				return Add(new LogItem(QString::Format("[{0:G}] {1}", DateTime::Now, eventName), image));
			}

			MeXgui::core::util::LogItem *LogItem::Info(const QString &text)
			{
				return Add(new LogItem(text, Information));
			}

			MeXgui::core::util::LogItem *LogItem::Warn(const QString &text)
			{
				return Add(new LogItem(text, Warning));
			}

			MeXgui::core::util::LogItem *LogItem::Error(const QString &text)
			{
				return Add(new LogItem(text, Error));
			}

			void LogItem::subItemTypeChanged(object *sender, EventArgs<ImageType> *typeInfo)
			{
				if (typeInfo->getData() < this->getType())
				{
					this->type = typeInfo->getData();
					TypeChanged(this, typeInfo);
				}
			}

			QString LogItem::ToString()
			{
				return ToString(0);
			}

			QString LogItem::ToString(bool includeSubnodes)
			{
				if (includeSubnodes)
					return ToString(0);
				else
					return QString::Format("[{0}] {1}", getType(), getText());
			}

			QString LogItem::ToString(int level)
			{
				StringBuilder *res = new StringBuilder();

				try
				{
					res->AppendFormat("{0}[{1}] {2}{3}", dashes(level), getType(), getText(), "\r\n");

					for (QVector<LogItem*>::const_iterator i = getSubEvents().begin(); i != getSubEvents().end(); ++i)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						res->Append((*i)->ToString(level + 1));
				}
				catch (std::exception &e)
				{
					MessageBox::Show(e.what());
				}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return res->ToString();
			}

			void LogItem::WriteLogEntry()
			{
				StringBuilder *res = new StringBuilder();

				try
				{
					MainForm::Instance->getLogLock()->WaitOne(10000, false);
					res->AppendFormat("{0}[{1}] {2}{3}", dashes(iLevel), getType(), getText(), "\r\n");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					System::IO::File::AppendAllText(MainForm::Instance->getLogFile(), res->ToString());
				}
				catch (std::exception &e)
				{
					MessageBox::Show(e.what(), "Error writing log file", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					MainForm::Instance->getLogLock()->Release();
				}
			}

			QString LogItem::dashes(int number)
			{
				wchar_t s[number];
				for (int i = 0; i < number; ++i)
					s[i] = '-';

				return QString(s);
			}

			void LogItem::InitializeInstanceFields()
			{
				iLevel = 0;
				subEvents = QVector<LogItem*>();
			}

			const MeXgui::core::util::TypeHandler &CustomLoggerAttribute::getCustomLogger() const
			{
				return customLogger;
			}

			CustomLoggerAttribute::CustomLoggerAttribute(TypeHandler logger)
			{
				this->customLogger = logger;
			}

QVector<Type*> AutomatedLogger::typesHandled = QVector<Type*>();
QMap<Type*, TypeHandler> AutomatedLogger::typeHandlers = QMap<Type*, TypeHandler>();

			void AutomatedLogger::Register(Type *ty, TypeHandler h)
			{
				assert(!typeHandlers.find(ty) != typeHandlers.end());
				typesHandled.push_back(ty);
				typeHandlers[ty] = h;
			}

			MeXgui::core::util::LogItem *AutomatedLogger::LogValue(const QString &name, object *value, ImageType image)
			{
				if (value == 0)
					value = "null"; // to avoid NullReferenceExceptions

				QVector<Type*> candidates = QVector<Type*>(typesHandled);

				// Remove the types which can't handle value
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				candidates.RemoveAll(delegate(Type t)
				{
					return !t::IsInstanceOfType(value);
				}
			   );

				// Ensure we used the most derived type
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				candidates.RemoveAll(delegate(Type t)
				{
					for (QVector<Type*>::const_iterator t2 = candidates.begin(); t2 != candidates.end(); ++t2)
					{
						if ((*t2)->IsSubclassOf(t))
							return true;
					}
					return false;
				}
			   );

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				QVector<TypeHandler> handlerCands = candidates.ConvertAll<TypeHandler>(delegate(Type t)
				{
					return typeHandlers[t];
				}
			   );

				Type *ty = value->GetType();

				if (ty->IsDefined(LogByMembersAttribute::typeid, true))
					handlerCands.push_back(LogByMembers);
				if (ty->IsDefined(CustomLoggerAttribute::typeid, true))
				{
//ORIGINAL LINE: CustomLoggerAttribute[] c = (CustomLoggerAttribute[])ty.GetCustomAttributes(typeof(CustomLoggerAttribute), true);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
					CustomLoggerAttribute *c = static_cast<CustomLoggerAttribute[]>(ty->GetCustomAttributes(CustomLoggerAttribute::typeid, true));
					assert(sizeof(c) / sizeof(c[0]) == 1);
					handlerCands.push_back(c[0]->getCustomLogger());
				}
				if (handlerCands.empty() || ty->IsDefined(LogAsToStringAttribute::typeid, true))
					handlerCands.push_back(LogAsToString);

				// We are guaranteed to have at least one logger: LogAsToString
				if (handlerCands.size() == 1)
					return handlerCands[0](name, value, image);
				else
				{
					LogItem *i = new LogItem(name, image);
					i->Warn(QString::Format("More than 1 loggers are defined for type '{0}'.", ty));
					for (QVector<TypeHandler>::const_iterator t = handlerCands.begin(); t != handlerCands.end(); ++t)
						i->Add(t("Value", value, NoImage));
					return i;
				}
			}

			MeXgui::core::util::LogItem *AutomatedLogger::LogAsToString(const QString &message, object *o, ImageType i)
			{
//ORIGINAL LINE: string[] lines = o.ToString().Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
				QString *lines = o->ToString()->Split(new wchar_t[] {'\r', '\n'}, StringSplitOptions::RemoveEmptyEntries);
				if (sizeof(lines) / sizeof(lines[0]) == 1)
					return new LogItem(message + ": " + lines[0], i);
				else
				{
//ORIGINAL LINE: LogItem[] events = Array.ConvertAll<string, LogItem>(lines, delegate(string s)
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					LogItem *events = Array::ConvertAll<QString, LogItem*>(lines, delegate(QString s)
					{
						return new LogItem(s, NoImage);
					}
				   );
					LogItem *r = new LogItem(message, i);
					for (MeXgui::core::util::LogItem::const_iterator e = events->begin(); e != events->end(); ++e)
						r->Add(*e);

					return r;
				}
			}

			MeXgui::core::util::LogItem *AutomatedLogger::LogByMembers(const QString &message, object *o, ImageType im)
			{
				LogItem *i = new LogItem(message, im);
				Type *ty = o->GetType();

				for (unknown::const_iterator p = ty->GetProperties().begin(); p != ty->GetProperties().end(); ++p)
				{
					if (!((*p)->CanRead && (*p)->GetGetMethod()->IsPublic) || (*p)->IsDefined(LogIgnoreAttribute::typeid, true))
						continue;

					i->LogValue((*p)->Name, (*p)->GetValue(o, 0));
				}

				for (unknown::const_iterator f = ty->GetFields().begin(); f != ty->GetFields().end(); ++f)
				{
					if ((!(*f)->IsPublic) || (*f)->IsDefined(LogIgnoreAttribute::typeid, true))
						continue;

					i->LogValue((*f)->Name, (*f)->GetValue(o));
				}

				return i;
			}

			AutomatedLogger::AutomatedLogger()
			{
				Register(std::exception::typeid, new TypeHandler(&ExceptionHandler));
				Register(Array::typeid, new TypeHandler(&ArrayHandler));
			}

			MeXgui::core::util::LogItem *AutomatedLogger::ExceptionHandler(const QString &message, object *o, ImageType i)
			{
				std::exception e = static_cast<std::exception>(o);

				LogItem *l = new LogItem(message, Error);
				l->LogValue("Exception message", e.what(), Error);
				l->LogValue("Stacktrace", e.StackTrace, Error);
				l->LogValue("Inner exception", e.InnerException, Error);

				for (unknown::const_iterator info = e.Data.begin(); info != e.Data.end(); ++info)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					l->LogValue((*info)->Key->ToString(), (*info)->Value, Error);

				return l;
			}

			MeXgui::core::util::LogItem *AutomatedLogger::ArrayHandler(const QString &message, object *o, ImageType im)
			{
				Array *a = static_cast<Array*>(o);
				int len = a->GetLength(0);

				LogItem *l = new LogItem(message, im);
				l->LogValue("array.Length", len);

				for (int i = 0; i < len; ++i)
					l->LogValue(QString::Format("array[{0}]", i), a->GetValue(i));

				return l;
			}
		}
	}
}
