#pragma once

#include "core/util/DAR.h"
#include "core/details/video/VideoCodecSettings.h"
#include <QString>

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



using namespace MeXgui::core::details::video;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::video::x264;
using namespace MeXgui::packages::video::xvid;
using namespace MeXgui::packages::audio::naac;
using namespace MeXgui::packages::audio::ffac3;
using namespace MeXgui::packages::audio::ffmp2;
using namespace MeXgui::packages::audio::lame;
using namespace MeXgui::packages::audio::vorbis;
using namespace MeXgui::packages::audio::aften;
using namespace MeXgui::packages::audio::opus;
using namespace MeXgui::packages::audio::qaac;

namespace MeXgui
{

	typedef void (*StringChanged)(object *sender, const QString &val);
	typedef void (*IntChanged)(object *sender, int val);
	class VideoInfo
	{
	private:
		QString videoInput;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event StringChanged VideoInputChanged;
	public:
		const QString &getVideoInput() const;
		void setVideoInput(const QString &value);

	private:
		QString videoOutput;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event StringChanged VideoOutputChanged;
	public:
		const QString &getVideoOutput() const;
		void setVideoOutput(const QString &value);

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

		VideoInfo(const QString &videoInput, const QString &videoOutput, int darX, int darY, int creditsStartFrame, int introEndFrame, Zone zones[]);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public VideoInfo() : this("", "", -1, -1, -1, -1, nullptr)
		VideoInfo();

		VideoInfo *Clone();

	private:
		void InitializeInstanceFields();
	};
}
