#include "ProfileImporter.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;





//using namespace System::Text;



//using namespace System::Xml;
using namespace ICSharpCode::SharpZipLib::Zip;
using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace core
	{
		namespace gui
		{

			QString ProfileImporter::askForZipFile()
			{
				OpenFileDialog *inputChooser = new OpenFileDialog();
				inputChooser->Filter = "Zip archives|*.zip";
				inputChooser->Title = "Select your input file";

				if (inputChooser->show() != DialogResult::OK)
					throw new CancelledException();

				return inputChooser->FileName;
			}

			ProfileImporter::ProfileImporter(MainForm *mf, bool bSilentError)
			{
				InitializeInstanceFields();
			}

			ProfileImporter::ProfileImporter(MainForm *mf, const QString &filename, bool bSilentError)
			{
				InitializeInstanceFields();
			}

			ProfileImporter::ProfileImporter(MainForm *mf, Stream *s, bool bSilentError)
			{
				InitializeInstanceFields();
				InitializeComponent();

				mainForm = mf;
				mainForm->setImportProfileSuccessful(false);

				tempFolder = FileUtil::CreateTempDirectory();
				FileUtil::ExtractZipFile(s, tempFolder->FullName);

				extraFiles = FileUtil::ensureDirectoryExists(Path::Combine(tempFolder->FullName, "extra"));
				QVector<Profile*> ps = ProfileManager::ReadAllProfiles(tempFolder->FullName, bSilentError);

				fixFileNames(ps, createInitSubTable());

				setProfiles(ps.ToArray());
			}

			bool ProfileImporter::ErrorDuringInit()
			{
				if (sizeof(getProfiles()) / sizeof(getProfiles()[0]) == 0)
					return true;
				else
					return false;
			}

			void ProfileImporter::AutoImport()
			{
				checkAllToolStripMenuItem_Click(0, 0);
				import_Click(0, 0);
			}

			std::QMap<QString, QString> ProfileImporter::createInitSubTable()
			{
				std::QMap<QString, QString> d = std::QMap<QString, QString>();

				for (unknown::const_iterator f = extraFiles->GetFiles().begin(); f != extraFiles->GetFiles().end(); ++f)
					d[getZippedExtraFileName((*f)->Name)] = (*f)->FullName;

				return d;
			}

			const QVector<QString> &ProfileImporter::getextraFilesList() const
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return (QVector<FileInfo*>(extraFiles->GetFiles()))->ConvertAll<QString>(delegate(FileInfo f)
				{
					return f->FullName;
				}
			   );
			}

			void ProfileImporter::import_Click(QObject *sender, QEvent *e)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Util::CatchExceptionsAndTellUser("Error importing file", delegate
				{
					QVector<Profile*> ps = getSelectedAndRequiredProfiles();
					fixFileNames(ps, copyExtraFilesToFolder(getextraFilesList(), Path::Combine(mainForm->getMeXguiPath(), "extra")));
					mainForm->getProfiles()->AddAll(ps.ToArray(), mainForm->getDialogManager());
					DialogResult = DialogResult::OK;
					mainForm->setImportProfileSuccessful(true);
					this->Close();
				}
			   );
			}

			void ProfileImporter::checkAllToolStripMenuItem_Click(QObject *sender, QEvent *e)
			{
				ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(sender);
				for (int i = 0; i < profileList->Items->Count; i++)
				{
					profileList->SetItemChecked(i, true);
				}
			}

			void ProfileImporter::checkNoneToolStripMenuItem_Click(QObject *sender, QEvent *e)
			{
				ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(sender);
				for (int i = 0; i < profileList->Items->Count; i++)
				{
					profileList->SetItemChecked(i, false);
				}
			}

			QString ProfileImporter::SelectHelpText(const QString &node)
			{
				StringBuilder *HelpText = new StringBuilder(64);

				QString xpath = "/ContextHelp/Form[@name='PresetImporter']/" + node;
				XmlNodeList *nl = ContextHelp->SelectNodes(xpath); // Return the details for the specified node

				if (nl->Count == 1) // if it finds the required HelpText, count should be 1
				{
					HelpText->AppendLine(nl[0]["Basic"]->InnerText);
					HelpText->AppendLine();
				}
				else // If count isn't 1, then theres no valid data.
					HelpText->Append("Error: No data available");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return (HelpText->ToString());
			}

			void ProfileImporter::SetToolTips()
			{
				PresetImporterToolTip->SetToolTip(this->profileList, SelectHelpText("presetList"));
			}

			void ProfileImporter::ProfileImporter_Shown(QObject *sender, QEvent *e)
			{
				try
				{
					QString p = System::IO::Path::Combine(Application::StartupPath, "Data");
					p = System::IO::Path::Combine(p, "ContextHelp.xml");
					ContextHelp->Load(p);
					SetToolTips();
				}
				catch (...)
				{
					MessageBox::Show("The ContextHelp.xml file could not be found. Please check in the 'Data' directory to see if it exists. Help tooltips will not be available.", "File Not Found", MessageBoxButtons::OK);
				}
			}

			void ProfileImporter::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				MeXgui::core::gui::ProfilePorter::Dispose(disposing);
			}

			void ProfileImporter::InitializeComponent()
			{
				this->components = new System::ComponentModel::Container();
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(ProfileImporter::typeid);
				this->statusCheck = new System::Windows::Forms::ContextMenuStrip(this->components);
				this->checkAllToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->checkNoneToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->PresetImporterToolTip = new System::Windows::Forms::ToolTip(this->components);
				this->statusCheck->SuspendLayout();
				this->SuspendLayout();
				// 
				// label1
				// 
				this->label1->Location = new System::Drawing::Point(12, 7);
				this->label1->Size = new System::Drawing::Size(140, 13);
				this->label1->Text = "Select the presets to import";
				// 
				// button2
				// 
				this->button2->Location = new System::Drawing::Point(266, 323);
				this->button2->Size = new System::Drawing::Size(49, 23);
				this->button2->Text = "Import";
				this->button2->Click += new System::EventHandler(this, &ProfileImporter::import_Click);
				// 
				// profileList
				// 
				this->profileList->ContextMenuStrip = this->statusCheck;
				// 
				// statusCheck
				// 
				this->statusCheck->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->checkAllToolStripMenuItem, this->checkNoneToolStripMenuItem});
				this->statusCheck->Name = "statusCheck";
				this->statusCheck->Size = new System::Drawing::Size(140, 48);
				// 
				// checkAllToolStripMenuItem
				// 
				this->checkAllToolStripMenuItem->Name = "checkAllToolStripMenuItem";
				this->checkAllToolStripMenuItem->Size = new System::Drawing::Size(139, 22);
				this->checkAllToolStripMenuItem->Text = "Check All";
				this->checkAllToolStripMenuItem->Click += new System::EventHandler(this, &ProfileImporter::checkAllToolStripMenuItem_Click);
				// 
				// checkNoneToolStripMenuItem
				// 
				this->checkNoneToolStripMenuItem->Name = "checkNoneToolStripMenuItem";
				this->checkNoneToolStripMenuItem->Size = new System::Drawing::Size(139, 22);
				this->checkNoneToolStripMenuItem->Text = "Check None";
				this->checkNoneToolStripMenuItem->Click += new System::EventHandler(this, &ProfileImporter::checkNoneToolStripMenuItem_Click);
				// 
				// PresetImporterToolTip
				// 
				this->PresetImporterToolTip->AutoPopDelay = 5000;
				this->PresetImporterToolTip->InitialDelay = 1000;
				this->PresetImporterToolTip->ReshowDelay = 100;
				// 
				// ProfileImporter
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->ClientSize = new System::Drawing::Size(383, 358);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->Name = "ProfileImporter";
				this->Text = "Preset Importer";
				this->Shown += new System::EventHandler(this, &ProfileImporter::ProfileImporter_Shown);
				this->Controls->SetChildIndex(this->profileList, 0);
				this->Controls->SetChildIndex(this->label1, 0);
				this->Controls->SetChildIndex(this->button2, 0);
				this->statusCheck->ResumeLayout(false);
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void ProfileImporter::InitializeInstanceFields()
			{
				ContextHelp = new XmlDocument();
				delete components;
			}
		}
	}
}
