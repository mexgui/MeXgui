#pragma once

#include "core/plugins/interfaces/Job.h"
#include "MeXgui.JobChain.h"
#include "TaggedJob.h"

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




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{
	namespace core
	{
		namespace details
		{



			class DUtil
			{
			public:
				static JobChain *convert(Job jobs[]);
			};
			typedef void (*MakeDependant)(TaggedJob *j);


			class EmptyJobChain : public JobChain
			{

			public:
				const TaggedJob *getJobs() const;

				void MakeJobDependOnChain(TaggedJob *allowedEnd);

				void MakeStartDepend(MakeDependant requiredEnd);
			};

			class JobDependencyChain : public JobChain
			{
			public:
				TaggedJob *j;
//ORIGINAL LINE: internal TaggedJob[] jobs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				TaggedJob *jobs;

				JobDependencyChain(Job *j);

				const TaggedJob *getJobs() const;

				void MakeJobDependOnChain(TaggedJob *allowedEnd);

				void MakeStartDepend(MakeDependant requiredEnd);
			};



		}
	}
}
