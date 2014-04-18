#pragma once

#include <string>
#include <cmath>

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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			enum Unit
			{
				B = 0,
				KB,
				MB,
				GB
			};

			/// <summary>
			/// Aims to be the universal representation of filesize in MeGUI.
			/// Should avoid problems of MB/KB/B, and gives nice formatting as required
			/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[TypeConverter(FileSizeConverter::typeid)]
			class FileSize
			{
			public:
				static const FileSize Empty;
				static const FileSize MinNonZero;


				static FileSize Of(const std::string &filename);

				static Nullable<FileSize> Of2(const std::string &filename);
				static const std::string UnitSuffixes[4];
			private:
				unsigned long long sizeInBytes;

				/// <summary>
				/// Returns the stored size, divided by divisor and rounded appropriately
				/// </summary>
				/// <param name="divisor"></param>
				/// <returns></returns>
				unsigned long long divideAndRound(unsigned long long divisor);

				/// <summary>
				/// Sets sizeInBytes to (value * divisor) rounded appropriately
				/// </summary>
				/// <param name="divisor"></param>
				/// <param name="value"></param>
				void setExact(unsigned long long divisor, decimal value);

				unsigned long long divisor(Unit u);

				/// <summary>
				/// Returns the stored size in the requested units (rounded)
				/// </summary>
				/// <param name="shift"></param>
				/// <returns></returns>
			public:
				unsigned long long InUnits(Unit u);

				/// <summary>
				/// Returns the stored size in the requested units (exact)
				/// </summary>
				/// <param name="u"></param>
				/// <returns></returns>
				decimal InUnitsExact(Unit u);

				void SetWithUnits(Unit u, decimal value);

				const Unit &getBestUnit() const;
				virtual std::string ToString();
				static FileSize Parse(const std::string &s);

				/// <summary>
				/// The size in bytes
				/// </summary>
				const unsigned long long &getBytes() const;
				void setBytes(const unsigned long long &value);

				/// <summary>
				/// The size in kilobytes (rounded)
				/// </summary>
				const unsigned long long &getKB() const;
				void setKB(const unsigned long long &value);

				/// <summary>
				/// The size in kilobytes (exact)
				/// </summary>
				const decimal &getKBExact() const;
				void setKBExact(const decimal &value);

				/// <summary>
				/// The size in megabytes (rounded)
				/// </summary>
				const unsigned long long &getMB() const;
				void setMB(const unsigned long long &value);

				/// <summary>
				/// The size in megabytes (exact)
				/// </summary>
				const decimal &getMBExact() const;
				void setMBExact(const decimal &value);

				/// <summary>
				/// Returns the size in gigabytes (rounded)
				/// </summary>
				const unsigned long long &getGB() const;
				void setGB(const unsigned long long &value);

				/// <summary>
				/// The size in gigabytes (exact)
				/// </summary>
				const decimal &getGBExact() const;
				void setGBExact(const decimal &value);

				FileSize operator + (FileSize b);
				FileSize operator - (FileSize b);
				decimal operator / (FileSize b);

				FileSize operator / (decimal b);

				FileSize operator *(FileSize b);
				FileSize operator *(decimal b);

				bool operator < (FileSize b);

				bool operator > (FileSize b);

				bool operator == (FileSize b);

				bool operator != (FileSize b);

				bool operator <= (FileSize b);

				bool operator >= (FileSize b);

				virtual int GetHashCode();

				virtual bool Equals(object *obj);

				FileSize(unsigned long long numBytes);

				FileSize(long long numBytes);

				FileSize(Unit u, decimal value);
			};

			class FileSizeConverter : public TypeConverter
			{
			public:
				virtual bool CanConvertFrom(ITypeDescriptorContext *context, Type *sourceType);

				virtual object *ConvertFrom(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value);
			};
		}
	}
}
