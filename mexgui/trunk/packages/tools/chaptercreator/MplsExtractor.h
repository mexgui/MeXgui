#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
#include "ChapterCreator.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include <string>
#include <vector>
#include <stdexcept>

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
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;

namespace MeGUI
{
	class MplsExtractor : public ChapterExtractor
	{
	public:
		const virtual std::string *getExtensions() const;

		const virtual bool &getSupportsMultipleStreams() const;

		virtual std::vector<ChapterInfo*> GetStreams(const std::string &location);

	private:
		std::vector<Clip*> GetClips(unsigned char data[]);
	};

	class Clip
	{
	public:
		int AngleIndex;
		std::string Name;
		double TimeIn;
		double TimeOut;
		double RelativeTimeIn;
		double RelativeTimeOut;
		double Length;

		unsigned long long FileSize;
		unsigned long long PayloadBytes;
		unsigned long long PacketCount;
		double PacketSeconds;

//C# TO C++ CONVERTER NOTE: The variable Chapters was renamed since it is named the same as a user-defined type:
		std::vector<double> Chapters_Renamed;

	private:
		void InitializeInstanceFields();

public:
		Clip()
		{
			InitializeInstanceFields();
		}
	};
}
