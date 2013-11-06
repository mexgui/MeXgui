#pragma once

#include "IJobProcessor.h"
#include "core/util/GenericRegisterer.h"
#include "Job.h"
#include "core/gui/MeGUI.MainForm.h"
#include <map>

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

using namespace MeGUI;

namespace MeGUI
{
	namespace core
	{
		namespace plugins
		{
			namespace implemented
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
				template<typename TJob> where TJob : Job
				class JobProcessorManager : public GenericRegisterer<JobProcessorFactory*>
				{
				public:
					IJobProcessor *CreateProcessor(MainForm *info, Job *job)
					{
						std::map<JobProcessorFactory*, IJobProcessor*> processors = std::map<JobProcessorFactory*, IJobProcessor*>();
						for (MeGUI::core::plugins::implemented::JobProcessorManager::const_iterator factory = this->begin(); factory != this->end(); ++factory)
						{
							IJobProcessor *processor = factory->second->Factory(info, job);
							if (processor != 0)
								processors.insert(make_pair(factory->second, processor));
						}
						return 0;
					}
				};
			}
		}
	}
}
