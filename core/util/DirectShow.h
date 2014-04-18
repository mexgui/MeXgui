#pragma once

#include <QString>
#include <stdexcept>

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




//using namespace System::Runtime::InteropServices;

//using namespace System::Text;

namespace MeXgui
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential), ComVisible(false)]
	class DsOptInt64
	{
	public:
		DsOptInt64(qint64 Value);
		qint64 Value;
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential), ComVisible(false)]
	class DsOptIntPtr
	{
	public:
		void* Pointer;
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(false)]
	enum PinDirection // PIN_DIRECTION
	{
		Input, // PINDIR_INPUT
		Output // PINDIR_OUTPUT
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(false)]
	class DsHlp
	{
	public:
		static const int OATRUE = -1;
		static const int OAFALSE = 0;

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("quartz.dll", CharSet = CharSet::Auto)]
		__declspec(dllimport) static int AMGetErrorText(int hr, StringBuilder *buf, int max);
	};


//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("56a86891-0ad4-11ce-b03a-0020af0ba770"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IPin
	{
	public:
//ORIGINAL LINE: int Connect([In] IPin pReceivePin, [In, MarshalAs(UnmanagedType.LPStruct)] AMMediaType pmt);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Connect(IPin*, AMMediaType*) = 0;

//ORIGINAL LINE: int ReceiveConnection([In] IPin pReceivePin, [In, MarshalAs(UnmanagedType.LPStruct)] AMMediaType pmt);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int ReceiveConnection(IPin*, AMMediaType*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Disconnect() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int ConnectedTo(IPin*&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int ConnectionMediaType(AMMediaType*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int QueryPinInfo(IntPtr) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int QueryDirection(PinDirection&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int QueryId(QString&) = 0;

//ORIGINAL LINE: int QueryAccept([In, MarshalAs(UnmanagedType.LPStruct)] AMMediaType pmt);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int QueryAccept(AMMediaType*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int EnumMediaTypes(IntPtr) = 0;

//ORIGINAL LINE: int QueryInternalConnections(IntPtr apPin, [In, Out] ref int nPin);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int QueryInternalConnections(IntPtr, int&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int EndOfStream() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int BeginFlush() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int EndFlush() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int NewSegment(qint64, qint64, double) = 0;
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("56a8689f-0ad4-11ce-b03a-0020af0ba770"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IFilterGraph
	{
	public:
//ORIGINAL LINE: int AddFilter([In] IBaseFilter pFilter, [In, MarshalAs(UnmanagedType.LPWStr)] string pName);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int AddFilter(IBaseFilter*, const QString&) = 0;

//ORIGINAL LINE: int RemoveFilter([In] IBaseFilter pFilter);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int RemoveFilter(IBaseFilter*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int EnumFilters(IEnumFilters*&) = 0;

//ORIGINAL LINE: int FindFilterByName([In, MarshalAs(UnmanagedType.LPWStr)] string pName, [Out] out IBaseFilter ppFilter);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int FindFilterByName(const QString&, IBaseFilter*&) = 0;

//ORIGINAL LINE: int ConnectDirect([In] IPin ppinOut, [In] IPin ppinIn, [In, MarshalAs(UnmanagedType.LPStruct)] AMMediaType pmt);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int ConnectDirect(IPin*, IPin*, AMMediaType*) = 0;

//ORIGINAL LINE: int Reconnect([In] IPin ppin);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Reconnect(IPin*) = 0;

//ORIGINAL LINE: int Disconnect([In] IPin ppin);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Disconnect(IPin*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetDefaultSyncSource() = 0;

	};

	// ---------------------------------------------------------------------------------------

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("0000010c-0000-0000-C000-000000000046"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IPersist
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetClassID(Guid*&) = 0;
	};

	// ---------------------------------------------------------------------------------------

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("56a86899-0ad4-11ce-b03a-0020af0ba770"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IMediaFilter
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetClassID(Guid*&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Stop() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Pause() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Run(qint64) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetState(int, int&) = 0;

//ORIGINAL LINE: int SetSyncSource([In] IReferenceClock pClock);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetSyncSource(IReferenceClock*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetSyncSource(IReferenceClock*&) = 0;
	};

	// ---------------------------------------------------------------------------------------

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("56a86895-0ad4-11ce-b03a-0020af0ba770"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IBaseFilter
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetClassID(Guid*&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Stop() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Pause() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Run(qint64) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetState(int, int&) = 0;

//ORIGINAL LINE: int SetSyncSource([In] IReferenceClock pClock);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetSyncSource(IReferenceClock*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetSyncSource(IReferenceClock*&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int EnumPins(IEnumPins*&) = 0;

//ORIGINAL LINE: int FindPin([In, MarshalAs(UnmanagedType.LPWStr)] string Id, [Out] out IPin ppPin);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int FindPin(const QString&, IPin*&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int QueryFilterInfo(FilterInfo*) = 0;

//ORIGINAL LINE: int JoinFilterGraph([In] IFilterGraph pGraph, [In, MarshalAs(UnmanagedType.LPWStr)] string pName);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int JoinFilterGraph(IFilterGraph*, const QString&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int QueryVendorInfo(QString&) = 0;
	};


//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential, CharSet = CharSet::Unicode), ComVisible(false)]
	class FilterInfo //  FILTER_INFO
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::ByValTStr, SizeConst = 128)]
		QString achName;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::IUnknown)]
		object *pUnk;
	};

	// ---------------------------------------------------------------------------------------

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("36b73880-c2c8-11cf-8b46-00805f6cef60"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IMediaSeeking
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetCapabilities(SeekingCapabilities&) = 0;

//ORIGINAL LINE: int CheckCapabilities([In, Out] ref SeekingCapabilities pCapabilities);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int CheckCapabilities(SeekingCapabilities&) = 0;

//ORIGINAL LINE: int IsFormatSupported([In] ref Guid pFormat);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int IsFormatSupported(Guid*&) = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int QueryPreferredFormat(Guid*&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetTimeFormat(Guid*&) = 0;
//ORIGINAL LINE: int IsUsingTimeFormat([In] ref Guid pFormat);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int IsUsingTimeFormat(Guid*&) = 0;
//ORIGINAL LINE: int SetTimeFormat([In] ref Guid pFormat);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetTimeFormat(Guid*&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetDuration(qint64&) = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetStopPosition(qint64&) = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetCurrentPosition(qint64&) = 0;

//ORIGINAL LINE: int ConvertTimeFormat(out long pTarget, [In] ref Guid pTargetFormat, long Source, [In] ref Guid pSourceFormat);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int ConvertTimeFormat(qint64&, Guid*&, qint64, Guid*&) = 0;

//ORIGINAL LINE: int SetPositions([In, Out, MarshalAs(UnmanagedType.LPStruct)] DsOptInt64 pCurrent, SeekingFlags dwCurrentFlags, [In, Out, MarshalAs(UnmanagedType.LPStruct)] DsOptInt64 pStop, SeekingFlags dwStopFlags);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetPositions(DsOptInt64*, SeekingFlags, DsOptInt64*, SeekingFlags) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetPositions(qint64&, qint64&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetAvailable(qint64&, qint64&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetRate(double) = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetRate(double&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetPreroll(qint64&) = 0;
	};


//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Flags, ComVisible(false)]
	enum SeekingCapabilities // AM_SEEKING_SeekingCapabilities AM_SEEKING_SEEKING_CAPABILITIES
	{
		CanSeekAbsolute = 0x001,
		CanSeekForwards = 0x002,
		CanSeekBackwards = 0x004,
		CanGetCurrentPos = 0x008,
		CanGetStopPos = 0x010,
		CanGetDuration = 0x020,
		CanPlayBackwards = 0x040,
		CanDoSegments = 0x080,
		Source = 0x100 // Doesn't pass thru used to count segment ends
	};


//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Flags, ComVisible(false)]
	enum SeekingFlags // AM_SEEKING_SeekingFlags AM_SEEKING_SEEKING_FLAGS
	{
		NoPositioning = 0x00, // No change
		AbsolutePositioning = 0x01, // Position is supplied and is absolute
		RelativePositioning = 0x02, // Position is supplied and is relative
		IncrementalPositioning = 0x03, // (Stop) position relative to current, useful for seeking when paused (use +1)
		PositioningBitsMask = 0x03, // Useful mask
		SeekToKeyFrame = 0x04, // Just seek to key frame (performance gain)
		ReturnTime = 0x08, // Plug the media time equivalents back into the supplied LONGLONGs
		Segment = 0x10, // At end just do EC_ENDOFSEGMENT, don't do EndOfStream
		NoFlush = 0x20 // Don't flush
	};

	// ---------------------------------------------------------------------------------------

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("56a86897-0ad4-11ce-b03a-0020af0ba770"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IReferenceClock
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetTime(qint64&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int AdviseTime(qint64, qint64, IntPtr, int&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int AdvisePeriodic(qint64, qint64, IntPtr, int&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Unadvise(int) = 0;
	};

	// ---------------------------------------------------------------------------------------

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("56a86893-0ad4-11ce-b03a-0020af0ba770"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IEnumFilters
	{
	public:
//ORIGINAL LINE: int Next([In] int cFilters, [Out, MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)] out IBaseFilter[] ppFilter, [Out] out int pcFetched);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Next(int, IBaseFilter[] , int&) = 0;

//ORIGINAL LINE: int Skip([In] int cFilters);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Skip(int) = 0;
		virtual void Reset() = 0;
		virtual void Clone(IEnumFilters*&) = 0;
	};


	// ---------------------------------------------------------------------------------------

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("56a86892-0ad4-11ce-b03a-0020af0ba770"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IEnumPins
	{
	public:
//ORIGINAL LINE: int Next([In] int cPins, [Out, MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)] out IPin[] ppPins, [Out] out int pcFetched);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Next(int, IPin[] , int&) = 0;

//ORIGINAL LINE: int Skip([In] int cPins);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Skip(int) = 0;
		virtual void Reset() = 0;
		virtual void Clone(IEnumPins*&) = 0;
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential), ComVisible(false)]
	class AMMediaType //  AM_MEDIA_TYPE
	{
	public:
		Guid *majorType;
		Guid *subType;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::Bool)]
		bool fixedSizeSamples;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::Bool)]
		bool temporalCompression;
		int sampleSize;
		Guid *formatType;
		void* unkPtr;
		int formatSize;
		void* formatPtr;
	};

	// ---------------------------------------------------------------------------------------

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("56a8689a-0ad4-11ce-b03a-0020af0ba770"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IMediaSample
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetPointer(IntPtr&) = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetSize() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetTime(qint64&, qint64&) = 0;

//ORIGINAL LINE: int SetTime([In, MarshalAs(UnmanagedType.LPStruct)] DsOptInt64 pTimeStart, [In, MarshalAs(UnmanagedType.LPStruct)] DsOptInt64 pTimeEnd);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetTime(DsOptInt64*, DsOptInt64*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int IsSyncPoint() = 0;
//ORIGINAL LINE: int SetSyncPoint([In, MarshalAs(UnmanagedType.Bool)] bool bIsSyncPoint);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetSyncPoint(bool) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int IsPreroll() = 0;
//ORIGINAL LINE: int SetPreroll([In, MarshalAs(UnmanagedType.Bool)] bool bIsPreroll);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetPreroll(bool) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetActualDataLength() = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetActualDataLength(int) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetMediaType(AMMediaType*&) = 0;

//ORIGINAL LINE: int SetMediaType([In, MarshalAs(UnmanagedType.LPStruct)] AMMediaType pMediaType);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetMediaType(AMMediaType*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int IsDiscontinuity() = 0;
//ORIGINAL LINE: int SetDiscontinuity([In, MarshalAs(UnmanagedType.Bool)] bool bDiscontinuity);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetDiscontinuity(bool) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetMediaTime(qint64&, qint64&) = 0;

//ORIGINAL LINE: int SetMediaTime([In, MarshalAs(UnmanagedType.LPStruct)] DsOptInt64 pTimeStart, [In, MarshalAs(UnmanagedType.LPStruct)] DsOptInt64 pTimeEnd);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetMediaTime(DsOptInt64*, DsOptInt64*) = 0;
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("93E5A4E0-2D50-11d2-ABFA-00A0C9C6E38D"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class ICaptureGraphBuilder2
	{
	public:
//ORIGINAL LINE: int SetFiltergraph([In] IGraphBuilder pfg);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetFiltergraph(IGraphBuilder*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int GetFiltergraph(IGraphBuilder*&) = 0;

//ORIGINAL LINE: int FindInterface([In] ref Guid pCategory, [In] ref Guid pType, [In] IBaseFilter pbf, [In] ref Guid riid, [Out, MarshalAs(UnmanagedType.IUnknown)] out object ppint);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int FindInterface(Guid*&, Guid*&, IBaseFilter*, Guid*&, object*&) = 0;

//ORIGINAL LINE: int RenderStream([In] ref Guid pCategory, [In] ref Guid pType, [In, MarshalAs(UnmanagedType.IUnknown)] object pSource, [In] IBaseFilter pfCompressor, [In] IBaseFilter pfRenderer);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int RenderStream(Guid*&, Guid*&, object*, IBaseFilter*, IBaseFilter*) = 0;

//ORIGINAL LINE: int ControlStream([In] ref Guid pCategory, [In] ref Guid pType, [In] IBaseFilter pFilter, [In] IntPtr pstart, [In] IntPtr pstop, [In] short wStartCookie, [In] short wStopCookie);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int ControlStream(Guid*&, Guid*&, IBaseFilter*, IntPtr, IntPtr, short, short) = 0;

//ORIGINAL LINE: int AllocCapFile([In, MarshalAs(UnmanagedType.LPWStr)] string lpstrFile, [In] long dwlSize);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int AllocCapFile(const QString&, qint64) = 0;

//ORIGINAL LINE: int FindPin([In] object pSource, [In] int pindir, [In] ref Guid pCategory, [In] ref Guid pType, [In, MarshalAs(UnmanagedType.Bool)] bool fUnconnected, [In] int num, [Out] out IPin ppPin);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int FindPin(object*, int, Guid*&, Guid*&, bool, int, IPin*&) = 0;
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(true), ComImport, Guid("56a868a9-0ad4-11ce-b03a-0020af0ba770"), InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	class IGraphBuilder
	{
	public:
//ORIGINAL LINE: int AddFilter([In] IBaseFilter pFilter, [In, MarshalAs(UnmanagedType.LPWStr)] string pName);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int AddFilter(IBaseFilter*, const QString&) = 0;

//ORIGINAL LINE: int RemoveFilter([In] IBaseFilter pFilter);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int RemoveFilter(IBaseFilter*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int EnumFilters(IEnumFilters*&) = 0;

//ORIGINAL LINE: int FindFilterByName([In, MarshalAs(UnmanagedType.LPWStr)] string pName, [Out] out IBaseFilter ppFilter);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int FindFilterByName(const QString&, IBaseFilter*&) = 0;

//ORIGINAL LINE: int ConnectDirect([In] IPin ppinOut, [In] IPin ppinIn, [In, MarshalAs(UnmanagedType.LPStruct)] AMMediaType pmt);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int ConnectDirect(IPin*, IPin*, AMMediaType*) = 0;

//ORIGINAL LINE: int Reconnect([In] IPin ppin);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Reconnect(IPin*) = 0;

//ORIGINAL LINE: int Disconnect([In] IPin ppin);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Disconnect(IPin*) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetDefaultSyncSource() = 0;

//ORIGINAL LINE: int Connect([In] IPin ppinOut, [In] IPin ppinIn);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Connect(IPin*, IPin*) = 0;

//ORIGINAL LINE: int Render([In] IPin ppinOut);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Render(IPin*) = 0;

//ORIGINAL LINE: int RenderFile([In, MarshalAs(UnmanagedType.LPWStr)] string lpcwstrFile, [In, MarshalAs(UnmanagedType.LPWStr)] string lpcwstrPlayList);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int RenderFile(const QString&, const QString&) = 0;

//ORIGINAL LINE: int AddSourceFilter([In, MarshalAs(UnmanagedType.LPWStr)] string lpcwstrFileName, [In, MarshalAs(UnmanagedType.LPWStr)] string lpcwstrFilterName, [Out] out IBaseFilter ppFilter);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int AddSourceFilter(const QString&, const QString&, IBaseFilter*&) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int SetLogFile(IntPtr) = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int Abort() = 0;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual int ShouldOperationContinue() = 0;
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComVisible(false)]
	class Clsid // uuids.h  :  CLSID_*
	{
		/// <summary> CLSID_SystemDeviceEnum for ICreateDevEnum </summary>
	public:
		static Guid *const SystemDeviceEnum;

		/// <summary> CLSID_FilterGraph, filter Graph </summary>
		static Guid *const FilterGraph;

		/// <summary> CLSID_CaptureGraphBuilder2, new Capture graph building </summary>
		static Guid *const CaptureGraphBuilder2;

		/// <summary> CLSID_SampleGrabber, Sample Grabber filter </summary>
		static Guid *const SampleGrabber;

		/// <summary> CLSID_DvdGraphBuilder,  DVD graph builder </summary>
		static Guid *const DvdGraphBuilder;

	};

	class DirectShow
	{
	private:
		IGraphBuilder *graphBuilder;

		/// <summary>
		/// Check whether DirectShow can render a video file
		/// </summary>
		/// <param name="fileName"></param>
		/// <returns>true if graphedit can render the input</returns>
	public:
		bool checkRender(const QString &fileName);
	};
}
