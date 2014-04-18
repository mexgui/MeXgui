#include "AviSynthWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;

namespace MeGUI
{

	const std::string &AviSynthWindowTool::getName() const
	{
		return "AVS Script Creator";
	}

	void AviSynthWindowTool::Run(MainForm *info)
	{
		info->ClosePlayer();
		AviSynthWindow *asw = new AviSynthWindow(info);
		asw->OpenScript += new OpenScriptCallback(this, &info->getVideo()->openVideoFile);
		asw->Show();
	}

	const Shortcut &AviSynthWindowTool::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlR};
	}

	const std::string &AviSynthWindowTool::getID() const
	{
		return "AvsCreator";
	}
}
