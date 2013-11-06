#pragma once

#include <string>
#include <map>

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
	class IIDable
	{
	public:
		virtual const std::string &getID() const = 0;
	};

	template<typename T>
	class IDable : public IIDable
	{
	public:
		T Data;

		IDable(const std::string &id, T t)
		{
			this->id = id;
			this->Data = t;
		}

	private:
		std::string id;
		const std::string &getID() = IIDable::ID::get const
		{
			return id;
		}

	};

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
	template<typename TType> where TType : IIDable
	class GenericRegisterer
	{
	private:
		std::map<std::string, TType> registeredTypes;

		/// <summary>
		/// Gets the registered type under the given name
		/// </summary>
		/// <param name="id">the id of the type</param>
		/// <returns>The TType, if found, else throws a KeyNotFoundException</returns>
	public:
		TType operator [](const std::string &id)
		{
			return registeredTypes[id];
		}

		/// <summary>
		/// Registers the given type
		/// </summary>
		/// <param name="registerable">The type to register</param>
		/// <returns>true if successful or already registered; false otherwise</returns>
		virtual bool Register(TType registerable)
		{
			if (registeredTypes.find(registerable->ID) != registeredTypes.end())
			{
				if (registerable->Equals(registeredTypes[registerable->ID]))
				{
					return true;
				}
				return false;
			}
			registeredTypes.insert(make_pair(registerable->ID, registerable));
			return true;
		}

		/// <summary>
		/// Unregisters the type under the given name.
		/// </summary>
		/// <param name="name">name of thing to unregister</param>
		/// <returns></returns>
		virtual bool Unregister(const std::string &name)
		{
			if (registeredTypes.find(name) != registeredTypes.end())
				registeredTypes.erase(name);
			return true;
		}

		const ICollection<TType> &getValues() const
		{
			return registeredTypes.Values;
		}

		const TType *getValuesArray() const
		{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			lock (this)
			{
				TType array_Renamed[Values->Count];
				getValues()->CopyTo(array_Renamed, 0);
				return array_Renamed;
			}
		}

	private:
		void InitializeInstanceFields()
		{
			registeredTypes = std::map<std::string, TType>();
		}

public:
		GenericRegisterer()
		{
			InitializeInstanceFields();
		}
	};
}
