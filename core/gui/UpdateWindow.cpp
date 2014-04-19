#include "UpdateWindow.h"






//using namespace System::Collections::Generic;





//using namespace System::Net;

//using namespace System::Text;

//using namespace System::Threading;



//using namespace System::Xml;

//using namespace System::Xml::Serialization;
using namespace ICSharpCode::SharpZipLib::Zip;
using namespace SevenZip;
using namespace MeXgui::core::util;

namespace MeXgui
{

	const QString &UpdateOptions::getName() const
	{
		return "Update";
	}

	void UpdateOptions::Run(MainForm *info)
	{
		UpdateWindow *update = new UpdateWindow(info, false);
		update->show();
	}

	const Shortcut &UpdateOptions::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlU};
	}

	const QString &UpdateOptions::getID() const
	{
		return "update_window";
	}

	const QString &FileNotRegisteredYetException::getName() const
	{
		return name;
	}

	FileNotRegisteredYetException::FileNotRegisteredYetException(const QString &name) : MeXguiException("AutoUpdate file '" + name + "' not registered with ")
	{
		this->name = name;
	}
}
