#pragma once

#include "DAR.h"
#include "LogItem.h"
#include "VideoUtil.h"
#include "packages/video/x264/x264Device.h"
#include "packages/tools/avscreator/AviSynthWindow.h"
#include "core/gui/MeGUI.MainForm.h"
#include <string>
#include <cmath>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
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
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			class Resolution
			{
				/// <summary>
				/// gets the desired resolution based on input settings
				/// </summary>
				/// <param name="sourceWidth">the complete width of the input file without cropping</param>
				/// <param name="sourceHeight">the complete height of the input file without cropping</param>
				/// <param name="inputDAR">the input DAR value</param>
				/// <param name="cropValues">the crop values</param>
				/// <param name="cropEnabled">true if crop values must be used</param>
				/// <param name="mod">the mod value used for the final resize values</param>
				/// <param name="resizeEnabled">true if resize can be used</param>
				/// <param name="upsizingEnabled">true if upsizing can be used</param>
				/// <param name="signalAR">whether or not ar signalling is to be used for the output 
				/// (depending on this parameter, resizing changes to match the source AR)</param>
				/// <param name="suggestHeight">true if height should be calculated</param>
				/// <param name="acceptableAspectErrorPercent">acceptable aspect error if signalAR is true</param>
				/// <param name="xTargetDevice">x264 Target Device - may limit the output resolution</param>
				/// <param name="fps">the frames per second of the source</param>
				/// <param name="outputWidth">the calculated output width</param>
				/// <param name="outputHeight">the calculated output height</param>
				/// <param name="paddingValues">the padding values</param>
				/// <param name="outputDar">the output DAR value</param>
				/// <param name="_log">the log item</param>
			public:
				static void GetResolution(int sourceWidth, int sourceHeight, Dar inputDar, CropValues *&cropValues, bool cropEnabled, int mod, bool &resizeEnabled, bool upsizingAllowed, bool signalAR, bool suggestHeight, decimal acceptableAspectErrorPercent, x264Device *xTargetDevice, double fps, int &outputWidth, int &outputHeight, CropValues *&paddingValues, Nullable<Dar> &outputDar, LogItem *_log);

				/// <summary>
				/// check if resolution is device compatible
				/// </summary>
				/// <param name="xTargetDevice">x264 Target Device - may limit the output resolution</param>
				/// <param name="outputWidth">the calculated output width</param>
				/// <param name="outputHeight">the calculated output height</param>
				/// <param name="settingsChanged">true if resize or crop has been changed</param>
				/// <param name="resizeEnabled">if resize is enabled</param>
				/// <param name="cropEnabled">if crop is enabled</param>
				/// <param name="_log">log item</param>
				/// <returns>true if the settings are device compatible</returns>
			private:
				static bool isResolutionDeviceCompliant(x264Device *xTargetDevice, int outputWidth, int outputHeight, bool &settingsChanged, bool &resizeEnabled, bool &cropEnabled, LogItem *_log);

				/// <summary>
				/// gets the desired resolution based on input settings
				/// </summary>
				/// <param name="sourceWidth">the complete width of the input file without cropping</param>
				/// <param name="sourceHeight">the complete height of the input file without cropping</param>
				/// <param name="inputDAR">the input DAR value</param>
				/// <param name="cropping">the crop values</param>
				/// <param name="mod">the mod value used for the final resize values</param>
				/// <param name="resizeEnabled">true if resize can be used</param>
				/// <param name="upsizingEnabled">true if upsizing can be used</param>
				/// <param name="signalAR">whether or not ar signalling is to be used for the output 
				/// (depending on this parameter, resizing changes to match the source AR)</param>
				/// <param name="suggestHeight">true if height should be calculated</param>
				/// <param name="acceptableAspectErrorPercent">acceptable aspect error if signalAR is true</param>
				/// <param name="outputWidth">the calculated output width</param>
				/// <param name="outputHeight">the calculated output height</param>
				/// <param name="outputDar">the output DAR value</param>
				/// <param name="_log">the log item</param>
				static void getResolution(int sourceWidth, int sourceHeight, Dar inputDar, CropValues *cropValues, bool cropEnabled, int mod, bool resizeEnabled, bool upsizingAllowed, bool signalAR, bool suggestHeight, decimal acceptableAspectErrorPercent, int &outputWidth, int &outputHeight, Nullable<Dar> &outputDar, LogItem *_log);

				/// <summary>
				/// calculates the mod value
				/// </summary>
				/// <param name="modMethod">the selected mod method</param>
				/// <param name="modMethod">the selected mod value</param>
				/// <param name="signalAR">whether or not we're going to signal the aspect ratio</param>
				/// <returns>the mod value</returns>
			public:
				static int GetModValue(modValue modValue, mod16Method modMethod, bool signalAR);

				/// <summary>
				/// calculates the ideal mod vertical resolution that matches the desired horizontal resolution
				/// </summary>
				/// <param name="readerHeight">height of the source</param>
				/// <param name="readerWidth">width of the source</param>
				/// <param name="customDAR">custom display aspect ratio to be taken into account for resizing</param>
				/// <param name="cropping">the crop values for the source</param>
				/// <param name="horizontalResolution">the desired horizontal resolution of the output</param>
				/// <param name="signalAR">whether or not we're going to signal the aspect ratio (influences the resizing)</param>
				/// <param name="sarX">horizontal pixel aspect ratio (used when signalAR = true)</param>
				/// <param name="sarY">vertical pixel aspect ratio (used when signalAR = true)</param>
				/// <param name="mod">the MOD value</param>
				/// <returns>the suggested horizontal resolution</returns>
				static int SuggestVerticalResolution(double readerHeight, double readerWidth, Dar inputDAR, CropValues *cropping, int horizontalResolution, bool signalAR, Nullable<Dar> &dar, int mod, decimal acceptableAspectErrorPercent);

				/// <summary>
				/// finds the aspect ratio closest to the one giving as parameter (which is an approximation using the selected DAR for the source and the cropping values)
				/// </summary>
				/// <param name="calculatedAR">the aspect ratio to be approximated</param>
				/// <returns>the aspect ratio that most closely matches the input</returns>
			private:
				static decimal getAspectRatio(decimal inputAR, decimal calculatedAR, decimal acceptableAspectErrorPercent);

				/// <summary>
				/// calculates the aspect ratio error
				/// </summary>
				/// <param name="inputWidth">height of the source (without cropping!)</param>
				/// <param name="inputHeight">width of the source (without cropping!)</param>
				/// <param name="outputWidth">the desired width of the output</param>
				/// <param name="outputHeight">the desired height of the output</param>
				/// <param name="Cropping">the crop values for the source</param>
				/// <param name="inputDar">custom input display aspect ratio to be taken into account</param>
				/// <param name="signalAR">whether or not we're going to signal the aspect ratio (influences the resizing)</param>
				/// <param name="outputDar">custom output display aspect ratio to be taken into account</param>
				/// <returns>the aspect ratio error in percent</returns>
			public:
				static decimal GetAspectRatioError(int inputWidth, int inputHeight, int outputWidth, int outputHeight, CropValues *Cropping, Nullable<Dar> inputDar, bool signalAR, Nullable<Dar> outputDar);

				/// <summary>
				/// calculates the DAR value based upon the video information 
				/// </summary>
				/// <param name="width">width of the video</param>
				/// <param name="height">height of the video</param>
				/// <param name="dar">display aspect ratio </param>
				/// <param name="par">pixel aspect ratio </param>
				/// <param name="darString">display aspect ratio string - e.g. 16:9 or 4:3</param>
				/// <returns>the DAR value</returns>
				static Dar GetDAR(int width, int height, const std::string &darValue, Nullable<decimal> par, const std::string &darString);

			private:
				static Nullable<decimal> easyParseDecimal(const std::string &value);
			};
		}
	}
}
