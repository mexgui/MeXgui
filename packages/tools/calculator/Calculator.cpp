#include "Calculator.h"




//using namespace System::Linq;

//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;






using namespace MeXgui::core::details;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::calculator;
using namespace MeXgui::Properties;

namespace MeXgui
{

	const QString &CalculatorTool::getName() const
	{
		return "Bitrate Calculator";
	}

	void CalculatorTool::Run(MainForm *info)
	{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Calculator calc = new Calculator(info))
		Calculator *calc = new Calculator(info);
		try
		{
			quint64 nbFrames = 0;
			double framerate = 0.0;
			int hRes = 0, vRes = 0;
			Dar dar = Dar();

			if (!info->getVideo()->getVideoInput().empty())
				JobUtil::GetAllInputProperties(nbFrames, framerate, hRes, vRes, dar, info->getVideo()->getVideoInput());

			calc->SetDefaults(nbFrames, framerate, hRes, vRes, info->getVideo()->getCurrentSettings(), info->getAudio()->getAudioStreams());

			DialogResult *dr = calc->show();
			if (dr != DialogResult::OK)
				return;

			if (info->getVideo()->getCurrentSettings()->getEncoderType() != calc->getSelectedVCodec())
				return;

			VideoCodecSettings *settings = info->getVideo()->getCurrentSettings();

			if (settings->getEncodingMode() == 1 || settings->getEncodingMode() == 9)
			{
				dr = MessageBox::Show("Copy calculated bitrate into current video settings and change encoding mode to automated " + info->getSettings()->getNbPasses() + "-pass?", "Save calculated bitrate?", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
				if (dr != DialogResult::Yes)
					return;
				if (info->getSettings()->getNbPasses() == 3)
					settings->setEncodingMode(8); // Automated 3-pass
				else
					settings->setEncodingMode(4); // Automated 2-pass
			}
			else
			{
				dr = MessageBox::Show("Copy calculated bitrate into current video settings?", "Save calculated bitrate?", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
				if (dr != DialogResult::Yes)
					return;
			}
			settings->setBitrateQuantizer(calc->getVideoBitrate());
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (calc != 0)
				calc.Dispose();
		}
	}

	const Shortcut &CalculatorTool::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlB};
	}

	const QString &CalculatorTool::getID() const
	{
		return "bitrate_calculator_window";
	}
}
