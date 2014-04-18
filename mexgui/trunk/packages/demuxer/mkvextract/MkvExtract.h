#pragma once

#include "core/plugins/implemented/CommandlineJobProcessor.h"
#include "MkvExtractJob.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/util/LogItem.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/details/TrackInfo.h"
#include "core/details/AudioTrackInfo.h"
#include "core/details/SubtitleTrackInfo.h"
#include <string>
#include <vector>
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
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;

using namespace MeGUI::core::util;

namespace MeGUI
{
	class MkvExtract : public CommandlineJobProcessor<MkvExtractJob*>
	{
	public:
		static JobProcessorFactory *const Factory;

	private:
		static IJobProcessor *init(MainForm *mf, Job *j);

	public:
		MkvExtract(const std::string &executablePath);

		/// <summary>
		/// gets the framenumber from an mkvmerge status update line
		/// </summary>
		/// <param name="line">mkvmerge commandline output</param>
		/// <returns>the framenumber included in the line</returns>
		Nullable<decimal> getPercentage(const std::string &line);

		virtual void ProcessLine(const std::string &line, StreamType stream, ImageType oType);

	protected:
		const virtual std::string &getCommandline() const;
	};
}
