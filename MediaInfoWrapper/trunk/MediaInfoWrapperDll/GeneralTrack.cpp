#include "GeneralTrack.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{

	const std::string &GeneralTrack::getCount() const
	{
		if (this->_Count.empty())
			this->_Count = "";
		return _Count;
	}

	void GeneralTrack::setCount(const std::string &value)
	{
		this->_Count = value;
	}

	const std::string &GeneralTrack::getStreamCount() const
	{
		if (this->_StreamCount.empty())
			this->_StreamCount = "";
		return _StreamCount;
	}

	void GeneralTrack::setStreamCount(const std::string &value)
	{
		this->_StreamCount = value;
	}

	const std::string &GeneralTrack::getPGCCount() const
	{
		if (this->_PGCCount.empty())
			this->_PGCCount = "";
		return _PGCCount;
	}

	void GeneralTrack::setPGCCount(const std::string &value)
	{
		this->_PGCCount = value;
	}

	const std::string &GeneralTrack::getPGCNumber() const
	{
		if (this->_PGCNumber.empty())
			this->_PGCNumber = "";
		return _PGCNumber;
	}

	void GeneralTrack::setPGCNumber(const std::string &value)
	{
		this->_PGCNumber = value;
	}

	const std::string &GeneralTrack::getStreamKind() const
	{
		if (this->_StreamKind.empty())
			this->_StreamKind = "";
		return _StreamKind;
	}

	void GeneralTrack::setStreamKind(const std::string &value)
	{
		this->_StreamKind = value;
	}

	const std::string &GeneralTrack::getStreamKindID() const
	{
		if (this->_StreamKindID.empty())
			this->_StreamKindID = "";
		return _StreamKindID;
	}

	void GeneralTrack::setStreamKindID(const std::string &value)
	{
		this->_StreamKindID = value;
	}

	const std::string &GeneralTrack::getStreamOrder() const
	{
		if (this->_StreamOrder.empty())
			this->_StreamOrder = "";
		return _StreamOrder;
	}

	void GeneralTrack::setStreamOrder(const std::string &value)
	{
		this->_StreamOrder = value;
	}

	const std::string &GeneralTrack::getInform() const
	{
		if (this->_Inform.empty())
			this->_Inform = "";
		return _Inform;
	}

	void GeneralTrack::setInform(const std::string &value)
	{
		this->_Inform = value;
	}

	const std::string &GeneralTrack::getID() const
	{
		if (this->_ID.empty())
			this->_ID = "";
		return _ID;
	}

	void GeneralTrack::setID(const std::string &value)
	{
		this->_ID = value;
	}

	const std::string &GeneralTrack::getUniqueID() const
	{
		if (this->_UniqueID.empty())
			this->_UniqueID = "";
		return _UniqueID;
	}

	void GeneralTrack::setUniqueID(const std::string &value)
	{
		this->_UniqueID = value;
	}

	const std::string &GeneralTrack::getGeneralCount() const
	{
		if (this->_GeneralCount.empty())
			this->_GeneralCount = "";
		return _GeneralCount;
	}

	void GeneralTrack::setGeneralCount(const std::string &value)
	{
		this->_GeneralCount = value;
	}

	const std::string &GeneralTrack::getVideoCount() const
	{
		if (this->_VideoCount.empty())
			this->_VideoCount = "";
		return _VideoCount;
	}

	void GeneralTrack::setVideoCount(const std::string &value)
	{
		this->_VideoCount = value;
	}

	const std::string &GeneralTrack::getAudioCount() const
	{
		if (this->_AudioCount.empty())
			this->_AudioCount = "";
		return _AudioCount;
	}

	void GeneralTrack::setAudioCount(const std::string &value)
	{
		this->_AudioCount = value;
	}

	const std::string &GeneralTrack::getTextCount() const
	{
		if (this->_TextCount.empty())
			this->_TextCount = "";
		return _TextCount;
	}

	void GeneralTrack::setTextCount(const std::string &value)
	{
		this->_TextCount = value;
	}

	const std::string &GeneralTrack::getChaptersCount() const
	{
		if (this->_ChaptersCount.empty())
			this->_ChaptersCount = "";
		return _ChaptersCount;
	}

	void GeneralTrack::setChaptersCount(const std::string &value)
	{
		this->_ChaptersCount = value;
	}

	const std::string &GeneralTrack::getImageCount() const
	{
		if (this->_ImageCount.empty())
			this->_ImageCount = "";
		return _ImageCount;
	}

	void GeneralTrack::setImageCount(const std::string &value)
	{
		this->_ImageCount = value;
	}

	const std::string &GeneralTrack::getCompleteName() const
	{
		if (this->_CompleteName.empty())
			this->_CompleteName = "";
		return _CompleteName;
	}

	void GeneralTrack::setCompleteName(const std::string &value)
	{
		this->_CompleteName = value;
	}

	const std::string &GeneralTrack::getFolderName() const
	{
		if (this->_FolderName.empty())
			this->_FolderName = "";
		return _FolderName;
	}

	void GeneralTrack::setFolderName(const std::string &value)
	{
		this->_FolderName = value;
	}

	const std::string &GeneralTrack::getFileName() const
	{
		if (this->_FileName.empty())
			this->_FileName = "";
		return _FileName;
	}

	void GeneralTrack::setFileName(const std::string &value)
	{
		this->_FileName = value;
	}

	const std::string &GeneralTrack::getFileExtension() const
	{
		if (this->_FileExtension.empty())
			this->_FileExtension = "";
		return _FileExtension;
	}

	void GeneralTrack::setFileExtension(const std::string &value)
	{
		this->_FileExtension = value;
	}

	const std::string &GeneralTrack::getFileSize() const
	{
		if (this->_FileSize.empty())
			this->_FileSize = "";
		return _FileSize;
	}

	void GeneralTrack::setFileSize(const std::string &value)
	{
		this->_FileSize = value;
	}

	const std::string &GeneralTrack::getFileSizeString() const
	{
		if (this->_FileSizeString.empty())
			this->_FileSizeString = "";
		return _FileSizeString;
	}

	void GeneralTrack::setFileSizeString(const std::string &value)
	{
		this->_FileSizeString = value;
	}

	const std::string &GeneralTrack::getFileSizeString1() const
	{
		if (this->_FileSizeString1.empty())
			this->_FileSizeString1 = "";
		return _FileSizeString1;
	}

	void GeneralTrack::setFileSizeString1(const std::string &value)
	{
		this->_FileSizeString1 = value;
	}

	const std::string &GeneralTrack::getFileSizeString2() const
	{
		if (this->_FileSizeString2.empty())
			this->_FileSizeString2 = "";
		return _FileSizeString2;
	}

	void GeneralTrack::setFileSizeString2(const std::string &value)
	{
		this->_FileSizeString2 = value;
	}

	const std::string &GeneralTrack::getFileSizeString3() const
	{
		if (this->_FileSizeString3.empty())
			this->_FileSizeString3 = "";
		return _FileSizeString3;
	}

	void GeneralTrack::setFileSizeString3(const std::string &value)
	{
		this->_FileSizeString3 = value;
	}

	const std::string &GeneralTrack::getFileSizeString4() const
	{
		if (this->_FileSizeString4.empty())
			this->_FileSizeString4 = "";
		return _FileSizeString4;
	}

	void GeneralTrack::setFileSizeString4(const std::string &value)
	{
		this->_FileSizeString4 = value;
	}

	const std::string &GeneralTrack::getFormat() const
	{
		if (this->_Format.empty())
			this->_Format = "";
		return _Format;
	}

	void GeneralTrack::setFormat(const std::string &value)
	{
		this->_Format = value;
	}

	const std::string &GeneralTrack::getFormatString() const
	{
		if (this->_FormatString.empty())
			this->_FormatString = "";
		return _FormatString;
	}

	void GeneralTrack::setFormatString(const std::string &value)
	{
		this->_FormatString = value;
	}

	const std::string &GeneralTrack::getFormatInfo() const
	{
		if (this->_FormatInfo.empty())
			this->_FormatInfo = "";
		return _FormatInfo;
	}

	void GeneralTrack::setFormatInfo(const std::string &value)
	{
		this->_FormatInfo = value;
	}

	const std::string &GeneralTrack::getFormatUrl() const
	{
		if (this->_FormatUrl.empty())
			this->_FormatUrl = "";
		return _FormatUrl;
	}

	void GeneralTrack::setFormatUrl(const std::string &value)
	{
		this->_FormatUrl = value;
	}

	const std::string &GeneralTrack::getFormatExtensions() const
	{
		if (this->_FormatExtensions.empty())
			this->_FormatExtensions = "";
		return _FormatExtensions;
	}

	void GeneralTrack::setFormatExtensions(const std::string &value)
	{
		this->_FormatExtensions = value;
	}

	const std::string &GeneralTrack::getOveralBitRate() const
	{
		if (this->_OveralBitRate.empty())
			this->_OveralBitRate = "";
		return _OveralBitRate;
	}

	void GeneralTrack::setOveralBitRate(const std::string &value)
	{
		this->_OveralBitRate = value;
	}

	const std::string &GeneralTrack::getOveralBitRateString() const
	{
		if (this->_OveralBitRateString.empty())
			this->_OveralBitRateString = "";
		return _OveralBitRateString;
	}

	void GeneralTrack::setOveralBitRateString(const std::string &value)
	{
		this->_OveralBitRateString = value;
	}

	const std::string &GeneralTrack::getPlayTime() const
	{
		if (this->_PlayTime.empty())
			this->_PlayTime = "";
		return _PlayTime;
	}

	void GeneralTrack::setPlayTime(const std::string &value)
	{
		this->_PlayTime = value;
	}

	const std::string &GeneralTrack::getPlayTimeString() const
	{
		if (this->_PlayTimeString.empty())
			this->_PlayTimeString = "";
		return _PlayTimeString;
	}

	void GeneralTrack::setPlayTimeString(const std::string &value)
	{
		this->_PlayTimeString = value;
	}

	const std::string &GeneralTrack::getPlayTimeString1() const
	{
		if (this->_PlayTimeString1.empty())
			this->_PlayTimeString1 = "";
		return _PlayTimeString1;
	}

	void GeneralTrack::setPlayTimeString1(const std::string &value)
	{
		this->_PlayTimeString1 = value;
	}

	const std::string &GeneralTrack::getPlayTimeString2() const
	{
		if (this->_PlayTimeString2.empty())
			this->_PlayTimeString2 = "";
		return _PlayTimeString2;
	}

	void GeneralTrack::setPlayTimeString2(const std::string &value)
	{
		this->_PlayTimeString2 = value;
	}

	const std::string &GeneralTrack::getPlayTimeString3() const
	{
		if (this->_PlayTimeString3.empty())
			this->_PlayTimeString3 = "";
		return _PlayTimeString3;
	}

	void GeneralTrack::setPlayTimeString3(const std::string &value)
	{
		this->_PlayTimeString3 = value;
	}

	const std::string &GeneralTrack::getTitle() const
	{
		if (this->_Title.empty())
			this->_Title = "";
		return _Title;
	}

	void GeneralTrack::setTitle(const std::string &value)
	{
		this->_Title = value;
	}

	const std::string &GeneralTrack::getTitleMore() const
	{
		if (this->_TitleMore.empty())
			this->_TitleMore = "";
		return _TitleMore;
	}

	void GeneralTrack::setTitleMore(const std::string &value)
	{
		this->_TitleMore = value;
	}

	const std::string &GeneralTrack::getDomain() const
	{
		if (this->_Domain.empty())
			this->_Domain = "";
		return _Domain;
	}

	void GeneralTrack::setDomain(const std::string &value)
	{
		this->_Domain = value;
	}

	const std::string &GeneralTrack::getCollection() const
	{
		if (this->_Collection.empty())
			this->_Collection = "";
		return _Collection;
	}

	void GeneralTrack::setCollection(const std::string &value)
	{
		this->_Collection = value;
	}

	const std::string &GeneralTrack::getCollectionTotalParts() const
	{
		if (this->_CollectionTotalParts.empty())
			this->_CollectionTotalParts = "";
		return _CollectionTotalParts;
	}

	void GeneralTrack::setCollectionTotalParts(const std::string &value)
	{
		this->_CollectionTotalParts = value;
	}

	const std::string &GeneralTrack::getSeason() const
	{
		if (this->_Season.empty())
			this->_Season = "";
		return _Season;
	}

	void GeneralTrack::setSeason(const std::string &value)
	{
		this->_Season = value;
	}

	const std::string &GeneralTrack::getMovie() const
	{
		if (this->_Movie.empty())
			this->_Movie = "";
		return _Movie;
	}

	void GeneralTrack::setMovie(const std::string &value)
	{
		this->_Movie = value;
	}

	const std::string &GeneralTrack::getMovieMore() const
	{
		if (this->_MovieMore.empty())
			this->_MovieMore = "";
		return _MovieMore;
	}

	void GeneralTrack::setMovieMore(const std::string &value)
	{
		this->_MovieMore = value;
	}

	const std::string &GeneralTrack::getAlbum() const
	{
		if (this->_Album.empty())
			this->_Album = "";
		return _Album;
	}

	void GeneralTrack::setAlbum(const std::string &value)
	{
		this->_Album = value;
	}

	const std::string &GeneralTrack::getAlbumTotalParts() const
	{
		if (this->_AlbumTotalParts.empty())
			this->_AlbumTotalParts = "";
		return _AlbumTotalParts;
	}

	void GeneralTrack::setAlbumTotalParts(const std::string &value)
	{
		this->_AlbumTotalParts = value;
	}

	const std::string &GeneralTrack::getAlbumSort() const
	{
		if (this->_AlbumSort.empty())
			this->_AlbumSort = "";
		return _AlbumSort;
	}

	void GeneralTrack::setAlbumSort(const std::string &value)
	{
		this->_AlbumSort = value;
	}

	const std::string &GeneralTrack::getComic() const
	{
		if (this->_Comic.empty())
			this->_Comic = "";
		return _Comic;
	}

	void GeneralTrack::setComic(const std::string &value)
	{
		this->_Comic = value;
	}

	const std::string &GeneralTrack::getComicTotalParts() const
	{
		if (this->_ComicTotalParts.empty())
			this->_ComicTotalParts = "";
		return _ComicTotalParts;
	}

	void GeneralTrack::setComicTotalParts(const std::string &value)
	{
		this->_ComicTotalParts = value;
	}

	const std::string &GeneralTrack::getPart() const
	{
		if (this->_Part.empty())
			this->_Part = "";
		return _Part;
	}

	void GeneralTrack::setPart(const std::string &value)
	{
		this->_Part = value;
	}

	const std::string &GeneralTrack::getPartTotalParts() const
	{
		if (this->_PartTotalParts.empty())
			this->_PartTotalParts = "";
		return _PartTotalParts;
	}

	void GeneralTrack::setPartTotalParts(const std::string &value)
	{
		this->_PartTotalParts = value;
	}

	const std::string &GeneralTrack::getPartPosition() const
	{
		if (this->_PartPosition.empty())
			this->_PartPosition = "";
		return _PartPosition;
	}

	void GeneralTrack::setPartPosition(const std::string &value)
	{
		this->_PartPosition = value;
	}

	const std::string &GeneralTrack::getTrack() const
	{
		if (this->_Track.empty())
			this->_Track = "";
		return _Track;
	}

	void GeneralTrack::setTrack(const std::string &value)
	{
		this->_Track = value;
	}

	const std::string &GeneralTrack::getTrackPosition() const
	{
		if (this->_TrackPosition.empty())
			this->_TrackPosition = "";
		return _TrackPosition;
	}

	void GeneralTrack::setTrackPosition(const std::string &value)
	{
		this->_TrackPosition = value;
	}

	const std::string &GeneralTrack::getTrackMore() const
	{
		if (this->_TrackMore.empty())
			this->_TrackMore = "";
		return _TrackMore;
	}

	void GeneralTrack::setTrackMore(const std::string &value)
	{
		this->_TrackMore = value;
	}

	const std::string &GeneralTrack::getTrackSort() const
	{
		if (this->_TrackSort.empty())
			this->_TrackSort = "";
		return _TrackSort;
	}

	void GeneralTrack::setTrackSort(const std::string &value)
	{
		this->_TrackSort = value;
	}

	const std::string &GeneralTrack::getChapter() const
	{
		if (this->_Chapter.empty())
			this->_Chapter = "";
		return _Chapter;
	}

	void GeneralTrack::setChapter(const std::string &value)
	{
		this->_Chapter = value;
	}

	const std::string &GeneralTrack::getSubTrack() const
	{
		if (this->_SubTrack.empty())
			this->_SubTrack = "";
		return _SubTrack;
	}

	void GeneralTrack::setSubTrack(const std::string &value)
	{
		this->_SubTrack = value;
	}

	const std::string &GeneralTrack::getOriginalAlbum() const
	{
		if (this->_OriginalAlbum.empty())
			this->_OriginalAlbum = "";
		return _OriginalAlbum;
	}

	void GeneralTrack::setOriginalAlbum(const std::string &value)
	{
		this->_OriginalAlbum = value;
	}

	const std::string &GeneralTrack::getOriginalMovie() const
	{
		if (this->_OriginalMovie.empty())
			this->_OriginalMovie = "";
		return _OriginalMovie;
	}

	void GeneralTrack::setOriginalMovie(const std::string &value)
	{
		this->_OriginalMovie = value;
	}

	const std::string &GeneralTrack::getOriginalPart() const
	{
		if (this->_OriginalPart.empty())
			this->_OriginalPart = "";
		return _OriginalPart;
	}

	void GeneralTrack::setOriginalPart(const std::string &value)
	{
		this->_OriginalPart = value;
	}

	const std::string &GeneralTrack::getOriginalTrack() const
	{
		if (this->_OriginalTrack.empty())
			this->_OriginalTrack = "";
		return _OriginalTrack;
	}

	void GeneralTrack::setOriginalTrack(const std::string &value)
	{
		this->_OriginalTrack = value;
	}

	const std::string &GeneralTrack::getAuthor() const
	{
		if (this->_Author.empty())
			this->_Author = "";
		return _Author;
	}

	void GeneralTrack::setAuthor(const std::string &value)
	{
		this->_Author = value;
	}

	const std::string &GeneralTrack::getArtist() const
	{
		if (this->_Artist.empty())
			this->_Artist = "";
		return _Artist;
	}

	void GeneralTrack::setArtist(const std::string &value)
	{
		this->_Artist = value;
	}

	const std::string &GeneralTrack::getPerformerSort() const
	{
		if (this->_PerformerSort.empty())
			this->_PerformerSort = "";
		return _PerformerSort;
	}

	void GeneralTrack::setPerformerSort(const std::string &value)
	{
		this->_PerformerSort = value;
	}

	const std::string &GeneralTrack::getOriginalPerformer() const
	{
		if (this->_OriginalPerformer.empty())
			this->_OriginalPerformer = "";
		return _OriginalPerformer;
	}

	void GeneralTrack::setOriginalPerformer(const std::string &value)
	{
		this->_OriginalPerformer = value;
	}

	const std::string &GeneralTrack::getAccompaniment() const
	{
		if (this->_Accompaniment.empty())
			this->_Accompaniment = "";
		return _Accompaniment;
	}

	void GeneralTrack::setAccompaniment(const std::string &value)
	{
		this->_Accompaniment = value;
	}

	const std::string &GeneralTrack::getMusicianInstrument() const
	{
		if (this->_MusicianInstrument.empty())
			this->_MusicianInstrument = "";
		return _MusicianInstrument;
	}

	void GeneralTrack::setMusicianInstrument(const std::string &value)
	{
		this->_MusicianInstrument = value;
	}

	const std::string &GeneralTrack::getComposer() const
	{
		if (this->_Composer.empty())
			this->_Composer = "";
		return _Composer;
	}

	void GeneralTrack::setComposer(const std::string &value)
	{
		this->_Composer = value;
	}

	const std::string &GeneralTrack::getComposerNationality() const
	{
		if (this->_ComposerNationality.empty())
			this->_ComposerNationality = "";
		return _ComposerNationality;
	}

	void GeneralTrack::setComposerNationality(const std::string &value)
	{
		this->_ComposerNationality = value;
	}

	const std::string &GeneralTrack::getArranger() const
	{
		if (this->_Arranger.empty())
			this->_Arranger = "";
		return _Arranger;
	}

	void GeneralTrack::setArranger(const std::string &value)
	{
		this->_Arranger = value;
	}

	const std::string &GeneralTrack::getLyricist() const
	{
		if (this->_Lyricist.empty())
			this->_Lyricist = "";
		return _Lyricist;
	}

	void GeneralTrack::setLyricist(const std::string &value)
	{
		this->_Lyricist = value;
	}

	const std::string &GeneralTrack::getOriginalLyricist() const
	{
		if (this->_OriginalLyricist.empty())
			this->_OriginalLyricist = "";
		return _OriginalLyricist;
	}

	void GeneralTrack::setOriginalLyricist(const std::string &value)
	{
		this->_OriginalLyricist = value;
	}

	const std::string &GeneralTrack::getConductor() const
	{
		if (this->_Conductor.empty())
			this->_Conductor = "";
		return _Conductor;
	}

	void GeneralTrack::setConductor(const std::string &value)
	{
		this->_Conductor = value;
	}

	const std::string &GeneralTrack::getActor() const
	{
		if (this->_Actor.empty())
			this->_Actor = "";
		return _Actor;
	}

	void GeneralTrack::setActor(const std::string &value)
	{
		this->_Actor = value;
	}

	const std::string &GeneralTrack::getActorCharacter() const
	{
		if (this->_ActorCharacter.empty())
			this->_ActorCharacter = "";
		return _ActorCharacter;
	}

	void GeneralTrack::setActorCharacter(const std::string &value)
	{
		this->_ActorCharacter = value;
	}

	const std::string &GeneralTrack::getWrittenBy() const
	{
		if (this->_WrittenBy.empty())
			this->_WrittenBy = "";
		return _WrittenBy;
	}

	void GeneralTrack::setWrittenBy(const std::string &value)
	{
		this->_WrittenBy = value;
	}

	const std::string &GeneralTrack::getScreenplayBy() const
	{
		if (this->_ScreenplayBy.empty())
			this->_ScreenplayBy = "";
		return _ScreenplayBy;
	}

	void GeneralTrack::setScreenplayBy(const std::string &value)
	{
		this->_ScreenplayBy = value;
	}

	const std::string &GeneralTrack::getDirector() const
	{
		if (this->_Director.empty())
			this->_Director = "";
		return _Director;
	}

	void GeneralTrack::setDirector(const std::string &value)
	{
		this->_Director = value;
	}

	const std::string &GeneralTrack::getAssistantDirector() const
	{
		if (this->_AssistantDirector.empty())
			this->_AssistantDirector = "";
		return _AssistantDirector;
	}

	void GeneralTrack::setAssistantDirector(const std::string &value)
	{
		this->_AssistantDirector = value;
	}

	const std::string &GeneralTrack::getDirectorOfPhotography() const
	{
		if (this->_DirectorOfPhotography.empty())
			this->_DirectorOfPhotography = "";
		return _DirectorOfPhotography;
	}

	void GeneralTrack::setDirectorOfPhotography(const std::string &value)
	{
		this->_DirectorOfPhotography = value;
	}

	const std::string &GeneralTrack::getArtDirector() const
	{
		if (this->_ArtDirector.empty())
			this->_ArtDirector = "";
		return _ArtDirector;
	}

	void GeneralTrack::setArtDirector(const std::string &value)
	{
		this->_ArtDirector = value;
	}

	const std::string &GeneralTrack::getEditedBy() const
	{
		if (this->_EditedBy.empty())
			this->_EditedBy = "";
		return _EditedBy;
	}

	void GeneralTrack::setEditedBy(const std::string &value)
	{
		this->_EditedBy = value;
	}

	const std::string &GeneralTrack::getProducer() const
	{
		if (this->_Producer.empty())
			this->_Producer = "";
		return _Producer;
	}

	void GeneralTrack::setProducer(const std::string &value)
	{
		this->_Producer = value;
	}

	const std::string &GeneralTrack::getCoProducer() const
	{
		if (this->_CoProducer.empty())
			this->_CoProducer = "";
		return _CoProducer;
	}

	void GeneralTrack::setCoProducer(const std::string &value)
	{
		this->_CoProducer = value;
	}

	const std::string &GeneralTrack::getExecutiveProducer() const
	{
		if (this->_ExecutiveProducer.empty())
			this->_ExecutiveProducer = "";
		return _ExecutiveProducer;
	}

	void GeneralTrack::setExecutiveProducer(const std::string &value)
	{
		this->_ExecutiveProducer = value;
	}

	const std::string &GeneralTrack::getProductionDesigner() const
	{
		if (this->_ProductionDesigner.empty())
			this->_ProductionDesigner = "";
		return _ProductionDesigner;
	}

	void GeneralTrack::setProductionDesigner(const std::string &value)
	{
		this->_ProductionDesigner = value;
	}

	const std::string &GeneralTrack::getCostumeDesigner() const
	{
		if (this->_CostumeDesigner.empty())
			this->_CostumeDesigner = "";
		return _CostumeDesigner;
	}

	void GeneralTrack::setCostumeDesigner(const std::string &value)
	{
		this->_CostumeDesigner = value;
	}

	const std::string &GeneralTrack::getChoregrapher() const
	{
		if (this->_Choregrapher.empty())
			this->_Choregrapher = "";
		return _Choregrapher;
	}

	void GeneralTrack::setChoregrapher(const std::string &value)
	{
		this->_Choregrapher = value;
	}

	const std::string &GeneralTrack::getSoundEngineer() const
	{
		if (this->_SoundEngineer.empty())
			this->_SoundEngineer = "";
		return _SoundEngineer;
	}

	void GeneralTrack::setSoundEngineer(const std::string &value)
	{
		this->_SoundEngineer = value;
	}

	const std::string &GeneralTrack::getMasteredBy() const
	{
		if (this->_MasteredBy.empty())
			this->_MasteredBy = "";
		return _MasteredBy;
	}

	void GeneralTrack::setMasteredBy(const std::string &value)
	{
		this->_MasteredBy = value;
	}

	const std::string &GeneralTrack::getRemixedBy() const
	{
		if (this->_RemixedBy.empty())
			this->_RemixedBy = "";
		return _RemixedBy;
	}

	void GeneralTrack::setRemixedBy(const std::string &value)
	{
		this->_RemixedBy = value;
	}

	const std::string &GeneralTrack::getProductionStudio() const
	{
		if (this->_ProductionStudio.empty())
			this->_ProductionStudio = "";
		return _ProductionStudio;
	}

	void GeneralTrack::setProductionStudio(const std::string &value)
	{
		this->_ProductionStudio = value;
	}

	const std::string &GeneralTrack::getPublisher() const
	{
		if (this->_Publisher.empty())
			this->_Publisher = "";
		return _Publisher;
	}

	void GeneralTrack::setPublisher(const std::string &value)
	{
		this->_Publisher = value;
	}

	const std::string &GeneralTrack::getPublisherURL() const
	{
		if (this->_PublisherURL.empty())
			this->_PublisherURL = "";
		return _PublisherURL;
	}

	void GeneralTrack::setPublisherURL(const std::string &value)
	{
		this->_PublisherURL = value;
	}

	const std::string &GeneralTrack::getDistributedBy() const
	{
		if (this->_DistributedBy.empty())
			this->_DistributedBy = "";
		return _DistributedBy;
	}

	void GeneralTrack::setDistributedBy(const std::string &value)
	{
		this->_DistributedBy = value;
	}

	const std::string &GeneralTrack::getEncodedBy() const
	{
		if (this->_EncodedBy.empty())
			this->_EncodedBy = "";
		return _EncodedBy;
	}

	void GeneralTrack::setEncodedBy(const std::string &value)
	{
		this->_EncodedBy = value;
	}

	const std::string &GeneralTrack::getThanksTo() const
	{
		if (this->_ThanksTo.empty())
			this->_ThanksTo = "";
		return _ThanksTo;
	}

	void GeneralTrack::setThanksTo(const std::string &value)
	{
		this->_ThanksTo = value;
	}

	const std::string &GeneralTrack::getTechnician() const
	{
		if (this->_Technician.empty())
			this->_Technician = "";
		return _Technician;
	}

	void GeneralTrack::setTechnician(const std::string &value)
	{
		this->_Technician = value;
	}

	const std::string &GeneralTrack::getCommissionedBy() const
	{
		if (this->_CommissionedBy.empty())
			this->_CommissionedBy = "";
		return _CommissionedBy;
	}

	void GeneralTrack::setCommissionedBy(const std::string &value)
	{
		this->_CommissionedBy = value;
	}

	const std::string &GeneralTrack::getEncodedOriginalDistributedBy() const
	{
		if (this->_EncodedOriginalDistributedBy.empty())
			this->_EncodedOriginalDistributedBy = "";
		return _EncodedOriginalDistributedBy;
	}

	void GeneralTrack::setEncodedOriginalDistributedBy(const std::string &value)
	{
		this->_EncodedOriginalDistributedBy = value;
	}

	const std::string &GeneralTrack::getRadioStation() const
	{
		if (this->_RadioStation.empty())
			this->_RadioStation = "";
		return _RadioStation;
	}

	void GeneralTrack::setRadioStation(const std::string &value)
	{
		this->_RadioStation = value;
	}

	const std::string &GeneralTrack::getRadioStationOwner() const
	{
		if (this->_RadioStationOwner.empty())
			this->_RadioStationOwner = "";
		return _RadioStationOwner;
	}

	void GeneralTrack::setRadioStationOwner(const std::string &value)
	{
		this->_RadioStationOwner = value;
	}

	const std::string &GeneralTrack::getRadioStationURL() const
	{
		if (this->_RadioStationURL.empty())
			this->_RadioStationURL = "";
		return _RadioStationURL;
	}

	void GeneralTrack::setRadioStationURL(const std::string &value)
	{
		this->_RadioStationURL = value;
	}

	const std::string &GeneralTrack::getContentType() const
	{
		if (this->_ContentType.empty())
			this->_ContentType = "";
		return _ContentType;
	}

	void GeneralTrack::setContentType(const std::string &value)
	{
		this->_ContentType = value;
	}

	const std::string &GeneralTrack::getSubject() const
	{
		if (this->_Subject.empty())
			this->_Subject = "";
		return _Subject;
	}

	void GeneralTrack::setSubject(const std::string &value)
	{
		this->_Subject = value;
	}

	const std::string &GeneralTrack::getSynopsys() const
	{
		if (this->_Synopsys.empty())
			this->_Synopsys = "";
		return _Synopsys;
	}

	void GeneralTrack::setSynopsys(const std::string &value)
	{
		this->_Synopsys = value;
	}

	const std::string &GeneralTrack::getSummary() const
	{
		if (this->_Summary.empty())
			this->_Summary = "";
		return _Summary;
	}

	void GeneralTrack::setSummary(const std::string &value)
	{
		this->_Summary = value;
	}

	const std::string &GeneralTrack::getDescription() const
	{
		if (this->_Description.empty())
			this->_Description = "";
		return _Description;
	}

	void GeneralTrack::setDescription(const std::string &value)
	{
		this->_Description = value;
	}

	const std::string &GeneralTrack::getKeywords() const
	{
		if (this->_Keywords.empty())
			this->_Keywords = "";
		return _Keywords;
	}

	void GeneralTrack::setKeywords(const std::string &value)
	{
		this->_Keywords = value;
	}

	const std::string &GeneralTrack::getPeriod() const
	{
		if (this->_Period.empty())
			this->_Period = "";
		return _Period;
	}

	void GeneralTrack::setPeriod(const std::string &value)
	{
		this->_Period = value;
	}

	const std::string &GeneralTrack::getLawRating() const
	{
		if (this->_LawRating.empty())
			this->_LawRating = "";
		return _LawRating;
	}

	void GeneralTrack::setLawRating(const std::string &value)
	{
		this->_LawRating = value;
	}

	const std::string &GeneralTrack::getIRCA() const
	{
		if (this->_IRCA.empty())
			this->_IRCA = "";
		return _IRCA;
	}

	void GeneralTrack::setIRCA(const std::string &value)
	{
		this->_IRCA = value;
	}

	const std::string &GeneralTrack::getLanguage() const
	{
		if (this->_Language.empty())
			this->_Language = "";
		return _Language;
	}

	void GeneralTrack::setLanguage(const std::string &value)
	{
		this->_Language = value;
	}

	const std::string &GeneralTrack::getMedium() const
	{
		if (this->_Medium.empty())
			this->_Medium = "";
		return _Medium;
	}

	void GeneralTrack::setMedium(const std::string &value)
	{
		this->_Medium = value;
	}

	const std::string &GeneralTrack::getProduct() const
	{
		if (this->_Product.empty())
			this->_Product = "";
		return _Product;
	}

	void GeneralTrack::setProduct(const std::string &value)
	{
		this->_Product = value;
	}

	const std::string &GeneralTrack::getCountry() const
	{
		if (this->_Country.empty())
			this->_Country = "";
		return _Country;
	}

	void GeneralTrack::setCountry(const std::string &value)
	{
		this->_Country = value;
	}

	const std::string &GeneralTrack::getWrittenDate() const
	{
		if (this->_WrittenDate.empty())
			this->_WrittenDate = "";
		return _WrittenDate;
	}

	void GeneralTrack::setWrittenDate(const std::string &value)
	{
		this->_WrittenDate = value;
	}

	const std::string &GeneralTrack::getRecordedDate() const
	{
		if (this->_RecordedDate.empty())
			this->_RecordedDate = "";
		return _RecordedDate;
	}

	void GeneralTrack::setRecordedDate(const std::string &value)
	{
		this->_RecordedDate = value;
	}

	const std::string &GeneralTrack::getReleasedDate() const
	{
		if (this->_ReleasedDate.empty())
			this->_ReleasedDate = "";
		return _ReleasedDate;
	}

	void GeneralTrack::setReleasedDate(const std::string &value)
	{
		this->_ReleasedDate = value;
	}

	const std::string &GeneralTrack::getMasteredDate() const
	{
		if (this->_MasteredDate.empty())
			this->_MasteredDate = "";
		return _MasteredDate;
	}

	void GeneralTrack::setMasteredDate(const std::string &value)
	{
		this->_MasteredDate = value;
	}

	const std::string &GeneralTrack::getEncodedDate() const
	{
		if (this->_EncodedDate.empty())
			this->_EncodedDate = "";
		return _EncodedDate;
	}

	void GeneralTrack::setEncodedDate(const std::string &value)
	{
		this->_EncodedDate = value;
	}

	const std::string &GeneralTrack::getTaggedDate() const
	{
		if (this->_TaggedDate.empty())
			this->_TaggedDate = "";
		return _TaggedDate;
	}

	void GeneralTrack::setTaggedDate(const std::string &value)
	{
		this->_TaggedDate = value;
	}

	const std::string &GeneralTrack::getOriginalReleasedDate() const
	{
		if (this->_OriginalReleasedDate.empty())
			this->_OriginalReleasedDate = "";
		return _OriginalReleasedDate;
	}

	void GeneralTrack::setOriginalReleasedDate(const std::string &value)
	{
		this->_OriginalReleasedDate = value;
	}

	const std::string &GeneralTrack::getOriginalRecordedDate() const
	{
		if (this->_OriginalRecordedDate.empty())
			this->_OriginalRecordedDate = "";
		return _OriginalRecordedDate;
	}

	void GeneralTrack::setOriginalRecordedDate(const std::string &value)
	{
		this->_OriginalRecordedDate = value;
	}

	const std::string &GeneralTrack::getWrittenLocation() const
	{
		if (this->_WrittenLocation.empty())
			this->_WrittenLocation = "";
		return _WrittenLocation;
	}

	void GeneralTrack::setWrittenLocation(const std::string &value)
	{
		this->_WrittenLocation = value;
	}

	const std::string &GeneralTrack::getRecordedLocation() const
	{
		if (this->_RecordedLocation.empty())
			this->_RecordedLocation = "";
		return _RecordedLocation;
	}

	void GeneralTrack::setRecordedLocation(const std::string &value)
	{
		this->_RecordedLocation = value;
	}

	const std::string &GeneralTrack::getArchivalLocation() const
	{
		if (this->_ArchivalLocation.empty())
			this->_ArchivalLocation = "";
		return _ArchivalLocation;
	}

	void GeneralTrack::setArchivalLocation(const std::string &value)
	{
		this->_ArchivalLocation = value;
	}

	const std::string &GeneralTrack::getGenre() const
	{
		if (this->_Genre.empty())
			this->_Genre = "";
		return _Genre;
	}

	void GeneralTrack::setGenre(const std::string &value)
	{
		this->_Genre = value;
	}

	const std::string &GeneralTrack::getMood() const
	{
		if (this->_Mood.empty())
			this->_Mood = "";
		return _Mood;
	}

	void GeneralTrack::setMood(const std::string &value)
	{
		this->_Mood = value;
	}

	const std::string &GeneralTrack::getComment() const
	{
		if (this->_Comment.empty())
			this->_Comment = "";
		return _Comment;
	}

	void GeneralTrack::setComment(const std::string &value)
	{
		this->_Comment = value;
	}

	const std::string &GeneralTrack::getRating() const
	{
		if (this->_Rating.empty())
			this->_Rating = "";
		return _Rating;
	}

	void GeneralTrack::setRating(const std::string &value)
	{
		this->_Rating = value;
	}

	const std::string &GeneralTrack::getEncodedApplication() const
	{
		if (this->_EncodedApplication.empty())
			this->_EncodedApplication = "";
		return _EncodedApplication;
	}

	void GeneralTrack::setEncodedApplication(const std::string &value)
	{
		this->_EncodedApplication = value;
	}

	const std::string &GeneralTrack::getEncodedLibrary() const
	{
		if (this->_EncodedLibrary.empty())
			this->_EncodedLibrary = "";
		return _EncodedLibrary;
	}

	void GeneralTrack::setEncodedLibrary(const std::string &value)
	{
		this->_EncodedLibrary = value;
	}

	const std::string &GeneralTrack::getEncodedLibrarySettings() const
	{
		if (this->_EncodedLibrarySettings.empty())
			this->_EncodedLibrarySettings = "";
		return _EncodedLibrarySettings;
	}

	void GeneralTrack::setEncodedLibrarySettings(const std::string &value)
	{
		this->_EncodedLibrarySettings = value;
	}

	const std::string &GeneralTrack::getEncodedOriginal() const
	{
		if (this->_EncodedOriginal.empty())
			this->_EncodedOriginal = "";
		return _EncodedOriginal;
	}

	void GeneralTrack::setEncodedOriginal(const std::string &value)
	{
		this->_EncodedOriginal = value;
	}

	const std::string &GeneralTrack::getEncodedOriginalUrl() const
	{
		if (this->_EncodedOriginalUrl.empty())
			this->_EncodedOriginalUrl = "";
		return _EncodedOriginalUrl;
	}

	void GeneralTrack::setEncodedOriginalUrl(const std::string &value)
	{
		this->_EncodedOriginalUrl = value;
	}

	const std::string &GeneralTrack::getCopyright() const
	{
		if (this->_Copyright.empty())
			this->_Copyright = "";
		return _Copyright;
	}

	void GeneralTrack::setCopyright(const std::string &value)
	{
		this->_Copyright = value;
	}

	const std::string &GeneralTrack::getProducerCopyright() const
	{
		if (this->_ProducerCopyright.empty())
			this->_ProducerCopyright = "";
		return _ProducerCopyright;
	}

	void GeneralTrack::setProducerCopyright(const std::string &value)
	{
		this->_ProducerCopyright = value;
	}

	const std::string &GeneralTrack::getTermsOfUse() const
	{
		if (this->_TermsOfUse.empty())
			this->_TermsOfUse = "";
		return _TermsOfUse;
	}

	void GeneralTrack::setTermsOfUse(const std::string &value)
	{
		this->_TermsOfUse = value;
	}

	const std::string &GeneralTrack::getCopyrightUrl() const
	{
		if (this->_CopyrightUrl.empty())
			this->_CopyrightUrl = "";
		return _CopyrightUrl;
	}

	void GeneralTrack::setCopyrightUrl(const std::string &value)
	{
		this->_CopyrightUrl = value;
	}

	const std::string &GeneralTrack::getISRC() const
	{
		if (this->_ISRC.empty())
			this->_ISRC = "";
		return _ISRC;
	}

	void GeneralTrack::setISRC(const std::string &value)
	{
		this->_ISRC = value;
	}

	const std::string &GeneralTrack::getMSDI() const
	{
		if (this->_MSDI.empty())
			this->_MSDI = "";
		return _MSDI;
	}

	void GeneralTrack::setMSDI(const std::string &value)
	{
		this->_MSDI = value;
	}

	const std::string &GeneralTrack::getISBN() const
	{
		if (this->_ISBN.empty())
			this->_ISBN = "";
		return _ISBN;
	}

	void GeneralTrack::setISBN(const std::string &value)
	{
		this->_ISBN = value;
	}

	const std::string &GeneralTrack::getBarCode() const
	{
		if (this->_BarCode.empty())
			this->_BarCode = "";
		return _BarCode;
	}

	void GeneralTrack::setBarCode(const std::string &value)
	{
		this->_BarCode = value;
	}

	const std::string &GeneralTrack::getLCCN() const
	{
		if (this->_LCCN.empty())
			this->_LCCN = "";
		return _LCCN;
	}

	void GeneralTrack::setLCCN(const std::string &value)
	{
		this->_LCCN = value;
	}

	const std::string &GeneralTrack::getCatalogNumber() const
	{
		if (this->_CatalogNumber.empty())
			this->_CatalogNumber = "";
		return _CatalogNumber;
	}

	void GeneralTrack::setCatalogNumber(const std::string &value)
	{
		this->_CatalogNumber = value;
	}

	const std::string &GeneralTrack::getLabelCode() const
	{
		if (this->_LabelCode.empty())
			this->_LabelCode = "";
		return _LabelCode;
	}

	void GeneralTrack::setLabelCode(const std::string &value)
	{
		this->_LabelCode = value;
	}

	const std::string &GeneralTrack::getCover() const
	{
		if (this->_Cover.empty())
			this->_Cover = "";
		return _Cover;
	}

	void GeneralTrack::setCover(const std::string &value)
	{
		this->_Cover = value;
	}

	const std::string &GeneralTrack::getCoverDatas() const
	{
		if (this->_CoverDatas.empty())
			this->_CoverDatas = "";
		return _CoverDatas;
	}

	void GeneralTrack::setCoverDatas(const std::string &value)
	{
		this->_CoverDatas = value;
	}

	const std::string &GeneralTrack::getBPM() const
	{
		if (this->_BPM.empty())
			this->_BPM = "";
		return _BPM;
	}

	void GeneralTrack::setBPM(const std::string &value)
	{
		this->_BPM = value;
	}

	const std::string &GeneralTrack::getVideoCodecList() const
	{
		if (this->_VideoCodecList.empty())
			this->_VideoCodecList = "";
		return _VideoCodecList;
	}

	void GeneralTrack::setVideoCodecList(const std::string &value)
	{
		this->_VideoCodecList = value;
	}

	const std::string &GeneralTrack::getVideoLanguageList() const
	{
		if (this->_VideoLanguageList.empty())
			this->_VideoLanguageList = "";
		return _VideoLanguageList;
	}

	void GeneralTrack::setVideoLanguageList(const std::string &value)
	{
		this->_VideoLanguageList = value;
	}

	const std::string &GeneralTrack::getAudioCodecList() const
	{
		if (this->_AudioCodecList.empty())
			this->_AudioCodecList = "";
		return _AudioCodecList;
	}

	void GeneralTrack::setAudioCodecList(const std::string &value)
	{
		this->_AudioCodecList = value;
	}

	const std::string &GeneralTrack::getAudioLanguageList() const
	{
		if (this->_AudioLanguageList.empty())
			this->_AudioLanguageList = "";
		return _AudioLanguageList;
	}

	void GeneralTrack::setAudioLanguageList(const std::string &value)
	{
		this->_AudioLanguageList = value;
	}

	const std::string &GeneralTrack::getTextCodecList() const
	{
		if (this->_TextCodecList.empty())
			this->_TextCodecList = "";
		return _TextCodecList;
	}

	void GeneralTrack::setTextCodecList(const std::string &value)
	{
		this->_TextCodecList = value;
	}

	const std::string &GeneralTrack::getTextLanguageList() const
	{
		if (this->_TextLanguageList.empty())
			this->_TextLanguageList = "";
		return _TextLanguageList;
	}

	void GeneralTrack::setTextLanguageList(const std::string &value)
	{
		this->_TextLanguageList = value;
	}

	const std::string &GeneralTrack::getChaptersCodecList() const
	{
		if (this->_ChaptersCodecList.empty())
			this->_ChaptersCodecList = "";
		return _ChaptersCodecList;
	}

	void GeneralTrack::setChaptersCodecList(const std::string &value)
	{
		this->_ChaptersCodecList = value;
	}

	const std::string &GeneralTrack::getChaptersLanguageList() const
	{
		if (this->_ChaptersLanguageList.empty())
			this->_ChaptersLanguageList = "";
		return _ChaptersLanguageList;
	}

	void GeneralTrack::setChaptersLanguageList(const std::string &value)
	{
		this->_ChaptersLanguageList = value;
	}

	const std::string &GeneralTrack::getImageCodecList() const
	{
		if (this->_ImageCodecList.empty())
			this->_ImageCodecList = "";
		return _ImageCodecList;
	}

	void GeneralTrack::setImageCodecList(const std::string &value)
	{
		this->_ImageCodecList = value;
	}

	const std::string &GeneralTrack::getImageLanguageList() const
	{
		if (this->_ImageLanguageList.empty())
			this->_ImageLanguageList = "";
		return _ImageLanguageList;
	}

	void GeneralTrack::setImageLanguageList(const std::string &value)
	{
		this->_ImageLanguageList = value;
	}

	const std::string &GeneralTrack::getOther() const
	{
		if (this->_Other.empty())
			this->_Other = "";
		return _Other;
	}

	void GeneralTrack::setOther(const std::string &value)
	{
		this->_Other = value;
	}
}
