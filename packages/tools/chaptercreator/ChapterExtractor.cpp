#include "ChapterExtractor.h"




//using namespace System::Collections::Generic;

//using namespace System::Linq;

//using namespace System::Text;

//using namespace System::Security::Cryptography;

namespace MeXgui
{

	const bool &ChapterExtractor::getSupportsMultipleStreams() const
	{
		return true;
	}

	QString ChapterExtractor::ComputeMD5Sum(const QString &path)
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		return BitConverter->ToString((new MD5CryptoServiceProvider())->ComputeHash(System::IO::File::ReadAllBytes(path)))->Replace("-", "")->ToLower(System::Globalization::CultureInfo::InvariantCulture);
	}

	void ChapterExtractor::OnExtractionComplete()
	{
		ExtractionComplete(this, EventArgs::Empty);
	}

	void ChapterExtractor::OnStreamDetected(ChapterInfo *pgc)
	{
		StreamDetected(this, new ProgramChainArg(new object[] {ProgramChain = pgc}));
	}

	void ChapterExtractor::OnChaptersLoaded(ChapterInfo *pgc)
	{
		ChaptersLoaded(this, new ProgramChainArg(new object[] {ProgramChain = pgc}));
	}

	const ChapterInfo &ProgramChainArg::getProgramChain() const
	{
		return privateProgramChain;
	}

	void ProgramChainArg::setProgramChain(const ChapterInfo &value)
	{
		privateProgramChain = value;
	}
}
