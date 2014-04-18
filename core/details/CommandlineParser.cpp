#include "CommandlineParser.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

	bool CommandlineParser::Parse(QString& commandline[])
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
		upgradeData = QMap<QString, QString>();
		filesToInstall = QVector<QString>();
		failedUpgrades = QVector<QString>();
		start = true;
	}
}
