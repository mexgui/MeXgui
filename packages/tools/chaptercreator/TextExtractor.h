#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
#include "ChapterCreator.h"
#include "core/plugins/interfaces/IMediaFile.h"
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
	class TextExtractor : public ChapterExtractor
	{
	public:
		const virtual bool &getSupportsMultipleStreams() const;

		const virtual QString *getExtensions() const;

		virtual QVector<ChapterInfo*> GetStreams(const QString &location);
	};
}
