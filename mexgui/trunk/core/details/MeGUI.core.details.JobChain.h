#pragma once

#include "core/plugins/interfaces/Job.h"
#include "DependencyChain.h"
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
			class JobChain
			{
			public:
//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
				operator JobChain*(Job *j);


				virtual const TaggedJob &getJobs() const = 0;
				virtual void MakeJobDependOnChain(TaggedJob*) = 0;
				virtual void MakeStartDepend(MakeDependant) = 0;
			};
		}
	}
}
