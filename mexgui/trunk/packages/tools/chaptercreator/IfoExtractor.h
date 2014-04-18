#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
#include "core/util/IFOparser.h"
#include "ChapterCreator.h"
#include "core/gui/FPSChooser.h"
#include <string>
#include <vector>

// ****************************************************************************
// 
// Copyright (C) 2009  Jarrett Vance
// 
// code from http://jvance.com/pages/ChapterGrabber.xhtml
// 
// ****************************************************************************

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;

using namespace MeGUI::core::util;

namespace MeGUI
{
	class IfoExtractor : public ChapterExtractor
	{
	public:
		const virtual std::string *getExtensions() const;

		const virtual bool &getSupportsMultipleStreams() const;

		virtual std::vector<ChapterInfo*> GetStreams(const std::string &ifoFile);

		ChapterInfo *GetChapterInfo(const std::string &location, int titleSetNum);

	private:
		std::vector<Chapter> GetChapters(const std::string &ifoFile, int programChain, TimeSpan *&duration, double &fps);
	};
}
