#pragma once

#include "StreamType.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "SubtitleStream.h"
#include "ChapterStream.h"
#include "JoinStream.h"
#include <string>

// ****************************************************************************
// 
// Copyright (C) 2005-2008  Doom9 & al
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
	/// <summary>A Stream</summary>
	class Stream
	{
	private:
		int privateNumber;
	public:
		const virtual int &getNumber() const;
		virtual void setNumber(const int &value);
	private:
		std::string privateName;
	public:
		const virtual std::string &getName() const;
		virtual void setName(const std::string &value);
	private:
		StreamType privateType;
	public:
		const virtual StreamType &getType() const;
		virtual void setType(const StreamType &value);
	private:
		std::string privateDescription;
	public:
		const virtual std::string &getDescription() const;
		virtual void setDescription(const std::string &value);
	private:
		std::string privateLanguage;
	public:
		const virtual std::string &getLanguage() const;
		virtual void setLanguage(const std::string &value);
		virtual const object &getExtractTypes() const = 0;

	protected:
		Stream();

		Stream(const std::string &s);

	public:
		static Stream *Parse(const std::string &s);

		virtual std::string ToString();
	};
}
