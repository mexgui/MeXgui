#pragma once

#include "core/util/GenericRegisterer.h"
#include "core/gui/Profiles.h"
#include "MeGUI.Properties.Settings.h"
#include <string>

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
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{
	/// <summary>
	/// Superclass of an actual video or audio profile
	/// defines some basic properties
	/// </summary>
	class Profile : public IIDable
	{
	private:
		std::string name; // name of the profile
		/// <summary>
		///  default constructor, initializes the private variables
		/// </summary>
	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public Profile():this("default")
		Profile();

		Profile(const std::string &name);

		/// <summary>
		/// Local name of the profile. Within a given settings type, this
		/// is guaranteed to be unique, but not within the entire profile
		/// collection
		/// </summary>
		const std::string &getName() const;
		void setName(const std::string &value);

		/// <summary>
		/// Fully qualified name in format 'type: name'. For a given profile
		/// collection, this is guaranteed to be unique.
		/// </summary>
		const std::string &getFQName() const;

		virtual std::string ToString();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore]
		virtual const GenericSettings &getBaseSettings() const = 0;
		virtual void setBaseSettings(const GenericSettings&) = 0;

		virtual Profile *baseClone() = 0;

		const std::string &getID() const;
	};

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
	template<typename TSettings> where TSettings : GenericSettings
	class GenericProfile : public Profile
	{
	private:
		TSettings settings;

	public:
		GenericProfile() : Profile()
		{
		}
		GenericProfile(const std::string &name, TSettings settings) : Profile(name)
		{
			this->settings = settings;
		}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore]
		const virtual GenericSettings &getBaseSettings() const
		{
			return settings;
		}
		virtual void setBaseSettings(const GenericSettings &value)
		{
			assert(dynamic_cast<TSettings>(value) != 0);
			settings = static_cast<TSettings>(value);
		}

		const TSettings &getSettings() const
		{
			return settings;
		}
		void setSettings(const TSettings &value)
		{
			settings = value;
		}
		GenericProfile<TSettings> *clone()
		{
			return new GenericProfile<TSettings>(getName(), static_cast<TSettings>(settings->Clone()));
		}
		virtual Profile *baseClone()
		{
			return clone();
		}
	};
}
