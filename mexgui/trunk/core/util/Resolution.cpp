#include "Resolution.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
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

			void Resolution::GetResolution(int sourceWidth, int sourceHeight, Dar inputDar, CropValues *&cropValues, bool cropEnabled, int mod, bool &resizeEnabled, bool upsizingAllowed, bool signalAR, bool suggestHeight, decimal acceptableAspectErrorPercent, x264Device *xTargetDevice, double fps, int &outputWidth, int &outputHeight, CropValues *&paddingValues, Nullable<Dar> &outputDar, LogItem *_log)
			{
				paddingValues = new CropValues();

				getResolution(sourceWidth, sourceHeight, inputDar, cropValues, cropEnabled, mod, resizeEnabled, upsizingAllowed, signalAR, suggestHeight, acceptableAspectErrorPercent, outputWidth, outputHeight, outputDar, _log);

				bool settingsChanged;
				if (isResolutionDeviceCompliant(xTargetDevice, outputWidth, outputHeight, settingsChanged, resizeEnabled, cropEnabled, _log) == true)
				{
					if (!cropEnabled)
						cropValues = new CropValues();
					return;
				}

				if (settingsChanged)
				{
					getResolution(sourceWidth, sourceHeight, inputDar, cropValues, cropEnabled, mod, resizeEnabled, upsizingAllowed, signalAR, suggestHeight, acceptableAspectErrorPercent, outputWidth, outputHeight, outputDar, _log);

					// check if the resolution is now compliant
					if (isResolutionDeviceCompliant(xTargetDevice, outputWidth, outputHeight, settingsChanged, resizeEnabled, cropEnabled, 0) == true)
					{
						if (!cropEnabled)
							cropValues = new CropValues();
						return;
					}
				}
				if (!cropEnabled)
					cropValues = new CropValues();

				// adjust horizontal resolution if width or height are too large
				int outputHeightIncludingPadding = 0;
				int outputWidthIncludingPadding = 0;
				if (xTargetDevice->getBluRay())
				{
					if (outputWidth >= 1920)
					{
						outputWidth = 1920;
						outputHeightIncludingPadding = 1080;
					}
					else if (outputWidth >= 1280)
					{
						outputWidth = 1280;
						outputHeightIncludingPadding = 720;
					}
					else
					{
						outputWidth = 720;
						if (fps == 25)
							outputHeightIncludingPadding = 576;
						else
							outputHeightIncludingPadding = 480;
					}
					outputWidthIncludingPadding = outputWidth;
					if (_log != 0)
						_log->LogEvent("Force resolution of " + outputWidth + "x" + outputHeightIncludingPadding + " as required for " + xTargetDevice->getName());
				}
				else if (xTargetDevice->getWidth() > 0 && outputWidth > xTargetDevice->getWidth())
				{
					outputWidth = xTargetDevice->getWidth();
					_log->LogEvent("Set resolution width to " + outputWidth + " as required for " + xTargetDevice->getName());
				}

				// adjust cropped vertical resolution
				getResolution(sourceWidth, sourceHeight, inputDar, cropValues, cropEnabled, mod, resizeEnabled, upsizingAllowed, signalAR, suggestHeight, acceptableAspectErrorPercent, outputWidth, outputHeight, outputDar, _log);
				while ((xTargetDevice->getHeight() > 0 && outputHeight > xTargetDevice->getHeight()) || (xTargetDevice->getBluRay() && outputHeight > outputHeightIncludingPadding))
				{
					outputWidth -= mod;
					getResolution(sourceWidth, sourceHeight, inputDar, cropValues, cropEnabled, mod, resizeEnabled, upsizingAllowed, signalAR, suggestHeight, acceptableAspectErrorPercent, outputWidth, outputHeight, outputDar, _log);
				}

				paddingValues->left = static_cast<int>(floor((outputWidthIncludingPadding - outputWidth) / 2.0));
				paddingValues->right = static_cast<int>(ceil((outputWidthIncludingPadding - outputWidth) / 2.0));
				paddingValues->bottom = static_cast<int>(floor((outputHeightIncludingPadding - outputHeight) / 2.0));
				paddingValues->top = static_cast<int>(ceil((outputHeightIncludingPadding - outputHeight) / 2.0));

				outputWidth = outputWidthIncludingPadding;
				outputHeight = outputHeightIncludingPadding;

				if (!cropEnabled)
					cropValues = new CropValues();
			}

			bool Resolution::isResolutionDeviceCompliant(x264Device *xTargetDevice, int outputWidth, int outputHeight, bool &settingsChanged, bool &resizeEnabled, bool &cropEnabled, LogItem *_log)
			{
				settingsChanged = false;
				if (xTargetDevice == 0)
					return true;
				if (!xTargetDevice->getBluRay() && xTargetDevice->getHeight() <= 0 && xTargetDevice->getWidth() <= 0)
					return true;

				bool bAdjustResolution = false;
				if (xTargetDevice->getWidth() > 0 && xTargetDevice->getWidth() < outputWidth)
				{
					// width must be lowered to be target conform
					bAdjustResolution = true;
					if (!resizeEnabled)
					{
						resizeEnabled = settingsChanged = true;
						if (_log != 0)
							_log->LogEvent("Enabling \"Resize\" as " + xTargetDevice->getName() + " does not support a resolution width of " + outputWidth + ". The maximum value is " + xTargetDevice->getWidth() + ".");
					}
				}
				else if (xTargetDevice->getHeight() > 0 && xTargetDevice->getHeight() < outputHeight)
				{
					// height must be lowered to be target conform
					bAdjustResolution = true;
					if (!resizeEnabled)
					{
						resizeEnabled = settingsChanged = true;
						if (_log != 0)
							_log->LogEvent("Enabling \"Resize\" as " + xTargetDevice->getName() + " does not support a resolution height of " + outputHeight + ". The maximum value is " + xTargetDevice->getHeight() + ".");
					}
				}
				else if (xTargetDevice->getBluRay())
				{
					std::string strResolution = outputWidth + "x" + outputHeight;
					if (!strResolution.Equals("1920x1080") && !strResolution.Equals("1440x1080") && !strResolution.Equals("1280x720") && !strResolution.Equals("720x576") && !strResolution.Equals("720x480"))
					{
						bAdjustResolution = settingsChanged = true;
						if (!resizeEnabled)
						{
							resizeEnabled = true;
							if (_log != 0)
								_log->LogEvent("Enabling \"Resize\" as " + xTargetDevice->getName() + " does not support a resolution of " + outputWidth + "x" + outputHeight + ". Supported are 1920x1080, 1440x1080, 1280x720, 720x576 and 720x480.");
						}
					}
				}

				if (bAdjustResolution && !cropEnabled)
				{
					if (_log != 0)
						_log->LogEvent("Enabling \"Crop\"");
					cropEnabled = settingsChanged = true;
				}

				if (bAdjustResolution)
					return false;
				return true;
			}

			void Resolution::getResolution(int sourceWidth, int sourceHeight, Dar inputDar, CropValues *cropValues, bool cropEnabled, int mod, bool resizeEnabled, bool upsizingAllowed, bool signalAR, bool suggestHeight, decimal acceptableAspectErrorPercent, int &outputWidth, int &outputHeight, Nullable<Dar> &outputDar, LogItem *_log)
			{
				outputDar = Nullable<Dar>();

				CropValues *cropping = new CropValues();
				if (cropEnabled)
					cropping = cropValues->Clone();

				// remove upsizing if not allowed
				if (!upsizingAllowed && sourceWidth - cropping->left - cropping->right < outputWidth)
				{
					outputWidth = sourceWidth - cropping->left - cropping->right;
					if (_log != 0)
						_log->LogEvent("Lowering output width resolution to " + outputWidth + " to avoid upsizing");
				}

				// correct hres if not mod compliant
				if (outputWidth % mod != 0)
				{
					int diff = outputWidth % mod;
					if (outputWidth - diff > 0)
						outputWidth -= diff;
					else
						outputWidth = mod;
				}

				if (suggestHeight)
				{
					int scriptVerticalResolution = Resolution::SuggestVerticalResolution(sourceHeight, sourceWidth, inputDar, cropping, outputWidth, signalAR, outputDar, mod, acceptableAspectErrorPercent);

					int iMaximum = 9999;
					if (!upsizingAllowed)
						iMaximum = sourceHeight - cropping->top - cropping->bottom;

					// Reduce horizontal resolution until a fit is found
					while (scriptVerticalResolution > iMaximum && outputWidth > mod)
					{
						outputWidth -= mod;
						scriptVerticalResolution = Resolution::SuggestVerticalResolution(sourceHeight, sourceWidth, inputDar, cropping, outputWidth, signalAR, outputDar, mod, acceptableAspectErrorPercent);
					}
					outputHeight = scriptVerticalResolution;
				}
				else if (!resizeEnabled)
					outputHeight = sourceHeight - cropping->top - cropping->bottom;
			}

			int Resolution::GetModValue(modValue modValue, mod16Method modMethod, bool signalAR)
			{
				int mod = 16;
				if (!signalAR || modMethod != nonMod16)
				{
					switch (modValue)
					{
						case mod8:
							mod = 8;
							break;
						case mod4:
							mod = 4;
							break;
						case mod2:
							mod = 2;
							break;
					}
				}
				else
					mod = 1;

				return mod;
			}

			int Resolution::SuggestVerticalResolution(double readerHeight, double readerWidth, Dar inputDAR, CropValues *cropping, int horizontalResolution, bool signalAR, Nullable<Dar> &dar, int mod, decimal acceptableAspectErrorPercent)
			{
				int scriptVerticalResolution;

				decimal fractionOfWidth = (static_cast<decimal>(readerWidth) - static_cast<decimal>(cropping->left) - static_cast<decimal>(cropping->right)) / static_cast<decimal>(readerWidth);
				decimal sourceHorizontalResolution = static_cast<decimal>(readerHeight) * inputDAR.getAR() * fractionOfWidth;
				decimal sourceVerticalResolution = static_cast<decimal>(readerHeight) - static_cast<decimal>(cropping->top) - static_cast<decimal>(cropping->bottom);
				decimal resizedVerticalResolution = static_cast<decimal>(horizontalResolution) / (sourceHorizontalResolution / sourceVerticalResolution);

				if (signalAR)
				{
					decimal inputWidthOnHeight = (static_cast<decimal>(readerWidth) - static_cast<decimal>(cropping->left) - static_cast<decimal>(cropping->right)) / (static_cast<decimal>(readerHeight) - static_cast<decimal>(cropping->top) - static_cast<decimal>(cropping->bottom));
					decimal realAspectRatio = getAspectRatio(inputDAR.getAR(), sourceHorizontalResolution / sourceVerticalResolution, acceptableAspectErrorPercent); // the aspect ratio of the video
					resizedVerticalResolution = static_cast<decimal>(horizontalResolution) / inputWidthOnHeight; // Scale vertical resolution appropriately
					scriptVerticalResolution = (static_cast<int>(Math::Round(resizedVerticalResolution / static_cast<decimal>(mod))) * mod);

					int parX = 0;
					int parY = 0;
					int iLimit = 101;
					decimal distance = 999999;
					if (acceptableAspectErrorPercent == 0)
						iLimit = 100001;
					for (int i = 1; i < iLimit; i++)
					{
						// We create a fraction with integers, and then convert back to a decimal, and see how big the rounding error is
						decimal fractionApproximation = static_cast<decimal>(Math::Round(realAspectRatio * (static_cast<decimal>(i)))) / static_cast<decimal>(i);
						decimal approximationDifference = abs(realAspectRatio - fractionApproximation);
						if (approximationDifference < distance)
						{
							distance = approximationDifference;
							parY = i;
							parX = static_cast<int>(Math::Round(realAspectRatio * (static_cast<decimal>(parY))));
						}
					}
					assert(parX > 0 && parY > 0);
					dar = Dar(static_cast<unsigned long long>(parX), static_cast<unsigned long long>(parY));
				}
				else
				{
					scriptVerticalResolution = (static_cast<int>(Math::Round(resizedVerticalResolution / static_cast<decimal>(mod)))) * mod;
					dar = Nullable<Dar>();
				}

				return scriptVerticalResolution;
			}

			decimal Resolution::getAspectRatio(decimal inputAR, decimal calculatedAR, decimal acceptableAspectErrorPercent)
			{
				decimal aspectError = inputAR / calculatedAR;
				if (abs(aspectError - 1.0) * 100.0 < acceptableAspectErrorPercent)
					return inputAR;
				else
					return calculatedAR;
			}

			decimal Resolution::GetAspectRatioError(int inputWidth, int inputHeight, int outputWidth, int outputHeight, CropValues *Cropping, Nullable<Dar> inputDar, bool signalAR, Nullable<Dar> outputDar)
			{
				if (inputHeight <= 0 || inputWidth <= 0 || outputHeight <= 0 || outputWidth <= 0)
					return 0;

				// get input dimension with SAR 1:1
				int iHeight = inputHeight - Cropping->top - Cropping->bottom;
				decimal iWidth = inputWidth - Cropping->left - Cropping->right;
				if (inputDar.HasValue)
				{
					Sar s = inputDar.Value::ToSar(inputWidth, inputHeight);
					iWidth = iWidth * s.getX() / s.getY();
				}

				// get output dimension with SAR 1:1
				int oHeight = outputHeight;
				decimal oWidth = outputWidth;
				if (signalAR && outputDar.HasValue)
				{
					Sar s = outputDar.Value::ToSar(outputWidth, outputHeight);
					oWidth = oWidth * s.getX() / s.getY();
				}

				return (iHeight * oWidth) / (iWidth * oHeight) - 1;
			}

			MeGUI::core::util::Dar Resolution::GetDAR(int width, int height, const std::string &darValue, Nullable<decimal> par, const std::string &darString)
			{
				if (!darString.empty() && width == 720 && (height == 576 || height == 480))
				{
					Dar newDar = Dar::A1x1;
					if (!MainForm::Instance->getSettings()->getUseITUValues())
					{
						if (darString.Equals("16:9"))
							newDar = Dar::STATIC16x9;
						else if (darString.Equals("4:3"))
							newDar = Dar::STATIC4x3;
					}
					else if (height == 576)
					{
						if (darString.Equals("16:9"))
							newDar = Dar::ITU16x9PAL;
						else if (darString.Equals("4:3"))
							newDar = Dar::ITU4x3PAL;
					}
					else
					{
						if (darString.Equals("16:9"))
							newDar = Dar::ITU16x9NTSC;
						else if (darString.Equals("4:3"))
							newDar = Dar::ITU4x3NTSC;
					}
					if (!newDar.Equals(Dar::A1x1))
						return newDar;
				}

				if (!par.HasValue || par <= 0)
					par = 1;

				Nullable<decimal> dar = easyParseDecimal(darValue);
				if (dar.HasValue && dar > 0)
				{
					decimal correctDar = static_cast<decimal>(width) * static_cast<decimal>(par) / height;
					if (abs(Math::Round(correctDar, 3) - Math::Round(static_cast<decimal>(dar), 3)) <= 0.001)
						return Dar(static_cast<unsigned long long>(Math::Round(width * static_cast<decimal>(par))), static_cast<unsigned long long>(height));
					else
						return Dar(static_cast<decimal>(dar));
				}

				if (darValue.find(":") != string::npos)
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					return Dar(unsigned long long::Parse(darValue.Split(':')[0]), unsigned long long::Parse(darValue.Split(':')[1]));
				else
					return Dar(static_cast<unsigned long long>(width), static_cast<unsigned long long>(height));
			}

			Nullable<decimal> Resolution::easyParseDecimal(const std::string &value)
			{
				try
				{
					System::Globalization::CultureInfo *culture = new System::Globalization::CultureInfo("en-us");
					return decimal::Parse(value, culture);
				}
				catch (std::exception &e1)
				{
					return 0;
				}
			}
		}
	}
}
