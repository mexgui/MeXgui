#include "TextTrack.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{

	const std::string &TextTrack::getCount() const
	{
		if (this->_Count.empty())
			this->_Count = "";
		return _Count;
	}

	void TextTrack::setCount(const std::string &value)
	{
		this->_Count = value;
	}

	const std::string &TextTrack::getStreamCount() const
	{
		if (this->_StreamCount.empty())
			this->_StreamCount = "";
		return _StreamCount;
	}

	void TextTrack::setStreamCount(const std::string &value)
	{
		this->_StreamCount = value;
	}

	const std::string &TextTrack::getStreamKind() const
	{
		if (this->_StreamKind.empty())
			this->_StreamKind = "";
		return _StreamKind;
	}

	void TextTrack::setStreamKind(const std::string &value)
	{
		this->_StreamKind = value;
	}

	const std::string &TextTrack::getStreamKindID() const
	{
		if (this->_StreamKindID.empty())
			this->_StreamKindID = "";
		return _StreamKindID;
	}

	void TextTrack::setStreamKindID(const std::string &value)
	{
		this->_StreamKindID = value;
	}

	const std::string &TextTrack::getStreamOrder() const
	{
		if (this->_StreamOrder.empty())
			this->_StreamOrder = "";
		return _StreamOrder;
	}

	void TextTrack::setStreamOrder(const std::string &value)
	{
		this->_StreamOrder = value;
	}

	const std::string &TextTrack::getInform() const
	{
		if (this->_Inform.empty())
			this->_Inform = "";
		return _Inform;
	}

	void TextTrack::setInform(const std::string &value)
	{
		this->_Inform = value;
	}

	const std::string &TextTrack::getID() const
	{
		if (this->_ID.empty())
			this->_ID = "";
		return _ID;
	}

	void TextTrack::setID(const std::string &value)
	{
		this->_ID = value;
	}

	const std::string &TextTrack::getUniqueID() const
	{
		if (this->_UniqueID.empty())
			this->_UniqueID = "";
		return _UniqueID;
	}

	void TextTrack::setUniqueID(const std::string &value)
	{
		this->_UniqueID = value;
	}

	const std::string &TextTrack::getTitle() const
	{
		if (this->_Title.empty())
			this->_Title = "";
		return _Title;
	}

	void TextTrack::setTitle(const std::string &value)
	{
		this->_Title = value;
	}

	const std::string &TextTrack::getCodec() const
	{
		if (this->_Codec.empty())
			this->_Codec = "";
		return _Codec;
	}

	void TextTrack::setCodec(const std::string &value)
	{
		this->_Codec = value;
	}

	const std::string &TextTrack::getCodecString() const
	{
		if (this->_CodecString.empty())
			this->_CodecString = "";
		return _CodecString;
	}

	void TextTrack::setCodecString(const std::string &value)
	{
		this->_CodecString = value;
	}

	const std::string &TextTrack::getCodecUrl() const
	{
		if (this->_CodecUrl.empty())
			this->_CodecUrl = "";
		return _CodecUrl;
	}

	void TextTrack::setCodecUrl(const std::string &value)
	{
		this->_CodecUrl = value;
	}

	const std::string &TextTrack::getDelay() const
	{
		if (this->_Delay.empty())
			this->_Delay = "";
		return _Delay;
	}

	void TextTrack::setDelay(const std::string &value)
	{
		this->_Delay = value;
	}

	const std::string &TextTrack::getVideo0Delay() const
	{
		if (this->_Video0Delay.empty())
			this->_Video0Delay = "";
		return _Video0Delay;
	}

	void TextTrack::setVideo0Delay(const std::string &value)
	{
		this->_Video0Delay = value;
	}

	const std::string &TextTrack::getPlayTime() const
	{
		if (this->_PlayTime.empty())
			this->_PlayTime = "";
		return _PlayTime;
	}

	void TextTrack::setPlayTime(const std::string &value)
	{
		this->_PlayTime = value;
	}

	const std::string &TextTrack::getPlayTimeString() const
	{
		if (this->_PlayTimeString.empty())
		this->_PlayTimeString = "";
		return _PlayTimeString;
	}

	void TextTrack::setPlayTimeString(const std::string &value)
	{
		this->_PlayTimeString = value;
	}

	const std::string &TextTrack::getPlayTimeString1() const
	{
		if (this->_PlayTimeString1.empty())
			this->_PlayTimeString1 = "";
		return _PlayTimeString1;
	}

	void TextTrack::setPlayTimeString1(const std::string &value)
	{
		this->_PlayTimeString1 = value;
	}

	const std::string &TextTrack::getPlayTimeString2() const
	{
		if (this->_PlayTimeString2.empty())
			this->_PlayTimeString2 = "";
		return _PlayTimeString2;
	}

	void TextTrack::setPlayTimeString2(const std::string &value)
	{
		this->_PlayTimeString2 = value;
	}

	const std::string &TextTrack::getPlayTimeString3() const
	{
		if (this->_PlayTimeString3.empty())
			this->_PlayTimeString3 = "";
		return _PlayTimeString3;
	}

	void TextTrack::setPlayTimeString3(const std::string &value)
	{
		this->_PlayTimeString3 = value;
	}

	const std::string &TextTrack::getLanguage() const
	{
		if (this->_Language.empty())
		this->_Language = "";
		return _Language;
	}

	void TextTrack::setLanguage(const std::string &value)
	{
		this->_Language = value;
	}

	const std::string &TextTrack::getLanguageString() const
	{
		if (this->_LanguageString.empty())
			this->_LanguageString = "";
		return _LanguageString;
	}

	void TextTrack::setLanguageString(const std::string &value)
	{
		this->_LanguageString = value;
	}

	const std::string &TextTrack::getLanguageMore() const
	{
		if (this->_LanguageMore.empty())
			this->_LanguageMore = "";
		return _LanguageMore;
	}

	void TextTrack::setLanguageMore(const std::string &value)
	{
		this->_LanguageMore = value;
	}

	const std::string &TextTrack::getDefault() const
	{
		if (this->_Default.empty())
			this->_Default = "";
		return _Default;
	}

	void TextTrack::setDefault(const std::string &value)
	{
		this->_Default = value;
	}

	const std::string &TextTrack::getDefaultString() const
	{
		if (this->_DefaultString.empty())
			this->_DefaultString = "";
		return _DefaultString;
	}

	void TextTrack::setDefaultString(const std::string &value)
	{
		this->_DefaultString = value;
	}

	const std::string &TextTrack::getForced() const
	{
		if (this->_Forced.empty())
			this->_Forced = "";
		return _Forced;
	}

	void TextTrack::setForced(const std::string &value)
	{
		this->_Forced = value;
	}

	const std::string &TextTrack::getForcedString() const
	{
		if (this->_ForcedString.empty())
			this->_ForcedString = "";
		return _ForcedString;
	}

	void TextTrack::setForcedString(const std::string &value)
	{
		this->_ForcedString = value;
	}
}
