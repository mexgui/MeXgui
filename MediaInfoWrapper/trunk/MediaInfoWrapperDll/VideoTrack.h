#pragma once

#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{
	///<summary>Contains properties for a VideoTrack </summary>
	class VideoTrack
	{
	private:
		std::string _Count;
		std::string _StreamCount;
		std::string _StreamKind;
		std::string _StreamKindID;
		std::string _StreamOrder;
		std::string _Inform;
		std::string _ID;
		std::string _UniqueID;
		std::string _Title;
		std::string _Codec;
		std::string _CodecString;
		std::string _CodecInfo;
		std::string _CodecUrl;
		std::string _CodecID;
		std::string _CodecIDInfo;
		std::string _BitRate;
		std::string _BitRateString;
		std::string _BitRateMode;
		std::string _EncodedLibrary;
		std::string _EncodedLibrarySettings;
		std::string _Width;
		std::string _Height;
		std::string _AspectRatio;
		std::string _AspectRatioString;
		std::string _PixelAspectRatio;
		std::string _PixelAspectRatioString;
		std::string _FrameRate;
		std::string _FrameRateString;
		std::string _FrameRateOriginal;
		std::string _FrameRateOriginalString;
		std::string _FrameRateMode;
		std::string _FrameRateModeString;
		std::string _FrameCount;
		std::string _BitDepth;
		std::string _BitsPixelFrame;
		std::string _Delay;
		std::string _Duration;
		std::string _DurationString;
		std::string _DurationString1;
		std::string _DurationString2;
		std::string _DurationString3;
		std::string _Language;
		std::string _LanguageString;
		std::string _LanguageMore;
		std::string _Format;
		std::string _FormatInfo;
		std::string _FormatUrl;
		std::string _FormatVersion;
		std::string _FormatProfile;
		std::string _FormatSettings;
		std::string _FormatSettingsBVOP;
		std::string _FormatSettingsBVOPString;
		std::string _FormatSettingsQPel;
		std::string _FormatSettingsQPelString;
		std::string _FormatSettingsGMC;
		std::string _FormatSettingsGMCString;
		std::string _FormatSettingsMatrix;
		std::string _FormatSettingsMatrixString;
		std::string _FormatSettingsMatrixData;
		std::string _FormatSettingsCABAC;
		std::string _FormatSettingsCABACString;
		std::string _FormatSettingsRefFrames;
		std::string _FormatSettingsRefFramesString;
		std::string _FormatSettingsPulldown;
		std::string _ScanType;
		std::string _ScanTypeString;
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

		///<summary> When multiple streams, number of the stream </summary>
		const std::string &getStreamKindID() const;
		void setStreamKindID(const std::string &value);

		///<summary>Stream order in the file, whatever is the kind of stream (base=0)</summary>
		const std::string &getStreamOrder() const;
		void setStreamOrder(const std::string &value);

		///<summary> Last   Inform   call </summary>
		const std::string &getInform() const;
		void setInform(const std::string &value);

		///<summary> A ID for this stream in this file </summary>
		const std::string &getID() const;
		void setID(const std::string &value);

		///<summary> A unique ID for this stream, should be copied with stream copy </summary>
		const std::string &getUniqueID() const;
		void setUniqueID(const std::string &value);

		///<summary> Name of the track </summary>
		const std::string &getTitle() const;
		void setTitle(const std::string &value);

		///<summary> Codec used </summary>
		const std::string &getCodec() const;
		void setCodec(const std::string &value);

		///<summary> Codec used (text) </summary>
		const std::string &getCodecString() const;
		void setCodecString(const std::string &value);

		///<summary> Info about codec </summary>
		const std::string &getCodecInfo() const;
		void setCodecInfo(const std::string &value);

		///<summary> Link </summary>
		const std::string &getCodecUrl() const;
		void setCodecUrl(const std::string &value);

		///<summary> Codec ID used </summary>
		const std::string &getCodecID() const;
		void setCodecID(const std::string &value);

		///<summary> Info about codec ID </summary>
		const std::string &getCodecIDInfo() const;
		void setCodecIDInfo(const std::string &value);

		///<summary> Bit rate in bps </summary>
		const std::string &getBitRate() const;
		void setBitRate(const std::string &value);

		///<summary> Bit rate (with measurement) </summary>
		const std::string &getBitRateString() const;
		void setBitRateString(const std::string &value);

		///<summary> Bit rate mode (VBR, CBR) </summary>
		const std::string &getBitRateMode() const;
		void setBitRateMode(const std::string &value);

		///<summary> Software used to create the file </summary>
		const std::string &getEncodedLibrary() const;
		void setEncodedLibrary(const std::string &value);

		///<summary> Parameters used by the software </summary>
		const std::string &getEncodedLibrarySettings() const;
		void setEncodedLibrarySettings(const std::string &value);

		///<summary> Width </summary>
		const std::string &getWidth() const;
		void setWidth(const std::string &value);

		///<summary> Height </summary>
		const std::string &getHeight() const;
		void setHeight(const std::string &value);

		///<summary> Aspect ratio </summary>
		const std::string &getAspectRatio() const;
		void setAspectRatio(const std::string &value);

		///<summary> Aspect ratio </summary>
		const std::string &getAspectRatioString() const;
		void setAspectRatioString(const std::string &value);

		///<summary> Pixel Aspect Ratio </summary>
		const std::string &getPixelAspectRatio() const;
		void setPixelAspectRatio(const std::string &value);

		///<summary> Pixel Aspect Ratio </summary>
		const std::string &getPixelAspectRatioString() const;
		void setPixelAspectRatioString(const std::string &value);

		///<summary> Frame rate </summary>
		const std::string &getFrameRate() const;
		void setFrameRate(const std::string &value);

		///<summary> Frame rate </summary>
		const std::string &getFrameRateString() const;
		void setFrameRateString(const std::string &value);

		///<summary> Frame rate original </summary>
		const std::string &getFrameRateOriginal() const;
		void setFrameRateOriginal(const std::string &value);

		///<summary> Frame rate original</summary>
		const std::string &getFrameRateOriginalString() const;
		void setFrameRateOriginalString(const std::string &value);

		///<summary> Frame rate mode</summary>
		const std::string &getFrameRateMode() const;
		void setFrameRateMode(const std::string &value);

		///<summary> Frame rate mode</summary>
		const std::string &getFrameRateModeString() const;
		void setFrameRateModeString(const std::string &value);

		///<summary> Frame count </summary>
		const std::string &getFrameCount() const;
		void setFrameCount(const std::string &value);

		///<summary> example for MP3 : 16 bits </summary>
		const std::string &getBitDepth() const;
		void setBitDepth(const std::string &value);

		///<summary> bits_(Pixel Frame) (like Gordian Knot) </summary>
		const std::string &getBitsPixelFrame() const;
		void setBitsPixelFrame(const std::string &value);

		///<summary> Delay fixed in the stream (relative) IN MS </summary>
		const std::string &getDelay() const;
		void setDelay(const std::string &value);

		///<summary> Duration of the stream </summary>
		const std::string &getDuration() const;
		void setDuration(const std::string &value);

		///<summary> Duration (formated) </summary>
		const std::string &getDurationString() const;
		void setDurationString(const std::string &value);

		///<summary> Duration in format : HHh MMmn SSs MMMms, XX omited if zero </summary>
		const std::string &getDurationString1() const;
		void setDurationString1(const std::string &value);

		///<summary> Duration in format : XXx YYy only, YYy omited if zero </summary>
		const std::string &getDurationString2() const;
		void setDurationString2(const std::string &value);

		///<summary> Duration in format : HH:MM:SS.MMM </summary>
		const std::string &getDurationString3() const;
		void setDurationString3(const std::string &value);

		///<summary> Language (2 letters) </summary>
		const std::string &getLanguage() const;
		void setLanguage(const std::string &value);

		///<summary> Language (full) </summary>
		const std::string &getLanguageString() const;
		void setLanguageString(const std::string &value);

		///<summary> More info about Language (director s comment...) </summary>
		const std::string &getLanguageMore() const;
		void setLanguageMore(const std::string &value);

		///<summary> Format </summary>
		const std::string &getFormat() const;
		void setFormat(const std::string &value);

		///<summary> Info about Format </summary>
		const std::string &getFormatInfo() const;
		void setFormatInfo(const std::string &value);

		///<summary> Url about Format </summary>
		const std::string &getFormatUrl() const;
		void setFormatUrl(const std::string &value);

		///<summary> Version of the Format </summary>
		const std::string &getFormatVersion() const;
		void setFormatVersion(const std::string &value);

		///<summary> Profile of the Format </summary>
		const std::string &getFormatProfile() const;
		void setFormatProfile(const std::string &value);

		///<summary> Settings of the Format </summary>
		const std::string &getFormatSettings() const;
		void setFormatSettings(const std::string &value);

		///<summary> BVOP Info </summary>
		const std::string &getFormatSettingsBVOP() const;
		void setFormatSettingsBVOP(const std::string &value);

		///<summary> BVOP Info (string format)</summary>
		const std::string &getFormatSettingsBVOPString() const;
		void setFormatSettingsBVOPString(const std::string &value);

		///<summary> Qpel Info </summary>
		const std::string &getFormatSettingsQPel() const;
		void setFormatSettingsQPel(const std::string &value);

		///<summary> Qpel Info (string format)</summary>
		const std::string &getFormatSettingsQPelString() const;
		void setFormatSettingsQPelString(const std::string &value);

		///<summary> GMC Info </summary>
		const std::string &getFormatSettingsGMC() const;
		void setFormatSettingsGMC(const std::string &value);

		///<summary> GMC Info (string format)</summary>
		const std::string &getFormatSettingsGMCString() const;
		void setFormatSettingsGMCString(const std::string &value);

		///<summary> Matrix Info </summary>
		const std::string &getFormatSettingsMatrix() const;
		void setFormatSettingsMatrix(const std::string &value);

		///<summary> Matrix Info (string format)</summary>
		const std::string &getFormatSettingsMatrixString() const;
		void setFormatSettingsMatrixString(const std::string &value);

		///<summary> Matrix Info (data format)</summary>
		const std::string &getFormatSettingsMatrixData() const;
		void setFormatSettingsMatrixData(const std::string &value);

		///<summary> CABAC Info </summary>
		const std::string &getFormatSettingsCABAC() const;
		void setFormatSettingsCABAC(const std::string &value);

		///<summary> CABAC Info (string format)</summary>
		const std::string &getFormatSettingsCABACString() const;
		void setFormatSettingsCABACString(const std::string &value);

		///<summary> RefFrames Info </summary>
		const std::string &getFormatSettingsRefFrames() const;
		void setFormatSettingsRefFrames(const std::string &value);

		///<summary> RefFrames Info (string format)</summary>
		const std::string &getFormatSettingsRefFramesString() const;
		void setFormatSettingsRefFramesString(const std::string &value);

		///<summary> Pulldown Info </summary>
		const std::string &getFormatSettingsPulldown() const;
		void setFormatSettingsPulldown(const std::string &value);

		///<summary> ScanType Info </summary>
		const std::string &getScanType() const;
		void setScanType(const std::string &value);

		///<summary> ScanType Info (string format)</summary>
		const std::string &getScanTypeString() const;
		void setScanTypeString(const std::string &value);

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
