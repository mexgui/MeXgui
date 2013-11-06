#pragma once

#include "MuxProvider.h"
#include "core/details/CodecManager.h"
#include "core/gui/MeGUI.MainForm.h"
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
	/// <summary>
	/// Provides a thin wrapper for a list of MuxPathLegs and adds some extra MuxPath-specific functionality
	/// </summary>
	class MuxPath
	{
	private:
		std::vector<MuxPathLeg> path;
		std::vector<MuxableType*> initialInputTypes;
		ContainerType *targetType;
		bool alwaysMux;

	public:
		const ContainerType &getTargetType() const;
		void setTargetType(const ContainerType &value);

		const std::vector<MuxableType*> &getInitialInputTypes() const;
		void setInitialInputTypes(const std::vector<MuxableType*> &value);

		const int &getLength() const;

		void Add(MuxPathLeg leg);

		MuxPath(ContainerType *targetType);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public MuxPath(IEnumerable<MuxableType> initialInputTypes, ContainerType targetType) : this(targetType)
		MuxPath(IEnumerable<MuxableType*> *initialInputTypes, ContainerType *targetType);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public MuxPath(IEnumerable<MuxableType> initialInputTypes, ContainerType targetType, bool alwaysMux) : this(initialInputTypes, targetType)
		MuxPath(IEnumerable<MuxableType*> *initialInputTypes, ContainerType *targetType, bool alwaysMux);

		MuxPath *Clone();

		IEnumerator<MuxPathLeg> *GetEnumerator();

		MuxPathLeg operator [](int index);

		bool IsCompleted();
	};
}
