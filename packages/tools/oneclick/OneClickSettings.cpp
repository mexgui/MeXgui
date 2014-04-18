#include "OneClickSettings.h"




//using namespace System::Collections::Generic;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;

namespace MeXgui
{

const AudioEncodingMode OneClickSettings::SupportedModes[4] = {Always, IfCodecDoesNotMatch, NeverOnlyCore, Never};

	const QString &OneClickSettings::getVideoProfileName() const
	{
		return videoProfileName;
	}

	void OneClickSettings::setVideoProfileName(const QString &value)
	{
		videoProfileName = value;
	}

	const QString &OneClickSettings::getAvsProfileName() const
	{
		return avsProfileName;
	}

	void OneClickSettings::setAvsProfileName(const QString &value)
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

	const QString &OneClickSettings::getAudioProfileName() const
	{
		return "migrated";
	}

	void OneClickSettings::setAudioProfileName(const QString &value)
	{
		audioProfileName = value;
	}

	const QString &OneClickSettings::getAudioEncodingModeString() const
	{
		return "migrated";
	}

	void OneClickSettings::setAudioEncodingModeString(const QString &value)
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

		audioSettings = QVector<OneClickAudioSettings*>();
		audioSettings.push_back(new OneClickAudioSettings("[default]", audioProfileName, audioEncodingMode, false));
	}

	const QVector<OneClickAudioSettings*> &OneClickSettings::getAudioSettings() const
	{
		return audioSettings;
	}

	void OneClickSettings::setAudioSettings(const QVector<OneClickAudioSettings*> &value)
	{
		audioSettings = value;
	}

	const OneClickAudioSettings &OneClickSettings::getAudioSettingsString() const
	{
		return audioSettings.ToArray();
	}

	void OneClickSettings::setAudioSettingsString(const OneClickAudioSettings &value[])
	{
		audioSettings = QVector<OneClickAudioSettings*>(value);
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

	const qint64 &OneClickSettings::getOutputResolution() const
	{
		return outputResolution;
	}

	void OneClickSettings::setOutputResolution(const qint64 &value)
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

	const QString &OneClickSettings::getContainerCandidates() const
	{
		return containerCandidates;
	}

	void OneClickSettings::setContainerCandidates(const QString &value[])
	{
		containerCandidates = value;
	}

	const QString &OneClickSettings::getDeviceOutputType() const
	{
		return deviceType;
	}

	void OneClickSettings::setDeviceOutputType(const QString &value)
	{
		deviceType = value;
	}

	const QString &OneClickSettings::getLeadingName() const
	{
		return leadingName;
	}

	void OneClickSettings::setLeadingName(const QString &value)
	{
		leadingName = value;
	}

	const QString &OneClickSettings::getWorkingNameReplace() const
	{
		return workingNameReplace;
	}

	void OneClickSettings::setWorkingNameReplace(const QString &value)
	{
		workingNameReplace = value;
	}

	const QString &OneClickSettings::getWorkingNameReplaceWith() const
	{
		return workingNameReplaceWith;
	}

	void OneClickSettings::setWorkingNameReplaceWith(const QString &value)
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

	const QString &OneClickSettings::getDefaultWorkingDirectory() const
	{
		return defaultWorkingDirectory;
	}

	void OneClickSettings::setDefaultWorkingDirectory(const QString &value)
	{
		defaultWorkingDirectory = value;
	}

	const QString &OneClickSettings::getDefaultOutputDirectory() const
	{
		return defaultOutputDirectory;
	}

	void OneClickSettings::setDefaultOutputDirectory(const QString &value)
	{
		defaultOutputDirectory = value;
	}

	const QString &OneClickSettings::getDefaultLanguage() const
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

	void OneClickSettings::setDefaultLanguage(const QString &value)
	{
		defaultLanguage = value;
	}

	const QVector<QString> &OneClickSettings::getDefaultAudioLanguage() const
	{
		return defaultAudioLanguage;
	}

	void OneClickSettings::setDefaultAudioLanguage(const QVector<QString> &value)
	{
		defaultAudioLanguage = value;
	}

	const QString &OneClickSettings::getDefaultAudioLanguageString() const
	{
		return defaultAudioLanguage.ToArray();
	}

	void OneClickSettings::setDefaultAudioLanguageString(const QString &value[])
	{
		defaultAudioLanguage = QVector<QString>(value);
	}

	const QVector<QString> &OneClickSettings::getDefaultSubtitleLanguage() const
	{
		return defaultSubtitleLanguage;
	}

	void OneClickSettings::setDefaultSubtitleLanguage(const QVector<QString> &value)
	{
		defaultSubtitleLanguage = value;
	}

	const QString &OneClickSettings::getDefaultSubtitleLanguageString() const
	{
		return defaultSubtitleLanguage.ToArray();
	}

	void OneClickSettings::setDefaultSubtitleLanguageString(const QString &value[])
	{
		defaultSubtitleLanguage = QVector<QString>(value);
	}

	const QVector<QString> &OneClickSettings::getIndexerPriority() const
	{
		return indexerPriority;
	}

	void OneClickSettings::setIndexerPriority(const QVector<QString> &value)
	{
		indexerPriority = value;
	}

	const QString &OneClickSettings::getIndexerPriorityString() const
	{
		return indexerPriority.ToArray();
	}

	void OneClickSettings::setIndexerPriorityString(const QString &value[])
	{
		if (value->Length == 4)
		{
			Array::Resize<QString>(value, 5);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			value[4] = FileIndexerWindow::AVISOURCE->ToString();
		}
		indexerPriority = QVector<QString>(value);
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
		containerCandidates = new QString[] {"MKV"};
		defaultAudioLanguage = QVector<QString>();
		defaultSubtitleLanguage = QVector<QString>();
		indexerPriority = QVector<QString>();
		defaultWorkingDirectory = "";
		workingNameReplace = "";
		workingNameReplaceWith = "";
		leadingName = "";
		audioSettings = QVector<OneClickAudioSettings*>();
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

	const QString &OneClickSettings::getSettingsID() const
	{
		return "OneClick";
	}

	void OneClickSettings::FixFileNames(QMap<QString, QString> &_)
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

	MeXgui::core::plugins::interfaces::GenericSettings *OneClickSettings::GenericSettings_Clone()
	{
		return Clone();
	}

	OneClickSettings *OneClickSettings::Clone()
	{
		return dynamic_cast<OneClickSettings*>(this->MemberwiseClone());
	}

	const QString &OneClickSettings::getRequiredFiles() const
	{
		return new QString[0];
	}

	const QString &OneClickSettings::getRequiredProfiles() const
	{
		return new QString[] {getVideoProfileName(), getAudioSettings()[0]->getProfile(), getAvsProfileName()};
	}
}
