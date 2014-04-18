#include "MuxProvider.h"






//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

	MuxableType::MuxableType(OutputType *type, ICodec *codec)
	{
		this->outputType = type;
		this->codec = codec;
	}

	MuxProvider::MuxProvider(MainForm *mainForm)
	{
		InitializeInstanceFields();
		this->mainForm = mainForm;
		comparer = new MuxPathComparer();
	}

	IMuxing *MuxProvider::GetMuxer(MuxerType type)
	{
		for (MeXgui::GenericRegisterer<IMuxing*>::const_iterator muxing = mainForm->getPackageSystem()->getMuxerProviders()->begin(); muxing != mainForm->getPackageSystem()->getMuxerProviders()->end(); ++muxing)
			if (muxing->second->MuxerType == type)
				return muxing->second;
		return 0;
	}

	IJobProcessor *MuxProvider::GetMuxer(MuxerType type, MeXguiSettings *settings)
	{
		IMuxing *muxer = GetMuxer(type);
		if (muxer == 0)
			return 0;
		return muxer->GetMuxer(settings);
	}

	MuxPath *MuxProvider::GetMuxPath(VideoEncoderType *videoCodec, AudioEncoderType audioCodecs[], ContainerType *containerType, ...)
	{
		QVector<IEncoderType*> inputCodecs = QVector<IEncoderType*>();
		if (videoCodec != 0)
			inputCodecs.push_back(videoCodec);
		for (MeXgui::AudioEncoderType::const_iterator ac = audioCodecs->begin(); ac != audioCodecs->end(); ++ac)
			inputCodecs.push_back(*ac);

		QVector<MuxableType*> decidedTypeList = QVector<MuxableType*>();
		for (unknown::const_iterator st = dictatedTypes.begin(); st != dictatedTypes.end(); ++st)
			decidedTypeList.push_back(*st);
		return findBestMuxPathAndConfig(inputCodecs, decidedTypeList, containerType);
	}

	MuxPath *MuxProvider::GetMuxPath(ContainerType *containerType, bool alwaysMux, ...)
	{
		QVector<MuxableType*> inputTypes = QVector<MuxableType*>();
		inputTypes.AddRange(allTypes);
		MuxPath *shortestPath = getShortestMuxPath(new MuxPath(inputTypes, containerType, alwaysMux), inputTypes, containerType);
		return shortestPath;
	}

	bool MuxProvider::CanBeMuxed(ContainerType *containerType, ...)
	{
		MuxPath *muxPath = GetMuxPath(containerType, false, allTypes);
		if (muxPath != 0)
			return true;
		else
			return false;
	}

	bool MuxProvider::CanBeMuxed(VideoEncoderType *codec, AudioEncoderType audioCodecs[], ContainerType *containerType, ...)
	{
		MuxPath *muxPath = GetMuxPath(codec, audioCodecs, containerType, decidedTypes);
		if (muxPath != 0)
			return true;
		else
			return false;
	}

	QVector<ContainerType*> MuxProvider::GetSupportedContainers()
	{
		QVector<ContainerType*> supportedContainers = QVector<ContainerType*>();
		for (MeXgui::GenericRegisterer<IMuxing*>::const_iterator muxerInterface = mainForm->getPackageSystem()->getMuxerProviders()->begin(); muxerInterface != mainForm->getPackageSystem()->getMuxerProviders()->end(); ++muxerInterface)
		{
			QVector<ContainerType*> outputTypes = muxerInterface->second->GetSupportedContainers();
			for (QVector<ContainerType*>::const_iterator type = outputTypes.begin(); type != outputTypes.end(); ++type)
			{
				if (!std::find(supportedContainers.begin(), supportedContainers.end(), *type) != supportedContainers.end())
					supportedContainers.push_back(*type);
			}
		}
		return supportedContainers;
	}

	QVector<DeviceType*> MuxProvider::GetSupportedDevices(ContainerType *oType)
	{
		QVector<DeviceType*> supportedDevices = QVector<DeviceType*>();
		for (MeXgui::GenericRegisterer<IMuxing*>::const_iterator muxerInterface = mainForm->getPackageSystem()->getMuxerProviders()->begin(); muxerInterface != mainForm->getPackageSystem()->getMuxerProviders()->end(); ++muxerInterface)
		{
			QVector<DeviceType*> outputTypes = muxerInterface->second->GetSupportedDeviceTypes();
			for (QVector<DeviceType*>::const_iterator type = outputTypes.begin(); type != outputTypes.end(); ++type)
			{
				if ((*type)->getContainerType() == oType)
					if (!std::find(supportedDevices.begin(), supportedDevices.end(), *type) != supportedDevices.end())
						supportedDevices.push_back(*type);
			}
		}
		return supportedDevices;
	}

	QVector<ContainerType*> MuxProvider::GetSupportedContainers(...)
	{
		// remove duplicate types
		QVector<MuxableType*> allTypes = QVector<MuxableType*>();
		for (unknown::const_iterator oType = inputTypes.begin(); oType != inputTypes.end(); ++oType)
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
		}

		QVector<ContainerType*> supportedContainers = QVector<ContainerType*>();
		for (QVector<ContainerType*>::const_iterator cot = GetSupportedContainers().begin(); cot != GetSupportedContainers().end(); ++cot)
		{
			if (CanBeMuxed(*cot, allTypes.ToArray()))
			{
				if (!std::find(supportedContainers.begin(), supportedContainers.end(), *cot) != supportedContainers.end())
					supportedContainers.push_back(*cot);
			}
		}
		return supportedContainers;
	}

	QVector<ContainerType*> MuxProvider::GetSupportedContainers(VideoEncoderType *videoCodec, AudioEncoderType audioCodecs[], ...)
	{
		// remove duplicate codecs
		QVector<AudioEncoderType*> allCodecs = QVector<AudioEncoderType*>();
		for (MeXgui::AudioEncoderType::const_iterator oType = audioCodecs->begin(); oType != audioCodecs->end(); ++oType)
			if (!std::find(allCodecs.begin(), allCodecs.end(), *oType) != allCodecs.end())
				allCodecs.push_back(*oType);

		// remove duplicate types
		QVector<MuxableType*> allTypes = QVector<MuxableType*>();
		for (unknown::const_iterator oType = dictatedOutputTypes.begin(); oType != dictatedOutputTypes.end(); ++oType)
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
		}

		QVector<ContainerType*> supportedContainers = QVector<ContainerType*>();
		QVector<ContainerType*> allKnownContainers = GetSupportedContainers();
		for (QVector<ContainerType*>::const_iterator cot = allKnownContainers.begin(); cot != allKnownContainers.end(); ++cot)
		{
			if (CanBeMuxed(videoCodec, allCodecs.ToArray(), *cot, allTypes.ToArray()))
			{
				if (!std::find(supportedContainers.begin(), supportedContainers.end(), *cot) != supportedContainers.end())
					supportedContainers.push_back(*cot);
			}
		}
		return supportedContainers;
	}

	MuxPath *MuxProvider::findBestMuxPathAndConfig(QVector<IEncoderType*> &undecidedInputs, QVector<MuxableType*> &decidedInputs, ContainerType *containerType)
	{
		if (undecidedInputs.empty())
		{
			return getShortestMuxPath(new MuxPath(decidedInputs, containerType), decidedInputs, containerType);
		}
		else
		{
			QVector<MuxPath*> allPaths = QVector<MuxPath*>();
			IEncoderType *undecidedInput = undecidedInputs[0];
			undecidedInputs.RemoveAt(0);

			if (dynamic_cast<VideoEncoderType*>(undecidedInput) != 0)
			{
//ORIGINAL LINE: VideoType[] allTypes = vProvider.GetSupportedOutput((VideoEncoderType)undecidedInput);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				VideoType *allTypes = vProvider->GetSupportedOutput(static_cast<VideoEncoderType*>(undecidedInput));
				for (MeXgui::VideoType::const_iterator v = allTypes->begin(); v != allTypes->end(); ++v)
				{
					MuxableType *input = new MuxableType(*v, undecidedInput->getCodec());
					decidedInputs.push_back(input);
					MuxPath *path = findBestMuxPathAndConfig(undecidedInputs, decidedInputs, containerType);
					if (path != 0)
					{
						allPaths.push_back(path);
					}
					decidedInputs.Remove(input);
				}
			}
			if (dynamic_cast<AudioEncoderType*>(undecidedInput) != 0)
			{
//ORIGINAL LINE: AudioType[] allTypes = aProvider.GetSupportedOutput((AudioEncoderType)undecidedInput);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				AudioType *allTypes = aProvider->GetSupportedOutput(static_cast<AudioEncoderType*>(undecidedInput));
				for (MeXgui::AudioType::const_iterator a = allTypes->begin(); a != allTypes->end(); ++a)
				{
					MuxableType *input = new MuxableType(*a, undecidedInput->getCodec());
					decidedInputs.push_back(input);
					MuxPath *path = findBestMuxPathAndConfig(undecidedInputs, decidedInputs, containerType);
					if (path != 0)
					{
						allPaths.push_back(path);
					}
					decidedInputs.Remove(input);
				}
			}
			undecidedInputs.Insert(0, undecidedInput);
			return comparer->GetBestMuxPath(allPaths);
		}
	}

	MuxPath *MuxProvider::getShortestMuxPath(MuxPath *currentMuxPath, QVector<IMuxing*> &remainingMuxers, ContainerType *desiredContainerType)
	{
		if (currentMuxPath->IsCompleted())
			return currentMuxPath;

		QVector<MuxPath*> allMuxPaths = QVector<MuxPath*>();

		QVector<IMuxing*> newRemainingMuxers = QVector<IMuxing*>();
		newRemainingMuxers.AddRange(remainingMuxers);

		for (QVector<IMuxing*>::const_iterator muxer = remainingMuxers.begin(); muxer != remainingMuxers.end(); ++muxer)
		{
			bool supportsInput = currentMuxPath[currentMuxPath->getLength() - 1].muxerInterface->GetContainersInCommon(*muxer)->Count > 0;
			if (!supportsInput)
				continue;

			MuxPath *newMuxPath = currentMuxPath->Clone();

			MuxPathLeg currentMPL = MuxPathLeg();
			currentMPL.muxerInterface = *muxer;
			currentMPL.handledInputTypes = QVector<MuxableType*>();
			currentMPL.unhandledInputTypes = QVector<MuxableType*>();
			newMuxPath->Add(currentMPL);

			newRemainingMuxers.Remove(*muxer);
			MuxPath *shortestPath = getShortestMuxPath(newMuxPath, newRemainingMuxers, desiredContainerType);
			if (shortestPath != 0)
			{
				allMuxPaths.push_back(shortestPath);
			}
			newRemainingMuxers.push_back(*muxer);
		}
		return comparer->GetBestMuxPath(allMuxPaths);
	}

	MuxPath *MuxProvider::getShortestMuxPath(MuxPath *currentMuxPath, IMuxing *muxer, QVector<MuxableType*> &decidedHandledTypes, QVector<MuxableType*> &undecidedPossibleHandledTypes, QVector<MuxableType*> &unhandledInputTypes, ContainerType *desiredContainerType)
	{
		if (undecidedPossibleHandledTypes.empty())
		{
			MuxPathLeg mpl = MuxPathLeg();
			mpl.muxerInterface = muxer;
			mpl.handledInputTypes = QVector<MuxableType*>(decidedHandledTypes);
			mpl.unhandledInputTypes = QVector<MuxableType*>(unhandledInputTypes);
			MuxPath *newMuxPath = currentMuxPath->Clone();
			newMuxPath->Add(mpl);
			if (decidedHandledTypes.empty())
				return 0;
			return getShortestMuxPath(newMuxPath, unhandledInputTypes, desiredContainerType);
		}
		else
		{
			QVector<MuxPath*> allMuxPaths = QVector<MuxPath*>();
			MuxableType *type = undecidedPossibleHandledTypes[0];
			undecidedPossibleHandledTypes.RemoveAt(0);

			decidedHandledTypes.push_back(type);
			MuxPath *shortestMuxPath = getShortestMuxPath(currentMuxPath, muxer, decidedHandledTypes, undecidedPossibleHandledTypes, unhandledInputTypes, desiredContainerType);
			if (shortestMuxPath != 0)
				allMuxPaths.push_back(shortestMuxPath);
			decidedHandledTypes.Remove(type);

			unhandledInputTypes.push_back(type);
			shortestMuxPath = getShortestMuxPath(currentMuxPath, muxer, decidedHandledTypes, undecidedPossibleHandledTypes, unhandledInputTypes, desiredContainerType);
			if (shortestMuxPath != 0)
				allMuxPaths.push_back(shortestMuxPath);
			unhandledInputTypes.Remove(type);

			undecidedPossibleHandledTypes.push_back(type);

			return (comparer->GetBestMuxPath(allMuxPaths));
		}
	}

	MuxPath *MuxProvider::getShortestMuxPath(MuxPath *currentMuxPath, QVector<MuxableType*> &unhandledDesiredInputTypes, ContainerType *desiredContainerType)
	{
		if (currentMuxPath->IsCompleted())
			return currentMuxPath;

		QVector<MuxableType*> handledInputTypes;
		QVector<MuxableType*> unhandledInputTypes;
		QVector<MuxPath*> allMuxPaths = QVector<MuxPath*>();

		for (MeXgui::GenericRegisterer<IMuxing*>::const_iterator muxer = mainForm->getPackageSystem()->getMuxerProviders()->begin(); muxer != mainForm->getPackageSystem()->getMuxerProviders()->end(); ++muxer)
		{
			ProcessingLevel level;
			if (currentMuxPath->getLength() > 0)
			{
				level = muxer->second->CanBeProcessed(currentMuxPath[currentMuxPath->getLength() - 1].muxerInterface->GetSupportedContainerTypes()->ToArray(), unhandledDesiredInputTypes.ToArray(), handledInputTypes, unhandledInputTypes);
			}
			else
			{
				level = muxer->second->CanBeProcessed(unhandledDesiredInputTypes.ToArray(), handledInputTypes, unhandledInputTypes);
			}
			if (level != NONE)
			{
				MuxPath *newMuxPath = currentMuxPath->Clone();

				MuxPathLeg currentMPL = MuxPathLeg();
				currentMPL.muxerInterface = muxer->second;
				currentMPL.handledInputTypes = handledInputTypes;
				currentMPL.unhandledInputTypes = unhandledInputTypes;
				newMuxPath->Add(currentMPL);

				if (unhandledInputTypes.empty())
				{
					// All the streams have been muxed into some file. Now let's 
					// just make sure that we can convert this file to the format we want
					// (or leave it alone if it already is in that format).
					QVector<IMuxing*> allMuxers = QVector<IMuxing*>();
					allMuxers.AddRange(mainForm->getPackageSystem()->getMuxerProviders()->getValues());
					MuxPath *shortestPath = getShortestMuxPath(newMuxPath, allMuxers, desiredContainerType);
					if (shortestPath != 0)
						allMuxPaths.push_back(shortestPath);
				}

				MuxPath *aShortestPath = getShortestMuxPath(currentMuxPath, muxer->second, QVector<MuxableType*>(), handledInputTypes, unhandledInputTypes, desiredContainerType);
				if (aShortestPath != 0)
					allMuxPaths.push_back(aShortestPath);
			}
		}
		return comparer->GetBestMuxPath(allMuxPaths);
	}

	void MuxProvider::InitializeInstanceFields()
	{
		vProvider = new VideoEncoderProvider();
		aProvider = new AudioEncoderProvider();
	}

	MP4BoxMuxerProvider::MP4BoxMuxerProvider() : MuxerProvider("MP4Box")
	{
		supportedVideoTypes.push_back(VideoType::AVI);
		supportedVideoTypes.push_back(VideoType::RAWASP);
		supportedVideoTypes.push_back(VideoType::RAWAVC);
		supportedVideoTypes.push_back(VideoType::RAWAVC2);
		supportedVideoTypes.push_back(VideoType::MPEG2);
		supportedVideoTypes.push_back(VideoType::MP4);
		supportedAudioTypes.push_back(AudioType::AC3);
		supportedAudioTypes.push_back(AudioType::RAWAAC);
		supportedAudioTypes.push_back(AudioType::MP4AAC);
		supportedAudioTypes.push_back(AudioType::M4A);
		supportedAudioTypes.push_back(AudioType::MP3);
		supportedAudioTypes.push_back(AudioType::VBRMP3);
		supportedAudioTypes.push_back(AudioType::CBRMP3);
		supportedVideoCodecs.push_back(VideoCodec::ASP);
		supportedVideoCodecs.push_back(VideoCodec::AVC);
		supportedAudioCodecs.push_back(AudioCodec::AAC);
		supportedAudioCodecs.push_back(AudioCodec::AC3);
		supportedAudioCodecs.push_back(AudioCodec::MP3);
		supportedSubtitleTypes.push_back(SubtitleType::SUBRIP);
		supportedSubtitleTypes.push_back(SubtitleType::VOBSUB);
		supportedSubtitleTypes.push_back(SubtitleType::TTXT);
		supportedChapterTypes.push_back(ChapterType::OGG_TXT);
		supportedContainers.push_back(ContainerType::MP4);
		supportedContainerInputTypes.push_back(ContainerType::AVI);
		supportedContainerInputTypes.push_back(ContainerType::MP4);
		supportedDeviceTypes.push_back(DeviceType::APPLETV);
		supportedDeviceTypes.push_back(DeviceType::IPAD);
		supportedDeviceTypes.push_back(DeviceType::IPHONE);
		supportedDeviceTypes.push_back(DeviceType::IPOD);
		supportedDeviceTypes.push_back(DeviceType::ISMA);
		supportedDeviceTypes.push_back(DeviceType::PSP);
		supportsAnyInputtableAudioCodec = false;
		supportsAnyInputtableVideoCodec = false;
		MuxerProvider::type = MP4BOX;
		maxFilesOfType = new int[] {1, -1, -1, 1, 1};
		name = "MP4 Muxer";
		shortcut = System::Windows::Forms::Shortcut::Ctrl5;
	}

	IJobProcessor *MP4BoxMuxerProvider::GetMuxer(MeXguiSettings *settings)
	{
		return new MP4BoxMuxer(settings->getMp4boxPath());
	}

	MKVMergeMuxerProvider::MKVMergeMuxerProvider() : MuxerProvider("mkvmerge")
	{
		supportedVideoTypes.push_back(VideoType::AVI);
		supportedVideoTypes.push_back(VideoType::MKV);
		supportedVideoTypes.push_back(VideoType::MP4);
		supportedVideoTypes.push_back(VideoType::RAWAVC);
		supportedVideoTypes.push_back(VideoType::RAWAVC2);
		supportedVideoTypes.push_back(VideoType::MPEG2);
		supportedVideoTypes.push_back(VideoType::VC1);
		supportedAudioTypes.push_back(AudioType::RAWAAC);
		supportedAudioTypes.push_back(AudioType::MP4AAC);
		supportedAudioTypes.push_back(AudioType::M4A);
		supportedAudioTypes.push_back(AudioType::MP3);
		supportedAudioTypes.push_back(AudioType::VBRMP3);
		supportedAudioTypes.push_back(AudioType::CBRMP3);
		supportedAudioTypes.push_back(AudioType::VORBIS);
		supportedAudioTypes.push_back(AudioType::MP2);
		supportedAudioTypes.push_back(AudioType::AC3);
		supportedAudioTypes.push_back(AudioType::DTS);
		supportedAudioTypes.push_back(AudioType::WAV);
		supportedAudioTypes.push_back(AudioType::EAC3);
		supportedAudioTypes.push_back(AudioType::FLAC);
		supportedAudioTypes.push_back(AudioType::THD);
		supportedAudioTypes.push_back(AudioType::DTSHD);
		supportedAudioTypes.push_back(AudioType::DTSMA);
		supportsAnyInputtableAudioCodec = true;
		supportsAnyInputtableVideoCodec = true;
		supportedSubtitleTypes.push_back(SubtitleType::SUBRIP);
		supportedSubtitleTypes.push_back(SubtitleType::VOBSUB);
		supportedSubtitleTypes.push_back(SubtitleType::SSA);
		supportedSubtitleTypes.push_back(SubtitleType::ASS);
		supportedSubtitleTypes.push_back(SubtitleType::BDSUP);
		supportedChapterTypes.push_back(ChapterType::OGG_TXT);
		supportedChapterTypes.push_back(ChapterType::MKV_XML);
		supportedContainers.push_back(ContainerType::MKV);
		supportedContainerInputTypes.push_back(ContainerType::MP4);
		supportedContainerInputTypes.push_back(ContainerType::AVI);
		supportedContainerInputTypes.push_back(ContainerType::MKV);
		maxFilesOfType = new int[] {-1, -1, -1, 1, 0};
		MuxerProvider::type = MKVMERGE;
		name = "MKV Muxer";
		shortcut = System::Windows::Forms::Shortcut::Ctrl4;
	}

	IJobProcessor *MKVMergeMuxerProvider::GetMuxer(MeXguiSettings *settings)
	{
		return new MkvMergeMuxer(settings->getMkvmergePath());
	}

	AVIMuxGUIMuxerProvider::AVIMuxGUIMuxerProvider() : MuxerProvider("AVIMuxGUI")
	{
		supportedVideoTypes.push_back(VideoType::AVI);
		supportsAnyInputtableVideoCodec = true;

		supportedAudioTypes.push_back(AudioType::AC3);
		supportedAudioTypes.push_back(AudioType::DTS);
		supportedAudioTypes.push_back(AudioType::MP3);
		supportedAudioTypes.push_back(AudioType::VBRMP3);
		supportedAudioTypes.push_back(AudioType::CBRMP3);
		supportedAudioTypes.push_back(AudioType::MP2);
		supportedAudioTypes.push_back(AudioType::RAWAAC);
		supportsAnyInputtableAudioCodec = true;

		supportedDeviceTypes.push_back(DeviceType::PC);

		supportedSubtitleTypes.push_back(SubtitleType::SUBRIP);

		supportedContainers.push_back(ContainerType::AVI);

		supportedContainerInputTypes.push_back(ContainerType::AVI);

		maxFilesOfType = new int[] {1, -1, -1, 0, 1};
		MuxerProvider::type = AVIMUXGUI;
		name = "AVI Muxer";
		shortcut = System::Windows::Forms::Shortcut::Ctrl2;
	}

	IJobProcessor *AVIMuxGUIMuxerProvider::GetMuxer(MeXguiSettings *settings)
	{
		return new AMGMuxer(settings->getAviMuxGUIPath());
	}

	TSMuxerProvider::TSMuxerProvider() : MuxerProvider("tsMuxeR")
	{
		supportedVideoTypes.push_back(VideoType::MPEG2);
		supportedVideoTypes.push_back(VideoType::RAWAVC);
		supportedVideoTypes.push_back(VideoType::RAWAVC2);
		supportedVideoTypes.push_back(VideoType::VC1);
		supportedVideoTypes.push_back(VideoType::MP4);
		supportedAudioTypes.push_back(AudioType::AC3);
		supportedAudioTypes.push_back(AudioType::DTS);
		supportedAudioTypes.push_back(AudioType::EAC3);
		supportedAudioTypes.push_back(AudioType::RAWAAC);
		supportedAudioTypes.push_back(AudioType::DTSHD);
		supportedAudioTypes.push_back(AudioType::DTSMA);
		supportedAudioTypes.push_back(AudioType::MP4AAC);
		supportedAudioTypes.push_back(AudioType::WAV);
		supportedAudioTypes.push_back(AudioType::PCM);
		supportedVideoCodecs.push_back(VideoCodec::AVC);
		supportedAudioCodecs.push_back(AudioCodec::AAC);
		supportedAudioCodecs.push_back(AudioCodec::AC3);
		supportedAudioCodecs.push_back(AudioCodec::DTS);
		supportedSubtitleTypes.push_back(SubtitleType::SUBRIP);
		supportedSubtitleTypes.push_back(SubtitleType::BDSUP);
		supportedChapterTypes.push_back(ChapterType::OGG_TXT);
		supportedContainers.push_back(ContainerType::M2TS);
		supportedContainerInputTypes.push_back(ContainerType::MKV);
		supportedContainerInputTypes.push_back(ContainerType::MP4);
		supportedContainerInputTypes.push_back(ContainerType::M2TS);
		supportedDeviceTypes.push_back(DeviceType::AVCHD);
		supportedDeviceTypes.push_back(DeviceType::BD);
		supportsAnyInputtableAudioCodec = true;
		supportsAnyInputtableVideoCodec = true;
		MuxerProvider::type = TSMUXER;
		maxFilesOfType = new int[] {1, -1, -1, 1, 1};
		name = "M2TS Muxer";
		shortcut = System::Windows::Forms::Shortcut::Ctrl3;
	}

	IJobProcessor *TSMuxerProvider::GetMuxer(MeXguiSettings *settings)
	{
		return new tsMuxeR(settings->getTSMuxerPath());
	}

	MuxerProvider::MuxerProvider(const QString &id)
	{
		InitializeInstanceFields();
		supportedVideoTypes = QVector<VideoType*>();
		supportedAudioTypes = QVector<AudioType*>();
		supportedSubtitleTypes = QVector<SubtitleType*>();
		supportedChapterTypes = QVector<ChapterType*>();
		supportedAudioCodecs = QVector<AudioCodec*>();
		supportedVideoCodecs = QVector<VideoCodec*>();
		supportedContainers = QVector<ContainerType*>();
		supportedContainerInputTypes = QVector<ContainerType*>();
		supportedDeviceTypes = QVector<DeviceType*>();
		videoInputFilter = audioInputFilter = subtitleInputFilter = "";
		this->id = id;
	}

	const QString &MuxerProvider::getID() const
	{
		return id;
	}

	bool MuxerProvider::SupportsVideoCodec(VideoCodec *codec)
	{
		if (supportsAnyInputtableVideoCodec)
			return true;
		return (std::find(GetSupportedVideoCodecs().begin(), GetSupportedVideoCodecs().end(), codec) != GetSupportedVideoCodecs().end());
	}

	bool MuxerProvider::SupportsAudioCodec(AudioCodec *codec)
	{
		if (supportsAnyInputtableAudioCodec)
			return true;
		return (std::find(GetSupportedAudioCodecs().begin(), GetSupportedAudioCodecs().end(), codec) != GetSupportedAudioCodecs().end());
	}

	QVector<VideoCodec*> MuxerProvider::GetSupportedVideoCodecs()
	{
		return supportedVideoCodecs;
	}

	QVector<AudioCodec*> MuxerProvider::GetSupportedAudioCodecs()
	{
		return supportedAudioCodecs;
	}

	const QString &MuxerProvider::getName() const
	{
		return name;
	}

	const MeXgui::MuxerType &MuxerProvider::getMuxerType() const
	{
		return type;
	}

	const System::Windows::Forms::Shortcut &MuxerProvider::getShortcut() const
	{
		return shortcut;
	}

	QVector<VideoType*> MuxerProvider::GetSupportedVideoTypes()
	{
		return this->supportedVideoTypes;
	}

	QVector<AudioType*> MuxerProvider::GetSupportedAudioTypes()
	{
		return this->supportedAudioTypes;
	}

	QVector<SubtitleType*> MuxerProvider::GetSupportedSubtitleTypes()
	{
		return this->supportedSubtitleTypes;
	}

	QVector<ChapterType*> MuxerProvider::GetSupportedChapterTypes()
	{
		return this->supportedChapterTypes;
	}

	QVector<ContainerType*> MuxerProvider::GetSupportedContainers()
	{
		return this->supportedContainers;
	}

	QVector<DeviceType*> MuxerProvider::GetSupportedDeviceTypes()
	{
		return this->supportedDeviceTypes;
	}

	QVector<ContainerType*> MuxerProvider::GetSupportedContainerTypes()
	{
		QVector<ContainerType*> supportedOutputTypes = GetSupportedContainers();
		QVector<ContainerType*> supportedContainers = QVector<ContainerType*>();
		for (QVector<ContainerType*>::const_iterator cot = supportedOutputTypes.begin(); cot != supportedOutputTypes.end(); ++cot)
		{
			supportedContainers.push_back(*cot);
		}
		return supportedContainers;
	}

	QVector<ContainerType*> MuxerProvider::GetSupportedContainerInputTypes()
	{
		return this->supportedContainerInputTypes;
	}

	QVector<ContainerType*> MuxerProvider::GetContainersInCommon(IMuxing *iMuxing)
	{
		QVector<ContainerType*> supportedOutputTypes = GetSupportedContainers();
		QVector<ContainerType*> nextSupportedInputTypes = iMuxing->GetSupportedContainerInputTypes();
		QVector<ContainerType*> commonContainers = QVector<ContainerType*>();
		for (QVector<ContainerType*>::const_iterator eligibleType = supportedOutputTypes.begin(); eligibleType != supportedOutputTypes.end(); ++eligibleType)
		{
			if (std::find(nextSupportedInputTypes.begin(), nextSupportedInputTypes.end(), *eligibleType) != nextSupportedInputTypes.end())
				commonContainers.push_back(*eligibleType);
		}
		return commonContainers;
	}

	int MuxerProvider::getSupportedType(MuxableType *type)
	{
		if (dynamic_cast<VideoType*>(type->outputType) != 0 && std::find(supportedVideoTypes.begin(), supportedVideoTypes.end(), static_cast<VideoType*>(type->outputType)) != supportedVideoTypes.end()) && (supportsAnyInputtableVideoCodec || std::find(supportedVideoCodecs.begin(), supportedVideoCodecs.end(), static_cast<VideoCodec*>(type->codec)) != supportedVideoCodecs.end())))
			return 0;
		if (dynamic_cast<AudioType*>(type->outputType) != 0 && std::find(supportedAudioTypes.begin(), supportedAudioTypes.end(), static_cast<AudioType*>(type->outputType)) != supportedAudioTypes.end()) && (supportsAnyInputtableAudioCodec || std::find(supportedAudioCodecs.begin(), supportedAudioCodecs.end(), static_cast<AudioCodec*>(type->codec)) != supportedAudioCodecs.end())))
			return 1;
		if (dynamic_cast<SubtitleType*>(type->outputType) != 0 && std::find(supportedSubtitleTypes.begin(), supportedSubtitleTypes.end(), static_cast<SubtitleType*>(type->outputType)) != supportedSubtitleTypes.end()))
			return 2;
		if (dynamic_cast<ChapterType*>(type->outputType) != 0 && std::find(supportedChapterTypes.begin(), supportedChapterTypes.end(), static_cast<ChapterType*>(type->outputType)) != supportedChapterTypes.end()))
			return 3;
		if (dynamic_cast<DeviceType*>(type->outputType) != 0 && std::find(supportedDeviceTypes.begin(), supportedDeviceTypes.end(), static_cast<DeviceType*>(type->outputType)) != supportedDeviceTypes.end()))
			return 4;
		return -1;
	}

	ProcessingLevel MuxerProvider::CanBeProcessed(MuxableType inputTypes[], QVector<MuxableType*> &handledInputTypes, QVector<MuxableType*> &unhandledInputTypes)
	{
		handledInputTypes = QVector<MuxableType*>();
		unhandledInputTypes = QVector<MuxableType*>();
		int filesOfType[5];
		for (MeXgui::MuxableType::const_iterator inputType = inputTypes->begin(); inputType != inputTypes->end(); ++inputType)
		{
			int type = getSupportedType(*inputType);
			if (type >= 0)
			{
				if (maxFilesOfType[type] < 0 || filesOfType[type] < maxFilesOfType[type]) // We ignore it in this case
				{
					handledInputTypes.push_back(*inputType);
					filesOfType[type]++;
				}
				else
					unhandledInputTypes.push_back(*inputType);
			}
			else
				unhandledInputTypes.push_back(*inputType);
		}
		ProcessingLevel retval = NONE;
		if (handledInputTypes.size() > 0)
			retval = SOME;
		if (unhandledInputTypes.empty() || sizeof(inputTypes) / sizeof(inputTypes[0]) == 0)
			retval = ALL;
		return retval;
	}

	ProcessingLevel MuxerProvider::CanBeProcessed(ContainerType inputContainers[], MuxableType inputTypes[], QVector<MuxableType*> &handledInputTypes, QVector<MuxableType*> &unhandledInputTypes)
	{
		bool commonContainerFound = false;
		for (MeXgui::ContainerType::const_iterator inputContainer = inputContainers->begin(); inputContainer != inputContainers->end(); ++inputContainer)
		{
			if (std::find(GetSupportedContainerInputTypes().begin(), GetSupportedContainerInputTypes().end(), *inputContainer) != GetSupportedContainerInputTypes().end())
			{
				commonContainerFound = true;
				break;
			}
		}
		if (commonContainerFound)
			return CanBeProcessed(inputTypes, handledInputTypes, unhandledInputTypes);
		else
		{
			handledInputTypes = QVector<MuxableType*>();
			unhandledInputTypes = QVector<MuxableType*>();
			return NONE;
		}
	}

	QString MuxerProvider::GetOutputTypeFilter(ContainerType *containerType)
	{
		for (QVector<ContainerType*>::const_iterator type = this->supportedContainers.begin(); type != this->supportedContainers.end(); ++type)
		{
			if (*type == containerType)
			{
				return (*type)->getOutputFilterString();
			}
		}
		return "";
	}

	QString MuxerProvider::GetOutputTypeFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedContainers.ToArray());
	}

	QString MuxerProvider::GetVideoInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedVideoTypes.ToArray());
	}

	QString MuxerProvider::GetAudioInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedAudioTypes.ToArray());
	}

	QString MuxerProvider::GetChapterInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedChapterTypes.ToArray());
	}

	QString MuxerProvider::GetSubtitleInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedSubtitleTypes.ToArray());
	}

	QString MuxerProvider::GetMuxedInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(GetSupportedContainerInputTypes().ToArray());
	}

	QString MuxerProvider::GetDeviceInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedDeviceTypes.ToArray());
	}

	void MuxerProvider::InitializeInstanceFields()
	{
		supportsAnyInputtableAudioCodec = false;
		supportsAnyInputtableVideoCodec = false;
	}

	AudioEncodingProvider::AudioEncodingProvider() : EncodingProvider()
	{
	}

	QString AudioEncodingProvider::GetInputTypeFilter()
	{
		return "All supported types|*.avs;*.wav;*.pcm;*.mpa;*.mp2;*.mp3;*.ac3;*.dts";
	}

	IJobProcessor *AudioEncodingProvider::CreateEncoder(MeXguiSettings *settings)
	{
		return new AviSynthAudioEncoder(settings);
	}

	VideoEncoderProvider::VideoEncoderProvider() : AllEncoderProvider()
	{
		this->RegisterEncoder(new X264EncoderProvider());
		this->RegisterEncoder(new XviDEncoderProvider());
	}

	AudioEncoderProvider::AudioEncoderProvider() : AllEncoderProvider()
	{
		RegisterEncoder(new NeroAACEncodingProvider());
		RegisterEncoder(new LameMP3EncodingProvider());
		RegisterEncoder(new VorbisEncodingProvider());
		RegisterEncoder(new AC3EncodingProvider());
		RegisterEncoder(new MP2EncodingProvider());
		RegisterEncoder(new AftenEncodingProvider());
		RegisterEncoder(new FlacEncodingProvider());
		RegisterEncoder(new QaacEncodingProvider());
		RegisterEncoder(new OpusEncodingProvider());
	}

	XviDEncoderProvider::XviDEncoderProvider()
	{
		supportedCodecs.push_back(VideoCodec::ASP);
		supportedTypes.push_back(VideoType::AVI);
		supportedTypes.push_back(VideoType::MKV);
		supportedTypes.push_back(VideoType::RAWASP);
		supportedEncoderTypes.push_back(VideoEncoderType::XVID);
	}

	IJobProcessor *XviDEncoderProvider::CreateEncoder(MeXguiSettings *settings)
	{
		return new XviDEncoder(settings->getXviDEncrawPath());
	}

	X264EncoderProvider::X264EncoderProvider()
	{
		supportedCodecs.push_back(VideoCodec::AVC);
		//supportedTypes.Add(VideoType.MP4); disabled as official x264 builds do not output to mp4
		supportedTypes.push_back(VideoType::MKV);
		supportedTypes.push_back(VideoType::RAWAVC);
		supportedEncoderTypes.push_back(VideoEncoderType::X264);
	}

	IJobProcessor *X264EncoderProvider::CreateEncoder(MeXguiSettings *settings)
	{
		return new x264Encoder(settings->getX264Path());
	}

	NeroAACEncodingProvider::NeroAACEncodingProvider() : AudioEncodingProvider()
	{
		supportedCodecs.push_back(AudioCodec::AAC);
		supportedTypes.push_back(AudioType::MP4AAC);
		supportedTypes.push_back(AudioType::M4A);
		supportedEncoderTypes.push_back(AudioEncoderType::NAAC);
	}

	LameMP3EncodingProvider::LameMP3EncodingProvider() : AudioEncodingProvider()
	{
		supportedCodecs.push_back(AudioCodec::MP3);
		supportedTypes.push_back(AudioType::MP3);
		supportedEncoderTypes.push_back(AudioEncoderType::LAME);
	}

	VorbisEncodingProvider::VorbisEncodingProvider() : AudioEncodingProvider()
	{
		supportedCodecs.push_back(AudioCodec::VORBIS);
		supportedTypes.push_back(AudioType::VORBIS);
		supportedEncoderTypes.push_back(AudioEncoderType::VORBIS);
	}

	AC3EncodingProvider::AC3EncodingProvider() : AudioEncodingProvider()
	{
		supportedCodecs.push_back(AudioCodec::AC3);
		supportedTypes.push_back(AudioType::AC3);
		supportedEncoderTypes.push_back(AudioEncoderType::FFAC3);
	}

	MP2EncodingProvider::MP2EncodingProvider() : AudioEncodingProvider()
	{
		supportedCodecs.push_back(AudioCodec::DTS);
		supportedTypes.push_back(AudioType::MP2);
		supportedEncoderTypes.push_back(AudioEncoderType::FFMP2);
	}

	AftenEncodingProvider::AftenEncodingProvider() : AudioEncodingProvider()
	{
		supportedCodecs.push_back(AudioCodec::AC3);
		supportedTypes.push_back(AudioType::AC3);
		supportedEncoderTypes.push_back(AudioEncoderType::AFTEN);
	}

	FlacEncodingProvider::FlacEncodingProvider() : AudioEncodingProvider()
	{
		supportedCodecs.push_back(AudioCodec::FLAC);
		supportedTypes.push_back(AudioType::FLAC);
		supportedEncoderTypes.push_back(AudioEncoderType::FLAC);
	}

	QaacEncodingProvider::QaacEncodingProvider() : AudioEncodingProvider()
	{
		supportedCodecs.push_back(AudioCodec::AAC);
		supportedTypes.push_back(AudioType::M4A);
		supportedTypes.push_back(AudioType::MP4AAC);
		supportedEncoderTypes.push_back(AudioEncoderType::QAAC);
	}

	OpusEncodingProvider::OpusEncodingProvider() : AudioEncodingProvider()
	{
		supportedCodecs.push_back(AudioCodec::OPUS);
		supportedTypes.push_back(AudioType::OPUS);
		supportedEncoderTypes.push_back(AudioEncoderType::OPUS);
	}
}
