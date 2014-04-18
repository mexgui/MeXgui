#include "AudioUtil.h"




//using namespace System::Collections::Generic;



namespace MeXgui
{

	AudioJob *AudioUtil::getConfiguredAudioJobs(AudioJob audioStreams[])
	{
		QVector<AudioJob*> list = QVector<AudioJob*>();
		for (MeXgui::AudioJob::const_iterator stream = audioStreams->begin(); stream != audioStreams->end(); ++stream)
		{
			if ((*stream)->Input->empty())
			{
				// no audio is ok, just skip
				break;
			}
			list.push_back(*stream);

		}
		return list.ToArray();
	}

	bool AudioUtil::AVSScriptHasAudio(const QString &strAVSScript, QString &strErrorText)
	{
		try
		{
			strErrorText = "";
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AviSynthScriptEnvironment env = new AviSynthScriptEnvironment())
			AviSynthScriptEnvironment *env = new AviSynthScriptEnvironment();
			try
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (AviSynthClip a = env.ParseScript(strAVSScript))
				AviSynthClip *a = env->ParseScript(strAVSScript);
				try
				{
					if (a->getChannelsCount() == 0)
						return false;
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (a != 0)
						a.Dispose();
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (env != 0)
					env.Dispose();
			}
			return true;
		}
		catch (std::exception &ex)
		{
			strErrorText = ex.what();
			return false;
		}
	}

	bool AudioUtil::AVSFileHasAudio(const QString &strAVSScript)
	{
		try
		{
			if (!Path::GetExtension(strAVSScript)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".avs"))
				return false;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AviSynthScriptEnvironment env = new AviSynthScriptEnvironment())
			AviSynthScriptEnvironment *env = new AviSynthScriptEnvironment();
			try
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (AviSynthClip a = env.OpenScriptFile(strAVSScript))
				AviSynthClip *a = env->OpenScriptFile(strAVSScript);
				try
				{
					if (a->getChannelsCount() == 0)
						return false;
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (a != 0)
						a.Dispose();
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (env != 0)
					env.Dispose();
			}
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	int AudioUtil::AVSFileChannelCount(const QString &strAVSScript)
	{
		try
		{
			if (!Path::GetExtension(strAVSScript)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".avs"))
				return 0;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AviSynthScriptEnvironment env = new AviSynthScriptEnvironment())
			AviSynthScriptEnvironment *env = new AviSynthScriptEnvironment();
			try
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (AviSynthClip a = env.OpenScriptFile(strAVSScript))
				AviSynthClip *a = env->OpenScriptFile(strAVSScript);
				try
				{
					return a->getChannelsCount();
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (a != 0)
						a.Dispose();
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (env != 0)
					env.Dispose();
			}
		}
		catch (...)
		{
			return 0;
		}
	}

	QString AudioUtil::getChannelPositionsFromAVSFile(const QString &strAVSFile)
	{
		QString strChannelPositions = "";

		try
		{
			QString line;
			StreamReader *file = new StreamReader(strAVSFile);
			while ((line = file->ReadLine()) != 0)
			{
				if (line.find("# detected channel positions: ") == 0)
				{
					strChannelPositions = line.substr(30);
					break;
				}
			}
			file->Close();
			return strChannelPositions;
		}
		catch (...)
		{
			return strChannelPositions;
		}
	}

	int AudioUtil::getChannelCountFromAVSFile(const QString &strAVSFile)
	{
		int iChannelCount = 0;

		try
		{
			QString line;
			StreamReader *file = new StreamReader(strAVSFile);
			while ((line = file->ReadLine()) != 0)
			{
				if (line.find("# detected channels: ") == 0)
				{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					int::TryParse(line.substr(21)->Split(' ')[0], iChannelCount);
					break;
				}
			}
			file->Close();
			return iChannelCount;
		}
		catch (...)
		{
			return iChannelCount;
		}
	}
}
