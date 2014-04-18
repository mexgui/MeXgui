#include "CommandlineVideoEncoder.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;
using namespace MeXgui::core::plugins::implemented;
using namespace MeXgui::core::util;

namespace MeXgui
{

	CommandlineVideoEncoder::CommandlineVideoEncoder() : CommandlineJobProcessor()
	{
		InitializeInstanceFields();
	}

	void CommandlineVideoEncoder::checkJobIO()
	{
		CommandlineJobProcessor::checkJobIO();
		if (File::Exists(job->Input) && Path::GetExtension(job->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".avs"))
		{
			QString strAVSFile = "";
			try
			{
				StreamReader *sr = new StreamReader(job->Input, Encoding::Default);
				strAVSFile = sr->ReadToEnd();
				sr->Close();
			}
			catch (std::exception &e1)
			{
			}
			log->LogValue("Avisynth input script", strAVSFile);
		}
		su->setStatus("Encoding video...");
		getInputProperties(job);
	}

	void CommandlineVideoEncoder::getInputProperties(VideoJob *job)
	{
		double fps;
		Dar d;
		JobUtil::GetAllInputProperties(numberOfFrames, fps, fps_n, fps_d, hres, vres, d, job->Input);
		dar = job->getDAR();
		su->setNbFramesTotal(numberOfFrames);
		su->setClipLength(TimeSpan::FromSeconds(static_cast<double>(numberOfFrames) / fps));
	}

	void CommandlineVideoEncoder::doExitConfig()
	{
		if (!su->getHasError() && !su->getWasAborted())
			compileFinalStats();

		CommandlineJobProcessor::doExitConfig();
	}

	void CommandlineVideoEncoder::compileFinalStats()
	{
		try
		{
			if (!job->Output.empty() && File::Exists(job->Output))
			{
				FileInfo *fi = new FileInfo(job->Output);
				qint64 size = fi->Length; // size in bytes

				quint64 framecount;
				double framerate;
				JobUtil::getInputProperties(framecount, framerate, job->Input);

				double numberOfSeconds = static_cast<double>(framecount) / framerate;
				qint64 bitrate = static_cast<qint64>(static_cast<double>(size * 8.0) / (numberOfSeconds * 1000.0));

				LogItem *stats = log->Info(QString::Format("[{0:G}] {1}", DateTime::Now, "Final statistics"));

				if (job->getSettings()->getEncodingMode() == 1) // QP mode
					stats->LogValue("Constant Quantizer Mode", "Quantizer " + job->getSettings()->getBitrateQuantizer() + " computed...");
				else if (job->getSettings()->getEncodingMode() == 9) // CRF mode
					stats->LogValue("Constant Quality Mode", "Quality " + job->getSettings()->getBitrateQuantizer() + " computed...");
				else
					stats->LogValue("Video Bitrate Desired", job->getSettings()->getBitrateQuantizer() + " kbit/s");

				stats->LogValue("Video Bitrate Obtained (approximate)", bitrate + " kbit/s");
			}
		}
		catch (std::exception &e)
		{
			log->LogValue("Exception in compileFinalStats", e, Warning);
		}
	}

	bool CommandlineVideoEncoder::setFrameNumber(const QString &frameString)
	{
		int currentFrameNumber;
		if (int::TryParse(frameString, currentFrameNumber))
		{
			if (currentFrameNumber < 0)
				this->currentFrameNumber = 0;
			else
				this->currentFrameNumber = static_cast<quint64>(currentFrameNumber);
			 return true;
		}
		return false;
	}

	void CommandlineVideoEncoder::doStatusCycleOverrides()
	{
		su->setNbFramesDone(currentFrameNumber);
	}

	void CommandlineVideoEncoder::InitializeInstanceFields()
	{
		lastStatusUpdateFramePosition = 0;
		hres = 0
		vres = 0;
		fps_n = 0
		fps_d = 0;
		usesSAR = false;
	}
}
