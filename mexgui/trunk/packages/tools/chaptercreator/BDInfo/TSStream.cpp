#include "TSStream.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace BDInfo
{

	TSDescriptor::TSDescriptor(unsigned char name, unsigned char length)
	{
		Name = name;
		Value = new unsigned char[length];
	}

	TSDescriptor *TSDescriptor::Clone()
	{
		TSDescriptor *descriptor = new TSDescriptor(Name, static_cast<unsigned char>(sizeof(Value) / sizeof(Value[0])));
		Value->CopyTo(descriptor->Value, 0);
		return descriptor;
	}

	TSStream::TSStream()
	{
		InitializeInstanceFields();
	}

	std::string TSStream::ToString()
	{
		return std::string::Format("{0} ({1})", getCodecShortName(), PID);
	}

	const unsigned long long &TSStream::getPacketSize() const
	{
		return PacketCount * 192;
	}

	const std::string &TSStream::getLanguageCode() const
	{
		return _LanguageCode;
	}

	void TSStream::setLanguageCode(const std::string &value)
	{
		_LanguageCode = value;
		LanguageName = LanguageCodes::GetName(value);
	}

	const bool &TSStream::getIsVideoStream() const
	{
		switch (StreamType)
		{
			case MPEG1_VIDEO:
			case MPEG2_VIDEO:
			case AVC_VIDEO:
			case VC1_VIDEO:
				return true;

			default:
				return false;
		}
	}

	const bool &TSStream::getIsAudioStream() const
	{
		switch (StreamType)
		{
			case MPEG1_AUDIO:
			case MPEG2_AUDIO:
			case LPCM_AUDIO:
			case AC3_AUDIO:
			case AC3_PLUS_AUDIO:
			case AC3_PLUS_SECONDARY_AUDIO:
			case AC3_TRUE_HD_AUDIO:
			case DTS_AUDIO:
			case DTS_HD_AUDIO:
			case DTS_HD_SECONDARY_AUDIO:
			case DTS_HD_MASTER_AUDIO:
				return true;

			default:
				return false;
		}
	}

	const bool &TSStream::getIsGraphicsStream() const
	{
		switch (StreamType)
		{
			case PRESENTATION_GRAPHICS:
			case INTERACTIVE_GRAPHICS:
				return true;

			default:
				return false;
		}
	}

	const bool &TSStream::getIsTextStream() const
	{
		switch (StreamType)
		{
			case SUBTITLE:
				return true;

			default:
				return false;
		}
	}

	const std::string &TSStream::getCodecName() const
	{
		switch (StreamType)
		{
			case MPEG1_VIDEO:
				return "MPEG-1 Video";
			case MPEG2_VIDEO:
				return "MPEG-2 Video";
			case AVC_VIDEO:
				return "MPEG-4 AVC Video";
			case VC1_VIDEO:
				return "VC-1 Video";
			case MPEG1_AUDIO:
				return "MP1 Audio";
			case MPEG2_AUDIO:
				return "MP2 Audio";
			case LPCM_AUDIO:
				return "LPCM Audio";
			case AC3_AUDIO:
				if ((static_cast<TSAudioStream*>(this))->AudioMode == Extended)
					return "Dolby Digital EX Audio";
				else
					return "Dolby Digital Audio";
			case AC3_PLUS_AUDIO:
			case AC3_PLUS_SECONDARY_AUDIO:
				return "Dolby Digital Plus Audio";
			case AC3_TRUE_HD_AUDIO:
				return "Dolby TrueHD Audio";
			case DTS_AUDIO:
				if ((static_cast<TSAudioStream*>(this))->AudioMode == Extended)
					return "DTS-ES Audio";
				else
					return "DTS Audio";
			case DTS_HD_AUDIO:
				return "DTS-HD Audio";
			case DTS_HD_SECONDARY_AUDIO:
				return "DTS Express";
			case DTS_HD_MASTER_AUDIO:
				return "DTS-HD Master Audio";
			case PRESENTATION_GRAPHICS:
				return "Presentation Graphics";
			case INTERACTIVE_GRAPHICS:
				return "Interactive Graphics";
			case SUBTITLE:
				return "Subtitle";
			default:
				return "UNKNOWN";
		}
	}

	const std::string &TSStream::getCodecAltName() const
	{
		switch (StreamType)
		{
			case MPEG1_VIDEO:
				return "MPEG-1";
			case MPEG2_VIDEO:
				return "MPEG-2";
			case AVC_VIDEO:
				return "AVC";
			case VC1_VIDEO:
				return "VC-1";
			case MPEG1_AUDIO:
				return "MP1";
			case MPEG2_AUDIO:
				return "MP2";
			case LPCM_AUDIO:
				return "LPCM";
			case AC3_AUDIO:
				return "DD AC3";
			case AC3_PLUS_AUDIO:
			case AC3_PLUS_SECONDARY_AUDIO:
				return "DD AC3+";
			case AC3_TRUE_HD_AUDIO:
				return "Dolby TrueHD";
			case DTS_AUDIO:
				return "DTS";
			case DTS_HD_AUDIO:
				return "DTS-HD Hi-Res";
			case DTS_HD_SECONDARY_AUDIO:
				return "DTS Express";
			case DTS_HD_MASTER_AUDIO:
				return "DTS-HD Master";
			case PRESENTATION_GRAPHICS:
				return "PGS";
			case INTERACTIVE_GRAPHICS:
				return "IGS";
			case SUBTITLE:
				return "SUB";
			default:
				return "UNKNOWN";
		}
	}

	const std::string &TSStream::getCodecShortName() const
	{
		switch (StreamType)
		{
			case MPEG1_VIDEO:
				return "MPEG-1";
			case MPEG2_VIDEO:
				return "MPEG-2";
			case AVC_VIDEO:
				return "AVC";
			case VC1_VIDEO:
				return "VC-1";
			case MPEG1_AUDIO:
				return "MP1";
			case MPEG2_AUDIO:
				return "MP2";
			case LPCM_AUDIO:
				return "LPCM";
			case AC3_AUDIO:
				if ((static_cast<TSAudioStream*>(this))->AudioMode == Extended)
					return "AC3-EX";
				else
					return "AC3";
			case AC3_PLUS_AUDIO:
			case AC3_PLUS_SECONDARY_AUDIO:
				return "AC3+";
			case AC3_TRUE_HD_AUDIO:
				return "TrueHD";
			case DTS_AUDIO:
				if ((static_cast<TSAudioStream*>(this))->AudioMode == Extended)
					return "DTS-ES";
				else
					return "DTS";
			case DTS_HD_AUDIO:
				return "DTS-HD HR";
			case DTS_HD_SECONDARY_AUDIO:
				return "DTS Express";
			case DTS_HD_MASTER_AUDIO:
				return "DTS-HD MA";
			case PRESENTATION_GRAPHICS:
				return "PGS";
			case INTERACTIVE_GRAPHICS:
				return "IGS";
			case SUBTITLE:
				return "SUB";
			default:
				return "UNKNOWN";
		}
	}

	const std::string &TSStream::getDescription() const
	{
		return "";
	}

	void TSStream::CopyTo(TSStream *stream)
	{
		stream->PID = PID;
		stream->StreamType = StreamType;
		stream->IsVBR = IsVBR;
		stream->BitRate = BitRate;
		stream->IsInitialized = IsInitialized;
		stream->setLanguageCode(_LanguageCode);
		if (Descriptors.size() > 0)
		{
			stream->Descriptors = std::vector<TSDescriptor*>();
			for (std::vector<TSDescriptor*>::const_iterator descriptor = Descriptors.begin(); descriptor != Descriptors.end(); ++descriptor)
			{
				stream->Descriptors.push_back((*descriptor)->Clone());
			}
		}
	}

	void TSStream::InitializeInstanceFields()
	{
		Descriptors.clear();
		BitRate = 0;
		ActiveBitRate = 0;
		IsVBR = false;
		IsInitialized = false;
		PayloadBytes = 0;
		PacketCount = 0;
		PacketSeconds = 0;
		AngleIndex = 0;
	}

	TSVideoStream::TSVideoStream()
	{
	}

	const TSVideoFormat &TSVideoStream::getVideoFormat() const
	{
		return _VideoFormat;
	}

	void TSVideoStream::setVideoFormat(const TSVideoFormat &value)
	{
		_VideoFormat = value;
		switch (value)
		{
			case VIDEOFORMAT_480i:
				Height = 480;
				IsInterlaced = true;
				break;
			case VIDEOFORMAT_480p:
				Height = 480;
				IsInterlaced = false;
				break;
			case VIDEOFORMAT_576i:
				Height = 576;
				IsInterlaced = true;
				break;
			case VIDEOFORMAT_576p:
				Height = 576;
				IsInterlaced = false;
				break;
			case VIDEOFORMAT_720p:
				Height = 720;
				IsInterlaced = false;
				break;
			case VIDEOFORMAT_1080i:
				Height = 1080;
				IsInterlaced = true;
				break;
			case VIDEOFORMAT_1080p:
				Height = 1080;
				IsInterlaced = false;
				break;
		}
	}

	const TSFrameRate &TSVideoStream::getFrameRate() const
	{
		return _FrameRate;
	}

	void TSVideoStream::setFrameRate(const TSFrameRate &value)
	{
		_FrameRate = value;
		switch (value)
		{
			case FRAMERATE_23_976:
				FrameRateEnumerator = 24000;
				FrameRateDenominator = 1001;
				break;
			case FRAMERATE_24:
				FrameRateEnumerator = 24000;
				FrameRateDenominator = 1000;
				break;
			case FRAMERATE_25:
				FrameRateEnumerator = 25000;
				FrameRateDenominator = 1000;
				break;
			case FRAMERATE_29_97:
				FrameRateEnumerator = 30000;
				FrameRateDenominator = 1001;
				break;
			case FRAMERATE_50:
				FrameRateEnumerator = 50000;
				FrameRateDenominator = 1000;
				break;
			case FRAMERATE_59_94:
				FrameRateEnumerator = 60000;
				FrameRateDenominator = 1001;
				break;
		}
	}

	const std::string &TSVideoStream::getDescription() const
	{
		std::string description = "";

		if (Height > 0)
		{
			description += std::string::Format("{0:D}{1} / ", Height, IsInterlaced ? "i" : "p");
		}
		if (FrameRateEnumerator > 0 && FrameRateDenominator > 0)
		{
			if (FrameRateEnumerator % FrameRateDenominator == 0)
			{
				description += std::string::Format("{0:D} fps / ", FrameRateEnumerator / FrameRateDenominator);
			}
			else
			{
				description += std::string::Format("{0:F3} fps / ", static_cast<double>(FrameRateEnumerator) / FrameRateDenominator);
			}

		}
		if (AspectRatio == ASPECT_4_3)
		{
			description += "4:3 / ";
		}
		else if (AspectRatio == ASPECT_16_9)
		{
			description += "16:9 / ";
		}
		if (EncodingProfile != "")
		{
			description += EncodingProfile + " / ";
		}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (description.EndsWith(" / "))
		{
			description = description.substr(0, description.length() - 3);
		}
		return description;
	}

	TSStream *TSVideoStream::Clone()
	{
		TSVideoStream *stream = new TSVideoStream();
		CopyTo(stream);

		stream->setVideoFormat(_VideoFormat);
		stream->setFrameRate(_FrameRate);
		stream->Width = Width;
		stream->Height = Height;
		stream->IsInterlaced = IsInterlaced;
		stream->FrameRateEnumerator = FrameRateEnumerator;
		stream->FrameRateDenominator = FrameRateDenominator;
		stream->AspectRatio = AspectRatio;
		stream->EncodingProfile = EncodingProfile;

		return stream;
	}

	TSAudioStream::TSAudioStream()
	{
	}

	int TSAudioStream::ConvertSampleRate(TSSampleRate sampleRate)
	{
		switch (sampleRate)
		{
			case SAMPLERATE_48:
				return 48000;

			case SAMPLERATE_96:
			case SAMPLERATE_48_96:
				return 96000;

			case SAMPLERATE_192:
			case SAMPLERATE_48_192:
				return 192000;
		}
		return 0;
	}

	const std::string &TSAudioStream::getChannelDescription() const
	{
		std::string description = "";
		if (ChannelCount > 0)
		{
			description += std::string::Format("{0:D}.{1:D}", ChannelCount, LFE);
		}
		else
		{
			switch (ChannelLayout)
			{
				case CHANNELLAYOUT_MONO:
					description += "1.0";
					break;
				case CHANNELLAYOUT_STEREO:
					description += "2.0";
					break;
				case CHANNELLAYOUT_MULTI:
					description += "5.1";
					break;
			}
		}
		if (AudioMode == Extended)
		{
			if (StreamType == AC3_AUDIO)
			{
				description += "-EX";
			}
			if (StreamType == DTS_AUDIO)
			{
				description += "-ES";
			}
		}
		return description;
	}

	const std::string &TSAudioStream::getDescription() const
	{
		std::string description = getChannelDescription();

		if (SampleRate > 0)
		{
			description += std::string::Format(" / {0:D} kHz", SampleRate / 1000);
		}
		if (BitRate > 0)
		{
			description += std::string::Format(" / {0:D} kbps", static_cast<unsigned int>(Math::Round(static_cast<double>(BitRate) / 1000)));
		}
		if (BitDepth > 0)
		{
			description += std::string::Format(" / {0:D}-bit", BitDepth);
		}
		if (ChannelCount == 2)
		{
			switch (AudioMode)
			{
				case DualMono:
					description += " / Dual Mono";
					break;

				case Surround:
					description += " / Dolby Surround";
					break;
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (description.EndsWith(" / "))
		{
			description = description.substr(0, description.length() - 3);
		}
		if (CoreStream != 0)
		{
			std::string codec = "";
			switch (CoreStream->StreamType)
			{
				case AC3_AUDIO:
					codec = "AC3";
					break;
				case DTS_AUDIO:
					codec = "DTS";
					break;
			}
			description += std::string::Format(" ({0} Core: {1})", codec, CoreStream->getDescription());
		}
		return description;
	}

	TSStream *TSAudioStream::Clone()
	{
		TSAudioStream *stream = new TSAudioStream();
		CopyTo(stream);

		stream->SampleRate = SampleRate;
		stream->ChannelLayout = ChannelLayout;
		stream->ChannelCount = ChannelCount;
		stream->BitDepth = BitDepth;
		stream->LFE = LFE;
		stream->DialNorm = DialNorm;
		stream->AudioMode = AudioMode;
		if (CoreStream != 0)
		{
			stream->CoreStream = static_cast<TSAudioStream*>(CoreStream->Clone());
		}

		return stream;
	}

	TSGraphicsStream::TSGraphicsStream()
	{
		IsVBR = true;
		IsInitialized = true;
	}

	TSStream *TSGraphicsStream::Clone()
	{
		TSGraphicsStream *stream = new TSGraphicsStream();
		CopyTo(stream);
		return stream;
	}

	TSTextStream::TSTextStream()
	{
		IsVBR = true;
		IsInitialized = true;
	}

	TSStream *TSTextStream::Clone()
	{
		TSTextStream *stream = new TSTextStream();
		CopyTo(stream);
		return stream;
	}
}
