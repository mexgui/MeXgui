#include "MediaInfoMain.h"

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

	MediaInfo::MediaInfo(const std::string &path)
	{
		if (!CheckFileExistence(path))
			return;
		_FileName = path;

		this->Handle = MediaInfo::MediaInfo_New();
		MediaInfo::MediaInfo_Open(this->Handle, path);
		try
		{
			getStreamCount();
			getAllInfos();
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally //ensure MediaInfo_Close is called even if something goes wrong
		{
			MediaInfo::MediaInfo_Close(this->Handle);
		}

	}

	void MediaInfo::Finalize()
	{
		this->Dispose(false);
	}

	const bool &MediaInfo::getIsDisposed() const
	{
		return disposed;
	}

	void MediaInfo::CheckDisposed()
	{
		if (disposed)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			throw new ObjectDisposedException(this->ToString());
		}
	}

	MediaInfo::~MediaInfo()
	{
		this->Dispose(true);
//C# TO C++ CONVERTER WARNING: There is no garbage collector in native C++:
//		GC::SuppressFinalize(this);
	}

	void MediaInfo::Dispose(bool disposing)
	{
		if (!this->disposed)
		{
			if (disposing)
			{
				DisposeManagedResources();
			}
			DisposeUnmanagedResources();
		}
		this->disposed = true;
	}

	void MediaInfo::DisposeManagedResources()
	{
	}

	void MediaInfo::DisposeUnmanagedResources()
	{
		MediaInfo::MediaInfo_Close(this->Handle);
		MediaInfo::MediaInfo_Delete(this->Handle);
	}

	bool MediaInfo::CheckFileExistence(const std::string &filepath)
	{
		if (!File::Exists(filepath))
			throw new FileNotFoundException("File not found: " + filepath, filepath);
		else
			return true;
	}

	std::string MediaInfo::GetSpecificMediaInfo(MediaInfoStreamKind KindOfStream, int trackindex, const std::string &NameOfParameter)
	{
		void* p = MediaInfo::MediaInfo_Get(this->Handle, KindOfStream, static_cast<unsigned int>(trackindex), NameOfParameter, getText(), Name);
		wchar_t* p2 = static_cast<wchar_t>(p.ToPointer());
		std::string s = "";
		while (*p2 != '\0')
		{
			s += *p2;
			++p2;
		}
		return s;
	}

	void MediaInfo::getStreamCount()
	{
		_AudioCount = MediaInfo::MediaInfo_Count_Get(this->Handle, getAudio(), -1);
		_VideoCount = MediaInfo::MediaInfo_Count_Get(this->Handle, getVideo(), -1);
		_GeneralCount = MediaInfo::MediaInfo_Count_Get(this->Handle, getGeneral(), -1);
		_TextCount = MediaInfo::MediaInfo_Count_Get(this->Handle, getText(), -1);
		_ChaptersCount = MediaInfo::MediaInfo_Count_Get(this->Handle, getChapters(), -1);
	}

	void MediaInfo::getAllInfos()
	{
		getVideoInfo();
		getAudioInfo();
		getChaptersInfo();
		getTextInfo();
		getGeneralInfo();
	}

	const std::string &MediaInfo::getInfoComplete() const
	{
		if (this->_InfoComplete.empty())
		{
			MediaInfo::MediaInfo_Open(this->Handle,_FileName);
			MediaInfo::MediaInfo_Option(this->Handle, "Complete", "1");
			_InfoComplete = MediaInfo::MediaInfo_Inform(this->Handle, 0);
			MediaInfo::MediaInfo_Close(this->Handle);
		}
		return _InfoComplete;
	}

	const std::string &MediaInfo::getInfoStandard() const
	{
		if (this->_InfoStandard.empty())
		{
			MediaInfo::MediaInfo_Open(this->Handle, _FileName);
			MediaInfo::MediaInfo_Option(this->Handle, "Complete", "");
			_InfoStandard = MediaInfo::MediaInfo_Inform(this->Handle, 0);
			MediaInfo::MediaInfo_Close(this->Handle);
		}
		return _InfoStandard;
	}

	const std::string &MediaInfo::getInfoCustom() const
	{
		if (_InfoCustom.empty())
		{
			std::string s = "";

			s += "General" + "\r\n";
			s += ListEveryAvailablePropery<GeneralTrack*>(this, &MediaInfo::General);
			s += "\r\n";
			s += "Video" + "\r\n";
			s += ListEveryAvailablePropery<VideoTrack*>(this, &MediaInfo::Video);
			s += "\r\n";
			s += "Audio" + "\r\n";
			s += ListEveryAvailablePropery<AudioTrack*>(this, &MediaInfo::Audio);
			s += "\r\n";
			s += "Text" + "\r\n";
			s += ListEveryAvailablePropery<TextTrack*>(this, &MediaInfo::Text);
			s += "\r\n";
			s += "Chapters" + "\r\n";
			s += ListEveryAvailablePropery<ChaptersTrack*>(this, &MediaInfo::Chapters);

			_InfoCustom = s;
		}
		return _InfoCustom;
	}

template<typename T1>
	std::string MediaInfo::ListEveryAvailablePropery(std::vector<T1> &L)
	{
		std::string s = "";
		for (std::vector<T1>::const_iterator track = L.begin(); track != L.end(); ++track)
		{
			for (unknown::const_iterator p = track->GetType()->GetProperties().begin(); p != track->GetType()->GetProperties().end(); ++p)
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				s += ((*p)->GetValue(*track, 0)->ToString() == "") ? (*p)->Name + " : Not available" + "\r\n" : (*p)->Name + " : " + (*p)->GetValue(*track, 0) + "\r\n";
			}
		}
		return s;
	}

	std::string MediaInfo::Capacities()
	{
		return MediaInfo_Option(static_cast<void*>(0), "Info_Capacities", "");
	}

	std::string MediaInfo::ParameterList()
	{
		return MediaInfo_Option(static_cast<void*>(0), "Info_Parameters", "");
	}

	std::string MediaInfo::KnownCodecs()
	{
		return MediaInfo_Option(static_cast<void*>(0), "Info_Codecs", "");
	}

	const std::vector<GeneralTrack*> &MediaInfo::getGeneral() const
	{
		if (this->_General.empty())
		{
		   getGeneralInfo();
		}
		return this->_General;
	}

	void MediaInfo::getGeneralInfo()
	{
		if (this->_General.empty())
		{
			this->_General = std::vector<GeneralTrack*>();
			int num1 = MediaInfo::MediaInfo_Count_Get(this->Handle, getGeneral(), -1);
			if (num1 > 0)
			{
				int num3 = num1 - 1;
				for (int num2 = 0; num2 <= num3; num2++)
				{
					GeneralTrack *_tracktemp_ = new GeneralTrack();
					_tracktemp_->setCount(GetSpecificMediaInfo(getGeneral(),num2,"Count"));
					_tracktemp_->setStreamCount(GetSpecificMediaInfo(getGeneral(),num2,"StreamCount"));
					_tracktemp_->setStreamKind(GetSpecificMediaInfo(getGeneral(),num2,"StreamKind"));
					_tracktemp_->setStreamKindID(GetSpecificMediaInfo(getGeneral(),num2,"StreamKindID"));
					_tracktemp_->setStreamOrder(GetSpecificMediaInfo(getGeneral(), num2, "StreamOrder"));
					_tracktemp_->setInform(GetSpecificMediaInfo(getGeneral(),num2,"Inform"));
					_tracktemp_->setID(GetSpecificMediaInfo(getGeneral(),num2,"ID"));
					_tracktemp_->setUniqueID(GetSpecificMediaInfo(getGeneral(),num2,"UniqueID"));
					_tracktemp_->setGeneralCount(GetSpecificMediaInfo(getGeneral(),num2,"GeneralCount"));
					_tracktemp_->setVideoCount(GetSpecificMediaInfo(getGeneral(),num2,"VideoCount"));
					_tracktemp_->setAudioCount(GetSpecificMediaInfo(getGeneral(),num2,"AudioCount"));
					_tracktemp_->setTextCount(GetSpecificMediaInfo(getGeneral(),num2,"TextCount"));
					_tracktemp_->setChaptersCount(GetSpecificMediaInfo(getGeneral(),num2,"ChaptersCount"));
					_tracktemp_->setImageCount(GetSpecificMediaInfo(getGeneral(),num2,"ImageCount"));
					_tracktemp_->setCompleteName(GetSpecificMediaInfo(getGeneral(),num2,"CompleteName"));
					_tracktemp_->setFolderName(GetSpecificMediaInfo(getGeneral(),num2,"FolderName"));
					_tracktemp_->setFileName(GetSpecificMediaInfo(getGeneral(),num2,"FileName"));
					_tracktemp_->setFileExtension(GetSpecificMediaInfo(getGeneral(),num2,"FileExtension"));
					_tracktemp_->setFileSize(GetSpecificMediaInfo(getGeneral(),num2,"FileSize"));
					_tracktemp_->setFileSizeString(GetSpecificMediaInfo(getGeneral(),num2,"FileSize/String"));
					_tracktemp_->setFileSizeString1(GetSpecificMediaInfo(getGeneral(),num2,"FileSize/String1"));
					_tracktemp_->setFileSizeString2(GetSpecificMediaInfo(getGeneral(),num2,"FileSize/String2"));
					_tracktemp_->setFileSizeString3(GetSpecificMediaInfo(getGeneral(),num2,"FileSize/String3"));
					_tracktemp_->setFileSizeString4(GetSpecificMediaInfo(getGeneral(),num2,"FileSize/String4"));
					_tracktemp_->setFormat(GetSpecificMediaInfo(getGeneral(),num2,"Format"));
					_tracktemp_->setFormatString(GetSpecificMediaInfo(getGeneral(),num2,"Format/String"));
					_tracktemp_->setFormatInfo(GetSpecificMediaInfo(getGeneral(),num2,"Format/Info"));
					_tracktemp_->setFormatUrl(GetSpecificMediaInfo(getGeneral(),num2,"Format/Url"));
					_tracktemp_->setFormatExtensions(GetSpecificMediaInfo(getGeneral(),num2,"Format/Extensions"));
					_tracktemp_->setOveralBitRate(GetSpecificMediaInfo(getGeneral(),num2,"OveralBitRate"));
					_tracktemp_->setOveralBitRateString(GetSpecificMediaInfo(getGeneral(),num2,"OveralBitRate/String"));
					_tracktemp_->setPlayTime(GetSpecificMediaInfo(getGeneral(),num2,"PlayTime"));
					_tracktemp_->setPlayTimeString(GetSpecificMediaInfo(getGeneral(),num2,"PlayTime/String"));
					_tracktemp_->setPlayTimeString1(GetSpecificMediaInfo(getGeneral(),num2,"PlayTime/String1"));
					_tracktemp_->setPlayTimeString2(GetSpecificMediaInfo(getGeneral(),num2,"PlayTime/String2"));
					_tracktemp_->setPlayTimeString3(GetSpecificMediaInfo(getGeneral(),num2,"PlayTime/String3"));
					_tracktemp_->setTitle(GetSpecificMediaInfo(getGeneral(),num2,"Title"));
					_tracktemp_->setTitleMore(GetSpecificMediaInfo(getGeneral(),num2,"Title/More"));
					_tracktemp_->setDomain(GetSpecificMediaInfo(getGeneral(),num2,"Domain"));
					_tracktemp_->setCollection(GetSpecificMediaInfo(getGeneral(),num2,"Collection"));
					_tracktemp_->setCollectionTotalParts(GetSpecificMediaInfo(getGeneral(),num2,"Collection/Total_Parts"));
					_tracktemp_->setSeason(GetSpecificMediaInfo(getGeneral(),num2,"Season"));
					_tracktemp_->setMovie(GetSpecificMediaInfo(getGeneral(),num2,"Movie"));
					_tracktemp_->setMovieMore(GetSpecificMediaInfo(getGeneral(),num2,"Movie/More"));
					_tracktemp_->setAlbum(GetSpecificMediaInfo(getGeneral(),num2,"Album"));
					_tracktemp_->setAlbumTotalParts(GetSpecificMediaInfo(getGeneral(),num2,"Album/Total_Parts"));
					_tracktemp_->setAlbumSort(GetSpecificMediaInfo(getGeneral(),num2,"Album/Sort"));
					_tracktemp_->setComic(GetSpecificMediaInfo(getGeneral(),num2,"Comic"));
					_tracktemp_->setComicTotalParts(GetSpecificMediaInfo(getGeneral(),num2,"Comic/Total_Parts"));
					_tracktemp_->setPart(GetSpecificMediaInfo(getGeneral(),num2,"Part"));
					_tracktemp_->setPartTotalParts(GetSpecificMediaInfo(getGeneral(),num2,"Part/Total_Parts"));
					_tracktemp_->setPartPosition(GetSpecificMediaInfo(getGeneral(),num2,"Part/Position"));
					_tracktemp_->setTrack(GetSpecificMediaInfo(getGeneral(),num2,"Track"));
					_tracktemp_->setTrackPosition(GetSpecificMediaInfo(getGeneral(),num2,"Track/Position"));
					_tracktemp_->setTrackMore(GetSpecificMediaInfo(getGeneral(),num2,"Track/More"));
					_tracktemp_->setTrackSort(GetSpecificMediaInfo(getGeneral(),num2,"Track/Sort"));
					_tracktemp_->setChapter(GetSpecificMediaInfo(getGeneral(),num2,"Chapter"));
					_tracktemp_->setSubTrack(GetSpecificMediaInfo(getGeneral(),num2,"SubTrack"));
					_tracktemp_->setOriginalAlbum(GetSpecificMediaInfo(getGeneral(),num2,"Original/Album"));
					_tracktemp_->setOriginalMovie(GetSpecificMediaInfo(getGeneral(),num2,"Original/Movie"));
					_tracktemp_->setOriginalPart(GetSpecificMediaInfo(getGeneral(),num2,"Original/Part"));
					_tracktemp_->setOriginalTrack(GetSpecificMediaInfo(getGeneral(),num2,"Original/Track"));
					_tracktemp_->setAuthor(GetSpecificMediaInfo(getGeneral(),num2,"Author"));
					_tracktemp_->setArtist(GetSpecificMediaInfo(getGeneral(),num2,"Artist"));
					_tracktemp_->setPerformerSort(GetSpecificMediaInfo(getGeneral(),num2,"Performer/Sort"));
					_tracktemp_->setOriginalPerformer(GetSpecificMediaInfo(getGeneral(),num2,"Original/Performer"));
					_tracktemp_->setAccompaniment(GetSpecificMediaInfo(getGeneral(),num2,"Accompaniment"));
					_tracktemp_->setMusicianInstrument(GetSpecificMediaInfo(getGeneral(),num2,"Musician_Instrument"));
					_tracktemp_->setComposer(GetSpecificMediaInfo(getGeneral(),num2,"Composer"));
					_tracktemp_->setComposerNationality(GetSpecificMediaInfo(getGeneral(),num2,"Composer/Nationality"));
					_tracktemp_->setArranger(GetSpecificMediaInfo(getGeneral(),num2,"Arranger"));
					_tracktemp_->setLyricist(GetSpecificMediaInfo(getGeneral(),num2,"Lyricist"));
					_tracktemp_->setOriginalLyricist(GetSpecificMediaInfo(getGeneral(),num2,"Original/Lyricist"));
					_tracktemp_->setConductor(GetSpecificMediaInfo(getGeneral(),num2,"Conductor"));
					_tracktemp_->setActor(GetSpecificMediaInfo(getGeneral(),num2,"Actor"));
					_tracktemp_->setActorCharacter(GetSpecificMediaInfo(getGeneral(),num2,"Actor_Character"));
					_tracktemp_->setWrittenBy(GetSpecificMediaInfo(getGeneral(),num2,"WrittenBy"));
					_tracktemp_->setScreenplayBy(GetSpecificMediaInfo(getGeneral(),num2,"ScreenplayBy"));
					_tracktemp_->setDirector(GetSpecificMediaInfo(getGeneral(),num2,"Director"));
					_tracktemp_->setAssistantDirector(GetSpecificMediaInfo(getGeneral(),num2,"AssistantDirector"));
					_tracktemp_->setDirectorOfPhotography(GetSpecificMediaInfo(getGeneral(),num2,"DirectorOfPhotography"));
					_tracktemp_->setArtDirector(GetSpecificMediaInfo(getGeneral(),num2,"ArtDirector"));
					_tracktemp_->setEditedBy(GetSpecificMediaInfo(getGeneral(),num2,"EditedBy"));
					_tracktemp_->setProducer(GetSpecificMediaInfo(getGeneral(),num2,"Producer"));
					_tracktemp_->setCoProducer(GetSpecificMediaInfo(getGeneral(),num2,"CoProducer"));
					_tracktemp_->setExecutiveProducer(GetSpecificMediaInfo(getGeneral(),num2,"ExecutiveProducer"));
					_tracktemp_->setProductionDesigner(GetSpecificMediaInfo(getGeneral(),num2,"ProductionDesigner"));
					_tracktemp_->setCostumeDesigner(GetSpecificMediaInfo(getGeneral(),num2,"CostumeDesigner"));
					_tracktemp_->setChoregrapher(GetSpecificMediaInfo(getGeneral(),num2,"Choregrapher"));
					_tracktemp_->setSoundEngineer(GetSpecificMediaInfo(getGeneral(),num2,"SoundEngineer"));
					_tracktemp_->setMasteredBy(GetSpecificMediaInfo(getGeneral(),num2,"MasteredBy"));
					_tracktemp_->setRemixedBy(GetSpecificMediaInfo(getGeneral(),num2,"RemixedBy"));
					_tracktemp_->setProductionStudio(GetSpecificMediaInfo(getGeneral(),num2,"ProductionStudio"));
					_tracktemp_->setPublisher(GetSpecificMediaInfo(getGeneral(),num2,"Publisher"));
					_tracktemp_->setPublisherURL(GetSpecificMediaInfo(getGeneral(),num2,"Publisher/URL"));
					_tracktemp_->setDistributedBy(GetSpecificMediaInfo(getGeneral(),num2,"DistributedBy"));
					_tracktemp_->setEncodedBy(GetSpecificMediaInfo(getGeneral(),num2,"EncodedBy"));
					_tracktemp_->setThanksTo(GetSpecificMediaInfo(getGeneral(),num2,"ThanksTo"));
					_tracktemp_->setTechnician(GetSpecificMediaInfo(getGeneral(),num2,"Technician"));
					_tracktemp_->setCommissionedBy(GetSpecificMediaInfo(getGeneral(),num2,"CommissionedBy"));
					_tracktemp_->setEncodedOriginalDistributedBy(GetSpecificMediaInfo(getGeneral(),num2,"Encoded_Original/DistributedBy"));
					_tracktemp_->setRadioStation(GetSpecificMediaInfo(getGeneral(),num2,"RadioStation"));
					_tracktemp_->setRadioStationOwner(GetSpecificMediaInfo(getGeneral(),num2,"RadioStation/Owner"));
					_tracktemp_->setRadioStationURL(GetSpecificMediaInfo(getGeneral(),num2,"RadioStation/URL"));
					_tracktemp_->setContentType(GetSpecificMediaInfo(getGeneral(),num2,"ContentType"));
					_tracktemp_->setSubject(GetSpecificMediaInfo(getGeneral(),num2,"Subject"));
					_tracktemp_->setSynopsys(GetSpecificMediaInfo(getGeneral(),num2,"Synopsys"));
					_tracktemp_->setSummary(GetSpecificMediaInfo(getGeneral(),num2,"Summary"));
					_tracktemp_->setDescription(GetSpecificMediaInfo(getGeneral(),num2,"Description"));
					_tracktemp_->setKeywords(GetSpecificMediaInfo(getGeneral(),num2,"Keywords"));
					_tracktemp_->setPeriod(GetSpecificMediaInfo(getGeneral(),num2,"Period"));
					_tracktemp_->setLawRating(GetSpecificMediaInfo(getGeneral(),num2,"LawRating"));
					_tracktemp_->setIRCA(GetSpecificMediaInfo(getGeneral(),num2,"IRCA"));
					_tracktemp_->setLanguage(GetSpecificMediaInfo(getGeneral(),num2,"Language"));
					_tracktemp_->setMedium(GetSpecificMediaInfo(getGeneral(),num2,"Medium"));
					_tracktemp_->setProduct(GetSpecificMediaInfo(getGeneral(),num2,"Product"));
					_tracktemp_->setCountry(GetSpecificMediaInfo(getGeneral(),num2,"Country"));
					_tracktemp_->setWrittenDate(GetSpecificMediaInfo(getGeneral(),num2,"Written_Date"));
					_tracktemp_->setRecordedDate(GetSpecificMediaInfo(getGeneral(),num2,"Recorded_Date"));
					_tracktemp_->setReleasedDate(GetSpecificMediaInfo(getGeneral(),num2,"Released_Date"));
					_tracktemp_->setMasteredDate(GetSpecificMediaInfo(getGeneral(),num2,"Mastered_Date"));
					_tracktemp_->setEncodedDate(GetSpecificMediaInfo(getGeneral(),num2,"Encoded_Date"));
					_tracktemp_->setTaggedDate(GetSpecificMediaInfo(getGeneral(),num2,"Tagged_Date"));
					_tracktemp_->setOriginalReleasedDate(GetSpecificMediaInfo(getGeneral(),num2,"Original/Released_Date"));
					_tracktemp_->setOriginalRecordedDate(GetSpecificMediaInfo(getGeneral(),num2,"Original/Recorded_Date"));
					_tracktemp_->setWrittenLocation(GetSpecificMediaInfo(getGeneral(),num2,"Written_Location"));
					_tracktemp_->setRecordedLocation(GetSpecificMediaInfo(getGeneral(),num2,"Recorded_Location"));
					_tracktemp_->setArchivalLocation(GetSpecificMediaInfo(getGeneral(),num2,"Archival_Location"));
					_tracktemp_->setGenre(GetSpecificMediaInfo(getGeneral(),num2,"Genre"));
					_tracktemp_->setMood(GetSpecificMediaInfo(getGeneral(),num2,"Mood"));
					_tracktemp_->setComment(GetSpecificMediaInfo(getGeneral(),num2,"Comment"));
					_tracktemp_->setRating(GetSpecificMediaInfo(getGeneral(),num2,"Rating "));
					_tracktemp_->setEncodedApplication(GetSpecificMediaInfo(getGeneral(),num2,"Encoded_Application"));
					_tracktemp_->setEncodedLibrary(GetSpecificMediaInfo(getGeneral(),num2,"Encoded_Library"));
					_tracktemp_->setEncodedLibrarySettings(GetSpecificMediaInfo(getGeneral(),num2,"Encoded_Library_Settings"));
					_tracktemp_->setEncodedOriginal(GetSpecificMediaInfo(getGeneral(),num2,"Encoded_Original"));
					_tracktemp_->setEncodedOriginalUrl(GetSpecificMediaInfo(getGeneral(),num2,"Encoded_Original/Url"));
					_tracktemp_->setCopyright(GetSpecificMediaInfo(getGeneral(),num2,"Copyright"));
					_tracktemp_->setProducerCopyright(GetSpecificMediaInfo(getGeneral(),num2,"Producer_Copyright"));
					_tracktemp_->setTermsOfUse(GetSpecificMediaInfo(getGeneral(),num2,"TermsOfUse"));
					_tracktemp_->setCopyrightUrl(GetSpecificMediaInfo(getGeneral(),num2,"Copyright/Url"));
					_tracktemp_->setISRC(GetSpecificMediaInfo(getGeneral(),num2,"ISRC"));
					_tracktemp_->setMSDI(GetSpecificMediaInfo(getGeneral(),num2,"MSDI"));
					_tracktemp_->setISBN(GetSpecificMediaInfo(getGeneral(),num2,"ISBN"));
					_tracktemp_->setBarCode(GetSpecificMediaInfo(getGeneral(),num2,"BarCode"));
					_tracktemp_->setLCCN(GetSpecificMediaInfo(getGeneral(),num2,"LCCN"));
					_tracktemp_->setCatalogNumber(GetSpecificMediaInfo(getGeneral(),num2,"CatalogNumber"));
					_tracktemp_->setLabelCode(GetSpecificMediaInfo(getGeneral(),num2,"LabelCode"));
					_tracktemp_->setCover(GetSpecificMediaInfo(getGeneral(),num2,"Cover"));
					_tracktemp_->setCoverDatas(GetSpecificMediaInfo(getGeneral(),num2,"Cover_Datas"));
					_tracktemp_->setBPM(GetSpecificMediaInfo(getGeneral(),num2,"BPM"));
					_tracktemp_->setVideoCodecList(GetSpecificMediaInfo(getGeneral(),num2,"Video_Codec_List"));
					_tracktemp_->setVideoLanguageList(GetSpecificMediaInfo(getGeneral(),num2,"Video_Language_List"));
					_tracktemp_->setAudioCodecList(GetSpecificMediaInfo(getGeneral(),num2,"Audio_Codec_List"));
					_tracktemp_->setAudioLanguageList(GetSpecificMediaInfo(getGeneral(),num2,"Audio_Language_List"));
					_tracktemp_->setTextCodecList(GetSpecificMediaInfo(getGeneral(),num2,"Text_Codec_List"));
					_tracktemp_->setTextLanguageList(GetSpecificMediaInfo(getGeneral(),num2,"Text_Language_List"));
					_tracktemp_->setChaptersCodecList(GetSpecificMediaInfo(getGeneral(),num2,"Chapters_Codec_List"));
					_tracktemp_->setChaptersLanguageList(GetSpecificMediaInfo(getGeneral(),num2,"Chapters_Language_List"));
					_tracktemp_->setImageCodecList(GetSpecificMediaInfo(getGeneral(),num2,"Image_Codec_List"));
					_tracktemp_->setImageLanguageList(GetSpecificMediaInfo(getGeneral(),num2,"Image_Language_List"));
					_tracktemp_->setOther(GetSpecificMediaInfo(getGeneral(),num2,"Other"));
					this->_General.push_back(_tracktemp_);
				}
			}
		}
	}

	const std::vector<VideoTrack*> &MediaInfo::getVideo() const
	{
		if (this->_Video.empty())
		{
		   getVideoInfo();
		}
		return this->_Video;
	}

	void MediaInfo::getVideoInfo()
	{
		if (this->_Video.empty())
		{
			this->_Video = std::vector<VideoTrack*>();
			int num1 = MediaInfo::MediaInfo_Count_Get(this->Handle, getVideo(), -1);
			if (num1 > 0)
			{
				int num3 = num1 - 1;
				for (int num2 = 0; num2 <= num3; num2++)
				{
					VideoTrack *_tracktemp_ = new VideoTrack();
					_tracktemp_->setCount(GetSpecificMediaInfo(getVideo(),num2,"Count"));
					_tracktemp_->setStreamCount(GetSpecificMediaInfo(getVideo(),num2,"StreamCount"));
					_tracktemp_->setStreamKind(GetSpecificMediaInfo(getVideo(),num2,"StreamKind"));
					_tracktemp_->setStreamKindID(GetSpecificMediaInfo(getVideo(),num2,"StreamKindID"));
					_tracktemp_->setStreamOrder(GetSpecificMediaInfo(getVideo(), num2, "StreamOrder"));
					_tracktemp_->setInform(GetSpecificMediaInfo(getVideo(),num2,"Inform"));
					_tracktemp_->setID(GetSpecificMediaInfo(getVideo(),num2,"ID"));
					_tracktemp_->setUniqueID(GetSpecificMediaInfo(getVideo(),num2,"UniqueID"));
					_tracktemp_->setTitle(GetSpecificMediaInfo(getVideo(),num2,"Title"));
					_tracktemp_->setCodec(GetSpecificMediaInfo(getVideo(),num2,"Codec"));
					_tracktemp_->setCodecString(GetSpecificMediaInfo(getVideo(),num2,"Codec/String"));
					_tracktemp_->setCodecInfo(GetSpecificMediaInfo(getVideo(),num2,"Codec/Info"));
					_tracktemp_->setCodecUrl(GetSpecificMediaInfo(getVideo(),num2,"Codec/Url"));
					_tracktemp_->setCodecID(GetSpecificMediaInfo(getVideo(), num2, "CodecID"));
					_tracktemp_->setCodecIDInfo(GetSpecificMediaInfo(getVideo(), num2, "CodecID/Info"));
					_tracktemp_->setBitRate(GetSpecificMediaInfo(getVideo(),num2,"BitRate"));
					_tracktemp_->setBitRateString(GetSpecificMediaInfo(getVideo(),num2,"BitRate/String"));
					_tracktemp_->setBitRateMode(GetSpecificMediaInfo(getVideo(),num2,"BitRate_Mode"));
					_tracktemp_->setEncodedLibrary(GetSpecificMediaInfo(getVideo(),num2,"Encoded_Library"));
					_tracktemp_->setEncodedLibrarySettings(GetSpecificMediaInfo(getVideo(),num2,"Encoded_Library_Settings"));
					_tracktemp_->setWidth(GetSpecificMediaInfo(getVideo(),num2,"Width"));
					_tracktemp_->setHeight(GetSpecificMediaInfo(getVideo(),num2,"Height"));
					_tracktemp_->setAspectRatio(GetSpecificMediaInfo(getVideo(),num2,"AspectRatio"));
					_tracktemp_->setAspectRatioString(GetSpecificMediaInfo(getVideo(), num2, "AspectRatio/String"));
					_tracktemp_->setPixelAspectRatio(GetSpecificMediaInfo(getVideo(), num2, "PixelAspectRatio"));
					_tracktemp_->setPixelAspectRatioString(GetSpecificMediaInfo(getVideo(), num2, "PixelAspectRatio/String"));
					_tracktemp_->setFrameRate(GetSpecificMediaInfo(getVideo(),num2,"FrameRate"));
					_tracktemp_->setFrameRateString(GetSpecificMediaInfo(getVideo(),num2,"FrameRate/String"));
					_tracktemp_->setFrameRateOriginal(GetSpecificMediaInfo(getVideo(), num2, "FrameRate_Original"));
					_tracktemp_->setFrameRateOriginalString(GetSpecificMediaInfo(getVideo(), num2, "FrameRate_Original/String"));
					_tracktemp_->setFrameRateMode(GetSpecificMediaInfo(getVideo(), num2, "FrameRate_Mode"));
					_tracktemp_->setFrameRateModeString(GetSpecificMediaInfo(getVideo(), num2, "FrameRate_Mode/String"));
					_tracktemp_->setFrameCount(GetSpecificMediaInfo(getVideo(),num2,"FrameCount"));
					_tracktemp_->setBitDepth(GetSpecificMediaInfo(getVideo(),num2,"BitDepth"));
					_tracktemp_->setBitsPixelFrame(GetSpecificMediaInfo(getVideo(),num2,"Bits/(Pixel*Frame)"));
					_tracktemp_->setDelay(GetSpecificMediaInfo(getVideo(),num2,"Delay"));
					_tracktemp_->setDuration(GetSpecificMediaInfo(getVideo(),num2,"Duration"));
					_tracktemp_->setDurationString(GetSpecificMediaInfo(getVideo(),num2,"Duration/String"));
					_tracktemp_->setDurationString1(GetSpecificMediaInfo(getVideo(),num2,"Duration/String1"));
					_tracktemp_->setDurationString2(GetSpecificMediaInfo(getVideo(),num2,"Duration/String2"));
					_tracktemp_->setDurationString3(GetSpecificMediaInfo(getVideo(),num2,"Duration/String3"));
					_tracktemp_->setLanguage(GetSpecificMediaInfo(getVideo(),num2,"Language"));
					_tracktemp_->setLanguageString(GetSpecificMediaInfo(getVideo(),num2,"Language/String"));
					_tracktemp_->setLanguageMore(GetSpecificMediaInfo(getVideo(),num2,"Language_More"));
					_tracktemp_->setFormat(GetSpecificMediaInfo(getVideo(), num2, "Format"));
					_tracktemp_->setFormatInfo(GetSpecificMediaInfo(getVideo(), num2, "Format/Info"));
					_tracktemp_->setFormatProfile(GetSpecificMediaInfo(getVideo(), num2, "Format_Profile"));
					_tracktemp_->setFormatSettings(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings"));
					_tracktemp_->setFormatSettingsBVOP(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_BVOP"));
					_tracktemp_->setFormatSettingsBVOPString(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_BVOP/String"));
					_tracktemp_->setFormatSettingsCABAC(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_CABAC"));
					_tracktemp_->setFormatSettingsCABACString(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_CABAC/String"));
					_tracktemp_->setFormatSettingsGMC(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_GMC"));
					_tracktemp_->setFormatSettingsGMCString(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_GMAC/String"));
					_tracktemp_->setFormatSettingsMatrix(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_Matrix"));
					_tracktemp_->setFormatSettingsMatrixData(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_Matrix_Data"));
					_tracktemp_->setFormatSettingsMatrixString(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_Matrix/String"));
					_tracktemp_->setFormatSettingsPulldown(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_Pulldown"));
					_tracktemp_->setFormatSettingsQPel(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_QPel"));
					_tracktemp_->setFormatSettingsQPelString(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_QPel/String"));
					_tracktemp_->setFormatSettingsRefFrames(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_RefFrames"));
					_tracktemp_->setFormatSettingsRefFramesString(GetSpecificMediaInfo(getVideo(), num2, "Format_Settings_RefFrames/String"));
					_tracktemp_->setScanType(GetSpecificMediaInfo(getVideo(), num2, "ScanType"));
					_tracktemp_->setScanTypeString(GetSpecificMediaInfo(getVideo(), num2, "ScanType/String"));
					_tracktemp_->setFormatUrl(GetSpecificMediaInfo(getVideo(), num2, "Format/Url"));
					_tracktemp_->setFormatVersion(GetSpecificMediaInfo(getVideo(), num2, "Format_Version"));
					_tracktemp_->setDefault(GetSpecificMediaInfo(getVideo(), num2, "Default"));
					_tracktemp_->setDefaultString(GetSpecificMediaInfo(getVideo(), num2, "Default/String"));
					_tracktemp_->setForced(GetSpecificMediaInfo(getVideo(), num2, "Forced"));
					_tracktemp_->setForcedString(GetSpecificMediaInfo(getVideo(), num2, "Forced/String"));
					 this->_Video.push_back(_tracktemp_);
				}
			}
		}
	}

	const std::vector<AudioTrack*> &MediaInfo::getAudio() const
	{
		if (this->_Audio.empty())
		{
		   getAudioInfo();
		}
		return this->_Audio;
	}

	void MediaInfo::getAudioInfo()
	{
		if (this->_Audio.empty())
		{
			this->_Audio = std::vector<AudioTrack*>();
			int num1 = MediaInfo::MediaInfo_Count_Get(this->Handle, getAudio(), -1);
			if (num1 > 0)
			{
				int num3 = num1 - 1;
				for (int num2 = 0; num2 <= num3; num2++)
				{
					AudioTrack *_tracktemp_ = new AudioTrack();
					_tracktemp_->setCount(GetSpecificMediaInfo(getAudio(),num2,"Count"));
					_tracktemp_->setStreamCount(GetSpecificMediaInfo(getAudio(),num2,"StreamCount"));
					_tracktemp_->setStreamKind(GetSpecificMediaInfo(getAudio(),num2,"StreamKind"));
					_tracktemp_->setStreamKindString(GetSpecificMediaInfo(getAudio(), num2, "StreamKind/String"));
					_tracktemp_->setStreamKindID(GetSpecificMediaInfo(getAudio(),num2,"StreamKindID"));
					_tracktemp_->setStreamKindPos(GetSpecificMediaInfo(getAudio(), num2, "StreamKindPos"));
					_tracktemp_->setStreamOrder(GetSpecificMediaInfo(getAudio(), num2, "StreamOrder"));
					_tracktemp_->setInform(GetSpecificMediaInfo(getAudio(),num2,"Inform"));
					_tracktemp_->setID(GetSpecificMediaInfo(getAudio(),num2,"ID"));
					_tracktemp_->setIDString(GetSpecificMediaInfo(getAudio(), num2, "ID/String"));
					_tracktemp_->setUniqueID(GetSpecificMediaInfo(getAudio(),num2,"UniqueID"));
					_tracktemp_->setMenuID(GetSpecificMediaInfo(getAudio(), num2, "MenuID"));
					_tracktemp_->setMenuIDString(GetSpecificMediaInfo(getAudio(), num2, "MenuID/String"));
					_tracktemp_->setFormat(GetSpecificMediaInfo(getAudio(), num2, "Format"));
					_tracktemp_->setFormatInfo(GetSpecificMediaInfo(getAudio(), num2, "Format/Info"));
					_tracktemp_->setFormatUrl(GetSpecificMediaInfo(getAudio(), num2, "Format/Url"));
					_tracktemp_->setFormatVersion(GetSpecificMediaInfo(getAudio(), num2, "Format_Version"));
					_tracktemp_->setFormatProfile(GetSpecificMediaInfo(getAudio(), num2, "Format_Profile"));
					_tracktemp_->setFormatSettings(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings"));
					_tracktemp_->setFormatSettingsSBR(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_SBR"));
					_tracktemp_->setFormatSettingsSBRString(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_SBR/String"));
					_tracktemp_->setFormatSettingsPS(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_PS"));
					_tracktemp_->setFormatSettingsPSString(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_PS/String"));
					_tracktemp_->setFormatSettingsFloor(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_Floor"));
					_tracktemp_->setFormatSettingsFirm(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_Firm"));
					_tracktemp_->setFormatSettingsEndianness(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_Endianness"));
					_tracktemp_->setFormatSettingsSign(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_Sign"));
					_tracktemp_->setFormatSettingsLaw(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_Law"));
					_tracktemp_->setFormatSettingsITU(GetSpecificMediaInfo(getAudio(), num2, "Format_Settings_ITU"));
					_tracktemp_->setMuxingMode(GetSpecificMediaInfo(getAudio(), num2, "MuxingMode"));
					_tracktemp_->setCodecID(GetSpecificMediaInfo(getAudio(), num2, "CodecID"));
					_tracktemp_->setCodecIDInfo(GetSpecificMediaInfo(getAudio(), num2, "CodecID/Info"));
					_tracktemp_->setCodecIDUrl(GetSpecificMediaInfo(getAudio(), num2, "CodecID/Url"));
					_tracktemp_->setCodecIDHint(GetSpecificMediaInfo(getAudio(), num2, "CodecID/Hint"));
					_tracktemp_->setCodecIDDescription(GetSpecificMediaInfo(getAudio(), num2, "CodecID_Description"));
					_tracktemp_->setDuration(GetSpecificMediaInfo(getAudio(), num2, "Duration"));
					_tracktemp_->setDurationString(GetSpecificMediaInfo(getAudio(), num2, "Duration/String"));
					_tracktemp_->setDurationString1(GetSpecificMediaInfo(getAudio(), num2, "Duration/String1"));
					_tracktemp_->setDurationString2(GetSpecificMediaInfo(getAudio(), num2, "Duration/String2"));
					_tracktemp_->setDurationString3(GetSpecificMediaInfo(getAudio(), num2, "Duration/String3"));
					_tracktemp_->setBitRateMode(GetSpecificMediaInfo(getAudio(), num2, "BitRate_Mode"));
					_tracktemp_->setBitRateModeString(GetSpecificMediaInfo(getAudio(), num2, "BitRate_Mode/String"));
					_tracktemp_->setBitRate(GetSpecificMediaInfo(getAudio(), num2, "BitRate"));
					_tracktemp_->setBitRateString(GetSpecificMediaInfo(getAudio(), num2, "BitRate/String"));
					_tracktemp_->setBitRateMinimum(GetSpecificMediaInfo(getAudio(), num2, "BitRate_Minimum"));
					_tracktemp_->setBitRateMinimumString(GetSpecificMediaInfo(getAudio(), num2, "BitRate_Minimum/String"));
					_tracktemp_->setBitRateNominal(GetSpecificMediaInfo(getAudio(), num2, "BitRate_Nominal"));
					_tracktemp_->setBitRateNominalString(GetSpecificMediaInfo(getAudio(), num2, "BitRate_Nominal/String"));
					_tracktemp_->setBitRateMaximum(GetSpecificMediaInfo(getAudio(), num2, "BitRate_Maximum"));
					_tracktemp_->setBitRateMaximumString(GetSpecificMediaInfo(getAudio(), num2, "BitRate_Maximum/String"));
					_tracktemp_->setChannels(GetSpecificMediaInfo(getAudio(), num2, "Channel(s)"));
					_tracktemp_->setChannelsString(GetSpecificMediaInfo(getAudio(), num2, "Channel(s)/String"));
					_tracktemp_->setChannelMode(GetSpecificMediaInfo(getAudio(), num2, "ChannelMode"));
					_tracktemp_->setChannelPositions(GetSpecificMediaInfo(getAudio(), num2, "ChannelPositions"));
					_tracktemp_->setChannelPositionsString2(GetSpecificMediaInfo(getAudio(), num2, "ChannelPositions/String2"));
					_tracktemp_->setSamplingRate(GetSpecificMediaInfo(getAudio(), num2, "SamplingRate"));
					_tracktemp_->setSamplingRateString(GetSpecificMediaInfo(getAudio(), num2, "SamplingRate/String"));
					_tracktemp_->setSamplingCount(GetSpecificMediaInfo(getAudio(), num2, "SamplingCount"));
					_tracktemp_->setBitDepth(GetSpecificMediaInfo(getAudio(), num2, "BitDepth"));
					_tracktemp_->setBitDepthString(GetSpecificMediaInfo(getAudio(), num2, "BitDepth/String"));
					_tracktemp_->setCompressionRatio(GetSpecificMediaInfo(getAudio(), num2, "CompressionRatio"));
					_tracktemp_->setDelay(GetSpecificMediaInfo(getAudio(), num2, "Delay"));
					_tracktemp_->setDelayString(GetSpecificMediaInfo(getAudio(), num2, "Delay/String"));
					_tracktemp_->setDelayString1(GetSpecificMediaInfo(getAudio(), num2, "Delay/String1"));
					_tracktemp_->setDelayString2(GetSpecificMediaInfo(getAudio(), num2, "Delay/String2"));
					_tracktemp_->setDelayString3(GetSpecificMediaInfo(getAudio(), num2, "Delay/String3"));
					_tracktemp_->setVideoDelay(GetSpecificMediaInfo(getAudio(), num2, "Video_Delay"));
					_tracktemp_->setVideoDelayString(GetSpecificMediaInfo(getAudio(), num2, "Video_Delay/String"));
					_tracktemp_->setVideoDelayString1(GetSpecificMediaInfo(getAudio(), num2, "Video_Delay/String1"));
					_tracktemp_->setVideoDelayString2(GetSpecificMediaInfo(getAudio(), num2, "Video_Delay/String2"));
					_tracktemp_->setVideoDelayString3(GetSpecificMediaInfo(getAudio(), num2, "Video_Delay/String3"));
					_tracktemp_->setReplayGainGain(GetSpecificMediaInfo(getAudio(), num2, "ReplayGain_Gain"));
					_tracktemp_->setReplayGainGainString(GetSpecificMediaInfo(getAudio(), num2, "ReplayGain_Gain/String"));
					_tracktemp_->setReplayGainPeak(GetSpecificMediaInfo(getAudio(), num2, "ReplayGain_Peak"));
					_tracktemp_->setStreamSize(GetSpecificMediaInfo(getAudio(), num2, "StreamSize"));
					_tracktemp_->setStreamSizeString(GetSpecificMediaInfo(getAudio(), num2, "StreamSize/String"));
					_tracktemp_->setStreamSizeString1(GetSpecificMediaInfo(getAudio(), num2, "StreamSize/String1"));
					_tracktemp_->setStreamSizeString2(GetSpecificMediaInfo(getAudio(), num2, "StreamSize/String2"));
					_tracktemp_->setStreamSizeString3(GetSpecificMediaInfo(getAudio(), num2, "StreamSize/String3"));
					_tracktemp_->setStreamSizeString4(GetSpecificMediaInfo(getAudio(), num2, "StreamSize/String4"));
					_tracktemp_->setStreamSizeString5(GetSpecificMediaInfo(getAudio(), num2, "StreamSize/String5"));
					_tracktemp_->setStreamSizeProportion(GetSpecificMediaInfo(getAudio(), num2, "StreamSize_Proportion"));
					_tracktemp_->setAlignment(GetSpecificMediaInfo(getAudio(), num2, "Alignment"));
					_tracktemp_->setAlignmentString(GetSpecificMediaInfo(getAudio(), num2, "Alignment/String"));
					_tracktemp_->setInterleaveVideoFrames(GetSpecificMediaInfo(getAudio(), num2, "Interleave_VideoFrames"));
					_tracktemp_->setInterleaveDuration(GetSpecificMediaInfo(getAudio(), num2, "Interleave_Duration"));
					_tracktemp_->setInterleaveDurationString(GetSpecificMediaInfo(getAudio(), num2, "Interleave_Duration/String"));
					_tracktemp_->setInterleavePreload(GetSpecificMediaInfo(getAudio(), num2, "Interleave_Preload"));
					_tracktemp_->setInterleavePreloadString(GetSpecificMediaInfo(getAudio(), num2, "Interleave_Preload/String"));
					_tracktemp_->setTitle(GetSpecificMediaInfo(getAudio(),num2,"Title"));
					_tracktemp_->setEncodedLibrary(GetSpecificMediaInfo(getAudio(),num2,"Encoded_Library"));
					_tracktemp_->setEncodedLibraryString(GetSpecificMediaInfo(getAudio(), num2, "Encoded_Library/String"));
					_tracktemp_->setEncodedLibraryName(GetSpecificMediaInfo(getAudio(), num2, "Encoded_Library/Name"));
					_tracktemp_->setEncodedLibraryVersion(GetSpecificMediaInfo(getAudio(), num2, "Encoded_Library/Version"));
					_tracktemp_->setEncodedLibraryDate(GetSpecificMediaInfo(getAudio(), num2, "Encoded_Library/Date"));
					_tracktemp_->setEncodedLibrarySettings(GetSpecificMediaInfo(getAudio(),num2,"Encoded_Library_Settings"));
					_tracktemp_->setLanguage(GetSpecificMediaInfo(getAudio(),num2,"Language"));
					_tracktemp_->setLanguageString(GetSpecificMediaInfo(getAudio(),num2,"Language/String"));
					_tracktemp_->setLanguageMore(GetSpecificMediaInfo(getAudio(),num2,"Language_More"));
					_tracktemp_->setEncodedDate(GetSpecificMediaInfo(getAudio(), num2, "Encoded_Date"));
					_tracktemp_->setTaggedDate(GetSpecificMediaInfo(getAudio(), num2, "Tagged_Date"));
					_tracktemp_->setEncryption(GetSpecificMediaInfo(getAudio(), num2, "Encryption"));
					_tracktemp_->setDefault(GetSpecificMediaInfo(getAudio(), num2, "Default"));
					_tracktemp_->setDefaultString(GetSpecificMediaInfo(getAudio(), num2, "Default/String"));
					_tracktemp_->setForced(GetSpecificMediaInfo(getAudio(), num2, "Forced"));
					_tracktemp_->setForcedString(GetSpecificMediaInfo(getAudio(), num2, "Forced/String"));
					this->_Audio.push_back(_tracktemp_);
				}
			}
		}
	}

	const std::vector<TextTrack*> &MediaInfo::getText() const
	{
		if (this->_Text.empty())
		{
		   getTextInfo();
		}
		return this->_Text;
	}

	void MediaInfo::getTextInfo()
	{
		if (this->_Text.empty())
		{
			this->_Text = std::vector<TextTrack*>();
			int num1 = MediaInfo::MediaInfo_Count_Get(this->Handle, getText(), -1);
			if (num1 > 0)
			{
				int num3 = num1 - 1;
				for (int num2 = 0; num2 <= num3; num2++)
				{
					TextTrack *_tracktemp_ = new TextTrack();
					_tracktemp_->setCount(GetSpecificMediaInfo(getText(),num2,"Count"));
					_tracktemp_->setStreamCount(GetSpecificMediaInfo(getText(),num2,"StreamCount"));
					_tracktemp_->setStreamKind(GetSpecificMediaInfo(getText(),num2,"StreamKind"));
					_tracktemp_->setStreamKindID(GetSpecificMediaInfo(getText(),num2,"StreamKindID"));
					_tracktemp_->setStreamOrder(GetSpecificMediaInfo(getText(), num2, "StreamOrder"));
					_tracktemp_->setInform(GetSpecificMediaInfo(getText(),num2,"Inform"));
					_tracktemp_->setID(GetSpecificMediaInfo(getText(),num2,"ID"));
					_tracktemp_->setUniqueID(GetSpecificMediaInfo(getText(),num2,"UniqueID"));
					_tracktemp_->setTitle(GetSpecificMediaInfo(getText(),num2,"Title"));
					_tracktemp_->setCodec(GetSpecificMediaInfo(getText(),num2,"Codec"));
					_tracktemp_->setCodecString(GetSpecificMediaInfo(getText(),num2,"Codec/String"));
					_tracktemp_->setCodecUrl(GetSpecificMediaInfo(getText(),num2,"Codec/Url"));
					_tracktemp_->setDelay(GetSpecificMediaInfo(getText(),num2,"Delay"));
					_tracktemp_->setVideo0Delay(GetSpecificMediaInfo(getText(),num2,"Video0_Delay"));
					_tracktemp_->setPlayTime(GetSpecificMediaInfo(getText(),num2,"PlayTime"));
					_tracktemp_->setPlayTimeString(GetSpecificMediaInfo(getText(),num2,"PlayTime/String"));
					_tracktemp_->setPlayTimeString1(GetSpecificMediaInfo(getText(),num2,"PlayTime/String1"));
					_tracktemp_->setPlayTimeString2(GetSpecificMediaInfo(getText(),num2,"PlayTime/String2"));
					_tracktemp_->setPlayTimeString3(GetSpecificMediaInfo(getText(),num2,"PlayTime/String3"));
					_tracktemp_->setLanguage(GetSpecificMediaInfo(getText(),num2,"Language"));
					_tracktemp_->setLanguageString(GetSpecificMediaInfo(getText(),num2,"Language/String"));
					_tracktemp_->setLanguageMore(GetSpecificMediaInfo(getText(),num2,"Language_More"));
					_tracktemp_->setDefault(GetSpecificMediaInfo(getText(), num2, "Default"));
					_tracktemp_->setDefaultString(GetSpecificMediaInfo(getText(), num2, "Default/String"));
					_tracktemp_->setForced(GetSpecificMediaInfo(getText(), num2, "Forced"));
					_tracktemp_->setForcedString(GetSpecificMediaInfo(getText(), num2, "Forced/String"));
					 this->_Text.push_back(_tracktemp_);
				}
			}
		}
	}

	const std::vector<ChaptersTrack*> &MediaInfo::getChapters() const
	{
		if (this->_Chapters.empty())
		{
		   getChaptersInfo();
		}
		return this->_Chapters;
	}

	void MediaInfo::getChaptersInfo()
	{
		if (this->_Chapters.empty())
		{
			this->_Chapters = std::vector<ChaptersTrack*>();
			int num1 = MediaInfo::MediaInfo_Count_Get(this->Handle, getChapters(), -1);
			if (num1 > 0)
			{
				int num3 = num1 - 1;
				for (int num2 = 0; num2 <= num3; num2++)
				{
					ChaptersTrack *_tracktemp_ = new ChaptersTrack();
					_tracktemp_->setCount(GetSpecificMediaInfo(getChapters(),num2,"Count"));
					_tracktemp_->setStreamCount(GetSpecificMediaInfo(getChapters(),num2,"StreamCount"));
					_tracktemp_->setStreamKind(GetSpecificMediaInfo(getChapters(),num2,"StreamKind"));
					_tracktemp_->setStreamKindID(GetSpecificMediaInfo(getChapters(),num2,"StreamKindID"));
					_tracktemp_->setStreamOrder(GetSpecificMediaInfo(getChapters(), num2, "StreamOrder"));
					_tracktemp_->setInform(GetSpecificMediaInfo(getChapters(),num2,"Inform"));
					_tracktemp_->setID(GetSpecificMediaInfo(getChapters(),num2,"ID"));
					_tracktemp_->setUniqueID(GetSpecificMediaInfo(getChapters(),num2,"UniqueID"));
					_tracktemp_->setTitle(GetSpecificMediaInfo(getChapters(),num2,"Title"));
					_tracktemp_->setCodec(GetSpecificMediaInfo(getChapters(),num2,"Codec"));
					_tracktemp_->setCodecString(GetSpecificMediaInfo(getChapters(),num2,"Codec/String"));
					_tracktemp_->setCodecUrl(GetSpecificMediaInfo(getChapters(),num2,"Codec/Url"));
					_tracktemp_->setTotal(GetSpecificMediaInfo(getChapters(),num2,"Total"));
					_tracktemp_->setLanguage(GetSpecificMediaInfo(getChapters(),num2,"Language"));
					_tracktemp_->setLanguageString(GetSpecificMediaInfo(getChapters(),num2,"Language/String"));
					_tracktemp_->setDefault(GetSpecificMediaInfo(getChapters(), num2, "Default"));
					_tracktemp_->setDefaultString(GetSpecificMediaInfo(getChapters(), num2, "Default/String"));
					_tracktemp_->setForced(GetSpecificMediaInfo(getChapters(), num2, "Forced"));
					_tracktemp_->setForcedString(GetSpecificMediaInfo(getChapters(), num2, "Forced/String"));
					this->_Chapters.push_back(_tracktemp_);
				}
			}
		}
	}
}
