#include "MeGUI.core.gui.ProfilePorter.h"






//using namespace System::Collections::Generic;



//using namespace System::Data;





//using namespace System::Text;


using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			ProfilePorter::ProfilePorter()
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			object *ProfilePorter::profilesToObjects(Profile ps[])
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return Array::ConvertAll<Profile*, object*>(ps, delegate(Profile p)
				{
					return new Named<Profile*>(p::FQName, p);
				}
			   );
			}

			Profile *ProfilePorter::objectsToProfiles(IEnumerable *objects)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return Array::ConvertAll<object*, Profile*>(Util::ToArray(objects), delegate(object o)
				{
					return (static_cast<Named<Profile*>*>(o))->Data;
				}
			   );
			}

			const Profile &ProfilePorter::getProfiles() const
			{
				return objectsToProfiles(profileList->Items);
			}

			void ProfilePorter::setProfiles(const Profile &value[])
			{
				profileList->Items->Clear();
				profileList->Items->AddRange(profilesToObjects(value));
			}

			const QVector<Profile*> &ProfilePorter::getSelectedAndRequiredProfiles() const
			{
//ORIGINAL LINE: Profile[] allProfs = Profiles;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
				Profile *allProfs = getProfiles();
				QVector<Profile*> profs = QVector<Profile*>(objectsToProfiles(profileList->CheckedItems));

				while (true)
				{
					int oldCount = profs.size();

					QVector<Profile*> newProfs = QVector<Profile*>();

					for (QVector<Profile*>::const_iterator p = profs.begin(); p != profs.end(); ++p)
					{
						// add the profiles we don't already have
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
						newProfs.AddRange(Array::ConvertAll<QString, Profile*>((*p)->BaseSettings->RequiredProfiles, delegate(QString s)
						{
							return Util::ByID(allProfs, s);
						}
					   ));
					}

					profs.AddRange(newProfs);
					profs = Util::RemoveDuds(profs);

					if (oldCount == profs.size())
						break;
				}

				return profs;
			}

			std::QMap<QString, QString> ProfilePorter::copyExtraFilesToFolder(QVector<QString> &extraFiles, const QString &folder)
			{
				std::QMap<QString, QString> subTable = std::QMap<QString, QString>();
				FileUtil::ensureDirectoryExists(folder);

				for (QVector<QString>::const_iterator file = extraFiles.begin(); file != extraFiles.end(); ++file)
				{
					QString filename = Path::GetFileName(*file);
					QString pathname = Path::Combine(folder, filename);
					subTable[*file] = pathname;

					// Copy the file
					if (File::Exists(pathname))
						File::Delete(pathname);

					File::Copy(*file, pathname);
				}

				return subTable;
			}

			void ProfilePorter::fixFileNames(QVector<Profile*> &ps, std::QMap<QString, QString> &subTable)
			{
				for (QVector<Profile*>::const_iterator p = ps.begin(); p != ps.end(); ++p)
					(*p)->BaseSettings->FixFileNames(subTable);
			}

			QString ProfilePorter::getZippedExtraFileName(const QString &p)
			{
				return Path::Combine("extra", p);
			}

			void ProfilePorter::cancelButton_Click(QObject *sender, QEvent *e)
			{
				MainForm::Instance->setImportProfileSuccessful(true);
				this->Close();
			}

			void ProfilePorter::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				System::Windows::Forms::Form::Dispose(disposing);
			}

			void ProfilePorter::InitializeComponent()
			{
				System::Windows::Forms::Button *cancelButton;
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(ProfilePorter::typeid);
				this->profileList = new System::Windows::Forms::CheckedListBox();
				this->label1 = new System::Windows::Forms::Label();
				this->button2 = new System::Windows::Forms::Button();
				cancelButton = new System::Windows::Forms::Button();
				this->SuspendLayout();
				// 
				// cancelButton
				// 
				cancelButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
				cancelButton->AutoSize = true;
				cancelButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				cancelButton->Location = new System::Drawing::Point(322, 323);
				cancelButton->Name = "cancelButton";
				cancelButton->Size = new System::Drawing::Size(49, 23);
				cancelButton->TabIndex = 2;
				cancelButton->Text = "Cancel";
				cancelButton->UseVisualStyleBackColor = true;
				cancelButton->Click += new System::EventHandler(this, &ProfilePorter::cancelButton_Click);
				// 
				// profileList
				// 
				this->profileList->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
				this->profileList->CheckOnClick = true;
				this->profileList->FormattingEnabled = true;
				this->profileList->IntegralHeight = false;
				this->profileList->Location = new System::Drawing::Point(12, 25);
				this->profileList->Name = "profileList";
				this->profileList->Size = new System::Drawing::Size(359, 288);
				this->profileList->TabIndex = 0;
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = new System::Drawing::Point(12, 9);
				this->label1->Name = "label1";
				this->label1->Size = new System::Drawing::Size(176, 13);
				this->label1->TabIndex = 1;
				this->label1->Text = "Select the presets to import/export";
				// 
				// button2
				// 
				this->button2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
				this->button2->AutoSize = true;
				this->button2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->button2->Location = new System::Drawing::Point(206, 323);
				this->button2->Name = "button2";
				this->button2->Size = new System::Drawing::Size(109, 23);
				this->button2->TabIndex = 2;
				this->button2->Text = "Import.../Export...";
				this->button2->UseVisualStyleBackColor = true;
				// 
				// ProfilePorter
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = new System::Drawing::Size(383, 358);
				this->Controls->Add(this->button2);
				this->Controls->Add(cancelButton);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->profileList);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->Name = "ProfilePorter";
				this->Text = "Presets Importer/Exporter";
				this->TopMost = true;
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void ProfilePorter::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
