#include "PackageSystem.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
using namespace MeXgui::core::plugins::interfaces;
namespace MeXgui
{
	namespace core
	{
		namespace details
		{

			const MeXgui::GenericRegisterer<ITool*> &PackageSystem::getTools() const
			{
				return tools;
			}

			const MeXgui::GenericRegisterer<IOption*> &PackageSystem::getOptions() const
			{
				return options;
			}

			const MeXgui::GenericRegisterer<IMediaFileFactory*> &PackageSystem::getMediaFileTypes() const
			{
				return mediaFileTypes;
			}

			const MeXgui::GenericRegisterer<IMuxing*> &PackageSystem::getMuxerProviders() const
			{
				return muxers;
			}

			const MeXgui::GenericRegisterer<JobPreProcessor*> &PackageSystem::getJobPreProcessors() const
			{
				return jobPreProcessors;
			}

			const MeXgui::GenericRegisterer<JobPostProcessor*> &PackageSystem::getJobPostProcessors() const
			{
				return jobPostProcessors;
			}

			const MeXgui::GenericRegisterer<JobProcessorFactory*> &PackageSystem::getJobProcessors() const
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
