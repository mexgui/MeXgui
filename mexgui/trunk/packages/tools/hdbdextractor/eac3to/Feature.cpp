#include "Feature.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::packages::tools::hdbdextractor;

namespace eac3to
{

	const int &Feature::getNumber() const
	{
		return privateNumber;
	}

	void Feature::setNumber(const int &value)
	{
		privateNumber = value;
	}

	const std::string &Feature::getName() const
	{
		return privateName;
	}

	void Feature::setName(const std::string &value)
	{
		privateName = value;
	}

	const std::string &Feature::getDescription() const
	{
		return privateDescription;
	}

	void Feature::setDescription(const std::string &value)
	{
		privateDescription = value;
	}

	const TimeSpan &Feature::getDuration() const
	{
		return privateDuration;
	}

	void Feature::setDuration(const TimeSpan &value)
	{
		privateDuration = value;
	}

	const std::vector<File*> &Feature::getFiles() const
	{
		return privateFiles;
	}

	void Feature::setFiles(const std::vector<File*> &value)
	{
		privateFiles = value;
	}

	const std::vector<Stream*> &Feature::getStreams() const
	{
		return privateStreams;
	}

	void Feature::setStreams(const std::vector<Stream*> &value)
	{
		privateStreams = value;
	}

	Feature::Feature()
	{
		setNumber(0);
		setName("");
		setDescription("");
		setDuration(new TimeSpan(0, 0, 0));
		setFiles(std::vector<File*>());
		setStreams(std::vector<Stream*>());
	}

	Feature *Feature::Parse(const std::string &s)
	{
		/*
		// Blu-Ray
		1) 00001.mpls, 00011.m2ts, 1:53:06
		   - h264/AVC, 1080p24 /1.001 (16:9)
		   - TrueHD, English, multi-channel, 48khz
		   - TrueHD, French, multi-channel, 48khz
		   - AC3, Spanish, multi-channel, 48khz
		   - AC3, Thai, multi-channel, 48khz
		   - AC3, Portuguese, multi-channel, 48khz
		   - AC3, English, stereo, 48khz
	
		2) 00216.mpls, 0:50:19
		   [99+100+101+102+103+104+105+106+114].m2ts
		   - h264/AVC, 1080i60 /1.001 (16:9)
		   - AC3, English, stereo, 48khz
		// HD-DVD
		1) Alternate_feature_01.EVO+Alternate_feature_02.EVO, 1:43:48
		   "director"
		   - VC-1, 1080p (16:9)
		   - TrueHD, English, 5.1, 48khz
	
		2) Theatrical_feature_01.EVO+Theatrical_feature_02.EVO, 1:40:26
		   "feature"
		   - VC-1, 1080p (16:9)
		   - TrueHD, English, 5.1, 48khz
		   - E-AC3, French, 5.1, 48khz
		   - E-AC3, Spanish, 5.1, 48khz
	
		3) default.EVO, 0:00:12
		   "pickFeature"
		   - VC-1, 1080p (16:9)             
	
		*/

		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		Feature *feature = new Feature();

		feature->setNumber(int::Parse(s.substr(0, s.find(")"))));
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		feature->setName(s.substr(s.find(")") + 1, s.find(",") - s.find(")") - 1)->Trim());
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		feature->setDescription(s.substr(s.find(")") + 1)->Trim());
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		feature->setDuration(TimeSpan::Parse(s.substr(s.rfind(',') + 1)->Trim()));

		if (s.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Contains(".M2TS,")) // Blu-ray
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			for (unknown::const_iterator file = s.substr(s.find(",") + 1, s.rfind(',') - s.find(",") - 1)->Split((std::string("+"))->ToCharArray()).begin(); file != s.substr(s.find(",") + 1, s.rfind(',') - s.find(",") - 1)->Split((std::string("+"))->ToCharArray()).end(); ++file)
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				feature->getFiles().push_back(new File((*file).Trim(), feature->getFiles().size() + 1));
		else if (s.ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Contains(".EVO,")) // HD-DVD
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			for (unknown::const_iterator file = s.substr(s.find(")") + 1, s.find(',') - s.find(")") - 1)->Split((std::string("+"))->ToCharArray()).begin(); file != s.substr(s.find(")") + 1, s.find(',') - s.find(")") - 1)->Split((std::string("+"))->ToCharArray()).end(); ++file)
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				feature->getFiles().push_back(new File((*file).Trim(), feature->getFiles().size() + 1));

		return feature;
	}

	std::string Feature::ToString()
	{
		StringBuilder *sb = new StringBuilder();

		sb->AppendFormat("Number:\t{0}{3}Name:\t{1}{3}Duration:\t{2}{3}File(s):{3}", getNumber(), getName(), getDuration(), "\r\n");

		for (std::vector<File*>::const_iterator file = getFiles().begin(); file != getFiles().end(); ++file)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			sb->AppendFormat("\t{0}{1}", (*file)->ToString(), "\r\n");

		sb->AppendFormat("Stream(s): {0}", "\r\n");

		if (getStreams().empty())
			sb->Append("\tRetrieve streams to view their details.");
		else
			for (std::vector<Stream*>::const_iterator stream = getStreams().begin(); stream != getStreams().end(); ++stream)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				sb->AppendFormat("\t{0}{1}", (*stream)->ToString(), "\r\n");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}
}
