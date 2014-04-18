#include "OneClickPostprocessingProperties.h"




//using namespace System::Collections::Generic;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::util;

namespace MeXgui
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
		container = MeXgui::ContainerType::MKV;
		outputSize = Nullable<FileSize>();
		splitSize = Nullable<FileSize>();
		prerenderJob = false;
		deviceType = "";
		useChapterMarks = false;
		filesToDelete = QVector<QString>();
		_audioTracks = QVector<OneClickAudioTrack*>();
		_subtitleTrack = QVector<OneClickStream*>();
		_videoFileToMux = "";
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete _oneClickSettings;
		_filesToProcess = QVector<OneClickFilesToProcess*>();
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

	const QString &OneClickPostprocessingProperties::getContainerTypeString() const
	{
		return getContainer()->getID();
	}

	void OneClickPostprocessingProperties::setContainerTypeString(const QString &value)
	{
		for (QVector<ContainerType*>::const_iterator t = MainForm::Instance->getMuxProvider()->GetSupportedContainers().begin(); t != MainForm::Instance->getMuxProvider()->GetSupportedContainers().end(); ++t)
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

	const QString &OneClickPostprocessingProperties::getChapterFile() const
	{
		return chapterFile;
	}

	void OneClickPostprocessingProperties::setChapterFile(const QString &value)
	{
		chapterFile = value;
	}

	const QString &OneClickPostprocessingProperties::getFinalOutput() const
	{
		return finalOutput;
	}

	void OneClickPostprocessingProperties::setFinalOutput(const QString &value)
	{
		finalOutput = value;
	}

	const QString &OneClickPostprocessingProperties::getVideoInput() const
	{
		return inputFile;
	}

	void OneClickPostprocessingProperties::setVideoInput(const QString &value)
	{
		inputFile = value;
	}

	const QString &OneClickPostprocessingProperties::getIFOInput() const
	{
		return ifoFile;
	}

	void OneClickPostprocessingProperties::setIFOInput(const QString &value)
	{
		ifoFile = value;
	}

	const QString &OneClickPostprocessingProperties::getWorkingDirectory() const
	{
		return workingDirectory;
	}

	void OneClickPostprocessingProperties::setWorkingDirectory(const QString &value)
	{
		workingDirectory = value;
	}

	const QString &OneClickPostprocessingProperties::getAviSynthScript() const
	{
		return aviSynthScript;
	}

	void OneClickPostprocessingProperties::setAviSynthScript(const QString &value)
	{
		aviSynthScript = value;
	}

	const QString &OneClickPostprocessingProperties::getDeviceOutputType() const
	{
		return deviceType;
	}

	void OneClickPostprocessingProperties::setDeviceOutputType(const QString &value)
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

	const QVector<QString> &OneClickPostprocessingProperties::getFilesToDelete() const
	{
		return filesToDelete;
	}

	void OneClickPostprocessingProperties::setFilesToDelete(const QVector<QString> &value)
	{
		filesToDelete = value;
	}

	const QVector<OneClickAudioTrack*> &OneClickPostprocessingProperties::getAudioTracks() const
	{
		return _audioTracks;
	}

	void OneClickPostprocessingProperties::setAudioTracks(const QVector<OneClickAudioTrack*> &value)
	{
		_audioTracks = value;
	}

	const QVector<OneClickStream*> &OneClickPostprocessingProperties::getSubtitleTracks() const
	{
		return _subtitleTrack;
	}

	void OneClickPostprocessingProperties::setSubtitleTracks(const QVector<OneClickStream*> &value)
	{
		_subtitleTrack = value;
	}

	const QString &OneClickPostprocessingProperties::getVideoFileToMux() const
	{
		return _videoFileToMux;
	}

	void OneClickPostprocessingProperties::setVideoFileToMux(const QString &value)
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

	const QVector<OneClickFilesToProcess*> &OneClickPostprocessingProperties::getFilesToProcess() const
	{
		return _filesToProcess;
	}

	void OneClickPostprocessingProperties::setFilesToProcess(const QVector<OneClickFilesToProcess*> &value)
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
