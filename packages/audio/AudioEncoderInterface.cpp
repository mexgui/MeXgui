#include "AudioEncoderInterface.h"






//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;

//using namespace System::Globalization;



//using namespace System::Runtime::InteropServices;

//using namespace System::Text;

//using namespace System::Threading;


using namespace MeXgui::core::util;
using namespace MediaInfoWrapper;

namespace MeXgui
{

JobProcessorFactory *const AviSynthAudioEncoder::Factory = new JobProcessorFactory(new ProcessorFactory(&init), "AviSynthAudioEncoder");

	IJobProcessor *AviSynthAudioEncoder::init(MainForm *mf, Job *j)
	{
		if (dynamic_cast<AudioJob*>(j) != 0 && ((dynamic_cast<MP3Settings*>((dynamic_cast<AudioJob*>(j))->Settings) != 0) || (dynamic_cast<MP2Settings*>((dynamic_cast<AudioJob*>(j))->Settings) != 0) || (dynamic_cast<AC3Settings*>((dynamic_cast<AudioJob*>(j))->Settings) != 0) || (dynamic_cast<OggVorbisSettings*>((dynamic_cast<AudioJob*>(j))->Settings) != 0) || (dynamic_cast<NeroAACSettings*>((dynamic_cast<AudioJob*>(j))->Settings) != 0) || (dynamic_cast<FlacSettings*>((dynamic_cast<AudioJob*>(j))->Settings) != 0) || (dynamic_cast<AftenSettings*>((dynamic_cast<AudioJob*>(j))->Settings) != 0) || (dynamic_cast<QaacSettings*>((dynamic_cast<AudioJob*>(j))->Settings) != 0) || (dynamic_cast<OpusSettings*>((dynamic_cast<AudioJob*>(j))->Settings) != 0)))
			return new AviSynthAudioEncoder(mf->getSettings());
		return 0;
	}

System::Text::RegularExpressions::Regex *const AviSynthAudioEncoder::_cleanUpStringRegex = new System::Text::RegularExpressions::Regex("\\n[^\\n]+\\r", System::Text::RegularExpressions::RegexOptions::Compiled | System::Text::RegularExpressions::RegexOptions::CultureInvariant);

	void AviSynthAudioEncoder::writeTempTextFile(const QString &filePath, const QString &text)
	{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Stream temp = new FileStream(filePath, System.IO.FileMode.Create))
		Stream *temp = new FileStream(filePath, System::IO::FileMode::Create);
		try
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (TextWriter avswr = new StreamWriter(temp, System.Text.Encoding.Default))
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
		_tempFiles.push_back(filePath);
	}

	void AviSynthAudioEncoder::deleteTempFiles()
	{
		for (QVector<QString>::const_iterator filePath = _tempFiles.begin(); filePath != _tempFiles.end(); ++filePath)
			safeDelete(*filePath);

	}

	void AviSynthAudioEncoder::safeDelete(const QString &filePath)
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

	void AviSynthAudioEncoder::createTemporallyEqFiles(const QString &tempPath)
	{
		// http://forum.doom9.org/showthread.php?p=778156#post778156
		writeTempTextFile(tempPath + "front.feq", "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-4" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "");
		writeTempTextFile(tempPath + "center.feq", "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "3" + "\r\n" + "");
		writeTempTextFile(tempPath + "lfe.feq", "0" + "\r\n" + "0" + "\r\n" + "0" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "");
		writeTempTextFile(tempPath + "back.feq", "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-6" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "-96" + "\r\n" + "");
	}

	void AviSynthAudioEncoder::raiseEvent()
	{
		if (su->setIsComplete((su->getIsComplete() || su->getWasAborted() || su->getHasError())))
		{
			_mre->Set(); // Make sure nothing is waiting for pause to stop
			stdoutDone->WaitOne(); // wait for stdout to finish processing
			stderrDone->WaitOne(); // wait for stderr to finish processing

			if (!su->getHasError() && !su->getWasAborted())
			{
				if (!audioJob->Output.empty() && File::Exists(audioJob->Output))
				{
					MediaInfoFile *oInfo = new MediaInfoFile(audioJob->Output, _log);
				}
			}
			else if (su->getHasError() && dynamic_cast<QaacSettings*>(audioJob->Settings) != 0 && _encoderStdErr.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("coreaudiotoolbox.dll"))
			{
				_log->LogEvent("CoreAudioToolbox.dll is missing and must be installed. Please have a look at https://sites.google.com/site/qaacpage", Error);
				if (MessageBox::Show("CoreAudioToolbox.dll is missing and must be installed.\r\nOtherwise QAAC cannot be used.\r\n\r\nDo you want to open the installation instructions?", "CoreAudioToolbox.dll missing", MessageBoxButtons::YesNo, MessageBoxIcon::Error) == DialogResult::Yes)
					System::Diagnostics::Process::Start("https://sites.google.com/site/qaacpage");
			}
		}
		StatusUpdate(su);
	}

	void AviSynthAudioEncoder::setProgress(decimal n)
	{
		su->setPercentageDoneExact(n * 100);
		su->setCurrentFileSize(FileSize::Of2(audioJob->Output));
		su->setTimeElapsed(DateTime::Now - _start);
		su->FillValues();
		raiseEvent();
	}

	void AviSynthAudioEncoder::updateTime()
	{
		su->setTimeElapsed(DateTime::Now - _start);
		su->FillValues();
		raiseEvent();
	}

	void AviSynthAudioEncoder::raiseEvent(const QString &s)
	{
		su->setStatus(s);
		raiseEvent();
	}

	AviSynthAudioEncoder::AviSynthAudioEncoder(MeXguiSettings *settings) : _uniqueId(Guid::NewGuid()->ToString("N"))
	{
		InitializeInstanceFields();
		SAMPLES_PER_UPDATE = static_cast<int>(settings->getAudioSamplesPerUpdate());
		_settings = settings;
	}

	void AviSynthAudioEncoder::readStdOut()
	{
		StreamReader *sr = 0;
		try
		{
			sr = _encoderProcess->StandardOutput;
		}
		catch (std::exception &e)
		{
			_log->LogValue("Exception getting IO reader for stdout", e, Error);
			stdoutDone->Set();
			return;
		}
		readStream(sr, stdoutDone, Stdout);
	}

	void AviSynthAudioEncoder::readStdErr()
	{
		StreamReader *sr = 0;
		try
		{
			sr = _encoderProcess->StandardError;
		}
		catch (std::exception &e)
		{
			_log->LogValue("Exception getting IO reader for stderr", e, Error);
			stderrDone->Set();
			return;
		}
		readStream(sr, stderrDone, Stderr);
	}

	void AviSynthAudioEncoder::readStream(StreamReader *sr, ManualResetEvent *rEvent, StreamType str)
	{
		QString line;
		if (_encoderProcess != 0)
		{
			try
			{
				while ((line = sr->ReadLine()) != 0)
				{
					_mre->WaitOne();
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

	void AviSynthAudioEncoder::ProcessLine(const QString &line, StreamType stream, ImageType oType)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		line = _cleanUpStringRegex->Replace(line.Replace("\r\n", "\n"), "\r\n");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
		if ((line.Trim())->empty())
			return;

		if (dynamic_cast<QaacSettings*>(audioJob->Settings) != 0)
		{
			if (System::Text::RegularExpressions::Regex::IsMatch(line, "^[0-9]*:"))
				return;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
			if (line.ToLowerInvariant()->StartsWith("error:"))
				oType = Error;
		}
		else if (dynamic_cast<OggVorbisSettings*>(audioJob->Settings) != 0)
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
			if (line.ToLowerInvariant()->StartsWith("\tencoding ["))
				return;
		}
		else if (dynamic_cast<NeroAACSettings*>(audioJob->Settings) != 0)
		{
			if (System::Text::RegularExpressions::Regex::IsMatch(line.ToLowerInvariant(), "^processed\\s?[0-9]{0,5}\\s?seconds..."))
				return;
		}
		else if (dynamic_cast<AftenSettings*>(audioJob->Settings) != 0)
		{
			if (System::Text::RegularExpressions::Regex::IsMatch(line.ToLowerInvariant(), "^progress: "))
				return;
		}

		if (stream == Stderr)
			_encoderStdErr += line + "\n";

		if (stream == Stdout)
			stdoutLog->LogEvent(line, oType);
		if (stream == Stderr)
			stderrLog->LogEvent(line, oType);

		if (oType == Error)
			su->setHasError(true);
	}

	void AviSynthAudioEncoder::encode()
	{
		QString fileErr = MainForm::verifyInputFile(this->audioJob->Input);
		if (fileErr != "")
		{
			_log->LogEvent("Problem with audio input file: " + fileErr, Error);
			su->setIsComplete(true);
		su->setHasError(su->getIsComplete());
			raiseEvent();
			return;
		}

		Thread *t = 0;
		try
		{
			raiseEvent("Opening file....please wait, it may take some time");
			_start = DateTime::Now;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			t = new Thread(new ThreadStart(delegate
			{
				while (true)
				{
					updateTime();
					delay(1000);
				}
			}
		   ));
			t->Start();
			createAviSynthScript();
			raiseEvent("Preprocessing...please wait, it may take some time");
			_start = DateTime::Now;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AviSynthScriptEnvironment env = new AviSynthScriptEnvironment())
			AviSynthScriptEnvironment *env = new AviSynthScriptEnvironment();
			try
			{
				_log->LogEvent("Avisynth script environment opened");
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (AviSynthClip a = env.ParseScript(_avisynthAudioScript))
				AviSynthClip *a = env->ParseScript(_avisynthAudioScript);
				try
				{
					_log->LogEvent("Script loaded");
					if (0 == a->getChannelsCount())
						throw new ApplicationException("Can't find audio stream");

					LogItem *inputLog = _log->LogEvent("Output Decoder", Information);
					inputLog->LogValue("Channels", a->getChannelsCount());
					inputLog->LogValue("Bits per sample", a->getBitsPerSample());
					inputLog->LogValue("Sample rate", a->getAudioSampleRate());

					if (dynamic_cast<FlacSettings*>(audioJob->Settings) != 0)
						_encoderCommandLine += " --channels=" + a->getChannelsCount() + " --bps=" + a->getBitsPerSample() + " --sample-rate=" + a->getAudioSampleRate();

					const int MAX_SAMPLES_PER_ONCE = 4096;
					int frameSample = 0;
					int lastUpdateSample = 0;
					int frameBufferTotalSize = MAX_SAMPLES_PER_ONCE * a->getChannelsCount() * a->getBytesPerSample();
					unsigned char frameBuffer[frameBufferTotalSize];
					createEncoderProcess(a);
					try
					{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//						using (Stream target = _encoderProcess.StandardInput.BaseStream)
						Stream *target = _encoderProcess->StandardInput->BaseStream;
						try
						{
							// let's write WAV Header
							if (_mustSendWavHeaderToEncoderStdIn)
								writeHeader(target, a);

							_sampleRate = a->getAudioSampleRate();

							bool hasStartedEncoding = false;

							GCHandle *h = GCHandle::Alloc(frameBuffer, GCHandleType::Pinned);
							void* address = h->AddrOfPinnedObject();
							try
							{
								su->setClipLength(TimeSpan::FromSeconds(static_cast<double>(a->getSamplesCount()) / static_cast<double>(_sampleRate)));
								while (frameSample < a->getSamplesCount())
								{
									_mre->WaitOne();

									if (_encoderProcess != 0)
										if (_encoderProcess->HasExited)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
											throw new ApplicationException("Abnormal encoder termination. Exit code: " + _encoderProcess->ExitCode->ToString());
									int nHowMany = __min(static_cast<int>(a->getSamplesCount() - frameSample), MAX_SAMPLES_PER_ONCE);

									a->ReadAudio(address, frameSample, nHowMany);

									_mre->WaitOne();
									if (!hasStartedEncoding)
									{
										t->Abort();
										raiseEvent("Encoding audio...");
										hasStartedEncoding = true;
									}

									target->Write(frameBuffer, 0, nHowMany * a->getChannelsCount() * a->getBytesPerSample());
									target->Flush();
									frameSample += nHowMany;
									if (frameSample - lastUpdateSample > SAMPLES_PER_UPDATE)
									{
										setProgress(static_cast<decimal>(frameSample) / static_cast<decimal>(a->getSamplesCount()));
										lastUpdateSample = frameSample;
									}
									delay(0);
								}
							}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
							finally
							{
								h->Free();
							}
							setProgress(1);

							if (_mustSendWavHeaderToEncoderStdIn && a->getBytesPerSample() % 2 == 1)
								target->WriteByte(0);
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
						finally
						{
							if (target != 0)
								target.Dispose();
						}
						raiseEvent("Finalizing encoder");
						while (!_encoderProcess->HasExited) // wait until the process has terminated without locking the GUI
						{
							System::Windows::Forms::Application::DoEvents();
							delay(100);
						}
						_encoderProcess->WaitForExit();
						_readFromStdErrThread->Join();
						_readFromStdOutThread->Join();
						if (0 != _encoderProcess->ExitCode)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
							throw new ApplicationException("Abnormal encoder termination " + _encoderProcess->ExitCode->ToString());

					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (!_encoderProcess->HasExited)
						{
							_encoderProcess->Kill();
							while (!_encoderProcess->HasExited) // wait until the process has terminated without locking the GUI
							{
								System::Windows::Forms::Application::DoEvents();
								delay(100);
							}
							_encoderProcess->WaitForExit();
							_readFromStdErrThread->Join();
							_readFromStdOutThread->Join();
						}
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
						delete _readFromStdErrThread;
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
						delete _readFromStdOutThread;
					}
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (a != 0)
						a.Dispose();
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (env != 0)
					env.Dispose();
			}
		}
		catch (std::exception &e)
		{
			deleteOutputFile();
			if (dynamic_cast<ThreadAbortException*>(e) != 0)
			{
				_log->LogEvent("Aborting...");
				su->setWasAborted(true);
				raiseEvent();
			}
			else
			{
				_log->LogValue("An error occurred", e, Error);
				su->setHasError(true);
				raiseEvent();
			}
			return;
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			t->Abort();
			deleteTempFiles();
		}
		su->setIsComplete(true);
		raiseEvent();
	}

	void AviSynthAudioEncoder::deleteOutputFile()
	{
		safeDelete(audioJob->Output);
	}

	void AviSynthAudioEncoder::createEncoderProcess(AviSynthClip *a)
	{
		try
		{
			_encoderProcess = new Process();
			ProcessStartInfo *info = new ProcessStartInfo();
			// Command line arguments, to be passed to encoder
			// {0} means output file name
			// {1} means samplerate in Hz
			// {2} means bits per sample
			// {3} means channel count
			// {4} means samplecount
			// {5} means size in bytes
			info->Arguments = QString::Format(_encoderCommandLine, audioJob->Output, a->getAudioSampleRate(), a->getBitsPerSample(), a->getChannelsCount(), a->getSamplesCount(), a->getAudioSizeInBytes());
			info->FileName = _encoderExecutablePath;
			_log->LogValue("Job commandline", _encoderExecutablePath + " " + info->Arguments);
			info->UseShellExecute = false;
			info->RedirectStandardInput = true;
			info->RedirectStandardOutput = true;
			info->RedirectStandardError = true;
			info->CreateNoWindow = true;
			_encoderProcess->StartInfo = info;
			_encoderProcess->Start();

			// Take priority from Avisynth thread rather than default in settings
			// just in case user has managed to change job setting before getting here.
			if (_encoderThread->Priority == ThreadPriority::Lowest)
				this->changePriority(IDLE);
			else if (_encoderThread->Priority == ThreadPriority::BelowNormal)
				this->changePriority(BELOW_NORMAL);
			else if (_encoderThread->Priority == ThreadPriority::Normal)
				this->changePriority(NORMAL);
			else if (_encoderThread->Priority == ThreadPriority::AboveNormal)
				this->changePriority(ABOVE_NORMAL);
			else if (_encoderThread->Priority == ThreadPriority::Highest)
				this->changePriority(HIGH);

			_log->LogEvent("Process started");
			stdoutLog = _log->Info(QString::Format("[{0:G}] {1}", DateTime::Now, "Standard output stream"));
			stderrLog = _log->Info(QString::Format("[{0:G}] {1}", DateTime::Now, "Standard error stream"));
			_readFromStdOutThread = new Thread(new ThreadStart(readStdOut));
			_readFromStdErrThread = new Thread(new ThreadStart(readStdErr));
			_readFromStdOutThread->Start();
			_readFromStdErrThread->Start();
		}
		catch (std::exception &e)
		{
			throw new ApplicationException("Can't start encoder: " + e.what(), e);
		}
	}

	void AviSynthAudioEncoder::writeHeader(Stream *target, AviSynthClip *a)
	{
		const unsigned int FAAD_MAGIC_VALUE = 0xFFFFFF00;
		const unsigned int WAV_HEADER_SIZE = 36;
		bool useFaadTrick = a->getAudioSizeInBytes() >= (static_cast<qint64>(unsigned int::MaxValue) - WAV_HEADER_SIZE);
		target->Write(System::Text::Encoding::ASCII::GetBytes("RIFF"), 0, 4);
		target->Write(BitConverter::GetBytes(useFaadTrick ? FAAD_MAGIC_VALUE : static_cast<unsigned int>(a->getAudioSizeInBytes() + WAV_HEADER_SIZE)), 0, 4);
		target->Write(System::Text::Encoding::ASCII::GetBytes("WAVEfmt "), 0, 8);
		target->Write(BitConverter::GetBytes(static_cast<unsigned int>(0x10)), 0, 4);
		target->Write(BitConverter::GetBytes((a->getSampleType() == FLOAT) ? static_cast<short>(0x03) : static_cast<short>(0x01)), 0, 2);
		target->Write(BitConverter::GetBytes(a->getChannelsCount()), 0, 2);
		target->Write(BitConverter::GetBytes(a->getAudioSampleRate()), 0, 4);
		target->Write(BitConverter::GetBytes(a->getAvgBytesPerSec()), 0, 4);
		target->Write(BitConverter::GetBytes(a->getBytesPerSample()*a->getChannelsCount()), 0, 2);
		target->Write(BitConverter::GetBytes(a->getBitsPerSample()), 0, 2);
		target->Write(System::Text::Encoding::ASCII::GetBytes("data"), 0, 4);
		target->Write(BitConverter::GetBytes(useFaadTrick ? (FAAD_MAGIC_VALUE - WAV_HEADER_SIZE) : static_cast<unsigned int>(a->getAudioSizeInBytes())), 0, 4);
	}

	void AviSynthAudioEncoder::Start()
	{
		Util::ensureExists(audioJob->Input);
		_encoderThread = new Thread(new ThreadStart(this->encode));
		if (MainForm::Instance->getSettings()->getProcessingPriority() == HIGH)
			_encoderThread->Priority = ThreadPriority::Highest;
		else if (MainForm::Instance->getSettings()->getProcessingPriority() == ABOVE_NORMAL)
			_encoderThread->Priority = ThreadPriority::AboveNormal;
		else if (MainForm::Instance->getSettings()->getProcessingPriority() == NORMAL)
			_encoderThread->Priority = ThreadPriority::Normal;
		else if (MainForm::Instance->getSettings()->getProcessingPriority() == BELOW_NORMAL)
			_encoderThread->Priority = ThreadPriority::BelowNormal;
		else
			_encoderThread->Priority = ThreadPriority::Lowest;
		_encoderThread->Start();
	}

	void AviSynthAudioEncoder::Abort()
	{
		_encoderThread->Abort();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete _encoderThread;
	}

	bool AviSynthAudioEncoder::OpenSourceWithFFAudioSource(StringBuilder *&sbOpen)
	{
		sbOpen = new StringBuilder();
		sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getFFMSIndexPath()), "ffms2.dll"), "\r\n");
		sbOpen->AppendFormat("FFAudioSource(\"{0}\"){1}", audioJob->Input, "\r\n");
		_log->LogEvent("Trying to open the file with FFAudioSource()", Information);
		QString strErrorText = "";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (AudioUtil::AVSScriptHasAudio(sbOpen->ToString(), strErrorText))
		{
			_log->LogEvent("Successfully opened the file with FFAudioSource()", Information);
			audioJob->FilesToDelete.push_back(audioJob->Input + ".ffindex");
			return true;
		}
		sbOpen = new StringBuilder();
		FileUtil::DeleteFile(audioJob->Input + ".ffindex");
		if (strErrorText.empty())
			_log->LogEvent("Failed opening the file with FFAudioSource()", Information);
		else
			_log->LogEvent("Failed opening the file with FFAudioSource(). " + strErrorText, Information);
		return false;
	}

	bool AviSynthAudioEncoder::OpenSourceWithBassAudio(StringBuilder *&sbOpen)
	{
		sbOpen = new StringBuilder();
		sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", MainForm::Instance->getSettings()->getBassPath(), "\r\n");
		sbOpen->AppendFormat("BassAudioSource(\"{0}\"){1}", audioJob->Input, "\r\n");
		_log->LogEvent("Trying to open the file with BassAudioSource()", Information);
		QString strErrorText = "";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (AudioUtil::AVSScriptHasAudio(sbOpen->ToString(), strErrorText))
		{
			_log->LogEvent("Successfully opened the file with BassAudioSource()", Information);
			return true;
		}
		sbOpen = new StringBuilder();
		if (strErrorText.empty())
			_log->LogEvent("Failed opening the file with BassAudioSource()", Information);
		else
			_log->LogEvent("Failed opening the file with BassAudioSource(). " + strErrorText, Information);
		return false;
	}

	bool AviSynthAudioEncoder::OpenSourceWithDirectShow(StringBuilder *&sbOpen, MediaInfoFile *oInfo)
	{
		sbOpen = new StringBuilder();

		try
		{
			if (oInfo->getHasAudio())
			{
				if (MainForm::Instance->getSettings()->getPortableAviSynth())
					sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getAviSynthPath()), "directshowsource.dll"), "\r\n");
				if (oInfo->getHasVideo())
					sbOpen->AppendFormat("DirectShowSource(\"{0}\", video=false){1}", audioJob->Input, "\r\n");
				else
					sbOpen->AppendFormat("DirectShowSource(\"{0}\"){1}", audioJob->Input, "\r\n");
				sbOpen->AppendFormat("EnsureVBRMP3Sync(){0}", "\r\n");
			}
		}
		catch (...)
		{
		}

		QString strErrorText = "";
		_log->LogEvent("Trying to open the file with DirectShowSource()", Information);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (sbOpen->Length > 0 && AudioUtil::AVSScriptHasAudio(sbOpen->ToString(), strErrorText))
		{
			_log->LogEvent("Successfully opened the file with DirectShowSource()", Information);
			return true;
		}
		sbOpen = new StringBuilder();
		if (strErrorText.empty())
			_log->LogEvent("Failed opening the file with DirectShowSource()", Information);
		else
			_log->LogEvent("Failed opening the file with DirectShowSource(). " + strErrorText, Information);
		return false;
	}

	bool AviSynthAudioEncoder::OpenSourceWithImportAVS(StringBuilder *&sbOpen, MediaInfoFile *oInfo)
	{
		sbOpen = new StringBuilder();

		try
		{
			if (oInfo->getHasAudio())
				sbOpen->AppendFormat("Import(\"{0}\"){1}", audioJob->Input, "\r\n");
		}
		catch (...)
		{
		}

		QString strErrorText = "";
		_log->LogEvent("Trying to open the file with Import()", Information);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		if (sbOpen->Length > 0 && AudioUtil::AVSScriptHasAudio(sbOpen->ToString(), strErrorText))
		{
			_log->LogEvent("Successfully opened the file with Import()", Information);
			return true;
		}
		sbOpen = new StringBuilder();
		if (strErrorText.empty())
			_log->LogEvent("Failed opening the file with Import()", Information);
		else
			_log->LogEvent("Failed opening the file with Import(). " + strErrorText, Information);
		return false;
	}

	bool AviSynthAudioEncoder::OpenSourceWithNicAudio(StringBuilder *&sbOpen, MediaInfoFile *oInfo, bool bForce)
	{
		sbOpen = new StringBuilder();
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (Path.GetExtension(audioJob.Input).ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case ".ac3":
		if (Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".ac3" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".ddp" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".eac3")
		{
				sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"), "\r\n");
				sbOpen->AppendFormat("NicAc3Source(\"{0}\"", audioJob->Input);
				if (audioJob->Settings->getApplyDRC())
					sbOpen->AppendFormat(", DRC=1){0}", "\r\n");
				else
					sbOpen->AppendFormat("){0}", "\r\n");
		}
//ORIGINAL LINE: case ".avi":
		else if (Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".avi")
		{
				sbOpen->AppendFormat("AVISource(\"{0}\", audio=true){1}", audioJob->Input, "\r\n");
				sbOpen->AppendFormat("EnsureVBRMP3Sync(){0}", "\r\n");
				sbOpen->AppendFormat("Trim(0,0){0}", "\r\n"); // to match audio length
		}
//ORIGINAL LINE: case ".avs":
		else if (Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".avs")
		{
				sbOpen->AppendFormat("Import(\"{0}\"){1}", audioJob->Input, "\r\n");
		}
//ORIGINAL LINE: case ".dtshd":
		else if (Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".dtshd" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".dtsma" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".dts")
		{
				sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"), "\r\n");
				sbOpen->AppendFormat("NicDtsSource(\"{0}\"", audioJob->Input);
				if (audioJob->Settings->getApplyDRC())
					sbOpen->AppendFormat(", DRC=1){0}", "\r\n");
				else
					sbOpen->AppendFormat("){0}", "\r\n");
		}
//ORIGINAL LINE: case ".mpa":
		else if (Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".mpa" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".mpg" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".mp2" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".mp3")
		{
				sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"), "\r\n");
				sbOpen->AppendFormat("NicMPG123Source(\"{0}\"){1}", audioJob->Input, "\r\n");
				audioJob->FilesToDelete.push_back(audioJob->Input + ".d2a");
		}
//ORIGINAL LINE: case ".wav":
		else if (Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".wav")
		{
				BinaryReader *r = new BinaryReader(File->Open(audioJob->Input, FileMode->Open, FileAccess::Read));

				try
				{
					r->ReadBytes(20);
					unsigned short AudioFormat = r->ReadUInt16(); // read a LE int_16, offset 20 + 2 = 22

					switch (AudioFormat)
					{
						case 0x0001: // PCM Format Int
							r->ReadBytes(22); // 22 + 22 = 44
							unsigned int DtsHeader = r->ReadUInt32(); // read a LE int_32
							sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"), "\r\n");
							if (DtsHeader == 0xE8001FFF)
							{
								sbOpen->AppendFormat("NicDtsSource(\"{0}\"", audioJob->Input);
								if (audioJob->Settings->getApplyDRC())
									sbOpen->AppendFormat(", DRC=1){0}", "\r\n");
								else
									sbOpen->AppendFormat("){0}", "\r\n");
							}
							else
								sbOpen->AppendFormat("RaWavSource(\"{0}\"){1}", audioJob->Input, "\r\n");
							break;
						case 0x0003: // IEEE Float
						case 0xFFFE: // WAVE_FORMAT_EXTENSIBLE header
							sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"), "\r\n");
							sbOpen->AppendFormat("RaWavSource(\"{0}\"){1}", audioJob->Input, "\r\n");
							break;
						case 0x0055: // MPEG Layer 3
							sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"), "\r\n");
							sbOpen->AppendFormat("NicMPG123Source(\"{0}\"){1}", audioJob->Input, "\r\n");
							break;
						case 0x2000: // AC3
							sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"), "\r\n");
							sbOpen->AppendFormat("NicAc3Source(\"{0}\"", audioJob->Input);
							if (audioJob->Settings->getApplyDRC())
								sbOpen->AppendFormat(", DRC=1){0}", "\r\n");
							else
								sbOpen->AppendFormat("){0}", "\r\n");
							break;
						default:
							sbOpen->AppendFormat("WavSource(\"{0}\"){1}", audioJob->Input, "\r\n");
							break;
					}
				}
				catch (EndOfStreamException *e)
				{
					LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
					_oLog->LogValue(e->GetType()->Name + ", wavfile can't be read.", e, Error);
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					r->Close();
				}
		}
//ORIGINAL LINE: case ".w64":
		else if (Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".w64" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".aif" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".au" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".caf" || Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture) == ".bwf")
		{
				sbOpen->AppendFormat("LoadPlugin(\"{0}\"){1}", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "NicAudio.dll"), "\r\n");
				sbOpen->AppendFormat("RaWavSource(\"{0}\", 2){1}", audioJob->Input, "\r\n");
		}

		_log->LogEvent("Trying to open the file with NicAudio", Information);

		QString strErrorText = "";
		if (oInfo->getAudioInfo()->getTracks().size() > 0 && oInfo->getAudioInfo()->getTracks()[0]->getCodec()->Equals("DTS-HD Master Audio") && !bForce)
		{
			_log->LogEvent("DTS-MA is blocked in the first place when using NicAudio", Information);
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		else if (sbOpen->Length > 0 && AudioUtil::AVSScriptHasAudio(sbOpen->ToString(), strErrorText))
		{
			_log->LogEvent("Successfully opened the file with NicAudio", Information);
			return true;
		}

		sbOpen = new StringBuilder();
		if (strErrorText.empty())
			_log->LogEvent("Failed opening the file with NicAudio()", Information);
		else
			_log->LogEvent("Failed opening the file with NicAudio(). " + strErrorText, Information);
		return false;
	}

	void AviSynthAudioEncoder::setup(Job *job, StatusUpdate *su, LogItem *log)
	{
		this->_log = log;
		this->audioJob = static_cast<AudioJob*>(job);
		this->su = su;
	}

	void AviSynthAudioEncoder::createAviSynthScript()
	{
		//let's create avisynth script
		StringBuilder *script = new StringBuilder();

		QString id = _uniqueId;
		QString tmp = Path::Combine(Path::GetTempPath(), id);

		MediaInfoFile *oInfo = new MediaInfoFile(audioJob->Input, _log);

		bool bFound = false;
		if (oInfo->getContainerFileTypeString().Equals("AVS"))
		{
			bFound = OpenSourceWithImportAVS(script, oInfo);
		}
		else if (audioJob->Settings->getPreferredDecoder() == NicAudio)
		{
			bFound = OpenSourceWithNicAudio(script, oInfo, false);
			if (!bFound)
				bFound = OpenSourceWithBassAudio(script);
			if (!bFound)
				bFound = OpenSourceWithFFAudioSource(script);
			if (!bFound)
				bFound = OpenSourceWithDirectShow(script, oInfo);
		}
		else if (audioJob->Settings->getPreferredDecoder() == BassAudio)
		{
			bFound = OpenSourceWithBassAudio(script);
			if (!bFound)
				bFound = OpenSourceWithNicAudio(script, oInfo, false);
			if (!bFound)
				bFound = OpenSourceWithFFAudioSource(script);
			if (!bFound)
				bFound = OpenSourceWithDirectShow(script, oInfo);
		}
		else if (audioJob->Settings->getPreferredDecoder() == FFAudioSource)
		{
			bFound = OpenSourceWithFFAudioSource(script);
			if (!bFound)
				bFound = OpenSourceWithNicAudio(script, oInfo, false);
			if (!bFound)
				bFound = OpenSourceWithBassAudio(script);
			if (!bFound)
				bFound = OpenSourceWithDirectShow(script, oInfo);
		}
		else
		{
			bFound = OpenSourceWithDirectShow(script, oInfo);
			if (!bFound)
				bFound = OpenSourceWithNicAudio(script, oInfo, false);
			if (!bFound)
				bFound = OpenSourceWithBassAudio(script);
			if (!bFound)
				bFound = OpenSourceWithFFAudioSource(script);
		}

		if (!bFound && oInfo->getAudioInfo()->getTracks().size() > 0 && oInfo->getAudioInfo()->getTracks()[0]->getCodec()->Equals("DTS-HD Master Audio"))
			bFound = OpenSourceWithNicAudio(script, oInfo, true);

		if (!bFound)
		{
			deleteTempFiles();
			throw new JobRunException("Input file cannot be opened: " + audioJob->Input);
		}

		if (audioJob->Delay != 0)
			script->AppendFormat("DelayAudio({0}.0/1000.0){1}", audioJob->Delay, "\r\n");

		if (!audioJob->CutFile.empty())
		{
			try
			{
				Cuts *cuts = FilmCutter::ReadCutsFromFile(audioJob->CutFile);
				script->AppendLine(FilmCutter::GetCutsScript(cuts, true));
			}
			catch (FileNotFoundException *e1)
			{
				deleteTempFiles();
				throw new MissingFileException(audioJob->CutFile);
			}
			catch (std::exception &e2)
			{
				deleteTempFiles();
				throw new JobRunException("Broken cuts file, " + audioJob->CutFile + ", can't continue.");
			}
		}

		switch (audioJob->Settings->getDownmixMode())
		{
			case KeepOriginal:
				break;
			case ConvertToMono:
				script->AppendFormat("ConvertToMono(){0}", "\r\n");
				break;
			case DPLDownmix:
			case DPLIIDownmix:
			case StereoDownmix:
				QString strChannelPositions;
				int iChannelCount = 0;
				if (Path::GetExtension(audioJob->Input)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".avs"))
				{
					if (!AudioUtil::AVSFileHasAudio(audioJob->Input))
					{
						_log->LogEvent("avs file has no audio: " + audioJob->Input, Error);
						break;
					}
					iChannelCount = AudioUtil::getChannelCountFromAVSFile(audioJob->Input);
					script->Append("# detected channels: " + iChannelCount + " channels" + "\r\n");
					strChannelPositions = AudioUtil::getChannelPositionsFromAVSFile(audioJob->Input);
				}
				else
				{
					if (!oInfo->getHasAudio())
					{
						_log->LogEvent("no audio file detected: " + audioJob->Input, Error);
						break;
					}
					strChannelPositions = oInfo->getAudioInfo()->getTracks()[0]->getChannelPositions();
					script->Append("# detected channels: " + oInfo->getAudioInfo()->getTracks()[0]->getNbChannels() + "\r\n");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					int::TryParse(oInfo->getAudioInfo()->getTracks()[0]->getNbChannels()->Split(' ')[0], iChannelCount);
				}

				if (!strChannelPositions.empty())
					script->Append("# detected channel positions: " + strChannelPositions + "\r\n");
				else
					_log->LogEvent("no channel positions found. Downmix result may be wrong.", Information);

				if (iChannelCount <= 2)
				{
					_log->LogEvent("ignoring downmix as there are only " + iChannelCount + " channels", Information);
					break;
				}

				int iAVSChannelCount = 0;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//				using (AvsFile avi = AvsFile.ParseScript(script.ToString()))
				AvsFile *avi = AvsFile::ParseScript(script->ToString());
				try
				{
					iAVSChannelCount = avi->getClip()->getChannelsCount();
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (avi != 0)
						avi.Dispose();
				}

				if (iAVSChannelCount != iChannelCount)
				{
					_log->LogEvent("channel count mismatch! ignoring downmix as the input file is reporting " + iChannelCount + " channels and the AviSynth script is reporting " + iAVSChannelCount + " channels", Warning);
					break;
				}

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//				switch (strChannelPositions)
					// http://forum.doom9.org/showthread.php?p=1461787#post1461787
//ORIGINAL LINE: case "3/0/0":
				if (strChannelPositions == "3/0/0" || strChannelPositions == "2/0/0.1")
				{
						script->Append("c3_stereo(ConvertAudioToFloat(last))" + "\r\n");
				}
//ORIGINAL LINE: case "2/1/0":
				else if (strChannelPositions == "2/1/0" || strChannelPositions == "2/0/1")
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
										script->Append("c3_stereo(ConvertAudioToFloat(last))" + "\r\n");
									else
										script->Append("c3_dpl(ConvertAudioToFloat(last))" + "\r\n");
				}
//ORIGINAL LINE: case "2/2/0":
				else if (strChannelPositions == "2/2/0" || strChannelPositions == "2/0/2")
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
										script->Append("c4_stereo(ConvertAudioToFloat(last))" + "\r\n");
									else if (audioJob->Settings->getDownmixMode() == DPLDownmix)
										script->Append("c4_dpl(ConvertAudioToFloat(last))" + "\r\n");
									else
										script->Append("c4_dpl2(ConvertAudioToFloat(last))" + "\r\n");
				}
//ORIGINAL LINE: case "2/1/0.1":
				else if (strChannelPositions == "2/1/0.1" || strChannelPositions == "2/0/1.1")
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
										script->Append("c42_stereo(ConvertAudioToFloat(last))" + "\r\n");
									else
											script->Append("c42_dpl(ConvertAudioToFloat(last))" + "\r\n");
				}
//ORIGINAL LINE: case "3/0/0.1":
				else if (strChannelPositions == "3/0/0.1")
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
										script->Append("c42_stereo(ConvertAudioToFloat(last))" + "\r\n");
									else
										script->Append("c3_stereo(ConvertAudioToFloat(last))" + "\r\n");

				}
//ORIGINAL LINE: case "3/1/0":
				else if (strChannelPositions == "3/1/0" || strChannelPositions == "3/0/1")
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
										script->Append("c42_stereo(ConvertAudioToFloat(last))" + "\r\n");
									else
										script->Append("c43_dpl(ConvertAudioToFloat(last))" + "\r\n");
				}
//ORIGINAL LINE: case "3/2/0":
				else if (strChannelPositions == "3/2/0" || strChannelPositions == "3/0/2")
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
										script->Append("c5_stereo(ConvertAudioToFloat(last))" + "\r\n");
									else if (audioJob->Settings->getDownmixMode() == DPLDownmix)
										script->Append("c5_dpl(ConvertAudioToFloat(last))" + "\r\n");
									else
										script->Append("c5_dpl2(ConvertAudioToFloat(last))" + "\r\n");
				}
//ORIGINAL LINE: case "2/2/0.1":
				else if (strChannelPositions == "2/2/0.1" || strChannelPositions == "2/0/2.1")
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
										script->Append("c5_stereo(ConvertAudioToFloat(last))" + "\r\n");
									else if (audioJob->Settings->getDownmixMode() == DPLDownmix)
										script->Append("c52_dpl(ConvertAudioToFloat(last))" + "\r\n");
									else
										script->Append("c52_dpl2(ConvertAudioToFloat(last))" + "\r\n");
				}
//ORIGINAL LINE: case "3/1/0.1":
				else if (strChannelPositions == "3/1/0.1" || strChannelPositions == "3/0/1.1")
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
										script->Append("c52_stereo(ConvertAudioToFloat(last))" + "\r\n");
									else
										script->Append("c53_dpl(ConvertAudioToFloat(last))" + "\r\n");
				}
//ORIGINAL LINE: case "3/2/0.1":
				else if (strChannelPositions == "3/2/0.1" || strChannelPositions == "3/0/2.1")
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
										script->Append("c6_stereo(ConvertAudioToFloat(last))" + "\r\n");
									else if (audioJob->Settings->getDownmixMode() == DPLDownmix)
										script->Append("c6_dpl(ConvertAudioToFloat(last))" + "\r\n");
									else
										script->Append("c6_dpl2(ConvertAudioToFloat(last))" + "\r\n");
				}
				else
				{
						if (audioJob->Settings->getDownmixMode() == StereoDownmix)
						{
										script->Append("6<=Audiochannels(last)?c6_stereo(ConvertAudioToFloat(last)):last" + "\r\n");
										script->Append("5==Audiochannels(last)?c5_stereo(ConvertAudioToFloat(last)):last" + "\r\n");
										script->Append("4==Audiochannels(last)?c4_stereo(ConvertAudioToFloat(last)):last" + "\r\n");
										script->Append("3==Audiochannels(last)?c3_stereo(ConvertAudioToFloat(last)):last" + "\r\n");
						}
									else if (audioJob->Settings->getDownmixMode() == DPLDownmix)
									{
										script->Append("6<=Audiochannels(last)?c6_dpl(ConvertAudioToFloat(last)):last" + "\r\n");
										script->Append("5==Audiochannels(last)?c5_dpl(ConvertAudioToFloat(last)):last" + "\r\n");
										script->Append("4==Audiochannels(last)?c4_dpl(ConvertAudioToFloat(last)):last" + "\r\n");
										script->Append("3==Audiochannels(last)?c3_dpl(ConvertAudioToFloat(last)):last" + "\r\n");
									}
									else
									{
										script->Append("6<=Audiochannels(last)?c6_dpl2(ConvertAudioToFloat(last)):last" + "\r\n");
										script->Append("5==Audiochannels(last)?c5_dpl2(ConvertAudioToFloat(last)):last" + "\r\n");
										script->Append("4==Audiochannels(last)?c4_dpl2(ConvertAudioToFloat(last)):last" + "\r\n");
										script->Append("3==Audiochannels(last)?c3_dpl2(ConvertAudioToFloat(last)):last" + "\r\n");
									}
				}
				break;
			case Upmix:
				createTemporallyEqFiles(tmp);
				script->Append("2==Audiochannels(last)?x_upmix" + id + "(last):last" + "\r\n");
				break;
			case UpmixUsingSoxEq:
				script->Append("2==Audiochannels(last)?x_upmixR" + id + "(last):last" + "\r\n");
				break;
			case UpmixWithCenterChannelDialog:
				script->Append("2==Audiochannels(last)?x_upmixC" + id + "(last):last" + "\r\n");
				break;
		}

		// SampleRate
		switch (audioJob->Settings->getSampleRateType())
		{
			case 0:
				break;
			case 1:
				script->Append("SSRC(8000)" + "\r\n");
				break;
			case 2:
				script->Append("SSRC(11025)" + "\r\n");
				break;
			case 3:
				script->Append("SSRC(22050)" + "\r\n");
				break;
			case 4:
				script->Append("SSRC(32000)" + "\r\n");
				break;
			case 5:
				script->Append("SSRC(44100)" + "\r\n");
				break;
			case 6:
				script->Append("SSRC(48000)" + "\r\n");
				break;
			case 7: // Speed-up (23.976 to 25)
				script->Append("AssumeSampleRate((AudioRate()*1001+480)/960).SSRC(AudioRate()).TimeStretch(pitch=Float((AudioRate()*1001+480)/960)*100.0/Float(AudioRate()))" + "\r\n");
				break;
			case 8: // Slow-down (25 to 23.976)
				script->Append("SSRC((AudioRate()*1001+480)/960).AssumeSampleRate(AudioRate()).TimeStretch(pitch=Float((AudioRate()*1001+480)/960)*100.0/Float(AudioRate()))" + "\r\n");
				break;
			case 9: // Speed-up (24 to 25)
				script->Append("AssumeSampleRate((AudioRate()*25)/24).SSRC(AudioRate()).TimeStretch(pitch=Float((AudioRate()*25)/24)*100.0/Float(AudioRate()))" + "\r\n");
				break;
			case 10: // Slow-down (25 to 24)
				script->Append("SSRC((AudioRate()*25)/24).AssumeSampleRate(AudioRate()).TimeStretch(pitch=Float((AudioRate()*25)/24)*100.0/Float(AudioRate()))" + "\r\n");
				break;
		}

		// put Normalize() after downmix cases >> http://forum.doom9.org/showthread.php?p=1166117#post1166117
		if (audioJob->Settings->getAutoGain())
		{
			if (audioJob->Settings->getNormalize() != 100)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				 script->AppendFormat("Normalize(" + (audioJob->Settings->getNormalize() / 100.0)->ToString(new CultureInfo("en-us")) + "){0}", "\r\n");
			else
				script->AppendFormat("Normalize(){0}", "\r\n");
		}

		//let's obtain command line & other staff
		if (dynamic_cast<AftenSettings*>(audioJob->Settings) != 0)
		{
			_mustSendWavHeaderToEncoderStdIn = true;
			AftenSettings *n = dynamic_cast<AftenSettings*>(audioJob->Settings);
			_encoderExecutablePath = this->_settings->getAftenPath();
			_encoderCommandLine = "-readtoeof 1 -b " + n->getBitrate() + " - \"{0}\"";
		}
		if (dynamic_cast<FlacSettings*>(audioJob->Settings) != 0)
		{
			script->Append("AudioBits(last)>24?ConvertAudioTo24bit(last):last " + "\r\n"); // flac encoder doesn't support 32bits streams
			_mustSendWavHeaderToEncoderStdIn = false;
			FlacSettings *n = dynamic_cast<FlacSettings*>(audioJob->Settings);
			_encoderExecutablePath = this->_settings->getFlacPath();
			_encoderCommandLine = "--force --force-raw-format --endian=little --sign=signed -" + n->getCompressionLevel() + " - -o \"{0}\"";
		}
		if (dynamic_cast<AC3Settings*>(audioJob->Settings) != 0)
		{
			script->Append("6<=Audiochannels(last)?GetChannel(last,1,3,2,5,6,4):last" + "\r\n");
			script->Append("32==Audiobits(last)?ConvertAudioTo16bit(last):last" + "\r\n"); // ffac3 encoder doesn't support 32bits streams
			_mustSendWavHeaderToEncoderStdIn = true;
			AC3Settings *n = dynamic_cast<AC3Settings*>(audioJob->Settings);
			_encoderExecutablePath = this->_settings->getFFMpegPath();
			_encoderCommandLine = "-i - -y -acodec ac3 -ab " + n->getBitrate() + "k \"{0}\"";
		}
		if (dynamic_cast<MP2Settings*>(audioJob->Settings) != 0)
		{
			script->Append("32==Audiobits(last)?ConvertAudioTo16bit(last):last" + "\r\n"); // ffmp2 encoder doesn't support 32 bits streams
			_mustSendWavHeaderToEncoderStdIn = true;
			MP2Settings *n = dynamic_cast<MP2Settings*>(audioJob->Settings);
			_encoderExecutablePath = this->_settings->getFFMpegPath();
			_encoderCommandLine = "-i - -y -acodec mp2 -ab " + n->getBitrate() + "k \"{0}\"";
		}
		if (dynamic_cast<OggVorbisSettings*>(audioJob->Settings) != 0)
		{
			_mustSendWavHeaderToEncoderStdIn = true;
			OggVorbisSettings *n = dynamic_cast<OggVorbisSettings*>(audioJob->Settings);
			_encoderExecutablePath = this->_settings->getOggEnc2Path();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_encoderCommandLine = "--ignorelength --quality " + n->Quality.ToString(System::Globalization::CultureInfo::InvariantCulture) + " -o \"{0}\" -";
		}
		if (dynamic_cast<NeroAACSettings*>(audioJob->Settings) != 0)
		{
			_mustSendWavHeaderToEncoderStdIn = true;
			NeroAACSettings *n = dynamic_cast<NeroAACSettings*>(audioJob->Settings);
			NeroAACSettings *nas = n;
			_encoderExecutablePath = this->_settings->getNeroAacEncPath();
			StringBuilder *sb = new StringBuilder("-ignorelength ");
			switch (n->getProfile())
			{
				case HE:
					sb->Append("-he ");
					break;
				case PS:
					sb->Append("-hev2 ");
					break;
				case LC:
					sb->Append("-lc ");
					break;
			}

			switch (n->getBitrateMode())
			{
				case ABR:
					sb->AppendFormat(System::Globalization::CultureInfo::InvariantCulture, "-br {0} ", n->getBitrate()*1000);
					break;
				case CBR:
					sb->AppendFormat(System::Globalization::CultureInfo::InvariantCulture, "-cbr {0} ", n->getBitrate()*1000);
					break;
				case VBR:
					sb->AppendFormat(System::Globalization::CultureInfo::InvariantCulture, "-q {0} ", n->Quality);
					break;
			}

			sb->Append("-if - -of \"{0}\"");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_encoderCommandLine = sb->ToString();
		}
		if (dynamic_cast<MP3Settings*>(audioJob->Settings) != 0)
		{
			MP3Settings *m = dynamic_cast<MP3Settings*>(audioJob->Settings);
			_mustSendWavHeaderToEncoderStdIn = true;
			_encoderExecutablePath = this->_settings->getLamePath();
			script->Append("32==Audiobits(last)?ConvertAudioTo16bit(last):last" + "\r\n"); // lame encoder doesn't support 32bits streams

			switch (m->getBitrateMode())
			{
				case VBR:
					_encoderCommandLine = "-V" + m->getQuality() + " - \"{0}\"";
					break;
				case CBR:
					_encoderCommandLine = "-b " + m->getBitrate() + " --cbr -h - \"{0}\"";
					break;
				case ABR:
					_encoderCommandLine = "--abr " + m->getAbrBitrate() + " -h - \"{0}\"";
					break;
			}
		}

		if (dynamic_cast<QaacSettings*>(audioJob->Settings) != 0)
		{
			QaacSettings *q = dynamic_cast<QaacSettings*>(audioJob->Settings);
			_encoderExecutablePath = this->_settings->getQaacPath();
			_mustSendWavHeaderToEncoderStdIn = true;
			StringBuilder *sb = new StringBuilder("--ignorelength --threading ");

			if (q->getProfile() == ALAC)
				sb->Append("-A ");
			else
			{
				if (q->getProfile() == HE)
					sb->Append("--he ");

				switch (q->getMode())
				{
					case TVBR:
						sb->Append("-V " + q->getQuality());
						break;
					case CVBR:
						sb->Append("-v " + q->getBitrate());
						break;
					case ABR:
						sb->Append("-a " + q->getBitrate());
						break;
					case CBR:
						sb->Append("-c " + q->getBitrate());
						break;
				}
			}

			if (q->getNoDelay()) // To resolve some A/V sync issues
				sb->Append(" --no-delay");

			sb->Append(" - -o \"{0}\"");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_encoderCommandLine = sb->ToString();
		}

		if (dynamic_cast<OpusSettings*>(audioJob->Settings) != 0)
		{
			OpusSettings *o = dynamic_cast<OpusSettings*>(audioJob->Settings);
			_encoderExecutablePath = this->_settings->getOpusPath();
			_mustSendWavHeaderToEncoderStdIn = true;
			StringBuilder *sb = new StringBuilder("--ignorelength ");

			switch (o->getMode())
			{
				case CVBR:
					sb->Append("--cvbr --bitrate " + o->getBitrate());
					break;
				case HCBR:
					sb->Append("--hard-cbr --bitrate " + o->getBitrate());
					break;
				case VBR:
					sb->Append("--vbr --bitrate " + o->getBitrate());
					break;
			}

			sb->Append(" - \"{0}\"");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_encoderCommandLine = sb->ToString();
		}

		//Just check encoder existance
		_encoderExecutablePath = Path::Combine(AppDomain::CurrentDomain::SetupInformation::ApplicationBase, _encoderExecutablePath);
		if (!File::Exists(_encoderExecutablePath))
		{
			deleteTempFiles();
			throw new EncoderMissingException(_encoderExecutablePath);
		}

		script->AppendLine("\r\n");
		script->AppendLine("return last");
		script->AppendLine("\r\n");

		// copy the appropriate function at the end of the script
		switch (audioJob->Settings->getDownmixMode())
		{
			case KeepOriginal:
				break;
			case ConvertToMono:
				break;
			case DPLDownmix:
			case DPLIIDownmix:
			case StereoDownmix:
				script->AppendLine("" + "\r\n" + "# 5.1 Channels L,R,C,LFE,SL,SR -> stereo + LFE" + "\r\n" + "function c6_stereo(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     lf = GetChannel(a, 4)" + "\r\n" + "     sl = GetChannel(a, 5)" + "\r\n" + "     sr = GetChannel(a, 6)" + "\r\n" + "     fl_sl = MixAudio(fl, sl, 0.2929, 0.2929)" + "\r\n" + "     fr_sr = MixAudio(fr, sr, 0.2929, 0.2929)" + "\r\n" + "     fc_lf = MixAudio(fc, lf, 0.2071, 0.2071)" + "\r\n" + "     l = MixAudio(fl_sl, fc_lf, 1.0, 1.0)" + "\r\n" + "     r = MixAudio(fr_sr, fc_lf, 1.0, 1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 5 Channels L,R,C,SL,SR or L,R,LFE,SL,SR-> Stereo" + "\r\n" + "function c5_stereo(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     sl = GetChannel(a, 4)" + "\r\n" + "     sr = GetChannel(a, 5)" + "\r\n" + "     fl_sl = MixAudio(fl, sl, 0.3694, 0.3694)" + "\r\n" + "     fr_sr = MixAudio(fr, sr, 0.3694, 0.3694)" + "\r\n" + "     l = MixAudio(fl_sl, fc, 1.0, 0.2612)" + "\r\n" + "     r = MixAudio(fr_sr, fc, 1.0, 0.2612)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 5 Channels L,R,C,LFE,S -> Stereo" + "\r\n" + "function c52_stereo(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     lf = GetChannel(a, 4)" + "\r\n" + "     bc = GetChannel(a, 5)" + "\r\n" + "     fl_bc = MixAudio(fl, bc, 0.3205, 0.2265)" + "\r\n" + "     fr_bc = MixAudio(fr, bc, 0.3205, 0.2265)" + "\r\n" + "     fc_lf = MixAudio(fc, lf, 0.2265, 0.2265)" + "\r\n" + "     l = MixAudio(fl_bc, fc_lf, 1.0, 1.0)" + "\r\n" + "     r = MixAudio(fr_bc, fc_lf, 1.0, 1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 4 Channels Quadro L,R,SL,SR -> Stereo" + "\r\n" + "function c4_stereo(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     sl = GetChannel(a, 3)" + "\r\n" + "     sr = GetChannel(a, 4)" + "\r\n" + "     l = MixAudio(fl, sl, 0.5, 0.5)" + "\r\n" + "     r = MixAudio(fr, sr, 0.5, 0.5)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 4 Channels L,R,C,LFE or L,R,S,LFE or L,R,C,S -> Stereo" + "\r\n" + "function c42_stereo(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     lf = GetChannel(a, 4)" + "\r\n" + "     fc_lf = MixAudio(fc, lf, 0.2929, 0.2929)" + "\r\n" + "     l = MixAudio(fl, fc_lf, 0.4142, 1.0)" + "\r\n" + "     r = MixAudio(fr, fc_lf, 0.4142, 1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 3 Channels L,R,C or L,R,S or L,R,LFE -> Stereo" + "\r\n" + "function c3_stereo(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     l = MixAudio(fl, fc, 0.5858, 0.4142)" + "\r\n" + "     r = MixAudio(fr, fc, 0.5858, 0.4142)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 5.1 Channels L,R,C,LFE,SL,SR -> Dolby ProLogic" + "\r\n" + "function c6_dpl(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     sl = GetChannel(a, 5)" + "\r\n" + "     sr = GetChannel(a, 6)" + "\r\n" + "     bc = MixAudio(sl, sr, 0.2265, 0.2265)" + "\r\n" + "     fl_fc = MixAudio(fl, fc, 0.3205, 0.2265)" + "\r\n" + "     fr_fc = MixAudio(fr, fc, 0.3205, 0.2265)" + "\r\n" + "     l = MixAudio(fl_fc, bc, 1.0, 1.0)" + "\r\n" + "     r = MixAudio(fr_fc, bc, 1.0, -1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 5 Channels L,R,C,SL,SR -> Dolby ProLogic" + "\r\n" + "function c5_dpl(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     sl = GetChannel(a, 4)" + "\r\n" + "     sr = GetChannel(a, 5)" + "\r\n" + "     bc = MixAudio(sl, sr, 0.2265, 0.2265)" + "\r\n" + "     fl_fc = MixAudio(fl, fc, 0.3205, 0.2265)" + "\r\n" + "     fr_fc = MixAudio(fr, fc, 0.3205, 0.2265)" + "\r\n" + "     l = MixAudio(fl_fc, bc, 1.0, 1.0)" + "\r\n" + "     r = MixAudio(fr_fc, bc, 1.0, -1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 5 Channels L,R,LFE,SL,SR -> Dolby ProLogic" + "\r\n" + "function c52_dpl(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     sl = GetChannel(a, 4)" + "\r\n" + "     sr = GetChannel(a, 5)" + "\r\n" + "     bc = MixAudio(sl, sr, 0.2929, 0.2929)" + "\r\n" + "     l = MixAudio(fl, bc, 0.4142, 1.0)" + "\r\n" + "     r = MixAudio(fr, bc, 0.4142, -1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 5 Channels L,R,C,LFE,S -> Dolby ProLogic" + "\r\n" + "function c53_dpl(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     bc = GetChannel(a, 5)" + "\r\n" + "     fl_fc = MixAudio(fl, fc, 0.4142, 0.2929)" + "\r\n" + "     fr_fc = MixAudio(fr, fc, 0.4142, 0.2929)" + "\r\n" + "     l = MixAudio(fl_fc, bc, 1.0, 0.2929)" + "\r\n" + "     r = MixAudio(fr_fc, bc, 1.0, -0.2929)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 4 Channels Quadro L,R,SL,SR -> Dolby ProLogic" + "\r\n" + "function c4_dpl(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     sl = GetChannel(a, 3)" + "\r\n" + "     sr = GetChannel(a, 4)" + "\r\n" + "     bc = MixAudio(sl, sr, 0.2929, 0.2929)" + "\r\n" + "     l = MixAudio(fl, bc, 0.4142, 1.0)" + "\r\n" + "     r = MixAudio(fr, bc, 0.4142, -1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 4 Channels L,R,LFE,S  -> Dolby ProLogic" + "\r\n" + "function c42_dpl(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     bc = GetChannel(a, 4)" + "\r\n" + "     l = MixAudio(fl, bc, 0.5858, 0.4142)" + "\r\n" + "     r = MixAudio(fr, bc, 0.5858, -0.4142)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 4 Channels L,R,C,S -> Dolby ProLogic" + "\r\n" + "function c43_dpl(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     bc = GetChannel(a, 4)" + "\r\n" + "     fl_fc = MixAudio(fl, fc, 0.4142, 0.2929)" + "\r\n" + "     fr_fc = MixAudio(fr, fc, 0.4142, 0.2929)" + "\r\n" + "     l = MixAudio(fl_fc, bc, 1.0, 0.2929)" + "\r\n" + "     r = MixAudio(fr_fc, bc, 1.0, -0.2929)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 3 Channels L,R,S  -> Dolby ProLogic" + "\r\n" + "function c3_dpl(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     bc = GetChannel(a, 3)" + "\r\n" + "     l = MixAudio(fl, bc, 0.5858, 0.4142)" + "\r\n" + "     r = MixAudio(fr, bc, 0.5858, -0.4142)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 5.1 Channels L,R,C,LFE,SL,SR -> Dolby ProLogic II" + "\r\n" + "function c6_dpl2(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     sl = GetChannel(a, 5)" + "\r\n" + "     sr = GetChannel(a, 6)" + "\r\n" + "     ssl = MixAudio(sl, sr, 0.2818, 0.1627)" + "\r\n" + "     ssr = MixAudio(sl, sr, -0.1627, -0.2818)" + "\r\n" + "     fl_fc = MixAudio(fl, fc, 0.3254, 0.2301)" + "\r\n" + "     fr_fc = MixAudio(fr, fc, 0.3254, 0.2301)" + "\r\n" + "     l = MixAudio(fl_fc, ssl, 1.0, 1.0)" + "\r\n" + "     r = MixAudio(fr_fc, ssr, 1.0, 1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 5 Channels L,R,C,SL,SR -> Dolby ProLogic II" + "\r\n" + "function c5_dpl2(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     fc = GetChannel(a, 3)" + "\r\n" + "     sl = GetChannel(a, 4)" + "\r\n" + "     sr = GetChannel(a, 5)" + "\r\n" + "     ssl = MixAudio(sl, sr, 0.2818, 0.1627)" + "\r\n" + "     ssr = MixAudio(sl, sr, -0.1627, -0.2818)" + "\r\n" + "     fl_fc = MixAudio(fl, fc, 0.3254, 0.2301)" + "\r\n" + "     fr_fc = MixAudio(fr, fc, 0.3254, 0.2301)" + "\r\n" + "     l = MixAudio(fl_fc, ssl, 1.0, 1.0)" + "\r\n" + "     r = MixAudio(fr_fc, ssr, 1.0, 1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 5 Channels L,R,LFE,SL,SR -> Dolby ProLogic II" + "\r\n" + "function c52_dpl2(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     sl = GetChannel(a, 4)" + "\r\n" + "     sr = GetChannel(a, 5)" + "\r\n" + "     ssl = MixAudio(sl, sr, 0.3714, 0.2144)" + "\r\n" + "     ssr = MixAudio(sl, sr, -0.2144, -0.3714)" + "\r\n" + "     l = MixAudio(fl, ssl, 0.4142, 1.0)" + "\r\n" + "     r = MixAudio(fr, ssr, 0.4142, 1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }" + "\r\n" + "# 4 Channels Quadro L,R,SL,SR -> Dolby ProLogic II" + "\r\n" + "function c4_dpl2(clip a)" + "\r\n" + "  {" + "\r\n" + "     fl = GetChannel(a, 1)" + "\r\n" + "     fr = GetChannel(a, 2)" + "\r\n" + "     sl = GetChannel(a, 3)" + "\r\n" + "     sr = GetChannel(a, 4)" + "\r\n" + "     ssl = MixAudio(sl, sr, 0.3714, 0.2144)" + "\r\n" + "     ssr = MixAudio(sl, sr, -0.2144, -0.3714)" + "\r\n" + "     l = MixAudio(fl, ssl, 0.4142, 1.0)" + "\r\n" + "     r = MixAudio(fr, ssr, 0.4142, 1.0)" + "\r\n" + "     return MergeChannels(l, r)" + "\r\n" + "  }");
				break;
			case Upmix:
				script->AppendLine("" + "\r\n" + "function x_upmix" + id + "(clip a) " + "\r\n" + " {" + "\r\n" + "    m = ConvertToMono(a)" + "\r\n" + "    a1 = GetLeftChannel(a)" + "\r\n" + "    a2 = GetRightChannel(a)" + "\r\n" + "    fl = SuperEQ(a1,\"" + tmp + "front.feq\")" + "\r\n" + "    fr = SuperEQ(a2,\"" + tmp + "front.feq\")" + "\r\n" + "    c = SuperEQ(m,\"" + tmp + "center.feq\") " + "\r\n" + "    lfe = SuperEQ(m,\"" + tmp + "lfe.feq\") " + "\r\n" + "    sl = SuperEQ(a1,\"" + tmp + "back.feq\")" + "\r\n" + "    sr = SuperEQ(a2,\"" + tmp + "back.feq\")" + "\r\n" + "    return MergeChannels(fl,fr,c,lfe,sl,sr)" + "\r\n" + " }");
				break;
			case UpmixUsingSoxEq:
				script->AppendLine("" + "\r\n" + "function x_upmixR" + id + "(clip Stereo) " + "\r\n" + " {" + "\r\n" + "    Front = mixaudio(Stereo.soxfilter(\"filter 0-600\"),mixaudio(Stereo.soxfilter(\"filter 600-1200\"),Stereo.soxfilter(\"filter 1200-7000\"),0.45,0.25),0.50,1)" + "\r\n" + "    Back = mixaudio(Stereo.soxfilter(\"filter 0-600\"),mixaudio(Stereo.soxfilter(\"filter 600-1200\"),Stereo.soxfilter(\"filter 1200-7000\"),0.35,0.15),0.40,1)" + "\r\n" + "    fl = GetLeftChannel(Front)" + "\r\n" + "    fr = GetRightChannel(Front)" + "\r\n" + "    cc = ConvertToMono(stereo).SoxFilter(\"filter 625-24000\")" + "\r\n" + "    lfe = ConvertToMono(stereo).SoxFilter(\"lowpass 100\",\"vol -0.5\")" + "\r\n" + "    sl = GetLeftChannel(Back)" + "\r\n" + "    sr = GetRightChannel(Back)" + "\r\n" + "    sl = DelayAudio(sl,0.02)" + "\r\n" + "    sr = DelayAudio(sr,0.02)" + "\r\n" + "    return MergeChannels(fl,fr,cc,lfe,sl,sr)" + "\r\n" + " }");
				break;
			case UpmixWithCenterChannelDialog:
				script->AppendLine("" + "\r\n" + "function x_upmixC" + id + "(clip stereo) " + "\r\n" + " {" + "\r\n" + "    left = stereo.GetLeftChannel()" + "\r\n" + "    right = stereo.GetRightChannel()" + "\r\n" + "    fl = mixaudio(left.soxfilter(\"filter 0-24000\"),right.soxfilter(\"filter 0-24000\"),0.6,-0.5)" + "\r\n" + "    fr = mixaudio(right.soxfilter(\"filter 0-24000\"),left.soxfilter(\"filter 0-24000\"),0.6,-0.5)" + "\r\n" + "    cc = ConvertToMono(stereo).SoxFilter(\"filter 625-24000\")" + "\r\n" + "    lfe = ConvertToMono(stereo).SoxFilter(\"lowpass 100\",\"vol -0.5\")" + "\r\n" + "    sl = mixaudio(left.soxfilter(\"filter 0-24000\"),right.soxfilter(\"filter 0-24000\"),0.5,-0.4)" + "\r\n" + "    sr = mixaudio(right.soxfilter(\"filter 0-24000\"),left.soxfilter(\"filter 0-24000\"),0.5,-0.4)" + "\r\n" + "    sl = DelayAudio(sl,0.02)" + "\r\n" + "    sr = DelayAudio(sr,0.02)" + "\r\n" + "     return MergeChannels(fl,fr,cc,lfe,sl,sr)                                                                                                                                              " + "\r\n" + " }");
				break;
		}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		_avisynthAudioScript = script->ToString();

		_log->LogValue("Avisynth script", _avisynthAudioScript);
		_log->LogValue("Commandline used", _encoderCommandLine);
	}

	void AviSynthAudioEncoder::start()
	{
		try
		{
			this->Start();
		}
		catch (std::exception &e)
		{
			throw new JobRunException(e);
		}
	}

	void AviSynthAudioEncoder::stop()
	{
		try
		{
			this->Abort();
		}
		catch (std::exception &e)
		{
			throw new JobRunException(e);
		}
	}

	void AviSynthAudioEncoder::pause()
	{
		if (!_mre->Reset())
			throw new JobRunException("Could not reset mutex. pause failed");
	}

	void AviSynthAudioEncoder::resume()
	{
		if (!_mre->Set())
			throw new JobRunException("Could not set mutex. pause failed");
	}

	void AviSynthAudioEncoder::changePriority(ProcessPriority priority)
	{
		if (this->_encoderThread != 0 && _encoderThread->IsAlive)
		{
			try
			{
				switch (priority)
				{
					case IDLE:
						_encoderThread->Priority = ThreadPriority::Lowest;
						_encoderProcess->PriorityClass = ProcessPriorityClass::Idle;
						break;
					case BELOW_NORMAL:
						_encoderThread->Priority = ThreadPriority::BelowNormal;
						_encoderProcess->PriorityClass = ProcessPriorityClass::BelowNormal;
						break;
					case NORMAL:
						_encoderThread->Priority = ThreadPriority::Normal;
						_encoderProcess->PriorityClass = ProcessPriorityClass::Normal;
						break;
					case ABOVE_NORMAL:
						_encoderThread->Priority = ThreadPriority::AboveNormal;
						_encoderProcess->PriorityClass = ProcessPriorityClass::AboveNormal;
						break;
					case HIGH:
						_encoderThread->Priority = ThreadPriority::Highest;
						_encoderProcess->PriorityClass = ProcessPriorityClass::High;
						break;
				}
				VistaStuff::SetProcessPriority(_encoderProcess->Handle, _encoderProcess->PriorityClass);
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
			if (_encoderThread == 0)
				throw new JobRunException("Thread has not been started yet");
			else
				throw new JobRunException("Thread has exited");
		}
	}

	void AviSynthAudioEncoder::InitializeInstanceFields()
	{
		_mre = new System::Threading::ManualResetEvent(true);
		delete _encoderThread;
		stdoutDone = new ManualResetEvent(false);
		stderrDone = new ManualResetEvent(false);
		delete _readFromStdOutThread;
		delete _readFromStdErrThread;
		delete _settings;
		_tempFiles = QVector<QString>();
	}
}
