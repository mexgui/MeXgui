#include "MuxProvider.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
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
		for (MeGUI::GenericRegisterer<IMuxing*>::const_iterator muxing = mainForm->getPackageSystem()->getMuxerProviders()->begin(); muxing != mainForm->getPackageSystem()->getMuxerProviders()->end(); ++muxing)
			if (muxing->second->MuxerType == type)
				return muxing->second;
		return 0;
	}

	IJobProcessor *MuxProvider::GetMuxer(MuxerType type, MeGUISettings *settings)
	{
		IMuxing *muxer = GetMuxer(type);
		if (muxer == 0)
			return 0;
		return muxer->GetMuxer(settings);
	}

	MuxPath *MuxProvider::GetMuxPath(VideoEncoderType *videoCodec, AudioEncoderType audioCodecs[], ContainerType *containerType, ...)
	{
		std::vector<IEncoderType*> inputCodecs = std::vector<IEncoderType*>();
		if (videoCodec != 0)
			inputCodecs.push_back(videoCodec);
		for (MeGUI::AudioEncoderType::const_iterator ac = audioCodecs->begin(); ac != audioCodecs->end(); ++ac)
			inputCodecs.push_back(*ac);

		std::vector<MuxableType*> decidedTypeList = std::vector<MuxableType*>();
		for (unknown::const_iterator st = dictatedTypes.begin(); st != dictatedTypes.end(); ++st)
			decidedTypeList.push_back(*st);
		return findBestMuxPathAndConfig(inputCodecs, decidedTypeList, containerType);
	}

	MuxPath *MuxProvider::GetMuxPath(ContainerType *containerType, bool alwaysMux, ...)
	{
		std::vector<MuxableType*> inputTypes = std::vector<MuxableType*>();
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

	std::vector<ContainerType*> MuxProvider::GetSupportedContainers()
	{
		std::vector<ContainerType*> supportedContainers = std::vector<ContainerType*>();
		for (MeGUI::GenericRegisterer<IMuxing*>::const_iterator muxerInterface = mainForm->getPackageSystem()->getMuxerProviders()->begin(); muxerInterface != mainForm->getPackageSystem()->getMuxerProviders()->end(); ++muxerInterface)
		{
			std::vector<ContainerType*> outputTypes = muxerInterface->second->GetSupportedContainers();
			for (std::vector<ContainerType*>::const_iterator type = outputTypes.begin(); type != outputTypes.end(); ++type)
			{
				if (!std::find(supportedContainers.begin(), supportedContainers.end(), *type) != supportedContainers.end())
					supportedContainers.push_back(*type);
			}
		}
		return supportedContainers;
	}

	std::vector<DeviceType*> MuxProvider::GetSupportedDevices(ContainerType *oType)
	{
		std::vector<DeviceType*> supportedDevices = std::vector<DeviceType*>();
		for (MeGUI::GenericRegisterer<IMuxing*>::const_iterator muxerInterface = mainForm->getPackageSystem()->getMuxerProviders()->begin(); muxerInterface != mainForm->getPackageSystem()->getMuxerProviders()->end(); ++muxerInterface)
		{
			std::vector<DeviceType*> outputTypes = muxerInterface->second->GetSupportedDeviceTypes();
			for (std::vector<DeviceType*>::const_iterator type = outputTypes.begin(); type != outputTypes.end(); ++type)
			{
				if ((*type)->getContainerType() == oType)
					if (!std::find(supportedDevices.begin(), supportedDevices.end(), *type) != supportedDevices.end())
						supportedDevices.push_back(*type);
			}
		}
		return supportedDevices;
	}

	std::vector<ContainerType*> MuxProvider::GetSupportedContainers(...)
	{
		// remove duplicate types
		std::vector<MuxableType*> allTypes = std::vector<MuxableType*>();
		for (unknown::const_iterator oType = inputTypes.begin(); oType != inputTypes.end(); ++oType)
		{
			bool bFound = false;
			for (std::vector<MuxableType*>::const_iterator oAllType = allTypes.begin(); oAllType != allTypes.end(); ++oAllType)
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

		std::vector<ContainerType*> supportedContainers = std::vector<ContainerType*>();
		for (std::vector<ContainerType*>::const_iterator cot = GetSupportedContainers().begin(); cot != GetSupportedContainers().end(); ++cot)
		{
			if (CanBeMuxed(*cot, allTypes.ToArray()))
			{
				if (!std::find(supportedContainers.begin(), supportedContainers.end(), *cot) != supportedContainers.end())
					supportedContainers.push_back(*cot);
			}
		}
		return supportedContainers;
	}

	std::vector<ContainerType*> MuxProvider::GetSupportedContainers(VideoEncoderType *videoCodec, AudioEncoderType audioCodecs[], ...)
	{
		// remove duplicate codecs
		std::vector<AudioEncoderType*> allCodecs = std::vector<AudioEncoderType*>();
		for (MeGUI::AudioEncoderType::const_iterator oType = audioCodecs->begin(); oType != audioCodecs->end(); ++oType)
			if (!std::find(allCodecs.begin(), allCodecs.end(), *oType) != allCodecs.end())
				allCodecs.push_back(*oType);

		// remove duplicate types
		std::vector<MuxableType*> allTypes = std::vector<MuxableType*>();
		for (unknown::const_iterator oType = dictatedOutputTypes.begin(); oType != dictatedOutputTypes.end(); ++oType)
		{
			bool bFound = false;
			for (std::vector<MuxableType*>::const_iterator oAllType = allTypes.begin(); oAllType != allTypes.end(); ++oAllType)
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

		std::vector<ContainerType*> supportedContainers = std::vector<ContainerType*>();
		std::vector<ContainerType*> allKnownContainers = GetSupportedContainers();
		for (std::vector<ContainerType*>::const_iterator cot = allKnownContainers.begin(); cot != allKnownContainers.end(); ++cot)
		{
			if (CanBeMuxed(videoCodec, allCodecs.ToArray(), *cot, allTypes.ToArray()))
			{
				if (!std::find(supportedContainers.begin(), supportedContainers.end(), *cot) != supportedContainers.end())
					supportedContainers.push_back(*cot);
			}
		}
		return supportedContainers;
	}

	MuxPath *MuxProvider::findBestMuxPathAndConfig(std::vector<IEncoderType*> &undecidedInputs, std::vector<MuxableType*> &decidedInputs, ContainerType *containerType)
	{
		if (undecidedInputs.empty())
		{
			return getShortestMuxPath(new MuxPath(decidedInputs, containerType), decidedInputs, containerType);
		}
		else
		{
			std::vector<MuxPath*> allPaths = std::vector<MuxPath*>();
			IEncoderType *undecidedInput = undecidedInputs[0];
			undecidedInputs.RemoveAt(0);

			if (dynamic_cast<VideoEncoderType*>(undecidedInput) != 0)
			{
//ORIGINAL LINE: VideoType[] allTypes = vProvider.GetSupportedOutput((VideoEncoderType)undecidedInput);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				VideoType *allTypes = vProvider->GetSupportedOutput(static_cast<VideoEncoderType*>(undecidedInput));
				for (MeGUI::VideoType::const_iterator v = allTypes->begin(); v != allTypes->end(); ++v)
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
				for (MeGUI::AudioType::const_iterator a = allTypes->begin(); a != allTypes->end(); ++a)
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

	MuxPath *MuxProvider::getShortestMuxPath(MuxPath *currentMuxPath, std::vector<IMuxing*> &remainingMuxers, ContainerType *desiredContainerType)
	{
		if (currentMuxPath->IsCompleted())
			return currentMuxPath;

		std::vector<MuxPath*> allMuxPaths = std::vector<MuxPath*>();

		std::vector<IMuxing*> newRemainingMuxers = std::vector<IMuxing*>();
		newRemainingMuxers.AddRange(remainingMuxers);

		for (std::vector<IMuxing*>::const_iterator muxer = remainingMuxers.begin(); muxer != remainingMuxers.end(); ++muxer)
		{
			bool supportsInput = currentMuxPath[currentMuxPath->getLength() - 1].muxerInterface->GetContainersInCommon(*muxer)->Count > 0;
			if (!supportsInput)
				continue;

			MuxPath *newMuxPath = currentMuxPath->Clone();

			MuxPathLeg currentMPL = MuxPathLeg();
			currentMPL.muxerInterface = *muxer;
			currentMPL.handledInputTypes = std::vector<MuxableType*>();
			currentMPL.unhandledInputTypes = std::vector<MuxableType*>();
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

	MuxPath *MuxProvider::getShortestMuxPath(MuxPath *currentMuxPath, IMuxing *muxer, std::vector<MuxableType*> &decidedHandledTypes, std::vector<MuxableType*> &undecidedPossibleHandledTypes, std::vector<MuxableType*> &unhandledInputTypes, ContainerType *desiredContainerType)
	{
		if (undecidedPossibleHandledTypes.empty())
		{
			MuxPathLeg mpl = MuxPathLeg();
			mpl.muxerInterface = muxer;
			mpl.handledInputTypes = std::vector<MuxableType*>(decidedHandledTypes);
			mpl.unhandledInputTypes = std::vector<MuxableType*>(unhandledInputTypes);
			MuxPath *newMuxPath = currentMuxPath->Clone();
			newMuxPath->Add(mpl);
			if (decidedHandledTypes.empty())
				return 0;
			return getShortestMuxPath(newMuxPath, unhandledInputTypes, desiredContainerType);
		}
		else
		{
			std::vector<MuxPath*> allMuxPaths = std::vector<MuxPath*>();
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

	MuxPath *MuxProvider::getShortestMuxPath(MuxPath *currentMuxPath, std::vector<MuxableType*> &unhandledDesiredInputTypes, ContainerType *desiredContainerType)
	{
		if (currentMuxPath->IsCompleted())
			return currentMuxPath;

		std::vector<MuxableType*> handledInputTypes;
		std::vector<MuxableType*> unhandledInputTypes;
		std::vector<MuxPath*> allMuxPaths = std::vector<MuxPath*>();

		for (MeGUI::GenericRegisterer<IMuxing*>::const_iterator muxer = mainForm->getPackageSystem()->getMuxerProviders()->begin(); muxer != mainForm->getPackageSystem()->getMuxerProviders()->end(); ++muxer)
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
					std::vector<IMuxing*> allMuxers = std::vector<IMuxing*>();
					allMuxers.AddRange(mainForm->getPackageSystem()->getMuxerProviders()->getValues());
					MuxPath *shortestPath = getShortestMuxPath(newMuxPath, allMuxers, desiredContainerType);
					if (shortestPath != 0)
						allMuxPaths.push_back(shortestPath);
				}

				MuxPath *aShortestPath = getShortestMuxPath(currentMuxPath, muxer->second, std::vector<MuxableType*>(), handledInputTypes, unhandledInputTypes, desiredContainerType);
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

	IJobProcessor *MP4BoxMuxerProvider::GetMuxer(MeGUISettings *settings)
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

	IJobProcessor *MKVMergeMuxerProvider::GetMuxer(MeGUISettings *settings)
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

	IJobProcessor *AVIMuxGUIMuxerProvider::GetMuxer(MeGUISettings *settings)
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

	IJobProcessor *TSMuxerProvider::GetMuxer(MeGUISettings *settings)
	{
		return new tsMuxeR(settings->getTSMuxerPath());
	}

	MuxerProvider::MuxerProvider(const std::string &id)
	{
		InitializeInstanceFields();
		supportedVideoTypes = std::vector<VideoType*>();
		supportedAudioTypes = std::vector<AudioType*>();
		supportedSubtitleTypes = std::vector<SubtitleType*>();
		supportedChapterTypes = std::vector<ChapterType*>();
		supportedAudioCodecs = std::vector<AudioCodec*>();
		supportedVideoCodecs = std::vector<VideoCodec*>();
		supportedContainers = std::vector<ContainerType*>();
		supportedContainerInputTypes = std::vector<ContainerType*>();
		supportedDeviceTypes = std::vector<DeviceType*>();
		videoInputFilter = audioInputFilter = subtitleInputFilter = "";
		this->id = id;
	}

	const std::string &MuxerProvider::getID() const
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

	std::vector<VideoCodec*> MuxerProvider::GetSupportedVideoCodecs()
	{
		return supportedVideoCodecs;
	}

	std::vector<AudioCodec*> MuxerProvider::GetSupportedAudioCodecs()
	{
		return supportedAudioCodecs;
	}

	const std::string &MuxerProvider::getName() const
	{
		return name;
	}

	const MeGUI::MuxerType &MuxerProvider::getMuxerType() const
	{
		return type;
	}

	const System::Windows::Forms::Shortcut &MuxerProvider::getShortcut() const
	{
		return shortcut;
	}

	std::vector<VideoType*> MuxerProvider::GetSupportedVideoTypes()
	{
		return this->supportedVideoTypes;
	}

	std::vector<AudioType*> MuxerProvider::GetSupportedAudioTypes()
	{
		return this->supportedAudioTypes;
	}

	std::vector<SubtitleType*> MuxerProvider::GetSupportedSubtitleTypes()
	{
		return this->supportedSubtitleTypes;
	}

	std::vector<ChapterType*> MuxerProvider::GetSupportedChapterTypes()
	{
		return this->supportedChapterTypes;
	}

	std::vector<ContainerType*> MuxerProvider::GetSupportedContainers()
	{
		return this->supportedContainers;
	}

	std::vector<DeviceType*> MuxerProvider::GetSupportedDeviceTypes()
	{
		return this->supportedDeviceTypes;
	}

	std::vector<ContainerType*> MuxerProvider::GetSupportedContainerTypes()
	{
		std::vector<ContainerType*> supportedOutputTypes = GetSupportedContainers();
		std::vector<ContainerType*> supportedContainers = std::vector<ContainerType*>();
		for (std::vector<ContainerType*>::const_iterator cot = supportedOutputTypes.begin(); cot != supportedOutputTypes.end(); ++cot)
		{
			supportedContainers.push_back(*cot);
		}
		return supportedContainers;
	}

	std::vector<ContainerType*> MuxerProvider::GetSupportedContainerInputTypes()
	{
		return this->supportedContainerInputTypes;
	}

	std::vector<ContainerType*> MuxerProvider::GetContainersInCommon(IMuxing *iMuxing)
	{
		std::vector<ContainerType*> supportedOutputTypes = GetSupportedContainers();
		std::vector<ContainerType*> nextSupportedInputTypes = iMuxing->GetSupportedContainerInputTypes();
		std::vector<ContainerType*> commonContainers = std::vector<ContainerType*>();
		for (std::vector<ContainerType*>::const_iterator eligibleType = supportedOutputTypes.begin(); eligibleType != supportedOutputTypes.end(); ++eligibleType)
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

	ProcessingLevel MuxerProvider::CanBeProcessed(MuxableType inputTypes[], std::vector<MuxableType*> &handledInputTypes, std::vector<MuxableType*> &unhandledInputTypes)
	{
		handledInputTypes = std::vector<MuxableType*>();
		unhandledInputTypes = std::vector<MuxableType*>();
		int filesOfType[5];
		for (MeGUI::MuxableType::const_iterator inputType = inputTypes->begin(); inputType != inputTypes->end(); ++inputType)
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

	ProcessingLevel MuxerProvider::CanBeProcessed(ContainerType inputContainers[], MuxableType inputTypes[], std::vector<MuxableType*> &handledInputTypes, std::vector<MuxableType*> &unhandledInputTypes)
	{
		bool commonContainerFound = false;
		for (MeGUI::ContainerType::const_iterator inputContainer = inputContainers->begin(); inputContainer != inputContainers->end(); ++inputContainer)
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
			handledInputTypes = std::vector<MuxableType*>();
			unhandledInputTypes = std::vector<MuxableType*>();
			return NONE;
		}
	}

	std::string MuxerProvider::GetOutputTypeFilter(ContainerType *containerType)
	{
		for (std::vector<ContainerType*>::const_iterator type = this->supportedContainers.begin(); type != this->supportedContainers.end(); ++type)
		{
			if (*type == containerType)
			{
				return (*type)->getOutputFilterString();
			}
		}
		return "";
	}

	std::string MuxerProvider::GetOutputTypeFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedContainers.ToArray());
	}

	std::string MuxerProvider::GetVideoInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedVideoTypes.ToArray());
	}

	std::string MuxerProvider::GetAudioInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedAudioTypes.ToArray());
	}

	std::string MuxerProvider::GetChapterInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedChapterTypes.ToArray());
	}

	std::string MuxerProvider::GetSubtitleInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(supportedSubtitleTypes.ToArray());
	}

	std::string MuxerProvider::GetMuxedInputFilter()
	{
		return VideoUtil::GenerateCombinedFilter(GetSupportedContainerInputTypes().ToArray());
	}

	std::string MuxerProvider::GetDeviceInputFilter()
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

	std::string AudioEncodingProvider::GetInputTypeFilter()
	{
		return "All supported types|*.avs;*.wav;*.pcm;*.mpa;*.mp2;*.mp3;*.ac3;*.dts";
	}

	IJobProcessor *AudioEncodingProvider::CreateEncoder(MeGUISettings *settings)
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

	IJobProcessor *XviDEncoderProvider::CreateEncoder(MeGUISettings *settings)
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

	IJobProcessor *X264EncoderProvider::CreateEncoder(MeGUISettings *settings)
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
