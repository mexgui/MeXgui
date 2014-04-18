#pragma once

#include "Stream.h"
#include "AudioStreamType.h"
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
	/// <summary>A Stream of StreamType Audio</summary>
	class AudioStream : public Stream
	{
	private:
		AudioStreamType privateAudioType;
	public:
		const AudioStreamType &getAudioType() const;
		void setAudioType(const AudioStreamType &value);
	private:
		QString privateLanguage;
	public:
		const virtual QString &getLanguage() const;
		virtual void setLanguage(const QString &value);
	private:
		QString privateChannels;
	public:
		const QString &getChannels() const;
		void setChannels(const QString &value);
	private:
		QString privateBitrate;
	public:
		const QString &getBitrate() const;
		void setBitrate(const QString &value);
	private:
		QString privateDialogNormalization;
	public:
		const QString &getDialogNormalization() const;
		void setDialogNormalization(const QString &value);
	private:
		QString privateDelay;
	public:
		const QString &getDelay() const;
		void setDelay(const QString &value);

		const virtual object *getExtractTypes() const;

		AudioStream(const QString &s);

		static Stream *Parse(const QString &s);

		virtual QString ToString();
	};
}
