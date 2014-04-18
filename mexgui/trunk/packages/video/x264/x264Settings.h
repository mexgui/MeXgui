#pragma once

#include "core/details/video/VideoCodecSettings.h"
#include "x264Device.h"
#include "packages/tools/avclevelschecker/AVCLevels.h"
#include "core/details/CodecManager.h"
#include "core/plugins/interfaces/Profile.h"
#include "x264SettingsHandler.h"
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include "stringconverter.h"

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

namespace MeGUI
{
	/// <summary>
	/// Summary description for x264Settings.
	/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Serializable]
	class x264Settings : public VideoCodecSettings
	{
	public:
		enum x264PsyTuningModes
		{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("None")]
			NONE,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Animation")]
			ANIMATION,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Film")]
			FILM,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Grain")]
			GRAIN,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Still Image")]
			STILLIMAGE,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("PSNR")]
			PSNR,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("SSIM")]
			SSIM
		};

	public:
		enum x264PresetLevelModes
		{
			ultrafast = 0,
			superfast = 1,
			veryfast = 2,
			faster = 3,
			fast = 4,
			medium = 5,
			slow = 6,
			slower = 7,
			veryslow = 8,
			placebo = 9
		};

	public:
		enum x264InterlacedModes
		{
			progressive = 0,
			tff = 1,
			bff = 2
		};

	public:
		static std::string ID;

		static const x264PsyTuningModes SupportedPsyTuningModes[7];

		virtual void setAdjustedNbThreads(int nbThreads);

		virtual void FixFileNames(std::map<std::string, std::string> &substitutionTable);
		const virtual std::string *getRequiredFiles() const;
	private:
		int NewadaptiveBFrames, nbRefFrames, alphaDeblock, betaDeblock, subPelRefinement, maxQuantDelta, tempQuantBlur, bframePredictionMode, vbvBufferSize, vbvMaxBitrate, meType, meRange, minGOPSize, macroBlockOptions, quantizerMatrixType, x264Trellis, noiseReduction, deadZoneInter, deadZoneIntra, AQMode, profile, lookahead, slicesnb, maxSliceSyzeBytes, maxSliceSyzeMBs, bFramePyramid, weightedPPrediction, x264Nalhrd, colorMatrix, transfer, colorPrim, x264PullDown, sampleAR, _gopCalculation;
		decimal ipFactor, pbFactor, chromaQPOffset, vbvInitialBuffer, bitrateVariance, quantCompression, tempComplexityBlur, tempQuanBlurCC, scdSensitivity, bframeBias, quantizerCrf, AQStrength, psyRDO, psyTrellis;
		bool deblock, cabac, p4x4mv, p8x8mv, b8x8mv, i4x4mv, i8x8mv, weightedBPrediction, blurayCompat, chromaME, adaptiveDCT, noMixedRefs, noFastPSkip, psnrCalc, noDctDecimate, ssimCalc, useQPFile, FullRange, advSet, noMBTree, threadInput, noPsy, scenecut, x264Aud, x264SlowFirstpass, picStruct, fakeInterlaced, nonDeterministic, tuneFastDecode, tuneZeroLatency, stitchable, x26410Bits;
		std::string quantizerMatrix, qpfile, openGop, range;
		x264PresetLevelModes preset;
		x264InterlacedModes interlacedMode;
		x264Device *targetDevice;
		x264PsyTuningModes psyTuningMode;
		AVCLevels::Levels avcLevel;
		std::vector<x264Device*> x264DeviceList;
		/// <summary>
		/// default constructor, initializes codec default values
		/// </summary>
	public:
		x264Settings();
		const x264PresetLevelModes &getx264PresetLevel() const;
		void setx264PresetLevel(const x264PresetLevelModes &value);
#warning Deprecated since 2327; delete after next stable release
		const std::string &getx264Tuning() const;
		void setx264Tuning(const std::string &value);
		const x264PsyTuningModes &getx264PsyTuning() const;
		void setx264PsyTuning(const x264PsyTuningModes &value);
		const decimal &getQuantizerCRF() const;
		void setQuantizerCRF(const decimal &value);
		const x264InterlacedModes &getInterlacedMode() const;
		void setInterlacedMode(const x264InterlacedModes &value);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore(), MeGUI::core::plugins::interfaces::PropertyEqualityIgnoreAttribute()]
		const x264Device &getTargetDevice() const;
		void setTargetDevice(const x264Device &value);
		// for profile import/export in case the enum changes
		const std::string &getTargetDeviceXML() const;
		void setTargetDeviceXML(const std::string &value);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const bool &getBlurayCompat() const;
		void setBlurayCompat(const bool &value);
		/// <summary>
		/// Only for XML export/import. For all other purposes use BlurayCompat()
		/// </summary>
		const std::string &getBlurayCompatXML() const;
		void setBlurayCompatXML(const std::string &value);
		const bool &getNoDCTDecimate() const;
		void setNoDCTDecimate(const bool &value);

		const bool &getPSNRCalculation() const;
		void setPSNRCalculation(const bool &value);
		const bool &getNoFastPSkip() const;
		void setNoFastPSkip(const bool &value);
		const int &getNoiseReduction() const;
		void setNoiseReduction(const int &value);
		const bool &getNoMixedRefs() const;
		void setNoMixedRefs(const bool &value);
		const int &getX264Trellis() const;
		void setX264Trellis(const int &value);
		const int &getNbRefFrames() const;
		void setNbRefFrames(const int &value);
		const int &getAlphaDeblock() const;
		void setAlphaDeblock(const int &value);
		const int &getBetaDeblock() const;
		void setBetaDeblock(const int &value);
		const int &getSubPelRefinement() const;
		void setSubPelRefinement(const int &value);
		const int &getMaxQuantDelta() const;
		void setMaxQuantDelta(const int &value);
		const int &getTempQuantBlur() const;
		void setTempQuantBlur(const int &value);
		const int &getBframePredictionMode() const;
		void setBframePredictionMode(const int &value);
		const int &getVBVBufferSize() const;
		void setVBVBufferSize(const int &value);
		const int &getVBVMaxBitrate() const;
		void setVBVMaxBitrate(const int &value);
		const int &getMEType() const;
		void setMEType(const int &value);
		const int &getMERange() const;
		void setMERange(const int &value);
		const int &getMinGOPSize() const;
		void setMinGOPSize(const int &value);
		const decimal &getIPFactor() const;
		void setIPFactor(const decimal &value);
		const decimal &getPBFactor() const;
		void setPBFactor(const decimal &value);
		const decimal &getChromaQPOffset() const;
		void setChromaQPOffset(const decimal &value);
		const decimal &getVBVInitialBuffer() const;
		void setVBVInitialBuffer(const decimal &value);
		const decimal &getBitrateVariance() const;
		void setBitrateVariance(const decimal &value);
		const decimal &getQuantCompression() const;
		void setQuantCompression(const decimal &value);
		const decimal &getTempComplexityBlur() const;
		void setTempComplexityBlur(const decimal &value);
		const decimal &getTempQuanBlurCC() const;
		void setTempQuanBlurCC(const decimal &value);
		const decimal &getSCDSensitivity() const;
		void setSCDSensitivity(const decimal &value);
		const decimal &getBframeBias() const;
		void setBframeBias(const decimal &value);
		const decimal &getPsyRDO() const;
		void setPsyRDO(const decimal &value);
		const decimal &getPsyTrellis() const;
		void setPsyTrellis(const decimal &value);
		const bool &getDeblock() const;
		void setDeblock(const bool &value);
		const bool &getCabac() const;
		void setCabac(const bool &value);
		const bool &getUseQPFile() const;
		void setUseQPFile(const bool &value);
		const bool &getWeightedBPrediction() const;
		void setWeightedBPrediction(const bool &value);
		const int &getWeightedPPrediction() const;
		void setWeightedPPrediction(const int &value);
		const int &getNewAdaptiveBFrames() const;
		void setNewAdaptiveBFrames(const int &value);
		const int &getx264BFramePyramid() const;
		void setx264BFramePyramid(const int &value);
		const int &getx264GOPCalculation() const;
		void setx264GOPCalculation(const int &value);
		const bool &getChromaME() const;
		void setChromaME(const bool &value);
		const int &getMacroBlockOptions() const;
		void setMacroBlockOptions(const int &value);
		const bool &getP8x8mv() const;
		void setP8x8mv(const bool &value);
		const bool &getB8x8mv() const;
		void setB8x8mv(const bool &value);
		const bool &getI4x4mv() const;
		void setI4x4mv(const bool &value);
		const bool &getI8x8mv() const;
		void setI8x8mv(const bool &value);
		const bool &getP4x4mv() const;
		void setP4x4mv(const bool &value);
		const bool &getAdaptiveDCT() const;
		void setAdaptiveDCT(const bool &value);
		const bool &getSSIMCalculation() const;
		void setSSIMCalculation(const bool &value);
		const bool &getStitchAble() const;
		void setStitchAble(const bool &value);
		const std::string &getQuantizerMatrix() const;
		void setQuantizerMatrix(const std::string &value);
		const int &getQuantizerMatrixType() const;
		void setQuantizerMatrixType(const int &value);
		const int &getDeadZoneInter() const;
		void setDeadZoneInter(const int &value);
		const int &getDeadZoneIntra() const;
		void setDeadZoneIntra(const int &value);
		const bool &getX26410Bits() const;
		void setX26410Bits(const bool &value);
		/// <summary>
		/// Only for XML export/import. For all other purposes use OpenGopValue()
		/// </summary>
		const std::string &getOpenGop() const;
		void setOpenGop(const std::string &value);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore()]
		const bool &getOpenGopValue() const;
		void setOpenGopValue(const bool &value);
		const int &getX264PullDown() const;
		void setX264PullDown(const int &value);
		const int &getSampleAR() const;
		void setSampleAR(const int &value);
		const int &getColorMatrix() const;
		void setColorMatrix(const int &value);
		const int &getColorPrim() const;
		void setColorPrim(const int &value);
		const int &getTransfer() const;
		void setTransfer(const int &value);
		const int &getAQmode() const;
		void setAQmode(const int &value);
		const decimal &getAQstrength() const;
		void setAQstrength(const decimal &value);
		const std::string &getQPFile() const;
		void setQPFile(const std::string &value);
		const std::string &getRange() const;
		void setRange(const std::string &value);
		const bool &getx264AdvancedSettings() const;
		void setx264AdvancedSettings(const bool &value);
		const int &getLookahead() const;
		void setLookahead(const int &value);
		const bool &getNoMBTree() const;
		void setNoMBTree(const bool &value);
		const bool &getThreadInput() const;
		void setThreadInput(const bool &value);
		const bool &getNoPsy() const;
		void setNoPsy(const bool &value);
		const bool &getScenecut() const;
		void setScenecut(const bool &value);
		const int &getNalhrd() const;
		void setNalhrd(const int &value);
		const bool &getX264Aud() const;
		void setX264Aud(const bool &value);
		const bool &getX264SlowFirstpass() const;
		void setX264SlowFirstpass(const bool &value);
		const bool &getPicStruct() const;
		void setPicStruct(const bool &value);
		const bool &getFakeInterlaced() const;
		void setFakeInterlaced(const bool &value);
		const bool &getNonDeterministic() const;
		void setNonDeterministic(const bool &value);
		const int &getSlicesNb() const;
		void setSlicesNb(const int &value);
		const int &getMaxSliceSyzeBytes() const;
		void setMaxSliceSyzeBytes(const int &value);
		const int &getMaxSliceSyzeMBs() const;
		void setMaxSliceSyzeMBs(const int &value);
		const int &getProfile() const;
		void setProfile(const int &value);
#warning Deprecated since 2327; delete after next stable release
		const std::string &getLevel() const;
		void setLevel(const std::string &value);
		const AVCLevels::Levels &getAVCLevel() const;
		void setAVCLevel(const AVCLevels::Levels &value);
		const bool &getTuneFastDecode() const;
		void setTuneFastDecode(const bool &value);
		const bool &getTuneZeroLatency() const;
		void setTuneZeroLatency(const bool &value);
		const virtual bool &getUsesSAR() const;
		/// <summary>
		///  Handles assessment of whether the encoding options vary between two x264Settings instances
		/// The following are excluded from the comparison:
		/// BitrateQuantizer
		/// CreditsQuantizer
		/// Logfile
		/// NbThreads
		/// SARX
		/// SARY
		/// Zones
		/// </summary>
		/// <param name="otherSettings"></param>
		/// <returns>true if the settings differ</returns>
		bool IsAltered(x264Settings *otherSettings);

		void doTriStateAdjustment();

		static int GetDefaultNumberOfRefFrames(x264PresetLevelModes oPreset, x264PsyTuningModes oTuningMode, x264Device *oDevice, AVCLevels::Levels avcLevel, bool blurayCompat);

		static int GetDefaultNumberOfRefFrames(x264PresetLevelModes oPreset, x264PsyTuningModes oTuningMode, x264Device *oDevice, AVCLevels::Levels avcLevel, bool blurayCompat, int hRes, int vRes);

		static int GetDefaultNumberOfBFrames(x264PresetLevelModes oPresetLevel, x264PsyTuningModes oTuningMode, bool bTuneZeroLatency, int oAVCProfile, x264Device *oDevice, bool blurayCompat);

		static int GetDefaultNumberOfWeightp(x264PresetLevelModes oPresetLevel, bool bFastDecode, int oAVCProfile, bool bBlurayCompat);

		static int GetDefaultAQMode(x264PresetLevelModes oPresetLevel, x264PsyTuningModes oTuningMode);

		static int GetDefaultRCLookahead(x264PresetLevelModes oPresetLevel, bool bTuneZeroLatency);
	};
}
