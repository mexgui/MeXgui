#include "Besplitter.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;





//using namespace System::Text;


using namespace MeXgui::core::details;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{

				const QString &BesplitterTool::getName() const
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

				const QString &BesplitterTool::getID() const
				{
					return getName();
				}
			}
		}
	}
}
