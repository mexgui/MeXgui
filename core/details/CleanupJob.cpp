#include "CleanupJob.h"




//using namespace System::Collections::Generic;

//using namespace System::Threading;
using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace core
	{
		namespace details
		{

			CleanupJob::CleanupJob()
			{
			}

			MeXgui::core::details::JobChain *CleanupJob::AddAfter(JobChain *other, QVector<QString> &files, const QString &strInput)
			{
				CleanupJob *j = new CleanupJob();
				j->files = files;
				j->Input = strInput;
				return new SequentialChain(other, j);
			}

			const QString &CleanupJob::getCodecString() const
			{
				return "";
			}

			const QString &CleanupJob::getEncodingMode() const
			{
				return "cleanup";
			}

			add
			{
				statusUpdate += value;
			}
			remove;

			remove
			{
						statusUpdate -= value;
			}
		}


			void CleanupJobRunner::InitializeInstanceFields()
			{
				mf = MainForm::Instance;
			}

public:
				CleanupJobRunner()
				{
					InitializeInstanceFields();
				}
	};
}
					}
				}
				}
			}
			}
