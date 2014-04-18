#pragma once

#include "core/plugins/interfaces/IPackage.h"
#include "core/gui/MeGUI.MainForm.h"
#include "MeGUI.AviSynthWindow.h"
#include <string>

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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::util;

namespace MeGUI
{

	/// <summary>
	/// Summary description for AviSynthWindow.
	/// </summary>
	typedef void (*OpenScriptCallback)(const std::string &avisynthScript);
	enum PossibleSources
	{
		d2v,
		dga,
		dgi,
		mpeg2,
		vdr,
		directShow,
		avs,
		ffindex
	};
	enum mod16Method
	{
		none = -1,
		resize = 0,
		overcrop,
		nonMod16,
		mod4Horizontal,
		undercrop
	};
	enum modValue
	{
		mod16 = 0,
		mod8,
		mod4,
		mod2
	};

	class AviSynthWindowTool : public MeGUI::core::plugins::interfaces::ITool
	{


	public:
		const std::string &getName() const;

		void Run(MainForm *info);

		const Shortcut *getShortcuts() const;



		const std::string &getID() const;

	};
}
