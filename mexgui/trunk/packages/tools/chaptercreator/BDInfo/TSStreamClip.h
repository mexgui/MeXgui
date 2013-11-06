#pragma once

#include "TSStreamClipFile.h"
#include <string>
#include <vector>
#include <cmath>

// ****************************************************************************
// 
// Copyright (C) 2009  Cinema Squid
// 
// code from http://www.cinemasquid.com/blu-ray/tools/bdinfo
// 
// ****************************************************************************

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace BDInfo
{
	class TSStreamClip
	{
	public:
		int AngleIndex;
		std::string Name;
		double TimeIn;
		double TimeOut;
		double RelativeTimeIn;
		double RelativeTimeOut;
		double Length;

		unsigned long long FileSize;
		unsigned long long PayloadBytes;
		unsigned long long PacketCount;
		double PacketSeconds;

		std::vector<double> Chapters;

		//public TSStreamFile StreamFile = null;
		TSStreamClipFile *StreamClipFile;

		TSStreamClip(TSStreamClipFile *streamClipFile);

		const unsigned long long &getPacketSize() const;

		const unsigned long long &getPacketBitRate() const;

		//public bool IsCompatible(TSStreamClip clip)
		//{
		//    foreach (TSStream stream1 in StreamFile.Streams.Values)
		//    {
		//        if (clip.StreamFile.Streams.ContainsKey(stream1.PID))
		//        {
		//            TSStream stream2 = clip.StreamFile.Streams[stream1.PID];
		//            if (stream1.StreamType != stream2.StreamType)
		//            {
		//                return false;
		//            }
		//        }
		//    }
		//    return true;
		//}

	private:
		void InitializeInstanceFields();
	};
}
