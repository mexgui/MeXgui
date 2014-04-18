#pragma once

#include "core/plugins/interfaces/Job.h"
#include <QString>
#include <QVector>

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




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{
	class HDStreamsExJob : public Job
	{
	private:
		QString featureNb;
		QString args;
		int inputType;
		QVector<QString> source;

	public:
		HDStreamsExJob();

		HDStreamsExJob(QVector<QString> &input, const QString &ouput, const QString &featureNb, const QString &args, int inputType);

		const QString &getFeatureNb() const;
		void setFeatureNb(const QString &value);

		const QString &getArgs() const;
		void setArgs(const QString &value);

		const QVector<QString> &getSource() const;
		void setSource(const QVector<QString> &value);

		// 1 = Folder as Input
		// 2 = File(s) as Input
		const int &getInputType() const;
		void setInputType(const int &value);

		const virtual QString &getCodecString() const;

		const virtual QString &getEncodingMode() const;
	};
}
