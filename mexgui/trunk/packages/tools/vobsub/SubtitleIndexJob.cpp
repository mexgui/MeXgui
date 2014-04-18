#include "SubtitleIndexJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	SubtitleIndexJob::SubtitleIndexJob() : Job()
	{
		indexAllTracks = true;
		trackIDs = std::vector<int>();
		pgc = 1;
	}

	SubtitleIndexJob::SubtitleIndexJob(const std::string &input, const std::string &output, bool indexAllTracks, std::vector<int> &trackIDs, int pgc)
	{
		Input = input;
		Output = output;
		setIndexAllTracks(indexAllTracks);
		setTrackIDs(trackIDs);
		setPGC(pgc);
	}

	const bool &SubtitleIndexJob::getIndexAllTracks() const
	{
		return indexAllTracks;
	}

	void SubtitleIndexJob::setIndexAllTracks(const bool &value)
	{
		indexAllTracks = value;
	}

	const std::vector<int> &SubtitleIndexJob::getTrackIDs() const
	{
		return trackIDs;
	}

	void SubtitleIndexJob::setTrackIDs(const std::vector<int> &value)
	{
		trackIDs = value;
	}

	const int &SubtitleIndexJob::getPGC() const
	{
		return pgc;
	}

	void SubtitleIndexJob::setPGC(const int &value)
	{
		pgc = value;
	}

	const std::string &SubtitleIndexJob::getCodecString() const
	{
		return "";
	}

	const std::string &SubtitleIndexJob::getEncodingMode() const
	{
		return "sub";
	}
}
