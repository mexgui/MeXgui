#include "ChaptersTrack.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{

	const std::string &ChaptersTrack::getCount() const
	{
		if (this->_Count.empty())
			this->_Count = "";
		return _Count;
	}

	void ChaptersTrack::setCount(const std::string &value)
	{
		this->_Count = value;
	}

	const std::string &ChaptersTrack::getStreamCount() const
	{
		if (this->_StreamCount.empty())
			this->_StreamCount = "";
		return _StreamCount;
	}

	void ChaptersTrack::setStreamCount(const std::string &value)
	{
		this->_StreamCount = value;
	}

	const std::string &ChaptersTrack::getStreamKind() const
	{
		if (this->_StreamKind.empty())
			this->_StreamKind = "";
		return _StreamKind;
	}

	void ChaptersTrack::setStreamKind(const std::string &value)
	{
		this->_StreamKind = value;
	}

	const std::string &ChaptersTrack::getStreamKindID() const
	{
		if (this->_StreamKindID.empty())
			this->_StreamKindID = "";
		return _StreamKindID;
	}

	void ChaptersTrack::setStreamKindID(const std::string &value)
	{
		this->_StreamKindID = value;
	}

	const std::string &ChaptersTrack::getStreamOrder() const
	{
		if (this->_StreamOrder.empty())
			this->_StreamOrder = "";
		return _StreamOrder;
	}

	void ChaptersTrack::setStreamOrder(const std::string &value)
	{
		this->_StreamOrder = value;
	}

	const std::string &ChaptersTrack::getInform() const
	{
		if (this->_Inform.empty())
			this->_Inform = "";
		return _Inform;
	}

	void ChaptersTrack::setInform(const std::string &value)
	{
		this->_Inform = value;
	}

	const std::string &ChaptersTrack::getID() const
	{
		if (this->_ID.empty())
			this->_ID = "";
		return _ID;
	}

	void ChaptersTrack::setID(const std::string &value)
	{
		this->_ID = value;
	}

	const std::string &ChaptersTrack::getUniqueID() const
	{
		if (this->_UniqueID.empty())
			this->_UniqueID = "";
		return _UniqueID;
	}

	void ChaptersTrack::setUniqueID(const std::string &value)
	{
		this->_UniqueID = value;
	}

	const std::string &ChaptersTrack::getTitle() const
	{
		if (this->_Title.empty())
			this->_Title = "";
		return _Title;
	}

	void ChaptersTrack::setTitle(const std::string &value)
	{
		this->_Title = value;
	}

	const std::string &ChaptersTrack::getCodec() const
	{
		if (this->_Codec.empty())
			this->_Codec = "";
		return _Codec;
	}

	void ChaptersTrack::setCodec(const std::string &value)
	{
		this->_Codec = value;
	}

	const std::string &ChaptersTrack::getCodecString() const
	{
		if (this->_CodecString.empty())
			this->_CodecString = "";
		return _CodecString;
	}

	void ChaptersTrack::setCodecString(const std::string &value)
	{
		this->_CodecString = value;
	}

	const std::string &ChaptersTrack::getCodecUrl() const
	{
		if (this->_CodecUrl.empty())
			this->_CodecUrl = "";
		return _CodecUrl;
	}

	void ChaptersTrack::setCodecUrl(const std::string &value)
	{
		this->_CodecUrl = value;
	}

	const std::string &ChaptersTrack::getTotal() const
	{
		if (this->_Total.empty())
			this->_Total = "";
		return _Total;
	}

	void ChaptersTrack::setTotal(const std::string &value)
	{
		this->_Total = value;
	}

	const std::string &ChaptersTrack::getLanguage() const
	{
		if (this->_Language.empty())
			this->_Language = "";
		return _Language;
	}

	void ChaptersTrack::setLanguage(const std::string &value)
	{
		this->_Language = value;
	}

	const std::string &ChaptersTrack::getLanguageString() const
	{
		if (this->_LanguageString.empty())
			this->_LanguageString = "";
		return _LanguageString;
	}

	void ChaptersTrack::setLanguageString(const std::string &value)
	{
		this->_LanguageString = value;
	}

	const std::string &ChaptersTrack::getDefault() const
	{
		if (this->_Default.empty())
			this->_Default = "";
		return _Default;
	}

	void ChaptersTrack::setDefault(const std::string &value)
	{
		this->_Default = value;
	}

	const std::string &ChaptersTrack::getDefaultString() const
	{
		if (this->_DefaultString.empty())
			this->_DefaultString = "";
		return _DefaultString;
	}

	void ChaptersTrack::setDefaultString(const std::string &value)
	{
		this->_DefaultString = value;
	}

	const std::string &ChaptersTrack::getForced() const
	{
		if (this->_Forced.empty())
			this->_Forced = "";
		return _Forced;
	}

	void ChaptersTrack::setForced(const std::string &value)
	{
		this->_Forced = value;
	}

	const std::string &ChaptersTrack::getForcedString() const
	{
		if (this->_ForcedString.empty())
			this->_ForcedString = "";
		return _ForcedString;
	}

	void ChaptersTrack::setForcedString(const std::string &value)
	{
		this->_ForcedString = value;
	}
}
