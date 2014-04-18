#pragma once

#include "Stream.h"
#include "AudioStreamType.h"
#include "StreamType.h"
#include <string>

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

namespace eac3to
{
	/// <summary>A Stream of StreamType Audio</summary>
	class AudioStream : public Stream
	{
	private:
		AudioStreamType privateAudioType;
	public:
		const AudioStreamType &getAudioType() const;
		void setAudioType(const AudioStreamType &value);
	private:
		std::string privateLanguage;
	public:
		const virtual std::string &getLanguage() const;
		virtual void setLanguage(const std::string &value);
	private:
		std::string privateChannels;
	public:
		const std::string &getChannels() const;
		void setChannels(const std::string &value);
	private:
		std::string privateBitrate;
	public:
		const std::string &getBitrate() const;
		void setBitrate(const std::string &value);
	private:
		std::string privateDialogNormalization;
	public:
		const std::string &getDialogNormalization() const;
		void setDialogNormalization(const std::string &value);
	private:
		std::string privateDelay;
	public:
		const std::string &getDelay() const;
		void setDelay(const std::string &value);

		const virtual object *getExtractTypes() const;

		AudioStream(const std::string &s);

		static Stream *Parse(const std::string &s);

		virtual std::string ToString();
	};
}
