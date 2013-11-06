#include "Calculator.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::tools::calculator;
using namespace MeGUI::Properties;

namespace MeGUI
{

	const std::string &CalculatorTool::getName() const
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
			unsigned long long nbFrames = 0;
			double framerate = 0.0;
			int hRes = 0, vRes = 0;
			Dar dar = Dar();

			if (!info->getVideo()->getVideoInput().empty())
				JobUtil::GetAllInputProperties(nbFrames, framerate, hRes, vRes, dar, info->getVideo()->getVideoInput());

			calc->SetDefaults(nbFrames, framerate, hRes, vRes, info->getVideo()->getCurrentSettings(), info->getAudio()->getAudioStreams());

			DialogResult *dr = calc->ShowDialog();
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

	const std::string &CalculatorTool::getID() const
	{
		return "bitrate_calculator_window";
	}
}
