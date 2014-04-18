#include "UpdateWindow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Net;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace ICSharpCode::SharpZipLib::Zip;
using namespace SevenZip;
using namespace MeGUI::core::util;

namespace MeGUI
{

	const std::string &UpdateOptions::getName() const
	{
		return "Update";
	}

	void UpdateOptions::Run(MainForm *info)
	{
		UpdateWindow *update = new UpdateWindow(info, false);
		update->ShowDialog();
	}

	const Shortcut &UpdateOptions::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlU};
	}

	const std::string &UpdateOptions::getID() const
	{
		return "update_window";
	}

	const std::string &FileNotRegisteredYetException::getName() const
	{
		return name;
	}

	FileNotRegisteredYetException::FileNotRegisteredYetException(const std::string &name) : MeGUIException("AutoUpdate file '" + name + "' not registered with MeGUI.")
	{
		this->name = name;
	}
}
