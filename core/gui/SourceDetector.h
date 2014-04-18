#pragma once

#include "SourceDetectorSettings.h"
#include "packages/reader/d2v/d2vReader.h"
#include "core/util/DeinterlaceFilter.h"
#include "packages/tools/avscreator/ScriptServer.h"
#include <QString>
#include <QVector>
#include <cmath>
#include <stdexcept>

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



//using namespace System::Data;

//using namespace System::Diagnostics;





//using namespace System::Globalization;

//using namespace System::Text;

//using namespace System::Threading;



namespace MeGUI
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	typedef void (*UpdateSourceDetectionStatus)(int numDone, int total); // catches the UpdateGUI events fired from the encoder
	typedef void (*FinishedAnalysis)(SourceInfo *info, bool error, const QString &errorMessage);

	class SourceInfo
	{
	public:
		FieldOrder fieldOrder;
		SourceType sourceType;
		int decimateM;
		bool majorityFilm;
		bool isAnime;
		QString analysisResult;
	};

	enum SourceType
	{
		UNKNOWN,
		NOT_ENOUGH_SECTIONS,
		PROGRESSIVE,
		INTERLACED,
		FILM,
		DECIMATING,
		HYBRID_FILM_INTERLACED,
		HYBRID_PROGRESSIVE_INTERLACED,
		HYBRID_PROGRESSIVE_FILM
	};

	enum FieldOrder
	{
		UNKNOWN,
		TFF,
		BFF,
		VARIABLE,
	};

	class SourceDetector
	{
	public:
//C# TO C++ CONVERTER NOTE: The parameter d2vFile was renamed since it is named the same as a user-defined type:
		SourceDetector(const QString &avsScript, const QString &d2vFile_Renamed, bool isAnime, SourceDetectorSettings *settings, UpdateSourceDetectionStatus updateMethod, FinishedAnalysis finishedMethod);

	private:
		bool isAnime;
		bool error, continueWorking;
		QString errorMessage;
		SourceDetectorSettings *settings;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		private event UpdateSourceDetectionStatus analyseUpdate;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		private event FinishedAnalysis finishedAnalysis;
		QString script, d2vFileName, trimmedFilteredLine;
		SourceType type;
		int decimateM;
		int tffCount, bffCount;
		FieldOrder fieldOrder;
	public:
		bool majorityFilm, usingPortions;

	private:
		QString analysis;
		QVector<DeinterlaceFilter*> filters;
		QString findPortions(QVector<int[]> &portions, int selectEvery, int selectLength, int numPortions, int sectionCount, int inputFrames, const QString &type, QString &trimLine, int &frameCount);

		QString getLogFileName(const QString &logFileName);

		// stax
		void Process(const QString &scriptBlock);
			private *catch_Renamed(std::exception &ex);

		private:
			void InitializeInstanceFields();
	};
	private:
		void runScript(int scriptType, int frameCount, const QString &trimLine);

		bool checkDecimate(int data[]);
		void analyseFF(const QString &filename);
		void analyse(const QString &logFileName, int selectEvery, int selectLength, int inputFrames);
		void finishProcessing();
	public:
		void analyse();
		void stop();
}
}
