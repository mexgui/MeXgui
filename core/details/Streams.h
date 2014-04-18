#pragma once

#include "TrackInfo.h"
#include "core/util/FileSize.h"
#include "CodecManager.h"
#include "core/util/VideoUtil.h"
#include <QString>

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

using namespace MeXgui::core::util;

namespace MeXgui
{
	namespace core
	{
		namespace details
		{
			class MuxStream
			{
			private:
				QString _language;
				QString _name;
			public:
				QString path;
				int delay;
				bool bDefaultTrack;
				bool bForceTrack;
				TrackInfo *MuxOnlyInfo;

				MuxStream(const QString &path, const QString &language, const QString &name, int delay, bool bDefaultTrack, bool bForceTrack, TrackInfo *MuxOnlyInfo);

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public MuxStream() : this(nullptr, nullptr, nullptr, 0, false, false, nullptr)
				MuxStream();

				const QString &getlanguage() const;
				void setlanguage(const QString &value);

				const QString &getname() const;
				void setname(const QString &value);
			};

			class BitrateCalculationStream
			{
			public:
				BitrateCalculationStream(const QString &filename);

				QString Filename;
				Nullable<FileSize> Size;
				OutputType *Type;

				virtual void fillInfo();

			};

			class AudioBitrateCalculationStream : public BitrateCalculationStream
			{
			public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AudioBitrateCalculationStream() : this(nullptr)
				AudioBitrateCalculationStream();

				AudioBitrateCalculationStream(const QString &filename);


				AudioType *AType;

				virtual void fillInfo();
			};
		}
	}
}

