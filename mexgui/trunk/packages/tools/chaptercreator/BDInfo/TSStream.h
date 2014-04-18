#pragma once

#include "LanguageCodes.h"
#include <string>
#include <vector>
#include <cmath>

// ****************************************************************************
// 
// Copyright (C) 2009  Cinema Squid
// 
// code from http://www.cinemasquid.com/blu-ray/tools/bdinfo
// 
// ****************************************************************************

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace BDInfo
{
	enum TSStreamType
	{
		Unknown = 0,
		MPEG1_VIDEO = 0x01,
		MPEG2_VIDEO = 0x02,
		AVC_VIDEO = 0x1b,
		VC1_VIDEO = 0xea,
		MPEG1_AUDIO = 0x03,
		MPEG2_AUDIO = 0x04,
		LPCM_AUDIO = 0x80,
		AC3_AUDIO = 0x81,
		AC3_PLUS_AUDIO = 0x84,
		AC3_PLUS_SECONDARY_AUDIO = 0xA1,
		AC3_TRUE_HD_AUDIO = 0x83,
		DTS_AUDIO = 0x82,
		DTS_HD_AUDIO = 0x85,
		DTS_HD_SECONDARY_AUDIO = 0xA2,
		DTS_HD_MASTER_AUDIO = 0x86,
		PRESENTATION_GRAPHICS = 0x90,
		INTERACTIVE_GRAPHICS = 0x91,
		SUBTITLE = 0x92
	};

	enum TSVideoFormat
	{
		Unknown = 0,
		VIDEOFORMAT_480i = 1,
		VIDEOFORMAT_576i = 2,
		VIDEOFORMAT_480p = 3,
		VIDEOFORMAT_1080i = 4,
		VIDEOFORMAT_720p = 5,
		VIDEOFORMAT_1080p = 6,
		VIDEOFORMAT_576p = 7,
	};

	enum TSFrameRate
	{
		Unknown = 0,
		FRAMERATE_23_976 = 1,
		FRAMERATE_24 = 2,
		FRAMERATE_25 = 3,
		FRAMERATE_29_97 = 4,
		FRAMERATE_50 = 6,
		FRAMERATE_59_94 = 7
	};

	enum TSChannelLayout
	{
		Unknown = 0,
		CHANNELLAYOUT_MONO = 1,
		CHANNELLAYOUT_STEREO = 3,
		CHANNELLAYOUT_MULTI = 6,
		CHANNELLAYOUT_COMBO = 12
	};

	enum TSSampleRate
	{
		Unknown = 0,
		SAMPLERATE_48 = 1,
		SAMPLERATE_96 = 4,
		SAMPLERATE_192 = 5,
		SAMPLERATE_48_192 = 12,
		SAMPLERATE_48_96 = 14
	};

	enum TSAspectRatio
	{
		Unknown = 0,
		ASPECT_4_3 = 2,
		ASPECT_16_9 = 3,
		ASPECT_2_21 = 4
	};

	class TSDescriptor
	{
	public:
		unsigned char Name;
//ORIGINAL LINE: public byte[] Value;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		unsigned char *Value;

		TSDescriptor(unsigned char name, unsigned char length);

		TSDescriptor *Clone();
	};

	class TSStream
	{
	public:
		TSStream();

		virtual std::string ToString();

		unsigned short PID;
		TSStreamType StreamType;
		std::vector<TSDescriptor*> Descriptors;
		long long BitRate;
		long long ActiveBitRate;
		bool IsVBR;
		bool IsInitialized;
		std::string LanguageName;

		unsigned long long PayloadBytes;
		unsigned long long PacketCount;
		double PacketSeconds;
		int AngleIndex;

		const unsigned long long &getPacketSize() const;

	private:
		std::string _LanguageCode;
	public:
		const std::string &getLanguageCode() const;
		void setLanguageCode(const std::string &value);

		const bool &getIsVideoStream() const;

		const bool &getIsAudioStream() const;

		const bool &getIsGraphicsStream() const;

		const bool &getIsTextStream() const;

		const std::string &getCodecName() const;

		const std::string &getCodecAltName() const;

		const std::string &getCodecShortName() const;

		const virtual std::string &getDescription() const;

		virtual TSStream *Clone() = 0;

	protected:
		void CopyTo(TSStream *stream);

	private:
		void InitializeInstanceFields();
	};

	class TSVideoStream : public TSStream
	{
	public:
		TSVideoStream();

		int Width;
		int Height;
		bool IsInterlaced;
		int FrameRateEnumerator;
		int FrameRateDenominator;
		TSAspectRatio AspectRatio;
		std::string EncodingProfile;

	private:
		TSVideoFormat _VideoFormat;
	public:
		const TSVideoFormat &getVideoFormat() const;
		void setVideoFormat(const TSVideoFormat &value);

	private:
		TSFrameRate _FrameRate;
	public:
		const TSFrameRate &getFrameRate() const;
		void setFrameRate(const TSFrameRate &value);

		const virtual std::string &getDescription() const;

		virtual TSStream *Clone();
	};

	enum TSAudioMode
	{
		Unknown,
		DualMono,
		Stereo,
		Surround,
		Extended
	};

	class TSAudioStream : public TSStream
	{
	public:
		TSAudioStream();

		int SampleRate;
		int ChannelCount;
		int BitDepth;
		int LFE;
		int DialNorm;
		TSAudioMode AudioMode;
		TSAudioStream *CoreStream;
		TSChannelLayout ChannelLayout;

		static int ConvertSampleRate(TSSampleRate sampleRate);

		const std::string &getChannelDescription() const;

		const virtual std::string &getDescription() const;

		virtual TSStream *Clone();
	};

	class TSGraphicsStream : public TSStream
	{
	public:
		TSGraphicsStream();

		virtual TSStream *Clone();
	};

	class TSTextStream : public TSStream
	{
	public:
		TSTextStream();

		virtual TSStream *Clone();
	};
}
