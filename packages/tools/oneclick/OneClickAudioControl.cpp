#include "OneClickAudioControl.h"




//using namespace System::Collections::Generic;




using namespace MeXgui::core::gui;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;

namespace MeXgui
{

	OneClickAudioSettings::OneClickAudioSettings()
	{

	}

	OneClickAudioSettings::OneClickAudioSettings(const QString &language, const QString &profile, MeXgui::AudioEncodingMode mode, bool useFirstTrackOnly)
	{
		this->language = language;
		this->profile = profile;
		this->audioEncodingMode = mode;
		this->useFirstTrackOnly = useFirstTrackOnly;
	}

	object *OneClickAudioSettings::ICloneable_Clone()
	{
		return Clone();
	}

	MeXgui::core::plugins::interfaces::GenericSettings *OneClickAudioSettings::GenericSettings_Clone()
	{
		return Clone();
	}

	OneClickSettings *OneClickAudioSettings::Clone()
	{
		return dynamic_cast<OneClickSettings*>(this->MemberwiseClone());
	}

	const QString &OneClickAudioSettings::getRequiredFiles() const
	{
		return new QString[0];
	}

	const QString &OneClickAudioSettings::getRequiredProfiles() const
	{
		return new QString[0];
	}

	bool OneClickAudioSettings::Equals(object *obj)
	{
		return Equals(dynamic_cast<GenericSettings*>(obj));
	}

	bool OneClickAudioSettings::Equals(GenericSettings *other)
	{
		return other == 0 ? false : PropertyEqualityTester::AreEqual(this, other);
	}

	const QString &OneClickAudioSettings::getSettingsID() const
	{
		return "OneClick";
	}

	void OneClickAudioSettings::FixFileNames(QMap<QString, QString> &_)
	{
	}

	int OneClickAudioSettings::GetHashCode()
	{
		return __super::GetHashCode();
	}

	const MeXgui::AudioEncodingMode &OneClickAudioSettings::getAudioEncodingMode() const
	{
		return audioEncodingMode;
	}

	void OneClickAudioSettings::setAudioEncodingMode(const MeXgui::AudioEncodingMode &value)
	{
		audioEncodingMode = value;
	}

	const QString &OneClickAudioSettings::getAudioEncodingModeString() const
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return audioEncodingMode.ToString();
	}

	void OneClickAudioSettings::setAudioEncodingModeString(const QString &value)
	{
		if (value.Equals("Never"))
			audioEncodingMode = Never;
		else if (value.Equals("IfCodecDoesNotMatch"))
			audioEncodingMode = IfCodecDoesNotMatch;
		else if (value.Equals("NeverOnlyCore"))
			audioEncodingMode = NeverOnlyCore;
		else
			audioEncodingMode = Always;
	}

	const QString &OneClickAudioSettings::getLanguage() const
	{
		return language;
	}

	void OneClickAudioSettings::setLanguage(const QString &value)
	{
		language = value;
	}

	const QString &OneClickAudioSettings::getProfile() const
	{
		return profile;
	}

	void OneClickAudioSettings::setProfile(const QString &value)
	{
		profile = value;
	}

	const bool &OneClickAudioSettings::getUseFirstTrackOnly() const
	{
		return useFirstTrackOnly;
	}

	void OneClickAudioSettings::setUseFirstTrackOnly(const bool &value)
	{
		useFirstTrackOnly = value;
	}
}
