#include "OneClickAudioControl.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::gui;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;

namespace MeGUI
{

	OneClickAudioSettings::OneClickAudioSettings()
	{

	}

	OneClickAudioSettings::OneClickAudioSettings(const std::string &language, const std::string &profile, MeGUI::AudioEncodingMode mode, bool useFirstTrackOnly)
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

	MeGUI::core::plugins::interfaces::GenericSettings *OneClickAudioSettings::GenericSettings_Clone()
	{
		return Clone();
	}

	OneClickSettings *OneClickAudioSettings::Clone()
	{
		return dynamic_cast<OneClickSettings*>(this->MemberwiseClone());
	}

	const std::string &OneClickAudioSettings::getRequiredFiles() const
	{
		return new std::string[0];
	}

	const std::string &OneClickAudioSettings::getRequiredProfiles() const
	{
		return new std::string[0];
	}

	bool OneClickAudioSettings::Equals(object *obj)
	{
		return Equals(dynamic_cast<GenericSettings*>(obj));
	}

	bool OneClickAudioSettings::Equals(GenericSettings *other)
	{
		return other == 0 ? false : PropertyEqualityTester::AreEqual(this, other);
	}

	const std::string &OneClickAudioSettings::getSettingsID() const
	{
		return "OneClick";
	}

	void OneClickAudioSettings::FixFileNames(std::map<std::string, std::string> &_)
	{
	}

	int OneClickAudioSettings::GetHashCode()
	{
		return __super::GetHashCode();
	}

	const MeGUI::AudioEncodingMode &OneClickAudioSettings::getAudioEncodingMode() const
	{
		return audioEncodingMode;
	}

	void OneClickAudioSettings::setAudioEncodingMode(const MeGUI::AudioEncodingMode &value)
	{
		audioEncodingMode = value;
	}

	const std::string &OneClickAudioSettings::getAudioEncodingModeString() const
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return audioEncodingMode.ToString();
	}

	void OneClickAudioSettings::setAudioEncodingModeString(const std::string &value)
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

	const std::string &OneClickAudioSettings::getLanguage() const
	{
		return language;
	}

	void OneClickAudioSettings::setLanguage(const std::string &value)
	{
		language = value;
	}

	const std::string &OneClickAudioSettings::getProfile() const
	{
		return profile;
	}

	void OneClickAudioSettings::setProfile(const std::string &value)
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
