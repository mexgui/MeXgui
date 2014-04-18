#pragma once

#include "core/util/DAR.h"
#include "core/details/video/VideoCodecSettings.h"
#include <string>

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
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details::video;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::video::x264;
using namespace MeGUI::packages::video::xvid;
using namespace MeGUI::packages::audio::naac;
using namespace MeGUI::packages::audio::ffac3;
using namespace MeGUI::packages::audio::ffmp2;
using namespace MeGUI::packages::audio::lame;
using namespace MeGUI::packages::audio::vorbis;
using namespace MeGUI::packages::audio::aften;
using namespace MeGUI::packages::audio::opus;
using namespace MeGUI::packages::audio::qaac;

namespace MeGUI
{

	typedef void (*StringChanged)(object *sender, const std::string &val);
	typedef void (*IntChanged)(object *sender, int val);
	class VideoInfo
	{
	private:
		std::string videoInput;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event StringChanged VideoInputChanged;
	public:
		const std::string &getVideoInput() const;
		void setVideoInput(const std::string &value);

	private:
		std::string videoOutput;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event StringChanged VideoOutputChanged;
	public:
		const std::string &getVideoOutput() const;
		void setVideoOutput(const std::string &value);

	private:
		Nullable<Dar> dar;
	public:
		const Nullable<Dar> &getDAR() const;
		void setDAR(const Nullable<Dar> &value);

	private:
		int introEndFrame;
	public:
		const int &getIntroEndFrame() const;
		void setIntroEndFrame(const int &value);

	private:
		int creditsStartFrame;
	public:
		const int &getCreditsStartFrame() const;
		void setCreditsStartFrame(const int &value);

	private:
//ORIGINAL LINE: private Zone[] zones;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		Zone *zones;
	public:
		const Zone *getZones() const;
		void setZones(Zone value[]);

		VideoInfo(const std::string &videoInput, const std::string &videoOutput, int darX, int darY, int creditsStartFrame, int introEndFrame, Zone zones[]);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public VideoInfo() : this("", "", -1, -1, -1, -1, nullptr)
		VideoInfo();

		VideoInfo *Clone();

	private:
		void InitializeInstanceFields();
	};
}
