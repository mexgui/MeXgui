#include "AudioUtil.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace MeGUI
{

	AudioJob *AudioUtil::getConfiguredAudioJobs(AudioJob audioStreams[])
	{
		std::vector<AudioJob*> list = std::vector<AudioJob*>();
		for (MeGUI::AudioJob::const_iterator stream = audioStreams->begin(); stream != audioStreams->end(); ++stream)
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

	bool AudioUtil::AVSScriptHasAudio(const std::string &strAVSScript, std::string &strErrorText)
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

	bool AudioUtil::AVSFileHasAudio(const std::string &strAVSScript)
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

	int AudioUtil::AVSFileChannelCount(const std::string &strAVSScript)
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

	std::string AudioUtil::getChannelPositionsFromAVSFile(const std::string &strAVSFile)
	{
		std::string strChannelPositions = "";

		try
		{
			std::string line;
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

	int AudioUtil::getChannelCountFromAVSFile(const std::string &strAVSFile)
	{
		int iChannelCount = 0;

		try
		{
			std::string line;
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
