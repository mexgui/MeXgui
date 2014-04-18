#pragma once

#include "core/gui/Profiles.h"
#include "OneClickSettings.h"
#include "core/plugins/interfaces/Profile.h"
#include <QString>
#include <QMap>

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




//using namespace System::Collections::Generic;





using namespace MeXgui::core::gui;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;

namespace MeXgui
{

	class OneClickAudioSettings : public GenericSettings
	{
	public:
		OneClickAudioSettings();

		OneClickAudioSettings(const QString &language, const QString &profile, MeXgui::AudioEncodingMode mode, bool useFirstTrackOnly);


	private:
		object *ICloneable_Clone();

		GenericSettings *GenericSettings_Clone();

	public:
		OneClickSettings *Clone();

		const QString *getRequiredFiles() const;

		const QString *getRequiredProfiles() const;

		virtual bool Equals(object *obj);

		bool Equals(GenericSettings *other);

		const QString &getSettingsID() const;
		virtual void FixFileNames(QMap<QString, QString> &_);

		virtual int GetHashCode();


	private:
		MeXgui::AudioEncodingMode audioEncodingMode;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[System::Xml::Serialization::XmlIgnore()]
		const MeXgui::AudioEncodingMode &getAudioEncodingMode() const;
		void setAudioEncodingMode(const MeXgui::AudioEncodingMode &value);

		// for profile import/export in case the enum changes
		const QString &getAudioEncodingModeString() const;
		void setAudioEncodingModeString(const QString &value);

	private:
		QString language;
	public:
		const QString &getLanguage() const;
		void setLanguage(const QString &value);

	private:
		QString profile;
	public:
		const QString &getProfile() const;
		void setProfile(const QString &value);

	private:
		bool useFirstTrackOnly;
	public:
		const bool &getUseFirstTrackOnly() const;
		void setUseFirstTrackOnly(const bool &value);
	};
}
