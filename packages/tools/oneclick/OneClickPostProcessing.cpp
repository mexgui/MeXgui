#include "OneClickPostProcessing.h"




//using namespace System::Collections::Generic;



//using namespace System::Threading;
using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const OneClickPostProcessing::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "OneClickPostProcessing");

	IJobProcessor *OneClickPostProcessing::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<OneClickPostProcessingJob*>(j) != 0)
			return new OneClickPostProcessing(mf);
		return 0;
	}

	OneClickPostProcessing::OneClickPostProcessing(MainForm *mf)
	{
		InitializeInstanceFields();
		mainForm = mf;
		this->vUtil = new VideoUtil(mainForm);
	}

	void OneClickPostProcessing::Start()
	{
		Util::ensureExists(job->Input);
		_processThread = new Thread(new ThreadStart(this->StartPostProcessing));
		_processThread->Priority = ThreadPriority::BelowNormal;
		_processThread->Start();
	}

	void OneClickPostProcessing::Abort()
	{
		_processThread->Abort();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete _processThread;
		if (_processTime != 0)
		{
			_processTime->Abort();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete _processTime;
		}
		if (_sourceDetector != 0)
		{
			_sourceDetector->stop();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete _sourceDetector;
		}
	}

	void OneClickPostProcessing::safeDelete(const QString &filePath)
	{
		try
		{
			File::Delete(filePath);
		}
		catch (...)
		{
			// Do Nothing
		}
	}

	void OneClickPostProcessing::raiseEvent()
	{
		StatusUpdate(su);
	}

	void OneClickPostProcessing::setProgress(decimal n)
	{
		if (n * 100 < su->getPercentageDoneExact())
			_start = DateTime::Now;
		su->setPercentageDoneExact(n * 100);
		su->setTimeElapsed(DateTime::Now - _start);
		su->FillValues();
		raiseEvent();
	}

	void OneClickPostProcessing::updateTime()
	{
		su->setTimeElapsed(DateTime::Now - _start);
		su->FillValues();
		raiseEvent();
	}

	void OneClickPostProcessing::raiseEvent(const QString &s)
	{
		su->setStatus(s);
		raiseEvent();
	}

	void OneClickPostProcessing::StartPostProcessing()
	{

		try
		{
			_log->LogEvent("Processing thread started");
			raiseEvent("Preprocessing...   ***PLEASE WAIT***");
			_start = DateTime::Now;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			_processTime = new Thread(new ThreadStart(delegate
			{
				while (true)
				{
					updateTime();
					delay(1000);
				}
			}
		   ));
			_processTime->Start();

			QVector<QString> arrAudioFilesDelete = QVector<QString>();
			audioFiles = QMap<int, QString>();
			QVector<AudioTrackInfo*> arrAudioTracks = QVector<AudioTrackInfo*>();
			QVector<AudioJob*> arrAudioJobs = QVector<AudioJob*>();
			QVector<MuxStream*> arrMuxStreams = QVector<MuxStream*>();
			QVector<QString> intermediateFiles = QVector<QString>();

			FileUtil::ensureDirectoryExists(job->getPostprocessingProperties()->getWorkingDirectory());

			// audio handling
			for (QVector<OneClickAudioTrack*>::const_iterator oAudioTrack = job->getPostprocessingProperties()->getAudioTracks().begin(); oAudioTrack != job->getPostprocessingProperties()->getAudioTracks().end(); ++oAudioTrack)
			{
				if ((*oAudioTrack)->getAudioTrackInfo() != 0)
				{
					if ((*oAudioTrack)->getAudioTrackInfo()->ExtractMKVTrack)
					{
						if (job->getPostprocessingProperties()->getApplyDelayCorrection() && File::Exists(job->getPostprocessingProperties()->getVideoFileToMux()))
						{
							MediaInfoFile *oFile = new MediaInfoFile(job->getPostprocessingProperties()->getVideoFileToMux(), _log);
							bool bFound = false;
							for (QVector<AudioTrackInfo*>::const_iterator oAudioInfo = oFile->getAudioInfo()->getTracks().begin(); oAudioInfo != oFile->getAudioInfo()->getTracks().end(); ++oAudioInfo)
							{
								if ((*oAudioInfo)->getMMGTrackID() == (*oAudioTrack)->getAudioTrackInfo()->MMGTrackID)
									bFound = true;
							}
							int mmgTrackID = 0;
							if (!bFound)
								mmgTrackID = oFile->getAudioInfo()->getTracks()[(*oAudioTrack)->getAudioTrackInfo()->TrackIndex]->getMMGTrackID();
							else
								mmgTrackID = (*oAudioTrack)->getAudioTrackInfo()->MMGTrackID;
							for (QVector<AudioTrackInfo*>::const_iterator oAudioInfo = oFile->getAudioInfo()->getTracks().begin(); oAudioInfo != oFile->getAudioInfo()->getTracks().end(); ++oAudioInfo)
							{
								if ((*oAudioInfo)->getMMGTrackID() == mmgTrackID)
								{
									if ((*oAudioTrack)->getDirectMuxAudio() != 0)
										(*oAudioTrack)->getDirectMuxAudio()->delay = (*oAudioInfo)->getDelay();
									if ((*oAudioTrack)->getAudioJob() != 0)
										(*oAudioTrack)->getAudioJob()->Delay = (*oAudioInfo)->getDelay();
									break;
								}
							}
						}
						audioFiles.insert(make_pair((*oAudioTrack)->getAudioTrackInfo()->TrackID, job->getPostprocessingProperties()->getWorkingDirectory() + "\\" + (*oAudioTrack)->getAudioTrackInfo()->DemuxFileName));
						arrAudioFilesDelete.push_back(job->getPostprocessingProperties()->getWorkingDirectory() + "\\" + (*oAudioTrack)->getAudioTrackInfo()->DemuxFileName);
					}
					else
						arrAudioTracks.push_back((*oAudioTrack)->getAudioTrackInfo());
				}
				if ((*oAudioTrack)->getAudioJob() != 0)
				{
					if (job->getPostprocessingProperties()->getIndexType() == FileIndexerWindow::NONE && (*oAudioTrack)->getAudioJob()->Input->empty())
						(*oAudioTrack)->getAudioJob()->Input = job->Input;
					arrAudioJobs.push_back((*oAudioTrack)->getAudioJob());
				}
				if ((*oAudioTrack)->getDirectMuxAudio() != 0)
					arrMuxStreams.push_back((*oAudioTrack)->getDirectMuxAudio());
			}
			if (audioFiles.empty() && job->getPostprocessingProperties()->getIndexType() != FileIndexerWindow::NONE && !job->getPostprocessingProperties()->getEac3toDemux())
				audioFiles = vUtil->getAllDemuxedAudio(arrAudioTracks, QVector<AudioTrackInfo*>(), arrAudioFilesDelete, job->getIndexFile(), _log);

			fillInAudioInformation(arrAudioJobs, arrMuxStreams);

			if (!job->getPostprocessingProperties()->getVideoFileToMux().empty())
				_log->LogEvent("Don't encode video: True");
			else
				_log->LogEvent("Desired size: " + job->getPostprocessingProperties()->getOutputSize());
			_log->LogEvent("Split size: " + job->getPostprocessingProperties()->getSplitting());


			// chapter file handling
			if (job->getPostprocessingProperties()->getChapterFile().empty())
			{
				job->getPostprocessingProperties()->setChapterFile("");
			}
			else if (job->getPostprocessingProperties()->getContainer() == ContainerType::AVI)
			{
				_log->LogEvent("Chapter handling disabled because of the AVI target container");
				job->getPostprocessingProperties()->setChapterFile("");
			}
			else if (!File::Exists(job->getPostprocessingProperties()->getChapterFile()))
			{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
				if (job->getPostprocessingProperties()->getChapterFile().StartsWith("<") || job->getPostprocessingProperties()->getChapterExtracted())
				{
					// internal chapter file
					QString strTempFile = job->getPostprocessingProperties()->getChapterFile();
					if (File::Exists(job->getPostprocessingProperties()->getIFOInput()))
					{
						job->getPostprocessingProperties()->setChapterFile(VideoUtil::getChaptersFromIFO(job->getPostprocessingProperties()->getIFOInput(), false, job->getPostprocessingProperties()->getWorkingDirectory(), job->getPostprocessingProperties()->getTitleNumberToProcess()));
						if (!job->getPostprocessingProperties()->getChapterFile().empty())
						{
							intermediateFiles.push_back(job->getPostprocessingProperties()->getChapterFile());
							job->getPostprocessingProperties()->setChapterExtracted(true);
						}
						else
							job->getPostprocessingProperties()->setChapterFile(strTempFile);
					}
					else if (Path::GetExtension(job->getPostprocessingProperties()->getVideoInput())->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".mkv"))
					{
						MediaInfoFile *oInfo = new MediaInfoFile(job->getPostprocessingProperties()->getVideoInput(), _log);
						if (oInfo->hasMKVChapters())
						{
							job->getPostprocessingProperties()->setChapterFile(Path::Combine(job->getPostprocessingProperties()->getWorkingDirectory(), Path::GetFileNameWithoutExtension(job->getIndexFile()) + " - Chapter Information.txt"));
							if (oInfo->extractMKVChapters(job->getPostprocessingProperties()->getChapterFile()))
							{
								intermediateFiles.push_back(job->getPostprocessingProperties()->getChapterFile());
								job->getPostprocessingProperties()->setChapterExtracted(true);
							}
							else
								job->getPostprocessingProperties()->setChapterFile(strTempFile);
						}
					}
				}
				if (!File::Exists(job->getPostprocessingProperties()->getChapterFile()))
				{
					_log->LogEvent("File not found: " + job->getPostprocessingProperties()->getChapterFile(), Error);
					job->getPostprocessingProperties()->setChapterFile("");
				}
			}
			else if (job->getPostprocessingProperties()->getChapterExtracted())
			{
				intermediateFiles.push_back(job->getPostprocessingProperties()->getChapterFile());
			}

			QString avsFile = "";
			VideoStream *myVideo = new VideoStream();
			VideoCodecSettings *videoSettings = job->getPostprocessingProperties()->getVideoSettings();
			if (job->getPostprocessingProperties()->getVideoFileToMux().empty())
			{
				//Open the video
				Nullable<Dar> dar;
				avsFile = createAVSFile(job->getIndexFile(), job->Input, job->getPostprocessingProperties()->getDAR(), job->getPostprocessingProperties()->getHorizontalOutputResolution(), job->getPostprocessingProperties()->getSignalAR(), _log, job->getPostprocessingProperties()->getAvsSettings(), job->getPostprocessingProperties()->getAutoDeinterlace(), videoSettings, dar, job->getPostprocessingProperties()->getAutoCrop(), job->getPostprocessingProperties()->getKeepInputResolution(), job->getPostprocessingProperties()->getUseChaptersMarks());

				quint64 length;
				double framerate;
				JobUtil::getInputProperties(length, framerate, avsFile);
				myVideo->setInput(avsFile);
				myVideo->setOutput(Path::Combine(job->getPostprocessingProperties()->getWorkingDirectory(), Path::GetFileNameWithoutExtension(job->Input) + "_Video"));
				myVideo->setNumberOfFrames(length);
				myVideo->setFramerate(static_cast<decimal>(framerate));
				myVideo->setDAR(dar);
				myVideo->setVideoType(new MuxableType(((new VideoEncoderProvider())->GetSupportedOutput(videoSettings->getEncoderType()))[0], videoSettings->getCodec()));
				myVideo->setSettings(videoSettings);
			}
			else
			{
				myVideo->setOutput(job->getPostprocessingProperties()->getVideoFileToMux());
				myVideo->setSettings(videoSettings);

				MediaInfoFile *oInfo = new MediaInfoFile(myVideo->getOutput(), _log);
				videoSettings->setVideoName(oInfo->getVideoInfo()->getTrack()->getName());
				myVideo->setFramerate(static_cast<decimal>(oInfo->getVideoInfo()->FPS));
			}

			intermediateFiles.push_back(avsFile);
			intermediateFiles.push_back(job->getIndexFile());
			intermediateFiles.AddRange(audioFiles.Values);
			if (!qpfile.empty())
				intermediateFiles.push_back(qpfile);
			for (QVector<QString>::const_iterator file = arrAudioFilesDelete.begin(); file != arrAudioFilesDelete.end(); ++file)
				intermediateFiles.push_back(*file);
			if (File::Exists(Path::Combine(Path::GetDirectoryName(job->Input), Path::GetFileNameWithoutExtension(job->Input) + "._log")))
				intermediateFiles.push_back(Path::Combine(Path::GetDirectoryName(job->Input), Path::GetFileNameWithoutExtension(job->Input) + "._log"));
			for (QVector<QString>::const_iterator file = job->getPostprocessingProperties()->getFilesToDelete().begin(); file != job->getPostprocessingProperties()->getFilesToDelete().end(); ++file)
				intermediateFiles.push_back(*file);

			// subtitle handling
			if (!avsFile.empty() || !job->getPostprocessingProperties()->getVideoFileToMux().empty())
			{
				QVector<MuxStream*> subtitles = QVector<MuxStream*>();
				if (job->getPostprocessingProperties()->getSubtitleTracks().size() > 0)
				{
					for (QVector<OneClickStream*>::const_iterator oTrack = job->getPostprocessingProperties()->getSubtitleTracks().begin(); oTrack != job->getPostprocessingProperties()->getSubtitleTracks().end(); ++oTrack)
					{
						if ((*oTrack)->getTrackInfo()->ExtractMKVTrack)
						{
							//demuxed MKV
							QString trackFile = Path::GetDirectoryName(job->getIndexFile()) + "\\" + (*oTrack)->getTrackInfo()->DemuxFileName;
							if (File::Exists(trackFile))
							{
								intermediateFiles.push_back(trackFile);
								if (Path::GetExtension(trackFile)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".idx"))
									intermediateFiles.push_back(FileUtil::GetPathWithoutExtension(trackFile) + ".sub");

								subtitles.push_back(new MuxStream(trackFile, (*oTrack)->getLanguage(), (*oTrack)->getName(), (*oTrack)->getDelay(), (*oTrack)->getDefaultStream(), (*oTrack)->getForcedStream(), 0));
							}
							else
								_log->LogEvent("Ignoring subtitle as the it cannot be found: " + trackFile, Warning);
						}
						else
						{
							if (File::Exists((*oTrack)->getDemuxFilePath()))
								subtitles.push_back(new MuxStream((*oTrack)->getDemuxFilePath(), (*oTrack)->getLanguage(), (*oTrack)->getName(), (*oTrack)->getDelay(), (*oTrack)->getDefaultStream(), (*oTrack)->getForcedStream(), 0));
							else
								_log->LogEvent("Ignoring subtitle as the it cannot be found: " + (*oTrack)->getDemuxFilePath(), Warning);
						}
					}
				}

				JobChain *c = vUtil->GenerateJobSeries(myVideo, job->getPostprocessingProperties()->getFinalOutput(), arrAudioJobs.ToArray(), subtitles.ToArray(), job->getPostprocessingProperties()->getChapterFile(), job->getPostprocessingProperties()->getOutputSize(), job->getPostprocessingProperties()->getSplitting(), job->getPostprocessingProperties()->getContainer(), job->getPostprocessingProperties()->getPrerenderJob(), arrMuxStreams.ToArray(), _log, job->getPostprocessingProperties()->getDeviceOutputType(), 0, job->getPostprocessingProperties()->getVideoFileToMux(), job->getPostprocessingProperties()->getAudioTracks().ToArray(), true);
				if (c == 0)
				{
					_log->Warn("Job creation aborted");
					return;
				}

				c = CleanupJob::AddAfter(c, intermediateFiles, job->getPostprocessingProperties()->getFinalOutput());
				mainForm->getJobs()->addJobsWithDependencies(c, false);

				// batch processing other input files if necessary
				if (job->getPostprocessingProperties()->getFilesToProcess().size() > 0)
				{
					OneClickWindow *ocw = new OneClickWindow(mainForm);
					ocw->setBatchProcessing(job->getPostprocessingProperties()->getFilesToProcess(), job->getPostprocessingProperties()->getOneClickSetting());
				}
			}
		}
		catch (std::exception &e)
		{
			_processTime->Abort();
			if (dynamic_cast<ThreadAbortException*>(e) != 0)
			{
				_log->LogEvent("Aborting...");
				su->setWasAborted(true);
				su->setIsComplete(true);
				raiseEvent();
			}
			else
			{
				_log->LogValue("An error occurred", e, Error);
				su->setHasError(true);
				su->setIsComplete(true);
				raiseEvent();
			}
			return;
		}
		_processTime->Abort();
		su->setIsComplete(true);
		raiseEvent();
	}

	void OneClickPostProcessing::fillInAudioInformation(QVector<AudioJob*> &arrAudioJobs, QVector<MuxStream*> &arrMuxStreams)
	{
		for (QVector<MuxStream*>::const_iterator m = arrMuxStreams.begin(); m != arrMuxStreams.end(); ++m)
			(*m)->path = convertTrackNumberToFile((*m)->path, (*m)->delay);

		QVector<AudioJob*> tempList = QVector<AudioJob*>();
		for (QVector<AudioJob*>::const_iterator a = arrAudioJobs.begin(); a != arrAudioJobs.end(); ++a)
		{
			(*a)->Input = convertTrackNumberToFile((*a)->Input, (*a)->Delay);
			if ((*a)->Output->empty() && !(*a)->Input->empty())
				(*a)->Output = FileUtil::AddToFileName((*a)->Input, "_audio");
			if (!(*a)->Input->empty())
				tempList.push_back(*a);
		}
		arrAudioJobs = tempList;
	}

	QString OneClickPostProcessing::convertTrackNumberToFile(const QString &input, int &delay)
	{
		if (input.empty())
		{
			_log->Warn("Couldn't find audio file. Skipping track.");
			return 0;
		}

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (input.StartsWith("::") && input.EndsWith("::") && input.length() > 4)
		{
			QString sub = input.substr(2, input.length() - 4);
			try
			{
				int t = int::Parse(sub);
				QString s = audioFiles[t];
				if (PrettyFormatting::getDelay(s).HasValue)
					Nullable<int> tempVar = PrettyFormatting.getDelay(s);
					delay = tempVar::HasValue ? tempVar : 0;
				return s;
			}
			catch (std::exception &e1)
			{
				_log->Warn(QString::Format("Couldn't find audio file for track {0}. Skipping track.", input));
				return 0;
			}
		}

		return input;
	}

	QString OneClickPostProcessing::createAVSFile(const QString &indexFile, const QString &inputFile, Nullable<Dar> AR, int desiredOutputWidth, bool signalAR, LogItem *_log, AviSynthSettings *avsSettings, bool autoDeint, VideoCodecSettings *settings, Nullable<Dar> &dar, bool autoCrop, bool keepInputResolution, bool useChaptersMarks)
	{
		dar = Nullable<Dar>();
		Dar customDAR;
		IMediaFile *iMediaFile = 0;
		IVideoReader *reader;
		PossibleSources oPossibleSource;
		x264Device *xTargetDevice = 0;
		CropValues *cropValues = new CropValues();

		int outputWidthIncludingPadding = 0;
		int outputHeightIncludingPadding = 0;
		int outputWidthCropped = 0;
		int outputHeightCropped = 0;

		// open index file to retrieve information
		if (job->getPostprocessingProperties()->getIndexType() == FileIndexerWindow::DGI)
		{
			iMediaFile = new dgiFile(indexFile);
			oPossibleSource = dgi;
		}
		else if (job->getPostprocessingProperties()->getIndexType() == FileIndexerWindow::D2V)
		{
			iMediaFile = new d2vFile(indexFile);
			oPossibleSource = d2v;
		}
		else if (job->getPostprocessingProperties()->getIndexType() == FileIndexerWindow::DGA)
		{
			iMediaFile = new dgaFile(indexFile);
			oPossibleSource = dga;
		}
		else if (job->getPostprocessingProperties()->getIndexType() == FileIndexerWindow::FFMS)
		{
			iMediaFile = new ffmsFile(inputFile, indexFile);
			oPossibleSource = ffindex;
		}
		else if (job->getPostprocessingProperties()->getIndexType() == FileIndexerWindow::AVISOURCE)
		{
			QString tempAvs = "AVISource(\"" + inputFile + "\", audio=false)" + VideoUtil::getAssumeFPS(0, inputFile);
			iMediaFile = AvsFile::ParseScript(tempAvs);
			oPossibleSource = directShow;
		}
		else
		{
			iMediaFile = AvsFile::OpenScriptFile(inputFile);
			oPossibleSource = avs;
		}
		reader = iMediaFile->GetVideoReader();

		// abort if the index file is invalid
		if (reader->getFrameCount() < 1)
		{
			_log->Error("There are " + reader->getFrameCount() + " frames in the index file. Aborting...");
			return "";
		}

		if (!AR.HasValue)
		{
			// AR needs to be detected automatically now
			_log->LogValue("Auto-detect aspect ratio", !AR.HasValue);
			customDAR = iMediaFile->getVideoInfo()->DAR;
			if (customDAR.getAR() <= 0)
			{
				customDAR = Dar::ITU16x9PAL;
				_log->Warn(QString::Format("No aspect ratio found, defaulting to {0}.", customDAR));
			}
		}
		else
			customDAR = AR.Value;
		_log->LogValue("Aspect ratio", customDAR);

		// check x264 settings (target device, chapter file)
		if (settings != 0 && dynamic_cast<x264Settings*>(settings) != 0)
		{
			x264Settings *xs = static_cast<x264Settings*>(settings);
			xTargetDevice = xs->getTargetDevice();
			_log->LogValue("Target device", xTargetDevice->getName());

			// create qpf file if necessary
			if (!job->getPostprocessingProperties()->getChapterFile().empty() && useChaptersMarks)
			{
				qpfile = job->getPostprocessingProperties()->getChapterFile();
				if ((Path::GetExtension(qpfile)->ToLower(System::Globalization::CultureInfo::InvariantCulture)) == ".txt")
					qpfile = VideoUtil::convertChaptersTextFileTox264QPFile(job->getPostprocessingProperties()->getChapterFile(), iMediaFile->getVideoInfo()->FPS);
				if (File::Exists(qpfile))
				{
					xs->setUseQPFile(true);
					xs->setQPFile(qpfile);
				}
			}
		}

		// get mod value for resizing
		int mod = Resolution::GetModValue(avsSettings->getModValue(), avsSettings->getMod16Method(), signalAR);

		// crop input as it may be required (autoCrop && !keepInputResolution or Blu-Ray)
		if (Autocrop::autocrop(cropValues, reader, signalAR, avsSettings->getMod16Method(), avsSettings->getModValue()) == false)
		{
			_log->Error("Autocrop failed. Aborting...");
			return "";
		}

		Nullable<Dar> suggestedDar = Nullable<Dar>();
		outputWidthIncludingPadding = desiredOutputWidth;
		CropValues *paddingValues;

		bool resizeEnabled = !keepInputResolution;
		Resolution::GetResolution(static_cast<int>(iMediaFile->getVideoInfo()->Width), static_cast<int>(iMediaFile->getVideoInfo()->Height), customDAR, cropValues, autoCrop && !keepInputResolution, mod, resizeEnabled, avsSettings->getUpsize(), signalAR, true, avsSettings->getAcceptableAspectError(), xTargetDevice, static_cast<double>(iMediaFile->getVideoInfo()->FPS_N) / iMediaFile->getVideoInfo()->FPS_D, outputWidthIncludingPadding, outputHeightIncludingPadding, paddingValues, suggestedDar, _log);
		keepInputResolution = !resizeEnabled;
		if ((keepInputResolution || signalAR) && suggestedDar.HasValue)
			dar = suggestedDar;

		// log calculated output resolution
		outputWidthCropped = outputWidthIncludingPadding - paddingValues->left - paddingValues->right;
		outputHeightCropped = outputHeightIncludingPadding - paddingValues->bottom - paddingValues->top;
		_log->LogValue("Input resolution", iMediaFile->getVideoInfo()->Width + "x" + iMediaFile->getVideoInfo()->Height);
		if (cropValues->isCropped())
		{
			_log->LogValue("Autocrop values", cropValues);
			_log->LogValue("Cropped output resolution", outputWidthCropped + "x" + outputHeightCropped);
		}
		else
			_log->LogValue("Output resolution", outputWidthCropped + "x" + outputHeightCropped);
		if (paddingValues->isCropped())
			_log->LogValue("Padded output resolution", outputWidthIncludingPadding + "x" + outputHeightIncludingPadding);

		//Generate the avs script based on the template
		QString inputLine = "#input";
		QString deinterlaceLines = "#deinterlace";
		QString denoiseLines = "#denoise";
		QString cropLine = "#crop";
		QString resizeLine = "#resize";

		inputLine = ScriptServer::GetInputLine(inputFile, indexFile, false, oPossibleSource, false, false, false, 0, avsSettings->getDSS2());
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (!inputLine.EndsWith(")"))
			inputLine += ")";

		_log->LogValue("Automatic deinterlacing", autoDeint);
		if (autoDeint)
		{
			raiseEvent("Automatic deinterlacing...   ***PLEASE WAIT***");
			QString d2vPath = indexFile;
			_sourceDetector = new SourceDetector(inputLine, d2vPath, false, mainForm->getSettings()->getSourceDetectorSettings(), new UpdateSourceDetectionStatus(this, &OneClickPostProcessing::analyseUpdate), new FinishedAnalysis(this, &OneClickPostProcessing::finishedAnalysis));
			finished = false;
			_sourceDetector->analyse();
			waitTillAnalyseFinished();
			_sourceDetector->stop();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete _sourceDetector;
			deinterlaceLines = filters[0]->getScript();
			if (interlaced)
				_log->LogValue("Deinterlacing used", deinterlaceLines, Warning);
			else
				_log->LogValue("Deinterlacing used", deinterlaceLines);
		}

		raiseEvent("Finalizing preprocessing...   ***PLEASE WAIT***");
		inputLine = ScriptServer::GetInputLine(inputFile, indexFile, interlaced, oPossibleSource, avsSettings->getColourCorrect(), avsSettings->getMPEG2Deblock(), false, 0, avsSettings->getDSS2());
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (!inputLine.EndsWith(")"))
			inputLine += ")";

		if (!keepInputResolution && autoCrop)
			cropLine = ScriptServer::GetCropLine(true, cropValues);

		denoiseLines = ScriptServer::GetDenoiseLines(avsSettings->getDenoise(), static_cast<DenoiseFilterType>(avsSettings->getDenoiseMethod()));

		if (!keepInputResolution)
		{
			resizeLine = ScriptServer::GetResizeLine(!signalAR || avsSettings->getMod16Method() == resize || outputWidthIncludingPadding > 0 || static_cast<int>(iMediaFile->getVideoInfo()->Width) != outputWidthCropped, outputWidthCropped, outputHeightCropped, outputWidthIncludingPadding, outputHeightIncludingPadding, static_cast<ResizeFilterType>(avsSettings->getResizeMethod()), autoCrop, cropValues, static_cast<int>(iMediaFile->getVideoInfo()->Width), static_cast<int>(iMediaFile->getVideoInfo()->Height));
		}

		QString newScript = ScriptServer::CreateScriptFromTemplate(avsSettings->getTemplate(), inputLine, cropLine, resizeLine, denoiseLines, deinterlaceLines);

		if (dar.HasValue)
			newScript = QString::Format("global MeXgui_darx = {0}\r\nglobal MeXgui_dary = {1}\r\n{2}", dar.Value::X, dar.Value::Y, newScript);
		else
		{
			if (xTargetDevice != 0 && xTargetDevice->getBluRay())
			{
				QString strResolution = outputWidthIncludingPadding + "x" + outputHeightIncludingPadding;
				x264Settings *_xs = static_cast<x264Settings*>(settings);

				if (strResolution.Equals("720x480"))
				{
					_xs->setSampleAR(4);
					_log->LogEvent("Set --sar to 10:11 as only 40:33 or 10:11 are supported with a resolution of " + strResolution + " as required for " + xTargetDevice->getName() + ".");
				}
				else if (strResolution.Equals("720x576"))
				{
					_xs->setSampleAR(5);
					_log->LogEvent("Set --sar to 12:11 as only 16:11 or 12:11 are supported with a resolution of " + strResolution + " as required for " + xTargetDevice->getName() + ".");
				}
				else if (strResolution.Equals("1280x720") || strResolution.Equals("1920x1080"))
				{
					_xs->setSampleAR(1);
					_log->LogEvent("Set --sar to 1:1 as only 1:1 is supported with a resolution of " + strResolution + " as required for " + xTargetDevice->getName() + ".");
				}
				else if (strResolution.Equals("1440x1080"))
				{
					_xs->setSampleAR(2);
					_log->LogEvent("Set --sar to 4:3 as only 4:3 is supported with a resolution of " + strResolution + " as required for " + xTargetDevice->getName() + ".");
				}
			}
		}

		_log->LogValue("Generated Avisynth script", newScript);
		QString strOutputAVSFile;
		if (indexFile.empty())
			strOutputAVSFile = Path::ChangeExtension(Path::Combine(job->getPostprocessingProperties()->getWorkingDirectory(), Path::GetFileName(inputFile)), ".avs");
		else
			strOutputAVSFile = Path::ChangeExtension(indexFile, ".avs");

		try
		{
			StreamWriter *sw = new StreamWriter(strOutputAVSFile, false, System::Text::Encoding::Default);
			sw->Write(newScript);
			sw->Close();
		}
		catch (IOException *i)
		{
			_log->LogValue("Error saving AviSynth script", i, Error);
			return "";
		}
		return strOutputAVSFile;
	}

	void OneClickPostProcessing::finishedAnalysis(SourceInfo *info, bool error, const QString &errorMessage)
	{
		if (error || info == 0)
		{
			LogItem *oSourceLog = _log->LogEvent("Source detection");
			oSourceLog->LogEvent("Source detection failed: " + errorMessage, Warning);
			filters = new DeinterlaceFilter[] {new DeinterlaceFilter("Error", "#An error occurred in source detection. Doing no processing")};
			interlaced = false;
		}
		else
		{
			LogItem *oSourceLog = _log->LogValue("Source detection", info->analysisResult);
			if (info->sourceType == NOT_ENOUGH_SECTIONS)
			{
				oSourceLog->LogEvent("Source detection failed: Could not find enough useful sections to determine source type for " + job->Input, Error);
				filters = new DeinterlaceFilter[] {new DeinterlaceFilter("Error", "#Not enough useful sections for source detection. Doing no processing")};
			}
			else
				this->filters = ScriptServer::GetDeinterlacers(info).ToArray();
			interlaced = (info->sourceType != PROGRESSIVE);
		}
		finished = true;
	}

	void OneClickPostProcessing::analyseUpdate(int amountDone, int total)
	{
		try
		{
			setProgress(static_cast<decimal>(amountDone) / static_cast<decimal>(total));
		}
		catch (std::exception &e1) // If we get any errors, just ignore -- it's only a cosmetic thing.
		{
		}
	}

	void OneClickPostProcessing::waitTillAnalyseFinished()
	{
		while (!finished)
		{
			delay(500);
		}
	}

	void OneClickPostProcessing::setup(Job *job, StatusUpdate *su, LogItem *_log)
	{
		this->_log = _log;
		this->job = static_cast<OneClickPostProcessingJob*>(job);
		this->su = su;
	}

	void OneClickPostProcessing::resume()
	{

	}

	void OneClickPostProcessing::pause()
	{

	}

	void OneClickPostProcessing::start()
	{
		try
		{
			this->Start();
		}
		catch (std::exception &e)
		{
			throw new JobRunException(e);
		}
	}

	void OneClickPostProcessing::stop()
	{
		try
		{
			this->Abort();
		}
		catch (std::exception &e)
		{
			throw new JobRunException(e);
		}
	}

	void OneClickPostProcessing::changePriority(ProcessPriority priority)
	{
		if (this->_processThread != 0 && _processThread->IsAlive)
		{
			try
			{
				switch (priority)
				{
					case IDLE:
						_processThread->Priority = ThreadPriority::Lowest;
						break;
					case BELOW_NORMAL:
						_processThread->Priority = ThreadPriority::BelowNormal;
						break;
					case NORMAL:
						_processThread->Priority = ThreadPriority::Normal;
						break;
					case ABOVE_NORMAL:
						_processThread->Priority = ThreadPriority::AboveNormal;
						break;
					case HIGH:
						_processThread->Priority = ThreadPriority::Highest;
						break;
				}
				return;
			}
			catch (std::exception &e) // process could not be running anymore
			{
				throw new JobRunException(e);
			}
		}
		else
		{
			if (_processThread == 0)
				throw new JobRunException("Thread has not been started yet");
			else
				throw new JobRunException("Thread has exited");
		}
	}

	void OneClickPostProcessing::InitializeInstanceFields()
	{
		delete _processThread;
		delete _processTime;
		delete _sourceDetector;
		al = new AVCLevels();
		finished = false;
		interlaced = false;
		qpfile = "";
	}
}
