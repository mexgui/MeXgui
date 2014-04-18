#pragma once

#include <string>
#include <vector>

// ****************************************************************************
// 
// Copyright (C) 2009  Cinema Squid
// 
// code from http://www.cinemasquid.com/blu-ray/tools/bdinfo
// 
// ****************************************************************************

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;

namespace BDInfo
{
  class LanguageCodes
  {
public:
	static std::vector<KeyValuePair<std::string, std::string>*> GetTopLanguages();

	static std::vector<KeyValuePair<std::string, std::string>*> GetLanguages();

	static std::string GetName(const std::string &code);

  };
}
