#pragma once

#include "packages/audio/AudioJob.h"
#include <string>
#include <vector>
#include <stdexcept>

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
//using namespace System::IO;

namespace MeGUI
{
	/// <summary>
	/// AudioUtil is used to perform various audio related tasks
	/// </summary>
	class AudioUtil
	{
		/// <summary>
		/// returns all audio streams that can be encoded or muxed
		/// </summary>
		/// <returns></returns>
	public:
		static AudioJob *getConfiguredAudioJobs(AudioJob audioStreams[]);

		static bool AVSScriptHasAudio(const std::string &strAVSScript, std::string &strErrorText);

		static bool AVSFileHasAudio(const std::string &strAVSScript);

		static int AVSFileChannelCount(const std::string &strAVSScript);

		static std::string getChannelPositionsFromAVSFile(const std::string &strAVSFile);

		static int getChannelCountFromAVSFile(const std::string &strAVSFile);
	};
}
