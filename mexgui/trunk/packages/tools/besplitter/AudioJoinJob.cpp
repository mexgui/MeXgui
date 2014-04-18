#include "AudioJoinJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{

				const TimeSpan &AudioJoinJob::getClipLength() const
				{
					return cliplength;
				}

				void AudioJoinJob::setClipLength(const TimeSpan &value)
				{
					cliplength = value;
				}

				const std::string &AudioJoinJob::getInputFiles() const
				{
					return inputFiles;
				}

				void AudioJoinJob::setInputFiles(const std::string &value[])
				{
					inputFiles = value;
				}

				std::string AudioJoinJob::generateJoinCommandline(const std::string &tempFilename)
				{
					FilesToDelete.push_back(tempFilename);
					return std::string::Format("-core ( -input \"{0}\" -prefix \"{1}\" -type lst -join )", tempFilename, Output);
				}

				AudioJoinJob::AudioJoinJob()
				{
				}

				AudioJoinJob::AudioJoinJob(std::string& inputFiles[], const std::string &output)
				{
					assert(sizeof(inputFiles) / sizeof(inputFiles[0]) > 0);
					this->inputFiles = inputFiles;
					this->Output = output;
					this->Input = inputFiles[0];
				}

				const std::string &AudioJoinJob::getCodecString() const
				{
					return "cut";
				}

				const std::string &AudioJoinJob::getEncodingMode() const
				{
					return "join";
				}
			}
		}
	}
}
