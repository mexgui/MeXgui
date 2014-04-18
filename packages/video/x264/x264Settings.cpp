#include "x264Settings.h"




//using namespace System::Collections::Generic;

//using namespace System::Xml::Serialization;

namespace MeXgui
{

QString x264Settings::ID = "x264";
const x264PsyTuningModes x264Settings::SupportedPsyTuningModes[7] = {NONE, ANIMATION, FILM, GRAIN, STILLIMAGE, PSNR, SSIM};

	void x264Settings::setAdjustedNbThreads(int nbThreads)
	{
		VideoCodecSettings::setAdjustedNbThreads(0);
	}

	void x264Settings::FixFileNames(QMap<QString, QString> &substitutionTable)
	{
		VideoCodecSettings::FixFileNames(substitutionTable);
		if (getQuantizerMatrixType() == 2) // CQM
		{
			if (substitutionTable.find(getQuantizerMatrix()) != substitutionTable.end())
				setQuantizerMatrix(substitutionTable[getQuantizerMatrix()]);
		}
	}

	const QString &x264Settings::getRequiredFiles() const
	{
		QVector<QString> list = QVector<QString>(VideoCodecSettings::getRequiredFiles());
		if (getQuantizerMatrixType() == 2) // Custom profile
			list.push_back(getQuantizerMatrix());
		return list.ToArray();
	}

	x264Settings::x264Settings() : VideoCodecSettings(ID, VideoEncoderType::X264)
	{
		x264DeviceList = x264Device::CreateDeviceList();
		preset = medium;
		psyTuningMode = NONE;
		deadZoneInter = 21;
		deadZoneIntra = 11;
		noFastPSkip = false;
		ssimCalc = false;
		psnrCalc = false;
		setEncodingMode(9);
		setBitrateQuantizer(23);
		setKeyframeInterval(250);
		nbRefFrames = 3;
		noMixedRefs = false;
		setNbBframes(3);
		deblock = true;
		alphaDeblock = 0;
		betaDeblock = 0;
		cabac = true;
		weightedBPrediction = true;
		weightedPPrediction = 2;
		NewadaptiveBFrames = 1;
		bFramePyramid = 2;
		subPelRefinement = 7;
		psyRDO = decimal(1.0);
		psyTrellis = decimal(0.0);
		macroBlockOptions = 3;
		chromaME = true;
		p8x8mv = true;
		b8x8mv = true;
		p4x4mv = false;
		i4x4mv = true;
		i8x8mv = true;
		setMinQuantizer(0);
		setMaxQuantizer(69);
		maxQuantDelta = 4;
		setCreditsQuantizer(decimal(40));
		ipFactor = decimal(1.4);
		pbFactor = decimal(1.3);
		chromaQPOffset = decimal(0.0);
		vbvBufferSize = 0;
		vbvMaxBitrate = 0;
		vbvInitialBuffer = decimal(0.9);
		bitrateVariance = 1;
		quantCompression = decimal(0.6);
		tempComplexityBlur = 20;
		tempQuanBlurCC = decimal(0.5);
		bframePredictionMode = 1;
		scdSensitivity = decimal(40);
		bframeBias = decimal(0);
		meType = 1;
		meRange = 16;
		setNbThreads(0);
		minGOPSize = 25;
		adaptiveDCT = true;
		quantizerMatrix = "";
		quantizerMatrixType = 0; // none
		x264Trellis = 1;
		VideoCodecSettings::setMaxNumberOfPasses(3);
		AQMode = 1;
		AQStrength = decimal(1.0);
		useQPFile = false;
		qpfile = "";
		FullRange = false;
		range = "auto";
		advSet = false;
		lookahead = 40;
		noMBTree = true;
		threadInput = true;
		noPsy = false;
		scenecut = true;
		slicesnb = 0;
		maxSliceSyzeBytes = 0;
		maxSliceSyzeMBs = 0;
		x264Nalhrd = 0;
		x264PullDown = 0;
		sampleAR = 0;
		colorMatrix = 0;
		transfer = 0;
		colorPrim = 0;
		x264Aud = false;
		profile = 3; // Autoguess. High if using default options.
		avcLevel = AVCLevels::L_UNRESTRICTED;
		x264SlowFirstpass = false;
		openGop = "False";
		picStruct = false;
		fakeInterlaced = false;
		nonDeterministic = false;
		interlacedMode = progressive;
		targetDevice = x264DeviceList[0];
		blurayCompat = false;
		_gopCalculation = 1;
		quantizerCrf = 23;
		tuneFastDecode = tuneZeroLatency = false;
		stitchable = false;
		x26410Bits = false;
	}

	const MeXgui::x264Settings::x264PresetLevelModes &x264Settings::getx264PresetLevel() const
	{
		return preset;
	}

	void x264Settings::setx264PresetLevel(const x264PresetLevelModes &value)
	{
		preset = value;
	}

	const QString &x264Settings::getx264Tuning() const
	{
		return "migrated";
	}

	void x264Settings::setx264Tuning(const QString &value)
	{
		if (value.Equals("migrated"))
			return;
		if (value.Equals("1"))
			psyTuningMode = FILM;
		if (value.Equals("2"))
			psyTuningMode = ANIMATION;
		if (value.Equals("3"))
			psyTuningMode = GRAIN;
		if (value.Equals("4"))
			psyTuningMode = PSNR;
		if (value.Equals("5"))
			psyTuningMode = SSIM;
		if (value.Equals("6"))
			tuneFastDecode = true;
	}

	const MeXgui::x264Settings::x264PsyTuningModes &x264Settings::getx264PsyTuning() const
	{
		return psyTuningMode;
	}

	void x264Settings::setx264PsyTuning(const x264PsyTuningModes &value)
	{
		psyTuningMode = value;
	}

	const decimal &x264Settings::getQuantizerCRF() const
	{
		return quantizerCrf;
	}

	void x264Settings::setQuantizerCRF(const decimal &value)
	{
		quantizerCrf = value;
	}

	const MeXgui::x264Settings::x264InterlacedModes &x264Settings::getInterlacedMode() const
	{
		return interlacedMode;
	}

	void x264Settings::setInterlacedMode(const x264InterlacedModes &value)
	{
		interlacedMode = value;
	}

	const x264Device &x264Settings::getTargetDevice() const
	{
		return targetDevice;
	}

	void x264Settings::setTargetDevice(const x264Device &value)
	{
		targetDevice = value;
	}

	const QString &x264Settings::getTargetDeviceXML() const
	{
		return StringConverterHelper::toString(targetDevice->getID());
	}

	void x264Settings::setTargetDeviceXML(const QString &value)
	{
		if (value.Equals("1")) // device profile 1 has been replaced with 7
			value = "7";
		else if (value.Equals("6")) // device profile 6 has been replaced with 8
			value = "8";
		else if (value.Equals("10") || value.Equals("11")) // device profiles 10/11 have been replaced with 9
			value = "9";

		// only support one device at the moment
		targetDevice = x264DeviceList[0];
		for (QVector<x264Device*>::const_iterator oDevice = x264DeviceList.begin(); oDevice != x264DeviceList.end(); ++oDevice)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			if ((*oDevice)->getID()->ToString()->Equals(value.Split(',')[0], StringComparison::CurrentCultureIgnoreCase))
			{
				targetDevice = *oDevice;
				break;
			}
		}
	}

	const bool &x264Settings::getBlurayCompat() const
	{
		return blurayCompat;
	}

	void x264Settings::setBlurayCompat(const bool &value)
	{
		blurayCompat = value;
	}

	const QString &x264Settings::getBlurayCompatXML() const
	{
		return StringConverterHelper::toString(blurayCompat);
	}

	void x264Settings::setBlurayCompatXML(const QString &value)
	{
		if (value.Equals("True", StringComparison::CurrentCultureIgnoreCase))
			blurayCompat = true;
		else
			blurayCompat = false;
	}

	const bool &x264Settings::getNoDCTDecimate() const
	{
		return noDctDecimate;
	}

	void x264Settings::setNoDCTDecimate(const bool &value)
	{
		noDctDecimate = value;
	}

	const bool &x264Settings::getPSNRCalculation() const
	{
		return psnrCalc;
	}

	void x264Settings::setPSNRCalculation(const bool &value)
	{
		psnrCalc = value;
	}

	const bool &x264Settings::getNoFastPSkip() const
	{
		return noFastPSkip;
	}

	void x264Settings::setNoFastPSkip(const bool &value)
	{
		noFastPSkip = value;
	}

	const int &x264Settings::getNoiseReduction() const
	{
		return noiseReduction;
	}

	void x264Settings::setNoiseReduction(const int &value)
	{
		noiseReduction = value;
	}

	const bool &x264Settings::getNoMixedRefs() const
	{
		return noMixedRefs;
	}

	void x264Settings::setNoMixedRefs(const bool &value)
	{
		noMixedRefs = value;
	}

	const int &x264Settings::getX264Trellis() const
	{
		return x264Trellis;
	}

	void x264Settings::setX264Trellis(const int &value)
	{
		x264Trellis = value;
	}

	const int &x264Settings::getNbRefFrames() const
	{
		return nbRefFrames;
	}

	void x264Settings::setNbRefFrames(const int &value)
	{
		nbRefFrames = value;
	}

	const int &x264Settings::getAlphaDeblock() const
	{
		return alphaDeblock;
	}

	void x264Settings::setAlphaDeblock(const int &value)
	{
		alphaDeblock = value;
	}

	const int &x264Settings::getBetaDeblock() const
	{
		return betaDeblock;
	}

	void x264Settings::setBetaDeblock(const int &value)
	{
		betaDeblock = value;
	}

	const int &x264Settings::getSubPelRefinement() const
	{
		return subPelRefinement;
	}

	void x264Settings::setSubPelRefinement(const int &value)
	{
		subPelRefinement = value;
	}

	const int &x264Settings::getMaxQuantDelta() const
	{
		return maxQuantDelta;
	}

	void x264Settings::setMaxQuantDelta(const int &value)
	{
		maxQuantDelta = value;
	}

	const int &x264Settings::getTempQuantBlur() const
	{
		return tempQuantBlur;
	}

	void x264Settings::setTempQuantBlur(const int &value)
	{
		tempQuantBlur = value;
	}

	const int &x264Settings::getBframePredictionMode() const
	{
		return bframePredictionMode;
	}

	void x264Settings::setBframePredictionMode(const int &value)
	{
		bframePredictionMode = value;
	}

	const int &x264Settings::getVBVBufferSize() const
	{
		return vbvBufferSize;
	}

	void x264Settings::setVBVBufferSize(const int &value)
	{
		vbvBufferSize = value;
	}

	const int &x264Settings::getVBVMaxBitrate() const
	{
		return vbvMaxBitrate;
	}

	void x264Settings::setVBVMaxBitrate(const int &value)
	{
		vbvMaxBitrate = value;
	}

	const int &x264Settings::getMEType() const
	{
		return meType;
	}

	void x264Settings::setMEType(const int &value)
	{
		meType = value;
	}

	const int &x264Settings::getMERange() const
	{
		return meRange;
	}

	void x264Settings::setMERange(const int &value)
	{
		meRange = value;
	}

	const int &x264Settings::getMinGOPSize() const
	{
		return minGOPSize;
	}

	void x264Settings::setMinGOPSize(const int &value)
	{
		minGOPSize = value;
	}

	const decimal &x264Settings::getIPFactor() const
	{
		return ipFactor;
	}

	void x264Settings::setIPFactor(const decimal &value)
	{
		ipFactor = value;
	}

	const decimal &x264Settings::getPBFactor() const
	{
		return pbFactor;
	}

	void x264Settings::setPBFactor(const decimal &value)
	{
		pbFactor = value;
	}

	const decimal &x264Settings::getChromaQPOffset() const
	{
		return chromaQPOffset;
	}

	void x264Settings::setChromaQPOffset(const decimal &value)
	{
		chromaQPOffset = value;
	}

	const decimal &x264Settings::getVBVInitialBuffer() const
	{
		return vbvInitialBuffer;
	}

	void x264Settings::setVBVInitialBuffer(const decimal &value)
	{
		vbvInitialBuffer = value;
	}

	const decimal &x264Settings::getBitrateVariance() const
	{
		return bitrateVariance;
	}

	void x264Settings::setBitrateVariance(const decimal &value)
	{
		bitrateVariance = value;
	}

	const decimal &x264Settings::getQuantCompression() const
	{
		return quantCompression;
	}

	void x264Settings::setQuantCompression(const decimal &value)
	{
		quantCompression = value;
	}

	const decimal &x264Settings::getTempComplexityBlur() const
	{
		return tempComplexityBlur;
	}

	void x264Settings::setTempComplexityBlur(const decimal &value)
	{
		tempComplexityBlur = value;
	}

	const decimal &x264Settings::getTempQuanBlurCC() const
	{
		return tempQuanBlurCC;
	}

	void x264Settings::setTempQuanBlurCC(const decimal &value)
	{
		tempQuanBlurCC = value;
	}

	const decimal &x264Settings::getSCDSensitivity() const
	{
		return scdSensitivity;
	}

	void x264Settings::setSCDSensitivity(const decimal &value)
	{
		scdSensitivity = value;
	}

	const decimal &x264Settings::getBframeBias() const
	{
		return bframeBias;
	}

	void x264Settings::setBframeBias(const decimal &value)
	{
		bframeBias = value;
	}

	const decimal &x264Settings::getPsyRDO() const
	{
		return psyRDO;
	}

	void x264Settings::setPsyRDO(const decimal &value)
	{
		psyRDO = value;
	}

	const decimal &x264Settings::getPsyTrellis() const
	{
		return psyTrellis;
	}

	void x264Settings::setPsyTrellis(const decimal &value)
	{
		psyTrellis = value;
	}

	const bool &x264Settings::getDeblock() const
	{
		return deblock;
	}

	void x264Settings::setDeblock(const bool &value)
	{
		deblock = value;
	}

	const bool &x264Settings::getCabac() const
	{
		return cabac;
	}

	void x264Settings::setCabac(const bool &value)
	{
		cabac = value;
	}

	const bool &x264Settings::getUseQPFile() const
	{
		return useQPFile;
	}

	void x264Settings::setUseQPFile(const bool &value)
	{
		useQPFile = value;
	}

	const bool &x264Settings::getWeightedBPrediction() const
	{
		return weightedBPrediction;
	}

	void x264Settings::setWeightedBPrediction(const bool &value)
	{
		weightedBPrediction = value;
	}

	const int &x264Settings::getWeightedPPrediction() const
	{
		return weightedPPrediction;
	}

	void x264Settings::setWeightedPPrediction(const int &value)
	{
		weightedPPrediction = value;
	}

	const int &x264Settings::getNewAdaptiveBFrames() const
	{
		return NewadaptiveBFrames;
	}

	void x264Settings::setNewAdaptiveBFrames(const int &value)
	{
		NewadaptiveBFrames = value;
	}

	const int &x264Settings::getx264BFramePyramid() const
	{
		return bFramePyramid;
	}

	void x264Settings::setx264BFramePyramid(const int &value)
	{
		bFramePyramid = value;
	}

	const int &x264Settings::getx264GOPCalculation() const
	{
		return _gopCalculation;
	}

	void x264Settings::setx264GOPCalculation(const int &value)
	{
		_gopCalculation = value;
	}

	const bool &x264Settings::getChromaME() const
	{
		return chromaME;
	}

	void x264Settings::setChromaME(const bool &value)
	{
		chromaME = value;
	}

	const int &x264Settings::getMacroBlockOptions() const
	{
		return macroBlockOptions;
	}

	void x264Settings::setMacroBlockOptions(const int &value)
	{
		macroBlockOptions = value;
	}

	const bool &x264Settings::getP8x8mv() const
	{
		return p8x8mv;
	}

	void x264Settings::setP8x8mv(const bool &value)
	{
		p8x8mv = value;
	}

	const bool &x264Settings::getB8x8mv() const
	{
		return b8x8mv;
	}

	void x264Settings::setB8x8mv(const bool &value)
	{
		b8x8mv = value;
	}

	const bool &x264Settings::getI4x4mv() const
	{
		return i4x4mv;
	}

	void x264Settings::setI4x4mv(const bool &value)
	{
		i4x4mv = value;
	}

	const bool &x264Settings::getI8x8mv() const
	{
		return i8x8mv;
	}

	void x264Settings::setI8x8mv(const bool &value)
	{
		i8x8mv = value;
	}

	const bool &x264Settings::getP4x4mv() const
	{
		return p4x4mv;
	}

	void x264Settings::setP4x4mv(const bool &value)
	{
		p4x4mv = value;
	}

	const bool &x264Settings::getAdaptiveDCT() const
	{
		return adaptiveDCT;
	}

	void x264Settings::setAdaptiveDCT(const bool &value)
	{
		adaptiveDCT = value;
	}

	const bool &x264Settings::getSSIMCalculation() const
	{
		return ssimCalc;
	}

	void x264Settings::setSSIMCalculation(const bool &value)
	{
		ssimCalc = value;
	}

	const bool &x264Settings::getStitchAble() const
	{
		return stitchable;
	}

	void x264Settings::setStitchAble(const bool &value)
	{
		stitchable = value;
	}

	const QString &x264Settings::getQuantizerMatrix() const
	{
		return quantizerMatrix;
	}

	void x264Settings::setQuantizerMatrix(const QString &value)
	{
		quantizerMatrix = value;
	}

	const int &x264Settings::getQuantizerMatrixType() const
	{
		return quantizerMatrixType;
	}

	void x264Settings::setQuantizerMatrixType(const int &value)
	{
		quantizerMatrixType = value;
	}

	const int &x264Settings::getDeadZoneInter() const
	{
		return deadZoneInter;
	}

	void x264Settings::setDeadZoneInter(const int &value)
	{
		deadZoneInter = value;
	}

	const int &x264Settings::getDeadZoneIntra() const
	{
		return deadZoneIntra;
	}

	void x264Settings::setDeadZoneIntra(const int &value)
	{
		deadZoneIntra = value;
	}

	const bool &x264Settings::getX26410Bits() const
	{
		return x26410Bits;
	}

	void x264Settings::setX26410Bits(const bool &value)
	{
		x26410Bits = value;
	}

	const QString &x264Settings::getOpenGop() const
	{
		return openGop;
	}

	void x264Settings::setOpenGop(const QString &value)
	{
		if (value.Equals("True", StringComparison::CurrentCultureIgnoreCase) || value.Equals("1"))
			openGop = "True";
		else if (value.Equals("2"))
		{
			openGop = "True";
			blurayCompat = true;
		}
		else
			openGop = "False";
	}

	const bool &x264Settings::getOpenGopValue() const
	{
		if (openGop.Equals("True", StringComparison::CurrentCultureIgnoreCase))
			return true;
		else
			return false;
	}

	void x264Settings::setOpenGopValue(const bool &value)
	{
		openGop = StringConverterHelper::toString(value);
	}

	const int &x264Settings::getX264PullDown() const
	{
		return x264PullDown;
	}

	void x264Settings::setX264PullDown(const int &value)
	{
		x264PullDown = value;
	}

	const int &x264Settings::getSampleAR() const
	{
		return sampleAR;
	}

	void x264Settings::setSampleAR(const int &value)
	{
		sampleAR = value;
	}

	const int &x264Settings::getColorMatrix() const
	{
		return colorMatrix;
	}

	void x264Settings::setColorMatrix(const int &value)
	{
		colorMatrix = value;
	}

	const int &x264Settings::getColorPrim() const
	{
		return colorPrim;
	}

	void x264Settings::setColorPrim(const int &value)
	{
		colorPrim = value;
	}

	const int &x264Settings::getTransfer() const
	{
		return transfer;
	}

	void x264Settings::setTransfer(const int &value)
	{
		transfer = value;
	}

	const int &x264Settings::getAQmode() const
	{
		return AQMode;
	}

	void x264Settings::setAQmode(const int &value)
	{
		AQMode = value;
	}

	const decimal &x264Settings::getAQstrength() const
	{
		return AQStrength;
	}

	void x264Settings::setAQstrength(const decimal &value)
	{
		AQStrength = value;
	}

	const QString &x264Settings::getQPFile() const
	{
		return qpfile;
	}

	void x264Settings::setQPFile(const QString &value)
	{
		qpfile = value;
	}

	const QString &x264Settings::getRange() const
	{
		if (!range.Equals("pc") && !range.Equals("tv"))
			return "auto";
		else
			return range;
	}

	void x264Settings::setRange(const QString &value)
	{
		range = value;
	}

	const bool &x264Settings::getx264AdvancedSettings() const
	{
		return advSet;
	}

	void x264Settings::setx264AdvancedSettings(const bool &value)
	{
		advSet = value;
	}

	const int &x264Settings::getLookahead() const
	{
		return lookahead;
	}

	void x264Settings::setLookahead(const int &value)
	{
		lookahead = value;
	}

	const bool &x264Settings::getNoMBTree() const
	{
		return noMBTree;
	}

	void x264Settings::setNoMBTree(const bool &value)
	{
		noMBTree = value;
	}

	const bool &x264Settings::getThreadInput() const
	{
		return threadInput;
	}

	void x264Settings::setThreadInput(const bool &value)
	{
		threadInput = value;
	}

	const bool &x264Settings::getNoPsy() const
	{
		return noPsy;
	}

	void x264Settings::setNoPsy(const bool &value)
	{
		noPsy = value;
	}

	const bool &x264Settings::getScenecut() const
	{
		return scenecut;
	}

	void x264Settings::setScenecut(const bool &value)
	{
		scenecut = value;
	}

	const int &x264Settings::getNalhrd() const
	{
		return x264Nalhrd;
	}

	void x264Settings::setNalhrd(const int &value)
	{
		x264Nalhrd = value;
	}

	const bool &x264Settings::getX264Aud() const
	{
		return x264Aud;
	}

	void x264Settings::setX264Aud(const bool &value)
	{
		x264Aud = value;
	}

	const bool &x264Settings::getX264SlowFirstpass() const
	{
		return x264SlowFirstpass;
	}

	void x264Settings::setX264SlowFirstpass(const bool &value)
	{
		x264SlowFirstpass = value;
	}

	const bool &x264Settings::getPicStruct() const
	{
		return picStruct;
	}

	void x264Settings::setPicStruct(const bool &value)
	{
		picStruct = value;
	}

	const bool &x264Settings::getFakeInterlaced() const
	{
		return fakeInterlaced;
	}

	void x264Settings::setFakeInterlaced(const bool &value)
	{
		fakeInterlaced = value;
	}

	const bool &x264Settings::getNonDeterministic() const
	{
		return nonDeterministic;
	}

	void x264Settings::setNonDeterministic(const bool &value)
	{
		nonDeterministic = value;
	}

	const int &x264Settings::getSlicesNb() const
	{
		return slicesnb;
	}

	void x264Settings::setSlicesNb(const int &value)
	{
		slicesnb = value;
	}

	const int &x264Settings::getMaxSliceSyzeBytes() const
	{
		return maxSliceSyzeBytes;
	}

	void x264Settings::setMaxSliceSyzeBytes(const int &value)
	{
		maxSliceSyzeBytes = value;
	}

	const int &x264Settings::getMaxSliceSyzeMBs() const
	{
		return maxSliceSyzeMBs;
	}

	void x264Settings::setMaxSliceSyzeMBs(const int &value)
	{
		maxSliceSyzeMBs = value;
	}

	const int &x264Settings::getProfile() const
	{
		return profile;
	}

	void x264Settings::setProfile(const int &value)
	{
		profile = value;
	}

	const QString &x264Settings::getLevel() const
	{
		return "migrated";
	}

	void x264Settings::setLevel(const QString &value)
	{
		if (value.Equals("migrated"))
			return;

		if (value.Equals("0"))
			avcLevel = AVCLevels::L_10;
		if (value.Equals("1"))
			avcLevel = AVCLevels::L_11;
		if (value.Equals("2"))
			avcLevel = AVCLevels::L_12;
		if (value.Equals("3"))
			avcLevel = AVCLevels::L_13;
		if (value.Equals("4"))
			avcLevel = AVCLevels::L_20;
		if (value.Equals("5"))
			avcLevel = AVCLevels::L_21;
		if (value.Equals("6"))
			avcLevel = AVCLevels::L_22;
		if (value.Equals("7"))
			avcLevel = AVCLevels::L_30;
		if (value.Equals("8"))
			avcLevel = AVCLevels::L_31;
		if (value.Equals("9"))
			avcLevel = AVCLevels::L_32;
		if (value.Equals("10"))
			avcLevel = AVCLevels::L_40;
		if (value.Equals("11"))
			avcLevel = AVCLevels::L_41;
		if (value.Equals("12"))
			avcLevel = AVCLevels::L_42;
		if (value.Equals("13"))
			avcLevel = AVCLevels::L_50;
		if (value.Equals("14"))
			avcLevel = AVCLevels::L_51;
		if (value.Equals("15"))
			avcLevel = AVCLevels::L_UNRESTRICTED;
	}

	const AVCLevels::Levels &x264Settings::getAVCLevel() const
	{
		return avcLevel;
	}

	void x264Settings::setAVCLevel(const AVCLevels::Levels &value)
	{
		avcLevel = value;
	}

	const bool &x264Settings::getTuneFastDecode() const
	{
		return tuneFastDecode;
	}

	void x264Settings::setTuneFastDecode(const bool &value)
	{
		tuneFastDecode = value;
	}

	const bool &x264Settings::getTuneZeroLatency() const
	{
		return tuneZeroLatency;
	}

	void x264Settings::setTuneZeroLatency(const bool &value)
	{
		tuneZeroLatency = value;
	}

	const bool &x264Settings::getUsesSAR() const
	{
		return true;
	}

	bool x264Settings::IsAltered(x264Settings *otherSettings)
	{
		if (this->getNewAdaptiveBFrames() != otherSettings->getNewAdaptiveBFrames() || this->getAdaptiveDCT() != otherSettings->getAdaptiveDCT() || this->getAlphaDeblock() != otherSettings->getAlphaDeblock() || this->getNoFastPSkip() != otherSettings->getNoFastPSkip() || this->getB8x8mv() != otherSettings->getB8x8mv() || this->getBetaDeblock() != otherSettings->getBetaDeblock() || this->getBframeBias() != otherSettings->getBframeBias() || this->getBframePredictionMode() != otherSettings->getBframePredictionMode() || this->getx264BFramePyramid() != otherSettings->getx264BFramePyramid() || this->getx264GOPCalculation() != otherSettings->getx264GOPCalculation() || this->getBitrateVariance() != otherSettings->getBitrateVariance() || this->getPsyRDO() != otherSettings->getPsyRDO() || this->getPsyTrellis() != otherSettings->getPsyTrellis() || this->getCabac() != otherSettings->getCabac() || this->getChromaME() != otherSettings->getChromaME() || this->getChromaQPOffset() != otherSettings->getChromaQPOffset() || this->getCustomEncoderOptions() != otherSettings->getCustomEncoderOptions() || this->getDeblock() != otherSettings->getDeblock() || this->getEncodingMode() != otherSettings->getEncodingMode() || this->getI4x4mv() != otherSettings->getI4x4mv() || this->getI8x8mv() != otherSettings->getI8x8mv() || this->getIPFactor() != otherSettings->getIPFactor() || this->getKeyframeInterval() != otherSettings->getKeyframeInterval() || this->getAVCLevel() != otherSettings->getAVCLevel() || this->getMaxQuantDelta() != otherSettings->getMaxQuantDelta() || this->getMaxQuantizer() != otherSettings->getMaxQuantizer() || this->getMERange() != otherSettings->getMERange() || this->getMEType() != otherSettings->getMEType() || this->getMinGOPSize() != otherSettings->getMinGOPSize() || this->getMinQuantizer() != otherSettings->getMinQuantizer() || this->getNoMixedRefs() != otherSettings->getNoMixedRefs() || this->getNbBframes() != otherSettings->getNbBframes() || this->getNbRefFrames() != otherSettings->getNbRefFrames() || this->noiseReduction != otherSettings->noiseReduction || this->getP4x4mv() != otherSettings->getP4x4mv() || this->getP8x8mv() != otherSettings->getP8x8mv() || this->getPBFactor() != otherSettings->getPBFactor() || this->getProfile() != otherSettings->getProfile() || this->getQPel() != otherSettings->getQPel() || this->getQuantCompression() != otherSettings->getQuantCompression() || this->getQuantizerMatrix() != otherSettings->getQuantizerMatrix() || this->getQuantizerMatrixType() != otherSettings->getQuantizerMatrixType() || this->getSCDSensitivity() != otherSettings->getSCDSensitivity() || this->getSubPelRefinement() != otherSettings->getSubPelRefinement() || this->getTempComplexityBlur() != otherSettings->getTempComplexityBlur() || this->getTempQuanBlurCC() != otherSettings->getTempQuanBlurCC() || this->getTempQuantBlur() != otherSettings->getTempQuantBlur() || this->getTrellis() != otherSettings->getTrellis() || this->x264SlowFirstpass != otherSettings->x264SlowFirstpass || this->getV4MV() != otherSettings->getV4MV() || this->getVBVBufferSize() != otherSettings->getVBVBufferSize() || this->getVBVInitialBuffer() != otherSettings->getVBVInitialBuffer() || this->getVBVMaxBitrate() != otherSettings->getVBVMaxBitrate() || this->getWeightedBPrediction() != otherSettings->getWeightedBPrediction() || this->getWeightedPPrediction() != otherSettings->getWeightedPPrediction() || this->getX264Trellis() != otherSettings->getX264Trellis() || this->getAQmode() != otherSettings->getAQmode() || this->getAQstrength() != otherSettings->getAQstrength() || this->getUseQPFile() != otherSettings->getUseQPFile() || this->getQPFile() != otherSettings->getQPFile() || this->FullRange != otherSettings->FullRange || this->getRange() != otherSettings->getRange() || this->getMacroBlockOptions() != otherSettings->getMacroBlockOptions() || this->getx264PresetLevel() != otherSettings->getx264PresetLevel() || this->getx264PsyTuning() != otherSettings->getx264PsyTuning() || this->getx264AdvancedSettings() != otherSettings->getx264AdvancedSettings() || this->getLookahead() != otherSettings->getLookahead() || this->getNoMBTree() != otherSettings->getNoMBTree() || this->getThreadInput() != otherSettings->getThreadInput() || this->getNoPsy() != otherSettings->getNoPsy() || this->getScenecut() != otherSettings->getScenecut() || this->getSlicesNb() != otherSettings->getSlicesNb() || this->getNalhrd() != otherSettings->getNalhrd() || this->getX264Aud() != otherSettings->getX264Aud() || this->getOpenGop() != otherSettings->getOpenGop() || this->getX264PullDown() != otherSettings->getX264PullDown() || this->getSampleAR() != otherSettings->getSampleAR() || this->getColorMatrix() != otherSettings->getColorMatrix() || this->getTransfer() != otherSettings->getTransfer() || this->getColorPrim() != otherSettings->getColorPrim() || this->getPicStruct() != otherSettings->getPicStruct() || this->getFakeInterlaced() != otherSettings->getFakeInterlaced() || this->getNonDeterministic() != otherSettings->getNonDeterministic() || this->getMaxSliceSyzeBytes() != otherSettings->getMaxSliceSyzeBytes() || this->getInterlacedMode() != otherSettings->getInterlacedMode() || this->getTargetDevice()->getID() != otherSettings->getTargetDevice()->getID() || this->getBlurayCompat() != otherSettings->getBlurayCompat() || this->getMaxSliceSyzeMBs() != otherSettings->getMaxSliceSyzeMBs() || this->tuneFastDecode != otherSettings->tuneFastDecode || this->tuneZeroLatency != otherSettings->tuneZeroLatency || this->getX26410Bits() != otherSettings->getX26410Bits())
			return true;
		else
			return false;
	}

	void x264Settings::doTriStateAdjustment()
	{
		switch (getProfile())
		{
			case 0:
				setCabac(false);
				setNbBframes(0);
				setNewAdaptiveBFrames(0);
				setx264BFramePyramid(0);
				setI8x8mv(false);
				setAdaptiveDCT(false);
				setBframeBias(0);
				setBframePredictionMode(1); // default
				setQuantizerMatrixType(0); // no matrix
				setQuantizerMatrix("");
				setWeightedPPrediction(0);
				break;
			case 1:
				setx264BFramePyramid(2);
				setI8x8mv(false);
				setAdaptiveDCT(false);
				setQuantizerMatrixType(0); // no matrix
				setQuantizerMatrix("");
				setWeightedPPrediction(0);
				break;
			case 2:
				setx264BFramePyramid(2);
				setWeightedPPrediction(1);
				break;
		}
		if (getEncodingMode() != 2 && getEncodingMode() != 5)
			x264SlowFirstpass = false;
		if (getNbBframes() == 0)
		{
			setNewAdaptiveBFrames(0);
			setWeightedBPrediction(false);
		}
		if (!getCabac()) // trellis requires CABAC
			setX264Trellis(0);
		if (!getP8x8mv()) // p8x8 requires p4x4
			setP4x4mv(false);
	}

	int x264Settings::GetDefaultNumberOfRefFrames(x264PresetLevelModes oPreset, x264PsyTuningModes oTuningMode, x264Device *oDevice, AVCLevels::Levels avcLevel, bool blurayCompat)
	{
		return GetDefaultNumberOfRefFrames(oPreset, oTuningMode, oDevice, avcLevel, blurayCompat, -1, -1);
	}

	int x264Settings::GetDefaultNumberOfRefFrames(x264PresetLevelModes oPreset, x264PsyTuningModes oTuningMode, x264Device *oDevice, AVCLevels::Levels avcLevel, bool blurayCompat, int hRes, int vRes)
	{
		int iDefaultSetting = 1;
		switch (oPreset)
		{
			case x264Settings::ultrafast:
			case x264Settings::superfast:
			case x264Settings::veryfast:
				iDefaultSetting = 1;
				break;
			case x264Settings::faster:
			case x264Settings::fast:
				iDefaultSetting = 2;
				break;
			case x264Settings::medium:
				iDefaultSetting = 3;
				break;
			case x264Settings::slow:
				iDefaultSetting = 5;
				break;
			case x264Settings::slower:
				iDefaultSetting = 8;
				break;
			case x264Settings::veryslow:
			case x264Settings::placebo:
				iDefaultSetting = 16;
				break;
		}
		if (oTuningMode == ANIMATION && iDefaultSetting > 1)
			iDefaultSetting *= 2;
		if (iDefaultSetting > 16)
			iDefaultSetting = 16;
		if (blurayCompat)
			iDefaultSetting = __min(6, iDefaultSetting);
		if (oDevice != 0 && oDevice->getReferenceFrames() > -1)
			iDefaultSetting = __min(oDevice->getReferenceFrames(), iDefaultSetting);
		if (hRes > 0 && vRes > 0)
		{
			int iMaxRefForLevel = MeXgui::packages::video::x264::x264SettingsHandler::getMaxRefForLevel(avcLevel, hRes, vRes);
			if (iMaxRefForLevel > -1 && iMaxRefForLevel < iDefaultSetting)
				iDefaultSetting = iMaxRefForLevel;
		}
		return iDefaultSetting;
	}

	int x264Settings::GetDefaultNumberOfBFrames(x264PresetLevelModes oPresetLevel, x264PsyTuningModes oTuningMode, bool bTuneZeroLatency, int oAVCProfile, x264Device *oDevice, bool blurayCompat)
	{
		int iDefaultSetting = 0;
		if (oAVCProfile == 0) // baseline
			return iDefaultSetting;
		if (bTuneZeroLatency)
			return iDefaultSetting;

		switch (oPresetLevel)
		{
			case x264Settings::ultrafast:
				iDefaultSetting = 0;
				break;
			case x264Settings::superfast:
			case x264Settings::veryfast:
			case x264Settings::faster:
			case x264Settings::fast:
			case x264Settings::medium:
			case x264Settings::slow:
			case x264Settings::slower:
				iDefaultSetting = 3;
				break;
			case x264Settings::veryslow:
				iDefaultSetting = 8;
				break;
			case x264Settings::placebo:
				iDefaultSetting = 16;
				break;
		}
		if (oTuningMode == ANIMATION)
			iDefaultSetting += 2;
		if (iDefaultSetting > 16)
			iDefaultSetting = 16;
		if (blurayCompat)
			iDefaultSetting = __min(3, iDefaultSetting);
		if (oDevice != 0 && oDevice->getBFrames() > -1)
			return __min(oDevice->getBFrames(), iDefaultSetting);
		else
			return iDefaultSetting;
	}

	int x264Settings::GetDefaultNumberOfWeightp(x264PresetLevelModes oPresetLevel, bool bFastDecode, int oAVCProfile, bool bBlurayCompat)
	{
		if (oAVCProfile == 0) // baseline
			return 0;
		if (bFastDecode) // Fast Decode
			return 0;

		int iDefaultSetting = 0;
		switch (oPresetLevel)
		{
			case x264Settings::ultrafast:
				iDefaultSetting = 0;
				break;
			case x264Settings::superfast:
			case x264Settings::veryfast:
			case x264Settings::faster:
			case x264Settings::fast:
				iDefaultSetting = 1;
				break;
			case x264Settings::medium:
			case x264Settings::slow:
			case x264Settings::slower:
			case x264Settings::veryslow:
			case x264Settings::placebo:
				iDefaultSetting = 2;
				break;
		}
		if (bBlurayCompat)
			return __min(iDefaultSetting, 1);
		else
			return iDefaultSetting;
	}

	int x264Settings::GetDefaultAQMode(x264PresetLevelModes oPresetLevel, x264PsyTuningModes oTuningMode)
	{
		if (oTuningMode == SSIM)
			return 2;

		if (oTuningMode == PSNR || oPresetLevel == x264Settings::ultrafast)
			return 0;

		return 1;
	}

	int x264Settings::GetDefaultRCLookahead(x264PresetLevelModes oPresetLevel, bool bTuneZeroLatency)
	{
		int iDefaultSetting = 0;
		if (bTuneZeroLatency)
			return iDefaultSetting;

		switch (oPresetLevel)
		{
			case x264Settings::ultrafast:
			case x264Settings::superfast:
				iDefaultSetting = 0;
				break;
			case x264Settings::veryfast:
				iDefaultSetting = 10;
				break;
			case x264Settings::faster:
				iDefaultSetting = 20;
				break;
			case x264Settings::fast:
				iDefaultSetting = 30;
				break;
			case x264Settings::medium:
				iDefaultSetting = 40;
				break;
			case x264Settings::slow:
				iDefaultSetting = 50;
				break;
			case x264Settings::slower:
			case x264Settings::veryslow:
			case x264Settings::placebo:
				iDefaultSetting = 60;
				break;
		}
		return iDefaultSetting;
	}
}
