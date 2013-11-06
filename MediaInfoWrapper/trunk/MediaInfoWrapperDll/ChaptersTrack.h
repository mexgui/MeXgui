#pragma once

#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{
	///<summary>Contains properties for a ChaptersTrack </summary>
	class ChaptersTrack
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
		std::string _CodecUrl;
		std::string _Total;
		std::string _Language;
		std::string _LanguageString;
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

		///<summary> Codec used (test) </summary>
		const std::string &getCodecString() const;
		void setCodecString(const std::string &value);

		///<summary> Codec used (test) </summary>
		const std::string &getCodecUrl() const;
		void setCodecUrl(const std::string &value);

		///<summary> Total number of chapters </summary>
		const std::string &getTotal() const;
		void setTotal(const std::string &value);

		///<summary> Language (2 letters) </summary>
		const std::string &getLanguage() const;
		void setLanguage(const std::string &value);

		///<summary> Language (full) </summary>
		const std::string &getLanguageString() const;
		void setLanguageString(const std::string &value);

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
