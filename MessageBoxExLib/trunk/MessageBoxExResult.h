#pragma once

#include<Qt>
#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace Utils
{
	namespace MessageBoxExLib
	{
		/// <summary>
		/// Standard MessageBoxEx results
		/// </summary>
		class MessageBoxExResult
		{
		public:
			static const std::string Ok;
			static const std::string Cancel;
			static const std::string Yes;
			static const std::string No;
			static const std::string Abort;
			static const std::string Retry;
			static const std::string Ignore;
			static const std::string Timeout;
		};
	}
}
