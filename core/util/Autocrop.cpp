#include "Autocrop.h"




//using namespace System::Collections::Generic;





//using namespace System::Text;
namespace MeXgui
{
	namespace core
	{
		namespace util
		{

			bool Autocrop::autocrop(CropValues *&cropValues, IVideoReader *reader, bool signalAR, mod16Method cropMethod, modValue mValue)
			{
				cropValues = Autocrop::autocrop(reader);

				if (signalAR)
				{
					if (cropMethod == overcrop)
						ScriptServer::overcrop(cropValues, mValue);
					else if (cropMethod == mod4Horizontal)
						ScriptServer::cropMod4Horizontal(cropValues);
					else if (cropMethod == undercrop)
						ScriptServer::undercrop(cropValues, mValue);
				}

				if (cropValues->left < 0)
					return false;
				else
					return true;
			}

			MeXgui::CropValues *Autocrop::autocrop(IVideoReader *reader)
			{
				// start at 10% of the video, then advance by 6,66% and analyze 11 frames in total
				int pos = reader->getFrameCount() / 10;
				int step = reader->getFrameCount() / 15;
				CropValues cropValues[11];
				for (int i = 0; i < 11; i++)
				{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (BitQMap b = reader.ReadFrameBitQMap(pos))
					BitQMap *b = reader->ReadFrameBitQMap(pos);
					try
					{
						cropValues[i] = getAutoCropValues(b);
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (b != 0)
							b.Dispose();
					}
					pos += step;
				}
				bool error = false;
				CropValues *final = getFinalAutocropValues(cropValues);
				if (!error)
				{
					return final;
				}
				else
				{
					final->left = -1;
					final->right = -1;
					final->top = -1;
					final->bottom = -1;
					return final;
				}
			}

			MeXgui::CropValues *Autocrop::getFinalAutocropValues(CropValues values[])
			{
				CropValues *retval = values[0]->Clone();
				QMap<int, int> topValues = QMap<int, int>();
				QMap<int, int> leftValues = QMap<int, int>();
				QMap<int, int> rightValues = QMap<int, int>();
				QMap<int, int> bottomValues = QMap<int, int>();

				// group crop values
				for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
				{
					if (leftValues.find(values[i]->left) != leftValues.end())
						leftValues[values[i]->left]++;
					else
						leftValues.insert(make_pair(values[i]->left, 1));
					if (topValues.find(values[i]->top) != topValues.end())
						topValues[values[i]->top]++;
					else
						topValues.insert(make_pair(values[i]->top, 1));
					if (rightValues.find(values[i]->right) != rightValues.end())
						rightValues[values[i]->right]++;
					else
						rightValues.insert(make_pair(values[i]->right, 1));
					if (bottomValues.find(values[i]->bottom) != bottomValues.end())
						bottomValues[values[i]->bottom]++;
					else
						bottomValues.insert(make_pair(values[i]->bottom, 1));

					// set min values found
					if (values[i]->left < retval->left)
						retval->left = values[i]->left;
					if (values[i]->top < retval->top)
						retval->top = values[i]->top;
					if (values[i]->right < retval->right)
						retval->right = values[i]->right;
					if (values[i]->bottom < retval->bottom)
						retval->bottom = values[i]->bottom;
				}

				// get "best match" values
				for (QMap<int, int>::const_iterator kvp = leftValues.begin(); kvp != leftValues.end(); ++kvp)
				{
					if (kvp->second > sizeof(values) / sizeof(values[0]) / 2) // we have more than 50% matching values, use value found
					{
						retval->left = kvp->first;
						break;
					}
				}
				for (QMap<int, int>::const_iterator kvp = topValues.begin(); kvp != topValues.end(); ++kvp)
				{
					if (kvp->second > sizeof(values) / sizeof(values[0]) / 2) // we have more than 50% matching values, use value found
					{
						retval->top = kvp->first;
						break;
					}
				}
				for (QMap<int, int>::const_iterator kvp = rightValues.begin(); kvp != rightValues.end(); ++kvp)
				{
					if (kvp->second > sizeof(values) / sizeof(values[0]) / 2) // we have more than 50% matching values, use value found
					{
						retval->right = kvp->first;
						break;
					}
				}
				for (QMap<int, int>::const_iterator kvp = bottomValues.begin(); kvp != bottomValues.end(); ++kvp)
				{
					if (kvp->second > sizeof(values) / sizeof(values[0]) / 2) // we have more than 50% matching values, use value found
					{
						retval->bottom = kvp->first;
						break;
					}
				}

				return retval;
			}

			bool Autocrop::isBadPixel(int pixel)
			{
				int comp = 12632256;
				int res = pixel & comp;
				return (res != 0);
			}

			MeXgui::CropValues *Autocrop::getAutoCropValues(BitQMap *b)
			{
				// When locking the pixels into memory, they are currently being converted from 24bpp to 32bpp. This incurs a small (5%) speed penalty,
				// but means that pixel management is easier, because each pixel is a 4-byte int.
				BitQMapData *image = b->LockBits(new Rectangle(0, 0, b->Width, b->Height), ImageLockMode::ReadOnly, PixelFormat::Format32bppArgb);
				int* pointer = static_cast<int>(image->Scan0->ToPointer());
				int* lineBegin, pixel;
				int stride = image->Stride / 4;
				CropValues *retval = new CropValues();
				bool lineFound = false;
				int badPixelThreshold = 50;
				int widthBadPixelThreshold = b->Width / badPixelThreshold;
				int heightBadPixelThreshold = b->Height / badPixelThreshold;
				int nbBadPixels = 0;

				lineBegin = pointer;
				for (int i = 0; i < b->Width; i++)
				{
					pixel = lineBegin;
					for (int j = 0; j < b->Height; j++)
					{
						if (isBadPixel(*pixel))
							nbBadPixels++;
						if (nbBadPixels > heightBadPixelThreshold)
						{
							retval->left = i;
							if (retval->left < 0)
								retval->left = 0;
							if (retval->left % 2 != 0)
								retval->left++;
							lineFound = true;
							break;
						}
						pixel += stride;
					}
					nbBadPixels = 0;
					if (lineFound)
						break;
					lineBegin += 1; // 4-byte Argb
				}
				nbBadPixels = 0;
				lineFound = false;
				lineBegin = pointer;
				for (int i = 0; i < b->Height; i++)
				{
					pixel = lineBegin;
					for (int j = 0; j < b->Width; j++)
					{
						if (isBadPixel(*pixel))
							nbBadPixels++;
						if (nbBadPixels > widthBadPixelThreshold)
						{
							retval->top = i;
							if (retval->top < 0)
								retval->top = 0;
							if (retval->top % 2 != 0)
								retval->top++;
							lineFound = true;
							break;
						}
						pixel += 1; // 4-byte Argb
					}
					nbBadPixels = 0;
					if (lineFound)
						break;
					lineBegin += stride;
				}
				nbBadPixels = 0;
				lineFound = false;
				lineBegin = pointer + b->Width - 1;
				for (int i = b->Width - 1; i >= 0; i--)
				{
					pixel = lineBegin;
					for (int j = 0; j < b->Height; j++)
					{
						if (isBadPixel(*pixel))
							nbBadPixels++;
						if (nbBadPixels > heightBadPixelThreshold)
						{
							retval->right = b->Width - i - 1;
							if (retval->right < 0)
								retval->right = 0;
							if (retval->right % 2 != 0)
								retval->right++;
							lineFound = true;
							break;
						}
						pixel += stride;
					}
					nbBadPixels = 0;
					if (lineFound)
						break;
					lineBegin -= 1; // Backwards across 4-byte Argb
				}
				nbBadPixels = 0;
				lineFound = false;
				lineBegin = pointer + stride * (b->Height - 1);
				for (int i = b->Height - 1; i >= 0; i--)
				{
					pixel = lineBegin;
					for (int j = 0; j < b->Width; j++)
					{
						if (isBadPixel(*pixel))
							nbBadPixels++;
						if (nbBadPixels > widthBadPixelThreshold)
						{
							retval->bottom = b->Height - i - 1;
							if (retval->bottom < 0)
								retval->bottom = 0;
							if (retval->bottom % 2 != 0)
								retval->bottom++;
							lineFound = true;
							break;
						}
						pixel += 1; // 4-byte Argb
					}
					nbBadPixels = 0;
					if (lineFound)
						break;
					lineBegin -= stride;
				}
				b->UnlockBits(image);
				return retval;
			}
		}
	}
}
