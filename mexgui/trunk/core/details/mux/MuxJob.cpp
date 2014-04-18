#include "MuxJob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;

namespace MeGUI
{

	const MeGUI::ContainerType &MuxJob::getContainerType() const
	{
		return containerType;
	}

	void MuxJob::setContainerType(const MeGUI::ContainerType &value)
	{
		containerType = value;
	}

	const std::string &MuxJob::getContainerTypeString() const
	{
		return getContainerType()->getID();
	}

	void MuxJob::setContainerTypeString(const std::string &value)
	{
		for (std::vector<MeGUI::ContainerType*>::const_iterator t = MainForm::Instance->getMuxProvider()->GetSupportedContainers().begin(); t != MainForm::Instance->getMuxProvider()->GetSupportedContainers().end(); ++t)
		{
			if ((*t)->getID() == value)
			{
				setContainerType(*t);
				return;
			}
		}
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete getContainerType();
	}

	const std::string &MuxJob::getCodecString() const
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return type.ToString()->ToLower(System::Globalization::CultureInfo::InvariantCulture);
	}

	const std::string &MuxJob::getEncodingMode() const
	{
		return "mux";
	}

	MuxJob::MuxJob() : Job()
	{
		codec = "";
		nbOfBframes = 0;
		bitrate = 0;
		overhead = 4.3;
		type = MP4BOX;
		containerType = getContainerType()->MP4;
		settings = new MuxSettings();
	}

	const std::string &MuxJob::getCodec() const
	{
		return codec;
	}

	void MuxJob::setCodec(const std::string &value)
	{
		codec = value;
	}

	const int &MuxJob::getNbOfBFrames() const
	{
		return nbOfBframes;
	}

	void MuxJob::setNbOfBFrames(const int &value)
	{
		nbOfBframes = value;
	}

	const unsigned long long &MuxJob::getNbOfFrames() const
	{
		return nbOfFrames;
	}

	void MuxJob::setNbOfFrames(const unsigned long long &value)
	{
		nbOfFrames = value;
	}

	const int &MuxJob::getBitrate() const
	{
		return bitrate;
	}

	void MuxJob::setBitrate(const int &value)
	{
		bitrate = value;
	}

	const double &MuxJob::getOverhead() const
	{
		return overhead;
	}

	void MuxJob::setOverhead(const double &value)
	{
		overhead = value;
	}

	const MuxSettings &MuxJob::getSettings() const
	{
		return settings;
	}

	void MuxJob::setSettings(const MuxSettings &value)
	{
		settings = value;
	}

	const MuxerType &MuxJob::getMuxType() const
	{
		return type;
	}

	void MuxJob::setMuxType(const MuxerType &value)
	{
		type = value;
	}
}
