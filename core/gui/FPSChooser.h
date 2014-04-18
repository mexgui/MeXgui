#pragma once

#include "MeGUI.core.gui.StandardAndCustomComboBox.h"
#include "MeGUI.core.gui.NumberChooser.h"
#include "MeGUI.MainForm.h"
#include "core/util/Util.h"
#include <QString>
#include <QVector>
#include <cmath>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
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



using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class FPSChooser : public StandardAndCustomComboBox
			{
			private:
				static const object Framerates[8];

				public:
				~FPSChooser()
				{
					this->Dispose(true);
				}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:
				void Finalize()
				{
					this->Dispose(false);
				}

			public:
				FPSChooser();

			private:
				void Dispose(bool disposing);

				QString nullString;
				/// <summary>
				/// String to display which represents "null" filesize. If NullString is set to null, then
				/// there is no option not to select a filesize.
				/// </summary>
			public:
				const QString &getNullString() const;
				void setNullString(const QString &value);

			private:
				void fillStandard();

				const FPS *getCustomFPSs() const;
				void setCustomFPSs(FPS value[]);


			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const Nullable<decimal> &getValue() const;
				void setValue(const Nullable<decimal> &value);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility::Hidden)]
				const decimal &getCertainValue() const;
				void setCertainValue(const decimal &value);
			};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[TypeConverter(FPSConverter::typeid)]
			class FPS
			{
			public:
				FPS(decimal v);

				decimal fps;

				virtual QString ToString();

				static FPS Parse(const QString &s);

				virtual bool Equals(object *obj);

				virtual int GetHashCode();
			};

			class FPSConverter : public TypeConverter
			{
			public:
				virtual bool CanConvertFrom(ITypeDescriptorContext *context, Type *sourceType);

				virtual object *ConvertFrom(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value);

				virtual object *ConvertTo(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value, Type *destinationType);
			};
		}
	}
}
