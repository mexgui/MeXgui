#include "VideoJob.h"



using namespace MeXgui::core::util;

namespace MeXgui
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

	VideoJob::VideoJob(const QString &input, const QString &output, VideoCodecSettings *settings, Nullable<Dar> dar, Zone zones[]) : Job(input, output)
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

	const QString &VideoJob::getCodecString() const
	{
		return settings->getSettingsID();
	}

	const QString &VideoJob::getEncodingMode() const
	{
		return "video";
	}

	void VideoJob::InitializeInstanceFields()
	{
		zones = new Zone[] { };
	}
}
