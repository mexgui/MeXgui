#include "Cutter.h"

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
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace cutter
			{

				const std::string &CutterTool::getName() const
				{
					return "AVS Cutter";
				}

				void CutterTool::Run(MainForm *info)
				{
					OpenFileDialog *d = new OpenFileDialog();
					d->Filter = "AviSynth scripts (*.avs)|*.avs";
					d->Title = "Select the input video";
					if (d->ShowDialog() != DialogResult::OK)
						return;
					(new Cutter(info, d->FileName))->Show();
				}

				const Shortcut &CutterTool::getShortcuts() const
				{
					return new Shortcut[] {Shortcut::CtrlD};
				}

				const std::string &CutterTool::getID() const
				{
					return getName();
				}
			}
		}
	}
}
