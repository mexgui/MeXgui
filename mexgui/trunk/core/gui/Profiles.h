#pragma once

// ****************************************************************************
// 
// Copyright (C) 2005-20012 Doom9 & al
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
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::gui;

namespace MeGUI
{
	namespace core
	{
		namespace plugins
		{
			namespace interfaces
			{
				class GenericSettings : public IEquatable<GenericSettings*>, ICloneable
				{
					/************************************************************************************
					 *                   Classes implementing GenericSettings must                      *
					 *                    ensure that object.Equals(object other)                       *
					 *                     is overridden and is correct for the                         *
					 *                                 given class.                                     *
					 ************************************************************************************/

					/// <summary>
					/// Deep-clones the settings
					/// </summary>
					/// <returns></returns>
				public:
					virtual GenericSettings *Clone() = 0;

					/// <summary>
					/// Returns the meta type of a profile. This is used as a lookup in the ProfileManager class
					/// to group like profile types. There should be one meta-type per settings type.
					/// </summary>
					/// <returns></returns>
					virtual const std::string &getSettingsID() const = 0;

					/// <summary>
					/// Substitutes any filenames stored in this profile (eg quantizer matrices) according to
					/// the substitution table
					/// </summary>
					/// <param name="substitutionTable"></param>
					virtual void FixFileNames(std::map<std::string, std::string>&) = 0;

					/// <summary>
					/// Lists all the files that these codec settings depend upon
					/// </summary>
					virtual const std::string &getRequiredFiles() const = 0;

					/// <summary>
					/// Lists all the profiles that these codec settings depend upon
					/// </summary>
					virtual const std::string &getRequiredProfiles() const = 0;

				};


//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[AttributeUsage(AttributeTargets::Property)]
				class PropertyEqualityIgnoreAttribute : public Attribute
				{
				public:
					PropertyEqualityIgnoreAttribute();
				};


				class PropertyEqualityTester
				{
					/// <summary>
					/// Returns whether all of the properties (excluding those with the PropertyEqualityIgnoreAttribute)
					/// of the two objects are equal
					/// </summary>
					/// <param name="a"></param>
					/// <param name="b"></param>
					/// <returns></returns>
				public:
					static bool AreEqual(object *a, object *b);

					/// <summary>
					/// Returns whether these two objects are equal. Returns object.Equals except for arrays,
					/// where it recursively does an elementwise comparison
					/// </summary>
					/// <param name="a"></param>
					/// <param name="b"></param>
					/// <returns></returns>
				private:
					static bool ArrayEqual(object *a, object *b);
				};
			}
		}
	}
}
