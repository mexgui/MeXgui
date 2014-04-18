#pragma once

#include "core/util/GenericRegisterer.h"
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




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Xml::Serialization;

namespace MeXgui
{
	/// <summary>
	/// Dummy interface to avoid some runtime type errors. This should be implemented by VideoCodec and AudioCodec
	/// </summary>
	class ICodec
	{
	};

	class VideoCodec : public ICodec, IIDable
	{
	private:
		QString id;
	public:
		const QString &getID() const;
		VideoCodec(const QString &id);
		static VideoCodec *const ASP;
		static VideoCodec *const AVC;
		static VideoCodec *const HFYU;
		static VideoCodec *const VC1;
		static VideoCodec *const MPEG2;
	};
	class AudioCodec : public ICodec, IIDable
	{
	private:
		QString id;
	public:
		const QString &getID() const;
		AudioCodec(const QString &id);
		static AudioCodec *const MP3;
		static AudioCodec *const AAC;
		static AudioCodec *const VORBIS;
		static AudioCodec *const DTS;
		static AudioCodec *const AC3;
		static AudioCodec *const MP2;
		static AudioCodec *const WAV;
		static AudioCodec *const PCM;
		static AudioCodec *const EAC3;
		static AudioCodec *const THD;
		static AudioCodec *const DTSHD;
		static AudioCodec *const DTSMA;
		static AudioCodec *const FLAC;
		static AudioCodec *const OPUS;
	};
	class SubtitleCodec : public ICodec, IIDable
	{
	private:
		QString id;
	public:
		const QString &getID() const;
		SubtitleCodec(const QString &id);
		static SubtitleCodec *const TEXT;
		static SubtitleCodec *const IMAGE;
	};
	/// <summary>
	/// Dummy interface so runtime typing problems don't arise, and we can avoid ugly (object) casts
	/// </summary>
	class IEncoderType
	{
	public:
		virtual const ICodec &getCodec() const = 0;
	};

	class VideoEncoderType : public IEncoderType, IIDable
	{
	private:
		QString id;
		VideoCodec *codec;
	public:
		const VideoCodec &getVCodec() const;
		const ICodec &getCodec() const;

		const QString &getID() const;
		VideoEncoderType(const QString &id, VideoCodec *codec);

		virtual QString ToString();
		static VideoEncoderType *const XVID;
		static VideoEncoderType *const X264;
		static VideoEncoderType *const HFYU;
	};

	class AudioEncoderType : public IEncoderType, IIDable
	{
	private:
		QString id;
		AudioCodec *codec;
	public:
		const ICodec &getCodec() const;
		const AudioCodec &getACodec() const;
		const QString &getID() const;
		AudioEncoderType(const QString &id, AudioCodec *codec);
		static AudioEncoderType *const LAME;
		static AudioEncoderType *const NAAC;
		static AudioEncoderType *const VORBIS;
		static AudioEncoderType *const FFAC3;
		static AudioEncoderType *const FFMP2;
		static AudioEncoderType *const AFTEN;
		static AudioEncoderType *const FLAC;
		static AudioEncoderType *const QAAC;
		static AudioEncoderType *const OPUS;
	};

	class CodecManager
	{
	public:
		static GenericRegisterer<VideoCodec*> *VideoCodecs;
		static GenericRegisterer<AudioCodec*> *AudioCodecs;
		static GenericRegisterer<VideoEncoderType*> *VideoEncoderTypes;
		static GenericRegisterer<AudioEncoderType*> *AudioEncoderTypes;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
        CodecManager();
	};

	class VideoType : public OutputType
	{
	private:
//ORIGINAL LINE: private VideoCodec[] supportedCodecs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		VideoCodec *supportedCodecs;

	public:
		const VideoCodec *getSupportedCodecs() const;

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public VideoType(string name, string filterName, string extension, ContainerType containerType, VideoCodec supportedCodec) : this(name, filterName, extension, containerType, new VideoCodec[] { supportedCodec })
		VideoType(const QString &name, const QString &filterName, const QString &extension, MeXgui::ContainerType *containerType, VideoCodec *supportedCodec);

		VideoType(const QString &name, const QString &filterName, const QString &extension, MeXgui::ContainerType *containerType, VideoCodec supportedCodecs[]);
		static VideoType *const MP4;
		static VideoType *const RAWASP;
		static VideoType *const RAWAVC;
		static VideoType *const RAWAVC2;
		static VideoType *const MKV;
		static VideoType *const AVI;
		static VideoType *const MPEG2;
		static VideoType *const VC1;
		static VideoType *const M2TS;
    };

    class AudioType : public OutputType
	{
	private:
//ORIGINAL LINE: private AudioCodec[] supportedCodecs;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		AudioCodec *supportedCodecs;

	public:
		const AudioCodec *getSupportedCodecs() const;

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public AudioType(string name, string filterName, string extension, ContainerType containerType, AudioCodec supportedCodec) : this(name, filterName, extension, containerType, new AudioCodec[] { supportedCodec })
		AudioType(const QString &name, const QString &filterName, const QString &extension, MeXgui::ContainerType *containerType, AudioCodec *supportedCodec);

		AudioType(const QString &name, const QString &filterName, const QString &extension, MeXgui::ContainerType *containerType, AudioCodec supportedCodecs[]);
		static AudioType *const MP4AAC;
		static AudioType *const M4A;
		static AudioType *const RAWAAC;
		static AudioType *const MP3;
		static AudioType *const VORBIS;
		static AudioType *const AC3;
		static AudioType *const MP2;
		static AudioType *const DTS;
		static AudioType *const WAV;
		static AudioType *const PCM;
		static AudioType *const CBRMP3;
		static AudioType *const VBRMP3;
		static AudioType *const EAC3;
		static AudioType *const THD;
		static AudioType *const DTSHD;
		static AudioType *const DTSMA;
		static AudioType *const FLAC;
		static AudioType *const AVS;
		static AudioType *const OPUS;
	};
	class SubtitleType : public OutputType
	{
	public:
		SubtitleType(const QString &name, const QString &filterName, const QString &extension, MeXgui::ContainerType *containerType);
		static SubtitleType *const SSA;
		static SubtitleType *const ASS;
		static SubtitleType *const SUBRIP;
		static SubtitleType *const BDSUP;
		static SubtitleType *const VOBSUB;
		static SubtitleType *const TTXT;
	};
	class ChapterType : public OutputType
	{
	public:
		ChapterType(const QString &name, const QString &filterName, const QString &extension, MeXgui::ContainerType *containerType);
		static ChapterType *const OGG_TXT;
		static ChapterType *const MKV_XML;
	};
	class DeviceType : public OutputType
	{
	public:
		DeviceType(const QString &name, const QString &filterName, const QString &extension, MeXgui::ContainerType *containerType);
		static DeviceType *const APPLETV;
		static DeviceType *const IPAD;
		static DeviceType *const IPOD;
		static DeviceType *const IPHONE;
		static DeviceType *const ISMA;
		static DeviceType *const PSP;
		static DeviceType *const BD;
		static DeviceType *const AVCHD;
		static DeviceType *const PC;
	};

    class ContainerType : public OutputFileType
	{
	public:
		ContainerType(const QString &name, const QString &filterName, const QString &extension);
		static ContainerType *const MP4;
		static ContainerType *const MKV;
		static ContainerType *const AVI;
		static ContainerType *const M2TS;
		static const ContainerType Containers[4];

		static ContainerType *ByName(const QString &id);
	};
	class ContainerManager
	{
	public:
		static GenericRegisterer<VideoType*> *VideoTypes;
		static GenericRegisterer<AudioType*> *AudioTypes;
		static GenericRegisterer<SubtitleType*> *SubtitleTypes;
		static GenericRegisterer<ContainerType*> *ContainerTypes;
		static GenericRegisterer<ChapterType*> *ChapterTypes;
		static GenericRegisterer<DeviceType*> *DeviceTypes;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static ContainerManager();
	};

	class OutputFileType : public IIDable
	{
	public:
		OutputFileType(const QString &name, const QString &filterName, const QString &extension);

		const QString &getID() const;

	private:
		QString name, filterName, extension;
		/// <summary>
		/// used to display the output type in dropdowns
		/// </summary>
		/// <returns></returns>
	public:
		virtual QString ToString();
		const QString &getOutputFilter() const;
		/// <summary>
		/// gets a valid filter string for file dialogs based on the known extension
		/// </summary>
		/// <returns></returns>
		const QString &getOutputFilterString() const;
		/// <summary>
		/// gets the extension for this file type
		/// </summary>
		const QString &getExtension() const;
	};

	class OutputType : public OutputFileType
	{
	public:
		OutputType(const QString &name, const QString &filterName, const QString &extension, MeXgui::ContainerType *containerType);

	private:
		MeXgui::ContainerType *containerType;
	public:
		const MeXgui::ContainerType &getContainerType() const;
	};
}
