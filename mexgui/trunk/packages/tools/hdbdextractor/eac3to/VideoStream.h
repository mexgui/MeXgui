#pragma once

#include "Stream.h"
#include "VideoStreamType.h"
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
	/// <summary>A Stream of StreamType Video</summary>
	class VideoStream : public Stream
	{
	private:
		VStreamType privateVType;
	public:
		const VStreamType &getVType() const;
		void setVType(const VStreamType &value);
	private:
		std::string privateResolution;
	public:
		const std::string &getResolution() const;
		void setResolution(const std::string &value);
	private:
		bool privateIsProgerssive;
	public:
		const bool &getIsProgerssive() const;
		void setIsProgerssive(const bool &value);
	private:
		double privateFramerate;
	public:
		const double &getFramerate() const;
		void setFramerate(const double &value);
	private:
		double privateRatio;
	public:
		const double &getRatio() const;
		void setRatio(const double &value);

		const virtual object *getExtractTypes() const;

		VideoStream(const std::string &s);

		static Stream *Parse(const std::string &s);

		virtual std::string ToString();
	};
}
