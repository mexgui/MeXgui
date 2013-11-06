#include "MeGUI.core.gui.ProfileImporter.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml;
using namespace ICSharpCode::SharpZipLib::Zip;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			std::string ProfileImporter::askForZipFile()
			{
				OpenFileDialog *inputChooser = new OpenFileDialog();
				inputChooser->Filter = "Zip archives|*.zip";
				inputChooser->Title = "Select your input file";

				if (inputChooser->ShowDialog() != DialogResult::OK)
					throw new CancelledException();

				return inputChooser->FileName;
			}

			ProfileImporter::ProfileImporter(MainForm *mf, bool bSilentError)
			{
				InitializeInstanceFields();
			}

			ProfileImporter::ProfileImporter(MainForm *mf, const std::string &filename, bool bSilentError)
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
				std::vector<Profile*> ps = ProfileManager::ReadAllProfiles(tempFolder->FullName, bSilentError);

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

			std::map<std::string, std::string> ProfileImporter::createInitSubTable()
			{
				std::map<std::string, std::string> d = std::map<std::string, std::string>();

				for (unknown::const_iterator f = extraFiles->GetFiles().begin(); f != extraFiles->GetFiles().end(); ++f)
					d[getZippedExtraFileName((*f)->Name)] = (*f)->FullName;

				return d;
			}

			const std::vector<std::string> &ProfileImporter::getextraFilesList() const
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				return (std::vector<FileInfo*>(extraFiles->GetFiles()))->ConvertAll<std::string>(delegate(FileInfo f)
				{
					return f->FullName;
				}
			   );
			}

			void ProfileImporter::import_Click(object *sender, EventArgs *e)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Util::CatchExceptionsAndTellUser("Error importing file", delegate
				{
					std::vector<Profile*> ps = getSelectedAndRequiredProfiles();
					fixFileNames(ps, copyExtraFilesToFolder(getextraFilesList(), Path::Combine(mainForm->getMeGUIPath(), "extra")));
					mainForm->getProfiles()->AddAll(ps.ToArray(), mainForm->getDialogManager());
					DialogResult = DialogResult::OK;
					mainForm->setImportProfileSuccessful(true);
					this->Close();
				}
			   );
			}

			void ProfileImporter::checkAllToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(sender);
				for (int i = 0; i < profileList->Items->Count; i++)
				{
					profileList->SetItemChecked(i, true);
				}
			}

			void ProfileImporter::checkNoneToolStripMenuItem_Click(object *sender, EventArgs *e)
			{
				ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(sender);
				for (int i = 0; i < profileList->Items->Count; i++)
				{
					profileList->SetItemChecked(i, false);
				}
			}

			std::string ProfileImporter::SelectHelpText(const std::string &node)
			{
				StringBuilder *HelpText = new StringBuilder(64);

				std::string xpath = "/ContextHelp/Form[@name='PresetImporter']/" + node;
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

			void ProfileImporter::ProfileImporter_Shown(object *sender, EventArgs *e)
			{
				try
				{
					std::string p = System::IO::Path::Combine(Application::StartupPath, "Data");
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
				MeGUI::core::gui::ProfilePorter::Dispose(disposing);
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
