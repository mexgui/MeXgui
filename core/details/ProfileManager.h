#pragma once

#include "MeXgui.Properties.Settings.h"
#include "video/VideoCodecSettings.h"
#include "packages/video/x264/x264Settings.h"
#include "packages/video/x264/MeXgui.packages.video.x264.x264ConfigurationPanel.h"
#include "packages/video/xvid/xvidSettings.h"
#include "packages/video/xvid/MeXgui.packages.video.xvid.xvidConfigurationPanel.h"
#include "packages/audio/AudioCodecSettings.h"
#include "packages/audio/aften/AftenSettings.h"
#include "packages/audio/aften/MeXgui.packages.audio.aften.AftenConfigurationPanel.h"
#include "packages/audio/ffac3/AC3Settings.h"
#include "packages/audio/ffac3/MeXgui.packages.audio.ffac3.AC3ConfigurationPanel.h"
#include "packages/audio/ffmp2/MP2Settings.h"
#include "packages/audio/ffmp2/MeXgui.packages.audio.ffmp2.MP2ConfigurationPanel.h"
#include "packages/audio/lame/MP3Settings.h"
#include "packages/audio/lame/MeXgui.packages.audio.lame.lameConfigurationPanel.h"
#include "packages/audio/naac/NeroAACSettings.h"
#include "packages/audio/naac/MeXgui.packages.audio.naac.neroConfigurationPanel.h"
#include "packages/audio/vorbis/OggVorbisSettings.h"
#include "packages/audio/vorbis/MeXgui.packages.audio.vorbis.OggVorbisConfigurationPanel.h"
#include "packages/audio/flac/FlacSettings.h"
#include "packages/audio/flac/MeXgui.packages.audio.flac.FlacConfigurationPanel.h"
#include "packages/audio/qaac/QaacSettings.h"
#include "packages/audio/qaac/MeXgui.packages.audio.qaac.qaacConfigurationPanel.h"
#include "packages/audio/opus/OpusSettings.h"
#include "packages/audio/opus/MeXgui.packages.audio.opus.OpusConfigurationPanel.h"
#include "packages/tools/oneclick/OneClickSettings.h"
#include "packages/tools/oneclick/MeXgui.packages.tools.oneclick.OneClickConfigPanel.h"
#include "packages/tools/avscreator/AviSynthSettings.h"
#include "packages/tools/avscreator/MeXgui.AviSynthProfileConfigPanel.h"
#include "core/util/Util.h"
#include "core/plugins/interfaces/Profile.h"
#include "core/util/FileUtil.h"
#include "core/gui/StandardAndCustomComboBox.h"
#include "DialogManager.h"
#include "core/gui/Profiles.h"
#include "core/util/GenericRegisterer.h"
#include "core/util/Tuples.h"
#include "core/util/LogItem.h"
#include "core/gui/MeXgui.ProfileConfigurationWindow - generic 2.h"
#include <QString>
#include <QVector>
#include <algorithm>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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



//using namespace System::Reflection;

//using namespace System::Xml::Serialization;

//using namespace System::Text;

//using namespace System::Text::RegularExpressions;



using namespace MeXgui::core::gui;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::oneclick;
using namespace MeXgui::packages::video::x264;

namespace MeXgui
{
	template<typename TSettings>
	class Editable
	{
	public:
		virtual const TSettings &getSettings() const = 0;
		virtual void setSettings(const TSettings&) = 0;
	};

	class ProfileManager
	{
	public:
		ProfileManager(const QString &path);

		static const QString ScratchPadName;

	private:
		QString path;
		QVector<ProfileType*> profileTypes;
		QVector<ProfileGroup*> profileGroups;



    public:
//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
		template<typename TSettings, typename TPanel> where TSettings : GenericSettings, new() where TPanel : Control, Editable<TSettings>, new()
//ORIGINAL LINE: public bool SafeRegister<TSettings, TPanel>(params string[] groups) where TSettings : GenericSettings, new() where TPanel : Control, Editable<TSettings>, new()
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		bool SafeRegister(...);

		bool Register(Type *TSettings, Type *TPanel, const QString &name);

		/// <summary>
		/// eliminates non allowed characters and replaced them with an underscore
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
	private:
		static QString fixName(const QString &name);

		ProfileGroup *groupByName(const QString &name);

		ProfileType *byName(const QString &name);

		ProfileType *bySettingsType(Type *t);

		Type *profileType(const QString &id);

		static QString profilePath(const QString &path, Profile *prof);

		static const QString SaveFolderName;

	public:
		static QString GetSaveFolder(const QString &path);

		/// <summary>
		/// saves all the profiles
		/// this is called when the program exists and ensures that all
		/// currently defined profiles are saved, overwriting currently existing ones
		/// </summary>
		static void WriteProfiles(const QString &path, IEnumerable<Profile*> *profiles);

		void SaveProfiles();

	private:
		void saveSelectedProfiles();

		void loadSelectedProfiles();

#warning delete block some months after the next stable release
		void deleteDeprecatedEntries(const QString &strFile);

	public:
		void LoadProfiles();

		static QVector<Profile*> ReadAllProfiles(const QString &path, bool bSilentError);

	private:
		QVector<Profile*> readAllProfiles(ProfileType *type, bool bSilentError);

		void setAllProfiles(QVector<Profile*> &ps);

	public:
		Profile *GetSelectedProfile(const QString &profileType);

		void SetSelectedProfile(Profile *prof);

		Profile *GetProfile(const QString &type, const QString &name);

	private:
		QVector<ProfileType*> byProfileSet(const QString &profileSet);

	public:
		IEnumerable<Named<Profile*>*> *Profiles(const QString &type);

		void AddProfilesChangedListener(const QString &profileSet, EventHandler *listener);

		void RemoveProfilesChangedListener(const QString &profileSet, EventHandler *listener);

	private:
		Profile *byFormattedName(const QString &formattedName);

	public:
		const Profile *getAllProfiles() const;

		void AddAll(Profile profiles[], DialogManager *asker);


	private:
		static Type *GetSettingsType(Profile *p);

	public:
		void Configure(Profile *SelectedProfile);

		void SetSettings(GenericSettings *s);

		GenericSettings *GetCurrentSettings(const QString &p);

	private:
		void InitializeInstanceFields();
	};

	class ProfileType : public IIDable
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler SelectedProfileSet;
//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler ProfilesChanged;

	private:
		const QString profileTypeID;

	public:
		const QString &getID() const;

		const Tuple<IEnumerable<Profile*>*, Profile*> &getProfilesAndSelected() const;
		void setProfilesAndSelected(const Tuple<IEnumerable<Profile*>*, Profile*> &value);

		const IEnumerable<Profile*> &getProfiles() const;
		void setProfiles(const IEnumerable<Profile*> &value);

	private:
		void raiseChangedEvent();

	protected:
		QVector<Profile*> profiles;

		virtual Profile *genScratchpad() = 0;

	private:
		Profile *selectedProfile;
	public:
		const Profile &getSelectedProfile() const;
		void setSelectedProfile(const Profile &value);

		void SetSettings(GenericSettings *s);

		virtual void ConfigureProfiles() = 0;

		virtual const Type &getSettingsType() const = 0;

		const Type &getGenericProfileType() const;

		ProfileType(const QString &name);

		Profile *ByName(const QString &name);

	private:
		int indexOf(const QString &name);

	public:
		void Add(Profile *prof, DialogManager *asker);

	private:
		void InitializeInstanceFields();
	};

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
	template<typename TSettings> where TSettings : GenericSettings, new()
	class SpecificProfileType : public ProfileType
	{
	public:
		SpecificProfileType(const QString &name) : ProfileType(name)
		{
		}

		const virtual Type &getSettingsType() const
		{
			return TSettings::typeid;
		}

		GenericProfile<TSettings> *SByName(const QString &name)
		{
			return static_cast<GenericProfile<TSettings>*>(ByName(name));
		}

		const Tuple<IEnumerable<GenericProfile<TSettings>*>*, GenericProfile<TSettings>*> &getSProfiles() const
		{
			Tuple<IEnumerable<Profile*>*, Profile*> *p = getProfilesAndSelected();

			return new Tuple<IEnumerable<GenericProfile<TSettings>*>*, GenericProfile<TSettings>*>(Util::CastAll<Profile*, GenericProfile<TSettings>*>(p->a), static_cast<GenericProfile<TSettings>*>(p->b));
		}
		void setSProfiles(const Tuple<IEnumerable<GenericProfile<TSettings>*>*, GenericProfile<TSettings>*> &value)
		{
			setProfilesAndSelected(new Tuple<IEnumerable<Profile*>*, Profile*>(Util::CastAll<GenericProfile<TSettings>*, Profile*>(value->a), value->b));
		}

		const GenericProfile<TSettings> &getSSelectedProfile() const
		{
			return static_cast<GenericProfile<TSettings>*>(getSelectedProfile());
		}
		void setSSelectedProfile(const GenericProfile<TSettings> &value)
		{
			setSelectedProfile(value);
		}

	protected:
		virtual Profile *genScratchpad()
		{
			return new GenericProfile<TSettings>(ProfileManager::ScratchPadName, new TSettings());
		}
	};

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
	template<typename TSettings, typename TPanel> where TSettings : GenericSettings, new() where TPanel : Control, Editable<TSettings>, new()
	class SpecificProfileType : public SpecificProfileType<TSettings>
	{
	public:
		virtual void ConfigureProfiles()
		{
			// used to init with mainForm, but that is not required any more. OTOH, a ProfileManager instance might be required
			TPanel t = new TPanel();
			ProfileConfigurationWindow<TSettings, TPanel> *w = new ProfileConfigurationWindow<TSettings, TPanel>(t, getID());
			w->setProfiles(getSProfiles());
			if (w->show() == DialogResult::Cancel)
				return;

			setSProfiles(w->getProfiles());
		}

		SpecificProfileType(const QString &name) : SpecificProfileType(name)
		{
		}
	};

	class ProfileGroup : public IIDable
	{
	private:
		const QString profileGroupID;

	public:
		const QString &getID() const;

		QVector<QString> ChildIDs;
		Type *const CommonType;
		QString SelectedChild;

		ProfileGroup(Type *t, const QString &name);

		void Register(ProfileType *t, const QString &childID, Type *childType);

	private:
		void InitializeInstanceFields();
	};

}
