#pragma once

#include "core/plugins/interfaces/IPackage.h"
#include "core/gui/MainForm.h"
#include "FileIndexerWindow.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/util/LogItem.h"
#include "D2VIndexJob.h"
#include "core/util/VideoUtil.h"
#include "core/details/AudioTrackInfo.h"
#include "core/util/Util.h"
#include "packages/tools/avscreator/AviSynthWindow.h"
#include "packages/tools/avscreator/AviSynthWindow.h"
#include "DGIIndexJob.h"
#include "DGAIndexJob.h"
#include "FFMSIndexJob.h"
#include <QString>
#include <QMap>
#include <QVector>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************




//using namespace System::Collections::Generic;



//using namespace System::Text;



using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{
	/// <summary>
	/// Summary description for File Indexer.
	/// </summary>

	class D2VCreatorTool : public MeXgui::core::plugins::interfaces::ITool
	{


	public:
		const QString &getName() const;

		void Run(MainForm *info);

		const Shortcut *getShortcuts() const;



		const QString &getID() const;

	};

	class d2vIndexJobPostProcessor
	{
	public:
		static JobPostProcessor *PostProcessor;
	private:
		static LogItem *postprocess(MainForm *mainForm, Job *ajob);
	};

	class dgiIndexJobPostProcessor
	{
	public:
		static JobPostProcessor *PostProcessor;
	private:
		static LogItem *postprocess(MainForm *mainForm, Job *ajob);
	};

	class dgaIndexJobPostProcessor
	{
	public:
		static JobPostProcessor *PostProcessor;
	private:
		static LogItem *postprocess(MainForm *mainForm, Job *ajob);
	};

	class ffmsIndexJobPostProcessor
	{
	public:
		static JobPostProcessor *PostProcessor;
	private:
		static LogItem *postprocess(MainForm *mainForm, Job *ajob);
	};

	typedef void (*ProjectCreationComplete)(); // this event is fired when the dgindex thread finishes
}
