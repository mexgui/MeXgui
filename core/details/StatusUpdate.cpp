#include "StatusUpdate.h"



using namespace MeXgui::core::util;

namespace MeXgui
{

	StatusUpdate::StatusUpdate(const QString &name)
	{
		InitializeInstanceFields();
		jobName = name;

		estimatedTime = Nullable<TimeSpan>();
		hasError = false;
		isComplete = false;
		wasAborted = false;
		error = "";
		log = "";
		audioPosition = Nullable<TimeSpan>();
		cliplength = Nullable<TimeSpan>();
		audioFileSize = Nullable<FileSize>();
		nbFramesDone = Nullable<quint64>();
		nbFramesTotal = Nullable<quint64>();
		projectedFileSize = Nullable<FileSize>();
		timeElapsed = TimeSpan::Zero;
		processingspeed = "";
		filesize = Nullable<FileSize>();
		jobStatus = MeXgui::PROCESSING;

		for (int i = 0; i < UpdatesPerEstimate; ++i)
		{
			previousUpdates[i] = TimeSpan::Zero;
			previousUpdatesProgress[i] = 0;
		}
	}

	const QString &StatusUpdate::getStatus() const
	{
		return status;
	}

	void StatusUpdate::setStatus(const QString &value)
	{
		status = value;
	}

	const MeXgui::JobStatus &StatusUpdate::getJobStatus() const
	{
		return jobStatus;
	}

	void StatusUpdate::setJobStatus(const MeXgui::JobStatus &value)
	{
		jobStatus = value;
	}

	const QString &StatusUpdate::getLog() const
	{
		return log;
	}

	void StatusUpdate::setLog(const QString &value)
	{
		log = value;
	}

	const QString &StatusUpdate::getError() const
	{
		return error;
	}

	void StatusUpdate::setError(const QString &value)
	{
		error = value;
	}

	const bool &StatusUpdate::getHasError() const
	{
		return hasError;
	}

	void StatusUpdate::setHasError(const bool &value)
	{
		hasError = value;
	}

	const bool &StatusUpdate::getIsComplete() const
	{
		return isComplete;
	}

	void StatusUpdate::setIsComplete(const bool &value)
	{
		isComplete = value;
	}

	const bool &StatusUpdate::getWasAborted() const
	{
		return wasAborted;
	}

	void StatusUpdate::setWasAborted(const bool &value)
	{
		wasAborted = value;
	}

	const QString &StatusUpdate::getJobName() const
	{
		return jobName;
	}

	void StatusUpdate::setJobName(const QString &value)
	{
		jobName = value;
	}

	const Nullable<TimeSpan*> &StatusUpdate::getClipPosition() const
	{
		return audioPosition;
	}

	void StatusUpdate::setClipPosition(const Nullable<TimeSpan*> &value)
	{
		_currentTime = value.HasValue ? value : _currentTime;
		audioPosition = _currentTime;
	}

	const Nullable<TimeSpan*> &StatusUpdate::getClipLength() const
	{
		return cliplength;
	}

	void StatusUpdate::setClipLength(const Nullable<TimeSpan*> &value)
	{
		_totalTime = value.HasValue ? value : _totalTime;
		cliplength = _totalTime;
	}

	const Nullable<quint64> &StatusUpdate::getNbFramesDone() const
	{
		return nbFramesDone;
	}

	void StatusUpdate::setNbFramesDone(const Nullable<quint64> &value)
	{
		_frame = value.HasValue ? value : _frame;
		nbFramesDone = _frame;
	}

	const Nullable<quint64> &StatusUpdate::getNbFramesTotal() const
	{
		return nbFramesTotal;
	}

	void StatusUpdate::setNbFramesTotal(const Nullable<quint64> &value)
	{
		_framecount = value.HasValue ? value : _framecount;
		nbFramesTotal = _framecount;
	}

	void StatusUpdate::setFPS(const Nullable<decimal> &value)
	{
		_fps = value.HasValue ? value : _fps;
	}

	const QString &StatusUpdate::getProcessingSpeed() const
	{
		return processingspeed;
	}

	const Nullable<FileSize> &StatusUpdate::getProjectedFileSize() const
	{
		return projectedFileSize;
	}

	void StatusUpdate::setProjectedFileSize(const Nullable<FileSize> &value)
	{
		_totalSize = value.HasValue ? value : _totalSize;
		projectedFileSize = _totalSize;
	}

	const int &StatusUpdate::getPercentageDone() const
	{
		return static_cast<int>(getPercentageDoneExact());
	}

	const Nullable<decimal> &StatusUpdate::getPercentageDoneExact() const
	{
		return percentage;
	}

	void StatusUpdate::setPercentageDoneExact(const Nullable<decimal> &value)
	{
		_percent = value.HasValue ? value : _percent;
		percentage = _percent.HasValue ? _percent : 0;
	}

	const Nullable<FileSize> &StatusUpdate::getCurrentFileSize() const
	{
		return filesize;
	}

	void StatusUpdate::setCurrentFileSize(const Nullable<FileSize> &value)
	{
		_currentSize = value.HasValue ? value : _currentSize;
		filesize = _currentSize;
	}

	void StatusUpdate::setAudioFileSize(const Nullable<FileSize> &value)
	{
		audioFileSize = value;
	}

	const TimeSpan &StatusUpdate::getTimeElapsed() const
	{
		return timeElapsed;
	}

	void StatusUpdate::setTimeElapsed(const TimeSpan &value)
	{
		timeElapsed = value;
	}

	const QString &StatusUpdate::getTimeElapsedString() const
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return Util::ToString(getTimeElapsed());
	}

	const Nullable<TimeSpan*> &StatusUpdate::getEstimatedTime() const
	{
		return estimatedTime;
	}

	void StatusUpdate::setEstimatedTime(const Nullable<TimeSpan*> &value)
	{
		_timeEstimate = value.HasValue ? value : _timeEstimate;
		estimatedTime = _timeEstimate;
	}

	void StatusUpdate::FillValues()
	{
		try
		{
			// First we attempt to find the percent done
			Nullable<decimal> fraction = Nullable<decimal>();

			// Percent
			if (_percent.HasValue)
				fraction = _percent / 100;
			// Time estimates
			else if (_timeEstimate.HasValue && !_timeEstimate.Equals(TimeSpan::Zero))
				fraction = (static_cast<decimal>(timeElapsed->Ticks) / static_cast<decimal>(_timeEstimate.Value::Ticks));
			// Frame counts
			else if (_frame.HasValue && _framecount.HasValue && _framecount.GetValueOrDefault() != 0)
				fraction = (static_cast<decimal>(_frame.Value) / static_cast<decimal>(_framecount.Value));
			// File sizes
			else if (_currentSize.HasValue && _totalSize.HasValue && !_totalSize.Equals(FileSize::Empty))
				fraction = (_currentSize.Value / _totalSize.Value);
			// Clip positions
			else if (_currentTime.HasValue && _totalTime.HasValue && !_totalTime.Equals(TimeSpan::Zero))
				fraction = (static_cast<decimal>(_currentTime.Value::Ticks) / static_cast<decimal>(_totalTime.Value::Ticks));


			if (fraction.HasValue)
				percentage = fraction.Value * 100;

			/// Frame counts
			if (_frame.HasValue)
				nbFramesDone = _frame.Value;
			if (_framecount.HasValue)
				nbFramesTotal = _framecount.Value;
			if (_framecount.HasValue && !_frame.HasValue && fraction.HasValue)
				nbFramesDone = static_cast<quint64>(fraction.Value * _framecount.Value);
			if (!_framecount.HasValue && _frame.HasValue && fraction.HasValue)
				nbFramesTotal = static_cast<quint64>(_frame.Value / fraction.Value);

			/// Sizes
			if (_currentSize.HasValue)
				filesize = _currentSize;
			if (_totalSize.HasValue)
				projectedFileSize = _totalSize;
			if (_currentSize.HasValue && !_totalSize.HasValue && fraction.HasValue)
				projectedFileSize = _currentSize / fraction.Value;
			// We don't estimate current size
			// because it would suggest to the user that
			// we are actually measuring it

			// We don't estimate the current time or total time
			// in the clip, because it would suggest we are measuring it.
			if (_currentTime.HasValue)
				audioPosition = _currentTime;
			if (_totalTime.HasValue)
				cliplength = _totalTime;
			// However, if we know the total time and the percent, it is
			// ok to estimate the current position
			if (_totalTime.HasValue && !_currentTime.HasValue && fraction.HasValue)
				audioPosition = new TimeSpan(static_cast<qint64>(static_cast<decimal>(_totalTime.Value::Ticks) * fraction.Value));

			// FPS
			if (_frame.HasValue && timeElapsed->TotalSeconds > 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				processingspeed = Util::ToString(static_cast<decimal>(_frame.Value) / static_cast<decimal>(timeElapsed->TotalSeconds), false) + " FPS";
			// Other processing speeds
			else if (_currentTime.HasValue && timeElapsed->Ticks > 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				processingspeed = Util::ToString(static_cast<decimal>(_currentTime.Value::Ticks) / static_cast<decimal>(timeElapsed->Ticks), false) + "x realtime";
			else if (fraction.HasValue && _totalTime.HasValue && timeElapsed->Ticks > 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				processingspeed = Util::ToString(static_cast<decimal>(_totalTime.Value::Ticks) * fraction.Value / static_cast<decimal>(timeElapsed->Ticks), false) + "x realtime";


			// Processing time
			if (fraction.HasValue)
			{
				TimeSpan *time = timeElapsed - previousUpdates[updateIndex];
				decimal progress = fraction.Value - previousUpdatesProgress[updateIndex];
				if (progress > 0 && time > FiveSeconds)
					estimatedTime = new TimeSpan(static_cast<qint64>(static_cast<decimal>(time->Ticks) * (1 - fraction) / progress));
				else
					estimatedTime = new TimeSpan(static_cast<qint64>(static_cast<decimal>(timeElapsed->Ticks) * ((1 / fraction.Value) - 1)));

				previousUpdates[updateIndex] = timeElapsed;
				previousUpdatesProgress[updateIndex] = fraction.Value;
				updateIndex = (updateIndex + 1) % UpdatesPerEstimate;
			}
		}
		catch (std::exception &e1)
		{
		}
	}

TimeSpan *const StatusUpdate::FiveSeconds = new TimeSpan(0, 0, 5);

	void StatusUpdate::InitializeInstanceFields()
	{
		_timeEstimate = Nullable<TimeSpan>();
		_audioSize = Nullable<FileSize>();
		_fps = Nullable<decimal>();
		_percent = Nullable<decimal>();
		_frame = Nullable<quint64>();
		_framecount = Nullable<quint64>();
		_currentSize = Nullable<FileSize>();
		_totalSize = Nullable<FileSize>();
		_currentTime = Nullable<TimeSpan>();
		_totalTime = Nullable<TimeSpan>();
		updateIndex = 0;
	}
}
