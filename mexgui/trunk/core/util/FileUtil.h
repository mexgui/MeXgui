#pragma once

#include "core/gui/MeGUI.MainForm.h"
#include "LogItem.h"
#include <string>
#include <vector>
#include <algorithm>
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
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace ICSharpCode::SharpZipLib::Zip;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			typedef bool (*FileExists)(const std::string &filename);

			class FileUtil
			{
			public:
				static DirectoryInfo *CreateTempDirectory();

				static bool DeleteFile(const std::string &strFile);

				static void CreateZipFile(const std::string &path, const std::string &filename);

				static void ExtractZipFile(const std::string &file, const std::string &extractFolder);

				static void ExtractZipFile(Stream *s, const std::string &extractFolder);

				static void DeleteDirectoryIfExists(const std::string &p, bool recursive);

				static DirectoryInfo *ensureDirectoryExists(const std::string &p);

				static std::string GetDirectoryName(const std::string &file);

				/// <summary>
				/// Generates a filename not in the list
				/// </summary>
				/// <param name="original"></param>
				/// <param name="filenames"></param>
				/// <returns></returns>
				static std::string getUniqueFilename(const std::string &original, std::vector<std::string> &filenames);

				/// <summary>
				/// Generates a unique filename by adding numbers to the filename.
				/// </summary>
				/// <param name="original"></param>
				/// <param name="fileExists"></param>
				/// <returns></returns>
				static std::string getUniqueFilename(const std::string &original, FileExists fileExists);

				static std::vector<std::string> AllFiles(const std::string &folder);

			private:
				static void AddFiles(const std::string &folder, std::vector<std::string> &list);

				static const int BUFFER_SIZE = 2 * 1024 * 1024; // 2 MBs
			public:
				static void copyData(Stream *input, Stream *output);

				/// <summary>
				/// Returns the full path and filename, but without the extension
				/// </summary>
				/// <param name="path"></param>
				/// <returns></returns>
				static std::string GetPathWithoutExtension(const std::string &path);

				/// <summary>
				/// Returns TimeSpan value formatted
				/// </summary>
				/// <param name="path"></param>
				/// <returns></returns>
				static std::string ToShortString(TimeSpan *ts);

				/// <summary>
				/// Adds extra to the filename, modifying the filename but keeping the extension and folder the same.
				/// </summary>
				/// <param name="filename"></param>
				/// <param name="extra"></param>
				/// <returns></returns>
				static std::string AddToFileName(const std::string &filename, const std::string &extra);

				/// <summary>
				/// Returns true if the filename matches the filter specified. The format
				/// of the filter is the same as that of a FileDialog.
				/// </summary>
				/// <param name="filter"></param>
				/// <param name="filename"></param>
				/// <returns></returns>
				static bool MatchesFilter(const std::string &filter, const std::string &filename);

				/// <summary>
				/// Copy File
				/// </summary>
				/// <param name"sourcePath">Path of the Source file</param>
				/// <param name"targetPath">Path of the Target File</param>
				/// <param name"targetName">Name of the Target file</param>
				/// <param name="overwrite"></param>
				static void CopyFile(const std::string &sourcePath, const std::string &targetPath, const std::string &targetName, bool overwrite);

				/// <summary>
				/// Backup File
				/// </summary>
				/// <param name"sourcePath">Path of the Source file</param>
				/// <param name="overwrite"></param>
				static void BackupFile(const std::string &sourcePath, bool overwrite);

				/// <summary>
				/// Checks if a directory is writable
				/// </summary>
				/// <param name"strPath">path to check</param>
				static bool IsDirWriteable(const std::string &strPath);

				/// <summary>
				/// Attempts to delete all files and directories listed 
				/// in job.FilesToDelete if settings.DeleteIntermediateFiles is checked
				/// </summary>
				/// <param name="job">the job which should just have been completed</param>
				static LogItem *DeleteIntermediateFiles(std::vector<std::string> &files, bool bAlwaysAddLog, bool askAboutDelete);

				/// <summary>
				/// Detects the file version/date and writes it into the log
				/// </summary>
				/// <param name="strName">the name in the log</param>
				/// <param name="strFile">the file to check</param>
				/// <param name="oLog">the LogItem where the information should be added</param>
				static void GetFileInformation(const std::string &strName, const std::string &strFile, LogItem *&oLog);

				/// <summary>
				/// Create Chapters XML File from OGG Chapters File
				/// </summary>
				/// <param name="inFile">input</inFile>
				static void CreateXMLFromOGGChapFile(const std::string &inFile);

				static short GetFileEncoding(const std::string &srcFile);

			};
		}
	}
}
