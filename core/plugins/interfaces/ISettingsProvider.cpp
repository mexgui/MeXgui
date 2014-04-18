#include "ISettingsProvider.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;


using namespace MeXgui::core::details::video;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::video::x264;
using namespace MeXgui::packages::video::xvid;
using namespace MeXgui::packages::audio::naac;
using namespace MeXgui::packages::audio::ffac3;
using namespace MeXgui::packages::audio::ffmp2;
using namespace MeXgui::packages::audio::lame;
using namespace MeXgui::packages::audio::vorbis;
using namespace MeXgui::packages::audio::aften;
using namespace MeXgui::packages::audio::opus;
using namespace MeXgui::packages::audio::qaac;

namespace MeXgui
{

	const QString &VideoInfo::getVideoInput() const
	{
		return videoInput;
	}

	void VideoInfo::setVideoInput(const QString &value)
	{
		videoInput = value;
		VideoInputChanged(this, value);
	}

	const QString &VideoInfo::getVideoOutput() const
	{
		return videoOutput;
	}

	void VideoInfo::setVideoOutput(const QString &value)
	{
		videoOutput = value;
		VideoOutputChanged(this, value);
	}

	const Nullable<Dar> &VideoInfo::getDAR() const
	{
		return dar;
	}

	void VideoInfo::setDAR(const Nullable<Dar> &value)
	{
		dar = value;
	}

	const int &VideoInfo::getIntroEndFrame() const
	{
		return introEndFrame;
	}

	void VideoInfo::setIntroEndFrame(const int &value)
	{
		introEndFrame = value;
	}

	const int &VideoInfo::getCreditsStartFrame() const
	{
		return creditsStartFrame;
	}

	void VideoInfo::setCreditsStartFrame(const int &value)
	{
		creditsStartFrame = value;
	}

	const Zone &VideoInfo::getZones() const
	{
		return zones;
	}

	void VideoInfo::setZones(const Zone &value[])
	{
		zones = (value != 0) ? value : new Zone[0];
	}

	VideoInfo::VideoInfo(const QString &videoInput, const QString &videoOutput, int darX, int darY, int creditsStartFrame, int introEndFrame, Zone zones[])
	{
		InitializeInstanceFields();
		this->videoInput = videoInput;
		this->videoOutput = videoOutput;
		this->creditsStartFrame = creditsStartFrame;
		this->introEndFrame = introEndFrame;
		this->zones = zones;
	}

	VideoInfo::VideoInfo()
	{
		InitializeInstanceFields();
	}

	VideoInfo *VideoInfo::Clone()
	{
		return static_cast<VideoInfo*>(this->MemberwiseClone());
	}

	void VideoInfo::InitializeInstanceFields()
	{
		dar = Nullable<Dar>();
	}
}
