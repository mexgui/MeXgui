#include "MeGUI.Properties.Settings.h"

namespace MeGUI
{
	namespace Properties
	{

		Settings::Settings()
		{
			// // To add event handlers for saving and changing settings, uncomment the lines below:
		}

		void Settings::SettingChangingEventHandler(object *sender, System::Configuration::SettingChangingEventArgs *e)
		{
			// Add code to handle the SettingChangingEvent event here.
		}

		void Settings::SettingsSavingEventHandler(object *sender, System::ComponentModel::CancelEventArgs *e)
		{
			// Add code to handle the SettingsSaving event here.
		}

Settings *Settings::defaultInstance = (static_cast<Settings*>(System::Configuration::ApplicationSettingsBase::Synchronized(new Settings())));

		const MeGUI::Properties::Settings &Settings::getDefault() const
		{
			return defaultInstance;
		}
	}
}
