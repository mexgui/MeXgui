#include "neroraw.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::CompilerServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;

namespace MeGUI
{

	int NeroRawAacEncoder::showUsage()
	{
		std::cout << "usage: neroraw [-i input] -o output -rr samplerate -rb bitsPerSample -rc channelsCount <encoder options>" << std::endl;
		std::cout << "if -i input is omited stdin is used" << std::endl;
		std::cout << "for <encoder options> look @ bsn switch documentation in besweet" << std::endl;
		std::cout << "bsn.dll from besweet must be @ executable folder" << std::endl;
		return -1;
	}

	int NeroRawAacEncoder::Main(std::string& args[])
	{
		killRegistryKey();

		try
		{

			std::string inputFileName = "";
			std::string outputFileName = "";
			int nSampleRate = 44100;
			int nBitsPerSample = 16;
			int nChannelsCount = 2;
			int nShowDialog = 0;
			ArrayList *arr = new ArrayList();
			arr->Add("-bsn(");
			for (int i = 0; i < sizeof(args) / sizeof(args[0]); i++)
			{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//				switch (args[i])
//ORIGINAL LINE: case "-d":
				if (args[i] == "-d")
				{
						nShowDialog = int::Parse(args[++i]);
						continue;
				}
//ORIGINAL LINE: case "-i":
				else if (args[i] == "-i")
				{
						inputFileName = args[++i];
						continue;
				}
//ORIGINAL LINE: case "-o":
				else if (args[i] == "-o")
				{
						outputFileName = args[++i];
						continue;
				}
//ORIGINAL LINE: case "-rr":
				else if (args[i] == "-rr")
				{
						nSampleRate = int::Parse(args[++i]);
						continue;
				}
//ORIGINAL LINE: case "-rb":
				else if (args[i] == "-rb")
				{
						nBitsPerSample = int::Parse(args[++i]);
						continue;
				}
//ORIGINAL LINE: case "-rc":
				else if (args[i] == "-rc")
				{
						nChannelsCount = int::Parse(args[++i]);
						continue;
				}
				else
				{
						arr->Add(args[i]);
				}
			}
			arr->Add(")");

			if (outputFileName == "" || 0 == outputFileName.length())
				return showUsage();

//ORIGINAL LINE: string[] array = (string[])arr.ToArray(typeof(string));
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
			std::string *array_Renamed = static_cast<std::string[]>(arr->ToArray(std::string::typeid));
			int nRes;
			try
			{
				if (0 != (nRes = BSN_Init(nSampleRate, nChannelsCount, outputFileName, nBitsPerSample, nShowDialog, 0, array_Renamed_Renamed, sizeof(array_Renamed) / sizeof(array_Renamed[0]))))
					throw new ApplicationException(std::string::Format("Error configuring bsn {0}", nRes));

				const int MAX_BUFFER_PER_ONCE = 0x10000;
				int nBufSize = MAX_BUFFER_PER_ONCE - MAX_BUFFER_PER_ONCE % (nBitsPerSample * nChannelsCount / 8);
				unsigned char buf[nBufSize];
				unsigned int bytesRead = 0;
				GCHandle *h = GCHandle::Alloc(buf, GCHandleType::Pinned);
				try
				{
					Stream *s = inputFileName == "" ? Console::OpenStandardInput() : new FileStream(inputFileName, FileMode->Open, FileAccess::Read, FileShare::Read);
					try
					{

						while (0 != (bytesRead = static_cast<unsigned int>(s->Read(buf, 0, nBufSize))))
						{
							BSN_EncodeBlock(h->AddrOfPinnedObject(), bytesRead);
						}
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (inputFileName != "")
							(dynamic_cast<IDisposable*>(s))->Dispose();
					}
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					h->Free();
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				try
				{
					BSN_DeInit();
				}
				catch (...)
				{
				};
			}
		}
		catch (std::exception &e)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			std::cout << e.ToString() << std::endl;
			return -1;
		}

		killRegistryKey();

		return 0;
	}

	void NeroRawAacEncoder::killRegistryKey()
	{
		try
		{
			Microsoft::Win32::Registry::ClassesRoot::DeleteSubKeyTree(".zhdb");
		}
		catch (...)
		{
		};
	}
}
