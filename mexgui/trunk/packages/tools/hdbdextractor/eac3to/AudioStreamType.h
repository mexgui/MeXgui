#pragma once

// ****************************************************************************
// 
// Copyright (C) 2005-2008  Doom9 & al
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

using namespace MeGUI::packages::tools::hdbdextractor;

namespace eac3to
{
	/// <summary>An enumeration of Audio Stream types</summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Flags]
	enum AudioStreamType
	{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("AC3")]
		AC3,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("E-AC3")]
		EAC3,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("DTS")]
		DTS,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("TrueHD")]
		TrueHD,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("RAW")]
		RAW,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("PCM")]
		PCM,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("WAV")]
		WAV,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("Multi-Channel WAV")]
		WAVS,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("MP2")]
		MP2,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("MP3")]
		MP3,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("AAC")]
		AAC,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("FLAC")]
		FLAC,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("TTA1")]
		TTA,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("WAVPACK4")]
		WAVPACK,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StringValue("VORBIS")]
		VORBIS
	};
}
