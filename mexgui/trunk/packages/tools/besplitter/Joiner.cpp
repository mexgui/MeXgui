#include "Joiner.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
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

JobProcessorFactory *const Joiner::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "BeSplit_Joiner");

				MeGUI::IJobProcessor *Joiner::init(MainForm *mf, Job *j)
				{
					if (dynamic_cast<AudioJoinJob*>(j) != 0)
						return new Joiner(mf->getSettings()->getBeSplitPath());
					return 0;
				}

				Joiner::Joiner(const std::string &exe)
				{
					executable = exe;
				}

				const bool &Joiner::getcheckExitCode() const
				{
					return false;
				}

				const std::string &Joiner::getCommandline() const
				{
					return job->generateJoinCommandline(tmpfile);
				}

				void Joiner::checkJobIO()
				{
					CommandlineJobProcessor::checkJobIO();
					FileSize totalSize = FileSize::Empty;
					try
					{
						// now create the temporary list
						tmpfile = Path::Combine(Path::GetDirectoryName(job->Output), Path::GetRandomFileName());
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//						using (StreamWriter w = new StreamWriter(File.OpenWrite(tmpfile), Encoding.Default))
						StreamWriter *w = new StreamWriter(File::OpenWrite(tmpfile), Encoding::Default);
						try
						{
							for (std::string::const_iterator file = job->getInputFiles()->begin(); file != job->getInputFiles()->end(); ++file)
							{
								Util::ensureExists(*file);
								totalSize += FileSize::Of(this, &Joiner::file);
								w->WriteLine(*file);
							}
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
						finally
						{
							if (w != 0)
								w.Dispose();
						}
					}
					catch (std::exception &e)
					{
						throw new JobRunException("Error generating temporary *.lst file: " + e.what(), e);
					}
					su->setProjectedFileSize(totalSize);
					su->setClipLength(job->getClipLength());
				}

				void Joiner::ProcessLine(const std::string &line, StreamType stream, ImageType oType)
				{
					if (line.find("writing to file") != -1)
						return;

					if (line.find("Usage") != -1)
						oType = Error;
					CommandlineJobProcessor::ProcessLine(line, stream, oType);
				}
			}
		}
	}
}
