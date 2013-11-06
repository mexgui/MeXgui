#include "MeGUI.core.details.ParallelChain.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
namespace MeGUI
{
	namespace core
	{
		namespace details
		{

			ParallelChain::ParallelChain(...)
			{
				resolve(chains);
			}

			ParallelChain::ParallelChain(...)
			{
			}

			void ParallelChain::resolve(JobChain chains[])
			{
				this->chains = chains;

				std::vector<TaggedJob*> jobsConstructor = std::vector<TaggedJob*>();
				for (MeGUI::core::details::JobChain::const_iterator chain = chains->begin(); chain != chains->end(); ++chain)
					jobsConstructor.AddRange((*chain)->Jobs);

				jobs = jobsConstructor.ToArray();
			}

			const TaggedJob &ParallelChain::getJobs() const
			{
				return jobs;
			}

			void ParallelChain::MakeJobDependOnChain(TaggedJob *j)
			{
				for (MeGUI::core::details::JobChain::const_iterator c = chains->begin(); c != chains->end(); ++c)
					(*c)->MakeJobDependOnChain(j);
			}

			void ParallelChain::MakeStartDepend(MakeDependant requiredEnd)
			{
				for (MeGUI::core::details::JobChain::const_iterator c = chains->begin(); c != chains->end(); ++c)
					(*c)->MakeStartDepend(requiredEnd);
			}
		}
	}
}
