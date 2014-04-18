#pragma once

#include "core/plugins/interfaces/IMediaFile.h"
#include "VideoUtil.h"
#include "packages/tools/avscreator/AviSynthWindow.h"
#include "packages/tools/avscreator/ScriptServer.h"
#include <QMap>

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




//using namespace System::Collections::Generic;





//using namespace System::Text;

namespace MeXgui
{
	namespace core
	{
		namespace util
		{
			class Autocrop
			{
			public:
				static bool autocrop(CropValues *&cropValues, IVideoReader *reader, bool signalAR, mod16Method cropMethod, modValue mValue);

				static CropValues *autocrop(IVideoReader *reader);

				/// <summary>
				/// iterates through a set of CropValues and tries to find a majority of matching crop values. 
				/// if a match is found, the crop values are returned
				/// if not, the minimum found value is returned for the value in question
				/// </summary>
				/// <param name="values">the CropValues array to be analyzed</param>
				/// <returns>the final CropValues</returns>
			private:
				static CropValues *getFinalAutocropValues(CropValues values[]);

				static bool isBadPixel(int pixel);

				/// <summary>
				/// iterates through the lines and columns of the bitQMap and compares the pixel values with the value of the upper left corner pixel
				/// if a pixel that doesn't have the same color value is found, it is assumed that this is the first line that does not need to be cropped away
				/// </summary>
				/// <param name="b">the bitQMap to be analyzed</param>
				/// <returns>struct containing the number of lines to be cropped away from the left, top, right and bottom</returns>
				static CropValues *getAutoCropValues(BitQMap *b);
			};
		}
	}
}
