#pragma once

#include "core/plugins/interfaces/Job.h"
#include "core/details/TrackInfo.h"
#include "core/details/AudioTrackInfo.h"
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

//using namespace System::Xml::Serialization;

namespace MeXgui
{
	/// <summary>
	/// Container object for MkvExtract
	/// </summary>
	class MkvExtractJob : public Job
	{
	private:
		QVector<TrackInfo*> _oTracks;
		QString _strOutputPath;

	public:
		MkvExtractJob();

		MkvExtractJob(const QString &strInput, const QString &strOutputPath, QVector<TrackInfo*> &oTracks);

		MkvExtractJob(const QString &strInput, const QString &strOutputPath, QVector<AudioTrackInfo*> &oTracks);

		const virtual QString &getCodecString() const;

		const virtual QString &getEncodingMode() const;

		const QVector<TrackInfo*> &getMkvTracks() const;
		void setMkvTracks(const QVector<TrackInfo*> &value);

		const QString &getOutputPath() const;
		void setOutputPath(const QString &value);
	};
}
