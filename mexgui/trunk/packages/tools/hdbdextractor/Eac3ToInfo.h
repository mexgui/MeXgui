#pragma once

#include "eac3to/Feature.h"
#include "core/util/LogItem.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/gui/MeGUI.MainForm.h"
#include "Extensions.h"
#include "eac3to/File.h"
#include "eac3to/Stream.h"
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "stringconverter.h"

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;

using namespace MeGUI::core::util;
using namespace eac3to;

namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace hdbdextractor
			{
				class eac3toArgs
				{
							private:
								std::string privateeac3toPath;
							public:
								const std::string &geteac3toPath() const;
								void seteac3toPath(const std::string &value);
							private:
								std::string privateworkingFolder;
							public:
								const std::string &getworkingFolder() const;
								void setworkingFolder(const std::string &value);
							private:
								std::string privatefeatureNumber;
							public:
								const std::string &getfeatureNumber() const;
								void setfeatureNumber(const std::string &value);
							private:
								std::string privateargs;
							public:
								const std::string &getargs() const;
								void setargs(const std::string &value);
							private:
								ResultState privateresultState;
							public:
								const ResultState &getresultState() const;
								void setresultState(const ResultState &value);
				};

				enum ResultState
				{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("Feature Retrieval Completed")]
					FeatureCompleted,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("Stream Retrieval Completed")]
					StreamCompleted,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("Stream Extraction Completed")]
					ExtractCompleted
				};

				typedef void (*OnFetchInformationCompletedHandler)(Eac3toInfo *sender, RunWorkerCompletedEventArgs *args);
				typedef void (*OnProgressChangedHandler)(Eac3toInfo *sender, ProgressChangedEventArgs *args);

				class Eac3toInfo
				{
				private:
					enum OperatingMode
					{
						FileBased,
						FolderBased
					};

				private:
					BackgroundWorker *backgroundWorker;
					std::vector<Feature*> features;
					OperatingMode oMode;
					eac3toArgs args;
					std::vector<std::string> input;
					LogItem *_log;
					MediaInfoFile *iFile;
					bool bFetchAll;
					int iFeatureToFetch;

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//					public event OnFetchInformationCompletedHandler FetchInformationCompleted;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//					public event OnProgressChangedHandler ProgressChanged;

				public:
					Eac3toInfo(std::vector<std::string> &input, MediaInfoFile *iFile, LogItem *oLog);

					bool IsBusy();

					const std::vector<Feature*> &getFeatures() const;

				private:
					void initBackgroundWorker();

				public:
					void FetchAllInformation();

					void FetchFeatureInformation();

					void FetchStreamInformation(int iFeatureNumber);

				private:
					void backgroundWorker_DoWork(object *sender, DoWorkEventArgs *e);

					void backgroundWorker_ProgressChanged(object *sender, ProgressChangedEventArgs *e);

					void backgroundWorker_RunWorkerCompleted(object *sender, RunWorkerCompletedEventArgs *e);

					void backgroundWorker_Exited(object *sender, EventArgs *e);

					void backgroundWorker_ErrorDataReceived(object *sender, DataReceivedEventArgs *e);

					void backgroundWorker_OutputDataReceived(object *sender, DataReceivedEventArgs *e);
				};
			}
		}
	}
}
