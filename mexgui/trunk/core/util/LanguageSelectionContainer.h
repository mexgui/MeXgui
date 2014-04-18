#pragma once

#include <string>
#include <map>

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

namespace MeGUI
{
	/// <summary>
	/// A container for the selectable languages in MeGUI
	/// </summary>
	class LanguageSelectionContainer
	{
		// used by all tools except MP4box
	private:
		static const std::map<std::string, std::string> languagesBibliographic;
		static const std::map<std::string, std::string> languagesReverseBibliographic;

		// used by MP4box
		static const std::map<std::string, std::string> languagesTerminology;
		static const std::map<std::string, std::string> languagesReverseTerminology;

		/// <summary>
		/// uses the ISO 639-2/B language codes
		/// </summary>
	public:
		const static std::map<std::string, std::string> &getLanguages() const;

		/// <summary>
		/// uses the ISO 639-2/T language codes
		/// </summary>
		const static std::map<std::string, std::string> &getLanguagesTerminology() const;

	private:
		static void addLanguageB(const std::string &name, const std::string &iso);

		static void addLanguageT(const std::string &name, const std::string &iso);

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static LanguageSelectionContainer();

		LanguageSelectionContainer();

	public:
		static std::string lookupISOCode(const std::string &code);

		/// <summary>
		/// takes an ISO639.2 3 letter language code and returns
		/// a 2 letter ISO639.1 language code
		/// </summary>
		/// <param name="iso639dot2"></param>
		/// <returns></returns>
		static std::string getISO639dot1(const std::string &iso639dot2);

		///<summary>
		///Convert the 2 char strings to the full language name
		///</summary>
		///
		static std::string Short2FullLanguageName(const std::string &LngCode);
	};
}
