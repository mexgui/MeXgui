#include "VideoTrack.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{

	const std::string &VideoTrack::getCount() const
	{
		if (this->_Count.empty())
			this->_Count = "";
		return _Count;
	}

	void VideoTrack::setCount(const std::string &value)
	{
		this->_Count = value;
	}

	const std::string &VideoTrack::getStreamCount() const
	{
		if (this->_StreamCount.empty())
			this->_StreamCount = "";
		return _StreamCount;
	}

	void VideoTrack::setStreamCount(const std::string &value)
	{
		this->_StreamCount = value;
	}

	const std::string &VideoTrack::getStreamKind() const
	{
		if (this->_StreamKind.empty())
			this->_StreamKind = "";
		return _StreamKind;
	}

	void VideoTrack::setStreamKind(const std::string &value)
	{
		this->_StreamKind = value;
	}

	const std::string &VideoTrack::getStreamKindID() const
	{
		if (this->_StreamKindID.empty())
			this->_StreamKindID = "";
		return _StreamKindID;
	}

	void VideoTrack::setStreamKindID(const std::string &value)
	{
		this->_StreamKindID = value;
	}

	const std::string &VideoTrack::getStreamOrder() const
	{
		if (this->_StreamOrder.empty())
			this->_StreamOrder = "";
		return _StreamOrder;
	}

	void VideoTrack::setStreamOrder(const std::string &value)
	{
		this->_StreamOrder = value;
	}

	const std::string &VideoTrack::getInform() const
	{
		if (this->_Inform.empty())
			this->_Inform = "";
		return _Inform;
	}

	void VideoTrack::setInform(const std::string &value)
	{
		this->_Inform = value;
	}

	const std::string &VideoTrack::getID() const
	{
		if (this->_ID.empty())
			this->_ID = "";
		return _ID;
	}

	void VideoTrack::setID(const std::string &value)
	{
		this->_ID = value;
	}

	const std::string &VideoTrack::getUniqueID() const
	{
		if (this->_UniqueID.empty())
			this->_UniqueID = "";
		return _UniqueID;
	}

	void VideoTrack::setUniqueID(const std::string &value)
	{
		this->_UniqueID = value;
	}

	const std::string &VideoTrack::getTitle() const
	{
		if (this->_Title.empty())
			this->_Title = "";
		return _Title;
	}

	void VideoTrack::setTitle(const std::string &value)
	{
		this->_Title = value;
	}

	const std::string &VideoTrack::getCodec() const
	{
		if (this->_Codec.empty())
			this->_Codec = "";
		return _Codec;
	}

	void VideoTrack::setCodec(const std::string &value)
	{
		this->_Codec = value;
	}

	const std::string &VideoTrack::getCodecString() const
	{
		if (this->_CodecString.empty())
			this->_CodecString = "";
		return _CodecString;
	}

	void VideoTrack::setCodecString(const std::string &value)
	{
		this->_CodecString = value;
	}

	const std::string &VideoTrack::getCodecInfo() const
	{
		if (this->_CodecInfo.empty())
			this->_CodecInfo = "";
		return _CodecInfo;
	}

	void VideoTrack::setCodecInfo(const std::string &value)
	{
		this->_CodecInfo = value;
	}

	const std::string &VideoTrack::getCodecUrl() const
	{
		if (this->_CodecUrl.empty())
			this->_CodecUrl = "";
		return _CodecUrl;
	}

	void VideoTrack::setCodecUrl(const std::string &value)
	{
		this->_CodecUrl = value;
	}

	const std::string &VideoTrack::getCodecID() const
	{
		if (this->_CodecID.empty())
			this->_CodecID = "";
		return _CodecID;
	}

	void VideoTrack::setCodecID(const std::string &value)
	{
		this->_CodecID = value;
	}

	const std::string &VideoTrack::getCodecIDInfo() const
	{
		if (this->_CodecIDInfo.empty())
			this->_CodecIDInfo = "";
		return _CodecIDInfo;
	}

	void VideoTrack::setCodecIDInfo(const std::string &value)
	{
		this->_CodecIDInfo = value;
	}

	const std::string &VideoTrack::getBitRate() const
	{
		if (this->_BitRate.empty())
			this->_BitRate = "";
		return _BitRate;
	}

	void VideoTrack::setBitRate(const std::string &value)
	{
		this->_BitRate = value;
	}

	const std::string &VideoTrack::getBitRateString() const
	{
		if (this->_BitRateString.empty())
			this->_BitRateString = "";
		return _BitRateString;
	}

	void VideoTrack::setBitRateString(const std::string &value)
	{
		this->_BitRateString = value;
	}

	const std::string &VideoTrack::getBitRateMode() const
	{
		if (this->_BitRateMode.empty())
			this->_BitRateMode = "";
		return _BitRateMode;
	}

	void VideoTrack::setBitRateMode(const std::string &value)
	{
		this->_BitRateMode = value;
	}

	const std::string &VideoTrack::getEncodedLibrary() const
	{
		if (this->_EncodedLibrary.empty())
			this->_EncodedLibrary = "";
		return _EncodedLibrary;
	}

	void VideoTrack::setEncodedLibrary(const std::string &value)
	{
		this->_EncodedLibrary = value;
	}

	const std::string &VideoTrack::getEncodedLibrarySettings() const
	{
		if (this->_EncodedLibrarySettings.empty())
			this->_EncodedLibrarySettings = "";
		return _EncodedLibrarySettings;
	}

	void VideoTrack::setEncodedLibrarySettings(const std::string &value)
	{
		this->_EncodedLibrarySettings = value;
	}

	const std::string &VideoTrack::getWidth() const
	{
		if (this->_Width.empty())
			this->_Width = "";
		return _Width;
	}

	void VideoTrack::setWidth(const std::string &value)
	{
		this->_Width = value;
	}

	const std::string &VideoTrack::getHeight() const
	{
		if (this->_Height.empty())
			this->_Height = "";
		return _Height;
	}

	void VideoTrack::setHeight(const std::string &value)
	{
		this->_Height = value;
	}

	const std::string &VideoTrack::getAspectRatio() const
	{
		if (this->_AspectRatio.empty())
			this->_AspectRatio = "";
		return _AspectRatio;
	}

	void VideoTrack::setAspectRatio(const std::string &value)
	{
		this->_AspectRatio = value;
	}

	const std::string &VideoTrack::getAspectRatioString() const
	{
		if (this->_AspectRatioString.empty())
			this->_AspectRatioString = "";
		return _AspectRatioString;
	}

	void VideoTrack::setAspectRatioString(const std::string &value)
	{
		this->_AspectRatioString = value;
	}

	const std::string &VideoTrack::getPixelAspectRatio() const
	{
		if (this->_PixelAspectRatio.empty())
			this->_PixelAspectRatio = "";
		return _PixelAspectRatio;
	}

	void VideoTrack::setPixelAspectRatio(const std::string &value)
	{
		this->_PixelAspectRatio = value;
	}

	const std::string &VideoTrack::getPixelAspectRatioString() const
	{
		if (this->_PixelAspectRatioString.empty())
			this->_PixelAspectRatioString = "";
		return _PixelAspectRatioString;
	}

	void VideoTrack::setPixelAspectRatioString(const std::string &value)
	{
		this->_PixelAspectRatioString = value;
	}

	const std::string &VideoTrack::getFrameRate() const
	{
		if (this->_FrameRate.empty())
			this->_FrameRate = "";
		return _FrameRate;
	}

	void VideoTrack::setFrameRate(const std::string &value)
	{
		this->_FrameRate = value;
	}

	const std::string &VideoTrack::getFrameRateString() const
	{
		if (this->_FrameRateString.empty())
			this->_FrameRateString = "";
		return _FrameRateString;
	}

	void VideoTrack::setFrameRateString(const std::string &value)
	{
		this->_FrameRateString = value;
	}

	const std::string &VideoTrack::getFrameRateOriginal() const
	{
		if (this->_FrameRateOriginal.empty())
			this->_FrameRateOriginal = "";
		return _FrameRateOriginal;
	}

	void VideoTrack::setFrameRateOriginal(const std::string &value)
	{
		this->_FrameRateOriginal = value;
	}

	const std::string &VideoTrack::getFrameRateOriginalString() const
	{
		if (this->_FrameRateOriginalString.empty())
			this->_FrameRateOriginalString = "";
		return _FrameRateOriginalString;
	}

	void VideoTrack::setFrameRateOriginalString(const std::string &value)
	{
		this->_FrameRateOriginalString = value;
	}

	const std::string &VideoTrack::getFrameRateMode() const
	{
		if (this->_FrameRateMode.empty())
			this->_FrameRateMode = "";
		return _FrameRateMode;
	}

	void VideoTrack::setFrameRateMode(const std::string &value)
	{
		this->_FrameRateMode = value;
	}

	const std::string &VideoTrack::getFrameRateModeString() const
	{
		if (this->_FrameRateModeString.empty())
			this->_FrameRateModeString = "";
		return _FrameRateModeString;
	}

	void VideoTrack::setFrameRateModeString(const std::string &value)
	{
		this->_FrameRateModeString = value;
	}

	const std::string &VideoTrack::getFrameCount() const
	{
		if (this->_FrameCount.empty())
			this->_FrameCount = "";
		return _FrameCount;
	}

	void VideoTrack::setFrameCount(const std::string &value)
	{
		this->_FrameCount = value;
	}

	const std::string &VideoTrack::getBitDepth() const
	{
		if (this->_BitDepth.empty())
			this->_BitDepth = "";
		return _BitDepth;
	}

	void VideoTrack::setBitDepth(const std::string &value)
	{
		this->_BitDepth = value;
	}

	const std::string &VideoTrack::getBitsPixelFrame() const
	{
		if (this->_BitsPixelFrame.empty())
			this->_BitsPixelFrame = "";
		return _BitsPixelFrame;
	}

	void VideoTrack::setBitsPixelFrame(const std::string &value)
	{
		this->_BitsPixelFrame = value;
	}

	const std::string &VideoTrack::getDelay() const
	{
		if (this->_Delay.empty())
			this->_Delay = "";
		return _Delay;
	}

	void VideoTrack::setDelay(const std::string &value)
	{
		this->_Delay = value;
	}

	const std::string &VideoTrack::getDuration() const
	{
		if (this->_Duration.empty())
			this->_Duration = "";
		return _Duration;
	}

	void VideoTrack::setDuration(const std::string &value)
	{
		this->_Duration = value;
	}

	const std::string &VideoTrack::getDurationString() const
	{
		if (this->_DurationString.empty())
			this->_DurationString = "";
		return _DurationString;
	}

	void VideoTrack::setDurationString(const std::string &value)
	{
		this->_DurationString = value;
	}

	const std::string &VideoTrack::getDurationString1() const
	{
		if (this->_DurationString1.empty())
			this->_DurationString1 = "";
		return _DurationString1;
	}

	void VideoTrack::setDurationString1(const std::string &value)
	{
		this->_DurationString1 = value;
	}

	const std::string &VideoTrack::getDurationString2() const
	{
		if (this->_DurationString2.empty())
			this->_DurationString2 = "";
		return _DurationString2;
	}

	void VideoTrack::setDurationString2(const std::string &value)
	{
		this->_DurationString2 = value;
	}

	const std::string &VideoTrack::getDurationString3() const
	{
		if (this->_DurationString3.empty())
			this->_DurationString3 = "";
		return _DurationString3;
	}

	void VideoTrack::setDurationString3(const std::string &value)
	{
		this->_DurationString3 = value;
	}

	const std::string &VideoTrack::getLanguage() const
	{
		if (this->_Language.empty())
			this->_Language = "";
		return _Language;
	}

	void VideoTrack::setLanguage(const std::string &value)
	{
		this->_Language = value;
	}

	const std::string &VideoTrack::getLanguageString() const
	{
		if (this->_LanguageString.empty())
			this->_LanguageString = "";
		return _LanguageString;
	}

	void VideoTrack::setLanguageString(const std::string &value)
	{
		this->_LanguageString = value;
	}

	const std::string &VideoTrack::getLanguageMore() const
	{
		if (this->_LanguageMore.empty())
			this->_LanguageMore = "";
		return _LanguageMore;
	}

	void VideoTrack::setLanguageMore(const std::string &value)
	{
		this->_LanguageMore = value;
	}

	const std::string &VideoTrack::getFormat() const
	{
		if (this->_Format.empty())
			this->_Format = "";
		return _Format;
	}

	void VideoTrack::setFormat(const std::string &value)
	{
		this->_Format = value;
	}

	const std::string &VideoTrack::getFormatInfo() const
	{
		if (this->_FormatInfo.empty())
			this->_FormatInfo = "";
		return _FormatInfo;
	}

	void VideoTrack::setFormatInfo(const std::string &value)
	{
		this->_FormatInfo = value;
	}

	const std::string &VideoTrack::getFormatUrl() const
	{
		if (this->_FormatUrl.empty())
			this->_FormatUrl = "";
		return _FormatUrl;
	}

	void VideoTrack::setFormatUrl(const std::string &value)
	{
		this->_FormatUrl = value;
	}

	const std::string &VideoTrack::getFormatVersion() const
	{
		if (this->_FormatVersion.empty())
			this->_FormatVersion = "";
		return _FormatVersion;
	}

	void VideoTrack::setFormatVersion(const std::string &value)
	{
		this->_FormatVersion = value;
	}

	const std::string &VideoTrack::getFormatProfile() const
	{
		if (this->_FormatProfile.empty())
			this->_FormatProfile = "";
		return _FormatProfile;
	}

	void VideoTrack::setFormatProfile(const std::string &value)
	{
		this->_FormatProfile = value;
	}

	const std::string &VideoTrack::getFormatSettings() const
	{
		if (this->_FormatSettings.empty())
			this->_FormatSettings = "";
		return _FormatSettings;
	}

	void VideoTrack::setFormatSettings(const std::string &value)
	{
		this->_FormatSettings = value;
	}

	const std::string &VideoTrack::getFormatSettingsBVOP() const
	{
		if (this->_FormatSettingsBVOP.empty())
			this->_FormatSettingsBVOP = "";
		return _FormatSettingsBVOP;
	}

	void VideoTrack::setFormatSettingsBVOP(const std::string &value)
	{
		this->_FormatSettingsBVOP = value;
	}

	const std::string &VideoTrack::getFormatSettingsBVOPString() const
	{
		if (this->_FormatSettingsBVOPString.empty())
			this->_FormatSettingsBVOPString = "";
		return _FormatSettingsBVOPString;
	}

	void VideoTrack::setFormatSettingsBVOPString(const std::string &value)
	{
		this->_FormatSettingsBVOPString = value;
	}

	const std::string &VideoTrack::getFormatSettingsQPel() const
	{
		if (this->_FormatSettingsQPel.empty())
			this->_FormatSettingsQPel = "";
		return _FormatSettingsQPel;
	}

	void VideoTrack::setFormatSettingsQPel(const std::string &value)
	{
		this->_FormatSettingsQPel = value;
	}

	const std::string &VideoTrack::getFormatSettingsQPelString() const
	{
		if (this->_FormatSettingsQPelString.empty())
			this->_FormatSettingsQPelString = "";
		return _FormatSettingsQPelString;
	}

	void VideoTrack::setFormatSettingsQPelString(const std::string &value)
	{
		this->_FormatSettingsQPelString = value;
	}

	const std::string &VideoTrack::getFormatSettingsGMC() const
	{
		if (this->_FormatSettingsGMC.empty())
			this->_FormatSettingsGMC = "";
		return _FormatSettingsGMC;
	}

	void VideoTrack::setFormatSettingsGMC(const std::string &value)
	{
		this->_FormatSettingsGMC = value;
	}

	const std::string &VideoTrack::getFormatSettingsGMCString() const
	{
		if (this->_FormatSettingsGMCString.empty())
			this->_FormatSettingsGMCString = "";
		return _FormatSettingsGMCString;
	}

	void VideoTrack::setFormatSettingsGMCString(const std::string &value)
	{
		this->_FormatSettingsGMCString = value;
	}

	const std::string &VideoTrack::getFormatSettingsMatrix() const
	{
		if (this->_FormatSettingsMatrix.empty())
			this->_FormatSettingsMatrix = "";
		return _FormatSettingsMatrix;
	}

	void VideoTrack::setFormatSettingsMatrix(const std::string &value)
	{
		this->_FormatSettingsMatrix = value;
	}

	const std::string &VideoTrack::getFormatSettingsMatrixString() const
	{
		if (this->_FormatSettingsMatrixString.empty())
			this->_FormatSettingsMatrixString = "";
		return _FormatSettingsMatrixString;
	}

	void VideoTrack::setFormatSettingsMatrixString(const std::string &value)
	{
		this->_FormatSettingsMatrixString = value;
	}

	const std::string &VideoTrack::getFormatSettingsMatrixData() const
	{
		if (this->_FormatSettingsMatrixData.empty())
			this->_FormatSettingsMatrixData = "";
		return _FormatSettingsMatrixData;
	}

	void VideoTrack::setFormatSettingsMatrixData(const std::string &value)
	{
		this->_FormatSettingsMatrixData = value;
	}

	const std::string &VideoTrack::getFormatSettingsCABAC() const
	{
		if (this->_FormatSettingsCABAC.empty())
			this->_FormatSettingsCABAC = "";
		return _FormatSettingsCABAC;
	}

	void VideoTrack::setFormatSettingsCABAC(const std::string &value)
	{
		this->_FormatSettingsCABAC = value;
	}

	const std::string &VideoTrack::getFormatSettingsCABACString() const
	{
		if (this->_FormatSettingsCABACString.empty())
			this->_FormatSettingsCABACString = "";
		return _FormatSettingsCABACString;
	}

	void VideoTrack::setFormatSettingsCABACString(const std::string &value)
	{
		this->_FormatSettingsCABACString = value;
	}

	const std::string &VideoTrack::getFormatSettingsRefFrames() const
	{
		if (this->_FormatSettingsRefFrames.empty())
			this->_FormatSettingsRefFrames = "";
		return _FormatSettingsRefFrames;
	}

	void VideoTrack::setFormatSettingsRefFrames(const std::string &value)
	{
		this->_FormatSettingsRefFrames = value;
	}

	const std::string &VideoTrack::getFormatSettingsRefFramesString() const
	{
		if (this->_FormatSettingsRefFramesString.empty())
			this->_FormatSettingsRefFramesString = "";
		return _FormatSettingsRefFramesString;
	}

	void VideoTrack::setFormatSettingsRefFramesString(const std::string &value)
	{
		this->_FormatSettingsRefFramesString = value;
	}

	const std::string &VideoTrack::getFormatSettingsPulldown() const
	{
		if (this->_FormatSettingsPulldown.empty())
			this->_FormatSettingsPulldown = "";
		return _FormatSettingsPulldown;
	}

	void VideoTrack::setFormatSettingsPulldown(const std::string &value)
	{
		this->_FormatSettingsPulldown = value;
	}

	const std::string &VideoTrack::getScanType() const
	{
		if (this->_ScanType.empty())
			this->_ScanType = "";
		return _ScanType;
	}

	void VideoTrack::setScanType(const std::string &value)
	{
		this->_ScanType = value;
	}

	const std::string &VideoTrack::getScanTypeString() const
	{
		if (this->_ScanTypeString.empty())
			this->_ScanTypeString = "";
		return _ScanTypeString;
	}

	void VideoTrack::setScanTypeString(const std::string &value)
	{
		this->_ScanTypeString = value;
	}

	const std::string &VideoTrack::getDefault() const
	{
		if (this->_Default.empty())
			this->_Default = "";
		return _Default;
	}

	void VideoTrack::setDefault(const std::string &value)
	{
		this->_Default = value;
	}

	const std::string &VideoTrack::getDefaultString() const
	{
		if (this->_DefaultString.empty())
			this->_DefaultString = "";
		return _DefaultString;
	}

	void VideoTrack::setDefaultString(const std::string &value)
	{
		this->_DefaultString = value;
	}

	const std::string &VideoTrack::getForced() const
	{
		if (this->_Forced.empty())
			this->_Forced = "";
		return _Forced;
	}

	void VideoTrack::setForced(const std::string &value)
	{
		this->_Forced = value;
	}

	const std::string &VideoTrack::getForcedString() const
	{
		if (this->_ForcedString.empty())
			this->_ForcedString = "";
		return _ForcedString;
	}

	void VideoTrack::setForcedString(const std::string &value)
	{
		this->_ForcedString = value;
	}
}
