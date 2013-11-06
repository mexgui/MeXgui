#pragma once

#include "core/plugins/interfaces/Job.h"
#include "MuxSettings.h"
#include "MuxProvider.h"
#include "core/details/CodecManager.h"
#include "core/gui/MeGUI.MainForm.h"
#include "MeGUI.Properties.Settings.h"
#include <string>
#include <vector>

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
//using namespace System::Collections;

namespace MeGUI
{
	/// <summary>
	/// Summary description for MuxJob.
	/// </summary>
	class MuxJob : public Job
	{
	private:
		std::string codec;
		int nbOfBframes, bitrate;
		unsigned long long nbOfFrames;
		double overhead;
		MuxSettings *settings;
		MuxerType type;
		MeGUI::ContainerType *containerType;

	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[System::Xml::Serialization::XmlIgnore()]
		const MeGUI::ContainerType &getContainerType() const;
		void setContainerType(const MeGUI::ContainerType &value);

		const std::string &getContainerTypeString() const;
		void setContainerTypeString(const std::string &value);

		const virtual std::string &getCodecString() const;

		const virtual std::string &getEncodingMode() const;

		MuxJob();

		/// <summary>
		/// codec used for video, used for informational purposes (put in the log)
		/// </summary>
		const std::string &getCodec() const;
		void setCodec(const std::string &value);

		/// <summary>
		/// number of b-frames in the video input, used for informational purposes
		/// </summary>
		const int &getNbOfBFrames() const;
		void setNbOfBFrames(const int &value);

		/// <summary>
		/// the number of frames the video has
		/// </summary>
		const unsigned long long &getNbOfFrames() const;
		void setNbOfFrames(const unsigned long long &value);

		/// <summary>
		/// chosen video bitrate for the output, used for informational purposes
		/// </summary>
		const int &getBitrate() const;
		void setBitrate(const int &value);

		/// <summary>
		/// projected mp4 muxing overhead for this job in bytes / frame
		/// </summary>
		const double &getOverhead() const;
		void setOverhead(const double &value);

		/// <summary>
		/// the settings for this job
		/// contains additional information like additional streams, framerate, etc.
		/// </summary>
		const MuxSettings &getSettings() const;
		void setSettings(const MuxSettings &value);

		/// <summary>
		/// gets / sets the type of mux job this is
		/// </summary>
		const MuxerType &getMuxType() const;
		void setMuxType(const MuxerType &value);
	};
}
