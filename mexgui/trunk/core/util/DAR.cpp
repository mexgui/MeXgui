#include "DAR.h"

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
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

const Dar Dar::ITU16x9PAL = Dar(640, 351);
const Dar Dar::ITU4x3PAL = Dar(160, 117);
const Dar Dar::ITU16x9NTSC = Dar(8640, 4739);
const Dar Dar::ITU4x3NTSC = Dar(6480, 4739);
const Dar Dar::STATIC4x3 = Dar(4, 3);
const Dar Dar::STATIC16x9 = Dar(16, 9);
const Dar Dar::A1x1 = Dar(1, 1);

			Dar::Dar(unsigned long long x, unsigned long long y)
			{
				ar = static_cast<decimal>(x) / static_cast<decimal>(y);
				this->x = x;
				this->y = y;
				RatioUtils::reduce(this->x, this->y);
			}

			Dar::Dar(decimal dar)
			{
				ar = dar;
				RatioUtils::approximate(ar, x, y);
			}

			Dar::Dar(Nullable<decimal> dar, unsigned long long width, unsigned long long height)
			{
				ar = -1;
				if (dar.HasValue)
					ar = dar.Value;
				else
					ar = static_cast<decimal>(width) / static_cast<decimal>(height);
				this->x = width;
				this->y = height;
				RatioUtils::reduce(this->x, this->y);
			}

			Dar::Dar(int x, int y, unsigned long long width, unsigned long long height)
			{
				ar = -1;
				if (x > 0 && y > 0)
				{
					ar = static_cast<decimal>(x) / static_cast<decimal>(y);
					this->x = static_cast<unsigned long long>(x);
					this->y = static_cast<unsigned long long>(y);
				}
				else
				{
					ar = static_cast<decimal>(width) / static_cast<decimal>(height);
					this->x = width;
					this->y = height;
				}
				RatioUtils::reduce(this->x, this->y);
			}

			const decimal &Dar::getAR() const
			{
				return ar;
			}

			void Dar::setAR(const decimal &value)
			{
				ar = value;
			}

			const unsigned long long &Dar::getX() const
			{
				return x;
			}

			void Dar::setX(const unsigned long long &value)
			{
				x = value;
			}

			const unsigned long long &Dar::getY() const
			{
				return y;
			}

			void Dar::setY(const unsigned long long &value)
			{
				y = value;
			}

			std::string Dar::ToString()
			{
				System::Globalization::CultureInfo *culture = new System::Globalization::CultureInfo("en-us");

				StringBuilder *sb = new StringBuilder();
				sb->Append(x + ":" + y + " (");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				sb->Append(ar.ToString("0.000)", culture));
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return sb->ToString();
			}

			bool Dar::Equals(object *obj)
			{
				if (!(dynamic_cast<Dar>(obj) != 0))
					return false;

				return (getX() == (static_cast<Dar>(obj)).getX() && getY() == (static_cast<Dar>(obj)).getY());
			}

			int Dar::GetHashCode()
			{
				return 0;
			}

			MeGUI::core::util::Sar Dar::ToSar(int hres, int vres)
			{
				// sarX
				// ----   must be the amount the video needs to be stretched horizontally.
				// sarY
				//
				//    horizontalResolution
				// --------------------------  is the ratio of the pixels. This must be stretched to equal realAspectRatio
				//  scriptVerticalResolution
				//
				// To work out the stretching amount, we then divide realAspectRatio by the ratio of the pixels:
				// sarX      parX        horizontalResolution        realAspectRatio * scriptVerticalResolution
				// ---- =    ---- /   -------------------------- =  --------------------------------------------   
				// sarY      parY     scriptVerticalResolution               horizontalResolution
				//
				// rounding value is mandatory here because some encoders (x264, xvid...) clamp sarX & sarY
				decimal ratio = ar * static_cast<decimal>(vres) / static_cast<decimal>(hres);
				return Sar(ratio);
			}

			bool DarConverter::CanConvertFrom(ITypeDescriptorContext *context, Type *sourceType)
			{
				if (sourceType == std::string::typeid)
					return true;
				return false;
			}

			object *DarConverter::ConvertFrom(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value)
			{
				if (dynamic_cast<std::string>(value) != 0)
					return Dar(decimal::Parse(static_cast<std::string>(value)));

				throw std::exception();
			}

			object *DarConverter::ConvertTo(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value, Type *destinationType)
			{
				if (destinationType == std::string::typeid)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return value->ToString();

				throw std::exception();
			}

			Sar::Sar(unsigned long long x, unsigned long long y)
			{
				ar = static_cast<decimal>(x) / static_cast<decimal>(y);
			}

			Sar::Sar(decimal sar)
			{
				ar = sar;
			}

			const unsigned long long &Sar::getX() const
			{
				unsigned long long x, y;
				RatioUtils::approximate(ar, x, y);
				return x;
			}

			const unsigned long long &Sar::getY() const
			{
				unsigned long long x, y;
				RatioUtils::approximate(ar, x, y);
				return y;
			}

			MeGUI::core::util::Dar Sar::ToDar(int hres, int vres)
			{
				return Dar(ar * static_cast<decimal>(hres) / static_cast<decimal>(vres));
			}

			void RatioUtils::reduce(unsigned long long &x, unsigned long long &y)
			{
				unsigned long long g = gcd(x, y);
				x /= g;
				y /= g;
			}

			unsigned long long RatioUtils::gcd(unsigned long long x, unsigned long long y)
			{
				while (y != 0)
				{
					unsigned long long t = y;
					y = x % y;
					x = t;
				}
				return x;
			}

			void RatioUtils::approximate(decimal val, unsigned long long &x, unsigned long long &y)
			{
				approximate(val, x, y, 1.0E-5);
			}

			void RatioUtils::approximate(decimal val, unsigned long long &x, unsigned long long &y, double precision)
			{
				// Fraction.Test();
				Fraction f = Fraction::toFract(static_cast<double>(val), precision);

				x = f.num;
				y = f.denom;

				reduce(x, y);
				// [i_a] ^^^ initial tests with the new algo show this is 
				// rather unnecessary, but we'll keep it anyway, just in case.
			}

			Fraction::Fraction(unsigned long long n, unsigned long long d)
			{
				num = n;
				denom = d;
			}

			MeGUI::core::util::Fraction Fraction::toFract(decimal val)
			{
				return Fraction::toFract(static_cast<double>(val), 1.0E-13); // 1.0E-28 = decimal.epsilon
			}

			MeGUI::core::util::Fraction Fraction::toFract(float val)
			{
				return Fraction::toFract(static_cast<double>(val), 1.0E-13); // float.Epsilon
			}

			MeGUI::core::util::Fraction Fraction::toFract(double val)
			{
				return Fraction::toFract(val, 1.0E-13); // double.Epsilon
			}

			MeGUI::core::util::Fraction Fraction::toFract(double val, double Precision)
			{
				// find nearest fraction
				unsigned long long intPart = static_cast<unsigned long long>(val);
				val -= static_cast<double>(intPart);

				Fraction low = Fraction(0, 1); // "A" = 0/1 (a/b)
				Fraction high = Fraction(1, 1); // "B" = 1/1 (c/d)

				for (; ;)
				{
					assert(low.getVal() <= val);
					assert(high.getVal() >= val);

					//         b*m - a
					//     x = -------
					//         c - d*m
					double testLow = low.denom * val - low.num;
					double testHigh = high.num - high.denom * val;
					// test for match:
					// 
					// m - a/b < precision
					//
					// ==>
					//
					// b * m - a < b * precision
					//
					// which is happening here: check both the current A and B fractions.
					//if (testHigh < high.denom * Precision)
					if (testHigh < Precision) // [i_a] speed improvement; this is even better for irrational 'val'
					{
						break; // high is answer
					}
					//if (testLow < low.denom * Precision)
					if (testLow < Precision) // [i_a] speed improvement; this is even better for irrational 'val'
					{
						// low is answer
						high = low;
						break;
					}

					double x1 = testHigh / testLow;
					double x2 = testLow / testHigh;

					// always choose the path where we find the largest change in direction:
					if (x1 > x2)
					{
						//double x1 = testHigh / testLow;
						// safety checks: are we going to be out of integer bounds?
						if ((x1 + 1) * low.denom + high.denom >= static_cast<double>(long long::MaxValue))
						{
							break;
						}

						unsigned long long n = static_cast<unsigned long long>(x1); // lower bound for m
						//int m = n + 1;    // upper bound for m

						//     a + x*c
						//     ------- = m
						//     b + x*d
						unsigned long long h_num = n * low.num + high.num;
						unsigned long long h_denom = n * low.denom + high.denom;

						//ulong l_num = m * low.num + high.num;
						//ulong l_denom = m * low.denom + high.denom;
						unsigned long long l_num = h_num + low.num;
						unsigned long long l_denom = h_denom + low.denom;

						low.num = l_num;
						low.denom = l_denom;
						high.num = h_num;
						high.denom = h_denom;
					}
					else
					{
						//double x2 = testLow / testHigh;
						// safety checks: are we going to be out of integer bounds?
						if (low.denom + (x2 + 1) * high.denom >= static_cast<double>(unsigned long long::MaxValue))
						{
							break;
						}

						unsigned long long n = static_cast<unsigned long long>(x2); // lower bound for m
						//ulong m = n + 1;    // upper bound for m

						//     a + x*c
						//     ------- = m
						//     b + x*d
						unsigned long long l_num = low.num + n * high.num;
						unsigned long long l_denom = low.denom + n * high.denom;

						//ulong h_num = low.num + m * high.num;
						//ulong h_denom = low.denom + m * high.denom;
						unsigned long long h_num = l_num + high.num;
						unsigned long long h_denom = l_denom + high.denom;

						high.num = h_num;
						high.denom = h_denom;
						low.num = l_num;
						low.denom = l_denom;
					}
					assert(low.getVal() <= val);
					assert(high.getVal() >= val);
				}

				high.num += high.denom * intPart;
				return high;
			}

			void Fraction::Test()
			{
				Fraction ret;
				double vut;

				vut = 0.1;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 0.99999997;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = (0x40000000 - 1.0) / (0x40000000 + 1.0);
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 1.0 / 3.0;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 1.0 / (0x40000000 - 1.0);
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 320.0 / 240.0;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 6.0 / 7.0;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 320.0 / 241.0;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 720.0 / 577.0;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 2971.0 / 3511.0;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 3041.0 / 7639.0;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = 1.0 / sqrt(2);
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
				vut = M_PI;
				ret = Fraction::toFract(vut);
				assert(abs(vut - ret.getVal()) < 1E-9);
			}

			const double &Fraction::getVal() const
			{
				return static_cast<double>(num) / denom;
			}
		}
	}
}
