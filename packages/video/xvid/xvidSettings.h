#pragma once

#include "core/details/video/VideoCodecSettings.h"
#include "core/details/CodecManager.h"
#include <QString>
#include <QMap>
#include <QVector>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************




//using namespace System::Collections::Generic;

namespace MeXgui
{
	/// <summary>
	/// this class contains all the settings for the xvid codec
	/// </summary>
	class xvidSettings : public VideoCodecSettings
	{
	public:
		static const QString ID;
		static const QString H263Matrix;
		static const QString MPEGMatrix;

		virtual void setAdjustedNbThreads(int nbThreads);

		const bool &getIsCustomMatrix() const;

		virtual void FixFileNames(QMap<QString, QString> &substitutionTable);
		const virtual QString *getRequiredFiles() const;

	private:
		int motionSearchPrecision, vhqMode, minPQuant, maxPQuant, minBQuant, maxBQuant, bQuantRatio, bQuantOffset, keyFrameBoost, keyframeThreshold, keyframeReduction, overflowControlStrength, maxOverflowImprovement, maxOverflowDegradation, highBitrateDegradation, lowBitrateImprovement, reactionDelayFactor, averagingPeriod, rateControlBuffer, frameDropRatio, xvidProfile, vbvBuffer, vbvMaxRate, vbvPeakRate, hvsMasking;
		bool packedBitstream, gmc, chromaMotion, closedGOP, vhqForBframes, interlaced, bottomFieldFirst, turbo;
		decimal bframeThreshold, quantizer;
		QString customQuantizerMatrix;
	public:
		const virtual bool &getUsesSAR() const;
		/// <summary>
		/// default constructor
		/// initializes all the variables at the codec's default (based on the xvid VfW defaults
		/// </summary>
		xvidSettings();
		/// I believe we really does'nt need to create this array @ per-instance basis
	private:
		static const QString m_fourCCs[4];

	public:
		const static QString *getFourCCsForMPEG4ASP() const;

		const decimal &getQuantizer() const;
		void setQuantizer(const decimal &value);
		const bool &getTurbo() const;
		void setTurbo(const bool &value);
		const int &getMotionSearchPrecision() const;
		void setMotionSearchPrecision(const int &value);
		const int &getVHQMode() const;
		void setVHQMode(const int &value);
		const int &getMinPQuant() const;
		void setMinPQuant(const int &value);
		const int &getMaxPQuant() const;
		void setMaxPQuant(const int &value);
		const int &getMinBQuant() const;
		void setMinBQuant(const int &value);
		const int &getMaxBQuant() const;
		void setMaxBQuant(const int &value);
		const int &getBQuantRatio() const;
		void setBQuantRatio(const int &value);
		const int &getBQuantOffset() const;
		void setBQuantOffset(const int &value);
		const int &getKeyFrameBoost() const;
		void setKeyFrameBoost(const int &value);
		const int &getKeyframeThreshold() const;
		void setKeyframeThreshold(const int &value);
		const int &getKeyframeReduction() const;
		void setKeyframeReduction(const int &value);
		const int &getOverflowControlStrength() const;
		void setOverflowControlStrength(const int &value);
		const int &getMaxOverflowImprovement() const;
		void setMaxOverflowImprovement(const int &value);
		const int &getMaxOverflowDegradation() const;
		void setMaxOverflowDegradation(const int &value);
		const int &getHighBitrateDegradation() const;
		void setHighBitrateDegradation(const int &value);
		const int &getLowBitrateImprovement() const;
		void setLowBitrateImprovement(const int &value);
		const int &getReactionDelayFactor() const;
		void setReactionDelayFactor(const int &value);
		const int &getAveragingPeriod() const;
		void setAveragingPeriod(const int &value);
		const int &getFrameDropRatio() const;
		void setFrameDropRatio(const int &value);
		const int &getRateControlBuffer() const;
		void setRateControlBuffer(const int &value);
		const int &getXvidProfile() const;
		void setXvidProfile(const int &value);
		/// <summary>
		/// gets / sets the VBV peak bitrate
		/// </summary>
		const int &getVbvPeakRate() const;
		void setVbvPeakRate(const int &value);
		/// <summary>
		/// gets / sets the VBV maximum bitrate
		/// </summary>
		const int &getVbvMaxRate() const;
		void setVbvMaxRate(const int &value);
		/// <summary>
		/// gets / sets the VBV buffer size
		/// </summary>
		const int &getVbvBuffer() const;
		void setVbvBuffer(const int &value);
		const bool &getPackedBitstream() const;
		void setPackedBitstream(const bool &value);
		const bool &getGMC() const;
		void setGMC(const bool &value);
		const bool &getChromaMotion() const;
		void setChromaMotion(const bool &value);
		const bool &getClosedGOP() const;
		void setClosedGOP(const bool &value);
		const bool &getVHQForBframes() const;
		void setVHQForBframes(const bool &value);
		const bool &getInterlaced() const;
		void setInterlaced(const bool &value);
		/// <summary>
		/// gets / sets whether the interlacing mode is bff
		/// if false, it's tff
		/// only active if <paramref name="Interlaced"/> is also set
		/// </summary>
		const bool &getBottomFieldFirst() const;
		void setBottomFieldFirst(const bool &value);
		const decimal &getBframeThreshold() const;
		void setBframeThreshold(const decimal &value);
		/// <summary>
		/// gets / sets the custom quantizer matrix to be used for encoding
		/// </summary>
		const QString &getQuantizerMatrix() const;
		void setQuantizerMatrix(const QString &value);
		const int &getHVSMasking() const;
		void setHVSMasking(const int &value);

		/// <summary>
		///  Handles assessment of whether the encoding options vary between two xvidSettings instances
		/// The following are excluded from the comparison:
		/// BitrateQuantizer
		/// CreditsQuantizer
		/// Logfile
		/// PAR
		/// PARs
		/// SARX
		/// SARY
		/// Zones
		/// </summary>
		/// <param name="otherSettings"></param>
		/// <returns>true if the settings differ</returns>
		bool IsAltered(VideoCodecSettings *settings);
	};
}
