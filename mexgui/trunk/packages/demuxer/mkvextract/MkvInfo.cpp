#include "MkvInfo.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
using namespace MeGUI::core::util;

namespace MeGUI
{

	MkvInfo::MkvInfo(const std::string &strFile, LogItem *&oLog)
	{
		InitializeInstanceFields();
		if (oLog == 0)
			this->_oLog = MainForm::Instance->getLog()->Info("MkvInfo");
		else
			this->_oLog = oLog;
		this->_strFile = strFile;
		_bMuxable = true;
		getInfo();
	}

	const bool &MkvInfo::getHasChapters() const
	{
		return _bHasChapters;
	}

	const bool &MkvInfo::getIsMuxable() const
	{
		return _bMuxable;
	}

	void MkvInfo::getInfo()
	{
		_strResult = "";
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Process mkvinfo = new Process())
		Process *mkvinfo = new Process();
		try
		{
			mkvinfo->StartInfo->FileName = MainForm::Instance->getSettings()->getMkvmergePath();
			mkvinfo->StartInfo->Arguments = std::string::Format("--ui-language en --identify-verbose \"{0}\"", _strFile);
			mkvinfo->StartInfo->CreateNoWindow = true;
			mkvinfo->StartInfo->UseShellExecute = false;
			mkvinfo->StartInfo->RedirectStandardOutput = true;
			mkvinfo->StartInfo->RedirectStandardError = true;
			mkvinfo->StartInfo->ErrorDialog = false;
			mkvinfo->EnableRaisingEvents = true;
			mkvinfo->ErrorDataReceived += new DataReceivedEventHandler(this, &MkvInfo::backgroundWorker_ErrorDataReceived);
			mkvinfo->OutputDataReceived += new DataReceivedEventHandler(this, &MkvInfo::backgroundWorker_OutputDataReceived);
			try
			{
				mkvinfo->Start();
				mkvinfo->BeginErrorReadLine();
				mkvinfo->BeginOutputReadLine();
				while (!mkvinfo->HasExited) // wait until the process has terminated without locking the GUI
				{
					System::Windows::Forms::Application::DoEvents();
					delay(100);
				}
				mkvinfo->WaitForExit();

				_oLog->LogValue("MkvInfo", _strResult);
				if (mkvinfo->ExitCode != 0)
				{
					_bMuxable = false;
					_bHasChapters = false;
				}
				else
					parseResult();
			}
			catch (std::exception &ex)
			{
				_oLog->LogValue("MkvInfo - Unhandled Error", ex, Error);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				mkvinfo->ErrorDataReceived -= new DataReceivedEventHandler(this, &MkvInfo::backgroundWorker_ErrorDataReceived);
				mkvinfo->OutputDataReceived -= new DataReceivedEventHandler(this, &MkvInfo::backgroundWorker_OutputDataReceived);
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (mkvinfo != 0)
				mkvinfo.Dispose();
		}
	}

	bool MkvInfo::extractChapters(const std::string &strChapterFile)
	{
		_strResult = "";
		bool bResult = false;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Process mkvinfo = new Process())
		Process *mkvinfo = new Process();
		try
		{
			mkvinfo->StartInfo->FileName = MainForm::Instance->getSettings()->getMkvExtractPath();
			mkvinfo->StartInfo->Arguments = std::string::Format("chapters \"{0}\" --ui-language en --simple", _strFile);
			mkvinfo->StartInfo->CreateNoWindow = true;
			mkvinfo->StartInfo->UseShellExecute = false;
			mkvinfo->StartInfo->RedirectStandardOutput = true;
			mkvinfo->StartInfo->RedirectStandardError = true;
			mkvinfo->StartInfo->ErrorDialog = false;
			mkvinfo->EnableRaisingEvents = true;
			mkvinfo->ErrorDataReceived += new DataReceivedEventHandler(this, &MkvInfo::backgroundWorker_ErrorDataReceived);
			mkvinfo->OutputDataReceived += new DataReceivedEventHandler(this, &MkvInfo::backgroundWorker_OutputDataReceived);
			try
			{
				mkvinfo->Start();
				mkvinfo->BeginErrorReadLine();
				mkvinfo->BeginOutputReadLine();
				while (!mkvinfo->HasExited) // wait until the process has terminated without locking the GUI
				{
					System::Windows::Forms::Application::DoEvents();
					delay(100);
				}
				mkvinfo->WaitForExit();

				if (mkvinfo->ExitCode != 0)
					_oLog->LogValue("MkvExtract", _strResult, Error);
				else
				{
					_oLog->LogValue("MkvExtract", _strResult);
					try
					{
						StreamWriter *sr = new StreamWriter(strChapterFile, false);
						sr->Write(_strResult);
						sr->Close();
						bResult = true;
					}
					catch (std::exception &e)
					{
						_oLog->LogValue("MkvExtract - Unhandled Error", e, Error);
					}
				}
				parseResult();
			}
			catch (std::exception &ex)
			{
				_oLog->LogValue("MkvExtract - Unhandled Error", ex, Error);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				mkvinfo->ErrorDataReceived -= new DataReceivedEventHandler(this, &MkvInfo::backgroundWorker_ErrorDataReceived);
				mkvinfo->OutputDataReceived -= new DataReceivedEventHandler(this, &MkvInfo::backgroundWorker_OutputDataReceived);
			}
			return bResult;
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (mkvinfo != 0)
				mkvinfo.Dispose();
		}
	}

	void MkvInfo::parseResult()
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		for (unknown::const_iterator Line = Regex->Split(_strResult, "\r\n").begin(); Line != Regex->Split(_strResult, "\r\n").end(); ++Line)
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
			if ((*Line).StartsWith("Chapters:"))
				_bHasChapters = true;
			else if ((*Line).Contains("(unsupported "))
				_bMuxable = false;
			else if ((*Line).Contains("unsupported container"))
				_bMuxable = false;
		}
	}

	void MkvInfo::backgroundWorker_ErrorDataReceived(object *sender, DataReceivedEventArgs *e)
	{
		if (!e->Data->empty())
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			_strResult += e->Data->Trim() + "\r\n";
	}

	void MkvInfo::backgroundWorker_OutputDataReceived(object *sender, DataReceivedEventArgs *e)
	{
		if (!e->Data->empty())
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			_strResult += e->Data->Trim() + "\r\n";
	}

	void MkvInfo::InitializeInstanceFields()
	{
		_oTracks = std::vector<TrackInfo*>();
	}
}
