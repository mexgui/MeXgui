#pragma once

#include "core/plugins/interfaces/Job.h"
#include <string>

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
//using namespace System::Xml::Serialization;

namespace MeGUI
{
	/// <summary>
	/// Container object for PgcDemux
	/// </summary>
	class PgcDemuxJob : public Job
	{
	private:
		std::string _strOutputPath;
		int _pgcNumber;

	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public PgcDemuxJob() : this(nullptr, nullptr, 1)
		PgcDemuxJob();

		PgcDemuxJob(const std::string &strInput, const std::string &strOutputPath, int pgcNumber);

		const virtual std::string &getCodecString() const;

		const virtual std::string &getEncodingMode() const;

		const std::string &getOutputPath() const;
		void setOutputPath(const std::string &value);

		const int &getPGCNumber() const;
		void setPGCNumber(const int &value);
	};
}
