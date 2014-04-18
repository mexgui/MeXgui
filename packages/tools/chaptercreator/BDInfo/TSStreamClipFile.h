#pragma once

#include "TSStream.h"
#include <QString>
#include <QMap>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2009  Cinema Squid
// 
// code from http://www.cinemasquid.com/blu-ray/tools/bdinfo
// 
// ****************************************************************************

#undef DEBUG



//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;

namespace BDInfo
{
	class TSStreamClipFile
	{
	public:
		FileInfo *FileInfo;
		QString FileType;
		bool IsValid;
		QString Name;

		QMap<unsigned short, TSStream*> Streams;

		TSStreamClipFile(FileInfo *fileInfo);

		void Scan();

	private:
		void InitializeInstanceFields();
	};
}
