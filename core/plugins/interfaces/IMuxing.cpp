#include "IMuxing.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
using namespace MeXgui::core::util;

namespace MeXgui
{

	VideoStream::VideoStream()
	{
		InitializeInstanceFields();
		input = "";
		numberOfFrames = 0;
	}

	const QString &VideoStream::getOutput() const
	{
		return output;
	}

	void VideoStream::setOutput(const QString &value)
	{
		output = value;
	}

	const QString &VideoStream::getInput() const
	{
		return input;
	}

	void VideoStream::setInput(const QString &value)
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

	const quint64 &VideoStream::getNumberOfFrames() const
	{
		return numberOfFrames;
	}

	void VideoStream::setNumberOfFrames(const quint64 &value)
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
