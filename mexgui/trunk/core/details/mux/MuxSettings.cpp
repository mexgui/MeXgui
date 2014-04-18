#include "MuxSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{

	MuxSettings::MuxSettings()
	{
		audioStreams = std::vector<MuxStream*>();
		subtitleStreams = std::vector<MuxStream*>();
		framerate = 0.0;
		muxedInput = "";
		chapterFile = "";
		videoName = "";
		videoInput = "";
		muxedOutput = "";
		deviceType = "";
		splitSize = Nullable<FileSize>();
		muxAll = false;
	}

	const std::string &MuxSettings::getMuxedInput() const
	{
		return muxedInput;
	}

	void MuxSettings::setMuxedInput(const std::string &value)
	{
		muxedInput = value;
	}

	const std::string &MuxSettings::getMuxedOutput() const
	{
		return muxedOutput;
	}

	void MuxSettings::setMuxedOutput(const std::string &value)
	{
		muxedOutput = value;
	}

	const std::string &MuxSettings::getVideoInput() const
	{
		return videoInput;
	}

	void MuxSettings::setVideoInput(const std::string &value)
	{
		videoInput = value;
	}

	const std::vector<MuxStream*> &MuxSettings::getAudioStreams() const
	{
		return audioStreams;
	}

	void MuxSettings::setAudioStreams(const std::vector<MuxStream*> &value)
	{
		audioStreams = value;
	}

	const std::vector<MuxStream*> &MuxSettings::getSubtitleStreams() const
	{
		return subtitleStreams;
	}

	void MuxSettings::setSubtitleStreams(const std::vector<MuxStream*> &value)
	{
		subtitleStreams = value;
	}

	const Nullable<decimal> &MuxSettings::getFramerate() const
	{
		return framerate;
	}

	void MuxSettings::setFramerate(const Nullable<decimal> &value)
	{
		framerate = value;
	}

	const std::string &MuxSettings::getChapterFile() const
	{
		return chapterFile;
	}

	void MuxSettings::setChapterFile(const std::string &value)
	{
		chapterFile = value;
	}

	const Nullable<FileSize> &MuxSettings::getSplitSize() const
	{
		return splitSize;
	}

	void MuxSettings::setSplitSize(const Nullable<FileSize> &value)
	{
		splitSize = value;
	}

	const Nullable<Dar> &MuxSettings::getDAR() const
	{
		return dar;
	}

	void MuxSettings::setDAR(const Nullable<Dar> &value)
	{
		dar = value;
	}

	const std::string &MuxSettings::getDeviceType() const
	{
		return deviceType;
	}

	void MuxSettings::setDeviceType(const std::string &value)
	{
		deviceType = value;
	}

	const std::string &MuxSettings::getVideoName() const
	{
		return videoName;
	}

	void MuxSettings::setVideoName(const std::string &value)
	{
		videoName = value;
	}

	const bool &MuxSettings::getMuxAll() const
	{
		return muxAll;
	}

	void MuxSettings::setMuxAll(const bool &value)
	{
		muxAll = value;
	}
}
