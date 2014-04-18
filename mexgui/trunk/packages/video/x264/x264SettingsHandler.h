#pragma once

#include "x264Settings.h"
#include "core/util/LogItem.h"
#include "x264Device.h"
#include "core/util/DAR.h"
#include "packages/tools/avclevelschecker/AVCLevels.h"
#include <string>
#include <cmath>
#include "stringconverter.h"

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
//using namespace System::Text;

using namespace MeGUI::core::util;

namespace MeGUI
{
	namespace packages
	{
		namespace video
		{
			namespace x264
			{
				class x264SettingsHandler
				{
				private:
					x264Settings *_xs;
					LogItem *_log;
					x264Device *_device;

				public:
					x264SettingsHandler(x264Settings *xs, LogItem *log);

					/// <summary>
					/// Checks input video file for device compatibility
					/// </summary>
					/// <param name="hRes">the horizontal resolution</param>
					/// <param name="vRes">the vertical resolution</param>
					/// <param name="fps_n">fps numerator</param>
					/// <param name="fps_d">fps denominator</param>
					/// <returns>whether the source could be opened or not</returns>
					void CheckInputFile(Nullable<Dar> d, int hres, int vres, int fps_n, int fps_d);

					/// <summary>
					/// Calculates the --vbv-bufsize value
					/// </summary>
					/// <returns>the --vbv-bufsize value</returns>
					int getVBVBufsize(AVCLevels::Levels avcLevel, bool bIsHighProfile);

					/// <summary>
					/// Calculates the --vbv-maxrate value
					/// </summary>
					/// <returns>the --vbv-maxrate value</returns>
					int getVBVMaxrate(AVCLevels::Levels avcLevel, bool bIsHighProfile);

					/// <summary>
					/// Calculates --sar value
					/// </summary>
					/// <returns>the --sar value</returns>
					int getSar(Nullable<Dar> d, int hRes, int vRes, std::string &CustomSarValue, const std::string &CustomSarValueInput);

					/// <summary>
					/// Calculates --colorprim value
					/// </summary>
					/// <returns>the --colorprim value</returns>
					int getColorprim();

					/// <summary>
					/// Calculates --pulldown value
					/// </summary>
					/// <returns>the --pulldown value</returns>
					int getPulldown();

					/// <summary>
					/// Calculates --transfer value
					/// </summary>
					/// <returns>the --transfer value</returns>
					int getTransfer();

					/// <summary>
					/// Calculates --colormatrix value
					/// </summary>
					/// <returns>the --colormatrix value</returns>
					int getColorMatrix();

					/// <summary>
					/// Calculates the AVC profile number
					/// </summary>
					/// <returns>the AVC profile value (0 baseline, 1 main, 2 high)</returns>
					int getProfile();

					/// <summary>
					/// Calculates --nal-hrd value
					/// </summary>
					/// <returns>the --nal-hrd value</returns>
					int getNalHrd();

					/// <summary>
					/// Calculates the AVC level number
					/// </summary>
					/// <returns>the AVC level value</returns>
					AVCLevels::Levels getLevel();

					/// <summary>
					/// Calculates the --key-int value
					/// </summary>
					/// <param name="fps_n">fps numerator</param>
					/// <param name="fps_d">fps denominator</param>
					/// <returns>the --key-int value</returns>
					int getKeyInt(int fps_n, int fps_d);

					/// <summary>
					/// Calculates the --min-keyint value
					/// </summary>
					/// <param name="fps_n">fps numerator</param>
					/// <param name="fps_d">fps denominator</param>
					/// <returns>the --min-keyint value</returns>
					int getMinKeyint(int fps_n, int fps_d);

					/// <summary>
					/// Calculates the --weightp value
					/// </summary>
					/// <returns>the --weightp value</returns>
					int getWeightp();

					/// <summary>
					/// Calculates the --bluray-compat value
					/// </summary>
					/// <returns>true for --bluray-compat</returns>
					bool getBlurayCompat();

					/// <summary>
					/// Calculates the --pic-struct value
					/// </summary>
					/// <returns>true for --pic-struct</returns>
					bool getPicStruct();

					/// <summary>
					/// Calculates the --fake-interlaced value
					/// </summary>
					/// <returns>true for --fake-interlaced</returns>
					bool getFakeInterlaced();

					/// <summary>
					/// Calculates the interlaced mode
					/// </summary>
					/// <returns>interlaced mode</returns>
					x264Settings::x264InterlacedModes getInterlacedMode();

					/// <summary>
					/// Calculates the --aud value
					/// </summary>
					/// <returns>true for --aud</returns>
					bool getAud();

					/// <summary>
					/// Calculates the --bframes value
					/// </summary>
					/// <returns>the --bframes value</returns>
					int getBFrames();

					/// <summary>
					/// Calculates the --b-pyramid value
					/// </summary>
					/// <returns>the --b-pyramid value</returns>
					int getBPyramid();

					/// <summary>
					/// Calculates the --slices value
					/// </summary>
					/// <returns>the --slices value</returns>
					int getSlices();

					/// <summary>
					/// Calculates the --ref value
					/// </summary>
					/// <param name="hRes">the horizontal resolution</param>
					/// <param name="vRes">the vertical resolution</param>
					/// <returns>the --ref value</returns>
					int getRefFrames(int hRes, int vRes);

					/// <summary>
					/// gets the maximum ref count based upon the given level
					/// </summary>
					/// <param name="level">the AVC level</param>
					/// <param name="hRes">the horizontal resolution</param>
					/// <param name="vRes">the vertical resolution</param>
					/// <returns>the maximum reference count; -1 if no restriction</returns>
					static int getMaxRefForLevel(AVCLevels::Levels avcLevel, int hRes, int vRes);

					/// <summary>
					/// returns the value for the selected command in the custom command line 
					/// and removes the command from the custom command line
					/// </summary>
					/// <param name="strCommandToExtract">the command to extract without --</param>
					/// <param name="strCommandValue">the value of the command</param>
					/// <returns>true if the command can be found</returns>
				private:
					bool extractCustomCommand(const std::string &strCommandToExtract, std::string &strCommandValue);

					/// <summary>
					/// returns the custom command line 
					/// </summary>
					/// <returns>the custom command line</returns>
				public:
					std::string getCustomCommandLine();
				};
			}
		}
	}
}
