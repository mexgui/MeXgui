#include "xvidSettings.h"




//using namespace System::Collections::Generic;

namespace MeXgui
{

const QString xvidSettings::ID = "XviD";
const QString xvidSettings::H263Matrix = "H.263";
const QString xvidSettings::MPEGMatrix = "MPEG";

	void xvidSettings::setAdjustedNbThreads(int nbThreads)
	{
		VideoCodecSettings::setAdjustedNbThreads(0);
	}

	const bool &xvidSettings::getIsCustomMatrix() const
	{
		return getQuantizerMatrix() != H263Matrix && getQuantizerMatrix() != MPEGMatrix && !getQuantizerMatrix().empty();
	}

	void xvidSettings::FixFileNames(QMap<QString, QString> &substitutionTable)
	{
		VideoCodecSettings::FixFileNames(substitutionTable);
		if (getIsCustomMatrix())
		{
			if (substitutionTable.find(getQuantizerMatrix()) != substitutionTable.end())
				setQuantizerMatrix(substitutionTable[getQuantizerMatrix()]);
		}
	}

	const QString &xvidSettings::getRequiredFiles() const
	{
		QVector<QString> list = QVector<QString>(VideoCodecSettings::getRequiredFiles());
		if (getIsCustomMatrix())
			list.push_back(getQuantizerMatrix());
		return list.ToArray();
	}

	const bool &xvidSettings::getUsesSAR() const
	{
		return true;
	}

	xvidSettings::xvidSettings() : VideoCodecSettings(ID, VideoEncoderType::XVID)
	{
		setEncodingMode(0);
		quantizer = 0;
		setBitrateQuantizer(700);
		setKeyframeInterval(300);
		setNbBframes(2);
		motionSearchPrecision = 6;
		vhqMode = 1;
		setMinQuantizer(2);
		setMaxQuantizer(31);
		minPQuant = 2;
		maxPQuant = 31;
		minBQuant = 2;
		maxBQuant = 31;
		setCreditsQuantizer(decimal(20));
		bQuantRatio = 150;
		bQuantOffset = 100;
		keyFrameBoost = 100;
		keyframeThreshold = 1;
		keyframeReduction = 20;
		overflowControlStrength = 5;
		maxOverflowImprovement = 5;
		maxOverflowDegradation = 5;
		highBitrateDegradation = 0;
		lowBitrateImprovement = 0;
		reactionDelayFactor = 16;
		averagingPeriod = 100;
		rateControlBuffer = 0;
		setTurbo(true);
		packedBitstream = false;
		setQPel(false);
		gmc = false;
		chromaMotion = true;
		closedGOP = true;
		setTrellis(true);
		bframeThreshold = decimal(0);
		interlaced = false;
		frameDropRatio = 0;
		bottomFieldFirst = true;
		customQuantizerMatrix = "";
		xvidProfile = 0;
		vbvBuffer = 0;
		vbvMaxRate = 0;
		vbvPeakRate = 0;
		VideoCodecSettings::setMaxNumberOfPasses(2);
		setFourCCs(getFourCCsForMPEG4ASP());
		hvsMasking = 1;
		setNbThreads(0);
	}

const QString xvidSettings::m_fourCCs[4] = {"XVID", "DIVX", "DX50", "MP4V"};

	const QString &xvidSettings::getFourCCsForMPEG4ASP() const
	{
		return m_fourCCs;
	}

	const decimal &xvidSettings::getQuantizer() const
	{
		return quantizer;
	}

	void xvidSettings::setQuantizer(const decimal &value)
	{
		quantizer = value;
	}

	const bool &xvidSettings::getTurbo() const
	{
		return turbo;
	}

	void xvidSettings::setTurbo(const bool &value)
	{
		turbo = value;
	}

	const int &xvidSettings::getMotionSearchPrecision() const
	{
		return motionSearchPrecision;
	}

	void xvidSettings::setMotionSearchPrecision(const int &value)
	{
		motionSearchPrecision = value;
	}

	const int &xvidSettings::getVHQMode() const
	{
		return vhqMode;
	}

	void xvidSettings::setVHQMode(const int &value)
	{
		vhqMode = value;
	}

	const int &xvidSettings::getMinPQuant() const
	{
		return minPQuant;
	}

	void xvidSettings::setMinPQuant(const int &value)
	{
		minPQuant = value;
	}

	const int &xvidSettings::getMaxPQuant() const
	{
		return maxPQuant;
	}

	void xvidSettings::setMaxPQuant(const int &value)
	{
		maxPQuant = value;
	}

	const int &xvidSettings::getMinBQuant() const
	{
		return minBQuant;
	}

	void xvidSettings::setMinBQuant(const int &value)
	{
		minBQuant = value;
	}

	const int &xvidSettings::getMaxBQuant() const
	{
		return maxBQuant;
	}

	void xvidSettings::setMaxBQuant(const int &value)
	{
		maxBQuant = value;
	}

	const int &xvidSettings::getBQuantRatio() const
	{
		return bQuantRatio;
	}

	void xvidSettings::setBQuantRatio(const int &value)
	{
		bQuantRatio = value;
	}

	const int &xvidSettings::getBQuantOffset() const
	{
		return bQuantOffset;
	}

	void xvidSettings::setBQuantOffset(const int &value)
	{
		bQuantOffset = value;
	}

	const int &xvidSettings::getKeyFrameBoost() const
	{
		return keyFrameBoost;
	}

	void xvidSettings::setKeyFrameBoost(const int &value)
	{
		keyFrameBoost = value;
	}

	const int &xvidSettings::getKeyframeThreshold() const
	{
		return keyframeThreshold;
	}

	void xvidSettings::setKeyframeThreshold(const int &value)
	{
		keyframeThreshold = value;
	}

	const int &xvidSettings::getKeyframeReduction() const
	{
		return keyframeReduction;
	}

	void xvidSettings::setKeyframeReduction(const int &value)
	{
		keyframeReduction = value;
	}

	const int &xvidSettings::getOverflowControlStrength() const
	{
		return overflowControlStrength;
	}

	void xvidSettings::setOverflowControlStrength(const int &value)
	{
		overflowControlStrength = value;
	}

	const int &xvidSettings::getMaxOverflowImprovement() const
	{
		return maxOverflowImprovement;
	}

	void xvidSettings::setMaxOverflowImprovement(const int &value)
	{
		maxOverflowImprovement = value;
	}

	const int &xvidSettings::getMaxOverflowDegradation() const
	{
		return maxOverflowDegradation;
	}

	void xvidSettings::setMaxOverflowDegradation(const int &value)
	{
		maxOverflowDegradation = value;
	}

	const int &xvidSettings::getHighBitrateDegradation() const
	{
		return highBitrateDegradation;
	}

	void xvidSettings::setHighBitrateDegradation(const int &value)
	{
		highBitrateDegradation = value;
	}

	const int &xvidSettings::getLowBitrateImprovement() const
	{
		return lowBitrateImprovement;
	}

	void xvidSettings::setLowBitrateImprovement(const int &value)
	{
		lowBitrateImprovement = value;
	}

	const int &xvidSettings::getReactionDelayFactor() const
	{
		return reactionDelayFactor;
	}

	void xvidSettings::setReactionDelayFactor(const int &value)
	{
		reactionDelayFactor = value;
	}

	const int &xvidSettings::getAveragingPeriod() const
	{
		return averagingPeriod;
	}

	void xvidSettings::setAveragingPeriod(const int &value)
	{
		averagingPeriod = value;
	}

	const int &xvidSettings::getFrameDropRatio() const
	{
		return frameDropRatio;
	}

	void xvidSettings::setFrameDropRatio(const int &value)
	{
		frameDropRatio = value;
	}

	const int &xvidSettings::getRateControlBuffer() const
	{
		return rateControlBuffer;
	}

	void xvidSettings::setRateControlBuffer(const int &value)
	{
		rateControlBuffer = value;
	}

	const int &xvidSettings::getXvidProfile() const
	{
		return xvidProfile;
	}

	void xvidSettings::setXvidProfile(const int &value)
	{
		xvidProfile = value;
	}

	const int &xvidSettings::getVbvPeakRate() const
	{
		return vbvPeakRate;
	}

	void xvidSettings::setVbvPeakRate(const int &value)
	{
		vbvPeakRate = value;
	}

	const int &xvidSettings::getVbvMaxRate() const
	{
		return vbvMaxRate;
	}

	void xvidSettings::setVbvMaxRate(const int &value)
	{
		vbvMaxRate = value;
	}

	const int &xvidSettings::getVbvBuffer() const
	{
		return vbvBuffer;
	}

	void xvidSettings::setVbvBuffer(const int &value)
	{
		vbvBuffer = value;
	}

	const bool &xvidSettings::getPackedBitstream() const
	{
		return packedBitstream;
	}

	void xvidSettings::setPackedBitstream(const bool &value)
	{
		packedBitstream = value;
	}

	const bool &xvidSettings::getGMC() const
	{
		return gmc;
	}

	void xvidSettings::setGMC(const bool &value)
	{
		gmc = value;
	}

	const bool &xvidSettings::getChromaMotion() const
	{
		return chromaMotion;
	}

	void xvidSettings::setChromaMotion(const bool &value)
	{
		chromaMotion = value;
	}

	const bool &xvidSettings::getClosedGOP() const
	{
		return closedGOP;
	}

	void xvidSettings::setClosedGOP(const bool &value)
	{
		closedGOP = value;
	}

	const bool &xvidSettings::getVHQForBframes() const
	{
		return vhqForBframes;
	}

	void xvidSettings::setVHQForBframes(const bool &value)
	{
		vhqForBframes = value;
	}

	const bool &xvidSettings::getInterlaced() const
	{
		return interlaced;
	}

	void xvidSettings::setInterlaced(const bool &value)
	{
		interlaced = value;
	}

	const bool &xvidSettings::getBottomFieldFirst() const
	{
		return bottomFieldFirst;
	}

	void xvidSettings::setBottomFieldFirst(const bool &value)
	{
		bottomFieldFirst = value;
	}

	const decimal &xvidSettings::getBframeThreshold() const
	{
		return bframeThreshold;
	}

	void xvidSettings::setBframeThreshold(const decimal &value)
	{
		bframeThreshold = value;
	}

	const QString &xvidSettings::getQuantizerMatrix() const
	{
		return customQuantizerMatrix;
	}

	void xvidSettings::setQuantizerMatrix(const QString &value)
	{
		customQuantizerMatrix = value;
	}

	const int &xvidSettings::getHVSMasking() const
	{
		if (hvsMasking > 1)
			hvsMasking = 1;
		return hvsMasking;
	}

	void xvidSettings::setHVSMasking(const int &value)
	{
		hvsMasking = value;
	}

	bool xvidSettings::IsAltered(VideoCodecSettings *settings)
	{
		if (!(dynamic_cast<xvidSettings*>(settings) != 0))
			return true;
		xvidSettings *otherSettings = static_cast<xvidSettings*>(settings);
		if (this->getAveragingPeriod() != otherSettings->getAveragingPeriod() || this->getBframeThreshold() != otherSettings->getBframeThreshold() || this->getBQuantOffset() != otherSettings->getBQuantOffset() || this->getBQuantRatio() != otherSettings->getBQuantRatio() || this->getChromaMotion() != otherSettings->getChromaMotion() || this->getClosedGOP() != otherSettings->getClosedGOP() || this->getCustomEncoderOptions() != otherSettings->getCustomEncoderOptions() || this->getEncodingMode() != otherSettings->getEncodingMode() || this->getFrameDropRatio() != otherSettings->getFrameDropRatio() || this->getGMC() != otherSettings->getGMC() || this->getHighBitrateDegradation() != otherSettings->getHighBitrateDegradation() || this->getInterlaced() != otherSettings->getInterlaced() || this->getKeyFrameBoost() != otherSettings->getKeyFrameBoost() || this->getKeyframeInterval() != otherSettings->getKeyframeInterval() || this->getKeyframeReduction() != otherSettings->getKeyframeReduction() || this->getKeyframeThreshold() != otherSettings->getKeyframeThreshold() || this->getLowBitrateImprovement() != otherSettings->getLowBitrateImprovement() || this->getMaxBQuant() != otherSettings->getMaxBQuant() || this->getMaxOverflowDegradation() != otherSettings->getMaxOverflowDegradation() || this->getMaxOverflowImprovement() != otherSettings->getMaxOverflowImprovement() || this->getMaxPQuant() != otherSettings->getMaxPQuant() || this->getMaxQuantizer() != otherSettings->getMaxQuantizer() || this->getMinBQuant() != otherSettings->getMinBQuant() || this->getMinPQuant() != otherSettings->getMinPQuant() || this->getMinQuantizer() != otherSettings->getMinQuantizer() || this->getMotionSearchPrecision() != otherSettings->getMotionSearchPrecision() || this->getNbBframes() != otherSettings->getNbBframes() || this->getOverflowControlStrength() != otherSettings->getOverflowControlStrength() || this->getPackedBitstream() != otherSettings->getPackedBitstream() || this->getQPel() != otherSettings->getQPel() || this->getRateControlBuffer() != otherSettings->getRateControlBuffer() || this->getReactionDelayFactor() != otherSettings->getReactionDelayFactor() || this->getTrellis() != otherSettings->getTrellis() || this->getTurbo() != otherSettings->getTurbo() || this->getV4MV() != otherSettings->getV4MV() || this->getVHQForBframes() != otherSettings->getVHQForBframes() || this->getXvidProfile() != otherSettings->getXvidProfile() || this->getVbvBuffer() != otherSettings->getVbvBuffer() || this->getVbvMaxRate() != otherSettings->getVbvMaxRate() || this->getVbvPeakRate() != otherSettings->getVbvPeakRate() || this->getVHQMode() != otherSettings->getVHQMode() || this->getHVSMasking() != otherSettings->getHVSMasking())
			return true;
		else
			return false;
	}
}
