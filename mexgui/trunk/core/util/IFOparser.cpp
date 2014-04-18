#include "IFOparser.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

			std::string IFOparser::DetermineMovieIFO(const std::string &inputPath)
			{
				// The first 7 characters are the same for each VOB set, e.g.
				// VTS_24_0.VOB, VTS_24_1.VOB etc.
//ORIGINAL LINE: string[] vobFiles = Directory.GetFiles(inputPath, "vts*.vob");
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				std::string *vobFiles = Directory::GetFiles(inputPath, "vts*.vob");
				if (sizeof(vobFiles) / sizeof(vobFiles[0]) == 0)
					return 0;

				// Look for the largest VOB set
				std::string vtsNameCurrent;
				std::string vtsNamePrevious = Path::GetFileName(vobFiles[0])->substr(0, 7);
				long long vtsSizeLargest = 0;
				long long vtsSize = 0;
				std::string vtsNumber = "01";
				for (std::string::const_iterator file = vobFiles->begin(); file != vobFiles->end(); ++file)
				{
					vtsNameCurrent = Path::GetFileName(*file)->substr(0, 7);
					if (vtsNameCurrent.Equals(vtsNamePrevious))
						vtsSize += (new FileInfo(*file))->Length;
					else
					{
						if (vtsSize > vtsSizeLargest)
						{
							vtsSizeLargest = vtsSize;
							vtsNumber = vtsNamePrevious.substr(4, 2);
						}
						vtsNamePrevious = vtsNameCurrent;
						vtsSize = (new FileInfo(*file))->Length;
					}
				}
				// Check whether the last one isn't the largest
				if (vtsSize > vtsSizeLargest)
					vtsNumber = vtsNamePrevious.substr(4, 2);

				std::string ifoFile = inputPath + Path::DirectorySeparatorChar + "VTS_" + vtsNumber + "_0.IFO";
				// Name of largest VOB set is the name of the IFO, so we can now create the IFO file
				return ifoFile;
			}

			unsigned char *IFOparser::GetFileBlock(const std::string &strFile, long long pos, int count)
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (FileStream stream = new FileStream(strFile, FileMode.Open, FileAccess.Read, FileShare.Read))
				FileStream *stream = new FileStream(strFile, FileMode->Open, FileAccess::Read, FileShare::Read);
				try
				{
					unsigned char buf[count];
					stream->Seek(pos, SeekOrigin::Begin);
					if (stream->Read(buf, 0, count) != count)
						return buf;
					return buf;
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (stream != 0)
						stream.Dispose();
				}
			}

			short IFOparser::ToInt16(unsigned char bytes[])
			{
				return static_cast<short>((bytes[0] << 8) + bytes[1]);
			}

			unsigned int IFOparser::ToInt32(unsigned char bytes[])
			{
				return static_cast<unsigned int>((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3]);
			}

			short IFOparser::ToShort(unsigned char bytes[])
			{
				return ToInt16(bytes);
			}

			long long IFOparser::ToFilePosition(unsigned char bytes[])
			{
				return ToInt32(bytes) * 0x800LL;
			}

			long long IFOparser::GetTotalFrames(TimeSpan *time, int fps)
			{
				return static_cast<long long>(Math::Round(fps * time->TotalSeconds));
			}

			std::string IFOparser::TwoLong(int val)
			{
				return std::string::Format("{0:D2}", val);
			}

			int IFOparser::AsHex(int val)
			{
				int ret;
				int::TryParse(std::string::Format("{0:X2}", val), ret);
				return ret;
			}

			Nullable<short> IFOparser::GetFrames(unsigned char val)
			{
				int byte0_high = val >> 4;
				int byte0_low = val & 0x0F;
				if (byte0_high > 11)
					return static_cast<short>(((byte0_high - 12) * 10) + byte0_low);
				if ((byte0_high <= 3) || (byte0_high >= 8))
					return 0;
				return static_cast<short>(((byte0_high - 4) * 10) + byte0_low);
			}

			int IFOparser::GetFrames(TimeSpan *time, int fps)
			{
				return static_cast<int>(Math::Round(fps * time->Milliseconds / 1000.0));
			}

			long long IFOparser::GetPCGIP_Position(const std::string &ifoFile)
			{
				return ToFilePosition(GetFileBlock(ifoFile, 0xCC, 4));
			}

			int IFOparser::GetProgramChains(const std::string &ifoFile, long long pcgitPosition)
			{
				return ToInt16(GetFileBlock(ifoFile, pcgitPosition, 2));
			}

			unsigned int IFOparser::GetChainOffset(const std::string &ifoFile, long long pcgitPosition, int programChain)
			{
				return ToInt32(GetFileBlock(ifoFile, (pcgitPosition + (8 * programChain)) + 4, 4));
			}

			int IFOparser::GetNumberOfPrograms(const std::string &ifoFile, long long pcgitPosition, unsigned int chainOffset)
			{
				return GetFileBlock(ifoFile, (pcgitPosition + chainOffset) + 2, 1)[0];
			}

			Nullable<TimeSpan*> IFOparser::ReadTimeSpan(const std::string &ifoFile, long long pcgitPosition, unsigned int chainOffset, double &fps)
			{
				return ReadTimeSpan(GetFileBlock(ifoFile, (pcgitPosition + chainOffset) + 4, 4), fps);
			}

			Nullable<TimeSpan*> IFOparser::ReadTimeSpan(unsigned char playbackBytes[], double &fps)
			{
				Nullable<short> frames = GetFrames(playbackBytes[3]);
				int fpsMask = playbackBytes[3] >> 6;
				fps = fpsMask == 0x01 ? 25 : fpsMask == 0x03 ? (30 / 1.001) : 0;
				if (!frames.HasValue)
					return 0;

				try
				{
					int hours = AsHex(playbackBytes[0]);
					int minutes = AsHex(playbackBytes[1]);
					int seconds = AsHex(playbackBytes[2]);
					TimeSpan *ret = new TimeSpan(hours, minutes, seconds);
					if (fps != 0)
						ret = ret->Add(TimeSpan::FromSeconds(static_cast<double>(frames) / fps));
					return ret;
				}
				catch (...)
				{
					return 0;
				}
			}

			std::string IFOparser::getAudioLanguage(const std::string &FileName, int count)
			{
				FileStream *fs = new FileStream(FileName, FileMode->Open, FileAccess::Read);
				BinaryReader *br = new BinaryReader(fs);
				Stream *sr = br->BaseStream;

				// go to audio stream number
				sr->Seek(0x203, SeekOrigin::Begin);
				unsigned char a = br->ReadByte();
				sr->Seek(2, SeekOrigin::Current);
				if (count > 0)
					sr->Seek(8*count, SeekOrigin::Current);
				unsigned char buff[2];
				br->Read(buff, 0, 2);
				std::string ShortLangCode = std::string::Format("{0}{1}", static_cast<wchar_t>(buff[0]), static_cast<wchar_t>(buff[1]));
				std::string audioLang = LanguageSelectionContainer::Short2FullLanguageName(ShortLangCode);
				fs->Close();
				return audioLang;
			}

			std::string *IFOparser::GetSubtitlesStreamsInfos(const std::string &FileName, int iPGC, bool bGetAllStreams)
			{
				unsigned char buff[4];
				unsigned char s = 0;
				std::string subdesc[s];
				std::string substreams[s];

				try
				{
					FileStream *fs = new FileStream(FileName, FileMode->Open, FileAccess::Read);
					BinaryReader *br = new BinaryReader(fs);
					Stream *sr = br->BaseStream;

					// go to the substream #1
					sr->Seek(0x255, SeekOrigin::Begin);

					s = br->ReadByte();
					if (s > 32 || bGetAllStreams)
						s = 32; // force the max #. According to the specs 32 is the max value for subtitles streams.

					subdesc = new std::string[s];

					// go to the Language Code
					sr->Seek(2, SeekOrigin::Current);

					for (int i = 0; i < s; i++)
					{
						// Presence (1 bit), Coding Mode (1bit), Short Language Code (2bits), Language Extension (1bit), Sub Picture Caption Type (1bit)
						br->Read(buff, 0, 2);

						if (buff[0] == 0 && buff[1] == 0)
						{
							subdesc[i] = "unknown";
						}
						else
						{
							std::string ShortLangCode = std::string::Format("{0}{1}", static_cast<wchar_t>(buff[0]), static_cast<wchar_t>(buff[1]));
							subdesc[i] = LanguageSelectionContainer::Short2FullLanguageName(ShortLangCode);
						}

						// Go to Code Extension
						sr->Seek(1, SeekOrigin::Current);
						buff[0] = br->ReadByte();

						switch (buff[0] & 0x0F)
						{
							// from http://dvd.sourceforge.net/dvdinfo/sprm.html
							case 1:
								subdesc[i] += " - (Caption/Normal Size Char)";
								break;
							case 2:
								subdesc[i] += " - (Caption/Large Size Char)";
								break;
							case 3:
								subdesc[i] += " - (Caption For Children)";
								break;
							case 5:
								subdesc[i] += " - (Closed Caption/Normal Size Char)";
								break;
							case 6:
								subdesc[i] += " - (Closed Caption/Large Size Char)";
								break;
							case 7:
								subdesc[i] += " - (Closed Caption For Children)";
								break;
							case 9:
								subdesc[i] += " - (Forced Caption)";
								break;
							case 13:
								subdesc[i] += " - (Director Comments/Normal Size Char)";
								break;
							case 14:
								subdesc[i] += " - (Director Comments/Large Size Char)";
								break;
							case 15:
								subdesc[i] += " - (Director Comments for Children)";
								break;
						}

						if (buff[0] == 0)
							buff[0] = 1;

						// go to the next sub stream
						sr->Seek(2, SeekOrigin::Current);
					}

					// find the PGC starting address of the requested PGC number
					sr->Seek(0x1000 + 0x0C + (iPGC - 1) * 0x08, SeekOrigin::Begin);
					br->Read(buff, 0, 4);

					// go to the starting address of the requested PGC number
					sr->Seek(0x1000 + buff[3] + buff[2] * 256 + buff[1] * 256 ^ 2 + buff[0] * 256 ^ 3, SeekOrigin::Begin);

					// go to the subtitle starting address
					sr->Seek(0x1B, SeekOrigin::Current);

					substreams = new std::string[32];
					for (int i = 0; i < 32; i++)
					{
						if (i >= sizeof(subdesc) / sizeof(subdesc[0]))
							break;

						br->Read(buff, 0, 4);

						if (buff[0] == 0)
							continue;
						buff[0] -= 128;

						if (buff[0] > 0)
							if ((substreams[buff[0]]).empty())
								substreams[buff[0]] = "[" + std::string::Format("{0:00}", buff[0]) + "] - " + subdesc[i];
						if (buff[1] > 0)
							if ((substreams[buff[1]]).empty())
								substreams[buff[1]] = "[" + std::string::Format("{0:00}", buff[1]) + "] - " + subdesc[i];
						if (buff[2] > 0)
							if ((substreams[buff[2]]).empty())
								substreams[buff[2]] = "[" + std::string::Format("{0:00}", buff[2]) + "] - " + subdesc[i];
						if (buff[3] > 0)
							if ((substreams[buff[3]]).empty())
								substreams[buff[3]] = "[" + std::string::Format("{0:00}", buff[3]) + "] - " + subdesc[i];
						if (buff[0] == 0 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0)
							if ((substreams[buff[0]]).empty())
								substreams[buff[0]] = "[" + std::string::Format("{0:00}", buff[0]) + "] - " + subdesc[i];
					}

					if (bGetAllStreams)
					{
						for (int i = 0; i < 32; i++)
							if ((substreams[i]).empty())
								substreams[i] = "[" + std::string::Format("{0:00}", i) + "] - not detected";
					}
					else
					{
						ArrayList *arrList = new ArrayList();
						for (std::string::const_iterator strItem = substreams->begin(); strItem != substreams->end(); ++strItem)
							if (!(*strItem).empty())
								arrList->Add(*strItem);
						substreams = new std::string[arrList->Count];
						for (int i = 0; i < arrList->Count; i++)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
							substreams[i] = arrList[i]->ToString();
					}

					fs->Close();
				}
				catch (std::exception &ex)
				{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					MessageBox::Show(ex.ToString());
				}
				return substreams;
			}

			unsigned int IFOparser::getPGCnb(const std::string &FileName)
			{
				FileStream *fs = new FileStream(FileName, FileMode->Open, FileAccess::Read);
				BinaryReader *br = new BinaryReader(fs);
				Stream *sr = br->BaseStream;

				sr->Seek(0xCC, SeekOrigin::Begin);
				unsigned int buf = ReadUInt32(br); // Read PGC offset
				sr->Seek(2048 * buf + 0x1, SeekOrigin::Begin); // Move to beginning of PGC
				long long VTS_PGCITI_start_position = sr->Position - 1;
				unsigned char nPGCs = br->ReadByte(); // Number of PGCs
				fs->Close();

				return nPGCs;
			}

			unsigned int IFOparser::ReadUInt32(BinaryReader *br)
			{
				unsigned int val = ((static_cast<unsigned int>(br->ReadByte())) << 24 | (static_cast<unsigned int>(br->ReadByte())) << 16 | (static_cast<unsigned int>(br->ReadByte())) << 8 | (static_cast<unsigned int>(br->ReadByte())));
				return val;
			}

			std::string IFOparser::GetVideoAR(const std::string &FileName)
			{
				FileStream *fs = new FileStream(FileName, FileMode->Open, FileAccess::Read);
				BinaryReader *br = new BinaryReader(fs);
				Stream *sr = br->BaseStream;

				sr->Seek(0x200, SeekOrigin::Begin);
				unsigned char array_Renamed[2];
				fs->Read(array_Renamed, 0, 2);
				fs->Close();

				unsigned char b = static_cast<unsigned char>((0x0C & array_Renamed[0]) >> 2);
				std::string ar = "";

				switch (b)
				{
					case 0:
						ar = "4:3";
						break;
					case 1:
					case 2:
						ar = "";
						break;
					case 3:
						ar = "16:9";
						break;
				}
				return ar;
			}
		}
	}
}
