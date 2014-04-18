#include "MeGUI.core.gui.ProfileExporter.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;





//using namespace System::Text;



//using namespace System::Xml;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			ProfileExporter::ProfileExporter(MainForm *mainForm)
			{
				InitializeInstanceFields();
				InitializeComponent();
				this->mainForm = mainForm;

				setProfiles(mainForm->getProfiles()->getAllProfiles());
			}

			QVector<QString> ProfileExporter::getRequiredFiles(QVector<Profile*> &ps)
			{
				QVector<QString> files = QVector<QString>();

				for (QVector<Profile*>::const_iterator p = ps.begin(); p != ps.end(); ++p)
					files.AddRange((*p)->BaseSettings->RequiredFiles);

				return Util::Unique(files);
			}

			void ProfileExporter::export_Click(QObject *sender, QEvent *e)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Util::CatchExceptionsAndTellUser("An error occurred when saving the file", delegate
				{
					try
					{
						QString filename = askForFilename();
						tempFolder = FileUtil::CreateTempDirectory();
						QVector<Profile*> profs = getSelectedAndRequiredProfiles();
						std::QMap<QString, QString> subTable = copyExtraFilesToFolder(getRequiredFiles(profs), Path::Combine(tempFolder->FullName, "extra"));
						subTable = turnValuesToZippedStyleName(subTable);
						fixFileNames(profs, subTable);
						ProfileManager::WriteProfiles(tempFolder->FullName, profs);
						FileUtil::CreateZipFile(tempFolder->FullName, filename);
						FileUtil::DeleteDirectoryIfExists(tempFolder->FullName, true);
						DialogResult = DialogResult::OK;
						MessageBox::Show("Completed successfully", "Export completed successfully", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					catch (CancelledException *e1)
					{
						DialogResult = DialogResult::Cancel;
					}
				}
			   );
			}

			std::QMap<QString, QString> ProfileExporter::turnValuesToZippedStyleName(std::QMap<QString, QString> &subTable)
			{
				std::QMap<QString, QString> newTable = std::QMap<QString, QString>();
				for (std::QMap<QString, QString>::const_iterator key = subTable.begin(); key != subTable.end(); ++key)
					newTable[key->first] = getZippedExtraFileName(subTable[key->first]);
				return newTable;
			}

			QString ProfileExporter::askForFilename()
			{
				SaveFileDialog *outputFilesChooser = new SaveFileDialog();
				outputFilesChooser->Title = "Choose your output file";
				outputFilesChooser->Filter = "Zip archives|*.zip";
				if (outputFilesChooser->show() != DialogResult::OK)
					throw new CancelledException();

				return outputFilesChooser->FileName;
			}

			QString ProfileExporter::SelectHelpText(const QString &node)
			{
				StringBuilder *HelpText = new StringBuilder(64);

				QString xpath = "/ContextHelp/Form[@name='PresetExporter']/" + node;
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

			void ProfileExporter::SetToolTips()
			{
				PresetExporterToolTip->SetToolTip(this->profileList, SelectHelpText("presetList"));
			}

			void ProfileExporter::ProfileExporter_Shown(QObject *sender, QEvent *e)
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

			void ProfileExporter::checkAllToolStripMenuItem_Click(QObject *sender, QEvent *e)
			{
				ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(sender);
				for (int i = 0; i < profileList->Items->Count; i++)
				{
					profileList->SetItemChecked(i, true);
				}
			}

			void ProfileExporter::checkNoneToolStripMenuItem_Click(QObject *sender, QEvent *e)
			{
				ToolStripMenuItem *ts = static_cast<ToolStripMenuItem*>(sender);
				for (int i = 0; i < profileList->Items->Count; i++)
				{
					profileList->SetItemChecked(i, false);
				}
			}

			void ProfileExporter::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				MeGUI::core::gui::ProfilePorter::Dispose(disposing);
			}

			void ProfileExporter::InitializeComponent()
			{
				this->components = new System::ComponentModel::Container();
				System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(ProfileExporter::typeid);
				this->PresetExporterToolTip = new System::Windows::Forms::ToolTip(this->components);
				this->statusCheck = new System::Windows::Forms::ContextMenuStrip(this->components);
				this->checkAllToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->checkNoneToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->statusCheck->SuspendLayout();
				this->SuspendLayout();
				// 
				// label1
				// 
				this->label1->Location = new System::Drawing::Point(12, 7);
				this->label1->Size = new System::Drawing::Size(142, 13);
				this->label1->Text = "Select the presets to export";
				// 
				// button2
				// 
				this->button2->Location = new System::Drawing::Point(254, 323);
				this->button2->Size = new System::Drawing::Size(61, 23);
				this->button2->Text = "Export...";
				this->button2->Click += new System::EventHandler(this, &ProfileExporter::export_Click);
				// 
				// profileList
				// 
				this->profileList->ContextMenuStrip = this->statusCheck;
				// 
				// PresetExporterToolTip
				// 
				this->PresetExporterToolTip->AutoPopDelay = 5000;
				this->PresetExporterToolTip->InitialDelay = 1000;
				this->PresetExporterToolTip->ReshowDelay = 100;
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
				this->checkAllToolStripMenuItem->Click += new System::EventHandler(this, &ProfileExporter::checkAllToolStripMenuItem_Click);
				// 
				// checkNoneToolStripMenuItem
				// 
				this->checkNoneToolStripMenuItem->Name = "checkNoneToolStripMenuItem";
				this->checkNoneToolStripMenuItem->Size = new System::Drawing::Size(139, 22);
				this->checkNoneToolStripMenuItem->Text = "Check None";
				this->checkNoneToolStripMenuItem->Click += new System::EventHandler(this, &ProfileExporter::checkNoneToolStripMenuItem_Click);
				// 
				// ProfileExporter
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->ClientSize = new System::Drawing::Size(383, 358);
				this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
				this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
				this->Name = "ProfileExporter";
				this->Text = "Presets Exporter";
				this->Shown += new System::EventHandler(this, &ProfileExporter::ProfileExporter_Shown);
				this->Controls->SetChildIndex(this->profileList, 0);
				this->Controls->SetChildIndex(this->label1, 0);
				this->Controls->SetChildIndex(this->button2, 0);
				this->statusCheck->ResumeLayout(false);
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void ProfileExporter::InitializeInstanceFields()
			{
				ContextHelp = new XmlDocument();
				delete components;
			}
		}
	}
}
