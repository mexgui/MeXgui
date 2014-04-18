#include "AudioJoinJob.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;
namespace MeXgui
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

				const QString &AudioJoinJob::getInputFiles() const
				{
					return inputFiles;
				}

				void AudioJoinJob::setInputFiles(const QString &value[])
				{
					inputFiles = value;
				}

				QString AudioJoinJob::generateJoinCommandline(const QString &tempFilename)
				{
					FilesToDelete.push_back(tempFilename);
					return QString::Format("-core ( -input \"{0}\" -prefix \"{1}\" -type lst -join )", tempFilename, Output);
				}

				AudioJoinJob::AudioJoinJob()
				{
				}

				AudioJoinJob::AudioJoinJob(QString& inputFiles[], const QString &output)
				{
					assert(sizeof(inputFiles) / sizeof(inputFiles[0]) > 0);
					this->inputFiles = inputFiles;
					this->Output = output;
					this->Input = inputFiles[0];
				}

				const QString &AudioJoinJob::getCodecString() const
				{
					return "cut";
				}

				const QString &AudioJoinJob::getEncodingMode() const
				{
					return "join";
				}
			}
		}
	}
}
