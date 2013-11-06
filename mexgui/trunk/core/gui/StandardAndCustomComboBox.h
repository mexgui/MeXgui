#pragma once

#include <string>

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
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Configuration;
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
	namespace core
	{
		namespace gui
		{
			/// <summary>
			/// Represents a drop-down ComboBox which has both standard and custom values.
			/// Examples are CQMs (for x264, the standard two are "flat" and "jvt", and
			/// custom ones are user-selected files) and file-sizes (standard is "1 CD", "2 CD",
			/// custom is "100MB", etc).
			/// 
			/// There are three separated sections, with the Standard at the top, the custom 
			/// in the middle, and one or two buttons at the bottom to choose a new custom 
			/// option, and to clear all custom options.
			/// 
			/// Known derived classes are FileSCBox, which opens an OpenFileDialog as the
			/// new custom option, and FileSizeSCBox, which lets the user choose a non-custom
			/// filesize.
			/// </summary>

			class SCItem
			{
			public:
				object *Tag;
				bool IsStandard;

				SCItem(object *tag, bool isStandard);

				virtual std::string ToString();
			};

			template<typename T>
			class Named
			{
			public:
				T Data;
				std::string Name;

				Named(const std::string &name, T data)
				{
					Data = data;
					Name = name;
				}

				virtual bool Equals(object *obj)
				{
					return ((static_cast<dynamic_cast<Named<T*>*>(obj)*>(!) = 0) && (static_cast<Named<T>*>(obj))->Data->Equals(Data)) || (dynamic_cast<T>(obj) != 0 && (static_cast<T>(obj))->Equals(Data));
				}

				virtual int GetHashCode()
				{
					return 0;
				}

				virtual std::string ToString()
				{
					return Name;
				}
			};
		}
	}
}


