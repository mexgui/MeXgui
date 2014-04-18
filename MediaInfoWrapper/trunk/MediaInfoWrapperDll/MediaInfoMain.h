#pragma once

#include "VideoTrack.h"
#include "GeneralTrack.h"
#include "AudioTrack.h"
#include "TextTrack.h"
#include "ChaptersTrack.h"
#include <string>
#include <vector>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;

namespace MediaInfoWrapper
{
	//disables the xml comment warning on compilation
	#pragma warning disable 1591
	enum MediaInfoStreamKind
	{
		General,
		Video,
		Audio,
		Text,
		Chapters,
		Image
	};

	enum MediaInfoInfoKind
	{
		Name,
		Text,
		Measure,
		Options,
		NameText,
		MeasureText,
		Info,
		HowTo
	};

	enum InfoOptions
	{
		ShowInInform,
		Support,
		ShowInSupported,
		TypeOfValue
	};
	#pragma warning restore 1591

	/// <summary>
	/// When called with a proper file target, returns a MediaInfo object filled with list of media tracks containing
	/// every information MediaInfo.dll can collect.
	/// Tracks are accessibles as properties.
	/// </summary>
	class MediaInfo
	{

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll")]
	public:
		__declspec(dllimport) static int MediaInfo_Close(IntPtr Handle);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll")]
//ORIGINAL LINE: internal static extern int MediaInfo_Count_Get(IntPtr Handle, [MarshalAs(UnmanagedType.U4)] MediaInfoStreamKind StreamKind, int StreamNumber);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		__declspec(dllimport) static int MediaInfo_Count_Get(IntPtr Handle, MediaInfoStreamKind StreamKind, int StreamNumber);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll")]
		__declspec(dllimport) static void MediaInfo_Delete(IntPtr Handle);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll", CharSet = CharSet::Unicode)]
//ORIGINAL LINE: internal static extern IntPtr MediaInfo_Get(IntPtr Handle, [MarshalAs(UnmanagedType.U4)] MediaInfoStreamKind StreamKind, uint StreamNumber, string Parameter, [MarshalAs(UnmanagedType.U4)] MediaInfoInfoKind KindOfInfo, [MarshalAs(UnmanagedType.U4)] MediaInfoInfoKind KindOfSearch);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		__declspec(dllimport) static IntPtr MediaInfo_Get(IntPtr Handle, MediaInfoStreamKind StreamKind, unsigned int StreamNumber, const std::string &Parameter, MediaInfoInfoKind KindOfInfo, MediaInfoInfoKind KindOfSearch);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll", CharSet = CharSet::Unicode)]
//ORIGINAL LINE: internal static extern string MediaInfo_GetI(IntPtr Handle, [MarshalAs(UnmanagedType.U4)] MediaInfoStreamKind StreamKind, uint StreamNumber, uint Parameter, [MarshalAs(UnmanagedType.U4)] MediaInfoInfoKind KindOfInfo);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		__declspec(dllimport) static std::string MediaInfo_GetI(IntPtr Handle, MediaInfoStreamKind StreamKind, unsigned int StreamNumber, unsigned int Parameter, MediaInfoInfoKind KindOfInfo);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll", CharSet = CharSet::Unicode)]
//ORIGINAL LINE: internal static extern string MediaInfo_Inform(IntPtr Handle, [MarshalAs(UnmanagedType.U4)] uint Reserved);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		__declspec(dllimport) static std::string MediaInfo_Inform(IntPtr Handle, unsigned int Reserved);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll")]
		__declspec(dllimport) static IntPtr MediaInfo_New();
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll", CharSet = CharSet::Unicode)]
		__declspec(dllimport) static int MediaInfo_Open(IntPtr Handle, const std::string &FileName);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll", CharSet = CharSet::Unicode)]
		__declspec(dllimport) static std::string MediaInfo_Option(IntPtr Handle, const std::string &OptionString, const std::string &Value);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("MediaInfo.dll")]
		__declspec(dllimport) static int MediaInfo_State_Get(IntPtr Handle);


	private:
		std::vector<VideoTrack*> _Video;
		std::vector<GeneralTrack*> _General;
		std::vector<AudioTrack*> _Audio;
		std::vector<TextTrack*> _Text;
		std::vector<ChaptersTrack*> _Chapters;
		int _VideoCount;
		int _GeneralCount;
		int _AudioCount;
		int _TextCount;
		int _ChaptersCount;
		std::string _InfoComplete;
		std::string _InfoStandard;
		std::string _InfoCustom;
		std::string _FileName;

		void* Handle;
	   //public static const string MediaInfoPath="MediaInfo.dll";

		/// <summary>
		/// Constructor :
		/// When called with a proper file target, returns a MediaInfo object filled with list of media tracks containing
		/// every information MediaInfo.dll can collect.
		/// Tracks are accessibles as properties.
		/// </summary>
		/// <param name="path"></param>
	public:
		MediaInfo(const std::string &path);

	private:
		bool disposed;

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
		void Finalize();

	protected:
		const bool &getIsDisposed() const;

		void CheckDisposed();

		/// <summary>Call this one to kill the wrapper, and close his handle to the MediaInfo.dll, you should never need it anyway </summary>
	public:
		~MediaInfo();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="disposing"></param>
	private:
		void Dispose(bool disposing);

	protected:
		virtual void DisposeManagedResources();
		virtual void DisposeUnmanagedResources();

		/// <summary>
		/// Simply checks file presence else throws a FileNotFoundException
		/// </summary>
		bool CheckFileExistence(const std::string &filepath);

	private:
		std::string GetSpecificMediaInfo(MediaInfoStreamKind KindOfStream, int trackindex, const std::string &NameOfParameter);

		void getStreamCount();

		void getAllInfos();

		/// <summary>
		/// More detailled standard information.
		/// </summary>
	public:
		const std::string &getInfoComplete() const;

		/// <summary>
		/// Detailled standard information.
		/// </summary>
		const std::string &getInfoStandard() const;

		/// <summary>
		/// Lists every available property in every track
		/// </summary>
		/// <returns></returns>
		const std::string &getInfoCustom() const;

		/// <summary>
		/// Uses reflection to get every property for every track in a tracklist and get its value.
		/// </summary>
		/// <typeparam name="T1">Type of tracklist, for instance List'VideoTrack'</typeparam>
		/// <param name="L">tracklist, for instance Video</param>
		/// <returns>A formatted string listing every property for every track</returns>
    private:
		template<typename T1>
		std::string ListEveryAvailablePropery(std::vector<T1> &L);

		/// <summary>
		/// Lists media info dll capacities
		/// </summary>
		/// <returns></returns>
	public:
		static std::string Capacities();

		/// <summary>
		/// Lists media info parameter list for MediaInfo_Get
		/// </summary>
		/// <returns></returns>
	private:
		static std::string ParameterList();

		/// <summary>
		/// Lists all supported codecs
		/// </summary>
		/// <returns></returns>
	public:
		static std::string KnownCodecs();

		///<summary> List of all the General streams available in the file, type GeneralTrack[trackindex] to access a specific track</summary>
		const std::vector<GeneralTrack*> &getGeneral() const;

	private:
		void getGeneralInfo();

		///<summary> List of all the Video streams available in the file, type VideoTrack[trackindex] to access a specific track</summary>
	public:
		const std::vector<VideoTrack*> &getVideo() const;

	private:
		void getVideoInfo();

		///<summary> List of all the Audio streams available in the file, type AudioTrack[trackindex] to access a specific track</summary>
	public:
		const std::vector<AudioTrack*> &getAudio() const;

	private:
		void getAudioInfo();

		///<summary> List of all the Text streams available in the file, type TextTrack[trackindex] to access a specific track</summary>
	public:
		const std::vector<TextTrack*> &getText() const;

	private:
		void getTextInfo();

		///<summary> List of all the Chapters streams available in the file, type ChaptersTrack[trackindex] to access a specific track</summary>
	public:
		const std::vector<ChaptersTrack*> &getChapters() const;

	private:
		void getChaptersInfo();
	};
}
