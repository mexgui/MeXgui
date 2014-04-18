#include "AMGMuxer.h"




//using namespace System::Collections::Generic;



//using namespace System::Text;


using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const AMGMuxer::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "AMGMuxer");

	IJobProcessor *AMGMuxer::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<MuxJob*>(j) != 0 && (dynamic_cast<MuxJob*>(j))->getMuxType() == AVIMUXGUI)
			return new AMGMuxer(mf->getSettings()->getAviMuxGUIPath());
		return 0;
	}

	AMGMuxer::AMGMuxer(const QString &executablePath)
	{
		this->executable = executablePath;
	}

	void AMGMuxer::checkJobIO()
	{
		script_filename = writeScript(job);
		job->FilesToDelete.push_back(script_filename);

		CommandlineMuxer::checkJobIO();
	}

	const QString &AMGMuxer::getCommandline() const
	{
		return "\"" + script_filename + "\"";
	}

	QString AMGMuxer::writeScript(MuxJob *job)
	{
		MuxSettings *settings = job->getSettings();

		// First, generate the script

		StringBuilder *script = new StringBuilder();
		script->AppendLine("CLEAR");

		int fileNum = 1; // the number of the file at the top

		int audioNum = 1; // the audio track number
		// add the audio streams
		for (QVector<MuxStream*>::const_iterator s = settings->getAudioStreams().begin(); s != settings->getAudioStreams().end(); ++s)
		{
			script->AppendFormat("LOAD {1}{0}", "\r\n", (*s)->path);
			script->AppendLine("SET OUTPUT OPTIONS");
			if (!(*s)->getname()->empty())
				script->AppendFormat("SET OPTION AUDIO NAME {0} {1}{2}", audioNum, (*s)->getname(), "\r\n");
			if (!(*s)->getlanguage()->empty())
				script->AppendFormat("SET OPTION AUDIO LNGCODE {0} {1}{2}", audioNum, (*s)->getlanguage(), "\r\n");
			if ((*s)->delay != 0)
				script->AppendFormat("SET OPTION DELAY {0} {1}{2}", audioNum, (*s)->delay, "\r\n");

			audioNum++;
			fileNum++;
		}

		int subtitleNum = 1; // the subtitle track number
		// add the subtitle streams
		for (QVector<MuxStream*>::const_iterator s = settings->getSubtitleStreams().begin(); s != settings->getSubtitleStreams().end(); ++s)
		{
			script->AppendFormat("LOAD {1}{0}", "\r\n", (*s)->path);
			script->AppendLine("SET OUTPUT OPTIONS");
			if (!(*s)->getname()->empty())
				script->AppendFormat("SET OPTION SUBTITLE NAME {0} {1}{2}", subtitleNum, (*s)->getname(), "\r\n");

			subtitleNum++;
			fileNum++;
		}

		// add the video stream if it exists
		if (!settings->getVideoInput().empty())
		{
			script->AppendFormat("LOAD {1}{0}SELECT FILE {2}{0}ADD VIDEOSOURCE{0}DESELECT FILE {2}{0}", "\r\n", settings->getVideoInput(), fileNum);
			fileNum++;
		}

		// mux in the rest if it exists
		if (!settings->getMuxedInput().empty())
		{
			script->AppendFormat("LOAD {1}{0}SELECT FILE {2}{0}ADD VIDEOSOURCE{0}DESELECT FILE {2}{0}", "\r\n", settings->getMuxedInput(), fileNum);
			fileNum++;
		}

		// AR can't be signalled in AVI

		// split size
		script->AppendLine("SET OUTPUT OPTIONS");
		if (settings->getSplitSize().HasValue || settings->getDeviceType().empty() || settings->getDeviceType() == "Standard")
		{
			script->AppendLine("SET OPTION NUMBERING ON");
			script->AppendLine("SET OPTION MAXFILESIZE ON");
			if ((settings->getDeviceType().empty() || settings->getDeviceType() == "Standard") && (!settings->getSplitSize().HasValue || (static_cast<MeXgui::core::util::FileSize>(settings->getSplitSize())).getMB() > 2000))
				script->AppendFormat("SET OPTION MAXFILESIZE {0}{1}", 2000, "\r\n");
			else
				script->AppendFormat("SET OPTION MAXFILESIZE {0}{1}", (static_cast<MeXgui::core::util::FileSize>(settings->getSplitSize())).getMB(), "\r\n");
		}
		else
		{
			script->AppendLine("SET OPTION NUMBERING OFF");
			script->AppendLine("SET OPTION MAXFILESIZE OFF");
		}

		// Now do the rest of the setup
		script->AppendLine("SET INPUT OPTIONS" + "\r\n" + "SET OPTION MP3 VERIFY CBR ALWAYS" + "\r\n" + "SET OPTION MP3 VERIFY RESDLG OFF" + "\r\n" + "SET OPTION AVI FIXDX50 1" + "\r\n" + "SET OPTION CHAPTERS IMPORT 1" + "\r\n" + "SET OUTPUT OPTIONS" + "\r\n" + "SET OPTION ALL SUBTITLES 1" + "\r\n" + "SET OPTION ALL AUDIO 1" + "\r\n" + "SET OPTION CLOSEAPP 1" + "\r\n" + "SET OPTION DONEDLG 0" + "\r\n" + "SET OPTION OVERWRITEDLG 0" + "\r\n" + "SET OPTION PRELOAD 200");

		if (settings->getDeviceType().empty() || settings->getDeviceType() == "Standard")
		{
			script->AppendLine("SET OPTION OPENDML 0" + "\r\n" + "SET OPTION RECLISTS 0" + "\r\n" + "SET OPTION AVI ADDJUNKBEFOREHEADERS 0" + "\r\n" + "SET OPTION AUDIO INTERLEAVE 4 FR");
		}
		else
		{
			script->AppendLine("SET OPTION OPENDML 1" + "\r\n" + "SET OPTION RECLISTS 1" + "\r\n" + "SET OPTION AUDIO INTERLEAVE 100 KB" + "\r\n" + "SET OPTION AVI RIFFAVISIZE 1" + "\r\n" + "SET OPTION AVI ADDJUNKBEFOREHEADERS 1" + "\r\n" + "SET OPTION AVI HAALIMODE 0" + "\r\n" + "SET OPTION STDIDX 10000 FRAMES" + "\r\n" + "SET OPTION LEGACY 1");
		}

		script->AppendFormat("START {0}{1}", settings->getMuxedOutput(), "\r\n");

		/// the script is now created; let's write it to a temp file
		QString filename = Path::ChangeExtension(job->Output, ".mux");
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (StreamWriter output = new StreamWriter(File.OpenWrite(filename), System.Text.Encoding.UTF8))
		StreamWriter *output = new StreamWriter(File::OpenWrite(filename), System::Text::Encoding::UTF8);
		try
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			output->Write(script->ToString());
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (output != 0)
				output.Dispose();
		}
		log->LogValue("mux script", script);
		return filename;
	}

	const bool &AMGMuxer::getcheckExitCode() const
	{
		return false;
	}
}
