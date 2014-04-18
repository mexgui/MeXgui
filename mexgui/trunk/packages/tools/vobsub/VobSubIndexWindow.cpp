#include "VobSubIndexWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;

namespace MeGUI
{

	const std::string &VobSubTool::getName() const
	{
		return "VobSubber";
	}

	void VobSubTool::Run(MainForm *info)
	{
		(new VobSubIndexWindow(info))->Show();
	}

	const Shortcut &VobSubTool::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlN};
	}

	const std::string &VobSubTool::getID() const
	{
		return "VobSubber";
	}
}
