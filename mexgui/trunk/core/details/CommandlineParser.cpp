#include "CommandlineParser.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	bool CommandlineParser::Parse(std::string& commandline[])
	{
		for (int i = 0; i < sizeof(commandline) / sizeof(commandline[0]); i++)
		{
			if (commandline[i] == "--upgraded")
			{
				if (sizeof(commandline) / sizeof(commandline[0]) > i + 2)
				{
					upgradeData.insert(make_pair(commandline[i + 1], commandline[i + 2]));
					i += 2;
				}
				else
					return false;
			}
			else if (commandline[i] == "--install")
			{
				if (sizeof(commandline) / sizeof(commandline[0]) > i + 1)
				{
					filesToInstall.push_back(commandline[i + 1]);
					i++;
				}
				else
					return false;
			}
			else if (commandline[i] == "--upgrade-failed")
			{
				if (sizeof(commandline) / sizeof(commandline[0]) > i + 1)
				{
					failedUpgrades.push_back(commandline[i + 1]);
					i++;
				}
				else
					return false;
			}
			else if (commandline[i] == "--dont-start")
			{
				start = false;
			}
			else
				return false;
		}
		return true;
	}

	void CommandlineParser::InitializeInstanceFields()
	{
		upgradeData = std::map<std::string, std::string>();
		filesToInstall = std::vector<std::string>();
		failedUpgrades = std::vector<std::string>();
		start = true;
	}
}
