#include "VideoUtil.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;


using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

	VideoUtil::VideoUtil(MainForm *mainForm)
	{
		this->mainForm = mainForm;
		jobUtil = new JobUtil(mainForm);
	}

	QString VideoUtil::getChapterFile(const QString &fileName)
	{
		QString vts;
		QString path = Path::GetDirectoryName(fileName);
		QString name = Path::GetFileNameWithoutExtension(fileName);
		if (name.length() > 6)
			vts = name.substr(0, 6);
		else
			vts = name;
		QString chapterFile = "";
//ORIGINAL LINE: string[] files = Directory.GetFiles(path, vts + "*Chapter Information*");
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		QString *files = Directory::GetFiles(path, vts + "*Chapter Information*");
		for (QString::const_iterator file = files->begin(); file != files->end(); ++file)
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if ((*file).ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".txt") || (*file).ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".qpf"))
			{
				chapterFile = *file;
				break;
			}
		}
		return chapterFile;
	}

	QString VideoUtil::getChaptersFromIFO(const QString &fileName, bool qpfile, const QString &outputDirectory, int iPGCNumber)
	{
		if (Path::GetExtension(fileName.ToLower(System::Globalization::CultureInfo::InvariantCulture)) == ".vob" || Path::GetExtension(fileName.ToLower(System::Globalization::CultureInfo::InvariantCulture)) == ".ifo")
		{
			QString ifoFile;
			QString fileNameNoPath = Path::GetFileName(fileName);
			if (outputDirectory.empty())
				outputDirectory = Path::GetDirectoryName(fileName);

			// we check the main IFO
			if (fileNameNoPath.substr(0, 4)->ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "VTS_")
				ifoFile = fileName.substr(0, fileName.rfind("_")) + "_0.IFO";
			else
				ifoFile = Path::ChangeExtension(fileName, ".IFO");

			if (File::Exists(ifoFile))
			{
				ChapterInfo *pgc;
				IfoExtractor *ex = new IfoExtractor();
				pgc = ex->GetChapterInfo(ifoFile, iPGCNumber);
				if (Drives::ableToWriteOnThisDrive(Path::GetPathRoot(outputDirectory)))
				{
					if (qpfile)
						pgc->SaveQpfile(outputDirectory + "\\" + fileNameNoPath.substr(0, 6) + " - Chapter Information.qpf");

					// save always this format - some users want it for the mux
					pgc->SaveText(outputDirectory + "\\" + fileNameNoPath.substr(0, 6) + " - Chapter Information.txt");
					return outputDirectory + "\\" + fileNameNoPath.substr(0, 6) + " - Chapter Information.txt";
				}
				else
					MessageBox::Show("MeXgui cannot write on the disc " + Path::GetPathRoot(ifoFile) + " \n" + "Please, select another output path to save the chapters file...", "Configuration Incomplete", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
		return 0;
	}

	bool VideoUtil::HasChapters(MediaInfoFile *iFile)
	{
		if (iFile->hasMKVChapters() || iFile->getEac3toChaptersTrack() > -1)
			return true;

		if (Path::GetExtension(iFile->getFileName().ToLowerInvariant()) != ".vob" && Path::GetExtension(iFile->getFileName().ToLowerInvariant()) != ".ifo")
			return false;

		// detect ifo file
		QString videoIFO = "";
		if (Path::GetExtension(iFile->getFileName().ToLowerInvariant()) == ".vob")
		{
			// find the main IFO
			if (Path::GetFileName(iFile->getFileName())->ToUpperInvariant()->substr(0, 4) == "VTS_")
				videoIFO = iFile->getFileName().substr(0, iFile->getFileName().rfind("_")) + "_0.IFO";
			else
				videoIFO = Path::ChangeExtension(iFile->getFileName(), ".IFO");
		}

		if (!File::Exists(videoIFO))
			return false;

		int iPGCNumber = 1;
		if (iFile->getVideoInfo()->PGCNumber > 0)
			iPGCNumber = iFile->getVideoInfo()->PGCNumber;

		IfoExtractor *ex = new IfoExtractor();
		ChapterInfo *pgc = ex->GetChapterInfo(videoIFO, iPGCNumber);
		if (pgc->getChapters().size() > 0)
			return true;
		return false;
	}

	QString VideoUtil::getChapterTimeLine(const QString &fileName)
	{
		qint64 count = 0;
		QString line;
		QString chap = "=";

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (StreamReader r = new StreamReader(fileName))
		StreamReader *r = new StreamReader(fileName);
		try
		{
			while ((line = r->ReadLine()) != 0)
			{
				count++;
				if (count % 2 != 0) // odd line
				{
					if (count >= 2)
						chap += ";";
					chap += line.substr(line.find("=") + 1, 12);
				}
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (r != 0)
				r.Dispose();
		}
		return chap;
	}

	QVector<QString> VideoUtil::setDeviceTypes(const QString &outputFormat)
	{
		QVector<QString> deviceList = QVector<QString>();
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (outputFormat)
//ORIGINAL LINE: case ".avi":
		if (outputFormat == ".avi")
		{
				deviceList.AddRange(new QString[] {"PC"});
		}
//ORIGINAL LINE: case ".mp4":
		else if (outputFormat == ".mp4")
		{
				deviceList.AddRange(new QString[] {"Apple TV", "iPad", "iPhone", "iPod", "ISMA", "PSP"});
		}
//ORIGINAL LINE: case ".m2ts":
		else if (outputFormat == ".m2ts")
		{
				deviceList.AddRange(new QString[] {"AVCHD", "Blu-ray"});
		}

		return deviceList;
	}

	QMap<int, QString> VideoUtil::getAllDemuxedAudio(QVector<AudioTrackInfo*> &audioTracks, QVector<AudioTrackInfo*> &audioTracksDemux, QVector<QString> &arrDeleteFiles, const QString &projectName, LogItem *log)
	{
		QMap<int, QString> audioFiles = QMap<int, QString>();
		arrDeleteFiles = QVector<QString>();
		QString strTrackName;
//ORIGINAL LINE: string[] files;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		QString *files;

		if ((audioTracks.empty() || audioTracks.empty()) && (audioTracksDeempty() || audioTracksDeempty()))
			return audioFiles;

		if (audioTracks.size() > 0 && audioTracks.size() > 0)
		{
			if (audioTracks[0]->getContainerType()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("matroska") || (Path::GetExtension(projectName)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".dgi") && audioTracks[0]->getContainerType() == "MPEG-4"))
				strTrackName = " [";
			else if (audioTracks[0]->getContainerType() == "MPEG-TS" || audioTracks[0]->getContainerType() == "BDAV")
				strTrackName = " PID ";
			else
				strTrackName = " T";

			for (int counter = 0; counter < audioTracks.size(); counter++)
			{
				bool bFound = false;
				QString trackFile = strTrackName + audioTracks[counter]->getTrackIDx() + "*";
				if (Path::GetExtension(projectName)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".dga"))
					trackFile = Path::GetFileName(projectName) + trackFile;
				else if (Path::GetExtension(projectName)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".ffindex"))
					trackFile = Path::GetFileNameWithoutExtension(projectName) + "_track_" + (audioTracks[counter]->getTrackIndex() + 1) + "_*.avs";
				else
					trackFile = Path::GetFileNameWithoutExtension(projectName) + trackFile;

				files = Directory::GetFiles(Path::GetDirectoryName(projectName), trackFile);
				for (QString::const_iterator file = files->begin(); file != files->end(); ++file)
				{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
					if ((*file).EndsWith(".ac3") || (*file).EndsWith(".mp3") || (*file).EndsWith(".mp2") || (*file).EndsWith(".mp1") || (*file).EndsWith(".mpa") || (*file).EndsWith(".dts") || (*file).EndsWith(".wav") || (*file).EndsWith(".ogg") || (*file).EndsWith(".flac") || (*file).EndsWith(".ra") || (*file).EndsWith(".avs") || (*file).EndsWith(".aac")) // It is the right track
					{
						bFound = true;
						if (!audioFiles.ContainsValue(*file))
							audioFiles.insert(make_pair(audioTracks[counter]->getTrackID(), *file));
						break;
					}
				}
				if (!bFound && log != 0)
					log->LogEvent("File not found: " + Path::Combine(Path::GetDirectoryName(projectName), trackFile), Error);
			}

			// Find files which can be deleted
			if (Path::GetExtension(projectName)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".dga"))
				strTrackName = Path::GetFileName(projectName) + strTrackName;
			else
				strTrackName = Path::GetFileNameWithoutExtension(projectName) + strTrackName;

			files = Directory::GetFiles(Path::GetDirectoryName(projectName), strTrackName + "*");
			for (QString::const_iterator file = files->begin(); file != files->end(); ++file)
			{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
				if ((*file).EndsWith(".ac3") || (*file).EndsWith(".mp3") || (*file).EndsWith(".mp2") || (*file).EndsWith(".mp1") || (*file).EndsWith(".mpa") || (*file).EndsWith(".dts") || (*file).EndsWith(".wav") || (*file).EndsWith(".avs") || (*file).EndsWith(".aac")) // It is the right track
				{
					if (!audioFiles.ContainsValue(*file))
						arrDeleteFiles.push_back(*file);
				}
			}
		}

		for (QVector<AudioTrackInfo*>::const_iterator oTrack = audioTracksDebegin(); oTrack != audioTracksDeend(); ++oTrack)
		{
			bool bFound = false;
			QString trackFile = Path::GetDirectoryName(projectName) + "\\" + (*oTrack)->getDemuxFileName();
			if (File::Exists(trackFile))
			{
				bFound = true;
				if (!audioFiles.ContainsValue(trackFile))
					audioFiles.insert(make_pair((*oTrack)->getTrackID(), trackFile));
				continue;
			}
			if (!bFound && log != 0)
				log->LogEvent("File not found: " + trackFile, Error);
		}

		return audioFiles;
	}

	MeXgui::core::util::LogItem *VideoUtil::eliminatedDuplicateFilenames(QString &videoOutput, QString &muxedOutput, AudioJob aStreams[])
	{
		LogItem *log = new LogItem("Eliminating duplicate filenames");
		if (!videoOutput.empty())
			videoOutput = Path::GetFullPath(videoOutput);
		muxedOutput = Path::GetFullPath(muxedOutput);

		log->LogValue("Video output file", videoOutput);
		if (File::Exists(videoOutput))
		{
			int counter = 0;
			QString directoryname = Path::GetDirectoryName(videoOutput);
			QString filename = Path::GetFileNameWithoutExtension(videoOutput);
			QString extension = Path::GetExtension(videoOutput);

			while (File::Exists(videoOutput))
			{
				videoOutput = Path::Combine(directoryname, filename + "_" + counter + extension);
				counter++;
			}

			log->LogValue("File already exists. New video output filename", videoOutput);
		}

		log->LogValue("Muxed output file", muxedOutput);
		if (File::Exists(muxedOutput) || muxedOutput == videoOutput)
		{
			int counter = 0;
			QString directoryname = Path::GetDirectoryName(muxedOutput);
			QString filename = Path::GetFileNameWithoutExtension(muxedOutput);
			QString extension = Path::GetExtension(muxedOutput);

			while (File::Exists(muxedOutput) || muxedOutput == videoOutput)
			{
				muxedOutput = Path::Combine(directoryname, filename + "_" + counter + extension);
				counter++;
			}

			log->LogValue("File already exists. New muxed output filename", muxedOutput);
		}

		for (int i = 0; i < sizeof(aStreams) / sizeof(aStreams[0]); i++)
		{
			QString name = Path::GetFullPath(aStreams[i]->Output);
			log->LogValue("Encodable audio stream " + i, name);
			if (name.Equals(videoOutput) || name.Equals(muxedOutput)) // audio will be overwritten -> no good
			{
				name = Path::Combine(Path::GetDirectoryName(name), Path::GetFileNameWithoutExtension(name) + StringConverterHelper::toString(i) + Path::GetExtension(name));
				aStreams[i]->Output = name;
				log->LogValue("Stream has the same name as video stream. New audio stream output", name);
			}
		}
		return log;

	}

	QString VideoUtil::checkVideo(const QString &avsFile)
	{
		return checkVideo(avsFile, true);
	}

	QString VideoUtil::checkVideo(const QString &avsFile, bool tryToFix)
	{
		try
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AvsFile avi = AvsFile.OpenScriptFile(avsFile))
			AvsFile *avi = AvsFile::OpenScriptFile(avsFile);
			try
			{
				if (avi->getClip()->getOriginalColorspace() != YV12 && avi->getClip()->getOriginalColorspace() != I420)
				{
					if (tryToFix && !isConvertedToYV12(avsFile))
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						bool convert = mainForm->getDialogManager()->addConvertToYV12(avi->getClip()->getOriginalColorspace().ToString());
						if (convert)
						{
							if (appendConvertToYV12(avsFile))
							{
								QString sResult = checkVideo(avsFile, false); // Check everything again, to see if it is all fixed now
								if (sResult == "")
									return 0;
								else
									return sResult;
							}
						}
						return "You didn't want me to append ConvertToYV12(). You'll have to fix the colorspace problem yourself.";
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return QString::Format("AviSynth clip is in {0} not in YV12, even though ConvertToYV12() has been appended.", avi->getClip()->getOriginalColorspace().ToString());
				}

				VideoCodecSettings *settings = GetCurrentVideoSettings();
				if (settings != 0 && settings->getSettingsID() != "x264") // mod16 restriction
				{
					if (avi->getClip()->getVideoHeight() % 16 != 0 || avi->getClip()->getVideoWidth() % 16 != 0)
						return QString::Format("AviSynth clip doesn't have mod16 dimensions:\r\nWidth: {0}\r\nHeight:{1}\r\n" + "This could cause problems with some encoders,\r\n" + "and will also result in a loss of compressibility.\r\n" + "I suggest you resize to a mod16 resolution.", avi->getClip()->getVideoWidth(), avi->getClip()->getVideoHeight());
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (avi != 0)
					avi.Dispose();
			}
		}
		catch (std::exception &e)
		{
			return "Error in AviSynth script:\r\n" + e.what();
		}
		return 0;
	}

	bool VideoUtil::appendConvertToYV12(const QString &file)
	{
		try
		{
			StreamWriter *avsOut = new StreamWriter(file, true);
			avsOut->Write("\r\nConvertToYV12()");
			avsOut->Close();
		}
		catch (IOException *e1)
		{
			return false;
		}
		return true;
	}

	bool VideoUtil::isConvertedToYV12(const QString &file)
	{
		try
		{
			QString strLastLine = "", line = "";
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (StreamReader reader = new StreamReader(file))
			StreamReader *reader = new StreamReader(file);
			try
			{
				while ((line = reader->ReadLine()) != 0)
				{
					if (!line.empty())
						strLastLine = line;
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (reader != 0)
					reader.Dispose();
			}
			if (strLastLine.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("converttoyv12()"))
				return true;
			else
				return false;
		}
		catch (...)
		{
			return false;
		}
	}

	VideoCodecSettings *VideoUtil::GetCurrentVideoSettings()
	{
		if (mainForm->InvokeRequired)
			return static_cast<VideoCodecSettings*>(mainForm->Invoke(new CurrentSettingsDelegate(GetCurrentVideoSettings)));
		else
			return mainForm->getVideo()->getCurrentSettings();
	}

	MeXgui::core::details::JobChain *VideoUtil::GenerateJobSeries(VideoStream *video, const QString &muxedOutput, AudioJob audioStreams[], MuxStream subtitles[], const QString &chapters, Nullable<FileSize> desiredSize, Nullable<FileSize> splitSize, ContainerType *container, bool prerender, MuxStream muxOnlyAudio[], LogItem *log, const QString &deviceType, Zone zones[], const QString &videoFileToMux, OneClickAudioTrack audioTracks[], bool alwaysMuxOutput)
	{
		if (desiredSize.HasValue && videoFileToempty())
		{
			if (video->getSettings()->getEncodingMode() != 4 && video->getSettings()->getEncodingMode() != 8) // no automated 2/3 pass
			{
				if (this->mainForm->getSettings()->getNbPasses() == 2)
					video->getSettings()->setEncodingMode(4); // automated 2 pass
				else if (video->getSettings()->getMaxNumberOfPasses() == 3)
					video->getSettings()->setEncodingMode(8);
			}
		}

		fixFileNameExtensions(video, audioStreams, container);
		QString videoOutput = video->getOutput();
		log->Add(eliminatedDuplicateFilenames(videoOutput, muxedOutput, audioStreams));

		JobChain *vjobs = 0;
		if (!videoFileToempty())
			video->setOutput(videoFileToMux);
		else
		{
			video->setOutput(videoOutput);
			vjobs = jobUtil->prepareVideoJob(video->getInput(), video->getOutput(), video->getSettings(), video->getDAR(), prerender, true, zones);
			if (vjobs == 0)
				return 0;
		}

		/* Here, we guess the types of the files based on extension.
		 * This is guaranteed to work with MeXgui-encoded files, because
		 * the extension will always be recognised. For non-MeXgui files,
		 * we can only ever hope.*/
		QVector<MuxStream*> allAudioToMux = QVector<MuxStream*>();
		QVector<MuxableType*> allInputAudioTypes = QVector<MuxableType*>();

		if (audioTracks != 0)
		{
			// OneClick mode
			for (MeXgui::OneClickAudioTrack::const_iterator ocAudioTrack = audioTracks->begin(); ocAudioTrack != audioTracks->end(); ++ocAudioTrack)
			{
				if ((*ocAudioTrack)->getDirectMuxAudio() != 0)
				{
					if (VideoUtil::guessAudioMuxableType((*ocAudioTrack)->getDirectMuxAudio()->path, true) != 0)
					{
						allInputAudioTypes.push_back(VideoUtil::guessAudioMuxableType((*ocAudioTrack)->getDirectMuxAudio()->path, true));
						allAudioTopush_back((*ocAudioTrack)->getDirectMuxAudio());
					}
				}
				if ((*ocAudioTrack)->getAudioJob() != 0 && !(*ocAudioTrack)->getAudioJob()->Input->empty())
				{
					allAudioTopush_back((*ocAudioTrack)->getAudioJob()->ToMuxStream());
					allInputAudioTypes.push_back((*ocAudioTrack)->getAudioJob()->ToMuxableType());
				}
			}
		}
		else
		{
			// AutoEncode mode
			for (MeXgui::AudioJob::const_iterator stream = audioStreams->begin(); stream != audioStreams->end(); ++stream)
			{
				allAudioTopush_back((*stream)->ToMuxStream());
				allInputAudioTypes.push_back((*stream)->ToMuxableType());
			}

			for (MeXgui::core::details::MuxStream::const_iterator muxStream = muxOnlyAudio->begin(); muxStream != muxOnlyAudio->end(); ++muxStream)
			{
				if (VideoUtil::guessAudioMuxableType((*muxStream)->path, true) != 0)
				{
					allInputAudioTypes.push_back(VideoUtil::guessAudioMuxableType((*muxStream)->path, true));
					allAudioTopush_back(*muxStream);
				}
			}
		}

		QVector<MuxableType*> allInputSubtitleTypes = QVector<MuxableType*>();
		for (MeXgui::core::details::MuxStream::const_iterator muxStream = subtitles->begin(); muxStream != subtitles->end(); ++muxStream)
			if (VideoUtil::guessSubtitleType((*muxStream)->path) != 0)
				allInputSubtitleTypes.push_back(new MuxableType(VideoUtil::guessSubtitleType((*muxStream)->path), 0));

		MuxableType *chapterInputType = 0;
		if (!chapters.empty())
		{
			ChapterType *type = VideoUtil::guessChapterType(chapters);
			if (type != 0)
				chapterInputType = new MuxableType(type, 0);
		}

		MuxableType *deviceOutputType = 0;
		if (!deviceType.empty())
		{
			DeviceType *type = VideoUtil::guessDeviceType(deviceType);
			if (type != 0)
				deviceOutputType = new MuxableType(type, 0);
		}

		QVector<QString> inputsToDelete = QVector<QString>();
		if (videoFileToempty())
			inputsToDelete.push_back(video->getOutput());
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		inputsToDelete.AddRange(Array::ConvertAll<AudioJob*, QString>(audioStreams, delegate(AudioJob a)
		{
			return a::Output;
		}
	   ));

		JobChain *muxJobs = jobUtil->GenerateMuxJobs(video, video->getFramerate(), allAudioToToArray(), allInputAudioTypes.ToArray(), subtitles, allInputSubtitleTypes.ToArray(), chapters, chapterInputType, container, muxedOutput, splitSize, inputsToDelete, deviceType, deviceOutputType, alwaysMuxOutput);

		if (desiredSize.HasValue && videoFileToempty())
		{
			BitrateCalculationInfo *b = new BitrateCalculationInfo();

			QVector<QString> audiofiles = QVector<QString>();
			for (QVector<MuxStream*>::const_iterator s = allAudioTobegin(); s != allAudioToend(); ++s)
				audiofiles.push_back((*s)->path);
			b->AudioFiles = audiofiles;

			b->Container = container;
			b->setVideoJobs(QVector<TaggedJob*>(vjobs->Jobs));
			b->DesiredSize = desiredSize.Value;
			(static_cast<VideoJob*>(vjobs->Jobs[0]->Job))->BitrateCalculationInfo_Renamed = b;
		}

		if (!videoFileToempty())
			return new SequentialChain(new SequentialChain(static_cast<Job[]>(audioStreams)), new SequentialChain(muxJobs));
		else
			return new SequentialChain(new SequentialChain(static_cast<Job[]>(audioStreams)), new SequentialChain(vjobs), new SequentialChain(muxJobs));
	}

	void VideoUtil::fixFileNameExtensions(VideoStream *video, AudioJob audioStreams[], ContainerType *container)
	{
		AudioEncoderType audioCodecs[sizeof(audioStreams) / sizeof(audioStreams[0])];
		for (int i = 0; i < sizeof(audioStreams) / sizeof(audioStreams[0]); i++)
		{
			audioCodecs[i] = audioStreams[i]->Settings->getEncoderType();
		}
		MuxPath *path;
		if (video->getSettings() == 0)
			path = mainForm->getMuxProvider()->GetMuxPath(VideoEncoderType::X264, audioCodecs, container);
		else
			path = mainForm->getMuxProvider()->GetMuxPath(video->getSettings()->getEncoderType(), audioCodecs, container);
		if (path == 0)
			return;
		QVector<AudioType*> audioTypes = QVector<AudioType*>();
		for (QVector<MuxableType*>::const_iterator type = path->getInitialInputTypes().begin(); type != path->getInitialInputTypes().end(); ++type)
		{
			if (dynamic_cast<VideoType*>((*type)->outputType) != 0)
			{
				// see http://forum.doom9.org/showthread.php?p=1243370#post1243370
				if (video->getSettings()->getEncoderType() == VideoEncoderType::X264 && (mainForm->getSettings()->getForceRawAVCExtension() || (*type)->outputType->ContainerType == ContainerType::MP4))
					video->setOutput(Path::ChangeExtension(video->getOutput(), ".264"));
				else
					video->setOutput(Path::ChangeExtension(video->getOutput(), (*type)->outputType->Extension));
				video->setVideoType(*type);
			}
			if (dynamic_cast<AudioType*>((*type)->outputType) != 0)
			{
				audioTypes.push_back(static_cast<AudioType*>((*type)->outputType));
			}
		}
		AudioEncoderProvider *aProvider = new AudioEncoderProvider();
		for (int i = 0; i < sizeof(audioStreams) / sizeof(audioStreams[0]); i++)
		{
//ORIGINAL LINE: AudioType[] types = aProvider.GetSupportedOutput(audioStreams[i].Settings.EncoderType);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			AudioType *types = aProvider->GetSupportedOutput(audioStreams[i]->Settings->getEncoderType());
			for (MeXgui::AudioType::const_iterator type = types->begin(); type != types->end(); ++type)
			{
				if (std::find(audioTypes.begin(), audioTypes.end(), *type) != audioTypes.end())
				{
					audioStreams[i]->Output = Path::ChangeExtension(audioStreams[i]->Output, (*type)->getExtension());
					break;
				}
			}
		}
	}

	SubtitleType *VideoUtil::guessSubtitleType(const QString &p)
	{
		if (p.empty())
			return 0;

		for (MeXgui::GenericRegisterer<SubtitleType*>::const_iterator type = ContainerManager::SubtitleTypes->begin(); type != ContainerManager::SubtitleTypes->end(); ++type)
		{
			if (Path::GetExtension(p.ToLower(System::Globalization::CultureInfo::InvariantCulture)) == "." + type->second->Extension)
				return type->second;
		}
		return 0;
	}

	VideoType *VideoUtil::guessVideoType(const QString &p)
	{
		for (MeXgui::GenericRegisterer<VideoType*>::const_iterator type = ContainerManager::VideoTypes->begin(); type != ContainerManager::VideoTypes->end(); ++type)
		{
			if (Path::GetExtension(p.ToLower(System::Globalization::CultureInfo::InvariantCulture)) == "." + type->second->Extension)
				return type->second;
		}
		return 0;
	}

	AudioType *VideoUtil::guessAudioType(const QString &p)
	{
		for (MeXgui::GenericRegisterer<AudioType*>::const_iterator type = ContainerManager::AudioTypes->begin(); type != ContainerManager::AudioTypes->end(); ++type)
		{
			if (Path::GetExtension(p.ToLower(System::Globalization::CultureInfo::InvariantCulture)) == "." + type->second->Extension)
				return type->second;
		}
		return 0;
	}

	ChapterType *VideoUtil::guessChapterType(const QString &p)
	{
		for (MeXgui::GenericRegisterer<ChapterType*>::const_iterator type = ContainerManager::ChapterTypes->begin(); type != ContainerManager::ChapterTypes->end(); ++type)
		{
			if (Path::GetExtension(p.ToLower(System::Globalization::CultureInfo::InvariantCulture)) == "." + type->second->Extension)
				return type->second;
		}
		return 0;
	}

	DeviceType *VideoUtil::guessDeviceType(const QString &p)
	{
		for (MeXgui::GenericRegisterer<DeviceType*>::const_iterator type = ContainerManager::DeviceTypes->begin(); type != ContainerManager::DeviceTypes->end(); ++type)
		{
			if (p == type->second->Extension)
				return type->second;
		}
		return 0;
	}

	MuxableType *VideoUtil::guessVideoMuxableType(const QString &p, bool useMediaInfo)
	{
		if (p.empty())
			return 0;
		if (useMediaInfo)
		{
			MediaInfoFile *info = new MediaInfoFile(p);
			if (info->getVideoInfo()->HasVideo)
				return new MuxableType(info->getVideoInfo()->getType(), info->getVideoInfo()->getCodec());
			// otherwise we may as well try the other route too
		}
		VideoType *vType = guessVideoType(p);
		if (vType != 0)
		{
			if (sizeof(vType->getSupportedCodecs()) / sizeof(vType->getSupportedCodecs()[0]) == 1)
				return new MuxableType(vType, vType->getSupportedCodecs()[0]);
			else
				return new MuxableType(vType, 0);
		}
		return 0;
	}

	MuxableType *VideoUtil::guessAudioMuxableType(const QString &p, bool useMediaInfo)
	{
		if (p.empty())
			return 0;
		if (useMediaInfo)
		{
			MediaInfoFile *info = new MediaInfoFile(p);
			if (info->getAudioInfo()->getType() != 0)
				return new MuxableType(info->getAudioInfo()->getType(), info->getAudioInfo()->getCodecs()[0]);
		}
		AudioType *aType = guessAudioType(p);
		if (aType != 0)
		{
			if (sizeof(aType->getSupportedCodecs()) / sizeof(aType->getSupportedCodecs()[0]) == 1)
				return new MuxableType(aType, aType->getSupportedCodecs()[0]);
			else
				return new MuxableType(aType, 0);
		}
		return 0;
	}

	QString VideoUtil::convertChaptersTextFileTox264QPFile(const QString &filename, double framerate)
	{
		StreamWriter *sw = 0;
		QString qpfile = "";
		if (File::Exists(filename))
		{
			StreamReader *sr = 0;
			QString line = "";
			qpfile = Path::ChangeExtension(filename, ".qpf");
			sw = new StreamWriter(qpfile, false, System::Text::Encoding::Default);
			try
			{
				sr = new StreamReader(filename);
				Chapter chap = Chapter();
				while ((line = sr->ReadLine()) != 0)
				{
					if (line.find("NAME") == -1) // chapter time
					{
						QString tc = line.substr(line.find("=") + 1);
						chap.timecode = tc;
						int chapTime = Util::getTimeCode(chap.timecode);
						int frameNumber = Util::convertTimecodeToFrameNumber(chapTime, framerate);
						sw->WriteLine(StringConverterHelper::toString(frameNumber) + " K");
					}
				}

			}
			catch (std::exception &f)
			{
				MessageBox::Show(f.what());
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (sw != 0)
				{
					try
					{
						sw->Close();
					}
					catch (std::exception &f)
					{
						MessageBox::Show(f.what());
					}
				}
			}
		}
		return qpfile;
	}

	QString VideoUtil::GenerateCombinedFilter(OutputFileType types[])
	{
		StringBuilder *initialFilterName = new StringBuilder();
		StringBuilder *initialFilter = new StringBuilder();
		StringBuilder *allSmallFilters = new StringBuilder();
		initialFilterName->Append("All supported files (");
		for (MeXgui::OutputFileType::const_iterator type = types->begin(); type != types->end(); ++type)
		{
			initialFilter->Append((*type)->getOutputFilter());
			initialFilter->Append(";");
			initialFilterName->Append((*type)->getOutputFilter());
			initialFilterName->Append(", ");
			allSmallFilters->Append((*type)->getOutputFilterString());
			allSmallFilters->Append("|");
		}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimEnd' method:
		QString initialFilterTrimmed = initialFilterName->ToString()->TrimEnd(' ', ',') + ")|" + initialFilter->ToString();

		if (sizeof(types) / sizeof(types[0]) > 1)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimEnd' method:
			return initialFilterTrimmed + "|" + allSmallFilters->ToString()->TrimEnd('|');
		else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimEnd' method:
			return allSmallFilters->ToString()->TrimEnd('|');
	}

	void VideoUtil::getAvisynthVersion(LogItem *i)
	{
		QString fileVersion = "";
		QString fileDate = "";
		bool bLocal = false;
		bool bFound = false;

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		QString syswow64path = Environment::GetFolderPath(Environment::SpecialFolder::System)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace("\\system32", "\\SysWOW64");
	#if defined(x86)
		// on x86, try the SysWOW64 folder first
		if (File::Exists(Path::Combine(syswow64path, "avisynth.dll")))
		{
			QString path = Path::Combine(syswow64path, "avisynth.dll");
			FileVersionInfo *FileProperties = FileVersionInfo::GetVersionInfo(path);
			fileVersion = FileProperties->FileVersion;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			fileDate = File::GetLastWriteTimeUtc(path)->ToString("dd-MM-yyyy");
			bFound = true;
		}
		else if (!Directory::Exists(syswow64path) && File::Exists(Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::System), "avisynth.dll")))
			if (File::Exists(Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::System), "avisynth.dll")))
	#else
		if (File::Exists(Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::System), "avisynth.dll")))
	#endif
	#if defined(x64)
	#endif
		{
			QString path = Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::System), "avisynth.dll");
			FileVersionInfo *FileProperties = FileVersionInfo::GetVersionInfo(path);
			fileVersion = FileProperties->FileVersion;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			fileDate = File::GetLastWriteTimeUtc(path)->ToString("dd-MM-yyyy");
			bFound = true;
		}

		if (File::Exists(Path::Combine(Path::GetDirectoryName(Application::ExecutablePath), "avisynth.dll")))
		{
			QString pathRoot = Path::GetDirectoryName(Application::ExecutablePath);
			if (File::Exists(MainForm::Instance->getSettings()->getAviSynthPath()))
			{
				QString pathTool = Path::GetDirectoryName(MainForm::Instance->getSettings()->getAviSynthPath());
				if (File::GetLastWriteTimeUtc(Path::Combine(pathRoot, "avisynth.dll")) != File::GetLastWriteTimeUtc(Path::Combine(pathTool, "avisynth.dll")))
					File::Copy(Path::Combine(pathTool, "avisynth.dll"), Path::Combine(pathRoot, "Avisynth.dll"), true);
				if (!File::Exists(Path::Combine(pathRoot, "devil.dll")) || File::GetLastWriteTimeUtc(Path::Combine(pathRoot, "devil.dll")) != File::GetLastWriteTimeUtc(Path::Combine(pathTool, "devil.dll")))
					File::Copy(Path::Combine(pathTool, "devil.dll"), Path::Combine(pathRoot, "DevIL.dll"), true);
			}

			if (bFound && i != 0)
			{
				QString strVersion = "";
				if (fileVersion.empty())
					strVersion = " (" + fileDate + ")";
				else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					strVersion = fileVersion.Replace(", ", ".")->ToString() + " (" + fileDate + ")";
				i->LogValue("AviSynth", strVersion + " (inactive)");
			}

			FileVersionInfo *FileProperties = FileVersionInfo::GetVersionInfo(Path::Combine(pathRoot, "avisynth.dll"));
			fileVersion = FileProperties->FileVersion;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			fileDate = File::GetLastWriteTimeUtc(Path::Combine(pathRoot, "avisynth.dll"))->ToString("dd-MM-yyyy");
			bLocal = true;

			if (i != 0)
			{
				QString strVersion = "";
				if (fileVersion.empty())
					strVersion = " (" + fileDate + ")";
				else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					strVersion = fileVersion.Replace(", ", ".")->ToString() + " (" + fileDate + ")";
				if (bFound)
					strVersion += " (active)";
				i->LogValue("AviSynth portable", strVersion);
			}
		}
		else
		{
			if (File::Exists(Path::Combine(Path::GetDirectoryName(Application::ExecutablePath), "devil.dll")))
				FileUtil::DeleteFile(Path::Combine(Path::GetDirectoryName(Application::ExecutablePath), "devil.dll"));
			if (bFound && i != 0)
			{
				QString strVersion = "";
				if (fileVersion.empty())
					strVersion = " (" + fileDate + ")";
				else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					strVersion = fileVersion.Replace(", ", ".")->ToString() + " (" + fileDate + ")";
				i->LogValue("AviSynth", strVersion);
			}
		}

		if (!bFound && !bLocal)
		{
			if (File::Exists(MainForm::Instance->getSettings()->getAviSynthPath()))
			{
				if (i != 0)
					i->LogValue("AviSynth", "files will be copied into the MeXgui directory as AviSynth is not installed");
				QString path = Path::GetDirectoryName(MainForm::Instance->getSettings()->getAviSynthPath());
				try
				{
					File::Copy(Path::Combine(path, "avisynth.dll"), Path::Combine(Path::GetDirectoryName(Application::ExecutablePath), "Avisynth.dll"), true);
					File::Copy(Path::Combine(path, "devil.dll"), Path::Combine(Path::GetDirectoryName(Application::ExecutablePath), "DevIL.dll"), true);
					path = Path::Combine(Path::GetDirectoryName(Application::ExecutablePath), "avisynth.dll");
					FileVersionInfo *FileProperties = FileVersionInfo::GetVersionInfo(path);
					fileVersion = FileProperties->FileVersion;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					fileDate = File::GetLastWriteTimeUtc(path)->ToString("dd-MM-yyyy");
					bLocal = true;

					if (i != 0)
					{
						QString strVersion = "";
						if (fileVersion.empty())
							strVersion = " (" + fileDate + ")";
						else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
							strVersion = fileVersion.Replace(", ", ".")->ToString() + " (" + fileDate + ")";
						i->LogValue("AviSynth portable", strVersion);
					}
				}
				catch (...)
				{
				}
			}
		}
		if (!bLocal && !bFound && i != 0)
			i->LogValue("AviSynth", "not installed", Error);
		MainForm::Instance->getSettings()->setPortableAviSynth(bLocal);
	}

	QString VideoUtil::getFFMSInputLine(const QString &inputFile, const QString &indexFile, double fps)
	{
		return getFFMSBasicInputLine(inputFile, indexFile, 0, 0, 0);
	}

	QString VideoUtil::getFFMSBasicInputLine(const QString &inputFile, const QString &indexFile, int rffmode, int fpsnum, int fpsden)
	{
		StringBuilder *script = new StringBuilder();
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (inputFile.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".ffindex"))
			inputFile = inputFile.substr(0, inputFile.length() - 8);
		script->AppendLine("LoadPlugin(\"" + Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getFFMSIndexPath()), "ffms2.dll") + "\")");
		script->Append("FFVideoSource(\"" + inputFile + "\"");
		if (!indexFile.empty() && !indexFile.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(inputFile.ToLower(System::Globalization::CultureInfo::InvariantCulture) + ".ffindex"))
			script->Append(", cachefile=\"" + indexFile + "\"");
		if (fpsnum > 0 && fpsden > 0)
			script->Append(", fpsnum=" + fpsnum + ", fpsden=" + fpsden);
		if (MainForm::Instance->getSettings()->getFFMSThreads() > 0)
			script->Append(", threads=" + MainForm::Instance->getSettings()->getFFMSThreads());
		if (rffmode > 0)
			script->Append(", rffmode=" + rffmode);
		script->Append(")");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return script->ToString();
	}

	QString VideoUtil::getAssumeFPS(double fps, const QString &strInput)
	{
		int fpsnum;
		int fpsden;

		if (!getFPSFraction(fps, strInput, fpsnum, fpsden))
			return "";

		return ".AssumeFPS(" + fpsnum + "," + fpsden + ")";
	}

	bool VideoUtil::getFPSFraction(double fps, const QString &strInput, int &fpsnum, int &fpsden)
	{
		fpsnum = fpsden = 0;

		if (fps <= 0)
		{
			if (!File::Exists(strInput))
				return false;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if (strInput.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".ffindex"))
				strInput = strInput.substr(0, strInput.length() - 8);
			if (Path::GetExtension(strInput)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".avs"))
			{
				fps = GetFPSFromAVSFile(strInput);
				if (fps <= 0)
					return false;
			}
			else
			{
				MediaInfoFile *oInfo = new MediaInfoFile(strInput);
				if (oInfo->getVideoInfo()->HasVideo && oInfo->getVideoInfo()->FPS > 0)
					fps = oInfo->getVideoInfo()->FPS;
				else
					return false;
			}
		}

		double dFPS = Math::Round(fps, 3);
		if (dFPS == 23.976)
		{
			fpsnum = 24000;
			fpsden = 1001;
		}
		else if (dFPS == 29.970)
		{
			fpsnum = 30000;
			fpsden = 1001;
		}
		else if (dFPS == 59.940)
		{
			fpsnum = 60000;
			fpsden = 1001;
		}
		else if (dFPS == 119.880)
		{
			fpsnum = 120000;
			fpsden = 1001;
		}
		else
		{
			dFPS = dFPS * 1000;
			if (dFPS % 1000 == 0)
			{
				fpsnum = static_cast<int>(floor(dFPS / 1000));
				fpsden = 1;
			}
			else if (dFPS % 100 == 0)
			{
				fpsnum = static_cast<int>(floor(dFPS / 100));
				fpsden = 10;
			}
			else if (dFPS % 1000 == 0)
			{
				fpsnum = static_cast<int>(floor(dFPS / 10));
				fpsden = 100;
			}
			else
			{
				fpsnum = static_cast<int>(dFPS);
				fpsden = 1000;
			}
		}
		return true;
	}

	double VideoUtil::GetFPSFromAVSFile(const QString &strAVSScript)
	{
		try
		{
			if (!Path::GetExtension(strAVSScript)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".avs"))
				return 0;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AviSynthScriptEnvironment env = new AviSynthScriptEnvironment())
			AviSynthScriptEnvironment *env = new AviSynthScriptEnvironment();
			try
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (AviSynthClip a = env.OpenScriptFile(strAVSScript))
				AviSynthClip *a = env->OpenScriptFile(strAVSScript);
				try
				{
					if (a->getHasVideo())
						return static_cast<double>(a->getraten()) / static_cast<double>(a->getrated());
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (a != 0)
						a.Dispose();
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (env != 0)
					env.Dispose();
			}
			return 0;
		}
		catch (...)
		{
			return 0;
		}
	}

	CropValues *CropValues::Clone()
	{
		return static_cast<CropValues*>(this->MemberwiseClone());
	}

	bool CropValues::isCropped()
	{
		if (left != 0 || top != 0 || right != 0 || bottom != 0)
			return true;
		else
			return false;
	}

	SubtitleInfo::SubtitleInfo(const QString &name, int index)
	{
		this->name = name;
		this->index = index;
	}

	const QString &SubtitleInfo::getName() const
	{
		return name;
	}

	void SubtitleInfo::setName(const QString &value)
	{
		name = value;
	}

	const int &SubtitleInfo::getIndex() const
	{
		return index;
	}

	void SubtitleInfo::setIndex(const int &value)
	{
		index = value;
	}

	QString SubtitleInfo::ToString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		QString fullString = "[" + this->index.ToString("D2") + "] - " + this->name;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		return fullString.Trim();
	}
}
