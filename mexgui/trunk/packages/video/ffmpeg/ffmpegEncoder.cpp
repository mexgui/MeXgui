#include "ffmpegEncoder.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::util;

namespace MeGUI
{

JobProcessorFactory *const ffmpegEncoder::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "FFmpegEncoder");

	IJobProcessor *ffmpegEncoder::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<VideoJob*>(j) != 0 && (dynamic_cast<hfyuSettings*>((dynamic_cast<VideoJob*>(j))->getSettings()) != 0))
			return new ffmpegEncoder(mf->getSettings()->getFFMpegPath());
		return 0;
	}

	ffmpegEncoder::ffmpegEncoder(const std::string &encoderPath) : CommandlineVideoEncoder()
	{
			executable = encoderPath;
	}

	const std::string &ffmpegEncoder::getCommandline() const
	{
		StringBuilder *sb = new StringBuilder();
		sb->Append("-y -i \"" + job->Input + "\" -c:v ffvhuff -threads 0 -sn -an -context 1 -vstrict -2 -pred 2 \"" + job->Output + "\" ");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
		throw std::exception();
	}

	void ffmpegEncoder::ProcessLine(const std::string &line, StreamType stream, ImageType oType)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("Pos:")) // status update
		{
			int frameNumberStart = line.find("s", 4) + 1;
			int frameNumberEnd = line.find("f");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			if (CommandlineVideoEncoder::setFrameNumber(line.substr(frameNumberStart, frameNumberEnd - frameNumberStart)->Trim()))
				return;
		}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		else if (line.StartsWith("frame=")) // status update for ffmpeg
		{
			int frameNumberEnd = line.find("f", 6);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			if (CommandlineVideoEncoder::setFrameNumber(line.substr(6, frameNumberEnd - 6)->Trim()))
				return;
		}

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (line.ToLowerInvariant()->Contains("error") && !line.ToLowerInvariant()->StartsWith("input #0, avisynth, from '") && !line.ToLowerInvariant()->StartsWith("output #0, avi, to '") && !line.ToLowerInvariant()->EndsWith("input/output error"))
			oType = Error;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		else if (line.ToLowerInvariant()->Contains("warning") && !line.ToLowerInvariant()->StartsWith("input #0, avisynth, from '") && !line.ToLowerInvariant()->StartsWith("output #0, avi, to '"))
			oType = Warning;
		CommandlineVideoEncoder::ProcessLine(line, stream, oType);
	}
}
