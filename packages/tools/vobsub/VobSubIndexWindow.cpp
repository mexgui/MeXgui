#include "VobSubIndexWindow.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;





//using namespace System::Text;


using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;

namespace MeXgui
{

	const QString &VobSubTool::getName() const
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

	const QString &VobSubTool::getID() const
	{
		return "VobSubber";
	}
}
