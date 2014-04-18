#include "TaggedJob.h"




//using namespace System::Collections::Generic;



//using namespace System::Xml::Serialization;
namespace MeXgui
{
	namespace core
	{
		namespace details
		{

			TaggedJob::TaggedJob()
			{
				InitializeInstanceFields();
			}

			TaggedJob::TaggedJob(MeXgui::Job *j)
			{
				InitializeInstanceFields();
				job = j;
			}

			const MeXgui::Job &TaggedJob::getJob() const
			{
				return job;
			}

			void TaggedJob::setJob(const MeXgui::Job &value)
			{
				job = value;
			}

			const QString &TaggedJob::getOwningWorker() const
			{
				return owningWorker;
			}

			void TaggedJob::setOwningWorker(const QString &value)
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

			const QVector<QString> &TaggedJob::getRequiredJobNames() const
			{
				return requiredJobNames;
			}

			void TaggedJob::setRequiredJobNames(const QVector<QString> &value)
			{
				requiredJobNames = value;
			}

			const QVector<QString> &TaggedJob::getEnabledJobNames() const
			{
				return enabledJobNames;
			}

			void TaggedJob::setEnabledJobNames(const QVector<QString> &value)
			{
				enabledJobNames = value;
			}

			const QString &TaggedJob::getName() const
			{
				return name;
			}

			void TaggedJob::setName(const QString &value)
			{
				name = value;
			}

			const MeXgui::JobStatus &TaggedJob::getStatus() const
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

			const QString &TaggedJob::getStatusString() const
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

			const QString &TaggedJob::getInputFileName() const
			{
				return Path::GetFileName(this->getJob()->Input);
			}

			const QString &TaggedJob::getInputFile() const
			{
				return this->getJob()->Input;
			}

			const QString &TaggedJob::getOutputFileName() const
			{
				return Path::GetFileName(this->getJob()->Output);
			}

			const QString &TaggedJob::getOutputFile() const
			{
				return this->getJob()->Output;
			}

			void TaggedJob::InitializeInstanceFields()
			{
				EncodingSpeed = "";
				EnabledJobs = QVector<TaggedJob*>();
				RequiredJobs = QVector<TaggedJob*>();
			}
		}
	}
}
