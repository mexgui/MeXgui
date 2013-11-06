#include "ISettingsProvider.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details::video;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::video::x264;
using namespace MeGUI::packages::video::xvid;
using namespace MeGUI::packages::audio::naac;
using namespace MeGUI::packages::audio::ffac3;
using namespace MeGUI::packages::audio::ffmp2;
using namespace MeGUI::packages::audio::lame;
using namespace MeGUI::packages::audio::vorbis;
using namespace MeGUI::packages::audio::aften;
using namespace MeGUI::packages::audio::opus;
using namespace MeGUI::packages::audio::qaac;

namespace MeGUI
{

	const std::string &VideoInfo::getVideoInput() const
	{
		return videoInput;
	}

	void VideoInfo::setVideoInput(const std::string &value)
	{
		videoInput = value;
		VideoInputChanged(this, value);
	}

	const std::string &VideoInfo::getVideoOutput() const
	{
		return videoOutput;
	}

	void VideoInfo::setVideoOutput(const std::string &value)
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

	VideoInfo::VideoInfo(const std::string &videoInput, const std::string &videoOutput, int darX, int darY, int creditsStartFrame, int introEndFrame, Zone zones[])
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
