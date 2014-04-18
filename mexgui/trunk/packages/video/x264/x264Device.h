#pragma once

#include "packages/tools/avclevelschecker/AVCLevels.h"
#include "core/plugins/interfaces/Profile.h"
#include <string>
#include <vector>

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

namespace MeGUI
{
	class x264Device
	{
	private:
		std::string strName;
		int iID, iProfile, iVBVBufsize, iVBVMaxrate, iBframes, iReframes, iMaxWidth, iMaxHeight, iMaxGop, iBPyramid;
		bool bBluRay;
		AVCLevels::Levels avcLevel;

	public:
		static std::vector<x264Device*> CreateDeviceList();

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public x264Device(int iID, string strName, int iProfile, AVCLevels.Levels avcLevel, int iVBVBufsize, int iVBVMaxrate, int iBframes, int iReframes, int iMaxWidth, int iMaxHeight) : this(iID, strName, iProfile, avcLevel, iVBVBufsize, iVBVMaxrate, iBframes, iReframes, iMaxWidth, iMaxHeight, false, -1, -1)
		x264Device(int iID, const std::string &strName, int iProfile, AVCLevels::Levels avcLevel, int iVBVBufsize, int iVBVMaxrate, int iBframes, int iReframes, int iMaxWidth, int iMaxHeight);

		x264Device(int iID, const std::string &strName, int iProfile, AVCLevels::Levels avcLevel, int iVBVBufsize, int iVBVMaxrate, int iBframes, int iReframes, int iMaxWidth, int iMaxHeight, bool bBluRay, int iMaxGop, int iBPyramid);

		const int &getID() const;

		const std::string &getName() const;

		const int &getProfile() const;

		const AVCLevels::Levels &getAVCLevel() const;

		const int &getVBVBufsize() const;

		const int &getVBVMaxrate() const;

		const int &getBFrames() const;

		const int &getReferenceFrames() const;

		const int &getHeight() const;

		const int &getWidth() const;

		const int &getMaxGOP() const;
		void setMaxGOP(const int &value);

		const bool &getBluRay() const;
		void setBluRay(const bool &value);

		const int &getBPyramid() const;
		void setBPyramid(const int &value);

		virtual std::string ToString();
	};
}
