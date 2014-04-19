#pragma once

#include "core/plugins/interfaces/IPackage.h"
#include "core/gui/MainForm.h"
#include "core/util/DAR.h"
#include "packages/video/x264/x264Settings.h"
#include "core/util/JobUtil.h"
#include <QString>
#include <cmath>

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






namespace MeXgui
{
	class AVCLevelTool : public MeXgui::core::plugins::interfaces::ITool
	{


	public:
		const QString &getName() const;

		void Run(MainForm *info);

		const Shortcut *getShortcuts() const;



		const QString &getID() const;

	};

	/// <summary>
	/// Summary description for AVCLevels.
	/// akupenguin http://forum.doom9.org/showthread.php?p=730001#post730001
	/// These are the properties listed in the levels tables in the standard, and how they should limit x264 settings:
	/// MaxMBPS >= width*height*fps. (w&h measured in macroblocks, i.e. pixels/16 round up in each dimension)
	/// MaxFS >= width*height
	/// sqrt(MaxFS*8) >= width
	/// sqrt(MaxFS*8) >= height
	/// MaxDPB >= (bytes in a frame) * min(16, ref)
	/// MaxBR >= vbv_maxrate. It isn't strictly required since we don't write the VCL HRD parameters, but this satisfies the intent.
	/// MaxCPB >= vbv_bufsize. Likewise.
	/// MaxVmvR >= max_mv_range. (Not exposed in the cli, I'll add it if people care.)
	/// MaxMvsPer2Mb, MinLumaBiPredSize, direct_8x8_inference_flag : are not enforced by x264. The only way to ensure compliance is to disable p4x4 at level>=3.1, or at level>=3 w/ B-frames.
	/// MinCR : is not enforced by x264. Won't ever be an issue unless you use lossless.
	/// SliceRate : I don't know what this limits.
	/// </summary>
	class AVCLevels
	{
	public:
		enum Levels
		{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 1")]
			L_10,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 1b")]
			L_1B,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 1.1")]
			L_11,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 1.2")]
			L_12,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 1.3")]
			L_13,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 2")]
			L_20,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 2.1")]
			L_21,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 2.2")]
			L_22,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 3")]
			L_30,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 3.1")]
			L_31,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 3.2")]
			L_32,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 4")]
			L_40,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 4.1")]
			L_41,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 4.2")]
			L_42,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 5")]
			L_50,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 5.1")]
			L_51,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Level 5.2")]
			L_52,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Unrestricted/Autoguess")]
			L_UNRESTRICTED
		};

	public:
		static const Levels SupportedLevels[18];

		/// <summary>
		/// gets the level number as text
		/// </summary>
		/// <param name="avcLevel">the level</param>
		/// <returns>the level number</returns>
		static QString GetLevelText(Levels avcLevel);

		/// <summary>
		/// Check functions to verify elements of the level
		/// </summary>
		/// <param name="level"></param>
		/// <param name="settings"></param>
		/// <returns>true if the settings are compliant with the level</returns>
	private:
		bool checkP4x4Enabled(Levels avcLevel, x264Settings *settings);

		bool checkP4x4(Levels avcLevel, x264Settings *settings);

		double pictureBufferSize(x264Settings *settings, double bytesInUncompressedFrame);

		bool checkMaxDPB(Levels avcLevel, x264Settings *settings, double bytesInUncompressedFrame);

		int macroblocks(int res);

		double maxFS(int hRes, int vRes);

		int maxBPS(int hres, int vres, double framerate);
	public:
		double bytesPerFrame(int hres, int vres);
		AVCLevels();
		/// <summary>
		/// gets the MaxCBP value corresponding to a given AVC Level
		/// </summary>
		/// <param name="level">the level</param>
		/// <returns>the MaxCBP in kbit/s</returns>
		int getMaxCBP(Levels avcLevel, bool isHighProfile);

		/// <summary>
		/// gets the maxBR rate in bits for a given level
		/// </summary>
		/// <param name="level">the level</param>
		/// <returns>the MaxBR in bits</returns>
		int getMaxBR(Levels avcLevel, bool isHighProfile);

		/// <summary>
		/// gets the Maximum macroblock rate given a level
		/// </summary>
		/// <param name="level">the level</param>
		/// <returns>the macroblock rate</returns>
		int getMaxMBPS(Levels avcLevel);

		/// <summary>
		/// gets the maximum framesize given a level
		/// </summary>
		/// <param name="level">the level</param>
		/// <returns>the maximum framesize in number of macroblocks
		/// (1MB = 16x16)</returns>
		int getMaxFS(Levels avcLevel);

		/// <summary>
		/// gets the maximum picture decoded buffer for the given level 
		/// </summary>
		/// <param name="level">the level</param>
		/// <returns>the size of the decoding buffer in bytes</returns>
		double getMaxDPB(Levels avcLevel);

		/// <summary>
		/// Verifies a group of x264Settings against an AVC Level 
		/// </summary>
		/// <param name="settings">the x264Settings to test</param>
		/// <param name="level">the level</param>
		/// <param name="bytesInUncompressedFrame">Number of bytes in an uncompressed frame</param>
		/// <returns>   0 if the settings are compliant with the level
		///             1 if (level > 3 || level = 3 AND Bframes > 0)
		///             2 if maxDPB violated</returns>
		int Verifyx264Settings(x264Settings *settings, AVCLevels::Levels avcLevel, double bytesInUncompressedFrame);

		/// <summary>
		/// Checks a collection of x264Settings and modifies them if needed to fit within the level constraints.
		/// </summary>
		/// <param name="level">the level to enforce</param>
		/// <param name="inputSettings">the collection of x264Settings to check</param>
		/// <param name="frameSize">the size of the decoded video frame in bytes</param>
		/// <returns>A compliant set of x264Settings</returns>
		x264Settings *EnforceSettings(AVCLevels::Levels avcLevel, x264Settings *inputSettings, double frameSize, AVCLevelEnforcementReturn *&enforcement);

		/// <summary>
		/// validates a source against a given AVC level taking into account the source properties and the x264 settings
		/// </summary>
		/// <param name="bytesPerFrame">bytesize of a single frame</param>
		/// <param name="FS">frame area in pixels</param>
		/// <param name="MBPS">macroblocks per second</param>
		/// <param name="settings">the codec config to test</param>
		/// <param name="compliantLevel">the first avc level that can be used to encode this source</param>
		/// <returns>whether or not the current level is okay, if false and compliantLevel is -1, 
		/// the source could not be read</returns>
		bool validateAVCLevel(int hRes, int vRes, double framerate, x264Settings *settings, Nullable<AVCLevels::Levels> &compliantLevel);

	};
	class AVCLevelEnforcementReturn
	{
	private:
		bool enableP4x4mv, enableVBVBufferSize, enableVBVMaxRate, altered;
		bool panic; // Panic! Something failed and the level was reset to unrestrained
		QString panicString; // Description of the error that caused the panic

	public:
		AVCLevelEnforcementReturn();
		const bool &getEnableP4x4mv() const;
		void setEnableP4x4mv(const bool &value);
		const bool &getEnableVBVBufferSize() const;
		void setEnableVBVBufferSize(const bool &value);
		const bool &getEnableVBVMaxRate() const;
		void setEnableVBVMaxRate(const bool &value);
		const bool &getAltered() const;
		void setAltered(const bool &value);
		const bool &getPanic() const;
		void setPanic(const bool &value);
		const QString &getPanicString() const;
		void setPanicString(const QString &value);
	};
}
