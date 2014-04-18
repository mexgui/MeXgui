#pragma once

#include "core/plugins/interfaces/Job.h"
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
//using namespace System::Text;

namespace MeGUI
{
	class SubtitleIndexJob : public Job
	{
	private:
		bool indexAllTracks;
		std::vector<int> trackIDs;
		int pgc;
	public:
		SubtitleIndexJob();

		SubtitleIndexJob(const std::string &input, const std::string &output, bool indexAllTracks, std::vector<int> &trackIDs, int pgc);


		const bool &getIndexAllTracks() const;
		void setIndexAllTracks(const bool &value);

		const std::vector<int> &getTrackIDs() const;
		void setTrackIDs(const std::vector<int> &value);

		const int &getPGC() const;
		void setPGC(const int &value);

		const virtual std::string &getCodecString() const;

		const virtual std::string &getEncodingMode() const;
	};
}
