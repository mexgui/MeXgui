#pragma once

#include "core/gui/Profiles.h"
#include "OneClickAudioControl.h"
#include "core/util/FileSize.h"
#include "core/gui/MeXgui.MainForm.h"
#include "packages/tools/fileindexer/MeXgui.FileIndexerWindow.h"
#include "core/plugins/interfaces/Profile.h"
#include <QString>
#include <QMap>
#include <QVector>

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




//using namespace System::Collections::Generic;

//using namespace System::Xml::Serialization;

using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;

namespace MeXgui
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
		QString videoProfileName;
	public:
		const QString &getVideoProfileName() const;
		void setVideoProfileName(const QString &value);

	private:
		QString avsProfileName;
	public:
		const QString &getAvsProfileName() const;
		void setAvsProfileName(const QString &value);

	private:
		bool prerenderVideo;
	public:
		const bool &getPrerenderVideo() const;
		void setPrerenderVideo(const bool &value);

	private:
		QString audioProfileName;
	public:
		const QString &getAudioProfileName() const;
		void setAudioProfileName(const QString &value);

		// for profile import/export in case the enum changes
		const QString &getAudioEncodingModeString() const;
		void setAudioEncodingModeString(const QString &value);

	private:
		QVector<OneClickAudioSettings*> audioSettings;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore(), PropertyEqualityIgnoreAttribute()]
		const QVector<OneClickAudioSettings*> &getAudioSettings() const;
		void setAudioSettings(const QVector<OneClickAudioSettings*> &value);

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
		qint64 outputResolution;
	public:
		const qint64 &getOutputResolution() const;
		void setOutputResolution(const qint64 &value);

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
		QString *containerCandidates;
	public:
		const QString *getContainerCandidates() const;
		void setContainerCandidates(QString value[]);

	private:
		QString deviceType;
	public:
		const QString &getDeviceOutputType() const;
		void setDeviceOutputType(const QString &value);

	private:
		QString leadingName;
	public:
		const QString &getLeadingName() const;
		void setLeadingName(const QString &value);

	private:
		QString workingNameReplace;
	public:
		const QString &getWorkingNameReplace() const;
		void setWorkingNameReplace(const QString &value);

	private:
		QString workingNameReplaceWith;
	public:
		const QString &getWorkingNameReplaceWith() const;
		void setWorkingNameReplaceWith(const QString &value);

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
		QString defaultWorkingDirectory;
	public:
		const QString &getDefaultWorkingDirectory() const;
		void setDefaultWorkingDirectory(const QString &value);

	private:
		QString defaultOutputDirectory;
	public:
		const QString &getDefaultOutputDirectory() const;
		void setDefaultOutputDirectory(const QString &value);

	private:
		QString defaultLanguage;
	public:
		const QString &getDefaultLanguage() const;
		void setDefaultLanguage(const QString &value);

	private:
		QVector<QString> defaultAudioLanguage;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore(), PropertyEqualityIgnoreAttribute()]
		const QVector<QString> &getDefaultAudioLanguage() const;
		void setDefaultAudioLanguage(const QVector<QString> &value);

		const QString *getDefaultAudioLanguageString() const;
		void setDefaultAudioLanguageString(QString value[]);

	private:
		QVector<QString> defaultSubtitleLanguage;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore(), PropertyEqualityIgnoreAttribute()]
		const QVector<QString> &getDefaultSubtitleLanguage() const;
		void setDefaultSubtitleLanguage(const QVector<QString> &value);

		const QString *getDefaultSubtitleLanguageString() const;
		void setDefaultSubtitleLanguageString(QString value[]);

	private:
		QVector<QString> indexerPriority;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[XmlIgnore(), PropertyEqualityIgnoreAttribute()]
		const QVector<QString> &getIndexerPriority() const;
		void setIndexerPriority(const QVector<QString> &value);

		const QString *getIndexerPriorityString() const;
		void setIndexerPriorityString(QString value[]);

		OneClickSettings();


		const QString &getSettingsID() const;
		virtual void FixFileNames(QMap<QString, QString> &_);

		virtual bool Equals(object *obj);

		bool Equals(GenericSettings *other);

		virtual int GetHashCode();

	private:
		object *ICloneable_Clone();

		GenericSettings *GenericSettings_Clone();

	public:
		OneClickSettings *Clone();

		const QString *getRequiredFiles() const;

		const QString *getRequiredProfiles() const;

	};
}
