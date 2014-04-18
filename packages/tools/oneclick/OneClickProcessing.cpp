#include "OneClickProcessing.h"




//using namespace System::Collections::Generic;




using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace oneclick
			{

				OneClickProcessing::OneClickProcessing(OneClickWindow *oWindow, const QString &strFileOrFolderName, OneClickSettings *oSettings, LogItem *oLog)
				{
					this->oOneClickWindow = oWindow;
					this->strInput = strFileOrFolderName;
					this->_log = oLog;
					this->_oSettings = oSettings;

					if (!getInputDVDBased(oSettings))
						if (!getInputBluRayBased(oSettings))
							if (!getInputFolderBased(oSettings))
								if (!getInputFileBased(oSettings))
									this->oOneClickWindow->setOpenFailure();
				}

				OneClickProcessing::OneClickProcessing(OneClickWindow *oWindow, QVector<OneClickFilesToProcess*> &arrFilesToProcess, OneClickSettings *oSettings, LogItem *oLog)
				{
					this->oOneClickWindow = oWindow;
					this->_log = oLog;

					QVector<OneClickFilesToProcess*> arrFilesToProcessNew = QVector<OneClickFilesToProcess*>();
					MediaInfoFile *iFile = 0;

					for (QVector<OneClickFilesToProcess*>::const_iterator oFileToProcess = arrFilesToProcess.begin(); oFileToProcess != arrFilesToProcess.end(); ++oFileToProcess)
					{
						if (iFile == 0)
						{
							MediaInfoFile *iFileTemp = new MediaInfoFile((*oFileToProcess)->FilePath, _log, (*oFileToProcess)->TrackNumber);
							if (iFileTemp->recommendIndexer(oSettings->getIndexerPriority()))
								iFile = iFileTemp;
							else if (iFileTemp->getContainerFileTypeString().Equals("AVS"))
							{
								iFile = iFileTemp;
								iFile->setIndexerToUse(FileIndexerWindow::NONE);
							}
							else
								_log->LogEvent((*oFileToProcess)->FilePath + " cannot be processed as no indexer can be used. skipping...");
						}
						else
							arrFilesToProcessNew.push_back(*oFileToProcess);
					}
					if (iFile != 0)
						oOneClickWindow->setInputData(iFile, arrFilesToProcessNew);
					else
						oOneClickWindow->setInputData(0, QVector<OneClickFilesToProcess*>()); // not demuxable
				}

				bool OneClickProcessing::getInputDVDBased(OneClickSettings *oSettings)
				{
					QString videoIFO;
					QString path;

					if (File::Exists(this->strInput) && Path::GetExtension(this->strInput)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".ifo"))
					{
						path = Path::GetDirectoryName(this->strInput);
						videoIFO = this->strInput;
					}
					else if (File::Exists(this->strInput) && Path::GetExtension(this->strInput)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".vob"))
					{
						path = Path::GetDirectoryName(this->strInput);
						if (Path::GetFileName(this->strInput)->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->substr(0, 4) == "VTS_")
							videoIFO = this->strInput.substr(0, this->strInput.rfind("_")) + "_0.IFO";
						else
							videoIFO = Path::ChangeExtension(this->strInput, ".IFO");
						if (!File::Exists(videoIFO))
							return false;
						else
							this->strInput = videoIFO;
					}
					else if (Directory::Exists(this->strInput) && Directory::GetFiles(this->strInput, "*.ifo")->Length > 0)
					{
						path = this->strInput;
						videoIFO = Path::Combine(path, "VIDEO_TS.IFO");
					}
					else if (Directory::Exists(Path::Combine(this->strInput, "VIDEO_TS")) && Directory::GetFiles(Path::Combine(this->strInput, "VIDEO_TS"), "*.IFO")->Length > 0)
					{
						path = Path::Combine(this->strInput, "VIDEO_TS");
						videoIFO = Path::Combine(path, "VIDEO_TS.IFO");
					}
					else
						return false;

					ChapterExtractor *ex = new DvdExtractor();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (frmStreamSelect frm = new frmStreamSelect(ex, SelectionMode.MultiExtended))
					frmStreamSelect *frm = new frmStreamSelect(ex, SelectionMode::MultiExtended);
					try
					{
						frm->Text = "Select your Titles";
						ex->GetStreams(this->strInput);
						if (frm->getChapterCount() == 1 || (frm->getChapterCount() > 1 && frm->show() == DialogResult::OK))
						{
							QVector<ChapterInfo*> oChapterList = frm->getSelectedMultipleChapterInfo();
							if (oChapterList.size() > 0)
							{
								QVector<OneClickFilesToProcess*> arrFilesToProcess = QVector<OneClickFilesToProcess*>();
								MediaInfoFile *iFile = 0;
								int iTitleNumber = 1;

								for (QVector<ChapterInfo*>::const_iterator oChapterInfo = oChapterList.begin(); oChapterInfo != oChapterList.end(); ++oChapterInfo)
								{
									QString strVOBFile = Path::Combine(path, (*oChapterInfo)->getTitle() + "_1.VOB");

									if (iFile == 0 && File::Exists(strVOBFile))
									{
										MediaInfoFile *iFileTemp = new MediaInfoFile(strVOBFile, _log, (*oChapterInfo)->getTitleNumber());
										if (iFileTemp->recommendIndexer(oSettings->getIndexerPriority()))
										{
											iFile = iFileTemp;
											iTitleNumber = (*oChapterInfo)->getTitleNumber();
										}
										else
											_log->LogEvent(strVOBFile + " cannot be processed as no indexer can be used. skipping...");
									}
									else
										arrFilesToProcess.push_back(new OneClickFilesToProcess(strVOBFile, (*oChapterInfo)->getTitleNumber()));
								}
								if (iFile != 0)
								{
									oOneClickWindow->setInputData(iFile, arrFilesToProcess);
									return true;
								}
								else
									return false;
							}
						}
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (frm != 0)
							frm.Dispose();
					}

					return false;
				}

				bool OneClickProcessing::getInputBluRayBased(OneClickSettings *oSettings)
				{
					QString path = this->strInput;
					while (!Path::GetFullPath(path)->Equals(Path::GetPathRoot(path)))
					{
						QString bdmvPath = Path::Combine(path, "BDMV\\PLAYLIST");
						if (Directory::Exists(bdmvPath))
							break;

						DirectoryInfo *pathInfo = new DirectoryInfo(path);
						path = pathInfo->Parent->FullName;
					}

					if (!Directory::Exists(Path::Combine(path, "BDMV\\PLAYLIST")))
						return false;

					ChapterExtractor *ex = new BlurayExtractor();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (frmStreamSelect frm = new frmStreamSelect(ex, SelectionMode.MultiExtended))
					frmStreamSelect *frm = new frmStreamSelect(ex, SelectionMode::MultiExtended);
					try
					{
						frm->Text = "Select your Titles";
						ex->GetStreams(path);
						if (frm->getChapterCount() == 1 || (frm->getChapterCount() > 1 && frm->show() == DialogResult::OK))
						{
							QVector<ChapterInfo*> oChapterList = frm->getSelectedMultipleChapterInfo();
							if (oChapterList.size() > 0)
							{
								QVector<OneClickFilesToProcess*> arrFilesToProcess = QVector<OneClickFilesToProcess*>();
								MediaInfoFile *iFile = 0;

								for (QVector<ChapterInfo*>::const_iterator oChapterInfo = oChapterList.begin(); oChapterInfo != oChapterList.end(); ++oChapterInfo)
								{
									QString strFile = path + "\\BDMV\\PLAYLIST\\" + (*oChapterInfo)->getSourceName();

									if (iFile == 0 && File::Exists(strFile))
									{
										iFile = new MediaInfoFile(strFile, _log);
										iFile->recommendIndexer(oSettings->getIndexerPriority());
									}
									else
										arrFilesToProcess.push_back(new OneClickFilesToProcess(strFile, 1));
								}
								if (iFile != 0)
								{
									oOneClickWindow->setInputData(iFile, arrFilesToProcess);
									return true;
								}
								else
									return false;
							}
						}
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (frm != 0)
							frm.Dispose();
					}

					return false;
				}

				bool OneClickProcessing::getInputFolderBased(OneClickSettings *oSettings)
				{
					QVector<OneClickFilesToProcess*> arrFilesToProcess = QVector<OneClickFilesToProcess*>();
					MediaInfoFile *iFile = 0;

					if (!Directory::Exists(this->strInput))
						return false;

					for (unknown::const_iterator strFileName = Directory::GetFiles(this->strInput).begin(); strFileName != Directory::GetFiles(this->strInput).end(); ++strFileName)
					{
						if (iFile == 0)
						{
							MediaInfoFile *iFileTemp = new MediaInfoFile(*strFileName, _log);
							if (iFileTemp->recommendIndexer(oSettings->getIndexerPriority()))
								iFile = iFileTemp;
							else if (iFileTemp->getContainerFileTypeString().Equals("AVS"))
							{
								iFile = iFileTemp;
								iFile->setIndexerToUse(FileIndexerWindow::NONE);
							}
							else
								_log->LogEvent(*strFileName + " cannot be processed as no indexer can be used. skipping...");
						}
						else
							arrFilesToProcess.push_back(new OneClickFilesToProcess(*strFileName, 1));
					}
					if (iFile != 0)
					{
						oOneClickWindow->setInputData(iFile, arrFilesToProcess);
						return true;
					}
					else
						return false;
				}

				bool OneClickProcessing::getInputFileBased(OneClickSettings *oSettings)
				{
					if (File::Exists(this->strInput))
					{
						MediaInfoFile *iFile = new MediaInfoFile(this->strInput, this->_log);
						if (iFile->recommendIndexer(oSettings->getIndexerPriority()))
							return getInputIndexerBased(iFile, oSettings);
						else if (iFile->getContainerFileTypeString().Equals("AVS"))
						{
							iFile->setIndexerToUse(FileIndexerWindow::NONE);
							return getInputIndexerBased(iFile, oSettings);
						}
					}

					return false;
				}

				bool OneClickProcessing::getInputIndexerBased(MediaInfoFile *iFile, OneClickSettings *oSettings)
				{
					oOneClickWindow->setInputData(iFile, QVector<OneClickFilesToProcess*>());
					return true;
				}
			}
		}
	}
}
