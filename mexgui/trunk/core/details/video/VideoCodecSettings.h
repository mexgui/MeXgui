#pragma once

#include "core/gui/Profiles.h"
#include "core/details/CodecManager.h"
#include <string>
#include <map>

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
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{
	/// <summary>
	/// Contains basic codec settings, basically all the settings that are often used by codecs like bitrate, encoding mode, etc.
	/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlInclude(x264Settings::typeid), XmlInclude(xvidSettings::typeid), XmlInclude(hfyuSettings::typeid)]
	class VideoCodecSettings : public MeGUI::core::plugins::interfaces::GenericSettings
	{
	public:
		enum Mode
		{
			CBR = 0,
			CQ,
			twopass1,
			twopass2,
			twopassAutomated,
			threepass1,
			threepass2,
			threepass3,
			threepassAutomated,
			quality
		};
	private:
		std::string id;
	public:
		const std::string &getSettingsID() const;

		virtual void setAdjustedNbThreads(int nbThreads);

		virtual bool Equals(object *obj);

		virtual bool Equals(GenericSettings *other);

		virtual int GetHashCode();

	private:
		int encodingMode, bitrateQuantizer, keyframeInterval, nbBframes, minQuantizer, maxQuantizer, fourCC, maxNumberOfPasses, nbThreads;
		bool v4mv, qpel, trellis;
		decimal creditsQuantizer;
		std::string logfile, customEncoderOptions, videoName;
//ORIGINAL LINE: private string[] fourCCs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		std::string *fourCCs;
		VideoEncoderType *vet;

	public:
		virtual const bool &getUsesSAR() const = 0;

		VideoCodecSettings(const std::string &id, VideoEncoderType *vet);
		const VideoCodec &getCodec() const;
		const VideoEncoderType &getEncoderType() const;
		const int &getEncodingMode() const;
		void setEncodingMode(const int &value);
		const int &getBitrateQuantizer() const;
		void setBitrateQuantizer(const int &value);
		const int &getKeyframeInterval() const;
		void setKeyframeInterval(const int &value);
		const int &getNbBframes() const;
		void setNbBframes(const int &value);
		const int &getMinQuantizer() const;
		void setMinQuantizer(const int &value);
		const int &getMaxQuantizer() const;
		void setMaxQuantizer(const int &value);
		const bool &getV4MV() const;
		void setV4MV(const bool &value);
		const bool &getQPel() const;
		void setQPel(const bool &value);
		const bool &getTrellis() const;
		void setTrellis(const bool &value);
		const decimal &getCreditsQuantizer() const;
		void setCreditsQuantizer(const decimal &value);
		/// <summary>
		/// returns the available FourCCs for the codec
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PropertyEqualityIgnore]
		const std::string *getFourCCs() const;
		void setFourCCs(std::string value[]);
		/// <summary>
		/// gets / sets the logfile
		/// </summary>
		const std::string &getLogfile() const;
		void setLogfile(const std::string &value);
		/// <summary>
		/// gets / sets Video Tracks Name (used with the muxers)
		/// </summary>
		const std::string &getVideoName() const;
		void setVideoName(const std::string &value);
		/// <summary>
		/// gets / set custom commandline options for the encoder
		/// </summary>
		const std::string &getCustomEncoderOptions() const;
		void setCustomEncoderOptions(const std::string &value);
		/// <summary>
		/// gets / sets which fourcc from the FourCCs array is to be used
		/// </summary>
		const int &getFourCC() const;
		void setFourCC(const int &value);
		/// <summary>
		///  gets / sets the maximum number of passes that can be performed with the current codec
		/// </summary>
		const int &getMaxNumberOfPasses() const;
		void setMaxNumberOfPasses(const int &value);
		/// <summary>
		/// gets / sets the number of encoder threads to be used
		/// </summary>
		const int &getNbThreads() const;
		void setNbThreads(const int &value);
		/// <summary>
		/// generates a copy of this object
		/// </summary>
		/// <returns>the codec specific settings of this object</returns>
	private:
		object *ICloneable_Clone();

		GenericSettings *GenericSettings_Clone();

	public:
		VideoCodecSettings *Clone();

		virtual void FixFileNames(std::map<std::string, std::string> &_);

		const virtual std::string *getRequiredFiles() const;

		const virtual std::string *getRequiredProfiles() const;

	};
	enum ZONEMODE
	{
		Quantizer = 0,
		Weight
	};
	class Zone
	{
	public:
		int startFrame;
		int endFrame;
		ZONEMODE mode;
		decimal modifier;
	};
}
