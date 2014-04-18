#pragma once

#include "core/plugins/interfaces/Job.h"
#include <string>
#include <vector>

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
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
//using namespace System::Text;

namespace MeGUI
{
	class HDStreamsExJob : public Job
	{
	private:
		std::string featureNb;
		std::string args;
		int inputType;
		std::vector<std::string> source;

	public:
		HDStreamsExJob();

		HDStreamsExJob(std::vector<std::string> &input, const std::string &ouput, const std::string &featureNb, const std::string &args, int inputType);

		const std::string &getFeatureNb() const;
		void setFeatureNb(const std::string &value);

		const std::string &getArgs() const;
		void setArgs(const std::string &value);

		const std::vector<std::string> &getSource() const;
		void setSource(const std::vector<std::string> &value);

		// 1 = Folder as Input
		// 2 = File(s) as Input
		const int &getInputType() const;
		void setInputType(const int &value);

		const virtual std::string &getCodecString() const;

		const virtual std::string &getEncodingMode() const;
	};
}
