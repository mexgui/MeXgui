#include "HDBDStreamExtractor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace eac3to;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace hdbdextractor
			{

				const std::string &HdBdExtractorTool::getName() const
				{
					return "HD Streams Extractor";
				}

				void HdBdExtractorTool::Run(MainForm *info)
				{
					(new HdBdStreamExtractor(info))->Show();
				}

				const Shortcut &HdBdExtractorTool::getShortcuts() const
				{
					return new Shortcut[] {Shortcut::CtrlF7};
				}

				const std::string &HdBdExtractorTool::getID() const
				{
					return getName();
				}
			}
		}
	}
}
