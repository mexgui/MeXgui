#pragma once

#include "core/plugins/interfaces/IPackage.h"
#include "core/gui/MainForm.h"
#include "OneClickWindow.h"
#include <QString>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************




//using namespace System::Collections::Generic;







//using namespace System::Text;



using namespace MeXgui::core::details;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::oneclick;

namespace MeXgui
{

	class OneClickFilesToProcess
	{
	public:
		QString FilePath;
		int TrackNumber;

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public OneClickFilesToProcess() : this(string.Empty, 1)
		OneClickFilesToProcess();

		OneClickFilesToProcess(const QString &strPath, int iNumber);
	};

	class OneClickTool : public MeXgui::core::plugins::interfaces::ITool
	{


	public:
		const QString &getName() const;

		void Run(MainForm *info);

		const Shortcut *getShortcuts() const;



		const QString &getID() const;


	};
}
