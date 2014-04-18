#include "OneClickWindow.h"




//using namespace System::Collections::Generic;







//using namespace System::Text;


using namespace MeXgui::core::details;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::oneclick;

namespace MeXgui
{

	OneClickFilesToProcess::OneClickFilesToProcess()
	{

	}

	OneClickFilesToProcess::OneClickFilesToProcess(const QString &strPath, int iNumber)
	{
		FilePath = strPath;
		TrackNumber = iNumber;
	}

	const QString &OneClickTool::getName() const
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

	const QString &OneClickTool::getID() const
	{
		return "one_click";
	}
}
