#include "CodecManager.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{

	const std::string &VideoCodec::getID() const
	{
		return id;
	}

	VideoCodec::VideoCodec(const std::string &id)
	{
		this->id = id;
	}

VideoCodec *const VideoCodec::ASP = new VideoCodec("ASP");
VideoCodec *const VideoCodec::AVC = new VideoCodec("AVC");
VideoCodec *const VideoCodec::HFYU = new VideoCodec("HFYU");
VideoCodec *const VideoCodec::VC1 = new VideoCodec("VC1");
VideoCodec *const VideoCodec::MPEG2 = new VideoCodec("MPEG2");

	const std::string &AudioCodec::getID() const
	{
		return id;
	}

	AudioCodec::AudioCodec(const std::string &id)
	{
		this->id = id;
	}

AudioCodec *const AudioCodec::MP3 = new AudioCodec("MP3");
AudioCodec *const AudioCodec::AAC = new AudioCodec("AAC");
AudioCodec *const AudioCodec::VORBIS = new AudioCodec("VORBIS");
AudioCodec *const AudioCodec::DTS = new AudioCodec("DTS");
AudioCodec *const AudioCodec::AC3 = new AudioCodec("AC-3");
AudioCodec *const AudioCodec::MP2 = new AudioCodec("MP2");
AudioCodec *const AudioCodec::WAV = new AudioCodec("WAV");
AudioCodec *const AudioCodec::PCM = new AudioCodec("PCM");
AudioCodec *const AudioCodec::EAC3 = new AudioCodec("EAC3");
AudioCodec *const AudioCodec::THD = new AudioCodec("THD");
AudioCodec *const AudioCodec::DTSHD = new AudioCodec("DTSHD");
AudioCodec *const AudioCodec::DTSMA = new AudioCodec("DTSMA");
AudioCodec *const AudioCodec::FLAC = new AudioCodec("FLAC");
AudioCodec *const AudioCodec::OPUS = new AudioCodec("OPUS");

	const std::string &SubtitleCodec::getID() const
	{
		return id;
	}

	SubtitleCodec::SubtitleCodec(const std::string &id)
	{
		this->id = id;
	}

SubtitleCodec *const SubtitleCodec::TEXT = new SubtitleCodec("TEXT");
SubtitleCodec *const SubtitleCodec::IMAGE = new SubtitleCodec("IMAGE");

	const VideoCodec &VideoEncoderType::getVCodec() const
	{
		return codec;
	}

	const ICodec &VideoEncoderType::getCodec() const
	{
		return getVCodec();
	}

	const std::string &VideoEncoderType::getID() const
	{
		return id;
	}

	VideoEncoderType::VideoEncoderType(const std::string &id, VideoCodec *codec)
	{
		this->id = id;
		this->codec = codec;
	}

	std::string VideoEncoderType::ToString()
	{
		return getID();
	}

VideoEncoderType *const VideoEncoderType::XVID = new VideoEncoderType("Xvid", VideoCodec::ASP);
VideoEncoderType *const VideoEncoderType::X264 = new VideoEncoderType("x264", VideoCodec::AVC);
VideoEncoderType *const VideoEncoderType::HFYU = new VideoEncoderType("Huffyuv", VideoCodec::HFYU);

	const ICodec &AudioEncoderType::getCodec() const
	{
		return getACodec();
	}

	const AudioCodec &AudioEncoderType::getACodec() const
	{
		return codec;
	}

	const std::string &AudioEncoderType::getID() const
	{
		return id;
	}

	AudioEncoderType::AudioEncoderType(const std::string &id, AudioCodec *codec)
	{
		this->id = id;
		this->codec = codec;
	}

AudioEncoderType *const AudioEncoderType::LAME = new AudioEncoderType("LAME", AudioCodec::MP3);
AudioEncoderType *const AudioEncoderType::NAAC = new AudioEncoderType("NAAC", AudioCodec::AAC);
AudioEncoderType *const AudioEncoderType::VORBIS = new AudioEncoderType("VORBIS", AudioCodec::VORBIS);
AudioEncoderType *const AudioEncoderType::FFAC3 = new AudioEncoderType("FFAC3", AudioCodec::AC3);
AudioEncoderType *const AudioEncoderType::FFMP2 = new AudioEncoderType("FFMP2", AudioCodec::MP2);
AudioEncoderType *const AudioEncoderType::AFTEN = new AudioEncoderType("AFTEN", AudioCodec::AC3);
AudioEncoderType *const AudioEncoderType::FLAC = new AudioEncoderType("FLAC", AudioCodec::FLAC);
AudioEncoderType *const AudioEncoderType::QAAC = new AudioEncoderType("QAAC", AudioCodec::AAC);
AudioEncoderType *const AudioEncoderType::OPUS = new AudioEncoderType("OPUS", AudioCodec::OPUS);
GenericRegisterer<VideoCodec*> *CodecManager::VideoCodecs = new GenericRegisterer<VideoCodec*>();
GenericRegisterer<AudioCodec*> *CodecManager::AudioCodecs = new GenericRegisterer<AudioCodec*>();
GenericRegisterer<VideoEncoderType*> *CodecManager::VideoEncoderTypes = new GenericRegisterer<VideoEncoderType*>();
GenericRegisterer<AudioEncoderType*> *CodecManager::AudioEncoderTypes = new GenericRegisterer<AudioEncoderType*>();

	CodecManager::CodecManager()
	{
		if (!(VideoCodecs->Register(VideoCodec::ASP) && VideoCodecs->Register(VideoCodec::AVC) && VideoCodecs->Register(VideoCodec::HFYU) && VideoCodecs->Register(VideoCodec::MPEG2) && VideoCodecs->Register(VideoCodec::VC1)))
			throw std::exception("Failed to register a standard video codec");
		if (!(AudioCodecs->Register(AudioCodec::AAC) && AudioCodecs->Register(AudioCodec::AC3) && AudioCodecs->Register(AudioCodec::DTS) && AudioCodecs->Register(AudioCodec::MP2) && AudioCodecs->Register(AudioCodec::MP3) && AudioCodecs->Register(AudioCodec::VORBIS) && AudioCodecs->Register(AudioCodec::DTSHD) && AudioCodecs->Register(AudioCodec::DTSMA) && AudioCodecs->Register(AudioCodec::EAC3) && AudioCodecs->Register(AudioCodec::PCM) && AudioCodecs->Register(AudioCodec::THD) && AudioCodecs->Register(AudioCodec::FLAC) && AudioCodecs->Register(AudioCodec::WAV)))
			throw std::exception("Failed to register a standard audio codec");
		if (!(VideoEncoderTypes->Register(VideoEncoderType::HFYU) && VideoEncoderTypes->Register(VideoEncoderType::X264) && VideoEncoderTypes->Register(VideoEncoderType::XVID)))
			throw std::exception("Failed to register a standard video encoder type");
		if (!(AudioEncoderTypes->Register(AudioEncoderType::FFAC3) && AudioEncoderTypes->Register(AudioEncoderType::FFMP2) && AudioEncoderTypes->Register(AudioEncoderType::LAME) && AudioEncoderTypes->Register(AudioEncoderType::NAAC) && AudioEncoderTypes->Register(AudioEncoderType::VORBIS) && AudioEncoderTypes->Register(AudioEncoderType::FLAC) && AudioEncoderTypes->Register(AudioEncoderType::AFTEN) && AudioEncoderTypes->Register(AudioEncoderType::QAAC) && AudioEncoderTypes->Register(AudioEncoderType::OPUS)))
			throw std::exception("Failed to register a standard audio encoder type");

	}

	const VideoCodec &VideoType::getSupportedCodecs() const
	{
		return supportedCodecs;
	}

	VideoType::VideoType(const std::string &name, const std::string &filterName, const std::string &extension, MeGUI::ContainerType *containerType, VideoCodec *supportedCodec)
	{
	}

	VideoType::VideoType(const std::string &name, const std::string &filterName, const std::string &extension, MeGUI::ContainerType *containerType, VideoCodec supportedCodecs[]) : OutputType(name, filterName, extension, containerType)
	{
			this->supportedCodecs = supportedCodecs;
	}

VideoType *const VideoType::MP4 = new VideoType("MP4", "MP4 Files", "mp4", getContainerType()->MP4, new VideoCodec[] {VideoCodec::ASP, VideoCodec::AVC, VideoCodec::MPEG2});
VideoType *const VideoType::RAWASP = new VideoType("RAWASP", "RAW MPEG-4 ASP Files", "m4v", 0, VideoCodec::ASP);
VideoType *const VideoType::RAWAVC = new VideoType("RAWAVC", "RAW MPEG-4 AVC Files", "264", 0, VideoCodec::AVC);
VideoType *const VideoType::RAWAVC2 = new VideoType("RAWAVC", "RAW MPEG-4 AVC Files", "h264", 0, VideoCodec::AVC);
VideoType *const VideoType::MKV = new VideoType("MKV", "Matroska Files", "mkv", getContainerType()->MKV, new VideoCodec[] {VideoCodec::ASP, VideoCodec::AVC, VideoCodec::HFYU, VideoCodec::MPEG2, VideoCodec::VC1});
VideoType *const VideoType::AVI = new VideoType("AVI", "AVI Files", "avi", getContainerType()->AVI, new VideoCodec[] {VideoCodec::ASP, VideoCodec::AVC, VideoCodec::HFYU});
VideoType *const VideoType::MPEG2 = new VideoType("MPEG2", "MPEG-2 Files", "m2v", 0, VideoCodec::MPEG2);
VideoType *const VideoType::VC1 = new VideoType("VC1", "VC-1 Files", "vc1", 0, VideoCodec::VC1);
VideoType *const VideoType::M2TS = new VideoType("M2TS", "M2TS Files", "m2ts", getContainerType()->M2TS, new VideoCodec[] {VideoCodec::AVC, VideoCodec::MPEG2, VideoCodec::VC1});

	const AudioCodec &AudioType::getSupportedCodecs() const
	{
		return supportedCodecs;
	}

	AudioType::AudioType(const std::string &name, const std::string &filterName, const std::string &extension, MeGUI::ContainerType *containerType, AudioCodec *supportedCodec)
	{
	}

	AudioType::AudioType(const std::string &name, const std::string &filterName, const std::string &extension, MeGUI::ContainerType *containerType, AudioCodec supportedCodecs[]) : OutputType(name, filterName, extension, containerType)
	{
			this->supportedCodecs = supportedCodecs;
	}

AudioType *const AudioType::MP4AAC = new AudioType("MP4-AAC", "MP4 AAC Files", "mp4", getContainerType()->MP4, AudioCodec::AAC);
AudioType *const AudioType::M4A = new AudioType("M4A", "MP4 Audio Files", "m4a", getContainerType()->MP4, AudioCodec::AAC);
AudioType *const AudioType::RAWAAC = new AudioType("Raw-AAC", "RAW AAC Files", "aac", 0, AudioCodec::AAC);
AudioType *const AudioType::MP3 = new AudioType("MP3", "MP3 Files", "mp3", 0, AudioCodec::MP3);
AudioType *const AudioType::VORBIS = new AudioType("Ogg", "Ogg Vorbis Files", "ogg", 0, AudioCodec::VORBIS);
AudioType *const AudioType::AC3 = new AudioType("AC3", "AC3 Files", "ac3", 0, AudioCodec::AC3);
AudioType *const AudioType::MP2 = new AudioType("MP2", "MP2 Files", "mp2", 0, AudioCodec::MP2);
AudioType *const AudioType::DTS = new AudioType("DTS", "DTS Files", "dts", 0, AudioCodec::DTS);
AudioType *const AudioType::WAV = new AudioType("WAV", "WAV Files", "wav", 0, AudioCodec::WAV);
AudioType *const AudioType::PCM = new AudioType("DTS", "DTS Files", "dts", 0, AudioCodec::PCM);
AudioType *const AudioType::CBRMP3 = new AudioType("CBR MP3", "CBR MP3 Files", "mp3", 0, AudioCodec::MP3);
AudioType *const AudioType::VBRMP3 = new AudioType("VBR MP3", "VBR MP3 Files", "mp3", 0, AudioCodec::MP3);
AudioType *const AudioType::EAC3 = new AudioType("EAC3", "EAC3 Files", "ddp", 0, AudioCodec::EAC3);
AudioType *const AudioType::THD = new AudioType("THD", "TrueHD Files", "thd", 0, AudioCodec::THD);
AudioType *const AudioType::DTSHD = new AudioType("DTSHD", "DTS-HD High Resolution Files", "dtshd", 0, AudioCodec::DTSHD);
AudioType *const AudioType::DTSMA = new AudioType("DTSMA", "DTS Master Audio Files", "dtsma", 0, AudioCodec::DTSMA);
AudioType *const AudioType::FLAC = new AudioType("FLAC", "FLAC Audio Lossless Files", "flac", 0, AudioCodec::FLAC);
AudioType *const AudioType::AVS = new AudioType("AVS", "AviSynth Script Files", "avs", 0, AudioCodec::PCM);
AudioType *const AudioType::OPUS = new AudioType("OPUS", "Opus Audio Files", "opus", 0, AudioCodec::OPUS);

	SubtitleType::SubtitleType(const std::string &name, const std::string &filterName, const std::string &extension, MeGUI::ContainerType *containerType) : OutputType(name, filterName, extension, containerType)
	{
	}

SubtitleType *const SubtitleType::SSA = new SubtitleType("SubStationAlpha", "SubStation Alpha Subtitle Files", "ssa", 0);
SubtitleType *const SubtitleType::ASS = new SubtitleType("Advanced SubStationAlpha", "Advanced SubStation Alpha Subtitle Files", "ass", 0);
SubtitleType *const SubtitleType::SUBRIP = new SubtitleType("Subrip", "Subrip Subtitle Files", "srt", 0);
SubtitleType *const SubtitleType::BDSUP = new SubtitleType("BDSup", "Blu-ray Sup Subtitle Files", "sup", 0);
SubtitleType *const SubtitleType::VOBSUB = new SubtitleType("Vobsub", "Vobsub Subtitle Files", "idx", 0);
SubtitleType *const SubtitleType::TTXT = new SubtitleType("TTXT", "Time Text Subtitles Files", "ttxt", 0);

	ChapterType::ChapterType(const std::string &name, const std::string &filterName, const std::string &extension, MeGUI::ContainerType *containerType) : OutputType(name, filterName, extension, containerType)
	{
	}

ChapterType *const ChapterType::OGG_TXT = new ChapterType("Ogg Chapter", "Ogg Chapter Files", "txt", 0);
ChapterType *const ChapterType::MKV_XML = new ChapterType("Matroska Chapter", "Matroska Chapter Files", "xml", 0);

	DeviceType::DeviceType(const std::string &name, const std::string &filterName, const std::string &extension, MeGUI::ContainerType *containerType) : OutputType(name, filterName, extension, containerType)
	{
	}

DeviceType *const DeviceType::APPLETV = new DeviceType("Apple TV", "Apple TV", "Apple TV", getContainerType()->MP4);
DeviceType *const DeviceType::IPAD = new DeviceType("iPad", "iPad", "iPad", getContainerType()->MP4);
DeviceType *const DeviceType::IPOD = new DeviceType("iPod", "iPod", "iPod", getContainerType()->MP4);
DeviceType *const DeviceType::IPHONE = new DeviceType("iPhone", "iPhone", "iPhone", getContainerType()->MP4);
DeviceType *const DeviceType::ISMA = new DeviceType("ISMA", "ISMA", "ISMA", getContainerType()->MP4);
DeviceType *const DeviceType::PSP = new DeviceType("PSP", "PSP", "PSP", getContainerType()->MP4);
DeviceType *const DeviceType::BD = new DeviceType("Blu-ray", "Blu-ray", "Blu-ray", getContainerType()->M2TS);
DeviceType *const DeviceType::AVCHD = new DeviceType("AVCHD", "AVCHD", "AVCHD", getContainerType()->M2TS);
DeviceType *const DeviceType::PC = new DeviceType("PC", "PC", "PC", getContainerType()->AVI);

	ContainerType::ContainerType(const std::string &name, const std::string &filterName, const std::string &extension) : OutputFileType(name, filterName, extension)
	{
	}

ContainerType *const ContainerType::MP4 = new ContainerType("MP4", "MP4 Files", "mp4");
ContainerType *const ContainerType::MKV = new ContainerType("MKV", "Matroska Files", "mkv");
ContainerType *const ContainerType::AVI = new ContainerType("AVI", "AVI Files", "avi");
ContainerType *const ContainerType::M2TS = new ContainerType("M2TS", "M2TS Files", "m2ts");
const ContainerType ContainerType::Containers[4] = {MP4, MKV, AVI, M2TS};

	ContainerType *ContainerType::ByName(const std::string &id)
	{
		for (MeGUI::ContainerType::const_iterator t = Containers->begin(); t != Containers->end(); ++t)
			if ((*t)->getID() == id)
				return t;
		return 0;
	}

GenericRegisterer<VideoType*> *ContainerManager::VideoTypes = new GenericRegisterer<VideoType*>();
GenericRegisterer<AudioType*> *ContainerManager::AudioTypes = new GenericRegisterer<AudioType*>();
GenericRegisterer<SubtitleType*> *ContainerManager::SubtitleTypes = new GenericRegisterer<SubtitleType*>();
GenericRegisterer<ContainerType*> *ContainerManager::ContainerTypes = new GenericRegisterer<ContainerType*>();
GenericRegisterer<ChapterType*> *ContainerManager::ChapterTypes = new GenericRegisterer<ChapterType*>();
GenericRegisterer<DeviceType*> *ContainerManager::DeviceTypes = new GenericRegisterer<DeviceType*>();

	ContainerManager::ContainerManager()
	{
		if (!(VideoTypes->Register(VideoType::AVI) && VideoTypes->Register(VideoType::MKV) && VideoTypes->Register(VideoType::MP4) && VideoTypes->Register(VideoType::RAWASP) && VideoTypes->Register(VideoType::RAWAVC) && VideoTypes->Register(VideoType::MPEG2) && VideoTypes->Register(VideoType::VC1) && VideoTypes->Register(VideoType::M2TS)))
			throw std::exception("Failed to register a video type");
		if (!(AudioTypes->Register(AudioType::AC3) && AudioTypes->Register(AudioType::MP3) && AudioTypes->Register(AudioType::DTS) && AudioTypes->Register(AudioType::WAV) && AudioTypes->Register(AudioType::MP2) && AudioTypes->Register(AudioType::MP4AAC) && AudioTypes->Register(AudioType::M4A) && AudioTypes->Register(AudioType::RAWAAC) && AudioTypes->Register(AudioType::VORBIS) && AudioTypes->Register(AudioType::DTSHD) && AudioTypes->Register(AudioType::DTSMA) && AudioTypes->Register(AudioType::EAC3) && AudioTypes->Register(AudioType::FLAC) && AudioTypes->Register(AudioType::AVS) && AudioTypes->Register(AudioType::THD)))
			throw std::exception("Failed to register an audio type");
		if (!(SubtitleTypes->Register(SubtitleType::ASS) && SubtitleTypes->Register(SubtitleType::SSA) && SubtitleTypes->Register(SubtitleType::SUBRIP) && SubtitleTypes->Register(SubtitleType::BDSUP) && SubtitleTypes->Register(SubtitleType::VOBSUB) && SubtitleTypes->Register(SubtitleType::TTXT)))
			throw std::exception("Failed to register a subtitle type");
		if (!(ContainerTypes->Register(ContainerType::AVI) && ContainerTypes->Register(ContainerType::MKV) && ContainerTypes->Register(ContainerType::MP4) && ContainerTypes->Register(ContainerType::M2TS)))
			throw std::exception("Failed to register a container type");
		if (!(ChapterTypes->Register(ChapterType::OGG_TXT) && ChapterTypes->Register(ChapterType::MKV_XML)))
			throw std::exception("Failed to register a chapter type");
		if (!(DeviceTypes->Register(DeviceType::AVCHD) && DeviceTypes->Register(DeviceType::BD) && DeviceTypes->Register(DeviceType::PC) && DeviceTypes->Register(DeviceType::IPOD) && DeviceTypes->Register(DeviceType::PSP) && DeviceTypes->Register(DeviceType::IPHONE) && DeviceTypes->Register(DeviceType::APPLETV) && DeviceTypes->Register(DeviceType::IPAD) && DeviceTypes->Register(DeviceType::ISMA)))
			throw std::exception("Failed to register a device type");
	}

	OutputFileType::OutputFileType(const std::string &name, const std::string &filterName, const std::string &extension)
	{
		this->name = name;
		this->filterName = filterName;
		this->extension = extension;
	}

	const std::string &OutputFileType::getID() const
	{
		return name;
	}

	std::string OutputFileType::ToString()
	{
		return this->name;
	}

	const std::string &OutputFileType::getOutputFilter() const
	{
		return "*." + extension;
	}

	const std::string &OutputFileType::getOutputFilterString() const
	{
		return filterName + " (*." + extension + ")|*." + extension;
	}

	const std::string &OutputFileType::getExtension() const
	{
		return this->extension;
	}

	OutputType::OutputType(const std::string &name, const std::string &filterName, const std::string &extension, MeGUI::ContainerType *containerType) : OutputFileType(name, filterName, extension)
	{
		this->containerType = containerType;
	}

	const MeGUI::ContainerType &OutputType::getContainerType() const
	{
		return this->containerType;
	}
}
