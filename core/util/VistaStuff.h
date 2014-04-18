#pragma once

#include <QString>

// ****************************************************************************
// 
// Copyright (C) 2005-2012  Doom9 & al
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




//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;

//using namespace System::Runtime::InteropServices;

//using namespace System::Runtime::ConstrainedExecution;

//using namespace System::Text;

//using namespace System::Threading;

namespace MeXgui
{
	namespace core
	{
		namespace util
		{
			class VistaStuff
			{
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential, CharSet = CharSet::Auto, Pack = 4)]
				class COMDLG_FILTERSPEC
				{
				public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszName;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszSpec;
				};

			public:
				enum FDAP
				{
					FDAP_BOTTOM = 0x00000000,
					FDAP_TOP = 0x00000001,
				};

			public:
				enum FDE_SHAREVIOLATION_RESPONSE
				{
					FDESVR_DEFAULT = 0x00000000,
					FDESVR_ACCEPT = 0x00000001,
					FDESVR_REFUSE = 0x00000002
				};

			public:
				enum FDE_OVERWRITE_RESPONSE
				{
					FDEOR_DEFAULT = 0x00000000,
					FDEOR_ACCEPT = 0x00000001,
					FDEOR_REFUSE = 0x00000002
				};

			public:
				enum SIATTRIBFLAGS
				{
					SIATTRIBFLAGS_AND = 0x00000001, // if multiple items and the attirbutes together.
					SIATTRIBFLAGS_OR = 0x00000002, // if multiple items or the attributes together.
					SIATTRIBFLAGS_APPCOMPAT = 0x00000003, // Call GetAttributes directly on the ShellFolder for multiple attributes
				};

			public:
				enum SIGDN
				{
					SIGDN_NORMALDISPLAY = 0x00000000, // SHGDN_NORMAL
					SIGDN_PARENTRELATIVEPARSING = 0x80018001, // SHGDN_INFOLDER | SHGDN_FORPARSING
					SIGDN_DESKTOPABSOLUTEPARSING = 0x80028000, // SHGDN_FORPARSING
					SIGDN_PARENTRELATIVEEDITING = 0x80031001, // SHGDN_INFOLDER | SHGDN_FOREDITING
					SIGDN_DESKTOPABSOLUTEEDITING = 0x8004c000, // SHGDN_FORPARSING | SHGDN_FORADDRESSBAR
					SIGDN_FILESYSPATH = 0x80058000, // SHGDN_FORPARSING
					SIGDN_URL = 0x80068000, // SHGDN_FORPARSING
					SIGDN_PARENTRELATIVEFORADDRESSBAR = 0x8007c001, // SHGDN_INFOLDER | SHGDN_FORPARSING | SHGDN_FORADDRESSBAR
					SIGDN_PARENTRELATIVE = 0x80080001 // SHGDN_INFOLDER
				};

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Flags]
				enum FOS
				{
					FOS_OVERWRITEPROMPT = 0x00000002,
					FOS_STRICTFILETYPES = 0x00000004,
					FOS_NOCHANGEDIR = 0x00000008,
					FOS_PICKFOLDERS = 0x00000020,
					FOS_FORCEFILESYSTEM = 0x00000040, // Ensure that items returned are filesystem items.
					FOS_ALLNONSTORAGEITEMS = 0x00000080, // Allow choosing items that have no storage.
					FOS_NOVALIDATE = 0x00000100,
					FOS_ALLOWMULTISELECT = 0x00000200,
					FOS_PATHMUSTEXIST = 0x00000800,
					FOS_FILEMUSTEXIST = 0x00001000,
					FOS_CREATEPROMPT = 0x00002000,
					FOS_SHAREAWARE = 0x00004000,
					FOS_NOREADONLYRETURN = 0x00008000,
					FOS_NOTESTFILECREATE = 0x00010000,
					FOS_HIDEMRUPLACES = 0x00020000,
					FOS_HIDEPINNEDPLACES = 0x00040000,
					FOS_NODEREFERENCELINKS = 0x00100000,
					FOS_DONTADDTORECENT = 0x02000000,
					FOS_FORCESHOWHIDDEN = 0x10000000,
					FOS_DEFAULTNOMINIMODE = 0x20000000
				};

			public:
				enum CDCONTROLSTATE
				{
					CDCS_INACTIVE = 0x00000000,
					CDCS_ENABLED = 0x00000001,
					CDCS_VISIBLE = 0x00000002
				};

			public:
				enum FFFP_MODE
				{
					FFFP_EXACTMATCH,
					FFFP_NEARESTPARENTMATCH
				};

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential, CharSet = CharSet::Auto, Pack = 4)]
				class KNOWNFOLDER_DEFINITION
				{
				public:
					VistaStuff::KF_CATEGORY category;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszName;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszCreator;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszDescription;
					Guid *fidParent;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszRelativePath;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszParsingName;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszToolTip;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszLocalizedName;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszIcon;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::LPWStr)]
					QString pszSecurity;
					unsigned int dwAttributes;
					VistaStuff::KF_DEFINITION_FLAGS kfdFlags;
					Guid *ftidType;
				};

			public:
				enum KF_CATEGORY
				{
					KF_CATEGORY_VIRTUAL = 0x00000001,
					KF_CATEGORY_FIXED = 0x00000002,
					KF_CATEGORY_COMMON = 0x00000003,
					KF_CATEGORY_PERUSER = 0x00000004
				};

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Flags]
				enum KF_DEFINITION_FLAGS
				{
					KFDF_PERSONALIZE = 0x00000001,
					KFDF_LOCAL_REDIRECT_ONLY = 0x00000002,
					KFDF_ROAMABLE = 0x00000004,
				};

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential, Pack = 4)]
				class PROPERTYKEY
				{
				public:
					Guid *fmtid;
					unsigned int pid;
				};

			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Flags()]
				enum FormatMessageFlags
				{
					FORMAT_MESSAGE_ALLOCATE_BUFFER = 0x00000100,
					FORMAT_MESSAGE_IGNORE_INSERTS = 0x00000200,
					FORMAT_MESSAGE_FROM_STRING = 0x00000400,
					FORMAT_MESSAGE_FROM_HMODULE = 0x00000800,
					FORMAT_MESSAGE_FROM_SYSTEM = 0x00001000,
					FORMAT_MESSAGE_ARGUMENT_ARRAY = 0x00002000
				};
				/// <value>
				/// Returns true on Windows Vista or newer operating systems; otherwise, false.
				/// </value>
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
				const static bool &getIsVistaOrNot() const;

				/// <value>
				/// Sets the memory and I/O priority on Windows Vista or newer operating systems
				/// </value>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
				static void SetProcessPriority(IntPtr handle, ProcessPriorityClass *priority);

				/// <value>
				/// Sets the memory and I/O priority on Windows Vista or newer operating systems
				/// </value>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[Browsable(false)]
				static void SetThreadPriority(IntPtr handle, ThreadPriority *priority);

				static const int BS_COMMANDLINK = 0x0000000E;
				static const int BCM_SETNOTE = 0x00001609;
				static const int BCM_SETSHIELD = 0x0000160C;

				static const int TV_FIRST = 0x1100;
				static const int TVM_SETEXTENDEDSTYLE = TV_FIRST + 44;
				static const int TVM_GETEXTENDEDSTYLE = TV_FIRST + 45;
				static const int TVM_SETAUTOSCROLLINFO = TV_FIRST + 59;
				static const int TVS_NOHSCROLL = 0x8000;
				static const int TVS_EX_AUTOHSCROLL = 0x0020;
				static const int TVS_EX_FADEINOUTEXPANDOS = 0x0040;
				static const int GWL_STYLE = -16;

			private:
				static const int PROCESS_INFORMATION_MEMORY_PRIORITY = 0x27;
				static const int PROCESS_INFORMATION_IO_PRIORITY = 0x21;
				static const int PRIORITY_MEMORY_NORMAL = 5;
				static const int PRIORITY_MEMORY_LOW = 3;
				static const int PRIORITY_IO_NORMAL = 2;
				static const int PRIORITY_IO_LOW = 1;
				static const unsigned int PROCESS_MODE_BACKGROUND_BEGIN = 0x00100000;
				static const unsigned int PROCESS_MODE_BACKGROUND_END = 0x00200000;
				static const int THREAD_MODE_BACKGROUND_BEGIN = 0x00010000;
				static const int THREAD_MODE_BACKGROUND_END = 0x00020000;

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("user32.dll", CharSet = CharSet::Unicode)]
			public:
				__declspec(dllimport) static int SendMessage(IntPtr hWnd, unsigned int Msg, int wParam, int lParam);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("user32", CharSet = CharSet::Unicode)]
				__declspec(dllimport) static IntPtr SendMessage(IntPtr hWnd, unsigned int Msg, IntPtr wParam, const QString &lParam);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("uxtheme.dll", CharSet = CharSet::Unicode)]
				__declspec(dllimport) static int SetWindowTheme(IntPtr hWnd, const QString &pszSubAppName, const QString &pszSubIdList);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("ntdll", CharSet = CharSet::Unicode)]
			private:
				__declspec(dllimport) static int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, int &processInformation, int processInformationLength);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("kernel32.dll", CharSet = CharSet::Unicode, SetLastError = true)]
				__declspec(dllimport) static bool SetPriorityClass(IntPtr handle, unsigned int priorityClass);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("Kernel32.dll", ExactSpelling = true)]
				__declspec(dllimport) static IntPtr GetCurrentThread();

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("Kernel32.dll", ExactSpelling = true), return: MarshalAs(UnmanagedType::Bool)]
				__declspec(dllimport) static bool SetThreadPriority(IntPtr hThread, int nPriority);


				// Various important window messages
			public:
				static const int WM_USER = 0x0400;
				static const int WM_ENTERIDLE = 0x0121;

				// FormatMessage constants and structs
				static const int FORMAT_MESSAGE_FROM_SYSTEM = 0x00001000;





				// Property System structs and consts

				static const unsigned int ERROR_CANCELLED = 0x800704C7;

			};
		}
	}
}
