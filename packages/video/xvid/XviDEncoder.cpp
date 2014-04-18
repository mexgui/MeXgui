#include "XviDEncoder.h"




//using namespace System::Collections::Generic;

//using namespace System::Globalization;



//using namespace System::Text;


using namespace MeXgui::core::plugins::implemented;
using namespace MeXgui::core::util;

namespace MeXgui
{

JobProcessorFactory *const XviDEncoder::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "XviDEncoder");

	IJobProcessor *XviDEncoder::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<VideoJob*>(j) != 0 && dynamic_cast<xvidSettings*>((dynamic_cast<VideoJob*>(j))->getSettings()) != 0)
			return new XviDEncoder(mf->getSettings()->getXviDEncrawPath());
		return 0;
	}

	XviDEncoder::XviDEncoder(const QString &exePath) : CommandlineVideoEncoder()
	{
		executable = exePath;
	}

	void XviDEncoder::ProcessLine(const QString &line, StreamType stream, ImageType oType)
	{
		if (line.find(": key") != -1) // we found a position line, parse it
		{
			int frameNumberEnd = line.find(":");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			if (CommandlineVideoEncoder::setFrameNumber(line.substr(0, frameNumberEnd)->Trim()))
				return;
		}

		if (line.ToLowerInvariant()->Contains("error") || line.ToLowerInvariant()->Contains("usage") || line.ToLowerInvariant()->Contains("avistreamwrite")) // we get the usage message if there's an unrecognized parameter
			oType = Error;
		else if (line.ToLowerInvariant()->Contains("warning"))
			oType = Warning;
		CommandlineVideoEncoder::ProcessLine(line, stream, oType);
	}

	const QString &XviDEncoder::getCommandline() const
	{
		return genCommandline(job->Input, job->Output, job->getDAR(), dynamic_cast<xvidSettings*>(job->getSettings()), hres, vres, job->getZones());
	}

	QString XviDEncoder::genCommandline(const QString &input, const QString &output, Nullable<Dar> d, xvidSettings *xs, int hres, int vres, Zone zones[])
	{
		StringBuilder *sb = new StringBuilder();
		CultureInfo *ci = new CultureInfo("en-us");
		sb->Append("-i \"" + input + "\" ");
		switch (xs->getEncodingMode())
		{
			case 0: // CBR
				sb->Append("-single -bitrate " + xs->getBitrateQuantizer() + " "); // add bitrate
				break;
			case 1: // CQ
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				sb->Append("-single -cq " + xs->getQuantizer().ToString(ci) + " "); // add quantizer
				break;
			case 2: // 2 pass first pass
				sb->Append("-pass1 " + "\"" + xs->getLogfile() + "\" -bitrate " + xs->getBitrateQuantizer() + " "); // add logfile
				break;
			case 3: // 2 pass second pass
			case 4: // automated twopass
				sb->Append("-pass2 " + "\"" + xs->getLogfile() + "\" -bitrate " + xs->getBitrateQuantizer() + " "); // add logfile
				break;
		}
		if (xs->getEncodingMode() <= 1) // 1 pass modes
		{
			if (!xs->getCustomEncoderOptions().find("-reaction ") != string::npos && xs->getReactionDelayFactor() != 16)
				sb->Append("-reaction " + xs->getReactionDelayFactor() + " ");
			if (!xs->getCustomEncoderOptions().find("-averaging ") != string::npos && xs->getAveragingPeriod() != 100)
				sb->Append("-averaging " + xs->getAveragingPeriod() + " ");
			if (!xs->getCustomEncoderOptions().find("-smoother ") != string::npos && xs->getRateControlBuffer() != 100)
				sb->Append("-smoother " + xs->getRateControlBuffer() + " ");
		}
		else // two pass modes
		{
			if (!xs->getCustomEncoderOptions().find("-kboost ") != string::npos && xs->getKeyFrameBoost() != 10)
				sb->Append("-kboost " + xs->getKeyFrameBoost() + " ");
			if (!xs->getCustomEncoderOptions().find("-kthresh ") != string::npos && xs->getKeyframeThreshold() != 1)
				sb->Append("-kthresh " + xs->getKeyframeThreshold() + " ");
			if (!xs->getCustomEncoderOptions().find("-kreduction ") != string::npos && xs->getKeyframeReduction() != 20)
				sb->Append("-kreduction " + xs->getKeyframeReduction() + " ");
			if (!xs->getCustomEncoderOptions().find("-ostrength ") != string::npos && xs->getOverflowControlStrength() != 5)
				sb->Append("-ostrength " + xs->getOverflowControlStrength() + " ");
			if (!xs->getCustomEncoderOptions().find("-oimprove ") != string::npos && xs->getMaxOverflowImprovement() != 5)
				sb->Append("-oimprove " + xs->getMaxOverflowImprovement() + " ");
			if (!xs->getCustomEncoderOptions().find("-odegrade ") != string::npos && xs->getMaxOverflowDegradation() != 5)
				sb->Append("-odegrade " + xs->getMaxOverflowDegradation() + " ");
			if (!xs->getCustomEncoderOptions().find("-chigh ") != string::npos && xs->getHighBitrateDegradation() != 0)
				sb->Append("-chigh " + xs->getHighBitrateDegradation() + " ");
			if (!xs->getCustomEncoderOptions().find("-clow ") != string::npos && xs->getLowBitrateImprovement() != 0)
				sb->Append("-clow " + xs->getLowBitrateImprovement() + " ");
			if (xs->getXvidProfile() != 0)
			{
				int ivbvmax = 0, ivbvsize = 0, ivbvpeak = 0;
				switch (xs->getXvidProfile())
				{
					case 1:
						ivbvmax = 4854000;
						ivbvsize = 3145728;
						ivbvpeak = 2359296;
						break;
					case 2:
						ivbvmax = 9708400;
						ivbvsize = 6291456;
						ivbvpeak = 4718592;
						break;
					case 3:
						ivbvmax = 20000000;
						ivbvsize = 16000000;
						ivbvpeak = 12000000;
						break;
					case 4:
						ivbvmax = 200000;
						ivbvsize = 262144;
						ivbvpeak = 196608;
						break;
					case 5:
						ivbvmax = 600000;
						ivbvsize = 655360;
						ivbvpeak = 491520;
						break;
					case 6:
						ivbvmax = xs->getVbvMaxRate();
						ivbvsize = xs->getVbvBuffer();
						ivbvpeak = xs->getVbvPeakRate();
						break;
				}
				if (!xs->getCustomEncoderOptions().find("-vbvsize ") != string::npos && ivbvsize != 0)
					sb->Append("-vbvsize " + ivbvsize + " ");
				if (!xs->getCustomEncoderOptions().find("-vbvmax ") != string::npos && ivbvmax != 0)
					sb->Append("-vbvmax " + ivbvmax + " ");
				if (!xs->getCustomEncoderOptions().find("-vbvpeak ") != string::npos && ivbvpeak != 0)
					sb->Append("-vbvpeak " + ivbvpeak + " ");
			}
		}
		if (!xs->getCustomEncoderOptions().find("-turbo") != string::npos && xs->getTurbo())
			sb->Append("-turbo ");
		if (!xs->getCustomEncoderOptions().find("-max_key_interval ") != string::npos && xs->getKeyframeInterval() != 300)
			sb->Append("-max_key_interval " + xs->getKeyframeInterval() + " ");
		if (!xs->getCustomEncoderOptions().find("-nopacked") != string::npos && !xs->getPackedBitstream()) // default is on in encraw
			sb->Append("-nopacked ");
		if (!xs->getCustomEncoderOptions().find("-quality ") != string::npos && xs->getMotionSearchPrecision() != 6)
			sb->Append("-quality " + xs->getMotionSearchPrecision() + " ");
		if (!xs->getCustomEncoderOptions().find("-vhqmode ") != string::npos && xs->getVHQMode() != 1)
			sb->Append("-vhqmode " + xs->getVHQMode() + " ");
		if (!xs->getCustomEncoderOptions().find("-qpel ") != string::npos && xs->getQPel())
			sb->Append("-qpel ");
		if (!xs->getCustomEncoderOptions().find("-gmc ") != string::npos && xs->getGMC())
			sb->Append("-gmc ");
		if (!xs->getCustomEncoderOptions().find("-qtype ") != string::npos && xs->getQuantizerMatrix() == xvidSettings::MPEGMatrix)
			sb->Append("-qtype 1 ");
		else if (!xs->getCustomEncoderOptions().find("-qmatrix ") != string::npos && xs->getQuantizerMatrix() != xvidSettings::H263Matrix && !xs->getQuantizerMatrix().empty())
			sb->Append("-qmatrix \"" + xs->getQuantizerMatrix() + "\" ");
		if (!xs->getCustomEncoderOptions().find("-interlaced ") != string::npos && xs->getInterlaced())
		{
			sb->Append("-interlaced ");
			if (xs->getBottomFieldFirst())
				sb->Append("1 ");
			else
				sb->Append("2 ");
		}
		if (!xs->getCustomEncoderOptions().find("-lumimasking") != string::npos && xs->getHVSMasking() != 0)
			sb->Append("-lumimasking ");
		if (!xs->getCustomEncoderOptions().find("-notrellis") != string::npos && !xs->getTrellis())
			sb->Append("-notrellis ");
		if (!xs->getCustomEncoderOptions().find("-nochromame") != string::npos && !xs->getChromaMotion())
			sb->Append("-nochromame ");
		if (!xs->getCustomEncoderOptions().find("-imin ") != string::npos && xs->getMinQuantizer() != 2)
			sb->Append("-imin " + xs->getMinQuantizer() + " ");
		if (!xs->getCustomEncoderOptions().find("-imax ") != string::npos && xs->getMaxQuantizer() != 31)
			sb->Append("-imax " + xs->getMaxQuantizer() + " ");
		if (!xs->getCustomEncoderOptions().find("-pmin ") != string::npos && xs->getMinPQuant() != 2)
			sb->Append("-pmin " + xs->getMinPQuant() + " ");
		if (!xs->getCustomEncoderOptions().find("-pmax ") != string::npos && xs->getMaxPQuant() != 31)
			sb->Append("-pmax " + xs->getMaxPQuant() + " ");
		if (!xs->getCustomEncoderOptions().find("-noclosed_gop") != string::npos && !xs->getClosedGOP())
			sb->Append("-noclosed_gop ");
		if (!xs->getCustomEncoderOptions().find("-drop ") != string::npos && xs->getFrameDropRatio() != 0)
			sb->Append("-drop " + xs->getFrameDropRatio() + " ");
		if (!xs->getCustomEncoderOptions().find("-max_bframes ") != string::npos && xs->getNbBframes() != 2)
			sb->Append("-max_bframes " + xs->getNbBframes() + " ");
		if (xs->getNbBframes() > 0)
		{
			if (!xs->getCustomEncoderOptions().find("-bvhq ") != string::npos && xs->getVHQForBframes())
				sb->Append("-bvhq ");
			if (!xs->getCustomEncoderOptions().find("-bquant_ratio ") != string::npos && xs->getBQuantRatio() != 150)
				sb->Append("-bquant_ratio " + xs->getBQuantRatio() + " ");
			if (!xs->getCustomEncoderOptions().find("-bquant_offset ") != string::npos && xs->getBQuantOffset() != 100)
				sb->Append("-bquant_offset " + xs->getBQuantOffset() + " ");
			if (!xs->getCustomEncoderOptions().find("-bmin ") != string::npos && xs->getMinBQuant() != 2)
				sb->Append("-bmin " + xs->getMinBQuant() + " ");
			if (!xs->getCustomEncoderOptions().find("-bmax ") != string::npos && xs->getMaxBQuant() != 31)
				sb->Append("-bmax " + xs->getMaxBQuant() + " ");
		}
		if (!xs->getCustomEncoderOptions().find("-par ") != string::npos && d.HasValue) // custom PAR mode
		{
			Sar s = d.Value::ToSar(hres, vres);
			if (s.getX() == 1 && s.getY() == 1)
				sb->Append("-par 1 ");
			else if (s.getX() == 12 && s.getY() == 11)
				sb->Append("-par 2 ");
			else if (s.getX() == 10 && s.getY() == 11)
				sb->Append("-par 3 ");
			else if (s.getX() == 16 && s.getY() == 11)
				sb->Append("-par 4 ");
			else if (s.getX() == 40 && s.getY() == 33)
				sb->Append("-par 5 ");
			else
				sb->Append("-par " + s.getX() + ":" + s.getY() + " ");
		}
		if (!xs->getCustomEncoderOptions().find("-threads ") != string::npos && xs->getNbThreads() > 0)
			sb->Append("-threads " + xs->getNbThreads() + " ");
		if (zones != 0 && sizeof(zones) / sizeof(zones[0]) > 0 && xs->getCreditsQuantizer() >= decimal(1) && xs->getEncodingMode() != 1) // only for non CQ mode at the moment
		{
			for (MeXgui::Zone::const_iterator zone = zones->begin(); zone != zones->end(); ++zone)
			{
				if ((*zone)->mode == Quantizer)
					sb->Append("-zq " + (*zone)->startFrame + " " + (*zone)->modifier + " ");
				if ((*zone)->mode == Weight)
				{
					sb->Append("-zw " + (*zone)->startFrame + " ");
					double mod = static_cast<double>((*zone)->modifier) / 100.0;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					sb->Append(mod.ToString(ci) + " ");
				}
			}
		}
		if (xs->getEncodingMode() != 2) // not 2 pass vbr first pass, add output filename and output type
		{
			QString extension = Path::GetExtension(output)->ToLower(System::Globalization::CultureInfo::InvariantCulture);
			if (extension.Equals(".mkv"))
				sb->Append("-mkv \"" + output + "\"");
			else if (extension.Equals(".avi"))
				sb->Append("-avi \"" + output + "\"");
			else
				sb->Append("-o \"" + output + "\"");
		}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		if (!(xs->getCustomEncoderOptions().Trim())->empty()) // add custom encoder options
			sb->Append(" " + xs->getCustomEncoderOptions());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}
}
