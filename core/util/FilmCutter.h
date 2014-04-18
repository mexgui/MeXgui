#pragma once

#include <QString>
#include <QVector>
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




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;

//using namespace System::Globalization;



//using namespace System::Text;

//using namespace System::Xml::Serialization;

namespace MeXgui
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
				QVector<CutSection*> cuts;
			public:
				double Framerate;
				TransitionStyle Style;

				const QVector<CutSection*> &getAllCuts() const;
				void setAllCuts(const QVector<CutSection*> &value);

				Cuts(TransitionStyle style);

				bool addSection(CutSection *cut);

				void Clear();

				const quint64 &getTotalFrames() const;

				Cuts *clone();

				void remove(CutSection *cutSection);

			private:
				void InitializeInstanceFields();
			};

			class FilmCutter
			{
			public:
				static void WriteCutsToFile(const QString &filename, Cuts *cuts);

				static Cuts *ReadCutsFromFile(const QString &filename);

				static QString GetCutsScript(Cuts *cuts, bool isAudio);

				static void WriteCutsToScript(const QString &script, Cuts *cuts, bool isAudio);


			private:
				static QString addFades(const QString &p, bool first, bool last, bool isAudio);
			};
		}
	}
}
