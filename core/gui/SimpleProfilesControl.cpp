#include "SimpleProfilesControl.h"







using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace core
	{
		namespace gui
		{

			const QString &ProfileCouldntBeSelectedException::getProfileName() const
			{
				return name;
			}

			ProfileCouldntBeSelectedException::ProfileCouldntBeSelectedException(const QString &name) : MeXguiException("The profile '" + name + "' couldn't be selected.")
			{
				this->name = name;
			}
		
			SimpleProfilesControl::SimpleProfilesControl()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			void SimpleProfilesControl::SetSettings(AudioCodecSettings *value)
			{
				manager->SetSettings(value);
			}

			const MeXgui::Profile &SimpleProfilesControl::getSelectedProfile() const
			{
				return (static_cast<Named<Profile*>*>(comboBox1->SelectedItem))->Data;
			}

			void SimpleProfilesControl::SelectProfile(const QString &fqname)
			{
				for (unknown::const_iterator n = comboBox1->Items.begin(); n != comboBox1->Items.end(); ++n)
				{
					if ((*n)->Data->FQName == fqname)
					{
						comboBox1->SelectedItem = *n;
						return;
					}
				}
				if (comboBox1->Items->Count > 0)
				{
					comboBox1->SelectedIndex = 0;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					MessageBox::Show("The profile \"" + fqname + "\" could not be selected.\r\nSelecting profile \"" + comboBox1->SelectedItem->ToString() + "\" instead.", "Profile couldn't be selected", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
			}

			void SimpleProfilesControl::SelectProfile(Profile *prof)
			{
				SelectProfile(prof->getFQName());
			}

			void SimpleProfilesControl::SetProfileNameOrWarn(const QString &fqname)
			{
				if (fqname.empty())
					return;
				try
				{
					SelectProfile(fqname);
				}
				catch (ProfileCouldntBeSelectedException *e1)
				{
					MessageBox::Show("The profile, " + fqname + ", could not be selected.", "Profile couldn't be selected", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
			}

			const MeXgui::ProfileManager &SimpleProfilesControl::getManager() const
			{
				return manager;
			}

			void SimpleProfilesControl::setManager(const ProfileManager &value)
			{
				if (!getProfileSet().empty())
				{
					manager->RemoveProfilesChangedListener(getProfileSet(), ProfilesChanged);
					value->AddProfilesChangedListener(getProfileSet(), ProfilesChanged);
				}
				manager = value;
				RefreshProfiles();
			}

			void SimpleProfilesControl::ProfilesChanged(object *_, QEvent *__)
			{
				RefreshProfiles();
			}

			const QString &SimpleProfilesControl::getProfileSet() const
			{
				return profileSet;
			}

			void SimpleProfilesControl::setProfileSet(const QString &value)
			{
				if (!profileSet.empty())
					getManager()->RemoveProfilesChangedListener(profileSet, ProfilesChanged);
				if (!value.empty())
					getManager()->AddProfilesChangedListener(value, ProfilesChanged);

				profileSet = value;
			}

			void SimpleProfilesControl::RefreshProfiles()
			{
				comboBox1->Items->Clear();
				for (IEnumerable<Named<Profile*>*>::const_iterator oProfile = getManager()->Profiles(getProfileSet())->begin(); oProfile != getManager()->Profiles(getProfileSet())->end(); ++oProfile)
				{
					if ((dynamic_cast<NeroAACSettings*>((*oProfile)->Data->BaseSettings) != 0) && !MainForm::Instance->getSettings()->IsNeroAACEncAvailable())
						continue;

					if ((dynamic_cast<QaacSettings*>((*oProfile)->Data->BaseSettings) != 0) && !MainForm::Instance->getSettings()->IsQAACAvailable())
						continue;

					comboBox1->Items->Add(*oProfile);
				}
				SelectProfile(getManager()->GetSelectedProfile(getProfileSet()));
			}

			void SimpleProfilesControl::raiseProfileChangedEvent()
			{
				SelectedProfileChanged(this, QEvent::Empty);
			}

			void SimpleProfilesControl::comboBox1_SelectedIndexChanged(QObject *sender, QEvent *e)
			{
				getManager()->SetSelectedProfile(getSelectedProfile());
				raiseProfileChangedEvent();
			}

			void SimpleProfilesControl::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				UserControl::Dispose(disposing);
			}

			void SimpleProfilesControl::InitializeComponent()
			{
				this->comboBox1 = new System::Windows::Forms::ComboBox();
				this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
				this->tableLayoutPanel1->SuspendLayout();
				this->SuspendLayout();
				// 
				// comboBox1
				// 
				this->comboBox1->Anchor = System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right;
				this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				this->comboBox1->FormattingEnabled = true;
				this->comboBox1->Location = new System::Drawing::Point(0, 0);
				this->comboBox1->Margin = new System::Windows::Forms::Padding(0);
				this->comboBox1->Name = "comboBox1";
				this->comboBox1->Size = new System::Drawing::Size(200, 21);
				this->comboBox1->Sorted = true;
				this->comboBox1->TabIndex = 0;
				this->comboBox1->SelectedIndexChanged += new System::EventHandler(this, &SimpleProfilesControl::comboBox1_SelectedIndexChanged);
				// 
				// tableLayoutPanel1
				// 
				this->tableLayoutPanel1->ColumnCount = 2;
				this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
				this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
				this->tableLayoutPanel1->Controls->Add(this->comboBox1, 0, 0);
				this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tableLayoutPanel1->Location = new System::Drawing::Point(0, 0);
				this->tableLayoutPanel1->Margin = new System::Windows::Forms::Padding(0);
				this->tableLayoutPanel1->Name = "tableLayoutPanel1";
				this->tableLayoutPanel1->RowCount = 1;
				this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100));
				this->tableLayoutPanel1->Size = new System::Drawing::Size(200, 22);
				this->tableLayoutPanel1->TabIndex = 1;
				// 
				// SimpleProfilesControl
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->Controls->Add(this->tableLayoutPanel1);
				this->Name = "SimpleProfilesControl";
				this->Size = new System::Drawing::Size(200, 22);
				this->tableLayoutPanel1->ResumeLayout(false);
				this->ResumeLayout(false);

			}

			void SimpleProfilesControl::InitializeInstanceFields()
			{
				manager = new ProfileManager("");
				delete components;
			}
		}
	}
}
