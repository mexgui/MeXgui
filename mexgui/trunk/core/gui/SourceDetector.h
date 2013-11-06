#pragma once

#include "SourceDetectorSettings.h"
#include "packages/reader/d2v/d2vReader.h"
#include "core/util/DeinterlaceFilter.h"
#include "packages/tools/avscreator/ScriptServer.h"
#include <string>
#include <vector>
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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace MeGUI
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	typedef void (*UpdateSourceDetectionStatus)(int numDone, int total); // catches the UpdateGUI events fired from the encoder
	typedef void (*FinishedAnalysis)(SourceInfo *info, bool error, const std::string &errorMessage);

	class SourceInfo
	{
	public:
		FieldOrder fieldOrder;
		SourceType sourceType;
		int decimateM;
		bool majorityFilm;
		bool isAnime;
		std::string analysisResult;
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
		SourceDetector(const std::string &avsScript, const std::string &d2vFile_Renamed, bool isAnime, SourceDetectorSettings *settings, UpdateSourceDetectionStatus updateMethod, FinishedAnalysis finishedMethod);

	private:
		bool isAnime;
		bool error, continueWorking;
		std::string errorMessage;
		SourceDetectorSettings *settings;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		private event UpdateSourceDetectionStatus analyseUpdate;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		private event FinishedAnalysis finishedAnalysis;
		std::string script, d2vFileName, trimmedFilteredLine;
		SourceType type;
		int decimateM;
		int tffCount, bffCount;
		FieldOrder fieldOrder;
	public:
		bool majorityFilm, usingPortions;

	private:
		std::string analysis;
		std::vector<DeinterlaceFilter*> filters;
		std::string findPortions(std::vector<int[]> &portions, int selectEvery, int selectLength, int numPortions, int sectionCount, int inputFrames, const std::string &type, std::string &trimLine, int &frameCount);

		std::string getLogFileName(const std::string &logFileName);

		// stax
		void Process(const std::string &scriptBlock);
			private *catch_Renamed(std::exception &ex);

		private:
			void InitializeInstanceFields();
	};
	private:
		void runScript(int scriptType, int frameCount, const std::string &trimLine);

		bool checkDecimate(int data[]);
		void analyseFF(const std::string &filename);
		void analyse(const std::string &logFileName, int selectEvery, int selectLength, int inputFrames);
		void finishProcessing();
	public:
		void analyse();
		void stop();
}
}
