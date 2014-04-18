#include "AudioCodecSettings.h"




//using namespace System::Collections::Generic;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::plugins::interfaces;

namespace MeXgui
{

	const QString &AudioCodecSettings::getSettingsID() const
	{
		return id;
	}

	void AudioCodecSettings::FixFileNames(QMap<QString, QString> &_)
	{
	}

	const AudioCodec &AudioCodecSettings::getCodec() const
	{
		return audioCodec;
	}

	void AudioCodecSettings::setCodec(const AudioCodec &value)
	{
		audioCodec = value;
	}

	const AudioEncoderType &AudioCodecSettings::getEncoderType() const
	{
		return audioEncoderType;
	}

	void AudioCodecSettings::setEncoderType(const AudioEncoderType &value)
	{
		audioEncoderType = value;
	}

	AudioCodecSettings::AudioCodecSettings(const QString &id, AudioCodec *codec, AudioEncoderType *encoder, int bitrate)
	{

	}

	AudioCodecSettings::AudioCodecSettings(const QString &id, AudioCodec *codec, AudioEncoderType *encoder, int bitrate, BitrateManagementMode mode) : id(id)
	{
		audioCodec = codec;
		audioEncoderType = encoder;
		downmixMode = KeepOriginal;
		bitrateMode = mode;
		this->bitrate = bitrate;
		delay = 0;
		delayEnabled = false;
		autoGain = false;
		applyDRC = false;
		sampleRateType = 0;
		normalize = 100;
		preferredDecoder = NicAudio;
	}

	const AudioDecodingEngine &AudioCodecSettings::getPreferredDecoder() const
	{
		return preferredDecoder;
	}

	void AudioCodecSettings::setPreferredDecoder(const AudioDecodingEngine &value)
	{
		preferredDecoder = value;
	}

	const QString &AudioCodecSettings::getPreferredDecoderString() const
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return preferredDecoder.ToString();
	}

	void AudioCodecSettings::setPreferredDecoderString(const QString &value)
	{
		if (value.Equals("FFAudioSource"))
			preferredDecoder = FFAudioSource;
		else if (value.Equals("DirectShow"))
			preferredDecoder = DirectShow;
		else if (value.Equals("BassAudio"))
			preferredDecoder = BassAudio;
	}

	const ChannelMode &AudioCodecSettings::getDownmixMode() const
	{
		return downmixMode;
	}

	void AudioCodecSettings::setDownmixMode(const ChannelMode &value)
	{
		downmixMode = value;
	}

	const BitrateManagementMode &AudioCodecSettings::getBitrateMode() const
	{
		return bitrateMode;
	}

	void AudioCodecSettings::setBitrateMode(const BitrateManagementMode &value)
	{
		bitrateMode = value;
	}

	const int &AudioCodecSettings::getBitrate() const
	{
		return NormalizeVar(bitrate, supportedBitrates);
	}

	void AudioCodecSettings::setBitrate(const int &value)
	{
		bitrate = value;
	}

	const bool &AudioCodecSettings::getAutoGain() const
	{
		return autoGain;
	}

	void AudioCodecSettings::setAutoGain(const bool &value)
	{
		autoGain = value;
	}

	const int &AudioCodecSettings::getSampleRateType() const
	{
		return sampleRateType;
	}

	void AudioCodecSettings::setSampleRateType(const int &value)
	{
		sampleRateType = value;
	}

	const bool &AudioCodecSettings::getApplyDRC() const
	{
		return applyDRC;
	}

	void AudioCodecSettings::setApplyDRC(const bool &value)
	{
		applyDRC = value;
	}

	const int &AudioCodecSettings::getNormalize() const
	{
		return normalize;
	}

	void AudioCodecSettings::setNormalize(const int &value)
	{
		normalize = value;
	}

	object *AudioCodecSettings::ICloneable_Clone()
	{
		return Clone();
	}

	MeXgui::core::plugins::interfaces::GenericSettings *AudioCodecSettings::GenericSettings_Clone()
	{
		return Clone();
	}

	AudioCodecSettings *AudioCodecSettings::Clone()
	{
		// This method is sutable for all known descendants!
		return dynamic_cast<AudioCodecSettings*>(this->MemberwiseClone());
	}

	bool AudioCodecSettings::Equals(object *obj)
	{
		return Equals(dynamic_cast<GenericSettings*>(obj));
	}

	bool AudioCodecSettings::Equals(GenericSettings *other)
	{
		// This works for all known descendants
		return other == 0 ? false : PropertyEqualityTester::AreEqual(this, other);
	}

	int AudioCodecSettings::NormalizeVar(int bitrate, int supportedBitrates[])
	{
		if (supportedBitrates == 0)
			return bitrate;

		int closest = bitrate;
		int d = int::MaxValue;

		for (int::const_iterator i = supportedBitrates->begin(); i != supportedBitrates->end(); ++i)
		{
			int d1 = abs(*i - bitrate);
			if (d1 <= d)
			{
				closest = *i;
				d = d1;
			}
		}
		return closest;
	}

	int AudioCodecSettings::GetHashCode()
	{
		// DO NOT CALL base.GetHashCode();
		return 0;
	}

	const QString &AudioCodecSettings::getRequiredFiles() const
	{
		return new QString[0];
	}

	const QString &AudioCodecSettings::getRequiredProfiles() const
	{
		return new QString[0];
	}
}
