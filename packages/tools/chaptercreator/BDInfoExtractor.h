#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
#include "ChapterCreator.h"
#include "BDInfo/TSPlaylistFile.h"
#include "BDInfo/TSStreamClip.h"
#include "BDInfo/TSStream.h"
#include <QString>
#include <QMap>
#include <QVector>

// ****************************************************************************
// 
// Copyright (C) 2009  Jarrett Vance
// 
// code from http://jvance.com/pages/ChapterGrabber.xhtml
// 
// ****************************************************************************




//using namespace System::Collections::Generic;

//using namespace System::Linq;

//using namespace System::Text;



//using namespace System::Diagnostics;
using namespace BDInfo;

namespace MeXgui
{
	class BDInfoExtractor : public ChapterExtractor
	{
	public:
		const virtual QString *getExtensions() const;

		const virtual bool &getSupportsMultipleStreams() const;

		virtual QVector<ChapterInfo*> GetStreams(const QString &location);
	};
}
