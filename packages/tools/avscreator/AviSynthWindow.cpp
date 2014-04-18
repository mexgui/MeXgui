#include "AviSynthWindow.h"




//using namespace System::Collections::Generic;



//using namespace System::Globalization;



//using namespace System::Text;


using namespace MeXgui::core::util;

namespace MeXgui
{

	const QString &AviSynthWindowTool::getName() const
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

	const QString &AviSynthWindowTool::getID() const
	{
		return "AvsCreator";
	}
}
