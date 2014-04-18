#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
#include "core/util/IFOparser.h"
#include "ChapterCreator.h"
#include "core/gui/FPSChooser.h"
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

//using namespace System::Text;

//using namespace System::Runtime::InteropServices;



//using namespace System::Diagnostics;

using namespace MeXgui::core::util;

namespace MeXgui
{
	class IfoExtractor : public ChapterExtractor
	{
	public:
		const virtual QString *getExtensions() const;

		const virtual bool &getSupportsMultipleStreams() const;

		virtual QVector<ChapterInfo*> GetStreams(const QString &ifoFile);

		ChapterInfo *GetChapterInfo(const QString &location, int titleSetNum);

	private:
		QVector<Chapter> GetChapters(const QString &ifoFile, int programChain, TimeSpan *&duration, double &fps);
	};
}
