#include "OneClickSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;

namespace MeGUI
{

const AudioEncodingMode OneClickSettings::SupportedModes[4] = {Always, IfCodecDoesNotMatch, NeverOnlyCore, Never};

	const std::string &OneClickSettings::getVideoProfileName() const
	{
		return videoProfileName;
	}

	void OneClickSettings::setVideoProfileName(const std::string &value)
	{
		videoProfileName = value;
	}

	const std::string &OneClickSettings::getAvsProfileName() const
	{
		return avsProfileName;
	}

	void OneClickSettings::setAvsProfileName(const std::string &value)
	{
		avsProfileName = value;
	}

	const bool &OneClickSettings::getPrerenderVideo() const
	{
		return prerenderVideo;
	}

	void OneClickSettings::setPrerenderVideo(const bool &value)
	{
		prerenderVideo = value;
	}

	const std::string &OneClickSettings::getAudioProfileName() const
	{
		return "migrated";
	}

	void OneClickSettings::setAudioProfileName(const std::string &value)
	{
		audioProfileName = value;
	}

	const std::string &OneClickSettings::getAudioEncodingModeString() const
	{
		return "migrated";
	}

	void OneClickSettings::setAudioEncodingModeString(const std::string &value)
	{
		if (value.Equals("migrated"))
			return;

		AudioEncodingMode audioEncodingMode = Always;
		if (value.Equals("Never"))
			audioEncodingMode = Never;
		else if (value.Equals("IfCodecDoesNotMatch"))
			audioEncodingMode = IfCodecDoesNotMatch;
		else if (value.Equals("NeverOnlyCore"))
			audioEncodingMode = NeverOnlyCore;

		audioSettings = std::vector<OneClickAudioSettings*>();
		audioSettings.push_back(new OneClickAudioSettings("[default]", audioProfileName, audioEncodingMode, false));
	}

	const std::vector<OneClickAudioSettings*> &OneClickSettings::getAudioSettings() const
	{
		return audioSettings;
	}

	void OneClickSettings::setAudioSettings(const std::vector<OneClickAudioSettings*> &value)
	{
		audioSettings = value;
	}

	const OneClickAudioSettings &OneClickSettings::getAudioSettingsString() const
	{
		return audioSettings.ToArray();
	}

	void OneClickSettings::setAudioSettingsString(const OneClickAudioSettings &value[])
	{
		audioSettings = std::vector<OneClickAudioSettings*>(value);
	}

	const bool &OneClickSettings::getDontEncodeVideo() const
	{
		return dontEncodeVideo;
	}

	void OneClickSettings::setDontEncodeVideo(const bool &value)
	{
		dontEncodeVideo = value;
	}

	const bool &OneClickSettings::getSignalAR() const
	{
		return signalAR;
	}

	void OneClickSettings::setSignalAR(const bool &value)
	{
		signalAR = value;
	}

	const bool &OneClickSettings::getAutomaticDeinterlacing() const
	{
		return automaticDeinterlacing;
	}

	void OneClickSettings::setAutomaticDeinterlacing(const bool &value)
	{
		automaticDeinterlacing = value;
	}

	const bool &OneClickSettings::getAutoCrop() const
	{
		return autoCrop;
	}

	void OneClickSettings::setAutoCrop(const bool &value)
	{
		autoCrop = value;
	}

	const bool &OneClickSettings::getKeepInputResolution() const
	{
		return keepInputResolution;
	}

	void OneClickSettings::setKeepInputResolution(const bool &value)
	{
		keepInputResolution = value;
	}

	const long long &OneClickSettings::getOutputResolution() const
	{
		return outputResolution;
	}

	void OneClickSettings::setOutputResolution(const long long &value)
	{
		outputResolution = value;
	}

	const Nullable<FileSize> &OneClickSettings::getFilesize() const
	{
		return filesize;
	}

	void OneClickSettings::setFilesize(const Nullable<FileSize> &value)
	{
		filesize = value;
	}

	const Nullable<FileSize> &OneClickSettings::getSplitSize() const
	{
		return splitSize;
	}

	void OneClickSettings::setSplitSize(const Nullable<FileSize> &value)
	{
		splitSize = value;
	}

	const std::string &OneClickSettings::getContainerCandidates() const
	{
		return containerCandidates;
	}

	void OneClickSettings::setContainerCandidates(const std::string &value[])
	{
		containerCandidates = value;
	}

	const std::string &OneClickSettings::getDeviceOutputType() const
	{
		return deviceType;
	}

	void OneClickSettings::setDeviceOutputType(const std::string &value)
	{
		deviceType = value;
	}

	const std::string &OneClickSettings::getLeadingName() const
	{
		return leadingName;
	}

	void OneClickSettings::setLeadingName(const std::string &value)
	{
		leadingName = value;
	}

	const std::string &OneClickSettings::getWorkingNameReplace() const
	{
		return workingNameReplace;
	}

	void OneClickSettings::setWorkingNameReplace(const std::string &value)
	{
		workingNameReplace = value;
	}

	const std::string &OneClickSettings::getWorkingNameReplaceWith() const
	{
		return workingNameReplaceWith;
	}

	void OneClickSettings::setWorkingNameReplaceWith(const std::string &value)
	{
		workingNameReplaceWith = value;
	}

	const bool &OneClickSettings::getUseChaptersMarks() const
	{
		return useChaptersMarks;
	}

	void OneClickSettings::setUseChaptersMarks(const bool &value)
	{
		useChaptersMarks = value;
	}

	const bool &OneClickSettings::getUseNoLanguagesAsFallback() const
	{
		return useNoLanguagesAsFallback;
	}

	void OneClickSettings::setUseNoLanguagesAsFallback(const bool &value)
	{
		useNoLanguagesAsFallback = value;
	}

	const bool &OneClickSettings::getDisableIntermediateMKV() const
	{
		return disableIntermediateMKV;
	}

	void OneClickSettings::setDisableIntermediateMKV(const bool &value)
	{
		disableIntermediateMKV = value;
	}

	const std::string &OneClickSettings::getDefaultWorkingDirectory() const
	{
		return defaultWorkingDirectory;
	}

	void OneClickSettings::setDefaultWorkingDirectory(const std::string &value)
	{
		defaultWorkingDirectory = value;
	}

	const std::string &OneClickSettings::getDefaultOutputDirectory() const
	{
		return defaultOutputDirectory;
	}

	void OneClickSettings::setDefaultOutputDirectory(const std::string &value)
	{
		defaultOutputDirectory = value;
	}

	const std::string &OneClickSettings::getDefaultLanguage() const
	{
		if (defaultLanguage.empty())
		{
			if (MainForm::Instance != 0 && !MainForm::Instance->getSettings()->getDefaultLanguage1().empty())
				defaultLanguage = MainForm::Instance->getSettings()->getDefaultLanguage1();
			else
				defaultLanguage = "English";
		}
		return defaultLanguage;
	}

	void OneClickSettings::setDefaultLanguage(const std::string &value)
	{
		defaultLanguage = value;
	}

	const std::vector<std::string> &OneClickSettings::getDefaultAudioLanguage() const
	{
		return defaultAudioLanguage;
	}

	void OneClickSettings::setDefaultAudioLanguage(const std::vector<std::string> &value)
	{
		defaultAudioLanguage = value;
	}

	const std::string &OneClickSettings::getDefaultAudioLanguageString() const
	{
		return defaultAudioLanguage.ToArray();
	}

	void OneClickSettings::setDefaultAudioLanguageString(const std::string &value[])
	{
		defaultAudioLanguage = std::vector<std::string>(value);
	}

	const std::vector<std::string> &OneClickSettings::getDefaultSubtitleLanguage() const
	{
		return defaultSubtitleLanguage;
	}

	void OneClickSettings::setDefaultSubtitleLanguage(const std::vector<std::string> &value)
	{
		defaultSubtitleLanguage = value;
	}

	const std::string &OneClickSettings::getDefaultSubtitleLanguageString() const
	{
		return defaultSubtitleLanguage.ToArray();
	}

	void OneClickSettings::setDefaultSubtitleLanguageString(const std::string &value[])
	{
		defaultSubtitleLanguage = std::vector<std::string>(value);
	}

	const std::vector<std::string> &OneClickSettings::getIndexerPriority() const
	{
		return indexerPriority;
	}

	void OneClickSettings::setIndexerPriority(const std::vector<std::string> &value)
	{
		indexerPriority = value;
	}

	const std::string &OneClickSettings::getIndexerPriorityString() const
	{
		return indexerPriority.ToArray();
	}

	void OneClickSettings::setIndexerPriorityString(const std::string &value[])
	{
		if (value->Length == 4)
		{
			Array::Resize<std::string>(value, 5);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			value[4] = FileIndexerWindow::AVISOURCE->ToString();
		}
		indexerPriority = std::vector<std::string>(value);
	}

	OneClickSettings::OneClickSettings()
	{
		videoProfileName = "";
		avsProfileName = "";
		automaticDeinterlacing = true;
		prerenderVideo = false;
		dontEncodeVideo = false;
		disableIntermediateMKV = false;
		useChaptersMarks = true;
		signalAR = false;
		autoCrop = true;
		keepInputResolution = false;
		outputResolution = 720;
		splitSize = Nullable<FileSize>();
		containerCandidates = new std::string[] {"MKV"};
		defaultAudioLanguage = std::vector<std::string>();
		defaultSubtitleLanguage = std::vector<std::string>();
		indexerPriority = std::vector<std::string>();
		defaultWorkingDirectory = "";
		workingNameReplace = "";
		workingNameReplaceWith = "";
		leadingName = "";
		audioSettings = std::vector<OneClickAudioSettings*>();
		audioSettings.push_back(new OneClickAudioSettings("[default]", "FFmpeg AC-3: *scratchpad*", IfCodecDoesNotMatch, true));

		if (MainForm::Instance != 0)
		{
			if (!MainForm::Instance->getSettings()->getDefaultLanguage1().empty())
			{
				getDefaultAudioLanguage().push_back(MainForm::Instance->getSettings()->getDefaultLanguage1());
				getDefaultSubtitleLanguage().push_back(MainForm::Instance->getSettings()->getDefaultLanguage1());
				setDefaultLanguage(MainForm::Instance->getSettings()->getDefaultLanguage1());
			}
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
			if (!String.IsNullOrEmpty(MainForm.Instance.Settings.DefaultLanguage2) && !DefaultAudioLanguage.Contains(MainForm.Instance.Settings.DefaultLanguage2))
				getDefaultAudioLanguage().push_back(MainForm::Instance->getSettings()->getDefaultLanguage2());
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
			if (!String.IsNullOrEmpty(MainForm.Instance.Settings.DefaultLanguage2) && !DefaultSubtitleLanguage.Contains(MainForm.Instance.Settings.DefaultLanguage2))
				getDefaultSubtitleLanguage().push_back(MainForm::Instance->getSettings()->getDefaultLanguage2());
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		getIndexerPriority().push_back(FileIndexerWindow::DGI->ToString());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		getIndexerPriority().push_back(FileIndexerWindow::D2V->ToString());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		getIndexerPriority().push_back(FileIndexerWindow::FFMS->ToString());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		getIndexerPriority().push_back(FileIndexerWindow::AVISOURCE->ToString());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		getIndexerPriority().push_back(FileIndexerWindow::DGA->ToString());
	}

	const std::string &OneClickSettings::getSettingsID() const
	{
		return "OneClick";
	}

	void OneClickSettings::FixFileNames(std::map<std::string, std::string> &_)
	{
	}

	bool OneClickSettings::Equals(object *obj)
	{
		return Equals(dynamic_cast<GenericSettings*>(obj));
	}

	bool OneClickSettings::Equals(GenericSettings *other)
	{
		return other == 0 ? false : PropertyEqualityTester::AreEqual(this, other);
	}

	int OneClickSettings::GetHashCode()
	{
		return __super::GetHashCode();
	}

	object *OneClickSettings::ICloneable_Clone()
	{
		return Clone();
	}

	MeGUI::core::plugins::interfaces::GenericSettings *OneClickSettings::GenericSettings_Clone()
	{
		return Clone();
	}

	OneClickSettings *OneClickSettings::Clone()
	{
		return dynamic_cast<OneClickSettings*>(this->MemberwiseClone());
	}

	const std::string &OneClickSettings::getRequiredFiles() const
	{
		return new std::string[0];
	}

	const std::string &OneClickSettings::getRequiredProfiles() const
	{
		return new std::string[] {getVideoProfileName(), getAudioSettings()[0]->getProfile(), getAvsProfileName()};
	}
}
