#include "AviSynthProcessor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
using namespace MeGUI::core::util;

namespace MeGUI
{

JobProcessorFactory *const AviSynthProcessor::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "AviSynthProcessor");

	IJobProcessor *AviSynthProcessor::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<AviSynthJob*>(j) != 0)
			return new AviSynthProcessor();
		return 0;
	}

	AviSynthProcessor::AviSynthProcessor()
	{
		InitializeInstanceFields();
	}

	void AviSynthProcessor::update()
	{
		while (!aborted && position < stup->getNbFramesTotal())
		{
			stup->setNbFramesDone(position);
			stup->setTimeElapsed(DateTime::Now - startTime);
			stup->FillValues();
			StatusUpdate(stup);
			delay(1000);
		}
		stup->setIsComplete(true);
		StatusUpdate(stup);
	}

	void AviSynthProcessor::process()
	{
		void* zero = new void*(0);
		for (position = 0; position < stup->getNbFramesTotal() && !aborted; position++)
		{
			file->getClip()->ReadFrame(zero, 0, static_cast<int>(position));
			mre->WaitOne();
		}
		delete file;
	}

	void AviSynthProcessor::setup(Job *job, StatusUpdate *su, LogItem *_)
	{
		assert(dynamic_cast<AviSynthJob*>(job) != 0, "Job isn't an AviSynthJob");
		stup = su;
		this->job = static_cast<AviSynthJob*>(job);

		try
		{
			file = AvsFile::OpenScriptFile(job->Input);
			reader = file->GetVideoReader();
		}
		catch (std::exception &ex)
		{
			throw new JobRunException(ex);
		}
		stup->setNbFramesTotal(static_cast<unsigned long long>(reader->getFrameCount()));
		stup->setClipLength(TimeSpan::FromSeconds(static_cast<double>(stup->getNbFramesTotal()) / file->getVideoInfo()->FPS));
		stup->setStatus("Playing through file...");
		position = 0;
		try
		{
			processorThread = new Thread(new ThreadStart(process));
		}
		catch (std::exception &e)
		{
			throw new JobRunException(e);
		}
		try
		{
			statusThread = new Thread(new ThreadStart(update));
		}
		catch (std::exception &e)
		{
			throw new JobRunException(e);
		}
	}

	void AviSynthProcessor::start()
	{
		try
		{
			statusThread->Start();
			processorThread->Start();
			startTime = DateTime::Now;
		}
		catch (std::exception &e)
		{
			throw new JobRunException(e);
		}
	}

	void AviSynthProcessor::stop()
	{
		aborted = true;
	}

	void AviSynthProcessor::pause()
	{
		if (!mre->Reset())
			throw new JobRunException("Could not reset mutex");
	}

	void AviSynthProcessor::resume()
	{
		if (!mre->Set())
			throw new JobRunException("Could not set mutex");
	}

	void AviSynthProcessor::changePriority(ProcessPriority priority)
	{
		if (processorThread != 0 && processorThread->IsAlive)
		{
			try
			{
				if (priority == IDLE)
					processorThread->Priority = ThreadPriority::Lowest;
				else if (priority == NORMAL)
					processorThread->Priority = ThreadPriority::Normal;
				else if (priority == HIGH)
					processorThread->Priority = ThreadPriority::Highest;
				return;
			}
			catch (std::exception &e) // process could not be running anymore
			{
				throw new JobRunException(e);
			}
		}
		else
		{
			if (processorThread == 0)
				throw new JobRunException("Process has not been started yet");
			else
				throw new JobRunException("Process has exited");
		}
	}

	void AviSynthProcessor::InitializeInstanceFields()
	{
		mre = new System::Threading::ManualResetEvent(true);
		delete stup;
	}
}
