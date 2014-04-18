#include "AudioSplitJob.h"

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
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{

				std::string AudioSplitJob::generateSplitCommandline()
				{
					StringBuilder *sb = new StringBuilder();
					CultureInfo *ci = new CultureInfo("en-us");

					sb->AppendFormat("-core( -input \"{0}\" -prefix \"{1}\" -type {2} -a )", Input, Output, Path::GetExtension(Input)->substr(1));
					sb->Append(" -split( ");
					for (std::vector<CutSection*>::const_iterator s = c->getAllCuts().begin(); s != c->getAllCuts().end(); ++s)
					{
						double start = (static_cast<double>((*s)->startFrame)) / c->Framerate;
						double end = (static_cast<double>((*s)->endFrame + 1)) / c->Framerate;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						sb->AppendFormat("{0} {1} ", start.ToString(ci), end.ToString(ci));
					}
					sb->Append(")");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return sb->ToString();
				}

				AudioSplitJob::AudioSplitJob()
				{
				}

				AudioSplitJob::AudioSplitJob(const std::string &input, const std::string &output, Cuts *c)
				{
					this->c = c;
					this->Input = input;
					this->Output = output;
				}

				const MeGUI::core::util::Cuts &AudioSplitJob::getTheCuts() const
				{
					return c;
				}

				void AudioSplitJob::setTheCuts(const Cuts &value)
				{
					c = value;
				}

				const std::string &AudioSplitJob::getCodecString() const
				{
					return "cut";
				}

				const std::string &AudioSplitJob::getEncodingMode() const
				{
					return "split";
				}
			}
		}
	}
}
