#include "PrettyFormatting.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

			std::string PrettyFormatting::ExtractWorkingName(const std::string &fileName, const std::string &strLeading, const std::string &strReplace, const std::string &strReplaceWith)
			{
				std::string A = Path::GetFileNameWithoutExtension(fileName); // In case they all fail

				int count = 0;
				while (!(Path::GetDirectoryName(fileName))->empty() && count < 3)
				{
					std::string temp = Path::GetFileNameWithoutExtension(fileName);
					// Fix to only assume extracted DVD source in fileName starts with video_/vts_/audio_
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
					if (!temp.StartsWith("vts_") && !temp.StartsWith("video_") && !temp.StartsWith("audio_"))
					{
						// we could potentially stop at video/audio
						int idxVideo = temp.find("video");
						int idxAudio = temp.find("audio");
						if (idxVideo < 3) // Too close to start, ignore
							idxVideo = temp.length();
						if (idxAudio < 3)
							idxAudio = temp.length();
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
						A = temp.substr(0, __min(idxVideo, idxAudio))->Trim();
						break;
					}
					fileName = Path::GetDirectoryName(fileName);
					count++;
				}

				// Format it nicely:
				if (!strReplace.empty())
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					A = A.Replace(strReplace, strReplaceWith);
				return strLeading + A;
			}

Regex *const PrettyFormatting::delayRegex = new Regex("(?<match>-?[0-9]+)ms");

			Nullable<int> PrettyFormatting::getDelayAndCheck(const std::string &filename)
			{
				Nullable<int> delay = getDelay(filename);

				if (delay.HasValue && abs(delay.Value) > 10000)
				{
					if (MessageBox::Show(std::string::Format("Your input filename suggests the delay is {0}ms ({1}s), " + "which is surprisingly large. Try checking the tool used to create this file to see " + "if it got the delay wrong.\n\nAre you sure this delay is correct?", delay, (delay / 1000)), "Very large delay", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == DialogResult::No)
						delay = Nullable<int>();
				}

				return delay;
			}

			Nullable<int> PrettyFormatting::getDelay(const std::string &fileName)
			{
				try
				{
					return int::Parse(delayRegex->Match(fileName)->Groups["match"]->Value);
				}
				catch (std::exception &e1)
				{
					return 0;
				}
			}

			std::string PrettyFormatting::ReplaceDelay(const std::string &fileName, int delay)
			{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				return delayRegex->Replace(fileName, delay + "ms", 1);
			}

			std::string PrettyFormatting::ReplaceFPSValue(const std::string &fpsIn)
			{
				std::string fpsOut = "25";
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				fpsIn = fpsIn.Replace(',', '.');

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//				switch (fpsIn)
//ORIGINAL LINE: case "23.976" :
				if (fpsIn == "23.976")
				{
						fpsOut = "24000/1001";
				}
//ORIGINAL LINE: case "24.0" :
				else if (fpsIn == "24.0")
				{
						fpsOut = "24";
				}
//ORIGINAL LINE: case "25.0" :
				else if (fpsIn == "25.0")
				{
						fpsOut = "25";
				}
//ORIGINAL LINE: case "29.97" :
				else if (fpsIn == "29.97")
				{
						fpsOut = "30000/1001";
				}
//ORIGINAL LINE: case "30.0" :
				else if (fpsIn == "30.0")
				{
						fpsOut = "30";
				}
//ORIGINAL LINE: case "50.0" :
				else if (fpsIn == "50.0")
				{
						fpsOut = "50";
				}
//ORIGINAL LINE: case "59.94" :
				else if (fpsIn == "59.94")
				{
						fpsOut = "60000/1001";
				}
//ORIGINAL LINE: case "60.0" :
				else if (fpsIn == "60.0")
				{
						fpsOut = "60";
				}
				else
				{
						fpsOut = fpsIn;
				}

				return fpsOut;
			}
		}
	}
}
