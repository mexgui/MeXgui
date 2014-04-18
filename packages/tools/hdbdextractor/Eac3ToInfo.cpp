#include "Eac3ToInfo.h"




//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;

//using namespace System::Text;

//using namespace System::Text::RegularExpressions;
using namespace MeXgui::core::util;
using namespace eac3to;
namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace hdbdextractor
			{

				const QString &eac3toArgs::geteac3toPath() const
				{
					return privateeac3toPath;
				}

				void eac3toArgs::seteac3toPath(const QString &value)
				{
					privateeac3toPath = value;
				}

				const QString &eac3toArgs::getworkingFolder() const
				{
					return privateworkingFolder;
				}

				void eac3toArgs::setworkingFolder(const QString &value)
				{
					privateworkingFolder = value;
				}

				const QString &eac3toArgs::getfeatureNumber() const
				{
					return privatefeatureNumber;
				}

				void eac3toArgs::setfeatureNumber(const QString &value)
				{
					privatefeatureNumber = value;
				}

				const QString &eac3toArgs::getargs() const
				{
					return privateargs;
				}

				void eac3toArgs::setargs(const QString &value)
				{
					privateargs = value;
				}

				const MeXgui::packages::tools::hdbdextractor::ResultState &eac3toArgs::getresultState() const
				{
					return privateresultState;
				}

				void eac3toArgs::setresultState(const ResultState &value)
				{
					privateresultState = value;
				}

				Eac3toInfo::Eac3toInfo(QVector<QString> &input, MediaInfoFile *iFile, LogItem *oLog)
				{
					// create log instance
					if (oLog == 0)
					{
						_log = MainForm::Instance->getEac3toLog();
						if (_log == 0)
						{
							_log = MainForm::Instance->getLog()->Info("HD Streams Extractor");
							MainForm::Instance->setEac3toLog(_log);
						}
					}
					else
						_log = oLog->Add(new LogItem("eac3toInfo"));

					for (QVector<QString>::const_iterator strPath = input.begin(); strPath != input.end(); ++strPath)
						_log->LogEvent("Input: " + *strPath);
					if (System::IO::Directory::Exists(input[0]))
						oMode = FolderBased;
					else
						oMode = FileBased;
					this->input = input;
					this->iFile = iFile;
				}

				bool Eac3toInfo::IsBusy()
				{
					return backgroundWorker->IsBusy;
				}

				const QVector<Feature*> &Eac3toInfo::getFeatures() const
				{
					return features;
				}

				void Eac3toInfo::initBackgroundWorker()
				{
					backgroundWorker = new BackgroundWorker();
					backgroundWorker->WorkerSupportsCancellation = true;
					backgroundWorker->WorkerReportsProgress = true;
					backgroundWorker->DoWork += new DoWorkEventHandler(this, &Eac3toInfo::backgroundWorker_DoWork);
					backgroundWorker->ProgressChanged += new ProgressChangedEventHandler(this, &Eac3toInfo::backgroundWorker_ProgressChanged);
					backgroundWorker->RunWorkerCompleted += new RunWorkerCompletedEventHandler(this, &Eac3toInfo::backgroundWorker_RunWorkerCompleted);
				}

				void Eac3toInfo::FetchAllInformation()
				{
					iFeatureToFetch = 0;
					bFetchAll = true;
					FetchFeatureInformation();
					while (bFetchAll)
					{
						System::Windows::Forms::Application::DoEvents();
						delay(100);
					}

				}

				void Eac3toInfo::FetchFeatureInformation()
				{
					initBackgroundWorker();
					args = eac3toArgs();
					args.seteac3toPath(MainForm::Instance->getSettings()->getEAC3toPath());
					args.setresultState(FeatureCompleted);
					args.setargs("");
					args.setworkingFolder(System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getEAC3toPath()));
					features = QVector<Feature*>();
					backgroundWorker->ReportProgress(0, "Retrieving features...");
					backgroundWorker->RunWorkerAsync(args);
				}

				void Eac3toInfo::FetchStreamInformation(int iFeatureNumber)
				{
					initBackgroundWorker();
					args = eac3toArgs();
					args.seteac3toPath(MainForm::Instance->getSettings()->getEAC3toPath());
					args.setresultState(StreamCompleted);
					args.setargs(StringConverterHelper::toString(iFeatureNumber));
					args.setfeatureNumber(StringConverterHelper::toString(iFeatureNumber));
					args.setworkingFolder(System::IO::Path::GetDirectoryName(MainForm::Instance->getSettings()->getEAC3toPath()));
					backgroundWorker->ReportProgress(0, "Retrieving streams...");
					backgroundWorker->RunWorkerAsync(args);
				}

				void Eac3toInfo::backgroundWorker_DoWork(object *sender, DoWorkEventArgs *e)
				{
					eac3toArgs args = static_cast<eac3toArgs>(e->Argument);

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (Process compiler = new Process())
					Process *compiler = new Process();
					try
					{
						QString strSource = QString::Format("\"{0}\"", input[0]);
						for (int i = 1; i < input.size(); i++)
							strSource += QString::Format("+\"{0}\"", input[i]);

						compiler->StartInfo->FileName = args.geteac3toPath();
						switch (args.getresultState())
						{
							case FeatureCompleted:
								compiler->StartInfo->Arguments = QString::Format("{0}", strSource);
								break;
							case StreamCompleted:
								if (args.getargs() == "")
									compiler->StartInfo->Arguments = QString::Format("{0}", strSource);
								else
									compiler->StartInfo->Arguments = QString::Format("{0} {1}) {2}", strSource, args.getargs(), "-progressnumbers");
								break;
							case ExtractCompleted:
								if (oMode == FileBased)
									compiler->StartInfo->Arguments = QString::Format("{0} {1}", strSource, args.getargs() + " -progressnumbers");
								else
									compiler->StartInfo->Arguments = QString::Format("{0} {1}) {2}", strSource, args.getfeatureNumber(), args.getargs() + "-progressnumbers");
								break;
						}

						if (_log != 0)
							_log->LogEvent(QString::Format("Arguments: {0}", compiler->StartInfo->Arguments));

						compiler->StartInfo->WorkingDirectory = args.getworkingFolder();
						compiler->StartInfo->CreateNoWindow = true;
						compiler->StartInfo->UseShellExecute = false;
						compiler->StartInfo->RedirectStandardOutput = true;
						compiler->StartInfo->RedirectStandardError = true;
						compiler->StartInfo->ErrorDialog = false;
						compiler->EnableRaisingEvents = true;

						compiler->EnableRaisingEvents = true;
						compiler->Exited += new EventHandler(this, &Eac3toInfo::backgroundWorker_Exited);
						compiler->ErrorDataReceived += new DataReceivedEventHandler(this, &Eac3toInfo::backgroundWorker_ErrorDataReceived);
						compiler->OutputDataReceived += new DataReceivedEventHandler(this, &Eac3toInfo::backgroundWorker_OutputDataReceived);

						try
						{
							compiler->Start();
							compiler->BeginErrorReadLine();
							compiler->BeginOutputReadLine();

							while (!compiler->HasExited)
								if (backgroundWorker->CancellationPending)
									compiler->Kill();
							while (!compiler->HasExited) // wait until the process has terminated without locking the GUI
							{
								System::Windows::Forms::Application::DoEvents();
								delay(100);
							}
							compiler->WaitForExit();
						}
						catch (std::exception &ex)
						{
							if (_log != 0)
								_log->LogValue("Error running job", ex);
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
						finally
						{
							compiler->ErrorDataReceived -= new DataReceivedEventHandler(this, &Eac3toInfo::backgroundWorker_ErrorDataReceived);
							compiler->OutputDataReceived -= new DataReceivedEventHandler(this, &Eac3toInfo::backgroundWorker_OutputDataReceived);
						}
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (compiler != 0)
							compiler.Dispose();
					}

					e->Result = args.getresultState();
				}

				void Eac3toInfo::backgroundWorker_ProgressChanged(object *sender, ProgressChangedEventArgs *e)
				{
					if (this->ProgressChanged != 0)
						this->ProgressChanged->Invoke(this, e);
				}

				void Eac3toInfo::backgroundWorker_RunWorkerCompleted(object *sender, RunWorkerCompletedEventArgs *e)
				{
					if (e->Cancelled && _log != 0)
							_log->Error("Work was cancelled");

					if (e->Error != 0 && _log != 0)
							_log->LogValue("Error running job", e);

					if (e->Result != 0)
					{
						if (_log != 0)
							_log->LogEvent(Extensions::GetStringValue((static_cast<ResultState>(e->Result))));

						if (bFetchAll)
						{
							if (features.size() > 0 && iFeatureToFetch < features.size())
							{
								FetchStreamInformation(++iFeatureToFetch);
								return;
							}
							else
								bFetchAll = false;
						}
					}

					if (this->FetchInformationCompleted != 0)
						this->FetchInformationCompleted->Invoke(this, e);
				}

				void Eac3toInfo::backgroundWorker_Exited()
				{
					//ResetCursor(Cursors.Default);
				}

				void Eac3toInfo::backgroundWorker_ErrorDataReceived(object *sender, DataReceivedEventArgs *e)
				{
					QString data;

					if (!e->Data->empty())
					{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimStart' method:
						data = e->Data->TrimStart('\b')->Trim();

						if (!data.empty() && _log != 0)
							_log->Error("Error: " + e->Data);
					}
				}

				void Eac3toInfo::backgroundWorker_OutputDataReceived(object *sender, DataReceivedEventArgs *e)
				{
					QString data;

					if (!e->Data->empty())
					{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimStart' method:
						data = e->Data->TrimStart('\b')->Trim();

						if (!data.empty())
						{
							// Feature line
							// 2) 00216.mpls, 0:50:19
							if (Regex::IsMatch(data, "^[0-99]+\\).+$", RegexOptions::Compiled))
							{
								try
								{
									features.push_back(eac3to::Feature::Parse(data));
								}
								catch (std::exception &ex)
								{
									if (_log != 0)
										_log->LogValue("Error receiving output data", ex);
								}

								return;
							}

							// Feature name
							// "Feature Name"
							else if (Regex::IsMatch(data, "^\".+\"$", RegexOptions::Compiled))
							{
								// streams[streams.Count - 1].Name = Extensions.CapitalizeAll(data.Trim("\" .".ToCharArray())); //original
								if (oMode == FileBased)
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
									features[0]->getStreams()[features[0]->getStreams()->size() - 1]->setName(Extensions::CapitalizeAll(data.Trim((QString("\" ."))->ToCharArray())));
								else
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
									features[features.size() - 1]->setName(Extensions::CapitalizeAll(data.Trim((QString("\" ."))->ToCharArray())));
								return;
							}

							// Stream line on feature listing
							// - h264/AVC, 1080p24 /1.001 (16:9)
							else if (Regex::IsMatch(data, "^-.+$", RegexOptions::Compiled))
								return;

							// Playlist file listing
							// [99+100+101+102+103+104+105+106+114].m2ts (blueray playlist *.mpls)
							else if (Regex::IsMatch(data, "^\\[.+\\].m2ts$", RegexOptions::Compiled))
							{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
								for (unknown::const_iterator file = Regex::Match(data, "\\[.+\\]")->Value->Trim((QString("[]"))->ToCharArray())->Split((QString("+"))->ToCharArray()).begin(); file != Regex::Match(data, "\\[.+\\]")->Value->Trim((QString("[]"))->ToCharArray())->Split((QString("+"))->ToCharArray()).end(); ++file)
									features[features.size() - 1]->getFiles()->push_back(new File(*file + ".m2ts", features[features.size() - 1]->getFiles()->size() + 1));

								return;
							}

							// Stream listing feature header
							// M2TS, 1 video track, 6 audio tracks, 9 subtitle tracks, 1:53:06
							// EVO, 2 video tracks, 4 audio tracks, 8 subtitle tracks, 2:20:02
							else if (Regex::IsMatch(data, "^M2TS, .+$", RegexOptions::Compiled) || Regex::IsMatch(data, "^EVO, .+$", RegexOptions::Compiled) || Regex::IsMatch(data, "^TS, .+$", RegexOptions::Compiled) || Regex::IsMatch(data, "^VOB, .+$", RegexOptions::Compiled) || Regex::IsMatch(data, "^MKV, .+$", RegexOptions::Compiled) || Regex::IsMatch(data, "^MKA, .+$", RegexOptions::Compiled))
							{
								if (_log != 0)
									_log->LogEvent(data);
								return;
							}

							// Stream line
							// 8: AC3, English, 2.0 channels, 192kbps, 48khz, dialnorm: -27dB
							else if (Regex::IsMatch(data, "^[0-99]+:.+$", RegexOptions::Compiled))
							{
								if (oMode == FileBased)
								{
									try
									{
										if (features.empty())
										{
											Feature *dummyFeature = new Feature();
											for (int i = 0; i < input.size(); i++)
											{
												if (System::IO::File::Exists(input[i]) && iFile == 0)
													iFile = new MediaInfoFile(input[i]);
												if (iFile != 0)
												{
													dummyFeature->setDuration(dummyFeature->getDuration() + TimeSpan::FromSeconds(ceil(iFile->getVideoInfo()->FrameCount / iFile->getVideoInfo()->FPS)));
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
													delete iFile;
												}
												dummyFeature->getFiles().push_back(new File(System::IO::Path::GetFileName(input[i]), i + 1));
											}
											dummyFeature->setName(System::IO::Path::GetFileName(input[0]));
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
											dummyFeature->setDescription(dummyFeature->getName() + ", " + dummyFeature->getDuration()->ToString());
											features.push_back(dummyFeature);
										}
										features[0]->getStreams()->push_back(eac3to::Stream::Parse(data));
									}
									catch (std::exception &ex)
									{
										if (_log != 0)
											_log->LogValue("Error receiving output data", ex);
									}
								}
								else
								{
									try
									{
										features[int::Parse(args.getfeatureNumber()) - 1]->getStreams()->push_back(Stream::Parse(data));
									}
									catch (std::exception &ex)
									{
										if (_log != 0)
											_log->LogValue("Error receiving output data", ex);
									}
								}
								return;
							}

							// Analyzing
							// analyze: 100%
							else if (Regex::IsMatch(data, "^analyze: [0-9]{1,3}%$", RegexOptions::Compiled))
							{
								if (backgroundWorker->IsBusy)
									backgroundWorker->ReportProgress(int::Parse(Regex::Match(data, "[0-9]{1,3}")->Value), QString::Format("Analyzing ({0}%)", int::Parse(Regex::Match(data, "[0-9]{1,3}")->Value)));

								return;
							}

							// Information line
							// [a03] Creating file "audio.ac3"...
							else if (Regex::IsMatch(data, "^\\[.+\\] .+\\.{3}$", RegexOptions::Compiled))
							{
								if (_log != 0)
									_log->LogEvent(data);
								return;
							}

							else if (Regex::IsMatch(data, "^\\v .*...", RegexOptions::Compiled))
							{
								if (_log != 0)
									_log->LogEvent(data);
								return;
							}

							else if (Regex::IsMatch(data, "(core: .*)", RegexOptions::Compiled))
							{
								if (_log != 0)
									_log->LogEvent(data);
								return;
							}

							else if (Regex::IsMatch(data, "(embedded: .*)", RegexOptions::Compiled))
							{
								if (_log != 0)
									_log->LogEvent(data);
								return;
							}

							// Creating file
							// Creating file "C:\1_1_chapter.txt"...
							else if (Regex::IsMatch(data, "^Creating file \".+\"\\.{3}$", RegexOptions::Compiled))
							{
								if (_log != 0)
									_log->LogEvent(data);
								return;
							}

							// Processing
							// process: 100%
							else if (Regex::IsMatch(data, "^process: [0-9]{1,3}%$", RegexOptions::Compiled))
							{
								if (backgroundWorker->IsBusy)
									backgroundWorker->ReportProgress(int::Parse(Regex::Match(data, "[0-9]{1,3}")->Value), QString::Format("Processing ({0}%)", int::Parse(Regex::Match(data, "[0-9]{1,3}")->Value)));

								return;
							}

							// Progress
							// progress: 100%
							else if (Regex::IsMatch(data, "^progress: [0-9]{1,3}%$", RegexOptions::Compiled))
							{
								if (backgroundWorker->IsBusy)
									backgroundWorker->ReportProgress(int::Parse(Regex::Match(data, "[0-9]{1,3}")->Value), QString::Format("Progress ({0}%)", int::Parse(Regex::Match(data, "[0-9]{1,3}")->Value)));

								return;
							}

							// Done
							// Done.
							else if (data.Equals("Done."))
							{
								if (_log != 0)
									_log->LogEvent(data);
								return;
							}

							// unusual video framerate
							// v02 The video framerate is correct, but rather unusual.
							else if (data.find("The video framerate is correct, but rather unusual") != string::npos)
							{
								if (_log != 0)
									_log->LogEvent(data);
								return;
							}

							// Source file not found
							// Source file "x:\" not found.
							else if (Regex::IsMatch(data, "^Source file \".*\" not found.$", RegexOptions::Compiled))
							{
								if (_log != 0)
									_log->Error(data);
								return;
							}

							// Format of Source file not detected
							// The format of the source file could not be detected.
							else if (data.Equals("The format of the source file could not be detected."))
							{
								if (_log != 0)
									_log->Error(data);
								return;
							}

							// Audio conversion not supported
							// This audio conversion is not supported.
							else if (data.Equals("This audio conversion is not supported."))
							{
								if (_log != 0)
									_log->Error(data);
								return;
							}

							// Unknown line
							else
							{
								if (_log != 0)
									_log->Warn(QString::Format("Unknown line: \"{0}\"", data));
							}
						}
					}
				}
			}
		}
	}
}
