#include "Program.h"

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

	void CommandlineUpgradeData::InitializeInstanceFields()
	{
		filename = std::vector<std::string>();
		tempFilename = std::vector<std::string>();
	}

	void Program::showCommandlineErrorMessage(std::string& args[])
	{
		StringBuilder *cmdline = new StringBuilder();
		for (std::string::const_iterator arg = args->begin(); arg != args->end(); ++arg)
			cmdline->AppendLine(*arg);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		MessageBox::Show("Error in commandline update arguments: there aren't enough. No program files will be updated. Commandline:\r\n" + cmdline->ToString(), "Error in commandline", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	void Program::Main(std::string& args[])
	{
		std::string appName = "";
		appName = Path::Combine(Path::GetDirectoryName(Application::ExecutablePath), "megui.exe");
		bool bDebug = false;
	#if defined(DEBUG)
		bDebug = true;
	#endif
		if (!File::Exists(appName) && !bDebug)
		{
			MessageBox::Show(appName + " not found. \nNo files will be updated.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		StringBuilder *commandline = new StringBuilder();
		std::vector<std::exception> errorsEncountered = std::vector<std::exception>();
		std::map<std::string, CommandlineUpgradeData*> filesToCopy = std::map<std::string, CommandlineUpgradeData*>();
		std::vector<std::string> filesToInstall = std::vector<std::string>();
		bool bRestart = false;
		std::string lastComponentName = "";
		for (int i = 0; i < sizeof(args) / sizeof(args[0]); i += 1)
		{
			if (args[i] == "--restart")
			{
				bRestart = true;
				i++;
			}
			else if (args[i] == "--no-restart")
			{
				bRestart = false;
				i++;
			}
			else if (args[i] == "--component")
			{
				if (sizeof(args) / sizeof(args[0]) > i + 2)
				{
					CommandlineUpgradeData *data = new CommandlineUpgradeData();
					data->newVersion = args[i + 2];
					filesToCopy.insert(make_pair(args[i + 1], data));
					lastComponentName = args[i + 1];
					i += 2;
				}
				else
				{
					showCommandlineErrorMessage(args);
					return;
				}
			}
			else
			{
				if (sizeof(args) / sizeof(args[0]) > i + 1 && lastComponentName != "")
				{
					if (Path::GetExtension(args[i])->ToLower()->Equals(".zip") || Path::GetExtension(args[i])->ToLower()->Equals(".7z"))
					{
						if (filesToCopy.find(lastComponentName) != filesToCopy.end())
							filesToCopy.erase(lastComponentName);
						try
						{
							if (File::Exists(args[i]))
								File::Delete(args[i]);
							if (File::Exists(args[i + 1]))
								File::Delete(args[i + 1]);
						}
						catch (std::exception &e)
						{
							errorsEncountered.push_back(e);
						}
					}
					else if (filesToCopy.find(lastComponentName) != filesToCopy.end())
					{
						filesToCopy[lastComponentName]->filename->push_back(args[i]);
						filesToCopy[lastComponentName]->tempFilename->push_back(args[i + 1]);
					}
					i++;
				}
				else
				{
					showCommandlineErrorMessage(args);
					return;
				}
			}
		}

		delay(2000);
		for (std::map<std::string, CommandlineUpgradeData*>::const_iterator file = filesToCopy.begin(); file != filesToCopy.end(); ++file)
		{
			bool succeeded = true;
			for (int i = 0; i < filesToCopy[file]->tempFilename->size(); i++)
			{
				try
				{
					if (File::Exists(filesToCopy[file->first]->tempFilename[i]))
					{
						File::Delete(filesToCopy[file->first]->filename[i]);
						File::Move(filesToCopy[file->first]->tempFilename[i], filesToCopy[file->first]->filename[i]);
					}
				}
				catch (IOException *e1)
				{
					succeeded = false;
				}
				catch (std::exception &e)
				{
					succeeded = false;
					errorsEncountered.push_back(e);
				}
			}
			if (succeeded)
				commandline->AppendFormat("--upgraded \"{0}\" \"{1}\" ", file->first, filesToCopy[file->first]->newVersion);
			else
				commandline->AppendFormat("--upgrade-failed \"{0}\" ", file->first);
		}
		if (!bRestart)
			commandline->Append("--dont-start");

		for (std::vector<std::string>::const_iterator file = filesToInstall.begin(); file != filesToInstall.end(); ++file)
			commandline->AppendFormat("--install \"{0}\" ", *file);

		Process *proc = new Process();
		ProcessStartInfo *pstart = new ProcessStartInfo();
		pstart->FileName = appName;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		pstart->Arguments = commandline->ToString();
		pstart->UseShellExecute = false;
		proc->StartInfo = pstart;
		if (!proc->Start())
		{
			if (errorsEncountered.empty())
			{
				MessageBox::Show("Files updated but failed to restart MeGUI. You'll have to start it yourself.", "Failed to restart MeGUI", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			else
			{
				std::string message = "The following errors were encountered when updating MeGUI:\r\n";
				for (std::vector<std::exception>::const_iterator e = errorsEncountered.begin(); e != errorsEncountered.end(); ++e)
					message += (*e).Message + "\r\n";
				message += "Failed to restart MeGUI";
				MessageBox::Show(message, "Errors in update", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		if (errorsEncountered.empty())
			return;
		std::string message1 = "The following errors were encountered when updating MeGUI:\r\n";
		for (std::vector<std::exception>::const_iterator e = errorsEncountered.begin(); e != errorsEncountered.end(); ++e)
			message1 += (*e).Message + "\r\n";
		MessageBox::Show(message1, "Errors in update", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
