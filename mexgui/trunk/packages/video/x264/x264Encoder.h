#pragma once

#include "core/plugins/implemented/video/CommandlineVideoEncoder.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/details/video/VideoJob.h"
#include "x264Settings.h"
#include "MeGUI.Properties.Settings.h"
#include "core/util/OSInfo.h"
#include "core/plugins/implemented/CommandlineJobProcessor.h"
#include "core/util/LogItem.h"
#include "core/details/video/VideoCodecSettings.h"
#include "core/util/DAR.h"
#include "x264SettingsHandler.h"
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
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms; // used for the MethodInvoker

using namespace MeGUI::core::util;

namespace MeGUI
{
	class x264Encoder : public CommandlineVideoEncoder
	{
	public:
		static JobProcessorFactory *const Factory;

	private:
		static IJobProcessor *init(MainForm *mf, Job *j);

	public:
		x264Encoder(const std::string &encoderPath);

		virtual void ProcessLine(const std::string &line, StreamType stream, ImageType oType);

		static std::string genCommandline(const std::string &input, const std::string &output, Nullable<Dar> d, int hres, int vres, int fps_n, int fps_d, x264Settings *_xs, Zone zones[], LogItem *log);

	protected:
		const virtual std::string &getCommandline() const;

		virtual void doExitConfig();
	};
}