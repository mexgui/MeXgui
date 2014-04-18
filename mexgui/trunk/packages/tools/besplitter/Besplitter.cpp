#include "Besplitter.h"

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
using namespace MeGUI::core::details;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{

				const std::string &BesplitterTool::getName() const
				{
					return "Audio Cutter";
				}

				void BesplitterTool::Run(MainForm *info)
				{
					(new Besplitter(info))->Show();
				}

				const Shortcut &BesplitterTool::getShortcuts() const
				{
					return new Shortcut[] {Shortcut::CtrlK};
				}

				const std::string &BesplitterTool::getID() const
				{
					return getName();
				}
			}
		}
	}
}
