#include "OneClickWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::tools::oneclick;

namespace MeGUI
{

	OneClickFilesToProcess::OneClickFilesToProcess()
	{

	}

	OneClickFilesToProcess::OneClickFilesToProcess(const std::string &strPath, int iNumber)
	{
		FilePath = strPath;
		TrackNumber = iNumber;
	}

	const std::string &OneClickTool::getName() const
	{
		return "One Click Encoder";
	}

	void OneClickTool::Run(MainForm *info)
	{
		OneClickWindow *ocmt = new OneClickWindow(info);
		ocmt->Show();
	}

	const Shortcut &OneClickTool::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlF1};
	}

	const std::string &OneClickTool::getID() const
	{
		return "one_click";
	}
}
