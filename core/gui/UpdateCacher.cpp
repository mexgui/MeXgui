#include "UpdateCacher.h"




//using namespace System::Collections::Generic;





//using namespace System::Net;

//using namespace System::Text;

//using namespace System::Threading;
using namespace ICSharpCode::SharpZipLib::Zip;
using namespace SevenZip;
using namespace MeXgui::core::util;

namespace MeXgui
{

	void UpdateCacher::flushOldCachedFilesAsync(QVector<QString> &urls, UpdateWindow *oUpdate)
	{
		QString updateCache = MainForm::Instance->getSettings()->getMeXguiUpdateCache();
		if (updateCache.empty() || !Directory::Exists(updateCache))
			return;

		DirectoryInfo *fi = new DirectoryInfo(updateCache);
//ORIGINAL LINE: FileInfo[] files = fi.GetFiles();
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		FileInfo *files = fi->GetFiles();

		for (int i = 0; i < urls.size(); ++i)
		{
			urls[i] = urls[i].ToLower(System::Globalization::CultureInfo::InvariantCulture);
		}

		for (FileInfo::const_iterator f = files->begin(); f != files->end(); ++f)
		{
			if (urls.find((*f)->Name->ToLower(System::Globalization::CultureInfo::InvariantCulture)) < 0)
			{
				if (DateTime::Now - (*f)->LastWriteTime > new TimeSpan(60, 0, 0, 0, 0))
				{
					(*f)->Delete();
					oUpdate->AddTextToLog("Deleted cached file " + (*f)->Name, Information);
				}
			}
		}
	}

	void UpdateCacher::ensureSensibleCacheFolderExists()
	{
		FileUtil::ensureDirectoryExists(MainForm::Instance->getSettings()->getMeXguiUpdateCache());
	}

	UpdateWindow::ErrorState UpdateCacher::DownloadFile(const QString &url, Uri *serverAddress, Stream *&str, DownloadProgressChangedEventHandler *wc_DownloadProgressChanged, UpdateWindow *oUpdate)
	{
		ensureSensibleCacheFolderExists();
		UpdateWindow::ErrorState er = UpdateWindow::Successful;
		QString updateCache = MainForm::Instance->getSettings()->getMeXguiUpdateCache();
		QString localFilename = Path::Combine(updateCache, url);
		bool downloadFile = true;

		if (File::Exists(localFilename))
		{
			FileInfo *finfo = new FileInfo(localFilename);
			if (finfo->Length == 0)
			{
				oUpdate->AddTextToLog(localFilename + " is empty. Deleting file.", Information);
				UpdateCacher::FlushFile(localFilename, oUpdate);
			}

			// check the zip file
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if (localFilename.ToLowerInvariant()->EndsWith(".zip"))
			{
				try
				{
					ZipFile *zipFile = new ZipFile(localFilename);
					if (zipFile->TestArchive(true) == false)
					{
						oUpdate->AddTextToLog("Could not unzip " + localFilename + ". Deleting file.", Information);
						UpdateCacher::FlushFile(localFilename, oUpdate);
					}
					else
						downloadFile = false;
				}
				catch (...)
				{
					oUpdate->AddTextToLog("Could not unzip " + localFilename + ". Deleting file.", Error);
					UpdateCacher::FlushFile(localFilename, oUpdate);
				}
			}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			else if (localFilename.ToLowerInvariant()->EndsWith(".7z")) // check the 7-zip file
			{
				try
				{
					SevenZipExtractor *oArchive = new SevenZipExtractor(localFilename);
					if (oArchive->Check() == false)
					{
						oUpdate->AddTextToLog("Could not extract " + localFilename + ". Deleting file.", Information);
						UpdateCacher::FlushFile(localFilename, oUpdate);
					}
					else
						downloadFile = false;
				}
				catch (...)
				{
					oUpdate->AddTextToLog("Could not extract " + localFilename + ". Deleting file.", Error);
					UpdateCacher::FlushFile(localFilename, oUpdate);
				}
			}
			else
				downloadFile = false;
		}

		if (downloadFile)
		{
			WebClient *wc = new WebClient();

			// check for proxy authentication...
			wc->Proxy = HttpProxy::GetProxy(MainForm::Instance->getSettings());

			ManualResetEvent *mre = new ManualResetEvent(false);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			wc->DownloadFileCompleted += delegate(object sender, AsyncCompletedQEvent e)
			{
				if (e::Error != 0)
					er = UpdateWindow::CouldNotDownloadFile;

				mre->Set();
			};

			wc->DownloadProgressChanged += wc_DownloadProgressChanged;

			wc->DownloadFileAsync(new Uri(serverAddress, url), localFilename);
			mre->WaitOne();

			if (File::Exists(localFilename))
			{
				FileInfo *finfo = new FileInfo(localFilename);
				if (finfo->Length == 0)
					UpdateCacher::FlushFile(localFilename, oUpdate);
			}
		}

		try
		{
			if (File::Exists(localFilename))
				str = File::OpenRead(localFilename);
			else
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
				delete str;
		}
		catch (IOException *e1)
		{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete str;
			return UpdateWindow::CouldNotDownloadFile;
		}

		return er;
	}

	void UpdateCacher::FlushFile(const QString &p, UpdateWindow *oUpdate)
	{
		QString localFilename = Path::Combine(MainForm::Instance->getSettings()->getMeXguiUpdateCache(), p);
		try
		{
			File::Delete(localFilename);
		}
		catch (IOException *e1)
		{
			oUpdate->AddTextToLog("Could not delete file " + localFilename, Error);
		}
	}
}
