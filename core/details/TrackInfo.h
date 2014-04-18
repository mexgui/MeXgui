#pragma once

#include "CodecManager.h"
#include <QString>

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

//using namespace System::Text;

//using namespace System::Xml::Serialization;

namespace MeXgui
{
	enum TrackType
	{
		Audio,
		Subtitle,
		Unknown,
		Video
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlInclude(SubtitleTrackInfo::typeid), XmlInclude(AudioTrackInfo::typeid), XmlInclude(VideoTrackInfo::typeid)]
	class TrackInfo
	{
	private:
		QString _codec, _containerType, _language, _name, _sourceFileName;
		int _trackID, _mmgTrackID, _delay, _trackIndex;
		bool _bDefault, _bForced, _bMKVTrack;
		MeXgui::TrackType _trackType;

	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public TrackInfo() : this(nullptr, nullptr)
		TrackInfo();

		TrackInfo(const QString &language, const QString &name);

		/// <summary>
		/// The Track Type
		/// </summary>
		const MeXgui::TrackType &getTrackType() const;
		void setTrackType(const MeXgui::TrackType &value);

		/// <summary>
		/// The full language string
		/// </summary>
		const QString &getLanguage() const;
		void setLanguage(const QString &value);

		/// <summary>
		/// The full source file name incuding path
		/// </summary>
		const QString &getSourceFileName() const;
		void setSourceFileName(const QString &value);

		/// <summary>
		/// The track name
		/// </summary>
		const QString &getName() const;
		void setName(const QString &value);

		/// <summary>
		/// The track ID
		/// </summary>
		const int &getTrackID() const;
		void setTrackID(const int &value);

		/// <summary>
		/// The MMG track ID
		/// </summary>
		const int &getMMGTrackID() const;
		void setMMGTrackID(const int &value);

		/// <summary>
		/// The Container Type
		/// </summary>
		const QString &getContainerType() const;
		void setContainerType(const QString &value);

		/// <summary>
		/// The track index
		/// </summary>
		const int &getTrackIndex() const;
		void setTrackIndex(const int &value);

		/// <summary>
		/// The Codec String
		/// </summary>
		const QString &getCodec() const;
		void setCodec(const QString &value);

		/// <summary>
		/// The delay of the track
		/// </summary>
		const int &getDelay() const;
		void setDelay(const int &value);

		/// <summary>
		/// Default Track
		/// </summary>
		const bool &getDefaultTrack() const;
		void setDefaultTrack(const bool &value);

		/// <summary>
		/// Forced Track
		/// </summary>
		const bool &getForcedTrack() const;
		void setForcedTrack(const bool &value);

		bool IsMKVContainer();

		const bool &getExtractMKVTrack() const;
		void setExtractMKVTrack(const bool &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const QString &getDemuxFileName() const;
	};
}
