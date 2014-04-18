#include "AudioSplitJob.h"




//using namespace System::Collections::Generic;

//using namespace System::Globalization;



//using namespace System::Text;
using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{

				QString AudioSplitJob::generateSplitCommandline()
				{
					StringBuilder *sb = new StringBuilder();
					CultureInfo *ci = new CultureInfo("en-us");

					sb->AppendFormat("-core( -input \"{0}\" -prefix \"{1}\" -type {2} -a )", Input, Output, Path::GetExtension(Input)->substr(1));
					sb->Append(" -split( ");
					for (QVector<CutSection*>::const_iterator s = c->getAllCuts().begin(); s != c->getAllCuts().end(); ++s)
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

				AudioSplitJob::AudioSplitJob(const QString &input, const QString &output, Cuts *c)
				{
					this->c = c;
					this->Input = input;
					this->Output = output;
				}

				const MeXgui::core::util::Cuts &AudioSplitJob::getTheCuts() const
				{
					return c;
				}

				void AudioSplitJob::setTheCuts(const Cuts &value)
				{
					c = value;
				}

				const QString &AudioSplitJob::getCodecString() const
				{
					return "cut";
				}

				const QString &AudioSplitJob::getEncodingMode() const
				{
					return "split";
				}
			}
		}
	}
}
