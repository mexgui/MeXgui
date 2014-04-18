#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
#include "BDInfoExtractor.h"
#include <QString>
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



namespace MeXgui
{
	class BlurayExtractor : public ChapterExtractor
	{
	public:
		const virtual QString *getExtensions() const;

		virtual QVector<ChapterInfo*> GetStreams(const QString &location);
	};
}
