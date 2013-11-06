#pragma once

#include "core/plugins/interfaces/Job.h"
#include "OneClickPostprocessingProperties.h"
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
	/// Container object for OneClickPostProcessing
	/// </summary>
	class OneClickPostProcessingJob : public Job
	{
	private:
		OneClickPostprocessingProperties *postprocessingProperties;
		std::string strIndexFile;

	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public OneClickPostProcessingJob() : this(nullptr, nullptr, nullptr)
		OneClickPostProcessingJob();

		OneClickPostProcessingJob(const std::string &input, const std::string &strIndexFile, OneClickPostprocessingProperties *postprocessingProperties);

		const virtual std::string &getCodecString() const;

		const virtual std::string &getEncodingMode() const;

		/// <summary>
		/// gets / sets the postprocessing properties
		/// and all the postprocessing that has to be done prior to audio encoding
		/// is defined in this property
		/// </summary>
		const OneClickPostprocessingProperties &getPostprocessingProperties() const;
		void setPostprocessingProperties(const OneClickPostprocessingProperties &value);

		const std::string &getIndexFile() const;
		void setIndexFile(const std::string &value);
	};
}
