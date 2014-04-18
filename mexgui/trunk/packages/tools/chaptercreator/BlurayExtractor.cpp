#include "BlurayExtractor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace MeGUI
{

	const std::string &BlurayExtractor::getExtensions() const
	{
		return new std::string[] { };
	}

	std::vector<ChapterInfo*> BlurayExtractor::GetStreams(const std::string &location)
	{
		std::vector<ChapterInfo*> mpls = std::vector<ChapterInfo*>();
		std::string path = Path::Combine(Path::Combine(location, "BDMV"), "PLAYLIST");
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
