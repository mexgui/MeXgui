#include "OneClickAudioTrack.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;

namespace MeGUI
{

	OneClickAudioTrack::OneClickAudioTrack()
	{
	}

	OneClickAudioTrack::OneClickAudioTrack(MeGUI::AudioJob *oAudioJob, MuxStream *oMuxStream, MeGUI::AudioTrackInfo *oAudioTrackInfo, bool bMKVTrack)
	{
		_audioJob = oAudioJob;
		_directMuxAudio = oMuxStream;
		_audioTrackInfo = oAudioTrackInfo;
		if (_audioTrackInfo != 0)
			_audioTrackInfo->setExtractMKVTrack(bMKVTrack);
	}

	const MeGUI::AudioJob &OneClickAudioTrack::getAudioJob() const
	{
		return _audioJob;
	}

	void OneClickAudioTrack::setAudioJob(const MeGUI::AudioJob &value)
	{
		_audioJob = value;
	}

	const MeGUI::core::details::MuxStream &OneClickAudioTrack::getDirectMuxAudio() const
	{
		return _directMuxAudio;
	}

	void OneClickAudioTrack::setDirectMuxAudio(const MuxStream &value)
	{
		_directMuxAudio = value;
	}

	const MeGUI::AudioTrackInfo &OneClickAudioTrack::getAudioTrackInfo() const
	{
		return _audioTrackInfo;
	}

	void OneClickAudioTrack::setAudioTrackInfo(const MeGUI::AudioTrackInfo &value)
	{
		_audioTrackInfo = value;
	}
}
