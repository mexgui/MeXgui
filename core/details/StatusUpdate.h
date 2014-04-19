#pragma once

#include "core/util/FileSize.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/FPSChooser.h"
#include "core/util/Util.h"
#include <QString>
#include <stdexcept>

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




using namespace MeXgui::core::util;

namespace MeXgui
{
	/// <summary>
	/// Class that is used to send an encoding update from the encoder to the GUI
	/// it contains all the elements that will be updated in the GUI at some point
	/// </summary>
	class StatusUpdate
	{
	private:
		bool hasError, isComplete, wasAborted;
		QString error, log, jobName, status;
		Nullable<TimeSpan*> audioPosition, cliplength, estimatedTime;
		Nullable<quint64> nbFramesDone, nbFramesTotal;
		TimeSpan *timeElapsed;
		Nullable<FileSize> filesize, audioFileSize, projectedFileSize;
		QString processingspeed;
		decimal percentage;
		MeXgui::JobStatus jobStatus;
	public:
		StatusUpdate(const QString &name);

		/// <summary>
		/// What is currently processing?
		/// </summary>
		const QString &getStatus() const;
		void setStatus(const QString &value);

		/// <summary>
		/// Job Status currently processing
		/// </summary>
		const MeXgui::JobStatus &getJobStatus() const;
		void setJobStatus(const MeXgui::JobStatus &value);

		/// <summary>
		/// Does the job have any Log?
		/// </summary>
		const QString &getLog() const;
		void setLog(const QString &value);

		/// <summary>
		/// What is the error ?
		/// </summary>
		const QString &getError() const;
		void setError(const QString &value);

		/// <summary>
		/// does the job have any errors?
		/// </summary>
		const bool &getHasError() const;
		void setHasError(const bool &value);
		/// <summary>
		///  has the encoding job completed?
		/// </summary>
		const bool &getIsComplete() const;
		void setIsComplete(const bool &value);
		/// <summary>
		/// did we get this statusupdate because the job was aborted?
		/// </summary>
		const bool &getWasAborted() const;
		void setWasAborted(const bool &value);
		/// <summary>
		/// name of the job this statusupdate is refering to
		/// </summary>
		const QString &getJobName() const;
		void setJobName(const QString &value);
		/// <summary>
		///  position in clip
		/// </summary>
		const Nullable<TimeSpan*> &getClipPosition() const;
		void setClipPosition(const Nullable<TimeSpan*> &value);
		/// <summary>
		/// Length of clip
		/// </summary>
		const Nullable<TimeSpan*> &getClipLength() const;
		void setClipLength(const Nullable<TimeSpan*> &value);
		/// <summary>
		/// number of frames that have been encoded so far
		/// </summary>
		const Nullable<quint64> &getNbFramesDone() const;
		void setNbFramesDone(const Nullable<quint64> &value);
		/// <summary>
		/// number of frames of the source
		/// </summary>
		const Nullable<quint64> &getNbFramesTotal() const;
		void setNbFramesTotal(const Nullable<quint64> &value);
		/// <summary>
		///  current encoding speed
		/// </summary>
//			get {return fps;}
		void setFPS(const Nullable<decimal> &value);
		/// <summary>
		/// Some estimate of the encoding speed (eg FPS, or ratio to realtime)
		/// </summary>
		const QString &getProcessingSpeed() const;
		/// <summary>
		/// projected output size
		/// </summary>
		const Nullable<FileSize> &getProjectedFileSize() const;
		void setProjectedFileSize(const Nullable<FileSize> &value);
		const int &getPercentageDone() const;
		/// <summary>
		/// gets / sets the exact percentage of the encoding progress
		/// </summary>
		const Nullable<decimal> &getPercentageDoneExact() const;
		void setPercentageDoneExact(const Nullable<decimal> &value);
		/// <summary>
		/// size of the encoded file at this point
		/// </summary>
		const Nullable<FileSize> &getCurrentFileSize() const;
		void setCurrentFileSize(const Nullable<FileSize> &value);

		/// <summary>
		/// current size of the audio
		/// this field is filled when muxing and contains the current size of the audio data
		/// </summary>
		void setAudioFileSize(const Nullable<FileSize> &value);
		/// <summary>
		/// time elapsed between start of encoding and the point where this status update is being sent
		/// </summary>
		const TimeSpan &getTimeElapsed() const;
		void setTimeElapsed(const TimeSpan &value);
		/// <summary>
		/// gets the elapsed time as a pretty string
		/// </summary>
		const QString &getTimeElapsedString() const;

		/// <summary>
		/// Gets/sets the estimated time for this encode
		/// </summary>
		const Nullable<TimeSpan*> &getEstimatedTime() const;
		void setEstimatedTime(const Nullable<TimeSpan*> &value);


	private:
		Nullable<TimeSpan*> _timeEstimate;
	public:
		Nullable<FileSize> _audioSize;
	private:
		Nullable<decimal> _fps;


		// The following groups each allow progress to be calculated (in percent)
		Nullable<decimal> _percent;

		Nullable<quint64> _frame;
		Nullable<quint64> _framecount;

		Nullable<FileSize> _currentSize;
		Nullable<FileSize> _totalSize;

		Nullable<TimeSpan*> _currentTime;
		Nullable<TimeSpan*> _totalTime;

	public:
		void FillValues();

	private:
		static TimeSpan *const FiveSeconds;
		static const int UpdatesPerEstimate = 10;
		TimeSpan previousUpdates[UpdatesPerEstimate];
		decimal previousUpdatesProgress[UpdatesPerEstimate];
		int updateIndex;

	private:
		void InitializeInstanceFields();
	};
}