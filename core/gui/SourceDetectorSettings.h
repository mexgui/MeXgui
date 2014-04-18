#pragma once

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




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Threading;

using namespace MeGUI::core::util;

namespace MeGUI
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[LogByMembers]
	class SourceDetectorSettings
	{
	private:
		double combedFrameMinimum;
		int minimumUsefulSections;
		int hybridThreshold;
		double decimationThreshold;
		int analysePercent;
		int minAnalyseSections;
		int hybridFOPercent;
		double portionThreshold;
		bool portionsAllowed;
		int maxPortions;
		ThreadPriority *priority;

	public:
		SourceDetectorSettings();

		const double &getCombedFrameMinimum() const;
		void setCombedFrameMinimum(const double &value);

		const int &getMinimumUsefulSections() const;
		void setMinimumUsefulSections(const int &value);

		const double &getDecimationThreshold() const;
		void setDecimationThreshold(const double &value);

		const int &getMaxPortions() const;
		void setMaxPortions(const int &value);

		const ThreadPriority &getPriority() const;
		void setPriority(const ThreadPriority &value);

		const bool &getPortionsAllowed() const;
		void setPortionsAllowed(const bool &value);

		const double &getPortionThreshold() const;
		void setPortionThreshold(const double &value);

		const int &getHybridFOPercent() const;
		void setHybridFOPercent(const int &value);

		const int &getMinimumAnalyseSections() const;
		void setMinimumAnalyseSections(const int &value);

		const int &getAnalysePercent() const;
		void setAnalysePercent(const int &value);

		const int &getHybridPercent() const;
		void setHybridPercent(const int &value);
	};
}
