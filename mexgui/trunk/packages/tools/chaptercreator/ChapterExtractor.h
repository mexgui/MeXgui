#pragma once

#include "ChapterInfo.h"
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
//using namespace System::Security::Cryptography;

namespace MeGUI
{
	class ChapterExtractor
	{
	public:
		virtual const std::string &getExtensions() const = 0;
		const virtual bool &getSupportsMultipleStreams() const;
		virtual std::vector<ChapterInfo*> GetStreams(const std::string&) = 0;

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler<ProgramChainArg> StreamDetected;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler<ProgramChainArg> ChaptersLoaded;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler ExtractionComplete;

		static std::string ComputeMD5Sum(const std::string &path);

	protected:
		void OnExtractionComplete();

		void OnStreamDetected(ChapterInfo *pgc);

		void OnChaptersLoaded(ChapterInfo *pgc);
	};

	class ProgramChainArg : public EventArgs
	{
	private:
		ChapterInfo *privateProgramChain;
	public:
		const ChapterInfo &getProgramChain() const;
		void setProgramChain(const ChapterInfo &value);
	};
}
