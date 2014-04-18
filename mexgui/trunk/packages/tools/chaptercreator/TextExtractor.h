#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
#include "ChapterCreator.h"
#include "core/plugins/interfaces/IMediaFile.h"
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
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace MeGUI
{
	class TextExtractor : public ChapterExtractor
	{
	public:
		const virtual bool &getSupportsMultipleStreams() const;

		const virtual std::string *getExtensions() const;

		virtual std::vector<ChapterInfo*> GetStreams(const std::string &location);
	};
}
