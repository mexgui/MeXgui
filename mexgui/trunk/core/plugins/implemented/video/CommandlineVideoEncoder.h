#pragma once

#include "core/details/video/VideoJob.h"
#include "core/plugins/implemented/CommandlineJobProcessor.h"
#include "core/util/DAR.h"
#include "core/util/JobUtil.h"
#include "core/util/LogItem.h"
#include <string>
#include <stdexcept>

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
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

using namespace MeGUI::core::plugins::implemented;
using namespace MeGUI::core::util;

namespace MeGUI
{
	typedef void (*EncoderOutputCallback)(const std::string &line, int type);

	class CommandlineVideoEncoder : public CommandlineJobProcessor<VideoJob*>
	{
	private:
		unsigned long long numberOfFrames;
		Nullable<Dar> dar;
		Nullable<unsigned long long> currentFrameNumber;
	protected:
		int lastStatusUpdateFramePosition;
		int hres, vres;
		int fps_n, fps_d;
		bool usesSAR;
	public:
		CommandlineVideoEncoder();
	protected:
		virtual void checkJobIO();
		/// <summary>
		/// tries to open the video source and gets the number of frames from it, or 
		/// exits with an error
		/// </summary>
		/// <param name="videoSource">the AviSynth script</param>
		/// <param name="error">return parameter for all errors</param>
		/// <returns>true if the file could be opened, false if not</returns>
		void getInputProperties(VideoJob *job);

		virtual void doExitConfig();
		/// <summary>
		/// compiles final bitrate statistics
		/// </summary>
		void compileFinalStats();

		bool setFrameNumber(const std::string &frameString);

		virtual void doStatusCycleOverrides();

	private:
		void InitializeInstanceFields();
	};
}
