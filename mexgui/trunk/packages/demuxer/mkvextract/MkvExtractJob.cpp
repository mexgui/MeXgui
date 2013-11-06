#include "MkvExtractJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{

	MkvExtractJob::MkvExtractJob()
	{
	}

	MkvExtractJob::MkvExtractJob(const std::string &strInput, const std::string &strOutputPath, std::vector<TrackInfo*> &oTracks) : Job(strInput, 0)
	{
		this->_oTracks = oTracks;
		this->_strOutputPath = strOutputPath;
	}

	MkvExtractJob::MkvExtractJob(const std::string &strInput, const std::string &strOutputPath, std::vector<AudioTrackInfo*> &oTracks) : Job(strInput, 0)
	{
		this->_oTracks = std::vector<TrackInfo*>();
		for (std::vector<AudioTrackInfo*>::const_iterator oInfo = oTracks.begin(); oInfo != oTracks.end(); ++oInfo)
			this->_oTracks.push_back(static_cast<TrackInfo*>(*oInfo));
		this->_strOutputPath = strOutputPath;
	}

	const std::string &MkvExtractJob::getCodecString() const
	{
		return "mkvextract";
	}

	const std::string &MkvExtractJob::getEncodingMode() const
	{
		return "ext";
	}

	const std::vector<TrackInfo*> &MkvExtractJob::getMkvTracks() const
	{
		return _oTracks;
	}

	void MkvExtractJob::setMkvTracks(const std::vector<TrackInfo*> &value)
	{
		_oTracks = value;
	}

	const std::string &MkvExtractJob::getOutputPath() const
	{
		return _strOutputPath;
	}

	void MkvExtractJob::setOutputPath(const std::string &value)
	{
		_strOutputPath = value;
	}
}
