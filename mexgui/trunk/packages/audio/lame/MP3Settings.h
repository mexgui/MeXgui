#pragma once

#include "packages/audio/AudioCodecSettings.h"
#include "core/details/CodecManager.h"
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

namespace MeGUI
{
	/// <summary>
	/// Summary description for MP3Settings.
	/// </summary>
	class MP3Settings : public AudioCodecSettings
	{
	public:
		static const std::string ID;
		static const int SupportedBitrates[14] = {32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320};

	private:
		int quality;
		int abrBitrate;
	public:
		MP3Settings();
		/// <summary>
		/// gets / sets the quality for vbr mode
		/// </summary>
		const int &getQuality() const;
		void setQuality(const int &value);

		/// <summary>
		/// gets / sets the bitrate for abr mode
		/// </summary>
		const int &getAbrBitrate() const;
		void setAbrBitrate(const int &value);
	};
}
