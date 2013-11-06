#include "FileUtil.h"

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
//using namespace System::Windows::Forms;
using namespace ICSharpCode::SharpZipLib::Zip;
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

			DirectoryInfo *FileUtil::CreateTempDirectory()
			{
				while (true)
				{
					std::string file = Path::Combine(Path::GetTempPath(), Path::GetRandomFileName());

					if (!File::Exists(file) && !Directory::Exists(file))
					{
						MainForm::Instance->DeleteOnClosing(file);
						return Directory::CreateDirectory(file);
					}
				}
			}

			bool FileUtil::DeleteFile(const std::string &strFile)
			{
				try
				{
					File::Delete(strFile);
					return true;
				}
				catch (...)
				{
					return false;
				}
			}

			void FileUtil::CreateZipFile(const std::string &path, const std::string &filename)
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (ZipOutputStream outputFile = new ZipOutputStream(File.OpenWrite(filename)))
				ZipOutputStream *outputFile = new ZipOutputStream(File::OpenWrite(filename));
				try
				{
					for (std::vector<std::string>::const_iterator file = FileUtil::AllFiles(path).begin(); file != FileUtil::AllFiles(path).end(); ++file)
					{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimStart' method:
						ZipEntry *newEntry = new ZipEntry((*file).substr(path.length())->TrimStart('\\', '/'));
						outputFile->PutNextEntry(newEntry);
						FileStream *input = File::OpenRead(*file);
						FileUtil::copyData(input, outputFile);
						input->Close();
					}
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (outputFile != 0)
						outputFile.Dispose();
				}
			}

			void FileUtil::ExtractZipFile(const std::string &file, const std::string &extractFolder)
			{
				ExtractZipFile(File::OpenRead(file), extractFolder);
			}

			void FileUtil::ExtractZipFile(Stream *s, const std::string &extractFolder)
			{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (ZipFile inputFile = new ZipFile(s))
				ZipFile *inputFile = new ZipFile(s);
				try
				{
					for (ZipFile::const_iterator entry = inputFile->begin(); entry != inputFile->end(); ++entry)
					{
						std::string pathname = Path::Combine(extractFolder, (*entry)->Name);
						if ((*entry)->IsDirectory)
						{
							Directory::CreateDirectory(pathname);
						}
						else // entry.isFile
						{
							assert((*entry)->IsFile);
							FileUtil::ensureDirectoryExists(Path::GetDirectoryName(pathname));
							Stream *outputStream = File::OpenWrite(pathname);
							FileUtil::copyData(inputFile->GetInputStream(*entry), outputStream);
							outputStream->Close();
							File::SetLastWriteTime(pathname, (*entry)->DateTime);
						}
					}
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (inputFile != 0)
						inputFile.Dispose();
				}
			}

			void FileUtil::DeleteDirectoryIfExists(const std::string &p, bool recursive)
			{
				if (Directory::Exists(p))
					Directory::Delete(p, recursive);
			}

			DirectoryInfo *FileUtil::ensureDirectoryExists(const std::string &p)
			{
				if (Directory::Exists(p))
					return new DirectoryInfo(p);
				if (p.empty())
					throw new IOException("Can't create directory");
				ensureDirectoryExists(GetDirectoryName(p));
				delay(100);
				return Directory::CreateDirectory(p);
			}

			std::string FileUtil::GetDirectoryName(const std::string &file)
			{
				std::string path = "";
				try
				{
					path = Path::GetDirectoryName(file);
				}
				catch (...)
				{
				}
				return path;
			}

			std::string FileUtil::getUniqueFilename(const std::string &original, std::vector<std::string> &filenames)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return getUniqueFilename(original, new FileExists(delegate(std::string test)
				{
					return std::find(filenames.begin(), filenames.end(), test) != filenames.end();
				}
			   ));
			}

			std::string FileUtil::getUniqueFilename(const std::string &original, FileExists fileExists)
			{
				if (!fileExists(original))
					return original;
				std::string prefix = Path::Combine(Path::GetDirectoryName(original), Path::GetFileNameWithoutExtension(original)) + "_";
				std::string suffix = Path::GetExtension(original);
				for (int i = 0; true; i++)
				{
					std::string filename = prefix + i + suffix;
					if (!fileExists(filename))
						return filename;
				}
			}

			std::vector<std::string> FileUtil::AllFiles(const std::string &folder)
			{
				std::vector<std::string> list = std::vector<std::string>();
				AddFiles(folder, list);
				return list;
			}

			void FileUtil::AddFiles(const std::string &folder, std::vector<std::string> &list)
			{
				list.AddRange(Directory::GetFiles(folder));
				for (unknown::const_iterator subFolder = Directory::GetDirectories(folder).begin(); subFolder != Directory::GetDirectories(folder).end(); ++subFolder)
					AddFiles(*subFolder, list);
			}

			void FileUtil::copyData(Stream *input, Stream *output)
			{
				int count = -1;
				unsigned char data[BUFFER_SIZE];
				while ((count = input->Read(data, 0, BUFFER_SIZE)) > 0)
				{
					output->Write(data, 0, count);
				}
			}

			std::string FileUtil::GetPathWithoutExtension(const std::string &path)
			{
				return Path::Combine(Path::GetDirectoryName(path), Path::GetFileNameWithoutExtension(path));
			}

			std::string FileUtil::ToShortString(TimeSpan *ts)
			{
				std::string time;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				time = ts->Hours->ToString("00");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				time = time + ":" + ts->Minutes->ToString("00");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				time = time + ":" + ts->Seconds->ToString("00");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				time = time + "." + ts->Milliseconds->ToString("000");
				return time;
			}

			std::string FileUtil::AddToFileName(const std::string &filename, const std::string &extra)
			{
				return Path::Combine(Path::GetDirectoryName(filename), Path::GetFileNameWithoutExtension(filename) + extra + Path::GetExtension(filename));
			}

			bool FileUtil::MatchesFilter(const std::string &filter, const std::string &filename)
			{
				if (filter.empty())
					return true;

				bool bIsFolder = Directory::Exists(filename);

				filter = filter.ToLower(System::Globalization::CultureInfo::InvariantCulture);
				filename = Path::GetFileName(filename)->ToLower(System::Globalization::CultureInfo::InvariantCulture);
//ORIGINAL LINE: string[] filters = filter.Split('|');
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
				std::string *filters = filter.Split('|');

				for (int i = 1; i < sizeof(filters) / sizeof(filters[0]); i += 2)
				{
//ORIGINAL LINE: string[] iFilters = filters[i].Split(';');
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					std::string *iFilters = filters[i].Split(';');
					for (std::string::const_iterator f = iFilters->begin(); f != iFilters->end(); ++f)
					{
						if ((*f).find('*') > -1)
						{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
							if (!(*f).StartsWith("*."))
								throw std::exception("Invalid filter format");

							if (*f == "*.*" && filename.find('.') > -1)
								return true;

							if (*f == "*." && bIsFolder)
								return true;

							std::string extension = (*f).substr(1);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
							if (filename.EndsWith(extension))
								return true;
						}
						else if (*f == filename)
							return true;
						else
							return false;

					}
				}

				return false;
			}

			void FileUtil::CopyFile(const std::string &sourcePath, const std::string &targetPath, const std::string &targetName, bool overwrite)
			{
				if (Directory::Exists(sourcePath))
				{
//ORIGINAL LINE: string[] files = Directory.GetFiles(sourcePath);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
					std::string *files = Directory::GetFiles(sourcePath);

					for (std::string::const_iterator s = files->begin(); s != files->end(); ++s)
					{
						// Use static Path methods to extract only the file name from the path.
						std::string fileName = Path::GetFileName(*s);
						if (fileName == targetName)
						{
							std::string destFile = Path::Combine(targetPath, fileName);
							File::Copy(*s, destFile, overwrite);
						}
					}
				}
				else
					MessageBox::Show("Source path does not exist!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

			void FileUtil::BackupFile(const std::string &sourcePath, bool overwrite)
			{
				try
				{
					if (File::Exists(sourcePath))
					{
						std::string targetPath;
						if (sourcePath.find(System::Windows::Forms::Application::StartupPath) != string::npos)
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
							targetPath = sourcePath.Replace(System::Windows::Forms::Application::StartupPath, System::Windows::Forms::Application::StartupPath + "\\backup");
						else
							targetPath = System::Windows::Forms::Application::StartupPath + "\\backup\\" + (new FileInfo(sourcePath))->Name;
						if (File::Exists(targetPath))
							File::Delete(targetPath);

						FileUtil::ensureDirectoryExists(Path::GetDirectoryName(targetPath));

						File::Move(sourcePath, targetPath);
					}
				}
				catch (std::exception &ex)
				{
					MessageBox::Show("Error while moving file: \n" + sourcePath + "\n" + ex.what(), "Error moving file", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}

			bool FileUtil::IsDirWriteable(const std::string &strPath)
			{
				try
				{
					bool bDirectoryCreated = false;

					// does the root directory exists
					if (!Directory::Exists(strPath))
					{
						Directory::CreateDirectory(strPath);
						bDirectoryCreated = true;
					}

					std::string newFilePath = "";
					// combine the random file name with the path
					do
						newFilePath = Path::Combine(strPath, Path::GetRandomFileName());
					while (File::Exists(newFilePath));

					// create & delete the file
					FileStream *fs = File::Create(newFilePath);
					fs->Close();
					File::Delete(newFilePath);

					if (bDirectoryCreated)
						Directory::Delete(strPath);

					return true;
				}
				catch (...)
				{
					return false;
				}
			}

			MeGUI::core::util::LogItem *FileUtil::DeleteIntermediateFiles(std::vector<std::string> &files, bool bAlwaysAddLog, bool askAboutDelete)
			{
				bool bShowLog = false;
				LogItem *i = new LogItem(std::string::Format("[{0:G}] {1}", DateTime::Now, "Deleting intermediate files"));

				std::vector<std::string> arrFiles = std::vector<std::string>();
				for (std::vector<std::string>::const_iterator file = files.begin(); file != files.end(); ++file)
				{
					if (Directory::Exists(*file))
						continue;
					else if (!File::Exists(*file))
						continue;
					if (!std::find(arrFiles.begin(), arrFiles.end(), *file) != arrFiles.end())
						arrFiles.push_back(*file);
				}

				if (arrFiles.size() > 0)
				{
					bShowLog = true;
					bool delete_Renamed = true;

					if (askAboutDelete)
						delete_Renamed = MainForm::Instance->getDialogManager()->DeleteIntermediateFiles(arrFiles);
					if (!delete_Renamed)
						return 0;

					// delete all files first
					for (std::vector<std::string>::const_iterator file = arrFiles.begin(); file != arrFiles.end(); ++file)
					{
						int iCounter = 0;
						while (File::Exists(file))
						{
							try
							{
								File::Delete(*file);
								i->LogEvent("Successfully deleted " + *file);
							}
							catch (IOException *e)
							{
								if (++iCounter >= 3)
								{
									i->LogValue("Problem deleting " + *file, e->Message, Warning);
									break;
								}
								else
									delay(2000);
							}
						}
					}
				}

				// delete empty directories
				for (std::vector<std::string>::const_iterator file = files.begin(); file != files.end(); ++file)
				{
					try
					{
						if (Directory::Exists(*file))
						{
							bShowLog = true;
							if (Directory::GetFiles(*file, "*.*", SearchOption::AllDirectories)->Length == 0)
							{
								Directory::Delete(*file, true);
								i->LogEvent("Successfully deleted directory " + *file);
							}
							else
								i->LogEvent("Did not delete " + *file + " as the directory is not empty.", Warning);
						}
					}
					catch (IOException *e)
					{
						i->LogValue("Problem deleting directory " + *file, e->Message, Warning);
					}
				}
				if (bAlwaysAddLog || bShowLog)
					return i;
				return 0;
			}

			void FileUtil::GetFileInformation(const std::string &strName, const std::string &strFile, LogItem *&oLog)
			{
				std::string fileVersion = "";
				std::string fileDate = "";
				if (File::Exists(strFile))
				{
					FileVersionInfo *FileProperties = FileVersionInfo::GetVersionInfo(strFile);
					fileVersion = FileProperties->FileVersion;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					fileDate = File::GetLastWriteTimeUtc(strFile)->ToString("dd-MM-yyyy");

					if (fileVersion.empty())
						oLog->LogValue(strName, " (" + fileDate + ")");
					else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
						oLog->LogValue(strName, fileVersion.Replace(", ", ".")->ToString() + " (" + fileDate + ")");
				}
				else
					if (strName.find("Haali") != string::npos)
						oLog->LogValue(strName, "not installed", Warning);
					else
						oLog->LogValue(strName, "not installed", Error);
			}

			void FileUtil::CreateXMLFromOGGChapFile(const std::string &inFile)
			{
				try
				{
					StringBuilder *sb = new StringBuilder();
					sb->AppendLine("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
					sb->AppendLine("<!-- GPAC 3GPP Text Stream -->");
					sb->AppendLine("<TextStream version=\"1.1\">");
					sb->AppendLine("<TextStreamHeader>");
					sb->AppendLine("<TextSampleDescription>");
					sb->AppendLine("</TextSampleDescription>");
					sb->AppendLine("</TextStreamHeader>");

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (StreamReader sr = new StreamReader(inFile))
					StreamReader *sr = new StreamReader(inFile);
					try
					{
						std::string line = "";
						std::string chapTitle = "";
						int i = 0;
						while ((line = sr->ReadLine()) != 0)
						{
							i++;
							if (i % 2 == 1)
								sb->Append("<TextSample sampleTime=\"" + line.substr(line.find("=") + 1) + "\"");
							else
							{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
								chapTitle = System::Text::RegularExpressions::Regex->Replace(line.substr(line.find("=") + 1), "\"", "&quot;");
								sb->Append(" text=\"" + chapTitle + "\"></TextSample>" + "\r\n");
							}
						}
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (sr != 0)
							sr.Dispose();
					}
					sb->AppendLine("</TextStream>");

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using (StreamWriter sw = new StreamWriter(Path.Combine(Path.GetDirectoryName(inFile), Path.GetFileNameWithoutExtension(inFile) + ".xml")))
					StreamWriter *sw = new StreamWriter(Path::Combine(Path::GetDirectoryName(inFile), Path::GetFileNameWithoutExtension(inFile) + ".xml"));
					try
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						sw->Write(sb->ToString());
						sw->Close();
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (sw != 0)
							sw.Dispose();
					}
				}
				catch (std::exception &e)
				{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					e.what()->ToString();
				}
			}

			short FileUtil::GetFileEncoding(const std::string &srcFile)
			{
				// *** Use Default of Encoding.Default (Ansi CodePage)
				Encoding *enc = Encoding::Default;
				short v = 0;

				// *** Detect byte order mark if any - otherwise assume default
				unsigned char buffer[5];
				FileStream *file = new FileStream(srcFile, FileMode->Open);
				file->Read(buffer, 0, 5);
				file->Close();

				if (buffer[0] == 0xef && buffer[1] == 0xbb && buffer[2] == 0xbf) // UTF8
				{
					enc = Encoding::UTF8;
					v = 1;
				}
				else if (buffer[0] == 0xfe && buffer[1] == 0xff) // Unicode
				{
					enc = Encoding::Unicode;
					v = 2;
				}
				else if (buffer[0] == 0 && buffer[1] == 0 && buffer[2] == 0xfe && buffer[3] == 0xff) // UTF32
				{
					enc = Encoding::UTF32;
					v = 3;
				}
				else if (buffer[0] == 0x2b && buffer[1] == 0x2f && buffer[2] == 0x76) // UTF7
				{
					enc = Encoding::UTF7;
					v = 4;
				}

				return v;
			}
		}
	}
}
