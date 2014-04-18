#pragma once

#include "MuxPath.h"
#include "MuxProvider.h"
#include "core/details/CodecManager.h"
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
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{
	/// <summary>
	/// Checks a mux path for any outright problems that absolutely cannot be tolerated.
	/// </summary>
	/// <param name="muxPath"></param>
	/// <returns>True if a problem is found</returns>
	typedef bool (*CheckMuxPath)(MuxPath *muxPath);
	/// <summary>
	/// Compare two mux paths to find which one is better by some given metric.
	/// </summary>
	/// <param name="x">first mux path</param>
	/// <param name="y">second mux path</param>
	/// <returns>negative if x is better, positive if y is better, 0 if they are equal</returns>
	typedef int (*MuxPathCompare)(MuxPath *x, MuxPath *y);

	/// <summary>
	/// Class to transparently handle specific cases for mux paths. 
	/// By default, the 'best' mux path is chosen according to which is shortest. However, if other
	/// factors come into play, these can be added be creating a new compare method, and registering it.
	/// Registering it with a lower order means it will regarded as more important than ones with higher order.
	/// 
	/// Similarly, this class manages checking for invalid mux paths. No examples spring to mind right now,
	/// but an invalid mux path is something that appears to the mux path generator to be valid, but is in fact
	/// not.
	/// </summary>
	class MuxPathComparer
	{
	private:
		std::vector<PreferencedComparer> comparisonMethods;
		std::vector<CheckMuxPath> checkingMethods;
		bool comparisonSorted;
	public:
		MuxPathComparer();
		void registerComparer(int order, MuxPathCompare method);
		void registerChecker(CheckMuxPath checker);
		/// <summary>
		/// Returns the result of the comparison of the two mux paths according to all the registered muxcomparers
		/// </summary>
		/// <param name="x">The first mux path to compare</param>
		/// <param name="y">The second mux path to compare</param>
		/// <returns>Negative if x is better, positive if y is better, 0 if equally good.</returns>
	private:
		int Compare(MuxPath *x, MuxPath *y);
		/// <summary>
		/// Checks if this mux path is invalid, according to any of the checkers registered.
		/// </summary>
		/// <param name="path"></param>
		/// <returns>false if valid or no checkers found, true if invalid.</returns>
		bool BadMuxPath(MuxPath *path);

	public:
		MuxPath *GetBestMuxPath(std::vector<MuxPath*> &muxPaths);
		/// <summary>
		/// The most primitive comparison method. Says the shorter ones are better
		/// </summary>
		/// <param name="x">The first mux path</param>
		/// <param name="y">The second mux path</param>
		/// <returns>x.Length - y.Length</returns>
		static int CompareByLength(MuxPath *x, MuxPath *y);
		/// <summary>
		/// Compares x to y by counting the number of raw AAC files that are input. Fewer is better,
		/// because the muxers can't pick up whether SBR is signalled if it is in raw aac format
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		static int CompareByAACContainer(MuxPath *x, MuxPath *y);

		static bool CheckForUnsupportedCodecs(MuxPath *x);

		/// <summary>
		/// Checks whether a mux path for AVC-in-MKV uses VFW-based storage (which is bad).
		/// </summary>
		/// <param name="x"></param>
		/// <returns>true if VFW storage is found</returns>
		static bool CheckForVFWMatroska(MuxPath *x);
	private:
		static int Compare(PreferencedComparer a, PreferencedComparer b);

	private:
		void InitializeInstanceFields();
	};

	class PreferencedComparer
	{
	public:
		int preference;
		MuxPathCompare method;
	};
}
