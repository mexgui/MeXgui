#include "DialogManager.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace Utils::MessageBoxExLib;

namespace MeGUI
{

	DialogManager::DialogManager(MainForm *mainForm)
	{
		this->mainForm = mainForm;
	}

	MessageBoxEx *DialogManager::createMessageBox(const std::string &text, const std::string &caption, MessageBoxIcon *icon)
	{
		MessageBoxEx *msgBox = new MessageBoxEx();
		msgBox->Caption = caption;
		msgBox->Text = text;
		msgBox->Icon = icon;
		msgBox->AllowSaveResponse = true;
		msgBox->SaveResponseText = "Don't ask me this again";
		return msgBox;
	}

	bool DialogManager::showMessage(const std::string &text, const std::string &caption, MessageBoxIcon *icon)
	{
		MessageBoxEx *msgBox = createMessageBox(text, caption, icon);
		msgBox->AddButtons(MessageBoxButtons::OK);
		msgBox->Show();
		return !msgBox->SaveResponseChecked;
	}

	bool DialogManager::askAbout(const std::string &text, const std::string &caption, MessageBoxIcon *icon, bool &askAgain)
	{
		return askAbout(text, caption, "Yes", "No", icon, askAgain);
	}

	bool DialogManager::askAbout(const std::string &text, const std::string &caption, const std::string &button1Text, const std::string &button2Text, MessageBoxIcon *icon, bool &askAgain)
	{
		MessageBoxEx *msgBox = createMessageBox(text, caption, icon);

		msgBox->AddButton(button1Text, "true");
		msgBox->AddButton(button2Text, "false");

		std::string sResult = msgBox->Show();
		askAgain = !msgBox->SaveResponseChecked;
		return (sResult.Equals("true"));
	}

	int DialogManager::askAbout3(const std::string &text, const std::string &caption, const std::string &button1Text, const std::string &button2Text, const std::string &button3Text, MessageBoxIcon *icon)
	{
		MessageBoxEx *msgBox = createMessageBox(text, caption, icon);

		msgBox->AddButton(button1Text, "0");
		msgBox->AddButton(button2Text, "1");
		msgBox->AddButton(button3Text, "2");

		msgBox->AllowSaveResponse = false;

		std::string sResult = msgBox->Show();
		return int::Parse(sResult);
	}

	bool DialogManager::overwriteJobOutput(const std::string &outputname)
	{
		if (mainForm->getSettings()->getDialogSettings()->getAskAboutOverwriteJobOutput())
		{
			bool askAgain;
			bool bResult = askAbout("The output file, '" + outputname + "' already exists. Would you like to overwrite?", "File Already Exists", MessageBoxIcon::Warning, askAgain);

			mainForm->getSettings()->getDialogSettings()->setAskAboutOverwriteJobOutput(askAgain);
			mainForm->getSettings()->getDialogSettings()->setOverwriteJobOutputResponse(bResult);
			return bResult;
		}
		return mainForm->getSettings()->getDialogSettings()->getOverwriteJobOutputResponse();
	}

	bool DialogManager::overwriteProfile(const std::string &profname)
	{
		if (mainForm->getSettings()->getDialogSettings()->getAskAboutDuplicates())
		{
			if (!MainForm::Instance->getSettings()->getAutoUpdateSession())
			{
				bool askAgain;
				bool bResult = askAbout("Problem adding profile '" + profname + "':\r\none with the same name already exists. \r\nWhat do you want to do?", "Duplicate profile", "Overwrite profile", "Skip profile", MessageBoxIcon::Exclamation, askAgain);

				mainForm->getSettings()->getDialogSettings()->setAskAboutDuplicates(askAgain);
				mainForm->getSettings()->getDialogSettings()->setDuplicateResponse(bResult);
				return bResult;
			}
			else
				return false;
		}
		return mainForm->getSettings()->getDialogSettings()->getDuplicateResponse();
	}

	bool DialogManager::useOneClick()
	{
		if (mainForm->getSettings()->getDialogSettings()->getAskAboutVOBs())
		{
			bool askAgain;
			bool bResult = askAbout("Do you want to open this file with the One Click\r\n" + "Encoder (automated, easy to use) or the File\r\n" + "Indexer (manual, advanced)?", "Please choose your preferred tool", "One Click Encoder", "File Indexer", MessageBoxIcon::Question, askAgain);

			mainForm->getSettings()->getDialogSettings()->setAskAboutVOBs(askAgain);
			mainForm->getSettings()->getDialogSettings()->setUseOneClick(bResult);
			return bResult;
		}
		return mainForm->getSettings()->getDialogSettings()->getUseOneClick();
	}

	int DialogManager::AVSCreatorOpen(const std::string &videoInput)
	{
		int iResult = -1;
		MediaInfoFile *iFile = new MediaInfoFile(videoInput);
		FileIndexerWindow::IndexType oIndexer;

		if (!iFile->recommendIndexer(oIndexer))
			return iResult;

		if (oIndexer != FileIndexerWindow::D2V && oIndexer != FileIndexerWindow::DGA && oIndexer != FileIndexerWindow::DGI && oIndexer != FileIndexerWindow::FFMS)
			return iResult;

		if (iFile->getContainerFileTypeString().ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Equals("AVI"))
		{
			iResult = askAbout3("Do you want to open this file with\r\n" + "- One Click Encoder (full automated, easy to use) or\r\n" + "- File Indexer (manual, advanced) or \r\n" + "- AviSource (manual, expert, may cause problems)?", "Please choose your prefered way to open this file", "One Click Encoder", "File Indexer", "AviSource", MessageBoxIcon::Question);
		}
		else
		{
			iResult = askAbout3("Do you want to open this file with\r\n" + "- One Click Encoder (full automated, easy to use) or\r\n" + "- File Indexer (manual, advanced) or \r\n" + "- DirectShowSource (manual, expert, may cause problems)?", "Please choose your prefered way to open this file", "One Click Encoder", "File Indexer", "DirectShowSource", MessageBoxIcon::Question);
		}
		return iResult;
	}

	bool DialogManager::createJobs(const std::string &error)
	{
		if (mainForm->getSettings()->getDialogSettings()->getAskAboutError())
		{
			bool askAgain;
			bool bResult = askAbout(std::string::Format("Your AviSynth clip has the following problem:\r\n{0}\r\nContinue anyway?", error), "Problem in AviSynth script", MessageBoxIcon::Warning, askAgain);

			mainForm->getSettings()->getDialogSettings()->setAskAboutError(askAgain);
			mainForm->getSettings()->getDialogSettings()->setContinueDespiteError(bResult);
			return bResult;
		}
		return mainForm->getSettings()->getDialogSettings()->getContinueDespiteError();
	}

	bool DialogManager::addConvertToYV12(const std::string &colorspace)
	{
		if (mainForm->getSettings()->getDialogSettings()->getAskAboutYV12())
		{
			bool askAgain;
			bool bResult = askAbout("The colorspace of your clip is not in YV12...\r\n" + "Do you want me to add ConvertToYV12() to the end of your script ?", "Incorrect Colorspace", MessageBoxIcon::Warning, askAgain);

			mainForm->getSettings()->getDialogSettings()->setAskAboutYV12(askAgain);
			mainForm->getSettings()->getDialogSettings()->setAddConvertToYV12(bResult);
			return bResult;
		}
		return mainForm->getSettings()->getDialogSettings()->getAddConvertToYV12();
	}

	bool DialogManager::DeleteIntermediateFiles(std::vector<std::string> &arrFiles)
	{
		if (mainForm->getSettings()->getDialogSettings()->getAskAboutIntermediateDelete())
		{
			std::string strFiles = "";
			;
			for (std::vector<std::string>::const_iterator file = arrFiles.begin(); file != arrFiles.end(); ++file)
				strFiles += "\r\n" + *file;

			bool askAgain;
			bool bResult = askAbout("Do you really want to delete the intermediate files below?\r\nThese files may still be required as the job did not finish successfully.\r\n" + strFiles, "Confirm deletion of intermediate files", MessageBoxIcon::Warning, askAgain);

			mainForm->getSettings()->getDialogSettings()->setAskAboutIntermediateDelete(askAgain);
			mainForm->getSettings()->getDialogSettings()->setIntermediateDelete(bResult);
			return bResult;
		}
		return mainForm->getSettings()->getDialogSettings()->getIntermediateDelete();
	}
}
