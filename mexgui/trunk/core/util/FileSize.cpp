#include "FileSize.h"

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

const FileSize FileSize::Empty = FileSize(0);
const FileSize FileSize::MinNonZero = FileSize(1);

			MeGUI::core::util::FileSize FileSize::Of(const std::string &filename)
			{
				FileInfo *fi = new FileInfo(filename);
				return FileSize(fi->Length);
			}

			Nullable<FileSize> FileSize::Of2(const std::string &filename)
			{
				if (filename.empty() || !File::Exists(filename))
					return 0;

				FileInfo *fi = new FileInfo(filename);
				if (fi->Length <= 0)
					return 0;

				return FileSize(fi->Length);
			}

const std::string FileSize::UnitSuffixes[4] = {"bytes", "KB", "MB", "GB"};

			unsigned long long FileSize::divideAndRound(unsigned long long divisor)
			{
				unsigned long long divided = sizeInBytes / divisor;
				if (sizeInBytes % divisor > (divisor / 2))
					divided++;
				return divided;
			}

			void FileSize::setExact(unsigned long long divisor, decimal value)
			{
				decimal result = value * (static_cast<decimal>(divisor));
				sizeInBytes = static_cast<unsigned long long>(Math::Round(result));
			}

			unsigned long long FileSize::divisor(Unit u)
			{
				unsigned long long divisor = 1;
				for (unsigned short i = 0; i < static_cast<unsigned short>(u); i++)
					divisor *= 1024;
				return divisor;
			}

			unsigned long long FileSize::InUnits(Unit u)
			{
				return divideAndRound(divisor(u));
			}

			decimal FileSize::InUnitsExact(Unit u)
			{
				return (static_cast<decimal>(sizeInBytes)) / (static_cast<decimal>(divisor(u)));
			}

			void FileSize::SetWithUnits(Unit u, decimal value)
			{
				setExact(divisor(u), value);
			}

			const MeGUI::core::util::Unit &FileSize::getBestUnit() const
			{
				Unit u = B;
				while (u < getGB())
				{
					if (InUnitsExact(u) < 1000)
						break;
					u++;
				}
				return u;
			}

			std::string FileSize::ToString()
			{
				Unit u = getBestUnit();
				decimal d = InUnitsExact(u);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return (Math::Round(d, 2))->ToString("0.00") + " " + UnitSuffixes[static_cast<unsigned short>(u)];
			}

			MeGUI::core::util::FileSize FileSize::Parse(const std::string &s)
			{
//ORIGINAL LINE: string[] parts = s.Split(' ');
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
				std::string *parts = s.Split(' ');
				return FileSize(static_cast<Unit>(Array->find(UnitSuffixes, parts[1])), decimal::Parse(parts[0]));

			}

			const unsigned long long &FileSize::getBytes() const
			{
				return sizeInBytes;
			}

			void FileSize::setBytes(const unsigned long long &value)
			{
				sizeInBytes = value;
			}

			const unsigned long long &FileSize::getKB() const
			{
				return divideAndRound(1024);
			}

			void FileSize::setKB(const unsigned long long &value)
			{
//				checked
					sizeInBytes = value * 1024;
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'checked' block
			}

			const decimal &FileSize::getKBExact() const
			{
				return (static_cast<decimal>(sizeInBytes)) / 1024;
			}

			void FileSize::setKBExact(const decimal &value)
			{
				setExact(1024, value);
			}

			const unsigned long long &FileSize::getMB() const
			{
				return divideAndRound(1024*1024);
			}

			void FileSize::setMB(const unsigned long long &value)
			{
//				checked
					sizeInBytes = value * 1024 * 1024;
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'checked' block
			}

			const decimal &FileSize::getMBExact() const
			{
				return (static_cast<decimal>(sizeInBytes)) / (1024 * 1024);
			}

			void FileSize::setMBExact(const decimal &value)
			{
				setExact(1024 * 1024, value);
			}

			const unsigned long long &FileSize::getGB() const
			{
				return divideAndRound(1024 * 1024 * 1024);
			}

			void FileSize::setGB(const unsigned long long &value)
			{
//				checked
					sizeInBytes = value * 1024 * 1024 * 1024;
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'checked' block
			}

			const decimal &FileSize::getGBExact() const
			{
				return (static_cast<decimal>(sizeInBytes)) / (1024 * 1024 * 1024);
			}

			void FileSize::setGBExact(const decimal &value)
			{
				setExact(1024 * 1024 * 1024, value);
			}

			FileSize FileSize::operator + (FileSize b)
			{
				FileSize result;
//				checked
					result.sizeInBytes = this->sizeInBytes + b.sizeInBytes;
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'checked' block
				return result;
			}

			FileSize FileSize::operator - (FileSize b)
			{
				FileSize result;
//				checked
					result.sizeInBytes = this->sizeInBytes - b.sizeInBytes;
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'checked' block
				return result;
			}

			decimal FileSize::operator / (FileSize b)
			{
				return (static_cast<decimal>(this->sizeInBytes)) / (static_cast<decimal>(b.sizeInBytes));
			}

			FileSize FileSize::operator / (decimal b)
			{
				return (*this * (1.0 / b));
			}

			FileSize FileSize::operator *(FileSize b)
			{
				FileSize result;
//				checked
					result.sizeInBytes = static_cast<unsigned long long>(Math::Round(*this * static_cast<decimal>(b.sizeInBytes)));
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'checked' block
				return result;
			}

			FileSize FileSize::operator *(decimal b)
			{
				return b * *this;
			}

			bool FileSize::operator < (FileSize b)
			{
				return (this->sizeInBytes < b.sizeInBytes);
			}

			bool FileSize::operator > (FileSize b)
			{
				return b < *this;
			}

			bool FileSize::operator == (FileSize b)
			{
				return (this->sizeInBytes == b.sizeInBytes);
			}

			bool FileSize::operator != (FileSize b)
			{
				return !(*this == b);
			}

			bool FileSize::operator <= (FileSize b)
			{
				return (this->sizeInBytes <= b.sizeInBytes);
			}

			bool FileSize::operator >= (FileSize b)
			{
				return (b <= *this);
			}

			int FileSize::GetHashCode()
			{
				return sizeInBytes.GetHashCode();
			}

			bool FileSize::Equals(object *obj)
			{
				return (dynamic_cast<FileSize>(obj) != 0 && (static_cast<FileSize>(obj)).sizeInBytes == sizeInBytes);
			}

			FileSize::FileSize(unsigned long long numBytes)
			{
				sizeInBytes = numBytes;
			}

			FileSize::FileSize(long long numBytes)
			{
				if (numBytes > 0)
					sizeInBytes = static_cast<unsigned long long>(numBytes);
				else
					sizeInBytes = 0;
			}

			FileSize::FileSize(Unit u, decimal value)
			{
				sizeInBytes = 0; // Dummy
				SetWithUnits(u, value);
			}

			bool FileSizeConverter::CanConvertFrom(ITypeDescriptorContext *context, Type *sourceType)
			{
				if (sourceType == std::string::typeid)
					return true;
				return TypeConverter::CanConvertFrom(context, sourceType);
			}

			object *FileSizeConverter::ConvertFrom(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value)
			{
				if (dynamic_cast<std::string>(value) != 0)
					return FileSize::Parse(static_cast<std::string>(value));
				return TypeConverter::ConvertFrom(context, culture, value);
			}
		}
	}
}
