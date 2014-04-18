#pragma once

#include "core/gui/Profiles.h"
#include "core/details/CodecManager.h"
#include <string>
#include <map>
#include <cmath>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{
	/// <summary>
	/// Summary description for AudioCodecSettings.
	/// </summary>
	/// 
	enum BitrateManagementMode
	{
		CBR,
		VBR,
		ABR
	};
	enum ChannelMode
	{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Keep Original Channels")]
		KeepOriginal,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Convert to Mono")]
		ConvertToMono,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Downmix multichannel to Stereo")]
		StereoDownmix,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Downmix multichannel to Dolby Pro Logic")]
		DPLDownmix,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Downmix multichannel to Dolby Pro Logic II")]
		DPLIIDownmix,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Upmix 2 to 5.1 via SuperEQ (slow)")]
		Upmix,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Upmix 2 to 5.1 via Sox equalizer adjustments")]
		UpmixUsingSoxEq,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Upmix 2 to 5.1 with center channel dialog")]
		UpmixWithCenterChannelDialog
	};
	enum AudioDecodingEngine
	{
		NicAudio,
		FFAudioSource,
		DirectShow,
		BassAudio
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlInclude(MP2Settings::typeid), XmlInclude(AC3Settings::typeid), XmlInclude(NeroAACSettings::typeid), XmlInclude(MP3Settings::typeid), XmlInclude(OggVorbisSettings::typeid), XmlInclude(AftenSettings::typeid), XmlInclude(FlacSettings::typeid), XmlInclude(QaacSettings::typeid), XmlInclude(OpusSettings::typeid)]
	class AudioCodecSettings : public MeGUI::core::plugins::interfaces::GenericSettings
	{
	protected:
//ORIGINAL LINE: protected int[] supportedBitrates;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		int *supportedBitrates;
	private:
		const std::string id;
	public:
		const std::string &getSettingsID() const;

		virtual void FixFileNames(std::map<std::string, std::string> &_);
	private:
		ChannelMode downmixMode;
		BitrateManagementMode bitrateMode;
		int sampleRateType;
		int bitrate;
		int normalize;
	public:
		int delay;
		bool delayEnabled;
	private:
		bool autoGain;
		bool applyDRC;
		AudioCodec *audioCodec;
		AudioEncoderType *audioEncoderType;
		AudioDecodingEngine preferredDecoder;

	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const AudioCodec &getCodec() const;
		void setCodec(const AudioCodec &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore]
		const AudioEncoderType &getEncoderType() const;
		void setEncoderType(const AudioEncoderType &value);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AudioCodecSettings(string id, AudioCodec codec, AudioEncoderType encoder, int bitrate) : this(id, codec, encoder, bitrate, BitrateManagementMode.CBR)
		AudioCodecSettings(const std::string &id, AudioCodec *codec, AudioEncoderType *encoder, int bitrate);

		AudioCodecSettings(const std::string &id, AudioCodec *codec, AudioEncoderType *encoder, int bitrate, BitrateManagementMode mode);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const AudioDecodingEngine &getPreferredDecoder() const;
		void setPreferredDecoder(const AudioDecodingEngine &value);

		// for profile import/export in case the enum changes
		const std::string &getPreferredDecoderString() const;
		void setPreferredDecoderString(const std::string &value);

		const ChannelMode &getDownmixMode() const;
		void setDownmixMode(const ChannelMode &value);

		const virtual BitrateManagementMode &getBitrateMode() const;
		virtual void setBitrateMode(const BitrateManagementMode &value);

		const virtual int &getBitrate() const;
		virtual void setBitrate(const int &value);

		const bool &getAutoGain() const;
		void setAutoGain(const bool &value);

		const int &getSampleRateType() const;
		void setSampleRateType(const int &value);

		const bool &getApplyDRC() const;
		void setApplyDRC(const bool &value);

		const int &getNormalize() const;
		void setNormalize(const int &value);

	private:
		object *ICloneable_Clone();

		GenericSettings *GenericSettings_Clone();

	public:
		AudioCodecSettings *Clone();

		virtual bool Equals(object *obj);

		bool Equals(GenericSettings *other);

		virtual int NormalizeVar(int bitrate, int supportedBitrates[]);

		virtual int GetHashCode();

		const std::string *getRequiredFiles() const;

		const std::string *getRequiredProfiles() const;
	};
}
