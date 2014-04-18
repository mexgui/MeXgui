#include "AudioTrack.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{

	const std::string &AudioTrack::getCount() const
	{
		if (this->_Count.empty())
			this->_Count = "";
		return _Count;
	}

	void AudioTrack::setCount(const std::string &value)
	{
		this->_Count = value;
	}

	const std::string &AudioTrack::getStreamCount() const
	{
		if (this->_StreamCount.empty())
			this->_StreamCount = "";
		return _StreamCount;
	}

	void AudioTrack::setStreamCount(const std::string &value)
	{
		this->_StreamCount = value;
	}

	const std::string &AudioTrack::getStreamKind() const
	{
		if (this->_StreamKind.empty())
			this->_StreamKind = "";
		return _StreamKind;
	}

	void AudioTrack::setStreamKind(const std::string &value)
	{
		this->_StreamKind = value;
	}

	const std::string &AudioTrack::getStreamKindString() const
	{
		if (this->_StreamKindString.empty())
			this->_StreamKindString = "";
		return _StreamKindString;
	}

	void AudioTrack::setStreamKindString(const std::string &value)
	{
		this->_StreamKindString = value;
	}

	const std::string &AudioTrack::getStreamKindID() const
	{
		if (this->_StreamKindID.empty())
			this->_StreamKindID = "";
		return _StreamKindID;
	}

	void AudioTrack::setStreamKindID(const std::string &value)
	{
		this->_StreamKindID = value;
	}

	const std::string &AudioTrack::getStreamKindPos() const
	{
		if (this->_StreamKindPos.empty())
			this->_StreamKindPos = "";
		return _StreamKindPos;
	}

	void AudioTrack::setStreamKindPos(const std::string &value)
	{
		this->_StreamKindPos = value;
	}

	const std::string &AudioTrack::getStreamOrder() const
	{
		if (this->_StreamOrder.empty())
			this->_StreamOrder = "";
		return _StreamOrder;
	}

	void AudioTrack::setStreamOrder(const std::string &value)
	{
		this->_StreamOrder = value;
	}

	const std::string &AudioTrack::getInform() const
	{
		if (this->_Inform.empty())
			this->_Inform = "";
		return _Inform;
	}

	void AudioTrack::setInform(const std::string &value)
	{
		this->_Inform = value;
	}

	const std::string &AudioTrack::getID() const
	{
		if (this->_ID.empty())
			this->_ID = "";
		return _ID;
	}

	void AudioTrack::setID(const std::string &value)
	{
		this->_ID = value;
	}

	const std::string &AudioTrack::getIDString() const
	{
		if (this->_IDString.empty())
			this->_IDString = "";
		return _IDString;
	}

	void AudioTrack::setIDString(const std::string &value)
	{
		this->_IDString = value;
	}

	const std::string &AudioTrack::getUniqueID() const
	{
		if (this->_UniqueID.empty())
			this->_UniqueID = "";
		return _UniqueID;
	}

	void AudioTrack::setUniqueID(const std::string &value)
	{
		this->_UniqueID = value;
	}

	const std::string &AudioTrack::getMenuID() const
	{
		if (this->_MenuID.empty())
			this->_MenuID = "";
		return _MenuID;
	}

	void AudioTrack::setMenuID(const std::string &value)
	{
		this->_MenuID = value;
	}

	const std::string &AudioTrack::getMenuIDString() const
	{
		if (this->_MenuIDString.empty())
			this->_MenuIDString = "";
		return _MenuIDString;
	}

	void AudioTrack::setMenuIDString(const std::string &value)
	{
		this->_MenuIDString = value;
	}

	const std::string &AudioTrack::getFormat() const
	{
		if (this->_Format.empty())
			this->_Format = "";
		return _Format;
	}

	void AudioTrack::setFormat(const std::string &value)
	{
		this->_Format = value;
	}

	const std::string &AudioTrack::getFormatInfo() const
	{
		if (this->_FormatInfo.empty())
			this->_FormatInfo = "";
		return _FormatInfo;
	}

	void AudioTrack::setFormatInfo(const std::string &value)
	{
		this->_FormatInfo = value;
	}

	const std::string &AudioTrack::getFormatUrl() const
	{
		if (this->_FormatUrl.empty())
			this->_FormatUrl = "";
		return _FormatUrl;
	}

	void AudioTrack::setFormatUrl(const std::string &value)
	{
		this->_FormatUrl = value;
	}

	const std::string &AudioTrack::getFormatVersion() const
	{
		if (this->_FormatVersion.empty())
			this->_FormatVersion = "";
		return _FormatVersion;
	}

	void AudioTrack::setFormatVersion(const std::string &value)
	{
		this->_FormatVersion = value;
	}

	const std::string &AudioTrack::getFormatProfile() const
	{
		if (this->_FormatProfile.empty())
			this->_FormatProfile = "";
		return _FormatProfile;
	}

	void AudioTrack::setFormatProfile(const std::string &value)
	{
		this->_FormatProfile = value;
	}

	const std::string &AudioTrack::getFormatSettings() const
	{
		if (this->_FormatSettings.empty())
			this->_FormatSettings = "";
		return _FormatSettings;
	}

	void AudioTrack::setFormatSettings(const std::string &value)
	{
		this->_FormatSettings = value;
	}

	const std::string &AudioTrack::getFormatSettingsSBR() const
	{
		if (this->_FormatSettingsSBR.empty())
			this->_FormatSettingsSBR = "";
		return _FormatSettingsSBR;
	}

	void AudioTrack::setFormatSettingsSBR(const std::string &value)
	{
		this->_FormatSettingsSBR = value;
	}

	const std::string &AudioTrack::getFormatSettingsSBRString() const
	{
		if (this->_FormatSettingsSBRString.empty())
			this->_FormatSettingsSBRString = "";
		return _FormatSettingsSBRString;
	}

	void AudioTrack::setFormatSettingsSBRString(const std::string &value)
	{
		this->_FormatSettingsSBRString = value;
	}

	const std::string &AudioTrack::getFormatSettingsPS() const
	{
		if (this->_FormatSettingsPS.empty())
			this->_FormatSettingsPS = "";
		return _FormatSettingsPS;
	}

	void AudioTrack::setFormatSettingsPS(const std::string &value)
	{
		this->_FormatSettingsPS = value;
	}

	const std::string &AudioTrack::getFormatSettingsPSString() const
	{
		if (this->_FormatSettingsPSString.empty())
			this->_FormatSettingsPSString = "";
		return _FormatSettingsPSString;
	}

	void AudioTrack::setFormatSettingsPSString(const std::string &value)
	{
		this->_FormatSettingsPSString = value;
	}

	const std::string &AudioTrack::getFormatSettingsFloor() const
	{
		if (this->_FormatSettingsFloor.empty())
			this->_FormatSettingsFloor = "";
		return _FormatSettingsFloor;
	}

	void AudioTrack::setFormatSettingsFloor(const std::string &value)
	{
		this->_FormatSettingsFloor = value;
	}

	const std::string &AudioTrack::getFormatSettingsFirm() const
	{
		if (this->_FormatSettingsFirm.empty())
			this->_FormatSettingsFirm = "";
		return _FormatSettingsFirm;
	}

	void AudioTrack::setFormatSettingsFirm(const std::string &value)
	{
		this->_FormatSettingsFirm = value;
	}

	const std::string &AudioTrack::getFormatSettingsEndianness() const
	{
		if (this->_FormatSettingsEndianness.empty())
			this->_FormatSettingsEndianness = "";
		return _FormatSettingsEndianness;
	}

	void AudioTrack::setFormatSettingsEndianness(const std::string &value)
	{
		this->_FormatSettingsEndianness = value;
	}

	const std::string &AudioTrack::getFormatSettingsSign() const
	{
		if (this->_FormatSettingsSign.empty())
			this->_FormatSettingsSign = "";
		return _FormatSettingsSign;
	}

	void AudioTrack::setFormatSettingsSign(const std::string &value)
	{
		this->_FormatSettingsSign = value;
	}

	const std::string &AudioTrack::getFormatSettingsLaw() const
	{
		if (this->_FormatSettingsLaw.empty())
			this->_FormatSettingsLaw = "";
		return _FormatSettingsLaw;
	}

	void AudioTrack::setFormatSettingsLaw(const std::string &value)
	{
		this->_FormatSettingsLaw = value;
	}

	const std::string &AudioTrack::getFormatSettingsITU() const
	{
		if (this->_FormatSettingsITU.empty())
			this->_FormatSettingsITU = "";
		return _FormatSettingsITU;
	}

	void AudioTrack::setFormatSettingsITU(const std::string &value)
	{
		this->_FormatSettingsITU = value;
	}

	const std::string &AudioTrack::getMuxingMode() const
	{
		if (this->_MuxingMode.empty())
			this->_MuxingMode = "";
		return _MuxingMode;
	}

	void AudioTrack::setMuxingMode(const std::string &value)
	{
		this->_MuxingMode = value;
	}

	const std::string &AudioTrack::getCodecID() const
	{
		if (this->_CodecID.empty())
			this->_CodecID = "";
		return _CodecID;
	}

	void AudioTrack::setCodecID(const std::string &value)
	{
		this->_CodecID = value;
	}

	const std::string &AudioTrack::getCodecIDInfo() const
	{
		if (this->_CodecIDInfo.empty())
			this->_CodecIDInfo = "";
		return _CodecIDInfo;
	}

	void AudioTrack::setCodecIDInfo(const std::string &value)
	{
		this->_CodecIDInfo = value;
	}

	const std::string &AudioTrack::getCodecIDHint() const
	{
		if (this->_CodecIDHint.empty())
			this->_CodecIDHint = "";
		return _CodecIDHint;
	}

	void AudioTrack::setCodecIDHint(const std::string &value)
	{
		this->_CodecIDHint = value;
	}

	const std::string &AudioTrack::getCodecIDUrl() const
	{
		if (this->_CodecIDUrl.empty())
			this->_CodecIDUrl = "";
		return _CodecIDUrl;
	}

	void AudioTrack::setCodecIDUrl(const std::string &value)
	{
		this->_CodecIDUrl = value;
	}

	const std::string &AudioTrack::getCodecIDDescription() const
	{
		if (this->_CodecIDDescription.empty())
			this->_CodecIDDescription = "";
		return _CodecIDDescription;
	}

	void AudioTrack::setCodecIDDescription(const std::string &value)
	{
		this->_CodecIDDescription = value;
	}

	const std::string &AudioTrack::getTitle() const
	{
		if (this->_Title.empty())
			this->_Title = "";
		return _Title;
	}

	void AudioTrack::setTitle(const std::string &value)
	{
		this->_Title = value;
	}

	const std::string &AudioTrack::getBitRate() const
	{
		if (this->_BitRate.empty())
			this->_BitRate = "";
		return _BitRate;
	}

	void AudioTrack::setBitRate(const std::string &value)
	{
		this->_BitRate = value;
	}

	const std::string &AudioTrack::getBitRateString() const
	{
		if (this->_BitRateString.empty())
			this->_BitRateString = "";
		return _BitRateString;
	}

	void AudioTrack::setBitRateString(const std::string &value)
	{
		this->_BitRateString = value;
	}

	const std::string &AudioTrack::getBitRateMode() const
	{
		if (this->_BitRateMode.empty())
			this->_BitRateMode = "";
		return _BitRateMode;
	}

	void AudioTrack::setBitRateMode(const std::string &value)
	{
		this->_BitRateMode = value;
	}

	const std::string &AudioTrack::getBitRateModeString() const
	{
		if (this->_BitRateModeString.empty())
			this->_BitRateModeString = "";
		return _BitRateModeString;
	}

	void AudioTrack::setBitRateModeString(const std::string &value)
	{
		this->_BitRateModeString = value;
	}

	const std::string &AudioTrack::getBitRateMinimum() const
	{
		if (this->_BitRateMinimum.empty())
			this->_BitRateMinimum = "";
		return _BitRateMinimum;
	}

	void AudioTrack::setBitRateMinimum(const std::string &value)
	{
		this->_BitRateMinimum = value;
	}

	const std::string &AudioTrack::getBitRateMinimumString() const
	{
		if (this->_BitRateMinimumString.empty())
			this->_BitRateMinimumString = "";
		return _BitRateMinimumString;
	}

	void AudioTrack::setBitRateMinimumString(const std::string &value)
	{
		this->_BitRateMinimumString = value;
	}

	const std::string &AudioTrack::getBitRateNominal() const
	{
		if (this->_BitRateNominal.empty())
			this->_BitRateNominal = "";
		return _BitRateNominal;
	}

	void AudioTrack::setBitRateNominal(const std::string &value)
	{
		this->_BitRateNominal = value;
	}

	const std::string &AudioTrack::getBitRateNominalString() const
	{
		if (this->_BitRateNominalString.empty())
			this->_BitRateNominalString = "";
		return _BitRateNominalString;
	}

	void AudioTrack::setBitRateNominalString(const std::string &value)
	{
		this->_BitRateNominalString = value;
	}

	const std::string &AudioTrack::getBitRateMaximum() const
	{
		if (this->_BitRateMaximum.empty())
			this->_BitRateMaximum = "";
		return _BitRateMaximum;
	}

	void AudioTrack::setBitRateMaximum(const std::string &value)
	{
		this->_BitRateMaximum = value;
	}

	const std::string &AudioTrack::getBitRateMaximumString() const
	{
		if (this->_BitRateMaximumString.empty())
			this->_BitRateMaximumString = "";
		return _BitRateMaximumString;
	}

	void AudioTrack::setBitRateMaximumString(const std::string &value)
	{
		this->_BitRateMaximumString = value;
	}

	const std::string &AudioTrack::getChannels() const
	{
		if (this->_Channels.empty())
			this->_Channels = "";
		return _Channels;
	}

	void AudioTrack::setChannels(const std::string &value)
	{
		this->_Channels = value;
	}

	const std::string &AudioTrack::getChannelsString() const
	{
		if (this->_ChannelsString.empty())
			this->_ChannelsString = "";
		return _ChannelsString;
	}

	void AudioTrack::setChannelsString(const std::string &value)
	{
		this->_ChannelsString = value;
	}

	const std::string &AudioTrack::getChannelPositions() const
	{
		if (this->_ChannelPositions.empty())
			this->_ChannelPositions = "";
		return _ChannelPositions;
	}

	void AudioTrack::setChannelPositions(const std::string &value)
	{
		this->_ChannelPositions = value;
	}

	const std::string &AudioTrack::getChannelPositionsString2() const
	{
		if (this->_ChannelPositionsString2.empty())
			this->_ChannelPositionsString2 = "";
		return _ChannelPositionsString2;
	}

	void AudioTrack::setChannelPositionsString2(const std::string &value)
	{
		this->_ChannelPositionsString2 = value;
	}

	const std::string &AudioTrack::getChannelMode() const
	{
		if (this->_ChannelMode.empty())
			this->_ChannelMode = "";
		return _ChannelMode;
	}

	void AudioTrack::setChannelMode(const std::string &value)
	{
		this->_ChannelMode = value;
	}

	const std::string &AudioTrack::getSamplingRate() const
	{
		if (this->_SamplingRate.empty())
			this->_SamplingRate = "";
		return _SamplingRate;
	}

	void AudioTrack::setSamplingRate(const std::string &value)
	{
		this->_SamplingRate = value;
	}

	const std::string &AudioTrack::getSamplingRateString() const
	{
		if (this->_SamplingRateString.empty())
			this->_SamplingRateString = "";
		return _SamplingRateString;
	}

	void AudioTrack::setSamplingRateString(const std::string &value)
	{
		this->_SamplingRateString = value;
	}

	const std::string &AudioTrack::getSamplingCount() const
	{
		if (this->_SamplingCount.empty())
			this->_SamplingCount = "";
		return _SamplingCount;
	}

	void AudioTrack::setSamplingCount(const std::string &value)
	{
		this->_SamplingCount = value;
	}

	const std::string &AudioTrack::getBitDepth() const
	{
		if (this->_BitDepth.empty())
			this->_BitDepth = "";
		return _BitDepth;
	}

	void AudioTrack::setBitDepth(const std::string &value)
	{
		this->_BitDepth = value;
	}

	const std::string &AudioTrack::getBitDepthString() const
	{
		if (this->_BitDepthString.empty())
			this->_BitDepthString = "";
		return _BitDepthString;
	}

	void AudioTrack::setBitDepthString(const std::string &value)
	{
		this->_BitDepthString = value;
	}

	const std::string &AudioTrack::getCompressionRatio() const
	{
		if (this->_CompressionRatio.empty())
			this->_CompressionRatio = "";
		return _CompressionRatio;
	}

	void AudioTrack::setCompressionRatio(const std::string &value)
	{
		this->_CompressionRatio = value;
	}

	const std::string &AudioTrack::getDelay() const
	{
		if (this->_Delay.empty())
			this->_Delay = "";
		return _Delay;
	}

	void AudioTrack::setDelay(const std::string &value)
	{
		this->_Delay = value;
	}

	const std::string &AudioTrack::getDelayString() const
	{
		if (this->_DelayString.empty())
			this->_DelayString = "";
		return _DelayString;
	}

	void AudioTrack::setDelayString(const std::string &value)
	{
		this->_DelayString = value;
	}

	const std::string &AudioTrack::getDelayString1() const
	{
		if (this->_DelayString1.empty())
			this->_DelayString1 = "";
		return _DelayString1;
	}

	void AudioTrack::setDelayString1(const std::string &value)
	{
		this->_DelayString1 = value;
	}

	const std::string &AudioTrack::getDelayString2() const
	{
		if (this->_DelayString2.empty())
			this->_DelayString2 = "";
		return _DelayString2;
	}

	void AudioTrack::setDelayString2(const std::string &value)
	{
		this->_DelayString2 = value;
	}

	const std::string &AudioTrack::getDelayString3() const
	{
		if (this->_DelayString3.empty())
			this->_DelayString3 = "";
		return _DelayString3;
	}

	void AudioTrack::setDelayString3(const std::string &value)
	{
		this->_DelayString3 = value;
	}

	const std::string &AudioTrack::getVideoDelay() const
	{
		if (this->_VideoDelay.empty())
			this->_VideoDelay = "";
		return _VideoDelay;
	}

	void AudioTrack::setVideoDelay(const std::string &value)
	{
		this->_VideoDelay = value;
	}

	const std::string &AudioTrack::getVideoDelayString() const
	{
		if (this->_VideoDelayString.empty())
			this->_VideoDelayString = "";
		return _VideoDelayString;
	}

	void AudioTrack::setVideoDelayString(const std::string &value)
	{
		this->_VideoDelayString = value;
	}

	const std::string &AudioTrack::getVideoDelayString1() const
	{
		if (this->_VideoDelayString1.empty())
			this->_VideoDelayString1 = "";
		return _VideoDelayString1;
	}

	void AudioTrack::setVideoDelayString1(const std::string &value)
	{
		this->_VideoDelayString1 = value;
	}

	const std::string &AudioTrack::getVideoDelayString2() const
	{
		if (this->_VideoDelayString2.empty())
			this->_VideoDelayString2 = "";
		return _VideoDelayString2;
	}

	void AudioTrack::setVideoDelayString2(const std::string &value)
	{
		this->_VideoDelayString2 = value;
	}

	const std::string &AudioTrack::getVideoDelayString3() const
	{
		if (this->_VideoDelayString3.empty())
			this->_VideoDelayString3 = "";
		return _VideoDelayString3;
	}

	void AudioTrack::setVideoDelayString3(const std::string &value)
	{
		this->_VideoDelayString3 = value;
	}

	const std::string &AudioTrack::getDuration() const
	{
		if (this->_Duration.empty())
			this->_Duration = "";
		return _Duration;
	}

	void AudioTrack::setDuration(const std::string &value)
	{
		this->_Duration = value;
	}

	const std::string &AudioTrack::getDurationString() const
	{
		if (this->_DurationString.empty())
			this->_DurationString = "";
		return _DurationString;
	}

	void AudioTrack::setDurationString(const std::string &value)
	{
		this->_DurationString = value;
	}

	const std::string &AudioTrack::getDurationString1() const
	{
		if (this->_DurationString1.empty())
			this->_DurationString1 = "";
		return _DurationString1;
	}

	void AudioTrack::setDurationString1(const std::string &value)
	{
		this->_DurationString1 = value;
	}

	const std::string &AudioTrack::getDurationString2() const
	{
		if (this->_DurationString2.empty())
			this->_DurationString2 = "";
		return _DurationString2;
	}

	void AudioTrack::setDurationString2(const std::string &value)
	{
		this->_DurationString2 = value;
	}

	const std::string &AudioTrack::getDurationString3() const
	{
		if (this->_DurationString3.empty())
			this->_DurationString3 = "";
		return _DurationString3;
	}

	void AudioTrack::setDurationString3(const std::string &value)
	{
		this->_DurationString3 = value;
	}

	const std::string &AudioTrack::getReplayGainGain() const
	{
		if (this->_ReplayGainGain.empty())
			this->_ReplayGainGain = "";
		return _ReplayGainGain;
	}

	void AudioTrack::setReplayGainGain(const std::string &value)
	{
		this->_ReplayGainGain = value;
	}

	const std::string &AudioTrack::getReplayGainGainString() const
	{
		if (this->_ReplayGainGainString.empty())
			this->_ReplayGainGainString = "";
		return _ReplayGainGainString;
	}

	void AudioTrack::setReplayGainGainString(const std::string &value)
	{
		this->_ReplayGainGainString = value;
	}

	const std::string &AudioTrack::getReplayGainPeak() const
	{
		if (this->_ReplayGainPeak.empty())
			this->_ReplayGainPeak = "";
		return _ReplayGainPeak;
	}

	void AudioTrack::setReplayGainPeak(const std::string &value)
	{
		this->_ReplayGainPeak = value;
	}

	const std::string &AudioTrack::getStreamSize() const
	{
		if (this->_StreamSize.empty())
			this->_StreamSize = "";
		return _StreamSize;
	}

	void AudioTrack::setStreamSize(const std::string &value)
	{
		this->_StreamSize = value;
	}

	const std::string &AudioTrack::getStreamSizeString() const
	{
		if (this->_StreamSizeString.empty())
			this->_StreamSizeString = "";
		return _StreamSizeString;
	}

	void AudioTrack::setStreamSizeString(const std::string &value)
	{
		this->_StreamSizeString = value;
	}

	const std::string &AudioTrack::getStreamSizeString1() const
	{
		if (this->_StreamSizeString1.empty())
			this->_StreamSizeString1 = "";
		return _StreamSizeString1;
	}

	void AudioTrack::setStreamSizeString1(const std::string &value)
	{
		this->_StreamSizeString1 = value;
	}

	const std::string &AudioTrack::getStreamSizeString2() const
	{
		if (this->_StreamSizeString2.empty())
			this->_StreamSizeString2 = "";
		return _StreamSizeString2;
	}

	void AudioTrack::setStreamSizeString2(const std::string &value)
	{
		this->_StreamSizeString2 = value;
	}

	const std::string &AudioTrack::getStreamSizeString3() const
	{
		if (this->_StreamSizeString3.empty())
			this->_StreamSizeString3 = "";
		return _StreamSizeString3;
	}

	void AudioTrack::setStreamSizeString3(const std::string &value)
	{
		this->_StreamSizeString3 = value;
	}

	const std::string &AudioTrack::getStreamSizeString4() const
	{
		if (this->_StreamSizeString4.empty())
			this->_StreamSizeString4 = "";
		return _StreamSizeString4;
	}

	void AudioTrack::setStreamSizeString4(const std::string &value)
	{
		this->_StreamSizeString4 = value;
	}

	const std::string &AudioTrack::getStreamSizeString5() const
	{
		if (this->_StreamSizeString5.empty())
			this->_StreamSizeString5 = "";
		return _StreamSizeString5;
	}

	void AudioTrack::setStreamSizeString5(const std::string &value)
	{
		this->_StreamSizeString5 = value;
	}

	const std::string &AudioTrack::getStreamSizeProportion() const
	{
		if (this->_StreamSizeProportion.empty())
			this->_StreamSizeProportion = "";
		return _StreamSizeProportion;
	}

	void AudioTrack::setStreamSizeProportion(const std::string &value)
	{
		this->_StreamSizeProportion = value;
	}

	const std::string &AudioTrack::getAlignment() const
	{
		if (this->_Alignment.empty())
			this->_Alignment = "";
		return _Alignment;
	}

	void AudioTrack::setAlignment(const std::string &value)
	{
		this->_Alignment = value;
	}

	const std::string &AudioTrack::getAlignmentString() const
	{
		if (this->_AlignmentString.empty())
			this->_AlignmentString = "";
		return _AlignmentString;
	}

	void AudioTrack::setAlignmentString(const std::string &value)
	{
		this->_AlignmentString = value;
	}

	const std::string &AudioTrack::getInterleaveVideoFrames() const
	{
		if (this->_InterleaveVideoFrames.empty())
			this->_InterleaveVideoFrames = "";
		return _InterleaveVideoFrames;
	}

	void AudioTrack::setInterleaveVideoFrames(const std::string &value)
	{
		this->_InterleaveVideoFrames = value;
	}

	const std::string &AudioTrack::getInterleaveDuration() const
	{
		if (this->_InterleaveDuration.empty())
			this->_InterleaveDuration = "";
		return _InterleaveDuration;
	}

	void AudioTrack::setInterleaveDuration(const std::string &value)
	{
		this->_InterleaveDuration = value;
	}

	const std::string &AudioTrack::getInterleaveDurationString() const
	{
		if (this->_InterleaveDurationString.empty())
			this->_InterleaveDurationString = "";
		return _InterleaveDurationString;
	}

	void AudioTrack::setInterleaveDurationString(const std::string &value)
	{
		this->_InterleaveDurationString = value;
	}

	const std::string &AudioTrack::getInterleavePreload() const
	{
		if (this->_InterleavePreload.empty())
			this->_InterleavePreload = "";
		return _InterleavePreload;
	}

	void AudioTrack::setInterleavePreload(const std::string &value)
	{
		this->_InterleavePreload = value;
	}

	const std::string &AudioTrack::getInterleavePreloadString() const
	{
		if (this->_InterleavePreloadString.empty())
			this->_InterleavePreloadString = "";
		return _InterleavePreloadString;
	}

	void AudioTrack::setInterleavePreloadString(const std::string &value)
	{
		this->_InterleavePreloadString = value;
	}

	const std::string &AudioTrack::getEncodedLibrary() const
	{
		if (this->_EncodedLibrary.empty())
			this->_EncodedLibrary = "";
		return _EncodedLibrary;
	}

	void AudioTrack::setEncodedLibrary(const std::string &value)
	{
		this->_EncodedLibrary = value;
	}

	const std::string &AudioTrack::getEncodedLibraryString() const
	{
		if (this->_EncodedLibraryString.empty())
			this->_EncodedLibraryString = "";
		return _EncodedLibraryString;
	}

	void AudioTrack::setEncodedLibraryString(const std::string &value)
	{
		this->_EncodedLibraryString = value;
	}

	const std::string &AudioTrack::getEncodedLibraryName() const
	{
		if (this->_EncodedLibraryName.empty())
			this->_EncodedLibraryName = "";
		return _EncodedLibraryName;
	}

	void AudioTrack::setEncodedLibraryName(const std::string &value)
	{
		this->_EncodedLibraryName = value;
	}

	const std::string &AudioTrack::getEncodedLibraryVersion() const
	{
		if (this->_EncodedLibraryVersion.empty())
			this->_EncodedLibraryVersion = "";
		return _EncodedLibraryVersion;
	}

	void AudioTrack::setEncodedLibraryVersion(const std::string &value)
	{
		this->_EncodedLibraryVersion = value;
	}

	const std::string &AudioTrack::getEncodedLibraryDate() const
	{
		if (this->_EncodedLibraryDate.empty())
			this->_EncodedLibraryDate = "";
		return _EncodedLibraryDate;
	}

	void AudioTrack::setEncodedLibraryDate(const std::string &value)
	{
		this->_EncodedLibraryDate = value;
	}

	const std::string &AudioTrack::getEncodedLibrarySettings() const
	{
		if (this->_EncodedLibrarySettings.empty())
			this->_EncodedLibrarySettings = "";
		return _EncodedLibrarySettings;
	}

	void AudioTrack::setEncodedLibrarySettings(const std::string &value)
	{
		this->_EncodedLibrarySettings = value;
	}

	const std::string &AudioTrack::getLanguage() const
	{
		if (this->_Language.empty())
			this->_Language = "";
		return _Language;
	}

	void AudioTrack::setLanguage(const std::string &value)
	{
		this->_Language = value;
	}

	const std::string &AudioTrack::getLanguageString() const
	{
		if (this->_LanguageString.empty())
			this->_LanguageString = "";
		return _LanguageString;
	}

	void AudioTrack::setLanguageString(const std::string &value)
	{
		this->_LanguageString = value;
	}

	const std::string &AudioTrack::getLanguageMore() const
	{
		if (this->_LanguageMore.empty())
			this->_LanguageMore = "";
		return _LanguageMore;
	}

	void AudioTrack::setLanguageMore(const std::string &value)
	{
		this->_LanguageMore = value;
	}

	const std::string &AudioTrack::getEncodedDate() const
	{
		if (this->_EncodedDate.empty())
			this->_EncodedDate = "";
		return _EncodedDate;
	}

	void AudioTrack::setEncodedDate(const std::string &value)
	{
		this->_EncodedDate = value;
	}

	const std::string &AudioTrack::getTaggedDate() const
	{
		if (this->_TaggedDate.empty())
			this->_TaggedDate = "";
		return _TaggedDate;
	}

	void AudioTrack::setTaggedDate(const std::string &value)
	{
		this->_TaggedDate = value;
	}

	const std::string &AudioTrack::getEncryption() const
	{
		if (this->_Encryption.empty())
			this->_Encryption = "";
		return _Encryption;
	}

	void AudioTrack::setEncryption(const std::string &value)
	{
		this->_Encryption = value;
	}

	const std::string &AudioTrack::getDefault() const
	{
		if (this->_Default.empty())
			this->_Default = "";
		return _Default;
	}

	void AudioTrack::setDefault(const std::string &value)
	{
		this->_Default = value;
	}

	const std::string &AudioTrack::getDefaultString() const
	{
		if (this->_DefaultString.empty())
			this->_DefaultString = "";
		return _DefaultString;
	}

	void AudioTrack::setDefaultString(const std::string &value)
	{
		this->_DefaultString = value;
	}

	const std::string &AudioTrack::getForced() const
	{
		if (this->_Forced.empty())
			this->_Forced = "";
		return _Forced;
	}

	void AudioTrack::setForced(const std::string &value)
	{
		this->_Forced = value;
	}

	const std::string &AudioTrack::getForcedString() const
	{
		if (this->_ForcedString.empty())
			this->_ForcedString = "";
		return _ForcedString;
	}

	void AudioTrack::setForcedString(const std::string &value)
	{
		this->_ForcedString = value;
	}
}
