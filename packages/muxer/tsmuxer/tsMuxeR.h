#pragma once

#include "core/plugins/implemented/CommandlineMuxer.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MainForm.h"
#include "core/details/mux/MuxJob.h"
#include "core/details/mux/MuxProvider.h"
#include "core/util/Util.h"
#include "core/plugins/implemented/CommandlineJobProcessor.h"
#include "core/util/LogItem.h"
#include "core/details/mux/MuxSettings.h"
#include "core/util/VideoUtil.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/details/CodecManager.h"
#include "core/details/Streams.h"
#include "core/util/LanguageSelectionContainer.h"
#include <QString>
#include <QMap>
#include <QVector>
#include <stdexcept>

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

//using namespace System::Globalization;



//using namespace System::Text;



//using namespace System::Text::RegularExpressions;

using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

using namespace MediaInfoWrapper;

namespace MeXgui
{
	class tsMuxeR : public CommandlineMuxer
	{
	public:
		static JobProcessorFactory *const Factory;

	private:
		static IJobProcessor *init(MainForm *mf, Job *j);

		int numberOfAudioTracks, numberOfSubtitleTracks;
		QString metaFile;

	public:
		tsMuxeR(const QString &executablePath);
	protected:
		virtual void checkJobIO();



		virtual void setProjectedFileSize();

		const virtual QString &getCommandline() const;

	public:
		virtual void ProcessLine(const QString &line, StreamType stream, ImageType oType);

		/// <summary>
		/// gets the completion percentage of an tsmuxer line
		/// </summary>
		/// <param name="line"></param>
		/// <returns></returns>
	private:
		Nullable<decimal> getPercentage(const QString &line);

		/// <summary>
		/// determines if a read line is empty
		/// </summary>
		/// <param name="line"></param>
		/// <returns></returns>
		bool isEmptyLine(const QString &line);

		void generateMetaFile();

	private:
		void InitializeInstanceFields();
	};
}
