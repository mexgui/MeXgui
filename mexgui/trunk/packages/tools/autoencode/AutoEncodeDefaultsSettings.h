#pragma once

#include "core/util/FileSize.h"
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
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

using namespace MeGUI::core::gui;
using namespace MeGUI::core::util;

namespace MeGUI
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[LogByMembers]
	class AutoEncodeDefaultsSettings
	{
	private:
		bool fileSizeMode, bitrateMode, noTargetSizeMode, addAdditionalContent;
		std::string container, deviceType;
		Nullable<MeGUI::core::util::FileSize> splitSize, fileSize;
		int bitrate;

	public:
		AutoEncodeDefaultsSettings();
		/// <summary>
		/// gets / sets if additional content should be added
		/// </summary>
		const bool &getAddAdditionalContent() const;
		void setAddAdditionalContent(const bool &value);
		/// <summary>
		/// gets / sets if the final size should be defined by the bitrate/encoding mode set in the video settings
		/// </summary>
		const bool &getNoTargetSizeMode() const;
		void setNoTargetSizeMode(const bool &value);
		/// <summary>
		/// gets / sets if a fixed bitrate should be used for video encoding
		/// </summary>
		const bool &getBitrateMode() const;
		void setBitrateMode(const bool &value);
		/// <summary>
		/// gets / sets if the output should be defined by a filesize
		/// </summary>
		const bool &getFileSizeMode() const;
		void setFileSizeMode(const bool &value);
		/// <summary>
		///  gets / sets the default container
		/// </summary>
		const std::string &getContainer() const;
		void setContainer(const std::string &value);
		/// <summary>
		///  gets / sets the device output type
		/// </summary>
		const std::string &getDeviceOutputType() const;
		void setDeviceOutputType(const std::string &value);
		/// <summary>
		/// gets / sets the output video bitrate
		/// </summary>
		const int &getBitrate() const;
		void setBitrate(const int &value);
		/// <summary>
		/// gets / sets the output filesize
		/// </summary>
		const Nullable<MeGUI::core::util::FileSize> &getFileSize() const;
		void setFileSize(const Nullable<MeGUI::core::util::FileSize> &value);
		/// <summary>
		/// gets / sets the default split size
		/// </summary>
		const Nullable<MeGUI::core::util::FileSize> &getSplitSize() const;
		void setSplitSize(const Nullable<MeGUI::core::util::FileSize> &value);

	private:
		void InitializeInstanceFields();
	};
}