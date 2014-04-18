#pragma once

#include "core/gui/SourceDetector.h"
#include "ChapterCreator.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include <QString>
#include <QVector>
#include <cmath>
#include "stringconverter.h"

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



//using namespace System::Xml;



namespace MeXgui
{
	class ChapterInfo
	{
	private:
		QString privateTitle;
	public:
		const QString &getTitle() const;
		void setTitle(const QString &value);
	private:
		QString privateLangCode;
	public:
		const QString &getLangCode() const;
		void setLangCode(const QString &value);
	private:
		QString privateSourceName;
	public:
		const QString &getSourceName() const;
		void setSourceName(const QString &value);
	private:
		int privateTitleNumber;
	public:
		const int &getTitleNumber() const;
		void setTitleNumber(const int &value);
	private:
		QString privateSourceType;
	public:
		const QString &getSourceType() const;
		void setSourceType(const QString &value);
	private:
		QString privateSourceHash;
	public:
		const QString &getSourceHash() const;
		void setSourceHash(const QString &value);
	private:
		double privateFramesPerSecond;
	public:
		const double &getFramesPerSecond() const;
		void setFramesPerSecond(const double &value);
	private:
		TimeSpan *privateDuration;
	public:
		const TimeSpan &getDuration() const;
		void setDuration(const TimeSpan &value);
	private:
		QVector<Chapter> privateChapters;
	public:
		const QVector<Chapter> &getChapters() const;
		void setChapters(const QVector<Chapter> &value);

		virtual QString ToString();

		void ChangeFps(double fps);

		void SaveText(const QString &filename);

		void SaveQpfile(const QString &filename);

		void SaveCelltimes(const QString &filename);

		void SaveTsmuxerMeta(const QString &filename);

		void SaveTimecodes(const QString &filename);

		void SaveXml(const QString &filename);
	};
}
