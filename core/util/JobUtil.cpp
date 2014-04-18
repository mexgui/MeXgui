#include "JobUtil.h"






//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;

//using namespace System::Threading;



//using namespace System::Xml::Serialization;
using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

	JobUtil::JobUtil(MainForm *mainForm)
	{
		InitializeInstanceFields();
		this->mainForm = mainForm;
	}

	VideoJob *JobUtil::generateVideoJob(const QString &input, const QString &output, VideoCodecSettings *settings, Nullable<Dar> dar, Zone zones[])
	{
		return generateVideoJob(input, output, settings, false, dar, zones);
	}

	VideoJob *JobUtil::generateVideoJob(const QString &input, const QString &output, VideoCodecSettings *settings, bool skipVideoCheck, Nullable<Dar> dar, Zone zones[])
	{
		VideoJob *job = new VideoJob(input, output, settings, dar, zones);

		if (Path::GetDirectoryName(settings->getLogfile())->Equals("")) // no path set
			settings->setLogfile(Path::ChangeExtension(output, ".stats"));
		if (job->getSettings()->getSettingsID().Equals("x264"))
			mbtreeFile = Path::ChangeExtension(output, ".stats.mbtree");
		if (job->getSettings()->getEncodingMode() == 4) // automated 2 pass, change type to 2 pass 2nd pass
		{
			job->getSettings()->setEncodingMode(3);
		}
		else if (job->getSettings()->getEncodingMode() == 8) // automated 3 pass, change type to 3 pass first pass
		{
			if (mainForm->getSettings()->getOverwriteStats())
				job->getSettings()->setEncodingMode(7);
			else
				job->getSettings()->setEncodingMode(3); // 2 pass 2nd pass.. doesn't overwrite the stats file
		}

		if (!skipVideoCheck)
			checkVideo(job->Input);

		return job;
	}

	void JobUtil::checkVideo(const QString &p)
	{
		quint64 a;
		double b;
		getInputProperties(a, b, p);
	}

	void JobUtil::adjustNbThreads(VideoCodecSettings *settings)
	{
		QString nbProc = System::Environment::GetEnvironmentVariable("NUMBER_OF_PROCESSORS");
		if (!nbProc.empty())
		{
			try
			{
				int nbCPUs = int::Parse(nbProc);
				settings->setAdjustedNbThreads(nbCPUs);
			}
			catch (std::exception &e1)
			{
			}
		}
	}

	MeXgui::core::details::JobChain *JobUtil::GenerateMuxJobs(VideoStream *video, Nullable<decimal> framerate, MuxStream audioStreamsArray[], MuxableType audioTypes[], MuxStream subtitleStreamsArray[], MuxableType subTypes[], const QString &chapterFile, MuxableType *chapterInputType, ContainerType *container, const QString &output, Nullable<FileSize> splitSize, QVector<QString> &inputsToDelete, const QString &deviceType, MuxableType *deviceOutputType, bool alwaysMuxOutput)
	{
		assert(!splitSize.HasValue || splitSize.Value != FileSize::Empty);

		MuxProvider *prov = mainForm->getMuxProvider();
		QVector<MuxableType*> allTypes = QVector<MuxableType*>();
		QVector<MuxableType*> tempTypes = QVector<MuxableType*>();
		QVector<MuxableType*> duplicateTypes = QVector<MuxableType*>();
		tempTypes.AddRange(audioTypes);
		tempTypes.AddRange(subTypes);
		allTypes.push_back(video->getVideoType());

		// remove duplicate entries to speed up the process
		for (QVector<MuxableType*>::const_iterator oType = tempTypes.begin(); oType != tempTypes.end(); ++oType)
		{
			bool bFound = false;
			for (QVector<MuxableType*>::const_iterator oAllType = allTypes.begin(); oAllType != allTypes.end(); ++oAllType)
			{
				if ((*oType)->outputType->ID->Equals((*oAllType)->outputType->ID))
				{
					bFound = true;
					break;
				}
			}
			if (!bFound)
				allTypes.push_back(*oType);
			else
				duplicateTypes.push_back(*oType);
		}
		if (chapterInputType != 0)
			allTypes.push_back(chapterInputType);
		if (deviceOutputType != 0)
			allTypes.push_back(deviceOutputType);

		// get mux path
		MuxPath *muxPath = prov->GetMuxPath(container, alwaysMuxOutput || splitSize.HasValue, allTypes.ToArray());

		// add duplicate entries back into the mux path
		muxPath->getInitialInputTypes().AddRange(duplicateTypes);
		while (duplicateTypes.size() > 0)
		{
			int iPath = 0;
			for (int i = 0; i < muxPath->getLength(); i++)
				for (QVector<MuxableType*>::const_iterator oType = muxPath[i].handledInputTypes.begin(); oType != muxPath[i].handledInputTypes.end(); ++oType)
					if ((*oType)->outputType->ID->Equals(duplicateTypes[0]->outputType->getID()))
						iPath = i;
			muxPath[iPath].handledInputTypes.push_back(duplicateTypes[0]);
			duplicateTypes.RemoveAt(0);
		}

		QVector<MuxJob*> jobs = QVector<MuxJob*>();
		QVector<MuxStream*> subtitleStreams = QVector<MuxStream*>(subtitleStreamsArray);
		QVector<MuxStream*> audioStreams = QVector<MuxStream*>(audioStreamsArray);
		int index = 0;
		int tempNumber = 1;
		QString previousOutput = "";
		for (MeXgui::MuxPath::const_iterator mpl = muxPath->begin(); mpl != muxPath->end(); ++mpl)
		{
			QVector<QString> filesToDeleteThisJob = QVector<QString>();

			MuxJob *mjob = new MuxJob();

			if (previousOutput != "")
			{
				mjob->getSettings()->setMuxedInput(previousOutput);
				filesToDeleteThisJob.push_back(previousOutput);
			}

			if (video->getSettings() != 0)
			{
				mjob->setNbOfBFrames(video->getSettings()->getNbBframes());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				mjob->setCodec(video->getSettings()->getCodec()->ToString());
				mjob->getSettings()->setVideoName(video->getSettings()->getVideoName());
			}
			mjob->setNbOfFrames(video->getNumberOfFrames());
			QString fpsFormated = QString::Format("{0:##.###}", framerate); // this formating is required for mkvmerge at least to avoid fps rounding error
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to this .NET Convert class method:
			mjob->getSettings()->setFramerate(Convert::ToDecimal(fpsFormated));

			QString tempOutputName = Path::Combine(Path::GetDirectoryName(output), Path::GetFileNameWithoutExtension(output) + tempNumber + ".");
			tempNumber++;
			for (QVector<MuxableType*>::const_iterator o = mpl.handledInputTypes.begin(); o != mpl.handledInputTypes.end(); ++o)
			{
				if (dynamic_cast<VideoType*>((*o)->outputType) != 0)
				{
					mjob->getSettings()->setVideoInput(video->getOutput());
					if (std::find(inputsToDelete.begin(), inputsToDelete.end(), video->getOutput()) != inputsToDelete.end())
						filesToDeleteThisJob.push_back(video->getOutput());
					mjob->getSettings()->setDAR(video->getDAR());
				}
				else if (dynamic_cast<AudioType*>((*o)->outputType) != 0)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					MuxStream *stream = audioStreams.Find(delegate(MuxStream m)
					{
						return (VideoUtil::guessAudioType(m::path) == (*o)->outputType);
					}
				   );

					if (stream != 0)
					{
						mjob->getSettings()->getAudioStreams().push_back(stream);
						audioStreams.Remove(stream);

						if (std::find(inputsToDelete.begin(), inputsToDelete.end(), stream->path) != inputsToDelete.end())
							filesToDeleteThisJob.push_back(stream->path);
					}
				}
				else if (dynamic_cast<SubtitleType*>((*o)->outputType) != 0)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					MuxStream *stream = subtitleStreams.Find(delegate(MuxStream m)
					{
						return (VideoUtil::guessSubtitleType(m::path) == (*o)->outputType);
					}
				   );

					if (stream != 0)
					{
						mjob->getSettings()->getSubtitleStreams().push_back(stream);
						subtitleStreams.Remove(stream);

						if (std::find(inputsToDelete.begin(), inputsToDelete.end(), stream->path) != inputsToDelete.end())
							filesToDeleteThisJob.push_back(stream->path);
					}
				}
				else if (dynamic_cast<ChapterType*>((*o)->outputType) != 0)
				{
					if ((VideoUtil::guessChapterType(chapterFile) == (*o)->outputType))
						mjob->getSettings()->setChapterFile(chapterFile);
					if (std::find(inputsToDelete.begin(), inputsToDelete.end(), chapterFile) != inputsToDelete.end())
						filesToDeleteThisJob.push_back(chapterFile);
				}
				else if (dynamic_cast<DeviceType*>((*o)->outputType) != 0)
				{
					if ((VideoUtil::guessDeviceType(deviceType) == (*o)->outputType))
						mjob->getSettings()->setDeviceType(deviceType);
				}
			}
			for (QVector<MuxStream*>::const_iterator s = mjob->getSettings()->getAudioStreams().begin(); s != mjob->getSettings()->getAudioStreams().end(); ++s)
			{
				audioStreams.Remove(*s);
			}
			for (QVector<MuxStream*>::const_iterator s = mjob->getSettings()->getSubtitleStreams().begin(); s != mjob->getSettings()->getSubtitleStreams().end(); ++s)
			{
				subtitleStreams.Remove(*s);
			}
			mjob->FilesToDelete.AddRange(filesToDeleteThisJob);
			if (index == muxPath->getLength() - 1)
			{
				mjob->getSettings()->setMuxedOutput(output);
				mjob->getSettings()->setSplitSize(splitSize);
				mjob->getSettings()->setDAR(video->getDAR());
				mjob->setContainerType(container);
			}
			else
			{
				ContainerType *cot = (*mpl).muxerInterface->GetContainersInCommon(muxPath[index + 1].muxerInterface)[0];
				mjob->getSettings()->setMuxedOutput(tempOutputName + cot->getExtension());
				mjob->setContainerType(cot);
			}
			previousOutput = mjob->getSettings()->getMuxedOutput();
			index++;
			jobs.push_back(mjob);
			if (mjob->getSettings()->getVideoInput().empty())
				mjob->Input = mjob->getSettings()->getMuxedInput();
			else
				mjob->Input = mjob->getSettings()->getVideoInput();
			mjob->Output = mjob->getSettings()->getMuxedOutput();
			mjob->setMuxType((*mpl).muxerInterface->MuxerType);
		}

		return new SequentialChain(jobs.ToArray());
	}

	MeXgui::core::details::JobChain *JobUtil::AddVideoJobs(const QString &movieInput, const QString &movieOutput, VideoCodecSettings *settings, int introEndFrame, int creditsStartFrame, Nullable<Dar> dar, bool prerender, bool checkVideo, Zone zones[])
	{
		JobChain *jobs = 0;
		bool cont = getFinalZoneConfiguration(settings, introEndFrame, creditsStartFrame, zones);
		if (!cont) // abort
			return jobs;
		return prepareVideoJob(movieInput, movieOutput, settings, dar, prerender, checkVideo, zones);
	}

	MeXgui::core::details::JobChain *JobUtil::prepareVideoJob(const QString &movieInput, const QString &movieOutput, VideoCodecSettings *settings, Nullable<Dar> dar, bool prerender, bool checkVideo, Zone zones[])
	{
		//Check to see if output file already exists before creating the job.
		if (File::Exists(movieOutput) && !mainForm->getDialogManager()->overwriteJobOutput(movieOutput))
			return 0;

		bool twoPasses = false, threePasses = false;
		if (settings->getEncodingMode() == 4) // automated twopass
			twoPasses = true;
		else if (settings->getEncodingMode() == 8) // automated threepass
			threePasses = true;

		VideoJob *prerenderJob = 0;
		FFMSIndexJob *indexJob = 0;
		QString hfyuFile = "";
		QString inputAVS = movieInput;
		if (prerender)
		{
			hfyuFile = Path::Combine(Path::GetDirectoryName(movieInput), "hfyu_" + Path::GetFileNameWithoutExtension(movieInput) + ".avi");
			inputAVS = Path::ChangeExtension(hfyuFile, ".avs");
			if (File::Exists(hfyuFile))
			{
				if (MessageBox::Show("The intended temporary file, " + hfyuFile + " already exists.\r\n" + "Do you wish to over-write it?", "File already exists", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation) == DialogResult::No)
					return 0;
			}
			if (File::Exists(inputAVS))
			{
				if (MessageBox::Show("The intended temporary file, " + inputAVS + " already exists.\r\n" + "Do you wish to over-write it?", "File already exists", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation) == DialogResult::No)
					return 0;
			}
			try
			{
				StreamWriter *hfyuWrapper = new StreamWriter(inputAVS, false, Encoding::Default);
				hfyuWrapper->WriteLine(VideoUtil::getFFMSInputLine(hfyuFile, 0, 0));
				hfyuWrapper->Close();
			}
			catch (std::exception &e1)
			{
				return 0;
			}
			indexJob = new FFMSIndexJob(hfyuFile, 0, 0, 0, false);
			prerenderJob = this->generateVideoJob(movieInput, hfyuFile, new hfyuSettings(), dar, zones);
			if (prerenderJob == 0)
				return 0;
		}
		if (checkVideo)
		{
			VideoUtil *vUtil = new VideoUtil(mainForm);
			QString error = vUtil->checkVideo(movieInput);
			if (error != "")
			{
				bool bContinue = mainForm->getDialogManager()->createJobs(error);
				if (!bContinue)
				{
					MessageBox::Show("Job creation aborted due to invalid AviSynth script");
					return 0;
				}
			}
		}
		VideoJob *job = this->generateVideoJob(inputAVS, movieOutput, settings, prerender, dar, zones);
		VideoJob *firstpass = 0;
		VideoJob *middlepass = 0;
		if (job != 0)
		{
			if (twoPasses || threePasses) // we just created the last pass, now create previous one(s)
			{
				job->FilesToDelete.push_back(job->getSettings()->getLogfile());
				if (job->getSettings()->getSettingsID().Equals("x264"))
					job->FilesToDelete.push_back(mbtreeFile);
				firstpass = cloneJob(job);
				firstpass->Output = ""; // the first pass has no output
				firstpass->getSettings()->setEncodingMode(2);
				firstpass->setDAR(dar);
				if (threePasses)
				{
					firstpass->getSettings()->setEncodingMode(5); // change to 3 pass 3rd pass just for show
					middlepass = cloneJob(job);
					middlepass->getSettings()->setEncodingMode(6); // 3 pass 2nd pass
					if (mainForm->getSettings()->getKeep2of3passOutput()) // give the 2nd pass a new name
					{
						middlepass->Output = Path::Combine(Path::GetDirectoryName(job->Output), Path::GetFileNameWithoutExtension(job->Output) + "-2ndpass" + Path::GetExtension(job->Output));
						job->FilesToDelete.push_back(middlepass->Output);
					}
					middlepass->setDAR(dar);
				}
			}
			if (prerender)
			{
				job->FilesToDelete.push_back(hfyuFile);
				job->FilesToDelete.push_back(inputAVS);
				job->FilesToDelete.push_back(hfyuFile + ".ffindex");
			}
			QVector<Job*> jobList = QVector<Job*>();
			if (prerenderJob != 0)
			{
				jobList.push_back(prerenderJob);
				jobList.push_back(indexJob);
			}
			if (firstpass != 0)
				jobList.push_back(firstpass);
			if (middlepass != 0) // we have a middle pass
				jobList.push_back(middlepass);
			jobList.push_back(job);

			return new SequentialChain(jobList.ToArray());
		}
		return 0;
	}

	VideoJob *JobUtil::cloneJob(VideoJob *oldJob)
	{
		VideoJob *job = new VideoJob();
		job->Input = oldJob->Input;
		job->Output = oldJob->Output;
		job->setSettings(oldJob->getSettings()->Clone());
		job->setZones(oldJob->getZones());
		return job;
	}

	void JobUtil::updateVideoBitrate(VideoJob *job, int bitrate)
	{
		job->getSettings()->setBitrateQuantizer(bitrate);
	}

	bool JobUtil::getInputProperties(quint64 &nbOfFrames, double &framerate, const QString &video)
	{
		int d1, d2, d3, d4;
		Dar d;
		return GetAllInputProperties(nbOfFrames, framerate, d1, d2, d3, d4, d, video);
	}

	bool JobUtil::GetAllInputProperties(quint64 &nbOfFrames, double &framerate, int &framerate_n, int &framerate_d, int &hRes, int &vRes, Dar &dar, const QString &video)
	{
		nbOfFrames = 0;
		hRes = vRes = 0;
		framerate = 0.0;
		try
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AvsFile avi = AvsFile.OpenScriptFile(video))
			AvsFile *avi = AvsFile::OpenScriptFile(video);
			try
			{
//				checked
					nbOfFrames = static_cast<quint64>(avi->getVideoInfo()->FrameCount);
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'checked' block
				framerate = avi->getVideoInfo()->FPS;
				framerate_n = avi->getVideoInfo()->FPS_N;
				framerate_d = avi->getVideoInfo()->FPS_D;
				hRes = static_cast<int>(avi->getVideoInfo()->Width);
				vRes = static_cast<int>(avi->getVideoInfo()->Height);
				dar = avi->getVideoInfo()->DAR;
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (avi != 0)
					avi.Dispose();
			}
			return true;
		}
		catch (std::exception &e)
		{
			throw new JobRunException("The file " + video + " cannot be opened.\r\n" + "Error message for your reference: " + e.what(), e);
		}
	}

	bool JobUtil::GetAllInputProperties(quint64 &nbOfFrames, double &framerate, int &hRes, int &vRes, Dar &dar, const QString &video)
	{
		int fn, fd;
		return GetAllInputProperties(nbOfFrames, framerate, fn, fd, hRes, vRes, dar, video);
	}

	quint64 JobUtil::getNumberOfFrames(const QString &path)
	{
		quint64 retval = 0;
		double framerate = 0.0;
		bool succ = getInputProperties(retval, framerate, path);
		return retval;
	}

	double JobUtil::getFramerate(const QString &path)
	{
		quint64 retval = 0;
		double framerate = 0.0;
		bool succ = getInputProperties(retval, framerate, path);
		return framerate;
	}

	Zone *JobUtil::createHelperZones(Zone zones[], int nbOfFrames)
	{
		ArrayList *newZones = new ArrayList();
		Zone *z = zones[0];
		Zone *newZone = new Zone();
		newZone->mode = Weight;
		newZone->modifier = static_cast<decimal>(100);
		if (z->startFrame > 0) // zone doesn't start at the beginning, add zone before the first configured zone
		{
			newZone->startFrame = 0;
			newZone->endFrame = z->startFrame - 1;
			newZones->Add(newZone);
		}
		if (sizeof(zones) / sizeof(zones[0]) == 1) // special case
		{
			newZones->Add(z);
			if (z->endFrame < nbOfFrames - 1) // we hav to add an end zone
			{
				newZone->startFrame = z->endFrame + 1;
				newZone->endFrame = nbOfFrames - 1;
				newZones->Add(newZone);
			}
		}
		else if (sizeof(zones) / sizeof(zones[0]) == 2)
		{
			newZones->Add(z);
			Zone *second = zones[1];
			if (z->endFrame + 1 < second->startFrame) // new zone needs to go in between
			{
				newZone->startFrame = z->endFrame + 1;
				newZone->endFrame = second->startFrame - 1;
				newZones->Add(newZone);
			}
			newZones->Add(second);
			if (second->endFrame < nbOfFrames - 1) // add end zone
			{
				newZone->startFrame = second->endFrame + 1;
				newZone->endFrame = nbOfFrames - 1;
				newZones->Add(newZone);
			}
		}
		else
		{
			for (int i = 0; i <= sizeof(zones) / sizeof(zones[0]) - 2; i++)
			{
				Zone *first = zones[i];
				Zone *second = zones[i + 1];
				if (first->endFrame + 1 == second->startFrame) // zones are adjacent
				{
					newZones->Add(first);
					continue;
				}
				else // zones are not adjacent, create filler zone
				{
					newZone->startFrame = first->endFrame + 1;
					newZone->endFrame = second->startFrame - 1;
					newZones->Add(first);
					newZones->Add(newZone);
				}
			}
			z = zones[sizeof(zones) / sizeof(zones[0]) - 1];
			newZones->Add(z);
			if (z->endFrame != nbOfFrames - 1) // we have to add another zone extending till the end of the video
			{
				newZone->startFrame = z->endFrame + 1;
				newZone->endFrame = nbOfFrames - 1;
				newZones->Add(newZone);
			}
		}
		Zone retval[newZones->Count];
		int index = 0;
		for (ArrayList::const_iterator o = newZones->begin(); o != newZones->end(); ++o)
		{
			z = static_cast<Zone*>(*o);
			if (index < 64)
			{
				retval[index] = z;
				index++;
			}
			else
			{
				DialogResult *dr = MessageBox::Show("XviD only supports 64 zones. Including filler zones your current\r\nconfiguration yields " + sizeof(retval) / sizeof(retval[0]) + " zones. Do you want to discard the " + "remaining zones?\r\nPress Cancel to reconfigure your zones. Keep in mind that if you have no adjacent zones, a filler zone will have to be added\r\nso 32 non adjacent zones is the " + "maximum number of zones you can have. Both intro and credits region also require a zone.", "Too many zones", MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);
				if (dr == DialogResult::OK)
					break;
				else // user wants to abort
					return 0;
			}
		}
		return retval;
	}

	bool JobUtil::getFinalZoneConfiguration(VideoCodecSettings *vSettings, int introEndFrame, int creditsStartFrame, Zone zones[])
	{
		Zone *introZone = new Zone();
		Zone *creditsZone = new Zone();
		quint64 nbOfFrames = getNumberOfFrames(mainForm->getVideo()->getVideoInput());
		bool doIntroZone = false, doCreditsZone = false;
		int flushZonesStart = 0, flushZonesEnd = 0;
		if (introEndFrame > 0) // add the intro zone
		{
			introZone->startFrame = 0;
			introZone->endFrame = introEndFrame;
			introZone->mode = Quantizer;
			introZone->modifier = vSettings->getCreditsQuantizer();
			if (sizeof(zones) / sizeof(zones[0]) > 0)
			{
				Zone *z = zones[0];
				if (z->startFrame > introZone->endFrame) // the first configured zone starts after the intro zone
					doIntroZone = true;
				else
				{
					flushZonesStart = 1;
					int numberOfConfiguredZones = sizeof(zones) / sizeof(zones[0]);
					while (flushZonesStart <= numberOfConfiguredZones) // iterate through all zones backwards until we find the first that goes with the intro
					{
						Zone *conflict = zones[flushZonesStart];
						if (conflict->startFrame <= introZone->endFrame) // zone starts before the end of the intro -> conflict
							flushZonesStart++;
						else
							break;
					}
					DialogResult *dr = MessageBox::Show("Your intro zone overlaps " + flushZonesStart + " zone(s) configured\nin the codec settings.\n" + "Do you want to remove those zones and add the intro zone instead?", "Zone overlap detected", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);
					if (dr == DialogResult::Yes)
						doIntroZone = true;
					else if (dr == DialogResult::Cancel) // abort
						return false;
					else // discard the intro zone
						flushZonesStart = 0;
				}
			}
			else
				doIntroZone = true;
		}
		if (creditsStartFrame > 0) // add the credits zone
		{
			creditsZone->startFrame = creditsStartFrame;
			creditsZone->endFrame = static_cast<int>(nbOfFrames) - 1;
			creditsZone->mode = Quantizer;
			creditsZone->modifier = vSettings->getCreditsQuantizer();
			if (sizeof(zones) / sizeof(zones[0]) > 0)
			{
				Zone *z = zones[sizeof(zones) / sizeof(zones[0]) - 1]; // get the last zone
				if (z->endFrame < creditsZone->startFrame) // the last configured zone ends before the credits start zone
					doCreditsZone = true;
				else
				{
					flushZonesEnd = 1;
					int numberOfConfiguredZones = sizeof(zones) / sizeof(zones[0]);
					while (numberOfConfiguredZones - flushZonesEnd - 1 >= 0) // iterate through all zones backwards until we find the first that goes with the credits
					{
						Zone *conflict = zones[numberOfConfiguredZones - flushZonesEnd - 1];
						if (conflict->endFrame >= creditsZone->startFrame) // zone ends after the end of the credits -> conflict
							flushZonesEnd++;
						else
							break;
					}
					DialogResult *dr = MessageBox::Show("Your credits zone overlaps " + flushZonesEnd + " zone(s) configured\nin the codec settings.\n" + "Do you want to remove those zones and add the credits zone instead?", "Zone overlap detected", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);
					if (dr == DialogResult::Yes)
						doCreditsZone = true;
					else if (dr == DialogResult::Cancel) // abort
						return false;
					else // discard the credits zone
						flushZonesEnd = 0;
				}
			}
			else // no additional zones configured
				doCreditsZone = true;
		}
		int newZoneSize = sizeof(zones) / sizeof(zones[0]) - flushZonesStart - flushZonesEnd;
		if (doIntroZone)
			newZoneSize++;
		if (doCreditsZone)
			newZoneSize++;
		Zone newZones[newZoneSize];
		int index = 0;
		if (doIntroZone)
		{
			newZones[index] = introZone;
			index++;
		}
		for (int i = flushZonesStart; i < sizeof(zones) / sizeof(zones[0]) - flushZonesEnd; i++)
		{
			newZones[index] = zones[i];
			index++;
		}
		if (doCreditsZone)
		{
			newZones[index] = creditsZone;
			index++;
		}
		if (dynamic_cast<xvidSettings*>(vSettings) != 0 && sizeof(newZones) / sizeof(newZones[0]) > 0)
		{
//ORIGINAL LINE: Zone[] xvidZones = createHelperZones(newZones, (int)nbOfFrames);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			Zone *xvidZones = createHelperZones(newZones, static_cast<int>(nbOfFrames));
			if (xvidZones == 0)
				return false;
			else
			{
				zones = xvidZones;
				return true;
			}
		}
		zones = newZones;
		return true;
	}

	void JobUtil::InitializeInstanceFields()
	{
		mbtreeFile = ".stats.mbtree";
	}
}
