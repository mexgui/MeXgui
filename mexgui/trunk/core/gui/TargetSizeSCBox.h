#pragma once

#include "MeGUI.core.gui.StandardAndCustomComboBox.h"
#include "StandardAndCustomComboBox.h"
#include "core/util/FileSize.h"
#include "MeGUI.MainForm.h"
#include "MeGUI.core.gui.FileSizeDialog.h"
#include "core/util/Util.h"
#include <string>
#include <vector>

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
//using namespace System::Diagnostics;
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
			class TargetSizeSCBox : public StandardAndCustomComboBox
			{
			public:
				static const Named<FileSize> PredefinedFilesizes[5];

				public:
				~TargetSizeSCBox()
				{
					this->Dispose(true);
				}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:
				void Finalize()
				{
					this->Dispose(false);
				}

			private:
				void Dispose(bool disposing);

				std::string nullString;
				/// <summary>
				/// String to display which represents "null" filesize. If NullString is set to null, then
				/// there is no option not to select a filesize.
				/// </summary>
			public:
				const std::string &getNullString() const;
				void setNullString(const std::string &value);

			private:
				FileSize minSize;

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const FileSize &getMinimumFileSize() const;
				void setMinimumFileSize(const FileSize &value);

			private:
				Nullable<FileSize> maxSize;

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const Nullable<FileSize> &getMaximumFileSize() const;
				void setMaximumFileSize(const Nullable<FileSize> &value);

				TargetSizeSCBox();

			private:
				void fillStandard();

				FileSizeDialog *ofd;

				object *getter();

			public:
				const FileSize *getCustomSizes() const;
				void setCustomSizes(FileSize value[]);


			private:
				std::string genRestrictions();

				/// <summary>
				/// Gets / sets the target, or null if the user doesn't care about filesize
				/// </summary>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const Nullable<FileSize> &getValue() const;

				void setValue(const Nullable<FileSize> &value);

				/// <summary>
				/// Gets / sets the target, or null if the user doesn't care about filesize
				/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const FileSize &getCertainValue() const;
				void setCertainValue(const FileSize &value);

				const bool &getSaveCustomValues() const;
				void setSaveCustomValues(const bool &value);

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
