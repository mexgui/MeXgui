#include "ProfileManager.h"

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

	ProfileManager::ProfileManager(const std::string &path)
	{
		InitializeInstanceFields();
		this->path = path;
		profileGroups.push_back(new ProfileGroup(VideoCodecSettings::typeid, "Video"));
		SafeRegister<x264Settings*, x264ConfigurationPanel*>("Video");
		SafeRegister<xvidSettings*, MeGUI::packages::video::xvid::xvidConfigurationPanel*>("Video");
		profileGroups.push_back(new ProfileGroup(AudioCodecSettings::typeid, "Audio"));
		SafeRegister<AftenSettings*, MeGUI::packages::audio::aften::AftenConfigurationPanel*>("Audio");
		SafeRegister<AC3Settings*, MeGUI::packages::audio::ffac3::AC3ConfigurationPanel*>("Audio");
		SafeRegister<MP2Settings*, MeGUI::packages::audio::ffmp2::MP2ConfigurationPanel*>("Audio");
		SafeRegister<MP3Settings*, MeGUI::packages::audio::lame::lameConfigurationPanel*>("Audio");
		SafeRegister<NeroAACSettings*, MeGUI::packages::audio::naac::neroConfigurationPanel*>("Audio");
		SafeRegister<OggVorbisSettings*, MeGUI::packages::audio::vorbis::OggVorbisConfigurationPanel*>("Audio");
		SafeRegister<FlacSettings*, MeGUI::packages::audio::flac::FlacConfigurationPanel*>("Audio");
		SafeRegister<QaacSettings*, MeGUI::packages::audio::qaac::qaacConfigurationPanel*>("Audio");
		SafeRegister<OpusSettings*, MeGUI::packages::audio::opus::OpusConfigurationPanel*>("Audio");

		SafeRegister<OneClickSettings*, OneClickConfigPanel*>();
		SafeRegister<AviSynthSettings*, AviSynthProfileConfigPanel*>();
	}

const std::string ProfileManager::ScratchPadName = "*scratchpad*";

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename TSettings, typename TPanel> where TSettings : GenericSettings, new() where TPanel : Control, Editable<TSettings>, new()
	bool ProfileManager::SafeRegister(...)
	{
		std::string name = (new TSettings())->SettingsID;
		if (byName(name) != 0)
			return false;
		if (bySettingsType(TSettings::typeid) != 0)
			return false;

		ProfileType *p = new SpecificProfileType<TSettings, TPanel>(name);
		profileTypes.push_back(p);

		for (unknown::const_iterator g = groups.begin(); g != groups.end(); ++g)
			groupByName(*g)->Register(p, name, TSettings::typeid);
		return true;
	}

	bool ProfileManager::Register(Type *TSettings, Type *TPanel, const std::string &name)
	{
		MethodInfo *m = ProfileManager::typeid::GetMethod("SafeRegister");
		MethodInfo *m2 = m->MakeGenericMethod(TSettings, TPanel);
		return static_cast<bool>(m2->Invoke(this, new object[] {name}));
	}

	std::string ProfileManager::fixName(const std::string &name)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		name = name.Replace("\"", "_hc_");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		name = name.Replace("*", "_st_");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		name = name.Replace("/", "_sl_");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		name = name.Replace(":", "_dp_");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		name = name.Replace("<", "_lt_");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		name = name.Replace(">", "_rt_");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		name = name.Replace("?", "_qm_");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		name = name.Replace("\\", "_bs_");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		name = name.Replace("|", "_vl_");
		return name;
	}

	ProfileGroup *ProfileManager::groupByName(const std::string &name)
	{
		return Util::ByID(profileGroups, name);
	}

	ProfileType *ProfileManager::byName(const std::string &name)
	{
		return Util::ByID(profileTypes, name);
	}

	ProfileType *ProfileManager::bySettingsType(Type *t)
	{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		return profileTypes.Find(delegate(ProfileType p)
		{
			return p->SettingsType == t;
		}
	   );
	}

	Type *ProfileManager::profileType(const std::string &id)
	{
		return GenericProfile<*>::typeid::MakeGenericType(byName(id)->SettingsType);
	}

	std::string ProfileManager::profilePath(const std::string &path, Profile *prof)
	{
		return Path::Combine(Path::Combine(GetSaveFolder(path), prof->BaseSettings->SettingsID), fixName(prof->getFQName()) + ".xml");
	}

const std::string ProfileManager::SaveFolderName = "allprofiles";

	std::string ProfileManager::GetSaveFolder(const std::string &path)
	{
		return Path::Combine(path, SaveFolderName);
	}

	void ProfileManager::WriteProfiles(const std::string &path, IEnumerable<Profile*> *profiles)
	{
		try
		{
			FileUtil::DeleteDirectoryIfExists(GetSaveFolder(path), true);
		}
		catch (std::exception &ex)
		{
			MessageBox::Show("There was an error clearing the profiles folder before deletion: " + ex.what(), "Error saving profiles", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		for (IEnumerable<Profile*>::const_iterator p = profiles->begin(); p != profiles->end(); ++p)
			Util::XmlSerialize(*p, profilePath(path, *p));
	}

	void ProfileManager::SaveProfiles()
	{
		WriteProfiles(path, getAllProfiles());
		saveSelectedProfiles();
	}

	void ProfileManager::saveSelectedProfiles()
	{
		std::string filename = Path::Combine(GetSaveFolder(path), "SelectedProfiles.xml");
		XmlSerializer *ser = 0;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Stream s = File.Open(filename, System.IO.FileMode.Create, System.IO.FileAccess.Write))
		Stream *s = File->Open(filename, System::IO::FileMode::Create, System::IO::FileAccess::Write);
		try
		{
			try
			{
				// Hacky workaround because serialization of dictionaries isn't possible
//ORIGINAL LINE: string[] groupKeys = profileGroups.ConvertAll<string>(delegate(ProfileGroup g)
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				std::string *groupKeys = profileGroups.ConvertAll<std::string>(delegate(ProfileGroup g)
				{
					return g::ID;
				}
			   ).ToArray();
//ORIGINAL LINE: string[] groupValues = profileGroups.ConvertAll<string>(delegate(ProfileGroup g)
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				std::string *groupValues = profileGroups.ConvertAll<std::string>(delegate(ProfileGroup g)
				{
					return g::SelectedChild;
				}
			   ).ToArray();
//ORIGINAL LINE: string[] keys = profileTypes.ConvertAll<string>(delegate(ProfileType p)
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				std::string *keys = profileTypes.ConvertAll<std::string>(delegate(ProfileType p)
				{
					return p::ID;
				}
			   ).ToArray();
//ORIGINAL LINE: string[] values = profileTypes.ConvertAll<string>(delegate(ProfileType p)
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				std::string *values = profileTypes.ConvertAll<std::string>(delegate(ProfileType p)
				{
					return p::SelectedProfile->Name;
				}
			   ).ToArray();
				std::string data[4] = {keys, values, groupKeys, groupValues};
				ser = new XmlSerializer(data->GetType());
				ser->Serialize(s, data);
			}
			catch (std::exception &e)
			{
				MessageBox::Show("List of selected profiles could not be saved. Error message: " + e.what(), "Error saving profile", MessageBoxButtons::OK);
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (s != 0)
				s.Dispose();
		}
	}

	void ProfileManager::loadSelectedProfiles()
	{
		std::string file = Path::Combine(GetSaveFolder(path), "SelectedProfiles.xml");
		if (!File::Exists(file))
			return;

		deleteDeprecatedEntries(file);

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Stream s = File.OpenRead(file))
		Stream *s = File::OpenRead(file);
		try
		{
			try
			{
				// Hacky workaround because serialization of dictionaries isn't possible
				XmlSerializer *ser = new XmlSerializer(std::string[][]::typeid);
//ORIGINAL LINE: string[][] data = (string[][])ser.Deserialize(s);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				std::string **data = static_cast<std::string[][]>(ser->Deserialize(s));
//ORIGINAL LINE: string[] keys = data[0];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				std::string *keys = data[0];
//ORIGINAL LINE: string[] values = data[1];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				std::string *values = data[1];
//ORIGINAL LINE: string[] groupKeys = data[2];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				std::string *groupKeys = data[2];
//ORIGINAL LINE: string[] groupValues = data[3];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				std::string *groupValues = data[3];
				assert(sizeof(keys) / sizeof(keys[0]) == sizeof(values) / sizeof(values[0]));
				assert(sizeof(groupKeys) / sizeof(groupKeys[0]) == sizeof(groupValues) / sizeof(groupValues[0]));
				for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
				{
					byName(keys[i])->setSelectedProfile(byName(keys[i])->ByName(values[i]));
				}

				for (int i = 0; i < sizeof(groupKeys) / sizeof(groupKeys[0]); ++i)
				{
					groupByName(groupKeys[i])->SelectedChild = groupValues[i];
				}
			}
			catch (std::exception &e1)
			{
				MessageBox::Show("List of selected profiles could not be loaded.", "Error loading profile", MessageBoxButtons::OK);
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (s != 0)
				s.Dispose();
		}
	}

	void ProfileManager::deleteDeprecatedEntries(const std::string &strFile)
	{
		std::string line;
		StringBuilder *sbNewFile = new StringBuilder();
		int counter = 0, iBlock = 0;
		std::vector<int> arrDeprecated = std::vector<int>();
		StreamReader *file = new StreamReader(strFile);

		while ((line = file->ReadLine()) != 0)
		{
			if (line.Equals("  <ArrayOfString>"))
			{
				iBlock++;
				counter = 0;
			}
			counter++;
			if (iBlock == 1 && (line.Equals("    <string>Snow</string>") || line.Equals("    <string>Aud-X MP3</string>") || line.Equals("    <string>Winamp AAC</string>") || line.Equals("    <string>FAAC</string>")))
				arrDeprecated.push_back(counter);
			else if (iBlock == 4 && (line.Equals("    <string>Snow</string>") || line.Equals("    <string>Aud-X MP3</string>") || line.Equals("    <string>Winamp AAC</string>") || line.Equals("    <string>FAAC</string>")))
			{
				if (line.find("Snow") != string::npos)
					sbNewFile->AppendLine("    <string>x264</string>");
				else
					sbNewFile->AppendLine("    <string>Aften AC-3</string>");
			}
			else if (iBlock == 2)
			{
				bool bDelete = false;
				for (std::vector<int>::const_iterator i = arrDeprecated.begin(); i != arrDeprecated.end(); ++i)
				{
					if (*i == counter)
						bDelete = true;
				}
				if (!bDelete)
					sbNewFile->AppendLine(line);
			}
			else
				sbNewFile->AppendLine(line);
		}
		file->Close();

		StreamWriter *newfile = new StreamWriter(strFile);
		newfile->Write(sbNewFile);
		newfile->Close();
	}

	void ProfileManager::LoadProfiles()
	{
		for (std::vector<ProfileType*>::const_iterator t = profileTypes.begin(); t != profileTypes.end(); ++t)
			(*t)->setProfiles(readAllProfiles(*t, false));

		loadSelectedProfiles();
	}

	std::vector<Profile*> ProfileManager::ReadAllProfiles(const std::string &path, bool bSilentError)
	{
		ProfileManager *p = new ProfileManager(path);

		std::vector<Profile*> ps = std::vector<Profile*>();

		for (unknown::const_iterator t = p->profileTypes.begin(); t != p->profileTypes.end(); ++t)
			ps.AddRange(p->readAllProfiles(*t, bSilentError));

		return ps;
	}

	std::vector<Profile*> ProfileManager::readAllProfiles(ProfileType *type, bool bSilentError)
	{
		std::string profilePath = Path::Combine(GetSaveFolder(path), type->getID());
		DirectoryInfo *di = FileUtil::ensureDirectoryExists(profilePath);
//ORIGINAL LINE: FileInfo[] files = di.GetFiles("*.xml");
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		FileInfo *files = di->GetFiles("*.xml");

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		return Util::RemoveDuds((std::vector<FileInfo*>(files))->ConvertAll<Profile*>(delegate(FileInfo fi)
		{
			return static_cast<Profile*>(Util::XmlDeserialize(fi->FullName, type->getGenericProfileType(), bSilentError));
		}
	   ));
	}

	void ProfileManager::setAllProfiles(std::vector<Profile*> &ps)
	{
		ps = Util::RemoveDuds(ps);
		for (std::vector<ProfileType*>::const_iterator type = profileTypes.begin(); type != profileTypes.end(); ++type)
		{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			(*type)->setProfiles(ps.FindAll(delegate(Profile p))
			{
				return p->GetType()->Equals((*type)->getGenericProfileType());
			}
		   );
		}
	}

	Profile *ProfileManager::GetSelectedProfile(const std::string &profileType)
	{
		ProfileType *t = byName(profileType);
		if (t != 0)
			return t->getSelectedProfile();

		ProfileGroup *g = groupByName(profileType);
		assert(g != 0);

		return GetSelectedProfile(g->SelectedChild);
	}

	void ProfileManager::SetSelectedProfile(Profile *prof)
	{
		bySettingsType(GetSettingsType(prof))->setSelectedProfile(prof);
	}

	Profile *ProfileManager::GetProfile(const std::string &type, const std::string &name)
	{
		return byName(type)->ByName(name);
	}

	std::vector<ProfileType*> ProfileManager::byProfileSet(const std::string &profileSet)
	{
		std::vector<ProfileType*> res = std::vector<ProfileType*>();
		ProfileType *p = byName(profileSet);
		if (p != 0)
		{
			res.push_back(p);
			return res;
		}

		ProfileGroup *g = groupByName(profileSet);
		if (g == 0)
			throw std::exception();

		for (std::vector<std::string>::const_iterator s = g->ChildIDs.begin(); s != g->ChildIDs.end(); ++s)
			res.AddRange(byProfileSet(*s));

		return res;
	}

	IEnumerable<Named<Profile*>*> *ProfileManager::Profiles(const std::string &type)
	{
		std::vector<ProfileType*> ps = byProfileSet(type);

		if (ps.size() == 1)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			return Util::ConvertAll<Profile*, Named<Profile*>*>(ps[0]->getProfiles(), delegate(Profile pr)
			{
				return new Named<Profile*>(pr->Name, pr);
			}
		   );

		std::vector<Named<Profile*>*> profiles = std::vector<Named<Profile*>*>();
		for (std::vector<ProfileType*>::const_iterator p = ps.begin(); p != ps.end(); ++p)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			profiles.AddRange(Util::ConvertAll<Profile*, Named<Profile*>*>((*p)->getProfiles(), delegate(Profile prof)
			{
				return new Named<Profile*>(prof::FQName, prof);
			}
		   ));

		return profiles;
	}

	void ProfileManager::AddProfilesChangedListener(const std::string &profileSet, EventHandler *listener)
	{
		for (std::vector<ProfileType*>::const_iterator p = byProfileSet(profileSet).begin(); p != byProfileSet(profileSet).end(); ++p)
			(*p)->ProfilesChanged += listener;
	}

	void ProfileManager::RemoveProfilesChangedListener(const std::string &profileSet, EventHandler *listener)
	{
		for (std::vector<ProfileType*>::const_iterator p = byProfileSet(profileSet).begin(); p != byProfileSet(profileSet).end(); ++p)
			(*p)->ProfilesChanged -= listener;
	}

	Profile *ProfileManager::byFormattedName(const std::string &formattedName)
	{
		std::string type = formattedName.substr(0, formattedName.find(':'));
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		assert(formattedName.StartsWith(type + ": "));
		std::string profileName = formattedName.substr(type.length() + 2);
		return GetProfile(type, profileName);
	}

	const Profile &ProfileManager::getAllProfiles() const
	{
		std::vector<Profile*> profileList = std::vector<Profile*>();

		for (std::vector<ProfileType*>::const_iterator ty = profileTypes.begin(); ty != profileTypes.end(); ++ty)
			profileList.AddRange((*ty)->getProfiles());

		return profileList.ToArray();
	}

	void ProfileManager::AddAll(Profile profiles[], DialogManager *asker)
	{
		for (MeGUI::Profile::const_iterator prof = profiles->begin(); prof != profiles->end(); ++prof)
		{
			bySettingsType(GetSettingsType(*prof))->Add(*prof, asker);
		}
	}

	Type *ProfileManager::GetSettingsType(Profile *p)
	{
		return p->GetType()->GetGenericArguments()[0];
	}

	void ProfileManager::Configure(Profile *SelectedProfile)
	{
		bySettingsType(GetSettingsType(SelectedProfile))->ConfigureProfiles();
	}

	void ProfileManager::SetSettings(GenericSettings *s)
	{
		bySettingsType(s->GetType())->SetSettings(s);
	}

	MeGUI::core::plugins::interfaces::GenericSettings *ProfileManager::GetCurrentSettings(const std::string &p)
	{
		return GetSelectedProfile(p)->BaseSettings;
	}

	void ProfileManager::InitializeInstanceFields()
	{
		profileTypes = std::vector<ProfileType*>();
		profileGroups = std::vector<ProfileGroup*>();
	}

	const std::string &ProfileType::getID() const
	{
		return profileTypeID;
	}

	const MeGUI::core::util::Tuple<IEnumerable<Profile*>*, Profile*> &ProfileType::getProfilesAndSelected() const
	{
		return new Tuple<IEnumerable<Profile*>*, Profile*>(profiles, selectedProfile);
	}

	void ProfileType::setProfilesAndSelected(const Tuple<IEnumerable<Profile*>*, &Profile*> *value)
	{
		profiles = std::vector<Profile*>(value->a);
		if (profiles.empty())
			profiles.push_back(genScratchpad());

		selectedProfile = (value->b != 0) ? value->b : profiles[0];

		raiseChangedEvent();
	}

	const IEnumerable<Profile*> &ProfileType::getProfiles() const
	{
		return getProfilesAndSelected()->a;
	}

	void ProfileType::setProfiles(const IEnumerable<Profile*> &value)
	{
		setProfilesAndSelected(new Tuple<IEnumerable<Profile*>*, Profile*>(value, 0));
	}

	void ProfileType::raiseChangedEvent()
	{
		ProfilesChanged(this, EventArgs::Empty);
	}

	const Profile &ProfileType::getSelectedProfile() const
	{
		return selectedProfile;
	}

	void ProfileType::setSelectedProfile(const Profile &value)
	{
		selectedProfile = (value != 0) ? value : selectedProfile;
		SelectedProfileSet(this, EventArgs::Empty);
	}

	void ProfileType::SetSettings(GenericSettings *s)
	{
		if (s->GetType() != SettingsType)
			throw std::exception("Wrong type of settings used");

		Profile *p = ByName(ProfileManager::ScratchPadName);
		if (p == 0)
		{
			p = genScratchpad();
			profiles.push_back(p);
		}
		p->BaseSettings = s;
		setSelectedProfile(p);
	}

	const Type &ProfileType::getGenericProfileType() const
	{
		return GenericProfile<*>::typeid::MakeGenericType(SettingsType);
	}

	ProfileType::ProfileType(const std::string &name) : profileTypeID(name)
	{
		InitializeInstanceFields();
	}

	Profile *ProfileType::ByName(const std::string &name)
	{
		int i = indexOf(name);
		if (i >= 0)
			return profiles[i];
		else
			return 0;
	}

	int ProfileType::indexOf(const std::string &name)
	{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		return profiles.FindIndex(delegate(Profile p)
		{
			return p->Name == name;
		}
	   );
	}

	void ProfileType::Add(Profile *prof, DialogManager *asker)
	{
		int i = indexOf(prof->getName());
		if (i < 0)
		{
			profiles.push_back(prof);
			raiseChangedEvent();
		}
		else if (asker->overwriteProfile(prof->getFQName()))
			profiles[i] = prof;
		else // skip this profile
		{
		}
	}

	void ProfileType::InitializeInstanceFields()
	{
		profiles = std::vector<Profile*>();
	}

	const std::string &ProfileGroup::getID() const
	{
		return profileGroupID;
	}

	ProfileGroup::ProfileGroup(Type *t, const std::string &name) : profileGroupID(name), CommonType(t)
	{
		InitializeInstanceFields();
		assert(Array->find(t->GetInterfaces(), GenericSettings::typeid) >= 0);
		//Debug.Assert(t.IsSubclassOf(typeof(GenericSettings)));
	}

	void ProfileGroup::Register(ProfileType *t, const std::string &childID, Type *childType)
	{
		assert(childType->IsSubclassOf(CommonType));

		if (!std::find(ChildIDs.begin(), ChildIDs.end(), childID) != ChildIDs.end())
			ChildIDs.push_back(childID);

		if (SelectedChild == "")
			SelectedChild = childID;

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		t->SelectedProfileSet += delegate(object _, EventArgs __)
		{
			SelectedChild = childID;
		};
	}

	void ProfileGroup::InitializeInstanceFields()
	{
		ChildIDs = std::vector<std::string>();
		SelectedChild = "";
	}
}
