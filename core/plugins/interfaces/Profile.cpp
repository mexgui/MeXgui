#include "Profile.h"




//using namespace System::Diagnostics;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::plugins::interfaces;

namespace MeXgui
{

	Profile::Profile()
	{
	}

	Profile::Profile(const QString &name)
	{
		this->name = name;
	}

	const QString &Profile::getName() const
	{
		assert(!name.empty());
		return name;
	}

	void Profile::setName(const QString &value)
	{
		name = value;
		assert(!name.empty());
	}

	const QString &Profile::getFQName() const
	{
		return BaseSettings::SettingsID + ": " + getName();
	}

	QString Profile::ToString()
	{
		return getName();
	}

	const QString &Profile::getID() const
	{
		return getFQName();
	}
}
