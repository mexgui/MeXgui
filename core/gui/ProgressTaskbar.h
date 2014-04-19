#pragma once

#include <QString>

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
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




//using namespace System::Runtime::InteropServices;

namespace MeXgui
{
	/// <summary>
	/// ProgressTaskbar provides Windows 7 taskbar progress
	/// </summary>

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[ComImportAttribute(), GuidAttribute("ea1afb91-9e28-4b86-90e9-9e9f8a5eefaf"), InterfaceTypeAttribute(ComInterfaceType::InterfaceIsIUnknown)]
	class ITaskbarList3
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual void HrInit() = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual void AddTab(IntPtr) = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual void DeleteTab(IntPtr) = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual void ActivateTab(IntPtr) = 0;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual void SetActiveAlt(IntPtr) = 0;

//ORIGINAL LINE: void MarkFullscreenWindow(IntPtr hwnd, [MarshalAs(UnmanagedType.Bool)] bool fFullscreen);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[PreserveSig]
		virtual void MarkFullscreenWindow(IntPtr, bool) = 0;

		virtual void SetProgressValue(IntPtr, quint64, quint64) = 0;
		virtual void SetProgressState(IntPtr, TBPFLAG) = 0;
		virtual void RegisterTab(IntPtr, IntPtr) = 0;
		virtual void UnregisterTab(IntPtr) = 0;
		virtual void SetTabOrder(IntPtr, IntPtr) = 0;
		virtual void SetTabActive(IntPtr, IntPtr, TBATFLAG) = 0;
//ORIGINAL LINE: void ThumbBarAddButtons(IntPtr hwnd, uint cButtons, [MarshalAs(UnmanagedType.LPArray)] THUMBBUTTON[] pButtons);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		virtual void ThumbBarAddButtons(IntPtr, unsigned int, THUMBBUTTON[]) = 0;
//ORIGINAL LINE: void ThumbBarUpdateButtons(IntPtr hwnd, uint cButtons, [MarshalAs(UnmanagedType.LPArray)] THUMBBUTTON[] pButtons);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		virtual void ThumbBarUpdateButtons(IntPtr, unsigned int, THUMBBUTTON[]) = 0;
		virtual void ThumbBarSetImageList(IntPtr, IntPtr) = 0;
//ORIGINAL LINE: void SetOverlayIcon(IntPtr hwnd, IntPtr hIcon, [MarshalAs(UnmanagedType.LPWStr)] string pszDescription);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		virtual void SetOverlayIcon(IntPtr, IntPtr, const QString&) = 0;
//ORIGINAL LINE: void SetThumbnailTooltip(IntPtr hwnd, [MarshalAs(UnmanagedType.LPWStr)] string pszTip);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
		virtual void SetThumbnailTooltip(IntPtr, const QString&) = 0;
		virtual void SetThumbnailClip(IntPtr, RECT&) = 0;
	};
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[GuidAttribute("56FDF344-FD6D-11d0-958A-006097C9A090"), ClassInterfaceAttribute(ClassInterfaceType::None), ComImportAttribute()]
	class ProgressTaskbar
	{
	};
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential, CharSet = CharSet::Auto)]
	class THUMBBUTTON
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::U4)]
		THBMASK dwMask;
		unsigned int iId;
		unsigned int iBitQMap;
		void* hIcon;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::ByValTStr, SizeConst = 260)]
		QString szTip;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::U4)]
		THBFLAGS dwFlags;
	};
	enum THBMASK
	{
		THB_BITQMap = 0x1,
		THB_ICON = 0x2,
		THB_TOOLTIP = 0x4,
		THB_FLAGS = 0x8
	};

	enum THBFLAGS
	{
		THBF_ENABLED = 0,
		THBF_DISABLED = 0x1,
		THBF_DISMISSONCLICK = 0x2,
		THBF_NOBACKGROUND = 0x4,
		THBF_HIDDEN = 0x8
	};
	enum TBPFLAG
	{
		TBPF_NOPROGRESS = 0,
		TBPF_INDETERMINATE = 0x1,
		TBPF_NORMAL = 0x2,
		TBPF_ERROR = 0x4,
		TBPF_PAUSED = 0x8
	};
	enum TBATFLAG
	{
		TBATF_USEMDITHUMBNAIL = 0x1,
		TBATF_USEMDILIVEPREVIEW = 0x2
	};
	class RECT
	{
	public:
		int left;
		int top;
		int right;
		int bottom;

		RECT(int left, int top, int right, int bottom);
	};
}
