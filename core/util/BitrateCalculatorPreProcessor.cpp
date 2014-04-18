#include "BitrateCalculatorPreProcessor.h"




//using namespace System::Collections::Generic;



//using namespace System::Text;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::details;
using namespace MeXgui::packages::tools::calculator;
namespace MeXgui
{
	namespace core
	{
		namespace util
		{

JobPreProcessor *BitrateCalculatorPreProcessor::CalculationProcessor = new JobPreProcessor(new Processor(&calculateBitrate), "CalculationProcessor");

			MeXgui::core::util::LogItem *BitrateCalculatorPreProcessor::calculateBitrate(MainForm *mainForm, Job *ajob)
			{
				if (!(dynamic_cast<VideoJob*>(ajob) != 0))
					return 0;
				VideoJob *job = static_cast<VideoJob*>(ajob);
				if (job->BitrateCalculationInfo_Renamed == 0)
					return 0;

				BitrateCalculationInfo *b = job->BitrateCalculationInfo_Renamed;
				LogItem *log = new LogItem("Bitrate calculation for video");

				QVector<AudioBitrateCalculationStream*> audioStreams = QVector<AudioBitrateCalculationStream*>();
				for (QVector<QString>::const_iterator s = b->AudioFiles.begin(); s != b->AudioFiles.end(); ++s)
					audioStreams.push_back(new AudioBitrateCalculationStream(*s));

				double framerate;
				quint64 framecount;
				JobUtil::getInputProperties(framecount, framerate, job->Input);

				CalcData *data = new CalcData(static_cast<qint64>(framecount), static_cast<decimal>(framerate), b->Container, job->getSettings()->getCodec(), job->getSettings()->getNbBframes() > 0, audioStreams.ToArray());
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

				for (QVector<TaggedJob*>::const_iterator t = b->getVideoJobs().begin(); t != b->getVideoJobs().end(); ++t)
					if (dynamic_cast<VideoJob*>((*t)->getJob()) != 0)
						(static_cast<VideoJob*>((*t)->getJob()))->getSettings()->setBitrateQuantizer(static_cast<int>(data->getVideoBitrate()));

				return log;
			}

			const QString &BitrateCalculationInfo::get_VideoJobNames() const
			{
				return MainForm::Instance->getJobs()->toStringList(getVideoJobs()).ToArray();
			}

			void BitrateCalculationInfo::set_VideoJobNames(const QString &value[])
			{
				_videoJobNames = value;
			}

			const QVector<TaggedJob*> &BitrateCalculationInfo::getVideoJobs() const
			{
				if (videoJobs.empty() && _videoJobNames != 0)
					videoJobs = MainForm::Instance->getJobs()->toJobList(_videoJobNames);
				return videoJobs;
			}

			void BitrateCalculationInfo::setVideoJobs(const QVector<TaggedJob*> &value)
			{
				videoJobs = value;
			}

			const QString &BitrateCalculationInfo::get_ContainerName() const
			{
				return Container->getID();
			}

			void BitrateCalculationInfo::set_ContainerName(const QString &value)
			{
				Container = ContainerType::ByName(value);
			}
		}
	}
}
