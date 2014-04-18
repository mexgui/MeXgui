#pragma once

#include "core/plugins/interfaces/Job.h"
#include <QString>
#include <QVector>
#include <algorithm>

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



//using namespace System::Xml::Serialization;

namespace MeXgui
{
	namespace core
	{
		namespace details
		{
			class TaggedJob
			{
			private:
				MeXgui::Job *job;
				JobStatus status;
				DateTime start, end; // time the job was started / ended
				QString name;
				QString owningWorker;
				QVector<QString> requiredJobNames;
				QVector<QString> enabledJobNames;
			public:
				QString EncodingSpeed;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore]
				QVector<TaggedJob*> EnabledJobs;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore]
				QVector<TaggedJob*> RequiredJobs;

				TaggedJob();

//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: internal TaggedJob(Job j) : this()
				TaggedJob(MeXgui::Job *j);

				const MeXgui::Job &getJob() const;
				void setJob(const MeXgui::Job &value);

				const QString &getOwningWorker() const;
				void setOwningWorker(const QString &value);

				void AddDependency(TaggedJob *other);

				/// <summary>
				/// List of jobs which need to be completed before this can be processed
				/// </summary>
				const QVector<QString> &getRequiredJobNames() const;
				void setRequiredJobNames(const QVector<QString> &value);

				/// <summary>
				/// List of jobs which completing this job enables
				/// </summary>
				const QVector<QString> &getEnabledJobNames() const;
				void setEnabledJobNames(const QVector<QString> &value);

				/// <summary>
				/// the name of this job
				/// </summary>
				const QString &getName() const;
				void setName(const QString &value);

				/// <summary>
				/// status of the job
				/// </summary>
				const JobStatus &getStatus() const;
				void setStatus(const JobStatus &value);

				/// <summary>
				/// time the job was started
				/// </summary>
				const DateTime &getStart() const;
				void setStart(const DateTime &value);

				/// <summary>
				///  time the job was completed
				/// </summary>
				const DateTime &getEnd() const;
				void setEnd(const DateTime &value);

				/// <summary>
				/// gets a humanly readable status tring
				/// </summary>
				const QString &getStatusString() const;

				/// <summary>
				/// filename without path of the source for this job
				/// </summary>
				const QString &getInputFileName() const;

				/// <summary>
				/// input file name & path of the job
				/// </summary>
				const QString &getInputFile() const;

				/// <summary>
				///  filename without path of the destination of this job
				/// </summary>
				const QString &getOutputFileName() const;

				/// <summary>
				/// output file name & path the job
				/// </summary>
				const QString &getOutputFile() const;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
