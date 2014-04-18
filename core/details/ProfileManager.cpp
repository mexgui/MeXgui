#include "ProfileManager.h"




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

	ProfileManager::ProfileManager(const QString &path)
	{
		InitializeInstanceFields();
		this->path = path;
		profileGroups.push_back(new ProfileGroup(VideoCodecSettings::typeid, "Video"));
		SafeRegister<x264Settings*, x264ConfigurationPanel*>("Video");
		SafeRegister<xvidSettings*, MeXgui::packages::video::xvid::xvidConfigurationPanel*>("Video");
		profileGroups.push_back(new ProfileGroup(AudioCodecSettings::typeid, "Audio"));
		SafeRegister<AftenSettings*, MeXgui::packages::audio::aften::AftenConfigurationPanel*>("Audio");
		SafeRegister<AC3Settings*, MeXgui::packages::audio::ffac3::AC3ConfigurationPanel*>("Audio");
		SafeRegister<MP2Settings*, MeXgui::packages::audio::ffmp2::MP2ConfigurationPanel*>("Audio");
		SafeRegister<MP3Settings*, MeXgui::packages::audio::lame::lameConfigurationPanel*>("Audio");
		SafeRegister<NeroAACSettings*, MeXgui::packages::audio::naac::neroConfigurationPanel*>("Audio");
		SafeRegister<OggVorbisSettings*, MeXgui::packages::audio::vorbis::OggVorbisConfigurationPanel*>("Audio");
		SafeRegister<FlacSettings*, MeXgui::packages::audio::flac::FlacConfigurationPanel*>("Audio");
		SafeRegister<QaacSettings*, MeXgui::packages::audio::qaac::qaacConfigurationPanel*>("Audio");
		SafeRegister<OpusSettings*, MeXgui::packages::audio::opus::OpusConfigurationPanel*>("Audio");

		SafeRegister<OneClickSettings*, OneClickConfigPanel*>();
		SafeRegister<AviSynthSettings*, AviSynthProfileConfigPanel*>();
	}

const QString ProfileManager::ScratchPadName = "*scratchpad*";

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename TSettings, typename TPanel> where TSettings : GenericSettings, new() where TPanel : Control, Editable<TSettings>, new()
	bool ProfileManager::SafeRegister(...)
	{
		QString name = (new TSettings())->SettingsID;
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

	bool ProfileManager::Register(Type *TSettings, Type *TPanel, const QString &name)
	{
		MethodInfo *m = ProfileManager::typeid::GetMethod("SafeRegister");
		MethodInfo *m2 = m->MakeGenericMethod(TSettings, TPanel);
		return static_cast<bool>(m2->Invoke(this, new object[] {name}));
	}

	QString ProfileManager::fixName(const QString &name)
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

	ProfileGroup *ProfileManager::groupByName(const QString &name)
	{
		return Util::ByID(profileGroups, name);
	}

	ProfileType *ProfileManager::byName(const QString &name)
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

	Type *ProfileManager::profileType(const QString &id)
	{
		return GenericProfile<*>::typeid::MakeGenericType(byName(id)->SettingsType);
	}

	QString ProfileManager::profilePath(const QString &path, Profile *prof)
	{
		return Path::Combine(Path::Combine(GetSaveFolder(path), prof->BaseSettings->SettingsID), fixName(prof->getFQName()) + ".xml");
	}

const QString ProfileManager::SaveFolderName = "allprofiles";

	QString ProfileManager::GetSaveFolder(const QString &path)
	{
		return Path::Combine(path, SaveFolderName);
	}

	void ProfileManager::WriteProfiles(const QString &path, IEnumerable<Profile*> *profiles)
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
		QString filename = Path::Combine(GetSaveFolder(path), "SelectedProfiles.xml");
		XmlSerializer *ser = 0;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (Stream s = File.Open(filename, System.IO.FileMode.Create, System.IO.FileAccess.Write))
		Stream *s = File->Open(filename, System::IO::FileMode::Create, System::IO::FileAccess::Write);
		try
		{
			try
			{
				// Hacky workaround because serialization of dictionaries isn't possible
//ORIGINAL LINE: string[] groupKeys = profileGroups.ConvertAll<QString>(delegate(ProfileGroup g)
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				QString *groupKeys = profileGroups.ConvertAll<QString>(delegate(ProfileGroup g)
				{
					return g::ID;
				}
			   ).ToArray();
//ORIGINAL LINE: string[] groupValues = profileGroups.ConvertAll<QString>(delegate(ProfileGroup g)
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				QString *groupValues = profileGroups.ConvertAll<QString>(delegate(ProfileGroup g)
				{
					return g::SelectedChild;
				}
			   ).ToArray();
//ORIGINAL LINE: string[] keys = profileTypes.ConvertAll<QString>(delegate(ProfileType p)
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				QString *keys = profileTypes.ConvertAll<QString>(delegate(ProfileType p)
				{
					return p::ID;
				}
			   ).ToArray();
//ORIGINAL LINE: string[] values = profileTypes.ConvertAll<QString>(delegate(ProfileType p)
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				QString *values = profileTypes.ConvertAll<QString>(delegate(ProfileType p)
				{
					return p::SelectedProfile->Name;
				}
			   ).ToArray();
				QString data[4] = {keys, values, groupKeys, groupValues};
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
		QString file = Path::Combine(GetSaveFolder(path), "SelectedProfiles.xml");
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
				XmlSerializer *ser = new XmlSerializer(QString[][]::typeid);
//ORIGINAL LINE: string[][] data = (string[][])ser.Deserialize(s);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				QString **data = static_cast<QString[][]>(ser->Deserialize(s));
//ORIGINAL LINE: string[] keys = data[0];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				QString *keys = data[0];
//ORIGINAL LINE: string[] values = data[1];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				QString *values = data[1];
//ORIGINAL LINE: string[] groupKeys = data[2];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				QString *groupKeys = data[2];
//ORIGINAL LINE: string[] groupValues = data[3];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				QString *groupValues = data[3];
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

	void ProfileManager::deleteDeprecatedEntries(const QString &strFile)
	{
		QString line;
		StringBuilder *sbNewFile = new StringBuilder();
		int counter = 0, iBlock = 0;
		QVector<int> arrDeprecated = QVector<int>();
		StreamReader *file = new StreamReader(strFile);

		while ((line = file->ReadLine()) != 0)
		{
			if (line.Equals("  <ArrayOfString>"))
			{
				iBlock++;
				counter = 0;
			}
			counter++;
			if (iBlock == 1 && (line.Equals("    <QString>Snow</string>") || line.Equals("    <QString>Aud-X MP3</string>") || line.Equals("    <QString>Winamp AAC</string>") || line.Equals("    <QString>FAAC</string>")))
				arrDeprecated.push_back(counter);
			else if (iBlock == 4 && (line.Equals("    <QString>Snow</string>") || line.Equals("    <QString>Aud-X MP3</string>") || line.Equals("    <QString>Winamp AAC</string>") || line.Equals("    <QString>FAAC</string>")))
			{
				if (line.find("Snow") != string::npos)
					sbNewFile->AppendLine("    <QString>x264</string>");
				else
					sbNewFile->AppendLine("    <QString>Aften AC-3</string>");
			}
			else if (iBlock == 2)
			{
				bool bDelete = false;
				for (QVector<int>::const_iterator i = arrDeprecated.begin(); i != arrDeprecated.end(); ++i)
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
		for (QVector<ProfileType*>::const_iterator t = profileTypes.begin(); t != profileTypes.end(); ++t)
			(*t)->setProfiles(readAllProfiles(*t, false));

		loadSelectedProfiles();
	}

	QVector<Profile*> ProfileManager::ReadAllProfiles(const QString &path, bool bSilentError)
	{
		ProfileManager *p = new ProfileManager(path);

		QVector<Profile*> ps = QVector<Profile*>();

		for (unknown::const_iterator t = p->profileTypes.begin(); t != p->profileTypes.end(); ++t)
			ps.AddRange(p->readAllProfiles(*t, bSilentError));

		return ps;
	}

	QVector<Profile*> ProfileManager::readAllProfiles(ProfileType *type, bool bSilentError)
	{
		QString profilePath = Path::Combine(GetSaveFolder(path), type->getID());
		DirectoryInfo *di = FileUtil::ensureDirectoryExists(profilePath);
//ORIGINAL LINE: FileInfo[] files = di.GetFiles("*.xml");
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		FileInfo *files = di->GetFiles("*.xml");

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		return Util::RemoveDuds((QVector<FileInfo*>(files))->ConvertAll<Profile*>(delegate(FileInfo fi)
		{
			return static_cast<Profile*>(Util::XmlDeserialize(fi->FullName, type->getGenericProfileType(), bSilentError));
		}
	   ));
	}

	void ProfileManager::setAllProfiles(QVector<Profile*> &ps)
	{
		ps = Util::RemoveDuds(ps);
		for (QVector<ProfileType*>::const_iterator type = profileTypes.begin(); type != profileTypes.end(); ++type)
		{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			(*type)->setProfiles(ps.FindAll(delegate(Profile p))
			{
				return p->GetType()->Equals((*type)->getGenericProfileType());
			}
		   );
		}
	}

	Profile *ProfileManager::GetSelectedProfile(const QString &profileType)
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

	Profile *ProfileManager::GetProfile(const QString &type, const QString &name)
	{
		return byName(type)->ByName(name);
	}

	QVector<ProfileType*> ProfileManager::byProfileSet(const QString &profileSet)
	{
		QVector<ProfileType*> res = QVector<ProfileType*>();
		ProfileType *p = byName(profileSet);
		if (p != 0)
		{
			res.push_back(p);
			return res;
		}

		ProfileGroup *g = groupByName(profileSet);
		if (g == 0)
			throw std::exception();

		for (QVector<QString>::const_iterator s = g->ChildIDs.begin(); s != g->ChildIDs.end(); ++s)
			res.AddRange(byProfileSet(*s));

		return res;
	}

	IEnumerable<Named<Profile*>*> *ProfileManager::Profiles(const QString &type)
	{
		QVector<ProfileType*> ps = byProfileSet(type);

		if (ps.size() == 1)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			return Util::ConvertAll<Profile*, Named<Profile*>*>(ps[0]->getProfiles(), delegate(Profile pr)
			{
				return new Named<Profile*>(pr->Name, pr);
			}
		   );

		QVector<Named<Profile*>*> profiles = QVector<Named<Profile*>*>();
		for (QVector<ProfileType*>::const_iterator p = ps.begin(); p != ps.end(); ++p)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			profiles.AddRange(Util::ConvertAll<Profile*, Named<Profile*>*>((*p)->getProfiles(), delegate(Profile prof)
			{
				return new Named<Profile*>(prof::FQName, prof);
			}
		   ));

		return profiles;
	}

	void ProfileManager::AddProfilesChangedListener(const QString &profileSet, EventHandler *listener)
	{
		for (QVector<ProfileType*>::const_iterator p = byProfileSet(profileSet).begin(); p != byProfileSet(profileSet).end(); ++p)
			(*p)->ProfilesChanged += listener;
	}

	void ProfileManager::RemoveProfilesChangedListener(const QString &profileSet, EventHandler *listener)
	{
		for (QVector<ProfileType*>::const_iterator p = byProfileSet(profileSet).begin(); p != byProfileSet(profileSet).end(); ++p)
			(*p)->ProfilesChanged -= listener;
	}

	Profile *ProfileManager::byFormattedName(const QString &formattedName)
	{
		QString type = formattedName.substr(0, formattedName.find(':'));
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
		assert(formattedName.StartsWith(type + ": "));
		QString profileName = formattedName.substr(type.length() + 2);
		return GetProfile(type, profileName);
	}

	const Profile &ProfileManager::getAllProfiles() const
	{
		QVector<Profile*> profileList = QVector<Profile*>();

		for (QVector<ProfileType*>::const_iterator ty = profileTypes.begin(); ty != profileTypes.end(); ++ty)
			profileList.AddRange((*ty)->getProfiles());

		return profileList.ToArray();
	}

	void ProfileManager::AddAll(Profile profiles[], DialogManager *asker)
	{
		for (MeXgui::Profile::const_iterator prof = profiles->begin(); prof != profiles->end(); ++prof)
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

	MeXgui::core::plugins::interfaces::GenericSettings *ProfileManager::GetCurrentSettings(const QString &p)
	{
		return GetSelectedProfile(p)->BaseSettings;
	}

	void ProfileManager::InitializeInstanceFields()
	{
		profileTypes = QVector<ProfileType*>();
		profileGroups = QVector<ProfileGroup*>();
	}

	const QString &ProfileType::getID() const
	{
		return profileTypeID;
	}

	const MeXgui::core::util::Tuple<IEnumerable<Profile*>*, Profile*> &ProfileType::getProfilesAndSelected() const
	{
		return new Tuple<IEnumerable<Profile*>*, Profile*>(profiles, selectedProfile);
	}

	void ProfileType::setProfilesAndSelected(const Tuple<IEnumerable<Profile*>*, &Profile*> *value)
	{
		profiles = QVector<Profile*>(value->a);
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

	ProfileType::ProfileType(const QString &name) : profileTypeID(name)
	{
		InitializeInstanceFields();
	}

	Profile *ProfileType::ByName(const QString &name)
	{
		int i = indexOf(name);
		if (i >= 0)
			return profiles[i];
		else
			return 0;
	}

	int ProfileType::indexOf(const QString &name)
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
		profiles = QVector<Profile*>();
	}

	const QString &ProfileGroup::getID() const
	{
		return profileGroupID;
	}

	ProfileGroup::ProfileGroup(Type *t, const QString &name) : profileGroupID(name), CommonType(t)
	{
		InitializeInstanceFields();
		assert(Array->find(t->GetInterfaces(), GenericSettings::typeid) >= 0);
		//Debug.Assert(t.IsSubclassOf(typeof(GenericSettings)));
	}

	void ProfileGroup::Register(ProfileType *t, const QString &childID, Type *childType)
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
		ChildIDs = QVector<QString>();
		SelectedChild = "";
	}
}
