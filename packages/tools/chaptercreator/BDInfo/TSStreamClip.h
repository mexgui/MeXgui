#pragma once

#include "TSStreamClipFile.h"
#include <QString>
#include <QVector>
#include <cmath>

// ****************************************************************************
// 
// Copyright (C) 2009  Cinema Squid
// 
// code from http://www.cinemasquid.com/blu-ray/tools/bdinfo
// 
// ****************************************************************************




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace BDInfo
{
	class TSStreamClip
	{
	public:
		int AngleIndex;
		QString Name;
		double TimeIn;
		double TimeOut;
		double RelativeTimeIn;
		double RelativeTimeOut;
		double Length;

		quint64 FileSize;
		quint64 PayloadBytes;
		quint64 PacketCount;
		double PacketSeconds;

		QVector<double> Chapters;

		//public TSStreamFile StreamFile = null;
		TSStreamClipFile *StreamClipFile;

		TSStreamClip(TSStreamClipFile *streamClipFile);

		const quint64 &getPacketSize() const;

		const quint64 &getPacketBitRate() const;

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
