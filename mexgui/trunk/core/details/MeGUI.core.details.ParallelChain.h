#pragma once

#include "MeGUI.core.details.JobChain.h"
#include "TaggedJob.h"
#include "DependencyChain.h"
#include <vector>

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
//using namespace System::Text;



namespace MeGUI
{
	namespace core
	{
		namespace details
		{
			class ParallelChain : public JobChain
			{
			public:
//ORIGINAL LINE: public ParallelChain(params JobChain[] chains)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
				ParallelChain(...);

//ORIGINAL LINE: public ParallelChain(params Job[] jobs) : this(DUtil.convert(jobs))
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
				ParallelChain(...);


			private:
//ORIGINAL LINE: private TaggedJob[] jobs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				TaggedJob *jobs;
//ORIGINAL LINE: private JobChain[] chains;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				JobChain *chains;

				void resolve(JobChain chains[]);

			public:
				const TaggedJob *getJobs() const;

				void MakeJobDependOnChain(TaggedJob *j);

				void MakeStartDepend(MakeDependant requiredEnd);
			};
		}
	}
}
