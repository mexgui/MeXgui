#pragma once

#include "core/plugins/implemented/CommandlineJobProcessor.h"
#include "AudioJoinJob.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/util/FileSize.h"
#include "core/util/Util.h"
#include "core/util/Exceptions.h"
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
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{
				class Joiner : public CommandlineJobProcessor<AudioJoinJob*>
				{
				public:
					static JobProcessorFactory *const Factory;

				private:
					static IJobProcessor *init(MainForm *mf, Job *j);

					std::string tmpfile;

				public:
					Joiner(const std::string &exe);

				protected:
					const virtual bool &getcheckExitCode() const;

					const virtual std::string &getCommandline() const;

					virtual void checkJobIO();

				public:
					virtual void ProcessLine(const std::string &line, StreamType stream, ImageType oType);
				};
			}
		}
	}
}
