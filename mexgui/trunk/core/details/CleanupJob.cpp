#include "CleanupJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace details
		{

			CleanupJob::CleanupJob()
			{
			}

			MeGUI::core::details::JobChain *CleanupJob::AddAfter(JobChain *other, std::vector<std::string> &files, const std::string &strInput)
			{
				CleanupJob *j = new CleanupJob();
				j->files = files;
				j->Input = strInput;
				return new SequentialChain(other, j);
			}

			const std::string &CleanupJob::getCodecString() const
			{
				return "";
			}

			const std::string &CleanupJob::getEncodingMode() const
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
