#pragma once

#include<Qt>
#include "MessageBoxExButtons.h"
#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
using namespace System::Resources;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
using namespace System::Reflection;

namespace Utils
{
	namespace MessageBoxExLib
	{
		/// <summary>
		/// Manages a collection of MessageBoxes. Basically manages the
		/// saved response handling for messageBoxes.
		/// </summary>
		class MessageBoxExManager
		{
		private:
			static Hashtable *_standardButtonsText;
//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
			static MessageBoxExManager();
			/// <summary>
			/// Returns the localized string for standard button texts like,
			/// "Ok", "Cancel" etc.
			/// </summary>
			/// <param name="key"></param>
			/// <returns></returns>
		public:
			static std::string GetLocalizedString(const std::string &key);
		};
	}
}
