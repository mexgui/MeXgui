#include "BitrateCalculatorPreProcessor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::details;
using namespace MeGUI::packages::tools::calculator;
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

JobPreProcessor *BitrateCalculatorPreProcessor::CalculationProcessor = new JobPreProcessor(new Processor(&calculateBitrate), "CalculationProcessor");

			MeGUI::core::util::LogItem *BitrateCalculatorPreProcessor::calculateBitrate(MainForm *mainForm, Job *ajob)
			{
				if (!(dynamic_cast<VideoJob*>(ajob) != 0))
					return 0;
				VideoJob *job = static_cast<VideoJob*>(ajob);
				if (job->BitrateCalculationInfo_Renamed == 0)
					return 0;

				BitrateCalculationInfo *b = job->BitrateCalculationInfo_Renamed;
				LogItem *log = new LogItem("Bitrate calculation for video");

				std::vector<AudioBitrateCalculationStream*> audioStreams = std::vector<AudioBitrateCalculationStream*>();
				for (std::vector<std::string>::const_iterator s = b->AudioFiles.begin(); s != b->AudioFiles.end(); ++s)
					audioStreams.push_back(new AudioBitrateCalculationStream(*s));

				double framerate;
				unsigned long long framecount;
				JobUtil::getInputProperties(framecount, framerate, job->Input);

				CalcData *data = new CalcData(static_cast<long long>(framecount), static_cast<decimal>(framerate), b->Container, job->getSettings()->getCodec(), job->getSettings()->getNbBframes() > 0, audioStreams.ToArray());
				data->setTotalSize(b->DesiredSize);

				try
				{
					data->CalcByTotalSize();
				}
				catch (std::exception &e)
				{
					log->LogValue("Calculation failed", e, Error);
					return log;
				}

				log->LogValue("Desired size after subtracting audio", floor(data->getVideoSize().getKBExact()) + " KBs");
				log->LogValue("Calculated desired bitrate", static_cast<int>(data->getVideoBitrate()) + " kbit/s");

				for (std::vector<TaggedJob*>::const_iterator t = b->getVideoJobs().begin(); t != b->getVideoJobs().end(); ++t)
					if (dynamic_cast<VideoJob*>((*t)->getJob()) != 0)
						(static_cast<VideoJob*>((*t)->getJob()))->getSettings()->setBitrateQuantizer(static_cast<int>(data->getVideoBitrate()));

				return log;
			}

			const std::string &BitrateCalculationInfo::get_VideoJobNames() const
			{
				return MainForm::Instance->getJobs()->toStringList(getVideoJobs()).ToArray();
			}

			void BitrateCalculationInfo::set_VideoJobNames(const std::string &value[])
			{
				_videoJobNames = value;
			}

			const std::vector<TaggedJob*> &BitrateCalculationInfo::getVideoJobs() const
			{
				if (videoJobs.empty() && _videoJobNames != 0)
					videoJobs = MainForm::Instance->getJobs()->toJobList(_videoJobNames);
				return videoJobs;
			}

			void BitrateCalculationInfo::setVideoJobs(const std::vector<TaggedJob*> &value)
			{
				videoJobs = value;
			}

			const std::string &BitrateCalculationInfo::get_ContainerName() const
			{
				return Container->getID();
			}

			void BitrateCalculationInfo::set_ContainerName(const std::string &value)
			{
				Container = ContainerType::ByName(value);
			}
		}
	}
}
