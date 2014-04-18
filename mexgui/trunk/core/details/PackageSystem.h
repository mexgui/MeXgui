#pragma once

#include "core/plugins/interfaces/Job.h"
#include "core/plugins/interfaces/IPackage.h"
#include "core/util/GenericRegisterer.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include "core/plugins/interfaces/IMuxing.h"
#include "core/plugins/interfaces/IJobProcessor.h"

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

using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{
	namespace core
	{
		namespace details
		{

			/// <summary>
			/// Shows a dialog (normally) which allows the user to view the job's settings
			/// and reconfigure them. If a dialog is shown, the reconfigured job must be returned.
			/// 
			/// If null is returned, this is taken to mean that the job configurer is 
			/// not valid for this type of job.
			/// </summary>
			/// <param name="j"></param>
			/// <returns></returns>
			typedef Job *(*ReconfigureJob)(Job *j);

			class PackageSystem
			{

			private:
				GenericRegisterer<ITool*> *tools;
				GenericRegisterer<IOption*> *options;
				GenericRegisterer<IMediaFileFactory*> *mediaFileTypes;
				GenericRegisterer<IMuxing*> *muxers;
				GenericRegisterer<JobPreProcessor*> *jobPreProcessors;
				GenericRegisterer<JobPostProcessor*> *jobPostProcessors;
				GenericRegisterer<JobProcessorFactory*> *jobProcessors;




			public:
				GenericRegisterer<IDable<ReconfigureJob>*> *JobConfigurers;

				const GenericRegisterer<ITool*> &getTools() const;
				const GenericRegisterer<IOption*> &getOptions() const;
				const GenericRegisterer<IMediaFileFactory*> &getMediaFileTypes() const;
				const GenericRegisterer<IMuxing*> &getMuxerProviders() const;
				const GenericRegisterer<JobPreProcessor*> &getJobPreProcessors() const;
				const GenericRegisterer<JobPostProcessor*> &getJobPostProcessors() const;
				const GenericRegisterer<JobProcessorFactory*> &getJobProcessors() const;

			private:
				void InitializeInstanceFields();

public:
				PackageSystem()
				{
					InitializeInstanceFields();
				}
			};
		}
	}
}
