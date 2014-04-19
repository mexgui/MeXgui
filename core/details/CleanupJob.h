#pragma once

#include "core/plugins/interfaces/Job.h"
#include "JobChain.h"
#include "SequentialChain.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/gui/MainForm.h"
#include "core/util/FileUtil.h"
#include "StatusUpdate.h"
#include "core/util/LogItem.h"
#include "core/util/Exceptions.h"
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

//using namespace System::Threading;

using namespace MeXgui::core::util;

namespace MeXgui
{
	namespace core
	{
		namespace details
		{
			class CleanupJob : public Job
			{
			public:
				QVector<QString> files;

			private:
				CleanupJob();

			public:
				static JobChain *AddAfter(JobChain *other, QVector<QString> &files, const QString &strInput);

				const virtual QString &getCodecString() const;

				const virtual QString &getEncodingMode() const;
			};

			class CleanupJobRunner : public IJobProcessor
			{
			public:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				static JobProcessorFactory Factory = new JobProcessorFactory(new ProcessorFactory(delegate(MainForm f, Job j)
				{
					if (dynamic_cast<CleanupJob*>(j) != nullptr_Renamed)
						return new CleanupJobRunner(f);
						return nullptr_Renamed;
				}
			   ), "cleanup");

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				static readonly JobPostProcessor DeleteIntermediateFilesPostProcessor = new JobPostProcessor(delegate(MainForm mf, Job j)
				{
					if (mf->getSettings()->getDeleteIntermediateFiles())
						return FileUtil::DeleteIntermediateFiles(j::FilesToDelete, true, false);
						return nullptr_Renamed;
				}
			   , "DeleteIntermediateFiles");


			private:
				CleanupJobRunner(MainForm m)
				{
					this->mf = m;
				}

				StatusUpdate *su;
				QVector<QString> files;
				MainForm *mf = MainForm::Instance;
				LogItem *log;

				void IJobProcessor::setup(Job job, StatusUpdate su, LogItem log)
				{
					CleanupJob *j = static_cast<CleanupJob*>(job);
					this->log = log;
					this->su = su;
					this->files = j->files;
				}

				void run()
				{
					su->setStatus("Cleanup files...");

					delay(2000); // just so that the job has properly registered as starting

					log->LogValue("Delete Intermediate Files option set", mf->getSettings()->getDeleteIntermediateFiles());
					if (mf->getSettings()->getDeleteIntermediateFiles())
						log->Add(FileUtil::DeleteIntermediateFiles(files, true, false));

					su->setIsComplete(true);
					statusUpdate(su);
				}

				void IJobProcessor::start()
				{
					(new Thread(run))->Start();
				}


				void IJobProcessor::stop()
				{
					throw new JobRunException("Not supported");
				}

				void IJobProcessor::pause()
				{
					throw new JobRunException("Not supported");
				}

				void IJobProcessor::resume()
				{
					throw new JobRunException("Not supported");
				}

				void IJobProcessor::changePriority(ProcessPriority priority)
				{
					throw new JobRunException("Not supported");
				}

				event JobProcessingStatusUpdateCallback statusUpdate;

				event JobProcessingStatusUpdateCallback IJobProcessor::StatusUpdate
				{
					add;

			private:
				void InitializeInstanceFields();
