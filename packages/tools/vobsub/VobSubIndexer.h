#pragma once

#include "core/plugins/implemented/CommandlineJobProcessor.h"
#include "SubtitleIndexJob.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MainForm.h"
#include "core/util/Util.h"
#include "core/util/FileUtil.h"
#include <QString>
#include <QVector>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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

//using namespace System::Diagnostics;



//using namespace System::Text;

using namespace MeXgui::core::util;

namespace MeXgui
{
	class VobSubIndexer : public CommandlineJobProcessor<SubtitleIndexJob*>
	{
	public:
		static JobProcessorFactory *const Factory;

	private:
		QString configFile;

		static IJobProcessor *init(MainForm *mf, Job *j);

	protected:
		const virtual QString &getCommandline() const;

	public:
		VobSubIndexer();
	protected:
		virtual void checkJobIO();

	private:
		void generateScript();

	public:
		const virtual bool &getcanPause() const;


	protected:
		const virtual bool &getcheckExitCode() const;

	private:
		void InitializeInstanceFields();
	};
}
