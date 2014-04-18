#include "x264Encoder.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;

namespace MeGUI
{

JobProcessorFactory *const x264Encoder::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "x264Encoder");

	IJobProcessor *x264Encoder::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<VideoJob*>(j) != 0 && dynamic_cast<x264Settings*>((dynamic_cast<VideoJob*>(j))->getSettings()) != 0)
		{
			x264Settings *xs = static_cast<x264Settings*>((dynamic_cast<VideoJob*>(j))->getSettings());
			if (xs->getX26410Bits())
				return new x264Encoder(mf->getSettings()->getX26410BitsPath());
			else
				return new x264Encoder(mf->getSettings()->getX264Path());
		}
		return 0;
	}

	x264Encoder::x264Encoder(const std::string &encoderPath) : CommandlineVideoEncoder()
	{
		executable = encoderPath;
	#if defined(x86)
		if (OSInfo::isWow64() && MainForm::Instance->getSettings()->getUse64bitX264())
		{
			std::string x264Path = Path::Combine(Path::GetDirectoryName(encoderPath), "avs4x264mod.exe");
			if (System::IO::File::Exists(x264Path))
				executable = x264Path;
		}
	#endif
	}

	void x264Encoder::ProcessLine(const std::string &line, StreamType stream, ImageType oType)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		if (line.StartsWith("[")) // status update
		{
			int frameNumberStart = line.find("]", 4) + 2;
			int frameNumberEnd = line.find("/");
			if (frameNumberStart > 0 && frameNumberEnd > 0 && frameNumberEnd > frameNumberStart)
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
				if (CommandlineVideoEncoder::setFrameNumber(line.substr(frameNumberStart, frameNumberEnd - frameNumberStart)->Trim()))
					return;
		}

		if (line.ToLowerInvariant()->Contains("[error]:") || line.ToLowerInvariant()->Contains("error:"))
			oType = Error;
		else if (line.ToLowerInvariant()->Contains("[warning]:") || line.ToLowerInvariant()->Contains("warning:"))
			oType = Warning;
		CommandlineVideoEncoder::ProcessLine(line, stream, oType);
	}

	std::string x264Encoder::genCommandline(const std::string &input, const std::string &output, Nullable<Dar> d, int hres, int vres, int fps_n, int fps_d, x264Settings *_xs, Zone zones[], LogItem *log)
	{
		int qp;
		bool display = false;
		StringBuilder *sb = new StringBuilder();
		CultureInfo *ci = new CultureInfo("en-us");
		x264Settings *xs = static_cast<x264Settings*>(_xs->Clone());
		MeGUI::packages::video::x264::x264SettingsHandler *oSettingsHandler = new packages::video::x264::x264SettingsHandler(xs, log);

		// log
		if (log != 0)
		{
			log->LogEvent("resolution: " + hres + "x" + vres);
			log->LogEvent("frame rate: " + fps_n + "/" + fps_d);
			if (d.HasValue)
				log->LogValue("aspect ratio", d.Value);
			if (xs->getTargetDevice()->getID() > 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				log->LogEvent("target device selected: " + xs->getTargetDevice()->ToString());
			if (!xs->getCustomEncoderOptions().empty())
				log->LogEvent("custom command line: " + xs->getCustomEncoderOptions());
		}

		///<summary>
		/// x264 Main Tab Settings
		///</summary>
	#if defined(x86)
		// Enable/Disable 10-Bits Encoding
		if (xs->getX26410Bits() && !input.Equals("input") && !output.Equals("output"))
		{
			if (OSInfo::isWow64() && MainForm::Instance->getSettings()->getUse64bitX264())
				sb->Append(" -L \"" + Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getX26410BitsPath()), "x264-10b_64.exe") + "\" ");
		}
	#endif
		// AVC Profiles
		if (!xs->getX26410Bits()) // disable those profiles - not suite for 10-Bits Encoding
		{
			xs->setProfile(oSettingsHandler->getProfile());
			switch (xs->getProfile())
			{
				case 0:
					sb->Append("--profile baseline ");
					break;
				case 1:
					sb->Append("--profile main ");
					break;
				case 2: // --profile high is the default value
					break;
			}
		}

		// AVC Levels
		xs->setAVCLevel(oSettingsHandler->getLevel());
		if (xs->getAVCLevel() != AVCLevels::L_UNRESTRICTED) // unrestricted
			sb->Append("--level " + AVCLevels::GetLevelText(xs->getAVCLevel()) + " ");

		// --bluray-compat
		xs->setBlurayCompat(oSettingsHandler->getBlurayCompat());
		if (xs->getBlurayCompat())
			sb->Append("--bluray-compat ");

		// x264 Presets
		if (!xs->getCustomEncoderOptions().find("--preset ") != string::npos)
		{
			switch (xs->getx264PresetLevel())
			{
				case x264Settings::ultrafast:
					sb->Append("--preset ultrafast ");
					break;
				case x264Settings::superfast:
					sb->Append("--preset superfast ");
					break;
				case x264Settings::veryfast:
					sb->Append("--preset veryfast ");
					break;
				case x264Settings::faster:
					sb->Append("--preset faster ");
					break;
				case x264Settings::fast:
					sb->Append("--preset fast ");
					break;
				//case x264Settings.x264PresetLevelModes.medium: sb.Append("--preset medium "); break; // default value
				case x264Settings::slow:
					sb->Append("--preset slow ");
					break;
				case x264Settings::slower:
					sb->Append("--preset slower ");
					break;
				case x264Settings::veryslow:
					sb->Append("--preset veryslow ");
					break;
				case x264Settings::placebo:
					sb->Append("--preset placebo ");
					break;
			}
		}

		// x264 Tunings
		if (!xs->getCustomEncoderOptions().find("--tune ") != string::npos)
		{
			switch (xs->getx264PsyTuning())
			{
				case x264Settings::FILM:
					sb->Append("--tune film");
					break;
				case x264Settings::ANIMATION:
					sb->Append("--tune animation");
					break;
				case x264Settings::GRAIN:
					sb->Append("--tune grain");
					break;
				case x264Settings::PSNR:
					sb->Append("--tune psnr");
					break;
				case x264Settings::SSIM:
					sb->Append("--tune ssim");
					break;
				case x264Settings::STILLIMAGE:
					sb->Append("--tune stillimage");
					break;
				default:
					break;
			}
			if (xs->getTuneFastDecode() || xs->getTuneZeroLatency())
			{
				std::string tune = "";
				if (xs->getTuneFastDecode())
					tune = ",fastdecode";
				if (xs->getTuneZeroLatency())
					tune += ",zerolatency";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				if (!sb->ToString()->Contains("--tune "))
					sb->Append("--tune " + tune.substr(1));
				else
					sb->Append(tune);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if (sb->ToString()->Contains("--tune "))
				sb->Append(" ");
		}

		// Encoding Modes
		switch (xs->getEncodingMode())
		{
			case 0: // ABR
				if (!xs->getCustomEncoderOptions().find("--bitrate ") != string::npos)
					sb->Append("--bitrate " + xs->getBitrateQuantizer() + " ");
				break;
			case 1: // CQ
				if (!xs->getCustomEncoderOptions().find("--qp ") != string::npos)
				{
					qp = static_cast<int>(xs->getQuantizerCRF());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sb->Append("--qp " + qp.ToString(ci) + " ");
				}
				break;
			case 2: // 2 pass first pass
				sb->Append("--pass 1 --bitrate " + xs->getBitrateQuantizer() + " --stats " + "\"" + xs->getLogfile() + "\" ");
				break;
			case 3: // 2 pass second pass
			case 4: // automated twopass
				sb->Append("--pass 2 --bitrate " + xs->getBitrateQuantizer() + " --stats " + "\"" + xs->getLogfile() + "\" ");
				break;
			case 5: // 3 pass first pass
				sb->Append("--pass 1 --bitrate " + xs->getBitrateQuantizer() + " --stats " + "\"" + xs->getLogfile() + "\" ");
				break;
			case 6: // 3 pass 2nd pass
				sb->Append("--pass 3 --bitrate " + xs->getBitrateQuantizer() + " --stats " + "\"" + xs->getLogfile() + "\" ");
				break;
			case 7: // 3 pass 3rd pass
			case 8: // automated threepass, show third pass options
				sb->Append("--pass 3 --bitrate " + xs->getBitrateQuantizer() + " --stats " + "\"" + xs->getLogfile() + "\" ");
				break;
			case 9: // constant quality
				if (!xs->getCustomEncoderOptions().find("--crf ") != string::npos)
					if (xs->getQuantizerCRF() != 23)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						sb->Append("--crf " + xs->getQuantizerCRF().ToString(ci) + " ");
				break;
		}

		// Slow 1st Pass
		if (!xs->getCustomEncoderOptions().find("--slow-firstpass") != string::npos)
			if ((xs->getX264SlowFirstpass()) && xs->getx264PresetLevel() < x264Settings::placebo && ((xs->getEncodingMode() == 2) || (xs->getEncodingMode() == 4) || (xs->getEncodingMode() == 5) || (xs->getEncodingMode() == 8))) // automated threepass -  3 pass first pass -  automated twopass -  2 pass first pass
				sb->Append("--slow-firstpass ");

		// Threads
		if (!xs->getCustomEncoderOptions().find("--thread-input") != string::npos)
			if (xs->getThreadInput() && xs->getNbThreads() == 1)
				sb->Append("--thread-input ");
		if (!xs->getCustomEncoderOptions().find("--threads ") != string::npos)
			if (xs->getNbThreads() > 0)
				sb->Append("--threads " + xs->getNbThreads() + " ");

		///<summary>
		/// x264 Frame-Type Tab Settings
		///</summary>

		// H.264 Features
		if (xs->getDeblock() && !xs->getCustomEncoderOptions().find("--no-deblock") != string::npos)
		{
			if (!xs->getCustomEncoderOptions().find("--deblock ") != string::npos)
			{
				display = false;
				switch (xs->getx264PsyTuning())
				{
					case x264Settings::FILM:
						if (xs->getAlphaDeblock() != -1 || xs->getBetaDeblock() != -1)
							display = true;
							break;
					case x264Settings::ANIMATION:
						if (xs->getAlphaDeblock() != 1 || xs->getBetaDeblock() != 1)
							display = true;
							break;
					case x264Settings::GRAIN:
						if (xs->getAlphaDeblock() != -2 || xs->getBetaDeblock() != -2)
							display = true;
							break;
					case x264Settings::STILLIMAGE:
						if (xs->getAlphaDeblock() != 3 || xs->getBetaDeblock() != -3)
							display = true;
							break;
					default:
						if (xs->getAlphaDeblock() != 0 || xs->getBetaDeblock() != 0)
							display = true;
							break;
				}
				if (display)
					sb->Append("--deblock " + xs->getAlphaDeblock() + ":" + xs->getBetaDeblock() + " ");
			}
		}
		else
		{
			if (!xs->getCustomEncoderOptions().find("--no-deblock") != string::npos)
				if (xs->getx264PresetLevel() != x264Settings::ultrafast && !xs->getTuneFastDecode())
					sb->Append("--no-deblock ");
		}

		if (xs->getProfile() > 0 && !xs->getCustomEncoderOptions().find("--no-cabac") != string::npos)
		{
			if (!xs->getCabac())
			{
				if (xs->getx264PresetLevel() != x264Settings::ultrafast && !xs->getTuneFastDecode())
					sb->Append("--no-cabac ");
			}
		}

		// GOP Size
		int iBackupKeyframeInterval = xs->getKeyframeInterval();
		int iBackupMinGOPSize = xs->getMinGOPSize();

		xs->setKeyframeInterval(oSettingsHandler->getKeyInt(fps_n, fps_d));
		if (xs->getKeyframeInterval() != 250) // gop size of 250 is default
		{
			if (xs->getKeyframeInterval() == 0)
				sb->Append("--keyint infinite ");
			else
				sb->Append("--keyint " + xs->getKeyframeInterval() + " ");
		}

		if (!xs->getBlurayCompat())
		{
			xs->setMinGOPSize(oSettingsHandler->getMinKeyint(fps_n, fps_d));
			if (xs->getMinGOPSize() > (xs->getKeyframeInterval() / 2 + 1))
			{
				xs->setMinGOPSize(xs->getKeyframeInterval() / 2 + 1);
				if (log != 0)
					log->LogEvent("--min-keyint bigger as --keyint/2+1. Lowering --min-keyint to max value: " + xs->getMinGOPSize(), Warning);
			}
			int iDefault = xs->getKeyframeInterval() / 10;
			if (log != 0)
				iDefault = __min(xs->getKeyframeInterval() / 10, fps_n / fps_d);
			if (xs->getMinGOPSize() != iDefault) // (MIN(--keyint / 10,--fps)) is default
				sb->Append("--min-keyint " + xs->getMinGOPSize() + " ");
		}

		xs->setKeyframeInterval(iBackupKeyframeInterval);
		xs->setMinGOPSize(iBackupMinGOPSize);

		if (!xs->getCustomEncoderOptions().find("--open-gop") != string::npos && (xs->getOpenGopValue() || xs->getTargetDevice()->getBluRay()))
			sb->Append("--open-gop ");

		// B-Frames
		xs->setNbBframes(oSettingsHandler->getBFrames());
		if (xs->getProfile() > 0 && xs->getNbBframes() != x264Settings::GetDefaultNumberOfBFrames(xs->getx264PresetLevel(), xs->getx264PsyTuning(), xs->getTuneZeroLatency(), xs->getProfile(), 0, xs->getBlurayCompat()))
			sb->Append("--bframes " + xs->getNbBframes() + " ");

		if (xs->getNbBframes() > 0)
		{
			if (!xs->getCustomEncoderOptions().find("-b-adapt") != string::npos)
			{
				display = false;
				if (xs->getx264PresetLevel() > x264Settings::medium)
				{
					if (xs->getNewAdaptiveBFrames() != 2)
						display = true;
				}
				else if (xs->getx264PresetLevel() > x264Settings::ultrafast)
				{
					if (xs->getNewAdaptiveBFrames() != 1)
						display = true;
				}
				else
				{
					if (xs->getNewAdaptiveBFrames() != 0)
						display = true;
				}
				if (display)
					sb->Append("--b-adapt " + xs->getNewAdaptiveBFrames() + " ");
			}

			xs->setx264BFramePyramid(oSettingsHandler->getBPyramid());
			if (xs->getNbBframes() > 1 && ((xs->getx264BFramePyramid() != 2 && !xs->getBlurayCompat()) || (xs->getx264BFramePyramid() != 1 && xs->getBlurayCompat())))
			{
				switch (xs->getx264BFramePyramid()) // pyramid needs a minimum of 2 b frames
				{
					case 1:
						sb->Append("--b-pyramid strict ");
						break;
					case 0:
						sb->Append("--b-pyramid none ");
						break;
				}
			}

			if (!xs->getCustomEncoderOptions().find("--no-weightb") != string::npos)
				if (!xs->getWeightedBPrediction() && !xs->getTuneFastDecode() && xs->getx264PresetLevel() != x264Settings::ultrafast)
					sb->Append("--no-weightb ");
		}

		// B-Frames bias
		if (!xs->getCustomEncoderOptions().find("--b-bias ") != string::npos)
			if (xs->getBframeBias() != 0.0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				sb->Append("--b-bias " + xs->getBframeBias().ToString(ci) + " ");

		// Other
		if (xs->getScenecut())
		{
			if (!xs->getCustomEncoderOptions().find("--scenecut ") != string::npos)
				if ((xs->getSCDSensitivity() != 40 && xs->getx264PresetLevel() != x264Settings::ultrafast) || (xs->getSCDSensitivity() != 0 && xs->getx264PresetLevel() == x264Settings::ultrafast))
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sb->Append("--scenecut " + xs->getSCDSensitivity().ToString(ci) + " ");
		}
		else
		{
			if (!xs->getCustomEncoderOptions().find("--no-scenecut") != string::npos)
				if (xs->getx264PresetLevel() != x264Settings::ultrafast)
					sb->Append("--no-scenecut ");
		}

		// reference frames
		int iRefFrames = oSettingsHandler->getRefFrames(hres, vres);
		if (iRefFrames != x264Settings::GetDefaultNumberOfRefFrames(xs->getx264PresetLevel(), xs->getx264PsyTuning(), 0, xs->getAVCLevel(), xs->getBlurayCompat(), hres, vres))
			sb->Append("--ref " + iRefFrames + " ");

		// WeightedPPrediction
		xs->setWeightedPPrediction(oSettingsHandler->getWeightp());
		if (xs->getWeightedPPrediction() != x264Settings::GetDefaultNumberOfWeightp(xs->getx264PresetLevel(), xs->getTuneFastDecode(), xs->getProfile(), xs->getBlurayCompat()))
			sb->Append("--weightp " + xs->getWeightedPPrediction() + " ");

		// Slicing
		xs->setSlicesNb(oSettingsHandler->getSlices());
		if (xs->getSlicesNb() != 0)
			sb->Append("--slices " + xs->getSlicesNb() + " ");
		if (!xs->getCustomEncoderOptions().find("--slice-max-size ") != string::npos)
			if (xs->getMaxSliceSyzeBytes() != 0)
				sb->Append("--slice-max-size " + xs->getMaxSliceSyzeBytes() + " ");
		if (!xs->getCustomEncoderOptions().find("--slice-max-mbs ") != string::npos)
			if (xs->getMaxSliceSyzeMBs() != 0)
				sb->Append("--slice-max-mbs " + xs->getMaxSliceSyzeMBs() + " ");

		///<summary>
		/// x264 Rate Control Tab Settings
		/// </summary>


		if (!xs->getCustomEncoderOptions().find("--qpmin ") != string::npos)
			if (xs->getMinQuantizer() != 0)
				sb->Append("--qpmin " + xs->getMinQuantizer() + " ");
		if (!xs->getCustomEncoderOptions().find("--qpmax ") != string::npos)
			if (xs->getMaxQuantizer() != 69)
				sb->Append("--qpmax " + xs->getMaxQuantizer() + " ");
		if (!xs->getCustomEncoderOptions().find("--qpstep ") != string::npos)
			if (xs->getMaxQuantDelta() != 4)
				sb->Append("--qpstep " + xs->getMaxQuantDelta() + " ");

		if (xs->getIPFactor() != 1.4)
		{
			if (!xs->getCustomEncoderOptions().find("--ipratio ") != string::npos)
			{
				if (xs->getx264PsyTuning() != x264Settings::GRAIN || xs->getIPFactor() != 1.1)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sb->Append("--ipratio " + xs->getIPFactor().ToString(ci) + " ");
			}
		}

		if (xs->getPBFactor() != 1.3)
		{
			if (!xs->getCustomEncoderOptions().find("--pbratio ") != string::npos)
			{
				if (xs->getx264PsyTuning() != x264Settings::GRAIN || xs->getPBFactor() != 1.1)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sb->Append("--pbratio " + xs->getPBFactor().ToString(ci) + " ");
			}
		}

		if (!xs->getCustomEncoderOptions().find("--chroma-qp-offset ") != string::npos)
			if (xs->getChromaQPOffset() != 0.0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				sb->Append("--chroma-qp-offset " + xs->getChromaQPOffset().ToString(ci) + " ");

		if (xs->getEncodingMode() != 1) // doesn't apply to CQ mode
		{
			xs->setVBVBufferSize(oSettingsHandler->getVBVBufsize(xs->getAVCLevel(), xs->getProfile() == 2));
			if (xs->getVBVBufferSize() > 0)
				sb->Append("--vbv-bufsize " + xs->getVBVBufferSize() + " ");
			xs->setVBVMaxBitrate(oSettingsHandler->getVBVMaxrate(xs->getAVCLevel(), xs->getProfile() == 2));
			if (xs->getVBVMaxBitrate() > 0)
				sb->Append("--vbv-maxrate " + xs->getVBVMaxBitrate() + " ");
			if (!xs->getCustomEncoderOptions().find("--vbv-init ") != string::npos)
				if (xs->getVBVInitialBuffer() != 0.9)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sb->Append("--vbv-init " + xs->getVBVInitialBuffer().ToString(ci) + " ");
			if (!xs->getCustomEncoderOptions().find("--ratetol ") != string::npos)
				if (xs->getBitrateVariance() != 1.0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sb->Append("--ratetol " + xs->getBitrateVariance().ToString(ci) + " ");

			if (!xs->getCustomEncoderOptions().find("--qcomp ") != string::npos)
			{
				display = true;
				if ((xs->getx264PsyTuning() == x264Settings::GRAIN && xs->getQuantCompression() == 0.8) || (xs->getx264PsyTuning() != x264Settings::GRAIN && xs->getQuantCompression() == 0.6))
					display = false;
				if (display)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sb->Append("--qcomp " + xs->getQuantCompression().ToString(ci) + " ");
			}

			if (xs->getEncodingMode() > 1) // applies only to twopass
			{
				if (!xs->getCustomEncoderOptions().find("--cplxblur ") != string::npos)
					if (xs->getTempComplexityBlur() != 20)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						sb->Append("--cplxblur " + xs->getTempComplexityBlur().ToString(ci) + " ");
				if (!xs->getCustomEncoderOptions().find("--qblur ") != string::npos)
					if (xs->getTempQuanBlurCC() != 0.5)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						sb->Append("--qblur " + xs->getTempQuanBlurCC().ToString(ci) + " ");
			}
		}

		// Dead Zones
		if (!xs->getCustomEncoderOptions().find("--deadzone-inter ") != string::npos)
		{
			display = true;
			if ((xs->getx264PsyTuning() != x264Settings::GRAIN && xs->getDeadZoneInter() == 21 && xs->getDeadZoneIntra() == 11) || (xs->getx264PsyTuning() == x264Settings::GRAIN && xs->getDeadZoneInter() == 6 && xs->getDeadZoneIntra() == 6))
				display = false;
			if (display)
				sb->Append("--deadzone-inter " + xs->getDeadZoneInter() + " ");
		}

		if (!xs->getCustomEncoderOptions().find("--deadzone-intra ") != string::npos)
		{
			display = true;
			if ((xs->getx264PsyTuning() != x264Settings::GRAIN && xs->getDeadZoneIntra() == 11) || (xs->getx264PsyTuning() == x264Settings::GRAIN && xs->getDeadZoneIntra() == 6))
				display = false;
			if (display)
				sb->Append("--deadzone-intra " + xs->getDeadZoneIntra() + " ");
		}

		// Disable Macroblok Tree
		if (!xs->getCustomEncoderOptions().find("--no-mbtree") != string::npos)
			if (!xs->getNoMBTree() && xs->getx264PresetLevel() > x264Settings::veryfast && !xs->getTuneZeroLatency())
				sb->Append("--no-mbtree ");

		// RC Lookahead
		if (!xs->getCustomEncoderOptions().find("--rc-lookahead ") != string::npos)
			if (xs->getLookahead() != x264Settings::GetDefaultRCLookahead(xs->getx264PresetLevel(), xs->getTuneZeroLatency()))
				sb->Append("--rc-lookahead " + xs->getLookahead() + " ");

		// AQ-Mode
		if (xs->getEncodingMode() != static_cast<int>(VideoCodecSettings::CQ))
		{
			if (!xs->getCustomEncoderOptions().find("--aq-mode ") != string::npos)
				if (xs->getAQmode() != x264Settings::GetDefaultAQMode(xs->getx264PresetLevel(), xs->getx264PsyTuning()))
					sb->Append("--aq-mode " + StringConverterHelper::toString(xs->getAQmode()) + " ");

			if (!xs->getCustomEncoderOptions().find("--aq-strength ") != string::npos)
			{
				if (xs->getAQmode() > 0)
				{
					display = false;
					switch (xs->getx264PsyTuning())
					{
						case x264Settings::ANIMATION:
							if (xs->getAQstrength() != 0.6)
								display = true;
								break;
						case x264Settings::GRAIN:
							if (xs->getAQstrength() != 0.5)
								display = true;
								break;
						case x264Settings::STILLIMAGE:
							if (xs->getAQstrength() != 1.2)
								display = true;
								break;
						default:
							if (xs->getAQstrength() != 1.0)
								display = true;
								break;
					}
					if (display)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						sb->Append("--aq-strength " + xs->getAQstrength().ToString(ci) + " ");
				}
			}
		}

		// custom matrices 
		if (xs->getProfile() > 1 && xs->getQuantizerMatrixType() > 0)
		{
			switch (xs->getQuantizerMatrixType())
			{
				case 1:
					if (!xs->getCustomEncoderOptions().find("--cqm ") != string::npos)
						sb->Append("--cqm \"jvt\" ");
						break;
				case 2:
					if (!xs->getCustomEncoderOptions().find("--cqmfile") != string::npos)
					{
							if (log != 0 && !System::IO::File::Exists(xs->getQuantizerMatrix()))
								log->LogEvent(xs->getQuantizerMatrix() + " not found. --cqmfile will be skipped.", Warning);
							else
								sb->Append("--cqmfile \"" + xs->getQuantizerMatrix() + "\" ");
					}
						break;
			}
		}


		///<summary>
		/// x264 Analysis Tab Settings
		/// </summary>

		// Disable Chroma Motion Estimation
		if (!xs->getCustomEncoderOptions().find("--no-chroma-me") != string::npos)
			if (!xs->getChromaME())
				sb->Append("--no-chroma-me ");

		// Motion Estimation Range
		if (!xs->getCustomEncoderOptions().find("--merange ") != string::npos)
		{
			if ((xs->getx264PresetLevel() <= x264Settings::slower && xs->getMERange() != 16) || (xs->getx264PresetLevel() >= x264Settings::veryslow && xs->getMERange() != 24))
				sb->Append("--merange " + xs->getMERange() + " ");
		}

		// ME Type
		if (!xs->getCustomEncoderOptions().find("--me ") != string::npos)
		{
			display = false;
			switch (xs->getx264PresetLevel())
			{
				case x264Settings::ultrafast:
				case x264Settings::superfast:
					if (xs->getMEType() != 0)
						display = true;
						break;
				case x264Settings::veryfast:
				case x264Settings::faster:
				case x264Settings::fast:
				case x264Settings::medium:
					if (xs->getMEType() != 1)
						display = true;
						break;
				case x264Settings::slow:
				case x264Settings::slower:
				case x264Settings::veryslow:
					if (xs->getMEType() != 2)
						display = true;
						break;
				case x264Settings::placebo:
					if (xs->getMEType() != 4)
						display = true;
						break;
			}

			if (display)
			{
				switch (xs->getMEType())
				{
					case 0:
						sb->Append("--me dia ");
						break;
					case 1:
						sb->Append("--me hex ");
						break;
					case 2:
						sb->Append("--me umh ");
						break;
					case 3:
						sb->Append("--me esa ");
						break;
					case 4:
						sb->Append("--me tesa ");
						break;
				}
			}

		}

		if (!xs->getCustomEncoderOptions().find("--direct ") != string::npos)
		{
			display = false;
			if (xs->getx264PresetLevel() > x264Settings::medium)
			{
				if (xs->getBframePredictionMode() != 3)
					display = true;
			}
			else if (xs->getBframePredictionMode() != 1)
				display = true;

			if (display)
			{
				switch (xs->getBframePredictionMode())
				{
					case 0:
						sb->Append("--direct none ");
						break;
					case 1:
						sb->Append("--direct spatial ");
						break;
					case 2:
						sb->Append("--direct temporal ");
						break;
					case 3:
						sb->Append("--direct auto ");
						break;
				}
			}
		}

		if (!xs->getCustomEncoderOptions().find("--nr ") != string::npos)
			if (xs->getNoiseReduction() > 0)
				sb->Append("--nr " + xs->getNoiseReduction() + " ");


		// subpel refinement
		if (!xs->getCustomEncoderOptions().find("--subme ") != string::npos)
		{
			display = false;
			switch (xs->getx264PresetLevel())
			{
				case x264Settings::ultrafast:
					if (xs->getSubPelRefinement() != 0)
						display = true;
						break;
				case x264Settings::superfast:
					if (xs->getSubPelRefinement() != 1)
						display = true;
						break;
				case x264Settings::veryfast:
					if (xs->getSubPelRefinement() != 2)
						display = true;
						break;
				case x264Settings::faster:
					if (xs->getSubPelRefinement() != 4)
						display = true;
						break;
				case x264Settings::fast:
					if (xs->getSubPelRefinement() != 6)
						display = true;
						break;
				case x264Settings::medium:
					if (xs->getSubPelRefinement() != 7)
						display = true;
						break;
				case x264Settings::slow:
					if (xs->getSubPelRefinement() != 8)
						display = true;
						break;
				case x264Settings::slower:
					if (xs->getSubPelRefinement() != 9)
						display = true;
						break;
				case x264Settings::veryslow:
					if (xs->getSubPelRefinement() != 10)
						display = true;
						break;
				case x264Settings::placebo:
					if (xs->getSubPelRefinement() != 11)
						display = true;
						break;
			}
			if (display)
				sb->Append("--subme " + (xs->getSubPelRefinement()) + " ");
		}

		// macroblock types
		if (!xs->getCustomEncoderOptions().find("--partitions ") != string::npos)
		{
			bool bExpectedP8x8mv = true;
			bool bExpectedB8x8mv = true;
			bool bExpectedI4x4mv = true;
			bool bExpectedI8x8mv = true;
			bool bExpectedP4x4mv = true;

			switch (xs->getx264PresetLevel())
			{
				case x264Settings::ultrafast:
					bExpectedP8x8mv = false;
					bExpectedB8x8mv = false;
					bExpectedI4x4mv = false;
																	bExpectedI8x8mv = false;
																	bExpectedP4x4mv = false;
																	break;
				case x264Settings::superfast:
					bExpectedP8x8mv = false;
					bExpectedB8x8mv = false;
					bExpectedP4x4mv = false;
					break;
				case x264Settings::veryfast:
				case x264Settings::faster:
				case x264Settings::fast:
				case x264Settings::medium:
				case x264Settings::slow:
					bExpectedP4x4mv = false;
					break;
			}

			if (xs->getProfile() < 2)
				bExpectedI8x8mv = false;

			if (bExpectedP8x8mv != xs->getP8x8mv() || bExpectedB8x8mv != xs->getB8x8mv() || bExpectedI4x4mv != xs->getI4x4mv() || bExpectedI8x8mv != xs->getI8x8mv() || bExpectedP4x4mv != xs->getP4x4mv())
			{
				if (xs->getP8x8mv() || xs->getB8x8mv() || xs->getI4x4mv() || xs->getI8x8mv() || xs->getP4x4mv())
				{
					sb->Append("--partitions ");
					if (xs->getI4x4mv() && xs->getI8x8mv() && xs->getP4x4mv() && xs->getP8x8mv() && xs->getB8x8mv())
						sb->Append("all ");
					else
					{
						if (xs->getP8x8mv()) // default is checked
							sb->Append("p8x8,");
						if (xs->getP4x4mv()) // default is unchecked
							sb->Append("p4x4,");
						if (xs->getB8x8mv()) // default is checked
							sb->Append("b8x8,");
						if (xs->getI8x8mv()) // default is checked
							sb->Append("i8x8");
						if (xs->getI4x4mv()) // default is checked
							sb->Append("i4x4,");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
						if (sb->ToString()->EndsWith(","))
							sb->Remove(sb->Length - 1, 1);
					}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
					if (!sb->ToString()->EndsWith(" "))
						sb->Append(" ");
				}
				else
					sb->Append("--partitions none ");
			}
		}

		if (xs->getProfile() > 1 && !xs->getCustomEncoderOptions().find("--no-8x8dct") != string::npos)
			if (!xs->getAdaptiveDCT())
				if (xs->getx264PresetLevel() > x264Settings::ultrafast)
					sb->Append("--no-8x8dct ");

		// Trellis
		if (!xs->getCustomEncoderOptions().find("--trellis ") != string::npos)
		{
			display = false;
			switch (xs->getx264PresetLevel())
			{
				case x264Settings::ultrafast:
				case x264Settings::superfast:
				case x264Settings::veryfast:
					if (xs->getX264Trellis() != 0)
						display = true;
						break;
				case x264Settings::faster:
				case x264Settings::fast:
				case x264Settings::medium:
				case x264Settings::slow:
					if (xs->getX264Trellis() != 1)
						display = true;
						break;
				case x264Settings::slower:
				case x264Settings::veryslow:
				case x264Settings::placebo:
					if (xs->getX264Trellis() != 2)
						display = true;
						break;
			}
			if (display)
				sb->Append("--trellis " + xs->getX264Trellis() + " ");
		}

		if (!xs->getCustomEncoderOptions().find("--psy-rd ") != string::npos)
		{
			if (xs->getSubPelRefinement() > 5)
			{
				display = false;
				switch (xs->getx264PsyTuning())
				{
					case x264Settings::FILM:
						if ((xs->getPsyRDO() != 1.0) || (xs->getPsyTrellis() != 0.15))
							display = true;
							break;
					case x264Settings::ANIMATION:
						if ((xs->getPsyRDO() != 0.4) || (xs->getPsyTrellis() != 0.0))
							display = true;
							break;
					case x264Settings::GRAIN:
						if ((xs->getPsyRDO() != 1.0) || (xs->getPsyTrellis() != 0.25))
							display = true;
							break;
					case x264Settings::STILLIMAGE:
						if ((xs->getPsyRDO() != 2.0) || (xs->getPsyTrellis() != 0.7))
							display = true;
							break;
					default:
						if ((xs->getPsyRDO() != 1.0) || (xs->getPsyTrellis() != 0.0))
							display = true;
							break;
				}

				if (display)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sb->Append("--psy-rd " + xs->getPsyRDO().ToString(ci) + ":" + xs->getPsyTrellis().ToString(ci) + " ");
			}
		}

		if (!xs->getCustomEncoderOptions().find("--no-mixed-refs") != string::npos)
			if (xs->getNoMixedRefs())
				if (xs->getx264PresetLevel() >= x264Settings::fast)
					sb->Append("--no-mixed-refs ");

		if (!xs->getCustomEncoderOptions().find("--no-dct-decimate") != string::npos)
			if (xs->getNoDCTDecimate())
				if (xs->getx264PsyTuning() != x264Settings::GRAIN)
					sb->Append("--no-dct-decimate ");

		if (!xs->getCustomEncoderOptions().find("--no-fast-pskip") != string::npos)
			if (xs->getNoFastPSkip())
				if (xs->getx264PresetLevel() != x264Settings::placebo)
					sb->Append("--no-fast-pskip ");

		if (!xs->getCustomEncoderOptions().find("--no-psy") != string::npos)
			if (xs->getNoPsy() && (xs->getx264PsyTuning() != x264Settings::PSNR && xs->getx264PsyTuning() != x264Settings::SSIM))
				sb->Append("--no-psy ");

		xs->setX264Aud(oSettingsHandler->getAud());
		if (xs->getX264Aud() && !xs->getBlurayCompat())
			sb->Append("--aud ");

		xs->setNalhrd(oSettingsHandler->getNalHrd());
		switch (xs->getNalhrd())
		{
			case 1:
				if (!xs->getBlurayCompat())
					sb->Append("--nal-hrd vbr ");
					break;
			case 2:
				sb->Append("--nal-hrd cbr ");
				break;
		}

		if (!xs->getCustomEncoderOptions().find("--non-deterministic") != string::npos)
			if (xs->getNonDeterministic())
				sb->Append("--non-deterministic ");

		///<summary>
		/// x264 Misc Tab Settings
		/// </summary>

		// QPFile
		if (!xs->getCustomEncoderOptions().find("--qpfile ") != string::npos)
		{
			if (xs->getUseQPFile())
			{
				if (xs->getEncodingMode() == 0 || xs->getEncodingMode() == 1 || xs->getEncodingMode() == 2 || xs->getEncodingMode() == 5 || xs->getEncodingMode() == 9)
				{
					if (log != 0 && !System::IO::File::Exists(xs->getQPFile()))
						log->LogEvent(xs->getQPFile() + " not found. --qpfile will be skipped.", Warning);
					else
						sb->Append("--qpfile " + "\"" + xs->getQPFile() + "\" ");
				}
			}
		}

		if (!xs->getCustomEncoderOptions().find("--psnr") != string::npos)
			if (xs->getPSNRCalculation())
				sb->Append("--psnr ");

		if (!xs->getCustomEncoderOptions().find("--ssim") != string::npos)
			if (xs->getSSIMCalculation())
				sb->Append("--ssim ");

		if (!xs->getCustomEncoderOptions().find("--range ") != string::npos)
			if (!xs->getRange().Equals("auto"))
				sb->Append("--range " + xs->getRange() + " ");

		if (!xs->getCustomEncoderOptions().find("--stitchable") != string::npos)
			if (xs->getStitchAble())
				sb->Append("--stitchable ");


		if (zones != 0 && sizeof(zones) / sizeof(zones[0]) > 0)
		{
			StringBuilder *sbZones = new StringBuilder();
			for (MeGUI::Zone::const_iterator zone = zones->begin(); zone != zones->end(); ++zone)
			{
				if ((*zone)->startFrame >= (*zone)->endFrame)
				{
					if (log != 0)
						log->LogEvent("invalid zone ignored: start=" + (*zone)->startFrame + " end=" + (*zone)->endFrame, Warning);
					continue;
				}

				sbZones->Append((*zone)->startFrame + "," + (*zone)->endFrame + ",");
				if ((*zone)->mode == Quantizer && (*zone)->modifier >= 0 && (*zone)->modifier <= 51)
				{
					sbZones->Append("q=");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sbZones->Append((*zone)->modifier->ToString(ci) + "/");
				}
				else
				{
					sbZones->Append("b=");
					double mod = static_cast<double>((*zone)->modifier) / 100.0;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sbZones->Append(mod.ToString(ci) + "/");
				}
			}
			if (sbZones->Length > 0)
			{
				sbZones->Remove(sbZones->Length - 1, 1);
				sb->Append("--zones ");
				sb->Append(sbZones);
				sb->Append(" ");
			}
		}


		// Call twice as they may be changed during CheckInputFile()
		std::string CustomSarValue;
		xs->setSampleAR(oSettingsHandler->getSar(d, hres, vres, CustomSarValue, ""));
		xs->setColorPrim(oSettingsHandler->getColorprim());
		xs->setTransfer(oSettingsHandler->getTransfer());
		xs->setColorMatrix(oSettingsHandler->getColorMatrix());
		xs->setInterlacedMode(oSettingsHandler->getInterlacedMode());
		xs->setFakeInterlaced(oSettingsHandler->getFakeInterlaced());
		xs->setPicStruct(oSettingsHandler->getPicStruct());
		xs->setX264PullDown(oSettingsHandler->getPulldown());

		oSettingsHandler->CheckInputFile(d, hres, vres, fps_n, fps_d);

		xs->setInterlacedMode(oSettingsHandler->getInterlacedMode());
		switch (xs->getInterlacedMode())
		{
			case x264Settings::bff:
				sb->Append("--bff ");
				break;
			case x264Settings::tff:
				sb->Append("--tff ");
				break;
		}

		xs->setFakeInterlaced(oSettingsHandler->getFakeInterlaced());
		if (xs->getFakeInterlaced() && xs->getInterlacedMode() == x264Settings::progressive)
			sb->Append("--fake-interlaced ");

		xs->setPicStruct(oSettingsHandler->getPicStruct());
		if (xs->getPicStruct() && xs->getInterlacedMode() == x264Settings::progressive && xs->getX264PullDown() == 0)
			sb->Append("--pic-struct ");

		xs->setColorPrim(oSettingsHandler->getColorprim());
		switch (xs->getColorPrim())
		{
			case 0:
				break;
			case 1:
				sb->Append("--colorprim bt709 ");
				break;
			case 2:
				sb->Append("--colorprim bt470m ");
				break;
			case 3:
				sb->Append("--colorprim bt470bg ");
				break;
			case 4:
				sb->Append("--colorprim smpte170m ");
				break;
			case 5:
				sb->Append("--colorprim smpte240m ");
				break;
			case 6:
				sb->Append("--colorprim film ");
				break;
		}

		xs->setTransfer(oSettingsHandler->getTransfer());
		switch (xs->getTransfer())
		{
			case 0:
				break;
			case 1:
				sb->Append("--transfer bt709 ");
				break;
			case 2:
				sb->Append("--transfer bt470m ");
				break;
			case 3:
				sb->Append("--transfer bt470bg ");
				break;
			case 4:
				sb->Append("--transfer linear ");
				break;
			case 5:
				sb->Append("--transfer log100 ");
				break;
			case 6:
				sb->Append("--transfer log316 ");
				break;
			case 7:
				sb->Append("--transfer smpte170m ");
				break;
			case 8:
				sb->Append("--transfer smpte240m ");
				break;
		}

		xs->setColorMatrix(oSettingsHandler->getColorMatrix());
		switch (xs->getColorMatrix())
		{
			case 0:
				break;
			case 1:
				sb->Append("--colormatrix bt709 ");
				break;
			case 2:
				sb->Append("--colormatrix fcc ");
				break;
			case 3:
				sb->Append("--colormatrix bt470bg ");
				break;
			case 4:
				sb->Append("--colormatrix smpte170m ");
				break;
			case 5:
				sb->Append("--colormatrix smpte240m ");
				break;
			case 6:
				sb->Append("--colormatrix GBR ");
				break;
			case 7:
				sb->Append("--colormatrix YCgCo ");
				break;
		}

		xs->setX264PullDown(oSettingsHandler->getPulldown());
		switch (xs->getX264PullDown())
		{
			case 0:
				break;
			case 1:
				sb->Append("--pulldown 22 ");
				break;
			case 2:
				sb->Append("--pulldown 32 ");
				break;
			case 3:
				sb->Append("--pulldown 64 ");
				break;
			case 4:
				sb->Append("--pulldown double ");
				break;
			case 5:
				sb->Append("--pulldown triple ");
				break;
			case 6:
				sb->Append("--pulldown euro ");
				break;
		}

		xs->setCustomEncoderOptions(oSettingsHandler->getCustomCommandLine());
		if (!xs->getCustomEncoderOptions().empty()) // add custom encoder options
			sb->Append(xs->getCustomEncoderOptions() + " ");

		std::string strTemp;
		xs->setSampleAR(oSettingsHandler->getSar(d, hres, vres, strTemp, CustomSarValue));
		switch (xs->getSampleAR())
		{
			case 0:
			{
					if (!CustomSarValue.empty())
						sb->Append("--sar " + CustomSarValue + " ");
					break;
			}
			case 1:
				sb->Append("--sar 1:1 ");
				break;
			case 2:
				sb->Append("--sar 4:3 ");
				break;
			case 3:
				sb->Append("--sar 8:9 ");
				break;
			case 4:
				sb->Append("--sar 10:11 ");
				break;
			case 5:
				sb->Append("--sar 12:11 ");
				break;
			case 6:
				sb->Append("--sar 16:11 ");
				break;
			case 7:
				sb->Append("--sar 32:27 ");
				break;
			case 8:
				sb->Append("--sar 40:33 ");
				break;
			case 9:
				sb->Append("--sar 64:45 ");
				break;
		}

		//add the rest of the commandline regarding the output
		if (xs->getEncodingMode() == 2 || xs->getEncodingMode() == 5)
			sb->Append("--output NUL ");
		else if (!output.empty())
			sb->Append("--output " + "\"" + output + "\" ");
		if (!input.empty())
			sb->Append("\"" + input + "\" ");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}

	const std::string &x264Encoder::getCommandline() const
	{
		return genCommandline(job->Input, job->Output, job->getDAR(), hres, vres, fps_n, fps_d, dynamic_cast<x264Settings*>(job->getSettings()), job->getZones(), CommandlineVideoEncoder::log);
	}

	void x264Encoder::doExitConfig()
	{
		if (proc->ExitCode != 0 && !su->getWasAborted() && OSInfo::isWow64() && MainForm::Instance->getSettings()->getUse64bitX264())
			log->LogEvent("The 64 bit mode of x264 is enabled. Depending on the error it may help to disable it in the MeGUI settings.", Warning);

		CommandlineVideoEncoder::doExitConfig();
	}
}
