#pragma once

#include "File.h"
#include "Stream.h"
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

//using namespace System::Text;

using namespace MeXgui::packages::tools::hdbdextractor;

namespace eac3to
{
	/// <summary>A Feature</summary>
	class Feature
	{
	private:
		int privateNumber;
	public:
		const int &getNumber() const;
		void setNumber(const int &value);
	private:
		QString privateName;
	public:
		const QString &getName() const;
		void setName(const QString &value);
	private:
		QString privateDescription;
	public:
		const QString &getDescription() const;
		void setDescription(const QString &value);
	private:
		TimeSpan *privateDuration;
	public:
		const TimeSpan &getDuration() const;
		void setDuration(const TimeSpan &value);
	private:
		QVector<File*> privateFiles;
	public:
		const QVector<File*> &getFiles() const;
		void setFiles(const QVector<File*> &value);
	private:
		QVector<Stream*> privateStreams;
	public:
		const QVector<Stream*> &getStreams() const;
		void setStreams(const QVector<Stream*> &value);

		Feature();

		/// <summary>Converts a string representation of a Feature into a Feature equivalent.</summary>
		/// <param name="s">A string containing a line of characters from the StdOut of eac3to</param>
		/// <returns></returns>
		static Feature *Parse(const QString &s);

		virtual QString ToString();
	};
}
