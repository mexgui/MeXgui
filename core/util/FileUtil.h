#pragma once

#include "core/gui/MainForm.h"
#include "LogItem.h"
#include <QString>
#include <QVector>
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




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;



using namespace ICSharpCode::SharpZipLib::Zip;

namespace MeXgui
{
	namespace core
	{
		namespace util
		{
			typedef bool (*FileExists)(const QString &filename);

			class FileUtil
			{
			public:
				static DirectoryInfo *CreateTempDirectory();

				static bool DeleteFile(const QString &strFile);

				static void CreateZipFile(const QString &path, const QString &filename);

				static void ExtractZipFile(const QString &file, const QString &extractFolder);

				static void ExtractZipFile(Stream *s, const QString &extractFolder);

				static void DeleteDirectoryIfExists(const QString &p, bool recursive);

				static DirectoryInfo *ensureDirectoryExists(const QString &p);

				static QString GetDirectoryName(const QString &file);

				/// <summary>
				/// Generates a filename not in the list
				/// </summary>
				/// <param name="original"></param>
				/// <param name="filenames"></param>
				/// <returns></returns>
				static QString getUniqueFilename(const QString &original, QVector<QString> &filenames);

				/// <summary>
				/// Generates a unique filename by adding numbers to the filename.
				/// </summary>
				/// <param name="original"></param>
				/// <param name="fileExists"></param>
				/// <returns></returns>
				static QString getUniqueFilename(const QString &original, FileExists fileExists);

				static QVector<QString> AllFiles(const QString &folder);

			private:
				static void AddFiles(const QString &folder, QVector<QString> &list);

				static const int BUFFER_SIZE = 2 * 1024 * 1024; // 2 MBs
			public:
				static void copyData(Stream *input, Stream *output);

				/// <summary>
				/// Returns the full path and filename, but without the extension
				/// </summary>
				/// <param name="path"></param>
				/// <returns></returns>
				static QString GetPathWithoutExtension(const QString &path);

				/// <summary>
				/// Returns TimeSpan value formatted
				/// </summary>
				/// <param name="path"></param>
				/// <returns></returns>
				static QString ToShortString(TimeSpan *ts);

				/// <summary>
				/// Adds extra to the filename, modifying the filename but keeping the extension and folder the same.
				/// </summary>
				/// <param name="filename"></param>
				/// <param name="extra"></param>
				/// <returns></returns>
				static QString AddToFileName(const QString &filename, const QString &extra);

				/// <summary>
				/// Returns true if the filename matches the filter specified. The format
				/// of the filter is the same as that of a FileDialog.
				/// </summary>
				/// <param name="filter"></param>
				/// <param name="filename"></param>
				/// <returns></returns>
				static bool MatchesFilter(const QString &filter, const QString &filename);

				/// <summary>
				/// Copy File
				/// </summary>
				/// <param name"sourcePath">Path of the Source file</param>
				/// <param name"targetPath">Path of the Target File</param>
				/// <param name"targetName">Name of the Target file</param>
				/// <param name="overwrite"></param>
				static void CopyFile(const QString &sourcePath, const QString &targetPath, const QString &targetName, bool overwrite);

				/// <summary>
				/// Backup File
				/// </summary>
				/// <param name"sourcePath">Path of the Source file</param>
				/// <param name="overwrite"></param>
				static void BackupFile(const QString &sourcePath, bool overwrite);

				/// <summary>
				/// Checks if a directory is writable
				/// </summary>
				/// <param name"strPath">path to check</param>
				static bool IsDirWriteable(const QString &strPath);

				/// <summary>
				/// Attempts to delete all files and directories listed 
				/// in job.FilesToDelete if settings.DeleteIntermediateFiles is checked
				/// </summary>
				/// <param name="job">the job which should just have been completed</param>
				static LogItem *DeleteIntermediateFiles(QVector<QString> &files, bool bAlwaysAddLog, bool askAboutDelete);

				/// <summary>
				/// Detects the file version/date and writes it into the log
				/// </summary>
				/// <param name="strName">the name in the log</param>
				/// <param name="strFile">the file to check</param>
				/// <param name="oLog">the LogItem where the information should be added</param>
				static void GetFileInformation(const QString &strName, const QString &strFile, LogItem *&oLog);

				/// <summary>
				/// Create Chapters XML File from OGG Chapters File
				/// </summary>
				/// <param name="inFile">input</inFile>
				static void CreateXMLFromOGGChapFile(const QString &inFile);

				static short GetFileEncoding(const QString &srcFile);

			};
		}
	}
}
