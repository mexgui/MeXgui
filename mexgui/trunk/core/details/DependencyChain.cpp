#include "DependencyChain.h"

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

			JobChain *DUtil::convert(Job jobs[])
			{
				JobChain d[sizeof(jobs) / sizeof(jobs[0])];
				for (int i = 0; i < sizeof(jobs) / sizeof(jobs[0]); ++i)
					d[i] = jobs[i];

				return d;
			}

			const TaggedJob &EmptyJobChain::getJobs() const
			{
				return new TaggedJob[] { };
			}

			void EmptyJobChain::MakeJobDependOnChain(TaggedJob *allowedEnd)
			{

			}

			void EmptyJobChain::MakeStartDepend(MakeDependant requiredEnd)
			{

			}

			JobDependencyChain::JobDependencyChain(Job *j)
			{
				this->j = new TaggedJob(j);
				jobs = new TaggedJob[] {this->j};
			}

			const TaggedJob &JobDependencyChain::getJobs() const
			{
				return jobs;
			}

			void JobDependencyChain::MakeJobDependOnChain(TaggedJob *allowedEnd)
			{
				allowedEnd->AddDependency(j);
			}

			void JobDependencyChain::MakeStartDepend(MakeDependant requiredEnd)
			{
				requiredEnd(j);
			}
		}
	}
}
