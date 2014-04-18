#include "SimpleProfilesControl.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			const std::string &ProfileCouldntBeSelectedException::getProfileName() const
			{
				return name;
			}

			ProfileCouldntBeSelectedException::ProfileCouldntBeSelectedException(const std::string &name) : MeGUIException("The profile '" + name + "' couldn't be selected.")
			{
				this->name = name;
			}
		}
	}
}
