#pragma once

#include "core/plugins/interfaces/Job.h"
#include "core/details/TrackInfo.h"
#include "core/details/AudioTrackInfo.h"
#include <string>
#include <vector>

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
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{
	/// <summary>
	/// Container object for MkvExtract
	/// </summary>
	class MkvExtractJob : public Job
	{
	private:
		std::vector<TrackInfo*> _oTracks;
		std::string _strOutputPath;

	public:
		MkvExtractJob();

		MkvExtractJob(const std::string &strInput, const std::string &strOutputPath, std::vector<TrackInfo*> &oTracks);

		MkvExtractJob(const std::string &strInput, const std::string &strOutputPath, std::vector<AudioTrackInfo*> &oTracks);

		const virtual std::string &getCodecString() const;

		const virtual std::string &getEncodingMode() const;

		const std::vector<TrackInfo*> &getMkvTracks() const;
		void setMkvTracks(const std::vector<TrackInfo*> &value);

		const std::string &getOutputPath() const;
		void setOutputPath(const std::string &value);
	};
}
