#pragma once

#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{
	///<summary>Contains properties for a AudioTrack </summary>
	class AudioTrack
	{
	private:
		std::string _Count;
		std::string _StreamCount;
		std::string _StreamKind;
		std::string _StreamKindString;
		std::string _StreamKindID;
		std::string _StreamKindPos;
		std::string _StreamOrder;
		std::string _Inform;
		std::string _ID;
		std::string _IDString;
		std::string _UniqueID;
		std::string _MenuID;
		std::string _MenuIDString;
		std::string _Format;
		std::string _FormatInfo;
		std::string _FormatUrl;
		std::string _FormatVersion;
		std::string _FormatProfile;
		std::string _FormatSettings;
		std::string _FormatSettingsSBR;
		std::string _FormatSettingsSBRString;
		std::string _FormatSettingsPS;
		std::string _FormatSettingsPSString;
		std::string _FormatSettingsFloor;
		std::string _FormatSettingsFirm;
		std::string _FormatSettingsEndianness;
		std::string _FormatSettingsSign;
		std::string _FormatSettingsLaw;
		std::string _FormatSettingsITU;
		std::string _MuxingMode;
		std::string _CodecID;
		std::string _CodecIDInfo;
		std::string _CodecIDHint;
		std::string _CodecIDUrl;
		std::string _CodecIDDescription;
		std::string _Duration;
		std::string _DurationString;
		std::string _DurationString1;
		std::string _DurationString2;
		std::string _DurationString3;
		std::string _BitRate;
		std::string _BitRateString;
		std::string _BitRateMode;
		std::string _BitRateModeString;
		std::string _BitRateMinimum;
		std::string _BitRateMinimumString;
		std::string _BitRateNominal;
		std::string _BitRateNominalString;
		std::string _BitRateMaximum;
		std::string _BitRateMaximumString;
		std::string _Channels;
		std::string _ChannelsString;
		std::string _ChannelPositions;
		std::string _ChannelPositionsString2;
		std::string _ChannelMode;
		std::string _SamplingRate;
		std::string _SamplingRateString;
		std::string _SamplingCount;
		std::string _BitDepth;
		std::string _BitDepthString;
		std::string _CompressionRatio;
		std::string _Delay;
		std::string _DelayString;
		std::string _DelayString1;
		std::string _DelayString2;
		std::string _DelayString3;
		std::string _VideoDelay;
		std::string _VideoDelayString;
		std::string _VideoDelayString1;
		std::string _VideoDelayString2;
		std::string _VideoDelayString3;
		std::string _ReplayGainGain;
		std::string _ReplayGainGainString;
		std::string _ReplayGainPeak;
		std::string _StreamSize;
		std::string _StreamSizeString;
		std::string _StreamSizeString1;
		std::string _StreamSizeString2;
		std::string _StreamSizeString3;
		std::string _StreamSizeString4;
		std::string _StreamSizeString5;
		std::string _StreamSizeProportion;
		std::string _Alignment;
		std::string _AlignmentString;
		std::string _InterleaveVideoFrames;
		std::string _InterleaveDuration;
		std::string _InterleaveDurationString;
		std::string _InterleavePreload;
		std::string _InterleavePreloadString;
		std::string _Title;
		std::string _EncodedLibrary;
		std::string _EncodedLibraryString;
		std::string _EncodedLibraryName;
		std::string _EncodedLibraryVersion;
		std::string _EncodedLibraryDate;
		std::string _EncodedLibrarySettings;
		std::string _Language;
		std::string _LanguageString;
		std::string _LanguageMore;
		std::string _EncodedDate;
		std::string _TaggedDate;
		std::string _Encryption;
		std::string _Default;
		std::string _DefaultString;
		std::string _Forced;
		std::string _ForcedString;

		///<summary> Count of objects available in this stream </summary>
	public:
		const std::string &getCount() const;
		void setCount(const std::string &value);

		///<summary> Count of streams of that kind available </summary>
		const std::string &getStreamCount() const;
		void setStreamCount(const std::string &value);

		///<summary> Stream name </summary>
		const std::string &getStreamKind() const;
		void setStreamKind(const std::string &value);

		///<summary> Stream name string formated</summary>
		const std::string &getStreamKindString() const;
		void setStreamKindString(const std::string &value);

		///<summary> id of the stream </summary>
		const std::string &getStreamKindID() const;
		void setStreamKindID(const std::string &value);

		///<summary> When multiple streams, number of the stream </summary>
		const std::string &getStreamKindPos() const;
		void setStreamKindPos(const std::string &value);

		///<summary>Stream order in the file, whatever is the kind of stream (base=0)</summary>
		const std::string &getStreamOrder() const;
		void setStreamOrder(const std::string &value);

		///<summary> Last   Inform   call </summary>
		const std::string &getInform() const;
		void setInform(const std::string &value);

		///<summary> A ID for the stream </summary>
		const std::string &getID() const;
		void setID(const std::string &value);

		///<summary> A ID for the stream  string formated</summary>
		const std::string &getIDString() const;
		void setIDString(const std::string &value);

		///<summary> A unique ID for this stream, should be copied with stream copy </summary>
		const std::string &getUniqueID() const;
		void setUniqueID(const std::string &value);

		///<summary> the Menu ID for this stream</summary>
		const std::string &getMenuID() const;
		void setMenuID(const std::string &value);

		///<summary> the Menu ID for this stream string formated</summary>
		const std::string &getMenuIDString() const;
		void setMenuIDString(const std::string &value);

		///<summary> the Format used</summary>
		const std::string &getFormat() const;
		void setFormat(const std::string &value);

		///<summary> Info about the Format used</summary>
		const std::string &getFormatInfo() const;
		void setFormatInfo(const std::string &value);

		///<summary> Webpage of the Format</summary>
		const std::string &getFormatUrl() const;
		void setFormatUrl(const std::string &value);

		///<summary> the Version of the Format used</summary>
		const std::string &getFormatVersion() const;
		void setFormatVersion(const std::string &value);

		///<summary> the Profile of the Format used</summary>
		const std::string &getFormatProfile() const;
		void setFormatProfile(const std::string &value);

		///<summary> the Settings of the Format used</summary>
		const std::string &getFormatSettings() const;
		void setFormatSettings(const std::string &value);

		///<summary> the SBR flag</summary>
		const std::string &getFormatSettingsSBR() const;
		void setFormatSettingsSBR(const std::string &value);

		///<summary> the SBR flag set as string</summary>
		const std::string &getFormatSettingsSBRString() const;
		void setFormatSettingsSBRString(const std::string &value);

		///<summary> the PS flag</summary>
		const std::string &getFormatSettingsPS() const;
		void setFormatSettingsPS(const std::string &value);

		///<summary> the PS flag set as string</summary>
		const std::string &getFormatSettingsPSString() const;
		void setFormatSettingsPSString(const std::string &value);

		///<summary> the Floor used in the stream</summary>
		const std::string &getFormatSettingsFloor() const;
		void setFormatSettingsFloor(const std::string &value);

		///<summary> the Firm used in the settings</summary>
		const std::string &getFormatSettingsFirm() const;
		void setFormatSettingsFirm(const std::string &value);

		///<summary> the Endianness used in the stream</summary>
		const std::string &getFormatSettingsEndianness() const;
		void setFormatSettingsEndianness(const std::string &value);

		///<summary> the Sign used in the stream</summary>
		const std::string &getFormatSettingsSign() const;
		void setFormatSettingsSign(const std::string &value);

		///<summary> the Law used in the stream</summary>
		const std::string &getFormatSettingsLaw() const;
		void setFormatSettingsLaw(const std::string &value);

		///<summary> the ITU Format used in the stream</summary>
		const std::string &getFormatSettingsITU() const;
		void setFormatSettingsITU(const std::string &value);

		///<summary> how the stream has been muxed </summary>
		const std::string &getMuxingMode() const;
		void setMuxingMode(const std::string &value);

		///<summary> the ID of the Codec, found in the container </summary>
		const std::string &getCodecID() const;
		void setCodecID(const std::string &value);

		///<summary> Info about the CodecID </summary>
		const std::string &getCodecIDInfo() const;
		void setCodecIDInfo(const std::string &value);

		///<summary> the Hint/popular name for the CodecID  </summary>
		const std::string &getCodecIDHint() const;
		void setCodecIDHint(const std::string &value);

		///<summary> homepage for more details about the CodecID </summary>
		const std::string &getCodecIDUrl() const;
		void setCodecIDUrl(const std::string &value);

		///<summary> the description of the Codec ID </summary>
		const std::string &getCodecIDDescription() const;
		void setCodecIDDescription(const std::string &value);

		///<summary> Name of the track </summary>
		const std::string &getTitle() const;
		void setTitle(const std::string &value);

		///<summary> Bit rate in bps </summary>
		const std::string &getBitRate() const;
		void setBitRate(const std::string &value);

		///<summary> Bit rate (with measurement) </summary>
		const std::string &getBitRateString() const;
		void setBitRateString(const std::string &value);

		///<summary> Bit rate mode (VBR, CBR) </summary>
		const std::string &getBitRateMode() const;
		void setBitRateMode(const std::string &value);

		///<summary> Bit rate mode (VBR, CBR) formated as string </summary>
		const std::string &getBitRateModeString() const;
		void setBitRateModeString(const std::string &value);

		///<summary> Minimum Bit rate mode </summary>
		const std::string &getBitRateMinimum() const;
		void setBitRateMinimum(const std::string &value);

		///<summary> Minimum Bit rate mode formated as string </summary>
		const std::string &getBitRateMinimumString() const;
		void setBitRateMinimumString(const std::string &value);

		///<summary> Nominal Bit rate </summary>
		const std::string &getBitRateNominal() const;
		void setBitRateNominal(const std::string &value);

		///<summary> Nominal Bit rate formated as string </summary>
		const std::string &getBitRateNominalString() const;
		void setBitRateNominalString(const std::string &value);

		///<summary> Max Bit rate </summary>
		const std::string &getBitRateMaximum() const;
		void setBitRateMaximum(const std::string &value);

		///<summary> Max Bit rate formated as string </summary>
		const std::string &getBitRateMaximumString() const;
		void setBitRateMaximumString(const std::string &value);

		///<summary> Number of channels </summary>
		const std::string &getChannels() const;
		void setChannels(const std::string &value);

		///<summary> Number of channels </summary>
		const std::string &getChannelsString() const;
		void setChannelsString(const std::string &value);

		///<summary> Positions of channels </summary>
		const std::string &getChannelPositions() const;
		void setChannelPositions(const std::string &value);

		///<summary> Positions of channels (x/y.z format) </summary>
		const std::string &getChannelPositionsString2() const;
		void setChannelPositionsString2(const std::string &value);

		///<summary> Channel mode </summary>
		const std::string &getChannelMode() const;
		void setChannelMode(const std::string &value);

		///<summary> Sampling rate </summary>
		const std::string &getSamplingRate() const;
		void setSamplingRate(const std::string &value);

		///<summary> in KHz </summary>
		const std::string &getSamplingRateString() const;
		void setSamplingRateString(const std::string &value);

		///<summary> Frame count </summary>
		const std::string &getSamplingCount() const;
		void setSamplingCount(const std::string &value);

		///<summary> BitDepth in bits (8, 16, 20, 24) </summary>
		const std::string &getBitDepth() const;
		void setBitDepth(const std::string &value);

		///<summary> BitDepth in bits (8, 16, 20, 24) formated as string </summary>
		const std::string &getBitDepthString() const;
		void setBitDepthString(const std::string &value);

		///<summary> Current Stream Size divided by uncompressed Stream Size </summary>
		const std::string &getCompressionRatio() const;
		void setCompressionRatio(const std::string &value);

		///<summary> Delay fixed in the stream (relative) </summary>
		const std::string &getDelay() const;
		void setDelay(const std::string &value);

		///<summary> Delay in format : XXx YYy only, YYy omitted if zero </summary>
		const std::string &getDelayString() const;
		void setDelayString(const std::string &value);

		///<summary> Delay in format : HHh MMmn SSs MMMms, XX omited if zero </summary>
		const std::string &getDelayString1() const;
		void setDelayString1(const std::string &value);

		///<summary> Delay in format : XXx YYy only, YYy omitted if zero </summary>
		const std::string &getDelayString2() const;
		void setDelayString2(const std::string &value);

		///<summary> Delay in format : HH:MM:SS.MMM </summary>
		const std::string &getDelayString3() const;
		void setDelayString3(const std::string &value);

		///<summary> Delay (ms) fixed in the stream (absolute / video) </summary>
		const std::string &getVideoDelay() const;
		void setVideoDelay(const std::string &value);

		///<summary> Delay (ms) fixed in the stream (absolute / video) formated as string </summary>
		const std::string &getVideoDelayString() const;
		void setVideoDelayString(const std::string &value);

		///<summary> Delay (ms) fixed in the stream (absolute / video) formated as string </summary>
		const std::string &getVideoDelayString1() const;
		void setVideoDelayString1(const std::string &value);

		///<summary> Delay (ms) fixed in the stream (absolute / video) formated as string </summary>
		const std::string &getVideoDelayString2() const;
		void setVideoDelayString2(const std::string &value);

		///<summary> Delay (ms) fixed in the stream (absolute / video) formated as string </summary>
		const std::string &getVideoDelayString3() const;
		void setVideoDelayString3(const std::string &value);

		///<summary> Play time of the stream </summary>
		const std::string &getDuration() const;
		void setDuration(const std::string &value);

		///<summary> Play time (formated) </summary>
		const std::string &getDurationString() const;
		void setDurationString(const std::string &value);

		///<summary> Play time in format : HHh MMmn SSs MMMms, XX omited if zero </summary>
		const std::string &getDurationString1() const;
		void setDurationString1(const std::string &value);

		///<summary> Play time in format : XXx YYy only, YYy omited if zero </summary>
		const std::string &getDurationString2() const;
		void setDurationString2(const std::string &value);

		///<summary> Play time in format : HH:MM:SS.MMM </summary>
		const std::string &getDurationString3() const;
		void setDurationString3(const std::string &value);

		///<summary> The gain to apply to reach 89dB SPL on playback </summary>
		const std::string &getReplayGainGain() const;
		void setReplayGainGain(const std::string &value);

		///<summary> The gain to apply to reach 89dB SPL on playback formated as string </summary>
		const std::string &getReplayGainGainString() const;
		void setReplayGainGainString(const std::string &value);

		///<summary> The maximum absolute peak value of the item </summary>
		const std::string &getReplayGainPeak() const;
		void setReplayGainPeak(const std::string &value);

		///<summary> Streamsize in bytes </summary>
		const std::string &getStreamSize() const;
		void setStreamSize(const std::string &value);

		///<summary> Streamsize with percentage value </summary>
		const std::string &getStreamSizeString() const;
		void setStreamSizeString(const std::string &value);

		///<summary> Streamsize with percentage value </summary>
		const std::string &getStreamSizeString1() const;
		void setStreamSizeString1(const std::string &value);

		///<summary> Streamsize with percentage value </summary>
		const std::string &getStreamSizeString2() const;
		void setStreamSizeString2(const std::string &value);

		///<summary> Streamsize with percentage value </summary>
		const std::string &getStreamSizeString3() const;
		void setStreamSizeString3(const std::string &value);

		///<summary> Streamsize with percentage value </summary>
		const std::string &getStreamSizeString4() const;
		void setStreamSizeString4(const std::string &value);

		///<summary> Streamsize with percentage value </summary>
		const std::string &getStreamSizeString5() const;
		void setStreamSizeString5(const std::string &value);

		///<summary> Stream size divided by file size </summary>
		const std::string &getStreamSizeProportion() const;
		void setStreamSizeProportion(const std::string &value);

		///<summary> How this stream file is aligned in the container </summary>
		const std::string &getAlignment() const;
		void setAlignment(const std::string &value);

		///<summary> Where this stream file is aligned in the container </summary>
		const std::string &getAlignmentString() const;
		void setAlignmentString(const std::string &value);

		///<summary> Between how many video frames the stream is inserted </summary>
		const std::string &getInterleaveVideoFrames() const;
		void setInterleaveVideoFrames(const std::string &value);

		///<summary> Between how much time (ms) the stream is inserted </summary>
		const std::string &getInterleaveDuration() const;
		void setInterleaveDuration(const std::string &value);

		///<summary> Between how much time and video frames the stream is inserted (with measurement) </summary>
		const std::string &getInterleaveDurationString() const;
		void setInterleaveDurationString(const std::string &value);

		///<summary> How much time is buffered before the first video frame </summary>
		const std::string &getInterleavePreload() const;
		void setInterleavePreload(const std::string &value);

		///<summary> How much time is buffered before the first video frame (with measurement) </summary>
		const std::string &getInterleavePreloadString() const;
		void setInterleavePreloadString(const std::string &value);

		///<summary> Software used to create the file </summary>
		const std::string &getEncodedLibrary() const;
		void setEncodedLibrary(const std::string &value);

		///<summary> Software used to create the file formated as string </summary>
		const std::string &getEncodedLibraryString() const;
		void setEncodedLibraryString(const std::string &value);

		///<summary> Name of the Software used to create the file </summary>
		const std::string &getEncodedLibraryName() const;
		void setEncodedLibraryName(const std::string &value);


		///<summary> Version of the Software used to create the file </summary>
		const std::string &getEncodedLibraryVersion() const;
		void setEncodedLibraryVersion(const std::string &value);

		///<summary> Date of the Software used to create the file </summary>
		const std::string &getEncodedLibraryDate() const;
		void setEncodedLibraryDate(const std::string &value);

		///<summary> Parameters used by the software </summary>
		const std::string &getEncodedLibrarySettings() const;
		void setEncodedLibrarySettings(const std::string &value);

		///<summary> Language (2 letters) </summary>
		const std::string &getLanguage() const;
		void setLanguage(const std::string &value);

		///<summary> Language (full) </summary>
		const std::string &getLanguageString() const;
		void setLanguageString(const std::string &value);

		///<summary> More info about Language (director s comment...) </summary>
		const std::string &getLanguageMore() const;
		void setLanguageMore(const std::string &value);

		///<summary> UTC time that the encoding of this item was completed began. </summary>
		const std::string &getEncodedDate() const;
		void setEncodedDate(const std::string &value);

		///<summary> UTC time that the tags were done for this item. </summary>
		const std::string &getTaggedDate() const;
		void setTaggedDate(const std::string &value);

		///<summary> encryption string. </summary>
		const std::string &getEncryption() const;
		void setEncryption(const std::string &value);

		///<summary> Default Info </summary>
		const std::string &getDefault() const;
		void setDefault(const std::string &value);

		///<summary> Default Info (string format)</summary>
		const std::string &getDefaultString() const;
		void setDefaultString(const std::string &value);

		///<summary> Forced Info </summary>
		const std::string &getForced() const;
		void setForced(const std::string &value);

		///<summary> Forced Info (string format)</summary>
		const std::string &getForcedString() const;
		void setForcedString(const std::string &value);
	};
}
