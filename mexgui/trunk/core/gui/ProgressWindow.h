#pragma once

#include "core/details/StatusUpdate.h"
#include "core/plugins/interfaces/Job.h"

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::util;

namespace MeGUI
{
	typedef void (*WindowClosedCallback)(bool hideOnly); // delegate for WindowClosed event
	typedef void (*AbortCallback)(); // delegate for Abort event
	typedef void (*UpdateStatusCallback)(StatusUpdate *su); // delegate for UpdateStatus event
	typedef void (*PriorityChangedCallback)(ProcessPriority priority); // delegate for PriorityChanged event

	/// <summary>
	/// ProgressWindow is a window that is being shown during encoding and shows the current encoding status
	/// it is being fed by UpdateStatus events fired from the main GUI class (Form1)
	/// </summary>
}
