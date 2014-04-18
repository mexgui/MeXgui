#pragma once

#include "ChapterExtractor.h"
#include "ChapterInfo.h"
#include "ChapterCreator.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include <QString>
#include <QVector>
#include <stdexcept>

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

namespace MeXgui
{
	class MplsExtractor : public ChapterExtractor
	{
	public:
		const virtual QString *getExtensions() const;

		const virtual bool &getSupportsMultipleStreams() const;

		virtual QVector<ChapterInfo*> GetStreams(const QString &location);

	private:
		QVector<Clip*> GetClips(unsigned char data[]);
	};

	class Clip
	{
	public:
		int AngleIndex;
		QString Name;
		double TimeIn;
		double TimeOut;
		double RelativeTimeIn;
		double RelativeTimeOut;
		double Length;

		quint64 FileSize;
		quint64 PayloadBytes;
		quint64 PacketCount;
		double PacketSeconds;

//C# TO C++ CONVERTER NOTE: The variable Chapters was renamed since it is named the same as a user-defined type:
		QVector<double> Chapters_Renamed;

	private:
		void InitializeInstanceFields();

public:
		Clip()
		{
			InitializeInstanceFields();
		}
	};
}
