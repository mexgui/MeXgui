#pragma once

#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace MediaInfoWrapper
{
	///<summary>Contains properties for a GeneralTrack </summary>
	class GeneralTrack
	{
	private:
		std::string _Count;
		std::string _StreamCount;
		std::string _StreamKind;
		std::string _StreamKindID;
		std::string _StreamOrder;
		std::string _Inform;
		std::string _ID;
		std::string _UniqueID;
		std::string _GeneralCount;
		std::string _VideoCount;
		std::string _AudioCount;
		std::string _TextCount;
		std::string _ChaptersCount;
		std::string _ImageCount;
		std::string _CompleteName;
		std::string _FolderName;
		std::string _FileName;
		std::string _FileExtension;
		std::string _FileSize;
		std::string _FileSizeString;
		std::string _FileSizeString1;
		std::string _FileSizeString2;
		std::string _FileSizeString3;
		std::string _FileSizeString4;
		std::string _Format;
		std::string _FormatString;
		std::string _FormatInfo;
		std::string _FormatUrl;
		std::string _FormatExtensions;
		std::string _OveralBitRate;
		std::string _OveralBitRateString;
		std::string _PlayTime;
		std::string _PlayTimeString;
		std::string _PlayTimeString1;
		std::string _PlayTimeString2;
		std::string _PlayTimeString3;
		std::string _Title;
		std::string _TitleMore;
		std::string _PGCNumber;
		std::string _PGCCount;
		std::string _Domain;
		std::string _Collection;
		std::string _CollectionTotalParts;
		std::string _Season;
		std::string _Movie;
		std::string _MovieMore;
		std::string _Album;
		std::string _AlbumTotalParts;
		std::string _AlbumSort;
		std::string _Comic;
		std::string _ComicTotalParts;
		std::string _Part;
		std::string _PartTotalParts;
		std::string _PartPosition;
		std::string _Track;
		std::string _TrackPosition;
		std::string _TrackMore;
		std::string _TrackSort;
		std::string _Chapter;
		std::string _SubTrack;
		std::string _OriginalAlbum;
		std::string _OriginalMovie;
		std::string _OriginalPart;
		std::string _OriginalTrack;
		std::string _Author;
		std::string _Artist;
		std::string _PerformerSort;
		std::string _OriginalPerformer;
		std::string _Accompaniment;
		std::string _MusicianInstrument;
		std::string _Composer;
		std::string _ComposerNationality;
		std::string _Arranger;
		std::string _Lyricist;
		std::string _OriginalLyricist;
		std::string _Conductor;
		std::string _Actor;
		std::string _ActorCharacter;
		std::string _WrittenBy;
		std::string _ScreenplayBy;
		std::string _Director;
		std::string _AssistantDirector;
		std::string _DirectorOfPhotography;
		std::string _ArtDirector;
		std::string _EditedBy;
		std::string _Producer;
		std::string _CoProducer;
		std::string _ExecutiveProducer;
		std::string _ProductionDesigner;
		std::string _CostumeDesigner;
		std::string _Choregrapher;
		std::string _SoundEngineer;
		std::string _MasteredBy;
		std::string _RemixedBy;
		std::string _ProductionStudio;
		std::string _Publisher;
		std::string _PublisherURL;
		std::string _DistributedBy;
		std::string _EncodedBy;
		std::string _ThanksTo;
		std::string _Technician;
		std::string _CommissionedBy;
		std::string _EncodedOriginalDistributedBy;
		std::string _RadioStation;
		std::string _RadioStationOwner;
		std::string _RadioStationURL;
		std::string _ContentType;
		std::string _Subject;
		std::string _Synopsys;
		std::string _Summary;
		std::string _Description;
		std::string _Keywords;
		std::string _Period;
		std::string _LawRating;
		std::string _IRCA;
		std::string _Language;
		std::string _Medium;
		std::string _Product;
		std::string _Country;
		std::string _WrittenDate;
		std::string _RecordedDate;
		std::string _ReleasedDate;
		std::string _MasteredDate;
		std::string _EncodedDate;
		std::string _TaggedDate;
		std::string _OriginalReleasedDate;
		std::string _OriginalRecordedDate;
		std::string _WrittenLocation;
		std::string _RecordedLocation;
		std::string _ArchivalLocation;
		std::string _Genre;
		std::string _Mood;
		std::string _Comment;
		std::string _Rating;
		std::string _EncodedApplication;
		std::string _EncodedLibrary;
		std::string _EncodedLibrarySettings;
		std::string _EncodedOriginal;
		std::string _EncodedOriginalUrl;
		std::string _Copyright;
		std::string _ProducerCopyright;
		std::string _TermsOfUse;
		std::string _CopyrightUrl;
		std::string _ISRC;
		std::string _MSDI;
		std::string _ISBN;
		std::string _BarCode;
		std::string _LCCN;
		std::string _CatalogNumber;
		std::string _LabelCode;
		std::string _Cover;
		std::string _CoverDatas;
		std::string _BPM;
		std::string _VideoCodecList;
		std::string _VideoLanguageList;
		std::string _AudioCodecList;
		std::string _AudioLanguageList;
		std::string _TextCodecList;
		std::string _TextLanguageList;
		std::string _ChaptersCodecList;
		std::string _ChaptersLanguageList;
		std::string _ImageCodecList;
		std::string _ImageLanguageList;
		std::string _Other;

		///<summary> Count of objects available in this stream </summary>
	public:
		const std::string &getCount() const;
		void setCount(const std::string &value);

		///<summary> Count of streams of that kind available </summary>
		const std::string &getStreamCount() const;
		void setStreamCount(const std::string &value);

		///<summary> DVD PGC Count </summary>
		const std::string &getPGCCount() const;
		void setPGCCount(const std::string &value);

		///<summary> DVD PGC Number </summary>
		const std::string &getPGCNumber() const;
		void setPGCNumber(const std::string &value);

		///<summary> Stream name </summary>
		const std::string &getStreamKind() const;
		void setStreamKind(const std::string &value);

		///<summary> When multiple streams, number of the stream </summary>
		const std::string &getStreamKindID() const;
		void setStreamKindID(const std::string &value);

		///<summary>Stream order in the file, whatever is the kind of stream (base=0)</summary>
		const std::string &getStreamOrder() const;
		void setStreamOrder(const std::string &value);

		///<summary> Last   Inform   call </summary>
		const std::string &getInform() const;
		void setInform(const std::string &value);

		///<summary> A ID for this stream in this file </summary>
		const std::string &getID() const;
		void setID(const std::string &value);

		///<summary> A unique ID for this stream, should be copied with stream copy </summary>
		const std::string &getUniqueID() const;
		void setUniqueID(const std::string &value);

		///<summary> Count of video streams </summary>
		const std::string &getGeneralCount() const;
		void setGeneralCount(const std::string &value);

		///<summary> Count of video streams </summary>
		const std::string &getVideoCount() const;
		void setVideoCount(const std::string &value);

		///<summary> Count of audio streams </summary>
		const std::string &getAudioCount() const;
		void setAudioCount(const std::string &value);

		///<summary> Count of text streams </summary>
		const std::string &getTextCount() const;
		void setTextCount(const std::string &value);

		///<summary> Count of chapters streams </summary>
		const std::string &getChaptersCount() const;
		void setChaptersCount(const std::string &value);

		///<summary> Count of image streams </summary>
		const std::string &getImageCount() const;
		void setImageCount(const std::string &value);

		///<summary> Complete name (Folder+Name+Extension) </summary>
		const std::string &getCompleteName() const;
		void setCompleteName(const std::string &value);

		///<summary> Folder name only </summary>
		const std::string &getFolderName() const;
		void setFolderName(const std::string &value);

		///<summary> File name only </summary>
		const std::string &getFileName() const;
		void setFileName(const std::string &value);

		///<summary> File extension only </summary>
		const std::string &getFileExtension() const;
		void setFileExtension(const std::string &value);

		///<summary> File size in bytes </summary>
		const std::string &getFileSize() const;
		void setFileSize(const std::string &value);

		///<summary> File size (with measure) </summary>
		const std::string &getFileSizeString() const;
		void setFileSizeString(const std::string &value);

		///<summary> File size (with measure, 1 digit mini) </summary>
		const std::string &getFileSizeString1() const;
		void setFileSizeString1(const std::string &value);

		///<summary> File size (with measure, 2 digit mini) </summary>
		const std::string &getFileSizeString2() const;
		void setFileSizeString2(const std::string &value);

		///<summary> File size (with measure, 3 digit mini) </summary>
		const std::string &getFileSizeString3() const;
		void setFileSizeString3(const std::string &value);

		///<summary> File size (with measure, 4 digit mini) </summary>
		const std::string &getFileSizeString4() const;
		void setFileSizeString4(const std::string &value);

		///<summary> Format (short name) </summary>
		const std::string &getFormat() const;
		void setFormat(const std::string &value);

		///<summary> Format (full name) </summary>
		const std::string &getFormatString() const;
		void setFormatString(const std::string &value);

		///<summary> More information about this format </summary>
		const std::string &getFormatInfo() const;
		void setFormatInfo(const std::string &value);

		///<summary> Url about this format </summary>
		const std::string &getFormatUrl() const;
		void setFormatUrl(const std::string &value);

		///<summary> Known extensions of format </summary>
		const std::string &getFormatExtensions() const;
		void setFormatExtensions(const std::string &value);

		///<summary> BitRate of all streams </summary>
		const std::string &getOveralBitRate() const;
		void setOveralBitRate(const std::string &value);

		///<summary> BitRate of all streams (with measure) </summary>
		const std::string &getOveralBitRateString() const;
		void setOveralBitRateString(const std::string &value);

		///<summary> Play time of the file </summary>
		const std::string &getPlayTime() const;
		void setPlayTime(const std::string &value);

		///<summary> Play time in format : XXx YYy only, YYy omited if zero </summary>
		const std::string &getPlayTimeString() const;
		void setPlayTimeString(const std::string &value);

		///<summary> Play time in format : HHh MMmn SSs MMMms, XX omited if zero </summary>
		const std::string &getPlayTimeString1() const;
		void setPlayTimeString1(const std::string &value);

		///<summary> Play time in format : XXx YYy only, YYy omited if zero </summary>
		const std::string &getPlayTimeString2() const;
		void setPlayTimeString2(const std::string &value);

		///<summary> Play time in format : HH:MM:SS.MMM </summary>
		const std::string &getPlayTimeString3() const;
		void setPlayTimeString3(const std::string &value);

		///<summary> (Generic)Title of file </summary>
		const std::string &getTitle() const;
		void setTitle(const std::string &value);

		///<summary> (Generic)More info about the title of file </summary>
		const std::string &getTitleMore() const;
		void setTitleMore(const std::string &value);

		///<summary> Level=8. Eg : Starwars, Stargate, U2 </summary>
		const std::string &getDomain() const;
		void setDomain(const std::string &value);

		///<summary> Level=7. Name of the collection. Eg : Starwars movies, Stargate movie, Stargate SG-1, Stargate Atlantis </summary>
		const std::string &getCollection() const;
		void setCollection(const std::string &value);

		///<summary> Total count of seasons </summary>
		const std::string &getCollectionTotalParts() const;
		void setCollectionTotalParts(const std::string &value);

		///<summary> Level=6. Name of the season. Eg : Strawars first Trilogy, Season 1 </summary>
		const std::string &getSeason() const;
		void setSeason(const std::string &value);

		///<summary> Level=5. Name of the movie. Eg : Starwars, a new hope </summary>
		const std::string &getMovie() const;
		void setMovie(const std::string &value);

		///<summary> More information about this movie </summary>
		const std::string &getMovieMore() const;
		void setMovieMore(const std::string &value);

		///<summary> Level=5. Name of album. Eg : The joshua tree </summary>
		const std::string &getAlbum() const;
		void setAlbum(const std::string &value);

		///<summary> Total number of track or parts (depend if there is a part) </summary>
		const std::string &getAlbumTotalParts() const;
		void setAlbumTotalParts(const std::string &value);

		///<summary> Sort order </summary>
		const std::string &getAlbumSort() const;
		void setAlbumSort(const std::string &value);

		///<summary> Level=5. Name of the comic. </summary>
		const std::string &getComic() const;
		void setComic(const std::string &value);

		///<summary> Total number of pages in the comic </summary>
		const std::string &getComicTotalParts() const;
		void setComicTotalParts(const std::string &value);

		///<summary> Level=4. Name of the part. Eg : CD1, CD2 </summary>
		const std::string &getPart() const;
		void setPart(const std::string &value);

		///<summary> Total count of track or episode </summary>
		const std::string &getPartTotalParts() const;
		void setPartTotalParts(const std::string &value);

		///<summary> Part number </summary>
		const std::string &getPartPosition() const;
		void setPartPosition(const std::string &value);

		///<summary> Level=3. Name of the track. Eg : track1, track 2 </summary>
		const std::string &getTrack() const;
		void setTrack(const std::string &value);

		///<summary> Track number or episode number... </summary>
		const std::string &getTrackPosition() const;
		void setTrackPosition(const std::string &value);

		///<summary> More information about this track (subtitle) </summary>
		const std::string &getTrackMore() const;
		void setTrackMore(const std::string &value);

		///<summary> Sort order </summary>
		const std::string &getTrackSort() const;
		void setTrackSort(const std::string &value);

		///<summary> Level=3. Name of the chapter. </summary>
		const std::string &getChapter() const;
		void setChapter(const std::string &value);

		///<summary> Level=2, Name of the subtrack. </summary>
		const std::string &getSubTrack() const;
		void setSubTrack(const std::string &value);

		///<summary> Original name of album, serie... </summary>
		const std::string &getOriginalAlbum() const;
		void setOriginalAlbum(const std::string &value);

		///<summary> Original name of the movie </summary>
		const std::string &getOriginalMovie() const;
		void setOriginalMovie(const std::string &value);

		///<summary> Name of the part in the original support </summary>
		const std::string &getOriginalPart() const;
		void setOriginalPart(const std::string &value);

		///<summary> Original name of the track in the original support </summary>
		const std::string &getOriginalTrack() const;
		void setOriginalTrack(const std::string &value);

		///<summary> (Generic)Performer of the file </summary>
		const std::string &getAuthor() const;
		void setAuthor(const std::string &value);

		///<summary> Duplicate of Performer </summary>
		const std::string &getArtist() const;
		void setArtist(const std::string &value);

		///<summary> Sort order </summary>
		const std::string &getPerformerSort() const;
		void setPerformerSort(const std::string &value);

		///<summary> Original artist(s)_performer(s). </summary>
		const std::string &getOriginalPerformer() const;
		void setOriginalPerformer(const std::string &value);

		///<summary> Band_orchestra_accompaniment_musician. </summary>
		const std::string &getAccompaniment() const;
		void setAccompaniment(const std::string &value);

		///<summary> Name of the character an actor or actress plays in this movie. </summary>
		const std::string &getMusicianInstrument() const;
		void setMusicianInstrument(const std::string &value);

		///<summary> Name of the original composer. </summary>
		const std::string &getComposer() const;
		void setComposer(const std::string &value);

		///<summary> Nationality of the main composer of the item, mostly for classical music. </summary>
		const std::string &getComposerNationality() const;
		void setComposerNationality(const std::string &value);

		///<summary> The person who arranged the piece. e.g. Ravel. </summary>
		const std::string &getArranger() const;
		void setArranger(const std::string &value);

		///<summary> The person who wrote the lyrics for a musical item. </summary>
		const std::string &getLyricist() const;
		void setLyricist(const std::string &value);

		///<summary> Original lyricist(s)_text writer(s). </summary>
		const std::string &getOriginalLyricist() const;
		void setOriginalLyricist(const std::string &value);

		///<summary> The artist(s) who performed the work. In classical music this would be the conductor, orchestra, soloists. </summary>
		const std::string &getConductor() const;
		void setConductor(const std::string &value);

		///<summary> Real name of actor or actress playing a role in the movie. </summary>
		const std::string &getActor() const;
		void setActor(const std::string &value);

		///<summary> Name of the character an actor or actress plays in this movie. </summary>
		const std::string &getActorCharacter() const;
		void setActorCharacter(const std::string &value);

		///<summary> The author of the story or script. </summary>
		const std::string &getWrittenBy() const;
		void setWrittenBy(const std::string &value);

		///<summary> The author of the screenplay or scenario (used for movies and TV shows). </summary>
		const std::string &getScreenplayBy() const;
		void setScreenplayBy(const std::string &value);

		///<summary> Name of the director. </summary>
		const std::string &getDirector() const;
		void setDirector(const std::string &value);

		///<summary> Name of the assistant director. </summary>
		const std::string &getAssistantDirector() const;
		void setAssistantDirector(const std::string &value);

		///<summary> The name of the director of photography, also known as cinematographer. </summary>
		const std::string &getDirectorOfPhotography() const;
		void setDirectorOfPhotography(const std::string &value);

		///<summary> The person who oversees the artists and craftspeople who build the sets. </summary>
		const std::string &getArtDirector() const;
		void setArtDirector(const std::string &value);

		///<summary> Editor name </summary>
		const std::string &getEditedBy() const;
		void setEditedBy(const std::string &value);

		///<summary> Name of the producer of the movie. </summary>
		const std::string &getProducer() const;
		void setProducer(const std::string &value);

		///<summary> The name of a co-producer. </summary>
		const std::string &getCoProducer() const;
		void setCoProducer(const std::string &value);

		///<summary> The name of an executive producer. </summary>
		const std::string &getExecutiveProducer() const;
		void setExecutiveProducer(const std::string &value);

		///<summary> Artist responsible for designing the overall visual appearance of a movie. </summary>
		const std::string &getProductionDesigner() const;
		void setProductionDesigner(const std::string &value);

		///<summary> The name of the costume designer. </summary>
		const std::string &getCostumeDesigner() const;
		void setCostumeDesigner(const std::string &value);

		///<summary> The name of the choregrapher. </summary>
		const std::string &getChoregrapher() const;
		void setChoregrapher(const std::string &value);

		///<summary> The name of the sound engineer or sound recordist. </summary>
		const std::string &getSoundEngineer() const;
		void setSoundEngineer(const std::string &value);

		///<summary> The engineer who mastered the content for a physical medium or for digital distribution. </summary>
		const std::string &getMasteredBy() const;
		void setMasteredBy(const std::string &value);

		///<summary> Interpreted, remixed, or otherwise modified by. </summary>
		const std::string &getRemixedBy() const;
		void setRemixedBy(const std::string &value);

		///<summary>   </summary>
		const std::string &getProductionStudio() const;
		void setProductionStudio(const std::string &value);

		///<summary> Name of the organization producing the track (i.e. the  record label ). </summary>
		const std::string &getPublisher() const;
		void setPublisher(const std::string &value);

		///<summary> Publishers official webpage. </summary>
		const std::string &getPublisherURL() const;
		void setPublisherURL(const std::string &value);

		///<summary>   </summary>
		const std::string &getDistributedBy() const;
		void setDistributedBy(const std::string &value);

		///<summary> Name of the person or organisation that encoded_ripped the audio file. </summary>
		const std::string &getEncodedBy() const;
		void setEncodedBy(const std::string &value);

		///<summary> A very general tag for everyone else that wants to be listed. </summary>
		const std::string &getThanksTo() const;
		void setThanksTo(const std::string &value);

		///<summary> Technician. Identifies the technician who digitized the subject file. For example, Smith, John. </summary>
		const std::string &getTechnician() const;
		void setTechnician(const std::string &value);

		///<summary> Commissioned. Lists the name of the person or organization that commissioned the subject of the file. e.g. Pope Julian II. </summary>
		const std::string &getCommissionedBy() const;
		void setCommissionedBy(const std::string &value);

		///<summary> Source. Identifies the name of the person or organization who supplied the original subject of the file. For example, Trey Research. </summary>
		const std::string &getEncodedOriginalDistributedBy() const;
		void setEncodedOriginalDistributedBy(const std::string &value);

		///<summary> Contains the name of the internet radio station from which the audio is streamed. </summary>
		const std::string &getRadioStation() const;
		void setRadioStation(const std::string &value);

		///<summary> Contains the name of the owner of the internet radio station from which the audio is streamed. </summary>
		const std::string &getRadioStationOwner() const;
		void setRadioStationOwner(const std::string &value);

		///<summary> Official internet radio station homepage. </summary>
		const std::string &getRadioStationURL() const;
		void setRadioStationURL(const std::string &value);

		///<summary> The type of the item. e.g. Documentary, Feature Film, Cartoon, Music Video, Music, Sound FX, etc. </summary>
		const std::string &getContentType() const;
		void setContentType(const std::string &value);

		///<summary> Describes the topic of the file, such as Aerial view of Seattle.. </summary>
		const std::string &getSubject() const;
		void setSubject(const std::string &value);

		///<summary> A description of the story line of the item. </summary>
		const std::string &getSynopsys() const;
		void setSynopsys(const std::string &value);

		///<summary> A plot outline or a summary of the story. </summary>
		const std::string &getSummary() const;
		void setSummary(const std::string &value);

		///<summary> A short description of the contents, such as Two birds flying. </summary>
		const std::string &getDescription() const;
		void setDescription(const std::string &value);

		///<summary> Keywords to the item separated by a comma, used for searching. </summary>
		const std::string &getKeywords() const;
		void setKeywords(const std::string &value);

		///<summary> Describes the period that the piece is from or about. e.g. Renaissance. </summary>
		const std::string &getPeriod() const;
		void setPeriod(const std::string &value);

		///<summary> Depending on the country it s the format of the rating of a movie (P, R, X in the USA, an age in other countries or a URI defining a logo). </summary>
		const std::string &getLawRating() const;
		void setLawRating(const std::string &value);

		///<summary> The ICRA rating. (Previously RSACi) </summary>
		const std::string &getIRCA() const;
		void setIRCA(const std::string &value);

		///<summary> Language(s) of the item in the bibliographic ISO-639-2 form. </summary>
		const std::string &getLanguage() const;
		void setLanguage(const std::string &value);

		///<summary> Medium. Describes the original subject of the file, such as, computer image, drawing, lithograph, and so forth. Not necessarily the same as ISRF. </summary>
		const std::string &getMedium() const;
		void setMedium(const std::string &value);

		///<summary> Product. Specifies the name of the title the file was originally intended for, such as Encyclopedia of Pacific Northwest Geography. </summary>
		const std::string &getProduct() const;
		void setProduct(const std::string &value);

		///<summary> Country </summary>
		const std::string &getCountry() const;
		void setCountry(const std::string &value);

		///<summary> The time that the composition of the music_script began. </summary>
		const std::string &getWrittenDate() const;
		void setWrittenDate(const std::string &value);

		///<summary> The time that the recording began. </summary>
		const std::string &getRecordedDate() const;
		void setRecordedDate(const std::string &value);

		///<summary> The time that the item was originaly released. </summary>
		const std::string &getReleasedDate() const;
		void setReleasedDate(const std::string &value);

		///<summary> The time that the item was tranfered to a digitalmedium. </summary>
		const std::string &getMasteredDate() const;
		void setMasteredDate(const std::string &value);

		///<summary> The time that the encoding of this item was completed began. </summary>
		const std::string &getEncodedDate() const;
		void setEncodedDate(const std::string &value);

		///<summary> The time that the tags were done for this item. </summary>
		const std::string &getTaggedDate() const;
		void setTaggedDate(const std::string &value);

		///<summary> Contains a timestamp describing when the original recording of the audio was released. </summary>
		const std::string &getOriginalReleasedDate() const;
		void setOriginalReleasedDate(const std::string &value);

		///<summary> Contains a timestamp describing when the original recording of the audio was recorded. </summary>
		const std::string &getOriginalRecordedDate() const;
		void setOriginalRecordedDate(const std::string &value);

		///<summary> Location that the item was originaly designed_written. Information should be stored in the following format: country code, state_province, city where the coutry code is the same 2 octets as in Internet domains, or possibly ISO-3166. e.g. US, Texas, Austin or US, , Austin. </summary>
		const std::string &getWrittenLocation() const;
		void setWrittenLocation(const std::string &value);

		///<summary> Location where track was recorded. (See COMPOSITION_LOCATION for format) </summary>
		const std::string &getRecordedLocation() const;
		void setRecordedLocation(const std::string &value);

		///<summary> Archival Location. Indicates where the subject of the file is archived. </summary>
		const std::string &getArchivalLocation() const;
		void setArchivalLocation(const std::string &value);

		///<summary> The main genre of the audio or video. e.g. classical, ambient-house, synthpop, sci-fi, drama, etc. </summary>
		const std::string &getGenre() const;
		void setGenre(const std::string &value);

		///<summary> Intended to reflect the mood of the item with a few keywords, e.g. Romantic, Sad, Uplifting, etc. </summary>
		const std::string &getMood() const;
		void setMood(const std::string &value);

		///<summary> Any comment related to the content. </summary>
		const std::string &getComment() const;
		void setComment(const std::string &value);

		///<summary> A numeric value defining how much a person likes the song_movie. The number is between 0 and 5 with decimal values possible (e.g. 2.7), 5(.0) being the highest possible rating. </summary>
		const std::string &getRating() const;
		void setRating(const std::string &value);

		///<summary> Software. Identifies the name of the software package used to create the file, such as Microsoft WaveEdit. </summary>
		const std::string &getEncodedApplication() const;
		void setEncodedApplication(const std::string &value);

		///<summary> The software or hardware used to encode this item. e.g. LAME or XviD </summary>
		const std::string &getEncodedLibrary() const;
		void setEncodedLibrary(const std::string &value);

		///<summary> A list of the settings used for encoding this item. No specific format. </summary>
		const std::string &getEncodedLibrarySettings() const;
		void setEncodedLibrarySettings(const std::string &value);

		///<summary> Identifies the original recording media form from which the material originated, such as CD, cassette, LP, radio broadcast, slide, paper, etc. </summary>
		const std::string &getEncodedOriginal() const;
		void setEncodedOriginal(const std::string &value);

		///<summary> Official audio source webpage. e.g. a movie. </summary>
		const std::string &getEncodedOriginalUrl() const;
		void setEncodedOriginalUrl(const std::string &value);

		///<summary> Copyright attribution. </summary>
		const std::string &getCopyright() const;
		void setCopyright(const std::string &value);

		///<summary> The copyright information as per the productioncopyright holder. </summary>
		const std::string &getProducerCopyright() const;
		void setProducerCopyright(const std::string &value);

		///<summary> License information, e.g., All Rights Reserved,Any Use Permitted. </summary>
		const std::string &getTermsOfUse() const;
		void setTermsOfUse(const std::string &value);

		///<summary> Copyright_legal information. </summary>
		const std::string &getCopyrightUrl() const;
		void setCopyrightUrl(const std::string &value);

		///<summary> International Standard Recording Code, excluding the ISRC prefix and including hyphens. </summary>
		const std::string &getISRC() const;
		void setISRC(const std::string &value);

		///<summary> This is a binary dump of the TOC of the CDROM that this item was taken from. </summary>
		const std::string &getMSDI() const;
		void setMSDI(const std::string &value);

		///<summary> International Standard Book Number. </summary>
		const std::string &getISBN() const;
		void setISBN(const std::string &value);

		///<summary> EAN-13 (13-digit European Article Numbering) or UPC-A (12-digit Universal Product Code) bar code identifier. </summary>
		const std::string &getBarCode() const;
		void setBarCode(const std::string &value);

		///<summary> Library of Congress Control Number. </summary>
		const std::string &getLCCN() const;
		void setLCCN(const std::string &value);

		///<summary> A label-specific catalogue number used to identify the release. e.g. TIC 01. </summary>
		const std::string &getCatalogNumber() const;
		void setCatalogNumber(const std::string &value);

		///<summary> A 4-digit or 5-digit number to identify the record label, typically printed as (LC) xxxx or (LC) 0xxxx on CDs medias or covers, with only the number being stored. </summary>
		const std::string &getLabelCode() const;
		void setLabelCode(const std::string &value);

		///<summary> Is there a cover </summary>
		const std::string &getCover() const;
		void setCover(const std::string &value);

		///<summary> Cover, in binary format encoded BASE64 </summary>
		const std::string &getCoverDatas() const;
		void setCoverDatas(const std::string &value);

		///<summary> Average number of beats per minute </summary>
		const std::string &getBPM() const;
		void setBPM(const std::string &value);

		///<summary> Video Codecs separated by _ </summary>
		const std::string &getVideoCodecList() const;
		void setVideoCodecList(const std::string &value);

		///<summary> Video languages separated by _ </summary>
		const std::string &getVideoLanguageList() const;
		void setVideoLanguageList(const std::string &value);

		///<summary> Audio Codecs separated by _ </summary>
		const std::string &getAudioCodecList() const;
		void setAudioCodecList(const std::string &value);

		///<summary> Audio languages separated by _ </summary>
		const std::string &getAudioLanguageList() const;
		void setAudioLanguageList(const std::string &value);

		///<summary> Text Codecs separated by _ </summary>
		const std::string &getTextCodecList() const;
		void setTextCodecList(const std::string &value);

		///<summary> Text languages separated by _ </summary>
		const std::string &getTextLanguageList() const;
		void setTextLanguageList(const std::string &value);

		///<summary> Chapters Codecs separated by _ </summary>
		const std::string &getChaptersCodecList() const;
		void setChaptersCodecList(const std::string &value);

		///<summary> Chapters languages separated by _ </summary>
		const std::string &getChaptersLanguageList() const;
		void setChaptersLanguageList(const std::string &value);

		///<summary> Image Codecs separated by _ </summary>
		const std::string &getImageCodecList() const;
		void setImageCodecList(const std::string &value);

		///<summary> Image languages separated by _ </summary>
		const std::string &getImageLanguageList() const;
		void setImageLanguageList(const std::string &value);

		///<summary> Other tags not known... </summary>
		const std::string &getOther() const;
		void setOther(const std::string &value);
	};
}
