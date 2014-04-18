#include "TaggedJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
namespace MeGUI
{
	namespace core
	{
		namespace details
		{

			TaggedJob::TaggedJob()
			{
				InitializeInstanceFields();
			}

			TaggedJob::TaggedJob(MeGUI::Job *j)
			{
				InitializeInstanceFields();
				job = j;
			}

			const MeGUI::Job &TaggedJob::getJob() const
			{
				return job;
			}

			void TaggedJob::setJob(const MeGUI::Job &value)
			{
				job = value;
			}

			const std::string &TaggedJob::getOwningWorker() const
			{
				return owningWorker;
			}

			void TaggedJob::setOwningWorker(const std::string &value)
			{
				owningWorker = value;
			}

			void TaggedJob::AddDependency(TaggedJob *other)
			{
				// we can't have each job depending on the other
				assert(!std::find(other->RequiredJobs.begin(), other->RequiredJobs.end(), this) != other->RequiredJobs.end());
				RequiredJobs.push_back(other);
				other->EnabledJobs.push_back(this);
			}

			const std::vector<std::string> &TaggedJob::getRequiredJobNames() const
			{
				return requiredJobNames;
			}

			void TaggedJob::setRequiredJobNames(const std::vector<std::string> &value)
			{
				requiredJobNames = value;
			}

			const std::vector<std::string> &TaggedJob::getEnabledJobNames() const
			{
				return enabledJobNames;
			}

			void TaggedJob::setEnabledJobNames(const std::vector<std::string> &value)
			{
				enabledJobNames = value;
			}

			const std::string &TaggedJob::getName() const
			{
				return name;
			}

			void TaggedJob::setName(const std::string &value)
			{
				name = value;
			}

			const MeGUI::JobStatus &TaggedJob::getStatus() const
			{
				return status;
			}

			void TaggedJob::setStatus(const JobStatus &value)
			{
				status = value;
			}

			const DateTime &TaggedJob::getStart() const
			{
				return start;
			}

			void TaggedJob::setStart(const DateTime &value)
			{
				start = value;
			}

			const DateTime &TaggedJob::getEnd() const
			{
				return end;
			}

			void TaggedJob::setEnd(const DateTime &value)
			{
				end = value;
			}

			const std::string &TaggedJob::getStatusString() const
			{
				switch (status)
				{
					case WAITING:
						return "waiting";
					case PROCESSING:
						return "processing";
					case POSTPONED:
						return "postponed";
					case ERROR:
						return "error";
					case ABORTING:
						return "aborting";
					case ABORTED:
						return "aborted";
					case DONE:
						return "done";
					case SKIP:
						return "skip";
					default:
						return "";
				}
			}

			const std::string &TaggedJob::getInputFileName() const
			{
				return Path::GetFileName(this->getJob()->Input);
			}

			const std::string &TaggedJob::getInputFile() const
			{
				return this->getJob()->Input;
			}

			const std::string &TaggedJob::getOutputFileName() const
			{
				return Path::GetFileName(this->getJob()->Output);
			}

			const std::string &TaggedJob::getOutputFile() const
			{
				return this->getJob()->Output;
			}

			void TaggedJob::InitializeInstanceFields()
			{
				EncodingSpeed = "";
				EnabledJobs = std::vector<TaggedJob*>();
				RequiredJobs = std::vector<TaggedJob*>();
			}
		}
	}
}
