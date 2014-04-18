#pragma once

#include "TSStream.h"
#include <string>
#include <map>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2009  Cinema Squid
// 
// code from http://www.cinemasquid.com/blu-ray/tools/bdinfo
// 
// ****************************************************************************

#undef DEBUG
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

namespace BDInfo
{
	class TSStreamClipFile
	{
	public:
		FileInfo *FileInfo;
		std::string FileType;
		bool IsValid;
		std::string Name;

		std::map<unsigned short, TSStream*> Streams;

		TSStreamClipFile(FileInfo *fileInfo);

		void Scan();

	private:
		void InitializeInstanceFields();
	};
}
