#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
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
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{
	namespace core
	{
		namespace util
		{
			class OverlappingSectionException : public std::exception
			{
			public:
				OverlappingSectionException();
			};

			class CutSection : public IComparable<CutSection*>
			{
			public:
				int startFrame;
				int endFrame;


				int CompareTo(CutSection *other);

			};
			enum TransitionStyle
			{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("No transition")]
				NO_TRANSITION,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Fade")]
				FADE,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Dissolve")]
				DISSOLVE
			};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlInclude(CutSection::typeid)]
			class Cuts
			{
			public:
				void AdaptToFramerate(double newFramerate);

				const int &getMinLength() const;

				Cuts();

			private:
				std::vector<CutSection*> cuts;
			public:
				double Framerate;
				TransitionStyle Style;

				const std::vector<CutSection*> &getAllCuts() const;
				void setAllCuts(const std::vector<CutSection*> &value);

				Cuts(TransitionStyle style);

				bool addSection(CutSection *cut);

				void Clear();

				const unsigned long long &getTotalFrames() const;

				Cuts *clone();

				void remove(CutSection *cutSection);

			private:
				void InitializeInstanceFields();
			};

			class FilmCutter
			{
			public:
				static void WriteCutsToFile(const std::string &filename, Cuts *cuts);

				static Cuts *ReadCutsFromFile(const std::string &filename);

				static std::string GetCutsScript(Cuts *cuts, bool isAudio);

				static void WriteCutsToScript(const std::string &script, Cuts *cuts, bool isAudio);


			private:
				static std::string addFades(const std::string &p, bool first, bool last, bool isAudio);
			};
		}
	}
}
