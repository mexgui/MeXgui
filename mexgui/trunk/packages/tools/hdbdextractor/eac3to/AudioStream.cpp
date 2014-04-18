#include "AudioStream.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace eac3to
{

	const AudioStreamType &AudioStream::getAudioType() const
	{
		return privateAudioType;
	}

	void AudioStream::setAudioType(const AudioStreamType &value)
	{
		privateAudioType = value;
	}

	const std::string &AudioStream::getLanguage() const
	{
		return privateLanguage;
	}

	void AudioStream::setLanguage(const std::string &value)
	{
		privateLanguage = value;
	}

	const std::string &AudioStream::getChannels() const
	{
		return privateChannels;
	}

	void AudioStream::setChannels(const std::string &value)
	{
		privateChannels = value;
	}

	const std::string &AudioStream::getBitrate() const
	{
		return privateBitrate;
	}

	void AudioStream::setBitrate(const std::string &value)
	{
		privateBitrate = value;
	}

	const std::string &AudioStream::getDialogNormalization() const
	{
		return privateDialogNormalization;
	}

	void AudioStream::setDialogNormalization(const std::string &value)
	{
		privateDialogNormalization = value;
	}

	const std::string &AudioStream::getDelay() const
	{
		return privateDelay;
	}

	void AudioStream::setDelay(const std::string &value)
	{
		privateDelay = value;
	}

	const object &AudioStream::getExtractTypes() const
	{
		switch (getAudioType())
		{
			case EAC3:
				return new object[] {"EAC3", "AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			case DTS:
				return new object[] {"DTS", "DTSHD", "AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			case TrueHD:
				return new object[] {"THD", "THD+AC3", "AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			case MP2:
				return new object[] {"MP2", "AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			case MP3:
				return new object[] {"MP3", "AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			case AAC:
				return new object[] {"AAC", "AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			case FLAC:
				return new object[] {"FLAC", "AC3", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			case VORBIS:
				return new object[] {"OGG", "AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			case TTA:
				return new object[] {"TTA", "AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			case WAVPACK:
				return new object[] {"WV", "AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
			default:
				return new object[] {"AC3", "FLAC", "AAC", "WAV", "WAVS", "RAW", "W64", "RF64", "AGM"};
		}
	}

	AudioStream::AudioStream(const std::string &s) : Stream(s)
	{
		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		Stream::setType(Audio);
	}

	Stream *AudioStream::Parse(const std::string &s)
	{
		//2: AC3, English, 2.0 channels, 192kbps, 48khz, dialnorm: -27dB, -8ms
		//4: TrueHD, English, 5.1 channels, 48khz, dialnorm: -27dB

		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		AudioStream *audioStream = new AudioStream(s);

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (audioStream.Name.ToUpper(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "AC3":
		if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "AC3" || audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "AC3 EX" || audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "AC3 SURROUND")
		{
				audioStream->setAudioType(AC3);
		}
//ORIGINAL LINE: case "DTS":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "DTS" || audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "DTS-ES" || audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "DTS MASTER AUDIO" || audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "DTS HI-RES")
		{
				audioStream->setAudioType(DTS);
		}
//ORIGINAL LINE: case "E-AC3":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "E-AC3")
		{
				audioStream->setAudioType(EAC3);
		}
//ORIGINAL LINE: case "TRUEHD":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "TRUEHD")
		{
				audioStream->setAudioType(TrueHD);
		}
//ORIGINAL LINE: case "TRUEHD/AC3":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "TRUEHD/AC3")
		{
				audioStream->setAudioType(TrueHD | AC3);
		}
//ORIGINAL LINE: case "PCM":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "PCM")
		{
				audioStream->setAudioType(PCM);
		}
//ORIGINAL LINE: case "WAV":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "WAV")
		{
				audioStream->setAudioType(WAV);
		}
//ORIGINAL LINE: case "WAVS":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "WAVS")
		{
				audioStream->setAudioType(WAVS);
		}
//ORIGINAL LINE: case "MP2":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "MP2")
		{
				audioStream->setAudioType(MP2);
		}
//ORIGINAL LINE: case "MP3":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "MP3")
		{
				audioStream->setAudioType(MP3);
		}
//ORIGINAL LINE: case "AAC":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "AAC")
		{
				audioStream->setAudioType(AAC);
		}
//ORIGINAL LINE: case "FLAC":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "FLAC")
		{
				audioStream->setAudioType(FLAC);
		}
//ORIGINAL LINE: case "TTA1":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "TTA1")
		{
				audioStream->setAudioType(TTA);
		}
//ORIGINAL LINE: case "WAVPACK4":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "WAVPACK4")
		{
				audioStream->setAudioType(WAVPACK);
		}
//ORIGINAL LINE: case "VORBIS":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "VORBIS")
		{
				audioStream->setAudioType(VORBIS);
		}
//ORIGINAL LINE: case "RAW":
		else if (audioStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "RAW")
		{
		}
		else
		{
				audioStream->setAudioType(RAW);
		}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		audioStream->setLanguage((s.find(',') == s.rfind(',')) ? s.substr(s.find(',') + 1)->Trim() : s.substr(s.find(',') + 1, s.rfind(',') - s.find(',') - 1)->Trim());

		return audioStream;
	}

	std::string AudioStream::ToString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return Stream::ToString();
	}
}
