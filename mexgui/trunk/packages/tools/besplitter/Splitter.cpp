#include "Splitter.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{

JobProcessorFactory *const Splitter::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "BeSplit_Splitter");

				MeGUI::IJobProcessor *Splitter::init(MainForm *mf, Job *j)
				{
					if (dynamic_cast<AudioSplitJob*>(j) != 0)
						return new Splitter(mf->getSettings()->getBeSplitPath());
					return 0;
				}

				const bool &Splitter::getcheckExitCode() const
				{
					return false;
				}

				Splitter::Splitter(const std::string &exe)
				{
					executable = exe;
				}

				const std::string &Splitter::getCommandline() const
				{
					return job->generateSplitCommandline();
				}

				void Splitter::checkJobIO()
				{
					int endFrame = job->getTheCuts()->getAllCuts()[job->getTheCuts()->getAllCuts().size() - 1]->endFrame;
					su->setClipLength(TimeSpan::FromSeconds(static_cast<double>(endFrame) / job->getTheCuts()->Framerate));
					CommandlineJobProcessor::checkJobIO();
				}

				void Splitter::ProcessLine(const std::string &line, StreamType stream, ImageType oType)
				{
					if (line.find("Writing") != -1 || line.find("Seeking") != -1)
					{
						// this is a progress line
						try
						{
							int hours = int::Parse(line.substr(1, 2));
							int mins = int::Parse(line.substr(4, 2));
							int secs = int::Parse(line.substr(7, 2));
							int millis = int::Parse(line.substr(10, 3));
							su->setClipPosition(new TimeSpan(0, hours, mins, secs, millis));
							return;
						}
						catch (std::exception &e1)
						{
						}
					}

					if (line.find("Usage") != -1)
						oType = Error;

					CommandlineJobProcessor::ProcessLine(line, stream, oType);
				}
			}
		}
	}
}
