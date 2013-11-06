#pragma once

#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "LogItem.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/details/video/VideoJob.h"
#include "core/details/Streams.h"
#include "JobUtil.h"
#include "packages/tools/calculator/CalcData.h"
#include "core/details/TaggedJob.h"
#include "MeGUI.Properties.Settings.h"
#include "FileSize.h"
#include "core/details/CodecManager.h"
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2011  Doom9 & al
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
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::details;
using namespace MeGUI::packages::tools::calculator;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			class BitrateCalculatorPreProcessor
			{
			public:
				static JobPreProcessor *CalculationProcessor;
				/// <summary>
				/// postprocesses an audio job followed by a video job
				/// this constellation happens in automated or one click encoding where we have an audio job linked
				/// to a video job
				/// first, any audio jobs previous to the audio job in question will be located
				/// then we get the size of all audio tracks
				/// from the desired final output size stored in the first video job, we calculate the video bitrate
				/// we have to use to obtain the final file size, taking container overhead into account
				/// the calculated bitrate is then applied to all video jobs
				/// </summary>
				/// <param name="firstAudio">the audio job that is linked to a video job</param>
				/// <param name="firstpass">the video job to which the audio job is linked</param>
				static LogItem *calculateBitrate(MainForm *mainForm, Job *ajob);
			};

			class BitrateCalculationInfo
			{
			public:
				const std::string *get_VideoJobNames() const;
				void set_VideoJobNames(std::string value[]);
			private:
//ORIGINAL LINE: private string[] _videoJobNames;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				std::string *_videoJobNames;

				std::vector<TaggedJob*> videoJobs;
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore]
				const std::vector<TaggedJob*> &getVideoJobs() const;
				void setVideoJobs(const std::vector<TaggedJob*> &value);

				FileSize DesiredSize;

				std::vector<std::string> AudioFiles;


//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore]
				ContainerType *Container;

				const std::string &get_ContainerName() const;
				void set_ContainerName(const std::string &value);
			};
		}
	}
}
