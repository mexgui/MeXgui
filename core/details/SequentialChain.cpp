#include "SequentialChain.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
namespace MeXgui
{
	namespace core
	{
		namespace details
		{

			SequentialChain::SequentialChain(...)
			{
				resolve(chains);
			}

			SequentialChain::SequentialChain(...)
			{
			}

			void SequentialChain::resolve(JobChain chains[])
			{
				if (sizeof(chains) / sizeof(chains[0]) == 0)
					chains = new JobChain[] {new EmptyJobChain()};

				QVector<TaggedJob*> jobs = QVector<TaggedJob*>();
				JobChain *last = 0;

				for (int i = 0; i < sizeof(chains) / sizeof(chains[0]); i++)
				{
					if (chains[i] == 0 || chains[i]->Jobs->Length == 0)
						continue;
//ORIGINAL LINE: TaggedJob[] cjobs = chains[i].Jobs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
					TaggedJob *cjobs = chains[i]->Jobs;
					if (last != 0)
						chains[i]->MakeStartDepend(new MakeDependant(last->MakeJobDependOnChain));
					jobs.AddRange(cjobs);
					last = chains[i];
				}
				this->jobs = jobs.ToArray();
				for (int i = 0; i < sizeof(chains) / sizeof(chains[0]); i++)
				{
					this->first = chains[i];
					if (chains[i] != 0 && chains[i]->Jobs->Length > 0)
						break;
				}
				for (int i = sizeof(chains) / sizeof(chains[0]) - 1; i >= 0; i--)
				{
					this->last = chains[i];
					if (chains[i] != 0 && chains[i]->Jobs->Length > 0)
						break;
				}
			}

			const TaggedJob &SequentialChain::getJobs() const
			{
				return jobs;
			}

			void SequentialChain::MakeJobDependOnChain(TaggedJob *j)
			{
				last->MakeJobDependOnChain(j);
			}

			void SequentialChain::MakeStartDepend(MakeDependant requiredEnd)
			{
				first->MakeStartDepend(requiredEnd);
			}
		}
	}
}
