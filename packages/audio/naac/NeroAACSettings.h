#pragma once

#include "packages/audio/AudioCodecSettings.h"
#include "core/details/CodecManager.h"
#include "core/plugins/interfaces/Profile.h"
#include <QString>

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




namespace MeXgui
{
	/// <summary>
	/// this class contains all the settings for the Nero AAC encoder
	/// </summary>
	enum AacProfile
	{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Automatic")]
		Auto,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("HE-AAC+PS")]
		PS,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("HE-AAC")]
		HE,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("AAC-LC")]
		LC,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("High")]
		HIGH
	};

	class NeroAACSettings : public AudioCodecSettings
	{
	public:
		static const QString ID;

		static const AacProfile SupportedProfiles[4];

		NeroAACSettings();

	private:
		AacProfile profile;
	public:
		const AacProfile &getProfile() const;
		void setProfile(const AacProfile &value);

	private:
		decimal quality;
	public:
		const Decimal &getQuality() const;
		void setQuality(const Decimal &value);

	private:
		bool createHintTrack;
	public:
		const bool &getCreateHintTrack() const;
		void setCreateHintTrack(const bool &value);


	};
}
