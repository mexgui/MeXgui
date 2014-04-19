#pragma once

#include "StandardAndCustomComboBox.h"
#include "MainForm.h"
#include "core/util/Util.h"
#include <QString>

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




//using namespace System::Collections::Generic;

//using namespace System::Text;



using namespace MeXgui::core::util;

namespace MeXgui
{
	namespace core
	{
		namespace gui
		{
			class FileSCBox : public StandardAndCustomComboBox
			{
			public:
				enum FileSCBoxType
				{
					Default,
					OC_FILE_AND_FOLDER,
					OC_FILE
				};

			public:
				FileSCBox();

			private:
				OpenFileDialog *ofd;
				FolderBrowserDialog *fbd;
				FileSCBoxType oType;

				object *getter();

				object *getterFolder();

			public:
				const QString &getFilter() const;
				void setFilter(const QString &value);

				const FileSCBoxType &getType() const;
				void setType(const FileSCBoxType &value);

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
