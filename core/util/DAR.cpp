#include "DAR.h"




//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;

//using namespace System::Text;
namespace MeXgui
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

			Dar::Dar(quint64 x, quint64 y)
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

			Dar::Dar(Nullable<decimal> dar, quint64 width, quint64 height)
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

			Dar::Dar(int x, int y, quint64 width, quint64 height)
			{
				ar = -1;
				if (x > 0 && y > 0)
				{
					ar = static_cast<decimal>(x) / static_cast<decimal>(y);
					this->x = static_cast<quint64>(x);
					this->y = static_cast<quint64>(y);
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

			const quint64 &Dar::getX() const
			{
				return x;
			}

			void Dar::setX(const quint64 &value)
			{
				x = value;
			}

			const quint64 &Dar::getY() const
			{
				return y;
			}

			void Dar::setY(const quint64 &value)
			{
				y = value;
			}

			QString Dar::ToString()
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

			MeXgui::core::util::Sar Dar::ToSar(int hres, int vres)
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
				if (sourceType == QString::typeid)
					return true;
				return false;
			}

			object *DarConverter::ConvertFrom(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value)
			{
				if (dynamic_cast<QString>(value) != 0)
					return Dar(decimal::Parse(static_cast<QString>(value)));

				throw std::exception();
			}

			object *DarConverter::ConvertTo(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value, Type *destinationType)
			{
				if (destinationType == QString::typeid)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return value->ToString();

				throw std::exception();
			}

			Sar::Sar(quint64 x, quint64 y)
			{
				ar = static_cast<decimal>(x) / static_cast<decimal>(y);
			}

			Sar::Sar(decimal sar)
			{
				ar = sar;
			}

			const quint64 &Sar::getX() const
			{
				quint64 x, y;
				RatioUtils::approximate(ar, x, y);
				return x;
			}

			const quint64 &Sar::getY() const
			{
				quint64 x, y;
				RatioUtils::approximate(ar, x, y);
				return y;
			}

			MeXgui::core::util::Dar Sar::ToDar(int hres, int vres)
			{
				return Dar(ar * static_cast<decimal>(hres) / static_cast<decimal>(vres));
			}

			void RatioUtils::reduce(quint64 &x, quint64 &y)
			{
				quint64 g = gcd(x, y);
				x /= g;
				y /= g;
			}

			quint64 RatioUtils::gcd(quint64 x, quint64 y)
			{
				while (y != 0)
				{
					quint64 t = y;
					y = x % y;
					x = t;
				}
				return x;
			}

			void RatioUtils::approximate(decimal val, quint64 &x, quint64 &y)
			{
				approximate(val, x, y, 1.0E-5);
			}

			void RatioUtils::approximate(decimal val, quint64 &x, quint64 &y, double precision)
			{
				// Fraction.Test();
				Fraction f = Fraction::toFract(static_cast<double>(val), precision);

				x = f.num;
				y = f.denom;

				reduce(x, y);
				// [i_a] ^^^ initial tests with the new algo show this is 
				// rather unnecessary, but we'll keep it anyway, just in case.
			}

			Fraction::Fraction(quint64 n, quint64 d)
			{
				num = n;
				denom = d;
			}

			MeXgui::core::util::Fraction Fraction::toFract(decimal val)
			{
				return Fraction::toFract(static_cast<double>(val), 1.0E-13); // 1.0E-28 = decimal.epsilon
			}

			MeXgui::core::util::Fraction Fraction::toFract(float val)
			{
				return Fraction::toFract(static_cast<double>(val), 1.0E-13); // float.Epsilon
			}

			MeXgui::core::util::Fraction Fraction::toFract(double val)
			{
				return Fraction::toFract(val, 1.0E-13); // double.Epsilon
			}

			MeXgui::core::util::Fraction Fraction::toFract(double val, double Precision)
			{
				// find nearest fraction
				quint64 intPart = static_cast<quint64>(val);
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
						if ((x1 + 1) * low.denom + high.denom >= static_cast<double>(qint64::MaxValue))
						{
							break;
						}

						quint64 n = static_cast<quint64>(x1); // lower bound for m
						//int m = n + 1;    // upper bound for m

						//     a + x*c
						//     ------- = m
						//     b + x*d
						quint64 h_num = n * low.num + high.num;
						quint64 h_denom = n * low.denom + high.denom;

						//ulong l_num = m * low.num + high.num;
						//ulong l_denom = m * low.denom + high.denom;
						quint64 l_num = h_num + low.num;
						quint64 l_denom = h_denom + low.denom;

						low.num = l_num;
						low.denom = l_denom;
						high.num = h_num;
						high.denom = h_denom;
					}
					else
					{
						//double x2 = testLow / testHigh;
						// safety checks: are we going to be out of integer bounds?
						if (low.denom + (x2 + 1) * high.denom >= static_cast<double>(quint64::MaxValue))
						{
							break;
						}

						quint64 n = static_cast<quint64>(x2); // lower bound for m
						//ulong m = n + 1;    // upper bound for m

						//     a + x*c
						//     ------- = m
						//     b + x*d
						quint64 l_num = low.num + n * high.num;
						quint64 l_denom = low.denom + n * high.denom;

						//ulong h_num = low.num + m * high.num;
						//ulong h_denom = low.denom + m * high.denom;
						quint64 h_num = l_num + high.num;
						quint64 h_denom = l_denom + high.denom;

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
