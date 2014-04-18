#include "TSStreamClip.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace BDInfo
{

	TSStreamClip::TSStreamClip(TSStreamClipFile *streamClipFile)
		//TSStreamFile streamFile,
	{
	  InitializeInstanceFields();
	  Name = streamClipFile->Name; //streamFile.Name;
		//StreamFile = streamFile;
		StreamClipFile = streamClipFile;
		//FileSize = (ulong)StreamFile.FileInfo.Length;
	}

	const unsigned long long &TSStreamClip::getPacketSize() const
	{
		return PacketCount * 192;
	}

	const unsigned long long &TSStreamClip::getPacketBitRate() const
	{
		if (PacketSeconds > 0)
		{
			return static_cast<unsigned long long>(Math::Round(((getPacketSize() * 8.0) / PacketSeconds)));
		}
		return 0;
	}

	void TSStreamClip::InitializeInstanceFields()
	{
		AngleIndex = 0;
		FileSize = 0;
		PayloadBytes = 0;
		PacketCount = 0;
		PacketSeconds = 0;
		Chapters = std::vector<double>();
		delete StreamClipFile;
	}
}
