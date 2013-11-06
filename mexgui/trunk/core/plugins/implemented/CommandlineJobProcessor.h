#pragma once

#include "core/plugins/interfaces/IJobProcessor.h"
#include "core/details/StatusUpdate.h"
#include "core/util/LogItem.h"
#include "core/util/Util.h"
#include "packages/reader/mediainfo/MediaInfoFile.h"
#include "core/util/WindowUtil.h"
#include "core/plugins/interfaces/Job.h"
#include "core/gui/MeGUI.MainForm.h"
#include "core/util/Exceptions.h"
#include "core/util/VistaStuff.h"
#include "core/util/FileSize.h"
#include <string>
#include <vector>
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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;

using namespace MeGUI::core::plugins::implemented;
using namespace MeGUI::core::util;

namespace MeGUI
{
	enum StreamType
	{
		None = 0,
		Stderr = 1,
		Stdout = 2
	};

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
	template<typename TJob> where TJob : Job
	class CommandlineJobProcessor : public IJobProcessor
	{
	protected:
		TJob job;
		DateTime startTime;
		bool isProcessing;
		Process *proc; // the encoder process
		std::string executable; // path and filename of the commandline encoder to be used
		ManualResetEvent *mre; // lock used to pause encoding
		ManualResetEvent *stdoutDone;
		ManualResetEvent *stderrDone;
		StatusUpdate *su;
		LogItem *log;
		LogItem *stdoutLog;
		LogItem *stderrLog;
		Thread *readFromStdErrThread;
		Thread *readFromStdOutThread;
		std::vector<std::string> tempFiles;
		bool bRunSecondTime;
		bool bWaitForExit;


		void writeTempTextFile(const std::string &filePath, const std::string &text)
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (Stream temp = new FileStream(filePath, System.IO.FileMode.Create))
			Stream *temp = new FileStream(filePath, System::IO::FileMode::Create);
			try
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (TextWriter avswr = new StreamWriter(temp, System.Text.Encoding.Default))
				TextWriter *avswr = new StreamWriter(temp, System::Text::Encoding::Default);
				try
				{
					avswr->WriteLine(text);
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (avswr != 0)
						avswr.Dispose();
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (temp != 0)
					temp.Dispose();
			}
			tempFiles.push_back(filePath);
		}
	private:
		void deleteTempFiles()
		{
			for (std::vector<std::string>::const_iterator filePath = tempFiles.begin(); filePath != tempFiles.end(); ++filePath)
				safeDelete(*filePath);

		}

		static void safeDelete(const std::string &filePath)
		{
			try
			{
				File::Delete(filePath);
			}
			catch (...)
			{
				// Do Nothing
			}
		}

	protected:
		virtual void checkJobIO()
		{
			Util::ensureExists(job->Input);
		}

		virtual void doExitConfig()
		{
			if (su->getHasError() || su->getWasAborted())
				return;

			if (!job->Output->empty() && File::Exists(job->Output))
			{
				MediaInfoFile *oInfo = new MediaInfoFile(job->Output, log);
			}
		}

		// returns true if the exit code yields a meaningful answer
		const virtual bool &getcheckExitCode() const
		{
			return true;
		}

		virtual const std::string &getCommandline() const = 0;

		/// <summary>
		/// handles the encoder process existing
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void proc_Exited(object *sender, EventArgs *e)
		{
			mre->Set(); // Make sure nothing is waiting for pause to stop
			stdoutDone->WaitOne(); // wait for stdout to finish processing
			stderrDone->WaitOne(); // wait for stderr to finish processing

			// check the exitcode because x264.exe sometimes exits with error but without
			// any commandline indication as to why
			if (getcheckExitCode() && proc->ExitCode != 0)
			{
				std::string strError = WindowUtil::GetErrorText(proc->ExitCode);
				if (!su->getWasAborted())
				{
					su->setHasError(true);
					log->LogEvent("Process exits with error: " + strError, Error);
				}
				else
				{
					log->LogEvent("Process exits with error: " + strError);
				}
			}

			if (bRunSecondTime)
			{
				bRunSecondTime = false;
				start();
			}
			else
			{
				su->setIsComplete(true);
				doExitConfig();
				StatusUpdate(su);
			}

			bWaitForExit = false;
		}


	public:
		void setup(Job *job2, StatusUpdate *su, LogItem *log)
		{
			assert(dynamic_cast<TJob>(job2) != 0, "Job is the wrong type");

			this->log = log;
			TJob job = static_cast<TJob>(job2);
			this->job = job;

			// This enables relative paths, etc
			executable = Path::Combine(System::Windows::Forms::Application::StartupPath, executable);

			Util::ensureExists(executable);

			this->su = su;
			checkJobIO();
		}

		void start()
		{
			proc = new Process();
			ProcessStartInfo *pstart = new ProcessStartInfo();
			pstart->FileName = executable;
			pstart->Arguments = Commandline;
			pstart->RedirectStandardOutput = true;
			pstart->RedirectStandardError = true;
			pstart->WindowStyle = ProcessWindowStyle::Minimized;
			pstart->CreateNoWindow = true;
			pstart->UseShellExecute = false;
			proc->StartInfo = pstart;
			proc->EnableRaisingEvents = true;
			proc->Exited += new EventHandler(this, &CommandlineJobProcessor::proc_Exited);
			bWaitForExit = false;
			log->LogValue("Job commandline", '"' + pstart->FileName + "\" " + pstart->Arguments);

			try
			{
				bool started = proc->Start();
				startTime = DateTime::Now;
				isProcessing = true;
				log->LogEvent("Process started");
				stdoutLog = log->Info(std::string::Format("[{0:G}] {1}", DateTime::Now, "Standard output stream"));
				stderrLog = log->Info(std::string::Format("[{0:G}] {1}", DateTime::Now, "Standard error stream"));
				readFromStdErrThread = new Thread(new ThreadStart(readStdErr));
				readFromStdOutThread = new Thread(new ThreadStart(readStdOut));
				readFromStdOutThread->Start();
				readFromStdErrThread->Start();
				(new System::Windows::Forms::MethodInvoker(this->RunStatusCycle))->BeginInvoke(0, 0);
				this->changePriority(MainForm::Instance->getSettings()->getProcessingPriority());
			}
			catch (std::exception &e)
			{
				throw new JobRunException(e);
			}
		}

		void stop()
		{
			if (proc != 0 && !proc->HasExited)
			{
				try
				{
					bWaitForExit = true;
					mre->Set(); // if it's paused, then unpause
					su->setWasAborted(true);
					proc->Kill();
					while (bWaitForExit) // wait until the process has terminated without locking the GUI
					{
						System::Windows::Forms::Application::DoEvents();
						delay(100);
					}
					proc->WaitForExit();
					return;
				}
				catch (std::exception &e)
				{
					throw new JobRunException(e);
				}
			}
			else
			{
				if (proc == 0)
					throw new JobRunException("Encoder process does not exist");
				else
					throw new JobRunException("Encoder process has already existed");
			}
		}

		void pause()
		{
			if (!getcanPause())
				throw new JobRunException("Can't pause this kind of job.");
			if (!mre->Reset())
				throw new JobRunException("Could not reset mutex. pause failed");
		}

		void resume()
		{
			if (!getcanPause())
				throw new JobRunException("Can't resume this kind of job.");
			if (!mre->Set())
				throw new JobRunException("Could not set mutex. pause failed");
		}

		bool isRunning()
		{
			return (proc != 0 && !proc->HasExited);
		}

		void changePriority(ProcessPriority priority)
		{
			if (isRunning())
			{
				try
				{
					switch (priority)
					{
						case IDLE:
								proc->PriorityClass = ProcessPriorityClass::Idle;
								break;
						case BELOW_NORMAL:
								proc->PriorityClass = ProcessPriorityClass::BelowNormal;
								break;
						case NORMAL:
								proc->PriorityClass = ProcessPriorityClass::Normal;
								break;
						case ABOVE_NORMAL:
								proc->PriorityClass = ProcessPriorityClass::AboveNormal;
								break;
						case HIGH:
								proc->PriorityClass = ProcessPriorityClass::RealTime;
								break;
					}
					VistaStuff::SetProcessPriority(proc->Handle, proc->PriorityClass);
					MainForm::Instance->getSettings()->setProcessingPriority(priority);
					return;
				}
				catch (std::exception &e) // process could not be running anymore
				{
					throw new JobRunException(e);
				}
			}
			else
			{
				if (proc == 0)
					throw new JobRunException("Process has not been started yet");
				else
				{
					assert(proc->HasExited);
					throw new JobRunException("Process has exited");
				}
			}
		}

		const virtual bool &getcanPause() const
		{
			return true;
		}


	protected:
		virtual void readStream(StreamReader *sr, ManualResetEvent *rEvent, StreamType str)
		{
			std::string line;
			if (proc != 0)
			{
				try
				{
					while ((line = sr->ReadLine()) != 0)
					{
						mre->WaitOne();
						ProcessLine(line, str, Information);
					}
				}
				catch (std::exception &e)
				{
					ProcessLine("Exception in readStream. Line cannot be processed. " + e.what(), str, Error);
				}
				rEvent->Set();
			}
		}
		void readStdOut()
		{
			StreamReader *sr = 0;
			try
			{
				sr = proc->StandardOutput;
			}
			catch (std::exception &e)
			{
				log->LogValue("Exception getting IO reader for stdout", e, Error);
				stdoutDone->Set();
				return;
			}
			readStream(sr, stdoutDone, Stdout);
		}
		void readStdErr()
		{
			StreamReader *sr = 0;
			try
			{
				sr = proc->StandardError;
			}
			catch (std::exception &e)
			{
				log->LogValue("Exception getting IO reader for stderr", e, Error);
				stderrDone->Set();
				return;
			}
			readStream(sr, stderrDone, Stderr);
		}

	public:
		virtual void ProcessLine(const std::string &line, StreamType stream, ImageType oType)
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			if ((line.Trim())->empty())
				return;

			if (stream == Stdout)
				stdoutLog->LogEvent(line, oType);
			if (stream == Stderr)
				stderrLog->LogEvent(line, oType);

			if (oType == Error)
				su->setHasError(true);
		}

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event JobProcessingStatusUpdateCallback StatusUpdate;
	protected:
		void RunStatusCycle()
		{
			while (isRunning())
			{
				su->setTimeElapsed(DateTime::Now - startTime);
				su->setCurrentFileSize(FileSize::Of2(job->Output));

				doStatusCycleOverrides();
				su->FillValues();
				if (proc != 0 && !proc->HasExited)
					StatusUpdate(su);
				delay(1000);

			}
		}

		virtual void doStatusCycleOverrides()
		{
		}

	private:
		void InitializeInstanceFields()
		{
			isProcessing = false;
			proc = new Process();
			mre = new ManualResetEvent(true);
			stdoutDone = new ManualResetEvent(false);
			stderrDone = new ManualResetEvent(false);
			tempFiles = std::vector<std::string>();
			bRunSecondTime = false;
			bWaitForExit = false;
		}

public:
		CommandlineJobProcessor()
		{
			InitializeInstanceFields();
		}
	};
}
