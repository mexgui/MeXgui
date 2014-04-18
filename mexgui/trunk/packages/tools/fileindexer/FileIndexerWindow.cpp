#include "FileIndexerWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{

	const std::string &D2VCreatorTool::getName() const
	{
		return "File Indexer";
	}

	void D2VCreatorTool::Run(MainForm *info)
	{
		(new FileIndexerWindow(info))->Show();

	}

	const Shortcut &D2VCreatorTool::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::Ctrl2};
	}

	const std::string &D2VCreatorTool::getID() const
	{
		return "d2v_creator";
	}

JobPostProcessor *d2vIndexJobPostProcessor::PostProcessor = new JobPostProcessor(new Processor(&postprocess), "D2V_postprocessor");

	MeGUI::core::util::LogItem *d2vIndexJobPostProcessor::postprocess(MainForm *mainForm, Job *ajob)
	{
		if (!(dynamic_cast<D2VIndexJob*>(ajob) != 0))
			return 0;
		D2VIndexJob *job = static_cast<D2VIndexJob*>(ajob);

		StringBuilder *logBuilder = new StringBuilder();
		VideoUtil *vUtil = new VideoUtil(mainForm);
		std::vector<std::string> arrFilesToDelete = std::vector<std::string>();
		std::map<int, std::string> audioFiles = vUtil->getAllDemuxedAudio(job->getAudioTracks(), std::vector<AudioTrackInfo*>(), arrFilesToDelete, job->Output, 0);
		if (job->getLoadSources())
		{
			if (job->getDemuxMode() != 0 && audioFiles.size() > 0)
			{
				std::string files[audioFiles.Values->Count];
				audioFiles.Values->CopyTo(files, 0);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Util::ThreadSafeRun(mainForm, new MethodInvoker(delegate
				{
					mainForm->getAudio()->openAudioFile(files);
				}
			   ));
			}
			// if the above needed delegation for openAudioFile this needs it for openVideoFile?
			// It seems to fix the problem of ASW dissapearing as soon as it appears on a system (Vista X64)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Util::ThreadSafeRun(mainForm, new MethodInvoker(delegate
			{
				AviSynthWindow *asw = new AviSynthWindow(mainForm, job->Output);
				asw->OpenScript += new OpenScriptCallback(&mainForm->getVideo()->openVideoFile);
				asw->Show();
			}
		   ));
		}

		return 0;
	}

JobPostProcessor *dgiIndexJobPostProcessor::PostProcessor = new JobPostProcessor(new Processor(&postprocess), "Dgi_postprocessor");

	MeGUI::core::util::LogItem *dgiIndexJobPostProcessor::postprocess(MainForm *mainForm, Job *ajob)
	{
		if (!(dynamic_cast<DGIIndexJob*>(ajob) != 0))
			return 0;
		DGIIndexJob *job = static_cast<DGIIndexJob*>(ajob);

		StringBuilder *logBuilder = new StringBuilder();
		VideoUtil *vUtil = new VideoUtil(mainForm);
		std::vector<std::string> arrFilesToDelete = std::vector<std::string>();
		std::map<int, std::string> audioFiles = vUtil->getAllDemuxedAudio(job->getAudioTracks(), std::vector<AudioTrackInfo*>(), arrFilesToDelete, job->Output, 0);
		if (job->getLoadSources())
		{
			if (job->getDemuxMode() != 0 && audioFiles.size() > 0)
			{
				std::string files[audioFiles.Values->Count];
				audioFiles.Values->CopyTo(files, 0);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Util::ThreadSafeRun(mainForm, new MethodInvoker(delegate
				{
					mainForm->getAudio()->openAudioFile(files);
				}
			   ));
			}
			// if the above needed delegation for openAudioFile this needs it for openVideoFile?
			// It seems to fix the problem of ASW dissapearing as soon as it appears on a system (Vista X64)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Util::ThreadSafeRun(mainForm, new MethodInvoker(delegate
			{
				AviSynthWindow *asw = new AviSynthWindow(mainForm, job->Output);
				asw->OpenScript += new OpenScriptCallback(&mainForm->getVideo()->openVideoFile);
				asw->Show();
			}
		   ));
		}

		return 0;
	}

JobPostProcessor *dgaIndexJobPostProcessor::PostProcessor = new JobPostProcessor(new Processor(&postprocess), "Dga_postprocessor");

	MeGUI::core::util::LogItem *dgaIndexJobPostProcessor::postprocess(MainForm *mainForm, Job *ajob)
	{
		if (!(dynamic_cast<DGAIndexJob*>(ajob) != 0))
			return 0;
		DGAIndexJob *job = static_cast<DGAIndexJob*>(ajob);

		StringBuilder *logBuilder = new StringBuilder();
		VideoUtil *vUtil = new VideoUtil(mainForm);
		std::vector<std::string> arrFilesToDelete = std::vector<std::string>();
		std::map<int, std::string> audioFiles = vUtil->getAllDemuxedAudio(job->getAudioTracks(), std::vector<AudioTrackInfo*>(), arrFilesToDelete, job->Output, 0);
		if (job->getLoadSources())
		{
			if (job->getDemuxMode() != 0 && audioFiles.size() > 0)
			{
				std::string files[audioFiles.Values->Count];
				audioFiles.Values->CopyTo(files, 0);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Util::ThreadSafeRun(mainForm, new MethodInvoker(delegate
				{
					mainForm->getAudio()->openAudioFile(files);
				}
			   ));
			}
			// if the above needed delegation for openAudioFile this needs it for openVideoFile?
			// It seems to fix the problem of ASW dissapearing as soon as it appears on a system (Vista X64)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Util::ThreadSafeRun(mainForm, new MethodInvoker(delegate
			{
				AviSynthWindow *asw = new AviSynthWindow(mainForm, job->Output);
				asw->OpenScript += new OpenScriptCallback(&mainForm->getVideo()->openVideoFile);
				asw->Show();
			}
		   ));
		}

		return 0;
	}

JobPostProcessor *ffmsIndexJobPostProcessor::PostProcessor = new JobPostProcessor(new Processor(&postprocess), "FFMS_postprocessor");

	MeGUI::core::util::LogItem *ffmsIndexJobPostProcessor::postprocess(MainForm *mainForm, Job *ajob)
	{
		if (!(dynamic_cast<FFMSIndexJob*>(ajob) != 0))
			return 0;
		FFMSIndexJob *job = static_cast<FFMSIndexJob*>(ajob);

		StringBuilder *logBuilder = new StringBuilder();
		VideoUtil *vUtil = new VideoUtil(mainForm);
		std::vector<std::string> arrFilesToDelete = std::vector<std::string>();
		std::map<int, std::string> audioFiles = vUtil->getAllDemuxedAudio(job->getAudioTracks(), job->getAudioTracksDemux(), arrFilesToDelete, job->Output, 0);
		if (job->getLoadSources())
		{
			if (job->getDemuxMode() != 0)
			{
				std::string files[audioFiles.Values->Count];
				audioFiles.Values->CopyTo(files, 0);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Util::ThreadSafeRun(mainForm, new MethodInvoker(delegate
				{
					mainForm->getAudio()->openAudioFile(files);
				}
			   ));
			}
			// if the above needed delegation for openAudioFile this needs it for openVideoFile?
			// It seems to fix the problem of ASW dissapearing as soon as it appears on a system (Vista X64)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Util::ThreadSafeRun(mainForm, new MethodInvoker(delegate
			{
				AviSynthWindow *asw = new AviSynthWindow(mainForm, job->Input, job->Output);
				asw->OpenScript += new OpenScriptCallback(&mainForm->getVideo()->openVideoFile);
				asw->Show();
			}
		   ));
		}

		return 0;
	}
}
