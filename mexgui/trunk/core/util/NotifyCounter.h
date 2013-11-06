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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			/// <summary>
			/// Keeps track of resources, including how many tasks are accessing it.
			/// The idea is to allow code to temporarily disable certain functions, and re-enable it later.
			/// Furthermore, this is nestable.
			/// 
			/// See FileBar for a usage of this.
			/// </summary>
			class NotifyCounter
			{
			public:
				class AutoCloser
				{
				private:
					NotifyCounter *counter;

				public:
					AutoCloser(NotifyCounter *counter);

					~AutoCloser();
				};
			private:
				unsigned int count;

				/// <summary>
				/// Returns whether this function/resource can be used, ie whether anyone still forbids its use.
				/// </summary>
			public:
				const bool &getReady() const;

				/// <summary>
				/// Add another forbid of its use.
				/// </summary>
				void Increment();

				/// <summary>
				/// Take of one person forbidding its use.
				/// </summary>
				void Decrement();

				/// <summary>
				/// To be used in a using() { } statement, to wrap a Increment/Decrement pair:
				/// using(IDisposable a = myAccessor.Wrap())
				/// {
				///     // This code hase myAccessor disabled.
				/// } // but the curly brace ensures you don't forget to re-enable it
				/// </summary>
				/// <returns></returns>
				IDisposable *Wrap();


			private:
				void InitializeInstanceFields();

public:
				NotifyCounter()
				{
					InitializeInstanceFields();
				}
			};
		}
	}
}
