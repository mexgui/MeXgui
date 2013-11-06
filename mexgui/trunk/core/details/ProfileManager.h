#pragma once

#include "MeGUI.Properties.Settings.h"
#include "video/VideoCodecSettings.h"
#include "packages/video/x264/x264Settings.h"
#include "packages/video/x264/MeGUI.packages.video.x264.x264ConfigurationPanel.h"
#include "packages/video/xvid/xvidSettings.h"
#include "packages/video/xvid/MeGUI.packages.video.xvid.xvidConfigurationPanel.h"
#include "packages/audio/AudioCodecSettings.h"
#include "packages/audio/aften/AftenSettings.h"
#include "packages/audio/aften/MeGUI.packages.audio.aften.AftenConfigurationPanel.h"
#include "packages/audio/ffac3/AC3Settings.h"
#include "packages/audio/ffac3/MeGUI.packages.audio.ffac3.AC3ConfigurationPanel.h"
#include "packages/audio/ffmp2/MP2Settings.h"
#include "packages/audio/ffmp2/MeGUI.packages.audio.ffmp2.MP2ConfigurationPanel.h"
#include "packages/audio/lame/MP3Settings.h"
#include "packages/audio/lame/MeGUI.packages.audio.lame.lameConfigurationPanel.h"
#include "packages/audio/naac/NeroAACSettings.h"
#include "packages/audio/naac/MeGUI.packages.audio.naac.neroConfigurationPanel.h"
#include "packages/audio/vorbis/OggVorbisSettings.h"
#include "packages/audio/vorbis/MeGUI.packages.audio.vorbis.OggVorbisConfigurationPanel.h"
#include "packages/audio/flac/FlacSettings.h"
#include "packages/audio/flac/MeGUI.packages.audio.flac.FlacConfigurationPanel.h"
#include "packages/audio/qaac/QaacSettings.h"
#include "packages/audio/qaac/MeGUI.packages.audio.qaac.qaacConfigurationPanel.h"
#include "packages/audio/opus/OpusSettings.h"
#include "packages/audio/opus/MeGUI.packages.audio.opus.OpusConfigurationPanel.h"
#include "packages/tools/oneclick/OneClickSettings.h"
#include "packages/tools/oneclick/MeGUI.packages.tools.oneclick.OneClickConfigPanel.h"
#include "packages/tools/avscreator/AviSynthSettings.h"
#include "packages/tools/avscreator/MeGUI.core.gui.AviSynthProfileConfigPanel.h"
#include "core/util/Util.h"
#include "core/plugins/interfaces/Profile.h"
#include "core/util/FileUtil.h"
#include "core/gui/StandardAndCustomComboBox.h"
#include "DialogManager.h"
#include "core/gui/Profiles.h"
#include "core/util/GenericRegisterer.h"
#include "core/util/Tuples.h"
#include "core/util/LogItem.h"
#include "core/gui/MeGUI.core.gui.ProfileConfigurationWindow - generic 2.h"
#include <string>
#include <vector>
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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::gui;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::tools::oneclick;
using namespace MeGUI::packages::video::x264;

namespace MeGUI
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
		ProfileManager(const std::string &path);

		static const std::string ScratchPadName;

	private:
		std::string path;
		std::vector<ProfileType*> profileTypes;
		std::vector<ProfileGroup*> profileGroups;



    public:
//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
		template<typename TSettings, typename TPanel> where TSettings : GenericSettings, new() where TPanel : Control, Editable<TSettings>, new()
//ORIGINAL LINE: public bool SafeRegister<TSettings, TPanel>(params string[] groups) where TSettings : GenericSettings, new() where TPanel : Control, Editable<TSettings>, new()
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		bool SafeRegister(...);

		bool Register(Type *TSettings, Type *TPanel, const std::string &name);

		/// <summary>
		/// eliminates non allowed characters and replaced them with an underscore
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
	private:
		static std::string fixName(const std::string &name);

		ProfileGroup *groupByName(const std::string &name);

		ProfileType *byName(const std::string &name);

		ProfileType *bySettingsType(Type *t);

		Type *profileType(const std::string &id);

		static std::string profilePath(const std::string &path, Profile *prof);

		static const std::string SaveFolderName;

	public:
		static std::string GetSaveFolder(const std::string &path);

		/// <summary>
		/// saves all the profiles
		/// this is called when the program exists and ensures that all
		/// currently defined profiles are saved, overwriting currently existing ones
		/// </summary>
		static void WriteProfiles(const std::string &path, IEnumerable<Profile*> *profiles);

		void SaveProfiles();

	private:
		void saveSelectedProfiles();

		void loadSelectedProfiles();

#warning delete block some months after the next stable release
		void deleteDeprecatedEntries(const std::string &strFile);

	public:
		void LoadProfiles();

		static std::vector<Profile*> ReadAllProfiles(const std::string &path, bool bSilentError);

	private:
		std::vector<Profile*> readAllProfiles(ProfileType *type, bool bSilentError);

		void setAllProfiles(std::vector<Profile*> &ps);

	public:
		Profile *GetSelectedProfile(const std::string &profileType);

		void SetSelectedProfile(Profile *prof);

		Profile *GetProfile(const std::string &type, const std::string &name);

	private:
		std::vector<ProfileType*> byProfileSet(const std::string &profileSet);

	public:
		IEnumerable<Named<Profile*>*> *Profiles(const std::string &type);

		void AddProfilesChangedListener(const std::string &profileSet, EventHandler *listener);

		void RemoveProfilesChangedListener(const std::string &profileSet, EventHandler *listener);

	private:
		Profile *byFormattedName(const std::string &formattedName);

	public:
		const Profile *getAllProfiles() const;

		void AddAll(Profile profiles[], DialogManager *asker);


	private:
		static Type *GetSettingsType(Profile *p);

	public:
		void Configure(Profile *SelectedProfile);

		void SetSettings(GenericSettings *s);

		GenericSettings *GetCurrentSettings(const std::string &p);

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
		const std::string profileTypeID;

	public:
		const std::string &getID() const;

		const Tuple<IEnumerable<Profile*>*, Profile*> &getProfilesAndSelected() const;
		void setProfilesAndSelected(const Tuple<IEnumerable<Profile*>*, Profile*> &value);

		const IEnumerable<Profile*> &getProfiles() const;
		void setProfiles(const IEnumerable<Profile*> &value);

	private:
		void raiseChangedEvent();

	protected:
		std::vector<Profile*> profiles;

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

		ProfileType(const std::string &name);

		Profile *ByName(const std::string &name);

	private:
		int indexOf(const std::string &name);

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
		SpecificProfileType(const std::string &name) : ProfileType(name)
		{
		}

		const virtual Type &getSettingsType() const
		{
			return TSettings::typeid;
		}

		GenericProfile<TSettings> *SByName(const std::string &name)
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
			if (w->ShowDialog() == DialogResult::Cancel)
				return;

			setSProfiles(w->getProfiles());
		}

		SpecificProfileType(const std::string &name) : SpecificProfileType(name)
		{
		}
	};

	class ProfileGroup : public IIDable
	{
	private:
		const std::string profileGroupID;

	public:
		const std::string &getID() const;

		std::vector<std::string> ChildIDs;
		Type *const CommonType;
		std::string SelectedChild;

		ProfileGroup(Type *t, const std::string &name);

		void Register(ProfileType *t, const std::string &childID, Type *childType);

	private:
		void InitializeInstanceFields();
	};

}
