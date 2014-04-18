#pragma once

#include "ChapterInfo.h"
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

//using namespace System::Security::Cryptography;

namespace MeXgui
{
	class ChapterExtractor
	{
	public:
		virtual const QString &getExtensions() const = 0;
		const virtual bool &getSupportsMultipleStreams() const;
		virtual QVector<ChapterInfo*> GetStreams(const QString&) = 0;

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler<ProgramChainArg> StreamDetected;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler<ProgramChainArg> ChaptersLoaded;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler ExtractionComplete;

		static QString ComputeMD5Sum(const QString &path);

	protected:
		void OnExtractionComplete();

		void OnStreamDetected(ChapterInfo *pgc);

		void OnChaptersLoaded(ChapterInfo *pgc);
	};

	class ProgramChainArg : public EventArgs
	{
	private:
		ChapterInfo *privateProgramChain;
	public:
		const ChapterInfo &getProgramChain() const;
		void setProgramChain(const ChapterInfo &value);
	};
}
