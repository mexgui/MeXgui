#include "PrettyFormatting.h"




//using namespace System::Collections::Generic;



//using namespace System::Text;

//using namespace System::Text::RegularExpressions;


namespace MeXgui
{
	namespace core
	{
		namespace util
		{

			QString PrettyFormatting::ExtractWorkingName(const QString &fileName, const QString &strLeading, const QString &strReplace, const QString &strReplaceWith)
			{
				QString A = Path::GetFileNameWithoutExtension(fileName); // In case they all fail

				int count = 0;
				while (!(Path::GetDirectoryName(fileName))->empty() && count < 3)
				{
					QString temp = Path::GetFileNameWithoutExtension(fileName);
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

			Nullable<int> PrettyFormatting::getDelayAndCheck(const QString &filename)
			{
				Nullable<int> delay = getDelay(filename);

				if (delay.HasValue && abs(delay.Value) > 10000)
				{
					if (MessageBox::Show(QString::Format("Your input filename suggests the delay is {0}ms ({1}s), " + "which is surprisingly large. Try checking the tool used to create this file to see " + "if it got the delay wrong.\n\nAre you sure this delay is correct?", delay, (delay / 1000)), "Very large delay", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == DialogResult::No)
						delay = Nullable<int>();
				}

				return delay;
			}

			Nullable<int> PrettyFormatting::getDelay(const QString &fileName)
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

			QString PrettyFormatting::ReplaceDelay(const QString &fileName, int delay)
			{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
				return delayRegex->Replace(fileName, delay + "ms", 1);
			}

			QString PrettyFormatting::ReplaceFPSValue(const QString &fpsIn)
			{
				QString fpsOut = "25";
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
