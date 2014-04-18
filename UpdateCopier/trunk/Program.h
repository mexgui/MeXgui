#pragma once

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace UpdateCopier
{
	class CommandlineUpgradeData
	{
	public:
		std::vector<std::string> filename;
		std::vector<std::string> tempFilename;
		std::string newVersion;

	private:
		void InitializeInstanceFields();

public:
		CommandlineUpgradeData()
		{
			InitializeInstanceFields();
		}
	};
	class Program
	{
	private:
		static void showCommandlineErrorMessage(std::string& args[]);

		static void Main(std::string& args[]);
	};
}
