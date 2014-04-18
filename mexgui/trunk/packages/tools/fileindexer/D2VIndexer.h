#pragma once

#include "core/plugins/implemented/CommandlineJobProcessor.h"
#include "D2VIndexJob.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/util/LogItem.h"
#include "core/details/AudioTrackInfo.h"
#include "core/util/FileUtil.h"
#include "packages/reader/d2v/d2vReader.h"
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
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::util;

namespace MeGUI
{
	class D2VIndexer : public CommandlineJobProcessor<D2VIndexJob*>
	{
	private:
		static Regex *const DGPercent;

		static TimeSpan *const TwoSeconds;

	public:
		static JobProcessorFactory *const Factory;

	private:
		static IJobProcessor *init(MainForm *mf, Job *j);

	public:
		D2VIndexer(const std::string &executableName);

		virtual void ProcessLine(const std::string &line, StreamType stream, ImageType oType);

	protected:
		const virtual std::string &getCommandline() const;

		virtual void checkJobIO();

		virtual void doExitConfig();

		/// <summary>
		/// opens a DGIndex project file and applies force film to it
		/// </summary>
		/// <param name="fileName">the dgindex project where force film is to be applied</param>
	private:
		bool applyForceFilm(const std::string &fileName);

	protected:
		virtual void doStatusCycleOverrides();

	};
}
