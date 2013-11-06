#include "PackageSystem.h"

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

			const MeGUI::GenericRegisterer<ITool*> &PackageSystem::getTools() const
			{
				return tools;
			}

			const MeGUI::GenericRegisterer<IOption*> &PackageSystem::getOptions() const
			{
				return options;
			}

			const MeGUI::GenericRegisterer<IMediaFileFactory*> &PackageSystem::getMediaFileTypes() const
			{
				return mediaFileTypes;
			}

			const MeGUI::GenericRegisterer<IMuxing*> &PackageSystem::getMuxerProviders() const
			{
				return muxers;
			}

			const MeGUI::GenericRegisterer<JobPreProcessor*> &PackageSystem::getJobPreProcessors() const
			{
				return jobPreProcessors;
			}

			const MeGUI::GenericRegisterer<JobPostProcessor*> &PackageSystem::getJobPostProcessors() const
			{
				return jobPostProcessors;
			}

			const MeGUI::GenericRegisterer<JobProcessorFactory*> &PackageSystem::getJobProcessors() const
			{
				return jobProcessors;
			}

			void PackageSystem::InitializeInstanceFields()
			{
				tools = new GenericRegisterer<ITool*>();
				options = new GenericRegisterer<IOption*>();
				mediaFileTypes = new GenericRegisterer<IMediaFileFactory*>();
				muxers = new GenericRegisterer<IMuxing*>();
				jobPreProcessors = new GenericRegisterer<JobPreProcessor*>();
				jobPostProcessors = new GenericRegisterer<JobPostProcessor*>();
				jobProcessors = new GenericRegisterer<JobProcessorFactory*>();
				JobConfigurers = new GenericRegisterer<IDable<ReconfigureJob>*>();
			}
		}
	}
}
