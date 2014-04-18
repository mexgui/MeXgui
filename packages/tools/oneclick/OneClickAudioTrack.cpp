#include "OneClickAudioTrack.h"




//using namespace System::Collections::Generic;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

	OneClickAudioTrack::OneClickAudioTrack()
	{
	}

	OneClickAudioTrack::OneClickAudioTrack(MeXgui::AudioJob *oAudioJob, MuxStream *oMuxStream, MeXgui::AudioTrackInfo *oAudioTrackInfo, bool bMKVTrack)
	{
		_audioJob = oAudioJob;
		_directMuxAudio = oMuxStream;
		_audioTrackInfo = oAudioTrackInfo;
		if (_audioTrackInfo != 0)
			_audioTrackInfo->setExtractMKVTrack(bMKVTrack);
	}

	const MeXgui::AudioJob &OneClickAudioTrack::getAudioJob() const
	{
		return _audioJob;
	}

	void OneClickAudioTrack::setAudioJob(const MeXgui::AudioJob &value)
	{
		_audioJob = value;
	}

	const MeXgui::core::details::MuxStream &OneClickAudioTrack::getDirectMuxAudio() const
	{
		return _directMuxAudio;
	}

	void OneClickAudioTrack::setDirectMuxAudio(const MuxStream &value)
	{
		_directMuxAudio = value;
	}

	const MeXgui::AudioTrackInfo &OneClickAudioTrack::getAudioTrackInfo() const
	{
		return _audioTrackInfo;
	}

	void OneClickAudioTrack::setAudioTrackInfo(const MeXgui::AudioTrackInfo &value)
	{
		_audioTrackInfo = value;
	}
}
