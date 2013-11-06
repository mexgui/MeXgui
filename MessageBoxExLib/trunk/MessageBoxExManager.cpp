#include "MessageBoxExManager.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Resources;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
namespace Utils
{
	namespace MessageBoxExLib
	{

Hashtable *MessageBoxExManager::_standardButtonsText = new Hashtable();

		MessageBoxExManager::MessageBoxExManager()
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_standardButtonsText[Ok->ToString()] = "Ok";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_standardButtonsText[Cancel->ToString()] = "Cancel";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_standardButtonsText[Yes->ToString()] = "Yes";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_standardButtonsText[No->ToString()] = "No";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_standardButtonsText[Abort->ToString()] = "Abort";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_standardButtonsText[Retry->ToString()] = "Retry";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_standardButtonsText[Ignore->ToString()] = "Ignore";
		}

		std::string MessageBoxExManager::GetLocalizedString(const std::string &key)
		{
			if (_standardButtonsText->ContainsKey(key))
			{
				return static_cast<std::string>(_standardButtonsText[key]);
			}
			else
			{
				return 0;
			}
		}
	}
}
