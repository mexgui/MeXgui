#include "VideoCodecSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{

	const std::string &VideoCodecSettings::getSettingsID() const
	{
		return id;
	}

	void VideoCodecSettings::setAdjustedNbThreads(int nbThreads)
	{
		setNbThreads(nbThreads);
	}

	bool VideoCodecSettings::Equals(object *obj)
	{
		return Equals(dynamic_cast<GenericSettings*>(obj));
	}

	bool VideoCodecSettings::Equals(GenericSettings *other)
	{
		return PropertyEqualityTester::AreEqual(this, other);
	}

	int VideoCodecSettings::GetHashCode()
	{
		// DO NOT CALL BASE.GETHASHCODE!
		return 0;
	}

	VideoCodecSettings::VideoCodecSettings(const std::string &id, VideoEncoderType *vet)
	{
		this->id = id;
		this->vet = vet;
		logfile = ".stats";
		customEncoderOptions = "";
		videoName = "";
		fourCC = 0;
		nbThreads = 1;
	}

	const VideoCodec &VideoCodecSettings::getCodec() const
	{
		return getEncoderType()->getVCodec();
	}

	const VideoEncoderType &VideoCodecSettings::getEncoderType() const
	{
		return vet;
	}

	const int &VideoCodecSettings::getEncodingMode() const
	{
		return encodingMode;
	}

	void VideoCodecSettings::setEncodingMode(const int &value)
	{
		encodingMode = value;
	}

	const int &VideoCodecSettings::getBitrateQuantizer() const
	{
		return bitrateQuantizer;
	}

	void VideoCodecSettings::setBitrateQuantizer(const int &value)
	{
		bitrateQuantizer = value;
	}

	const int &VideoCodecSettings::getKeyframeInterval() const
	{
		return keyframeInterval;
	}

	void VideoCodecSettings::setKeyframeInterval(const int &value)
	{
		keyframeInterval = value;
	}

	const int &VideoCodecSettings::getNbBframes() const
	{
		return nbBframes;
	}

	void VideoCodecSettings::setNbBframes(const int &value)
	{
		nbBframes = value;
	}

	const int &VideoCodecSettings::getMinQuantizer() const
	{
		return minQuantizer;
	}

	void VideoCodecSettings::setMinQuantizer(const int &value)
	{
		minQuantizer = value;
	}

	const int &VideoCodecSettings::getMaxQuantizer() const
	{
		return maxQuantizer;
	}

	void VideoCodecSettings::setMaxQuantizer(const int &value)
	{
		maxQuantizer = value;
	}

	const bool &VideoCodecSettings::getV4MV() const
	{
		return v4mv;
	}

	void VideoCodecSettings::setV4MV(const bool &value)
	{
		v4mv = value;
	}

	const bool &VideoCodecSettings::getQPel() const
	{
		return qpel;
	}

	void VideoCodecSettings::setQPel(const bool &value)
	{
		qpel = value;
	}

	const bool &VideoCodecSettings::getTrellis() const
	{
		return trellis;
	}

	void VideoCodecSettings::setTrellis(const bool &value)
	{
		trellis = value;
	}

	const decimal &VideoCodecSettings::getCreditsQuantizer() const
	{
		return creditsQuantizer;
	}

	void VideoCodecSettings::setCreditsQuantizer(const decimal &value)
	{
		creditsQuantizer = value;
	}

	const std::string &VideoCodecSettings::getFourCCs() const
	{
		return fourCCs;
	}

	void VideoCodecSettings::setFourCCs(const std::string &value[])
	{
		fourCCs = value;
	}

	const std::string &VideoCodecSettings::getLogfile() const
	{
		return logfile;
	}

	void VideoCodecSettings::setLogfile(const std::string &value)
	{
		logfile = value;
	}

	const std::string &VideoCodecSettings::getVideoName() const
	{
		return videoName;
	}

	void VideoCodecSettings::setVideoName(const std::string &value)
	{
		videoName = value;
	}

	const std::string &VideoCodecSettings::getCustomEncoderOptions() const
	{
		if (getEncoderType()->getID().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("x264"))
		{
			// update custom command line if necessary
			std::string strNewCommandLine = "", strNewCommand = "";
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			for (unknown::const_iterator strCommand = System::Text::RegularExpressions::Regex->Split(customEncoderOptions, "--").begin(); strCommand != System::Text::RegularExpressions::Regex->Split(customEncoderOptions, "--").end(); ++strCommand)
			{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				if ((*strCommand).Trim()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("nal-hrd"))
					strNewCommand = "nal-hrd vbr";
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				else if ((*strCommand).Trim()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("open-gop none"))
					strNewCommand = "";
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				else if ((*strCommand).Trim()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("open-gop normal"))
					strNewCommand = "open-gop";
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				else if ((*strCommand).Trim()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("open-gop bluray"))
					strNewCommand = "open-gop --bluray-compat";
				else
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
					strNewCommand = (*strCommand).Trim();
				if (!strNewCommand.empty())
					strNewCommandLine += " --" + strNewCommand;
			}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			return strNewCommandLine.Trim();
		}
		else
			return customEncoderOptions;
	}

	void VideoCodecSettings::setCustomEncoderOptions(const std::string &value)
	{
		customEncoderOptions = value;
	}

	const int &VideoCodecSettings::getFourCC() const
	{
		return fourCC;
	}

	void VideoCodecSettings::setFourCC(const int &value)
	{
		fourCC = value;
	}

	const int &VideoCodecSettings::getMaxNumberOfPasses() const
	{
		return maxNumberOfPasses;
	}

	void VideoCodecSettings::setMaxNumberOfPasses(const int &value)
	{
		maxNumberOfPasses = value;
	}

	const int &VideoCodecSettings::getNbThreads() const
	{
		return nbThreads;
	}

	void VideoCodecSettings::setNbThreads(const int &value)
	{
		nbThreads = value;
	}

	object *VideoCodecSettings::ICloneable_Clone()
	{
		return Clone();
	}

	MeGUI::core::plugins::interfaces::GenericSettings *VideoCodecSettings::GenericSettings_Clone()
	{
		return Clone();
	}

	VideoCodecSettings *VideoCodecSettings::Clone()
	{
		// This method is sutable for all known descendants!
		return dynamic_cast<VideoCodecSettings*>(this->MemberwiseClone());
	}

	void VideoCodecSettings::FixFileNames(std::map<std::string, std::string> &_)
	{
	}

	const std::string &VideoCodecSettings::getRequiredFiles() const
	{
		return new std::string[0];
	}

	const std::string &VideoCodecSettings::getRequiredProfiles() const
	{
		return new std::string[0];
	}
}
