#include "AutoEncodeDefaultsSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::gui;
using namespace MeGUI::core::util;

namespace MeGUI
{

	AutoEncodeDefaultsSettings::AutoEncodeDefaultsSettings()
	{
		InitializeInstanceFields();
		fileSizeMode = true;
		bitrateMode = false;
		noTargetSizeMode = false;
		addAdditionalContent = false;
		container = "MP4";
		deviceType = "Standard";
		bitrate = 700;
	}

	const bool &AutoEncodeDefaultsSettings::getAddAdditionalContent() const
	{
		return addAdditionalContent;
	}

	void AutoEncodeDefaultsSettings::setAddAdditionalContent(const bool &value)
	{
		addAdditionalContent = value;
	}

	const bool &AutoEncodeDefaultsSettings::getNoTargetSizeMode() const
	{
		return noTargetSizeMode;
	}

	void AutoEncodeDefaultsSettings::setNoTargetSizeMode(const bool &value)
	{
		noTargetSizeMode = value;
	}

	const bool &AutoEncodeDefaultsSettings::getBitrateMode() const
	{
		return bitrateMode;
	}

	void AutoEncodeDefaultsSettings::setBitrateMode(const bool &value)
	{
		bitrateMode = value;
	}

	const bool &AutoEncodeDefaultsSettings::getFileSizeMode() const
	{
		return fileSizeMode;
	}

	void AutoEncodeDefaultsSettings::setFileSizeMode(const bool &value)
	{
		fileSizeMode = value;
	}

	const std::string &AutoEncodeDefaultsSettings::getContainer() const
	{
		return container;
	}

	void AutoEncodeDefaultsSettings::setContainer(const std::string &value)
	{
		container = value;
	}

	const std::string &AutoEncodeDefaultsSettings::getDeviceOutputType() const
	{
		return deviceType;
	}

	void AutoEncodeDefaultsSettings::setDeviceOutputType(const std::string &value)
	{
		deviceType = value;
	}

	const int &AutoEncodeDefaultsSettings::getBitrate() const
	{
		return bitrate;
	}

	void AutoEncodeDefaultsSettings::setBitrate(const int &value)
	{
		bitrate = value;
	}

	const Nullable<MeGUI::core::util::FileSize> &AutoEncodeDefaultsSettings::getFileSize() const
	{
		return fileSize;
	}

	void AutoEncodeDefaultsSettings::setFileSize(const Nullable<MeGUI::core::util::FileSize> &value)
	{
		fileSize = value;
	}

	const Nullable<MeGUI::core::util::FileSize> &AutoEncodeDefaultsSettings::getSplitSize() const
	{
		return splitSize;
	}

	void AutoEncodeDefaultsSettings::setSplitSize(const Nullable<MeGUI::core::util::FileSize> &value)
	{
		splitSize = value;
	}

	void AutoEncodeDefaultsSettings::InitializeInstanceFields()
	{
		splitSize = Nullable<FileSize>()
		fileSize = TargetSizeSCBox::PredefinedFilesizes[2]->Data;
	}
}
