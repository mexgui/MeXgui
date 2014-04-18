#include "MeXgui.ParallelChain.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
namespace MeXgui
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

				QVector<TaggedJob*> jobsConstructor = QVector<TaggedJob*>();
				for (MeXgui::core::details::JobChain::const_iterator chain = chains->begin(); chain != chains->end(); ++chain)
					jobsConstructor.AddRange((*chain)->Jobs);

				jobs = jobsConstructor.ToArray();
			}

			const TaggedJob &ParallelChain::getJobs() const
			{
				return jobs;
			}

			void ParallelChain::MakeJobDependOnChain(TaggedJob *j)
			{
				for (MeXgui::core::details::JobChain::const_iterator c = chains->begin(); c != chains->end(); ++c)
					(*c)->MakeJobDependOnChain(j);
			}

			void ParallelChain::MakeStartDepend(MakeDependant requiredEnd)
			{
				for (MeXgui::core::details::JobChain::const_iterator c = chains->begin(); c != chains->end(); ++c)
					(*c)->MakeStartDepend(requiredEnd);
			}
		}
	}
}
