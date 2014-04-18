#include "Joiner.h"




//using namespace System::Collections::Generic;



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

JobProcessorFactory *const Joiner::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "BeSplit_Joiner");

				MeXgui::IJobProcessor *Joiner::init(MainForm *mf, Job *j)
				{
					if (dynamic_cast<AudioJoinJob*>(j) != 0)
						return new Joiner(mf->getSettings()->getBeSplitPath());
					return 0;
				}

				Joiner::Joiner(const QString &exe)
				{
					executable = exe;
				}

				const bool &Joiner::getcheckExitCode() const
				{
					return false;
				}

				const QString &Joiner::getCommandline() const
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
							for (QString::const_iterator file = job->getInputFiles()->begin(); file != job->getInputFiles()->end(); ++file)
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

				void Joiner::ProcessLine(const QString &line, StreamType stream, ImageType oType)
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
