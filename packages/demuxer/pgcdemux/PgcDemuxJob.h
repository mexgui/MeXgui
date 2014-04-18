#pragma once

#include "core/plugins/interfaces/Job.h"
#include <QString>

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
	/// Container object for PgcDemux
	/// </summary>
	class PgcDemuxJob : public Job
	{
	private:
		QString _strOutputPath;
		int _pgcNumber;

	public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public PgcDemuxJob() : this(nullptr, nullptr, 1)
		PgcDemuxJob();

		PgcDemuxJob(const QString &strInput, const QString &strOutputPath, int pgcNumber);

		const virtual QString &getCodecString() const;

		const virtual QString &getEncodingMode() const;

		const QString &getOutputPath() const;
		void setOutputPath(const QString &value);

		const int &getPGCNumber() const;
		void setPGCNumber(const int &value);
	};
}
