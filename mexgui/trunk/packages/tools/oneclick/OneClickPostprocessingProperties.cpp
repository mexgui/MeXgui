#include "OneClickPostprocessingProperties.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::util;

namespace MeGUI
{

	OneClickPostprocessingProperties::OneClickPostprocessingProperties()
	{
		signalAR = false;
		autoCrop = true;
		keepInputResolution = false;
		ar = Nullable<Dar>();
		avsSettings = new AviSynthSettings();
		horizontalOutputResolution = 720;
		customAR = 1.0;
		container = MeGUI::ContainerType::MKV;
		outputSize = Nullable<FileSize>();
		splitSize = Nullable<FileSize>();
		prerenderJob = false;
		deviceType = "";
		useChapterMarks = false;
		filesToDelete = std::vector<std::string>();
		_audioTracks = std::vector<OneClickAudioTrack*>();
		_subtitleTrack = std::vector<OneClickStream*>();
		_videoFileToMux = "";
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete _oneClickSettings;
		_filesToProcess = std::vector<OneClickFilesToProcess*>();
		chapterExtracted = false;
		_titleNumberToProcess = 1;
		eac3toDemux = false;
		ifoFile = "";
		applyDelayCorrection = false;
	}

	const bool &OneClickPostprocessingProperties::getAutoDeinterlace() const
	{
		return autoDeint;
	}

	void OneClickPostprocessingProperties::setAutoDeinterlace(const bool &value)
	{
		autoDeint = value;
	}

	const bool &OneClickPostprocessingProperties::getChapterExtracted() const
	{
		return chapterExtracted;
	}

	void OneClickPostprocessingProperties::setChapterExtracted(const bool &value)
	{
		chapterExtracted = value;
	}

	const bool &OneClickPostprocessingProperties::getSignalAR() const
	{
		return signalAR;
	}

	void OneClickPostprocessingProperties::setSignalAR(const bool &value)
	{
		signalAR = value;
	}

	const bool &OneClickPostprocessingProperties::getAutoCrop() const
	{
		return autoCrop;
	}

	void OneClickPostprocessingProperties::setAutoCrop(const bool &value)
	{
		autoCrop = value;
	}

	const bool &OneClickPostprocessingProperties::getKeepInputResolution() const
	{
		return keepInputResolution;
	}

	void OneClickPostprocessingProperties::setKeepInputResolution(const bool &value)
	{
		keepInputResolution = value;
	}

	const bool &OneClickPostprocessingProperties::getPrerenderJob() const
	{
		return prerenderJob;
	}

	void OneClickPostprocessingProperties::setPrerenderJob(const bool &value)
	{
		prerenderJob = value;
	}

	const int &OneClickPostprocessingProperties::getHorizontalOutputResolution() const
	{
		return horizontalOutputResolution;
	}

	void OneClickPostprocessingProperties::setHorizontalOutputResolution(const int &value)
	{
		horizontalOutputResolution = value;
	}

	const ContainerType &OneClickPostprocessingProperties::getContainer() const
	{
		return container;
	}

	void OneClickPostprocessingProperties::setContainer(const ContainerType &value)
	{
		container = value;
	}

	const std::string &OneClickPostprocessingProperties::getContainerTypeString() const
	{
		return getContainer()->getID();
	}

	void OneClickPostprocessingProperties::setContainerTypeString(const std::string &value)
	{
		for (std::vector<ContainerType*>::const_iterator t = MainForm::Instance->getMuxProvider()->GetSupportedContainers().begin(); t != MainForm::Instance->getMuxProvider()->GetSupportedContainers().end(); ++t)
		{
			if ((*t)->getID() == value)
			{
				setContainer(*t);
				return;
			}
		}
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete getContainer();
	}

	const Nullable<FileSize> &OneClickPostprocessingProperties::getOutputSize() const
	{
		return outputSize;
	}

	void OneClickPostprocessingProperties::setOutputSize(const Nullable<FileSize> &value)
	{
		outputSize = value;
	}

	const Nullable<FileSize> &OneClickPostprocessingProperties::getSplitting() const
	{
		return splitSize;
	}

	void OneClickPostprocessingProperties::setSplitting(const Nullable<FileSize> &value)
	{
		splitSize = value;
	}

	const Nullable<Dar> &OneClickPostprocessingProperties::getDAR() const
	{
		return ar;
	}

	void OneClickPostprocessingProperties::setDAR(const Nullable<Dar> &value)
	{
		ar = value;
	}

	const AviSynthSettings &OneClickPostprocessingProperties::getAvsSettings() const
	{
		return avsSettings;
	}

	void OneClickPostprocessingProperties::setAvsSettings(const AviSynthSettings &value)
	{
		avsSettings = value;
	}

	const VideoCodecSettings &OneClickPostprocessingProperties::getVideoSettings() const
	{
		return videoSettings;
	}

	void OneClickPostprocessingProperties::setVideoSettings(const VideoCodecSettings &value)
	{
		videoSettings = value;
	}

	const double &OneClickPostprocessingProperties::getCustomAR() const
	{
		return customAR;
	}

	void OneClickPostprocessingProperties::setCustomAR(const double &value)
	{
		customAR = value;
	}

	const std::string &OneClickPostprocessingProperties::getChapterFile() const
	{
		return chapterFile;
	}

	void OneClickPostprocessingProperties::setChapterFile(const std::string &value)
	{
		chapterFile = value;
	}

	const std::string &OneClickPostprocessingProperties::getFinalOutput() const
	{
		return finalOutput;
	}

	void OneClickPostprocessingProperties::setFinalOutput(const std::string &value)
	{
		finalOutput = value;
	}

	const std::string &OneClickPostprocessingProperties::getVideoInput() const
	{
		return inputFile;
	}

	void OneClickPostprocessingProperties::setVideoInput(const std::string &value)
	{
		inputFile = value;
	}

	const std::string &OneClickPostprocessingProperties::getIFOInput() const
	{
		return ifoFile;
	}

	void OneClickPostprocessingProperties::setIFOInput(const std::string &value)
	{
		ifoFile = value;
	}

	const std::string &OneClickPostprocessingProperties::getWorkingDirectory() const
	{
		return workingDirectory;
	}

	void OneClickPostprocessingProperties::setWorkingDirectory(const std::string &value)
	{
		workingDirectory = value;
	}

	const std::string &OneClickPostprocessingProperties::getAviSynthScript() const
	{
		return aviSynthScript;
	}

	void OneClickPostprocessingProperties::setAviSynthScript(const std::string &value)
	{
		aviSynthScript = value;
	}

	const std::string &OneClickPostprocessingProperties::getDeviceOutputType() const
	{
		return deviceType;
	}

	void OneClickPostprocessingProperties::setDeviceOutputType(const std::string &value)
	{
		deviceType = value;
	}

	const bool &OneClickPostprocessingProperties::getUseChaptersMarks() const
	{
		return useChapterMarks;
	}

	void OneClickPostprocessingProperties::setUseChaptersMarks(const bool &value)
	{
		useChapterMarks = value;
	}

	const bool &OneClickPostprocessingProperties::getEac3toDemux() const
	{
		return eac3toDemux;
	}

	void OneClickPostprocessingProperties::setEac3toDemux(const bool &value)
	{
		eac3toDemux = value;
	}

	const bool &OneClickPostprocessingProperties::getApplyDelayCorrection() const
	{
		return applyDelayCorrection;
	}

	void OneClickPostprocessingProperties::setApplyDelayCorrection(const bool &value)
	{
		applyDelayCorrection = value;
	}

	const std::vector<std::string> &OneClickPostprocessingProperties::getFilesToDelete() const
	{
		return filesToDelete;
	}

	void OneClickPostprocessingProperties::setFilesToDelete(const std::vector<std::string> &value)
	{
		filesToDelete = value;
	}

	const std::vector<OneClickAudioTrack*> &OneClickPostprocessingProperties::getAudioTracks() const
	{
		return _audioTracks;
	}

	void OneClickPostprocessingProperties::setAudioTracks(const std::vector<OneClickAudioTrack*> &value)
	{
		_audioTracks = value;
	}

	const std::vector<OneClickStream*> &OneClickPostprocessingProperties::getSubtitleTracks() const
	{
		return _subtitleTrack;
	}

	void OneClickPostprocessingProperties::setSubtitleTracks(const std::vector<OneClickStream*> &value)
	{
		_subtitleTrack = value;
	}

	const std::string &OneClickPostprocessingProperties::getVideoFileToMux() const
	{
		return _videoFileToMux;
	}

	void OneClickPostprocessingProperties::setVideoFileToMux(const std::string &value)
	{
		_videoFileToMux = value;
	}

	const FileIndexerWindow::IndexType &OneClickPostprocessingProperties::getIndexType() const
	{
		return _indexType;
	}

	void OneClickPostprocessingProperties::setIndexType(const FileIndexerWindow::IndexType &value)
	{
		_indexType = value;
	}

	const std::vector<OneClickFilesToProcess*> &OneClickPostprocessingProperties::getFilesToProcess() const
	{
		return _filesToProcess;
	}

	void OneClickPostprocessingProperties::setFilesToProcess(const std::vector<OneClickFilesToProcess*> &value)
	{
		_filesToProcess = value;
	}

	const OneClickSettings &OneClickPostprocessingProperties::getOneClickSetting() const
	{
		return _oneClickSettings;
	}

	void OneClickPostprocessingProperties::setOneClickSetting(const OneClickSettings &value)
	{
		_oneClickSettings = value;
	}

	const int &OneClickPostprocessingProperties::getTitleNumberToProcess() const
	{
		return _titleNumberToProcess;
	}

	void OneClickPostprocessingProperties::setTitleNumberToProcess(const int &value)
	{
		_titleNumberToProcess = value;
	}
}
