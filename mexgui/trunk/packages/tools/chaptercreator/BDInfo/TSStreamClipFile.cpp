#include "TSStreamClipFile.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace BDInfo
{

	TSStreamClipFile::TSStreamClipFile(FileInfo *fileInfo)
	{
		InitializeInstanceFields();
		FileInfo = fileInfo;
		Name = fileInfo->Name->ToUpper(System::Globalization::CultureInfo::InvariantCulture);
	}

	void TSStreamClipFile::Scan()
	{
		FileStream *fileStream = 0;
		BinaryReader *fileReader = 0;

		try
		{
	#if defined(DEBUG)
			Debug::WriteLine(std::string::Format("Scanning {0}...", Name));
	#endif
			Streams.clear();

			fileStream = File::OpenRead(FileInfo->FullName);
			fileReader = new BinaryReader(fileStream);

			unsigned char data[fileStream->Length];
			fileReader->Read(data, 0, sizeof(data) / sizeof(data[0]));

			unsigned char fileType[8];
			Array::Copy(data, 0, fileType, 0, sizeof(fileType) / sizeof(fileType[0]));

			FileType = ASCIIEncoding::ASCII::GetString(fileType);
			if (FileType != "HDMV0100" && FileType != "HDMV0200")
			{
				throw std::exception(std::string::Format("Clip info file {0} has an unknown file type {1}.", FileInfo->Name, FileType));
			}
	#if defined(DEBUG)                
			Debug::WriteLine(std::string::Format("\tFileType: {0}", FileType));
	#endif
			int clipIndex = (static_cast<int>(data[12]) << 24) + (static_cast<int>(data[13]) << 16) + (static_cast<int>(data[14]) << 8) + (static_cast<int>(data[15]));

			int clipLength = (static_cast<int>(data[clipIndex]) << 24) + (static_cast<int>(data[clipIndex + 1]) << 16) + (static_cast<int>(data[clipIndex + 2]) << 8) + (static_cast<int>(data[clipIndex + 3]));

			unsigned char clipData[clipLength];
			Array::Copy(data, clipIndex + 4, clipData, 0, sizeof(clipData) / sizeof(clipData[0]));

			int streamCount = clipData[8];
	#if defined(DEBUG)
			Debug::WriteLine(std::string::Format("\tStreamCount: {0}", streamCount));
	#endif
			int streamOffset = 10;
			for (int streamIndex = 0; streamIndex < streamCount; streamIndex++)
			{
				TSStream *stream = 0;

				unsigned short PID = static_cast<unsigned short>((clipData[streamOffset] << 8) + clipData[streamOffset + 1]);

				streamOffset += 2;

				TSStreamType streamType = static_cast<TSStreamType>(clipData[streamOffset + 1]);
				switch (streamType)
				{
					case AVC_VIDEO:
					case MPEG1_VIDEO:
					case MPEG2_VIDEO:
					case VC1_VIDEO:
					{
						TSVideoFormat videoFormat = static_cast<TSVideoFormat>(clipData[streamOffset + 2] >> 4);
						TSFrameRate frameRate = static_cast<TSFrameRate>(clipData[streamOffset + 2] & 0xF);
						TSAspectRatio aspectRatio = static_cast<TSAspectRatio>(clipData[streamOffset + 3] >> 4);

						stream = new TSVideoStream();
						(static_cast<TSVideoStream*>(stream))->setVideoFormat(videoFormat);
						(static_cast<TSVideoStream*>(stream))->AspectRatio = aspectRatio;
						(static_cast<TSVideoStream*>(stream))->setFrameRate(frameRate);
	#if defined(DEBUG)
						Debug::WriteLine(std::string::Format("\t{0} {1} {2} {3} {4}", PID, streamType, videoFormat, frameRate, aspectRatio));
	#endif
					}
					break;

					case AC3_AUDIO:
					case AC3_PLUS_AUDIO:
					case AC3_PLUS_SECONDARY_AUDIO:
					case AC3_TRUE_HD_AUDIO:
					case DTS_AUDIO:
					case DTS_HD_AUDIO:
					case DTS_HD_MASTER_AUDIO:
					case DTS_HD_SECONDARY_AUDIO:
					case LPCM_AUDIO:
					case MPEG1_AUDIO:
					case MPEG2_AUDIO:
					{
						unsigned char languageBytes[3];
						Array::Copy(clipData, streamOffset + 3, languageBytes, 0, sizeof(languageBytes) / sizeof(languageBytes[0]));
						std::string languageCode = ASCIIEncoding::ASCII::GetString(languageBytes);

						TSChannelLayout channelLayout = static_cast<TSChannelLayout>(clipData[streamOffset + 2] >> 4);
						TSSampleRate sampleRate = static_cast<TSSampleRate>(clipData[streamOffset + 2] & 0xF);

						stream = new TSAudioStream();
						(static_cast<TSAudioStream*>(stream))->setLanguageCode(languageCode);
						(static_cast<TSAudioStream*>(stream))->ChannelLayout = channelLayout;
						(static_cast<TSAudioStream*>(stream))->SampleRate = TSAudioStream::ConvertSampleRate(sampleRate);
						(static_cast<TSAudioStream*>(stream))->setLanguageCode(languageCode);
	#if defined(DEBUG)
						Debug::WriteLine(std::string::Format("\t{0} {1} {2} {3} {4}", PID, streamType, languageCode, channelLayout, sampleRate));
	#endif
					}
					break;

					case INTERACTIVE_GRAPHICS:
					case PRESENTATION_GRAPHICS:
					{
						unsigned char languageBytes[3];
						Array::Copy(clipData, streamOffset + 2, languageBytes, 0, sizeof(languageBytes) / sizeof(languageBytes[0]));
						std::string languageCode = ASCIIEncoding::ASCII::GetString(languageBytes);

						stream = new TSGraphicsStream();
						stream->setLanguageCode(languageCode);
	#if defined(DEBUG)
						Debug::WriteLine(std::string::Format("\t{0} {1} {2}", PID, streamType, languageCode));
	#endif
					}
					break;

					case SUBTITLE:
					{
						unsigned char languageBytes[3];
						Array::Copy(clipData, streamOffset + 3, languageBytes, 0, sizeof(languageBytes) / sizeof(languageBytes[0]));
						std::string languageCode = ASCIIEncoding::ASCII::GetString(languageBytes);
	#if defined(DEBUG)
						Debug::WriteLine(std::string::Format("\t{0} {1} {2}", PID, streamType, languageCode));
	#endif
						stream = new TSTextStream();
						stream->setLanguageCode(languageCode);
					}
					break;
				}

				if (stream != 0)
				{
					stream->PID = PID;
					stream->StreamType = streamType;
					Streams.insert(make_pair(PID, stream));
				}

				streamOffset += clipData[streamOffset] + 1;
			}
			IsValid = true;
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (fileReader != 0)
				fileReader->Close();
			if (fileStream != 0)
				fileStream->Close();
		}
	}

	void TSStreamClipFile::InitializeInstanceFields()
	{
		delete FileInfo;
		FileType = "";
		IsValid = false;
		Name = "";
		Streams = std::map<unsigned short, TSStream*>();
	}
}
