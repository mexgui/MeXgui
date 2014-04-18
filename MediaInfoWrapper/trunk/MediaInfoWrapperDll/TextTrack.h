#pragma once

#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{
	///<summary>Contains properties for a TextTrack </summary>
	class TextTrack
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
		std::string _Delay;
		std::string _Video0Delay;
		std::string _PlayTime;
		std::string _PlayTimeString;
		std::string _PlayTimeString1;
		std::string _PlayTimeString2;
		std::string _PlayTimeString3;
		std::string _Language;
		std::string _LanguageString;
		std::string _LanguageMore;
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

		///<summary> Delay fixed in the stream (relative) </summary>
		const std::string &getDelay() const;
		void setDelay(const std::string &value);

		///<summary> Delay fixed in the stream (absolute _ video0) </summary>
		const std::string &getVideo0Delay() const;
		void setVideo0Delay(const std::string &value);

		///<summary> Play time of the stream </summary>
		const std::string &getPlayTime() const;
		void setPlayTime(const std::string &value);

		///<summary> Play time (formated) </summary>
		const std::string &getPlayTimeString() const;
		void setPlayTimeString(const std::string &value);

		///<summary> Play time in format : HHh MMmn SSs MMMms, XX omited if zero </summary>
		const std::string &getPlayTimeString1() const;
		void setPlayTimeString1(const std::string &value);

		///<summary> Play time in format : XXx YYy only, YYy omited if zero </summary>
		const std::string &getPlayTimeString2() const;
		void setPlayTimeString2(const std::string &value);

		///<summary> Play time in format : HH:MM:SS.MMM </summary>
		const std::string &getPlayTimeString3() const;
		void setPlayTimeString3(const std::string &value);

		///<summary> Language (2 letters) </summary>
		const std::string &getLanguage() const;
		void setLanguage(const std::string &value);

		///<summary> Language (full) </summary>
		const std::string &getLanguageString() const;
		void setLanguageString(const std::string &value);

		///<summary> More info about Language (director s comment...) </summary>
		const std::string &getLanguageMore() const;
		void setLanguageMore(const std::string &value);

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
