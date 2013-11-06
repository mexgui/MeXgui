#pragma once

#include "core/gui/MeGUI.MainForm.h"
#include <string>
#include <map>
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
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
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
			enum ImageType
			{
				Error = 0,
				Warning = 1,
				Information = 2,
				NoImage = 3
			};

			template<typename TData>
			class EventArgs : public EventArgs
			{
			public:
				 const TData &getData() const
				 {
					 return data;
				 }

			private:
				TData data;

			public:
				EventArgs(TData t)
				{
					data = t;
				}
			};

			class LogItem
			{
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler<EventArgs<LogItem>> SubItemAdded;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler<EventArgs<ImageType>> TypeChanged;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler Expanded;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler Collapsed;

			public:
				void Expand();

				void Collapse();

				const std::string &getText() const;

			private:
				int iLevel;
			public:
				const int &getLevel() const;
				void setLevel(const int &value);

				const ImageType &getType() const;

				const std::vector<LogItem*> &getSubEvents() const;

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public LogItem(string name) : this(name, ImageType.Information)
				LogItem(const std::string &name);

				LogItem(const std::string &name, ImageType type);

				LogItem *Add(LogItem *logItem);


				LogItem *LogValue(const std::string &name, object *value);

				LogItem *LogValue(const std::string &name, object *value, ImageType im);

				LogItem *LogEvent(const std::string &eventName);

				LogItem *LogEvent(const std::string &eventName, ImageType image);

				LogItem *Info(const std::string &text);

				LogItem *Warn(const std::string &text);

				LogItem *Error(const std::string &text);

			private:
				ImageType type;
				std::string text;

				std::vector<LogItem*> subEvents;

				void subItemTypeChanged(object *sender, EventArgs<ImageType> *typeInfo);

			public:
				virtual std::string ToString();

				std::string ToString(bool includeSubnodes);

			private:
				std::string ToString(int level);

				void WriteLogEntry();

				static std::string dashes(int number);


			private:
				void InitializeInstanceFields();
			};

			typedef LogItem *(*TypeHandler)(const std::string &message, object *o, ImageType i);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[AttributeUsage(AttributeTargets::Class | AttributeTargets::Struct)]
			class LogByMembersAttribute : public Attribute
			{
			};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[AttributeUsage(AttributeTargets::Class | AttributeTargets::Struct)]
			class LogAsToStringAttribute : public Attribute
			{
			};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[AttributeUsage(AttributeTargets::Class | AttributeTargets::Struct)]
			class CustomLoggerAttribute : public Attribute
			{
			public:
				const TypeHandler &getCustomLogger() const;

			private:
				TypeHandler customLogger;

			public:
				CustomLoggerAttribute(TypeHandler logger);
			};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[AttributeUsage(AttributeTargets::Field | AttributeTargets::Property)]
			class LogIgnoreAttribute : public Attribute
			{
			};

			class AutomatedLogger
			{
			private:
				static std::vector<Type*> typesHandled;
				static std::map<Type*, TypeHandler> typeHandlers;

			public:
				static void Register(Type *ty, TypeHandler h);

				static LogItem *LogValue(const std::string &name, object *value, ImageType image);

				static LogItem *LogAsToString(const std::string &message, object *o, ImageType i);

				static LogItem *LogByMembers(const std::string &message, object *o, ImageType im);

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
				static AutomatedLogger();

			private:
				static LogItem *ExceptionHandler(const std::string &message, object *o, ImageType i);

				static LogItem *ArrayHandler(const std::string &message, object *o, ImageType im);
			};
		}
	}
}
