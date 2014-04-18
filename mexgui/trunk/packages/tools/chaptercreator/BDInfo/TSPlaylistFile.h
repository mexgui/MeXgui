#pragma once

#include "TSStream.h"
#include "TSStreamClip.h"
#include "TSStreamClipFile.h"
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2009  Cinema Squid
// 
// code from http://www.cinemasquid.com/blu-ray/tools/bdinfo
// 
// ****************************************************************************

#undef DEBUG
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace BDInfo
{
	class TSPlaylistFile
	{
	private:
		FileInfo *FileInfo;
	public:
		std::string FileType;
		bool IsInitialized;
		std::string Name;

		std::vector<double> Chapters;

		std::map<unsigned short, TSStream*> Streams;
		std::vector<TSStreamClip*> StreamClips;
		std::vector<std::map<unsigned short, TSStream*>*> AngleStreams;
		int AngleCount;
	  /*
	    public List<TSStream> SortedStreams = 
	        new List<TSStream>();
	    public List<TSVideoStream> VideoStreams = 
	        new List<TSVideoStream>();
	    public List<TSAudioStream> AudioStreams = 
	        new List<TSAudioStream>();
	    public List<TSTextStream> TextStreams = 
	        new List<TSTextStream>();
	    public List<TSGraphicsStream> GraphicsStreams = 
	        new List<TSGraphicsStream>();
	  */
		TSPlaylistFile(FileInfo *fileInfo);

		//public TSPlaylistFile(
		//    string name,
		//    List<TSStreamClip> clips)
		//{
		//    Name = name;
		//    foreach (TSStreamClip clip in clips)
		//    {
		//        TSStreamClip newClip = new TSStreamClip(
		//            clip.StreamFile, clip.StreamClipFile);

		//        newClip.Name = clip.Name;
		//        newClip.TimeIn = clip.TimeIn;
		//        newClip.TimeOut = clip.TimeOut;
		//        newClip.Length = newClip.TimeOut - newClip.TimeIn;
		//        newClip.RelativeTimeIn = TotalLength;
		//        newClip.RelativeTimeOut = newClip.RelativeTimeIn + newClip.Length;
		//        newClip.Chapters.Add(clip.TimeIn);
		//        StreamClips.Add(newClip);

		//        Chapters.Add(newClip.RelativeTimeIn);
		//    }
		//    LoadStreamClips();
		//    IsInitialized = true;
		//}

		virtual std::string ToString();

		const unsigned long long &getFileSize() const;
		const double &getTotalLength() const;

		const double &getAngleLength() const;

		const unsigned long long &getTotalSize() const;

		const unsigned long long &getAngleSize() const;

		const unsigned long long &getTotalBitRate() const;

		const unsigned long long &getAngleBitRate() const;

		void Scan();

		//private void LoadStreamClips()
		//{
		//    foreach (TSStreamClip clip in StreamClips)
		//    {
		//        foreach (TSStream clipStream
		//            in clip.StreamClipFile.Streams.Values)
		//        {
		//            if (!Streams.ContainsKey(clipStream.PID))
		//            {
		//                TSStream stream = clipStream.Clone();
		//                Streams[clipStream.PID] = stream;

		//                if (stream.IsVideoStream)
		//                {
		//                    VideoStreams.Add((TSVideoStream)stream);
		//                }
		//                else if (stream.IsAudioStream)
		//                {
		//                    AudioStreams.Add((TSAudioStream)stream);
		//                }
		//                else if (stream.IsGraphicsStream)
		//                {
		//                    GraphicsStreams.Add((TSGraphicsStream)stream);
		//                }
		//                else if (stream.IsTextStream)
		//                {
		//                    TextStreams.Add((TSTextStream)stream);
		//                }
		//            }
		//        }

		//    //    foreach (TSStream clipStream
		//    //        in clip.StreamFile.Streams.Values)
		//    //    {
		//    //        if (Streams.ContainsKey(clipStream.PID))
		//    //        {
		//    //            TSStream stream = Streams[clipStream.PID];

		//    //            if (stream.StreamType != clipStream.StreamType) continue;

		//    //            if (clipStream.BitRate > stream.BitRate)
		//    //            {
		//    //                stream.BitRate = clipStream.BitRate;
		//    //            }
		//    //            stream.IsVBR = clipStream.IsVBR;

		//    //            if (stream.IsVideoStream &&
		//    //                clipStream.IsVideoStream)
		//    //            {
		//    //                ((TSVideoStream)stream).EncodingProfile =
		//    //                    ((TSVideoStream)clipStream).EncodingProfile;
		//    //            }
		//    //            else if (stream.IsAudioStream &&
		//    //                clipStream.IsAudioStream)
		//    //            {
		//    //                TSAudioStream audioStream = (TSAudioStream)stream;
		//    //                TSAudioStream clipAudioStream = (TSAudioStream)clipStream;

		//    //                if (clipAudioStream.ChannelCount > audioStream.ChannelCount)
		//    //                {
		//    //                    audioStream.ChannelCount = clipAudioStream.ChannelCount;
		//    //                }
		//    //                if (clipAudioStream.LFE > audioStream.LFE)
		//    //                {
		//    //                    audioStream.LFE = clipAudioStream.LFE;
		//    //                }
		//    //                if (clipAudioStream.SampleRate > audioStream.SampleRate)
		//    //                {
		//    //                    audioStream.SampleRate = clipAudioStream.SampleRate;
		//    //                }
		//    //                if (clipAudioStream.BitDepth > audioStream.BitDepth)
		//    //                {
		//    //                    audioStream.BitDepth = clipAudioStream.BitDepth;
		//    //                }
		//    //                if (clipAudioStream.DialNorm < audioStream.DialNorm)
		//    //                {
		//    //                    audioStream.DialNorm = clipAudioStream.DialNorm;
		//    //                }
		//    //                if (clipAudioStream.AudioMode != TSAudioMode.Unknown)
		//    //                {
		//    //                    audioStream.AudioMode = clipAudioStream.AudioMode;
		//    //                }
		//    //                if (clipAudioStream.CoreStream != null &&
		//    //                    audioStream.CoreStream == null)
		//    //                {
		//    //                    audioStream.CoreStream = (TSAudioStream)
		//    //                        clipAudioStream.CoreStream.Clone();
		//    //                }
		//    //            }
		//    //        }
		//    //    }
		//    //}

		//    for (int i = 0; i < AngleCount; i++)
		//    {
		//        AngleStreams.Add(new Dictionary<ushort, TSStream>());
		//    }

		//    VideoStreams.Sort(CompareVideoStreams);
		//    foreach (TSStream stream in VideoStreams)
		//    {
		//        SortedStreams.Add(stream);
		//        for (int i = 0; i < AngleCount; i++)
		//        {
		//            TSStream angleStream = stream.Clone();
		//            angleStream.AngleIndex = i + 1;
		//            AngleStreams[i][angleStream.PID] = angleStream;
		//            SortedStreams.Add(angleStream);
		//        }
		//    }
		//    AudioStreams.Sort(CompareAudioStreams);
		//    foreach (TSStream stream in AudioStreams)
		//    {
		//        SortedStreams.Add(stream);
		//    }
		//    GraphicsStreams.Sort(CompareGraphicsStreams);
		//    foreach (TSStream stream in GraphicsStreams)
		//    {
		//        SortedStreams.Add(stream);
		//    }
		//    TextStreams.Sort(CompareTextStreams);
		//    foreach (TSStream stream in TextStreams)
		//    {
		//        SortedStreams.Add(stream);
		//    }
		//}

		//public void ClearBitrates()
		//{
		//    foreach (TSStreamClip clip in StreamClips)
		//    {
		//        clip.PayloadBytes = 0;
		//        clip.PacketCount = 0;
		//        clip.PacketSeconds = 0;

		//        foreach (TSStream stream in clip.StreamFile.Streams.Values)
		//        {
		//            stream.PayloadBytes = 0;
		//            stream.PacketCount = 0;
		//            stream.PacketSeconds = 0;
		//        }

		//        if (clip.StreamFile != null &&
		//            clip.StreamFile.StreamDiagnostics != null)
		//        {
		//            clip.StreamFile.StreamDiagnostics.Clear();
		//        }
		//    }

		//    foreach (TSStream stream in SortedStreams)
		//    {
		//        stream.PayloadBytes = 0;
		//        stream.PacketCount = 0;
		//        stream.PacketSeconds = 0;
		//    }
		//}

		//public bool IsValid
		//{
		//    get
		//    {
		//        if (!IsInitialized) return false;
		//        if (!BDInfoSettings.FilterPlaylists) return true;
		//        if (TotalLength < 10) return false;

		//        Dictionary<string, TSStreamClip> clips =
		//            new Dictionary<string, TSStreamClip>();
		//        foreach (TSStreamClip clip in StreamClips)
		//        {
		//            if (!clips.ContainsKey(clip.Name))
		//            {
		//                clips[clip.Name] = clip;
		//            }
		//            else return false;
		//        }
		//        return true;
		//    }
		//}

		static int CompareVideoStreams(TSVideoStream *x, TSVideoStream *y);

		static int CompareAudioStreams(TSAudioStream *x, TSAudioStream *y);

		static int CompareTextStreams(TSTextStream *x, TSTextStream *y);

	private:
		static int CompareGraphicsStreams(TSGraphicsStream *x, TSGraphicsStream *y);

		static int GetStreamTypeSortIndex(TSStreamType streamType);

	private:
		void InitializeInstanceFields();
	};
}
