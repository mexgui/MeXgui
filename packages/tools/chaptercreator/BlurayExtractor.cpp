#include "BlurayExtractor.h"




//using namespace System::Collections::Generic;

//using namespace System::Linq;

//using namespace System::Text;



namespace MeXgui
{

	const QString &BlurayExtractor::getExtensions() const
	{
		return new QString[] { };
	}

	QVector<ChapterInfo*> BlurayExtractor::GetStreams(const QString &location)
	{
		QVector<ChapterInfo*> mpls = QVector<ChapterInfo*>();
		QString path = Path::Combine(Path::Combine(location, "BDMV"), "PLAYLIST");
		if (!Directory::Exists(path))
			throw new FileNotFoundException("Could not find PLAYLIST folder on BluRay disc.");

		ChapterExtractor *ex = new BDInfoExtractor();
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		ex->StreamDetected += (sender, args) => OnStreamDetected(args::ProgramChain);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		ex->ChaptersLoaded += (sender, args) => OnChaptersLoaded(args::ProgramChain);

		for (unknown::const_iterator file = Directory::GetFiles(path, "*.mpls").begin(); file != Directory::GetFiles(path, "*.mpls").end(); ++file)
		{
			ChapterInfo *pl = ex->GetStreams(*file)[0];
			pl->setSourceName(Path::GetFileName(*file));
			mpls.push_back(pl);
		}

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		mpls = mpls.OrderByDescending(p => p::Duration)->ToList();
		OnExtractionComplete();
		return mpls;
	}
}
