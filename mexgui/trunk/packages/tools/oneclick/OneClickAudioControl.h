#pragma once

#include "core/gui/Profiles.h"
#include "OneClickSettings.h"
#include "core/plugins/interfaces/Profile.h"
#include <string>
#include <map>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
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
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::gui;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;

namespace MeGUI
{

	class OneClickAudioSettings : public GenericSettings
	{
	public:
		OneClickAudioSettings();

		OneClickAudioSettings(const std::string &language, const std::string &profile, MeGUI::AudioEncodingMode mode, bool useFirstTrackOnly);


	private:
		object *ICloneable_Clone();

		GenericSettings *GenericSettings_Clone();

	public:
		OneClickSettings *Clone();

		const std::string *getRequiredFiles() const;

		const std::string *getRequiredProfiles() const;

		virtual bool Equals(object *obj);

		bool Equals(GenericSettings *other);

		const std::string &getSettingsID() const;
		virtual void FixFileNames(std::map<std::string, std::string> &_);

		virtual int GetHashCode();


	private:
		MeGUI::AudioEncodingMode audioEncodingMode;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[System::Xml::Serialization::XmlIgnore()]
		const MeGUI::AudioEncodingMode &getAudioEncodingMode() const;
		void setAudioEncodingMode(const MeGUI::AudioEncodingMode &value);

		// for profile import/export in case the enum changes
		const std::string &getAudioEncodingModeString() const;
		void setAudioEncodingModeString(const std::string &value);

	private:
		std::string language;
	public:
		const std::string &getLanguage() const;
		void setLanguage(const std::string &value);

	private:
		std::string profile;
	public:
		const std::string &getProfile() const;
		void setProfile(const std::string &value);

	private:
		bool useFirstTrackOnly;
	public:
		const bool &getUseFirstTrackOnly() const;
		void setUseFirstTrackOnly(const bool &value);
	};
}
