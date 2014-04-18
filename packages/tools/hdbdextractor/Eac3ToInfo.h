#pragma once

#include "eac3to/Feature.h"
#include "core/util/LogItem.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/gui/MeXgui.MainForm.h"
#include "Extensions.h"
#include "eac3to/File.h"
#include "eac3to/Stream.h"
#include <QString>
#include <QVector>
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




//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;

//using namespace System::Text;

//using namespace System::Text::RegularExpressions;

using namespace MeXgui::core::util;
using namespace eac3to;

namespace MeXgui
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
								QString privateeac3toPath;
							public:
								const QString &geteac3toPath() const;
								void seteac3toPath(const QString &value);
							private:
								QString privateworkingFolder;
							public:
								const QString &getworkingFolder() const;
								void setworkingFolder(const QString &value);
							private:
								QString privatefeatureNumber;
							public:
								const QString &getfeatureNumber() const;
								void setfeatureNumber(const QString &value);
							private:
								QString privateargs;
							public:
								const QString &getargs() const;
								void setargs(const QString &value);
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
					QVector<Feature*> features;
					OperatingMode oMode;
					eac3toArgs args;
					QVector<QString> input;
					LogItem *_log;
					MediaInfoFile *iFile;
					bool bFetchAll;
					int iFeatureToFetch;

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//					public event OnFetchInformationCompletedHandler FetchInformationCompleted;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//					public event OnProgressChangedHandler ProgressChanged;

				public:
					Eac3toInfo(QVector<QString> &input, MediaInfoFile *iFile, LogItem *oLog);

					bool IsBusy();

					const QVector<Feature*> &getFeatures() const;

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

					void backgroundWorker_Exited();

					void backgroundWorker_ErrorDataReceived(object *sender, DataReceivedEventArgs *e);

					void backgroundWorker_OutputDataReceived(object *sender, DataReceivedEventArgs *e);
				};
			}
		}
	}
}
