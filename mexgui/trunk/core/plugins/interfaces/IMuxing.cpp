#include "IMuxing.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::util;

namespace MeGUI
{

	VideoStream::VideoStream()
	{
		InitializeInstanceFields();
		input = "";
		numberOfFrames = 0;
	}

	const std::string &VideoStream::getOutput() const
	{
		return output;
	}

	void VideoStream::setOutput(const std::string &value)
	{
		output = value;
	}

	const std::string &VideoStream::getInput() const
	{
		return input;
	}

	void VideoStream::setInput(const std::string &value)
	{
		input = value;
	}

	const Nullable<Dar> &VideoStream::getDAR() const
	{
		return dar;
	}

	void VideoStream::setDAR(const Nullable<Dar> &value)
	{
		dar = value;
	}

	const unsigned long long &VideoStream::getNumberOfFrames() const
	{
		return numberOfFrames;
	}

	void VideoStream::setNumberOfFrames(const unsigned long long &value)
	{
		numberOfFrames = value;
	}

	const decimal &VideoStream::getFramerate() const
	{
		return framerate;
	}

	void VideoStream::setFramerate(const decimal &value)
	{
		framerate = value;
	}

	const MuxableType &VideoStream::getVideoType() const
	{
		return videoType;
	}

	void VideoStream::setVideoType(const MuxableType &value)
	{
		videoType = value;
	}

	const VideoCodecSettings &VideoStream::getSettings() const
	{
		return settings;
	}

	void VideoStream::setSettings(const VideoCodecSettings &value)
	{
		settings = value;
	}

	void VideoStream::InitializeInstanceFields()
	{
		dar = Nullable<Dar>();
	}
}
