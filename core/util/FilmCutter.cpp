#include "FilmCutter.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;

//using namespace System::Globalization;



//using namespace System::Text;

//using namespace System::Xml::Serialization;
namespace MeXgui
{
	namespace core
	{
		namespace util
		{

			OverlappingSectionException::OverlappingSectionException() : Exception("Sections overlap")
			{
			}

			int CutSection::CompareTo(CutSection *other)
			{
				if (other == this)
					return 0;
				if (other->startFrame == this->startFrame)
					throw new OverlappingSectionException();

				if (other->startFrame < this->startFrame)
				{
					if (other->endFrame < this->startFrame)
						return 1;
					throw new OverlappingSectionException();
				}

				return 0 - other->compare(this);

			}

			void Cuts::AdaptToFramerate(double newFramerate)
			{
				double ratio = newFramerate / Framerate;
				for (QVector<CutSection*>::const_iterator c = cuts.begin(); c != cuts.end(); ++c)
				{
					(*c)->startFrame = static_cast<int>(static_cast<double>((*c)->startFrame) * ratio);
					(*c)->endFrame = static_cast<int>(static_cast<double>((*c)->endFrame) * ratio);
				}
				Framerate = newFramerate;
			}

			const int &Cuts::getMinLength() const
			{
				if (cuts.empty())
					throw std::exception("Must have at least one cut");
				return cuts[cuts.size() - 1]->endFrame;
			}

			Cuts::Cuts()
			{
				InitializeInstanceFields();
			}

			const QVector<CutSection*> &Cuts::getAllCuts() const
			{
				return cuts;
			}

			void Cuts::setAllCuts(const QVector<CutSection*> &value)
			{
				cuts = value;
			}

			Cuts::Cuts(TransitionStyle style)
			{
				InitializeInstanceFields();
				this->Style = style;
			}

			bool Cuts::addSection(CutSection *cut)
			{
				QVector<CutSection*> old = QVector<CutSection*>(cuts);
				cuts.push_back(cut);
				try
				{
					try
					{
						std::sort(cuts.begin(), cuts.end());
					}
					catch (InvalidOperationException *e)
					{
						throw e->InnerException;
					}
				}
				catch (OverlappingSectionException *e1)
				{
					cuts = old;
					return false;
				}

				return true;
			}

			void Cuts::Clear()
			{
				cuts.clear();
			}

			const quint64 &Cuts::getTotalFrames() const
			{
				quint64 ans = 0;
				for (QVector<CutSection*>::const_iterator c = getAllCuts().begin(); c != getAllCuts().end(); ++c)
					ans += static_cast<quint64>((*c)->endFrame - (*c)->startFrame);
				return ans;
			}

			MeXgui::core::util::Cuts *Cuts::clone()
			{
				Cuts *copy = new Cuts(Style);
				copy->cuts = QVector<CutSection*>(cuts);
				copy->Framerate = this->Framerate;
				return copy;
			}

			void Cuts::remove(CutSection *cutSection)
			{
				cuts.Remove(cutSection);
			}

			void Cuts::InitializeInstanceFields()
			{
				cuts = QVector<CutSection*>();
				Framerate = -1;
				Style = FADE;
			}

			void FilmCutter::WriteCutsToFile(const QString &filename, Cuts *cuts)
			{
				assert(cuts->getAllCuts().size() > 0);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (Stream s = File.Open(filename, FileMode.Create))
				Stream *s = File->Open(filename, FileMode::Create);
				try
				{
					XmlSerializer *serializer = new XmlSerializer(Cuts::typeid);
					serializer->Serialize(s, cuts);
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (s != 0)
						s.Dispose();
				}
			}

			MeXgui::core::util::Cuts *FilmCutter::ReadCutsFromFile(const QString &filename)
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (Stream s = File.OpenRead(filename))
				Stream *s = File::OpenRead(filename);
				try
				{
					XmlSerializer *deserializer = new XmlSerializer(Cuts::typeid);
					return static_cast<Cuts*>(deserializer->Deserialize(s));
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (s != 0)
						s.Dispose();
				}
			}

			QString FilmCutter::GetCutsScript(Cuts *cuts, bool isAudio)
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (StringWriter s = new StringWriter())
				StringWriter *s = new StringWriter();
				try
				{
					s->WriteLine();
					s->WriteLine("__film = last");

					if (isAudio) // We need to generate a fake video track to add
					{
						s->WriteLine("__just_audio = __film");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						s->WriteLine("__blank = BlankClip(length={0}, fps={1})", cuts->getMinLength(), Math::Round(cuts->Framerate, 3)->ToString(new CultureInfo("en-us")));
						s->WriteLine("__film = AudioDub(__blank, __film)");
					}

					int counter = 0;
					for (QVector<CutSection*>::const_iterator c = cuts->getAllCuts().begin(); c != cuts->getAllCuts().end(); ++c)
					{
						s->WriteLine("__t{0} = __film.trim({1}, {2})", counter, (*c)->startFrame, (*c)->endFrame);
						counter++;
					}

					if (cuts->Style == NO_TRANSITION)
					{
						for (int i = 0; i < counter; i++)
						{
							s->Write("__t{0} ", i);
							if (i < counter - 1)
								s->Write("++ ");
						}
						s->WriteLine();
					}
					else if (cuts->Style == FADE)
					{
						for (int i = 0; i < counter; i++)
						{
							bool first = (i == 0);
							bool last = (i == (counter - 1));
							s->Write(addFades("__t" + i, first, last, isAudio));
							if (!last)
								s->Write(" ++ ");
						}
						s->WriteLine();
					}
					else if (cuts->Style == DISSOLVE && counter != 0)
					{
						QString scriptlet = "__t" + (counter - 1);
						for (int i = counter - 2; i >= 0; i--)
						{
							scriptlet = QString::Format("__t{0}.Dissolve({1}, 60)", i, scriptlet);
						}
						s->WriteLine(scriptlet);
					}

					if (isAudio) // We now need to remove the dummy audio track
					{
						// It will try to take the video from __just_audio, but there isn't any, so it just takes 
						// the audio stream from last
						s->WriteLine("AudioDubEx(__just_audio, last)");
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return s->ToString();
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (s != 0)
						s.Dispose();
				}
			}

			void FilmCutter::WriteCutsToScript(const QString &script, Cuts *cuts, bool isAudio)
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (TextWriter s = new StreamWriter(File.Open(script, FileMode.Append)))
				TextWriter *s = new StreamWriter(File->Open(script, FileMode->Append));
				try
				{
					s->WriteLine(GetCutsScript(cuts, isAudio));
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (s != 0)
						s.Dispose();
				}
			}

			QString FilmCutter::addFades(const QString &p, bool first, bool last, bool isAudio)
			{
				if (first && last)
					return p;
				if (isAudio)
				{
					if (!first && !last)
						return QString::Format("FadeIO0(FadeIO0({0}, 10, fps=AudioRate(__just_audio)), 10, fps=AudioRate(__just_audio))", p);
					if (first)
						return QString::Format("FadeOut0(FadeOut0({0}, 10, fps=AudioRate(__just_audio)), 10, fps=AudioRate(__just_audio))", p);
					if (last)
						return QString::Format("FadeIn0(FadeIn0({0}, 10, fps=AudioRate(__just_audio)), 10, fps=AudioRate(__just_audio))", p);
				}
				else
				{
					if (!first && !last)
						return QString::Format("FadeIO0({0}, 10, fps=AudioRate(__film))", p);
					if (first)
						return QString::Format("FadeOut0({0}, 10, fps=AudioRate(__film))", p);
					if (last)
						return QString::Format("FadeIn0({0}, 10, fps=AudioRate(__film))", p);
				}
				assert(false);
				return 0;
			}
		}
	}
}
