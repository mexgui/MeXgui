#include "AVCLevels.h"






namespace MeXgui
{

	const QString &AVCLevelTool::getName() const
	{
		return "AVC Levels Checker";
	}

	void AVCLevelTool::Run(MainForm *info)
	{
		if (info->getVideo()->getVideoInput().Equals(""))
		{
			MessageBox::Show("You first need to load an AviSynth script", "No video configured", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		bool succ;
		int hRes, vRes;
		MeXgui::core::util::Dar d;
		quint64 nbFrames;
		double framerate;
		Nullable<AVCLevels::Levels> compliantLevel = Nullable<AVCLevels::Levels>();
		x264Settings *currentX264Settings = static_cast<x264Settings*>(MainForm::Instance->getProfiles()->GetCurrentSettings("x264"));

		if (JobUtil::GetAllInputProperties(nbFrames, framerate, hRes, vRes, d, info->getVideo()->getVideoInput()))
		{
			AVCLevels *al = new AVCLevels();
			succ = al->validateAVCLevel(hRes, vRes, framerate, currentX264Settings, compliantLevel);
		}
		else
			succ = false;

		if (succ)
			MessageBox::Show("This file matches the criteria for the level chosen", "Video validated", MessageBoxButtons::OK, MessageBoxIcon::Information);
		else
		{
			if (!compliantLevel.HasValue)
				MessageBox::Show("Unable to open video", "Test failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
			else
			{
				AVCLevels *al = new AVCLevels();
				QString message = "This video source cannot be encoded to comply with the chosen level.\n" + "You need at least Level " + AVCLevels::GetLevelText(static_cast<AVCLevels::Levels>(compliantLevel)) + " for this source. Do you want\n" + "to increase the level automatically now?";
				DialogResult *dr = MessageBox::Show(message, "Test failed", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
				if (dr == DialogResult::Yes)
					currentX264Settings->setAVCLevel(static_cast<AVCLevels::Levels>(compliantLevel));
			}
		}

	}

	const Shortcut &AVCLevelTool::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlL};
	}

	const QString &AVCLevelTool::getID() const
	{
		return "avc_level_validater";
	}

const Levels AVCLevels::SupportedLevels[18] = {L_10, L_1B, L_11, L_12, L_13, L_20, L_21, L_22, L_30, L_31, L_32, L_40, L_41, L_42, L_50, L_51, L_52, L_UNRESTRICTED};

	QString AVCLevels::GetLevelText(Levels avcLevel)
	{
		switch (avcLevel)
		{
			case L_10:
				return "1.0";
			case L_1B:
				return "1b";
			case L_11:
				return "1.1";
			case L_12:
				return "1.2";
			case L_13:
				return "1.3";
			case L_20:
				return "2.0";
			case L_21:
				return "2.1";
			case L_22:
				return "2.2";
			case L_30:
				return "3.0";
			case L_31:
				return "3.1";
			case L_32:
				return "3.2";
			case L_40:
				return "4.0";
			case L_41:
				return "4.1";
			case L_42:
				return "4.2";
			case L_50:
				return "5.0";
			case L_51:
				return "5.1";
			default:
				return "5.2";
		}
	}

	bool AVCLevels::checkP4x4Enabled(Levels avcLevel, x264Settings *settings)
	{
		//if (level != 15 && (level > 7 || (level == 7 && settings.NbBframes != 0)))
		//    return false;
		//else
			return true;
	}

	bool AVCLevels::checkP4x4(Levels avcLevel, x264Settings *settings)
	{
		if (!checkP4x4Enabled(avcLevel, settings))
			if (settings->getP4x4mv())
				return false;
		return true;
	}

	double AVCLevels::pictureBufferSize(x264Settings *settings, double bytesInUncompressedFrame)
	{
		double decodedPictureBufferSizeTestValue = 0;
		if (settings != 0)
			decodedPictureBufferSizeTestValue = bytesInUncompressedFrame * __min(16, settings->getNbRefFrames());
		return decodedPictureBufferSizeTestValue;
	}

	bool AVCLevels::checkMaxDPB(Levels avcLevel, x264Settings *settings, double bytesInUncompressedFrame)
	{
		if (pictureBufferSize(settings, bytesInUncompressedFrame) > this->getMaxDPB(avcLevel))
			return false;
		else
			return true;
	}

	int AVCLevels::macroblocks(int res)
	{
		int blocks;
		if (res % 16 == 0)
			blocks = res / 16;
		else
		{
			int remainder;
			blocks = Math::DivRem(res, 16, remainder);
			blocks++;
		}
		return blocks;
	}

	double AVCLevels::maxFS(int hRes, int vRes)
	{
		int horizontalBlocks, verticalBlocks;
		if (hRes % 16 == 0)
			horizontalBlocks = hRes / 16;
		else
		{
			int remainder;
			horizontalBlocks = Math::DivRem(hRes, 16, remainder);
			horizontalBlocks++;
		}
		if (vRes % 16 == 0)
			verticalBlocks = vRes / 16;
		else
		{
			int remainder;
			verticalBlocks = Math::DivRem(vRes, 16, remainder);
			verticalBlocks++;
		}
		return static_cast<double>(horizontalBlocks) * static_cast<double>(verticalBlocks);
	}

	int AVCLevels::maxBPS(int hres, int vres, double framerate)
	{
		return static_cast<int>(maxFS(hres, vres) * framerate);
	}

	double AVCLevels::bytesPerFrame(int hres, int vres)
	{
		return hres * vres * 1.5;
	}

	AVCLevels::AVCLevels()
	{
		//
		// TODO: Add constructor logic here
		//
	}

	int AVCLevels::getMaxCBP(Levels avcLevel, bool isHighProfile)
	{
		int maxCBP = 0;
		switch (avcLevel)
		{
			case L_10:
				maxCBP = 175;
				break;
			case L_1B:
				maxCBP = 350;
				break;
			case L_11:
				maxCBP = 500;
				break;
			case L_12:
				maxCBP = 1000;
				break;
			case L_13:
				maxCBP = 2000;
				break;
			case L_20:
				maxCBP = 2000;
				break;
			case L_21:
				maxCBP = 4000;
				break;
			case L_22:
				maxCBP = 4000;
				break;
			case L_30:
				maxCBP = 10000;
				break;
			case L_31:
				maxCBP = 14000;
				break;
			case L_32:
				maxCBP = 20000;
				break;
			case L_40:
				maxCBP = 25000;
				break;
			case L_41:
				maxCBP = 62500;
				break;
			case L_42:
				maxCBP = 62500;
				break;
			case L_50:
				maxCBP = 135000;
				break;
			case L_51:
				maxCBP = 240000;
				break;
			case L_52:
				maxCBP = 240000;
				break;
		}

		if (isHighProfile) // all bitrates and CBPs are multiplied by 1.25 in high profile
			maxCBP = maxCBP * 125 / 100;

		return maxCBP;
	}

	int AVCLevels::getMaxBR(Levels avcLevel, bool isHighProfile)
	{
		int maxBR = 0;
		switch (avcLevel)
		{
			case L_10:
				maxBR = 64;
				break;
			case L_1B:
				maxBR = 128;
				break;
			case L_11:
				maxBR = 192;
				break;
			case L_12:
				maxBR = 384;
				break;
			case L_13:
				maxBR = 768;
				break;
			case L_20:
				maxBR = 2000;
				break;
			case L_21:
				maxBR = 4000;
				break;
			case L_22:
				maxBR = 4000;
				break;
			case L_30:
				maxBR = 10000;
				break;
			case L_31:
				maxBR = 14000;
				break;
			case L_32:
				maxBR = 20000;
				break;
			case L_40:
				maxBR = 20000;
				break;
			case L_41:
				maxBR = 50000;
				break;
			case L_42:
				maxBR = 50000;
				break;
			case L_50:
				maxBR = 135000;
				break;
			case L_51:
				maxBR = 240000;
				break;
			case L_52:
				maxBR = 240000;
				break;
		}

		if (isHighProfile) // all bitrates and cbps are multiplied by 1.25 in high profile
			maxBR = maxBR * 125 / 100;

		return maxBR;
	}

	int AVCLevels::getMaxMBPS(Levels avcLevel)
	{
		switch (avcLevel)
		{
			case L_10:
				return 1485;
			case L_1B:
				return 1485;
			case L_11:
				return 3000;
			case L_12:
				return 6000;
			case L_13:
				return 11880;
			case L_20:
				return 11880;
			case L_21:
				return 19800;
			case L_22:
				return 20250;
			case L_30:
				return 40500;
			case L_31:
				return 108000;
			case L_32:
				return 216000;
			case L_40:
				return 245760;
			case L_41:
				return 245760;
			case L_42:
				return 491520;
			case L_50:
				return 589824;
			case L_51:
				return 983040;
			default: // level 5.2
				return 2073600;
		}
	}

	int AVCLevels::getMaxFS(Levels avcLevel)
	{
		switch (avcLevel)
		{
			case L_10:
				return 99;
			case L_1B:
				return 99;
			case L_11:
				return 396;
			case L_12:
				return 396;
			case L_13:
				return 396;
			case L_20:
				return 396;
			case L_21:
				return 792;
			case L_22:
				return 1620;
			case L_30:
				return 1620;
			case L_31:
				return 3600;
			case L_32:
				return 5120;
			case L_40:
				return 8192;
			case L_41:
				return 8192;
			case L_42:
				return 8192;
			case L_50:
				return 22080;
			case L_51:
				return 36864;
			default: // level 5.2
				return 36864;
		}
	}

	double AVCLevels::getMaxDPB(Levels avcLevel)
	{
		double maxDPB = 69120;
		switch (avcLevel)
		{
			case L_10:
				maxDPB = 148.5;
				break;
			case L_1B:
				maxDPB = 148.5;
				break;
			case L_11:
				maxDPB = 337.5;
				break;
			case L_12:
				maxDPB = 891;
				break;
			case L_13:
				maxDPB = 891;
				break;
			case L_20:
				maxDPB = 891;
				break;
			case L_21:
				maxDPB = 1782;
				break;
			case L_22:
				maxDPB = 3037.5;
				break;
			case L_30:
				maxDPB = 3037.5;
				break;
			case L_31:
				maxDPB = 6750;
				break;
			case L_32:
				maxDPB = 7680;
				break;
			case L_40:
				maxDPB = 12288;
				break;
			case L_41:
				maxDPB = 12288;
				break;
			case L_42:
				maxDPB = 12288;
				break;
			case L_50:
				maxDPB = 41310;
				break;
			case L_51:
				maxDPB = 69120;
				break;
			case L_52:
				maxDPB = 69120;
				break;
		}
		return maxDPB * 1024;
	}

	int AVCLevels::Verifyx264Settings(x264Settings *settings, AVCLevels::Levels avcLevel, double bytesInUncompressedFrame)
	{

		if (!this->checkP4x4(avcLevel, settings))
			return 1;

		if (!this->checkMaxDPB(avcLevel, settings, bytesInUncompressedFrame))
			return 2;

		return 0;
	}

	x264Settings *AVCLevels::EnforceSettings(AVCLevels::Levels avcLevel, x264Settings *inputSettings, double frameSize, AVCLevelEnforcementReturn *&enforcement)
	{
		x264Settings *enforcedSettings = static_cast<x264Settings*>(inputSettings->Clone());
		enforcement = new AVCLevelEnforcementReturn();
		enforcement->setAltered(false);
		enforcement->setEnableP4x4mv(true);
		enforcement->setEnableVBVBufferSize(true);
		enforcement->setEnableVBVMaxRate(true);
		enforcement->setPanic(false);
		enforcement->setPanicString("");

		if (!checkP4x4(avcLevel, inputSettings))
		{
			enforcement->setAltered(true);
			enforcedSettings->setP4x4mv(false);
		}
		if (checkP4x4Enabled(avcLevel, inputSettings))
			enforcement->setEnableP4x4mv(true);
		else
			enforcement->setEnableP4x4mv(false);

		// step through various options to enforce the max decoded picture buffer size
		while (!this->checkMaxDPB(avcLevel,enforcedSettings, frameSize))
		{
			if (enforcedSettings->getNbRefFrames() > 1)
			{
				enforcement->setAltered(true);
				enforcedSettings->setNbRefFrames(enforcedSettings->getNbRefFrames() - 1); // try reducing the number of reference frames
			}
			else
			{
				enforcement->setPanic(true);
				enforcement->setPanicString("Can't force settings to conform to level (the frame size is too large)");
				// reset output settings to original and set level to unrestrained
				enforcedSettings = static_cast<x264Settings*>(inputSettings->Clone());
				enforcedSettings->setAVCLevel(L_UNRESTRICTED);
				return enforcedSettings;
			}
		}

		// Disallow independent specification of MaxBitrate and MaxBufferSize unless Unrestrained
		if (avcLevel != L_UNRESTRICTED)
		{
			enforcement->setEnableVBVMaxRate(false);
			enforcedSettings->setVBVMaxBitrate(-1);
			enforcement->setEnableVBVBufferSize(false);
			enforcedSettings->setVBVBufferSize(-1);
		}
		else
		{
			enforcement->setEnableVBVMaxRate(true);
			enforcement->setEnableVBVBufferSize(true);
		}

		return enforcedSettings;

	}

	bool AVCLevels::validateAVCLevel(int hRes, int vRes, double framerate, x264Settings *settings, Nullable<AVCLevels::Levels> &compliantLevel)
	{
		settings = static_cast<x264Settings*>(settings->Clone()); // otherwise this sets it to the lowest compliant level anyway.
		compliantLevel = L_UNRESTRICTED;
		if (settings->getAVCLevel() == L_UNRESTRICTED)
			return true;

		int FrameSize = static_cast<int>(maxFS(hRes, vRes));
		int MBPS = maxBPS(hRes, vRes, framerate);
		int hBlocks = macroblocks(hRes);
		int vBlocks = macroblocks(vRes);
		double bufferSize = pictureBufferSize(settings, bytesPerFrame(hRes, vRes));
		int allowableBPS = this->getMaxMBPS(settings->getAVCLevel());
		int allowableFS = this->getMaxFS(settings->getAVCLevel());
		double dimensionRestriction = ceil(sqrt(static_cast<double>(allowableFS)*8));
		double allowableDPB = this->getMaxDPB(settings->getAVCLevel());

		if (allowableBPS >= MBPS && allowableFS >= FrameSize && allowableDPB >= bufferSize && dimensionRestriction >= hBlocks && dimensionRestriction >= vBlocks)
			return true;
		else
		{
			while (settings->getAVCLevel() != L_UNRESTRICTED && (allowableBPS < MBPS || allowableFS < FrameSize || allowableDPB < bufferSize || dimensionRestriction < hBlocks || dimensionRestriction < vBlocks))
			{
				settings->setAVCLevel(settings->getAVCLevel() + 1);
				allowableBPS = this->getMaxMBPS(settings->getAVCLevel());
				allowableFS = this->getMaxFS(settings->getAVCLevel());
				dimensionRestriction = ceil(sqrt(static_cast<double>(allowableFS)*8));
				allowableDPB = this->getMaxDPB(settings->getAVCLevel());
			}
			compliantLevel = settings->getAVCLevel();
			return false;
		}
	}

	AVCLevelEnforcementReturn::AVCLevelEnforcementReturn()
	{
		enableP4x4mv = true;
		enableVBVBufferSize = true;
		enableVBVMaxRate = true;
		altered = false;
	}

	const bool &AVCLevelEnforcementReturn::getEnableP4x4mv() const
	{
		return enableP4x4mv;
	}

	void AVCLevelEnforcementReturn::setEnableP4x4mv(const bool &value)
	{
		enableP4x4mv = value;
	}

	const bool &AVCLevelEnforcementReturn::getEnableVBVBufferSize() const
	{
		return enableVBVBufferSize;
	}

	void AVCLevelEnforcementReturn::setEnableVBVBufferSize(const bool &value)
	{
		enableVBVBufferSize = value;
	}

	const bool &AVCLevelEnforcementReturn::getEnableVBVMaxRate() const
	{
		return enableVBVMaxRate;
	}

	void AVCLevelEnforcementReturn::setEnableVBVMaxRate(const bool &value)
	{
		enableVBVMaxRate = value;
	}

	const bool &AVCLevelEnforcementReturn::getAltered() const
	{
		return altered;
	}

	void AVCLevelEnforcementReturn::setAltered(const bool &value)
	{
		altered = value;
	}

	const bool &AVCLevelEnforcementReturn::getPanic() const
	{
		return panic;
	}

	void AVCLevelEnforcementReturn::setPanic(const bool &value)
	{
		panic = value;
	}

	const QString &AVCLevelEnforcementReturn::getPanicString() const
	{
		return panicString;
	}

	void AVCLevelEnforcementReturn::setPanicString(const QString &value)
	{
		panicString = value;
	}
}
