#include "TSStreamClip.h"




//using namespace System::Collections::Generic;

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

	const quint64 &TSStreamClip::getPacketSize() const
	{
		return PacketCount * 192;
	}

	const quint64 &TSStreamClip::getPacketBitRate() const
	{
		if (PacketSeconds > 0)
		{
			return static_cast<quint64>(Math::Round(((getPacketSize() * 8.0) / PacketSeconds)));
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
		Chapters = QVector<double>();
		delete StreamClipFile;
	}
}
