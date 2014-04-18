#pragma once

#include "Stream.h"
#include "VideoStreamType.h"
#include "StreamType.h"
#include <QString>

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
		QString privateResolution;
	public:
		const QString &getResolution() const;
		void setResolution(const QString &value);
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

		VideoStream(const QString &s);

		static Stream *Parse(const QString &s);

		virtual QString ToString();
	};
}
