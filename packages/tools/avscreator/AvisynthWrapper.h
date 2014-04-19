#pragma once

#include "core/gui/MainForm.h"
#include <QString>
#include <stdexcept>

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






//using namespace System::Runtime::InteropServices;

//using namespace System::Runtime::Serialization;

//using namespace System::Text;

//using namespace System::Threading;

namespace MeXgui
{
	enum AviSynthColorspace
	{
		Unknown = 0,
		YV12 = -1610612728,
		RGB24 = +1342177281,
		RGB32 = +1342177282,
		YUY2 = -1610612740,
		I420 = -1610612720,
		IYUV = I420
	};

	class AviSynthException : public ApplicationException
	{
	public:
		AviSynthException(SerializationInfo *info, StreamingContext *context);

		AviSynthException(const QString &message);

		AviSynthException();

		AviSynthException(const QString &message, std::exception &innerException);
	};

	enum AudioSampleType
	{
		Unknown = 0,
		INT8 = 1,
		INT16 = 2,
		INT24 = 4, // Int24 is a very stupid thing to code, but it's supported by some hardware.
		INT32 = 8,
		FLOAT = 16
	};

	class AviSynthScriptEnvironment
	{
	public:
		static QString GetLastError();

		AviSynthScriptEnvironment();

		const IntPtr &getHandle() const;

		AviSynthClip *OpenScriptFile(const QString &filePath, AviSynthColorspace forceColorspace);

		AviSynthClip *ParseScript(const QString &script, AviSynthColorspace forceColorspace);


		AviSynthClip *OpenScriptFile(const QString &filePath);

		AviSynthClip *ParseScript(const QString &script);

		~AviSynthScriptEnvironment();
	};

	/// <summary>
	/// Summary description for AviSynthClip.
	/// </summary>
	class AviSynthClip
	{
	private:
		class EnvRef
		{
		public:
			void* env;
			qint64 refCount;
			object *lockObj;
			int threadID;

			EnvRef(IntPtr e, int threadID);
		};
	private:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential)]
		class AVSDLLVideoInfo
		{
		public:
			int width;
			int height;
			int raten;
			int rated;
			int aspectn;
			int aspectd;
			int interlaced_frame;
			int top_field_first;
			int num_frames;
			AviSynthColorspace pixel_type;

			// Audio
			int audio_samples_per_second;
			AudioSampleType sample_type;
			int nchannels;
			int num_audio_frames;
			qint64 num_audio_samples;
		};

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("AvisynthWrapper", ExactSpelling = true, SetLastError = false, CharSet = CharSet::Ansi)]
	private:
		__declspec(dllimport) static int dimzon_avs_init(IntPtr &avs, const QString &func, const QString &arg, AVSDLLVideoInfo &vi, AviSynthColorspace &originalColorspace, AudioSampleType &originalSampleType, const QString &cs);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("AvisynthWrapper", ExactSpelling = true, SetLastError = false, CharSet = CharSet::Ansi)]
		__declspec(dllimport) static int dimzon_avs_init_2(IntPtr &avs, const QString &func, const QString &arg, AVSDLLVideoInfo &vi, AviSynthColorspace &originalColorspace, AudioSampleType &originalSampleType, const QString &cs);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("AvisynthWrapper", ExactSpelling = true, SetLastError = false, CharSet = CharSet::Ansi)]
		__declspec(dllimport) static int dimzon_avs_destroy(IntPtr &avs);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("AvisynthWrapper", ExactSpelling = true, SetLastError = false, CharSet = CharSet::Ansi)]
//ORIGINAL LINE: private static extern int dimzon_avs_getlasterror(IntPtr avs, [MarshalAs(UnmanagedType.LPStr)] StringBuilder sb, int len);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		__declspec(dllimport) static int dimzon_avs_getlasterror(IntPtr avs, StringBuilder *sb, int len);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("AvisynthWrapper", ExactSpelling = true, SetLastError = false, CharSet = CharSet::Ansi)]
		__declspec(dllimport) static int dimzon_avs_getaframe(IntPtr avs, IntPtr buf, qint64 sampleNo, qint64 sampleCount);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("AvisynthWrapper", ExactSpelling = true, SetLastError = false, CharSet = CharSet::Ansi)]
		__declspec(dllimport) static int dimzon_avs_getvframe(IntPtr avs, IntPtr buf, int stride, int frm);
//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("AvisynthWrapper", ExactSpelling = true, SetLastError = false, CharSet = CharSet::Ansi)]
		__declspec(dllimport) static int dimzon_avs_getintvariable(IntPtr avs, const QString &name, int &val);


		void* _avs;
		AVSDLLVideoInfo _vi;
		AviSynthColorspace _colorSpace;
		AudioSampleType _sampleType;

#if defined(dimzon)


		static Hashtable *_threadHash;

		EnvRef *createNewEnvRef(int threadId);

		void destroyEnvRef(EnvRef *r);

		EnvRef *addRef();

		void Release();

		EnvRef *_avsEnv;


#endif

		QString getLastError();


	public:
		const bool &getHasVideo() const;

		const int &getVideoWidth() const;

		const int &getVideoHeight() const;

		const int &getraten() const;

		const int &getrated() const;

		const int &getaspectn() const;

		const int &getaspectd() const;

		const int &getinterlaced_frame() const;

		const int &gettop_field_first() const;

		const int &getnum_frames() const;

		// Audio
		const bool &getHasAudio() const;

		const int &getAudioSampleRate() const;

		const qint64 &getSamplesCount() const;

		const AudioSampleType &getSampleType() const;

		const short &getChannelsCount() const;

		const AviSynthColorspace &getPixelType() const;

		const AviSynthColorspace &getOriginalColorspace() const;

		const AudioSampleType &getOriginalSampleType() const;


		int GetIntVariable(const QString &variableName, int defaultValue);

		void ReadAudio(IntPtr addr, qint64 offset, int count);

		void ReadAudio(unsigned char buffer, qint64 offset, int count);

		void ReadFrame(IntPtr addr, int stride, int frame);

		AviSynthClip(const QString &func, const QString &arg, AviSynthColorspace forceColorspace, AviSynthScriptEnvironment *env);

	private:
		void cleanup(bool disposing);

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
		void Finalize();

	public:
		~AviSynthClip();
		const short &getBitsPerSample() const;
		const short &getBytesPerSample() const;

		const int &getAvgBytesPerSec() const;

		const qint64 &getAudioSizeInBytes() const;

	};
}
