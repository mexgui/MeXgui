#pragma once

#include "core/plugins/interfaces/Job.h"
#include "VideoCodecSettings.h"
#include "core/util/BitrateCalculatorPreProcessor.h"
#include "core/util/DAR.h"
#include "Properties.Settings.h"
#include <QString>

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
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




using namespace MeXgui::core::util;

namespace MeXgui
{
	/// <summary>
	/// Summary description for VideoJob.
	/// </summary>
	class VideoJob : public Job
	{
	private:
		VideoCodecSettings *settings;
	public:
//C# TO C++ CONVERTER NOTE: The variable BitrateCalculationInfo was renamed since it is named the same as a user-defined type:
		BitrateCalculationInfo *BitrateCalculationInfo_Renamed;

		VideoJob();

	private:
//ORIGINAL LINE: private Zone[] zones = new Zone[] { };
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		Zone *zones;
		/// <summary>
		/// gets / sets the zones
		/// </summary>
	public:
		const Zone *getZones() const;
		void setZones(Zone value[]);

		VideoJob(const QString &input, const QString &output, VideoCodecSettings *settings, Nullable<Dar> dar, Zone zones[]);

	private:
		Nullable<Dar> dar;

	public:
		const Nullable<Dar> &getDAR() const;
		void setDAR(const Nullable<Dar> &value);

		/// <summary>
		/// the codec settings for this job
		/// </summary>
		const VideoCodecSettings &getSettings() const;
		void setSettings(const VideoCodecSettings &value);
		/// <summary>
		/// codec used as presentable string
		/// </summary>
		const virtual QString &getCodecString() const;
		/// <summary>
		/// returns the encoding mode as a human readable string
		/// (this string is placed in the appropriate column in the queue)
		/// </summary>
		const virtual QString &getEncodingMode() const;

	private:
		void InitializeInstanceFields();
	};
}
