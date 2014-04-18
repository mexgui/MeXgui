#pragma once

#include <QString>
#include <QMap>
#include <iostream>
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




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{
	class IIDable
	{
	public:
		virtual const QString &getID() const = 0;
	};

	template<typename T>
	class IDable : public IIDable
	{
	public:
		T Data;

		IDable(const QString &id, T t)
		{
			this->id = id;
			this->Data = t;
		}

	private:
		QString id;
        const QString &getID() //Orginal &getID() = IIDable::ID::getID() here may be a bug
		{
            id = IIDable::getID(); //Added this and if it works it is fix.
			return id;
		}

	};

    //Orginal C# was this:
    //template<typename TType> where TType : IIdable
    //Removed where statement as it should not make any different for handling the IIDable code.
    template<typename TType> class GenericRegisterer
    {
	private:
		QMap<QString, TType> registeredTypes;

		/// <summary>
		/// Gets the registered type under the given name
		/// </summary>
		/// <param name="id">the id of the type</param>
		/// <returns>The TType, if found, else throws a KeyNotFoundException</returns>
	public:
		TType operator [](const QString &id)
		{
			return registeredTypes[id];
		}

		/// <summary>
		/// Registers the given type
		/// </summary>
		/// <param name="registerable">The type to register</param>
		/// <returns>true if successful or already registered; false otherwise</returns>
        bool Register(TType registerable)
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
        bool Unregister(const QString &name)
		{
			if (registeredTypes.find(name) != registeredTypes.end())
				registeredTypes.erase(name);
			return true;
		}
        template<typename TType> const GenericRegisterer<TType>::getValues() //const ICollection<TType> getValues()
        {
			return registeredTypes.Values;
        }

        const TType *getValuesArray()
		{
        //There is no built-in support for multithreading in native C++:
            //lock (this)
            //{
				TType array_Renamed[Values->Count];
				getValues()->CopyTo(array_Renamed, 0);
				return array_Renamed;
            //}
		}

	private:
		void InitializeInstanceFields()
		{
			registeredTypes = QMap<QString, TType>();
		}

public:
		GenericRegisterer()
		{
			InitializeInstanceFields();
		}
	};
}
