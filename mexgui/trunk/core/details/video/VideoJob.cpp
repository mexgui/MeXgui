#include "VideoJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace MeGUI::core::util;

namespace MeGUI
{

	VideoJob::VideoJob() : Job()
	{
		InitializeInstanceFields();
	}

	const Zone &VideoJob::getZones() const
	{
		return zones;
	}

	void VideoJob::setZones(const Zone &value[])
	{
		zones = value;
	}

	VideoJob::VideoJob(const std::string &input, const std::string &output, VideoCodecSettings *settings, Nullable<Dar> dar, Zone zones[]) : Job(input, output)
	{
		InitializeInstanceFields();
		setSettings(settings);
		setDAR(dar);
		setZones(zones);
	}

	const Nullable<Dar> &VideoJob::getDAR() const
	{
		return dar;
	}

	void VideoJob::setDAR(const Nullable<Dar> &value)
	{
		dar = value;
	}

	const VideoCodecSettings &VideoJob::getSettings() const
	{
		return settings;
	}

	void VideoJob::setSettings(const VideoCodecSettings &value)
	{
		settings = value;
	}

	const std::string &VideoJob::getCodecString() const
	{
		return settings->getSettingsID();
	}

	const std::string &VideoJob::getEncodingMode() const
	{
		return "video";
	}

	void VideoJob::InitializeInstanceFields()
	{
		zones = new Zone[] { };
	}
}
