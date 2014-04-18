#include "SubtitleIndexJob.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

	SubtitleIndexJob::SubtitleIndexJob() : Job()
	{
		indexAllTracks = true;
		trackIDs = QVector<int>();
		pgc = 1;
	}

	SubtitleIndexJob::SubtitleIndexJob(const QString &input, const QString &output, bool indexAllTracks, QVector<int> &trackIDs, int pgc)
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

	const QVector<int> &SubtitleIndexJob::getTrackIDs() const
	{
		return trackIDs;
	}

	void SubtitleIndexJob::setTrackIDs(const QVector<int> &value)
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

	const QString &SubtitleIndexJob::getCodecString() const
	{
		return "";
	}

	const QString &SubtitleIndexJob::getEncodingMode() const
	{
		return "sub";
	}
}
