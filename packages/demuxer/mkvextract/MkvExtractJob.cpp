#include "MkvExtractJob.h"




//using namespace System::Collections::Generic;

//using namespace System::Xml::Serialization;

namespace MeXgui
{

	MkvExtractJob::MkvExtractJob()
	{
	}

	MkvExtractJob::MkvExtractJob(const QString &strInput, const QString &strOutputPath, QVector<TrackInfo*> &oTracks) : Job(strInput, 0)
	{
		this->_oTracks = oTracks;
		this->_strOutputPath = strOutputPath;
	}

	MkvExtractJob::MkvExtractJob(const QString &strInput, const QString &strOutputPath, QVector<AudioTrackInfo*> &oTracks) : Job(strInput, 0)
	{
		this->_oTracks = QVector<TrackInfo*>();
		for (QVector<AudioTrackInfo*>::const_iterator oInfo = oTracks.begin(); oInfo != oTracks.end(); ++oInfo)
			this->_oTracks.push_back(static_cast<TrackInfo*>(*oInfo));
		this->_strOutputPath = strOutputPath;
	}

	const QString &MkvExtractJob::getCodecString() const
	{
		return "mkvextract";
	}

	const QString &MkvExtractJob::getEncodingMode() const
	{
		return "ext";
	}

	const QVector<TrackInfo*> &MkvExtractJob::getMkvTracks() const
	{
		return _oTracks;
	}

	void MkvExtractJob::setMkvTracks(const QVector<TrackInfo*> &value)
	{
		_oTracks = value;
	}

	const QString &MkvExtractJob::getOutputPath() const
	{
		return _strOutputPath;
	}

	void MkvExtractJob::setOutputPath(const QString &value)
	{
		_strOutputPath = value;
	}
}
