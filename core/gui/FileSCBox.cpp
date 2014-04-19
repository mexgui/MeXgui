#include "FileSCBox.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;


using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace core
	{
		namespace gui
		{

			FileSCBox::FileSCBox() : StandardAndCustomComboBox("Clear user-selected files...", "Select file...")
			{
				InitializeInstanceFields();
				StandardAndCustomComboBox::Getter = new Getter(this, &FileSCBox::getter);
				StandardAndCustomComboBox::bSaveEveryItem = true;
			}

			object *FileSCBox::getter()
			{
				if (ofd->show() == DialogResult::OK)
					return ofd->FileName;
				return 0;
			}

			object *FileSCBox::getterFolder()
			{
				if (fbd->show() == DialogResult::OK)
				{
					MainForm::Instance->getSettings()->setLastUsedOneClickFolder(fbd->SelectedPath);
					return fbd->SelectedPath;
				}
				return 0;
			}

			const QString &FileSCBox::getFilter() const
			{
				return ofd->Filter;
			}

			void FileSCBox::setFilter(const QString &value)
			{
				ofd->Filter = value;
			}

			const MeXgui::core::gui::FileSCBox::FileSCBoxType &FileSCBox::getType() const
			{
				return oType;
			}

			void FileSCBox::setType(const FileSCBoxType &value)
			{
				oType = value;
				if (oType == OC_FILE || oType == OC_FILE_AND_FOLDER)
				{
					StandardAndCustomComboBox::SetFileSCBoxType("Select file...", "Select folder...", oType);
					if (oType == OC_FILE_AND_FOLDER)
					{
						StandardAndCustomComboBox::GetterFolder = new Getter(this, &FileSCBox::getterFolder);
						if (MainForm::Instance != 0 && System::IO::Directory::Exists(MainForm::Instance->getSettings()->getLastUsedOneClickFolder()))
							fbd->SelectedPath = MainForm::Instance->getSettings()->getLastUsedOneClickFolder();
					}
				}
			}

			void FileSCBox::InitializeInstanceFields()
			{
				ofd = new OpenFileDialog();
				fbd = new FolderBrowserDialog();
				oType = Default;
			}
		}
	}
}
