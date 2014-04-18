#include "OSInfo.h"






//using namespace System::Diagnostics;

//using namespace System::Management;

//using namespace System::Runtime::InteropServices;



namespace MeXgui
{

	bool OSInfo::isWow64()
	{
		if (Environment::OSVersion::Version->Major == 5 && Environment::OSVersion::Version->Minor == 0)
			return false; // windows 2000

		Process *p = Process::GetCurrentProcess();
		void* handle = p->Handle;
		bool isWow64;
		bool success = IsWow64Process(handle, isWow64);
		if ((!success) && (void*::Size != 8))
			throw std::exception();
		else
			return isWow64;
	}

	QString OSInfo::GetOSServicePack()
	{
		OSVERSIONINFOEX osVersionInfo = OSVERSIONINFOEX();

		osVersionInfo.dwOSVersionInfoSize = Marshal::SizeOf(OSVERSIONINFOEX::typeid);

		if (!GetVersionEx(osVersionInfo))
		{
			return "";
		}
		else
		{
			if (osVersionInfo.szCSDVersion != "")
			{
				return " SP" + osVersionInfo.szCSDVersion.substr(13, 1);
			}
			else
			{
				return "";
			}
		}
	}

	QString OSInfo::GetOSName()
	{
		OperatingSystem *osInfo = Environment::OSVersion;
		OSVERSIONINFOEX osVersionInfo = OSVERSIONINFOEX();
		osVersionInfo.dwOSVersionInfoSize = Marshal::SizeOf(OSVERSIONINFOEX::typeid);
		QString osName = "UNKNOWN";
		bool x64Detection = false;

		if (!GetVersionEx(osVersionInfo))
		{
			return "";
		}
		else
		{
			switch (osInfo->Platform)
			{
				case PlatformID::Win32Windows:
				{
						switch (osInfo->Version->Minor)
						{
							case 0:
								osName = "Windows 95";
								break;
							case 10:
							{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
									if (osInfo->Version->Revision->ToString() == "2222A")
										 osName = "Windows 98 Second Edition";
									else
										osName = "Windows 98";
							}
								break;
							case 90:
								osName = "Windows Me";
								break;
						}
						break;
				}
				case PlatformID::Win32NT:
				{
						switch (osInfo->Version->Major)
						{
							case 3:
								osName = "Windows NT 3.51";
								break;
							case 4:
							{
									switch (osVersionInfo.wProductType)
									{
										case 1:
											osName = "Windows NT 4.0 Workstation";
											break;
										case 3:
											osName = "Windows NT 4.0 Server";
											break;
									}
									break;
							}
							case 5:
							{
									switch (osInfo->Version->Minor)
									{
										case 0: // win2K
										{
												if ((osVersionInfo.wSuiteMask & VER_SUITE_DATACENTER) == VER_SUITE_DATACENTER)
													 osName = "Windows 2000 Datacenter Server";
												else if ((osVersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE) == VER_SUITE_ENTERPRISE)
													 osName = "Windows 2000 Advanced Server";
												else
													 osName = "Windows 2000";
												break;
										}
										case 1: // winXP
										{
												if ((osVersionInfo.wSuiteMask & VER_SUITE_PERSONAL) == VER_SUITE_PERSONAL)
													 osName = "Windows XP Home Edition";
												else
													osName = "Windows XP Professional";
												x64Detection = true;
												break;
										}
										case 2: // winserver 2003
										{
												if ((osVersionInfo.wSuiteMask & VER_SUITE_DATACENTER) == VER_SUITE_DATACENTER)
													 osName = "Windows Server 2003 DataCenter Edition";
												else if ((osVersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE) == VER_SUITE_ENTERPRISE)
													 osName = "Windows Server 2003 Enterprise Edition";
												else if ((osVersionInfo.wSuiteMask & VER_SUITE_BLADE) == VER_SUITE_BLADE)
													 osName = "Windows Server 2003 Web Edition";
												else
													osName = "Windows Server 2003 Standard Edition";
												x64Detection = true;
												break;
										}
									}
									break;
							}
							case 6:
							{
									x64Detection = true;
									switch (osInfo->Version->Minor)
									{
										case 0:
										{
												switch (osVersionInfo.wProductType)
												{
													case 1: // Vista
													{
															unsigned int edition = PRODUCT_UNDEFINED;
															if (GetProductInfo(osVersionInfo.dwMajorVersion, osVersionInfo.dwMinorVersion, osVersionInfo.wServicePackMajor, osVersionInfo.wServicePackMinor, edition))
															{
																switch (edition)
																{
																	case PRODUCT_ULTIMATE:
																		osName = "Windows Vista Ultimate Edition";
																		break;
																	case PRODUCT_HOME_BASIC:
																	case PRODUCT_HOME_BASIC_N:
																		osName = "Windows Vista Home Basic Edition";
																		break;
																	case PRODUCT_HOME_PREMIUM:
																		osName = "Windows Vista Premium Edition";
																		break;
																	case PRODUCT_ENTERPRISE:
																		osName = "Windows Vista Enterprise Edition";
																		break;
																	case PRODUCT_BUSINESS:
																	case PRODUCT_BUSINESS_N:
																		osName = "Windows Vista Business Edition";
																		break;
																	case PRODUCT_STARTER:
																		osName = "Windows Vista Starter Edition";
																		break;
																	default:
																		osName = "Windows Vista";
																		break;
																}
															}
															break;
													}
													case 3: // Server 2008
													{
															if ((osVersionInfo.wSuiteMask & VER_SUITE_DATACENTER) == VER_SUITE_DATACENTER)
																osName = "Windows Server 2008 Datacenter Server";
															else if ((osVersionInfo.wSuiteMask & VER_SUITE_ENTERPRISE) == VER_SUITE_ENTERPRISE)
																osName = "Windows Server 2008 Advanced Server";
															else
																osName = "Windows Server 2008";
															break;
													}
												}
												break;
										}
										case 1: // Se7en
										{
												unsigned int edition = PRODUCT_UNDEFINED;
												if (GetProductInfo(osVersionInfo.dwMajorVersion, osVersionInfo.dwMinorVersion, osVersionInfo.wServicePackMajor, osVersionInfo.wServicePackMinor, edition))
												{
													switch (edition)
													{
														case PRODUCT_ULTIMATE:
															osName = "Windows 7 Ultimate Edition";
															break;
														case PRODUCT_HOME_BASIC:
														case PRODUCT_HOME_BASIC_N:
															osName = "Windows 7 Home Basic Edition";
															break;
														case PRODUCT_HOME_PREMIUM:
															osName = "Windows 7 Premium Edition";
															break;
														case PRODUCT_ENTERPRISE:
															osName = "Windows 7 Enterprise Edition";
															break;
														case PRODUCT_BUSINESS:
														case PRODUCT_BUSINESS_N:
															osName = "Windows 7 Professional Edition";
															break;
														case PRODUCT_STARTER:
															osName = "Windows 7 Starter Edition";
															break;
														default:
															osName = "Windows 7";
															break;
													}
												}
												break;
										}
										case 2: // Windows 8
										{
												unsigned int edition = PRODUCT_UNDEFINED;
												if (GetProductInfo(osVersionInfo.dwMajorVersion, osVersionInfo.dwMinorVersion, osVersionInfo.wServicePackMajor, osVersionInfo.wServicePackMinor, edition))
												{
													switch (edition)
													{
														case PRODUCT_CORE:
														case PRODUCT_CORE_COUNTRYSPECIFIC:
														case PRODUCT_CORE_N:
															osName = "Windows 8 Standard Edition";
															break;
														case PRODUCT_ENTERPRISE:
														case PRODUCT_ENTERPRISE_N:
															osName = "Windows 8 Entreprise Edition";
															break;
														case PRODUCT_PROFESSIONAL:
														case PRODUCT_PROFESSIONAL_N:
															osName = "Windows 8 Professional Edition";
															break;
														case PRODUCT_PROFESSIONAL_WMC:
															osName = "Windows 8 Professional with Media Center Edition";
															break;
														default:
															osName = "Windows 8";
															break;
													}
												}
												break;
										}
										case 3: // Windows 8.1
										{
												unsigned int edition = PRODUCT_UNDEFINED;
												if (GetProductInfo(osVersionInfo.dwMajorVersion, osVersionInfo.dwMinorVersion, osVersionInfo.wServicePackMajor, osVersionInfo.wServicePackMinor, edition))
												{
													switch (edition)
													{
														case PRODUCT_CORE:
														case PRODUCT_CORE_COUNTRYSPECIFIC:
														case PRODUCT_CORE_N:
															osName = "Windows 8.1 Standard Edition";
															break;
														case PRODUCT_ENTERPRISE:
														case PRODUCT_ENTERPRISE_N:
															osName = "Windows 8.1 Entreprise Edition";
															break;
														case PRODUCT_PROFESSIONAL:
														case PRODUCT_PROFESSIONAL_N:
															osName = "Windows 8.1 Professional Edition";
															break;
														case PRODUCT_PROFESSIONAL_WMC:
															osName = "Windows 8.1 Professional with Media Center Edition";
															break;
														default:
															osName = "Windows 8.1";
															break;
													}
												}
												break;
										}
									}
									break;
							}
						}
						break;
				}
			}
		}
	#if defined(x64)
		osName += " x64";
	#endif
	#if defined(x86)
		if (x64Detection)
		{
			if (!isWow64())
				osName += " x86";
			else
				osName += " x64";
		}
	#endif
		return osName;
	}

	QString OSInfo::GetDotNetVersion()
	{
		return GetDotNetVersion("");
	}

	QString OSInfo::GetDotNetVersion(const QString &getSpecificVersion)
	{
		QString fv = "unknown";
		QString componentsKeyName = "SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\";

		// Find out in the registry anything under:
		// HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP & ".NET Framework" in the name

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Microsoft.Win32.RegistryKey componentsKey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(componentsKeyName))
		Microsoft::Win32::RegistryKey *componentsKey = Microsoft::Win32::Registry::LocalMachine::OpenSubKey(componentsKeyName);
		try
		{
			try
			{
//ORIGINAL LINE: string[] instComps = componentsKey.GetSubKeyNames();
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				QString *instComps = componentsKey->GetSubKeyNames();
				ArrayList *versions = new ArrayList();

				for (QString::const_iterator instComp = instComps->begin(); instComp != instComps->end(); ++instComp)
				{
					Microsoft::Win32::RegistryKey *key = componentsKey->OpenSubKey(*instComp);
					QString version = static_cast<QString>(key->GetValue("Version"));

					if (!version.empty())
					{
						versions->Add(version);
					}
					else
					{
						for (unknown::const_iterator strRegKey = key->GetSubKeyNames().begin(); strRegKey != key->GetSubKeyNames().end(); ++strRegKey)
						{
							Microsoft::Win32::RegistryKey *strKey = key->OpenSubKey(*strRegKey);
							QString strVersion = static_cast<QString>(strKey->GetValue("Version"));
							if (!strVersion.empty())
								versions->Add(strVersion);
						}
					}
				}
				versions->Sort();

				for (ArrayList::const_iterator version = versions->begin(); version != versions->end(); ++version)
				{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
					if (!getSpecificVersion.empty() && ((*version).StartsWith(getSpecificVersion) || DotNetVersionFormated(*version).StartsWith(getSpecificVersion)))
						return version;
					fv = *version;
				}

				if (!getSpecificVersion.empty())
					return 0;
			}
			catch (...)
			{
				return 0;
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (componentsKey != 0)
				componentsKey.Dispose();
		}
		return fv;
	}

	QString OSInfo::DotNetVersionFormated(const QString &dotNetVersion)
	{
		QString dnvf = "unknown";
		QString major = "";
		QString minor = "";
		QString build = "";
		QString revision = "";

		try
		{
			if (dotNetVersion != "unknown")
			{
//ORIGINAL LINE: string[] versions = dotNetVersion.Split('.');
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
				QString *versions = dotNetVersion.Split('.');

				if (sizeof(versions) / sizeof(versions[0]) >= 1)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					major = versions[0].ToString();
				if (sizeof(versions) / sizeof(versions[0]) > 1)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					minor = versions[1].ToString();
				if (sizeof(versions) / sizeof(versions[0]) > 2)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					build = versions[2].ToString();
				if (sizeof(versions) / sizeof(versions[0]) > 3)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					revision = versions[3].ToString();

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//				switch (major)
//ORIGINAL LINE: case "1":
				if (major == "1")
				{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//							switch (minor)
//ORIGINAL LINE: case "0":
							if (minor == "0")
							{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//										switch (revision)
//ORIGINAL LINE: case "209":
										if (revision == "209")
										{
												dnvf = "1.0 SP1";
										}
//ORIGINAL LINE: case "288":
										else if (revision == "288")
										{
												dnvf = "1.0 SP2";
										}
//ORIGINAL LINE: case "6018":
										else if (revision == "6018")
										{
												dnvf = "1.0 SP3";
										}
										else
										{
												dnvf = "1.0";
										}
							}
//ORIGINAL LINE: case "1":
							else if (minor == "1")
							{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//										switch (revision)
//ORIGINAL LINE: case "2032":
										if (revision == "2032" || revision == "2300")
										{
												dnvf = "1.1 SP1";
										}
										else
										{
												dnvf = "1.1";
										}
							}
							else
							{
									dnvf = "1.x";
							}
				}
//ORIGINAL LINE: case "2":
				else if (major == "2")
				{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//							switch (revision)
//ORIGINAL LINE: case "1433":
							if (revision == "1433" || revision == "1434")
							{
									dnvf = "2.0 SP1";
							}
//ORIGINAL LINE: case "2407":
							else if (revision == "2407" || revision == "3053" || revision == "3074" || revision == "4016" || revision == "4927")
							{
									dnvf = "2.0 SP2";
							}
							else
							{
									dnvf = "2.0";
							}
				}
//ORIGINAL LINE: case "3":
				else if (major == "3")
				{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//							switch (minor)
//ORIGINAL LINE: case "0":
							if (minor == "0")
							{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//										switch (revision)
//ORIGINAL LINE: case "648":
										if (revision == "648")
										{
												dnvf = "3.0 SP1";
										}
//ORIGINAL LINE: case "1453":
										else if (revision == "1453" || revision == "2123" || revision == "4000" || revision == "4037" || revision == "4902" || revision == "4926")
										{
												dnvf = "3.0 SP2";
										}
										else
										{
												dnvf = "3.0";
										}
							}
//ORIGINAL LINE: case "5":
							else if (minor == "5")
							{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//										switch (revision)
//ORIGINAL LINE: case "4926":
										if (revision == "4926" || revision == "1") // Se7en
										{
												dnvf = "3.5 SP1";
										}
										else
										{
												dnvf = "3.5";
										}
							}
							else
							{
									dnvf = "3.x";
							}
				}
//ORIGINAL LINE: case "4":
				else if (major == "4")
				{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//							switch (minor)
//ORIGINAL LINE: case "0":
							if (minor == "0")
							{
									dnvf = "4.0";
							}
//ORIGINAL LINE: case "5":
							else if (minor == "5")
							{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//										switch (build)
//ORIGINAL LINE: case "50709":
										if (build == "50709")
										{
												dnvf = "4.5";
										}
//ORIGINAL LINE: case "51641":
										else if (build == "51641")
										{
												dnvf = "4.5.1";
										}
										else
										{
												dnvf = "4.5.x";
										}
							}
							else
							{
									dnvf = "4.x";
							}
				}
				else
				{
						dnvf = major + ".x";
				}

				if (revision.empty())
					dnvf += " (" + major + "." + minor + "." + build + ")";
				else
					dnvf += " (" + major + "." + minor + "." + build + "." + revision + ")";
			}
		}
		catch (...)
		{
			dnvf = "unknown: " + dotNetVersion;
		}
		return dnvf;
	}

	QString OSInfo::GetMOStuff(const QString &queryObject)
	{
		ManagementObjectSearcher *searcher = 0;
		QString res = "";
		try
		{
		   searcher = new ManagementObjectSearcher("SELECT * FROM " + queryObject);
		   for (unknown::const_iterator mo = searcher->Get().begin(); mo != searcher->Get().end(); ++mo)
		   {
				if (queryObject == "Win32_OperatingSystem")
				{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					res = *mo["Caption"]->ToString();
				}
				else if (queryObject == "Win32_Processor")
				{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					res = *mo["Name"]->ToString();
				}
				else if (queryObject == "Win32_LogicalDisk")
				{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					if (*mo["DriveType"]->ToString() == "3") // HDD
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						qint64 freespace = qint64::Parse(*mo["FreeSpace"]->ToString()) / 1073741824;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						qint64 totalsize = qint64::Parse(*mo["Size"]->ToString()) / 1073741824;

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						if (*mo["VolumeName"]->ToString() == "")
							*mo["VolumeName"] = "Local Disk";

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						res += *mo["VolumeName"]->ToString() + " (" + *mo["Name"]->ToString() + ")  -  " + StringConverterHelper::toString(freespace) + " Go free of " + StringConverterHelper::toString(totalsize) + " Go\n";
					}
				}
		   }
		}
		catch (std::exception &ex)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			MessageBox::Show(ex.ToString());
		}
		return res;
	}

	const QString &OSInfo::getOSVersion() const
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return Environment::OSVersion::Version->ToString();
	}

	const int &OSInfo::getOSMajorVersion() const
	{
		return Environment::OSVersion::Version::Major;
	}

	const int &OSInfo::getOSMinorVersion() const
	{
		return Environment::OSVersion::Version::Minor;
	}

	const int &OSInfo::getOSBuildVersion() const
	{
		return Environment::OSVersion::Version::Build;
	}

	const int &OSInfo::getOSRevisionVersion() const
	{
		return Environment::OSVersion::Version::Revision;
	}
}
