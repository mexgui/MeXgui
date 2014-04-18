#include "FileSize.h"




//using namespace System::Collections::Generic;





//using namespace System::Text;
namespace MeXgui
{
	namespace core
	{
		namespace util
		{

const FileSize FileSize::Empty = FileSize(0);
const FileSize FileSize::MinNonZero = FileSize(1);

			MeXgui::core::util::FileSize FileSize::Of(const QString &filename)
			{
				FileInfo *fi = new FileInfo(filename);
				return FileSize(fi->Length);
			}

			Nullable<FileSize> FileSize::Of2(const QString &filename)
			{
				if (filename.empty() || !File::Exists(filename))
					return 0;

				FileInfo *fi = new FileInfo(filename);
				if (fi->Length <= 0)
					return 0;

				return FileSize(fi->Length);
			}

const QString FileSize::UnitSuffixes[4] = {"bytes", "KB", "MB", "GB"};

			quint64 FileSize::divideAndRound(quint64 divisor)
			{
				quint64 divided = sizeInBytes / divisor;
				if (sizeInBytes % divisor > (divisor / 2))
					divided++;
				return divided;
			}

			void FileSize::setExact(quint64 divisor, decimal value)
			{
				decimal result = value * (static_cast<decimal>(divisor));
				sizeInBytes = static_cast<quint64>(Math::Round(result));
			}

			quint64 FileSize::divisor(Unit u)
			{
				quint64 divisor = 1;
				for (unsigned short i = 0; i < static_cast<unsigned short>(u); i++)
					divisor *= 1024;
				return divisor;
			}

			quint64 FileSize::InUnits(Unit u)
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

			const MeXgui::core::util::Unit &FileSize::getBestUnit() const
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

			QString FileSize::ToString()
			{
				Unit u = getBestUnit();
				decimal d = InUnitsExact(u);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return (Math::Round(d, 2))->ToString("0.00") + " " + UnitSuffixes[static_cast<unsigned short>(u)];
			}

			MeXgui::core::util::FileSize FileSize::Parse(const QString &s)
			{
//ORIGINAL LINE: string[] parts = s.Split(' ');
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
				QString *parts = s.Split(' ');
				return FileSize(static_cast<Unit>(Array->find(UnitSuffixes, parts[1])), decimal::Parse(parts[0]));

			}

			const quint64 &FileSize::getBytes() const
			{
				return sizeInBytes;
			}

			void FileSize::setBytes(const quint64 &value)
			{
				sizeInBytes = value;
			}

			const quint64 &FileSize::getKB() const
			{
				return divideAndRound(1024);
			}

			void FileSize::setKB(const quint64 &value)
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

			const quint64 &FileSize::getMB() const
			{
				return divideAndRound(1024*1024);
			}

			void FileSize::setMB(const quint64 &value)
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

			const quint64 &FileSize::getGB() const
			{
				return divideAndRound(1024 * 1024 * 1024);
			}

			void FileSize::setGB(const quint64 &value)
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
					result.sizeInBytes = static_cast<quint64>(Math::Round(*this * static_cast<decimal>(b.sizeInBytes)));
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

			FileSize::FileSize(quint64 numBytes)
			{
				sizeInBytes = numBytes;
			}

			FileSize::FileSize(qint64 numBytes)
			{
				if (numBytes > 0)
					sizeInBytes = static_cast<quint64>(numBytes);
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
				if (sourceType == QString::typeid)
					return true;
				return TypeConverter::CanConvertFrom(context, sourceType);
			}

			object *FileSizeConverter::ConvertFrom(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value)
			{
				if (dynamic_cast<QString>(value) != 0)
					return FileSize::Parse(static_cast<QString>(value));
				return TypeConverter::ConvertFrom(context, culture, value);
			}
		}
	}
}
