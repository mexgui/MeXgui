#pragma once

#include "core/gui/Profiles.h"
#include "OneClickAudioControl.h"
#include "core/util/FileSize.h"
#include "core/gui/MeGUI.MainForm.h"
#include "packages/tools/fileindexer/MeGUI.FileIndexerWindow.h"
#include "core/plugins/interfaces/Profile.h"
#include <string>
#include <map>
#include <vector>

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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;

using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;

namespace MeGUI
{
	enum AudioEncodingMode
	{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("always")]
		Always,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("if codec does not match")]
		IfCodecDoesNotMatch,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("never, but use only the core of HD tracks")]
		NeverOnlyCore,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("never")]
		Never
	};

	/// <summary>
	/// Summary description for OneClickDefaults.
	/// </summary>
	class OneClickSettings : public GenericSettings
	{
	public:
		static const AudioEncodingMode SupportedModes[4];

	private:
		std::string videoProfileName;
	public:
		const std::string &getVideoProfileName() const;
		void setVideoProfileName(const std::string &value);

	private:
		std::string avsProfileName;
	public:
		const std::string &getAvsProfileName() const;
		void setAvsProfileName(const std::string &value);

	private:
		bool prerenderVideo;
	public:
		const bool &getPrerenderVideo() const;
		void setPrerenderVideo(const bool &value);

	private:
		std::string audioProfileName;
	public:
		const std::string &getAudioProfileName() const;
		void setAudioProfileName(const std::string &value);

		// for profile import/export in case the enum changes
		const std::string &getAudioEncodingModeString() const;
		void setAudioEncodingModeString(const std::string &value);

	private:
		std::vector<OneClickAudioSettings*> audioSettings;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore(), PropertyEqualityIgnoreAttribute()]
		const std::vector<OneClickAudioSettings*> &getAudioSettings() const;
		void setAudioSettings(const std::vector<OneClickAudioSettings*> &value);

		const OneClickAudioSettings *getAudioSettingsString() const;
		void setAudioSettingsString(OneClickAudioSettings value[]);

	private:
		bool dontEncodeVideo;
	public:
		const bool &getDontEncodeVideo() const;
		void setDontEncodeVideo(const bool &value);

	private:
		bool signalAR;
	public:
		const bool &getSignalAR() const;
		void setSignalAR(const bool &value);

	private:
		bool automaticDeinterlacing;
	public:
		const bool &getAutomaticDeinterlacing() const;
		void setAutomaticDeinterlacing(const bool &value);

	private:
		bool autoCrop;
	public:
		const bool &getAutoCrop() const;
		void setAutoCrop(const bool &value);

	private:
		bool keepInputResolution;
	public:
		const bool &getKeepInputResolution() const;
		void setKeepInputResolution(const bool &value);

	private:
		long long outputResolution;
	public:
		const long long &getOutputResolution() const;
		void setOutputResolution(const long long &value);

	private:
		Nullable<FileSize> filesize;
	public:
		const Nullable<FileSize> &getFilesize() const;
		void setFilesize(const Nullable<FileSize> &value);

	private:
		Nullable<FileSize> splitSize;
	public:
		const Nullable<FileSize> &getSplitSize() const;
		void setSplitSize(const Nullable<FileSize> &value);

	private:
//ORIGINAL LINE: private string[] containerCandidates;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		std::string *containerCandidates;
	public:
		const std::string *getContainerCandidates() const;
		void setContainerCandidates(std::string value[]);

	private:
		std::string deviceType;
	public:
		const std::string &getDeviceOutputType() const;
		void setDeviceOutputType(const std::string &value);

	private:
		std::string leadingName;
	public:
		const std::string &getLeadingName() const;
		void setLeadingName(const std::string &value);

	private:
		std::string workingNameReplace;
	public:
		const std::string &getWorkingNameReplace() const;
		void setWorkingNameReplace(const std::string &value);

	private:
		std::string workingNameReplaceWith;
	public:
		const std::string &getWorkingNameReplaceWith() const;
		void setWorkingNameReplaceWith(const std::string &value);

	private:
		bool useChaptersMarks;
	public:
		const bool &getUseChaptersMarks() const;
		void setUseChaptersMarks(const bool &value);

	private:
		bool useNoLanguagesAsFallback;
	public:
		const bool &getUseNoLanguagesAsFallback() const;
		void setUseNoLanguagesAsFallback(const bool &value);

	private:
		bool disableIntermediateMKV;
	public:
		const bool &getDisableIntermediateMKV() const;
		void setDisableIntermediateMKV(const bool &value);

	private:
		std::string defaultWorkingDirectory;
	public:
		const std::string &getDefaultWorkingDirectory() const;
		void setDefaultWorkingDirectory(const std::string &value);

	private:
		std::string defaultOutputDirectory;
	public:
		const std::string &getDefaultOutputDirectory() const;
		void setDefaultOutputDirectory(const std::string &value);

	private:
		std::string defaultLanguage;
	public:
		const std::string &getDefaultLanguage() const;
		void setDefaultLanguage(const std::string &value);

	private:
		std::vector<std::string> defaultAudioLanguage;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore(), PropertyEqualityIgnoreAttribute()]
		const std::vector<std::string> &getDefaultAudioLanguage() const;
		void setDefaultAudioLanguage(const std::vector<std::string> &value);

		const std::string *getDefaultAudioLanguageString() const;
		void setDefaultAudioLanguageString(std::string value[]);

	private:
		std::vector<std::string> defaultSubtitleLanguage;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore(), PropertyEqualityIgnoreAttribute()]
		const std::vector<std::string> &getDefaultSubtitleLanguage() const;
		void setDefaultSubtitleLanguage(const std::vector<std::string> &value);

		const std::string *getDefaultSubtitleLanguageString() const;
		void setDefaultSubtitleLanguageString(std::string value[]);

	private:
		std::vector<std::string> indexerPriority;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore(), PropertyEqualityIgnoreAttribute()]
		const std::vector<std::string> &getIndexerPriority() const;
		void setIndexerPriority(const std::vector<std::string> &value);

		const std::string *getIndexerPriorityString() const;
		void setIndexerPriorityString(std::string value[]);

		OneClickSettings();


		const std::string &getSettingsID() const;
		virtual void FixFileNames(std::map<std::string, std::string> &_);

		virtual bool Equals(object *obj);

		bool Equals(GenericSettings *other);

		virtual int GetHashCode();

	private:
		object *ICloneable_Clone();

		GenericSettings *GenericSettings_Clone();

	public:
		OneClickSettings *Clone();

		const std::string *getRequiredFiles() const;

		const std::string *getRequiredProfiles() const;

	};
}
