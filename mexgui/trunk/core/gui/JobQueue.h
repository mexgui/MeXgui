#pragma once

#include "core/util/Util.h"
#include "core/details/TaggedJob.h"
#include "core/util/LogItem.h"
#include "core/plugins/interfaces/Job.h"
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
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			typedef Pair<std::string, MultiJobHandler>[] (*MultiJobMenuGenerator)();
			typedef void (*JobChangeEvent)(object *sender, JobQueueEventArgs *info);
			typedef void (*RequestJobDeleted)(TaggedJob *jobs);
			typedef void (*SingleJobHandler)(TaggedJob *job);
			typedef void (*MultiJobHandler)(std::vector<TaggedJob*> &jobs);
			enum StartStopMode
			{
				Start,
				Stop
			};
			enum PauseResumeMode
			{
				Pause,
				Resume,
				Disabled
			};
			enum Dependencies
			{
				DeleteAll,
				RemoveDependencies
			};


			class JobQueueEventArgs : public EventArgs
			{
			private:
				Job *job;
			public:
				const Job &getModifiedJob() const;

				JobQueueEventArgs(Job *j);
			};

		}
	}
}
