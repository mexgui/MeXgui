#pragma once

#include "core/gui/SourceDetector.h"
#include "ChapterCreator.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include <string>
#include <vector>
#include <cmath>
#include "stringconverter.h"

// ****************************************************************************
// 
// Copyright (C) 2009  Jarrett Vance
// 
// code from http://jvance.com/pages/ChapterGrabber.xhtml
// 
// ****************************************************************************

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace MeGUI
{
	class ChapterInfo
	{
	private:
		std::string privateTitle;
	public:
		const std::string &getTitle() const;
		void setTitle(const std::string &value);
	private:
		std::string privateLangCode;
	public:
		const std::string &getLangCode() const;
		void setLangCode(const std::string &value);
	private:
		std::string privateSourceName;
	public:
		const std::string &getSourceName() const;
		void setSourceName(const std::string &value);
	private:
		int privateTitleNumber;
	public:
		const int &getTitleNumber() const;
		void setTitleNumber(const int &value);
	private:
		std::string privateSourceType;
	public:
		const std::string &getSourceType() const;
		void setSourceType(const std::string &value);
	private:
		std::string privateSourceHash;
	public:
		const std::string &getSourceHash() const;
		void setSourceHash(const std::string &value);
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
		std::vector<Chapter> privateChapters;
	public:
		const std::vector<Chapter> &getChapters() const;
		void setChapters(const std::vector<Chapter> &value);

		virtual std::string ToString();

		void ChangeFps(double fps);

		void SaveText(const std::string &filename);

		void SaveQpfile(const std::string &filename);

		void SaveCelltimes(const std::string &filename);

		void SaveTsmuxerMeta(const std::string &filename);

		void SaveTimecodes(const std::string &filename);

		void SaveXml(const std::string &filename);
	};
}
