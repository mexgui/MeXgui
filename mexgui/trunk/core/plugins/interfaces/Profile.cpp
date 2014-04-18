#include "Profile.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{

	Profile::Profile()
	{
	}

	Profile::Profile(const std::string &name)
	{
		this->name = name;
	}

	const std::string &Profile::getName() const
	{
		assert(!name.empty());
		return name;
	}

	void Profile::setName(const std::string &value)
	{
		name = value;
		assert(!name.empty());
	}

	const std::string &Profile::getFQName() const
	{
		return BaseSettings::SettingsID + ": " + getName();
	}

	std::string Profile::ToString()
	{
		return getName();
	}

	const std::string &Profile::getID() const
	{
		return getFQName();
	}
}
