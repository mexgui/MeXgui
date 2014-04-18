#include "MuxSettings.h"




//using namespace System::Collections::Generic;
using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

	MuxSettings::MuxSettings()
	{
		audioStreams = QVector<MuxStream*>();
		subtitleStreams = QVector<MuxStream*>();
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

	const QString &MuxSettings::getMuxedInput() const
	{
		return muxedInput;
	}

	void MuxSettings::setMuxedInput(const QString &value)
	{
		muxedInput = value;
	}

	const QString &MuxSettings::getMuxedOutput() const
	{
		return muxedOutput;
	}

	void MuxSettings::setMuxedOutput(const QString &value)
	{
		muxedOutput = value;
	}

	const QString &MuxSettings::getVideoInput() const
	{
		return videoInput;
	}

	void MuxSettings::setVideoInput(const QString &value)
	{
		videoInput = value;
	}

	const QVector<MuxStream*> &MuxSettings::getAudioStreams() const
	{
		return audioStreams;
	}

	void MuxSettings::setAudioStreams(const QVector<MuxStream*> &value)
	{
		audioStreams = value;
	}

	const QVector<MuxStream*> &MuxSettings::getSubtitleStreams() const
	{
		return subtitleStreams;
	}

	void MuxSettings::setSubtitleStreams(const QVector<MuxStream*> &value)
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

	const QString &MuxSettings::getChapterFile() const
	{
		return chapterFile;
	}

	void MuxSettings::setChapterFile(const QString &value)
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

	const QString &MuxSettings::getDeviceType() const
	{
		return deviceType;
	}

	void MuxSettings::setDeviceType(const QString &value)
	{
		deviceType = value;
	}

	const QString &MuxSettings::getVideoName() const
	{
		return videoName;
	}

	void MuxSettings::setVideoName(const QString &value)
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
